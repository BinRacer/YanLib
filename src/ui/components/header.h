/* clang-format off */
/*
 * @file header.h
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
#ifndef HEADER_H
#define HEADER_H
#ifndef UNICODE
#define UNICODE
#endif
#ifndef _UNICODE
#define _UNICODE
#endif
#include <Windows.h>
#include <CommCtrl.h>
#include <cstdint>
#include <vector>
#include <string>
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
#ifndef HEADERSTYLE
#define HEADERSTYLE
    enum class HeaderStyle : uint32_t {
        Horiz = HDS_HORZ,
        Buttons = HDS_BUTTONS,
        HotTrack = HDS_HOTTRACK,
        Hidden = HDS_HIDDEN,
        DragDrop = HDS_DRAGDROP,
        FullDrag = HDS_FULLDRAG,
        FilterBar = HDS_FILTERBAR,
        Flat = HDS_FLAT,
        CheckBoxes = HDS_CHECKBOXES,
        NoSizing = HDS_NOSIZING,
        Overflow = HDS_OVERFLOW,
    };
    inline HeaderStyle operator|(HeaderStyle a, HeaderStyle b) {
        return static_cast<HeaderStyle>(static_cast<uint32_t>(a) |
                                        static_cast<uint32_t>(b));
    }
#endif
#ifndef HEADERMESSAGE
#define HEADERMESSAGE
    enum class HeaderMessage : uint32_t {
        ClearFilter = HDM_CLEARFILTER,
        CreateDragImage = HDM_CREATEDRAGIMAGE,
        DeleteItem = HDM_DELETEITEM,
        EditFilter = HDM_EDITFILTER,
        GetBitmapMargin = HDM_GETBITMAPMARGIN,
        GetFocusedItem = HDM_GETFOCUSEDITEM,
        GetImageList = HDM_GETIMAGELIST,
        GetItem = HDM_GETITEM,
        GetItemCount = HDM_GETITEMCOUNT,
        GetItemDropDownRect = HDM_GETITEMDROPDOWNRECT,
        GetItemRect = HDM_GETITEMRECT,
        GetOrderArray = HDM_GETORDERARRAY,
        GetOverflowRect = HDM_GETOVERFLOWRECT,
        GetUnicodeFormat = HDM_GETUNICODEFORMAT,
        HitTest = HDM_HITTEST,
        InsertItem = HDM_INSERTITEM,
        Layout = HDM_LAYOUT,
        OrderToIndex = HDM_ORDERTOINDEX,
        SetBitmapMargin = HDM_SETBITMAPMARGIN,
        SetFilterChangeTimeout = HDM_SETFILTERCHANGETIMEOUT,
        SetFocusedItem = HDM_SETFOCUSEDITEM,
        SetHotDivider = HDM_SETHOTDIVIDER,
        SetImageList = HDM_SETIMAGELIST,
        SetItem = HDM_SETITEM,
        SetOrderArray = HDM_SETORDERARRAY,
        SetUnicodeFormat = HDM_SETUNICODEFORMAT,
    };
#endif
#ifndef HEADERNOTIFY
#define HEADERNOTIFY
    enum class HeaderNotify : uint32_t {
        BeginDrag = HDN_BEGINDRAG,
        BeginFilterEdit = HDN_BEGINFILTEREDIT,
        BeginTrack = HDN_BEGINTRACK,
        DividerDblClick = HDN_DIVIDERDBLCLICK,
        DropDown = HDN_DROPDOWN,
        EndDrag = HDN_ENDDRAG,
        EndFilterEdit = HDN_ENDFILTEREDIT,
        FilterBtnClick = HDN_FILTERBTNCLICK,
        FilterChange = HDN_FILTERCHANGE,
        GetDispInfo = HDN_GETDISPINFO,
        ItemChanged = HDN_ITEMCHANGED,
        ItemChanging = HDN_ITEMCHANGING,
        ItemClick = HDN_ITEMCLICK,
        ItemDblClick = HDN_ITEMDBLCLICK,
        ItemKeyDown = HDN_ITEMKEYDOWN,
        ItemStateIconClick = HDN_ITEMSTATEICONCLICK,
        OverflowClick = HDN_OVERFLOWCLICK,
        Track = HDN_TRACK,
        CustomDraw = NM_CUSTOMDRAW,
        RightClick = NM_RCLICK,
        ReleasedCapture = NM_RELEASEDCAPTURE,
    };
#endif
    class header {
    private:
        std::vector<HWND> header_handles = {};
        sync::rwlock header_rwlock = {};
        uint32_t error_code = 0;

    public:
        header(const header &other) = delete;

        header(header &&other) = delete;

        header &operator=(const header &other) = delete;

        header &operator=(header &&other) = delete;

        header();

        ~header();

        HWND create(uintptr_t header_id,
                    HWND parent_window_handle,
                    LPARAM lparam,
                    int32_t x,
                    int32_t y,
                    int32_t width,
                    int32_t height,
                    HeaderStyle style = HeaderStyle::Buttons |
                            HeaderStyle::DragDrop | HeaderStyle::FilterBar |
                            HeaderStyle::HotTrack | HeaderStyle::CheckBoxes |
                            HeaderStyle::Overflow | HeaderStyle::Flat |
                            HeaderStyle::Horiz,
                    WindowStyle window_style = WindowStyle::Child |
                            WindowStyle::Visible | WindowStyle::Border);

        HWND create(const char *header_name,
                    uintptr_t header_id,
                    HWND parent_window_handle,
                    LPARAM lparam,
                    int32_t x,
                    int32_t y,
                    int32_t width,
                    int32_t height,
                    HeaderStyle style = HeaderStyle::Buttons |
                            HeaderStyle::DragDrop | HeaderStyle::FilterBar |
                            HeaderStyle::HotTrack | HeaderStyle::CheckBoxes |
                            HeaderStyle::Overflow | HeaderStyle::Flat |
                            HeaderStyle::Horiz,
                    WindowStyle window_style = WindowStyle::Child |
                            WindowStyle::Visible | WindowStyle::Border);

        HWND create(const wchar_t *header_name,
                    uintptr_t header_id,
                    HWND parent_window_handle,
                    LPARAM lparam,
                    int32_t x,
                    int32_t y,
                    int32_t width,
                    int32_t height,
                    HeaderStyle style = HeaderStyle::Buttons |
                            HeaderStyle::DragDrop | HeaderStyle::FilterBar |
                            HeaderStyle::HotTrack | HeaderStyle::CheckBoxes |
                            HeaderStyle::Overflow | HeaderStyle::Flat |
                            HeaderStyle::Horiz,
                    WindowStyle window_style = WindowStyle::Child |
                            WindowStyle::Visible | WindowStyle::Border);

        bool destroy(HWND header_handle);

        HIMAGELIST create_drag_image(HWND header_handle, int32_t index);

        HIMAGELIST get_image_list(HWND header_handle);

        HIMAGELIST set_image_list(HWND header_handle,
                                  HIMAGELIST image_list_handle);

        HIMAGELIST get_state_image_list(HWND header_handle);

        HIMAGELIST set_state_image_list(HWND header_handle,
                                        HIMAGELIST image_list_handle);

        int32_t get_bitmap_margin(HWND header_handle);

        int32_t set_bitmap_margin(HWND header_handle, int32_t width);

        bool clear_all_filters(HWND header_handle);

        bool clear_filter(HWND header_handle, int32_t index);

        bool set_filter(HWND header_handle,
                        int32_t index,
                        bool discard_change = false);

        int32_t insert_item(HWND header_handle,
                            const HDITEMW *item,
                            int32_t index = INT32_MAX);

        bool delete_item(HWND header_handle, int32_t index);

        bool get_item(HWND header_handle, HDITEMW *item, int32_t index);

        bool set_item(HWND header_handle, HDITEMW *item, int32_t index);

        int32_t get_item_count(HWND header_handle);

        bool get_item_rect(HWND header_handle, RECT *rect, int32_t index);

        bool
        get_item_drop_down_rect(HWND header_handle, RECT *rect, int32_t index);

        int32_t get_focused_item(HWND header_handle);

        bool set_focused_item(HWND header_handle, int32_t index);

        bool get_item_order(HWND header_handle, std::vector<int32_t> &order);

        bool set_item_order(HWND header_handle, std::vector<int32_t> &order);

        int32_t order_to_index(HWND header_handle, int32_t order);

        bool get_overflow_rect(HWND header_handle, RECT *rect);

        bool is_ansi_format(HWND header_handle);

        bool is_unicode_format(HWND header_handle);

        void set_unicode_format(HWND header_handle);

        void set_ansi_format(HWND header_handle);

        bool get_layout(HWND header_handle, HDLAYOUT *layout);

        int32_t set_filter_change_timeout(HWND header_handle,
                                          int32_t milli_seconds);

        int32_t set_hot_divider(HWND header_handle, uint32_t x, uint32_t y);

        int32_t set_hot_divider(HWND header_handle, uint32_t index);

        [[nodiscard]] uint32_t err_code() const;

        [[nodiscard]] std::string err_string() const;

        [[nodiscard]] std::wstring err_wstring() const;
    };
} // namespace YanLib::ui::components
#endif // HEADER_H
