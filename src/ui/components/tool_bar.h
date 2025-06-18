/* clang-format off */
/*
 * @file tool_bar.h
 * @date 2025-06-01
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
#ifndef TOOL_BAR_H
#define TOOL_BAR_H
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
#include <oleidl.h>
#include <cstdint>
#include <string>
#include <vector>
#include "sync/rwlock.h"
#include "helper/convert.h"
#include "ui/core/core.h"
#include "ui/gdi/gdi.h"
#include "components.h"
#pragma comment(lib, "ComCtl32.Lib")
#pragma comment(linker, "\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#pragma comment(lib, "User32.Lib")
namespace YanLib::ui::components {
    class tool_bar {
    private:
        std::vector<HWND> tool_bar_handles = {};
        sync::rwlock tool_bar_rwlock = {};
        uint32_t error_code = 0;

    public:
        tool_bar(const tool_bar &other) = delete;

        tool_bar(tool_bar &&other) = delete;

        tool_bar &operator=(const tool_bar &other) = delete;

        tool_bar &operator=(tool_bar &&other) = delete;

        tool_bar();

        ~tool_bar();

        HWND create(HWND parent_window_handle,
                    LPARAM lparam,
                    int32_t x = 0,
                    int32_t y = 0,
                    int32_t width = 0,
                    int32_t height = 0,
                    ToolBarStyle style = ToolBarStyle::Flat |
                            ToolBarStyle::Transparent | ToolBarStyle::ToolTips |
                            ToolBarStyle::AltDrag | ToolBarStyle::CustomErase |
                            ToolBarStyle::RegisterDrop |
                            ToolBarStyle::AutoSize | CommonStyle::Top |
                            CommonStyle::NoParentAlign |
                            CommonStyle::Adjustable,
                    core::WindowStyle window_style = core::WindowStyle::Child |
                            core::WindowStyle::Visible);

        HWND create(const char *tool_bar_name,
                    HWND parent_window_handle,
                    LPARAM lparam,
                    int32_t x = 0,
                    int32_t y = 0,
                    int32_t width = 0,
                    int32_t height = 0,
                    ToolBarStyle style = ToolBarStyle::Flat |
                            ToolBarStyle::Transparent | ToolBarStyle::ToolTips |
                            ToolBarStyle::AltDrag | ToolBarStyle::CustomErase |
                            ToolBarStyle::RegisterDrop |
                            ToolBarStyle::AutoSize | CommonStyle::Top |
                            CommonStyle::NoParentAlign |
                            CommonStyle::Adjustable,
                    core::WindowStyle window_style = core::WindowStyle::Child |
                            core::WindowStyle::Visible);

        HWND create(const wchar_t *tool_bar_name,
                    HWND parent_window_handle,
                    LPARAM lparam,
                    int32_t x = 0,
                    int32_t y = 0,
                    int32_t width = 0,
                    int32_t height = 0,
                    ToolBarStyle style = ToolBarStyle::Flat |
                            ToolBarStyle::Transparent | ToolBarStyle::ToolTips |
                            ToolBarStyle::AltDrag | ToolBarStyle::CustomErase |
                            ToolBarStyle::RegisterDrop |
                            ToolBarStyle::AutoSize | CommonStyle::Top |
                            CommonStyle::NoParentAlign |
                            CommonStyle::Adjustable,
                    core::WindowStyle window_style = core::WindowStyle::Child |
                            core::WindowStyle::Visible);

        bool destroy(HWND tool_bar_handle);

        HBITMAP create_mapped_bitmap(HINSTANCE instance_handle,
                                     intptr_t bitmap_id,
                                     std::vector<COLORMAP> &color_map,
                                     bool use_mask = true);

        bool is_anchor_highlight(HWND tool_bar_handle);

        void enable_anchor_highlight(HWND tool_bar_handle);

        void disable_anchor_highlight(HWND tool_bar_handle);

        bool get_color_scheme(HWND tool_bar_handle, COLORSCHEME *color_scheme);

        void set_color_scheme(HWND tool_bar_handle, COLORSCHEME *color_scheme);

        HIMAGELIST get_disabled_image_list(HWND tool_bar_handle);

        HIMAGELIST set_disabled_image_list(HWND tool_bar_handle,
                                           HIMAGELIST image_list_handle);

        HIMAGELIST get_hot_image_list(HWND tool_bar_handle);

        HIMAGELIST set_hot_image_list(HWND tool_bar_handle,
                                      HIMAGELIST image_list_handle);

        HIMAGELIST get_image_list(HWND tool_bar_handle);

        HIMAGELIST set_image_list(HWND tool_bar_handle,
                                  int64_t index,
                                  HIMAGELIST image_list_handle);

        HIMAGELIST remove_image_list(HWND tool_bar_handle, int64_t index);

        HIMAGELIST get_pressed_image_list(HWND tool_bar_handle);

        HIMAGELIST set_pressed_image_list(HWND tool_bar_handle,
                                          int64_t index,
                                          HIMAGELIST image_list_handle);

        HIMAGELIST remove_pressed_image_list(HWND tool_bar_handle,
                                             int64_t index);

        int64_t get_image_list_count(HWND tool_bar_handle);

        int64_t load_images(HWND tool_bar_handle, TBImageListID id);

        ToolBarExtendStyle get_extend_style(HWND tool_bar_handle);

        ToolBarExtendStyle set_extend_style(HWND tool_bar_handle,
                                            ToolBarExtendStyle style);

        int64_t get_hot_item(HWND tool_bar_handle);

        int64_t set_hot_item(HWND tool_bar_handle, int64_t index);

        int64_t
        set_hot_item(HWND tool_bar_handle, int64_t index, TBHotItemFlag flag);

        int64_t add_bitmap(HWND tool_bar_handle,
                           int64_t image_num,
                           TBADDBITMAP *bitmap);

        bool
        change_bitmap(HWND tool_bar_handle, int64_t index, int64_t bitmap_id);

        bool replace_bitmap(HWND tool_bar_handle, TBREPLACEBITMAP *bitmap);

        bool
        set_bitmap_size(HWND tool_bar_handle, int32_t width, int32_t height);

        bool set_bitmap_size(HWND tool_bar_handle, SIZE size);

        int64_t get_bitmap_index(HWND tool_bar_handle, int64_t bitmap_id);

        bool support_large_bitmap(HWND tool_bar_handle);

        bool add_button(HWND tool_bar_handle, std::vector<TBBUTTON> &buttons);

        bool
        insert_button(HWND tool_bar_handle, int64_t index, TBBUTTON *button);

        bool delete_button(HWND tool_bar_handle, int64_t index);

        bool
        move_button(HWND tool_bar_handle, int64_t index_from, int64_t index_to);

        int64_t get_button_count(HWND tool_bar_handle);

        int64_t get_button_info(HWND tool_bar_handle,
                                int64_t button_id,
                                TBBUTTONINFOA *button_info);

        int64_t get_button_info(HWND tool_bar_handle,
                                int64_t button_id,
                                TBBUTTONINFOW *button_info);

        bool set_button_info(HWND tool_bar_handle,
                             int64_t button_id,
                             TBBUTTONINFOA *button_info);

        bool set_button_info(HWND tool_bar_handle,
                             int64_t button_id,
                             TBBUTTONINFOW *button_info);

        bool get_button(HWND tool_bar_handle, int64_t index, TBBUTTON *button);


        int64_t
        get_button_text(HWND tool_bar_handle,
                        int64_t button_id,
                        std::string &button_text,
                        helper::CodePage code_page = helper::curr_code_page());

        int64_t get_button_text(HWND tool_bar_handle,
                                int64_t button_id,
                                std::wstring &button_text);

        // std::pair<width, height>
        std::pair<uint32_t, uint32_t> get_button_size(HWND tool_bar_handle);

        bool get_button_size(HWND tool_bar_handle, SIZE *size);

        bool
        set_button_size(HWND tool_bar_handle, uint32_t width, uint32_t height);

        bool set_button_size(HWND tool_bar_handle, SIZE size);

        bool set_button_width(HWND tool_bar_handle, uint32_t min, uint32_t max);

        bool check_button(HWND tool_bar_handle, int64_t button_id);

        bool uncheck_button(HWND tool_bar_handle, int64_t button_id);

        bool enable_button(HWND tool_bar_handle, int64_t button_id);

        bool disable_button(HWND tool_bar_handle, int64_t button_id);

        bool show_button(HWND tool_bar_handle, int64_t button_id);

        bool hide_button(HWND tool_bar_handle, int64_t button_id);

        bool mark_button(HWND tool_bar_handle, int64_t button_id);

        bool unmark_button(HWND tool_bar_handle, int64_t button_id);

        bool press_button(HWND tool_bar_handle, int64_t button_id);

        bool release_button(HWND tool_bar_handle, int64_t button_id);

        bool is_button_checked(HWND tool_bar_handle, int64_t button_id);

        bool is_button_enabled(HWND tool_bar_handle, int64_t button_id);

        bool is_button_show(HWND tool_bar_handle, int64_t button_id);

        bool is_button_hidden(HWND tool_bar_handle, int64_t button_id);

        bool is_button_highlighted(HWND tool_bar_handle, int64_t button_id);

        bool is_button_indeterminate(HWND tool_bar_handle, int64_t button_id);

        bool is_button_pressed(HWND tool_bar_handle, int64_t button_id);

        void set_button_struct_size(HWND tool_bar_handle, int64_t size);

        bool get_ideal_size(HWND tool_bar_handle, SIZE *size);

        int64_t command_to_index(HWND tool_bar_handle, int64_t command_id);

        bool get_max_size(HWND tool_bar_handle, SIZE *size);

        TBButtonState get_button_state(HWND tool_bar_handle, int64_t index);

        bool set_button_state(HWND tool_bar_handle,
                              int64_t button_id,
                              TBButtonState state);

        bool set_indeterminate(HWND tool_bar_handle, int64_t button_id);

        bool clear_indeterminate(HWND tool_bar_handle, int64_t button_id);

        void get_insert_mark(HWND tool_bar_handle, TBINSERTMARK *insert_mark);

        void set_insert_mark(HWND tool_bar_handle, TBINSERTMARK *insert_mark);

        COLORREF get_insert_mark_color(HWND tool_bar_handle);

        COLORREF set_insert_mark_color(HWND tool_bar_handle, COLORREF color);

        bool insert_mark_hit_test(HWND tool_bar_handle,
                                  POINT *point,
                                  TBINSERTMARK *insert_mark);

        void get_item_drop_down_rect(HWND tool_bar_handle,
                                     int64_t index,
                                     RECT *rect);

        bool get_item_rect(HWND tool_bar_handle, int64_t index, RECT *rect);

        bool
        get_button_rect(HWND tool_bar_handle, int64_t button_id, RECT *rect);

        void get_metrics(HWND tool_bar_handle, TBMETRICS *metrics);

        void set_metrics(HWND tool_bar_handle, TBMETRICS *metrics);

        // std::pair<horiz, vert>
        std::pair<uint32_t, uint32_t> get_padding(HWND tool_bar_handle);

        void set_padding(HWND tool_bar_handle, uint32_t horiz, uint32_t vert);

        int64_t get_rows(HWND tool_bar_handle);

        void set_rows(HWND tool_bar_handle,
                      uint32_t count,
                      RECT *rect,
                      bool more_rows = true);

        int64_t get_text_rows(HWND tool_bar_handle);

        bool set_text_rows(HWND tool_bar_handle, int64_t count);

        int64_t add_string(HWND tool_bar_handle,
                           HINSTANCE instance_handle,
                           int64_t res_id);

        // wchar_t res_str[] = L"New\0Open\0Save\0\0";
        int64_t add_string(HWND tool_bar_handle, wchar_t res_str[]);

        // return value = return string len
        int64_t
        get_string(HWND tool_bar_handle,
                   int64_t index,
                   std::string &str,
                   helper::CodePage code_page = helper::curr_code_page());

        // return value = return string len
        int64_t
        get_string(HWND tool_bar_handle, int64_t index, std::wstring &str);

        ToolBarStyle get_style(HWND tool_bar_handle);

        void set_style(HWND tool_bar_handle, ToolBarStyle style);

        HWND get_tool_tips(HWND tool_bar_handle);

        void set_tool_tips(HWND tool_bar_handle, HWND tool_tips_handle);

        bool is_ansi_format(HWND tool_bar_handle);

        bool is_unicode_format(HWND tool_bar_handle);

        void set_ansi_format(HWND tool_bar_handle);

        void set_unicode_format(HWND tool_bar_handle);

        void set_bounding_size(HWND tool_bar_handle, SIZE *size);

        bool
        set_command_id(HWND tool_bar_handle, int64_t index, int64_t command_id);

        gdi::TextFormat set_draw_text_flag(HWND tool_bar_handle,
                                      gdi::TextFormat format,
                                      gdi::TextFormat mask);

        bool set_indent(HWND tool_bar_handle, int64_t size);

        void set_list_gap(HWND tool_bar_handle, int64_t gap_size);

        HWND set_parent(HWND tool_bar_handle, HWND parent_window_handle);

        void
        set_window_theme(HWND tool_bar_handle,
                         std::string &window_theme,
                         helper::CodePage code_page = helper::curr_code_page());

        void set_window_theme(HWND tool_bar_handle, std::wstring &window_theme);

        void auto_size(HWND tool_bar_handle);

        void show_customize_dialog(HWND tool_bar_handle);

        bool has_accelerator(HWND tool_bar_handle, wchar_t accel);

        bool map_accelerator(HWND tool_bar_handle,
                             wchar_t accel,
                             uint32_t *button_id);

        int64_t hit_test(HWND tool_bar_handle, POINT *point);

        void save(HWND tool_bar_handle, TBSAVEPARAMSW *param);

        void restore(HWND tool_bar_handle, TBSAVEPARAMSW *param);

        bool get_object(HWND tool_bar_handle, IDropTarget **target);

        [[nodiscard]] uint32_t err_code() const;

        [[nodiscard]] std::string err_string() const;

        [[nodiscard]] std::wstring err_wstring() const;
    };
} // namespace YanLib::ui::components
#endif // TOOL_BAR_H
