//
// Created by forkernel on 2025/4/9.
//

#include "base32.h"

namespace YanLib::crypto {
    std::vector<uint8_t> base32::encode(const std::vector<uint8_t> &data) {
        constexpr uint8_t BASE32_CHARS[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ234567";
        if (data.empty()) return {};
        std::vector<uint8_t> encoded;
        encoded.reserve((data.size() * 8 + 4) / 5 + 1);

        int32_t buffer = 0, bits_left = 0;
        for (const uint8_t c: data) {
            buffer = (buffer << 8) | c;
            bits_left += 8;

            while (bits_left >= 5) {
                const int32_t idx = (buffer >> (bits_left - 5)) & 0x1F;
                encoded.push_back(BASE32_CHARS[idx]);
                bits_left -= 5;
            }
        }

        if (bits_left > 0) {
            const int32_t idx = (buffer << (5 - bits_left)) & 0x1F;
            encoded.push_back(BASE32_CHARS[idx]);
        }

        while (encoded.size() % 8 != 0) {
            encoded.push_back('=');
        }
        return encoded;
    }

    std::vector<uint8_t> base32::decode(const std::vector<uint8_t> &data) {
        constexpr uint8_t BASE32_CHARS[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ234567";
        if (data.empty()) return {};
        std::vector<int32_t> table(256, -1);
        for (int32_t i = 0; i < 32; ++i) {
            const auto c = BASE32_CHARS[i];
            table[c] = i;
            table[tolower(c)] = i;
        }
        std::vector<uint8_t> decoded;
        decoded.reserve((data.size() * 5) / 8);

        int32_t buffer = 0, bits_collected = 0;
        for (const uint8_t c: data) {
            if (c == '=') break;

            const int32_t idx = table[c];
            if (idx == -1) return {};

            buffer = (buffer << 5) | idx;
            bits_collected += 5;

            if (bits_collected >= 8) {
                decoded.push_back((buffer >> (bits_collected - 8)) & 0xFF);
                bits_collected -= 8;
            }
        }
        return decoded;
    }

    std::string base32::encode_string(const std::string &data) {
        std::vector<uint8_t> input(data.begin(), data.end());
        std::vector<uint8_t> encoded = encode(input);
        std::string result(encoded.begin(), encoded.end());
        return result;
    }

    std::string base32::decode_string(const std::string &data) {
        std::vector<uint8_t> input(data.begin(), data.end());
        std::vector<uint8_t> decoded = decode(input);
        std::string result(decoded.begin(), decoded.end());
        return result;
    }
}
