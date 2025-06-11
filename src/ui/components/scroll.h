/* clang-format off */
/*
 * @file scroll.h
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
#ifndef SCROLL_H
#define SCROLL_H
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
#ifndef SCROLLSTYLE
#define SCROLLSTYLE
    enum class ScrollStyle : uint32_t {
        Horiz = SBS_HORZ,
        Vert = SBS_VERT,
        TopAlign = SBS_TOPALIGN,
        LeftAlign = SBS_LEFTALIGN,
        BottomAlign = SBS_BOTTOMALIGN,
        RightAlign = SBS_RIGHTALIGN,
        SizeBoxTopLeftAlign = SBS_SIZEBOXTOPLEFTALIGN,
        SizeBoxBottomRightAlign = SBS_SIZEBOXBOTTOMRIGHTALIGN,
        SizeBox = SBS_SIZEBOX,
        SizeGrip = SBS_SIZEGRIP,
    };
    inline ScrollStyle operator|(ScrollStyle a, ScrollStyle b) {
        return static_cast<ScrollStyle>(static_cast<uint32_t>(a) |
                                        static_cast<uint32_t>(b));
    }
#endif
#ifndef SCROLLTYPE
#define SCROLLTYPE
    enum class ScrollType : uint32_t {
        Horiz = SB_HORZ,
        Vert = SB_VERT,
        Ctl = SB_CTL,
        Both = SB_BOTH,
    };
    inline ScrollType operator|(ScrollType a, ScrollType b) {
        return static_cast<ScrollType>(static_cast<uint32_t>(a) |
                                       static_cast<uint32_t>(b));
    }
#endif
#ifndef ARROWTYPE
#define ARROWTYPE
    enum class ArrowType : uint32_t {
        EnableBoth = ESB_ENABLE_BOTH,
        DisableBoth = ESB_DISABLE_BOTH,
        DisableLeft = ESB_DISABLE_LEFT,
        DisableRight = ESB_DISABLE_RIGHT,
        DisableUp = ESB_DISABLE_UP,
        DisableDown = ESB_DISABLE_DOWN,
        DisableLeftUp = ESB_DISABLE_LTUP,
        DisableRightDown = ESB_DISABLE_RTDN,
    };
    inline ArrowType operator|(ArrowType a, ArrowType b) {
        return static_cast<ArrowType>(static_cast<uint32_t>(a) |
                                      static_cast<uint32_t>(b));
    }
#endif
#ifndef SCROLLCOMMAND
#define SCROLLCOMMAND

    enum class ScrollCommand : uint32_t {
        LineUp = SB_LINEUP,
        LineLeft = SB_LINELEFT,
        LineDown = SB_LINEDOWN,
        LineRight = SB_LINERIGHT,
        PageUp = SB_PAGEUP,
        PageLeft = SB_PAGELEFT,
        PageDown = SB_PAGEDOWN,
        PageRight = SB_PAGERIGHT,
        ThumbPosition = SB_THUMBPOSITION,
        ThumbTrack = SB_THUMBTRACK,
        Top = SB_TOP,
        Left = SB_LEFT,
        Bottom = SB_BOTTOM,
        Right = SB_RIGHT,
        EndScroll = SB_ENDSCROLL,
    };

    inline ScrollCommand operator|(ScrollCommand a, ScrollCommand b) {
        return static_cast<ScrollCommand>(static_cast<uint32_t>(a) |
                                          static_cast<uint32_t>(b));
    }
#endif
#ifndef OBJECTID
#define OBJECTID

    enum class ObjectID : int32_t {
        Window = OBJID_WINDOW,
        SysMenu = OBJID_SYSMENU,
        TitleBar = OBJID_TITLEBAR,
        Menu = OBJID_MENU,
        Client = OBJID_CLIENT,
        VScroll = OBJID_VSCROLL,
        HScroll = OBJID_HSCROLL,
        SizeGrip = OBJID_SIZEGRIP,
        Caret = OBJID_CARET,
        Cursor = OBJID_CURSOR,
        Alert = OBJID_ALERT,
        Sound = OBJID_SOUND,
        QueryClassNameIDX = OBJID_QUERYCLASSNAMEIDX,
        NativeOM = OBJID_NATIVEOM,
    };
#endif
#ifndef SCROLLFLAG
#define SCROLLFLAG

    enum class ScrollFlag : uint32_t {
        ScrollChildren = SW_SCROLLCHILDREN,
        InValidate = SW_INVALIDATE,
        Erase = SW_ERASE,
        SmoothScroll = SW_SMOOTHSCROLL,
    };

    inline ScrollFlag operator|(ScrollFlag a, ScrollFlag b) {
        return static_cast<ScrollFlag>(static_cast<uint32_t>(a) |
                                       static_cast<uint32_t>(b));
    }
#endif
#ifndef SCROLLMESSAGE
#define SCROLLMESSAGE
    enum class ScrollMessage : uint32_t {
        EnableArrows = SBM_ENABLE_ARROWS,
        GetPos = SBM_GETPOS,
        GetRange = SBM_GETRANGE,
        GetScrollBarInfo = SBM_GETSCROLLBARINFO,
        GetScrollInfo = SBM_GETSCROLLINFO,
        SetPos = SBM_SETPOS,
        SetRange = SBM_SETRANGE,
        SetRangeRedraw = SBM_SETRANGEREDRAW,
        SetScrollInfo = SBM_SETSCROLLINFO,
    };
#endif
#ifndef SCROLLNOTIFY
#define SCROLLNOTIFY
    enum class ScrollNotify : uint32_t {
        CtlColorScrollBar = WM_CTLCOLORSCROLLBAR,
        HScroll = WM_HSCROLL,
        VScroll = WM_VSCROLL,
    };
#endif
    class scroll {
    private:
        std::vector<HWND> scroll_handles = {};
        sync::rwlock scroll_rwlock = {};
        uint32_t error_code = 0;

    public:
        scroll(const scroll &other) = delete;

        scroll(scroll &&other) = delete;

        scroll &operator=(const scroll &other) = delete;

        scroll &operator=(scroll &&other) = delete;

        scroll() = default;

        ~scroll();

        HWND create(uintptr_t scroll_id,
                    HWND parent_window_handle,
                    LPARAM lparam,
                    int32_t x,
                    int32_t y,
                    int32_t width,
                    int32_t height,
                    ScrollStyle style = ScrollStyle::Vert |
                            ScrollStyle::RightAlign,
                    WindowStyle window_style = WindowStyle::Child |
                            WindowStyle::Visible);

        HWND create(const char *scroll_name,
                    uintptr_t scroll_id,
                    HWND parent_window_handle,
                    LPARAM lparam,
                    int32_t x,
                    int32_t y,
                    int32_t width,
                    int32_t height,
                    ScrollStyle style = ScrollStyle::Vert |
                            ScrollStyle::RightAlign,
                    WindowStyle window_style = WindowStyle::Child |
                            WindowStyle::Visible);

        HWND create(const wchar_t *scroll_name,
                    uintptr_t scroll_id,
                    HWND parent_window_handle,
                    LPARAM lparam,
                    int32_t x,
                    int32_t y,
                    int32_t width,
                    int32_t height,
                    ScrollStyle style = ScrollStyle::Vert |
                            ScrollStyle::RightAlign,
                    WindowStyle window_style = WindowStyle::Child |
                            WindowStyle::Visible);

        bool destroy(HWND scroll_handle);

        bool enable(HWND scroll_handle,
                    ScrollType scroll_type = ScrollType::Both,
                    ArrowType arrow_type = ArrowType::EnableBoth);

        bool show(HWND scroll_handle,
                  ScrollType scroll_type = ScrollType::Both);

        bool hide(HWND scroll_handle,
                  ScrollType scroll_type = ScrollType::Both);

        bool get_info(HWND scroll_handle,
                      SCROLLBARINFO *scroll_bar_info,
                      ObjectID object_id = ObjectID::VScroll);

        bool get_info(HWND scroll_handle,
                      SCROLLINFO *scroll_info,
                      ScrollType scroll_type = ScrollType::Vert);

        int32_t set_info(HWND scroll_handle,
                         SCROLLINFO *scroll_info,
                         ScrollType scroll_type = ScrollType::Vert,
                         bool is_redraw = true);

        int32_t get_pos(HWND scroll_handle,
                        ScrollType scroll_type = ScrollType::Vert);

        int32_t set_pos(HWND scroll_handle,
                        int32_t pos,
                        ScrollType scroll_type = ScrollType::Vert,
                        bool is_redraw = true);

        bool get_range(HWND scroll_handle,
                       int32_t *min_pos,
                       int32_t *max_pos,
                       ScrollType scroll_type = ScrollType::Vert);

        bool set_range(HWND scroll_handle,
                       int32_t min_pos,
                       int32_t max_pos,
                       ScrollType scroll_type = ScrollType::Vert,
                       bool is_redraw = true);

        bool scroll_dc(HDC dc_handle,
                       int32_t x,
                       int32_t y,
                       const RECT *rect_scroll,
                       const RECT *rect_clip = nullptr,
                       HRGN region_update_handle = nullptr,
                       RECT *rect_update = nullptr);

        bool scroll_window(HWND scroll_handle,
                           int32_t x_amount,
                           int32_t y_amount,
                           const RECT *rect = nullptr,
                           const RECT *clip_rect = nullptr);

        int32_t scroll_window_extend(HWND scroll_handle,
                                     int32_t dx,
                                     int32_t dy,
                                     const RECT *rect_scroll = nullptr,
                                     const RECT *rect_clip = nullptr,
                                     HRGN region_handle_update = nullptr,
                                     RECT *rect_update = nullptr,
                                     ScrollFlag flag = ScrollFlag::InValidate |
                                             ScrollFlag::Erase);

        [[nodiscard]] uint32_t err_code() const;

        [[nodiscard]] std::string err_string() const;

        [[nodiscard]] std::wstring err_wstring() const;
    };
} // namespace YanLib::ui::components
#endif // SCROLL_H
