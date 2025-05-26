//
// Created by forkernel on 2025/5/24.
//

#include "combobox.h"
#include <windowsx.h>

namespace YanLib::components {
    HWND combobox::create(uintptr_t combobox_id,
                          HWND parent_window_handle,
                          LPARAM lparam,
                          int32_t x,
                          int32_t y,
                          int32_t width,
                          int32_t height,
                          ComboBoxStyle style,
                          WindowStyle window_style) {
        HWND result = CreateWindowExW(0L, L"ComboBox", nullptr,
                                      static_cast<uint32_t>(window_style) |
                                              static_cast<uint32_t>(style),
                                      x, y, width, height, parent_window_handle,
                                      reinterpret_cast<HMENU>(combobox_id),
                                      reinterpret_cast<CREATESTRUCT *>(lparam)
                                              ->hInstance,
                                      nullptr);
        if (!result) {
            error_code = GetLastError();
        }
        return result;
    }

    bool combobox::enable(HWND combobox_handle) {
        return ComboBox_Enable(combobox_handle, TRUE);
    }

    bool combobox::disable(HWND combobox_handle) {
        return ComboBox_Enable(combobox_handle, FALSE);
    }

    int32_t combobox::fill(HWND combobox_handle,
                           char *path_spec,
                           FileType type,
                           helper::CodePage code_page) {
        int32_t result =
                ComboBox_Dir(combobox_handle, static_cast<uint32_t>(type),
                             helper::convert::str_to_wstr(path_spec, code_page)
                                     .data());
        if (result == CB_ERRSPACE) {
            error_code = ERROR_OUTOFMEMORY;
        }
        else if (result == CB_ERR) {
            error_code = GetLastError();
        }
        return result;
    }

    int32_t
    combobox::fill(HWND combobox_handle, wchar_t *path_spec, FileType type) {
        int32_t result = ComboBox_Dir(combobox_handle,
                                      static_cast<uint32_t>(type), path_spec);
        if (result == CB_ERRSPACE) {
            error_code = ERROR_OUTOFMEMORY;
        }
        else if (result == CB_ERR) {
            error_code = GetLastError();
        }
        return result;
    }

    int32_t combobox::add_text(HWND combobox_handle,
                               std::string &text,
                               helper::CodePage code_page) {
        int32_t result =
                ComboBox_AddString(combobox_handle,
                                   helper::convert::str_to_wstr(text, code_page)
                                           .data());
        if (result == CB_ERRSPACE) {
            error_code = ERROR_OUTOFMEMORY;
        }
        else if (result == CB_ERR) {
            error_code = GetLastError();
        }
        return result;
    }

    int32_t combobox::add_text(HWND combobox_handle, std::wstring &text) {
        int32_t result = ComboBox_AddString(combobox_handle, text.data());
        if (result == CB_ERRSPACE) {
            error_code = ERROR_OUTOFMEMORY;
        }
        else if (result == CB_ERR) {
            error_code = GetLastError();
        }
        return result;
    }

    int32_t combobox::insert_text(HWND combobox_handle,
                                  std::string &text,
                                  int32_t index,
                                  helper::CodePage code_page) {
        int32_t result = ComboBox_InsertString(
                combobox_handle, index,
                helper::convert::str_to_wstr(text, code_page).data());
        if (result == CB_ERRSPACE) {
            error_code = ERROR_OUTOFMEMORY;
        }
        else if (result == CB_ERR) {
            error_code = GetLastError();
        }
        return result;
    }

    int32_t combobox::insert_text(HWND combobox_handle,
                                  std::wstring &text,
                                  int32_t index) {
        int32_t result =
                ComboBox_InsertString(combobox_handle, index, text.data());
        if (result == CB_ERRSPACE) {
            error_code = ERROR_OUTOFMEMORY;
        }
        else if (result == CB_ERR) {
            error_code = GetLastError();
        }
        return result;
    }

