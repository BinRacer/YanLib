/* clang-format off */
/*
 * @file up_down.h
 * @date 2025-06-04
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
#ifndef UP_DOWN_H
#define UP_DOWN_H
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
    class up_down {
    private:
        std::vector<HWND> up_down_handles = {};
        sync::rwlock up_down_rwlock = {};
        uint32_t error_code = 0;

    public:
        up_down(const up_down &other) = delete;

        up_down(up_down &&other) = delete;

        up_down &operator=(const up_down &other) = delete;

        up_down &operator=(up_down &&other) = delete;

        up_down();

        ~up_down();

        HWND create(uintptr_t up_down_id,
                    HWND parent_window_handle,
                    LPARAM lparam,
                    int32_t x = 0,
                    int32_t y = 0,
                    int32_t width = 0,
                    int32_t height = 0,
                    UpDownStyle style = UpDownStyle::AlignRight |
                            UpDownStyle::SetBuddyInt | UpDownStyle::ArrowKeys |
                            UpDownStyle::HotTrack | UpDownStyle::Wrap |
                            UpDownStyle::AutoBuddy,
                    core::WindowStyle window_style = core::WindowStyle::Child |
                            core::WindowStyle::Visible);

        HWND create(const char *up_down_name,
                    uintptr_t up_down_id,
                    HWND parent_window_handle,
                    LPARAM lparam,
                    int32_t x = 0,
                    int32_t y = 0,
                    int32_t width = 0,
                    int32_t height = 0,
                    UpDownStyle style = UpDownStyle::AlignRight |
                            UpDownStyle::SetBuddyInt | UpDownStyle::ArrowKeys |
                            UpDownStyle::HotTrack | UpDownStyle::Wrap |
                            UpDownStyle::AutoBuddy,
                    core::WindowStyle window_style = core::WindowStyle::Child |
                            core::WindowStyle::Visible);

        HWND create(const wchar_t *up_down_name,
                    uintptr_t up_down_id,
                    HWND parent_window_handle,
                    LPARAM lparam,
                    int32_t x = 0,
                    int32_t y = 0,
                    int32_t width = 0,
                    int32_t height = 0,
                    UpDownStyle style = UpDownStyle::AlignRight |
                            UpDownStyle::SetBuddyInt | UpDownStyle::ArrowKeys |
                            UpDownStyle::HotTrack | UpDownStyle::Wrap |
                            UpDownStyle::AutoBuddy,
                    core::WindowStyle window_style = core::WindowStyle::Child |
                            core::WindowStyle::Visible);

        bool destroy(HWND up_down_handle);

        HWND get_buddy(HWND up_down_handle);

        HWND set_buddy(HWND up_down_handle, HWND buddy_handle);

        // return value = accel.size()
        int64_t get_accel(HWND up_down_handle, std::vector<UDACCEL> &accel);

        bool set_accel(HWND up_down_handle, std::vector<UDACCEL> &accel);

        int64_t get_base(HWND up_down_handle);

        int64_t set_base(HWND up_down_handle, int64_t base);

        // std::pair<bool, pos>
        std::pair<bool, uint16_t> get_pos(HWND up_down_handle);

        uint16_t set_pos(HWND up_down_handle, uint16_t pos);

        uint32_t get_pos32(HWND up_down_handle, bool *is_ok);

        uint32_t set_pos32(HWND up_down_handle, uint32_t pos);

        // std::pair<min, max>
        std::pair<uint16_t, uint16_t> get_range(HWND up_down_handle);

        void set_range(HWND up_down_handle, uint16_t min, uint16_t max);

        void get_range32(HWND up_down_handle, uint32_t *min, uint32_t *max);

        void set_range32(HWND up_down_handle, uint32_t min, uint32_t max);

        bool is_ansi_format(HWND up_down_handle);

        bool is_unicode_format(HWND up_down_handle);

        void set_ansi_format(HWND up_down_handle);

        void set_unicode_format(HWND up_down_handle);

        [[nodiscard]] uint32_t err_code() const;

        [[nodiscard]] std::string err_string() const;

        [[nodiscard]] std::wstring err_wstring() const;
    };
} // namespace YanLib::ui::components
#endif // UP_DOWN_H
