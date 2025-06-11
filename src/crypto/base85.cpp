/* clang-format off */
/*
 * @file base85.cpp
 * @date 2025-04-09
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
#include "base85.h"

namespace YanLib::crypto {
    std::vector<uint8_t> base85::encode(const std::vector<uint8_t> &data) {
        constexpr uint8_t BASE85_CHARS[] = "!\"#$%&'()*+,-./0123456789:;<=>?@"
                                           "ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`"
                                           "abcdefghijklmnopqrstu";
        if (data.empty())
            return {};
        std::vector<uint8_t> encoded;
        const size_t padding = (4 - (data.size() % 4)) % 4;
        std::vector padded(data);
        padded.insert(padded.end(), padding, 0);

        for (size_t i = 0; i < padded.size(); i += 4) {
            uint32_t chunk = (padded[i] << 24) | (padded[i + 1] << 16) |
                    (padded[i + 2] << 8) | padded[i + 3];
            if (chunk == 0) {
                encoded.push_back('z');
                continue;
            }

            uint8_t buf[5];
            for (int32_t j = 4; j >= 0; --j) {
                buf[j] = BASE85_CHARS[chunk % 85];
                chunk /= 85;
            }
            encoded.insert(encoded.end(), buf, buf + 5);
        }
        if (padding)
            encoded.resize(encoded.size() - padding);
        return encoded;
    }

    std::vector<uint8_t> base85::decode(const std::vector<uint8_t> &data) {
        constexpr uint8_t BASE85_CHARS[] = "!\"#$%&'()*+,-./0123456789:;<=>?@"
                                           "ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`"
                                           "abcdefghijklmnopqrstu";
        if (data.empty())
            return {};
        std::vector table(256, -1);
        for (int32_t i = 0; i < 85; ++i) {
            table[BASE85_CHARS[i]] = i;
        }
        std::vector<uint8_t> decoded;
        std::vector<uint8_t> buffer;

        for (auto c : data) {
            if (std::isspace(c))
                continue;
            if (c == 'z') {
                if (!buffer.empty())
                    return {};
                decoded.insert(decoded.end(), 4, 0x00);
                continue;
            }

            buffer.push_back(c);
            if (buffer.size() == 5) {
                uint32_t chunk = 0;
                for (int32_t j = 0; j < 5; ++j) {
                    const auto pos = table[buffer[j]];
                    if (pos == -1)
                        return {};
                    chunk = chunk * 85 + pos;
                }

                decoded.push_back((chunk >> 24) & 0xFF);
                decoded.push_back((chunk >> 16) & 0xFF);
                decoded.push_back((chunk >> 8) & 0xFF);
                decoded.push_back(chunk & 0xFF);
                buffer.clear();
            }
        }

        if (!buffer.empty()) {
            const size_t padding = 5 - buffer.size();
            for (size_t i = 0; i < padding; ++i)
                buffer.push_back('u');

            uint32_t chunk = 0;
            for (int32_t j = 0; j < 5; ++j) {
                const auto pos = table[buffer[j]];
                if (pos == -1)
                    return {};
                chunk = chunk * 85 + pos;
            }

            const size_t valid_bytes = 4 - padding;
            for (size_t j = 0; j < valid_bytes; ++j) {
                decoded.push_back((chunk >> (24 - j * 8)) & 0xFF);
            }
        }
        return decoded;
    }

    std::string base85::encode_string(const std::string &data) {
        const std::vector<uint8_t> input(data.begin(), data.end());
        std::vector<uint8_t> encoded = encode(input);
        std::string result(encoded.begin(), encoded.end());
        return result;
    }

    std::string base85::decode_string(const std::string &data) {
        const std::vector<uint8_t> input(data.begin(), data.end());
        std::vector<uint8_t> decoded = decode(input);
        std::string result(decoded.begin(), decoded.end());
        return result;
    }
} // namespace YanLib::crypto
