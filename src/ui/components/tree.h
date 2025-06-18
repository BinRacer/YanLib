/* clang-format off */
/*
 * @file tree.h
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
#ifndef TREE_H
#define TREE_H
#ifndef UNICODE
#define UNICODE
#endif
#ifndef _UNICODE
#define _UNICODE
#endif
#include <Windows.h>
#include <CommCtrl.h>
#include <minwindef.h>
#include <windef.h>
#include <cstdint>
#include <string>
#include <vector>
#include "sync/rwlock.h"
#include "helper/convert.h"
#include "ui/core/core.h"
#include "components.h"
#pragma comment(lib, "ComCtl32.Lib")
#pragma comment(linker, "\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#pragma comment(lib, "User32.Lib")
namespace YanLib::ui::components {
    class tree {
    private:
        std::vector<HWND> tree_handles = {};
        sync::rwlock tree_rwlock = {};
        uint32_t error_code = 0;

    public:
        tree(const tree &other) = delete;

        tree(tree &&other) = delete;

        tree &operator=(const tree &other) = delete;

        tree &operator=(tree &&other) = delete;

        tree();

        ~tree();

        HWND create(uintptr_t tree_id,
                    HWND parent_window_handle,
                    LPARAM lparam,
                    int32_t x,
                    int32_t y,
                    int32_t width,
                    int32_t height,
                    TreeStyle style = TreeStyle::HasLines |
                            TreeStyle::EditLabels | TreeStyle::HasButtons |
                            TreeStyle::LinesAtRoot | TreeStyle::InfoTip |
                            TreeStyle::ShowSelectAlways |
                            TreeStyle::SingleExpand | TreeStyle::TrackSelect,
                    core::WindowStyle window_style = core::WindowStyle::Child |
                            core::WindowStyle::Visible | core::WindowStyle::Border);

        HWND create(const char *tree_name,
                    uintptr_t tree_id,
                    HWND parent_window_handle,
                    LPARAM lparam,
                    int32_t x,
                    int32_t y,
                    int32_t width,
                    int32_t height,
                    TreeStyle style = TreeStyle::HasLines |
                            TreeStyle::EditLabels | TreeStyle::HasButtons |
                            TreeStyle::LinesAtRoot | TreeStyle::InfoTip |
                            TreeStyle::ShowSelectAlways |
                            TreeStyle::SingleExpand | TreeStyle::TrackSelect,
                    core::WindowStyle window_style = core::WindowStyle::Child |
                            core::WindowStyle::Visible | core::WindowStyle::Border);

        HWND create(const wchar_t *tree_name,
                    uintptr_t tree_id,
                    HWND parent_window_handle,
                    LPARAM lparam,
                    int32_t x,
                    int32_t y,
                    int32_t width,
                    int32_t height,
                    TreeStyle style = TreeStyle::HasLines |
                            TreeStyle::EditLabels | TreeStyle::HasButtons |
                            TreeStyle::LinesAtRoot | TreeStyle::InfoTip |
                            TreeStyle::ShowSelectAlways |
                            TreeStyle::SingleExpand | TreeStyle::TrackSelect,
                    core::WindowStyle window_style = core::WindowStyle::Child |
                            core::WindowStyle::Visible | core::WindowStyle::Border);

        bool destroy(HWND tree_handle);

        COLORREF get_background_color(HWND tree_handle);

        COLORREF set_background_color(HWND tree_handle, COLORREF color);

        COLORREF get_text_color(HWND tree_handle);

        COLORREF set_text_color(HWND tree_handle, COLORREF color);

        COLORREF get_line_color(HWND tree_handle);

        COLORREF set_line_color(HWND tree_handle, COLORREF color);

        COLORREF get_insert_mark_color(HWND tree_handle);

        COLORREF set_insert_mark_color(HWND tree_handle, COLORREF color);

        bool is_ansi_format(HWND tree_handle);

        bool is_unicode_format(HWND tree_handle);

        void set_ansi_format(HWND tree_handle);

        void set_unicode_format(HWND tree_handle);

        HWND get_tool_tips(HWND tree_handle);

        HWND set_tool_tips(HWND tree_handle, HWND tool_tips_handle);

        TreeExtendStyle get_extend_style(HWND tree_handle);

        bool set_extend_style(HWND tree_handle,
                              TreeExtendStyle style,
                              TreeExtendStyle mask);

        uint32_t get_indent(HWND tree_handle);

        void set_indent(HWND tree_handle, uint32_t indent);

        uint32_t get_scroll_time(HWND tree_handle);

        uint32_t set_scroll_time(HWND tree_handle, uint32_t milli_seconds);

        int32_t get_item_height(HWND tree_handle);

        int32_t set_item_height(HWND tree_handle, int32_t height);

        TreeItemState get_item_state(HWND tree_handle,
                                     HTREEITEM tree_item_handle,
                                     TreeItemFlag mask);

        void set_item_state(HWND tree_handle,
                            HTREEITEM tree_item_handle,
                            TreeItemState state,
                            TreeItemState mask);

        TreeItemCheckState get_check_state(HWND tree_handle,
                                           HTREEITEM tree_item_handle);

        void set_check_state(HWND tree_handle, HTREEITEM tree_item_handle);

        void set_uncheck_state(HWND tree_handle, HTREEITEM tree_item_handle);

        HIMAGELIST
        get_image_list(HWND tree_handle,
                       TreeImageListType type = TreeImageListType::Normal);

        HIMAGELIST
        set_image_list(HWND tree_handle,
                       HIMAGELIST image_list_handle,
                       TreeImageListType type = TreeImageListType::Normal);

        bool get_item(HWND tree_handle, TVITEMW *item);

        bool set_item(HWND tree_handle, TVITEMW *item);

        bool get_item_rect(HWND tree_handle,
                           HTREEITEM tree_item_handle,
                           RECT *rect,
                           bool include_text_only = false);

        bool get_item_part_rect(HWND tree_handle,
                                HTREEITEM tree_item_handle,
                                RECT *rect);

        HTREEITEM get_first_visible(HWND tree_handle);

        bool set_first_visible(HWND tree_handle, HTREEITEM tree_item_handle);

        HTREEITEM get_curr_select(HWND tree_handle);

        bool
        select(HWND tree_handle, HTREEITEM tree_item_handle, TreeOpFlag flag);

        bool select_item(HWND tree_handle, HTREEITEM tree_item_handle);

        uint32_t get_selected_count(HWND tree_handle);

        HTREEITEM get_next_selected(HWND tree_handle,
                                    HTREEITEM tree_item_handle);

        bool select_drop_target(HWND tree_handle, HTREEITEM tree_item_handle);

        HTREEITEM get_drop_hilight(HWND tree_handle);

        HTREEITEM get_child(HWND tree_handle, HTREEITEM tree_item_handle);

        HTREEITEM get_parent(HWND tree_handle, HTREEITEM tree_item_handle);

        HTREEITEM get_root(HWND tree_handle);

        HTREEITEM get_next_sibling(HWND tree_handle,
                                   HTREEITEM tree_item_handle);

        HTREEITEM get_prev_sibling(HWND tree_handle,
                                   HTREEITEM tree_item_handle);

        HTREEITEM get_next_item(HWND tree_handle,
                                HTREEITEM tree_item_handle,
                                TreeOpFlag flag);

        HTREEITEM get_next_visible(HWND tree_handle,
                                   HTREEITEM tree_item_handle);

        HTREEITEM get_prev_visible(HWND tree_handle,
                                   HTREEITEM tree_item_handle);

        HTREEITEM get_last_visible(HWND tree_handle);

        uint32_t get_count(HWND tree_handle);

        uint32_t get_visible_count(HWND tree_handle);

        HWND get_edit_control(HWND tree_handle);

        bool get_increment_search_string(
                HWND tree_handle,
                std::string &text,
                helper::CodePage code_page = helper::curr_code_page());

        bool get_increment_search_string(HWND tree_handle, std::wstring &text);

        void set_auto_scroll_info(HWND tree_handle,
                                  uint32_t pixel_per_sec,
                                  uint32_t update_time_ms);

        // std::pair<horiz, vert>
        std::pair<uint16_t, uint16_t>
        set_left_border(HWND tree_handle, uint16_t left, uint16_t top);

        // std::pair<horiz, vert>
        std::pair<uint16_t, uint16_t>
        set_top_border(HWND tree_handle, uint16_t left, uint16_t top);

        bool set_hot(HWND tree_handle, HTREEITEM tree_item_handle);

        bool set_insert_mark(HWND tree_handle,
                             HTREEITEM tree_item_handle,
                             bool insert_after = true);

        HIMAGELIST create_drag_image(HWND tree_handle,
                                     HTREEITEM tree_item_handle);

        bool delete_all_items(HWND tree_handle);

        bool delete_item(HWND tree_handle, HTREEITEM tree_item_handle);

        HWND edit_label(HWND tree_handle, HTREEITEM tree_item_handle);

        bool end_edit_label_now(HWND tree_handle, bool save = true);

        bool ensure_visible(HWND tree_handle, HTREEITEM tree_item_handle);

        bool expand(HWND tree_handle,
                    HTREEITEM tree_item_handle,
                    TreeExpandFlag flag);

        HTREEITEM hit_test(HWND tree_handle, TVHITTESTINFO *hit_test_info);

        HTREEITEM insert_item(HWND tree_handle, TVINSERTSTRUCTW *insert_struct);

        HTREEITEM map_access_id_to_tree_item_handle(HWND tree_handle,
                                                    uint32_t id);

        uint32_t map_tree_item_handle_to_access_id(HWND tree_handle,
                                                   HTREEITEM tree_item_handle);

        void show_info_tip(HWND tree_handle, HTREEITEM tree_item_handle);

        bool sort_child(HWND tree_handle,
                        HTREEITEM tree_item_handle,
                        bool recursive = true);

        bool sort_child_callback(HWND tree_handle, TVSORTCB *sort);

        [[nodiscard]] uint32_t err_code() const;

        [[nodiscard]] std::string err_string() const;

        [[nodiscard]] std::wstring err_wstring() const;
    };
} // namespace YanLib::ui::components
#endif // TREE_H
