/* clang-format off */
/*
 * @file caret.h
 * @date 2025-04-30
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
#ifndef CARET_H
#define CARET_H
#include <Windows.h>
#include <string>

namespace YanLib::ui::core {
    class caret {
    private:
        HWND _window_handle = nullptr;
        volatile bool is_create = false;
        uint32_t error_code = 0;

    public:
        caret(const caret &other) = delete;

        caret(caret &&other) = delete;

        caret &operator=(const caret &other) = delete;

        caret &operator=(caret &&other) = delete;

        caret() = delete;

        ~caret();

        explicit caret(HWND window_handle,
                       HBITMAP bitmap_handle,
                       int32_t width,
                       int32_t height);

        [[nodiscard]] bool is_ok() const;

        uint32_t get_blink_time();

        bool set_blink_time(uint32_t milli_second);

        bool get_pos(POINT *point);

        bool set_pos(int32_t x, int32_t y);

        bool show();

        bool hide();

        [[nodiscard]] uint32_t err_code() const;

        [[nodiscard]] std::string err_string() const;

        [[nodiscard]] std::wstring err_wstring() const;
    };
} // namespace YanLib::ui::core
#endif // CARET_H
