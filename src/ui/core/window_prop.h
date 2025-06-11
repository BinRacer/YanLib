/* clang-format off */
/*
 * @file window_prop.h
 * @date 2025-05-18
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
#ifndef WINDOW_PROP_H
#define WINDOW_PROP_H
#include <Windows.h>
#include <string>

namespace YanLib::ui::core {
    class window_prop {
    private:
        uint32_t error_code = 0;

    public:
        window_prop(const window_prop &other) = delete;

        window_prop(window_prop &&other) = delete;

        window_prop &operator=(const window_prop &other) = delete;

        window_prop &operator=(window_prop &&other) = delete;

        window_prop() = default;

        ~window_prop() = default;

        int32_t enum_prop(HWND window_handle, PROPENUMPROCA enum_func);

        int32_t enum_prop(HWND window_handle, PROPENUMPROCW enum_func);

        int32_t
        enum_prop(HWND window_handle, PROPENUMPROCEXA enum_func, LPARAM lparam);

        int32_t
        enum_prop(HWND window_handle, PROPENUMPROCEXW enum_func, LPARAM lparam);

        void *get_prop(HWND window_handle, const char *key);

        void *get_prop(HWND window_handle, const wchar_t *key);

        bool set_prop(HWND window_handle, const char *key, void *value);

        bool set_prop(HWND window_handle, const wchar_t *key, void *value);

        void *remove_prop(HWND window_handle, const char *key);

        void *remove_prop(HWND window_handle, const wchar_t *key);

        [[nodiscard]] uint32_t err_code() const;

        [[nodiscard]] std::string err_string() const;

        [[nodiscard]] std::wstring err_wstring() const;
    };
} // namespace YanLib::ui::core
#endif // WINDOW_PROP_H
