//
// Created by forkernel on 2025/4/30.
//

#include "dialog.h"
#include "helper/convert.h"

namespace YanLib::ui {
    INT_PTR dialog::create_dialog(HINSTANCE instance_handle,
                                  const wchar_t *template_name,
                                  HWND hwnd_parent,
                                  DLGPROC dialog_func) {
        INT_PTR result = DialogBoxParamW(instance_handle,
                                         template_name,
                                         hwnd_parent,
                                         dialog_func,
                                         0L);
        if (result == -1) {
            error_code = GetLastError();
        }
        return result;
    }

    INT_PTR dialog::create_dialog(HINSTANCE instance_handle,
                                  const wchar_t *template_name,
                                  HWND hwnd_parent,
                                  DLGPROC dialog_func,
                                  LPARAM init_param) {
        INT_PTR result = DialogBoxParamW(instance_handle,
                                         template_name,
                                         hwnd_parent,
                                         dialog_func,
                                         init_param);
        if (result == -1) {
            error_code = GetLastError();
        }
        return result;
    }

    INT_PTR dialog::create_dialog_indirect(HINSTANCE instance_handle,
                                           const DLGTEMPLATE* dialog_template,
                                           HWND hwnd_parent,
                                           DLGPROC dialog_func) {
        INT_PTR result = DialogBoxIndirectParamW(instance_handle,
                                                 dialog_template,
                                                 hwnd_parent,
                                                 dialog_func,
                                                 0L);
        if (result == -1) {
            error_code = GetLastError();
        }
        return result;
    }

    INT_PTR dialog::create_dialog_indirect(HINSTANCE instance_handle,
                                           const DLGTEMPLATE* dialog_template,
                                           HWND hwnd_parent,
                                           DLGPROC dialog_func,
                                           LPARAM init_param) {
        INT_PTR result = DialogBoxIndirectParamW(instance_handle,
                                                 dialog_template,
                                                 hwnd_parent,
                                                 dialog_func,
                                                 init_param);
        if (result == -1) {
            error_code = GetLastError();
        }
        return result;
    }

    HWND dialog::create_dialog_modeless(HINSTANCE instance_handle,
                                        const wchar_t *template_name,
                                        HWND hwnd_parent,
                                        DLGPROC dialog_func) {
        HWND result = CreateDialogParamW(instance_handle,
                                         template_name,
                                         hwnd_parent,
                                         dialog_func,
                                         0L);
        if (!result) {
            error_code = GetLastError();
        }
        return result;
    }

    HWND dialog::create_dialog_modeless(HINSTANCE instance_handle,
                                        const wchar_t *template_name,
                                        HWND hwnd_parent,
                                        DLGPROC dialog_func,
                                        LPARAM init_param) {
        HWND result = CreateDialogParamW(instance_handle,
                                         template_name,
                                         hwnd_parent,
                                         dialog_func,
                                         init_param);
        if (!result) {
            error_code = GetLastError();
        }
        return result;
    }

    HWND dialog::create_dialog_indirect_modeless(HINSTANCE instance_handle,
                                                 const DLGTEMPLATE* dialog_template,
                                                 HWND hwnd_parent,
                                                 DLGPROC dialog_func) {
        HWND result = CreateDialogIndirectParamW(instance_handle,
                                                 dialog_template,
                                                 hwnd_parent,
                                                 dialog_func,
                                                 0L);
        if (!result) {
            error_code = GetLastError();
        }
        return result;
    }

    HWND dialog::create_dialog_indirect_modeless(HINSTANCE instance_handle,
                                                 const DLGTEMPLATE* dialog_template,
                                                 HWND hwnd_parent,
                                                 DLGPROC dialog_func,
                                                 LPARAM init_param) {
        HWND result = CreateDialogIndirectParamW(instance_handle,
                                                 dialog_template,
                                                 hwnd_parent,
                                                 dialog_func,
                                                 init_param);
        if (!result) {
            error_code = GetLastError();
        }
        return result;
    }

