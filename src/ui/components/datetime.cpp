/* clang-format off */
/*
 * @file datetime.cpp
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
#include "datetime.h"
#include <windowsx.h>

namespace YanLib::ui::components {
    datetime::datetime() {
        INITCOMMONCONTROLSEX icc = {};
        icc.dwSize = sizeof(INITCOMMONCONTROLSEX);
        icc.dwICC = ICC_DATE_CLASSES;
        InitCommonControlsEx(&icc);
    }

    datetime::~datetime() {
        for (auto &handle : datetime_handles) {
            if (handle && IsWindow(handle)) {
                DestroyWindow(handle);
                handle = nullptr;
            }
        }
        datetime_handles.clear();
    }

    HWND datetime::create(uintptr_t datatime_id,
                          HWND parent_window_handle,
                          LPARAM lparam,
                          int32_t x,
                          int32_t y,
                          int32_t width,
                          int32_t height,
                          DateTimeStyle style,
                          core::WindowStyle window_style) {
        HWND result = CreateWindowExW(0L, L"SysDateTimePick32", nullptr,
                                      static_cast<uint32_t>(window_style) |
                                              static_cast<uint32_t>(style),
                                      x, y, width, height, parent_window_handle,
                                      reinterpret_cast<HMENU>(datatime_id),
                                      reinterpret_cast<CREATESTRUCT *>(lparam)
                                              ->hInstance,
                                      nullptr);
        if (!result) {
            error_code = GetLastError();
            return nullptr;
        }
        datetime_rwlock.write_lock();
        datetime_handles.push_back(result);
        datetime_rwlock.write_unlock();
        return result;
    }

    HWND datetime::create(const char *datatime_name,
                          uintptr_t datatime_id,
                          HWND parent_window_handle,
                          LPARAM lparam,
                          int32_t x,
                          int32_t y,
                          int32_t width,
                          int32_t height,
                          DateTimeStyle style,
                          core::WindowStyle window_style) {
        HWND result = CreateWindowExA(0L, "SysDateTimePick32", datatime_name,
                                      static_cast<uint32_t>(window_style) |
                                              static_cast<uint32_t>(style),
                                      x, y, width, height, parent_window_handle,
                                      reinterpret_cast<HMENU>(datatime_id),
                                      reinterpret_cast<CREATESTRUCT *>(lparam)
                                              ->hInstance,
                                      nullptr);
        if (!result) {
            error_code = GetLastError();
            return nullptr;
        }
        datetime_rwlock.write_lock();
        datetime_handles.push_back(result);
        datetime_rwlock.write_unlock();
        return result;
    }

    HWND datetime::create(const wchar_t *datatime_name,
                          uintptr_t datatime_id,
                          HWND parent_window_handle,
                          LPARAM lparam,
                          int32_t x,
                          int32_t y,
                          int32_t width,
                          int32_t height,
                          DateTimeStyle style,
                          core::WindowStyle window_style) {
        HWND result = CreateWindowExW(0L, L"SysDateTimePick32", datatime_name,
                                      static_cast<uint32_t>(window_style) |
                                              static_cast<uint32_t>(style),
                                      x, y, width, height, parent_window_handle,
                                      reinterpret_cast<HMENU>(datatime_id),
                                      reinterpret_cast<CREATESTRUCT *>(lparam)
                                              ->hInstance,
                                      nullptr);
        if (!result) {
            error_code = GetLastError();
            return nullptr;
        }
        datetime_rwlock.write_lock();
        datetime_handles.push_back(result);
        datetime_rwlock.write_unlock();
        return result;
    }

    bool datetime::destroy(HWND datetime_handle) {
        if (!datetime_handle || !IsWindow(datetime_handle)) {
            return false;
        }
        datetime_rwlock.write_lock();
        const auto it = std::find(datetime_handles.begin(),
                                  datetime_handles.end(), datetime_handle);
        if (it != datetime_handles.end()) {
            *it = nullptr;
        }
        datetime_rwlock.write_unlock();
        if (!DestroyWindow(datetime_handle)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    void datetime::get_datetime_picker_info(
            HWND datetime_handle,
            DATETIMEPICKERINFO *datetime_picker_info) {
        DateTime_GetDateTimePickerInfo(datetime_handle, datetime_picker_info);
    }

    bool datetime::get_ideal_size(HWND datetime_handle, SIZE *size) {
        return DateTime_GetIdealSize(datetime_handle, size);
    }

    HWND datetime::get_month_control(HWND datetime_handle) {
        return DateTime_GetMonthCal(datetime_handle);
    }

    void datetime::close_month_control(HWND month_handle) {
        DateTime_CloseMonthCal(month_handle);
    }

    bool datetime::get_system_time(HWND datetime_handle,
                                   SYSTEMTIME *system_time) {
        if (const uint32_t result =
                    DateTime_GetSystemtime(datetime_handle, system_time);
            result == static_cast<uint32_t>(GDT_ERROR)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool datetime::set_system_time(HWND datetime_handle,
                                   SYSTEMTIME *system_time) {
        return DateTime_SetSystemtime(datetime_handle, GDT_VALID, system_time);
    }

    bool datetime::clear_system_time(HWND datetime_handle) {
        return DateTime_SetSystemtime(datetime_handle, GDT_NONE, nullptr);
    }

    bool datetime::get_range(HWND datetime_handle, SYSTEMTIME system_time[2]) {
        if (const uint32_t result =
                    DateTime_GetRange(datetime_handle, system_time);
            (result & GDTR_MIN) && (result & GDTR_MAX)) {
            return true;
        }
        return false;
    }

    bool datetime::set_range(HWND datetime_handle, SYSTEMTIME system_time[2]) {
        return DateTime_SetRange(datetime_handle, GDTR_MIN | GDTR_MAX,
                                 system_time);
    }

    void datetime::set_format(HWND datetime_handle,
                              std::string &format,
                              helper::CodePage code_page) {
        DateTime_SetFormat(datetime_handle,
                           helper::convert::str_to_wstr(format, code_page)
                                   .data());
    }

    void datetime::set_format(HWND datetime_handle, std::wstring &format) {
        DateTime_SetFormat(datetime_handle, format.data());
    }

    void datetime::reset_format(HWND datetime_handle) {
        DateTime_SetFormat(datetime_handle, nullptr);
    }

    COLORREF datetime::get_month_control_color(HWND datetime_handle,
                                               MonthCode code) {
        return DateTime_GetMonthCalColor(datetime_handle,
                                         static_cast<int32_t>(code));
    }

    COLORREF datetime::set_month_control_color(HWND datetime_handle,
                                               MonthCode code,
                                               COLORREF color) {
        return DateTime_SetMonthCalColor(datetime_handle,
                                         static_cast<int32_t>(code), color);
    }

    HFONT datetime::get_month_control_font(HWND datetime_handle) {
        return reinterpret_cast<HFONT>(
                DateTime_GetMonthCalFont(datetime_handle));
    }

    void datetime::set_month_control_font(HWND datetime_handle,
                                          HFONT font_handle,
                                          bool is_redraw) {
        DateTime_SetMonthCalFont(datetime_handle, font_handle,
                                 is_redraw ? TRUE : FALSE);
    }

    MonthStyle datetime::get_month_control_style(HWND datetime_handle) {
        return static_cast<MonthStyle>(
                DateTime_GetMonthCalStyle(datetime_handle));
    }

    MonthStyle datetime::set_month_control_style(HWND datetime_handle,
                                                 MonthStyle style) {
        return static_cast<MonthStyle>(
                DateTime_SetMonthCalStyle(datetime_handle, style));
    }

    uint32_t datetime::err_code() const {
        return error_code;
    }

    std::string datetime::err_string() const {
        std::string result = helper::convert::err_string(error_code);
        return result;
    }

    std::wstring datetime::err_wstring() const {
        std::wstring result = helper::convert::err_wstring(error_code);
        return result;
    }
} // namespace YanLib::ui::components
