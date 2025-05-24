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
#ifndef COMBOBOXRETCODE
#define COMBOBOXRETCODE

    enum class ComboBoxRetCode : int32_t {
        Ok = CB_OKAY,
        Error = CB_ERR,
        ErrorNoSpace = CB_ERRSPACE,
    };
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

        ComboBoxRetCode
        fill(HWND combobox_handle,
             char *path_spec,
             FileType type = FileType::Drives | FileType::Directory |
                     FileType::ReadWrite,
             helper::CodePage code_page = helper::CodePage::GB2312);

        ComboBoxRetCode fill(HWND combobox_handle,
                             wchar_t *path_spec,
                             FileType type = FileType::Drives |
                                     FileType::Directory | FileType::ReadWrite);

        ComboBoxRetCode
        add_text(HWND combobox_handle,
                 std::string &text,
                 helper::CodePage code_page = helper::CodePage::GB2312);

        ComboBoxRetCode add_text(HWND combobox_handle, std::wstring &text);

        ComboBoxRetCode
        insert_text(HWND combobox_handle,
                    std::string &text,
                    int32_t index = -1,
                    helper::CodePage code_page = helper::CodePage::GB2312);

        ComboBoxRetCode insert_text(HWND combobox_handle,
                                    std::wstring &text,
                                    int32_t index = -1);

        ComboBoxRetCode
        select_text(HWND combobox_handle,
                    std::string &text,
                    int32_t index = -1,
                    helper::CodePage code_page = helper::CodePage::GB2312);

        ComboBoxRetCode select_text(HWND combobox_handle,
                                    std::wstring &text,
                                    int32_t index = -1);

        ComboBoxRetCode
        find_text(HWND combobox_handle,
                  std::string &text,
                  int32_t index = -1,
                  helper::CodePage code_page = helper::CodePage::GB2312);

        ComboBoxRetCode
        find_text(HWND combobox_handle, std::wstring &text, int32_t index = -1);

        ComboBoxRetCode
        find_exact_text(HWND combobox_handle,
                        std::string &text,
                        int32_t index = -1,
                        helper::CodePage code_page = helper::CodePage::GB2312);

        ComboBoxRetCode find_exact_text(HWND combobox_handle,
                                        std::wstring &text,
                                        int32_t index = -1);

        ComboBoxRetCode delete_item(HWND combobox_handle, int32_t index);

        void clear(HWND combobox_handle);

        void set_text_limit(HWND combobox_handle, int32_t limit);

        int32_t get_text_len(HWND combobox_handle);

        int32_t get_text(HWND combobox_handle, std::string &text);

        int32_t get_text(HWND combobox_handle, std::wstring &text);

        int32_t get_item_count(HWND combobox_handle);

        int32_t get_item_text_len(HWND combobox_handle, int32_t index);

        ComboBoxRetCode
        get_item_text(HWND combobox_handle,
                      std::string &text,
                      int32_t index,
                      helper::CodePage code_page = helper::CodePage::GB2312);

        ComboBoxRetCode
        get_item_text(HWND combobox_handle, std::wstring &text, int32_t index);

        ComboBoxRetCode replace_item_text(
                HWND combobox_handle,
                std::string &text,
                int32_t index,
                helper::CodePage code_page = helper::CodePage::GB2312);

        ComboBoxRetCode replace_item_text(HWND combobox_handle,
                                          std::wstring &text,
                                          int32_t index);

        int32_t get_item_height(HWND combobox_handle);

        bool set_item_height(HWND combobox_handle,
                             int32_t height,
                             int32_t index = -1);

        bool set_text(HWND combobox_handle, std::string &text);

        bool set_text(HWND combobox_handle, std::wstring &text);

        ComboBoxRetCode add_data(HWND combobox_handle, LPARAM data);

        ComboBoxRetCode
        insert_data(HWND combobox_handle, LPARAM data, int32_t index = -1);

        ComboBoxRetCode
        select_data(HWND combobox_handle, LPARAM data, int32_t index = -1);

        ComboBoxRetCode
        find_data(HWND combobox_handle, LPARAM data, int32_t index = -1);

        LPARAM get_data(HWND combobox_handle, int32_t index);

        ComboBoxRetCode
        set_data(HWND combobox_handle, LPARAM data, int32_t index);

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

        ComboBoxRetCode get_curr_select(HWND combobox_handle);

        ComboBoxRetCode set_curr_select(HWND combobox_handle, int32_t index);

        bool is_extended_ui(HWND combobox_handle);

        bool is_default_ui(HWND combobox_handle);

        ComboBoxRetCode set_extended_ui(HWND combobox_handle);

        ComboBoxRetCode set_default_ui(HWND combobox_handle);

        int32_t get_min_visible(HWND combobox_handle);

        bool set_min_visible(HWND combobox_handle, int32_t num);

        [[nodiscard]] uint32_t err_code() const;

        [[nodiscard]] std::string err_string() const;

        [[nodiscard]] std::wstring err_wstring() const;
    };
} // namespace YanLib::components
#endif // COMBOBOX_H