    bool dialog::end_dialog(HWND hwnd_dialog, INT_PTR result) {
        if (!EndDialog(hwnd_dialog, result)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool dialog::check_dialog_button(HWND hwnd_dialog,
                                     int id_button,
                                     unsigned int check) {
        if (!CheckDlgButton(hwnd_dialog,
                            id_button,
                            check)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    LRESULT dialog::default_dialog_proc(HWND hwnd_dialog,
                                        unsigned int msg,
                                        WPARAM w_param,
                                        LPARAM l_param) {
        return DefDlgProcW(hwnd_dialog,
                           msg,
                           w_param,
                           l_param);
    }

    int dialog::dialog_dir_list(HWND hwnd_dialog,
                                wchar_t *path_spec,
                                int id_listbox,
                                int id_static_path,
                                unsigned int file_type) {
        int result = DlgDirListW(hwnd_dialog,
                                 path_spec,
                                 id_listbox,
                                 id_static_path,
                                 file_type);
        if (!result) {
            error_code = GetLastError();
        }
        return result;
    }

    int dialog::dialog_dir_list_combobox(HWND hwnd_dialog,
                                         wchar_t *path_spec,
                                         int id_combobox,
                                         int id_static_path,
                                         unsigned int filetype) {
        int result = DlgDirListComboBoxW(hwnd_dialog,
                                         path_spec,
                                         id_combobox,
                                         id_static_path,
                                         filetype);
        if (!result) {
            error_code = GetLastError();
        }
        return result;
    }

    bool dialog::dialog_dir_select_combobox(HWND hwnd_dialog,
                                            wchar_t *text,
                                            int cch_size,
                                            int id_combobox) {
        if (!DlgDirSelectComboBoxExW(hwnd_dialog,
                                     text,
                                     cch_size,
                                     id_combobox)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool dialog::dialog_dir_select(HWND hwnd_dialog,
                                   wchar_t *text,
                                   int cch_size,
                                   int id_listbox) {
        if (!DlgDirSelectExW(hwnd_dialog,
                             text,
                             cch_size,
                             id_listbox)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    int dialog::get_dialog_ctrl_id(HWND hwnd_ctrl) {
        int result = GetDlgCtrlID(hwnd_ctrl);
        if (!result) {
            error_code = GetLastError();
        }
        return result;
    }

    HWND dialog::get_dialog_item(HWND hwnd_dialog, int id_dialog_item) {
        HWND result = GetDlgItem(hwnd_dialog, id_dialog_item);
        if (!result) {
            error_code = GetLastError();
        }
        return result;
    }

    std::pair<unsigned int, bool> dialog::get_dialog_item_int(HWND hwnd_dialog,
                                                      int id_dialog_item,
                                                      bool is_signed) {
        int is_translated = 0;
        unsigned int result = GetDlgItemInt(hwnd_dialog,
                                    id_dialog_item,
                                    &is_translated,
                                    is_signed ? TRUE : FALSE);
        if (!is_translated) {
            error_code = GetLastError();
        }
        return std::make_pair(result, is_translated);
    }

    bool dialog::set_dialog_item_int(HWND hwnd_dialog,
                                     int id_dialog_item,
                                     unsigned int value,
                                     bool is_signed) {
        if (!SetDlgItemInt(hwnd_dialog,
                           id_dialog_item,
                           value,
                           is_signed ? TRUE : FALSE)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    unsigned int dialog::get_dialog_item_text(HWND hwnd_dialog,
                                      int id_dialog_item,
                                      wchar_t *text,
                                      int cch_max) {
        unsigned int result = GetDlgItemTextW(hwnd_dialog,
                                      id_dialog_item,
                                      text,
                                      cch_max);
        if (!result) {
            error_code = GetLastError();
        }
        return result;
    }

    bool dialog::set_dialog_item_text(HWND hwnd_dialog,
                                      int id_dialog_item,
                                      const wchar_t *text) {
        if (!SetDlgItemTextW(hwnd_dialog,
                             id_dialog_item,
                             text)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    HWND dialog::get_next_dialog_group_item(HWND hwnd_dialog,
                                            HWND hwnd_ctrl,
                                            bool previous) {
        HWND result = GetNextDlgGroupItem(hwnd_dialog,
                                          hwnd_ctrl,
                                          previous);
        if (!result) {
            error_code = GetLastError();
        }
        return result;
    }

    HWND dialog::get_next_dialog_tab_item(HWND hwnd_dialog,
                                          HWND hwnd_ctrl,
                                          bool previous) {
        HWND result = GetNextDlgTabItem(hwnd_dialog,
                                        hwnd_ctrl,
                                        previous);
        if (!result) {
            error_code = GetLastError();
        }
        return result;
    }

    unsigned int dialog::is_dialog_button_checked(HWND hwnd_dialog, int id_button) {
        return IsDlgButtonChecked(hwnd_dialog, id_button);
    }

    long dialog::get_dialog_base_units() {
        return GetDialogBaseUnits();
    }

    DIALOG_CONTROL_DPI_CHANGE_BEHAVIORS
    dialog::get_dialog_control_dpi_change_behavior(HWND hwnd) {
        DIALOG_CONTROL_DPI_CHANGE_BEHAVIORS result =
                GetDialogControlDpiChangeBehavior(hwnd);
        if (!result) {
            error_code = GetLastError();
        }
        return result;
    }

    bool dialog::set_dialog_control_dpi_change_behavior(
        HWND hwnd_dialog,
        DIALOG_CONTROL_DPI_CHANGE_BEHAVIORS mask,
        DIALOG_CONTROL_DPI_CHANGE_BEHAVIORS values) {
        if (!SetDialogControlDpiChangeBehavior(hwnd_dialog,
                                               mask,
                                               values)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    DIALOG_DPI_CHANGE_BEHAVIORS
    dialog::get_dialog_dpi_change_behavior(HWND hwnd_dialog) {
        DIALOG_DPI_CHANGE_BEHAVIORS result =
                GetDialogDpiChangeBehavior(hwnd_dialog);
        if (!result) {
            error_code = GetLastError();
        }
        return result;
    }

    bool dialog::set_dialog_dpi_change_behavior(
        HWND hwnd_dialog,
        DIALOG_DPI_CHANGE_BEHAVIORS mask,
        DIALOG_DPI_CHANGE_BEHAVIORS values) {
        if (!SetDialogDpiChangeBehavior(hwnd_dialog,
                                        mask,
                                        values)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool dialog::map_dialog_rect(HWND hwnd_dialog, RECT* rect) {
        if (!MapDialogRect(hwnd_dialog, rect)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    unsigned long dialog::err_code() const {
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
}
