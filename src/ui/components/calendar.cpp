//
// Created by forkernel on 2025/5/28.
//

#include "calendar.h"
#include <windowsx.h>
#include "helper/convert.h"
namespace YanLib::components {
    HWND calendar::create(uintptr_t calendar_id,
                          HWND parent_window_handle,
                          LPARAM lparam,
                          int32_t x,
                          int32_t y,
                          int32_t width,
                          int32_t height,
                          CalendarStyle style,
                          WindowStyle window_style) {
        INITCOMMONCONTROLSEX icc = {};
        icc.dwSize = sizeof(INITCOMMONCONTROLSEX);
        icc.dwICC = ICC_DATE_CLASSES;
        InitCommonControlsEx(&icc);
        HWND result = CreateWindowExW(0L, L"SysMonthCal32", nullptr,
                                      static_cast<uint32_t>(window_style) |
                                              static_cast<uint32_t>(style),
                                      x, y, width, height, parent_window_handle,
                                      reinterpret_cast<HMENU>(calendar_id),
                                      reinterpret_cast<CREATESTRUCT *>(lparam)
                                              ->hInstance,
                                      nullptr);
        if (!result) {
            error_code = GetLastError();
        }
        return result;
    }

    HWND calendar::create(const char *calendar_name,
                          uintptr_t calendar_id,
                          HWND parent_window_handle,
                          LPARAM lparam,
                          int32_t x,
                          int32_t y,
                          int32_t width,
                          int32_t height,
                          CalendarStyle style,
                          WindowStyle window_style) {
        INITCOMMONCONTROLSEX icc = {};
        icc.dwSize = sizeof(INITCOMMONCONTROLSEX);
        icc.dwICC = ICC_DATE_CLASSES;
        InitCommonControlsEx(&icc);
        HWND result = CreateWindowExA(0L, "SysMonthCal32", calendar_name,
                                      static_cast<uint32_t>(window_style) |
                                              static_cast<uint32_t>(style),
                                      x, y, width, height, parent_window_handle,
                                      reinterpret_cast<HMENU>(calendar_id),
                                      reinterpret_cast<CREATESTRUCT *>(lparam)
                                              ->hInstance,
                                      nullptr);
        if (!result) {
            error_code = GetLastError();
        }
        return result;
    }

    HWND calendar::create(const wchar_t *calendar_name,
                          uintptr_t calendar_id,
                          HWND parent_window_handle,
                          LPARAM lparam,
                          int32_t x,
                          int32_t y,
                          int32_t width,
                          int32_t height,
                          CalendarStyle style,
                          WindowStyle window_style) {
        INITCOMMONCONTROLSEX icc = {};
        icc.dwSize = sizeof(INITCOMMONCONTROLSEX);
        icc.dwICC = ICC_DATE_CLASSES;
        InitCommonControlsEx(&icc);
        HWND result = CreateWindowExW(0L, L"SysMonthCal32", calendar_name,
                                      static_cast<uint32_t>(window_style) |
                                              static_cast<uint32_t>(style),
                                      x, y, width, height, parent_window_handle,
                                      reinterpret_cast<HMENU>(calendar_id),
                                      reinterpret_cast<CREATESTRUCT *>(lparam)
                                              ->hInstance,
                                      nullptr);
        if (!result) {
            error_code = GetLastError();
        }
        return result;
    }

    uint32_t calendar::get_border(HWND calendar_handle) {
        return MonthCal_GetCalendarBorder(calendar_handle);
    }

    void calendar::set_border(HWND calendar_handle, uint32_t border) {
        MonthCal_SetCalendarBorder(calendar_handle, TRUE, border);
    }


    void calendar::reset_border(HWND calendar_handle) {
        MonthCal_SetCalendarBorder(calendar_handle, FALSE, 0);
    }

    CalendarId calendar::get_calendar_id(HWND calendar_handle) {
        return static_cast<CalendarId>(MonthCal_GetCALID(calendar_handle));
    }

    void calendar::set_calendar_id(HWND calendar_handle, CalendarId id) {
        MonthCal_SetCALID(calendar_handle, id);
    }

    COLORREF calendar::get_color(HWND calendar_handle, CalendarColorCode code) {
        return MonthCal_GetColor(calendar_handle, static_cast<uint32_t>(code));
    }

    COLORREF calendar::set_color(HWND calendar_handle,
                                 CalendarColorCode code,
                                 COLORREF color) {
        return MonthCal_SetColor(calendar_handle, static_cast<uint32_t>(code),
                                 color);
    }

    CalendarView calendar::get_curr_view(HWND calendar_handle) {
        return static_cast<CalendarView>(
                MonthCal_GetCurrentView(calendar_handle));
    }

    bool calendar::set_curr_view(HWND calendar_handle, CalendarView view) {
        return MonthCal_SetCurrentView(calendar_handle,
                                       static_cast<uint32_t>(view));
    }

    bool calendar::get_curr_select(HWND calendar_handle,
                                   SYSTEMTIME *system_time) {
        return MonthCal_GetCurSel(calendar_handle, system_time);
    }

    bool calendar::set_curr_select(HWND calendar_handle,
                                   SYSTEMTIME *system_time) {
        return MonthCal_SetCurSel(calendar_handle, system_time);
    }

