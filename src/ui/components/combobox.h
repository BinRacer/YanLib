//
// Created by forkernel on 2025/5/24.
//

#ifndef COMBOBOX_H
#define COMBOBOX_H
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
#include "helper/convert.h"
#pragma comment(lib, "Comctl32.lib")
#pragma comment(linker, "\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
namespace YanLib::components {
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
#ifndef COMBOBOXSTYLE
#define COMBOBOXSTYLE

    enum class ComboBoxStyle : uint32_t {
        Simple = CBS_SIMPLE,
        DropDown = CBS_DROPDOWN,
        DropDownList = CBS_DROPDOWNLIST,
        OwnerDrawFixed = CBS_OWNERDRAWFIXED,
        OwnerDrawVariable = CBS_OWNERDRAWVARIABLE,
        AutoHorizScroll = CBS_AUTOHSCROLL,
        OemConvert = CBS_OEMCONVERT,
        Sort = CBS_SORT,
        HasStrings = CBS_HASSTRINGS,
        NoIntegralHeight = CBS_NOINTEGRALHEIGHT,
        DisableNoScroll = CBS_DISABLENOSCROLL,
        Uppercase = CBS_UPPERCASE,
        Lowercase = CBS_LOWERCASE,
    };

    inline ComboBoxStyle operator|(ComboBoxStyle a, ComboBoxStyle b) {
        return static_cast<ComboBoxStyle>(static_cast<uint32_t>(a) |
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
#ifndef COMBOBOXMESSAGE
#define COMBOBOXMESSAGE
    enum class ComboBoxMessage : uint32_t {
        AddString = CB_ADDSTRING,
        DeleteString = CB_DELETESTRING,
        Dir = CB_DIR,
        FindString = CB_FINDSTRING,
        FindStringExact = CB_FINDSTRINGEXACT,
        GetComboBoxInfo = CB_GETCOMBOBOXINFO,
        GetCount = CB_GETCOUNT,
        GetCueBanner = CB_GETCUEBANNER,
        GetCurSel = CB_GETCURSEL,
        GetDroppedControlRect = CB_GETDROPPEDCONTROLRECT,
        GetDroppedState = CB_GETDROPPEDSTATE,
        GetDroppedWidth = CB_GETDROPPEDWIDTH,
        GetEditSel = CB_GETEDITSEL,
        GetExtendedUI = CB_GETEXTENDEDUI,
        GetHorizontalExtent = CB_GETHORIZONTALEXTENT,
        GetItemData = CB_GETITEMDATA,
        GetItemHeight = CB_GETITEMHEIGHT,
        GetLBText = CB_GETLBTEXT,
        GetLBTextLen = CB_GETLBTEXTLEN,
        GetLocale = CB_GETLOCALE,
        GetMinVisible = CB_GETMINVISIBLE,
        GetTopIndex = CB_GETTOPINDEX,
        InitStorage = CB_INITSTORAGE,
        InsertString = CB_INSERTSTRING,
        LimitText = CB_LIMITTEXT,
        ResetContent = CB_RESETCONTENT,
        SelectString = CB_SELECTSTRING,
        SetCueBanner = CB_SETCUEBANNER,
        SetCurSel = CB_SETCURSEL,
        SetDroppedWidth = CB_SETDROPPEDWIDTH,
        SetEditSel = CB_SETEDITSEL,
        SetExtendedUI = CB_SETEXTENDEDUI,
        SetHorizontalExtent = CB_SETHORIZONTALEXTENT,
        SetItemData = CB_SETITEMDATA,
        SetItemHeight = CB_SETITEMHEIGHT,
        SetLocale = CB_SETLOCALE,
        SetMinVisible = CB_SETMINVISIBLE,
        SetTopIndex = CB_SETTOPINDEX,
        ShowDropDown = CB_SHOWDROPDOWN,
    };
#endif
#ifndef COMBOBOXNOTIFY
#define COMBOBOXNOTIFY
    enum class ComboBoxNotify : int32_t {
        CloseUp = CBN_CLOSEUP,
        DoubleClick = CBN_DBLCLK,
        DropDown = CBN_DROPDOWN,
        EditChange = CBN_EDITCHANGE,
        EditUpdate = CBN_EDITUPDATE,
        ErrSpace = CBN_ERRSPACE,
        KillFocus = CBN_KILLFOCUS,
        SelChange = CBN_SELCHANGE,
        SelEndCancel = CBN_SELENDCANCEL,
        SelEndOK = CBN_SELENDOK,
        SetFocus = CBN_SETFOCUS,
        CompareItem = WM_COMPAREITEM,
        DrawItem = WM_DRAWITEM,
        MeasureItem = WM_MEASUREITEM
    };
#endif
    class combobox {
    private:
        uint32_t error_code = 0;

    public:
        combobox(const combobox &other) = delete;

        combobox(combobox &&other) = delete;

        combobox &operator=(const combobox &other) = delete;

        combobox &operator=(combobox &&other) = delete;

        combobox() = default;

        ~combobox() = default;

        HWND create(uintptr_t combobox_id,
                    HWND parent_window_handle,
                    LPARAM lparam,
                    int32_t x,
                    int32_t y,
                    int32_t width,
                    int32_t height,
                    ComboBoxStyle style = ComboBoxStyle::DropDownList |
                            ComboBoxStyle::AutoHorizScroll |
                            ComboBoxStyle::HasStrings,
                    WindowStyle window_style = WindowStyle::Child |
                            WindowStyle::Visible | WindowStyle::VScroll);

        bool enable(HWND combobox_handle);

        bool disable(HWND combobox_handle);

        int32_t fill(HWND combobox_handle,
                     char *path_spec,
                     FileType type = FileType::Drives | FileType::Directory |
                             FileType::ReadWrite,
                     helper::CodePage code_page = helper::CodePage::GB2312);

        int32_t fill(HWND combobox_handle,
                     wchar_t *path_spec,
                     FileType type = FileType::Drives | FileType::Directory |
                             FileType::ReadWrite);

        int32_t add_text(HWND combobox_handle,
                         std::string &text,
                         helper::CodePage code_page = helper::CodePage::GB2312);

        int32_t add_text(HWND combobox_handle, std::wstring &text);

        int32_t
        insert_text(HWND combobox_handle,
                    std::string &text,
                    int32_t index = -1,
                    helper::CodePage code_page = helper::CodePage::GB2312);

        int32_t insert_text(HWND combobox_handle,
                            std::wstring &text,
                            int32_t index = -1);

        int32_t
        select_text(HWND combobox_handle,
                    std::string &text,
                    int32_t index = -1,
                    helper::CodePage code_page = helper::CodePage::GB2312);

        int32_t select_text(HWND combobox_handle,
                            std::wstring &text,
                            int32_t index = -1);

        int32_t
        find_text(HWND combobox_handle,
                  std::string &text,
                  int32_t index = -1,
                  helper::CodePage code_page = helper::CodePage::GB2312);

        int32_t
        find_text(HWND combobox_handle, std::wstring &text, int32_t index = -1);

        int32_t
        find_exact_text(HWND combobox_handle,
                        std::string &text,
                        int32_t index = -1,
                        helper::CodePage code_page = helper::CodePage::GB2312);

        int32_t find_exact_text(HWND combobox_handle,
                                std::wstring &text,
                                int32_t index = -1);

        int32_t delete_item(HWND combobox_handle, int32_t index);

        void clear(HWND combobox_handle);

        void set_text_limit(HWND combobox_handle, int32_t limit);

        int32_t get_text_len(HWND combobox_handle);

        int32_t get_text(HWND combobox_handle, std::string &text);

        int32_t get_text(HWND combobox_handle, std::wstring &text);

        int32_t get_item_count(HWND combobox_handle);

        int32_t get_item_text_len(HWND combobox_handle, int32_t index);

        int32_t
        get_item_text(HWND combobox_handle,
                      std::string &text,
                      int32_t index,
                      helper::CodePage code_page = helper::CodePage::GB2312);

        int32_t
        get_item_text(HWND combobox_handle, std::wstring &text, int32_t index);

        int32_t replace_item_text(
                HWND combobox_handle,
                std::string &text,
                int32_t index,
                helper::CodePage code_page = helper::CodePage::GB2312);

        int32_t replace_item_text(HWND combobox_handle,
                                  std::wstring &text,
                                  int32_t index);

        int32_t get_item_height(HWND combobox_handle);

        bool set_item_height(HWND combobox_handle,
                             int32_t height,
                             int32_t index = -1);

        bool set_text(HWND combobox_handle, std::string &text);

        bool set_text(HWND combobox_handle, std::wstring &text);

        int32_t add_data(HWND combobox_handle, LPARAM data);

        int32_t
        insert_data(HWND combobox_handle, LPARAM data, int32_t index = -1);

        int32_t
        select_data(HWND combobox_handle, LPARAM data, int32_t index = -1);

        int32_t
        find_data(HWND combobox_handle, LPARAM data, int32_t index = -1);

        LPARAM get_data(HWND combobox_handle, int32_t index);

        int32_t set_data(HWND combobox_handle, LPARAM data, int32_t index);

        bool get_prompt_banner(
                HWND combobox_handle,
                std::string &text,
                helper::CodePage code_page = helper::CodePage::GB2312);

        bool get_prompt_banner(HWND combobox_handle, std::wstring &text);

        bool set_prompt_banner(
                HWND combobox_handle,
                std::string &text,
                helper::CodePage code_page = helper::CodePage::GB2312);

        bool set_prompt_banner(HWND combobox_handle, std::wstring &text);

        int32_t get_curr_select(HWND combobox_handle);

        int32_t set_curr_select(HWND combobox_handle, int32_t index);

        bool is_extended_ui(HWND combobox_handle);

        bool is_default_ui(HWND combobox_handle);

        int32_t set_extended_ui(HWND combobox_handle);

        int32_t set_default_ui(HWND combobox_handle);

        int32_t get_min_visible(HWND combobox_handle);

        bool set_min_visible(HWND combobox_handle, int32_t num);

        void show_drop_down(HWND combobox_handle);

        void hide_drop_down(HWND combobox_handle);

        bool is_drop_down_visible(HWND combobox_handle);

        void get_dropped_control_rect(HWND combobox_handle, RECT *rect);

        bool get_info(HWND combobox_handle, COMBOBOXINFO *combobox_info);

        [[nodiscard]] uint32_t err_code() const;

        [[nodiscard]] std::string err_string() const;

        [[nodiscard]] std::wstring err_wstring() const;
    };
} // namespace YanLib::components
#endif // COMBOBOX_H
