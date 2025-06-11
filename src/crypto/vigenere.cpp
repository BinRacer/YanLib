/* clang-format off */
/*
 * @file vigenere.cpp
 * @date 2025-04-10
 * @license MIT License
 *
 * Copyright (c) 2025 BinRacer <native.lab@outlook.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
/* clang-format on */
#include "vigenere.h"

namespace YanLib::crypto {
    std::vector<uint8_t> vigenere::encode(const std::vector<uint8_t> &data,
                                          const std::vector<uint8_t> &key) {
        if (data.empty() || key.empty())
            return {};
        std::vector<uint8_t> result;
        for (const auto k : key) {
            if (!((k >= 'a' && k <= 'z') || (k >= 'A' && k <= 'Z')))
                return {};
        }

        size_t key_index = 0;
        for (auto c : data) {
            if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {
                const uint8_t base = (c >= 'a') ? 'a' : 'A';
                const int32_t offset = (key[key_index % key.size()] >= 'A' &&
                                        key[key_index % key.size()] <= 'Z')
                        ? (key[key_index % key.size()] - 'A')
                        : (key[key_index % key.size()] - 'a');
                const int32_t shifted = (c - base + offset) % 26;
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
        if (data.empty() || key.empty())
            return {};
        std::vector<uint8_t> result;

        for (const auto k : key) {
            if (!((k >= 'a' && k <= 'z') || (k >= 'A' && k <= 'Z')))
                return {};
        }

        size_t key_index = 0;
        for (auto c : data) {
            if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {
                const uint8_t base = (c >= 'a') ? 'a' : 'A';
                const int32_t offset = (key[key_index % key.size()] >= 'A' &&
                                        key[key_index % key.size()] <= 'Z')
                        ? (key[key_index % key.size()] - 'A')
                        : (key[key_index % key.size()] - 'a');
                const int32_t shifted = (c - base - offset + 26) % 26;
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
        const std::vector<uint8_t> encode_data(data.begin(), data.end());
        const std::vector<uint8_t> encode_key(key.begin(), key.end());
        std::vector<uint8_t> encoded = encode(encode_data, encode_key);
        std::string result(encoded.begin(), encoded.end());
        return result;
    }

    std::string vigenere::decode_string(const std::string &data,
                                        const std::string &key) {
        const std::vector<uint8_t> decode_data(data.begin(), data.end());
        const std::vector<uint8_t> decode_key(key.begin(), key.end());
        std::vector<uint8_t> decoded = decode(decode_data, decode_key);
        std::string result(decoded.begin(), decoded.end());
        return result;
    }
} // namespace YanLib::crypto