    std::pair<bool, CalendarWeekDay>
    calendar::get_first_day_of_week(HWND calendar_handle) {
        uint32_t result = MonthCal_GetFirstDayOfWeek(calendar_handle);
        return std::make_pair(HIWORD(result) == LOCALE_IFIRSTDAYOFWEEK,
                              static_cast<CalendarWeekDay>(LOWORD(result)));
    }

    std::pair<bool, CalendarWeekDay>
    calendar::set_first_day_of_week(HWND calendar_handle, CalendarWeekDay day) {
        uint32_t result =
                MonthCal_SetFirstDayOfWeek(calendar_handle,
                                           static_cast<uint32_t>(day));
        return std::make_pair(HIWORD(result) == LOCALE_IFIRSTDAYOFWEEK,
                              static_cast<CalendarWeekDay>(LOWORD(result)));
    }

    uint32_t calendar::get_max_select_day(HWND calendar_handle) {
        return MonthCal_GetMaxSelCount(calendar_handle);
    }

    bool calendar::set_max_select_day(HWND calendar_handle, uint32_t day) {
        return MonthCal_SetMaxSelCount(calendar_handle, day);
    }

    int32_t calendar::get_month_delta(HWND calendar_handle) {
        return MonthCal_GetMonthDelta(calendar_handle);
    }

    int32_t calendar::set_month_delta(HWND calendar_handle, int32_t delta) {
        return MonthCal_SetMonthDelta(calendar_handle, delta);
    }

    bool calendar::get_range(HWND calendar_handle, SYSTEMTIME range[2]) {
        return MonthCal_GetRange(calendar_handle, range);
    }

    bool calendar::set_range(HWND calendar_handle, SYSTEMTIME range[2]) {
        return MonthCal_SetRange(calendar_handle, GDTR_MIN | GDTR_MAX, range);
    }

    bool calendar::get_select_range(HWND calendar_handle, SYSTEMTIME range[2]) {
        return MonthCal_GetSelRange(calendar_handle, range);
    }

    bool calendar::set_select_range(HWND calendar_handle, SYSTEMTIME range[2]) {
        return MonthCal_SetSelRange(calendar_handle, range);
    }

    bool calendar::get_today(HWND calendar_handle, SYSTEMTIME *day) {
        return MonthCal_GetToday(calendar_handle, day);
    }

    void calendar::set_today(HWND calendar_handle, SYSTEMTIME *day) {
        MonthCal_SetToday(calendar_handle, day);
    }

    bool calendar::is_ansi_format(HWND calendar_handle) {
        return !(MonthCal_GetUnicodeFormat(calendar_handle));
    }

    bool calendar::is_unicode_format(HWND calendar_handle) {
        return MonthCal_GetUnicodeFormat(calendar_handle);
    }

    void calendar::set_ansi_format(HWND calendar_handle) {
        MonthCal_SetUnicodeFormat(calendar_handle, FALSE);
    }

    void calendar::set_unicode_format(HWND calendar_handle) {
        MonthCal_SetUnicodeFormat(calendar_handle, TRUE);
    }

    CalendarMonth calendar::get_month(HWND calendar_handle) {
        return static_cast<CalendarMonth>(
                MonthCal_GetCalendarCount(calendar_handle));
    }

    bool calendar::get_calendar_grid_info(HWND calendar_handle,
                                          MCGRIDINFO *grid_info) {
        return MonthCal_GetCalendarGridInfo(calendar_handle, grid_info);
    }

    uint32_t calendar::get_max_today_width(HWND calendar_handle) {
        return MonthCal_GetMaxTodayWidth(calendar_handle);
    }

    bool calendar::get_min_request_rect(HWND calendar_handle, RECT *rect) {
        return MonthCal_GetMinReqRect(calendar_handle, rect);
    }

    bool calendar::get_month_range(HWND calendar_handle, SYSTEMTIME range[2]) {
        return MonthCal_GetMonthRange(calendar_handle, GMR_DAYSTATE, range);
    }

    bool calendar::get_month_visible_range(HWND calendar_handle,
                                           SYSTEMTIME range[2]) {
        return MonthCal_GetMonthRange(calendar_handle, GMR_VISIBLE, range);
    }

    bool calendar::set_day_state(HWND calendar_handle,
                                 std::vector<MONTHDAYSTATE> &month_day_state) {
        return MonthCal_SetDayState(calendar_handle, month_day_state.size(),
                                    month_day_state.data());
    }

    uint32_t calendar::hit_test(HWND calendar_handle,
                                MCHITTESTINFO *hit_test_info) {
        return MonthCal_HitTest(calendar_handle, hit_test_info);
    }

    void calendar::size_rect_to_min(HWND calendar_handle, RECT *rect) {
        MonthCal_SizeRectToMin(calendar_handle, rect);
    }

    uint32_t calendar::err_code() const {
        return error_code;
    }

    std::string calendar::err_string() const {
        std::string result = helper::convert::err_string(error_code);
        return result;
    }

    std::wstring calendar::err_wstring() const {
        std::wstring result = helper::convert::err_wstring(error_code);
        return result;
    }
} // namespace YanLib::components
