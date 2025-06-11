/* clang-format off */
/*
 * @file window_aware.h
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
#ifndef WINDOW_AWARE_H
#define WINDOW_AWARE_H
#include <Windows.h>
#include <shellscalingapi.h>
#include <string>
#pragma comment(lib, "shcore.lib")
namespace YanLib::ui::core {
    class window_aware {
    private:
        uint32_t error_code = 0;

    public:
        window_aware(const window_aware &other) = delete;

        window_aware(window_aware &&other) = delete;

        window_aware &operator=(const window_aware &other) = delete;

        window_aware &operator=(window_aware &&other) = delete;

        window_aware() = default;

        ~window_aware() = default;

        DPI_AWARENESS_CONTEXT get_dpi_context(HWND window_handle);

        bool is_dpi_context_equal(DPI_AWARENESS_CONTEXT context1,
                                  DPI_AWARENESS_CONTEXT context2);

        bool is_proc_dpi();

        bool is_valid_dpi_context(DPI_AWARENESS_CONTEXT context);

        uint32_t dpi_context_to_dpi(DPI_AWARENESS_CONTEXT context);

        DPI_AWARENESS dpi_context_to_dpi_aware(DPI_AWARENESS_CONTEXT context);

        DPI_AWARENESS_CONTEXT get_proc_dpi_context(HANDLE proc_handle);

        bool set_proc_dpi_context(DPI_AWARENESS_CONTEXT value);

        HRESULT get_proc_dpi_aware(HANDLE proc_handle,
                                   PROCESS_DPI_AWARENESS *dpi_aware);

        HRESULT set_proc_dpi_aware(PROCESS_DPI_AWARENESS dpi_aware);

        DPI_AWARENESS_CONTEXT get_thread_dpi_context();

        DPI_AWARENESS_CONTEXT
        set_thread_dpi_context(DPI_AWARENESS_CONTEXT context);

        [[nodiscard]] uint32_t err_code() const;

        [[nodiscard]] std::string err_string() const;

        [[nodiscard]] std::wstring err_wstring() const;
    };
} // namespace YanLib::ui::core
#endif // WINDOW_AWARE_H
