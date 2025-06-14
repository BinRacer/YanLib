/* clang-format off */
/*
 * @file tree.cpp
 * @date 2025-06-04
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
#include "tree.h"
#include <windowsx.h>

namespace YanLib::ui::components {
    tree::tree() {
        INITCOMMONCONTROLSEX icc = {};
        icc.dwSize = sizeof(INITCOMMONCONTROLSEX);
        icc.dwICC = ICC_TREEVIEW_CLASSES;
        InitCommonControlsEx(&icc);
    }

    tree::~tree() {
        for (auto &handle : tree_handles) {
            if (handle && IsWindow(handle)) {
                DestroyWindow(handle);
                handle = nullptr;
            }
        }
        tree_handles.clear();
    }

    HWND tree::create(uintptr_t tree_id,
                      HWND parent_window_handle,
                      LPARAM lparam,
                      int32_t x,
                      int32_t y,
                      int32_t width,
                      int32_t height,
                      TreeStyle style,
                      WindowStyle window_style) {
        HWND result = CreateWindowExW(0L, L"SysTreeView32", nullptr,
                                      static_cast<uint32_t>(window_style) |
                                              static_cast<uint32_t>(style),
                                      x, y, width, height, parent_window_handle,
                                      reinterpret_cast<HMENU>(tree_id),
                                      reinterpret_cast<CREATESTRUCT *>(lparam)
                                              ->hInstance,
                                      nullptr);
        if (!result) {
            error_code = GetLastError();
            return nullptr;
        }
        tree_rwlock.write_lock();
        tree_handles.push_back(result);
        tree_rwlock.write_unlock();
        return result;
    }

    HWND tree::create(const char *tree_name,
                      uintptr_t tree_id,
                      HWND parent_window_handle,
                      LPARAM lparam,
                      int32_t x,
                      int32_t y,
                      int32_t width,
                      int32_t height,
                      TreeStyle style,
                      WindowStyle window_style) {
        HWND result = CreateWindowExA(0L, "SysTreeView32", tree_name,
                                      static_cast<uint32_t>(window_style) |
                                              static_cast<uint32_t>(style),
                                      x, y, width, height, parent_window_handle,
                                      reinterpret_cast<HMENU>(tree_id),
                                      reinterpret_cast<CREATESTRUCT *>(lparam)
                                              ->hInstance,
                                      nullptr);
        if (!result) {
            error_code = GetLastError();
            return nullptr;
        }
        tree_rwlock.write_lock();
        tree_handles.push_back(result);
        tree_rwlock.write_unlock();
        return result;
    }

    HWND tree::create(const wchar_t *tree_name,
                      uintptr_t tree_id,
                      HWND parent_window_handle,
                      LPARAM lparam,
                      int32_t x,
                      int32_t y,
                      int32_t width,
                      int32_t height,
                      TreeStyle style,
                      WindowStyle window_style) {
        HWND result = CreateWindowExW(0L, L"SysTreeView32", tree_name,
                                      static_cast<uint32_t>(window_style) |
                                              static_cast<uint32_t>(style),
                                      x, y, width, height, parent_window_handle,
                                      reinterpret_cast<HMENU>(tree_id),
                                      reinterpret_cast<CREATESTRUCT *>(lparam)
                                              ->hInstance,
                                      nullptr);
        if (!result) {
            error_code = GetLastError();
            return nullptr;
        }
        tree_rwlock.write_lock();
        tree_handles.push_back(result);
        tree_rwlock.write_unlock();
        return result;
    }

    bool tree::destroy(HWND tree_handle) {
        if (!tree_handle || !IsWindow(tree_handle)) {
            return false;
        }
        tree_rwlock.write_lock();
        const auto it = std::find(tree_handles.begin(), tree_handles.end(),
                                  tree_handle);
        if (it != tree_handles.end()) {
            *it = nullptr;
        }
        tree_rwlock.write_unlock();
        if (!DestroyWindow(tree_handle)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    COLORREF tree::get_background_color(HWND tree_handle) {
        return TreeView_GetBkColor(tree_handle);
    }

    COLORREF tree::set_background_color(HWND tree_handle, COLORREF color) {
        return TreeView_SetBkColor(tree_handle, color);
    }

    COLORREF tree::get_text_color(HWND tree_handle) {
        return TreeView_GetTextColor(tree_handle);
    }

    COLORREF tree::set_text_color(HWND tree_handle, COLORREF color) {
        return TreeView_SetTextColor(tree_handle, color);
    }

    COLORREF tree::get_line_color(HWND tree_handle) {
        return TreeView_GetLineColor(tree_handle);
    }

    COLORREF tree::set_line_color(HWND tree_handle, COLORREF color) {
        return TreeView_SetLineColor(tree_handle, color);
    }

    COLORREF tree::get_insert_mark_color(HWND tree_handle) {
        return TreeView_GetInsertMarkColor(tree_handle);
    }

    COLORREF tree::set_insert_mark_color(HWND tree_handle, COLORREF color) {
        return TreeView_SetInsertMarkColor(tree_handle, color);
    }

    bool tree::is_ansi_format(HWND tree_handle) {
        return !(TreeView_GetUnicodeFormat(tree_handle));
    }

    bool tree::is_unicode_format(HWND tree_handle) {
        return TreeView_GetUnicodeFormat(tree_handle);
    }

    void tree::set_ansi_format(HWND tree_handle) {
        TreeView_SetUnicodeFormat(tree_handle, FALSE);
    }

    void tree::set_unicode_format(HWND tree_handle) {
        TreeView_SetUnicodeFormat(tree_handle, TRUE);
    }

    HWND tree::get_tool_tips(HWND tree_handle) {
        return TreeView_GetToolTips(tree_handle);
    }

    HWND tree::set_tool_tips(HWND tree_handle, HWND tool_tips_handle) {
        return TreeView_SetToolTips(tree_handle, tool_tips_handle);
    }

    TreeExtendStyle tree::get_extend_style(HWND tree_handle) {
        return static_cast<TreeExtendStyle>(
                TreeView_GetExtendedStyle(tree_handle));
    }

    bool tree::set_extend_style(HWND tree_handle,
                                TreeExtendStyle style,
                                TreeExtendStyle mask) {
        return TreeView_SetExtendedStyle(tree_handle,
                                         static_cast<uint32_t>(style),
                                         static_cast<uint32_t>(mask)) == S_OK;
    }

    uint32_t tree::get_indent(HWND tree_handle) {
        return TreeView_GetIndent(tree_handle);
    }

    void tree::set_indent(HWND tree_handle, uint32_t indent) {
        TreeView_SetIndent(tree_handle, indent);
    }

    uint32_t tree::get_scroll_time(HWND tree_handle) {
        return TreeView_GetScrollTime(tree_handle);
    }

    uint32_t tree::set_scroll_time(HWND tree_handle, uint32_t milli_seconds) {
        return TreeView_SetScrollTime(tree_handle, milli_seconds);
    }

    int32_t tree::get_item_height(HWND tree_handle) {
        return TreeView_GetItemHeight(tree_handle);
    }

    int32_t tree::set_item_height(HWND tree_handle, int32_t height) {
        return TreeView_SetItemHeight(tree_handle, height);
    }

    TreeItemState tree::get_item_state(HWND tree_handle,
                                       HTREEITEM tree_item_handle,
                                       TreeItemFlag mask) {
        return static_cast<TreeItemState>(
                TreeView_GetItemState(tree_handle, tree_item_handle,
                                      static_cast<uint32_t>(mask)));
    }

    void tree::set_item_state(HWND tree_handle,
                              HTREEITEM tree_item_handle,
                              TreeItemState state,
                              TreeItemState mask) {
        TreeView_SetItemState(tree_handle, tree_item_handle,
                              static_cast<uint32_t>(state),
                              static_cast<uint32_t>(mask));
    }

    TreeItemCheckState tree::get_check_state(HWND tree_handle,
                                             HTREEITEM tree_item_handle) {
        return static_cast<TreeItemCheckState>(
                TreeView_GetCheckState(tree_handle, tree_item_handle));
    }

    void tree::set_check_state(HWND tree_handle, HTREEITEM tree_item_handle) {
        TreeView_SetCheckState(tree_handle, tree_item_handle, TRUE);
    }

    void tree::set_uncheck_state(HWND tree_handle, HTREEITEM tree_item_handle) {
        TreeView_SetCheckState(tree_handle, tree_item_handle, FALSE);
    }

    HIMAGELIST tree::get_image_list(HWND tree_handle, TreeImageListType type) {
        return TreeView_GetImageList(tree_handle, static_cast<int32_t>(type));
    }

    HIMAGELIST tree::set_image_list(HWND tree_handle,
                                    HIMAGELIST image_list_handle,
                                    TreeImageListType type) {
        return TreeView_SetImageList(tree_handle, image_list_handle,
                                     static_cast<int32_t>(type));
    }

    bool tree::get_item(HWND tree_handle, TVITEMW *item) {
        return TreeView_GetItem(tree_handle, item);
    }

    bool tree::set_item(HWND tree_handle, TVITEMW *item) {
        return TreeView_SetItem(tree_handle, item);
    }

    bool tree::get_item_rect(HWND tree_handle,
                             HTREEITEM tree_item_handle,
                             RECT *rect,
                             bool include_text_only) {
        return TreeView_GetItemRect(tree_handle, tree_item_handle, rect,
                                    include_text_only ? TRUE : FALSE);
    }

    bool tree::get_item_part_rect(HWND tree_handle,
                                  HTREEITEM tree_item_handle,
                                  RECT *rect) {
        TVGETITEMPARTRECTINFO info;
        info.hti = tree_item_handle;
        info.prc = rect;
        info.partID = TVGIPR_BUTTON;
        return SendMessageW(tree_handle, TVM_GETITEMPARTRECT, 0,
                            reinterpret_cast<LPARAM>(&info));
    }

    HTREEITEM tree::get_first_visible(HWND tree_handle) {
        return TreeView_GetFirstVisible(tree_handle);
    }

    bool tree::set_first_visible(HWND tree_handle, HTREEITEM tree_item_handle) {
        return TreeView_SelectSetFirstVisible(tree_handle, tree_item_handle);
    }

    HTREEITEM tree::get_curr_select(HWND tree_handle) {
        return TreeView_GetSelection(tree_handle);
    }

    bool tree::select(HWND tree_handle,
                      HTREEITEM tree_item_handle,
                      TreeOpFlag flag) {
        return TreeView_Select(tree_handle, tree_item_handle,
                               static_cast<uint32_t>(flag));
    }

    bool tree::select_item(HWND tree_handle, HTREEITEM tree_item_handle) {
        return TreeView_SelectItem(tree_handle, tree_item_handle);
    }

    uint32_t tree::get_selected_count(HWND tree_handle) {
        return TreeView_GetSelectedCount(tree_handle);
    }

    HTREEITEM tree::get_next_selected(HWND tree_handle,
                                      HTREEITEM tree_item_handle) {
        return TreeView_GetNextSelected(tree_handle, tree_item_handle);
    }

    bool tree::select_drop_target(HWND tree_handle,
                                  HTREEITEM tree_item_handle) {
        return TreeView_SelectDropTarget(tree_handle, tree_item_handle);
    }

    HTREEITEM tree::get_drop_hilight(HWND tree_handle) {
        return TreeView_GetDropHilight(tree_handle);
    }

    HTREEITEM tree::get_child(HWND tree_handle, HTREEITEM tree_item_handle) {
        return TreeView_GetChild(tree_handle, tree_item_handle);
    }

    HTREEITEM tree::get_parent(HWND tree_handle, HTREEITEM tree_item_handle) {
        return TreeView_GetParent(tree_handle, tree_item_handle);
    }

    HTREEITEM tree::get_root(HWND tree_handle) {
        return TreeView_GetRoot(tree_handle);
    }

    HTREEITEM tree::get_next_sibling(HWND tree_handle,
                                     HTREEITEM tree_item_handle) {
        return TreeView_GetNextSibling(tree_handle, tree_item_handle);
    }

    HTREEITEM tree::get_prev_sibling(HWND tree_handle,
                                     HTREEITEM tree_item_handle) {
        return TreeView_GetPrevSibling(tree_handle, tree_item_handle);
    }

    HTREEITEM tree::get_next_item(HWND tree_handle,
                                  HTREEITEM tree_item_handle,
                                  TreeOpFlag flag) {
        return TreeView_GetNextItem(tree_handle, tree_item_handle,
                                    static_cast<uint32_t>(flag));
    }

    HTREEITEM tree::get_next_visible(HWND tree_handle,
                                     HTREEITEM tree_item_handle) {
        return TreeView_GetNextVisible(tree_handle, tree_item_handle);
    }

    HTREEITEM tree::get_prev_visible(HWND tree_handle,
                                     HTREEITEM tree_item_handle) {
        return TreeView_GetPrevVisible(tree_handle, tree_item_handle);
    }

    HTREEITEM tree::get_last_visible(HWND tree_handle) {
        return TreeView_GetLastVisible(tree_handle);
    }

    uint32_t tree::get_count(HWND tree_handle) {
        return TreeView_GetCount(tree_handle);
    }

    uint32_t tree::get_visible_count(HWND tree_handle) {
        return TreeView_GetVisibleCount(tree_handle);
    }

    HWND tree::get_edit_control(HWND tree_handle) {
        return TreeView_GetEditControl(tree_handle);
    }

    bool tree::get_increment_search_string(HWND tree_handle,
                                           std::string &text,
                                           helper::CodePage code_page) {
        auto temp = helper::convert::str_to_wstr(text, code_page);
        return TreeView_GetISearchString(tree_handle, temp.data());
    }

    bool tree::get_increment_search_string(HWND tree_handle,
                                           std::wstring &text) {
        return TreeView_GetISearchString(tree_handle, text.data());
    }

    void tree::set_auto_scroll_info(HWND tree_handle,
                                    uint32_t pixel_per_sec,
                                    uint32_t update_time_ms) {
        TreeView_SetAutoScrollInfo(tree_handle, pixel_per_sec, update_time_ms);
    }

    std::pair<uint16_t, uint16_t>
    tree::set_left_border(HWND tree_handle, uint16_t left, uint16_t top) {
        const uint32_t result =
                TreeView_SetBorder(tree_handle, TVSBF_XBORDER, left, top);
        return std::make_pair(LOWORD(result), HIWORD(result));
    }

    std::pair<uint16_t, uint16_t>
    tree::set_top_border(HWND tree_handle, uint16_t left, uint16_t top) {
        const uint32_t result =
                TreeView_SetBorder(tree_handle, TVSBF_YBORDER, left, top);
        return std::make_pair(LOWORD(result), HIWORD(result));
    }

    bool tree::set_hot(HWND tree_handle, HTREEITEM tree_item_handle) {
        return TreeView_SetHot(tree_handle, tree_item_handle);
    }

    bool tree::set_insert_mark(HWND tree_handle,
                               HTREEITEM tree_item_handle,
                               bool insert_after) {
        return TreeView_SetInsertMark(tree_handle, tree_item_handle,
                                      insert_after ? TRUE : FALSE);
    }

    HIMAGELIST tree::create_drag_image(HWND tree_handle,
                                       HTREEITEM tree_item_handle) {
        return TreeView_CreateDragImage(tree_handle, tree_item_handle);
    }

    bool tree::delete_all_items(HWND tree_handle) {
        return TreeView_DeleteAllItems(tree_handle);
    }

    bool tree::delete_item(HWND tree_handle, HTREEITEM tree_item_handle) {
        return TreeView_DeleteItem(tree_handle, tree_item_handle);
    }

    HWND tree::edit_label(HWND tree_handle, HTREEITEM tree_item_handle) {
        return TreeView_EditLabel(tree_handle, tree_item_handle);
    }

    bool tree::end_edit_label_now(HWND tree_handle, bool save) {
        return TreeView_EndEditLabelNow(tree_handle, save ? FALSE : TRUE);
    }

    bool tree::ensure_visible(HWND tree_handle, HTREEITEM tree_item_handle) {
        return TreeView_EnsureVisible(tree_handle, tree_item_handle);
    }

    bool tree::expand(HWND tree_handle,
                      HTREEITEM tree_item_handle,
                      TreeExpandFlag flag) {
        return TreeView_Expand(tree_handle, tree_item_handle,
                               static_cast<uint32_t>(flag));
    }

    HTREEITEM tree::hit_test(HWND tree_handle, TVHITTESTINFO *hit_test_info) {
        return TreeView_HitTest(tree_handle, hit_test_info);
    }

    HTREEITEM tree::insert_item(HWND tree_handle,
                                TVINSERTSTRUCTW *insert_struct) {
        return TreeView_InsertItem(tree_handle, insert_struct);
    }

    HTREEITEM tree::map_access_id_to_tree_item_handle(HWND tree_handle,
                                                      uint32_t id) {
        return TreeView_MapAccIDToHTREEITEM(tree_handle, id);
    }

    uint32_t
    tree::map_tree_item_handle_to_access_id(HWND tree_handle,
                                            HTREEITEM tree_item_handle) {
        return TreeView_MapHTREEITEMToAccID(tree_handle, tree_item_handle);
    }

    void tree::show_info_tip(HWND tree_handle, HTREEITEM tree_item_handle) {
        TreeView_ShowInfoTip(tree_handle, tree_item_handle);
    }

    bool tree::sort_child(HWND tree_handle,
                          HTREEITEM tree_item_handle,
                          bool recursive) {
        return TreeView_SortChildren(tree_handle, tree_item_handle,
                                     recursive ? TRUE : FALSE);
    }

    bool tree::sort_child_callback(HWND tree_handle, TVSORTCB *sort) {
        return TreeView_SortChildrenCB(tree_handle, sort, 0);
    }

    uint32_t tree::err_code() const {
        return error_code;
    }

    std::string tree::err_string() const {
        std::string result = helper::convert::err_string(error_code);
        return result;
    }

    std::wstring tree::err_wstring() const {
        std::wstring result = helper::convert::err_wstring(error_code);
        return result;
    }
} // namespace YanLib::ui::components
