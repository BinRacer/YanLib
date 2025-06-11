/* clang-format off */
/*
 * @file status.h
 * @date 2025-05-31
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
#ifndef STATUS_H
#define STATUS_H
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
#include "helper/convert.h"
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
#ifndef STATUSSTYLE
#define STATUSSTYLE
    enum class StatusStyle : uint32_t {
        SizeGrip = SBARS_SIZEGRIP,
        ToolTips = SBARS_TOOLTIPS,
    };
    inline StatusStyle operator|(StatusStyle a, StatusStyle b) {
        return static_cast<StatusStyle>(static_cast<uint32_t>(a) |
                                        static_cast<uint32_t>(b));
    }
#endif
#ifndef COMMONSTYLE
#define COMMONSTYLE
    enum class CommonStyle : uint32_t {
        Top = CCS_TOP,
        NoMoveY = CCS_NOMOVEY,
        Bottom = CCS_BOTTOM,
        NoResize = CCS_NORESIZE,
        NoParentAlign = CCS_NOPARENTALIGN,
        Adjustable = CCS_ADJUSTABLE,
        NoDivider = CCS_NODIVIDER,
        Vert = CCS_VERT,
        Left = CCS_LEFT,
        Right = CCS_RIGHT,
        NoMoveX = CCS_NOMOVEX,
    };
    inline CommonStyle operator|(CommonStyle a, CommonStyle b) {
        return static_cast<CommonStyle>(static_cast<uint32_t>(a) |
                                        static_cast<uint32_t>(b));
    }
#endif
    inline StatusStyle operator|(StatusStyle a, CommonStyle b) {
        return static_cast<StatusStyle>(static_cast<uint32_t>(a) |
                                        static_cast<uint32_t>(b));
    }
    inline StatusStyle operator|(CommonStyle a, StatusStyle b) {
        return static_cast<StatusStyle>(static_cast<uint32_t>(a) |
                                        static_cast<uint32_t>(b));
    }
#ifndef STATUSTEXTFLAG
#define STATUSTEXTFLAG
    enum class StatusTextFlag : uint32_t {
        None = 0,
        OwnerDraw = SBT_OWNERDRAW,
        NoBorders = SBT_NOBORDERS,
        PopOut = SBT_POPOUT,
        RtlReading = SBT_RTLREADING,
        NoTabParsing = SBT_NOTABPARSING,
    };
    inline StatusTextFlag operator|(StatusTextFlag a, StatusTextFlag b) {
        return static_cast<StatusTextFlag>(static_cast<uint32_t>(a) |
                                           static_cast<uint32_t>(b));
    }
#endif
#ifndef STATUSMESSAGE
#define STATUSMESSAGE
    enum class StatusMessage : uint32_t {
        GetBorders = SB_GETBORDERS,
        GetIcon = SB_GETICON,
        GetParts = SB_GETPARTS,
        GetRect = SB_GETRECT,
        GetText = SB_GETTEXT,
        GetTextLength = SB_GETTEXTLENGTH,
        GetTipText = SB_GETTIPTEXT,
        GetUnicodeFormat = SB_GETUNICODEFORMAT,
        IsSimple = SB_ISSIMPLE,
        SetBackgroundColor = SB_SETBKCOLOR,
        SetIcon = SB_SETICON,
        SetMinHeight = SB_SETMINHEIGHT,
        SetParts = SB_SETPARTS,
        SetText = SB_SETTEXT,
        SetTipText = SB_SETTIPTEXT,
        SetUnicodeFormat = SB_SETUNICODEFORMAT,
        Simple = SB_SIMPLE,
    };
#endif
#ifndef STATUSNOTIFY
#define STATUSNOTIFY
    enum class StatusNotify : uint32_t {
        Click = NM_CLICK,
        DoubleClick = NM_DBLCLK,
        RightClick = NM_RCLICK,
        RightDoubleClick = NM_RDBLCLK,
        SimpleModeChange = SBN_SIMPLEMODECHANGE,
    };
#endif
    class status {
    private:
        std::vector<HWND> status_handles = {};
        sync::rwlock status_rwlock = {};
        uint32_t error_code = 0;

    public:
        status(const status &other) = delete;

        status(status &&other) = delete;

        status &operator=(const status &other) = delete;

        status &operator=(status &&other) = delete;

        status() = default;

        ~status();

        HWND create(uintptr_t status_id,
                    HWND parent_window_handle,
                    LPARAM lparam,
                    int32_t x,
                    int32_t y,
                    int32_t width,
                    int32_t height,
                    StatusStyle style = StatusStyle::SizeGrip |
                            StatusStyle::ToolTips,
                    WindowStyle window_style = WindowStyle::Child |
                            WindowStyle::Visible);

        HWND create(const char *status_name,
                    uintptr_t status_id,
                    HWND parent_window_handle,
                    LPARAM lparam,
                    int32_t x,
                    int32_t y,
                    int32_t width,
                    int32_t height,
                    StatusStyle style = StatusStyle::SizeGrip |
                            StatusStyle::ToolTips,
                    WindowStyle window_style = WindowStyle::Child |
                            WindowStyle::Visible);

        HWND create(const wchar_t *status_name,
                    uintptr_t status_id,
                    HWND parent_window_handle,
                    LPARAM lparam,
                    int32_t x,
                    int32_t y,
                    int32_t width,
                    int32_t height,
                    StatusStyle style = StatusStyle::SizeGrip |
                            StatusStyle::ToolTips,
                    WindowStyle window_style = WindowStyle::Child |
                            WindowStyle::Visible);

        bool destroy(HWND status_handle);

        void draw_status_text(HDC dc_handle,
                              RECT *rect,
                              const char *text,
                              StatusTextFlag flag);

        void draw_status_text(HDC dc_handle,
                              RECT *rect,
                              const wchar_t *text,
                              StatusTextFlag flag);

        // message = WM_MENUSELECT or WM_COMMAND
        void menu_help(uint32_t message,
                       WPARAM wparam,
                       LPARAM lparam,
                       HMENU menu_handle,
                       HINSTANCE instance_handle,
                       HWND status_handle,
                       uint32_t id[]);

        // borders[0] = the width of the horizontal border
        // borders[1] = the width of the vertical border
        // borders[2] = the width of the border between rectangles
        bool get_borders(HWND status_handle, int32_t borders[3]);

        bool get_rect(HWND status_handle, int32_t index, RECT *rect);

        COLORREF set_background_color(HWND status_handle,
                                      COLORREF color = CLR_DEFAULT);

        void set_min_height(HWND status_handle, int32_t height);

        HICON get_icon(HWND status_handle, int32_t index = -1);

        bool set_icon(HWND status_handle, HICON icon, int32_t index = -1);

        bool delete_icon(HWND status_handle, int32_t index = -1);

        int64_t get_parts(HWND status_handle, std::vector<int32_t> &parts);

        bool set_parts(HWND status_handle, std::vector<int32_t> &parts);

        std::pair<uint32_t, StatusTextFlag>
        get_text(HWND status_handle,
                 uint8_t index,
                 std::string &text,
                 helper::CodePage code_page = helper::curr_code_page());

        std::pair<uint32_t, StatusTextFlag>
        get_text(HWND status_handle, uint8_t index, std::wstring &text);

        bool set_text(HWND status_handle,
                      uint8_t index,
                      StatusTextFlag flag,
                      std::string &text,
                      helper::CodePage code_page = helper::curr_code_page());

        bool set_text(HWND status_handle,
                      uint8_t index,
                      StatusTextFlag flag,
                      std::wstring &text);

        std::pair<uint32_t, StatusTextFlag> get_text_len(HWND status_handle,
                                                         uint8_t index);

        void
        get_tip_text(HWND status_handle,
                     uint8_t index,
                     std::string &text,
                     helper::CodePage code_page = helper::curr_code_page());

        void
        get_tip_text(HWND status_handle, uint8_t index, std::wstring &text);

        void
        set_tip_text(HWND status_handle,
                     uint8_t index,
                     std::string &text,
                     helper::CodePage code_page = helper::curr_code_page());

        void
        set_tip_text(HWND status_handle, uint8_t index, std::wstring &text);

        bool is_ansi_format(HWND status_handle);

        bool is_unicode_format(HWND status_handle);

        void set_ansi_format(HWND status_handle);

        void set_unicode_format(HWND status_handle);

        bool is_simple(HWND status_handle);

        void show_simple(HWND status_handle);

        void show_parts(HWND status_handle);

        [[nodiscard]] uint32_t err_code() const;

        [[nodiscard]] std::string err_string() const;

        [[nodiscard]] std::wstring err_wstring() const;
    };
} // namespace YanLib::ui::components
#endif // STATUS_H
