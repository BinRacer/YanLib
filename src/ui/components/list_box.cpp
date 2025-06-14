/* clang-format off */
/*
 * @file list_box.cpp
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
#include "list_box.h"
#include <windowsx.h>

namespace YanLib::ui::components {
    list_box::~list_box() {
        for (auto &handle : list_box_handles) {
            if (handle && IsWindow(handle)) {
                DestroyWindow(handle);
                handle = nullptr;
            }
        }
        list_box_handles.clear();
    }

    HWND list_box::create(uintptr_t list_box_id,
                          HWND parent_window_handle,
                          LPARAM lparam,
                          int32_t x,
                          int32_t y,
                          int32_t width,
                          int32_t height,
                          ListBoxStyle style,
                          WindowStyle window_style) {
        HWND result = CreateWindowExW(0L, L"ListBox", nullptr,
                                      static_cast<uint32_t>(window_style) |
                                              static_cast<uint32_t>(style),
                                      x, y, width, height, parent_window_handle,
                                      reinterpret_cast<HMENU>(list_box_id),
                                      reinterpret_cast<CREATESTRUCT *>(lparam)
                                              ->hInstance,
                                      nullptr);
        if (!result) {
            error_code = GetLastError();
            return nullptr;
        }
        list_box_rwlock.write_lock();
        list_box_handles.push_back(result);
        list_box_rwlock.write_unlock();
        return result;
    }

    HWND list_box::create(const char *list_box_name,
                          uintptr_t list_box_id,
                          HWND parent_window_handle,
                          LPARAM lparam,
                          int32_t x,
                          int32_t y,
                          int32_t width,
                          int32_t height,
                          ListBoxStyle style,
                          WindowStyle window_style) {
        HWND result = CreateWindowExA(0L, "ListBox", list_box_name,
                                      static_cast<uint32_t>(window_style) |
                                              static_cast<uint32_t>(style),
                                      x, y, width, height, parent_window_handle,
                                      reinterpret_cast<HMENU>(list_box_id),
                                      reinterpret_cast<CREATESTRUCT *>(lparam)
                                              ->hInstance,
                                      nullptr);
        if (!result) {
            error_code = GetLastError();
            return nullptr;
        }
        list_box_rwlock.write_lock();
        list_box_handles.push_back(result);
        list_box_rwlock.write_unlock();
        return result;
    }

    HWND list_box::create(const wchar_t *list_box_name,
                          uintptr_t list_box_id,
                          HWND parent_window_handle,
                          LPARAM lparam,
                          int32_t x,
                          int32_t y,
                          int32_t width,
                          int32_t height,
                          ListBoxStyle style,
                          WindowStyle window_style) {
        HWND result = CreateWindowExW(0L, L"ListBox", list_box_name,
                                      static_cast<uint32_t>(window_style) |
                                              static_cast<uint32_t>(style),
                                      x, y, width, height, parent_window_handle,
                                      reinterpret_cast<HMENU>(list_box_id),
                                      reinterpret_cast<CREATESTRUCT *>(lparam)
                                              ->hInstance,
                                      nullptr);
        if (!result) {
            error_code = GetLastError();
            return nullptr;
        }
        list_box_rwlock.write_lock();
        list_box_handles.push_back(result);
        list_box_rwlock.write_unlock();
        return result;
    }

    bool list_box::destroy(HWND list_box_handle) {
        if (!list_box_handle || !IsWindow(list_box_handle)) {
            return false;
        }
        list_box_rwlock.write_lock();
        const auto it = std::find(list_box_handles.begin(),
                                  list_box_handles.end(), list_box_handle);
        if (it != list_box_handles.end()) {
            *it = nullptr;
        }
        list_box_rwlock.write_unlock();
        if (!DestroyWindow(list_box_handle)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool list_box::enable(HWND list_box_handle) {
        return ListBox_Enable(list_box_handle, TRUE);
    }

    bool list_box::disable(HWND list_box_handle) {
        return ListBox_Enable(list_box_handle, FALSE);
    }


    int32_t list_box::fill(HWND list_box_handle,
                           const char *path_spec,
                           FileType type,
                           helper::CodePage code_page) {
        const int32_t result =
                ListBox_Dir(list_box_handle, static_cast<uint32_t>(type),
                            helper::convert::str_to_wstr(path_spec, code_page)
                                    .data());
        if (result == LB_ERRSPACE) {
            error_code = ERROR_OUTOFMEMORY;
        } else if (result == LB_ERR) {
            error_code = GetLastError();
        }
        return result;
    }

    int32_t list_box::fill(HWND list_box_handle,
                           const wchar_t *path_spec,
                           FileType type) {
        const int32_t result =
                ListBox_Dir(list_box_handle, static_cast<uint32_t>(type),
                            path_spec);
        if (result == LB_ERRSPACE) {
            error_code = ERROR_OUTOFMEMORY;
        } else if (result == LB_ERR) {
            error_code = GetLastError();
        }
        return result;
    }

    int32_t list_box::add_text(HWND list_box_handle,
                               std::string &text,
                               helper::CodePage code_page) {
        const int32_t result =
                ListBox_AddString(list_box_handle,
                                  helper::convert::str_to_wstr(text, code_page)
                                          .data());
        if (result == LB_ERRSPACE) {
            error_code = ERROR_OUTOFMEMORY;
        } else if (result == LB_ERR) {
            error_code = GetLastError();
        }
        return result;
    }

    int32_t list_box::add_text(HWND list_box_handle, std::wstring &text) {
        const int32_t result = ListBox_AddString(list_box_handle, text.data());
        if (result == LB_ERRSPACE) {
            error_code = ERROR_OUTOFMEMORY;
        } else if (result == LB_ERR) {
            error_code = GetLastError();
        }
        return result;
    }

    int32_t list_box::find_text(HWND list_box_handle,
                                std::string &text,
                                int32_t index,
                                helper::CodePage code_page) {
        const int32_t result =
                ListBox_FindString(list_box_handle, index,
                                   helper::convert::str_to_wstr(text, code_page)
                                           .data());
        if (result == LB_ERR) {
            error_code = GetLastError();
        }
        return result;
    }

    int32_t list_box::find_text(HWND list_box_handle,
                                std::wstring &text,
                                int32_t index) {
        const int32_t result =
                ListBox_FindString(list_box_handle, index, text.data());
        if (result == LB_ERR) {
            error_code = GetLastError();
        }
        return result;
    }

    int32_t list_box::find_text_exact(HWND list_box_handle,
                                      std::string &text,
                                      int32_t index,
                                      helper::CodePage code_page) {
        const int32_t result = ListBox_FindStringExact(
                list_box_handle, index,
                helper::convert::str_to_wstr(text, code_page).data());
        if (result == LB_ERR) {
            error_code = GetLastError();
        }
        return result;
    }

    int32_t list_box::find_text_exact(HWND list_box_handle,
                                      std::wstring &text,
                                      int32_t index) {
        const int32_t result =
                ListBox_FindStringExact(list_box_handle, index, text.data());
        if (result == LB_ERR) {
            error_code = GetLastError();
        }
        return result;
    }

    int32_t list_box::insert_text(HWND list_box_handle,
                                  std::string &text,
                                  int32_t index,
                                  helper::CodePage code_page) {
        const int32_t result = ListBox_InsertString(
                list_box_handle, index,
                helper::convert::str_to_wstr(text, code_page).data());
        if (result == LB_ERRSPACE) {
            error_code = ERROR_OUTOFMEMORY;
        } else if (result == LB_ERR) {
            error_code = GetLastError();
        }
        return result;
    }

    int32_t list_box::insert_text(HWND list_box_handle,
                                  std::wstring &text,
                                  int32_t index) {
        const int32_t result =
                ListBox_InsertString(list_box_handle, index, text.data());
        if (result == LB_ERRSPACE) {
            error_code = ERROR_OUTOFMEMORY;
        } else if (result == LB_ERR) {
            error_code = GetLastError();
        }
        return result;
    }

    int32_t list_box::select_text(HWND list_box_handle,
                                  std::string &text,
                                  int32_t index,
                                  helper::CodePage code_page) {
        const int32_t result = ListBox_SelectString(
                list_box_handle, index,
                helper::convert::str_to_wstr(text, code_page).data());
        if (result == LB_ERR) {
            error_code = GetLastError();
        }
        return result;
    }

    int32_t list_box::select_text(HWND list_box_handle,
                                  std::wstring &text,
                                  int32_t index) {
        const int32_t result =
                ListBox_SelectString(list_box_handle, index, text.data());
        if (result == LB_ERR) {
            error_code = GetLastError();
        }
        return result;
    }

    int32_t list_box::delete_item(HWND list_box_handle, int32_t index) {
        const int32_t result = ListBox_DeleteString(list_box_handle, index);
        if (result == LB_ERR) {
            error_code = GetLastError();
        }
        return result;
    }

    int32_t list_box::get_item_text_len(HWND list_box_handle, int32_t index) {
        return ListBox_GetTextLen(list_box_handle, index);
    }

    int32_t list_box::get_item_text(HWND list_box_handle,
                                    std::string &text,
                                    int32_t index,
                                    helper::CodePage code_page) {
        std::wstring temp(text.size(), L'\0');
        const int32_t result =
                ListBox_GetText(list_box_handle, index, temp.data());
        text.clear();
        text = helper::convert::wstr_to_str(temp, code_page);
        if (result == LB_ERR) {
            error_code = GetLastError();
        }
        return result;
    }

    int32_t list_box::get_item_text(HWND list_box_handle,
                                    std::wstring &text,
                                    int32_t index) {
        const int32_t result =
                ListBox_GetText(list_box_handle, index, text.data());
        if (result == LB_ERR) {
            error_code = GetLastError();
        }
        return result;
    }

    int32_t list_box::add_data(HWND list_box_handle, LPARAM data) {
        const int32_t result = ListBox_AddItemData(list_box_handle, data);
        if (result == LB_ERRSPACE) {
            error_code = ERROR_OUTOFMEMORY;
        } else if (result == LB_ERR) {
            error_code = GetLastError();
        }
        return result;
    }

    int32_t
    list_box::find_data(HWND list_box_handle, LPARAM data, int32_t index) {
        const int32_t result =
                ListBox_FindItemData(list_box_handle, index, data);
        if (result == LB_ERR) {
            error_code = GetLastError();
        }
        return result;
    }

    LPARAM list_box::get_data(HWND list_box_handle, int32_t index) {
        return ListBox_GetItemData(list_box_handle, index);
    }

    int32_t
    list_box::set_data(HWND list_box_handle, LPARAM data, int32_t index) {
        const int32_t result =
                ListBox_SetItemData(list_box_handle, index, data);
        if (result == LB_ERR) {
            error_code = GetLastError();
        }
        return result;
    }

    int32_t
    list_box::insert_data(HWND list_box_handle, LPARAM data, int32_t index) {
        const int32_t result =
                ListBox_InsertItemData(list_box_handle, index, data);
        if (result == LB_ERRSPACE) {
            error_code = ERROR_OUTOFMEMORY;
        } else if (result == LB_ERR) {
            error_code = GetLastError();
        }
        return result;
    }

    int32_t
    list_box::select_data(HWND list_box_handle, LPARAM data, int32_t index) {
        const int32_t result =
                ListBox_SelectItemData(list_box_handle, index, data);
        if (result == LB_ERR) {
            error_code = GetLastError();
        }
        return result;
    }

    int32_t list_box::get_item_height(HWND list_box_handle, int32_t index) {
        const int32_t result = ListBox_GetItemHeight(list_box_handle, index);
        if (result == LB_ERR) {
            error_code = GetLastError();
        }
        return result;
    }

    int32_t list_box::set_item_height(HWND list_box_handle,
                                      int32_t width,
                                      int32_t index) {
        const int32_t result =
                ListBox_SetItemHeight(list_box_handle, index, width);
        if (result == LB_ERR) {
            error_code = GetLastError();
        }
        return result;
    }

    bool
    list_box::get_item_rect(HWND list_box_handle, RECT *rect, int32_t index) {
        return ListBox_GetItemRect(list_box_handle, index, rect) != LB_ERR;
    }

    int32_t list_box::get_select_items(HWND list_box_handle,
                                       std::vector<int32_t> &select_index) {
        const int32_t result =
                ListBox_GetSelItems(list_box_handle, select_index.size(),
                                    select_index.data());
        if (result == LB_ERR) {
            error_code = GetLastError();
        }
        return result;
    }

    bool
    list_box::set_item_range(HWND list_box_handle, int32_t start, int32_t end) {
        return ListBox_SelItemRange(list_box_handle, TRUE, start, end) !=
                LB_ERR;
    }

    bool list_box::unset_item_range(HWND list_box_handle,
                                    int32_t start,
                                    int32_t end) {
        return ListBox_SelItemRange(list_box_handle, FALSE, start, end) !=
                LB_ERR;
    }

    int32_t list_box::get_curr_select(HWND list_box_handle) {
        const int32_t result = ListBox_GetCurSel(list_box_handle);
        if (result == LB_ERR) {
            error_code = GetLastError();
        }
        return result;
    }

    int32_t list_box::set_curr_select(HWND list_box_handle, int32_t index) {
        const int32_t result = ListBox_SetCurSel(list_box_handle, index);
        if (result == LB_ERR) {
            error_code = GetLastError();
        }
        return result;
    }

    bool list_box::is_select(HWND list_box_handle, int32_t index) {
        if (const int32_t result = ListBox_GetSel(list_box_handle, index);
            result == LB_ERR || result == 0) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool list_box::set_select(HWND list_box_handle, int32_t index) {
        return ListBox_SetSel(list_box_handle, TRUE, index) != LB_ERR;
    }

    bool list_box::unset_select(HWND list_box_handle, int32_t index) {
        return ListBox_SetSel(list_box_handle, FALSE, index) != LB_ERR;
    }

    int32_t list_box::get_select_count(HWND list_box_handle) {
        const int32_t result = ListBox_GetSelCount(list_box_handle);
        if (result == LB_ERR) {
            error_code = GetLastError();
        }
        return result;
    }

    int32_t list_box::get_caret_index(HWND list_box_handle) {
        return ListBox_GetCaretIndex(list_box_handle);
    }

    bool list_box::set_caret_index(HWND list_box_handle, int32_t index) {
        return ListBox_SetCaretIndex(list_box_handle, index) != LB_ERR;
    }

    int32_t list_box::get_top_index(HWND list_box_handle) {
        return ListBox_GetTopIndex(list_box_handle);
    }

    bool list_box::set_top_index(HWND list_box_handle, int32_t index) {
        return ListBox_SetTopIndex(list_box_handle, index) != LB_ERR;
    }

    void list_box::reset_content(HWND list_box_handle) {
        ListBox_ResetContent(list_box_handle);
    }

    int32_t list_box::get_horiz_extent(HWND list_box_handle) {
        return ListBox_GetHorizontalExtent(list_box_handle);
    }

    void list_box::set_horiz_extent(HWND list_box_handle, int32_t extent) {
        ListBox_SetHorizontalExtent(list_box_handle, extent);
    }

    void list_box::set_all_colum_width(HWND list_box_handle, int32_t width) {
        ListBox_SetColumnWidth(list_box_handle, width);
    }

    int32_t list_box::get_item_count(HWND list_box_handle) {
        return ListBox_GetCount(list_box_handle);
    }

    bool list_box::set_tab_stops(HWND list_box_handle,
                                 std::vector<int32_t> &tab_stops) {
        return ListBox_SetTabStops(list_box_handle, tab_stops.size(),
                                   tab_stops.data());
    }

    void list_box::draw_insert(HWND parent_window_handle,
                               HWND list_box_handle,
                               int32_t icon_id) {
        DrawInsert(parent_window_handle, list_box_handle, icon_id);
    }

    int32_t list_box::item_id_from_point(HWND list_box_handle,
                                         POINT point,
                                         bool auto_scroll) {
        return LBItemFromPt(list_box_handle, point, auto_scroll ? TRUE : FALSE);
    }

    bool list_box::modify_to_drag_list(HWND list_box_handle) {
        return MakeDragList(list_box_handle);
    }

    uint32_t list_box::err_code() const {
        return error_code;
    }

    std::string list_box::err_string() const {
        std::string result = helper::convert::err_string(error_code);
        return result;
    }

    std::wstring list_box::err_wstring() const {
        std::wstring result = helper::convert::err_wstring(error_code);
        return result;
    }
} // namespace YanLib::ui::components
