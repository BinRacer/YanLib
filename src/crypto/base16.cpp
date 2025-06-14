/* clang-format off */
/*
 * @file base16.cpp
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
#include "base16.h"

namespace YanLib::crypto {
    std::vector<uint8_t> base16::encode(const std::vector<uint8_t> &data) {
        constexpr uint8_t BASE16_CHARS[] = "0123456789ABCDEF";
        if (data.empty())
            return {};
        std::vector<uint8_t> encoded;
        encoded.reserve(data.size() * 2);

        for (const uint8_t c : data) {
            encoded.push_back(BASE16_CHARS[c >> 4]);
            encoded.push_back(BASE16_CHARS[c & 0x0F]);
        }
        return encoded;
    }

    std::vector<uint8_t> base16::decode(const std::vector<uint8_t> &data) {
        if (data.empty() || data.size() % 2 != 0)
            return {};

        auto char_to_nibble = [](const uint8_t c) -> int32_t {
            if (std::isdigit(c))
                return c - '0';
            if (c >= 'A' && c <= 'F')
                return c - 'A' + 10;
            if (c >= 'a' && c <= 'f')
                return c - 'a' + 10;
            return -1;
        };

        std::vector<uint8_t> decoded;
        decoded.reserve(data.size() / 2);
        for (size_t i = 0; i < data.size(); i += 2) {
            const int32_t hi = char_to_nibble(data[i]);
            const int32_t lo = char_to_nibble(data[i + 1]);
            if (hi == -1 || lo == -1)
                return {};
            decoded.push_back((hi << 4) | lo);
        }
        return decoded;
    }

    std::string base16::encode_string(const std::string &data) {
        const std::vector<uint8_t> input(data.begin(), data.end());
        std::vector<uint8_t> encoded = encode(input);
        std::string result(encoded.begin(), encoded.end());
        return result;
    }

    std::string base16::decode_string(const std::string &data) {
        const std::vector<uint8_t> input(data.begin(), data.end());
        std::vector<uint8_t> decoded = decode(input);
        std::string result(decoded.begin(), decoded.end());
        return result;
    }
} // namespace YanLib::crypto