    int32_t combobox::select_text(HWND combobox_handle,
                                  std::string &text,
                                  int32_t index,
                                  helper::CodePage code_page) {
        int32_t result = ComboBox_SelectString(
                combobox_handle, index,
                helper::convert::str_to_wstr(text, code_page).data());
        if (result == CB_ERR) {
            error_code = GetLastError();
        }
        return result;
    }

    int32_t combobox::select_text(HWND combobox_handle,
                                  std::wstring &text,
                                  int32_t index) {
        int32_t result =
                ComboBox_SelectString(combobox_handle, index, text.data());
        if (result == CB_ERR) {
            error_code = GetLastError();
        }
        return result;
    }

    int32_t combobox::find_text(HWND combobox_handle,
                                std::string &text,
                                int32_t index,
                                helper::CodePage code_page) {
        int32_t result = ComboBox_FindString(
                combobox_handle, index,
                helper::convert::str_to_wstr(text, code_page).data());
        if (result == CB_ERR) {
            error_code = GetLastError();
        }
        return result;
    }

    int32_t combobox::find_text(HWND combobox_handle,
                                std::wstring &text,
                                int32_t index) {
        int32_t result =
                ComboBox_FindString(combobox_handle, index, text.data());
        if (result == CB_ERR) {
            error_code = GetLastError();
        }
        return result;
    }

    int32_t combobox::find_exact_text(HWND combobox_handle,
                                      std::string &text,
                                      int32_t index,
                                      helper::CodePage code_page) {
        int32_t result = ComboBox_FindStringExact(
                combobox_handle, index,
                helper::convert::str_to_wstr(text, code_page).data());
        if (result == CB_ERR) {
            error_code = GetLastError();
        }
        return result;
    }

    int32_t combobox::find_exact_text(HWND combobox_handle,
                                      std::wstring &text,
                                      int32_t index) {
        int32_t result =
                ComboBox_FindStringExact(combobox_handle, index, text.data());
        if (result == CB_ERR) {
            error_code = GetLastError();
        }
        return result;
    }

    int32_t combobox::delete_item(HWND combobox_handle, int32_t index) {
        int32_t result = ComboBox_DeleteString(combobox_handle, index);
        if (result == CB_ERR) {
            error_code = GetLastError();
        }
        return result;
    }

    void combobox::clear(HWND combobox_handle) {
        ComboBox_ResetContent(combobox_handle);
    }

    void combobox::set_text_limit(HWND combobox_handle, int32_t limit) {
        ComboBox_LimitText(combobox_handle, limit);
    }

    int32_t combobox::get_text_len(HWND combobox_handle) {
        SetLastError(ERROR_SUCCESS);
        int32_t result = GetWindowTextLengthW(combobox_handle);
        error_code = GetLastError();
        return result;
    }

    int32_t combobox::get_text(HWND combobox_handle, std::string &text) {
        int32_t result = GetWindowTextA(combobox_handle, text.data(),
                                        static_cast<int32_t>(text.size()));
        if (!result) {
            error_code = GetLastError();
        }
        return result;
    }

    int32_t combobox::get_text(HWND combobox_handle, std::wstring &text) {
        int32_t result = GetWindowTextW(combobox_handle, text.data(),
                                        static_cast<int32_t>(text.size()));
        if (!result) {
            error_code = GetLastError();
        }
        return result;
    }

    int32_t combobox::get_item_count(HWND combobox_handle) {
        return ComboBox_GetCount(combobox_handle);
    }

    int32_t combobox::get_item_text_len(HWND combobox_handle, int32_t index) {
        return ComboBox_GetLBTextLen(combobox_handle, index);
    }

    int32_t combobox::get_item_text(HWND combobox_handle,
                                    std::string &text,
                                    int32_t index,
                                    helper::CodePage code_page) {
        int32_t result =
                ComboBox_GetLBText(combobox_handle, index,
                                   helper::convert::str_to_wstr(text, code_page)
                                           .data());
        if (result == CB_ERR) {
            error_code = GetLastError();
        }
        return result;
    }

