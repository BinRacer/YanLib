//
// Created by forkernel on 2025/4/9.
//

#include "base32.h"

namespace YanLib::crypto {
    std::vector<unsigned char> base32::encode(const std::vector<unsigned char> &data) {
        constexpr unsigned char BASE32_CHARS[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ234567";
        if (data.empty()) return {};
        std::vector<unsigned char> encoded;
        encoded.reserve((data.size() * 8 + 4) / 5 + 1);

        int buffer = 0, bits_left = 0;
        for (const unsigned char c: data) {
            buffer = (buffer << 8) | c;
            bits_left += 8;

            while (bits_left >= 5) {
                const int idx = (buffer >> (bits_left - 5)) & 0x1F;
                encoded.push_back(BASE32_CHARS[idx]);
                bits_left -= 5;
            }
        }

        if (bits_left > 0) {
            const int idx = (buffer << (5 - bits_left)) & 0x1F;
            encoded.push_back(BASE32_CHARS[idx]);
        }

        while (encoded.size() % 8 != 0) {
            encoded.push_back('=');
        }
        return encoded;
    }

    std::vector<unsigned char> base32::decode(const std::vector<unsigned char> &data) {
        constexpr unsigned char BASE32_CHARS[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ234567";
        if (data.empty()) return {};
        std::vector<int> table(256, -1);
        for (int i = 0; i < 32; ++i) {
            const auto c = BASE32_CHARS[i];
            table[c] = i;
            table[tolower(c)] = i;
        }
        std::vector<unsigned char> decoded;
        decoded.reserve((data.size() * 5) / 8);

        int buffer = 0, bits_collected = 0;
        for (const unsigned char c: data) {
            if (c == '=') break;

            const int idx = table[c];
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
        std::vector<unsigned char> input(data.begin(), data.end());
        std::vector<unsigned char> encoded = encode(input);
        std::string result(encoded.begin(), encoded.end());
        return result;
    }

    std::string base32::decode_string(const std::string &data) {
        std::vector<unsigned char> input(data.begin(), data.end());
        std::vector<unsigned char> decoded = decode(input);
        std::string result(decoded.begin(), decoded.end());
        return result;
    }
}
