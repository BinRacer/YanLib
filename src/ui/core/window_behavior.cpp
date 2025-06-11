/* clang-format off */
/*
 * @file window_behavior.cpp
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
#include "window_behavior.h"
#include "helper/convert.h"
namespace YanLib::ui::core {
    DPI_HOSTING_BEHAVIOR window_behavior::get_dpi_hosting(HWND window_handle) {
        return GetWindowDpiHostingBehavior(window_handle);
    }

    DPI_HOSTING_BEHAVIOR window_behavior::get_thread_dpi_hosting() {
        return GetThreadDpiHostingBehavior();
    }

    DPI_HOSTING_BEHAVIOR
    window_behavior::set_thread_dpi_hosting(DPI_HOSTING_BEHAVIOR value) {
        return SetThreadDpiHostingBehavior(value);
    }
} // namespace YanLib::ui::core
