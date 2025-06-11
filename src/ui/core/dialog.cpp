/* clang-format off */
/*
 * @file dialog.cpp
 * @date 2025-04-30
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
#include "dialog.h"
#include "helper/convert.h"

namespace YanLib::ui::core {
    dialog::~dialog() {
        for (auto &handle : dialog_modeless_handle) {
            if (handle && IsWindow(handle)) {
                DestroyWindow(handle);
                handle = nullptr;
            }
        }
        dialog_modeless_handle.clear();
    }

    intptr_t dialog::create(HINSTANCE instance_handle,
                            const char *template_name,
                            HWND parent_window_handle,
                            DLGPROC dialog_func) {
        const intptr_t result =
                DialogBoxParamA(instance_handle, template_name,
                                parent_window_handle, dialog_func, 0L);
        if (result == -1) {
            error_code = GetLastError();
        }
        return result;
    }

    intptr_t dialog::create(HINSTANCE instance_handle,
                            const wchar_t *template_name,
                            HWND parent_window_handle,
                            DLGPROC dialog_func) {
        const intptr_t result =
                DialogBoxParamW(instance_handle, template_name,
                                parent_window_handle, dialog_func, 0L);
        if (result == -1) {
            error_code = GetLastError();
        }
        return result;
    }

    intptr_t dialog::create(HINSTANCE instance_handle,
                            const char *template_name,
                            HWND parent_window_handle,
                            DLGPROC dialog_func,
                            LPARAM init_param) {
        const intptr_t result =
                DialogBoxParamA(instance_handle, template_name,
                                parent_window_handle, dialog_func, init_param);
        if (result == -1) {
            error_code = GetLastError();
        }
        return result;
    }

    intptr_t dialog::create(HINSTANCE instance_handle,
                            const wchar_t *template_name,
                            HWND parent_window_handle,
                            DLGPROC dialog_func,
                            LPARAM init_param) {
        const intptr_t result =
                DialogBoxParamW(instance_handle, template_name,
                                parent_window_handle, dialog_func, init_param);
        if (result == -1) {
            error_code = GetLastError();
        }
        return result;
    }

    intptr_t dialog::create(HINSTANCE instance_handle,
                            const DLGTEMPLATE *dialog_template,
                            HWND parent_window_handle,
                            DLGPROC dialog_func) {
        const intptr_t result =
                DialogBoxIndirectParamW(instance_handle, dialog_template,
                                        parent_window_handle, dialog_func, 0L);
        if (result == -1) {
            error_code = GetLastError();
        }
        return result;
    }

    intptr_t dialog::create(HINSTANCE instance_handle,
                            const DLGTEMPLATE *dialog_template,
                            HWND parent_window_handle,
                            DLGPROC dialog_func,
                            LPARAM init_param) {
        const intptr_t result =
                DialogBoxIndirectParamW(instance_handle, dialog_template,
                                        parent_window_handle, dialog_func,
                                        init_param);
        if (result == -1) {
            error_code = GetLastError();
        }
        return result;
    }

    HWND dialog::create_modeless(HINSTANCE instance_handle,
                                 const wchar_t *template_name,
                                 HWND parent_window_handle,
                                 DLGPROC dialog_func) {
        HWND result = CreateDialogParamW(instance_handle, template_name,
                                         parent_window_handle, dialog_func, 0L);
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
                                 const wchar_t *template_name,
                                 HWND parent_window_handle,
                                 DLGPROC dialog_func,
                                 LPARAM init_param) {
        HWND result = CreateDialogParamW(instance_handle, template_name,
                                         parent_window_handle, dialog_func,
                                         init_param);
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
                                 const DLGTEMPLATE *dialog_template,
                                 HWND parent_window_handle,
                                 DLGPROC dialog_func) {
        HWND result =
                CreateDialogIndirectParamW(instance_handle, dialog_template,
                                           parent_window_handle, dialog_func,
                                           0L);
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
                                 const DLGTEMPLATE *dialog_template,
                                 HWND parent_window_handle,
                                 DLGPROC dialog_func,
                                 LPARAM init_param) {
        HWND result =
                CreateDialogIndirectParamW(instance_handle, dialog_template,
                                           parent_window_handle, dialog_func,
                                           init_param);
        if (!result) {
            error_code = GetLastError();
            return nullptr;
        }
        rwlock.write_lock();
        dialog_modeless_handle.push_back(result);
        rwlock.write_unlock();
        return result;
    }

    bool dialog::destroy(HWND dialog_handle, intptr_t result) {
        if (!EndDialog(dialog_handle, result)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool dialog::destroy_modeless(HWND dialog_handle) {
        if (!dialog_handle || !IsWindow(dialog_handle)) {
            return false;
        }
        rwlock.write_lock();
        const auto it = std::find(dialog_modeless_handle.begin(),
                                  dialog_modeless_handle.end(), dialog_handle);
        if (it != dialog_modeless_handle.end()) {
            *it = nullptr;
        }
        rwlock.write_unlock();
        if (!DestroyWindow(dialog_handle)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool dialog::set_button_state(HWND dialog_handle,
                                  int32_t button_id,
                                  ButtonState state) {
        if (!CheckDlgButton(dialog_handle, button_id,
                            static_cast<uint32_t>(state))) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool dialog::set_radio_state(HWND dialog_handle,
                                 int32_t first_button_id,
                                 int32_t last_button_id,
                                 int32_t check_button_id) {
        if (!CheckRadioButton(dialog_handle, first_button_id, last_button_id,
                              check_button_id)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    LRESULT dialog::default_proc(HWND dialog_handle,
                                 uint32_t msg,
                                 WPARAM wparam,
                                 LPARAM lparam) {
        return DefDlgProcW(dialog_handle, msg, wparam, lparam);
    }

    int32_t dialog::fill_list_box(HWND dialog_handle,
                                  char *path_spec,
                                  int32_t list_box_id,
                                  int32_t static_id,
                                  FileType file_type) {
        const int32_t result =
                DlgDirListA(dialog_handle, path_spec, list_box_id, static_id,
                            static_cast<uint32_t>(file_type));
        if (!result) {
            error_code = GetLastError();
        }
        return result;
    }

    int32_t dialog::fill_list_box(HWND dialog_handle,
                                  wchar_t *path_spec,
                                  int32_t list_box_id,
                                  int32_t static_id,
                                  FileType file_type) {
        const int32_t result =
                DlgDirListW(dialog_handle, path_spec, list_box_id, static_id,
                            static_cast<uint32_t>(file_type));
        if (!result) {
            error_code = GetLastError();
        }
        return result;
    }

    int32_t dialog::fill_combo_box(HWND dialog_handle,
                                   char *path_spec,
                                   int32_t combo_box_id,
                                   int32_t static_id,
                                   FileType file_type) {
        const int32_t result =
                DlgDirListComboBoxA(dialog_handle, path_spec, combo_box_id,
                                    static_id,
                                    static_cast<uint32_t>(file_type));
        if (!result) {
            error_code = GetLastError();
        }
        return result;
    }

    int32_t dialog::fill_combo_box(HWND dialog_handle,
                                   wchar_t *path_spec,
                                   int32_t combo_box_id,
                                   int32_t static_id,
                                   FileType file_type) {
        const int32_t result =
                DlgDirListComboBoxW(dialog_handle, path_spec, combo_box_id,
                                    static_id,
                                    static_cast<uint32_t>(file_type));
        if (!result) {
            error_code = GetLastError();
        }
        return result;
    }

    bool dialog::get_select_combo_box(HWND dialog_handle,
                                      std::string &path,
                                      int32_t combo_box_id) {
        if (!DlgDirSelectComboBoxExA(dialog_handle, path.data(),
                                     static_cast<int32_t>(path.size()),
                                     combo_box_id)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool dialog::get_select_combo_box(HWND dialog_handle,
                                      std::wstring &path,
                                      int32_t combo_box_id) {
        if (!DlgDirSelectComboBoxExW(dialog_handle, path.data(),
                                     static_cast<int32_t>(path.size()),
                                     combo_box_id)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool dialog::get_select_list_box(HWND dialog_handle,
                                     std::string &path,
                                     int32_t list_box_id) {
        if (!DlgDirSelectExA(dialog_handle, path.data(),
                             static_cast<int32_t>(path.size()), list_box_id)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool dialog::get_select_list_box(HWND dialog_handle,
                                     std::wstring &path,
                                     int32_t list_box_id) {
        if (!DlgDirSelectExW(dialog_handle, path.data(),
                             static_cast<int32_t>(path.size()), list_box_id)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    int32_t dialog::get_item_id(HWND item_handle) {
        const int32_t result = GetDlgCtrlID(item_handle);
        if (!result) {
            error_code = GetLastError();
        }
        return result;
    }

    HWND dialog::get_item_handle(HWND dialog_handle, int32_t item_id) {
        HWND result = GetDlgItem(dialog_handle, item_id);
        if (!result) {
            error_code = GetLastError();
        }
        return result;
    }

    bool dialog::get_item_int(HWND dialog_handle,
                              int32_t item_id,
                              uint32_t *value,
                              bool is_signed) {
        if (!value) {
            return false;
        }
        int32_t is_translated = 0;
        *value = GetDlgItemInt(dialog_handle, item_id, &is_translated,
                               is_signed ? TRUE : FALSE);
        if (!is_translated) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool dialog::set_item_int(HWND dialog_handle,
                              int32_t item_id,
                              uint32_t value,
                              bool is_signed) {
        if (!SetDlgItemInt(dialog_handle, item_id, value,
                           is_signed ? TRUE : FALSE)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    uint32_t dialog::get_item_text(HWND dialog_handle,
                                   int32_t item_id,
                                   std::string &text) {
        const uint32_t result =
                GetDlgItemTextA(dialog_handle, item_id, text.data(),
                                static_cast<int32_t>(text.size()));
        if (!result) {
            error_code = GetLastError();
        }
        return result;
    }

    uint32_t dialog::get_item_text(HWND dialog_handle,
                                   int32_t item_id,
                                   std::wstring &text) {
        const uint32_t result =
                GetDlgItemTextW(dialog_handle, item_id, text.data(),
                                static_cast<int32_t>(text.size()));
        if (!result) {
            error_code = GetLastError();
        }
        return result;
    }

    bool dialog::set_item_text(HWND dialog_handle,
                               int32_t item_id,
                               const char *text) {
        if (!SetDlgItemTextA(dialog_handle, item_id, text)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool dialog::set_item_text(HWND dialog_handle,
                               int32_t item_id,
                               const wchar_t *text) {
        if (!SetDlgItemTextW(dialog_handle, item_id, text)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    HWND dialog::next_group_item(HWND dialog_handle,
                                 HWND item_handle,
                                 bool search_upward) {
        HWND result = GetNextDlgGroupItem(dialog_handle, item_handle,
                                          search_upward ? TRUE : FALSE);
        if (!result) {
            error_code = GetLastError();
        }
        return result;
    }

    HWND dialog::next_tab_item(HWND dialog_handle,
                               HWND item_handle,
                               bool search_upward) {
        HWND result = GetNextDlgTabItem(dialog_handle, item_handle,
                                        search_upward ? TRUE : FALSE);
        if (!result) {
            error_code = GetLastError();
        }
        return result;
    }

    ButtonState dialog::is_button_checked(HWND dialog_handle,
                                          int32_t button_id) {
        return static_cast<ButtonState>(
                IsDlgButtonChecked(dialog_handle, button_id));
    }

    ItemDpiBehavior dialog::get_item_dpi_behavior(HWND dialog_handle) {
        DIALOG_CONTROL_DPI_CHANGE_BEHAVIORS result =
                GetDialogControlDpiChangeBehavior(dialog_handle);
        if (!result) {
            error_code = GetLastError();
        }
        return static_cast<ItemDpiBehavior>(result);
    }

    bool dialog::set_item_dpi_behavior(HWND dialog_handle,
                                       ItemDpiBehavior mask,
                                       ItemDpiBehavior values) {
        if (!SetDialogControlDpiChangeBehavior(
                    dialog_handle,
                    static_cast<DIALOG_CONTROL_DPI_CHANGE_BEHAVIORS>(mask),
                    static_cast<DIALOG_CONTROL_DPI_CHANGE_BEHAVIORS>(values))) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    DialogDpiBehavior dialog::get_dpi_behavior(HWND dialog_handle) {
        DIALOG_DPI_CHANGE_BEHAVIORS result =
                GetDialogDpiChangeBehavior(dialog_handle);
        if (!result) {
            error_code = GetLastError();
        }
        return static_cast<DialogDpiBehavior>(result);
    }

    bool dialog::set_dpi_behavior(HWND dialog_handle,
                                  DialogDpiBehavior mask,
                                  DialogDpiBehavior values) {
        if (!SetDialogDpiChangeBehavior(
                    dialog_handle,
                    static_cast<DIALOG_DPI_CHANGE_BEHAVIORS>(mask),
                    static_cast<DIALOG_DPI_CHANGE_BEHAVIORS>(values))) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    int32_t dialog::get_base_units() {
        return GetDialogBaseUnits();
    }

    bool dialog::base_units_to_screen_point(HWND dialog_handle, RECT *rect) {
        if (!MapDialogRect(dialog_handle, rect)) {
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
} // namespace YanLib::ui::core
