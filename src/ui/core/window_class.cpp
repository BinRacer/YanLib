/* clang-format off */
/*
 * @file window_class.cpp
 * @date 2025-05-18
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
#include "window_class.h"
#include "helper/convert.h"

namespace YanLib::ui::core {
    WNDCLASSEXA window_class::make(const char *class_name,
                                   WNDPROC window_proc,
                                   HINSTANCE instance_handle,
                                   ClassStyle style,
                                   const char *menu_name,
                                   int32_t class_extra_size,
                                   int32_t window_extra_size,
                                   HICON icon_handle,
                                   HCURSOR cursor_handle,
                                   HBRUSH brush_background_handle,
                                   HICON icon_small_handle) {
        WNDCLASSEXA result = {};
        result.cbSize = sizeof(WNDCLASSEXA);
        result.style = static_cast<uint32_t>(style);
        result.lpfnWndProc = window_proc;
        result.cbClsExtra = class_extra_size;
        result.cbWndExtra = window_extra_size;
        result.hInstance = instance_handle;
        result.hIcon = icon_handle;
        result.hCursor = cursor_handle;
        result.hbrBackground = brush_background_handle;
        result.lpszMenuName = menu_name;
        result.lpszClassName = class_name;
        result.hIconSm = icon_small_handle;
        return result;
    }

    WNDCLASSEXW window_class::make(const wchar_t *class_name,
                                   WNDPROC window_proc,
                                   HINSTANCE instance_handle,
                                   ClassStyle style,
                                   const wchar_t *menu_name,
                                   int32_t class_extra_size,
                                   int32_t window_extra_size,
                                   HICON icon_handle,
                                   HCURSOR cursor_handle,
                                   HBRUSH brush_background_handle,
                                   HICON icon_small_handle) {
        WNDCLASSEXW result = {};
        result.cbSize = sizeof(WNDCLASSEXW);
        result.style = static_cast<uint32_t>(style);
        result.lpfnWndProc = window_proc;
        result.cbClsExtra = class_extra_size;
        result.cbWndExtra = window_extra_size;
        result.hInstance = instance_handle;
        result.hIcon = icon_handle;
        result.hCursor = cursor_handle;
        result.hbrBackground = brush_background_handle;
        result.lpszMenuName = menu_name;
        result.lpszClassName = class_name;
        result.hIconSm = icon_small_handle;
        return result;
    }

    ATOM window_class::register_class(const WNDCLASSEXA *window_class) {
        const ATOM result = RegisterClassExA(window_class);
        if (!result) {
            error_code = GetLastError();
        }
        return result;
    }

    ATOM window_class::register_class(const WNDCLASSEXW *window_class) {
        const ATOM result = RegisterClassExW(window_class);
        if (!result) {
            error_code = GetLastError();
        }
        return result;
    }

    bool window_class::unregister_class(const char *class_name,
                                        HINSTANCE instance_handle) {
        if (!UnregisterClassA(class_name, instance_handle)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool window_class::unregister_class(const wchar_t *class_name,
                                        HINSTANCE instance_handle) {
        if (!UnregisterClassW(class_name, instance_handle)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool window_class::get_info(HINSTANCE instance_handle,
                                const char *class_name,
                                WNDCLASSA *window_class) {
        if (!GetClassInfoA(instance_handle, class_name, window_class)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool window_class::get_info(HINSTANCE instance_handle,
                                const wchar_t *class_name,
                                WNDCLASSW *window_class) {
        if (!GetClassInfoW(instance_handle, class_name, window_class)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool window_class::get_info(HINSTANCE instance_handle,
                                const char *class_name,
                                WNDCLASSEXA *window_class) {
        if (!GetClassInfoExA(instance_handle, class_name, window_class)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool window_class::get_info(HINSTANCE instance_handle,
                                const wchar_t *class_name,
                                WNDCLASSEXW *window_class) {
        if (!GetClassInfoExW(instance_handle, class_name, window_class)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    uint32_t window_class::get_long(HWND window_handle, int32_t index) {
        const uint32_t result = GetClassLongW(window_handle, index);
        if (!result) {
            error_code = GetLastError();
        }
        return result;
    }

    uint32_t
    window_class::set_long(HWND window_handle, int32_t index, int32_t value) {
        const uint32_t result = SetClassLongW(window_handle, index, value);
        if (!result) {
            error_code = GetLastError();
        }
        return result;
    }

    uintptr_t window_class::get_long_ptr(HWND window_handle, int32_t index) {
        const uintptr_t result = GetClassLongPtrW(window_handle, index);
        if (!result) {
            error_code = GetLastError();
        }
        return result;
    }

    uintptr_t window_class::set_long_ptr(HWND window_handle,
                                         int32_t index,
                                         intptr_t value) {
        const uintptr_t result = SetClassLongPtrW(window_handle, index, value);
        if (!result) {
            error_code = GetLastError();
        }
        return result;
    }

    uint16_t window_class::get_word(HWND window_handle, int32_t index) {
        const uint16_t result = GetClassWord(window_handle, index);
        if (!result) {
            error_code = GetLastError();
        }
        return result;
    }

    uint16_t
    window_class::set_word(HWND window_handle, int32_t index, uint16_t value) {
        const uint16_t result = SetClassWord(window_handle, index, value);
        if (!result) {
            error_code = GetLastError();
        }
        return result;
    }

    int32_t window_class::get_name(HWND window_handle,
                                   std::string &class_name) {
        const int32_t result =
                GetClassNameA(window_handle, class_name.data(),
                              static_cast<int32_t>(class_name.size()));
        if (!result) {
            error_code = GetLastError();
        }
        return result;
    }

    int32_t window_class::get_name(HWND window_handle,
                                   std::wstring &class_name) {
        const int32_t result =
                GetClassNameW(window_handle, class_name.data(),
                              static_cast<int32_t>(class_name.size()));
        if (!result) {
            error_code = GetLastError();
        }
        return result;
    }

    uint32_t window_class::err_code() const {
        return error_code;
    }

    std::string window_class::err_string() const {
        std::string result = helper::convert::err_string(error_code);
        return result;
    }

    std::wstring window_class::err_wstring() const {
        std::wstring result = helper::convert::err_wstring(error_code);
        return result;
    }
} // namespace YanLib::ui::core
