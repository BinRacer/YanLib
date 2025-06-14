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
#include <cstdint>
#include <string>
#include <vector>
#include "sync/rwlock.h"
#pragma comment(lib, "ComCtl32.Lib")
#pragma comment(linker, "\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#pragma comment(lib, "User32.Lib")
namespace YanLib::ui::components {
#ifndef WINDOWSTYLE
#define WINDOWSTYLE

    enum class WindowStyle : uint32_t {
        Overlapped = WS_OVERLAPPED,
        Popup = WS_POPUP,
        Child = WS_CHILD,
        Minimize = WS_MINIMIZE,
        Visible = WS_VISIBLE,
        Disabled = WS_DISABLED,
        ClipSiblings = WS_CLIPSIBLINGS,
        ClipChildren = WS_CLIPCHILDREN,
        Maximize = WS_MAXIMIZE,
        Caption = WS_CAPTION,
        Border = WS_BORDER,
        DialogFrame = WS_DLGFRAME,
        VScroll = WS_VSCROLL,
        HScroll = WS_HSCROLL,
        SysMenu = WS_SYSMENU,
        ThickFrame = WS_THICKFRAME,
        Group = WS_GROUP,
        TabStop = WS_TABSTOP,
        MinimizeBox = WS_MINIMIZEBOX,
        MaximizeBox = WS_MAXIMIZEBOX,
        Tiled = WS_TILED,
        Iconic = WS_ICONIC,
        SizeBox = WS_SIZEBOX,
        TiledWindow = WS_TILEDWINDOW,
        OverlappedWindow = WS_OVERLAPPEDWINDOW,
        PopupWindow = WS_POPUPWINDOW,
        ChildWindow = WS_CHILDWINDOW,
    };

