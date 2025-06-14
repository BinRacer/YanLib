/* clang-format off */
/*
 * @file list_box.h
 * @date 2025-05-26
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
#ifndef LIST_BOX_H
#define LIST_BOX_H
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
#ifndef LISTBOXSTYLE
#define LISTBOXSTYLE
    enum class ListBoxStyle : uint32_t {
        Notify = LBS_NOTIFY,
        Sort = LBS_SORT,
        NoRedraw = LBS_NOREDRAW,
        MultipleSelect = LBS_MULTIPLESEL,
        OwnerDrawFixed = LBS_OWNERDRAWFIXED,
        OwnerDrawVariable = LBS_OWNERDRAWVARIABLE,
        HasStrings = LBS_HASSTRINGS,
        UseTabStops = LBS_USETABSTOPS,
        NoIntegralHeight = LBS_NOINTEGRALHEIGHT,
        MultiColumn = LBS_MULTICOLUMN,
        WantKeyboardInput = LBS_WANTKEYBOARDINPUT,
        ExtendedSelect = LBS_EXTENDEDSEL,
        DisableNoScroll = LBS_DISABLENOSCROLL,
        NoData = LBS_NODATA,
        NoSelect = LBS_NOSEL,
        ComboBox = LBS_COMBOBOX,
        Standard = LBS_STANDARD
    };
    inline ListBoxStyle operator|(ListBoxStyle a, ListBoxStyle b) {
        return static_cast<ListBoxStyle>(static_cast<uint32_t>(a) |
                                         static_cast<uint32_t>(b));
    }
#endif
#ifndef FILETYPE
#define FILETYPE

    enum class FileType : uint32_t {
        ReadWrite = DDL_READWRITE,
        ReadOnly = DDL_READONLY,
        Hidden = DDL_HIDDEN,
        System = DDL_SYSTEM,
        Directory = DDL_DIRECTORY,
        Archive = DDL_ARCHIVE,
        PostMsgs = DDL_POSTMSGS,
        Drives = DDL_DRIVES,
        Exclusive = DDL_EXCLUSIVE,
    };

    inline FileType operator|(FileType a, FileType b) {
        return static_cast<FileType>(static_cast<uint32_t>(a) |
                                     static_cast<uint32_t>(b));
    }
#endif
#ifndef LISTBOXMESSAGE
#define LISTBOXMESSAGE
    enum class ListBoxMessage : uint32_t {
        AddFile = LB_ADDFILE,
        AddString = LB_ADDSTRING,
        DeleteString = LB_DELETESTRING,
        Dir = LB_DIR,
        FindString = LB_FINDSTRING,
        FindStringExact = LB_FINDSTRINGEXACT,
        GetAnchorIndex = LB_GETANCHORINDEX,
        GetCaretIndex = LB_GETCARETINDEX,
        GetCount = LB_GETCOUNT,
        GetCurrentSelect = LB_GETCURSEL,
        GetHorizontalExtent = LB_GETHORIZONTALEXTENT,
        GetItemData = LB_GETITEMDATA,
        GetItemHeight = LB_GETITEMHEIGHT,
        GetItemRect = LB_GETITEMRECT,
        GetListBoxInfo = LB_GETLISTBOXINFO,
        GetLocale = LB_GETLOCALE,
        GetSelect = LB_GETSEL,
        GetSelCount = LB_GETSELCOUNT,
        GetSelItems = LB_GETSELITEMS,
        GetText = LB_GETTEXT,
        GetTextLen = LB_GETTEXTLEN,
        GetTopIndex = LB_GETTOPINDEX,
        InitStorage = LB_INITSTORAGE,
        InsertString = LB_INSERTSTRING,
        ItemFromPoint = LB_ITEMFROMPOINT,
        ResetContent = LB_RESETCONTENT,
        SelectString = LB_SELECTSTRING,
        SelItemRange = LB_SELITEMRANGE,
        SelItemRangeEx = LB_SELITEMRANGEEX,
        SetAnchorIndex = LB_SETANCHORINDEX,
        SetCaretIndex = LB_SETCARETINDEX,
        SetColumnWidth = LB_SETCOLUMNWIDTH,
        SetCount = LB_SETCOUNT,
        SetCurrentSelect = LB_SETCURSEL,
        SetHorizontalExtent = LB_SETHORIZONTALEXTENT,
        SetItemData = LB_SETITEMDATA,
        SetItemHeight = LB_SETITEMHEIGHT,
        SetLocale = LB_SETLOCALE,
        SetSelect = LB_SETSEL,
        SetTabStops = LB_SETTABSTOPS,
        SetTopIndex = LB_SETTOPINDEX
    };
#endif
#ifndef LISTBOXNOTIFY
#define LISTBOXNOTIFY
    enum class ListBoxNotify : int32_t {
        BeginDrag = DL_BEGINDRAG,
        CancelDrag = DL_CANCELDRAG,
        Dragging = DL_DRAGGING,
        Dropped = DL_DROPPED,
        DoubleClick = LBN_DBLCLK,
        ErrSpace = LBN_ERRSPACE,
        KillFocus = LBN_KILLFOCUS,
        SelectCancel = LBN_SELCANCEL,
        SelectChange = LBN_SELCHANGE,
        SetFocus = LBN_SETFOCUS,
        CharToItem = WM_CHARTOITEM,
        CtlColorListBox = WM_CTLCOLORLISTBOX,
        DeleteItem = WM_DELETEITEM,
        VKeyToItem = WM_VKEYTOITEM
    };
#endif
    class list_box {
    private:
        std::vector<HWND> list_box_handles = {};
        sync::rwlock list_box_rwlock = {};
        uint32_t error_code = 0;

    public:
        list_box(const list_box &other) = delete;

        list_box(list_box &&other) = delete;

        list_box &operator=(const list_box &other) = delete;

        list_box &operator=(list_box &&other) = delete;

        list_box() = default;

        ~list_box();

        HWND create(uintptr_t list_box_id,
                    HWND parent_window_handle,
                    LPARAM lparam,
                    int32_t x,
                    int32_t y,
                    int32_t width,
                    int32_t height,
                    ListBoxStyle style = ListBoxStyle::HasStrings |
                            ListBoxStyle::ExtendedSelect |
                            ListBoxStyle::MultiColumn |
                            ListBoxStyle::MultipleSelect |
                            ListBoxStyle::Notify | ListBoxStyle::UseTabStops |
                            ListBoxStyle::WantKeyboardInput,
                    WindowStyle window_style = WindowStyle::Child |
                            WindowStyle::Visible | WindowStyle::VScroll);

        HWND create(const char *list_box_name,
                    uintptr_t list_box_id,
                    HWND parent_window_handle,
                    LPARAM lparam,
                    int32_t x,
                    int32_t y,
                    int32_t width,
                    int32_t height,
                    ListBoxStyle style = ListBoxStyle::HasStrings |
                            ListBoxStyle::ExtendedSelect |
                            ListBoxStyle::MultiColumn |
                            ListBoxStyle::MultipleSelect |
                            ListBoxStyle::Notify | ListBoxStyle::UseTabStops |
                            ListBoxStyle::WantKeyboardInput,
                    WindowStyle window_style = WindowStyle::Child |
                            WindowStyle::Visible | WindowStyle::VScroll);

        HWND create(const wchar_t *list_box_name,
                    uintptr_t list_box_id,
                    HWND parent_window_handle,
                    LPARAM lparam,
                    int32_t x,
                    int32_t y,
                    int32_t width,
                    int32_t height,
                    ListBoxStyle style = ListBoxStyle::HasStrings |
                            ListBoxStyle::ExtendedSelect |
                            ListBoxStyle::MultiColumn |
                            ListBoxStyle::MultipleSelect |
                            ListBoxStyle::Notify | ListBoxStyle::UseTabStops |
                            ListBoxStyle::WantKeyboardInput,
                    WindowStyle window_style = WindowStyle::Child |
                            WindowStyle::Visible | WindowStyle::VScroll);

        bool destroy(HWND list_box_handle);

        bool enable(HWND list_box_handle);

        bool disable(HWND list_box_handle);

        int32_t fill(HWND list_box_handle,
                     const char *path_spec,
                     FileType type = FileType::Drives | FileType::Directory |
                             FileType::ReadWrite,
                     helper::CodePage code_page = helper::curr_code_page());

        int32_t fill(HWND list_box_handle,
                     const wchar_t *path_spec,
                     FileType type = FileType::Drives | FileType::Directory |
                             FileType::ReadWrite);

        int32_t add_text(HWND list_box_handle,
                         std::string &text,
                         helper::CodePage code_page = helper::curr_code_page());

        int32_t add_text(HWND list_box_handle, std::wstring &text);

        int32_t
        find_text(HWND list_box_handle,
                  std::string &text,
                  int32_t index = -1,
                  helper::CodePage code_page = helper::curr_code_page());

        int32_t
        find_text(HWND list_box_handle, std::wstring &text, int32_t index = -1);

        int32_t
        find_text_exact(HWND list_box_handle,
                        std::string &text,
                        int32_t index = -1,
                        helper::CodePage code_page = helper::curr_code_page());

        int32_t find_text_exact(HWND list_box_handle,
                                std::wstring &text,
                                int32_t index = -1);

        int32_t
        insert_text(HWND list_box_handle,
                    std::string &text,
                    int32_t index = -1,
                    helper::CodePage code_page = helper::curr_code_page());

        int32_t insert_text(HWND list_box_handle,
                            std::wstring &text,
                            int32_t index = -1);

        int32_t
        select_text(HWND list_box_handle,
                    std::string &text,
                    int32_t index = -1,
                    helper::CodePage code_page = helper::curr_code_page());

        int32_t select_text(HWND list_box_handle,
                            std::wstring &text,
                            int32_t index = -1);

        int32_t delete_item(HWND list_box_handle, int32_t index);

        int32_t get_item_text_len(HWND list_box_handle, int32_t index);

        int32_t
        get_item_text(HWND list_box_handle,
                      std::string &text,
                      int32_t index,
                      helper::CodePage code_page = helper::curr_code_page());

        int32_t
        get_item_text(HWND list_box_handle, std::wstring &text, int32_t index);

        int32_t add_data(HWND list_box_handle, LPARAM data);

        int32_t
        find_data(HWND list_box_handle, LPARAM data, int32_t index = -1);

        LPARAM get_data(HWND list_box_handle, int32_t index);

        int32_t set_data(HWND list_box_handle, LPARAM data, int32_t index);

        int32_t
        insert_data(HWND list_box_handle, LPARAM data, int32_t index = -1);

        int32_t
        select_data(HWND list_box_handle, LPARAM data, int32_t index = -1);

        int32_t get_item_height(HWND list_box_handle, int32_t index);

        int32_t
        set_item_height(HWND list_box_handle, int32_t width, int32_t index);

        bool get_item_rect(HWND list_box_handle, RECT *rect, int32_t index);

        int32_t get_select_items(HWND list_box_handle,
                                 std::vector<int32_t> &select_index);

        bool set_item_range(HWND list_box_handle, int32_t start, int32_t end);

        bool unset_item_range(HWND list_box_handle, int32_t start, int32_t end);

        int32_t get_curr_select(HWND list_box_handle);

        int32_t set_curr_select(HWND list_box_handle, int32_t index);

        bool is_select(HWND list_box_handle, int32_t index);

        bool set_select(HWND list_box_handle, int32_t index);

        bool unset_select(HWND list_box_handle, int32_t index);

        int32_t get_select_count(HWND list_box_handle);

        int32_t get_caret_index(HWND list_box_handle);

        bool set_caret_index(HWND list_box_handle, int32_t index);

        int32_t get_top_index(HWND list_box_handle);

        bool set_top_index(HWND list_box_handle, int32_t index);

        void reset_content(HWND list_box_handle);

        int32_t get_horiz_extent(HWND list_box_handle);

        void set_horiz_extent(HWND list_box_handle, int32_t extent);

        void set_all_colum_width(HWND list_box_handle, int32_t width);

        int32_t get_item_count(HWND list_box_handle);

        bool set_tab_stops(HWND list_box_handle,
                           std::vector<int32_t> &tab_stops);

        void draw_insert(HWND parent_window_handle,
                         HWND list_box_handle,
                         int32_t icon_id);

        int32_t item_id_from_point(HWND list_box_handle,
                                   POINT point,
                                   bool auto_scroll = true);

        bool modify_to_drag_list(HWND list_box_handle);

        [[nodiscard]] uint32_t err_code() const;

        [[nodiscard]] std::string err_string() const;

        [[nodiscard]] std::wstring err_wstring() const;
    };
} // namespace YanLib::ui::components
#endif // LIST_BOX_H
