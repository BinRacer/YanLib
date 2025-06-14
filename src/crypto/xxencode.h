/* clang-format off */
/*
 * @file xxencode.h
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
#ifndef XXENCODE_H
#define XXENCODE_H
#include <vector>
#include <string>

namespace YanLib::crypto {
    class xxencode {
    public:
        xxencode(const xxencode &other) = delete;

        xxencode(xxencode &&other) = delete;

        xxencode &operator=(const xxencode &other) = delete;

        xxencode &operator=(xxencode &&other) = delete;

        xxencode() = default;

        ~xxencode() = default;

        static std::vector<uint8_t> encode(const std::vector<uint8_t> &data);

        static std::vector<uint8_t> decode(const std::vector<uint8_t> &data);

        static std::string encode_string(const std::string &data);

        static std::string decode_string(const std::string &data);
    };
} // namespace YanLib::crypto
#endif // XXENCODE_H
