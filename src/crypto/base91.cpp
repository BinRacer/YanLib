/* clang-format off */
/*
 * @file base91.cpp
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
#include "base91.h"

namespace YanLib::crypto {
    std::vector<uint8_t> base91::encode(const std::vector<uint8_t> &data) {
        constexpr uint8_t BASE91_CHARS[] =
                "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                "abcdefghijklmnopqrstuvwxyz"
                "0123456789!#$%&()*+,./:;<=>?@[]^_`{|}~\"";
        if (data.empty())
            return {};
        std::vector<uint8_t> encoded;
        encoded.reserve(data.size());
        uint32_t b = 0;
        int32_t n = 0;
        for (const auto byte : data) {
            b |= static_cast<uint32_t>(byte) << n;
            n += 8;

            while (n >= 13) {
                uint32_t v = b & 0x1FFF;
                if (v > 88) {
                    b >>= 13;
                    n -= 13;
                } else {
                    v = b & 0x3FFF;
                    b >>= 14;
                    n -= 14;
                }
                encoded.push_back(BASE91_CHARS[v % 91]);
                encoded.push_back(BASE91_CHARS[v / 91]);
            }
        }

        if (n > 0) {
            encoded.push_back(BASE91_CHARS[b % 91]);
            if (n > 7 || b >= 91) {
                encoded.push_back(BASE91_CHARS[b / 91]);
            }
        }

        return encoded;
    }

    std::vector<uint8_t> base91::decode(const std::vector<uint8_t> &data) {
        constexpr uint8_t BASE91_CHARS[] =
                "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                "abcdefghijklmnopqrstuvwxyz"
                "0123456789!#$%&()*+,./:;<=>?@[]^_`{|}~\"";
        if (data.empty())
            return {};

        std::vector reverse_table(256, -1);
        for (int32_t i = 0; i < 91; ++i) {
            reverse_table[BASE91_CHARS[i]] = i;
        }

        std::vector<uint8_t> decoded;
        decoded.reserve(data.size() * 3 / 4);

        uint32_t buffer = 0;
        int32_t bits_count = 0;
        int32_t value = -1;

        for (const auto c : data) {
            const int32_t idx = reverse_table[c];
            if (idx == -1)
                continue;

            if (value < 0) {
                value = idx;
            } else {
                value += idx * 91;
                buffer |= value << bits_count;
                bits_count += (value & 0x1FFF) > 88 ? 13 : 14;

                while (bits_count >= 8) {
                    decoded.push_back(static_cast<uint8_t>(buffer & 0xFF));
                    buffer >>= 8;
                    bits_count -= 8;
                }
                value = -1;
            }
        }

        if (value != -1) {
            decoded.push_back(static_cast<uint8_t>(
                    (buffer | (value << bits_count)) & 0xFF));
        }
        return decoded;
    }

    std::string base91::encode_string(const std::string &data) {
        const std::vector<uint8_t> input(data.begin(), data.end());
        std::vector<uint8_t> encoded = encode(input);
        std::string result(encoded.begin(), encoded.end());
        return result;
    }

    std::string base91::decode_string(const std::string &data) {
        const std::vector<uint8_t> input(data.begin(), data.end());
        std::vector<uint8_t> decoded = decode(input);
        std::string result(decoded.begin(), decoded.end());
        return result;
    }
} // namespace YanLib::crypto
