//
// Created by forkernel on 2025/4/10.
//

#include "vigenere.h"

namespace YanLib::crypto {
    std::vector<uint8_t> vigenere::encode(const std::vector<uint8_t> &data,
                                                const std::vector<uint8_t> &key) {
        if (data.empty() || key.empty()) return {};
        std::vector<uint8_t> result;
        for (const auto k: key) {
            if (!((k >= 'a' && k <= 'z') ||
                  (k >= 'A' && k <= 'Z')))
                return {};
        }

        size_t key_index = 0;
        for (auto c: data) {
            if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {
                const uint8_t base = (c >= 'a') ? 'a' : 'A';
                const int offset = (key[key_index % key.size()] >= 'A' &&
                                    key[key_index % key.size()] <= 'Z')
                                       ? (key[key_index % key.size()] - 'A')
                                       : (key[key_index % key.size()] - 'a');
                const int shifted = (c - base + offset) % 26;
                result.push_back(static_cast<uint8_t>(base + shifted));
                key_index++;
            } else {
                result.push_back(c);
            }
        }
        return result;
    }

    std::vector<uint8_t> vigenere::decode(const std::vector<uint8_t> &data,
                                                const std::vector<uint8_t> &key) {
        if (data.empty() || key.empty()) return {};
        std::vector<uint8_t> result;

        for (const auto k: key) {
            if (!((k >= 'a' && k <= 'z') ||
                  (k >= 'A' && k <= 'Z')))
                return {};
        }

        size_t key_index = 0;
        for (auto c: data) {
            if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {
                const uint8_t base = (c >= 'a') ? 'a' : 'A';
                const int offset = (key[key_index % key.size()] >= 'A' &&
                                    key[key_index % key.size()] <= 'Z')
                                       ? (key[key_index % key.size()] - 'A')
                                       : (key[key_index % key.size()] - 'a');
                const int shifted = (c - base - offset + 26) % 26;
                result.push_back(static_cast<uint8_t>(base + shifted));
                key_index++;
            } else {
                result.push_back(c);
            }
        }
        return result;
    }

    std::string vigenere::encode_string(const std::string &data,
                                        const std::string &key) {
        std::vector<uint8_t> encode_data(data.begin(), data.end());
        std::vector<uint8_t> encode_key(key.begin(), key.end());
        std::vector<uint8_t> encoded = encode(encode_data, encode_key);
        std::string result(encoded.begin(), encoded.end());
        return result;
    }

    std::string vigenere::decode_string(const std::string &data,
                                        const std::string &key) {
        std::vector<uint8_t> decode_data(data.begin(), data.end());
        std::vector<uint8_t> decode_key(key.begin(), key.end());
        std::vector<uint8_t> decoded = decode(decode_data, decode_key);
        std::string result(decoded.begin(), decoded.end());
        return result;
    }
}
