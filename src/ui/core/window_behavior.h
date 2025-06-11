/* clang-format off */
/*
 * @file window_behavior.h
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
#ifndef WINDOW_BEHAVIOR_H
#define WINDOW_BEHAVIOR_H
#include <Windows.h>

namespace YanLib::ui::core {
    class window_behavior {
    public:
        window_behavior(const window_behavior &other) = delete;

        window_behavior(window_behavior &&other) = delete;

        window_behavior &operator=(const window_behavior &other) = delete;

        window_behavior &operator=(window_behavior &&other) = delete;

        window_behavior() = default;

        ~window_behavior() = default;

        static DPI_HOSTING_BEHAVIOR get_dpi_hosting(HWND window_handle);

        static DPI_HOSTING_BEHAVIOR get_thread_dpi_hosting();

        static DPI_HOSTING_BEHAVIOR
        set_thread_dpi_hosting(DPI_HOSTING_BEHAVIOR value);
    };
} // namespace YanLib::ui::core
#endif // WINDOW_BEHAVIOR_H
