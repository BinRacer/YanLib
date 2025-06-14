/* clang-format off */
/*
 * @file window_prop.cpp
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
#include "window_prop.h"
#include "helper/convert.h"
namespace YanLib::ui::core {
    int32_t window_prop::enum_prop(HWND window_handle,
                                   PROPENUMPROCA enum_func) {
        return EnumPropsA(window_handle, enum_func);
    }

    int32_t window_prop::enum_prop(HWND window_handle,
                                   PROPENUMPROCW enum_func) {
        return EnumPropsW(window_handle, enum_func);
    }

    int32_t window_prop::enum_prop(HWND window_handle,
                                   PROPENUMPROCEXA enum_func,
                                   LPARAM lparam) {
        return EnumPropsExA(window_handle, enum_func, lparam);
    }

    int32_t window_prop::enum_prop(HWND window_handle,
                                   PROPENUMPROCEXW enum_func,
                                   LPARAM lparam) {
        return EnumPropsExW(window_handle, enum_func, lparam);
    }

    void *window_prop::get_prop(HWND window_handle, const char *key) {
        return GetPropA(window_handle, key);
    }

    void *window_prop::get_prop(HWND window_handle, const wchar_t *key) {
        return GetPropW(window_handle, key);
    }

    bool
    window_prop::set_prop(HWND window_handle, const char *key, void *value) {
        if (!SetPropA(window_handle, key, value)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool
    window_prop::set_prop(HWND window_handle, const wchar_t *key, void *value) {
        if (!SetPropW(window_handle, key, value)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    void *window_prop::remove_prop(HWND window_handle, const char *key) {
        return RemovePropA(window_handle, key);
    }

    void *window_prop::remove_prop(HWND window_handle, const wchar_t *key) {
        return RemovePropW(window_handle, key);
    }
    uint32_t window_prop::err_code() const {
        return error_code;
    }

    std::string window_prop::err_string() const {
        std::string result = helper::convert::err_string(error_code);
        return result;
    }

    std::wstring window_prop::err_wstring() const {
        std::wstring result = helper::convert::err_wstring(error_code);
        return result;
    }
} // namespace YanLib::ui::core