    int32_t combobox::get_item_text(HWND combobox_handle,
                                    std::wstring &text,
                                    int32_t index) {
        int32_t result =
                ComboBox_GetLBText(combobox_handle, index, text.data());
        if (result == CB_ERR) {
            error_code = GetLastError();
        }
        return result;
    }

    int32_t combobox::replace_item_text(HWND combobox_handle,
                                        std::string &text,
                                        int32_t index,
                                        helper::CodePage code_page) {
        int32_t result = ComboBox_DeleteString(combobox_handle, index);
        if (result == CB_ERR) {
            error_code = GetLastError();
            return result;
        }
        result = ComboBox_InsertString(
                combobox_handle, index,
                helper::convert::str_to_wstr(text, code_page).data());
        if (result == CB_ERR) {
            error_code = GetLastError();
        }
        return result;
    }

    int32_t combobox::replace_item_text(HWND combobox_handle,
                                        std::wstring &text,
                                        int32_t index) {
        int32_t result = ComboBox_DeleteString(combobox_handle, index);
        if (result == CB_ERR) {
            error_code = GetLastError();
            return result;
        }
        result = ComboBox_InsertString(combobox_handle, index, text.data());
        if (result == CB_ERR) {
            error_code = GetLastError();
        }
        return result;
    }

    int32_t combobox::get_item_height(HWND combobox_handle) {
        return ComboBox_GetItemHeight(combobox_handle);
    }

    bool combobox::set_item_height(HWND combobox_handle,
                                   int32_t height,
                                   int32_t index) {
        int32_t result = ComboBox_SetItemHeight(combobox_handle, index, height);
        return result != CB_ERR;
    }

