/* clang-format off */
/*
 * @file tool_tips.cpp
 * @date 2025-06-02
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
#include "tool_tips.h"
#include <windowsx.h>

namespace YanLib::ui::components {
    tool_tips::tool_tips() {
        INITCOMMONCONTROLSEX icc = {};
        icc.dwSize = sizeof(INITCOMMONCONTROLSEX);
        icc.dwICC = ICC_BAR_CLASSES;
        InitCommonControlsEx(&icc);
    }

    tool_tips::~tool_tips() {
        for (auto &handle : tool_tips_handles) {
            if (handle && IsWindow(handle)) {
                DestroyWindow(handle);
                handle = nullptr;
            }
        }
        tool_tips_handles.clear();
    }

    HWND tool_tips::create(HWND parent_window_handle,
                           LPARAM lparam,
                           int32_t x,
                           int32_t y,
                           int32_t width,
                           int32_t height,
                           ToolTipStyle style,
                           core::WindowStyle window_style) {
        HWND result = CreateWindowExW(
                0L, L"tooltips_class32", nullptr,
                static_cast<uint32_t>(window_style) |
                        static_cast<uint32_t>(style),
                x, y, width, height, parent_window_handle, nullptr,
                reinterpret_cast<CREATESTRUCT *>(lparam)->hInstance, nullptr);
        if (!result) {
            error_code = GetLastError();
            return nullptr;
        }
        tool_tips_rwlock.write_lock();
        tool_tips_handles.push_back(result);
        tool_tips_rwlock.write_unlock();
        return result;
    }

    HWND tool_tips::create(const char *tool_tips_name,
                           HWND parent_window_handle,
                           LPARAM lparam,
                           int32_t x,
                           int32_t y,
                           int32_t width,
                           int32_t height,
                           ToolTipStyle style,
                           core::WindowStyle window_style) {
        HWND result = CreateWindowExA(
                0L, "tooltips_class32", tool_tips_name,
                static_cast<uint32_t>(window_style) |
                        static_cast<uint32_t>(style),
                x, y, width, height, parent_window_handle, nullptr,
                reinterpret_cast<CREATESTRUCT *>(lparam)->hInstance, nullptr);
        if (!result) {
            error_code = GetLastError();
            return nullptr;
        }
        tool_tips_rwlock.write_lock();
        tool_tips_handles.push_back(result);
        tool_tips_rwlock.write_unlock();
        return result;
    }

    HWND tool_tips::create(const wchar_t *tool_tips_name,
                           HWND parent_window_handle,
                           LPARAM lparam,
                           int32_t x,
                           int32_t y,
                           int32_t width,
                           int32_t height,
                           ToolTipStyle style,
                           core::WindowStyle window_style) {
        HWND result = CreateWindowExW(
                0L, L"tooltips_class32", tool_tips_name,
                static_cast<uint32_t>(window_style) |
                        static_cast<uint32_t>(style),
                x, y, width, height, parent_window_handle, nullptr,
                reinterpret_cast<CREATESTRUCT *>(lparam)->hInstance, nullptr);
        if (!result) {
            error_code = GetLastError();
            return nullptr;
        }
        tool_tips_rwlock.write_lock();
        tool_tips_handles.push_back(result);
        tool_tips_rwlock.write_unlock();
        return result;
    }

    bool tool_tips::destroy(HWND tool_tips_handle) {
        if (!tool_tips_handle || !IsWindow(tool_tips_handle)) {
            return false;
        }
        tool_tips_rwlock.write_lock();
        const auto it = std::find(tool_tips_handles.begin(),
                                  tool_tips_handles.end(), tool_tips_handle);
        if (it != tool_tips_handles.end()) {
            *it = nullptr;
        }
        tool_tips_rwlock.write_unlock();
        if (!DestroyWindow(tool_tips_handle)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    void tool_tips::activate(HWND tool_tips_handle) {
        SendMessageW(tool_tips_handle, TTM_ACTIVATE, TRUE, 0);
    }

    void tool_tips::deactivate(HWND tool_tips_handle) {
        SendMessageW(tool_tips_handle, TTM_ACTIVATE, FALSE, 0);
    }

    TTTOOLINFOA tool_tips::make_info(uintptr_t id,
                                     HWND parent_window_handle,
                                     HINSTANCE instance_handle,
                                     RECT rect,
                                     std::string &text,
                                     LPARAM lparam,
                                     TTInfoFlag flag) {
        TTTOOLINFOA info = {};
        info.cbSize = sizeof(TTTOOLINFOA);
        info.uFlags = static_cast<uint32_t>(flag);
        info.hwnd = parent_window_handle;
        info.uId = id;
        info.rect = rect;
        info.hinst = instance_handle;
        info.lpszText = text.data();
        info.lParam = lparam;
        info.lpReserved = nullptr;
        return info;
    }

    TTTOOLINFOW tool_tips::make_info(uintptr_t id,
                                     HWND parent_window_handle,
                                     HINSTANCE instance_handle,
                                     RECT rect,
                                     std::wstring &text,
                                     LPARAM lparam,
                                     TTInfoFlag flag) {
        TTTOOLINFOW info = {};
        info.cbSize = sizeof(TTTOOLINFOW);
        info.uFlags = static_cast<uint32_t>(flag);
        info.hwnd = parent_window_handle;
        info.uId = id;
        info.rect = rect;
        info.hinst = instance_handle;
        info.lpszText = text.data();
        info.lParam = lparam;
        info.lpReserved = nullptr;
        return info;
    }

    void tool_tips::activate_track(HWND tool_tips_handle,
                                   TTTOOLINFOW *tool_tips) {
        SendMessageW(tool_tips_handle, TTM_TRACKACTIVATE, TRUE,
                     reinterpret_cast<LPARAM>(tool_tips));
    }

    void tool_tips::deactivate_track(HWND tool_tips_handle,
                                     TTTOOLINFOW *tool_tips) {
        SendMessageW(tool_tips_handle, TTM_TRACKACTIVATE, FALSE,
                     reinterpret_cast<LPARAM>(tool_tips));
    }

    void tool_tips::set_track_pos(HWND tool_tips_handle, POINT point) {
        SendMessageW(tool_tips_handle, TTM_TRACKPOSITION, 0,
                     MAKELPARAM(point.x, point.y));
    }

    bool tool_tips::add_tool(HWND tool_tips_handle, TTTOOLINFOA *tool_tips) {
        return SendMessageW(tool_tips_handle, TTM_ADDTOOLA, 0,
                            reinterpret_cast<LPARAM>(tool_tips));
    }

    bool tool_tips::add_tool(HWND tool_tips_handle, TTTOOLINFOW *tool_tips) {
        return SendMessageW(tool_tips_handle, TTM_ADDTOOLW, 0,
                            reinterpret_cast<LPARAM>(tool_tips));
    }

    void tool_tips::delete_tool(HWND tool_tips_handle, TTTOOLINFOA *tool_tips) {
        SendMessageW(tool_tips_handle, TTM_DELTOOLA, 0,
                     reinterpret_cast<LPARAM>(tool_tips));
    }

    void tool_tips::delete_tool(HWND tool_tips_handle, TTTOOLINFOW *tool_tips) {
        SendMessageW(tool_tips_handle, TTM_DELTOOLW, 0,
                     reinterpret_cast<LPARAM>(tool_tips));
    }

    bool tool_tips::enum_tool(HWND tool_tips_handle,
                              int64_t index,
                              TTTOOLINFOA *tool_info) {
        return SendMessageW(tool_tips_handle, TTM_ENUMTOOLSA, index,
                            reinterpret_cast<LPARAM>(tool_info));
    }

    bool tool_tips::enum_tool(HWND tool_tips_handle,
                              int64_t index,
                              TTTOOLINFOW *tool_info) {
        return SendMessageW(tool_tips_handle, TTM_ENUMTOOLSW, index,
                            reinterpret_cast<LPARAM>(tool_info));
    }

    int64_t tool_tips::get_tool_count(HWND tool_tips_handle) {
        return SendMessageW(tool_tips_handle, TTM_GETTOOLCOUNT, 0, 0);
    }

    bool tool_tips::get_tool_info(HWND tool_tips_handle,
                                  TTTOOLINFOA *tool_info) {
        return SendMessageW(tool_tips_handle, TTM_GETTOOLINFOA, 0,
                            reinterpret_cast<LPARAM>(tool_info));
    }

    bool tool_tips::get_tool_info(HWND tool_tips_handle,
                                  TTTOOLINFOW *tool_info) {
        return SendMessageW(tool_tips_handle, TTM_GETTOOLINFOW, 0,
                            reinterpret_cast<LPARAM>(tool_info));
    }

    void tool_tips::set_tool_info(HWND tool_tips_handle,
                                  TTTOOLINFOA *tool_info) {
        SendMessageW(tool_tips_handle, TTM_SETTOOLINFOA, 0,
                     reinterpret_cast<LPARAM>(tool_info));
    }

    void tool_tips::set_tool_info(HWND tool_tips_handle,
                                  TTTOOLINFOW *tool_info) {
        SendMessageW(tool_tips_handle, TTM_SETTOOLINFOW, 0,
                     reinterpret_cast<LPARAM>(tool_info));
    }

    void tool_tips::set_tool_rect(HWND tool_tips_handle,
                                  TTTOOLINFOA *tool_info) {
        SendMessageW(tool_tips_handle, TTM_NEWTOOLRECTA, 0,
                     reinterpret_cast<LPARAM>(tool_info));
    }

    void tool_tips::set_tool_rect(HWND tool_tips_handle,
                                  TTTOOLINFOW *tool_info) {
        SendMessageW(tool_tips_handle, TTM_NEWTOOLRECTW, 0,
                     reinterpret_cast<LPARAM>(tool_info));
    }

    void tool_tips::get_margin(HWND tool_tips_handle, RECT *rect) {
        SendMessageW(tool_tips_handle, TTM_GETMARGIN, 0,
                     reinterpret_cast<LPARAM>(rect));
    }

    void tool_tips::set_margin(HWND tool_tips_handle, RECT *rect) {
        SendMessageW(tool_tips_handle, TTM_SETMARGIN, 0,
                     reinterpret_cast<LPARAM>(rect));
    }

    int32_t tool_tips::get_delay_time(HWND tool_tips_handle,
                                      TTDelayTime delay_time) {
        return static_cast<int32_t>(
                SendMessageW(tool_tips_handle, TTM_GETDELAYTIME,
                             static_cast<uint32_t>(delay_time), 0));
    }

    void tool_tips::set_delay_time(HWND tool_tips_handle,
                                   TTDelayTime delay_time,
                                   int32_t delay_ms) {
        SendMessageW(tool_tips_handle, TTM_SETDELAYTIME,
                     static_cast<uint32_t>(delay_time), delay_ms);
    }

    int64_t tool_tips::get_max_tip_width(HWND tool_tips_handle) {
        return SendMessageW(tool_tips_handle, TTM_GETMAXTIPWIDTH, 0, 0);
    }

    int64_t tool_tips::get_max_tip_width(HWND tool_tips_handle, int64_t width) {
        return SendMessageW(tool_tips_handle, TTM_SETMAXTIPWIDTH, 0, width);
    }

    COLORREF tool_tips::get_tip_background_color(HWND tool_tips_handle) {
        return SendMessageW(tool_tips_handle, TTM_GETTIPBKCOLOR, 0, 0);
    }

    void tool_tips::set_tip_background_color(HWND tool_tips_handle,
                                             COLORREF color) {
        SendMessageW(tool_tips_handle, TTM_SETTIPBKCOLOR, color, 0);
    }

    COLORREF tool_tips::get_text_background_color(HWND tool_tips_handle) {
        return SendMessageW(tool_tips_handle, TTM_GETTIPTEXTCOLOR, 0, 0);
    }

    void tool_tips::set_text_background_color(HWND tool_tips_handle,
                                              COLORREF color) {
        SendMessageW(tool_tips_handle, TTM_SETTIPTEXTCOLOR, color, 0);
    }

    void tool_tips::get_title(HWND tool_tips_handle, TTGETTITLE *title) {
        SendMessageW(tool_tips_handle, TTM_GETTITLE, 0,
                     reinterpret_cast<LPARAM>(title));
    }

    bool tool_tips::set_title(HWND tool_tips_handle,
                              TTTitleType type,
                              std::string &title,
                              helper::CodePage code_page) {
        auto temp = helper::convert::str_to_wstr(title, code_page);
        return SendMessageW(tool_tips_handle, TTM_SETTITLE,
                            static_cast<uint32_t>(type),
                            reinterpret_cast<LPARAM>(temp.data()));
    }

    bool tool_tips::set_title(HWND tool_tips_handle,
                              TTTitleType type,
                              std::wstring &title) {
        return SendMessageW(tool_tips_handle, TTM_SETTITLE,
                            static_cast<uint32_t>(type),
                            reinterpret_cast<LPARAM>(title.data()));
    }

    bool tool_tips::set_title(HWND tool_tips_handle,
                              HICON icon_handle,
                              std::string &title,
                              helper::CodePage code_page) {
        auto temp = helper::convert::str_to_wstr(title, code_page);
        return SendMessageW(tool_tips_handle, TTM_SETTITLE,
                            reinterpret_cast<WPARAM>(icon_handle),
                            reinterpret_cast<LPARAM>(temp.data()));
    }

    bool tool_tips::set_title(HWND tool_tips_handle,
                              HICON icon_handle,
                              std::wstring &title) {
        return SendMessageW(tool_tips_handle, TTM_SETTITLE,
                            reinterpret_cast<WPARAM>(icon_handle),
                            reinterpret_cast<LPARAM>(title.data()));
    }

    std::pair<uint32_t, uint32_t>
    tool_tips::get_bubble_size(HWND tool_tips_handle, TTTOOLINFOW *tool_info) {
        const auto result = static_cast<int32_t>(
                SendMessageW(tool_tips_handle, TTM_GETBUBBLESIZE, 0,
                             reinterpret_cast<LPARAM>(tool_info)));
        return std::make_pair(LOWORD(result), HIWORD(result));
    }

    bool tool_tips::get_curr_tool(HWND tool_tips_handle,
                                  TTTOOLINFOA *tool_info) {
        return SendMessageW(tool_tips_handle, TTM_GETCURRENTTOOLA, 0,
                            reinterpret_cast<LPARAM>(tool_info));
    }

    bool tool_tips::get_curr_tool(HWND tool_tips_handle,
                                  TTTOOLINFOW *tool_info) {
        return SendMessageW(tool_tips_handle, TTM_GETCURRENTTOOLW, 0,
                            reinterpret_cast<LPARAM>(tool_info));
    }

    void tool_tips::get_text(HWND tool_tips_handle,
                             int64_t text_size,
                             TTTOOLINFOA *tool_info) {
        SendMessageW(tool_tips_handle, TTM_GETTEXTA,
                     text_size / (sizeof(wchar_t)),
                     reinterpret_cast<LPARAM>(tool_info));
    }

    void tool_tips::get_text(HWND tool_tips_handle,
                             int64_t text_size,
                             TTTOOLINFOW *tool_info) {
        SendMessageW(tool_tips_handle, TTM_GETTEXTW,
                     text_size / (sizeof(wchar_t)),
                     reinterpret_cast<LPARAM>(tool_info));
    }

    void tool_tips::update_text(HWND tool_tips_handle, TTTOOLINFOA *tool_info) {
        SendMessageW(tool_tips_handle, TTM_UPDATETIPTEXTA, 0,
                     reinterpret_cast<LPARAM>(tool_info));
    }

    void tool_tips::update_text(HWND tool_tips_handle, TTTOOLINFOW *tool_info) {
        SendMessageW(tool_tips_handle, TTM_UPDATETIPTEXTW, 0,
                     reinterpret_cast<LPARAM>(tool_info));
    }

    bool tool_tips::display_rect_to_window_rect(HWND tool_tips_handle,
                                                RECT *rect) {
        return SendMessageW(tool_tips_handle, TTM_ADJUSTRECT, TRUE,
                            reinterpret_cast<LPARAM>(rect));
    }

    bool tool_tips::window_rect_to_display_rect(HWND tool_tips_handle,
                                                RECT *rect) {
        return SendMessageW(tool_tips_handle, TTM_ADJUSTRECT, FALSE,
                            reinterpret_cast<LPARAM>(rect));
    }

    bool tool_tips::hit_test(HWND tool_tips_handle,
                             TTHITTESTINFOA *hit_test_info) {
        return SendMessageW(tool_tips_handle, TTM_HITTESTA, 0,
                            reinterpret_cast<LPARAM>(hit_test_info));
    }

    bool tool_tips::hit_test(HWND tool_tips_handle,
                             TTHITTESTINFOW *hit_test_info) {
        return SendMessageW(tool_tips_handle, TTM_HITTESTW, 0,
                            reinterpret_cast<LPARAM>(hit_test_info));
    }

    HWND tool_tips::window_from_point(HWND tool_tips_handle, POINT *point) {
        return reinterpret_cast<HWND>(
                SendMessageW(tool_tips_handle, TTM_WINDOWFROMPOINT, 0,
                             reinterpret_cast<LPARAM>(point)));
    }

    void tool_tips::relay_event(HWND tool_tips_handle, MSG *msg) {
        SendMessageW(tool_tips_handle, TTM_RELAYEVENT, 0,
                     reinterpret_cast<LPARAM>(msg));
    }

    void tool_tips::pop(HWND tool_tips_handle) {
        SendMessageW(tool_tips_handle, TTM_POP, 0, 0);
    }

    void tool_tips::popup(HWND tool_tips_handle) {
        SendMessageW(tool_tips_handle, TTM_POPUP, 0, 0);
    }

    void tool_tips::update(HWND tool_tips_handle) {
        SendMessageW(tool_tips_handle, TTM_UPDATE, 0, 0);
    }

    void tool_tips::set_window_theme(HWND tool_tips_handle,
                                     std::string &theme,
                                     helper::CodePage code_page) {
        auto temp = helper::convert::str_to_wstr(theme, code_page);
        SendMessageW(tool_tips_handle, TTM_SETWINDOWTHEME, 0,
                     reinterpret_cast<LPARAM>(temp.data()));
    }

    void tool_tips::set_window_theme(HWND tool_tips_handle,
                                     std::wstring &theme) {
        SendMessageW(tool_tips_handle, TTM_SETWINDOWTHEME, 0,
                     reinterpret_cast<LPARAM>(theme.data()));
    }

    uint32_t tool_tips::err_code() const {
        return error_code;
    }

    std::string tool_tips::err_string() const {
        std::string result = helper::convert::err_string(error_code);
        return result;
    }

    std::wstring tool_tips::err_wstring() const {
        std::wstring result = helper::convert::err_wstring(error_code);
        return result;
    }
} // namespace YanLib::ui::components
