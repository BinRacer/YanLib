/* clang-format off */
/*
 * @file tab.h
 * @date 2025-05-31
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
#ifndef TAB_H
#define TAB_H
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
#include "ui/core/core.h"
#include "components.h"
#pragma comment(lib, "ComCtl32.Lib")
#pragma comment(linker, "\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#pragma comment(lib, "User32.Lib")
namespace YanLib::ui::components {
    class tab {
    private:
        std::vector<HWND> tab_handles = {};
        sync::rwlock tab_rwlock = {};
        uint32_t error_code = 0;

    public:
        tab(const tab &other) = delete;

        tab(tab &&other) = delete;

        tab &operator=(const tab &other) = delete;

        tab &operator=(tab &&other) = delete;

        tab();

        ~tab();

        HWND create(uintptr_t tab_id,
                    HWND parent_window_handle,
                    LPARAM lparam,
                    int32_t x,
                    int32_t y,
                    int32_t width,
                    int32_t height,
                    TabStyle style = TabStyle::RightJustify |
                            TabStyle::FocusNever | TabStyle::ScrollOpposite |
                            TabStyle::SingleLine | TabStyle::Tabs,
                    core::WindowStyle window_style = core::WindowStyle::Child |
                            core::WindowStyle::Visible | core::WindowStyle::ClipSiblings);

        HWND create(const char *tab_name,
                    uintptr_t tab_id,
                    HWND parent_window_handle,
                    LPARAM lparam,
                    int32_t x,
                    int32_t y,
                    int32_t width,
                    int32_t height,
                    TabStyle style = TabStyle::RightJustify |
                            TabStyle::FocusNever | TabStyle::ScrollOpposite |
                            TabStyle::SingleLine | TabStyle::Tabs,
                    core::WindowStyle window_style = core::WindowStyle::Child |
                            core::WindowStyle::Visible | core::WindowStyle::ClipSiblings);

        HWND create(const wchar_t *tab_name,
                    uintptr_t tab_id,
                    HWND parent_window_handle,
                    LPARAM lparam,
                    int32_t x,
                    int32_t y,
                    int32_t width,
                    int32_t height,
                    TabStyle style = TabStyle::RightJustify |
                            TabStyle::FocusNever | TabStyle::ScrollOpposite |
                            TabStyle::SingleLine | TabStyle::Tabs,
                    core::WindowStyle window_style = core::WindowStyle::Child |
                            core::WindowStyle::Visible | core::WindowStyle::ClipSiblings);

        bool destroy(HWND tab_handle);

        int32_t get_curr_focus(HWND tab_handle);

        void set_curr_focus(HWND tab_handle, int32_t tab_index);

        int32_t get_curr_select(HWND tab_handle);

        int32_t set_curr_select(HWND tab_handle, int32_t tab_index);

        TabExtendStyle get_extend_style(HWND tab_handle);

        TabExtendStyle set_extend_style(HWND tab_handle, TabExtendStyle style);

        bool is_ansi_format(HWND tab_handle);

        bool is_unicode_format(HWND tab_handle);

        void set_ansi_format(HWND tab_handle);

        void set_unicode_format(HWND tab_handle);

        HIMAGELIST get_image_list(HWND tab_handle);

        HIMAGELIST set_image_list(HWND tab_handle, HIMAGELIST image_list);

        void remove_image(HWND tab_handle, int32_t image_index);

        HWND get_tool_tips(HWND tab_handle);

        void set_tool_tips(HWND tab_handle, HWND tool_tips_handle);

        int32_t get_item_count(HWND tab_handle);

        bool get_item_rect(HWND tab_handle, int32_t tab_index, RECT *rect);

        bool get_item(HWND tab_handle, int32_t tab_index, TCITEMW *item);

        bool set_item(HWND tab_handle, int32_t tab_index, TCITEMW *item);

        bool set_item_extra(HWND tab_handle, int32_t size);

        // std::pair<width, height>
        std::pair<uint32_t, uint32_t>
        set_item_size(HWND tab_handle, int32_t width, int32_t height);

        SIZE set_item_size(HWND tab_handle, SIZE size);

        int32_t insert_item(HWND tab_handle, int32_t tab_index, TCITEMW *item);

        bool delete_item(HWND tab_handle, int32_t tab_index);

        bool delete_all_items(HWND tab_handle);

        bool highlight_item(HWND tab_handle, int32_t tab_index);

        bool unhighlight_item(HWND tab_handle, int32_t tab_index);

        int32_t hit_test(HWND tab_handle, TCHITTESTINFO *hit_test_info);

        int32_t get_row_count(HWND tab_handle);

        int32_t set_min_width(HWND tab_handle, int32_t width);

        void set_padding(HWND tab_handle, int32_t horiz, int32_t vert);

        void display_rect_to_window_rect(HWND tab_handle, RECT *rect);

        void window_rect_to_display_rect(HWND tab_handle, RECT *rect);

        void reset_curr_item(HWND tab_handle);

        void reset_all_items(HWND tab_handle);

        [[nodiscard]] uint32_t err_code() const;

        [[nodiscard]] std::string err_string() const;

        [[nodiscard]] std::wstring err_wstring() const;
    };
} // namespace YanLib::ui::components
#endif // TAB_H
