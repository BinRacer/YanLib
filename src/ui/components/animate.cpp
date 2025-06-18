/* clang-format off */
/*
 * @file animate.cpp
 * @date 2025-05-24
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
#include "animate.h"
#include <windowsx.h>
namespace YanLib::ui::components {
    animate::animate() {
        INITCOMMONCONTROLSEX icc = {};
        icc.dwSize = sizeof(INITCOMMONCONTROLSEX);
        icc.dwICC = ICC_ANIMATE_CLASS;
        InitCommonControlsEx(&icc);
    }

    animate::~animate() {
        for (auto &resource : resource_handles) {
            if (resource && IsWindow(resource)) {
                Animate_Close(resource);
                resource = nullptr;
            }
        }
        resource_handles.clear();
        for (auto &handle : animate_handles) {
            if (handle && IsWindow(handle)) {
                DestroyWindow(handle);
                handle = nullptr;
            }
        }
        animate_handles.clear();
    }

    HWND animate::create(uintptr_t animate_id,
                         HWND parent_window_handle,
                         LPARAM lparam,
                         AnimateStyle style,
                         core::WindowStyle window_style) {
        HWND result = CreateWindowExW(0L, L"SysAnimate32", nullptr,
                                      static_cast<uint32_t>(window_style) |
                                              static_cast<uint32_t>(style),
                                      0, 0, 0, 0, parent_window_handle,
                                      reinterpret_cast<HMENU>(animate_id),
                                      reinterpret_cast<CREATESTRUCT *>(lparam)
                                              ->hInstance,
                                      nullptr);
        if (!result) {
            error_code = GetLastError();
            return nullptr;
        }
        animate_rwlock.write_lock();
        animate_handles.push_back(result);
        animate_rwlock.write_unlock();
        return result;
    }

    HWND animate::create(const char *animate_name,
                         uintptr_t animate_id,
                         HWND parent_window_handle,
                         LPARAM lparam,
                         AnimateStyle style,
                         core::WindowStyle window_style) {
        HWND result = CreateWindowExA(0L, "SysAnimate32", animate_name,
                                      static_cast<uint32_t>(window_style) |
                                              static_cast<uint32_t>(style),
                                      0, 0, 0, 0, parent_window_handle,
                                      reinterpret_cast<HMENU>(animate_id),
                                      reinterpret_cast<CREATESTRUCT *>(lparam)
                                              ->hInstance,
                                      nullptr);
        if (!result) {
            error_code = GetLastError();
            return nullptr;
        }
        animate_rwlock.write_lock();
        animate_handles.push_back(result);
        animate_rwlock.write_unlock();
        return result;
    }

    HWND animate::create(const wchar_t *animate_name,
                         uintptr_t animate_id,
                         HWND parent_window_handle,
                         LPARAM lparam,
                         AnimateStyle style,
                         core::WindowStyle window_style) {
        HWND result = CreateWindowExW(0L, L"SysAnimate32", animate_name,
                                      static_cast<uint32_t>(window_style) |
                                              static_cast<uint32_t>(style),
                                      0, 0, 0, 0, parent_window_handle,
                                      reinterpret_cast<HMENU>(animate_id),
                                      reinterpret_cast<CREATESTRUCT *>(lparam)
                                              ->hInstance,
                                      nullptr);
        if (!result) {
            error_code = GetLastError();
            return nullptr;
        }
        animate_rwlock.write_lock();
        animate_handles.push_back(result);
        animate_rwlock.write_unlock();
        return result;
    }

    bool animate::destroy(HWND animate_handle) {
        if (!animate_handle || !IsWindow(animate_handle)) {
            return false;
        }
        animate_rwlock.write_lock();
        const auto it = std::find(animate_handles.begin(),
                                  animate_handles.end(), animate_handle);
        if (it != animate_handles.end()) {
            *it = nullptr;
        }
        animate_rwlock.write_unlock();
        if (!DestroyWindow(animate_handle)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool animate::open(HWND animate_handle,
                       const char *file_name,
                       helper::CodePage code_page) {
        resource_rwlock.write_lock();
        const auto it = std::find(resource_handles.begin(),
                                  resource_handles.end(), animate_handle);
        if (it == resource_handles.end()) {
            resource_handles.push_back(animate_handle);
        }
        resource_rwlock.write_unlock();
        return Animate_Open(animate_handle,
                            helper::convert::str_to_wstr(file_name, code_page)
                                    .data());
    }

    bool animate::open(HWND animate_handle, wchar_t *file_name) {
        resource_rwlock.write_lock();
        const auto it = std::find(resource_handles.begin(),
                                  resource_handles.end(), animate_handle);
        if (it == resource_handles.end()) {
            resource_handles.push_back(animate_handle);
        }
        resource_rwlock.write_unlock();
        return Animate_Open(animate_handle, file_name);
    }

    bool animate::open(HWND animate_handle,
                       HINSTANCE dll_handle,
                       const char *file_name,
                       helper::CodePage code_page) {
        resource_rwlock.write_lock();
        const auto it = std::find(resource_handles.begin(),
                                  resource_handles.end(), animate_handle);
        if (it == resource_handles.end()) {
            resource_handles.push_back(animate_handle);
        }
        resource_rwlock.write_unlock();
        return Animate_OpenEx(animate_handle, dll_handle,
                              helper::convert::str_to_wstr(file_name, code_page)
                                      .data());
    }

    bool animate::open(HWND animate_handle,
                       HINSTANCE dll_handle,
                       wchar_t *file_name) {
        resource_rwlock.write_lock();
        const auto it = std::find(resource_handles.begin(),
                                  resource_handles.end(), animate_handle);
        if (it == resource_handles.end()) {
            resource_handles.push_back(animate_handle);
        }
        resource_rwlock.write_unlock();
        return Animate_OpenEx(animate_handle, dll_handle, file_name);
    }

    void animate::close(HWND animate_handle) {
        if (!animate_handle || !IsWindow(animate_handle)) {
            return;
        }
        resource_rwlock.write_lock();
        const auto it = std::find(resource_handles.begin(),
                                  resource_handles.end(), animate_handle);
        if (it != resource_handles.end()) {
            *it = nullptr;
        }
        resource_rwlock.write_unlock();
        Animate_Close(animate_handle);
    }

    bool animate::play(HWND animate_handle,
                       uint32_t from,
                       uint32_t to,
                       uint32_t repeat) {
        return Animate_Play(animate_handle, from, to, repeat);
    }

    bool animate::seek(HWND animate_handle, uint32_t frame_index) {
        return Animate_Seek(animate_handle, frame_index);
    }

    bool animate::stop(HWND animate_handle) {
        return Animate_Stop(animate_handle);
    }

    bool animate::is_playing(HWND animate_handle) {
        return Animate_IsPlaying(animate_handle);
    }

    uint32_t animate::err_code() const {
        return error_code;
    }

    std::string animate::err_string() const {
        std::string result = helper::convert::err_string(error_code);
        return result;
    }

    std::wstring animate::err_wstring() const {
        std::wstring result = helper::convert::err_wstring(error_code);
        return result;
    }
} // namespace YanLib::ui::components
