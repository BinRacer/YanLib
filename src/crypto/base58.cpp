/* clang-format off */
/*
 * @file base58.cpp
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
#include "base58.h"

namespace YanLib::crypto {
    std::vector<uint8_t> base58::encode(const std::vector<uint8_t> &data) {
        constexpr uint8_t BASE58_CHARS[] =
                "123456789ABCDEFGHJKLMNPQRSTUVWXYZabcdefghijkmnopqrstuvwxyz";
        if (data.empty())
            return {};
        size_t leading_zeros = 0;
        while (leading_zeros < data.size() && data[leading_zeros] == 0) {
            ++leading_zeros;
        }
        std::vector<int32_t> digits;
        for (const uint8_t byte : data) {
            int32_t carry = byte;
            for (auto &digit : digits) {
                carry += digit * 256;
                digit = carry % 58;
                carry /= 58;
            }
            while (carry > 0) {
                digits.push_back(carry % 58);
                carry /= 58;
            }
        }
        std::vector<uint8_t> result(leading_zeros, '1');
        for (auto it = digits.rbegin(); it != digits.rend(); ++it) {
            result.push_back(BASE58_CHARS[*it]);
        }
        return result;
    }

    std::vector<uint8_t> base58::decode(const std::vector<uint8_t> &data) {
        static const std::vector<int32_t> table = [] {
            std::vector t(256, -1);
            constexpr uint8_t BASE58_CHARS[] = "123456789ABCDEFGHJKLMNPQRSTUVWX"
                                               "YZabcdefghijkmnopqrstuvwxyz";
            for (int32_t i = 0; i < 58; ++i) {
                t[BASE58_CHARS[i]] = i;
            }
            return t;
        }();

        if (data.empty())
            return {};

        size_t leading_ones = 0;
        while (leading_ones < data.size() && data[leading_ones] == '1') {
            ++leading_ones;
        }

        const size_t max_bytes = (data.size() - leading_ones) * 138 / 100 + 1;
        std::vector<uint8_t> bytes;
        bytes.reserve(max_bytes);

        for (size_t i = leading_ones; i < data.size(); ++i) {
            const uint8_t c = data[i];
            const int32_t pos = table[c];
            if (pos == -1)
                return {};

            int32_t carry = pos;
            for (auto &byte : bytes) {
                carry += static_cast<int32_t>(byte) * 58;
                byte = carry % 256;
                carry /= 256;
            }

            while (carry > 0) {
                bytes.push_back(carry % 256);
                carry /= 256;
            }
        }

        std::vector<uint8_t> result;
        result.reserve(leading_ones + bytes.size());
        result.insert(result.end(), leading_ones, 0x00);
        result.insert(result.end(), bytes.rbegin(), bytes.rend());
        return result;
    }

    std::string base58::encode_string(const std::string &data) {
        const std::vector<uint8_t> input(data.begin(), data.end());
        std::vector<uint8_t> encoded = encode(input);
        std::string result(encoded.begin(), encoded.end());
        return result;
    }

    std::string base58::decode_string(const std::string &data) {
        const std::vector<uint8_t> input(data.begin(), data.end());
        std::vector<uint8_t> decoded = decode(input);
        std::string result(decoded.begin(), decoded.end());
        return result;
    }
} // namespace YanLib::crypto
