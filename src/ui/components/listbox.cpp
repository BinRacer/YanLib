//
// Created by forkernel on 2025/5/26.
//

#include "listbox.h"
#include <windowsx.h>

namespace YanLib::components {
    HWND listbox::create(uintptr_t listbox_id,
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
                                      reinterpret_cast<HMENU>(listbox_id),
                                      reinterpret_cast<CREATESTRUCT *>(lparam)
                                              ->hInstance,
                                      nullptr);
        if (!result) {
            error_code = GetLastError();
        }
        return result;
    }

    bool listbox::enable(HWND listbox_handle) {
        return ListBox_Enable(listbox_handle, TRUE);
    }

    bool listbox::disable(HWND listbox_handle) {
        return ListBox_Enable(listbox_handle, FALSE);
    }


    int32_t listbox::fill(HWND listbox_handle,
                          const char *path_spec,
                          FileType type,
                          helper::CodePage code_page) {
        int32_t result =
                ListBox_Dir(listbox_handle, static_cast<uint32_t>(type),
                            helper::convert::str_to_wstr(path_spec, code_page)
                                    .data());
        if (result == LB_ERRSPACE) {
            error_code = ERROR_OUTOFMEMORY;
        }
        else if (result == LB_ERR) {
            error_code = GetLastError();
        }
        return result;
    }

    int32_t listbox::fill(HWND listbox_handle,
                          const wchar_t *path_spec,
                          FileType type) {
        int32_t result = ListBox_Dir(listbox_handle,
                                     static_cast<uint32_t>(type), path_spec);
        if (result == LB_ERRSPACE) {
            error_code = ERROR_OUTOFMEMORY;
        }
        else if (result == LB_ERR) {
            error_code = GetLastError();
        }
        return result;
    }

    int32_t listbox::add_text(HWND listbox_handle,
                              std::string &text,
                              helper::CodePage code_page) {
        int32_t result =
                ListBox_AddString(listbox_handle,
                                  helper::convert::str_to_wstr(text, code_page)
                                          .data());
        if (result == LB_ERRSPACE) {
            error_code = ERROR_OUTOFMEMORY;
        }
        else if (result == LB_ERR) {
            error_code = GetLastError();
        }
        return result;
    }

    int32_t listbox::add_text(HWND listbox_handle, std::wstring &text) {
        int32_t result = ListBox_AddString(listbox_handle, text.data());
        if (result == LB_ERRSPACE) {
            error_code = ERROR_OUTOFMEMORY;
        }
        else if (result == LB_ERR) {
            error_code = GetLastError();
        }
        return result;
    }

    int32_t listbox::find_text(HWND listbox_handle,
                               std::string &text,
                               int32_t index,
                               helper::CodePage code_page) {
        int32_t result =
                ListBox_FindString(listbox_handle, index,
                                   helper::convert::str_to_wstr(text, code_page)
                                           .data());
        if (result == LB_ERR) {
            error_code = GetLastError();
        }
        return result;
    }

    int32_t
    listbox::find_text(HWND listbox_handle, std::wstring &text, int32_t index) {
        int32_t result = ListBox_FindString(listbox_handle, index, text.data());
        if (result == LB_ERR) {
            error_code = GetLastError();
        }
        return result;
    }

    int32_t listbox::find_text_exact(HWND listbox_handle,
                                     std::string &text,
                                     int32_t index,
                                     helper::CodePage code_page) {
        int32_t result = ListBox_FindStringExact(
                listbox_handle, index,
                helper::convert::str_to_wstr(text, code_page).data());
        if (result == LB_ERR) {
            error_code = GetLastError();
        }
        return result;
    }

    int32_t listbox::find_text_exact(HWND listbox_handle,
                                     std::wstring &text,
                                     int32_t index) {
        int32_t result =
                ListBox_FindStringExact(listbox_handle, index, text.data());
        if (result == LB_ERR) {
            error_code = GetLastError();
        }
        return result;
    }

    int32_t listbox::insert_text(HWND listbox_handle,
                                 std::string &text,
                                 int32_t index,
                                 helper::CodePage code_page) {
        int32_t result = ListBox_InsertString(
                listbox_handle, index,
                helper::convert::str_to_wstr(text, code_page).data());
        if (result == LB_ERRSPACE) {
            error_code = ERROR_OUTOFMEMORY;
        }
        else if (result == LB_ERR) {
            error_code = GetLastError();
        }
        return result;
    }

    int32_t listbox::insert_text(HWND listbox_handle,
                                 std::wstring &text,
                                 int32_t index) {
        int32_t result =
                ListBox_InsertString(listbox_handle, index, text.data());
        if (result == LB_ERRSPACE) {
            error_code = ERROR_OUTOFMEMORY;
        }
        else if (result == LB_ERR) {
            error_code = GetLastError();
        }
        return result;
    }

    int32_t listbox::select_text(HWND listbox_handle,
                                 std::string &text,
                                 int32_t index,
                                 helper::CodePage code_page) {
        int32_t result = ListBox_SelectString(
                listbox_handle, index,
                helper::convert::str_to_wstr(text, code_page).data());
        if (result == LB_ERR) {
            error_code = GetLastError();
        }
        return result;
    }

    int32_t listbox::select_text(HWND listbox_handle,
                                 std::wstring &text,
                                 int32_t index) {
        int32_t result =
                ListBox_SelectString(listbox_handle, index, text.data());
        if (result == LB_ERR) {
            error_code = GetLastError();
        }
        return result;
    }

    int32_t listbox::delete_item(HWND listbox_handle, int32_t index) {
        int32_t result = ListBox_DeleteString(listbox_handle, index);
        if (result == LB_ERR) {
            error_code = GetLastError();
        }
        return result;
    }

    int32_t listbox::get_item_text_len(HWND listbox_handle, int32_t index) {
        return ListBox_GetTextLen(listbox_handle, index);
    }

    int32_t listbox::get_item_text(HWND listbox_handle,
                                   std::string &text,
                                   int32_t index,
                                   helper::CodePage code_page) {
        std::wstring temp(text.size(), L'\0');
        int32_t result = ListBox_GetText(listbox_handle, index, temp.data());
        text.clear();
        text = helper::convert::wstr_to_str(temp, code_page);
        if (result == LB_ERR) {
            error_code = GetLastError();
        }
        return result;
    }

    int32_t listbox::get_item_text(HWND listbox_handle,
                                   std::wstring &text,
                                   int32_t index) {
        int32_t result = ListBox_GetText(listbox_handle, index, text.data());
        if (result == LB_ERR) {
            error_code = GetLastError();
        }
        return result;
    }

    int32_t listbox::add_data(HWND listbox_handle, LPARAM data) {
        int32_t result = ListBox_AddItemData(listbox_handle, data);
        if (result == LB_ERRSPACE) {
            error_code = ERROR_OUTOFMEMORY;
        }
        else if (result == LB_ERR) {
            error_code = GetLastError();
        }
        return result;
    }

    int32_t
    listbox::find_data(HWND listbox_handle, LPARAM data, int32_t index) {
        int32_t result = ListBox_FindItemData(listbox_handle, index, data);
        if (result == LB_ERR) {
            error_code = GetLastError();
        }
        return result;
    }

    LPARAM listbox::get_data(HWND listbox_handle, int32_t index) {
        return ListBox_GetItemData(listbox_handle, index);
    }

    int32_t listbox::set_data(HWND listbox_handle, LPARAM data, int32_t index) {
        int32_t result = ListBox_SetItemData(listbox_handle, index, data);
        if (result == LB_ERR) {
            error_code = GetLastError();
        }
        return result;
    }

    int32_t
    listbox::insert_data(HWND listbox_handle, LPARAM data, int32_t index) {
        int32_t result = ListBox_InsertItemData(listbox_handle, index, data);
        if (result == LB_ERRSPACE) {
            error_code = ERROR_OUTOFMEMORY;
        }
        else if (result == LB_ERR) {
            error_code = GetLastError();
        }
        return result;
    }

    int32_t
    listbox::select_data(HWND listbox_handle, LPARAM data, int32_t index) {
        int32_t result = ListBox_SelectItemData(listbox_handle, index, data);
        if (result == LB_ERR) {
            error_code = GetLastError();
        }
        return result;
    }

    int32_t listbox::get_item_height(HWND listbox_handle, int32_t index) {
        int32_t result = ListBox_GetItemHeight(listbox_handle, index);
        if (result == LB_ERR) {
            error_code = GetLastError();
        }
        return result;
    }

    int32_t listbox::set_item_height(HWND listbox_handle,
                                     int32_t width,
                                     int32_t index) {
        int32_t result = ListBox_SetItemHeight(listbox_handle, index, width);
        if (result == LB_ERR) {
            error_code = GetLastError();
        }
        return result;
    }

    bool
    listbox::get_item_rect(HWND listbox_handle, RECT *rect, int32_t index) {
        return ListBox_GetItemRect(listbox_handle, index, rect) != LB_ERR;
    }

    int32_t listbox::get_select_items(HWND listbox_handle,
                                      std::vector<int32_t> &select_index) {
        int32_t result =
                ListBox_GetSelItems(listbox_handle, select_index.size(),
                                    select_index.data());
        if (result == LB_ERR) {
            error_code = GetLastError();
        }
        return result;
    }

    bool
    listbox::set_item_range(HWND listbox_handle, int32_t start, int32_t end) {
        return ListBox_SelItemRange(listbox_handle, TRUE, start, end) != LB_ERR;
    }

    bool
    listbox::unset_item_range(HWND listbox_handle, int32_t start, int32_t end) {
        return ListBox_SelItemRange(listbox_handle, FALSE, start, end) !=
                LB_ERR;
    }

    int32_t listbox::get_curr_select(HWND listbox_handle) {
        int32_t result = ListBox_GetCurSel(listbox_handle);
        if (result == LB_ERR) {
            error_code = GetLastError();
        }
        return result;
    }

    int32_t listbox::set_curr_select(HWND listbox_handle, int32_t index) {
        int32_t result = ListBox_SetCurSel(listbox_handle, index);
        if (result == LB_ERR) {
            error_code = GetLastError();
        }
        return result;
    }

    bool listbox::is_select(HWND listbox_handle, int32_t index) {
        int32_t result = ListBox_GetSel(listbox_handle, index);
        if (result == LB_ERR || result == 0) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool listbox::set_select(HWND listbox_handle, int32_t index) {
        return ListBox_SetSel(listbox_handle, TRUE, index) != LB_ERR;
    }

    bool listbox::unset_select(HWND listbox_handle, int32_t index) {
        return ListBox_SetSel(listbox_handle, FALSE, index) != LB_ERR;
    }

    int32_t listbox::get_select_count(HWND listbox_handle) {
        int32_t result = ListBox_GetSelCount(listbox_handle);
        if (result == LB_ERR) {
            error_code = GetLastError();
        }
        return result;
    }

    int32_t listbox::get_caret_index(HWND listbox_handle) {
        return ListBox_GetCaretIndex(listbox_handle);
    }

    bool listbox::set_caret_index(HWND listbox_handle, int32_t index) {
        return ListBox_SetCaretIndex(listbox_handle, index) != LB_ERR;
    }

    int32_t listbox::get_top_index(HWND listbox_handle) {
        return ListBox_GetTopIndex(listbox_handle);
    }

    bool listbox::set_top_index(HWND listbox_handle, int32_t index) {
        return ListBox_SetTopIndex(listbox_handle, index) != LB_ERR;
    }

    void listbox::reset_content(HWND listbox_handle) {
        ListBox_ResetContent(listbox_handle);
    }

    int32_t listbox::get_horiz_extent(HWND listbox_handle) {
        return ListBox_GetHorizontalExtent(listbox_handle);
    }

    void listbox::set_horiz_extent(HWND listbox_handle, int32_t extent) {
        ListBox_SetHorizontalExtent(listbox_handle, extent);
    }

    void listbox::set_all_colum_width(HWND listbox_handle, int32_t width) {
        ListBox_SetColumnWidth(listbox_handle, width);
    }

    int32_t listbox::get_item_count(HWND listbox_handle) {
        return ListBox_GetCount(listbox_handle);
    }

    bool listbox::set_tab_stops(HWND listbox_handle,
                                std::vector<int32_t> &tab_stops) {
        return ListBox_SetTabStops(listbox_handle, tab_stops.size(),
                                   tab_stops.data());
    }

    void listbox::draw_insert(HWND parent_window_handle,
                              HWND listbox_handle,
                              int32_t icon_id) {
        DrawInsert(parent_window_handle, listbox_handle, icon_id);
    }

    int32_t listbox::item_id_from_point(HWND listbox_handle,
                                        POINT point,
                                        bool auto_scroll) {
        return LBItemFromPt(listbox_handle, point, auto_scroll ? TRUE : FALSE);
    }

    bool listbox::modify_to_drag_list(HWND listbox_handle) {
        return MakeDragList(listbox_handle);
    }

    uint32_t listbox::err_code() const {
        return error_code;
    }

    std::string listbox::err_string() const {
        std::string result = helper::convert::err_string(error_code);
        return result;
    }

    std::wstring listbox::err_wstring() const {
        std::wstring result = helper::convert::err_wstring(error_code);
        return result;
    }
} // namespace YanLib::components
