/* clang-format off */
/*
 * @file task_dialog.cpp
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
#include "task_dialog.h"
#include <windowsx.h>

namespace YanLib::ui::components {
    bool task_dialog::create(HWND parent_window_handle,
                             HINSTANCE instance_handle,
                             TDButtonResult *button_result,
                             const wchar_t *title,
                             const wchar_t *main_instruction,
                             const wchar_t *content,
                             TDButtonFlag flag,
                             const wchar_t *icon) {
        if (!button_result) {
            return false;
        }
        auto temp = static_cast<int32_t>(*button_result);
        const bool is_ok =
                TaskDialog(parent_window_handle, instance_handle, title,
                           main_instruction, content,
                           static_cast<TASKDIALOG_COMMON_BUTTON_FLAGS>(flag),
                           icon, &temp);
        *button_result = static_cast<TDButtonResult>(temp);
        return is_ok == S_OK;
    }

    bool task_dialog::create(const TASKDIALOGCONFIG *config,
                             TDButtonResult *button_result,
                             TDButtonResult *radio_result,
                             bool *verify_checked) {
        if (!button_result || !radio_result || !verify_checked) {
            return false;
        }
        auto button_temp = static_cast<int32_t>(*button_result);
        auto radio_temp = static_cast<int32_t>(*radio_result);
        int32_t verify_temp = *verify_checked;
        const bool is_ok = TaskDialogIndirect(config, &button_temp, &radio_temp,
                                              &verify_temp);
        *button_result = static_cast<TDButtonResult>(button_temp);
        *radio_result = static_cast<TDButtonResult>(radio_temp);
        *verify_checked = verify_temp;
        return is_ok == S_OK;
    }

    TASKDIALOGCONFIG
    task_dialog::make_config(HWND parent_window_handle,
                             HINSTANCE instance_handle,
                             std::vector<TASKDIALOG_BUTTON> &normal_buttons,
                             TDButtonResult default_button,
                             std::vector<TASKDIALOG_BUTTON> &radio_buttons,
                             TDButtonResult default_radio,
                             PFTASKDIALOGCALLBACK callback,
                             intptr_t callback_data,
                             TaskDialogFlag dialog_flag,
                             TDButtonFlag button_flag,
                             const wchar_t *title,
                             HICON main_icon,
                             const wchar_t *main_instruction,
                             const wchar_t *content,
                             const wchar_t *verify_text,
                             const wchar_t *expand_info,
                             const wchar_t *expand_control_text,
                             const wchar_t *collapse_control_text,
                             HICON footer_icon,
                             const wchar_t *footer,
                             uint32_t width) {
        TASKDIALOGCONFIG config = {};
        config.cbSize = sizeof(TASKDIALOGCONFIG);
        config.hwndParent = parent_window_handle;
        config.hInstance = instance_handle;
        config.dwFlags = static_cast<TASKDIALOG_FLAGS>(dialog_flag);
        config.dwCommonButtons =
                static_cast<TASKDIALOG_COMMON_BUTTON_FLAGS>(button_flag);
        config.pszWindowTitle = title;
        config.hMainIcon = main_icon;
        config.pszMainInstruction = main_instruction;
        config.pszContent = content;
        config.cButtons = normal_buttons.size();
        config.pButtons = normal_buttons.data();
        config.nDefaultButton = static_cast<int32_t>(default_button);
        config.cRadioButtons = radio_buttons.size();
        config.pRadioButtons = radio_buttons.data();
        config.nDefaultRadioButton = static_cast<int32_t>(default_radio);
        config.pszVerificationText = verify_text;
        config.pszExpandedInformation = expand_info;
        config.pszExpandedControlText = expand_control_text;
        config.pszCollapsedControlText = collapse_control_text;
        config.hFooterIcon = footer_icon;
        config.pszFooter = footer;
        config.pfCallback = callback;
        config.lpCallbackData = callback_data;
        config.cxWidth = width;
        return config;
    }

    void task_dialog::click_button(HWND task_dialog_handle, int32_t button_id) {
        SendMessageW(task_dialog_handle, TDM_CLICK_BUTTON, button_id, 0);
    }

    void task_dialog::click_radio(HWND task_dialog_handle, int32_t radio_id) {
        SendMessageW(task_dialog_handle, TDM_CLICK_RADIO_BUTTON, radio_id, 0);
    }

    void task_dialog::click_verify(HWND task_dialog_handle,
                                   bool checked,
                                   bool focus) {
        SendMessageW(task_dialog_handle, TDM_CLICK_VERIFICATION,
                     checked ? TRUE : FALSE, focus ? TRUE : FALSE);
    }

    void task_dialog::enable_button(HWND task_dialog_handle,
                                    int32_t button_id) {
        SendMessageW(task_dialog_handle, TDM_ENABLE_BUTTON, button_id, TRUE);
    }

    void task_dialog::disable_button(HWND task_dialog_handle,
                                     int32_t button_id) {
        SendMessageW(task_dialog_handle, TDM_ENABLE_BUTTON, button_id, FALSE);
    }

    void task_dialog::enable_radio(HWND task_dialog_handle, int32_t radio_id) {
        SendMessageW(task_dialog_handle, TDM_ENABLE_RADIO_BUTTON, radio_id,
                     TRUE);
    }

    void task_dialog::disable_radio(HWND task_dialog_handle, int32_t radio_id) {
        SendMessageW(task_dialog_handle, TDM_ENABLE_RADIO_BUTTON, radio_id,
                     FALSE);
    }

    void task_dialog::navigate_page(HWND task_dialog_handle,
                                    TASKDIALOGCONFIG *config) {
        SendMessageW(task_dialog_handle, TDM_NAVIGATE_PAGE, 0,
                     reinterpret_cast<LPARAM>(config));
    }

    void
    task_dialog::set_button_elevation_required_state(HWND task_dialog_handle,
                                                     int32_t button_id,
                                                     bool elevation) {
        SendMessageW(task_dialog_handle,
                     TDM_SET_BUTTON_ELEVATION_REQUIRED_STATE, button_id,
                     elevation ? TRUE : FALSE);
    }

    void task_dialog::set_link_elevation_required_state(HWND task_dialog_handle,
                                                        int32_t link_id,
                                                        bool elevation) {
        SendMessageW(task_dialog_handle,
                     TDM_SET_BUTTON_ELEVATION_REQUIRED_STATE, link_id,
                     elevation ? TRUE : FALSE);
    }

    void task_dialog::set_element_text(HWND task_dialog_handle,
                                       TaskDialogElement element,
                                       std::string &text,
                                       helper::CodePage code_page) {
        auto temp = helper::convert::str_to_wstr(text, code_page);
        SendMessageW(task_dialog_handle, TDM_SET_ELEMENT_TEXT,
                     static_cast<uint32_t>(element),
                     reinterpret_cast<LPARAM>(temp.data()));
    }

    void task_dialog::set_element_text(HWND task_dialog_handle,
                                       TaskDialogElement element,
                                       std::wstring &text) {
        SendMessageW(task_dialog_handle, TDM_SET_ELEMENT_TEXT,
                     static_cast<uint32_t>(element),
                     reinterpret_cast<LPARAM>(text.data()));
    }

    void task_dialog::update_element_text(HWND task_dialog_handle,
                                          TaskDialogElement element,
                                          std::string &text,
                                          helper::CodePage code_page) {
        auto temp = helper::convert::str_to_wstr(text, code_page);
        SendMessageW(task_dialog_handle, TDM_UPDATE_ELEMENT_TEXT,
                     static_cast<uint32_t>(element),
                     reinterpret_cast<LPARAM>(temp.data()));
    }

    void task_dialog::update_element_text(HWND task_dialog_handle,
                                          TaskDialogElement element,
                                          std::wstring &text) {
        SendMessageW(task_dialog_handle, TDM_UPDATE_ELEMENT_TEXT,
                     static_cast<uint32_t>(element),
                     reinterpret_cast<LPARAM>(text.data()));
    }

    void task_dialog::update_icon(HWND task_dialog_handle,
                                  TaskDialogIconType type,
                                  HICON icon_handle) {
        SendMessageW(task_dialog_handle, TDM_UPDATE_ICON,
                     static_cast<uint32_t>(type),
                     reinterpret_cast<LPARAM>(icon_handle));
    }

    void task_dialog::update_icon(HWND task_dialog_handle,
                                  TaskDialogIconType type,
                                  std::string &icon,
                                  helper::CodePage code_page) {
        auto temp = helper::convert::str_to_wstr(icon, code_page);
        SendMessageW(task_dialog_handle, TDM_UPDATE_ICON,
                     static_cast<uint32_t>(type),
                     reinterpret_cast<LPARAM>(temp.data()));
    }

    void task_dialog::update_icon(HWND task_dialog_handle,
                                  TaskDialogIconType type,
                                  std::wstring &icon) {
        SendMessageW(task_dialog_handle, TDM_UPDATE_ICON,
                     static_cast<uint32_t>(type),
                     reinterpret_cast<LPARAM>(icon.data()));
    }

    void task_dialog::show_marquee_progress(HWND task_dialog_handle) {
        SendMessageW(task_dialog_handle, TDM_SET_MARQUEE_PROGRESS_BAR, TRUE, 0);
    }

    void task_dialog::hide_marquee_progress(HWND task_dialog_handle) {
        SendMessageW(task_dialog_handle, TDM_SET_MARQUEE_PROGRESS_BAR, FALSE,
                     0);
    }

    void task_dialog::start_marquee_progress(HWND task_dialog_handle,
                                             int32_t milli_seconds) {
        SendMessageW(task_dialog_handle, TDM_SET_PROGRESS_BAR_MARQUEE, TRUE,
                     milli_seconds);
    }

    void task_dialog::stop_marquee_progress(HWND task_dialog_handle,
                                            int32_t milli_seconds) {
        SendMessageW(task_dialog_handle, TDM_SET_PROGRESS_BAR_MARQUEE, FALSE,
                     milli_seconds);
    }

    int64_t task_dialog::set_progress_pos(HWND task_dialog_handle,
                                          int64_t pos) {
        return SendMessageW(task_dialog_handle, TDM_SET_PROGRESS_BAR_POS, pos,
                            0);
    }

    std::pair<uint32_t, uint32_t>
    task_dialog::set_progress_range(HWND task_dialog_handle,
                                    uint32_t min,
                                    uint32_t max) {
        const int64_t result =
                SendMessageW(task_dialog_handle, TDM_SET_PROGRESS_BAR_RANGE, 0,
                             MAKELPARAM(min, max));
        return std::make_pair(LOWORD(result), HIWORD(result));
    }

    bool task_dialog::set_progress_state(HWND task_dialog_handle,
                                         ProgressState state) {
        return SendMessageW(task_dialog_handle, TDM_SET_PROGRESS_BAR_STATE,
                            static_cast<uint32_t>(state), 0);
    }
} // namespace YanLib::ui::components
