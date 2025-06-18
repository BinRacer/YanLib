/* clang-format off */
/*
 * @file list_box.h
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
#ifndef LIST_BOX_H
#define LIST_BOX_H
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
    class list_box {
    private:
        std::vector<HWND> list_box_handles = {};
        sync::rwlock list_box_rwlock = {};
        uint32_t error_code = 0;

    public:
        list_box(const list_box &other) = delete;

        list_box(list_box &&other) = delete;

        list_box &operator=(const list_box &other) = delete;

        list_box &operator=(list_box &&other) = delete;

        list_box() = default;

        ~list_box();

        HWND create(uintptr_t list_box_id,
                    HWND parent_window_handle,
                    LPARAM lparam,
                    int32_t x,
                    int32_t y,
                    int32_t width,
                    int32_t height,
                    ListBoxStyle style = ListBoxStyle::HasStrings |
                            ListBoxStyle::ExtendedSelect |
                            ListBoxStyle::MultiColumn |
                            ListBoxStyle::MultipleSelect |
                            ListBoxStyle::Notify | ListBoxStyle::UseTabStops |
                            ListBoxStyle::WantKeyboardInput,
                    core::WindowStyle window_style = core::WindowStyle::Child |
                            core::WindowStyle::Visible | core::WindowStyle::VScroll);

        HWND create(const char *list_box_name,
                    uintptr_t list_box_id,
                    HWND parent_window_handle,
                    LPARAM lparam,
                    int32_t x,
                    int32_t y,
                    int32_t width,
                    int32_t height,
                    ListBoxStyle style = ListBoxStyle::HasStrings |
                            ListBoxStyle::ExtendedSelect |
                            ListBoxStyle::MultiColumn |
                            ListBoxStyle::MultipleSelect |
                            ListBoxStyle::Notify | ListBoxStyle::UseTabStops |
                            ListBoxStyle::WantKeyboardInput,
                    core::WindowStyle window_style = core::WindowStyle::Child |
                            core::WindowStyle::Visible | core::WindowStyle::VScroll);

        HWND create(const wchar_t *list_box_name,
                    uintptr_t list_box_id,
                    HWND parent_window_handle,
                    LPARAM lparam,
                    int32_t x,
                    int32_t y,
                    int32_t width,
                    int32_t height,
                    ListBoxStyle style = ListBoxStyle::HasStrings |
                            ListBoxStyle::ExtendedSelect |
                            ListBoxStyle::MultiColumn |
                            ListBoxStyle::MultipleSelect |
                            ListBoxStyle::Notify | ListBoxStyle::UseTabStops |
                            ListBoxStyle::WantKeyboardInput,
                    core::WindowStyle window_style = core::WindowStyle::Child |
                            core::WindowStyle::Visible | core::WindowStyle::VScroll);

        bool destroy(HWND list_box_handle);

        bool enable(HWND list_box_handle);

        bool disable(HWND list_box_handle);

        int32_t fill(HWND list_box_handle,
                     const char *path_spec,
                     ListFileType type = ListFileType::Drives | ListFileType::Directory |
                             ListFileType::ReadWrite,
                     helper::CodePage code_page = helper::curr_code_page());

        int32_t fill(HWND list_box_handle,
                     const wchar_t *path_spec,
                     ListFileType type = ListFileType::Drives | ListFileType::Directory |
                             ListFileType::ReadWrite);

        int32_t add_text(HWND list_box_handle,
                         std::string &text,
                         helper::CodePage code_page = helper::curr_code_page());

        int32_t add_text(HWND list_box_handle, std::wstring &text);

        int32_t
        find_text(HWND list_box_handle,
                  std::string &text,
                  int32_t index = -1,
                  helper::CodePage code_page = helper::curr_code_page());

        int32_t
        find_text(HWND list_box_handle, std::wstring &text, int32_t index = -1);

        int32_t
        find_text_exact(HWND list_box_handle,
                        std::string &text,
                        int32_t index = -1,
                        helper::CodePage code_page = helper::curr_code_page());

        int32_t find_text_exact(HWND list_box_handle,
                                std::wstring &text,
                                int32_t index = -1);

        int32_t
        insert_text(HWND list_box_handle,
                    std::string &text,
                    int32_t index = -1,
                    helper::CodePage code_page = helper::curr_code_page());

        int32_t insert_text(HWND list_box_handle,
                            std::wstring &text,
                            int32_t index = -1);

        int32_t
        select_text(HWND list_box_handle,
                    std::string &text,
                    int32_t index = -1,
                    helper::CodePage code_page = helper::curr_code_page());

        int32_t select_text(HWND list_box_handle,
                            std::wstring &text,
                            int32_t index = -1);

        int32_t delete_item(HWND list_box_handle, int32_t index);

        int32_t get_item_text_len(HWND list_box_handle, int32_t index);

        int32_t
        get_item_text(HWND list_box_handle,
                      std::string &text,
                      int32_t index,
                      helper::CodePage code_page = helper::curr_code_page());

        int32_t
        get_item_text(HWND list_box_handle, std::wstring &text, int32_t index);

        int32_t add_data(HWND list_box_handle, LPARAM data);

        int32_t
        find_data(HWND list_box_handle, LPARAM data, int32_t index = -1);

        LPARAM get_data(HWND list_box_handle, int32_t index);

        int32_t set_data(HWND list_box_handle, LPARAM data, int32_t index);

        int32_t
        insert_data(HWND list_box_handle, LPARAM data, int32_t index = -1);

        int32_t
        select_data(HWND list_box_handle, LPARAM data, int32_t index = -1);

        int32_t get_item_height(HWND list_box_handle, int32_t index);

        int32_t
        set_item_height(HWND list_box_handle, int32_t width, int32_t index);

        bool get_item_rect(HWND list_box_handle, RECT *rect, int32_t index);

        int32_t get_select_items(HWND list_box_handle,
                                 std::vector<int32_t> &select_index);

        bool set_item_range(HWND list_box_handle, int32_t start, int32_t end);

        bool unset_item_range(HWND list_box_handle, int32_t start, int32_t end);

        int32_t get_curr_select(HWND list_box_handle);

        int32_t set_curr_select(HWND list_box_handle, int32_t index);

        bool is_select(HWND list_box_handle, int32_t index);

        bool set_select(HWND list_box_handle, int32_t index);

        bool unset_select(HWND list_box_handle, int32_t index);

        int32_t get_select_count(HWND list_box_handle);

        int32_t get_caret_index(HWND list_box_handle);

        bool set_caret_index(HWND list_box_handle, int32_t index);

        int32_t get_top_index(HWND list_box_handle);

        bool set_top_index(HWND list_box_handle, int32_t index);

        void reset_content(HWND list_box_handle);

        int32_t get_horiz_extent(HWND list_box_handle);

        void set_horiz_extent(HWND list_box_handle, int32_t extent);

        void set_all_colum_width(HWND list_box_handle, int32_t width);

        int32_t get_item_count(HWND list_box_handle);

        bool set_tab_stops(HWND list_box_handle,
                           std::vector<int32_t> &tab_stops);

        void draw_insert(HWND parent_window_handle,
                         HWND list_box_handle,
                         int32_t icon_id);

        int32_t item_id_from_point(HWND list_box_handle,
                                   POINT point,
                                   bool auto_scroll = true);

        bool modify_to_drag_list(HWND list_box_handle);

        [[nodiscard]] uint32_t err_code() const;

        [[nodiscard]] std::string err_string() const;

        [[nodiscard]] std::wstring err_wstring() const;
    };
} // namespace YanLib::ui::components
#endif // LIST_BOX_H
