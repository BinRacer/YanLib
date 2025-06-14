/* clang-format off */
/*
 * @file base100.cpp
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
#include "base100.h"

namespace YanLib::crypto {
    std::vector<uint8_t> base100::encode(const std::vector<uint8_t> &data) {
        if (data.empty())
            return {};
        std::vector<uint8_t> result;
        result.reserve(data.size() * 4);

        for (const auto ch : data) {
            const uint32_t temp = static_cast<uint32_t>(ch) + 55;
            uint8_t byte3 = (temp >> 6) + 143;
            uint8_t byte4 = (temp & 0x3F) + 128;

            result.push_back(0xF0);
            result.push_back(0x9F);
            result.push_back(byte3);
            result.push_back(byte4);
        }
        return result;
    }

    std::vector<uint8_t> base100::decode(const std::vector<uint8_t> &data) {
        std::vector<uint8_t> result;

        if (data.empty() || data.size() % 4 != 0)
            return {};
        result.reserve(data.size() / 4);

        for (size_t i = 0; i < data.size(); i += 4) {
            if (data[i] != 0xF0 || data[i + 1] != 0x9F)
                return {};

            const uint8_t byte3 = data[i + 2];
            const uint8_t byte4 = data[i + 3];

            int32_t decoded = ((byte3 - 143) << 6) | (byte4 - 128);
            decoded -= 55;

            if (decoded < 0 || decoded > 255)
                return {};

            result.push_back(static_cast<uint8_t>(decoded));
        }
        return result;
    }

    std::string base100::encode_string(const std::string &data) {
        const std::vector<uint8_t> input(data.begin(), data.end());
        std::vector<uint8_t> encoded = encode(input);
        std::string result(encoded.begin(), encoded.end());
        return result;
    }

    std::string base100::decode_string(const std::string &data) {
        const std::vector<uint8_t> input(data.begin(), data.end());
        std::vector<uint8_t> decoded = decode(input);
        std::string result(decoded.begin(), decoded.end());
        return result;
    }
} // namespace YanLib::crypto
