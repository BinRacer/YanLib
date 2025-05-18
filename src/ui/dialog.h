//
// Created by forkernel on 2025/4/30.
//

#ifndef DIALOG_H
#define DIALOG_H
#include <Windows.h>
#include <string>
#include <vector>
#include "sync/rwlock.h"

namespace YanLib::ui {
#ifndef BUTTONSTATE
#define BUTTONSTATE

enum class ButtonState : uint32_t {
    Unchecked     = BST_UNCHECKED,
    Checked       = BST_CHECKED,
    Indeterminate = BST_INDETERMINATE,
};
#endif
#ifndef FILETYPE
#define FILETYPE

enum class FileType : uint32_t {
    ReadWrite = DDL_READWRITE,
    ReadOnly  = DDL_READONLY,
    Hidden    = DDL_HIDDEN,
    System    = DDL_SYSTEM,
    Directory = DDL_DIRECTORY,
    Archive   = DDL_ARCHIVE,
    PostMsgs  = DDL_POSTMSGS,
    Drives    = DDL_DRIVES,
    Exclusive = DDL_EXCLUSIVE,
};

inline FileType operator|(FileType a, FileType b) {
    return static_cast<FileType>(
        static_cast<uint32_t>(a) | static_cast<uint32_t>(b));
}
#endif
#ifndef ITEMDPIBEHAVIORS
#define ITEMDPIBEHAVIORS

enum class ItemDpiBehavior : uint32_t {
    Default           = DCDC_DEFAULT,
    DisableFontUpdate = DCDC_DISABLE_FONT_UPDATE,
    DisableReLayout   = DCDC_DISABLE_RELAYOUT,
};
#endif
#ifndef DIALOGDPIBEHAVIORS
#define DIALOGDPIBEHAVIORS

enum class DialogDpiBehavior : uint32_t {
    Default             = DDC_DEFAULT,
    DisableAll          = DDC_DISABLE_ALL,
    DisableResize       = DDC_DISABLE_RESIZE,
    DisableItemReLayout = DDC_DISABLE_CONTROL_RELAYOUT,
};
#endif
class dialog {
private:
    std::vector<HWND> dialog_modeless_handle = {};
    sync::rwlock      rwlock                 = {};
    uint32_t          error_code             = 0;

public:
    dialog(const dialog &other)            = delete;

    dialog(dialog &&other)                 = delete;

    dialog &operator=(const dialog &other) = delete;

    dialog &operator=(dialog &&other)      = delete;

    dialog()                               = default;

    ~dialog();

    INT_PTR create(HINSTANCE instance_handle,
        const char          *template_name,
        HWND                 parent_window_handle,
        DLGPROC              dialog_func);

    INT_PTR create(HINSTANCE instance_handle,
        const wchar_t       *template_name,
        HWND                 parent_window_handle,
        DLGPROC              dialog_func);

    INT_PTR create(HINSTANCE instance_handle,
        const char          *template_name,
        HWND                 parent_window_handle,
        DLGPROC              dialog_func,
        LPARAM               init_param);

    INT_PTR create(HINSTANCE instance_handle,
        const wchar_t       *template_name,
        HWND                 parent_window_handle,
        DLGPROC              dialog_func,
        LPARAM               init_param);

    INT_PTR create(HINSTANCE instance_handle,
        const DLGTEMPLATE   *dialog_template,
        HWND                 parent_window_handle,
        DLGPROC              dialog_func);

    INT_PTR create(HINSTANCE instance_handle,
        const DLGTEMPLATE   *dialog_template,
        HWND                 parent_window_handle,
        DLGPROC              dialog_func,
        LPARAM               init_param);

    HWND create_modeless(HINSTANCE instance_handle,
        const wchar_t             *template_name,
        HWND                       parent_window_handle,
        DLGPROC                    dialog_func);

    HWND create_modeless(HINSTANCE instance_handle,
        const wchar_t             *template_name,
        HWND                       parent_window_handle,
        DLGPROC                    dialog_func,
        LPARAM                     init_param);

    HWND create_modeless(HINSTANCE instance_handle,
        const DLGTEMPLATE         *dialog_template,
        HWND                       parent_window_handle,
        DLGPROC                    dialog_func);

