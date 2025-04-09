//
// Created by forkernel on 2025/4/9.
//

#include "base62.h"

namespace YanLib::crypto {
    std::vector<unsigned char> base62::encode(const std::vector<unsigned char> &data) {
        constexpr unsigned char BASE62_CHARS[] =
                "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

        if (data.empty()) return {};

        std::vector<unsigned char> result;
        result.reserve(static_cast<size_t>(data.size() * 1.37) + 3);
        std::vector<uint32_t> digits(data.begin(), data.end());

        while (!digits.empty()) {
            uint32_t remainder = 0;
            std::vector<uint32_t> new_digits;
            new_digits.reserve(digits.size());

            for (const uint32_t num: digits) {
                uint64_t val = static_cast<uint64_t>(remainder) * 256 + num;
                uint32_t quot = static_cast<uint32_t>(val / 62);
                remainder = static_cast<uint32_t>(val % 62);

                if (!new_digits.empty() || quot != 0) {
                    new_digits.push_back(quot);
                }
            }

            result.push_back(remainder);
            digits.assign(new_digits.begin(), new_digits.end());
        }

        std::reverse(result.begin(), result.end());

        std::vector<unsigned char> encoded;
        encoded.reserve(result.size());
        for (const uint8_t num: result) {
            encoded.push_back(BASE62_CHARS[num]);
        }

        return encoded;
    }

    std::vector<unsigned char> base62::decode(const std::vector<unsigned char> &data) {
        constexpr unsigned char BASE62_CHARS[] =
                "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
        if (data.empty()) return {};
        std::vector<unsigned char> table(256, -1);
        for (int i = 0; i < 62; i++) {
            table[BASE62_CHARS[i]] = i;
        }
        std::vector<unsigned char> result;
        for (const auto c: data) {
            size_t pos = table[c];
            if (pos == -1) {
                return {};
            }
            unsigned int num = static_cast<unsigned int>(pos);

            unsigned int carry = num;
            for (int i = result.size() - 1; i >= 0; --i) {
                unsigned int temp = result[i] * 62 + carry;
                result[i] = static_cast<unsigned char>(temp % 256);
                carry = temp / 256;
            }

            while (carry > 0) {
                result.insert(result.begin(), carry % 256);
                carry /= 256;
            }
        }

        if (!data.empty() && result.empty()) {
            result.push_back(0);
        }

        return result;
    }

    std::string base62::encode_string(const std::string &data) {
        std::vector<unsigned char> input(data.begin(), data.end());
        std::vector<unsigned char> encoded = encode(input);
        std::string result(encoded.begin(), encoded.end());
        return result;
    }

    std::string base62::decode_string(const std::string &data) {
        std::vector<unsigned char> input(data.begin(), data.end());
        std::vector<unsigned char> decoded = decode(input);
        std::string result(decoded.begin(), decoded.end());
        return result;
    }
}
