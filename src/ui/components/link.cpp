/* clang-format off */
/*
 * @file link.cpp
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
#include "link.h"
#include <windowsx.h>

namespace YanLib::ui::components {
    link::link() {
        INITCOMMONCONTROLSEX icc = {};
        icc.dwSize = sizeof(INITCOMMONCONTROLSEX);
        icc.dwICC = ICC_LINK_CLASS;
        InitCommonControlsEx(&icc);
    }

    link::~link() {
        for (auto &handle : link_handles) {
            if (handle && IsWindow(handle)) {
                DestroyWindow(handle);
                handle = nullptr;
            }
        }
        link_handles.clear();
    }

    HWND link::create(uintptr_t link_id,
                      HWND parent_window_handle,
                      LPARAM lparam,
                      int32_t x,
                      int32_t y,
                      int32_t width,
                      int32_t height,
                      LinkStyle style,
                      WindowStyle window_style) {
        HWND result = CreateWindowExW(0L, L"SysLink", nullptr,
                                      static_cast<uint32_t>(window_style) |
                                              static_cast<uint32_t>(style),
                                      x, y, width, height, parent_window_handle,
                                      reinterpret_cast<HMENU>(link_id),
                                      reinterpret_cast<CREATESTRUCT *>(lparam)
                                              ->hInstance,
                                      nullptr);
        if (!result) {
            error_code = GetLastError();
            return nullptr;
        }
        link_rwlock.write_lock();
        link_handles.push_back(result);
        link_rwlock.write_unlock();
        return result;
    }

    HWND link::create(const char *link_name,
                      uintptr_t link_id,
                      HWND parent_window_handle,
                      LPARAM lparam,
                      int32_t x,
                      int32_t y,
                      int32_t width,
                      int32_t height,
                      LinkStyle style,
                      WindowStyle window_style,
                      helper::CodePage code_page) {
        HWND result = CreateWindowExW(
                0L, L"SysLink",
                helper::convert::str_to_wstr(link_name, code_page).data(),
                static_cast<uint32_t>(window_style) |
                        static_cast<uint32_t>(style),
                x, y, width, height, parent_window_handle,
                reinterpret_cast<HMENU>(link_id),
                reinterpret_cast<CREATESTRUCT *>(lparam)->hInstance, nullptr);
        if (!result) {
            error_code = GetLastError();
            return nullptr;
        }
        link_rwlock.write_lock();
        link_handles.push_back(result);
        link_rwlock.write_unlock();
        return result;
    }

    HWND link::create(const wchar_t *link_name,
                      uintptr_t link_id,
                      HWND parent_window_handle,
                      LPARAM lparam,
                      int32_t x,
                      int32_t y,
                      int32_t width,
                      int32_t height,
                      LinkStyle style,
                      WindowStyle window_style) {
        HWND result = CreateWindowExW(0L, L"SysLink", link_name,
                                      static_cast<uint32_t>(window_style) |
                                              static_cast<uint32_t>(style),
                                      x, y, width, height, parent_window_handle,
                                      reinterpret_cast<HMENU>(link_id),
                                      reinterpret_cast<CREATESTRUCT *>(lparam)
                                              ->hInstance,
                                      nullptr);
        if (!result) {
            error_code = GetLastError();
            return nullptr;
        }
        link_rwlock.write_lock();
        link_handles.push_back(result);
        link_rwlock.write_unlock();
        return result;
    }

    bool link::destroy(HWND link_handle) {
        if (!link_handle || !IsWindow(link_handle)) {
            return false;
        }
        link_rwlock.write_lock();
        const auto it = std::find(link_handles.begin(), link_handles.end(),
                                  link_handle);
        if (it != link_handles.end()) {
            *it = nullptr;
        }
        link_rwlock.write_unlock();
        if (!DestroyWindow(link_handle)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    int64_t link::get_ideal_height(HWND link_handle) {
        return SendMessageW(link_handle, LM_GETIDEALHEIGHT, 0, 0);
    }

    int64_t link::get_ideal_size(HWND link_handle, int32_t width, SIZE *size) {
        return SendMessageW(link_handle, LM_GETIDEALSIZE, width,
                            reinterpret_cast<LPARAM>(size));
    }

    bool link::get_item(HWND link_handle, LITEM *item) {
        return SendMessageW(link_handle, LM_GETITEM, 0,
                            reinterpret_cast<LPARAM>(item));
    }

    bool link::set_item(HWND link_handle, LITEM *item) {
        return SendMessageW(link_handle, LM_SETITEM, 0,
                            reinterpret_cast<LPARAM>(item));
    }

    bool link::hit_test(HWND link_handle, LHITTESTINFO *hit_test_info) {
        return SendMessageW(link_handle, LM_HITTEST, 0,
                            reinterpret_cast<LPARAM>(hit_test_info));
    }

    uint32_t link::err_code() const {
        return error_code;
    }

    std::string link::err_string() const {
        std::string result = helper::convert::err_string(error_code);
        return result;
    }

    std::wstring link::err_wstring() const {
        std::wstring result = helper::convert::err_wstring(error_code);
        return result;
    }
} // namespace YanLib::ui::components
