/* clang-format off */
/*
 * @file track.cpp
 * @date 2025-06-04
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
#include "track.h"
#include <windowsx.h>
#include "helper/convert.h"
namespace YanLib::ui::components {
    track::track() {
        INITCOMMONCONTROLSEX icc = {};
        icc.dwSize = sizeof(INITCOMMONCONTROLSEX);
        icc.dwICC = ICC_BAR_CLASSES;
        InitCommonControlsEx(&icc);
    }

    track::~track() {
        for (auto &handle : track_handles) {
            if (handle && IsWindow(handle)) {
                DestroyWindow(handle);
                handle = nullptr;
            }
        }
        track_handles.clear();
    }

    HWND track::create(uintptr_t track_id,
                       HWND parent_window_handle,
                       LPARAM lparam,
                       int32_t x,
                       int32_t y,
                       int32_t width,
                       int32_t height,
                       TrackStyle style,
                       core::WindowStyle window_style) {
        HWND result = CreateWindowExW(0L, L"msctls_trackbar32", nullptr,
                                      static_cast<uint32_t>(window_style) |
                                              static_cast<uint32_t>(style),
                                      x, y, width, height, parent_window_handle,
                                      reinterpret_cast<HMENU>(track_id),
                                      reinterpret_cast<CREATESTRUCT *>(lparam)
                                              ->hInstance,
                                      nullptr);
        if (!result) {
            error_code = GetLastError();
            return nullptr;
        }
        track_rwlock.write_lock();
        track_handles.push_back(result);
        track_rwlock.write_unlock();
        return result;
    }

    HWND track::create(const char *track_name,
                       uintptr_t track_id,
                       HWND parent_window_handle,
                       LPARAM lparam,
                       int32_t x,
                       int32_t y,
                       int32_t width,
                       int32_t height,
                       TrackStyle style,
                       core::WindowStyle window_style) {
        HWND result = CreateWindowExA(0L, "msctls_trackbar32", track_name,
                                      static_cast<uint32_t>(window_style) |
                                              static_cast<uint32_t>(style),
                                      x, y, width, height, parent_window_handle,
                                      reinterpret_cast<HMENU>(track_id),
                                      reinterpret_cast<CREATESTRUCT *>(lparam)
                                              ->hInstance,
                                      nullptr);
        if (!result) {
            error_code = GetLastError();
            return nullptr;
        }
        track_rwlock.write_lock();
        track_handles.push_back(result);
        track_rwlock.write_unlock();
        return result;
    }

    HWND track::create(const wchar_t *track_name,
                       uintptr_t track_id,
                       HWND parent_window_handle,
                       LPARAM lparam,
                       int32_t x,
                       int32_t y,
                       int32_t width,
                       int32_t height,
                       TrackStyle style,
                       core::WindowStyle window_style) {
        HWND result = CreateWindowExW(0L, L"msctls_trackbar32", track_name,
                                      static_cast<uint32_t>(window_style) |
                                              static_cast<uint32_t>(style),
                                      x, y, width, height, parent_window_handle,
                                      reinterpret_cast<HMENU>(track_id),
                                      reinterpret_cast<CREATESTRUCT *>(lparam)
                                              ->hInstance,
                                      nullptr);
        if (!result) {
            error_code = GetLastError();
            return nullptr;
        }
        track_rwlock.write_lock();
        track_handles.push_back(result);
        track_rwlock.write_unlock();
        return result;
    }

    bool track::destroy(HWND track_handle) {
        if (!track_handle || !IsWindow(track_handle)) {
            return false;
        }
        track_rwlock.write_lock();
        const auto it = std::find(track_handles.begin(), track_handles.end(),
                                  track_handle);
        if (it != track_handles.end()) {
            *it = nullptr;
        }
        track_rwlock.write_unlock();
        if (!DestroyWindow(track_handle)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    void track::clear_select(HWND track_handle, bool redraw) {
        SendMessageW(track_handle, TBM_CLEARSEL, redraw ? TRUE : FALSE, 0);
    }

    void track::clear_ticks(HWND track_handle, bool redraw) {
        SendMessageW(track_handle, TBM_CLEARTICS, redraw ? TRUE : FALSE, 0);
    }

    HWND track::get_left_or_top_buddy(HWND track_handle) {
        return reinterpret_cast<HWND>(
                SendMessageW(track_handle, TBM_GETBUDDY, TRUE, 0));
    }

    HWND track::set_left_or_top_buddy(HWND track_handle) {
        return reinterpret_cast<HWND>(
                SendMessageW(track_handle, TBM_SETBUDDY, TRUE, 0));
    }

    HWND track::get_right_or_bottom_buddy(HWND track_handle) {
        return reinterpret_cast<HWND>(
                SendMessageW(track_handle, TBM_GETBUDDY, FALSE, 0));
    }

    HWND track::set_right_or_bottom_buddy(HWND track_handle) {
        return reinterpret_cast<HWND>(
                SendMessageW(track_handle, TBM_SETBUDDY, FALSE, 0));
    }

    void track::get_channel_rect(HWND track_handle, RECT *rect) {
        SendMessageW(track_handle, TBM_GETCHANNELRECT, 0,
                     reinterpret_cast<LPARAM>(rect));
    }

    int64_t track::get_line_size(HWND track_handle) {
        return SendMessageW(track_handle, TBM_GETLINESIZE, 0, 0);
    }

    int64_t track::set_line_size(HWND track_handle, int64_t line_size) {
        return SendMessageW(track_handle, TBM_SETLINESIZE, 0, line_size);
    }

    int64_t track::get_page_size(HWND track_handle) {
        return SendMessageW(track_handle, TBM_GETPAGESIZE, 0, 0);
    }

    int64_t track::set_page_size(HWND track_handle, int64_t page_size) {
        return SendMessageW(track_handle, TBM_SETPAGESIZE, 0, page_size);
    }

    int64_t track::get_pos(HWND track_handle) {
        return SendMessageW(track_handle, TBM_GETPOS, 0, 0);
    }

    void track::set_pos(HWND track_handle, int64_t pos, bool redraw) {
        SendMessageW(track_handle, TBM_SETPOS, redraw ? TRUE : FALSE, pos);
    }

    void track::set_pos_notify(HWND track_handle, int64_t pos) {
        SendMessageW(track_handle, TBM_SETPOSNOTIFY, 0, pos);
    }

    int64_t track::get_range_min(HWND track_handle) {
        return SendMessageW(track_handle, TBM_GETRANGEMIN, 0, 0);
    }

    void track::set_range_min(HWND track_handle, int64_t min, bool redraw) {
        SendMessageW(track_handle, TBM_SETRANGEMIN, redraw ? TRUE : FALSE, min);
    }

    int64_t track::get_range_max(HWND track_handle) {
        return SendMessageW(track_handle, TBM_GETRANGEMAX, 0, 0);
    }

    void track::set_range_max(HWND track_handle, int64_t max, bool redraw) {
        SendMessageW(track_handle, TBM_SETRANGEMAX, redraw ? TRUE : FALSE, max);
    }

    void
    track::set_range(HWND track_handle, int32_t min, int32_t max, bool redraw) {
        SendMessageW(track_handle, TBM_SETRANGE, redraw ? TRUE : FALSE,
                     MAKELPARAM(min, max));
    }

    int64_t track::get_select_start(HWND track_handle) {
        return SendMessageW(track_handle, TBM_GETSELSTART, 0, 0);
    }

    void
    track::set_select_start(HWND track_handle, int64_t start, bool redraw) {
        SendMessageW(track_handle, TBM_SETSELSTART, redraw ? TRUE : FALSE,
                     start);
    }

    int64_t track::get_select_end(HWND track_handle) {
        return SendMessageW(track_handle, TBM_GETSELEND, 0, 0);
    }

    void track::set_select_end(HWND track_handle, int64_t end, bool redraw) {
        SendMessageW(track_handle, TBM_SETSELEND, redraw ? TRUE : FALSE, end);
    }

    void track::set_select(HWND track_handle,
                           int32_t start,
                           int32_t end,
                           bool redraw) {
        SendMessageW(track_handle, TBM_SETSEL, redraw ? TRUE : FALSE,
                     MAKELPARAM(start, end));
    }

    int64_t track::get_thumb_len(HWND track_handle) {
        return SendMessageW(track_handle, TBM_GETTHUMBLENGTH, 0, 0);
    }

    void track::set_thumb_len(HWND track_handle, int64_t len) {
        SendMessageW(track_handle, TBM_SETTHUMBLENGTH, len, 0);
    }

    void track::get_thumb_rect(HWND track_handle, RECT *rect) {
        SendMessageW(track_handle, TBM_GETTHUMBRECT, 0,
                     reinterpret_cast<LPARAM>(rect));
    }

    int64_t track::get_num_ticks(HWND track_handle) {
        return SendMessageW(track_handle, TBM_GETNUMTICS, 0, 0);
    }

    std::vector<uint32_t> track::get_ticks(HWND track_handle) {
        const int64_t num_ticks =
                SendMessageW(track_handle, TBM_GETNUMTICS, 0, 0);
        const auto *ticks = reinterpret_cast<uint32_t *>(
                SendMessageW(track_handle, TBM_GETPTICS, 0, 0));
        if (num_ticks <= 2) {
            return {};
        }
        std::vector<uint32_t> result(num_ticks - 2, 0);
        for (int64_t i = 0; i < num_ticks; i++) {
            result.push_back(ticks[i]);
        }
        return result;
    }

    int64_t track::get_tick(HWND track_handle, int64_t index) {
        return SendMessageW(track_handle, TBM_GETTIC, index, 0);
    }

    bool track::set_tick(HWND track_handle, int64_t tick) {
        return SendMessageW(track_handle, TBM_SETTIC, 0, tick);
    }

    int64_t track::get_tick_pos(HWND track_handle, int64_t index) {
        return SendMessageW(track_handle, TBM_GETTICPOS, index, 0);
    }

    void track::set_tick_freq(HWND track_handle, int64_t freq) {
        SendMessageW(track_handle, TBM_SETTICFREQ, freq, 0);
    }

    HWND track::get_tool_tips(HWND track_handle) {
        return reinterpret_cast<HWND>(
                SendMessageW(track_handle, TBM_GETTOOLTIPS, 0, 0));
    }

    void track::set_tool_tips(HWND track_handle, HWND tool_tips_handle) {
        SendMessageW(track_handle, TBM_SETTOOLTIPS,
                     reinterpret_cast<WPARAM>(tool_tips_handle), 0);
    }

    TrackTipSide track::set_tip_side(HWND track_handle, TrackTipSide pos) {
        return static_cast<TrackTipSide>(
                SendMessageW(track_handle, TBM_SETTIPSIDE,
                             static_cast<uint32_t>(pos), 0));
    }

    bool track::is_ansi_format(HWND track_handle) {
        return !SendMessageW(track_handle, TBM_GETUNICODEFORMAT, 0, 0);
    }

    bool track::is_unicode_format(HWND track_handle) {
        return SendMessageW(track_handle, TBM_GETUNICODEFORMAT, 0, 0);
    }

    void track::set_ansi_format(HWND track_handle) {
        SendMessageW(track_handle, TBM_SETUNICODEFORMAT, TRUE, 0);
    }

    void track::set_unicode_format(HWND track_handle) {
        SendMessageW(track_handle, TBM_SETUNICODEFORMAT, FALSE, 0);
    }

    uint32_t track::err_code() const {
        return error_code;
    }

    std::string track::err_string() const {
        std::string result = helper::convert::err_string(error_code);
        return result;
    }

    std::wstring track::err_wstring() const {
        std::wstring result = helper::convert::err_wstring(error_code);
        return result;
    }
} // namespace YanLib::ui::components
