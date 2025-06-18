/* clang-format off */
/*
 * @file combo_box.h
 * @date 2025-05-24
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
#ifndef COMBO_BOX_H
#define COMBO_BOX_H
#ifndef UNICODE
#define UNICODE
#endif
#ifndef _UNICODE
#define _UNICODE
#endif
#include <Windows.h>
#include <CommCtrl.h>
#include <WinUser.h>
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
    class combo_box {
    private:
        std::vector<HWND> combo_box_handles = {};
        sync::rwlock combo_box_rwlock = {};
        uint32_t error_code = 0;

    public:
        combo_box(const combo_box &other) = delete;

        combo_box(combo_box &&other) = delete;

        combo_box &operator=(const combo_box &other) = delete;

        combo_box &operator=(combo_box &&other) = delete;

        combo_box() = default;

        ~combo_box();

        HWND create(uintptr_t combo_box_id,
                    HWND parent_window_handle,
                    LPARAM lparam,
                    int32_t x,
                    int32_t y,
                    int32_t width,
                    int32_t height,
                    ComboBoxStyle style = ComboBoxStyle::DropDownList |
                            ComboBoxStyle::AutoHorizScroll |
                            ComboBoxStyle::HasStrings,
                    core::WindowStyle window_style = core::WindowStyle::Child |
                            core::WindowStyle::Visible | core::WindowStyle::VScroll);

        HWND create(const char *combo_box_name,
                    uintptr_t combo_box_id,
                    HWND parent_window_handle,
                    LPARAM lparam,
                    int32_t x,
                    int32_t y,
                    int32_t width,
                    int32_t height,
                    ComboBoxStyle style = ComboBoxStyle::DropDownList |
                            ComboBoxStyle::AutoHorizScroll |
                            ComboBoxStyle::HasStrings,
                    core::WindowStyle window_style = core::WindowStyle::Child |
                            core::WindowStyle::Visible | core::WindowStyle::VScroll);

        HWND create(const wchar_t *combo_box_name,
                    uintptr_t combo_box_id,
                    HWND parent_window_handle,
                    LPARAM lparam,
                    int32_t x,
                    int32_t y,
                    int32_t width,
                    int32_t height,
                    ComboBoxStyle style = ComboBoxStyle::DropDownList |
                            ComboBoxStyle::AutoHorizScroll |
                            ComboBoxStyle::HasStrings,
                    core::WindowStyle window_style = core::WindowStyle::Child |
                            core::WindowStyle::Visible | core::WindowStyle::VScroll);

        bool destroy(HWND combo_box_handle);

        bool enable(HWND combo_box_handle);

        bool disable(HWND combo_box_handle);

        int32_t fill(HWND combo_box_handle,
                     const char *path_spec,
                     ComboFileType type = ComboFileType::Drives | ComboFileType::Directory |
                             ComboFileType::ReadWrite,
                     helper::CodePage code_page = helper::curr_code_page());

        int32_t fill(HWND combo_box_handle,
                     wchar_t *path_spec,
                     ComboFileType type = ComboFileType::Drives | ComboFileType::Directory |
                             ComboFileType::ReadWrite);

        int32_t add_text(HWND combo_box_handle,
                         std::string &text,
                         helper::CodePage code_page = helper::curr_code_page());

        int32_t add_text(HWND combo_box_handle, std::wstring &text);

        int32_t
        insert_text(HWND combo_box_handle,
                    std::string &text,
                    int32_t index = -1,
                    helper::CodePage code_page = helper::curr_code_page());

        int32_t insert_text(HWND combo_box_handle,
                            std::wstring &text,
                            int32_t index = -1);

        int32_t
        select_text(HWND combo_box_handle,
                    std::string &text,
                    int32_t index = -1,
                    helper::CodePage code_page = helper::curr_code_page());

        int32_t select_text(HWND combo_box_handle,
                            std::wstring &text,
                            int32_t index = -1);

        int32_t
        find_text(HWND combo_box_handle,
                  std::string &text,
                  int32_t index = -1,
                  helper::CodePage code_page = helper::curr_code_page());

        int32_t find_text(HWND combo_box_handle,
                          std::wstring &text,
                          int32_t index = -1);

        int32_t
        find_exact_text(HWND combo_box_handle,
                        std::string &text,
                        int32_t index = -1,
                        helper::CodePage code_page = helper::curr_code_page());

        int32_t find_exact_text(HWND combo_box_handle,
                                std::wstring &text,
                                int32_t index = -1);

        int32_t delete_item(HWND combo_box_handle, int32_t index);

        void clear(HWND combo_box_handle);

        void set_text_limit(HWND combo_box_handle, int32_t limit);

        int32_t get_text_len(HWND combo_box_handle);

        int32_t get_text(HWND combo_box_handle, std::string &text);

        int32_t get_text(HWND combo_box_handle, std::wstring &text);

        int32_t get_item_count(HWND combo_box_handle);

        int32_t get_item_text_len(HWND combo_box_handle, int32_t index);

        int32_t
        get_item_text(HWND combo_box_handle,
                      std::string &text,
                      int32_t index,
                      helper::CodePage code_page = helper::curr_code_page());

        int32_t
        get_item_text(HWND combo_box_handle, std::wstring &text, int32_t index);

        int32_t replace_item_text(
                HWND combo_box_handle,
                std::string &text,
                int32_t index,
                helper::CodePage code_page = helper::curr_code_page());

        int32_t replace_item_text(HWND combo_box_handle,
                                  std::wstring &text,
                                  int32_t index);

        int32_t get_item_height(HWND combo_box_handle);

        bool set_item_height(HWND combo_box_handle,
                             int32_t height,
                             int32_t index = -1);

        bool set_text(HWND combo_box_handle, std::string &text);

        bool set_text(HWND combo_box_handle, std::wstring &text);

        int32_t add_data(HWND combo_box_handle, LPARAM data);

        int32_t
        insert_data(HWND combo_box_handle, LPARAM data, int32_t index = -1);

        int32_t
        select_data(HWND combo_box_handle, LPARAM data, int32_t index = -1);

        int32_t
        find_data(HWND combo_box_handle, LPARAM data, int32_t index = -1);

        LPARAM get_data(HWND combo_box_handle, int32_t index);

        int32_t set_data(HWND combo_box_handle, LPARAM data, int32_t index);

        bool get_prompt_banner(
                HWND combo_box_handle,
                std::string &text,
                helper::CodePage code_page = helper::curr_code_page());

        bool get_prompt_banner(HWND combo_box_handle, std::wstring &text);

        bool set_prompt_banner(
                HWND combo_box_handle,
                std::string &text,
                helper::CodePage code_page = helper::curr_code_page());

        bool set_prompt_banner(HWND combo_box_handle, std::wstring &text);

        int32_t get_curr_select(HWND combo_box_handle);

        int32_t set_curr_select(HWND combo_box_handle, int32_t index);

        bool is_extended_ui(HWND combo_box_handle);

        bool is_default_ui(HWND combo_box_handle);

        int32_t set_extended_ui(HWND combo_box_handle);

        int32_t set_default_ui(HWND combo_box_handle);

        int32_t get_min_visible(HWND combo_box_handle);

        bool set_min_visible(HWND combo_box_handle, int32_t num);

        void show_drop_down(HWND combo_box_handle);

        void hide_drop_down(HWND combo_box_handle);

        bool is_drop_down_visible(HWND combo_box_handle);

        void get_dropped_control_rect(HWND combo_box_handle, RECT *rect);

        bool get_info(HWND combo_box_handle, COMBOBOXINFO *combo_box_info);

        [[nodiscard]] uint32_t err_code() const;

        [[nodiscard]] std::string err_string() const;

        [[nodiscard]] std::wstring err_wstring() const;
    };
} // namespace YanLib::ui::components
#endif // COMBO_BOX_H
