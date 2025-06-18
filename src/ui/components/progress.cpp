/* clang-format off */
/*
 * @file progress.cpp
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
#include "progress.h"
#include <windowsx.h>
#include "helper/convert.h"
namespace YanLib::ui::components {
    progress::progress() {
        INITCOMMONCONTROLSEX icc = {};
        icc.dwSize = sizeof(INITCOMMONCONTROLSEX);
        icc.dwICC = ICC_PROGRESS_CLASS;
        InitCommonControlsEx(&icc);
    }

    progress::~progress() {
        for (auto &handle : progress_handles) {
            if (handle && IsWindow(handle)) {
                DestroyWindow(handle);
                handle = nullptr;
            }
        }
        progress_handles.clear();
    }

    HWND progress::create(uintptr_t progress_id,
                          HWND parent_window_handle,
                          LPARAM lparam,
                          int32_t x,
                          int32_t y,
                          int32_t width,
                          int32_t height,
                          ProgressStyle style,
                          core::WindowStyle window_style) {
        HWND result = CreateWindowExW(0L, L"msctls_progress32", nullptr,
                                      static_cast<uint32_t>(window_style) |
                                              static_cast<uint32_t>(style),
                                      x, y, width, height, parent_window_handle,
                                      reinterpret_cast<HMENU>(progress_id),
                                      reinterpret_cast<CREATESTRUCT *>(lparam)
                                              ->hInstance,
                                      nullptr);
        if (!result) {
            error_code = GetLastError();
            return nullptr;
        }
        progress_rwlock.write_lock();
        progress_handles.push_back(result);
        progress_rwlock.write_unlock();
        return result;
    }

    HWND progress::create(const char *progress_name,
                          uintptr_t progress_id,
                          HWND parent_window_handle,
                          LPARAM lparam,
                          int32_t x,
                          int32_t y,
                          int32_t width,
                          int32_t height,
                          ProgressStyle style,
                          core::WindowStyle window_style) {
        HWND result = CreateWindowExA(0L, "msctls_progress32", progress_name,
                                      static_cast<uint32_t>(window_style) |
                                              static_cast<uint32_t>(style),
                                      x, y, width, height, parent_window_handle,
                                      reinterpret_cast<HMENU>(progress_id),
                                      reinterpret_cast<CREATESTRUCT *>(lparam)
                                              ->hInstance,
                                      nullptr);
        if (!result) {
            error_code = GetLastError();
            return nullptr;
        }
        progress_rwlock.write_lock();
        progress_handles.push_back(result);
        progress_rwlock.write_unlock();
        return result;
    }

    HWND progress::create(const wchar_t *progress_name,
                          uintptr_t progress_id,
                          HWND parent_window_handle,
                          LPARAM lparam,
                          int32_t x,
                          int32_t y,
                          int32_t width,
                          int32_t height,
                          ProgressStyle style,
                          core::WindowStyle window_style) {
        HWND result = CreateWindowExW(0L, L"msctls_progress32", progress_name,
                                      static_cast<uint32_t>(window_style) |
                                              static_cast<uint32_t>(style),
                                      x, y, width, height, parent_window_handle,
                                      reinterpret_cast<HMENU>(progress_id),
                                      reinterpret_cast<CREATESTRUCT *>(lparam)
                                              ->hInstance,
                                      nullptr);
        if (!result) {
            error_code = GetLastError();
            return nullptr;
        }
        progress_rwlock.write_lock();
        progress_handles.push_back(result);
        progress_rwlock.write_unlock();
        return result;
    }

    bool progress::destroy(HWND progress_handle) {
        if (!progress_handle || !IsWindow(progress_handle)) {
            return false;
        }
        progress_rwlock.write_lock();
        const auto it = std::find(progress_handles.begin(),
                                  progress_handles.end(), progress_handle);
        if (it != progress_handles.end()) {
            *it = nullptr;
        }
        progress_rwlock.write_unlock();
        if (!DestroyWindow(progress_handle)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    COLORREF progress::get_bar_color(HWND progress_handle) {
        return SendMessageW(progress_handle, PBM_GETBARCOLOR, 0, 0);
    }

    COLORREF progress::set_bar_color(HWND progress_handle, COLORREF color) {
        return SendMessageW(progress_handle, PBM_SETBARCOLOR, 0, color);
    }

    COLORREF progress::get_background_color(HWND progress_handle) {
        return SendMessageW(progress_handle, PBM_GETBKCOLOR, 0, 0);
    }

    COLORREF progress::set_background_color(HWND progress_handle,
                                            COLORREF color) {
        return SendMessageW(progress_handle, PBM_SETBARCOLOR, 0, color);
    }

    uint32_t progress::get_pos(HWND progress_handle) {
        return SendMessageW(progress_handle, PBM_GETPOS, 0, 0);
    }

    uint32_t progress::set_pos(HWND progress_handle, uint32_t pos) {
        return SendMessageW(progress_handle, PBM_SETPOS, pos, 0);
    }

    void progress::get_range(HWND progress_handle, PBRANGE *range) {
        SendMessageW(progress_handle, PBM_GETRANGE, TRUE,
                     reinterpret_cast<LPARAM>(range));
    }

    bool progress::set_range(HWND progress_handle, PBRANGE range) {
        return SendMessageW(progress_handle, PBM_SETRANGE, 0,
                            MAKELPARAM(range.iLow, range.iHigh));
    }

    bool progress::set_range(HWND progress_handle, int32_t low, int32_t high) {
        return SendMessageW(progress_handle, PBM_SETRANGE, 0,
                            MAKELPARAM(low, high));
    }

    void
    progress::set_range32(HWND progress_handle, int32_t low, int32_t high) {
        SendMessageW(progress_handle, PBM_SETRANGE32, low, high);
    }

    ProgressState progress::get_state(HWND progress_handle) {
        return static_cast<ProgressState>(
                SendMessageW(progress_handle, PBM_GETSTATE, 0, 0));
    }

    ProgressState progress::set_state(HWND progress_handle,
                                      ProgressState state) {
        return static_cast<ProgressState>(
                SendMessageW(progress_handle, PBM_SETSTATE,
                             static_cast<uint32_t>(state), 0));
    }

    uint32_t progress::get_step(HWND progress_handle) {
        return SendMessageW(progress_handle, PBM_GETSTEP, 0, 0);
    }

    uint32_t progress::set_step(HWND progress_handle, uint32_t step) {
        return SendMessageW(progress_handle, PBM_SETSTEP, step, 0);
    }

    uint32_t progress::set_delta_pos(HWND progress_handle, uint32_t increment) {
        return SendMessageW(progress_handle, PBM_DELTAPOS, increment, 0);
    }

    void progress::enable_marquee(HWND progress_handle, int32_t milli_second) {
        SendMessageW(progress_handle, PBM_SETMARQUEE, TRUE, milli_second);
    }

    void progress::disable_marquee(HWND progress_handle, int32_t milli_second) {
        SendMessageW(progress_handle, PBM_SETMARQUEE, FALSE, milli_second);
    }

    uint32_t progress::forward_step(HWND progress_handle) {
        return SendMessageW(progress_handle, PBM_STEPIT, 0, 0);
    }

    uint32_t progress::err_code() const {
        return error_code;
    }

    std::string progress::err_string() const {
        std::string result = helper::convert::err_string(error_code);
        return result;
    }

    std::wstring progress::err_wstring() const {
        std::wstring result = helper::convert::err_wstring(error_code);
        return result;
    }
} // namespace YanLib::ui::components
