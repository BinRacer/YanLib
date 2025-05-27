//
// Created by forkernel on 2025/5/27.
//

#include "listview.h"
#include <windowsx.h>

namespace YanLib::components {
    HWND listview::create(uintptr_t listview_id,
                          HWND parent_window_handle,
                          LPARAM lparam,
                          int32_t x,
                          int32_t y,
                          int32_t width,
                          int32_t height,
                          ListViewStyle style,
                          WindowStyle window_style) {
        INITCOMMONCONTROLSEX icex = {};
        icex.dwSize = sizeof(INITCOMMONCONTROLSEX);
        icex.dwICC = ICC_LISTVIEW_CLASSES;
        InitCommonControlsEx(&icex);
        HWND result = CreateWindowExW(0L, L"SysListView32", nullptr,
                                      static_cast<uint32_t>(window_style) |
                                              static_cast<uint32_t>(style),
                                      x, y, width, height, parent_window_handle,
                                      reinterpret_cast<HMENU>(listview_id),
                                      reinterpret_cast<CREATESTRUCT *>(lparam)
                                              ->hInstance,
                                      nullptr);
        if (!result) {
            error_code = GetLastError();
        }
        return result;
    }

    HWND listview::edit_label(HWND listview_handle, int32_t index) {
        return ListView_EditLabel(listview_handle, index);
    }

    void listview::cancel_edit_label(HWND listview_handle) {
        ListView_CancelEditLabel(listview_handle);
    }

    bool listview::delete_item(HWND listview_handle, int32_t index) {
        return ListView_DeleteItem(listview_handle, index);
    }

    bool listview::delete_column(HWND listview_handle, int32_t column_index) {
        return ListView_DeleteColumn(listview_handle, column_index);
    }

    bool listview::delete_all_items(HWND listview_handle) {
        return ListView_DeleteAllItems(listview_handle);
    }

    HIMAGELIST listview::create_drag_image(HWND listview_handle,
                                           POINT *left_top,
                                           int32_t index) {
        return ListView_CreateDragImage(listview_handle, index, left_top);
    }

    std::pair<uint32_t, uint32_t>
    listview::approximate_view_rect(HWND listview_handle,
                                    int32_t width,
                                    int32_t height,
                                    int32_t count) {
        uint32_t result = ListView_ApproximateViewRect(listview_handle, width,
                                                       height, count);
        return std::make_pair(LOWORD(result), HIWORD(result));
    }

    bool listview::arrange(HWND listview_handle, LVAlignStyle style) {
        return ListView_Arrange(listview_handle, static_cast<uint32_t>(style));
    }

    int32_t listview::enable_group_view(HWND listview_handle) {
        return ListView_EnableGroupView(listview_handle, TRUE);
    }

    int32_t listview::disable_group_view(HWND listview_handle) {
        return ListView_EnableGroupView(listview_handle, FALSE);
    }

    bool listview::is_group_view_enabled(HWND listview_handle) {
        return ListView_IsGroupViewEnabled(listview_handle);
    }

    bool listview::ensure_visible(HWND listview_handle,
                                  int32_t index,
                                  bool entire_visible) {
        return ListView_EnsureVisible(listview_handle, index, entire_visible);
    }

    int32_t listview::find_item(HWND listview_handle,
                                const LVFINDINFOW *find_info,
                                int32_t index) {
        return ListView_FindItem(listview_handle, index, find_info);
    }

    COLORREF listview::get_background_color(HWND listview_handle) {
        return ListView_GetBkColor(listview_handle);
    }

    bool listview::set_background_color(HWND listview_handle, COLORREF color) {
        return ListView_SetBkColor(listview_handle, color);
    }

    bool listview::get_background_image(HWND listview_handle,
                                        LVBKIMAGEW *image) {
        return ListView_GetBkImage(listview_handle, image);
    }

    bool listview::set_background_image(HWND listview_handle,
                                        LVBKIMAGEW *image) {
        return ListView_SetBkImage(listview_handle, image);
    }

    LVItemState listview::get_callback_mask(HWND listview_handle) {
        return static_cast<LVItemState>(
                ListView_GetCallbackMask(listview_handle));
    }

