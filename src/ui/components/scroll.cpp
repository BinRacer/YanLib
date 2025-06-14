/* clang-format off */
/*
 * @file scroll.cpp
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
#include "scroll.h"
#include <windowsx.h>
#include "helper/convert.h"
namespace YanLib::ui::components {
    scroll::~scroll() {
        for (auto &handle : scroll_handles) {
            if (handle && IsWindow(handle)) {
                DestroyWindow(handle);
                handle = nullptr;
            }
        }
        scroll_handles.clear();
    }

    HWND scroll::create(uintptr_t scroll_id,
                        HWND parent_window_handle,
                        LPARAM lparam,
                        int32_t x,
                        int32_t y,
                        int32_t width,
                        int32_t height,
                        ScrollStyle style,
                        WindowStyle window_style) {
        HWND result = CreateWindowExW(0L, L"ScrollBar", nullptr,
                                      static_cast<uint32_t>(window_style) |
                                              static_cast<uint32_t>(style),
                                      x, y, width, height, parent_window_handle,
                                      reinterpret_cast<HMENU>(scroll_id),
                                      reinterpret_cast<CREATESTRUCT *>(lparam)
                                              ->hInstance,
                                      nullptr);
        if (!result) {
            error_code = GetLastError();
            return nullptr;
        }
        scroll_rwlock.write_lock();
        scroll_handles.push_back(result);
        scroll_rwlock.write_unlock();
        return result;
    }

    HWND scroll::create(const char *scroll_name,
                        uintptr_t scroll_id,
                        HWND parent_window_handle,
                        LPARAM lparam,
                        int32_t x,
                        int32_t y,
                        int32_t width,
                        int32_t height,
                        ScrollStyle style,
                        WindowStyle window_style) {
        HWND result = CreateWindowExA(0L, "ScrollBar", scroll_name,
                                      static_cast<uint32_t>(window_style) |
                                              static_cast<uint32_t>(style),
                                      x, y, width, height, parent_window_handle,
                                      reinterpret_cast<HMENU>(scroll_id),
                                      reinterpret_cast<CREATESTRUCT *>(lparam)
                                              ->hInstance,
                                      nullptr);
        if (!result) {
            error_code = GetLastError();
            return nullptr;
        }
        scroll_rwlock.write_lock();
        scroll_handles.push_back(result);
        scroll_rwlock.write_unlock();
        return result;
    }

    HWND scroll::create(const wchar_t *scroll_name,
                        uintptr_t scroll_id,
                        HWND parent_window_handle,
                        LPARAM lparam,
                        int32_t x,
                        int32_t y,
                        int32_t width,
                        int32_t height,
                        ScrollStyle style,
                        WindowStyle window_style) {
        HWND result = CreateWindowExW(0L, L"ScrollBar", scroll_name,
                                      static_cast<uint32_t>(window_style) |
                                              static_cast<uint32_t>(style),
                                      x, y, width, height, parent_window_handle,
                                      reinterpret_cast<HMENU>(scroll_id),
                                      reinterpret_cast<CREATESTRUCT *>(lparam)
                                              ->hInstance,
                                      nullptr);
        if (!result) {
            error_code = GetLastError();
            return nullptr;
        }
        scroll_rwlock.write_lock();
        scroll_handles.push_back(result);
        scroll_rwlock.write_unlock();
        return result;
    }

    bool scroll::destroy(HWND scroll_handle) {
        if (!scroll_handle || !IsWindow(scroll_handle)) {
            return false;
        }
        scroll_rwlock.write_lock();
        const auto it = std::find(scroll_handles.begin(), scroll_handles.end(),
                                  scroll_handle);
        if (it != scroll_handles.end()) {
            *it = nullptr;
        }
        scroll_rwlock.write_unlock();
        if (!DestroyWindow(scroll_handle)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool scroll::enable(HWND scroll_handle,
                        ScrollType scroll_type,
                        ArrowType arrow_type) {
        if (!EnableScrollBar(scroll_handle, static_cast<uint32_t>(scroll_type),
                             static_cast<uint32_t>(arrow_type))) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool scroll::show(HWND scroll_handle, ScrollType scroll_type) {
        if (!ShowScrollBar(scroll_handle, static_cast<int32_t>(scroll_type),
                           TRUE)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool scroll::hide(HWND scroll_handle, ScrollType scroll_type) {
        if (!ShowScrollBar(scroll_handle, static_cast<int32_t>(scroll_type),
                           FALSE)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool scroll::get_info(HWND scroll_handle,
                          SCROLLBARINFO *scroll_bar_info,
                          ObjectID object_id) {
        if (!GetScrollBarInfo(scroll_handle, static_cast<int32_t>(object_id),
                              scroll_bar_info)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool scroll::get_info(HWND scroll_handle,
                          SCROLLINFO *scroll_info,
                          ScrollType scroll_type) {
        if (!GetScrollInfo(scroll_handle, static_cast<int32_t>(scroll_type),
                           scroll_info)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    int32_t scroll::set_info(HWND scroll_handle,
                             SCROLLINFO *scroll_info,
                             ScrollType scroll_type,
                             bool is_redraw) {
        return SetScrollInfo(scroll_handle, static_cast<int32_t>(scroll_type),
                             scroll_info, is_redraw ? TRUE : FALSE);
    }

    int32_t scroll::get_pos(HWND scroll_handle, ScrollType scroll_type) {
        const int32_t result =
                GetScrollPos(scroll_handle, static_cast<int32_t>(scroll_type));
        if (!result) {
            error_code = GetLastError();
        }
        return result;
    }

    int32_t scroll::set_pos(HWND scroll_handle,
                            int32_t pos,
                            ScrollType scroll_type,
                            bool is_redraw) {
        const int32_t result =
                SetScrollPos(scroll_handle, static_cast<int32_t>(scroll_type),
                             pos, is_redraw ? TRUE : FALSE);
        if (!result) {
            error_code = GetLastError();
        }
        return result;
    }

    bool scroll::get_range(HWND scroll_handle,
                           int32_t *min_pos,
                           int32_t *max_pos,
                           ScrollType scroll_type) {
        if (!GetScrollRange(scroll_handle, static_cast<int32_t>(scroll_type),
                            min_pos, max_pos)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool scroll::set_range(HWND scroll_handle,
                           int32_t min_pos,
                           int32_t max_pos,
                           ScrollType scroll_type,
                           bool is_redraw) {
        if (!SetScrollRange(scroll_handle, static_cast<int32_t>(scroll_type),
                            min_pos, max_pos, is_redraw ? TRUE : FALSE)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool scroll::scroll_dc(HDC dc_handle,
                           int32_t x,
                           int32_t y,
                           const RECT *rect_scroll,
                           const RECT *rect_clip,
                           HRGN region_update_handle,
                           RECT *rect_update) {
        if (!ScrollDC(dc_handle, x, y, rect_scroll, rect_clip,
                      region_update_handle, rect_update)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool scroll::scroll_window(HWND scroll_handle,
                               int32_t x_amount,
                               int32_t y_amount,
                               const RECT *rect,
                               const RECT *clip_rect) {
        if (!ScrollWindow(scroll_handle, x_amount, y_amount, rect, clip_rect)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    int32_t scroll::scroll_window_extend(HWND scroll_handle,
                                         int32_t dx,
                                         int32_t dy,
                                         const RECT *rect_scroll,
                                         const RECT *rect_clip,
                                         HRGN region_handle_update,
                                         RECT *rect_update,
                                         ScrollFlag flag) {
        const int32_t result =
                ScrollWindowEx(scroll_handle, dx, dy, rect_scroll, rect_clip,
                               region_handle_update, rect_update,
                               static_cast<uint32_t>(flag));
        if (!result) {
            error_code = GetLastError();
        }
        return result;
    }

    uint32_t scroll::err_code() const {
        return error_code;
    }

    std::string scroll::err_string() const {
        std::string result = helper::convert::err_string(error_code);
        return result;
    }

    std::wstring scroll::err_wstring() const {
        std::wstring result = helper::convert::err_wstring(error_code);
        return result;
    }
} // namespace YanLib::ui::components
