/* clang-format off */
/*
 * @file datetime.h
 * @date 2025-05-25
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
#ifndef DATETIME_H
#define DATETIME_H
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
#include <minwinbase.h>
#include <cstdint>
#include <string>
#include <vector>
#include "sync/rwlock.h"
#include "helper/convert.h"
#include "ui/core/core.h"
#include "components.h"
#pragma comment(lib, "ComCtl32.Lib")
#pragma comment(linker, "\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#pragma comment(lib, "User32.Lib")
namespace YanLib::ui::components {
    class datetime {
    private:
        std::vector<HWND> datetime_handles = {};
        sync::rwlock datetime_rwlock = {};
        uint32_t error_code = 0;

    public:
        datetime(const datetime &other) = delete;

        datetime(datetime &&other) = delete;

        datetime &operator=(const datetime &other) = delete;

        datetime &operator=(datetime &&other) = delete;

        datetime();

        ~datetime();

        HWND
        create(uintptr_t datatime_id,
               HWND parent_window_handle,
               LPARAM lparam,
               int32_t x,
               int32_t y,
               int32_t width,
               int32_t height,
               DateTimeStyle style = DateTimeStyle::ShortDateCenturyFormat |
                       DateTimeStyle::TimeFormat | DateTimeStyle::UpDown,
               core::WindowStyle window_style = core::WindowStyle::Child |
                       core::WindowStyle::Visible | core::WindowStyle::Border);

        HWND
        create(const char *datatime_name,
               uintptr_t datatime_id,
               HWND parent_window_handle,
               LPARAM lparam,
               int32_t x,
               int32_t y,
               int32_t width,
               int32_t height,
               DateTimeStyle style = DateTimeStyle::ShortDateCenturyFormat |
                       DateTimeStyle::TimeFormat | DateTimeStyle::UpDown,
               core::WindowStyle window_style = core::WindowStyle::Child |
                       core::WindowStyle::Visible | core::WindowStyle::Border);

        HWND
        create(const wchar_t *datatime_name,
               uintptr_t datatime_id,
               HWND parent_window_handle,
               LPARAM lparam,
               int32_t x,
               int32_t y,
               int32_t width,
               int32_t height,
               DateTimeStyle style = DateTimeStyle::ShortDateCenturyFormat |
                       DateTimeStyle::TimeFormat | DateTimeStyle::UpDown,
               core::WindowStyle window_style = core::WindowStyle::Child |
                       core::WindowStyle::Visible | core::WindowStyle::Border);

        bool destroy(HWND datetime_handle);

        void get_datetime_picker_info(HWND datetime_handle,
                                      DATETIMEPICKERINFO *datetime_picker_info);

        bool get_ideal_size(HWND datetime_handle, SIZE *size);

        HWND get_month_control(HWND datetime_handle);

        void close_month_control(HWND month_handle);

        bool get_system_time(HWND datetime_handle, SYSTEMTIME *system_time);

        bool set_system_time(HWND datetime_handle, SYSTEMTIME *system_time);

        bool clear_system_time(HWND datetime_handle);

        // SYSTEMTIME system_time[2] = { min, max };
        bool get_range(HWND datetime_handle, SYSTEMTIME system_time[2]);

        // SYSTEMTIME system_time[2] = { min, max };
        bool set_range(HWND datetime_handle, SYSTEMTIME system_time[2]);

        void set_format(HWND datetime_handle,
                        std::string &format,
                        helper::CodePage code_page = helper::curr_code_page());

        void set_format(HWND datetime_handle, std::wstring &format);

        void reset_format(HWND datetime_handle);

        COLORREF get_month_control_color(HWND datetime_handle, MonthCode code);

        COLORREF set_month_control_color(HWND datetime_handle,
                                         MonthCode code,
                                         COLORREF color);

        HFONT get_month_control_font(HWND datetime_handle);

        void set_month_control_font(HWND datetime_handle,
                                    HFONT font_handle,
                                    bool is_redraw = true);

        MonthStyle get_month_control_style(HWND datetime_handle);

        MonthStyle set_month_control_style(HWND datetime_handle,
                                           MonthStyle style);

        [[nodiscard]] uint32_t err_code() const;

        [[nodiscard]] std::string err_string() const;

        [[nodiscard]] std::wstring err_wstring() const;
    };
} // namespace YanLib::ui::components
#endif // DATETIME_H
