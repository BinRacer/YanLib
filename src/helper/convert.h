/* clang-format off */
/*
 * @file convert.h
 * @date 2025-04-05
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
#ifndef CONVERT_H
#define CONVERT_H
#include <Windows.h>
#include <string>
#include "helper.h"
namespace YanLib::helper {
    class convert {
    public:
        convert(const convert &other) = delete;

        convert(convert &&other) = delete;

        convert &operator=(const convert &other) = delete;

        convert &operator=(convert &&other) = delete;

        convert() = delete;

        ~convert() = delete;

        static std::wstring str_to_wstr(const std::string &str,
                                        CodePage code_page = curr_code_page());

        static std::string wstr_to_str(const std::wstring &wstr,
                                       CodePage code_page = curr_code_page());

        static std::string err_string(uint32_t error_code);

        static std::wstring err_wstring(uint32_t error_code);
    };
} // namespace YanLib::helper
#endif // CONVERT_H