    inline WindowStyle operator|(WindowStyle a, WindowStyle b) {
        return static_cast<WindowStyle>(static_cast<uint32_t>(a) |
                                        static_cast<uint32_t>(b));
    }
#endif
#ifndef CALENDARSTYLE
#define CALENDARSTYLE
    enum class CalendarStyle : uint32_t {
        DayState = MCS_DAYSTATE,
        MultiSelect = MCS_MULTISELECT,
        WeekNumbers = MCS_WEEKNUMBERS,
        NoTodayCircle = MCS_NOTODAYCIRCLE,
        NoToday = MCS_NOTODAY,
        NoTrailingDates = MCS_NOTRAILINGDATES,
        ShortDaysOfWeek = MCS_SHORTDAYSOFWEEK,
        NoSelectChangeOnNav = MCS_NOSELCHANGEONNAV,
    };
    inline CalendarStyle operator|(CalendarStyle a, CalendarStyle b) {
        return static_cast<CalendarStyle>(static_cast<uint32_t>(a) |
                                          static_cast<uint32_t>(b));
    }
#endif
#ifndef CALENDARID
#define CALENDARID
    enum class CalendarId : uint32_t {
        GREGORIAN = CAL_GREGORIAN,
        GREGORIAN_US = CAL_GREGORIAN_US,
        JAPAN = CAL_JAPAN,
        TAIWAN = CAL_TAIWAN,
        KOREA = CAL_KOREA,
        HIJRI = CAL_HIJRI,
        THAI = CAL_THAI,
        HEBREW = CAL_HEBREW,
        GREGORIAN_ME_FRENCH = CAL_GREGORIAN_ME_FRENCH,
        GREGORIAN_ARABIC = CAL_GREGORIAN_ARABIC,
        GREGORIAN_XLIT_ENGLISH = CAL_GREGORIAN_XLIT_ENGLISH,
        GREGORIAN_XLIT_FRENCH = CAL_GREGORIAN_XLIT_FRENCH,
        PERSIAN = CAL_PERSIAN,
        UMALQURA = CAL_UMALQURA,

    };
#endif
#ifndef CALENDARCOLORCODE
#define CALENDARCOLORCODE
    enum class CalendarColorCode : uint32_t {
        Background = MCSC_BACKGROUND,
        Text = MCSC_TEXT,
        TitleBackground = MCSC_TITLEBK,
        TitleText = MCSC_TITLETEXT,
        MonthBackground = MCSC_MONTHBK,
        TrailingText = MCSC_TRAILINGTEXT,
    };
#endif
#ifndef CALENDARVIEW
#define CALENDARVIEW
    enum class CalendarView : uint32_t {
        Month = MCMV_MONTH,
        Year = MCMV_YEAR,
        Decade = MCMV_DECADE,
        Century = MCMV_CENTURY,
    };
#endif
#ifndef CALENDARWEEKDAY
#define CALENDARWEEKDAY
    enum class CalendarWeekDay : uint32_t {
        Monday = 0,
        Tuesday,
        Wednesday,
        Thursday,
        Friday,
        Saturday,
        Sunday
    };
#endif
#ifndef CALENDARMONTH
#define CALENDARMONTH
    enum class CalendarMonth : uint32_t {
        January = 1,
        February,
        March,
        April,
        May,
        June,
        July,
        August,
        September,
        October,
        November,
        December
    };
#endif
#ifndef CALENDARMESSAGE
#define CALENDARMESSAGE
    enum class CalendarMessage : uint32_t {
        GetCalendarBorder = MCM_GETCALENDARBORDER,
        GetCalendarCount = MCM_GETCALENDARCOUNT,
        GetCalendarGridInfo = MCM_GETCALENDARGRIDINFO,
        GetCalendarId = MCM_GETCALID,
        GetColor = MCM_GETCOLOR,
        GetCurrentView = MCM_GETCURRENTVIEW,
        GetCurrentSelect = MCM_GETCURSEL,
        GetFirstDayOfWeek = MCM_GETFIRSTDAYOFWEEK,
        GetMaxSelCount = MCM_GETMAXSELCOUNT,
        GetMaxTodayWidth = MCM_GETMAXTODAYWIDTH,
        GetMinRequestRect = MCM_GETMINREQRECT,
        GetMonthDelta = MCM_GETMONTHDELTA,
        GetMonthRange = MCM_GETMONTHRANGE,
        GetRange = MCM_GETRANGE,
        GetSelectRange = MCM_GETSELRANGE,
        GetToday = MCM_GETTODAY,
        GetUnicodeFormat = MCM_GETUNICODEFORMAT,
        HitTest = MCM_HITTEST,
        SetCalendarBorder = MCM_SETCALENDARBORDER,
        SetCalendarId = MCM_SETCALID,
        SetColor = MCM_SETCOLOR,
        SetCurrentView = MCM_SETCURRENTVIEW,
        SetCurrentSelect = MCM_SETCURSEL,
        SetDayState = MCM_SETDAYSTATE,
        SetFirstDayOfWeek = MCM_SETFIRSTDAYOFWEEK,
        SetMaxSelectCount = MCM_SETMAXSELCOUNT,
        SetMonthDelta = MCM_SETMONTHDELTA,
        SetRange = MCM_SETRANGE,
        SetSelectRange = MCM_SETSELRANGE,
        SetToday = MCM_SETTODAY,
        SetUnicodeFormat = MCM_SETUNICODEFORMAT,
        SizeRectToMin = MCM_SIZERECTTOMIN
    };
#endif
#ifndef CALENDARNOTIFY
#define CALENDARNOTIFY
    enum class CalendarNotify : uint32_t {
        GetDayState = MCN_GETDAYSTATE,
        SelectChange = MCN_SELCHANGE,
        Select = MCN_SELECT,
        ViewChange = MCN_VIEWCHANGE,
        ReleasedCapture = NM_RELEASEDCAPTURE,
    };
#endif
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
                    WindowStyle window_style = WindowStyle::Child |
                            WindowStyle::Visible | WindowStyle::Border);

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
                    WindowStyle window_style = WindowStyle::Child |
                            WindowStyle::Visible | WindowStyle::Border);

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
                    WindowStyle window_style = WindowStyle::Child |
                            WindowStyle::Visible | WindowStyle::Border);

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
