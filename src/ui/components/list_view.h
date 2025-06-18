/* clang-format off */
/*
 * @file list_view.h
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
#ifndef LIST_VIEW_H
#define LIST_VIEW_H
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
    class list_view {
    private:
        std::vector<HWND> list_view_handles = {};
        sync::rwlock list_view_rwlock = {};
        uint32_t error_code = 0;

    public:
        list_view(const list_view &other) = delete;

        list_view(list_view &&other) = delete;

        list_view &operator=(const list_view &other) = delete;

        list_view &operator=(list_view &&other) = delete;

        list_view();

        ~list_view();

        HWND create(uintptr_t list_view_id,
                    HWND parent_window_handle,
                    LPARAM lparam,
                    int32_t x,
                    int32_t y,
                    int32_t width,
                    int32_t height,
                    ListViewStyle style = ListViewStyle::Report |
                            ListViewStyle::EditLabels,
                    core::WindowStyle window_style = core::WindowStyle::Child |
                            core::WindowStyle::Visible);

        HWND create(const char *list_view_name,
                    uintptr_t list_view_id,
                    HWND parent_window_handle,
                    LPARAM lparam,
                    int32_t x,
                    int32_t y,
                    int32_t width,
                    int32_t height,
                    ListViewStyle style = ListViewStyle::Report |
                            ListViewStyle::EditLabels,
                    core::WindowStyle window_style = core::WindowStyle::Child |
                            core::WindowStyle::Visible);

        HWND create(const wchar_t *list_view_name,
                    uintptr_t list_view_id,
                    HWND parent_window_handle,
                    LPARAM lparam,
                    int32_t x,
                    int32_t y,
                    int32_t width,
                    int32_t height,
                    ListViewStyle style = ListViewStyle::Report |
                            ListViewStyle::EditLabels,
                    core::WindowStyle window_style = core::WindowStyle::Child |
                            core::WindowStyle::Visible);

        bool destroy(HWND list_view_handle);

        HWND edit_label(HWND list_view_handle, int32_t index);

        void cancel_edit_label(HWND list_view_handle);

        bool delete_item(HWND list_view_handle, int32_t index);

        bool delete_column(HWND list_view_handle, int32_t column_index);

        bool delete_all_items(HWND list_view_handle);

        HIMAGELIST
        create_drag_image(HWND list_view_handle,
                          POINT *left_top,
                          int32_t index);

        // std::pair<width, height>
        std::pair<uint32_t, uint32_t>
        approximate_view_rect(HWND list_view_handle,
                              int32_t width = -1,
                              int32_t height = -1,
                              int32_t count = -1);

        bool arrange(HWND list_view_handle,
                     LVAlignStyle style = LVAlignStyle::Default);

        int32_t enable_group_view(HWND list_view_handle);

        int32_t disable_group_view(HWND list_view_handle);

        bool is_group_view_enabled(HWND list_view_handle);

        bool ensure_visible(HWND list_view_handle,
                            int32_t index,
                            bool entire_visible = false);

        int32_t find_item(HWND list_view_handle,
                          const LVFINDINFOW *find_info,
                          int32_t index = -1);

        COLORREF get_background_color(HWND list_view_handle);

        bool set_background_color(HWND list_view_handle, COLORREF color);

        bool get_background_image(HWND list_view_handle, LVBKIMAGEW *image);

        bool set_background_image(HWND list_view_handle, LVBKIMAGEW *image);

        LVItemState get_callback_mask(HWND list_view_handle);

        bool set_callback_mask(HWND list_view_handle, LVItemState mask);

        bool is_checked(HWND list_view_handle, uint32_t index);

        void set_check(HWND list_view_handle, uint32_t index);

        void unset_check(HWND list_view_handle, uint32_t index);

        bool get_column(HWND list_view_handle,
                        LVCOLUMNW *column,
                        int32_t column_index);

        bool set_column(HWND list_view_handle,
                        const LVCOLUMNW *column,
                        int32_t column_index);

        bool get_column_order(HWND list_view_handle,
                              std::vector<int32_t> &order);

        void set_column_order(HWND list_view_handle,
                              std::vector<int32_t> &order);

        int32_t get_column_width(HWND list_view_handle, int32_t column_index);

        bool set_column_width(HWND list_view_handle,
                              int32_t column_index,
                              int32_t width = LVSCW_AUTOSIZE_USEHEADER);

        int32_t get_count_per_page(HWND list_view_handle);

        HWND get_edit_control(HWND list_view_handle);

        bool
        get_empty_text(HWND list_view_handle,
                       std::string &text,
                       helper::CodePage code_page = helper::curr_code_page());

        bool get_empty_text(HWND list_view_handle, std::wstring &text);

        ListViewExtendStyle get_extended_style(HWND list_view_handle);

        void set_extended_style(HWND list_view_handle,
                                ListViewExtendStyle style);

        void set_extended_style(HWND list_view_handle,
                                ListViewExtendStyle style,
                                ListViewExtendStyle mask /* 0 */);

        int32_t get_focused_group(HWND list_view_handle);

        void get_footer_info(HWND list_view_handle, LVFOOTERINFO *footer_info);

        bool get_footer_item(HWND list_view_handle,
                             LVFOOTERITEM *footer_item,
                             uint32_t index);

        bool
        get_footer_item_rect(HWND list_view_handle, RECT *rect, uint32_t index);

        bool get_footer_rect(HWND list_view_handle, RECT *rect);

        int32_t get_group_count(HWND list_view_handle);

        HIMAGELIST get_group_header_image_list(HWND list_view_handle);

        HIMAGELIST set_group_header_image_list(HWND list_view_handle,
                                               HIMAGELIST image_list_handle);

        int32_t
        get_group_info(HWND list_view_handle, LVGROUP *group, int32_t index);

        int32_t
        set_group_info(HWND list_view_handle, LVGROUP *group, int32_t index);

        bool get_group_info_by_index(HWND list_view_handle,
                                     LVGROUP *group,
                                     int32_t index);

        void get_group_metrics(HWND list_view_handle,
                               LVGROUPMETRICS *group_metrics);

        void set_group_metrics(HWND list_view_handle,
                               LVGROUPMETRICS *group_metrics);

        bool get_group_rect(HWND list_view_handle,
                            RECT *rect,
                            int32_t index,
                            GroupRectType type = GroupRectType::Group);

        GroupState get_group_state(HWND list_view_handle,
                                   uint32_t index,
                                   GroupState mask = GroupState::Normal);
        bool set_group_state(HWND list_view_handle,
                             GroupState state,
                             uint32_t index,
                             GroupState mask = GroupState::Normal);

        HWND get_header(HWND list_view_handle);

        HCURSOR get_hot_cursor(HWND list_view_handle);

        HCURSOR set_hot_cursor(HWND list_view_handle, HCURSOR cursor_handle);

        int32_t get_hot_item(HWND list_view_handle);

        int32_t set_hot_item(HWND list_view_handle, int32_t index);

        uint32_t get_hover_time(HWND list_view_handle);

        void set_hover_time(HWND list_view_handle, uint32_t milli_seconds);

        HIMAGELIST get_image_list(HWND list_view_handle, LVILStyle style);

        HIMAGELIST set_image_list(HWND list_view_handle,
                                  HIMAGELIST image_list_handle,
                                  LVILStyle style);

        bool get_insert_mark(HWND list_view_handle, LVINSERTMARK *insert_mark);

        bool set_insert_mark(HWND list_view_handle, LVINSERTMARK *insert_mark);

        COLORREF get_insert_mark_color(HWND list_view_handle);

        COLORREF set_insert_mark_color(HWND list_view_handle, COLORREF color);

        bool get_insert_mark_rect(HWND list_view_handle, RECT *rect);

        int32_t get_increment_search_string(
                HWND list_view_handle,
                std::string &text,
                helper::CodePage code_page = helper::curr_code_page());

        int32_t get_increment_search_string(HWND list_view_handle,
                                            std::wstring &text);

        bool get_item(HWND list_view_handle, LVITEMW *item);

        bool set_item(HWND list_view_handle, const LVITEMW *item);

        int32_t get_item_count(HWND list_view_handle);

        void set_item_count(HWND list_view_handle, int32_t count);

        void
        set_item_count(HWND list_view_handle, int32_t count, LVICFlag flag);

        bool get_item_index_rect(HWND list_view_handle,
                                 LVITEMINDEX *item_index,
                                 int32_t index,
                                 LVIRCode code,
                                 RECT *rect);

        bool get_item_pos(HWND list_view_handle, POINT *point, int32_t index);

        bool set_item_pos(HWND list_view_handle, POINT point, int32_t index);

        void set_item_pos32(HWND list_view_handle, POINT point, int32_t index);

        bool get_item_rect(HWND list_view_handle,
                           RECT *rect,
                           int32_t index,
                           LVIRCode code);

        // std::pair<horizontal, vertical>
        std::pair<uint32_t, uint32_t> get_item_spacing(HWND list_view_handle,
                                                       bool small_icon = false);

        LVItemState
        get_item_state(HWND list_view_handle, int32_t index, LVItemState mask);

        void set_item_state(HWND list_view_handle,
                            LVItemState state,
                            int32_t index,
                            LVItemState mask);

        void
        get_item_text(HWND list_view_handle,
                      std::string &text,
                      int32_t item_index,
                      int32_t sub_item_index,
                      helper::CodePage code_page = helper::curr_code_page());

        void get_item_text(HWND list_view_handle,
                           std::wstring &text,
                           int32_t item_index,
                           int32_t sub_item_index);

        void
        set_item_text(HWND list_view_handle,
                      const std::string &text,
                      int32_t item_index,
                      int32_t sub_item_index,
                      helper::CodePage code_page = helper::curr_code_page());

        void set_item_text(HWND list_view_handle,
                           std::wstring &text,
                           int32_t item_index,
                           int32_t sub_item_index);

        int32_t get_next_item(HWND list_view_handle,
                              int32_t index,
                              LVNIFlag flag = LVNIFlag::All);

        bool get_next_item_index(HWND list_view_handle,
                                 LVITEMINDEX *item_index,
                                 LVNIFlag flag = LVNIFlag::All);

        void get_number_of_work_areas(HWND list_view_handle,
                                      uint32_t *num_work_areas);

        bool get_origin(HWND list_view_handle, POINT *point);

        COLORREF get_outline_color(HWND list_view_handle);

        COLORREF set_outline_color(HWND list_view_handle, COLORREF color);

        uint32_t get_selected_column(HWND list_view_handle);

        void set_selected_column(HWND list_view_handle, uint32_t column);

        uint32_t get_selected_count(HWND list_view_handle);

        int32_t get_selection_mark(HWND list_view_handle);

        int32_t set_selection_mark(HWND list_view_handle, int32_t mark);

        int32_t
        get_string_width(HWND list_view_handle,
                         const std::string &text,
                         helper::CodePage code_page = helper::curr_code_page());

        int32_t get_string_width(HWND list_view_handle,
                                 const std::wstring &text);

        bool get_sub_item_rect(HWND list_view_handle,
                               RECT *rect,
                               int32_t item_index,
                               int32_t sub_item_index,
                               LVIRCode code);

        COLORREF get_text_background_color(HWND list_view_handle);

        bool set_text_background_color(HWND list_view_handle, COLORREF color);

        COLORREF get_text_color(HWND list_view_handle);

        bool set_text_color(HWND list_view_handle, COLORREF color);

        void get_tile_info(HWND list_view_handle, LVTILEINFO *tile_info);

        bool set_tile_info(HWND list_view_handle, LVTILEINFO *tile_info);

        void get_tile_view_info(HWND list_view_handle,
                                LVTILEVIEWINFO *tile_view_info);

        bool set_tile_view_info(HWND list_view_handle,
                                LVTILEVIEWINFO *tile_view_info);

        HWND get_tool_tips(HWND list_view_handle);

        HWND set_tool_tips(HWND list_view_handle, HWND tool_tips_handle);

        int32_t get_top_index(HWND list_view_handle);

        bool is_ansi_format(HWND list_view_handle);

        bool is_unicode_format(HWND list_view_handle);

        void set_ansi_format(HWND list_view_handle);

        void set_unicode_format(HWND list_view_handle);

        uint32_t get_view(HWND list_view_handle);

        bool set_view(HWND list_view_handle, uint32_t view);

        bool get_view_rect(HWND list_view_handle, RECT *rect);

        void get_work_areas(HWND list_view_handle,
                            std::vector<RECT> &work_areas);

        void set_work_areas(HWND list_view_handle,
                            std::vector<RECT> &work_areas);

        bool contains_group(HWND list_view_handle, int32_t index);

        int32_t hit_test(HWND list_view_handle, LVHITTESTINFO *hit_test_info);

        int32_t hit_test2(HWND list_view_handle, LVHITTESTINFO *hit_test_info);

        int32_t insert_column(HWND list_view_handle,
                              const LVCOLUMNW *column,
                              int32_t index);

        int32_t
        insert_group(HWND list_view_handle, LVGROUP *group, int32_t index);

        void insert_group_sorted(HWND list_view_handle,
                                 LVINSERTGROUPSORTED *insert_group_sorted);

        int32_t insert_item(HWND list_view_handle, const LVITEMW *item);

        bool insert_mark_hit_test(HWND list_view_handle,
                                  POINT *point,
                                  LVINSERTMARK *insert_mark);

        bool is_item_visible(HWND list_view_handle, uint32_t index);

        uint32_t map_id_to_index(HWND list_view_handle, uint32_t id);

        uint32_t map_index_to_id(HWND list_view_handle, uint32_t index);

        void
        move_group(HWND list_view_handle, int32_t index_from, int32_t index_to);

        void move_item_to_group(HWND list_view_handle,
                                int32_t item_index,
                                int32_t group_index);

        bool redraw_items(HWND list_view_handle, int32_t first, int32_t last);

        void remove_all_groups(HWND list_view_handle);

        int32_t remove_group(HWND list_view_handle, int32_t index);

        bool scroll(HWND list_view_handle, int32_t horiz, int32_t vert);

        uint32_t
        set_icon_spacing(HWND list_view_handle, int32_t width, int32_t height);

        bool set_info_tip(HWND list_view_handle, LVSETINFOTIP *set_info_tip);

        bool set_item_index_state(HWND list_view_handle,
                                  LVITEMINDEX *item_index,
                                  LVItemState state,
                                  LVItemState mask);

        bool
        sort_groups(HWND list_view_handle, PFNLVGROUPCOMPARE fn, void *param3);

        // int CALLBACK PFNLVCOMPARE(LPARAM lParam1, LPARAM lParam2, LPARAM
        // lParam3);
        bool sort_items(HWND list_view_handle, PFNLVCOMPARE fn, void *param3);

        bool sort_items2(HWND list_view_handle, PFNLVCOMPARE fn, void *param3);

        int32_t sub_item_hit_test(HWND list_view_handle,
                                  LVHITTESTINFO *hit_test_info);

        int32_t sub_item_hit_test2(HWND list_view_handle,
                                   LVHITTESTINFO *hit_test_info);

        bool update(HWND list_view_handle, int32_t index);

        [[nodiscard]] uint32_t err_code() const;

        [[nodiscard]] std::string err_string() const;

        [[nodiscard]] std::wstring err_wstring() const;
    };
} // namespace YanLib::ui::components
#endif // LIST_VIEW_H