    bool listview::set_callback_mask(HWND listview_handle, LVItemState mask) {
        return ListView_SetCallbackMask(listview_handle,
                                        static_cast<uint32_t>(mask));
    }

    bool listview::is_checked(HWND listview_handle, uint32_t index) {
        return ListView_GetCheckState(listview_handle, index);
    }

    void listview::set_check(HWND listview_handle, uint32_t index) {
        ListView_SetCheckState(listview_handle, index, TRUE);
    }

    void listview::unset_check(HWND listview_handle, uint32_t index) {
        ListView_SetCheckState(listview_handle, index, FALSE);
    }

    bool listview::get_column(HWND listview_handle,
                              LVCOLUMNW *column,
                              int32_t column_index) {
        return ListView_GetColumn(listview_handle, column_index, column);
    }

    bool listview::set_column(HWND listview_handle,
                              LVCOLUMNW *column,
                              int32_t column_index) {
        return ListView_SetColumn(listview_handle, column_index, column);
    }

    bool listview::get_column_order(HWND listview_handle,
                                    std::vector<int32_t> &order) {
        return ListView_GetColumnOrderArray(listview_handle, order.size(),
                                            order.data());
    }

    void listview::set_column_order(HWND listview_handle,
                                    std::vector<int32_t> &order) {
        ListView_SetColumnOrderArray(listview_handle, order.size(),
                                     order.data());
    }

    int32_t listview::get_column_width(HWND listview_handle,
                                       int32_t column_index) {
        return ListView_GetColumnWidth(listview_handle, column_index);
    }

    bool listview::set_column_width(HWND listview_handle,
                                    int32_t column_index,
                                    int32_t width) {
        return ListView_SetColumnWidth(listview_handle, column_index, width);
    }

    int32_t listview::get_count_per_page(HWND listview_handle) {
        return ListView_GetCountPerPage(listview_handle);
    }

    HWND listview::get_edit_control(HWND listview_handle) {
        return ListView_GetEditControl(listview_handle);
    }

    bool listview::get_empty_text(HWND listview_handle,
                                  std::string &text,
                                  helper::CodePage code_page) {
        std::wstring temp(text.size(), L'\0');
        bool is_ok = ListView_GetEmptyText(listview_handle, temp.data(),
                                           temp.size());
        text.clear();
        text = helper::convert::wstr_to_str(temp, code_page);
        return is_ok;
    }

    bool listview::get_empty_text(HWND listview_handle, std::wstring &text) {
        return ListView_GetEmptyText(listview_handle, text.data(), text.size());
    }

    ListViewExtendStyle listview::get_extended_style(HWND listview_handle) {
        return static_cast<ListViewExtendStyle>(
                ListView_GetExtendedListViewStyle(listview_handle));
    }

    void listview::set_extended_style(HWND listview_handle,
                                      ListViewExtendStyle style) {
        ListView_SetExtendedListViewStyle(listview_handle,
                                          static_cast<uint32_t>(style));
    }

    void listview::set_extended_style(HWND listview_handle,
                                      ListViewExtendStyle style,
                                      ListViewExtendStyle mask) {
        ListView_SetExtendedListViewStyleEx(listview_handle,
                                            static_cast<uint32_t>(mask),
                                            static_cast<uint32_t>(style));
    }

    int32_t listview::get_focused_group(HWND listview_handle) {
        return ListView_GetFocusedGroup(listview_handle);
    }

    void listview::get_footer_info(HWND listview_handle,
                                   LVFOOTERINFO *footer_info) {
        ListView_GetFooterInfo(listview_handle, footer_info);
    }

    bool listview::get_footer_item(HWND listview_handle,
                                   LVFOOTERITEM *footer_item,
                                   uint32_t index) {
        return ListView_GetFooterItem(listview_handle, index, footer_item);
    }

    bool listview::get_footer_item_rect(HWND listview_handle,
                                        RECT *rect,
                                        uint32_t index) {
        return ListView_GetFooterItemRect(listview_handle, index, rect);
    }

    bool listview::get_footer_rect(HWND listview_handle, RECT *rect) {
        return ListView_GetFooterRect(listview_handle, rect);
    }

    int32_t listview::get_group_count(HWND listview_handle) {
        return ListView_GetGroupCount(listview_handle);
    }

