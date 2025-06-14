/* clang-format off */
/*
 * @file base92.cpp
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
#include "base92.h"
#include <bitset>

namespace YanLib::crypto {
    std::vector<uint8_t> base92::encode(const std::vector<uint8_t> &data) {
        // The valid character set of Base92 consists of 91 characters,
        // of which '~' is a placeholder, not in the character set
        constexpr uint8_t BASE92_CHARS[] =
                "!#$%&'()*+,-./"
                "0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_"
                "abcdefghijklmnopqrstuvwxyz{|}";
        if (data.empty())
            return {};

        std::string bitstr;
        for (const auto b : data) {
            bitstr += std::bitset<8>(b).to_string();
        }

        std::vector<uint8_t> result;
        size_t pos = 0;
        while (pos < bitstr.length()) {
            std::string chunk = bitstr.substr(pos, 13);
            pos += chunk.length();

            if (chunk.length() < 13) {
                if (chunk.length() <= 6) {
                    chunk += std::string(6 - chunk.length(), '0');
                    const int32_t val = static_cast<int32_t>(
                            std::bitset<6>(chunk).to_ulong());
                    result.push_back(BASE92_CHARS[val]);
                } else {
                    chunk += std::string(13 - chunk.length(), '0');
                    const int32_t high = static_cast<int32_t>(
                            std::bitset<13>(chunk).to_ulong() / 91);
                    const int32_t low = static_cast<int32_t>(
                            std::bitset<13>(chunk).to_ulong() % 91);
                    result.push_back(BASE92_CHARS[high]);
                    result.push_back(BASE92_CHARS[low]);
                }
                break;
            }

            const int32_t high = static_cast<int32_t>(
                    std::bitset<13>(chunk).to_ulong() / 91);
            const int32_t low = static_cast<int32_t>(
                    std::bitset<13>(chunk).to_ulong() % 91);
            result.push_back(BASE92_CHARS[high]);
            result.push_back(BASE92_CHARS[low]);
        }

        return result;
    }

    std::vector<uint8_t> base92::decode(const std::vector<uint8_t> &data) {
        // The valid character set of Base92 consists of 91 characters,
        // of which '~' is a placeholder, not in the character set
        constexpr uint8_t BASE92_CHARS[] =
                "!#$%&'()*+,-./"
                "0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_"
                "abcdefghijklmnopqrstuvwxyz{|}";
        if (data.empty())
            return {};

        std::vector table(256, -1);
        for (int32_t i = 0; i < sizeof(BASE92_CHARS) - 1; ++i) {
            table[BASE92_CHARS[i]] = i;
        }

        std::string bitstr;
        for (size_t i = 0; i < data.size(); ++i) {
            if (i + 1 < data.size()) {
                const int32_t high = table[data[i]];
                const int32_t low = table[data[i + 1]];
                if (high == -1 || low == -1)
                    return {};

                const int32_t combined = high * 91 + low;
                bitstr += std::bitset<13>(combined).to_string();
                ++i;
            } else {
                const int32_t val = table[data[i]];
                if (val == -1)
                    return {};
                bitstr += std::bitset<6>(val).to_string().substr(0, 6);
            }
        }

        std::vector<uint8_t> result;
        for (size_t i = 0; i + 8 <= bitstr.length(); i += 8) {
            std::string byte = bitstr.substr(i, 8);
            result.push_back(
                    static_cast<uint8_t>(std::bitset<8>(byte).to_ulong()));
        }
        return result;
    }

    std::string base92::encode_string(const std::string &data) {
        const std::vector<uint8_t> input(data.begin(), data.end());
        std::vector<uint8_t> encoded = encode(input);
        std::string result(encoded.begin(), encoded.end());
        return result;
    }

    std::string base92::decode_string(const std::string &data) {
        const std::vector<uint8_t> input(data.begin(), data.end());
        std::vector<uint8_t> decoded = decode(input);
        std::string result(decoded.begin(), decoded.end());
        return result;
    }
} // namespace YanLib::crypto
