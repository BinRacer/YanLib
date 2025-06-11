/* clang-format off */
/*
 * @file window_pos.cpp
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
#include "window_pos.h"
#include "helper/convert.h"

namespace YanLib::ui::core {
    HDWP window_pos::prepare(int32_t window_num) {
        HDWP result = BeginDeferWindowPos(window_num);
        if (!result) {
            error_code = GetLastError();
        }
        return result;
    }

    HDWP window_pos::add(HDWP window_pos_handle,
                         HWND window_handle,
                         HWND insert_after_window_handle,
                         int32_t x,
                         int32_t y,
                         int32_t width,
                         int32_t height,
                         PosFlag flag) {
        HDWP result = DeferWindowPos(window_pos_handle, window_handle,
                                     insert_after_window_handle, x, y, width,
                                     height, static_cast<uint32_t>(flag));
        if (!result) {
            error_code = GetLastError();
        }
        return result;
    }

    bool window_pos::apply(HDWP window_pos_handle) {
        if (!EndDeferWindowPos(window_pos_handle)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    uint32_t window_pos::err_code() const {
        return error_code;
    }

    std::string window_pos::err_string() const {
        std::string result = helper::convert::err_string(error_code);
        return result;
    }

    std::wstring window_pos::err_wstring() const {
        std::wstring result = helper::convert::err_wstring(error_code);
        return result;
    }
} // namespace YanLib::ui::core
