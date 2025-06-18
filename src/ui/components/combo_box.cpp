/* clang-format off */
/*
 * @file combo_box.cpp
 * @date 2025-05-24
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
#include "combo_box.h"
#include <windowsx.h>

namespace YanLib::ui::components {
    combo_box::~combo_box() {
        for (auto &handle : combo_box_handles) {
            if (handle && IsWindow(handle)) {
                DestroyWindow(handle);
                handle = nullptr;
            }
        }
        combo_box_handles.clear();
    }

    HWND combo_box::create(uintptr_t combo_box_id,
                           HWND parent_window_handle,
                           LPARAM lparam,
                           int32_t x,
                           int32_t y,
                           int32_t width,
                           int32_t height,
                           ComboBoxStyle style,
                           core::WindowStyle window_style) {
        HWND result = CreateWindowExW(0L, L"ComboBox", nullptr,
                                      static_cast<uint32_t>(window_style) |
                                              static_cast<uint32_t>(style),
                                      x, y, width, height, parent_window_handle,
                                      reinterpret_cast<HMENU>(combo_box_id),
                                      reinterpret_cast<CREATESTRUCT *>(lparam)
                                              ->hInstance,
                                      nullptr);
        if (!result) {
            error_code = GetLastError();
            return nullptr;
        }
        combo_box_rwlock.write_lock();
        combo_box_handles.push_back(result);
        combo_box_rwlock.write_unlock();
        return result;
    }

    HWND combo_box::create(const char *combo_box_name,
                           uintptr_t combo_box_id,
                           HWND parent_window_handle,
                           LPARAM lparam,
                           int32_t x,
                           int32_t y,
                           int32_t width,
                           int32_t height,
                           ComboBoxStyle style,
                           core::WindowStyle window_style) {
        HWND result = CreateWindowExA(0L, "ComboBox", combo_box_name,
                                      static_cast<uint32_t>(window_style) |
                                              static_cast<uint32_t>(style),
                                      x, y, width, height, parent_window_handle,
                                      reinterpret_cast<HMENU>(combo_box_id),
                                      reinterpret_cast<CREATESTRUCT *>(lparam)
                                              ->hInstance,
                                      nullptr);
        if (!result) {
            error_code = GetLastError();
            return nullptr;
        }
        combo_box_rwlock.write_lock();
        combo_box_handles.push_back(result);
        combo_box_rwlock.write_unlock();
        return result;
    }

    HWND combo_box::create(const wchar_t *combo_box_name,
                           uintptr_t combo_box_id,
                           HWND parent_window_handle,
                           LPARAM lparam,
                           int32_t x,
                           int32_t y,
                           int32_t width,
                           int32_t height,
                           ComboBoxStyle style,
                           core::WindowStyle window_style) {
        HWND result = CreateWindowExW(0L, L"ComboBox", combo_box_name,
                                      static_cast<uint32_t>(window_style) |
                                              static_cast<uint32_t>(style),
                                      x, y, width, height, parent_window_handle,
                                      reinterpret_cast<HMENU>(combo_box_id),
                                      reinterpret_cast<CREATESTRUCT *>(lparam)
                                              ->hInstance,
                                      nullptr);
        if (!result) {
            error_code = GetLastError();
            return nullptr;
        }
        combo_box_rwlock.write_lock();
        combo_box_handles.push_back(result);
        combo_box_rwlock.write_unlock();
        return result;
    }

    bool combo_box::destroy(HWND combo_box_handle) {
        if (!combo_box_handle || !IsWindow(combo_box_handle)) {
            return false;
        }
        combo_box_rwlock.write_lock();
        const auto it = std::find(combo_box_handles.begin(),
                                  combo_box_handles.end(), combo_box_handle);
        if (it != combo_box_handles.end()) {
            *it = nullptr;
        }
        combo_box_rwlock.write_unlock();
        if (!DestroyWindow(combo_box_handle)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool combo_box::enable(HWND combo_box_handle) {
        return ComboBox_Enable(combo_box_handle, TRUE);
    }

    bool combo_box::disable(HWND combo_box_handle) {
        return ComboBox_Enable(combo_box_handle, FALSE);
    }

    int32_t combo_box::fill(HWND combo_box_handle,
                            const char *path_spec,
                            ComboFileType type,
                            helper::CodePage code_page) {
        const int32_t result =
                ComboBox_Dir(combo_box_handle, static_cast<uint32_t>(type),
                             helper::convert::str_to_wstr(path_spec, code_page)
                                     .data());
        if (result == CB_ERRSPACE) {
            error_code = ERROR_OUTOFMEMORY;
        } else if (result == CB_ERR) {
            error_code = GetLastError();
        }
        return result;
    }

    int32_t
    combo_box::fill(HWND combo_box_handle, wchar_t *path_spec, ComboFileType type) {
        const int32_t result =
                ComboBox_Dir(combo_box_handle, static_cast<uint32_t>(type),
                             path_spec);
        if (result == CB_ERRSPACE) {
            error_code = ERROR_OUTOFMEMORY;
        } else if (result == CB_ERR) {
            error_code = GetLastError();
        }
        return result;
    }

    int32_t combo_box::add_text(HWND combo_box_handle,
                                std::string &text,
                                helper::CodePage code_page) {
        const int32_t result =
                ComboBox_AddString(combo_box_handle,
                                   helper::convert::str_to_wstr(text, code_page)
                                           .data());
        if (result == CB_ERRSPACE) {
            error_code = ERROR_OUTOFMEMORY;
        } else if (result == CB_ERR) {
            error_code = GetLastError();
        }
        return result;
    }

    int32_t combo_box::add_text(HWND combo_box_handle, std::wstring &text) {
        const int32_t result =
                ComboBox_AddString(combo_box_handle, text.data());
        if (result == CB_ERRSPACE) {
            error_code = ERROR_OUTOFMEMORY;
        } else if (result == CB_ERR) {
            error_code = GetLastError();
        }
        return result;
    }

    int32_t combo_box::insert_text(HWND combo_box_handle,
                                   std::string &text,
                                   int32_t index,
                                   helper::CodePage code_page) {
        const int32_t result = ComboBox_InsertString(
                combo_box_handle, index,
                helper::convert::str_to_wstr(text, code_page).data());
        if (result == CB_ERRSPACE) {
            error_code = ERROR_OUTOFMEMORY;
        } else if (result == CB_ERR) {
            error_code = GetLastError();
        }
        return result;
    }

    int32_t combo_box::insert_text(HWND combo_box_handle,
                                   std::wstring &text,
                                   int32_t index) {
        const int32_t result =
                ComboBox_InsertString(combo_box_handle, index, text.data());
        if (result == CB_ERRSPACE) {
            error_code = ERROR_OUTOFMEMORY;
        } else if (result == CB_ERR) {
            error_code = GetLastError();
        }
        return result;
    }

    int32_t combo_box::select_text(HWND combo_box_handle,
                                   std::string &text,
                                   int32_t index,
                                   helper::CodePage code_page) {
        const int32_t result = ComboBox_SelectString(
                combo_box_handle, index,
                helper::convert::str_to_wstr(text, code_page).data());
        if (result == CB_ERR) {
            error_code = GetLastError();
        }
        return result;
    }

    int32_t combo_box::select_text(HWND combo_box_handle,
                                   std::wstring &text,
                                   int32_t index) {
        const int32_t result =
                ComboBox_SelectString(combo_box_handle, index, text.data());
        if (result == CB_ERR) {
            error_code = GetLastError();
        }
        return result;
    }

    int32_t combo_box::find_text(HWND combo_box_handle,
                                 std::string &text,
                                 int32_t index,
                                 helper::CodePage code_page) {
        const int32_t result = ComboBox_FindString(
                combo_box_handle, index,
                helper::convert::str_to_wstr(text, code_page).data());
        if (result == CB_ERR) {
            error_code = GetLastError();
        }
        return result;
    }

    int32_t combo_box::find_text(HWND combo_box_handle,
                                 std::wstring &text,
                                 int32_t index) {
        const int32_t result =
                ComboBox_FindString(combo_box_handle, index, text.data());
        if (result == CB_ERR) {
            error_code = GetLastError();
        }
        return result;
    }

    int32_t combo_box::find_exact_text(HWND combo_box_handle,
                                       std::string &text,
                                       int32_t index,
                                       helper::CodePage code_page) {
        const int32_t result = ComboBox_FindStringExact(
                combo_box_handle, index,
                helper::convert::str_to_wstr(text, code_page).data());
        if (result == CB_ERR) {
            error_code = GetLastError();
        }
        return result;
    }

    int32_t combo_box::find_exact_text(HWND combo_box_handle,
                                       std::wstring &text,
                                       int32_t index) {
        const int32_t result =
                ComboBox_FindStringExact(combo_box_handle, index, text.data());
        if (result == CB_ERR) {
            error_code = GetLastError();
        }
        return result;
    }

    int32_t combo_box::delete_item(HWND combo_box_handle, int32_t index) {
        const int32_t result = ComboBox_DeleteString(combo_box_handle, index);
        if (result == CB_ERR) {
            error_code = GetLastError();
        }
        return result;
    }

    void combo_box::clear(HWND combo_box_handle) {
        ComboBox_ResetContent(combo_box_handle);
    }

    void combo_box::set_text_limit(HWND combo_box_handle, int32_t limit) {
        ComboBox_LimitText(combo_box_handle, limit);
    }

    int32_t combo_box::get_text_len(HWND combo_box_handle) {
        SetLastError(ERROR_SUCCESS);
        const int32_t result = GetWindowTextLengthW(combo_box_handle);
        error_code = GetLastError();
        return result;
    }

    int32_t combo_box::get_text(HWND combo_box_handle, std::string &text) {
        const int32_t result =
                GetWindowTextA(combo_box_handle, text.data(),
                               static_cast<int32_t>(text.size()));
        if (!result) {
            error_code = GetLastError();
        }
        return result;
    }

    int32_t combo_box::get_text(HWND combo_box_handle, std::wstring &text) {
        const int32_t result =
                GetWindowTextW(combo_box_handle, text.data(),
                               static_cast<int32_t>(text.size()));
        if (!result) {
            error_code = GetLastError();
        }
        return result;
    }

    int32_t combo_box::get_item_count(HWND combo_box_handle) {
        return ComboBox_GetCount(combo_box_handle);
    }

    int32_t combo_box::get_item_text_len(HWND combo_box_handle, int32_t index) {
        return ComboBox_GetLBTextLen(combo_box_handle, index);
    }

    int32_t combo_box::get_item_text(HWND combo_box_handle,
                                     std::string &text,
                                     int32_t index,
                                     helper::CodePage code_page) {
        const int32_t result =
                ComboBox_GetLBText(combo_box_handle, index,
                                   helper::convert::str_to_wstr(text, code_page)
                                           .data());
        if (result == CB_ERR) {
            error_code = GetLastError();
        }
        return result;
    }

    int32_t combo_box::get_item_text(HWND combo_box_handle,
                                     std::wstring &text,
                                     int32_t index) {
        const int32_t result =
                ComboBox_GetLBText(combo_box_handle, index, text.data());
        if (result == CB_ERR) {
            error_code = GetLastError();
        }
        return result;
    }

    int32_t combo_box::replace_item_text(HWND combo_box_handle,
                                         std::string &text,
                                         int32_t index,
                                         helper::CodePage code_page) {
        int32_t result = ComboBox_DeleteString(combo_box_handle, index);
        if (result == CB_ERR) {
            error_code = GetLastError();
            return result;
        }
        result = ComboBox_InsertString(
                combo_box_handle, index,
                helper::convert::str_to_wstr(text, code_page).data());
        if (result == CB_ERR) {
            error_code = GetLastError();
        }
        return result;
    }

    int32_t combo_box::replace_item_text(HWND combo_box_handle,
                                         std::wstring &text,
                                         int32_t index) {
        int32_t result = ComboBox_DeleteString(combo_box_handle, index);
        if (result == CB_ERR) {
            error_code = GetLastError();
            return result;
        }
        result = ComboBox_InsertString(combo_box_handle, index, text.data());
        if (result == CB_ERR) {
            error_code = GetLastError();
        }
        return result;
    }

    int32_t combo_box::get_item_height(HWND combo_box_handle) {
        return ComboBox_GetItemHeight(combo_box_handle);
    }

    bool combo_box::set_item_height(HWND combo_box_handle,
                                    int32_t height,
                                    int32_t index) {
        const int32_t result =
                ComboBox_SetItemHeight(combo_box_handle, index, height);
        return result != CB_ERR;
    }

    bool combo_box::set_text(HWND combo_box_handle, std::string &text) {
        if (!SetWindowTextA(combo_box_handle, text.data())) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool combo_box::set_text(HWND combo_box_handle, std::wstring &text) {
        const int32_t result =
                GetWindowTextW(combo_box_handle, text.data(),
                               static_cast<int32_t>(text.size()));
        if (!result) {
            error_code = GetLastError();
        }
        return result;
    }

    int32_t combo_box::add_data(HWND combo_box_handle, LPARAM data) {
        const int32_t result = ComboBox_AddItemData(combo_box_handle, data);
        if (result == CB_ERRSPACE) {
            error_code = ERROR_OUTOFMEMORY;
        } else if (result == CB_ERR) {
            error_code = GetLastError();
        }
        return result;
    }

    int32_t
    combo_box::insert_data(HWND combo_box_handle, LPARAM data, int32_t index) {
        const int32_t result =
                ComboBox_InsertItemData(combo_box_handle, index, data);
        if (result == CB_ERRSPACE) {
            error_code = ERROR_OUTOFMEMORY;
        } else if (result == CB_ERR) {
            error_code = GetLastError();
        }
        return result;
    }

    int32_t
    combo_box::select_data(HWND combo_box_handle, LPARAM data, int32_t index) {
        const int32_t result =
                ComboBox_SelectItemData(combo_box_handle, index, data);
        if (result == CB_ERR) {
            error_code = GetLastError();
        }
        return result;
    }

    int32_t
    combo_box::find_data(HWND combo_box_handle, LPARAM data, int32_t index) {
        const int32_t result =
                ComboBox_FindItemData(combo_box_handle, index, data);
        if (result == CB_ERR) {
            error_code = GetLastError();
        }
        return result;
    }

    LPARAM combo_box::get_data(HWND combo_box_handle, int32_t index) {
        return ComboBox_GetItemData(combo_box_handle, index);
    }

    int32_t
    combo_box::set_data(HWND combo_box_handle, LPARAM data, int32_t index) {
        const int32_t result =
                ComboBox_SetItemData(combo_box_handle, index, data);
        if (result == CB_ERR) {
            error_code = GetLastError();
        }
        return result;
    }

    bool combo_box::get_prompt_banner(HWND combo_box_handle,
                                      std::string &text,
                                      helper::CodePage code_page) {
        std::wstring temp(text.size(), L'\0');
        const bool is_ok = ComboBox_GetCueBannerText(combo_box_handle,
                                                     temp.data(), temp.size());
        error_code = GetLastError();
        text.clear();
        text = helper::convert::wstr_to_str(temp, code_page);
        return is_ok;
    }

    bool combo_box::get_prompt_banner(HWND combo_box_handle,
                                      std::wstring &text) {
        const bool is_ok = ComboBox_GetCueBannerText(combo_box_handle,
                                                     text.data(), text.size());
        error_code = GetLastError();
        return is_ok;
    }

    bool combo_box::set_prompt_banner(HWND combo_box_handle,
                                      std::string &text,
                                      helper::CodePage code_page) {
        std::wstring temp = helper::convert::str_to_wstr(text, code_page);
        const bool is_ok =
                ComboBox_SetCueBannerText(combo_box_handle, temp.data());
        error_code = GetLastError();
        return is_ok;
    }

    bool combo_box::set_prompt_banner(HWND combo_box_handle,
                                      std::wstring &text) {
        const bool is_ok =
                ComboBox_SetCueBannerText(combo_box_handle, text.data());
        error_code = GetLastError();
        return is_ok;
    }

    int32_t combo_box::get_curr_select(HWND combo_box_handle) {
        const int32_t result = ComboBox_GetCurSel(combo_box_handle);
        if (result == CB_ERR) {
            error_code = GetLastError();
        }
        return result;
    }

    int32_t combo_box::set_curr_select(HWND combo_box_handle, int32_t index) {
        const int32_t result = ComboBox_SetCurSel(combo_box_handle, index);
        if (result == CB_ERR) {
            error_code = GetLastError();
        }
        return result;
    }

    bool combo_box::is_extended_ui(HWND combo_box_handle) {
        return ComboBox_GetExtendedUI(combo_box_handle);
    }

    bool combo_box::is_default_ui(HWND combo_box_handle) {
        return !(ComboBox_GetExtendedUI(combo_box_handle));
    }

    int32_t combo_box::set_extended_ui(HWND combo_box_handle) {
        const int32_t result = ComboBox_SetExtendedUI(combo_box_handle, TRUE);
        if (result == CB_ERR) {
            error_code = GetLastError();
        }
        return result;
    }

    int32_t combo_box::set_default_ui(HWND combo_box_handle) {
        const int32_t result = ComboBox_SetExtendedUI(combo_box_handle, FALSE);
        if (result == CB_ERR) {
            error_code = GetLastError();
        }
        return result;
    }

    int32_t combo_box::get_min_visible(HWND combo_box_handle) {
        return ComboBox_GetMinVisible(combo_box_handle);
    }

    bool combo_box::set_min_visible(HWND combo_box_handle, int32_t num) {
        return ComboBox_SetMinVisible(combo_box_handle, num);
    }

    void combo_box::show_drop_down(HWND combo_box_handle) {
        ComboBox_ShowDropdown(combo_box_handle, TRUE);
    }
    void combo_box::hide_drop_down(HWND combo_box_handle) {
        ComboBox_ShowDropdown(combo_box_handle, FALSE);
    }

    bool combo_box::is_drop_down_visible(HWND combo_box_handle) {
        return ComboBox_GetDroppedState(combo_box_handle);
    }

    void combo_box::get_dropped_control_rect(HWND combo_box_handle,
                                             RECT *rect) {
        ComboBox_GetDroppedControlRect(combo_box_handle, rect);
    }

    bool combo_box::get_info(HWND combo_box_handle,
                             COMBOBOXINFO *combo_box_info) {
        if (!GetComboBoxInfo(combo_box_handle, combo_box_info)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    uint32_t combo_box::err_code() const {
        return error_code;
    }

    std::string combo_box::err_string() const {
        std::string result = helper::convert::err_string(error_code);
        return result;
    }

    std::wstring combo_box::err_wstring() const {
        std::wstring result = helper::convert::err_wstring(error_code);
        return result;
    }
} // namespace YanLib::ui::components