    HIMAGELIST listview::get_group_header_image_list(HWND listview_handle) {
        return ListView_GetGroupHeaderImageList(listview_handle);
    }

    HIMAGELIST
    listview::set_group_header_image_list(HWND listview_handle,
                                          HIMAGELIST image_list_handle) {
        return ListView_SetGroupHeaderImageList(listview_handle,
                                                image_list_handle);
    }

    int32_t listview::get_group_info(HWND listview_handle,
                                     LVGROUP *group,
                                     int32_t index) {
        return ListView_GetGroupInfo(listview_handle, index, group);
    }

    int32_t listview::set_group_info(HWND listview_handle,
                                     LVGROUP *group,
                                     int32_t index) {
        return ListView_SetGroupInfo(listview_handle, index, group);
    }

    bool listview::get_group_info_by_index(HWND listview_handle,
                                           LVGROUP *group,
                                           int32_t index) {
        return ListView_GetGroupInfoByIndex(listview_handle, index, group);
    }

    void listview::get_group_metrics(HWND listview_handle,
                                     LVGROUPMETRICS *group_metrics) {
        ListView_GetGroupMetrics(listview_handle, group_metrics);
    }

    void listview::set_group_metrics(HWND listview_handle,
                                     LVGROUPMETRICS *group_metrics) {
        ListView_SetGroupMetrics(listview_handle, group_metrics);
    }

    bool listview::get_group_rect(HWND listview_handle,
                                  RECT *rect,
                                  int32_t index,
                                  GroupRectType type) {
        return ListView_GetGroupRect(listview_handle, index,
                                     static_cast<uint32_t>(type), rect);
    }

    GroupState listview::get_group_state(HWND listview_handle,
                                         uint32_t index,
                                         GroupState mask) {
        return static_cast<GroupState>(
                ListView_GetGroupState(listview_handle, index,
                                       static_cast<uint32_t>(mask)));
    }

    bool listview::set_group_state(HWND listview_handle,
                                   GroupState state,
                                   uint32_t index,
                                   GroupState mask) {
        LVGROUP group;
        group.cbSize = sizeof(group);
        group.mask = LVGF_STATE;
        group.stateMask = static_cast<uint32_t>(mask);
        group.state = static_cast<uint32_t>(state);
        LRESULT result = SendMessageW(listview_handle, LVM_SETGROUPINFO, index,
                                      reinterpret_cast<LPARAM>(&group));
        return result != -1;
    }

    HWND listview::get_header(HWND listview_handle) {
        return ListView_GetHeader(listview_handle);
    }

    HCURSOR listview::get_hot_cursor(HWND listview_handle) {
        return ListView_GetHotCursor(listview_handle);
    }

    HCURSOR listview::set_hot_cursor(HWND listview_handle,
                                     HCURSOR cursor_handle) {
        return ListView_SetHotCursor(listview_handle, cursor_handle);
    }

    int32_t listview::get_hot_item(HWND listview_handle) {
        return ListView_GetHotItem(listview_handle);
    }

    int32_t listview::set_hot_item(HWND listview_handle, int32_t index) {
        return ListView_SetHotItem(listview_handle, index);
    }

    uint32_t listview::get_hover_time(HWND listview_handle) {
        return ListView_GetHoverTime(listview_handle);
    }

    void listview::set_hover_time(HWND listview_handle,
                                  uint32_t milli_seconds) {
        ListView_SetHoverTime(listview_handle, milli_seconds);
    }

    HIMAGELIST listview::get_image_list(HWND listview_handle, LVILStyle style) {
        return ListView_GetImageList(listview_handle,
                                     static_cast<int32_t>(style));
    }

    HIMAGELIST listview::set_image_list(HWND listview_handle,
                                        HIMAGELIST image_list_handle,
                                        LVILStyle style) {
        return ListView_SetImageList(listview_handle, image_list_handle,
                                     static_cast<int32_t>(style));
    }

    bool listview::get_insert_mark(HWND listview_handle,
                                   LVINSERTMARK *insert_mark) {
        return ListView_GetInsertMark(listview_handle, insert_mark);
    }

    bool listview::set_insert_mark(HWND listview_handle,
                                   LVINSERTMARK *insert_mark) {
        return ListView_SetInsertMark(listview_handle, insert_mark);
    }

