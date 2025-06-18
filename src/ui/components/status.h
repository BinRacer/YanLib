/* clang-format off */
/*
 * @file status.h
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
#ifndef STATUS_H
#define STATUS_H
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
    class status {
    private:
        std::vector<HWND> status_handles = {};
        sync::rwlock status_rwlock = {};
        uint32_t error_code = 0;

    public:
        status(const status &other) = delete;

        status(status &&other) = delete;

        status &operator=(const status &other) = delete;

        status &operator=(status &&other) = delete;

        status() = default;

        ~status();

        HWND create(uintptr_t status_id,
                    HWND parent_window_handle,
                    LPARAM lparam,
                    int32_t x,
                    int32_t y,
                    int32_t width,
                    int32_t height,
                    StatusStyle style = StatusStyle::SizeGrip |
                            StatusStyle::ToolTips,
                    core::WindowStyle window_style = core::WindowStyle::Child |
                            core::WindowStyle::Visible);

        HWND create(const char *status_name,
                    uintptr_t status_id,
                    HWND parent_window_handle,
                    LPARAM lparam,
                    int32_t x,
                    int32_t y,
                    int32_t width,
                    int32_t height,
                    StatusStyle style = StatusStyle::SizeGrip |
                            StatusStyle::ToolTips,
                    core::WindowStyle window_style = core::WindowStyle::Child |
                            core::WindowStyle::Visible);

        HWND create(const wchar_t *status_name,
                    uintptr_t status_id,
                    HWND parent_window_handle,
                    LPARAM lparam,
                    int32_t x,
                    int32_t y,
                    int32_t width,
                    int32_t height,
                    StatusStyle style = StatusStyle::SizeGrip |
                            StatusStyle::ToolTips,
                    core::WindowStyle window_style = core::WindowStyle::Child |
                            core::WindowStyle::Visible);

        bool destroy(HWND status_handle);

        void draw_status_text(HDC dc_handle,
                              RECT *rect,
                              const char *text,
                              StatusTextFlag flag);

        void draw_status_text(HDC dc_handle,
                              RECT *rect,
                              const wchar_t *text,
                              StatusTextFlag flag);

        // message = WM_MENUSELECT or WM_COMMAND
        void menu_help(uint32_t message,
                       WPARAM wparam,
                       LPARAM lparam,
                       HMENU menu_handle,
                       HINSTANCE instance_handle,
                       HWND status_handle,
                       uint32_t id[]);

        // borders[0] = the width of the horizontal border
        // borders[1] = the width of the vertical border
        // borders[2] = the width of the border between rectangles
        bool get_borders(HWND status_handle, int32_t borders[3]);

        bool get_rect(HWND status_handle, int32_t index, RECT *rect);

        COLORREF set_background_color(HWND status_handle,
                                      COLORREF color = CLR_DEFAULT);

        void set_min_height(HWND status_handle, int32_t height);

        HICON get_icon(HWND status_handle, int32_t index = -1);

        bool set_icon(HWND status_handle, HICON icon, int32_t index = -1);

        bool delete_icon(HWND status_handle, int32_t index = -1);

        int64_t get_parts(HWND status_handle, std::vector<int32_t> &parts);

        bool set_parts(HWND status_handle, std::vector<int32_t> &parts);

        std::pair<uint32_t, StatusTextFlag>
        get_text(HWND status_handle,
                 uint8_t index,
                 std::string &text,
                 helper::CodePage code_page = helper::curr_code_page());

        std::pair<uint32_t, StatusTextFlag>
        get_text(HWND status_handle, uint8_t index, std::wstring &text);

        bool set_text(HWND status_handle,
                      uint8_t index,
                      StatusTextFlag flag,
                      std::string &text,
                      helper::CodePage code_page = helper::curr_code_page());

        bool set_text(HWND status_handle,
                      uint8_t index,
                      StatusTextFlag flag,
                      std::wstring &text);

        std::pair<uint32_t, StatusTextFlag> get_text_len(HWND status_handle,
                                                         uint8_t index);

        void
        get_tip_text(HWND status_handle,
                     uint8_t index,
                     std::string &text,
                     helper::CodePage code_page = helper::curr_code_page());

        void
        get_tip_text(HWND status_handle, uint8_t index, std::wstring &text);

        void
        set_tip_text(HWND status_handle,
                     uint8_t index,
                     std::string &text,
                     helper::CodePage code_page = helper::curr_code_page());

        void
        set_tip_text(HWND status_handle, uint8_t index, std::wstring &text);

        bool is_ansi_format(HWND status_handle);

        bool is_unicode_format(HWND status_handle);

        void set_ansi_format(HWND status_handle);

        void set_unicode_format(HWND status_handle);

        bool is_simple(HWND status_handle);

        void show_simple(HWND status_handle);

        void show_parts(HWND status_handle);

        [[nodiscard]] uint32_t err_code() const;

        [[nodiscard]] std::string err_string() const;

        [[nodiscard]] std::wstring err_wstring() const;
    };
} // namespace YanLib::ui::components
#endif // STATUS_H
