/* clang-format off */
/*
 * @file caret.cpp
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
#include "caret.h"
#include "helper/convert.h"

namespace YanLib::ui::core {
    caret::~caret() {
        if (is_create) {
            DestroyCaret();
        }
    }

    caret::caret(HWND window_handle,
                 HBITMAP bitmap_handle,
                 int32_t width,
                 int32_t height) {
        _window_handle = window_handle;
        if (!CreateCaret(window_handle, bitmap_handle, width, height)) {
            error_code = GetLastError();
            is_create = false;
        } else {
            is_create = true;
        }
    }

    bool caret::is_ok() const {
        return is_create;
    }

    uint32_t caret::get_blink_time() {
        const uint32_t result = GetCaretBlinkTime();
        if (!result) {
            error_code = GetLastError();
        }
        return result;
    }

    bool caret::set_blink_time(uint32_t milli_second) {
        if (!SetCaretBlinkTime(milli_second)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool caret::get_pos(POINT *point) {
        if (!GetCaretPos(point)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool caret::set_pos(int32_t x, int32_t y) {
        if (!SetCaretPos(x, y)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool caret::show() {
        if (!ShowCaret(_window_handle)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool caret::hide() {
        if (!HideCaret(_window_handle)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    uint32_t caret::err_code() const {
        return error_code;
    }

    std::string caret::err_string() const {
        std::string result = helper::convert::err_string(error_code);
        return result;
    }

    std::wstring caret::err_wstring() const {
        std::wstring result = helper::convert::err_wstring(error_code);
        return result;
    }
} // namespace YanLib::ui::core
