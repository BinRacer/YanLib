/* clang-format off */
/*
 * @file base58.h
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
#ifndef BASE58_H
#define BASE58_H
#include <string>
#include <vector>

namespace YanLib::crypto {
    class base58 {
    public:
        base58(const base58 &other) = delete;

        base58(base58 &&other) = delete;

        base58 &operator=(const base58 &other) = delete;

        base58 &operator=(base58 &&other) = delete;

        base58() = default;

        ~base58() = default;

        static std::vector<uint8_t> encode(const std::vector<uint8_t> &data);

        static std::vector<uint8_t> decode(const std::vector<uint8_t> &data);

        static std::string encode_string(const std::string &data);

        static std::string decode_string(const std::string &data);
    };
} // namespace YanLib::crypto
#endif // BASE58_H
