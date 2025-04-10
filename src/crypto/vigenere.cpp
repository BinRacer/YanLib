//
// Created by forkernel on 2025/4/10.
//

#include "vigenere.h"

namespace YanLib::crypto {
    std::vector<unsigned char> vigenere::encode(const std::vector<unsigned char> &data,
                                                const std::vector<unsigned char> &key) {
        if (data.empty() || key.empty()) return {};
        std::vector<unsigned char> result;
        for (const auto k: key) {
            if (!((k >= 'a' && k <= 'z') ||
                  (k >= 'A' && k <= 'Z')))
                return {};
        }

        size_t keyIndex = 0;
        for (auto c: data) {
            if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {
                const unsigned char base = (c >= 'a') ? 'a' : 'A';
                const int offset = (key[keyIndex % key.size()] >= 'A' &&
                                    key[keyIndex % key.size()] <= 'Z')
                                       ? (key[keyIndex % key.size()] - 'A')
                                       : (key[keyIndex % key.size()] - 'a');
                const int shifted = (c - base + offset) % 26;
                result.push_back(static_cast<unsigned char>(base + shifted));
                keyIndex++;
            } else {
                result.push_back(c);
            }
        }
        return result;
    }

    std::vector<unsigned char> vigenere::decode(const std::vector<unsigned char> &data,
                                                const std::vector<unsigned char> &key) {
        if (data.empty() || key.empty()) return {};
        std::vector<unsigned char> result;

        for (const auto k: key) {
            if (!((k >= 'a' && k <= 'z') ||
                  (k >= 'A' && k <= 'Z')))
                return {};
        }

        size_t keyIndex = 0;
        for (auto c: data) {
            if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {
                const unsigned char base = (c >= 'a') ? 'a' : 'A';
                const int offset = (key[keyIndex % key.size()] >= 'A' &&
                                    key[keyIndex % key.size()] <= 'Z')
                                       ? (key[keyIndex % key.size()] - 'A')
                                       : (key[keyIndex % key.size()] - 'a');
                const int shifted = (c - base - offset + 26) % 26;
                result.push_back(static_cast<unsigned char>(base + shifted));
                keyIndex++;
            } else {
                result.push_back(c);
            }
        }
        return result;
    }

    std::string vigenere::encode_string(const std::string &data,
                                        const std::string &key) {
        std::vector<unsigned char> encode_data(data.begin(), data.end());
        std::vector<unsigned char> encode_key(key.begin(), key.end());
        std::vector<unsigned char> encoded = encode(encode_data, encode_key);
        std::string result(encoded.begin(), encoded.end());
        return result;
    }

    std::string vigenere::decode_string(const std::string &data,
                                        const std::string &key) {
        std::vector<unsigned char> decode_data(data.begin(), data.end());
        std::vector<unsigned char> decode_key(key.begin(), key.end());
        std::vector<unsigned char> decoded = decode(decode_data, decode_key);
        std::string result(decoded.begin(), decoded.end());
        return result;
    }
}
