//
// Created by forkernel on 2025/4/9.
//

#include "base85.h"

namespace YanLib::crypto {
    std::vector<unsigned char> base85::encode(const std::vector<unsigned char> &data) {
        constexpr unsigned char BASE85_CHARS[] =
                "!\"#$%&'()*+,-./0123456789:;<=>?@"
                "ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstu";
        if (data.empty()) return {};

        std::vector<unsigned char> result;
        const size_t output_size = ((data.size() + 3) / 4) * 5;
        result.reserve(output_size);

        const uint8_t *ptr = data.data();
        const uint8_t *end = ptr + data.size();

        while (ptr < end) {
            uint32_t value = 0;
            const int valid_bytes = std::min(4,
                                             static_cast<int>(end - ptr));

            for (int j = 0; j < valid_bytes; ++j) {
                value = (value << 8) | ptr[j];
            }
            ptr += valid_bytes;

            if (valid_bytes < 4) {
                value <<= (8 * (4 - valid_bytes));
            }

            if (value == 0 && valid_bytes == 4) {
                result.push_back('z');
                continue;
            }

            std::vector<uint32_t> digits(5, 0);
            for (int j = 4; j >= 0; --j) {
                digits[j] = value % 85;
                value /= 85;
            }

            const int encode_chars = valid_bytes + 1;
            for (int j = 0; j < encode_chars; ++j) {
                result.push_back(BASE85_CHARS[digits[j]]);
            }
        }

        return result;
    }

    std::vector<unsigned char> base85::decode(const std::vector<unsigned char> &data) {
        constexpr unsigned char BASE85_CHARS[] =
                "!\"#$%&'()*+,-./0123456789:;<=>?@"
                "ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstu";
        if (data.empty()) return {};

        std::vector<unsigned char> table(256, 0xFF);
        for (int i = 0; i < 85; ++i) {
            table[static_cast<uint8_t>(BASE85_CHARS[i])] = i;
        }
        table['z'] = 0;

        std::vector<unsigned char> result;
        result.reserve((data.size() * 4) / 5);
        if (data.empty() || data.size() % 5 != 0) return {};
        for (size_t i = 0; i < data.size();) {
            if (data[i] == 'z') {
                result.insert(result.end(), 4, 0x00);
                ++i;
                continue;
            }

            uint32_t value = 0;
            for (int j = 0; j < 5; ++j) {
                const uint8_t c = data[i + j];
                const uint8_t digit = table[c];

                if (digit == 0xFF && c != 'z') return {};

                value = value * 85 + digit;
            }

            result.push_back(static_cast<uint8_t>(value >> 24));
            result.push_back(static_cast<uint8_t>((value >> 16) & 0xFF));
            result.push_back(static_cast<uint8_t>((value >> 8) & 0xFF));
            result.push_back(static_cast<uint8_t>(value & 0xFF));
            i += 5;
        }

        if (!data.empty() && data.back() == '=') {
            const auto padding = std::count(data.end() - 5,
                                            data.end(),
                                            '=');
            result.resize(result.size() - (4 - padding));
        }

        return result;
    }

    std::string base85::encode_string(const std::string &data) {
        std::vector<unsigned char> input(data.begin(), data.end());
        std::vector<unsigned char> encoded = encode(input);
        std::string result(encoded.begin(), encoded.end());
        return result;
    }

    std::string base85::decode_string(const std::string &data) {
        std::vector<unsigned char> input(data.begin(), data.end());
        std::vector<unsigned char> decoded = decode(input);
        std::string result(decoded.begin(), decoded.end());
        return result;
    }
}
