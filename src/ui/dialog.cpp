//
// Created by forkernel on 2025/4/30.
//

#include "dialog.h"
#include "helper/convert.h"

namespace YanLib::ui {
dialog::~dialog() {
    for (auto &handle : dialog_modeless_handle) {
        if (handle && IsWindow(handle)) {
            DestroyWindow(handle);
            handle = nullptr;
        }
    }
    dialog_modeless_handle.clear();
}

INT_PTR dialog::create(HINSTANCE instance_handle,
    const char                  *template_name,
    HWND                         hwnd_parent,
    DLGPROC                      dialog_func) {
    INT_PTR result = DialogBoxParamA(
        instance_handle, template_name, hwnd_parent, dialog_func, 0L);
    if (result == -1) {
        error_code = GetLastError();
    }
    return result;
}

INT_PTR dialog::create(HINSTANCE instance_handle,
    const wchar_t               *template_name,
    HWND                         hwnd_parent,
    DLGPROC                      dialog_func) {
    INT_PTR result = DialogBoxParamW(
        instance_handle, template_name, hwnd_parent, dialog_func, 0L);
    if (result == -1) {
        error_code = GetLastError();
    }
    return result;
}

INT_PTR dialog::create(HINSTANCE instance_handle,
    const char                  *template_name,
    HWND                         hwnd_parent,
    DLGPROC                      dialog_func,
    LPARAM                       init_param) {
    INT_PTR result = DialogBoxParamA(
        instance_handle, template_name, hwnd_parent, dialog_func, init_param);
    if (result == -1) {
        error_code = GetLastError();
    }
    return result;
}

INT_PTR dialog::create(HINSTANCE instance_handle,
    const wchar_t               *template_name,
    HWND                         hwnd_parent,
    DLGPROC                      dialog_func,
    LPARAM                       init_param) {
    INT_PTR result = DialogBoxParamW(
        instance_handle, template_name, hwnd_parent, dialog_func, init_param);
    if (result == -1) {
        error_code = GetLastError();
    }
    return result;
}

INT_PTR dialog::create(HINSTANCE instance_handle,
    const DLGTEMPLATE           *dialog_template,
    HWND                         hwnd_parent,
    DLGPROC                      dialog_func) {
    INT_PTR result = DialogBoxIndirectParamW(
        instance_handle, dialog_template, hwnd_parent, dialog_func, 0L);
    if (result == -1) {
        error_code = GetLastError();
    }
    return result;
}

INT_PTR dialog::create(HINSTANCE instance_handle,
    const DLGTEMPLATE           *dialog_template,
    HWND                         hwnd_parent,
    DLGPROC                      dialog_func,
    LPARAM                       init_param) {
    INT_PTR result = DialogBoxIndirectParamW(
        instance_handle, dialog_template, hwnd_parent, dialog_func, init_param);
    if (result == -1) {
        error_code = GetLastError();
    }
    return result;
}

HWND dialog::create_modeless(HINSTANCE instance_handle,
    const wchar_t                     *template_name,
    HWND                               hwnd_parent,
    DLGPROC                            dialog_func) {
    HWND result = CreateDialogParamW(
        instance_handle, template_name, hwnd_parent, dialog_func, 0L);
    if (!result) {
        error_code = GetLastError();
        return nullptr;
    }
    rwlock.write_lock();
    dialog_modeless_handle.push_back(result);
    rwlock.write_unlock();
    return result;
}

HWND dialog::create_modeless(HINSTANCE instance_handle,
    const wchar_t                     *template_name,
    HWND                               hwnd_parent,
    DLGPROC                            dialog_func,
    LPARAM                             init_param) {
    HWND result = CreateDialogParamW(
        instance_handle, template_name, hwnd_parent, dialog_func, init_param);
    if (!result) {
        error_code = GetLastError();
        return nullptr;
    }
    rwlock.write_lock();
    dialog_modeless_handle.push_back(result);
    rwlock.write_unlock();
    return result;
}

HWND dialog::create_modeless(HINSTANCE instance_handle,
    const DLGTEMPLATE                 *dialog_template,
    HWND                               hwnd_parent,
    DLGPROC                            dialog_func) {
    HWND result = CreateDialogIndirectParamW(
        instance_handle, dialog_template, hwnd_parent, dialog_func, 0L);
    if (!result) {
        error_code = GetLastError();
        return nullptr;
    }
    rwlock.write_lock();
    dialog_modeless_handle.push_back(result);
    rwlock.write_unlock();
    return result;
}

HWND dialog::create_modeless(HINSTANCE instance_handle,
    const DLGTEMPLATE                 *dialog_template,
    HWND                               hwnd_parent,
    DLGPROC                            dialog_func,
    LPARAM                             init_param) {
    HWND result = CreateDialogIndirectParamW(
        instance_handle, dialog_template, hwnd_parent, dialog_func, init_param);
    if (!result) {
        error_code = GetLastError();
        return nullptr;
    }
    rwlock.write_lock();
    dialog_modeless_handle.push_back(result);
    rwlock.write_unlock();
    return result;
}

bool dialog::destroy(HWND hwnd_dialog, INT_PTR result) {
    if (!EndDialog(hwnd_dialog, result)) {
        error_code = GetLastError();
        return false;
    }
    return true;
}

bool dialog::destroy_modeless(HWND hwnd_dialog) {
    if (!hwnd_dialog || !IsWindow(hwnd_dialog)) {
        return false;
    }
    rwlock.write_lock();
    const auto it = std::find(dialog_modeless_handle.begin(),
        dialog_modeless_handle.end(), hwnd_dialog);
    if (it != dialog_modeless_handle.end()) {
        *it = nullptr;
    }
    rwlock.write_unlock();
    if (!DestroyWindow(hwnd_dialog)) {
        error_code = GetLastError();
        return false;
    }
    return true;
}

bool dialog::set_button_state(HWND hwnd_dialog,
    int32_t                        button_id,
    ButtonState                    state) {
    if (!CheckDlgButton(hwnd_dialog, button_id, static_cast<uint32_t>(state))) {
        error_code = GetLastError();
        return false;
    }
    return true;
}

bool dialog::set_radio_state(HWND hwnd_dialog,
    int32_t                       first_button_id,
    int32_t                       last_button_id,
    int32_t                       check_button_id) {
    if (!CheckRadioButton(
            hwnd_dialog, first_button_id, last_button_id, check_button_id)) {
        error_code = GetLastError();
        return false;
    }
    return true;
}

LRESULT dialog::default_proc(HWND hwnd_dialog,
    uint32_t                      msg,
    WPARAM                        wparam,
    LPARAM                        lparam) {
    return DefDlgProcW(hwnd_dialog, msg, wparam, lparam);
}

int32_t dialog::fill_listbox(HWND hwnd_dialog,
    char                         *path_spec,
    int32_t                       listbox_id,
    int32_t                       static_id,
    FileType                      file_type) {
    int32_t result = DlgDirListA(hwnd_dialog, path_spec, listbox_id, static_id,
        static_cast<uint32_t>(file_type));
    if (!result) {
        error_code = GetLastError();
    }
    return result;
}

int32_t dialog::fill_listbox(HWND hwnd_dialog,
    wchar_t                      *path_spec,
    int32_t                       listbox_id,
    int32_t                       static_id,
    FileType                      file_type) {
    int32_t result = DlgDirListW(hwnd_dialog, path_spec, listbox_id, static_id,
        static_cast<uint32_t>(file_type));
    if (!result) {
        error_code = GetLastError();
    }
    return result;
}

int32_t dialog::fill_combobox(HWND hwnd_dialog,
    char                          *path_spec,
    int32_t                        combobox_id,
    int32_t                        static_id,
    FileType                       file_type) {
    int32_t result = DlgDirListComboBoxA(hwnd_dialog, path_spec, combobox_id,
        static_id, static_cast<uint32_t>(file_type));
    if (!result) {
        error_code = GetLastError();
    }
    return result;
}

int32_t dialog::fill_combobox(HWND hwnd_dialog,
    wchar_t                       *path_spec,
    int32_t                        combobox_id,
    int32_t                        static_id,
    FileType                       file_type) {
    int32_t result = DlgDirListComboBoxW(hwnd_dialog, path_spec, combobox_id,
        static_id, static_cast<uint32_t>(file_type));
    if (!result) {
        error_code = GetLastError();
    }
    return result;
}

bool dialog::get_select_combobox(HWND hwnd_dialog,
    std::string                      &path,
    int32_t                           combobox_id) {
    if (!DlgDirSelectComboBoxExA(hwnd_dialog, path.data(),
            static_cast<int>(path.size()), combobox_id)) {
        error_code = GetLastError();
        return false;
    }
    return true;
}

bool dialog::get_select_combobox(HWND hwnd_dialog,
    std::wstring                     &path,
    int32_t                           combobox_id) {
    if (!DlgDirSelectComboBoxExW(hwnd_dialog, path.data(),
            static_cast<int>(path.size()), combobox_id)) {
        error_code = GetLastError();
        return false;
    }
    return true;
}

bool dialog::get_select_listbox(HWND hwnd_dialog,
    std::string                     &path,
    int32_t                          listbox_id) {
    if (!DlgDirSelectExA(hwnd_dialog, path.data(),
            static_cast<int>(path.size()), listbox_id)) {
        error_code = GetLastError();
        return false;
    }
    return true;
}

bool dialog::get_select_listbox(HWND hwnd_dialog,
    std::wstring                    &path,
    int32_t                          listbox_id) {
    if (!DlgDirSelectExW(hwnd_dialog, path.data(),
            static_cast<int>(path.size()), listbox_id)) {
        error_code = GetLastError();
        return false;
    }
    return true;
}

int32_t dialog::get_item_id(HWND hwnd_item) {
    int32_t result = GetDlgCtrlID(hwnd_item);
    if (!result) {
        error_code = GetLastError();
    }
    return result;
}

HWND dialog::get_item_handle(HWND hwnd_dialog, int32_t item_id) {
    HWND result = GetDlgItem(hwnd_dialog, item_id);
    if (!result) {
        error_code = GetLastError();
    }
    return result;
}

bool dialog::get_item_int(HWND hwnd_dialog,
    int32_t                    item_id,
    uint32_t                  *value,
    bool                       is_signed) {
    if (!value) {
        return false;
    }
    int32_t is_translated = 0;
    *value                = GetDlgItemInt(
        hwnd_dialog, item_id, &is_translated, is_signed ? TRUE : FALSE);
    if (!is_translated) {
        error_code = GetLastError();
        return false;
    }
    return true;
}

bool dialog::set_item_int(HWND hwnd_dialog,
    int32_t                    item_id,
    uint32_t                   value,
    bool                       is_signed) {
    if (!SetDlgItemInt(hwnd_dialog, item_id, value, is_signed ? TRUE : FALSE)) {
        error_code = GetLastError();
        return false;
    }
    return true;
}

uint32_t
dialog::get_item_text(HWND hwnd_dialog, int32_t item_id, std::string &text) {
    uint32_t result = GetDlgItemTextA(
        hwnd_dialog, item_id, text.data(), static_cast<int>(text.size()));
    if (!result) {
        error_code = GetLastError();
    }
    return result;
}

uint32_t
dialog::get_item_text(HWND hwnd_dialog, int32_t item_id, std::wstring &text) {
    uint32_t result = GetDlgItemTextW(
        hwnd_dialog, item_id, text.data(), static_cast<int>(text.size()));
    if (!result) {
        error_code = GetLastError();
    }
    return result;
}

bool dialog::set_item_text(HWND hwnd_dialog,
    int32_t                     item_id,
    const char                 *text) {
    if (!SetDlgItemTextA(hwnd_dialog, item_id, text)) {
        error_code = GetLastError();
        return false;
    }
    return true;
}

bool dialog::set_item_text(HWND hwnd_dialog,
    int32_t                     item_id,
    const wchar_t              *text) {
    if (!SetDlgItemTextW(hwnd_dialog, item_id, text)) {
        error_code = GetLastError();
        return false;
    }
    return true;
}

HWND dialog::next_group_item(HWND hwnd_dialog,
    HWND                          hwnd_item,
    bool                          search_upward) {
    HWND result = GetNextDlgGroupItem(
        hwnd_dialog, hwnd_item, search_upward ? TRUE : FALSE);
    if (!result) {
        error_code = GetLastError();
    }
    return result;
}

HWND dialog::next_tab_item(HWND hwnd_dialog,
    HWND                        hwnd_item,
    bool                        search_upward) {
    HWND result =
        GetNextDlgTabItem(hwnd_dialog, hwnd_item, search_upward ? TRUE : FALSE);
    if (!result) {
        error_code = GetLastError();
    }
    return result;
}

ButtonState dialog::is_button_checked(HWND hwnd_dialog, int32_t button_id) {
    return static_cast<ButtonState>(IsDlgButtonChecked(hwnd_dialog, button_id));
}

ItemDpiBehavior dialog::get_item_dpi_behavior(HWND hwnd_dialog) {
    DIALOG_CONTROL_DPI_CHANGE_BEHAVIORS result =
        GetDialogControlDpiChangeBehavior(hwnd_dialog);
    if (!result) {
        error_code = GetLastError();
    }
    return static_cast<ItemDpiBehavior>(result);
}

bool dialog::set_item_dpi_behavior(HWND hwnd_dialog,
    ItemDpiBehavior                     mask,
    ItemDpiBehavior                     values) {
    if (!SetDialogControlDpiChangeBehavior(hwnd_dialog,
            static_cast<DIALOG_CONTROL_DPI_CHANGE_BEHAVIORS>(mask),
            static_cast<DIALOG_CONTROL_DPI_CHANGE_BEHAVIORS>(values))) {
        error_code = GetLastError();
        return false;
    }
    return true;
}

DialogDpiBehavior dialog::get_dpi_behavior(HWND hwnd_dialog) {
    DIALOG_DPI_CHANGE_BEHAVIORS result =
        GetDialogDpiChangeBehavior(hwnd_dialog);
    if (!result) {
        error_code = GetLastError();
    }
    return static_cast<DialogDpiBehavior>(result);
}

bool dialog::set_dpi_behavior(HWND hwnd_dialog,
    DialogDpiBehavior              mask,
    DialogDpiBehavior              values) {
    if (!SetDialogDpiChangeBehavior(hwnd_dialog,
            static_cast<DIALOG_DPI_CHANGE_BEHAVIORS>(mask),
            static_cast<DIALOG_DPI_CHANGE_BEHAVIORS>(values))) {
        error_code = GetLastError();
        return false;
    }
    return true;
}

long dialog::get_base_units() {
    return GetDialogBaseUnits();
}

bool dialog::base_units_to_screen_point(HWND hwnd_dialog, RECT *rect) {
    if (!MapDialogRect(hwnd_dialog, rect)) {
        error_code = GetLastError();
        return false;
    }
    return true;
}

uint32_t dialog::err_code() const {
    return error_code;
}

std::string dialog::err_string() const {
    std::string result = helper::convert::err_string(error_code);
    return result;
}

std::wstring dialog::err_wstring() const {
    std::wstring result = helper::convert::err_wstring(error_code);
    return result;
}
} // namespace YanLib::ui
