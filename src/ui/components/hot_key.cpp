/* clang-format off */
/*
 * @file hot_key.cpp
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
#include "hot_key.h"
#include <windowsx.h>
#include "helper/convert.h"
namespace YanLib::ui::components {
    hot_key::hot_key() {
        INITCOMMONCONTROLSEX icc = {};
        icc.dwSize = sizeof(INITCOMMONCONTROLSEX);
        icc.dwICC = ICC_HOTKEY_CLASS;
        InitCommonControlsEx(&icc);
    }

    hot_key::~hot_key() {
        for (auto &handle : hot_key_handles) {
            if (handle && IsWindow(handle)) {
                DestroyWindow(handle);
                handle = nullptr;
            }
        }
        hot_key_handles.clear();
    }

    HWND hot_key::create(uintptr_t hot_key_id,
                         HWND parent_window_handle,
                         LPARAM lparam,
                         int32_t x,
                         int32_t y,
                         int32_t width,
                         int32_t height,
                         core::WindowStyle window_style) {
        HWND result = CreateWindowExW(
                0L, L"msctls_hotkey32", nullptr,
                static_cast<uint32_t>(window_style), x, y, width, height,
                parent_window_handle, reinterpret_cast<HMENU>(hot_key_id),
                reinterpret_cast<CREATESTRUCT *>(lparam)->hInstance, nullptr);
        if (!result) {
            error_code = GetLastError();
            return nullptr;
        }
        hot_key_rwlock.write_lock();
        hot_key_handles.push_back(result);
        hot_key_rwlock.write_unlock();
        return result;
    }

    HWND hot_key::create(const char *hot_key_name,
                         uintptr_t hot_key_id,
                         HWND parent_window_handle,
                         LPARAM lparam,
                         int32_t x,
                         int32_t y,
                         int32_t width,
                         int32_t height,
                         core::WindowStyle window_style) {
        HWND result = CreateWindowExA(
                0L, "msctls_hotkey32", hot_key_name,
                static_cast<uint32_t>(window_style), x, y, width, height,
                parent_window_handle, reinterpret_cast<HMENU>(hot_key_id),
                reinterpret_cast<CREATESTRUCT *>(lparam)->hInstance, nullptr);
        if (!result) {
            error_code = GetLastError();
            return nullptr;
        }
        hot_key_rwlock.write_lock();
        hot_key_handles.push_back(result);
        hot_key_rwlock.write_unlock();
        return result;
    }

    HWND hot_key::create(const wchar_t *hot_key_name,
                         uintptr_t hot_key_id,
                         HWND parent_window_handle,
                         LPARAM lparam,
                         int32_t x,
                         int32_t y,
                         int32_t width,
                         int32_t height,
                         core::WindowStyle window_style) {
        HWND result = CreateWindowExW(
                0L, L"msctls_hotkey32", hot_key_name,
                static_cast<uint32_t>(window_style), x, y, width, height,
                parent_window_handle, reinterpret_cast<HMENU>(hot_key_id),
                reinterpret_cast<CREATESTRUCT *>(lparam)->hInstance, nullptr);
        if (!result) {
            error_code = GetLastError();
            return nullptr;
        }
        hot_key_rwlock.write_lock();
        hot_key_handles.push_back(result);
        hot_key_rwlock.write_unlock();
        return result;
    }

    bool hot_key::destroy(HWND hot_key_handle) {
        if (!hot_key_handle || !IsWindow(hot_key_handle)) {
            return false;
        }
        hot_key_rwlock.write_lock();
        const auto it = std::find(hot_key_handles.begin(),
                                  hot_key_handles.end(), hot_key_handle);
        if (it != hot_key_handles.end()) {
            *it = nullptr;
        }
        hot_key_rwlock.write_unlock();
        if (!DestroyWindow(hot_key_handle)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    std::pair<HotKeyModifiersKey, HotKeyVirtualKey>
    hot_key::get_hotkey(HWND hot_key_handle) {
        const auto hot_key = static_cast<uint16_t>(
                SendMessageW(hot_key_handle, HKM_GETHOTKEY, 0, 0));
        return std::make_pair(static_cast<HotKeyModifiersKey>(LOBYTE(hot_key)),
                              static_cast<HotKeyVirtualKey>(HIBYTE(hot_key)));
    }

    void
    hot_key::set_hotkey(HWND hot_key_handle, HotKeyModifiersKey mod, HotKeyVirtualKey vk) {
        const uint16_t hot_key =
                static_cast<uint8_t>(mod) | (static_cast<uint8_t>(vk) << 8);
        SendMessageW(hot_key_handle, HKM_SETHOTKEY, hot_key, 0);
    }

    void hot_key::set_rules(
            HWND hot_key_handle,
            RuleFlag rule,
            std::vector<std::pair<HotKeyModifiersKey, HotKeyVirtualKey>> &hot_key) {
        std::vector<uint32_t> temp = {};
        temp.reserve(hot_key.size());
        for (const auto &[mod, vk] : hot_key) {
            temp.emplace_back(static_cast<uint8_t>(mod) |
                              (static_cast<uint8_t>(vk) << 8));
        }
        SendMessageW(hot_key_handle, HKM_SETRULES, static_cast<uint32_t>(rule),
                     reinterpret_cast<LPARAM>(temp.data()));
    }

    uint32_t hot_key::err_code() const {
        return error_code;
    }

    std::string hot_key::err_string() const {
        std::string result = helper::convert::err_string(error_code);
        return result;
    }

    std::wstring hot_key::err_wstring() const {
        std::wstring result = helper::convert::err_wstring(error_code);
        return result;
    }
} // namespace YanLib::ui::components
