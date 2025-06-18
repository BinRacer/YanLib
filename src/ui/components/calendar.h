/* clang-format off */
/*
 * @file calendar.h
 * @date 2025-05-28
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
#ifndef CALENDAR_H
#define CALENDAR_H
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
#include "ui/core/core.h"
#include "components.h"
#pragma comment(lib, "ComCtl32.Lib")
#pragma comment(linker, "\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#pragma comment(lib, "User32.Lib")
namespace YanLib::ui::components {
    class calendar {
    private:
        std::vector<HWND> calendar_handles = {};
        sync::rwlock calendar_rwlock = {};
        uint32_t error_code = 0;

    public:
        calendar(const calendar &other) = delete;

        calendar(calendar &&other) = delete;

        calendar &operator=(const calendar &other) = delete;

        calendar &operator=(calendar &&other) = delete;

        calendar();

        ~calendar();

        HWND create(uintptr_t calendar_id,
                    HWND parent_window_handle,
                    LPARAM lparam,
                    int32_t x,
                    int32_t y,
                    int32_t width,
                    int32_t height,
                    CalendarStyle style = CalendarStyle::DayState |
                            CalendarStyle::WeekNumbers |
                            CalendarStyle::ShortDaysOfWeek |
                            CalendarStyle::NoSelectChangeOnNav,
                    core::WindowStyle window_style = core::WindowStyle::Child |
                            core::WindowStyle::Visible | core::WindowStyle::Border);

        HWND create(const char *calendar_name,
                    uintptr_t calendar_id,
                    HWND parent_window_handle,
                    LPARAM lparam,
                    int32_t x,
                    int32_t y,
                    int32_t width,
                    int32_t height,
                    CalendarStyle style = CalendarStyle::DayState |
                            CalendarStyle::WeekNumbers |
                            CalendarStyle::ShortDaysOfWeek |
                            CalendarStyle::NoSelectChangeOnNav,
                    core::WindowStyle window_style = core::WindowStyle::Child |
                            core::WindowStyle::Visible | core::WindowStyle::Border);

        HWND create(const wchar_t *calendar_name,
                    uintptr_t calendar_id,
                    HWND parent_window_handle,
                    LPARAM lparam,
                    int32_t x,
                    int32_t y,
                    int32_t width,
                    int32_t height,
                    CalendarStyle style = CalendarStyle::DayState |
                            CalendarStyle::WeekNumbers |
                            CalendarStyle::ShortDaysOfWeek |
                            CalendarStyle::NoSelectChangeOnNav,
                    core::WindowStyle window_style = core::WindowStyle::Child |
                            core::WindowStyle::Visible | core::WindowStyle::Border);

        bool destroy(HWND calendar_handle);

        uint32_t get_border(HWND calendar_handle);

        void set_border(HWND calendar_handle, uint32_t border);

        void reset_border(HWND calendar_handle);

        CalendarId get_calendar_id(HWND calendar_handle);

        void set_calendar_id(HWND calendar_handle, CalendarId id);

        COLORREF get_color(HWND calendar_handle, CalendarColorCode code);

        COLORREF
        set_color(HWND calendar_handle, CalendarColorCode code, COLORREF color);

        CalendarView get_curr_view(HWND calendar_handle);

        bool set_curr_view(HWND calendar_handle, CalendarView view);

        bool get_curr_select(HWND calendar_handle, SYSTEMTIME *system_time);

        bool set_curr_select(HWND calendar_handle, SYSTEMTIME *system_time);

        std::pair<bool, CalendarWeekDay>
        get_first_day_of_week(HWND calendar_handle);

        std::pair<bool, CalendarWeekDay>
        set_first_day_of_week(HWND calendar_handle, CalendarWeekDay day);

        uint32_t get_max_select_day(HWND calendar_handle);

        bool set_max_select_day(HWND calendar_handle, uint32_t day);

        int32_t get_month_delta(HWND calendar_handle);

        int32_t set_month_delta(HWND calendar_handle, int32_t delta);

        // range[0] = min, range[1] = max
        bool get_range(HWND calendar_handle, SYSTEMTIME range[2]);

        // range[0] = min, range[1] = max
        bool set_range(HWND calendar_handle, SYSTEMTIME range[2]);

        // range[0] = min, range[1] = max
        bool get_select_range(HWND calendar_handle, SYSTEMTIME range[2]);

        // range[0] = min, range[1] = max
        bool set_select_range(HWND calendar_handle, SYSTEMTIME range[2]);

        bool get_today(HWND calendar_handle, SYSTEMTIME *day);

        void set_today(HWND calendar_handle, SYSTEMTIME *day);

        bool is_ansi_format(HWND calendar_handle);

        bool is_unicode_format(HWND calendar_handle);

        void set_ansi_format(HWND calendar_handle);

        void set_unicode_format(HWND calendar_handle);

        CalendarMonth get_month(HWND calendar_handle);

        bool get_calendar_grid_info(HWND calendar_handle,
                                    MCGRIDINFO *grid_info);

        uint32_t get_max_today_width(HWND calendar_handle);

        bool get_min_request_rect(HWND calendar_handle, RECT *rect);

        // range[0] = min, range[1] = max
        bool get_month_range(HWND calendar_handle, SYSTEMTIME range[2]);

        // range[0] = min, range[1] = max
        bool get_month_visible_range(HWND calendar_handle, SYSTEMTIME range[2]);

        bool set_day_state(HWND calendar_handle,
                           std::vector<MONTHDAYSTATE> &month_day_state);

        uint32_t hit_test(HWND calendar_handle, MCHITTESTINFO *hit_test_info);

        void size_rect_to_min(HWND calendar_handle, RECT *rect);

        [[nodiscard]] uint32_t err_code() const;

        [[nodiscard]] std::string err_string() const;

        [[nodiscard]] std::wstring err_wstring() const;
    };
} // namespace YanLib::ui::components
#endif // CALENDAR_H
