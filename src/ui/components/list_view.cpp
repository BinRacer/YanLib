/* clang-format off */
/*
 * @file list_view.cpp
 * @date 2025-05-27
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
#include "list_view.h"
#include <windowsx.h>

namespace YanLib::ui::components {
    list_view::list_view() {
        INITCOMMONCONTROLSEX icc = {};
        icc.dwSize = sizeof(INITCOMMONCONTROLSEX);
        icc.dwICC = ICC_LISTVIEW_CLASSES;
        InitCommonControlsEx(&icc);
    }

    list_view::~list_view() {
        for (auto &handle : list_view_handles) {
            if (handle && IsWindow(handle)) {
                DestroyWindow(handle);
                handle = nullptr;
            }
        }
        list_view_handles.clear();
    }

    HWND list_view::create(uintptr_t list_view_id,
                           HWND parent_window_handle,
                           LPARAM lparam,
                           int32_t x,
                           int32_t y,
                           int32_t width,
                           int32_t height,
                           ListViewStyle style,
                           WindowStyle window_style) {
        HWND result = CreateWindowExW(0L, L"SysListView32", nullptr,
                                      static_cast<uint32_t>(window_style) |
                                              static_cast<uint32_t>(style),
                                      x, y, width, height, parent_window_handle,
                                      reinterpret_cast<HMENU>(list_view_id),
                                      reinterpret_cast<CREATESTRUCT *>(lparam)
                                              ->hInstance,
                                      nullptr);
        if (!result) {
            error_code = GetLastError();
            return nullptr;
        }
        list_view_rwlock.write_lock();
        list_view_handles.push_back(result);
        list_view_rwlock.write_unlock();
        return result;
    }

    HWND list_view::create(const char *list_view_name,
                           uintptr_t list_view_id,
                           HWND parent_window_handle,
                           LPARAM lparam,
                           int32_t x,
                           int32_t y,
                           int32_t width,
                           int32_t height,
                           ListViewStyle style,
                           WindowStyle window_style) {
        HWND result = CreateWindowExA(0L, "SysListView32", list_view_name,
                                      static_cast<uint32_t>(window_style) |
                                              static_cast<uint32_t>(style),
                                      x, y, width, height, parent_window_handle,
                                      reinterpret_cast<HMENU>(list_view_id),
                                      reinterpret_cast<CREATESTRUCT *>(lparam)
                                              ->hInstance,
                                      nullptr);
        if (!result) {
            error_code = GetLastError();
            return nullptr;
        }
        list_view_rwlock.write_lock();
        list_view_handles.push_back(result);
        list_view_rwlock.write_unlock();
        return result;
    }

    HWND list_view::create(const wchar_t *list_view_name,
                           uintptr_t list_view_id,
                           HWND parent_window_handle,
                           LPARAM lparam,
                           int32_t x,
                           int32_t y,
                           int32_t width,
                           int32_t height,
                           ListViewStyle style,
                           WindowStyle window_style) {
        HWND result = CreateWindowExW(0L, L"SysListView32", list_view_name,
                                      static_cast<uint32_t>(window_style) |
                                              static_cast<uint32_t>(style),
                                      x, y, width, height, parent_window_handle,
                                      reinterpret_cast<HMENU>(list_view_id),
                                      reinterpret_cast<CREATESTRUCT *>(lparam)
                                              ->hInstance,
                                      nullptr);
        if (!result) {
            error_code = GetLastError();
            return nullptr;
        }
        list_view_rwlock.write_lock();
        list_view_handles.push_back(result);
        list_view_rwlock.write_unlock();
        return result;
    }

    bool list_view::destroy(HWND list_view_handle) {
        if (!list_view_handle || !IsWindow(list_view_handle)) {
            return false;
        }
        list_view_rwlock.write_lock();
        const auto it = std::find(list_view_handles.begin(),
                                  list_view_handles.end(), list_view_handle);
        if (it != list_view_handles.end()) {
            *it = nullptr;
        }
        list_view_rwlock.write_unlock();
        if (!DestroyWindow(list_view_handle)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    HWND list_view::edit_label(HWND list_view_handle, int32_t index) {
        return ListView_EditLabel(list_view_handle, index);
    }

    void list_view::cancel_edit_label(HWND list_view_handle) {
        ListView_CancelEditLabel(list_view_handle);
    }

    bool list_view::delete_item(HWND list_view_handle, int32_t index) {
        return ListView_DeleteItem(list_view_handle, index);
    }

    bool list_view::delete_column(HWND list_view_handle, int32_t column_index) {
        return ListView_DeleteColumn(list_view_handle, column_index);
    }

    bool list_view::delete_all_items(HWND list_view_handle) {
        return ListView_DeleteAllItems(list_view_handle);
    }

    HIMAGELIST list_view::create_drag_image(HWND list_view_handle,
                                            POINT *left_top,
                                            int32_t index) {
        return ListView_CreateDragImage(list_view_handle, index, left_top);
    }

    std::pair<uint32_t, uint32_t>
    list_view::approximate_view_rect(HWND list_view_handle,
                                     int32_t width,
                                     int32_t height,
                                     int32_t count) {
        uint32_t result = ListView_ApproximateViewRect(list_view_handle, width,
                                                       height, count);
        return std::make_pair(LOWORD(result), HIWORD(result));
    }

    bool list_view::arrange(HWND list_view_handle, LVAlignStyle style) {
        return ListView_Arrange(list_view_handle, static_cast<uint32_t>(style));
    }

    int32_t list_view::enable_group_view(HWND list_view_handle) {
        return ListView_EnableGroupView(list_view_handle, TRUE);
    }

    int32_t list_view::disable_group_view(HWND list_view_handle) {
        return ListView_EnableGroupView(list_view_handle, FALSE);
    }

    bool list_view::is_group_view_enabled(HWND list_view_handle) {
        return ListView_IsGroupViewEnabled(list_view_handle);
    }

    bool list_view::ensure_visible(HWND list_view_handle,
                                   int32_t index,
                                   bool entire_visible) {
        return ListView_EnsureVisible(list_view_handle, index, entire_visible);
    }

    int32_t list_view::find_item(HWND list_view_handle,
                                 const LVFINDINFOW *find_info,
                                 int32_t index) {
        return ListView_FindItem(list_view_handle, index, find_info);
    }

    COLORREF list_view::get_background_color(HWND list_view_handle) {
        return ListView_GetBkColor(list_view_handle);
    }

    bool list_view::set_background_color(HWND list_view_handle,
                                         COLORREF color) {
        return ListView_SetBkColor(list_view_handle, color);
    }

    bool list_view::get_background_image(HWND list_view_handle,
                                         LVBKIMAGEW *image) {
        return ListView_GetBkImage(list_view_handle, image);
    }

    bool list_view::set_background_image(HWND list_view_handle,
                                         LVBKIMAGEW *image) {
        return ListView_SetBkImage(list_view_handle, image);
    }

    LVItemState list_view::get_callback_mask(HWND list_view_handle) {
        return static_cast<LVItemState>(
                ListView_GetCallbackMask(list_view_handle));
    }

    bool list_view::set_callback_mask(HWND list_view_handle, LVItemState mask) {
        return ListView_SetCallbackMask(list_view_handle,
                                        static_cast<uint32_t>(mask));
    }

    bool list_view::is_checked(HWND list_view_handle, uint32_t index) {
        return ListView_GetCheckState(list_view_handle, index);
    }

    void list_view::set_check(HWND list_view_handle, uint32_t index) {
        ListView_SetCheckState(list_view_handle, index, TRUE);
    }

    void list_view::unset_check(HWND list_view_handle, uint32_t index) {
        ListView_SetCheckState(list_view_handle, index, FALSE);
    }

    bool list_view::get_column(HWND list_view_handle,
                               LVCOLUMNW *column,
                               int32_t column_index) {
        return ListView_GetColumn(list_view_handle, column_index, column);
    }

    bool list_view::set_column(HWND list_view_handle,
                               const LVCOLUMNW *column,
                               int32_t column_index) {
        return ListView_SetColumn(list_view_handle, column_index, column);
    }

    bool list_view::get_column_order(HWND list_view_handle,
                                     std::vector<int32_t> &order) {
        return ListView_GetColumnOrderArray(list_view_handle, order.size(),
                                            order.data());
    }

    void list_view::set_column_order(HWND list_view_handle,
                                     std::vector<int32_t> &order) {
        ListView_SetColumnOrderArray(list_view_handle, order.size(),
                                     order.data());
    }

    int32_t list_view::get_column_width(HWND list_view_handle,
                                        int32_t column_index) {
        return ListView_GetColumnWidth(list_view_handle, column_index);
    }

    bool list_view::set_column_width(HWND list_view_handle,
                                     int32_t column_index,
                                     int32_t width) {
        return ListView_SetColumnWidth(list_view_handle, column_index, width);
    }

    int32_t list_view::get_count_per_page(HWND list_view_handle) {
        return ListView_GetCountPerPage(list_view_handle);
    }

    HWND list_view::get_edit_control(HWND list_view_handle) {
        return ListView_GetEditControl(list_view_handle);
    }

    bool list_view::get_empty_text(HWND list_view_handle,
                                   std::string &text,
                                   helper::CodePage code_page) {
        std::wstring temp(text.size(), L'\0');
        const bool is_ok = ListView_GetEmptyText(list_view_handle, temp.data(),
                                                 temp.size());
        text.clear();
        text = helper::convert::wstr_to_str(temp, code_page);
        return is_ok;
    }

    bool list_view::get_empty_text(HWND list_view_handle, std::wstring &text) {
        return ListView_GetEmptyText(list_view_handle, text.data(),
                                     text.size());
    }

    ListViewExtendStyle list_view::get_extended_style(HWND list_view_handle) {
        return static_cast<ListViewExtendStyle>(
                ListView_GetExtendedListViewStyle(list_view_handle));
    }

    void list_view::set_extended_style(HWND list_view_handle,
                                       ListViewExtendStyle style) {
        ListView_SetExtendedListViewStyle(list_view_handle,
                                          static_cast<uint32_t>(style));
    }

    void list_view::set_extended_style(HWND list_view_handle,
                                       ListViewExtendStyle style,
                                       ListViewExtendStyle mask) {
        ListView_SetExtendedListViewStyleEx(list_view_handle,
                                            static_cast<uint32_t>(mask),
                                            static_cast<uint32_t>(style));
    }

    int32_t list_view::get_focused_group(HWND list_view_handle) {
        return ListView_GetFocusedGroup(list_view_handle);
    }

    void list_view::get_footer_info(HWND list_view_handle,
                                    LVFOOTERINFO *footer_info) {
        ListView_GetFooterInfo(list_view_handle, footer_info);
    }

    bool list_view::get_footer_item(HWND list_view_handle,
                                    LVFOOTERITEM *footer_item,
                                    uint32_t index) {
        return ListView_GetFooterItem(list_view_handle, index, footer_item);
    }

    bool list_view::get_footer_item_rect(HWND list_view_handle,
                                         RECT *rect,
                                         uint32_t index) {
        return ListView_GetFooterItemRect(list_view_handle, index, rect);
    }

    bool list_view::get_footer_rect(HWND list_view_handle, RECT *rect) {
        return ListView_GetFooterRect(list_view_handle, rect);
    }

    int32_t list_view::get_group_count(HWND list_view_handle) {
        return ListView_GetGroupCount(list_view_handle);
    }

    HIMAGELIST list_view::get_group_header_image_list(HWND list_view_handle) {
        return ListView_GetGroupHeaderImageList(list_view_handle);
    }

    HIMAGELIST
    list_view::set_group_header_image_list(HWND list_view_handle,
                                           HIMAGELIST image_list_handle) {
        return ListView_SetGroupHeaderImageList(list_view_handle,
                                                image_list_handle);
    }

    int32_t list_view::get_group_info(HWND list_view_handle,
                                      LVGROUP *group,
                                      int32_t index) {
        return ListView_GetGroupInfo(list_view_handle, index, group);
    }

    int32_t list_view::set_group_info(HWND list_view_handle,
                                      LVGROUP *group,
                                      int32_t index) {
        return ListView_SetGroupInfo(list_view_handle, index, group);
    }

    bool list_view::get_group_info_by_index(HWND list_view_handle,
                                            LVGROUP *group,
                                            int32_t index) {
        return ListView_GetGroupInfoByIndex(list_view_handle, index, group);
    }

    void list_view::get_group_metrics(HWND list_view_handle,
                                      LVGROUPMETRICS *group_metrics) {
        ListView_GetGroupMetrics(list_view_handle, group_metrics);
    }

    void list_view::set_group_metrics(HWND list_view_handle,
                                      LVGROUPMETRICS *group_metrics) {
        ListView_SetGroupMetrics(list_view_handle, group_metrics);
    }

    bool list_view::get_group_rect(HWND list_view_handle,
                                   RECT *rect,
                                   int32_t index,
                                   GroupRectType type) {
        return ListView_GetGroupRect(list_view_handle, index,
                                     static_cast<uint32_t>(type), rect);
    }

    GroupState list_view::get_group_state(HWND list_view_handle,
                                          uint32_t index,
                                          GroupState mask) {
        return static_cast<GroupState>(
                ListView_GetGroupState(list_view_handle, index,
                                       static_cast<uint32_t>(mask)));
    }

    bool list_view::set_group_state(HWND list_view_handle,
                                    GroupState state,
                                    uint32_t index,
                                    GroupState mask) {
        LVGROUP group;
        group.cbSize = sizeof(group);
        group.mask = LVGF_STATE;
        group.stateMask = static_cast<uint32_t>(mask);
        group.state = static_cast<uint32_t>(state);
        const LRESULT result =
                SendMessageW(list_view_handle, LVM_SETGROUPINFO, index,
                             reinterpret_cast<LPARAM>(&group));
        return result != -1;
    }

    HWND list_view::get_header(HWND list_view_handle) {
        return ListView_GetHeader(list_view_handle);
    }

    HCURSOR list_view::get_hot_cursor(HWND list_view_handle) {
        return ListView_GetHotCursor(list_view_handle);
    }

    HCURSOR list_view::set_hot_cursor(HWND list_view_handle,
                                      HCURSOR cursor_handle) {
        return ListView_SetHotCursor(list_view_handle, cursor_handle);
    }

    int32_t list_view::get_hot_item(HWND list_view_handle) {
        return ListView_GetHotItem(list_view_handle);
    }

    int32_t list_view::set_hot_item(HWND list_view_handle, int32_t index) {
        return ListView_SetHotItem(list_view_handle, index);
    }

    uint32_t list_view::get_hover_time(HWND list_view_handle) {
        return ListView_GetHoverTime(list_view_handle);
    }

    void list_view::set_hover_time(HWND list_view_handle,
                                   uint32_t milli_seconds) {
        ListView_SetHoverTime(list_view_handle, milli_seconds);
    }

    HIMAGELIST list_view::get_image_list(HWND list_view_handle,
                                         LVILStyle style) {
        return ListView_GetImageList(list_view_handle,
                                     static_cast<int32_t>(style));
    }

    HIMAGELIST list_view::set_image_list(HWND list_view_handle,
                                         HIMAGELIST image_list_handle,
                                         LVILStyle style) {
        return ListView_SetImageList(list_view_handle, image_list_handle,
                                     static_cast<int32_t>(style));
    }

    bool list_view::get_insert_mark(HWND list_view_handle,
                                    LVINSERTMARK *insert_mark) {
        return ListView_GetInsertMark(list_view_handle, insert_mark);
    }

    bool list_view::set_insert_mark(HWND list_view_handle,
                                    LVINSERTMARK *insert_mark) {
        return ListView_SetInsertMark(list_view_handle, insert_mark);
    }

    COLORREF list_view::get_insert_mark_color(HWND list_view_handle) {
        return ListView_GetInsertMarkColor(list_view_handle);
    }

    COLORREF list_view::set_insert_mark_color(HWND list_view_handle,
                                              COLORREF color) {
        return ListView_SetInsertMarkColor(list_view_handle, color);
    }

    bool list_view::get_insert_mark_rect(HWND list_view_handle, RECT *rect) {
        return ListView_GetInsertMarkRect(list_view_handle, rect);
    }

    int32_t list_view::get_increment_search_string(HWND list_view_handle,
                                                   std::string &text,
                                                   helper::CodePage code_page) {
        std::wstring temp(text.size(), L'\0');
        const auto result =
                ListView_GetISearchString(list_view_handle, temp.data());
        text.clear();
        text = helper::convert::wstr_to_str(temp, code_page);
        return result;
    }

    int32_t list_view::get_increment_search_string(HWND list_view_handle,
                                                   std::wstring &text) {
        return ListView_GetISearchString(list_view_handle, text.data());
    }

    bool list_view::get_item(HWND list_view_handle, LVITEMW *item) {
        return ListView_GetItem(list_view_handle, item);
    }

    bool list_view::set_item(HWND list_view_handle, const LVITEMW *item) {
        return ListView_SetItem(list_view_handle, item);
    }

    int32_t list_view::get_item_count(HWND list_view_handle) {
        return ListView_GetItemCount(list_view_handle);
    }

    void list_view::set_item_count(HWND list_view_handle, int32_t count) {
        ListView_SetItemCount(list_view_handle, count);
    }

    void list_view::set_item_count(HWND list_view_handle,
                                   int32_t count,
                                   LVICFlag flag) {
        ListView_SetItemCountEx(list_view_handle, count, flag);
    }

    bool list_view::get_item_index_rect(HWND list_view_handle,
                                        LVITEMINDEX *item_index,
                                        int32_t index,
                                        LVIRCode code,
                                        RECT *rect) {
        return ListView_GetItemIndexRect(list_view_handle, item_index, index,
                                         static_cast<int32_t>(code), rect);
    }

    bool list_view::get_item_pos(HWND list_view_handle,
                                 POINT *point,
                                 int32_t index) {
        return ListView_GetItemPosition(list_view_handle, index, point);
    }

    bool
    list_view::set_item_pos(HWND list_view_handle, POINT point, int32_t index) {
        return ListView_SetItemPosition(list_view_handle, index, point.x,
                                        point.y);
    }

    void list_view::set_item_pos32(HWND list_view_handle,
                                   POINT point,
                                   int32_t index) {
        ListView_SetItemPosition32(list_view_handle, index, point.x, point.y);
    }

    bool list_view::get_item_rect(HWND list_view_handle,
                                  RECT *rect,
                                  int32_t index,
                                  LVIRCode code) {
        return ListView_GetItemRect(list_view_handle, index, rect,
                                    static_cast<int32_t>(code));
    }

    std::pair<uint32_t, uint32_t>
    list_view::get_item_spacing(HWND list_view_handle, bool small_icon) {
        const uint32_t result =
                ListView_GetItemSpacing(list_view_handle, small_icon);
        return std::make_pair(LOWORD(result), HIWORD(result));
    }

    LVItemState list_view::get_item_state(HWND list_view_handle,
                                          int32_t index,
                                          LVItemState mask) {
        return static_cast<LVItemState>(
                ListView_GetItemState(list_view_handle, index,
                                      static_cast<uint32_t>(mask)));
    }

    void list_view::set_item_state(HWND list_view_handle,
                                   LVItemState state,
                                   int32_t index,
                                   LVItemState mask) {
        ListView_SetItemState(list_view_handle, index,
                              static_cast<uint32_t>(state),
                              static_cast<uint32_t>(mask));
    }

    void list_view::get_item_text(HWND list_view_handle,
                                  std::string &text,
                                  int32_t item_index,
                                  int32_t sub_item_index,
                                  helper::CodePage code_page) {
        std::wstring temp(text.size(), L'\0');
        ListView_GetItemText(list_view_handle, item_index, sub_item_index,
                             temp.data(), temp.size());
        text.clear();
        text = helper::convert::wstr_to_str(temp, code_page);
    }

    void list_view::get_item_text(HWND list_view_handle,
                                  std::wstring &text,
                                  int32_t item_index,
                                  int32_t sub_item_index) {
        ListView_GetItemText(list_view_handle, item_index, sub_item_index,
                             text.data(), text.size());
    }

    void list_view::set_item_text(HWND list_view_handle,
                                  const std::string &text,
                                  int32_t item_index,
                                  int32_t sub_item_index,
                                  helper::CodePage code_page) {
        auto temp = helper::convert::str_to_wstr(text, code_page);
        ListView_SetItemText(list_view_handle, item_index, sub_item_index,
                             temp.data());
    }
    void list_view::set_item_text(HWND list_view_handle,
                                  std::wstring &text,
                                  int32_t item_index,
                                  int32_t sub_item_index) {
        ListView_SetItemText(list_view_handle, item_index, sub_item_index,
                             text.data());
    }

    int32_t list_view::get_next_item(HWND list_view_handle,
                                     int32_t index,
                                     LVNIFlag flag) {
        return ListView_GetNextItem(list_view_handle, index,
                                    static_cast<uint32_t>(flag));
    }

    bool list_view::get_next_item_index(HWND list_view_handle,
                                        LVITEMINDEX *item_index,
                                        LVNIFlag flag) {
        return ListView_GetNextItemIndex(list_view_handle, item_index,
                                         static_cast<uint32_t>(flag));
    }

    void list_view::get_number_of_work_areas(HWND list_view_handle,
                                             uint32_t *num_work_areas) {
        ListView_GetNumberOfWorkAreas(list_view_handle, num_work_areas);
    }

    bool list_view::get_origin(HWND list_view_handle, POINT *point) {
        return ListView_GetOrigin(list_view_handle, point);
    }

    COLORREF list_view::get_outline_color(HWND list_view_handle) {
        return ListView_GetOutlineColor(list_view_handle);
    }

    COLORREF list_view::set_outline_color(HWND list_view_handle,
                                          COLORREF color) {
        return ListView_SetOutlineColor(list_view_handle, color);
    }

    uint32_t list_view::get_selected_column(HWND list_view_handle) {
        return ListView_GetSelectedColumn(list_view_handle);
    }

    void list_view::set_selected_column(HWND list_view_handle,
                                        uint32_t column) {
        ListView_SetSelectedColumn(list_view_handle, column);
    }

    uint32_t list_view::get_selected_count(HWND list_view_handle) {
        return ListView_GetSelectedCount(list_view_handle);
    }

    int32_t list_view::get_selection_mark(HWND list_view_handle) {
        return ListView_GetSelectionMark(list_view_handle);
    }

    int32_t list_view::set_selection_mark(HWND list_view_handle, int32_t mark) {
        return ListView_SetSelectionMark(list_view_handle, mark);
    }

    int32_t list_view::get_string_width(HWND list_view_handle,
                                        const std::string &text,
                                        helper::CodePage code_page) {
        auto temp = helper::convert::str_to_wstr(text, code_page);
        return ListView_GetStringWidth(list_view_handle, temp.data());
    }

    int32_t list_view::get_string_width(HWND list_view_handle,
                                        const std::wstring &text) {
        return ListView_GetStringWidth(list_view_handle, text.data());
    }

    bool list_view::get_sub_item_rect(HWND list_view_handle,
                                      RECT *rect,
                                      int32_t item_index,
                                      int32_t sub_item_index,
                                      LVIRCode code) {
        return ListView_GetSubItemRect(list_view_handle, item_index,
                                       sub_item_index,
                                       static_cast<int32_t>(code), rect);
    }

    COLORREF list_view::get_text_background_color(HWND list_view_handle) {
        return ListView_GetTextBkColor(list_view_handle);
    }

    bool list_view::set_text_background_color(HWND list_view_handle,
                                              COLORREF color) {
        return ListView_SetTextBkColor(list_view_handle, color);
    }

    COLORREF list_view::get_text_color(HWND list_view_handle) {
        return ListView_GetTextColor(list_view_handle);
    }

    bool list_view::set_text_color(HWND list_view_handle, COLORREF color) {
        return ListView_SetTextColor(list_view_handle, color);
    }

    void list_view::get_tile_info(HWND list_view_handle,
                                  LVTILEINFO *tile_info) {
        ListView_GetTileInfo(list_view_handle, tile_info);
    }

    bool list_view::set_tile_info(HWND list_view_handle,
                                  LVTILEINFO *tile_info) {
        return ListView_SetTileInfo(list_view_handle, tile_info);
    }

    void list_view::get_tile_view_info(HWND list_view_handle,
                                       LVTILEVIEWINFO *tile_view_info) {
        ListView_GetTileViewInfo(list_view_handle, tile_view_info);
    }

    bool list_view::set_tile_view_info(HWND list_view_handle,
                                       LVTILEVIEWINFO *tile_view_info) {
        return ListView_SetTileViewInfo(list_view_handle, tile_view_info);
    }

    HWND list_view::get_tool_tips(HWND list_view_handle) {
        return ListView_GetToolTips(list_view_handle);
    }

    HWND list_view::set_tool_tips(HWND list_view_handle,
                                  HWND tool_tips_handle) {
        return ListView_SetToolTips(list_view_handle, tool_tips_handle);
    }

    int32_t list_view::get_top_index(HWND list_view_handle) {
        return ListView_GetTopIndex(list_view_handle);
    }

    bool list_view::is_ansi_format(HWND list_view_handle) {
        return !(ListView_GetUnicodeFormat(list_view_handle));
    }

    bool list_view::is_unicode_format(HWND list_view_handle) {
        return ListView_GetUnicodeFormat(list_view_handle);
    }

    void list_view::set_ansi_format(HWND list_view_handle) {
        ListView_SetUnicodeFormat(list_view_handle, FALSE);
    }

    void list_view::set_unicode_format(HWND list_view_handle) {
        ListView_SetUnicodeFormat(list_view_handle, TRUE);
    }

    uint32_t list_view::get_view(HWND list_view_handle) {
        return ListView_GetView(list_view_handle);
    }

    bool list_view::set_view(HWND list_view_handle, uint32_t view) {
        return ListView_SetView(list_view_handle, view) == 1;
    }

    bool list_view::get_view_rect(HWND list_view_handle, RECT *rect) {
        return ListView_GetViewRect(list_view_handle, rect);
    }

    void list_view::get_work_areas(HWND list_view_handle,
                                   std::vector<RECT> &work_areas) {
        ListView_GetWorkAreas(list_view_handle, work_areas.size(),
                              work_areas.data());
    }

    void list_view::set_work_areas(HWND list_view_handle,
                                   std::vector<RECT> &work_areas) {
        ListView_SetWorkAreas(list_view_handle, work_areas.size(),
                              work_areas.data());
    }

    bool list_view::contains_group(HWND list_view_handle, int32_t index) {
        return ListView_HasGroup(list_view_handle, index);
    }

    int32_t list_view::hit_test(HWND list_view_handle,
                                LVHITTESTINFO *hit_test_info) {
        return ListView_HitTest(list_view_handle, hit_test_info);
    }

    int32_t list_view::hit_test2(HWND list_view_handle,
                                 LVHITTESTINFO *hit_test_info) {
        return ListView_HitTestEx(list_view_handle, hit_test_info);
    }

    int32_t list_view::insert_column(HWND list_view_handle,
                                     const LVCOLUMNW *column,
                                     int32_t index) {
        return ListView_InsertColumn(list_view_handle, index, column);
    }

    int32_t list_view::insert_group(HWND list_view_handle,
                                    LVGROUP *group,
                                    int32_t index) {
        return ListView_InsertGroup(list_view_handle, index, group);
    }

    void
    list_view::insert_group_sorted(HWND list_view_handle,
                                   LVINSERTGROUPSORTED *insert_group_sorted) {
        ListView_InsertGroupSorted(list_view_handle, insert_group_sorted);
    }

    int32_t list_view::insert_item(HWND list_view_handle, const LVITEMW *item) {
        return ListView_InsertItem(list_view_handle, item);
    }

    bool list_view::insert_mark_hit_test(HWND list_view_handle,
                                         POINT *point,
                                         LVINSERTMARK *insert_mark) {
        return ListView_InsertMarkHitTest(list_view_handle, point, insert_mark);
    }

    bool list_view::is_item_visible(HWND list_view_handle, uint32_t index) {
        return ListView_IsItemVisible(list_view_handle, index);
    }

    uint32_t list_view::map_id_to_index(HWND list_view_handle, uint32_t id) {
        return ListView_MapIDToIndex(list_view_handle, id);
    }

    uint32_t list_view::map_index_to_id(HWND list_view_handle, uint32_t index) {
        return ListView_MapIndexToID(list_view_handle, index);
    }

    void list_view::move_group(HWND list_view_handle,
                               int32_t index_from,
                               int32_t index_to) {
        ListView_MoveGroup(list_view_handle, index_from, index_to);
    }

    void list_view::move_item_to_group(HWND list_view_handle,
                                       int32_t item_index,
                                       int32_t group_index) {
        ListView_MoveItemToGroup(list_view_handle, item_index, group_index);
    }

    bool list_view::redraw_items(HWND list_view_handle,
                                 int32_t first,
                                 int32_t last) {
        return ListView_RedrawItems(list_view_handle, first, last);
    }

    void list_view::remove_all_groups(HWND list_view_handle) {
        ListView_RemoveAllGroups(list_view_handle);
    }

    int32_t list_view::remove_group(HWND list_view_handle, int32_t index) {
        return ListView_RemoveGroup(list_view_handle, index);
    }

    bool list_view::scroll(HWND list_view_handle, int32_t horiz, int32_t vert) {
        return ListView_Scroll(list_view_handle, horiz, vert);
    }

    uint32_t list_view::set_icon_spacing(HWND list_view_handle,
                                         int32_t width,
                                         int32_t height) {
        return ListView_SetIconSpacing(list_view_handle, width, height);
    }

    bool list_view::set_info_tip(HWND list_view_handle,
                                 LVSETINFOTIP *set_info_tip) {
        return ListView_SetInfoTip(list_view_handle, set_info_tip);
    }

    bool list_view::set_item_index_state(HWND list_view_handle,
                                         LVITEMINDEX *item_index,
                                         LVItemState state,
                                         LVItemState mask) {
        LVITEMW item;
        item.stateMask = static_cast<uint32_t>(mask);
        item.state = static_cast<uint32_t>(state);
        return SendMessageW(list_view_handle, LVM_SETITEMINDEXSTATE,
                            reinterpret_cast<WPARAM>(item_index),
                            reinterpret_cast<LPARAM>(&item)) == S_OK;
    }

    bool list_view::sort_groups(HWND list_view_handle,
                                PFNLVGROUPCOMPARE fn,
                                void *param3) {
        return ListView_SortGroups(list_view_handle, fn, param3);
    }

    bool list_view::sort_items(HWND list_view_handle,
                               PFNLVCOMPARE fn,
                               void *param3) {
        return ListView_SortItems(list_view_handle, fn, param3);
    }

    bool list_view::sort_items2(HWND list_view_handle,
                                PFNLVCOMPARE fn,
                                void *param3) {
        return ListView_SortItemsEx(list_view_handle, fn, param3);
    }

    int32_t list_view::sub_item_hit_test(HWND list_view_handle,
                                         LVHITTESTINFO *hit_test_info) {
        return ListView_SubItemHitTest(list_view_handle, hit_test_info);
    }

    int32_t list_view::sub_item_hit_test2(HWND list_view_handle,
                                          LVHITTESTINFO *hit_test_info) {
        return ListView_SubItemHitTestEx(list_view_handle, hit_test_info);
    }

    bool list_view::update(HWND list_view_handle, int32_t index) {
        return ListView_Update(list_view_handle, index);
    }

    uint32_t list_view::err_code() const {
        return error_code;
    }

    std::string list_view::err_string() const {
        std::string result = helper::convert::err_string(error_code);
        return result;
    }

    std::wstring list_view::err_wstring() const {
        std::wstring result = helper::convert::err_wstring(error_code);
        return result;
    }
} // namespace YanLib::ui::components
