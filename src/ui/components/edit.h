/* clang-format off */
/*
 * @file edit.h
 * @date 2025-05-25
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
#ifndef EDIT_H
#define EDIT_H
#ifndef UNICODE
#define UNICODE
#endif
#ifndef _UNICODE
#define _UNICODE
#endif
#include <Windows.h>
#include <WinUser.h>
#include <CommCtrl.h>
#include <minwindef.h>
#include <windef.h>
#include <cstdint>
#include <vector>
#include <string>
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
    class edit {
    private:
        std::vector<HWND> edit_handles = {};
        sync::rwlock edit_rwlock = {};
        uint32_t error_code = 0;

    public:
        edit(const edit &other) = delete;

        edit(edit &&other) = delete;

        edit &operator=(const edit &other) = delete;

        edit &operator=(edit &&other) = delete;

        edit() = default;

        ~edit();

        HWND line(uintptr_t edit_id,
                  HWND parent_window_handle,
                  LPARAM lparam,
                  int32_t x,
                  int32_t y,
                  int32_t width,
                  int32_t height,
                  EditStyle style = EditStyle::AutoHScroll | EditStyle::Left,
                  core::WindowStyle window_style = core::WindowStyle::Child |
                          core::WindowStyle::Visible | core::WindowStyle::Border);

        HWND line(const char *edit_name,
                  uintptr_t edit_id,
                  HWND parent_window_handle,
                  LPARAM lparam,
                  int32_t x,
                  int32_t y,
                  int32_t width,
                  int32_t height,
                  EditStyle style = EditStyle::AutoHScroll | EditStyle::Left,
                  core::WindowStyle window_style = core::WindowStyle::Child |
                          core::WindowStyle::Visible | core::WindowStyle::Border);

        HWND line(const wchar_t *edit_name,
                  uintptr_t edit_id,
                  HWND parent_window_handle,
                  LPARAM lparam,
                  int32_t x,
                  int32_t y,
                  int32_t width,
                  int32_t height,
                  EditStyle style = EditStyle::AutoHScroll | EditStyle::Left,
                  core::WindowStyle window_style = core::WindowStyle::Child |
                          core::WindowStyle::Visible | core::WindowStyle::Border);

        HWND multi_line(uintptr_t edit_id,
                        HWND parent_window_handle,
                        LPARAM lparam,
                        int32_t x,
                        int32_t y,
                        int32_t width,
                        int32_t height,
                        EditStyle style = EditStyle::Multiline |
                                EditStyle::AutoHScroll |
                                EditStyle::AutoVScroll | EditStyle::Left |
                                EditStyle::WantReturn,
                        core::WindowStyle window_style = core::WindowStyle::Child |
                                core::WindowStyle::Visible | core::WindowStyle::Border |
                                core::WindowStyle::HScroll | core::WindowStyle::VScroll);

        HWND multi_line(const char *edit_name,
                        uintptr_t edit_id,
                        HWND parent_window_handle,
                        LPARAM lparam,
                        int32_t x,
                        int32_t y,
                        int32_t width,
                        int32_t height,
                        EditStyle style = EditStyle::Multiline |
                                EditStyle::AutoHScroll |
                                EditStyle::AutoVScroll | EditStyle::Left |
                                EditStyle::WantReturn,
                        core::WindowStyle window_style = core::WindowStyle::Child |
                                core::WindowStyle::Visible | core::WindowStyle::Border |
                                core::WindowStyle::HScroll | core::WindowStyle::VScroll);

        HWND multi_line(const wchar_t *edit_name,
                        uintptr_t edit_id,
                        HWND parent_window_handle,
                        LPARAM lparam,
                        int32_t x,
                        int32_t y,
                        int32_t width,
                        int32_t height,
                        EditStyle style = EditStyle::Multiline |
                                EditStyle::AutoHScroll |
                                EditStyle::AutoVScroll | EditStyle::Left |
                                EditStyle::WantReturn,
                        core::WindowStyle window_style = core::WindowStyle::Child |
                                core::WindowStyle::Visible | core::WindowStyle::Border |
                                core::WindowStyle::HScroll | core::WindowStyle::VScroll);

        HWND password(uintptr_t edit_id,
                      HWND parent_window_handle,
                      LPARAM lparam,
                      int32_t x,
                      int32_t y,
                      int32_t width,
                      int32_t height,
                      EditStyle style = EditStyle::Password |
                              EditStyle::AutoHScroll | EditStyle::Left,
                      core::WindowStyle window_style = core::WindowStyle::Child |
                              core::WindowStyle::Visible | core::WindowStyle::Border);

        HWND password(const char *edit_name,
                      uintptr_t edit_id,
                      HWND parent_window_handle,
                      LPARAM lparam,
                      int32_t x,
                      int32_t y,
                      int32_t width,
                      int32_t height,
                      EditStyle style = EditStyle::Password |
                              EditStyle::AutoHScroll | EditStyle::Left,
                      core::WindowStyle window_style = core::WindowStyle::Child |
                              core::WindowStyle::Visible | core::WindowStyle::Border);

        HWND password(const wchar_t *edit_name,
                      uintptr_t edit_id,
                      HWND parent_window_handle,
                      LPARAM lparam,
                      int32_t x,
                      int32_t y,
                      int32_t width,
                      int32_t height,
                      EditStyle style = EditStyle::Password |
                              EditStyle::AutoHScroll | EditStyle::Left,
                      core::WindowStyle window_style = core::WindowStyle::Child |
                              core::WindowStyle::Visible | core::WindowStyle::Border);

        bool destroy(HWND edit_handle);

        bool enable(HWND edit_handle);

        bool disable(HWND edit_handle);

        bool can_undo(HWND edit_handle);

        void clear_undo(HWND edit_handle);

        bool undo(HWND edit_handle);

        int32_t get_line(HWND edit_handle,
                         std::string &line,
                         int32_t lineno = 0,
                         helper::CodePage code_page = helper::curr_code_page());

        int32_t
        get_line(HWND edit_handle, std::wstring &line, int32_t lineno = 0);

        int32_t get_line_len(HWND edit_handle, int32_t lineno = 0);

        int32_t get_first_visible_line(HWND edit_handle);

        int32_t get_line_count(HWND edit_handle);

        int32_t get_char_index(HWND edit_handle, int32_t lineno = -1);

        int32_t get_lineno(HWND edit_handle, int32_t char_index);

        void format(HWND edit_handle, bool add_eof = true);

        int32_t get_text(HWND edit_handle, std::string &text);

        int32_t get_text(HWND edit_handle, std::wstring &text);

        bool set_text(HWND edit_handle, std::string &text);

        bool set_text(HWND edit_handle, std::wstring &text);

        int32_t get_text_len(HWND edit_handle);

        void set_text_limit(HWND edit_handle, int32_t limit);

        bool get_prompt_banner(
                HWND edit_handle,
                std::string &banner,
                helper::CodePage code_page = helper::curr_code_page());

        bool get_prompt_banner(HWND edit_handle, std::wstring &banner);

        bool set_prompt_banner(
                HWND edit_handle,
                std::string &banner,
                helper::CodePage code_page = helper::curr_code_page());

        bool set_prompt_banner(HWND edit_handle, std::wstring &banner);

        bool set_prompt_banner_focused(
                HWND edit_handle,
                std::string &banner,
                helper::CodePage code_page = helper::curr_code_page(),
                bool is_redraw = true);

        bool set_prompt_banner_focused(HWND edit_handle,
                                       std::wstring &banner,
                                       bool is_redraw = true);

        void take_focus(HWND edit_handle);

        void no_set_focus(HWND edit_handle);

        bool set_read_only(HWND edit_handle);

        bool unset_read_only(HWND edit_handle);

        void set_tab_stops(HWND edit_handle, std::vector<int32_t> &tab_stops);

        HLOCAL get_handle(HWND edit_handle);

        void set_handle(HWND edit_handle, HLOCAL mem_handle);

        // std::pair<start, end>
        std::pair<int32_t, int32_t> get_hilite(HWND edit_handle);

        void set_hilite(HWND edit_handle, int32_t start, int32_t end);

        bool get_modify(HWND edit_handle);

        void set_modify(HWND edit_handle, bool modify);

        wchar_t get_password_char(HWND edit_handle);

        void set_password_char(HWND edit_handle, wchar_t ch);

        void get_rect(HWND edit_handle, RECT *rect);

        void set_rect(HWND edit_handle, RECT *rect);

        void set_rect_no_paint(HWND edit_handle, RECT *rect);

        void reset_rect(HWND edit_handle);

        // std::pair<start, end>
        std::pair<int32_t, int32_t> get_select(HWND edit_handle);

        void set_select(HWND edit_handle, int32_t start, int32_t end);

        void
        replace_select(HWND edit_handle,
                       std::string &text,
                       helper::CodePage code_page = helper::curr_code_page());

        void replace_select(HWND edit_handle, std::wstring &text);

        EDITWORDBREAKPROC get_word_break_proc(HWND edit_handle);

        void set_word_break_proc(HWND edit_handle,
                                 EDITWORDBREAKPROC word_break_proc);

        bool show_balloon_tip(HWND edit_handle, EDITBALLOONTIP *balloon_tip);

        bool hide_balloon_tip(HWND edit_handle);

        void scroll(HWND edit_handle, int32_t vert, int32_t horiz);

        void scroll_caret(HWND edit_handle);

        [[nodiscard]] uint32_t err_code() const;

        [[nodiscard]] std::string err_string() const;

        [[nodiscard]] std::wstring err_wstring() const;
    };
} // namespace YanLib::ui::components
#endif // EDIT_H
