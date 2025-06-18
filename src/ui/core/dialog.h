/* clang-format off */
/*
 * @file dialog.h
 * @date 2025-04-30
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
#ifndef DIALOG_H
#define DIALOG_H
#include <Windows.h>
#include <WinUser.h>
#include <minwindef.h>
#include <windef.h>
#include <CommCtrl.h>
#include <string>
#include <vector>
#include "sync/rwlock.h"
#include "core.h"
namespace YanLib::ui::core {
    class dialog {
    private:
        std::vector<HWND> dialog_modeless_handle = {};
        sync::rwlock rwlock = {};
        uint32_t error_code = 0;

    public:
        dialog(const dialog &other) = delete;

        dialog(dialog &&other) = delete;

        dialog &operator=(const dialog &other) = delete;

        dialog &operator=(dialog &&other) = delete;

        dialog() = default;

        ~dialog();

        intptr_t create(HINSTANCE instance_handle,
                        const char *template_name,
                        HWND parent_window_handle,
                        DLGPROC dialog_func);

        intptr_t create(HINSTANCE instance_handle,
                        const wchar_t *template_name,
                        HWND parent_window_handle,
                        DLGPROC dialog_func);

        intptr_t create(HINSTANCE instance_handle,
                        const char *template_name,
                        HWND parent_window_handle,
                        DLGPROC dialog_func,
                        LPARAM init_param);

        intptr_t create(HINSTANCE instance_handle,
                        const wchar_t *template_name,
                        HWND parent_window_handle,
                        DLGPROC dialog_func,
                        LPARAM init_param);

        intptr_t create(HINSTANCE instance_handle,
                        const DLGTEMPLATE *dialog_template,
                        HWND parent_window_handle,
                        DLGPROC dialog_func);

        intptr_t create(HINSTANCE instance_handle,
                        const DLGTEMPLATE *dialog_template,
                        HWND parent_window_handle,
                        DLGPROC dialog_func,
                        LPARAM init_param);

        HWND create_modeless(HINSTANCE instance_handle,
                             const wchar_t *template_name,
                             HWND parent_window_handle,
                             DLGPROC dialog_func);

        HWND create_modeless(HINSTANCE instance_handle,
                             const wchar_t *template_name,
                             HWND parent_window_handle,
                             DLGPROC dialog_func,
                             LPARAM init_param);

        HWND create_modeless(HINSTANCE instance_handle,
                             const DLGTEMPLATE *dialog_template,
                             HWND parent_window_handle,
                             DLGPROC dialog_func);

        HWND create_modeless(HINSTANCE instance_handle,
                             const DLGTEMPLATE *dialog_template,
                             HWND parent_window_handle,
                             DLGPROC dialog_func,
                             LPARAM init_param);

        bool destroy(HWND dialog_handle, intptr_t result);

        bool destroy_modeless(HWND dialog_handle);

        bool set_button_state(HWND dialog_handle,
                              int32_t button_id,
                              ButtonState state = ButtonState::Checked);

        bool set_radio_state(HWND dialog_handle,
                             int32_t first_button_id,
                             int32_t last_button_id,
                             int32_t check_button_id);

        LRESULT default_proc(HWND dialog_handle,
                             uint32_t msg,
                             WPARAM wparam,
                             LPARAM lparam);

        int32_t fill_list_box(HWND dialog_handle,
                              char *path_spec,
                              int32_t list_box_id,
                              int32_t static_id,
                              DialogFileType file_type = DialogFileType::Drives |
                                      DialogFileType::Directory |
                                      DialogFileType::ReadWrite);

        int32_t fill_list_box(HWND dialog_handle,
                              wchar_t *path_spec,
                              int32_t list_box_id,
                              int32_t static_id,
                              DialogFileType file_type = DialogFileType::Drives |
                                      DialogFileType::Directory |
                                      DialogFileType::ReadWrite);

        int32_t fill_combo_box(HWND dialog_handle,
                               char *path_spec,
                               int32_t combo_box_id,
                               int32_t static_id,
                               DialogFileType file_type = DialogFileType::Drives |
                                       DialogFileType::Directory |
                                       DialogFileType::ReadWrite);

        int32_t fill_combo_box(HWND dialog_handle,
                               wchar_t *path_spec,
                               int32_t combo_box_id,
                               int32_t static_id,
                               DialogFileType file_type = DialogFileType::Drives |
                                       DialogFileType::Directory |
                                       DialogFileType::ReadWrite);

        bool get_select_combo_box(HWND dialog_handle,
                                  std::string &path,
                                  int32_t combo_box_id);

        bool get_select_combo_box(HWND dialog_handle,
                                  std::wstring &path,
                                  int32_t combo_box_id);

        bool get_select_list_box(HWND dialog_handle,
                                 std::string &path,
                                 int32_t list_box_id);

        bool get_select_list_box(HWND dialog_handle,
                                 std::wstring &path,
                                 int32_t list_box_id);

        int32_t get_item_id(HWND item_handle);

        HWND get_item_handle(HWND dialog_handle, int32_t item_id);

        bool get_item_int(HWND dialog_handle,
                          int32_t item_id,
                          uint32_t *value,
                          bool is_signed);

        bool set_item_int(HWND dialog_handle,
                          int32_t item_id,
                          uint32_t value,
                          bool is_signed);

        uint32_t
        get_item_text(HWND dialog_handle, int32_t item_id, std::string &text);

        uint32_t
        get_item_text(HWND dialog_handle, int32_t item_id, std::wstring &text);

        bool
        set_item_text(HWND dialog_handle, int32_t item_id, const char *text);

        bool
        set_item_text(HWND dialog_handle, int32_t item_id, const wchar_t *text);

        HWND next_group_item(HWND dialog_handle,
                             HWND item_handle,
                             bool search_upward = false);

        HWND next_tab_item(HWND dialog_handle,
                           HWND item_handle,
                           bool search_upward = false);

        ButtonState is_button_checked(HWND dialog_handle, int32_t button_id);

        ItemDpiBehavior get_item_dpi_behavior(HWND dialog_handle);

        bool set_item_dpi_behavior(HWND dialog_handle,
                                   ItemDpiBehavior mask,
                                   ItemDpiBehavior values);

        DialogDpiBehavior get_dpi_behavior(HWND dialog_handle);

        bool set_dpi_behavior(HWND dialog_handle,
                              DialogDpiBehavior mask,
                              DialogDpiBehavior values);

        int32_t get_base_units();

        bool base_units_to_screen_point(HWND dialog_handle, RECT *rect);

        [[nodiscard]] uint32_t err_code() const;

        [[nodiscard]] std::string err_string() const;

        [[nodiscard]] std::wstring err_wstring() const;
    };
} // namespace YanLib::ui::core
#endif // DIALOG_H
