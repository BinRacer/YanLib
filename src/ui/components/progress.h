/* clang-format off */
/*
 * @file progress.h
 * @date 2025-05-29
 * @license MIT License
 *
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
#ifndef PROGRESS_H
#define PROGRESS_H
#ifndef UNICODE
#define UNICODE
#endif
#ifndef _UNICODE
#define _UNICODE
#endif
#include <Windows.h>
#include <CommCtrl.h>
#include <minwindef.h>
#include <windef.h>
#include <cstdint>
#include <string>
#include <vector>
#include "sync/rwlock.h"
#include "ui/core/core.h"
#include "components.h"
#pragma comment(lib, "ComCtl32.Lib")
#pragma comment(linker, "\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#pragma comment(lib, "User32.Lib")
namespace YanLib::ui::components {
    class progress {
    private:
        std::vector<HWND> progress_handles = {};
        sync::rwlock progress_rwlock = {};
        uint32_t error_code = 0;

    public:
        progress(const progress &other) = delete;

        progress(progress &&other) = delete;

        progress &operator=(const progress &other) = delete;

        progress &operator=(progress &&other) = delete;

        progress();

        ~progress();

        HWND create(uintptr_t progress_id,
                    HWND parent_window_handle,
                    LPARAM lparam,
                    int32_t x,
                    int32_t y,
                    int32_t width,
                    int32_t height,
                    ProgressStyle style = ProgressStyle::Smooth,
                    core::WindowStyle window_style = core::WindowStyle::Child |
                            core::WindowStyle::Visible);

        HWND create(const char *progress_name,
                    uintptr_t progress_id,
                    HWND parent_window_handle,
                    LPARAM lparam,
                    int32_t x,
                    int32_t y,
                    int32_t width,
                    int32_t height,
                    ProgressStyle style = ProgressStyle::Smooth,
                    core::WindowStyle window_style = core::WindowStyle::Child |
                            core::WindowStyle::Visible);

        HWND create(const wchar_t *progress_name,
                    uintptr_t progress_id,
                    HWND parent_window_handle,
                    LPARAM lparam,
                    int32_t x,
                    int32_t y,
                    int32_t width,
                    int32_t height,
                    ProgressStyle style = ProgressStyle::Smooth,
                    core::WindowStyle window_style = core::WindowStyle::Child |
                            core::WindowStyle::Visible);

        bool destroy(HWND progress_handle);

        COLORREF get_bar_color(HWND progress_handle);

        COLORREF set_bar_color(HWND progress_handle, COLORREF color);

        COLORREF get_background_color(HWND progress_handle);

        COLORREF set_background_color(HWND progress_handle, COLORREF color);

        uint32_t get_pos(HWND progress_handle);

        uint32_t set_pos(HWND progress_handle, uint32_t pos);

        void get_range(HWND progress_handle, PBRANGE *range);

        bool set_range(HWND progress_handle, PBRANGE range);

        bool set_range(HWND progress_handle, int32_t low, int32_t high);

        void set_range32(HWND progress_handle, int32_t low, int32_t high);

        ProgressState get_state(HWND progress_handle);

        ProgressState set_state(HWND progress_handle, ProgressState state);

        uint32_t get_step(HWND progress_handle);

        uint32_t set_step(HWND progress_handle, uint32_t step);

        uint32_t set_delta_pos(HWND progress_handle, uint32_t increment);

        void enable_marquee(HWND progress_handle, int32_t milli_second = 0);

        void disable_marquee(HWND progress_handle, int32_t milli_second = 0);

        uint32_t forward_step(HWND progress_handle);

        [[nodiscard]] uint32_t err_code() const;

        [[nodiscard]] std::string err_string() const;

        [[nodiscard]] std::wstring err_wstring() const;
    };
} // namespace YanLib::ui::components
#endif // PROGRESS_H