    COLORREF listview::get_insert_mark_color(HWND listview_handle) {
        return ListView_GetInsertMarkColor(listview_handle);
    }

    COLORREF listview::set_insert_mark_color(HWND listview_handle,
                                             COLORREF color) {
        return ListView_SetInsertMarkColor(listview_handle, color);
    }

    bool listview::get_insert_mark_rect(HWND listview_handle, RECT *rect) {
        return ListView_GetInsertMarkRect(listview_handle, rect);
    }

    int32_t listview::get_increment_search_string(HWND listview_handle,
                                                  std::string &text,
                                                  helper::CodePage code_page) {
        std::wstring temp(text.size(), L'\0');
        int32_t result =
                ListView_GetISearchString(listview_handle, temp.data());
        text.clear();
        text = helper::convert::wstr_to_str(temp.data());
        return result;
    }

    int32_t listview::get_increment_search_string(HWND listview_handle,
                                                  std::wstring &text) {
        return ListView_GetISearchString(listview_handle, text.data());
    }

    bool listview::get_item(HWND listview_handle, LVITEMW *item) {
        return ListView_GetItem(listview_handle, item);
    }

    bool listview::set_item(HWND listview_handle, LVITEMW *item) {
        return ListView_SetItem(listview_handle, item);
    }

    int32_t listview::get_item_count(HWND listview_handle) {
        return ListView_GetItemCount(listview_handle);
    }

    void listview::set_item_count(HWND listview_handle, int32_t count) {
        ListView_SetItemCount(listview_handle, count);
    }

    void listview::set_item_count(HWND listview_handle,
                                  int32_t count,
                                  LVICFlag flag) {
        ListView_SetItemCountEx(listview_handle, count, flag);
    }

    bool listview::get_item_index_rect(HWND listview_handle,
                                       LVITEMINDEX *item_index,
                                       int32_t index,
                                       LVIRCode code,
                                       RECT *rect) {
        return ListView_GetItemIndexRect(listview_handle, item_index, index,
                                         static_cast<int32_t>(code), rect);
    }

    bool
    listview::get_item_pos(HWND listview_handle, POINT *point, int32_t index) {
        return ListView_GetItemPosition(listview_handle, index, point);
    }

    bool
    listview::set_item_pos(HWND listview_handle, POINT point, int32_t index) {
        return ListView_SetItemPosition(listview_handle, index, point.x,
                                        point.y);
    }

    void
    listview::set_item_pos32(HWND listview_handle, POINT point, int32_t index) {
        ListView_SetItemPosition32(listview_handle, index, point.x, point.y);
    }

    bool listview::get_item_rect(HWND listview_handle,
                                 RECT *rect,
                                 int32_t index,
                                 LVIRCode code) {
        return ListView_GetItemRect(listview_handle, index, rect,
                                    static_cast<int32_t>(code));
    }

    std::pair<uint32_t, uint32_t>
    listview::get_item_spacing(HWND listview_handle, bool small_icon) {
        uint32_t result = ListView_GetItemSpacing(listview_handle, small_icon);
        return std::make_pair(LOWORD(result), HIWORD(result));
    }

    LVItemState listview::get_item_state(HWND listview_handle,
                                         int32_t index,
                                         LVItemState mask) {
        return static_cast<LVItemState>(
                ListView_GetItemState(listview_handle, index,
                                      static_cast<uint32_t>(mask)));
    }

    void listview::set_item_state(HWND listview_handle,
                                  LVItemState state,
                                  int32_t index,
                                  LVItemState mask) {
        ListView_SetItemState(listview_handle, index,
                              static_cast<uint32_t>(state),
                              static_cast<uint32_t>(mask));
    }

    void listview::get_item_text(HWND listview_handle,
                                 std::string &text,
                                 int32_t item_index,
                                 int32_t sub_item_index,
                                 helper::CodePage code_page) {
        std::wstring temp(text.size(), L'\0');
        ListView_GetItemText(listview_handle, item_index, sub_item_index,
                             temp.data(), temp.size());
        text.clear();
        text = helper::convert::wstr_to_str(temp.data());
    }