    HWND create_modeless(HINSTANCE instance_handle,
        const DLGTEMPLATE         *dialog_template,
        HWND                       parent_window_handle,
        DLGPROC                    dialog_func,
        LPARAM                     init_param);

    bool destroy(HWND dialog_handle, INT_PTR result);

    bool destroy_modeless(HWND dialog_handle);

    bool set_button_state(HWND dialog_handle,
        int32_t                button_id,
        ButtonState            state = ButtonState::Checked);

    bool set_radio_state(HWND dialog_handle,
        int32_t               first_button_id,
        int32_t               last_button_id,
        int32_t               check_button_id);

    LRESULT
    default_proc(HWND dialog_handle,
        uint32_t      msg,
        WPARAM        wparam,
        LPARAM        lparam);

    int32_t fill_listbox(HWND dialog_handle,
        char                 *path_spec,
        int32_t               listbox_id,
        int32_t               static_id,
        FileType file_type = FileType::Drives | FileType::Directory |
                             FileType::ReadWrite);

    int32_t fill_listbox(HWND dialog_handle,
        wchar_t              *path_spec,
        int32_t               listbox_id,
        int32_t               static_id,
        FileType file_type = FileType::Drives | FileType::Directory |
                             FileType::ReadWrite);

    int32_t fill_combobox(HWND dialog_handle,
        char                  *path_spec,
        int32_t                combobox_id,
        int32_t                static_id,
        FileType file_type = FileType::Drives | FileType::Directory |
                             FileType::ReadWrite);

    int32_t fill_combobox(HWND dialog_handle,
        wchar_t               *path_spec,
        int32_t                combobox_id,
        int32_t                static_id,
        FileType file_type = FileType::Drives | FileType::Directory |
                             FileType::ReadWrite);

    bool get_select_combobox(HWND dialog_handle,
        std::string              &path,
        int32_t                   combobox_id);

    bool get_select_combobox(HWND dialog_handle,
        std::wstring             &path,
        int32_t                   combobox_id);

    bool get_select_listbox(HWND dialog_handle,
        std::string             &path,
        int32_t                  listbox_id);

    bool get_select_listbox(HWND dialog_handle,
        std::wstring            &path,
        int32_t                  listbox_id);

    int32_t get_item_id(HWND item_handle);

    HWND get_item_handle(HWND dialog_handle, int32_t item_id);

    bool get_item_int(HWND dialog_handle,
        int32_t            item_id,
        uint32_t          *value,
        bool               is_signed);

    bool set_item_int(HWND dialog_handle,
        int32_t            item_id,
        uint32_t           value,
        bool               is_signed);

    uint32_t
    get_item_text(HWND dialog_handle, int32_t item_id, std::string &text);

    uint32_t
    get_item_text(HWND dialog_handle, int32_t item_id, std::wstring &text);

    bool set_item_text(HWND dialog_handle, int32_t item_id, const char *text);

    bool
    set_item_text(HWND dialog_handle, int32_t item_id, const wchar_t *text);

    HWND next_group_item(HWND dialog_handle,
        HWND                  item_handle,
        bool                  search_upward = false);

    HWND next_tab_item(HWND dialog_handle,
        HWND                item_handle,
        bool                search_upward = false);

    ButtonState is_button_checked(HWND dialog_handle, int32_t button_id);

    ItemDpiBehavior get_item_dpi_behavior(HWND dialog_handle);

    bool set_item_dpi_behavior(HWND dialog_handle,
        ItemDpiBehavior             mask,
        ItemDpiBehavior             values);

    DialogDpiBehavior get_dpi_behavior(HWND dialog_handle);

    bool set_dpi_behavior(HWND dialog_handle,
        DialogDpiBehavior      mask,
        DialogDpiBehavior      values);

    long get_base_units();

    bool base_units_to_screen_point(HWND dialog_handle, RECT *rect);

    [[nodiscard]] uint32_t err_code() const;

    [[nodiscard]] std::string err_string() const;

    [[nodiscard]] std::wstring err_wstring() const;
};
} // namespace YanLib::ui
#endif // DIALOG_H
