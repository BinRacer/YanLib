/* clang-format off */
/*
 * @file page.h
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
#ifndef PAGE_H
#define PAGE_H
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
#ifndef PAGESTYLE
#define PAGESTYLE
    enum class PageStyle : uint32_t {
        Vertical = PGS_VERT,
        Horizontal = PGS_HORZ,
        AutoScroll = PGS_AUTOSCROLL,
        DragnDrop = PGS_DRAGNDROP,
    };
    inline PageStyle operator|(PageStyle a, PageStyle b) {
        return static_cast<PageStyle>(static_cast<uint32_t>(a) |
                                      static_cast<uint32_t>(b));
    }
#endif
#ifndef PAGEBUTTONINDEX
#define PAGEBUTTONINDEX
    enum class PageButtonIndex : uint32_t {
        TopOrLeft = PGB_TOPORLEFT,
        BottomOrRight = PGB_BOTTOMORRIGHT,
    };
#endif
#ifndef PAGEBUTTONSTATE
#define PAGEBUTTONSTATE
    enum class PageButtonState : uint32_t {
        Invisible = PGF_INVISIBLE,
        Normal = PGF_NORMAL,
        Grayed = PGF_GRAYED,
        Depressed = PGF_DEPRESSED,
        Hot = PGF_HOT,
    };
    inline PageButtonState operator|(PageButtonState a, PageButtonState b) {
        return static_cast<PageButtonState>(static_cast<uint32_t>(a) |
                                            static_cast<uint32_t>(b));
    }
#endif
#ifndef PAGEMESSAGE
#define PAGEMESSAGE
    enum class PageMessage : uint32_t {
        ForwardMouse = PGM_FORWARDMOUSE,
        GetBackgroundColor = PGM_GETBKCOLOR,
        GetBorder = PGM_GETBORDER,
        GetButtonSize = PGM_GETBUTTONSIZE,
        GetButtonState = PGM_GETBUTTONSTATE,
        GetDropTarget = PGM_GETDROPTARGET,
        GetPos = PGM_GETPOS,
        RecalcSize = PGM_RECALCSIZE,
        SetBackgroundColor = PGM_SETBKCOLOR,
        SetBorder = PGM_SETBORDER,
        SetButtonSize = PGM_SETBUTTONSIZE,
        SetChild = PGM_SETCHILD,
        SetPos = PGM_SETPOS,
        SetScrollInfo = PGM_SETSCROLLINFO
    };
#endif
#ifndef PAGENOTIFY
#define PAGENOTIFY
    enum class PageNotify : uint32_t {
        ReleasedCapture = NM_RELEASEDCAPTURE,
        CalcSize = PGN_CALCSIZE,
        HotItemChange = PGN_HOTITEMCHANGE,
        Scroll = PGN_SCROLL,
    };
#endif
    class page {
    private:
        std::vector<HWND> pages_handles = {};
        sync::rwlock pages_rwlock = {};
        uint32_t error_code = 0;

    public:
        page(const page &other) = delete;

        page(page &&other) = delete;

        page &operator=(const page &other) = delete;

        page &operator=(page &&other) = delete;

        page();

        ~page();

        HWND create(uintptr_t page_id,
                    HWND parent_window_handle,
                    LPARAM lparam,
                    int32_t x,
                    int32_t y,
                    int32_t width,
                    int32_t height,
                    PageStyle style = PageStyle::Horizontal |
                            PageStyle::AutoScroll,
                    WindowStyle window_style = WindowStyle::Child |
                            WindowStyle::Visible);

        HWND create(const char *page_name,
                    uintptr_t page_id,
                    HWND parent_window_handle,
                    LPARAM lparam,
                    int32_t x,
                    int32_t y,
                    int32_t width,
                    int32_t height,
                    PageStyle style = PageStyle::Horizontal |
                            PageStyle::AutoScroll,
                    WindowStyle window_style = WindowStyle::Child |
                            WindowStyle::Visible);

        HWND create(const wchar_t *page_name,
                    uintptr_t page_id,
                    HWND parent_window_handle,
                    LPARAM lparam,
                    int32_t x,
                    int32_t y,
                    int32_t width,
                    int32_t height,
                    PageStyle style = PageStyle::Horizontal |
                            PageStyle::AutoScroll,
                    WindowStyle window_style = WindowStyle::Child |
                            WindowStyle::Visible);

        bool destroy(HWND page_handle);

        void enable_forward_mouse(HWND page_handle);

        void disable_forward_mouse(HWND page_handle);

        COLORREF get_background_color(HWND page_handle);

        COLORREF set_background_color(HWND page_handle, COLORREF color);

        int32_t get_border(HWND page_handle);

        int32_t set_border(HWND page_handle, int32_t border);

        int32_t get_button_size(HWND page_handle);

        int32_t set_button_size(HWND page_handle, int32_t size);

        PageButtonState get_button_state(HWND page_handle,
                                         PageButtonIndex index);

        void get_drop_target(HWND page_handle, IDropTarget **target);

        int32_t get_pos(HWND page_handle);

        void set_pos(HWND page_handle, int32_t pos);

        void recalc_size(HWND page_handle);

        void set_child(HWND page_handle, HWND child_window_handle);

        void set_scroll_info(HWND page_handle,
                             uint32_t timeout_ms,
                             uint32_t line_num,
                             uint32_t per_line_pixels);

        [[nodiscard]] uint32_t err_code() const;

        [[nodiscard]] std::string err_string() const;

        [[nodiscard]] std::wstring err_wstring() const;
    };
} // namespace YanLib::ui::components
#endif // PAGE_H
