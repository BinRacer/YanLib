/* clang-format off */
/*
 * @file string.cpp
 * @date 2025-04-14
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
#include "string.h"
#include <algorithm>
#include <cwctype>

namespace YanLib::helper {
    bool string::strstri(const std::wstring &text, const std::wstring &substr) {
        if (substr.empty())
            return false;
        if (text.empty())
            return false;

        auto case_insensitive_compare = [](const wchar_t a,
                                           const wchar_t b) -> bool {
            return std::towlower(a) == std::towlower(b);
        };
        const auto it = std::search(text.begin(), text.end(), substr.begin(),
                                    substr.end(), case_insensitive_compare);
        return it != text.end();
    }

    bool string::strstri(const wchar_t *text, const wchar_t *substr) {
        if (!text || !substr || wcslen(text) == 0 || wcslen(substr) == 0)
            return false;

        auto case_insensitive_compare = [](const wchar_t a,
                                           const wchar_t b) -> bool {
            return std::towlower(a) == std::towlower(b);
        };

        const wchar_t *result =
                std::search(text, text + wcslen(text), substr,
                            substr + wcslen(substr), case_insensitive_compare);

        return *result ? true : false;
    }
} // namespace YanLib::helper