    bool combobox::set_text(HWND combobox_handle, std::string &text) {
        if (!SetWindowTextA(combobox_handle, text.data())) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool combobox::set_text(HWND combobox_handle, std::wstring &text) {
        int32_t result = GetWindowTextW(combobox_handle, text.data(),
                                        static_cast<int32_t>(text.size()));
        if (!result) {
            error_code = GetLastError();
        }
        return result;
    }

    int32_t combobox::add_data(HWND combobox_handle, LPARAM data) {
        int32_t result = ComboBox_AddItemData(combobox_handle, data);
        if (result == CB_ERRSPACE) {
            error_code = ERROR_OUTOFMEMORY;
        }
        else if (result == CB_ERR) {
            error_code = GetLastError();
        }
        return result;
    }

    int32_t
    combobox::insert_data(HWND combobox_handle, LPARAM data, int32_t index) {
        int32_t result = ComboBox_InsertItemData(combobox_handle, index, data);
        if (result == CB_ERRSPACE) {
            error_code = ERROR_OUTOFMEMORY;
        }
        else if (result == CB_ERR) {
            error_code = GetLastError();
        }
        return result;
    }

    int32_t
    combobox::select_data(HWND combobox_handle, LPARAM data, int32_t index) {
        int32_t result = ComboBox_SelectItemData(combobox_handle, index, data);
        if (result == CB_ERR) {
            error_code = GetLastError();
        }
        return result;
    }

    int32_t
    combobox::find_data(HWND combobox_handle, LPARAM data, int32_t index) {
        int32_t result = ComboBox_FindItemData(combobox_handle, index, data);
        if (result == CB_ERR) {
            error_code = GetLastError();
        }
        return result;
    }

    LPARAM combobox::get_data(HWND combobox_handle, int32_t index) {
        return ComboBox_GetItemData(combobox_handle, index);
    }

    int32_t
    combobox::set_data(HWND combobox_handle, LPARAM data, int32_t index) {
        int32_t result = ComboBox_SetItemData(combobox_handle, index, data);
        if (result == CB_ERR) {
            error_code = GetLastError();
        }
        return result;
    }

    bool combobox::get_prompt_banner(HWND combobox_handle,
                                     std::string &text,
                                     helper::CodePage code_page) {
        std::wstring temp(text.size(), L'\0');
        bool is_ok = ComboBox_GetCueBannerText(combobox_handle, temp.data(),
                                               temp.size());
        error_code = GetLastError();
        text.clear();
        text = helper::convert::wstr_to_str(temp, code_page);
        return is_ok;
    }

    bool combobox::get_prompt_banner(HWND combobox_handle, std::wstring &text) {
        bool is_ok = ComboBox_GetCueBannerText(combobox_handle, text.data(),
                                               text.size());
        error_code = GetLastError();
        return is_ok;
    }

    bool combobox::set_prompt_banner(HWND combobox_handle,
                                     std::string &text,
                                     helper::CodePage code_page) {
        std::wstring temp = helper::convert::str_to_wstr(text, code_page);
        bool is_ok = ComboBox_SetCueBannerText(combobox_handle, temp.data());
        error_code = GetLastError();
        return is_ok;
    }

    bool combobox::set_prompt_banner(HWND combobox_handle, std::wstring &text) {
        bool is_ok = ComboBox_SetCueBannerText(combobox_handle, text.data());
        error_code = GetLastError();
        return is_ok;
    }

    int32_t combobox::get_curr_select(HWND combobox_handle) {
        int32_t result = ComboBox_GetCurSel(combobox_handle);
        if (result == CB_ERR) {
            error_code = GetLastError();
        }
        return result;
    }

    int32_t combobox::set_curr_select(HWND combobox_handle, int32_t index) {
        int32_t result = ComboBox_SetCurSel(combobox_handle, index);
        if (result == CB_ERR) {
            error_code = GetLastError();
        }
        return result;
    }

    bool combobox::is_extended_ui(HWND combobox_handle) {
        return ComboBox_GetExtendedUI(combobox_handle);
    }

    bool combobox::is_default_ui(HWND combobox_handle) {
        return !(ComboBox_GetExtendedUI(combobox_handle));
    }

    int32_t combobox::set_extended_ui(HWND combobox_handle) {
        int32_t result = ComboBox_SetExtendedUI(combobox_handle, TRUE);
        if (result == CB_ERR) {
            error_code = GetLastError();
        }
        return result;
    }

    int32_t combobox::set_default_ui(HWND combobox_handle) {
        int32_t result = ComboBox_SetExtendedUI(combobox_handle, FALSE);
        if (result == CB_ERR) {
            error_code = GetLastError();
        }
        return result;
    }

    int32_t combobox::get_min_visible(HWND combobox_handle) {
        return ComboBox_GetMinVisible(combobox_handle);
    }

    bool combobox::set_min_visible(HWND combobox_handle, int32_t num) {
        return ComboBox_SetMinVisible(combobox_handle, num);
    }

    void combobox::show_drop_down(HWND combobox_handle) {
        ComboBox_ShowDropdown(combobox_handle, TRUE);
    }
    void combobox::hide_drop_down(HWND combobox_handle) {
        ComboBox_ShowDropdown(combobox_handle, FALSE);
    }

    bool combobox::is_drop_down_visible(HWND combobox_handle) {
        return ComboBox_GetDroppedState(combobox_handle);
    }

    void combobox::get_dropped_control_rect(HWND combobox_handle, RECT *rect) {
        ComboBox_GetDroppedControlRect(combobox_handle, rect);
    }

    bool combobox::get_info(HWND combobox_handle, COMBOBOXINFO *combobox_info) {
        if (!GetComboBoxInfo(combobox_handle, combobox_info)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    uint32_t combobox::err_code() const {
        return error_code;
    }

    std::string combobox::err_string() const {
        std::string result = helper::convert::err_string(error_code);
        return result;
    }

    std::wstring combobox::err_wstring() const {
        std::wstring result = helper::convert::err_wstring(error_code);
        return result;
    }
} // namespace YanLib::components
