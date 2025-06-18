/* clang-format off */
/*
 * @file button.h
 * @date 2025-05-23
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
#ifndef BUTTON_H
#define BUTTON_H
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
    class button {
    private:
        std::vector<HWND> button_handles = {};
        sync::rwlock button_rwlock = {};
        uint32_t error_code = 0;

    public:
        button(const button &other) = delete;

        button(button &&other) = delete;

        button &operator=(const button &other) = delete;

        button &operator=(button &&other) = delete;

        button() = default;

        ~button();

        HWND create(uintptr_t button_id,
                    HWND parent_window_handle,
                    LPARAM lparam,
                    int32_t x,
                    int32_t y,
                    int32_t width = 100,
                    int32_t height = 30,
                    ButtonStyle style = ButtonStyle::PushButton,
                    core::WindowStyle window_style = core::WindowStyle::Child |
                            core::WindowStyle::Visible);

        HWND create(const char *button_name,
                    uintptr_t button_id,
                    HWND parent_window_handle,
                    LPARAM lparam,
                    int32_t x,
                    int32_t y,
                    int32_t width = 100,
                    int32_t height = 30,
                    ButtonStyle style = ButtonStyle::PushButton,
                    core::WindowStyle window_style = core::WindowStyle::Child |
                            core::WindowStyle::Visible);

        HWND create(const wchar_t *button_name,
                    uintptr_t button_id,
                    HWND parent_window_handle,
                    LPARAM lparam,
                    int32_t x,
                    int32_t y,
                    int32_t width = 100,
                    int32_t height = 30,
                    ButtonStyle style = ButtonStyle::PushButton,
                    core::WindowStyle window_style = core::WindowStyle::Child |
                            core::WindowStyle::Visible);

        bool destroy(HWND button_handle);

        bool enable(HWND button_handle);

        bool disable(HWND button_handle);

        core::ButtonState get_check(HWND button_handle);

        void set_check(HWND button_handle, core::ButtonState state);

        bool get_ideal_size(HWND button_handle, SIZE *size);

        bool get_image_list(HWND button_handle, BUTTON_IMAGELIST *image_list);

        bool set_image_list(HWND button_handle, BUTTON_IMAGELIST *image_list);

        int64_t get_note_len(HWND button_handle);

        bool get_note(HWND button_handle,
                      std::string &note,
                      helper::CodePage code_page = helper::curr_code_page());

        bool set_note(HWND button_handle,
                      std::string &note,
                      helper::CodePage code_page = helper::curr_code_page());

        bool get_note(HWND button_handle, std::wstring &note);

        bool set_note(HWND button_handle, std::wstring &note);

        bool get_split_info(HWND button_handle, BUTTON_SPLITINFO *split_info);

        bool set_split_info(HWND button_handle, BUTTON_SPLITINFO *split_info);

        int32_t get_text_len(HWND button_handle);

        int32_t get_text(HWND button_handle, std::string &text);

        bool set_text(HWND button_handle, std::string &text);

        int32_t get_text(HWND button_handle, std::wstring &text);

        bool set_text(HWND button_handle, std::wstring &text);

        TextAlign get_text_align(HWND button_handle);

        void set_text_align(HWND button_handle, TextAlign align);

        bool get_text_margin(HWND button_handle, RECT *margin);

        bool set_text_margin(HWND button_handle, RECT *margin);

        core::ButtonState get_state(HWND button_handle);

        void hilite(HWND button_handle);

        void unhilite(HWND button_handle);

        bool active_drop_down_state(HWND button_handle);

        bool inactive_drop_down_state(HWND button_handle);

        LRESULT set_elevation_state(HWND button_handle);

        LRESULT unset_elevation_state(HWND button_handle);

        ButtonStyle get_style(HWND button_handle);

        void
        set_style(HWND button_handle, ButtonStyle style, bool is_redraw = true);

        [[nodiscard]] uint32_t err_code() const;

        [[nodiscard]] std::string err_string() const;

        [[nodiscard]] std::wstring err_wstring() const;
    };
} // namespace YanLib::ui::components
#endif // BUTTON_H
