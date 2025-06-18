/* clang-format off */
/*
 * @file rebar.cpp
 * @date 2025-05-29
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
#include "rebar.h"
#include <windowsx.h>

namespace YanLib::ui::components {
    rebar::rebar() {
        INITCOMMONCONTROLSEX icc = {};
        icc.dwSize = sizeof(INITCOMMONCONTROLSEX);
        icc.dwICC = ICC_COOL_CLASSES | ICC_BAR_CLASSES;
        InitCommonControlsEx(&icc);
    }

    rebar::~rebar() {
        for (auto &handle : rebar_handles) {
            if (handle && IsWindow(handle)) {
                DestroyWindow(handle);
                handle = nullptr;
            }
        }
        rebar_handles.clear();
    }

    HWND rebar::create(HWND parent_window_handle,
                       LPARAM lparam,
                       int32_t x,
                       int32_t y,
                       int32_t width,
                       int32_t height,
                       RebarStyle style,
                       core::WindowStyle window_style) {
        HWND result = CreateWindowExW(
                WS_EX_TOOLWINDOW, L"ReBarWindow32", nullptr,
                static_cast<uint32_t>(window_style) |
                        static_cast<uint32_t>(style),
                x, y, width, height, parent_window_handle, nullptr,
                reinterpret_cast<CREATESTRUCT *>(lparam)->hInstance, nullptr);
        if (!result) {
            error_code = GetLastError();
            return nullptr;
        }
        rebar_rwlock.write_lock();
        rebar_handles.push_back(result);
        rebar_rwlock.write_unlock();
        return result;
    }

    HWND rebar::create(const char *rebar_name,
                       HWND parent_window_handle,
                       LPARAM lparam,
                       int32_t x,
                       int32_t y,
                       int32_t width,
                       int32_t height,
                       RebarStyle style,
                       core::WindowStyle window_style) {
        HWND result = CreateWindowExA(
                WS_EX_TOOLWINDOW, "ReBarWindow32", rebar_name,
                static_cast<uint32_t>(window_style) |
                        static_cast<uint32_t>(style),
                x, y, width, height, parent_window_handle, nullptr,
                reinterpret_cast<CREATESTRUCT *>(lparam)->hInstance, nullptr);
        if (!result) {
            error_code = GetLastError();
            return nullptr;
        }
        rebar_rwlock.write_lock();
        rebar_handles.push_back(result);
        rebar_rwlock.write_unlock();
        return result;
    }

    HWND rebar::create(const wchar_t *rebar_name,
                       HWND parent_window_handle,
                       LPARAM lparam,
                       int32_t x,
                       int32_t y,
                       int32_t width,
                       int32_t height,
                       RebarStyle style,
                       core::WindowStyle window_style) {
        HWND result = CreateWindowExW(
                WS_EX_TOOLWINDOW, L"ReBarWindow32", rebar_name,
                static_cast<uint32_t>(window_style) |
                        static_cast<uint32_t>(style),
                x, y, width, height, parent_window_handle, nullptr,
                reinterpret_cast<CREATESTRUCT *>(lparam)->hInstance, nullptr);
        if (!result) {
            error_code = GetLastError();
            return nullptr;
        }
        rebar_rwlock.write_lock();
        rebar_handles.push_back(result);
        rebar_rwlock.write_unlock();
        return result;
    }

    bool rebar::destroy(HWND rebar_handle) {
        if (!rebar_handle || !IsWindow(rebar_handle)) {
            return false;
        }
        rebar_rwlock.write_lock();
        const auto it = std::find(rebar_handles.begin(), rebar_handles.end(),
                                  rebar_handle);
        if (it != rebar_handles.end()) {
            *it = nullptr;
        }
        rebar_rwlock.write_unlock();
        if (!DestroyWindow(rebar_handle)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    void rebar::begin_drag(HWND rebar_handle, int32_t index, POINT point) {
        SendMessageW(rebar_handle, RB_BEGINDRAG, index,
                     MAKELPARAM(point.x, point.y));
    }

    void rebar::move_drag(HWND rebar_handle, POINT point) {
        SendMessageW(rebar_handle, RB_DRAGMOVE, 0,
                     MAKELPARAM(point.x, point.y));
    }

    void rebar::end_drag(HWND rebar_handle) {
        SendMessageW(rebar_handle, RB_ENDDRAG, 0, 0);
    }

    bool rebar::insert_band(HWND rebar_handle,
                            REBARBANDINFOW *band_info,
                            int32_t index) {
        return SendMessageW(rebar_handle, RB_INSERTBAND, index,
                            reinterpret_cast<LPARAM>(band_info));
    }

    bool
    rebar::move_band(HWND rebar_handle, int32_t index_from, int32_t index_to) {
        return SendMessageW(rebar_handle, RB_MOVEBAND, index_from, index_to);
    }

    bool rebar::delete_band(HWND rebar_handle, int32_t index) {
        return SendMessageW(rebar_handle, RB_DELETEBAND, index, 0);
    }

    bool rebar::show_band(HWND rebar_handle, int32_t index) {
        return SendMessageW(rebar_handle, RB_SHOWBAND, index, TRUE);
    }

    bool rebar::hide_band(HWND rebar_handle, int32_t index) {
        return SendMessageW(rebar_handle, RB_SHOWBAND, index, FALSE);
    }

    void rebar::maximize_band(HWND rebar_handle,
                              int32_t index,
                              int32_t ideal_width) {
        SendMessageW(rebar_handle, RB_MAXIMIZEBAND, index, ideal_width);
    }

    void rebar::minimize_band(HWND rebar_handle, int32_t index) {
        SendMessageW(rebar_handle, RB_MINIMIZEBAND, index, 0);
    }

    void rebar::get_band_borders(HWND rebar_handle, int32_t index, RECT *rect) {
        SendMessageW(rebar_handle, RB_GETBANDBORDERS, index,
                     reinterpret_cast<LPARAM>(rect));
    }

    uint32_t rebar::get_band_count(HWND rebar_handle) {
        return SendMessageW(rebar_handle, RB_GETBANDCOUNT, 0, 0);
    }

    bool rebar::get_band_info(HWND rebar_handle,
                              int32_t index,
                              REBARBANDINFOW *band_info) {
        return SendMessageW(rebar_handle, RB_GETBANDINFO, index,
                            reinterpret_cast<LPARAM>(band_info));
    }

    bool rebar::set_band_info(HWND rebar_handle,
                              int32_t index,
                              REBARBANDINFOW *band_info) {
        return SendMessageW(rebar_handle, RB_SETBANDINFO, index,
                            reinterpret_cast<LPARAM>(band_info));
    }

    void rebar::get_band_margins(HWND rebar_handle, MARGINS *margin) {
        SendMessageW(rebar_handle, RB_GETBANDMARGINS, 0,
                     reinterpret_cast<LPARAM>(margin));
    }

    bool
    rebar::set_band_width(HWND rebar_handle, int32_t index, int32_t width) {
        return SendMessageW(rebar_handle, RB_SETBANDWIDTH, index, width);
    }

    uint32_t rebar::get_height(HWND rebar_handle) {
        return SendMessageW(rebar_handle, RB_GETBARHEIGHT, 0, 0);
    }

    bool rebar::get_info(HWND rebar_handle, REBARINFO *info) {
        return SendMessageW(rebar_handle, RB_GETBARINFO, 0,
                            reinterpret_cast<LPARAM>(info));
    }

    bool rebar::set_info(HWND rebar_handle, REBARINFO *info) {
        return SendMessageW(rebar_handle, RB_SETBARINFO, 0,
                            reinterpret_cast<LPARAM>(info));
    }

    COLORREF rebar::get_background_color(HWND rebar_handle) {
        return SendMessageW(rebar_handle, RB_GETBKCOLOR, 0, 0);
    }

    COLORREF rebar::set_background_color(HWND rebar_handle, COLORREF color) {
        return SendMessageW(rebar_handle, RB_SETBKCOLOR, 0, color);
    }

    bool rebar::get_color_scheme(HWND rebar_handle, COLORSCHEME *color_scheme) {
        return SendMessageW(rebar_handle, RB_GETCOLORSCHEME, 0,
                            reinterpret_cast<LPARAM>(color_scheme));
    }

    void rebar::set_color_scheme(HWND rebar_handle, COLORSCHEME *color_scheme) {
        SendMessageW(rebar_handle, RB_SETCOLORSCHEME, 0,
                     reinterpret_cast<LPARAM>(color_scheme));
    }

    void rebar::get_drop_target(HWND rebar_handle, IDropTarget **target) {
        SendMessageW(rebar_handle, RB_GETDROPTARGET, 0,
                     reinterpret_cast<LPARAM>(target));
    }

    COLORREF rebar::get_text_color(HWND rebar_handle) {
        return SendMessageW(rebar_handle, RB_GETTEXTCOLOR, 0, 0);
    }

    COLORREF rebar::set_text_color(HWND rebar_handle, COLORREF color) {
        return SendMessageW(rebar_handle, RB_SETTEXTCOLOR, 0, color);
    }

    HPALETTE rebar::get_palette(HWND rebar_handle) {
        return reinterpret_cast<HPALETTE>(
                SendMessageW(rebar_handle, RB_GETPALETTE, 0, 0));
    }

    HPALETTE rebar::set_palette(HWND rebar_handle, HPALETTE palette) {
        return reinterpret_cast<HPALETTE>(
                SendMessageW(rebar_handle, RB_SETPALETTE, 0,
                             reinterpret_cast<LPARAM>(palette)));
    }

    bool rebar::get_rect(HWND rebar_handle, int32_t index, RECT *rect) {
        return SendMessageW(rebar_handle, RB_GETRECT, index,
                            reinterpret_cast<LPARAM>(rect));
    }

    uint32_t rebar::get_row_count(HWND rebar_handle) {
        return SendMessageW(rebar_handle, RB_GETROWCOUNT, 0, 0);
    }

    uint32_t rebar::get_row_height(HWND rebar_handle, int32_t index) {
        return SendMessageW(rebar_handle, RB_GETROWHEIGHT, index, 0);
    }

    HWND rebar::get_tool_tips(HWND rebar_handle) {
        return reinterpret_cast<HWND>(
                SendMessageW(rebar_handle, RB_GETTOOLTIPS, 0, 0));
    }

    void rebar::set_tool_tips(HWND rebar_handle, HWND tool_tips_handle) {
        SendMessageW(rebar_handle, RB_SETTOOLTIPS,
                     reinterpret_cast<WPARAM>(tool_tips_handle), 0);
    }

    bool rebar::is_ansi_format(HWND rebar_handle) {
        return !SendMessageW(rebar_handle, RB_GETUNICODEFORMAT, 0, 0);
    }

    bool rebar::is_unicode_format(HWND rebar_handle) {
        return SendMessageW(rebar_handle, RB_GETUNICODEFORMAT, 0, 0);
    }

    void rebar::set_ansi_format(HWND rebar_handle) {
        SendMessageW(rebar_handle, RB_SETUNICODEFORMAT, FALSE, 0);
    }

    void rebar::set_unicode_format(HWND rebar_handle) {
        SendMessageW(rebar_handle, RB_SETUNICODEFORMAT, TRUE, 0);
    }

    int32_t rebar::hit_test(HWND rebar_handle, RBHITTESTINFO *hit_test_info) {
        return static_cast<int32_t>(
                SendMessageW(rebar_handle, RB_HITTEST, 0,
                             reinterpret_cast<LPARAM>(hit_test_info)));
    }

    int32_t rebar::id_to_index(HWND rebar_handle, uint32_t id) {
        return static_cast<int32_t>(
                SendMessageW(rebar_handle, RB_IDTOINDEX, id, 0));
    }

    void rebar::push_chevron(HWND rebar_handle, int32_t index, int32_t value) {
        SendMessageW(rebar_handle, RB_PUSHCHEVRON, index, value);
    }

    HWND rebar::set_parent(HWND rebar_handle, HWND parent_window_handle) {
        return reinterpret_cast<HWND>(
                SendMessageW(rebar_handle, RB_SETPARENT,
                             reinterpret_cast<WPARAM>(parent_window_handle),
                             0));
    }

    void rebar::set_window_theme(HWND rebar_handle,
                                 std::string &theme,
                                 helper::CodePage code_page) {
        SendMessageW(rebar_handle, RB_SETWINDOWTHEME, 0,
                     reinterpret_cast<LPARAM>(
                             helper::convert::str_to_wstr(theme, code_page)
                                     .data()));
    }

    void rebar::set_window_theme(HWND rebar_handle, std::wstring &theme) {
        SendMessageW(rebar_handle, RB_SETWINDOWTHEME, 0,
                     reinterpret_cast<LPARAM>(theme.data()));
    }

    bool rebar::size_to_rect(HWND rebar_handle, RECT *rect) {
        return SendMessageW(rebar_handle, RB_SIZETORECT, 0,
                            reinterpret_cast<LPARAM>(rect));
    }

    uint32_t rebar::err_code() const {
        return error_code;
    }

    std::string rebar::err_string() const {
        std::string result = helper::convert::err_string(error_code);
        return result;
    }

    std::wstring rebar::err_wstring() const {
        std::wstring result = helper::convert::err_wstring(error_code);
        return result;
    }
} // namespace YanLib::ui::components