    void listview::get_item_text(HWND listview_handle,
                                 std::wstring &text,
                                 int32_t item_index,
                                 int32_t sub_item_index) {
        ListView_GetItemText(listview_handle, item_index, sub_item_index,
                             text.data(), text.size());
    }

    void listview::set_item_text(HWND listview_handle,
                                 std::string &text,
                                 int32_t item_index,
                                 int32_t sub_item_index,
                                 helper::CodePage code_page) {
        auto temp = helper::convert::str_to_wstr(text, code_page);
        ListView_SetItemText(listview_handle, item_index, sub_item_index,
                             temp.data());
    }
    void listview::set_item_text(HWND listview_handle,
                                 std::wstring &text,
                                 int32_t item_index,
                                 int32_t sub_item_index) {
        ListView_SetItemText(listview_handle, item_index, sub_item_index,
                             text.data());
    }

    int32_t listview::get_next_item(HWND listview_handle,
                                    int32_t index,
                                    LVNIFlag flag) {
        return ListView_GetNextItem(listview_handle, index,
                                    static_cast<uint32_t>(flag));
    }

    bool listview::get_next_item_index(HWND listview_handle,
                                       LVITEMINDEX *item_index,
                                       LVNIFlag flag) {
        return ListView_GetNextItemIndex(listview_handle, item_index,
                                         static_cast<uint32_t>(flag));
    }

    void listview::get_number_of_work_areas(HWND listview_handle,
                                            uint32_t *num_work_areas) {
        ListView_GetNumberOfWorkAreas(listview_handle, num_work_areas);
    }

    bool listview::get_origin(HWND listview_handle, POINT *point) {
        return ListView_GetOrigin(listview_handle, point);
    }

    COLORREF listview::get_outline_color(HWND listview_handle) {
        return ListView_GetOutlineColor(listview_handle);
    }

    COLORREF listview::set_outline_color(HWND listview_handle, COLORREF color) {
        return ListView_SetOutlineColor(listview_handle, color);
    }

    uint32_t listview::get_selected_column(HWND listview_handle) {
        return ListView_GetSelectedColumn(listview_handle);
    }

    void listview::set_selected_column(HWND listview_handle, uint32_t column) {
        ListView_SetSelectedColumn(listview_handle, column);
    }

    uint32_t listview::get_selected_count(HWND listview_handle) {
        return ListView_GetSelectedCount(listview_handle);
    }

    int32_t listview::get_selection_mark(HWND listview_handle) {
        return ListView_GetSelectionMark(listview_handle);
    }

    int32_t listview::set_selection_mark(HWND listview_handle, int32_t mark) {
        return ListView_SetSelectionMark(listview_handle, mark);
    }

    int32_t listview::get_string_width(HWND listview_handle,
                                       std::string &text,
                                       helper::CodePage code_page) {
        auto temp = helper::convert::str_to_wstr(text, code_page);
        return ListView_GetStringWidth(listview_handle, temp.data());
    }

    int32_t listview::get_string_width(HWND listview_handle,
                                       std::wstring &text) {
        return ListView_GetStringWidth(listview_handle, text.data());
    }

    bool listview::get_sub_item_rect(HWND listview_handle,
                                     RECT *rect,
                                     int32_t item_index,
                                     int32_t sub_item_index,
                                     LVIRCode code) {
        return ListView_GetSubItemRect(listview_handle, item_index,
                                       sub_item_index,
                                       static_cast<int32_t>(code), rect);
    }

    COLORREF listview::get_text_background_color(HWND listview_handle) {
        return ListView_GetTextBkColor(listview_handle);
    }

    bool listview::set_text_background_color(HWND listview_handle,
                                             COLORREF color) {
        return ListView_SetTextBkColor(listview_handle, color);
    }

    COLORREF listview::get_text_color(HWND listview_handle) {
        return ListView_GetTextColor(listview_handle);
    }

    bool listview::set_text_color(HWND listview_handle, COLORREF color) {
        return ListView_SetTextColor(listview_handle, color);
    }

    uint32_t listview::err_code() const {
        return error_code;
    }

    std::string listview::err_string() const {
        std::string result = helper::convert::err_string(error_code);
        return result;
    }

    std::wstring listview::err_wstring() const {
        std::wstring result = helper::convert::err_wstring(error_code);
        return result;
    }
} // namespace YanLib::components
