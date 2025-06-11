/* clang-format off */
/*
 * @file edit.cpp
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
#include "edit.h"
#include <windowsx.h>

namespace YanLib::ui::components {
    edit::~edit() {
        for (auto &handle : edit_handles) {
            if (handle && IsWindow(handle)) {
                DestroyWindow(handle);
                handle = nullptr;
            }
        }
        edit_handles.clear();
    }

    HWND edit::line(uintptr_t edit_id,
                    HWND parent_window_handle,
                    LPARAM lparam,
                    int32_t x,
                    int32_t y,
                    int32_t width,
                    int32_t height,
                    EditStyle style,
                    WindowStyle window_style) {
        HWND result = CreateWindowExW(0L, L"EDIT", nullptr,
                                      static_cast<uint32_t>(window_style) |
                                              static_cast<uint32_t>(style),
                                      x, y, width, height, parent_window_handle,
                                      reinterpret_cast<HMENU>(edit_id),
                                      reinterpret_cast<CREATESTRUCT *>(lparam)
                                              ->hInstance,
                                      nullptr);
        if (!result) {
            error_code = GetLastError();
            return nullptr;
        }
        edit_rwlock.write_lock();
        edit_handles.push_back(result);
        edit_rwlock.write_unlock();
        return result;
    }

    HWND edit::line(const char *edit_name,
                    uintptr_t edit_id,
                    HWND parent_window_handle,
                    LPARAM lparam,
                    int32_t x,
                    int32_t y,
                    int32_t width,
                    int32_t height,
                    EditStyle style,
                    WindowStyle window_style) {
        HWND result = CreateWindowExA(0L, "EDIT", edit_name,
                                      static_cast<uint32_t>(window_style) |
                                              static_cast<uint32_t>(style),
                                      x, y, width, height, parent_window_handle,
                                      reinterpret_cast<HMENU>(edit_id),
                                      reinterpret_cast<CREATESTRUCT *>(lparam)
                                              ->hInstance,
                                      nullptr);
        if (!result) {
            error_code = GetLastError();
            return nullptr;
        }
        edit_rwlock.write_lock();
        edit_handles.push_back(result);
        edit_rwlock.write_unlock();
        return result;
    }

    HWND edit::line(const wchar_t *edit_name,
                    uintptr_t edit_id,
                    HWND parent_window_handle,
                    LPARAM lparam,
                    int32_t x,
                    int32_t y,
                    int32_t width,
                    int32_t height,
                    EditStyle style,
                    WindowStyle window_style) {
        HWND result = CreateWindowExW(0L, L"EDIT", edit_name,
                                      static_cast<uint32_t>(window_style) |
                                              static_cast<uint32_t>(style),
                                      x, y, width, height, parent_window_handle,
                                      reinterpret_cast<HMENU>(edit_id),
                                      reinterpret_cast<CREATESTRUCT *>(lparam)
                                              ->hInstance,
                                      nullptr);
        if (!result) {
            error_code = GetLastError();
            return nullptr;
        }
        edit_rwlock.write_lock();
        edit_handles.push_back(result);
        edit_rwlock.write_unlock();
        return result;
    }

    HWND edit::multi_line(uintptr_t edit_id,
                          HWND parent_window_handle,
                          LPARAM lparam,
                          int32_t x,
                          int32_t y,
                          int32_t width,
                          int32_t height,
                          EditStyle style,
                          WindowStyle window_style) {
        HWND result = CreateWindowExW(0L, L"EDIT", nullptr,
                                      static_cast<uint32_t>(window_style) |
                                              static_cast<uint32_t>(style),
                                      x, y, width, height, parent_window_handle,
                                      reinterpret_cast<HMENU>(edit_id),
                                      reinterpret_cast<CREATESTRUCT *>(lparam)
                                              ->hInstance,
                                      nullptr);
        if (!result) {
            error_code = GetLastError();
            return nullptr;
        }
        edit_rwlock.write_lock();
        edit_handles.push_back(result);
        edit_rwlock.write_unlock();
        return result;
    }

    HWND edit::multi_line(const char *edit_name,
                          uintptr_t edit_id,
                          HWND parent_window_handle,
                          LPARAM lparam,
                          int32_t x,
                          int32_t y,
                          int32_t width,
                          int32_t height,
                          EditStyle style,
                          WindowStyle window_style) {
        HWND result = CreateWindowExA(0L, "EDIT", edit_name,
                                      static_cast<uint32_t>(window_style) |
                                              static_cast<uint32_t>(style),
                                      x, y, width, height, parent_window_handle,
                                      reinterpret_cast<HMENU>(edit_id),
                                      reinterpret_cast<CREATESTRUCT *>(lparam)
                                              ->hInstance,
                                      nullptr);
        if (!result) {
            error_code = GetLastError();
            return nullptr;
        }
        edit_rwlock.write_lock();
        edit_handles.push_back(result);
        edit_rwlock.write_unlock();
        return result;
    }

    HWND edit::multi_line(const wchar_t *edit_name,
                          uintptr_t edit_id,
                          HWND parent_window_handle,
                          LPARAM lparam,
                          int32_t x,
                          int32_t y,
                          int32_t width,
                          int32_t height,
                          EditStyle style,
                          WindowStyle window_style) {
        HWND result = CreateWindowExW(0L, L"EDIT", edit_name,
                                      static_cast<uint32_t>(window_style) |
                                              static_cast<uint32_t>(style),
                                      x, y, width, height, parent_window_handle,
                                      reinterpret_cast<HMENU>(edit_id),
                                      reinterpret_cast<CREATESTRUCT *>(lparam)
                                              ->hInstance,
                                      nullptr);
        if (!result) {
            error_code = GetLastError();
            return nullptr;
        }
        edit_rwlock.write_lock();
        edit_handles.push_back(result);
        edit_rwlock.write_unlock();
        return result;
    }

    HWND edit::password(uintptr_t edit_id,
                        HWND parent_window_handle,
                        LPARAM lparam,
                        int32_t x,
                        int32_t y,
                        int32_t width,
                        int32_t height,
                        EditStyle style,
                        WindowStyle window_style) {
        HWND result = CreateWindowExW(0L, L"EDIT", nullptr,
                                      static_cast<uint32_t>(window_style) |
                                              static_cast<uint32_t>(style),
                                      x, y, width, height, parent_window_handle,
                                      reinterpret_cast<HMENU>(edit_id),
                                      reinterpret_cast<CREATESTRUCT *>(lparam)
                                              ->hInstance,
                                      nullptr);
        if (!result) {
            error_code = GetLastError();
            return nullptr;
        }
        edit_rwlock.write_lock();
        edit_handles.push_back(result);
        edit_rwlock.write_unlock();
        return result;
    }

    HWND edit::password(const char *edit_name,
                        uintptr_t edit_id,
                        HWND parent_window_handle,
                        LPARAM lparam,
                        int32_t x,
                        int32_t y,
                        int32_t width,
                        int32_t height,
                        EditStyle style,
                        WindowStyle window_style) {
        HWND result = CreateWindowExA(0L, "EDIT", edit_name,
                                      static_cast<uint32_t>(window_style) |
                                              static_cast<uint32_t>(style),
                                      x, y, width, height, parent_window_handle,
                                      reinterpret_cast<HMENU>(edit_id),
                                      reinterpret_cast<CREATESTRUCT *>(lparam)
                                              ->hInstance,
                                      nullptr);
        if (!result) {
            error_code = GetLastError();
            return nullptr;
        }
        edit_rwlock.write_lock();
        edit_handles.push_back(result);
        edit_rwlock.write_unlock();
        return result;
    }

    HWND edit::password(const wchar_t *edit_name,
                        uintptr_t edit_id,
                        HWND parent_window_handle,
                        LPARAM lparam,
                        int32_t x,
                        int32_t y,
                        int32_t width,
                        int32_t height,
                        EditStyle style,
                        WindowStyle window_style) {
        HWND result = CreateWindowExW(0L, L"EDIT", edit_name,
                                      static_cast<uint32_t>(window_style) |
                                              static_cast<uint32_t>(style),
                                      x, y, width, height, parent_window_handle,
                                      reinterpret_cast<HMENU>(edit_id),
                                      reinterpret_cast<CREATESTRUCT *>(lparam)
                                              ->hInstance,
                                      nullptr);
        if (!result) {
            error_code = GetLastError();
            return nullptr;
        }
        edit_rwlock.write_lock();
        edit_handles.push_back(result);
        edit_rwlock.write_unlock();
        return result;
    }

    bool edit::destroy(HWND edit_handle) {
        if (!edit_handle || !IsWindow(edit_handle)) {
            return false;
        }
        edit_rwlock.write_lock();
        const auto it = std::find(edit_handles.begin(), edit_handles.end(),
                                  edit_handle);
        if (it != edit_handles.end()) {
            *it = nullptr;
        }
        edit_rwlock.write_unlock();
        if (!DestroyWindow(edit_handle)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool edit::enable(HWND edit_handle) {
        return Edit_Enable(edit_handle, TRUE);
    }

    bool edit::disable(HWND edit_handle) {
        return Edit_Enable(edit_handle, FALSE);
    }

    bool edit::can_undo(HWND edit_handle) {
        return Edit_CanUndo(edit_handle);
    }

    void edit::clear_undo(HWND edit_handle) {
        Edit_EmptyUndoBuffer(edit_handle);
    }

    bool edit::undo(HWND edit_handle) {
        return Edit_Undo(edit_handle);
    }

    int32_t edit::get_line(HWND edit_handle,
                           std::string &line,
                           int32_t lineno,
                           helper::CodePage code_page) {
        std::wstring temp(line.size(), L'\0');
        const int32_t result =
                Edit_GetLine(edit_handle, lineno, temp.data(), temp.size());
        line.clear();
        line = helper::convert::wstr_to_str(temp, code_page);
        return result;
    }

    int32_t
    edit::get_line(HWND edit_handle, std::wstring &line, int32_t lineno) {
        return Edit_GetLine(edit_handle, lineno, line.data(), line.size());
    }

    int32_t edit::get_line_len(HWND edit_handle, int32_t lineno) {
        return Edit_LineLength(edit_handle, lineno);
    }

    int32_t edit::get_first_visible_line(HWND edit_handle) {
        return Edit_GetFirstVisibleLine(edit_handle);
    }

    int32_t edit::get_line_count(HWND edit_handle) {
        return Edit_GetLineCount(edit_handle);
    }

    int32_t edit::get_char_index(HWND edit_handle, int32_t lineno) {
        return Edit_LineIndex(edit_handle, lineno);
    }

    int32_t edit::get_lineno(HWND edit_handle, int32_t char_index) {
        return Edit_LineFromChar(edit_handle, char_index);
    }

    void edit::format(HWND edit_handle, bool add_eof) {
        Edit_FmtLines(edit_handle, add_eof ? TRUE : FALSE);
    }

    int32_t edit::get_text(HWND edit_handle, std::string &text) {
        const int32_t result =
                GetWindowTextA(edit_handle, text.data(),
                               static_cast<int32_t>(text.size()));
        if (!result) {
            error_code = GetLastError();
        }
        return result;
    }

    int32_t edit::get_text(HWND edit_handle, std::wstring &text) {
        const int32_t result =
                GetWindowTextW(edit_handle, text.data(),
                               static_cast<int32_t>(text.size()));
        if (!result) {
            error_code = GetLastError();
        }
        return result;
    }

    bool edit::set_text(HWND edit_handle, std::string &text) {
        if (!SetWindowTextA(edit_handle, text.data())) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool edit::set_text(HWND edit_handle, std::wstring &text) {
        if (!SetWindowTextW(edit_handle, text.data())) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    int32_t edit::get_text_len(HWND edit_handle) {
        SetLastError(ERROR_SUCCESS);
        const int32_t result = Edit_GetTextLength(edit_handle);
        error_code = GetLastError();
        return result;
    }

    void edit::set_text_limit(HWND edit_handle, int32_t limit) {
        Edit_LimitText(edit_handle, limit);
    }

    bool edit::get_prompt_banner(HWND edit_handle,
                                 std::string &banner,
                                 helper::CodePage code_page) {
        std::wstring temp(banner.size(), L'\0');
        const auto result =
                Edit_GetCueBannerText(edit_handle, temp.data(), temp.size());
        banner.clear();
        banner = helper::convert::wstr_to_str(temp, code_page);
        return result;
    }

    bool edit::get_prompt_banner(HWND edit_handle, std::wstring &banner) {
        return Edit_GetCueBannerText(edit_handle, banner.data(), banner.size());
    }

    bool edit::set_prompt_banner(HWND edit_handle,
                                 std::string &banner,
                                 helper::CodePage code_page) {
        auto temp = helper::convert::str_to_wstr(banner, code_page);
        return Edit_SetCueBannerText(edit_handle, temp.data());
    }

    bool edit::set_prompt_banner(HWND edit_handle, std::wstring &banner) {
        return Edit_SetCueBannerText(edit_handle, banner.data());
    }

    bool edit::set_prompt_banner_focused(HWND edit_handle,
                                         std::string &banner,
                                         helper::CodePage code_page,
                                         bool is_redraw) {
        auto temp = helper::convert::str_to_wstr(banner, code_page);
        return Edit_SetCueBannerTextFocused(edit_handle, temp.data(),
                                            is_redraw ? TRUE : FALSE);
    }

    bool edit::set_prompt_banner_focused(HWND edit_handle,
                                         std::wstring &banner,
                                         bool is_redraw) {
        return Edit_SetCueBannerTextFocused(edit_handle, banner.data(),
                                            is_redraw ? TRUE : FALSE);
    }

    void edit::take_focus(HWND edit_handle) {
        Edit_TakeFocus(edit_handle);
    }

    void edit::no_set_focus(HWND edit_handle) {
        Edit_NoSetFocus(edit_handle);
    }

    bool edit::set_read_only(HWND edit_handle) {
        return Edit_SetReadOnly(edit_handle, TRUE);
    }

    bool edit::unset_read_only(HWND edit_handle) {
        return Edit_SetReadOnly(edit_handle, FALSE);
    }

    void edit::set_tab_stops(HWND edit_handle,
                             std::vector<int32_t> &tab_stops) {
        Edit_SetTabStops(edit_handle, tab_stops.size(), tab_stops.data());
    }

    HLOCAL edit::get_handle(HWND edit_handle) {
        return Edit_GetHandle(edit_handle);
    }

    void edit::set_handle(HWND edit_handle, HLOCAL mem_handle) {
        Edit_SetHandle(edit_handle, mem_handle);
    }

    std::pair<int32_t, int32_t> edit::get_hilite(HWND edit_handle) {
        const uint32_t result = Edit_GetHilite(edit_handle);
        return std::make_pair(LOWORD(result), HIWORD(result));
    }

    void edit::set_hilite(HWND edit_handle, int32_t start, int32_t end) {
        Edit_SetHilite(edit_handle, start, end);
    }

    bool edit::get_modify(HWND edit_handle) {
        return Edit_GetModify(edit_handle);
    }

    void edit::set_modify(HWND edit_handle, bool modify) {
        Edit_SetModify(edit_handle, modify ? TRUE : FALSE);
    }

    wchar_t edit::get_password_char(HWND edit_handle) {
        return Edit_GetPasswordChar(edit_handle);
    }

    void edit::set_password_char(HWND edit_handle, wchar_t ch) {
        Edit_SetPasswordChar(edit_handle, ch);
    }

    void edit::get_rect(HWND edit_handle, RECT *rect) {
        Edit_GetRect(edit_handle, rect);
    }

    void edit::set_rect(HWND edit_handle, RECT *rect) {
        Edit_SetRect(edit_handle, rect);
    }

    void edit::set_rect_no_paint(HWND edit_handle, RECT *rect) {
        Edit_SetRectNoPaint(edit_handle, rect);
    }

    void edit::reset_rect(HWND edit_handle) {
        Edit_SetRect(edit_handle, nullptr);
    }

    std::pair<int32_t, int32_t> edit::get_select(HWND edit_handle) {
        const uint32_t result = Edit_GetSel(edit_handle);
        if (result == static_cast<uint32_t>(-1)) {
            return std::make_pair(0, 0);
        }
        return std::make_pair(LOWORD(result), HIWORD(result));
    }

    void edit::set_select(HWND edit_handle, int32_t start, int32_t end) {
        Edit_SetSel(edit_handle, start, end);
    }

    void edit::replace_select(HWND edit_handle,
                              std::string &text,
                              helper::CodePage code_page) {
        auto temp = helper::convert::str_to_wstr(text, code_page);
        Edit_ReplaceSel(edit_handle, temp.data());
    }

    void edit::replace_select(HWND edit_handle, std::wstring &text) {
        Edit_ReplaceSel(edit_handle, text.data());
    }

    EDITWORDBREAKPROC edit::get_word_break_proc(HWND edit_handle) {
        return Edit_GetWordBreakProc(edit_handle);
    }

    void edit::set_word_break_proc(HWND edit_handle,
                                   EDITWORDBREAKPROC word_break_proc) {
        Edit_SetWordBreakProc(edit_handle, word_break_proc);
    }

    bool edit::show_balloon_tip(HWND edit_handle, EDITBALLOONTIP *balloon_tip) {
        return Edit_ShowBalloonTip(edit_handle, balloon_tip);
    }

    bool edit::hide_balloon_tip(HWND edit_handle) {
        return Edit_HideBalloonTip(edit_handle);
    }

    void edit::scroll(HWND edit_handle, int32_t vert, int32_t horiz) {
        Edit_Scroll(edit_handle, vert, horiz);
    }

    void edit::scroll_caret(HWND edit_handle) {
        Edit_ScrollCaret(edit_handle);
    }

    uint32_t edit::err_code() const {
        return error_code;
    }

    std::string edit::err_string() const {
        std::string result = helper::convert::err_string(error_code);
        return result;
    }

    std::wstring edit::err_wstring() const {
        std::wstring result = helper::convert::err_wstring(error_code);
        return result;
    }
} // namespace YanLib::ui::components
