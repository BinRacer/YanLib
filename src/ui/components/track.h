/* clang-format off */
/*
 * @file track.h
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
#ifndef TRACK_H
#define TRACK_H
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
#ifndef TRACKSTYLE
#define TRACKSTYLE
    enum class TrackStyle : uint32_t {
        AutoTicks = TBS_AUTOTICKS,
        Vert = TBS_VERT,
        Horiz = TBS_HORZ,
        Top = TBS_TOP,
        Bottom = TBS_BOTTOM,
        Left = TBS_LEFT,
        Right = TBS_RIGHT,
        Both = TBS_BOTH,
        NoTicks = TBS_NOTICKS,
        EnableSelectRange = TBS_ENABLESELRANGE,
        FixedLength = TBS_FIXEDLENGTH,
        NoThumb = TBS_NOTHUMB,
        ToolTips = TBS_TOOLTIPS,
        Reversed = TBS_REVERSED,
        DownIsLeft = TBS_DOWNISLEFT,
        NotifyBeforeMove = TBS_NOTIFYBEFOREMOVE,
        TransparentBackground = TBS_TRANSPARENTBKGND,
    };
    inline TrackStyle operator|(TrackStyle a, TrackStyle b) {
        return static_cast<TrackStyle>(static_cast<uint32_t>(a) |
                                       static_cast<uint32_t>(b));
    }
#endif
#ifndef TRACKTIPSIDE
#define TRACKTIPSIDE
    enum class TrackTipSide : uint32_t {
        Top = TBTS_TOP,
        Left = TBTS_LEFT,
        Bottom = TBTS_BOTTOM,
        Right = TBTS_RIGHT,
    };
#endif
#ifndef TRACKMESSAGE
#define TRACKMESSAGE
    enum class TrackMessage : uint32_t {
        ClearSelect = TBM_CLEARSEL,
        ClearTicks = TBM_CLEARTICS,
        GetBuddy = TBM_GETBUDDY,
        GetChannelRect = TBM_GETCHANNELRECT,
        GetLineSize = TBM_GETLINESIZE,
        GetNumTicks = TBM_GETNUMTICS,
        GetPageSize = TBM_GETPAGESIZE,
        GetPos = TBM_GETPOS,
        GetPTicks = TBM_GETPTICS,
        GetRangeMax = TBM_GETRANGEMAX,
        GetRangeMin = TBM_GETRANGEMIN,
        GetSelectEnd = TBM_GETSELEND,
        GetSelectStart = TBM_GETSELSTART,
        GetThumbLength = TBM_GETTHUMBLENGTH,
        GetThumbRect = TBM_GETTHUMBRECT,
        GetTick = TBM_GETTIC,
        GetTickPos = TBM_GETTICPOS,
        GetToolTips = TBM_GETTOOLTIPS,
        GetUnicodeFormat = TBM_GETUNICODEFORMAT,
        SetBuddy = TBM_SETBUDDY,
        SetLineSize = TBM_SETLINESIZE,
        SetPageSize = TBM_SETPAGESIZE,
        SetPos = TBM_SETPOS,
        SetPosNotify = TBM_SETPOSNOTIFY,
        SetRange = TBM_SETRANGE,
        SetRangeMax = TBM_SETRANGEMAX,
        SetRangeMin = TBM_SETRANGEMIN,
        SetSelect = TBM_SETSEL,
        SetSelectEnd = TBM_SETSELEND,
        SetSelectStart = TBM_SETSELSTART,
        SetThumbLength = TBM_SETTHUMBLENGTH,
        SetTick = TBM_SETTIC,
        SetTickFreq = TBM_SETTICFREQ,
        SetTipSide = TBM_SETTIPSIDE,
        SetToolTips = TBM_SETTOOLTIPS,
        SetUnicodeFormat = TBM_SETUNICODEFORMAT
    };
#endif
#ifndef TRACKNOTIFY
#define TRACKNOTIFY
    enum class TrackNotify : uint32_t {
        CustomDraw = NM_CUSTOMDRAW,
        ReleasedCapture = NM_RELEASEDCAPTURE,
        ThumbPosChanging = TRBN_THUMBPOSCHANGING,
        HScroll = WM_HSCROLL,
        VScroll = WM_VSCROLL,
    };
#endif
    class track {
    private:
        std::vector<HWND> track_handles = {};
        sync::rwlock track_rwlock = {};
        uint32_t error_code = 0;

    public:
        track(const track &other) = delete;

        track(track &&other) = delete;

        track &operator=(const track &other) = delete;

        track &operator=(track &&other) = delete;

        track();

        ~track();

        HWND create(uintptr_t track_id,
                    HWND parent_window_handle,
                    LPARAM lparam,
                    int32_t x,
                    int32_t y,
                    int32_t width,
                    int32_t height,
                    TrackStyle style = TrackStyle::AutoTicks |
                            TrackStyle::EnableSelectRange,
                    WindowStyle window_style = WindowStyle::Child |
                            WindowStyle::Visible);

        HWND create(const char *track_name,
                    uintptr_t track_id,
                    HWND parent_window_handle,
                    LPARAM lparam,
                    int32_t x,
                    int32_t y,
                    int32_t width,
                    int32_t height,
                    TrackStyle style = TrackStyle::AutoTicks |
                            TrackStyle::EnableSelectRange,
                    WindowStyle window_style = WindowStyle::Child |
                            WindowStyle::Visible);

        HWND create(const wchar_t *track_name,
                    uintptr_t track_id,
                    HWND parent_window_handle,
                    LPARAM lparam,
                    int32_t x,
                    int32_t y,
                    int32_t width,
                    int32_t height,
                    TrackStyle style = TrackStyle::AutoTicks |
                            TrackStyle::EnableSelectRange,
                    WindowStyle window_style = WindowStyle::Child |
                            WindowStyle::Visible);

        bool destroy(HWND track_handle);

        void clear_select(HWND track_handle, bool redraw = true);

        void clear_ticks(HWND track_handle, bool redraw = true);

        HWND get_left_or_top_buddy(HWND track_handle);

        HWND set_left_or_top_buddy(HWND track_handle);

        HWND get_right_or_bottom_buddy(HWND track_handle);

        HWND set_right_or_bottom_buddy(HWND track_handle);

        void get_channel_rect(HWND track_handle, RECT *rect);

        int64_t get_line_size(HWND track_handle);

        int64_t set_line_size(HWND track_handle, int64_t line_size);

        int64_t get_page_size(HWND track_handle);

        int64_t set_page_size(HWND track_handle, int64_t page_size);

        int64_t get_pos(HWND track_handle);

        void set_pos(HWND track_handle, int64_t pos, bool redraw = true);

        void set_pos_notify(HWND track_handle, int64_t pos);

        int64_t get_range_min(HWND track_handle);

        void set_range_min(HWND track_handle, int64_t min, bool redraw = true);

        int64_t get_range_max(HWND track_handle);

        void set_range_max(HWND track_handle, int64_t max, bool redraw = true);

        void set_range(HWND track_handle,
                       int32_t min,
                       int32_t max,
                       bool redraw = true);

        int64_t get_select_start(HWND track_handle);

        void
        set_select_start(HWND track_handle, int64_t start, bool redraw = true);

        int64_t get_select_end(HWND track_handle);

        void set_select_end(HWND track_handle, int64_t end, bool redraw = true);

        void set_select(HWND track_handle,
                        int32_t start,
                        int32_t end,
                        bool redraw = true);

        int64_t get_thumb_len(HWND track_handle);

        void set_thumb_len(HWND track_handle, int64_t len);

        void get_thumb_rect(HWND track_handle, RECT *rect);

        int64_t get_num_ticks(HWND track_handle);

        // don't contain first tick and last tick
        std::vector<uint32_t> get_ticks(HWND track_handle);

        // 1 <= index <= 2
        int64_t get_tick(HWND track_handle, int64_t index);

        bool set_tick(HWND track_handle, int64_t tick);

        int64_t get_tick_pos(HWND track_handle, int64_t index);

        void set_tick_freq(HWND track_handle, int64_t freq);

        HWND get_tool_tips(HWND track_handle);

        void set_tool_tips(HWND track_handle, HWND tool_tips_handle);

        TrackTipSide set_tip_side(HWND track_handle, TrackTipSide pos);

        bool is_ansi_format(HWND track_handle);

        bool is_unicode_format(HWND track_handle);

        void set_ansi_format(HWND track_handle);

        void set_unicode_format(HWND track_handle);

        [[nodiscard]] uint32_t err_code() const;

        [[nodiscard]] std::string err_string() const;

        [[nodiscard]] std::wstring err_wstring() const;
    };
} // namespace YanLib::ui::components
#endif // TRACK_H
