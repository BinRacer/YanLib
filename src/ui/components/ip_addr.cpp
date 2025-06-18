/* clang-format off */
/*
 * @file ip_addr.cpp
 * @date 2025-05-26
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
#include "ip_addr.h"
#include <windowsx.h>
#include <vector>
#include "helper/convert.h"
namespace YanLib::ui::components {
    ip_addr::ip_addr() {
        INITCOMMONCONTROLSEX icc = {};
        icc.dwSize = sizeof(INITCOMMONCONTROLSEX);
        icc.dwICC = ICC_INTERNET_CLASSES;
        InitCommonControlsEx(&icc);
    }

    ip_addr::~ip_addr() {
        for (auto &handle : ip_addr_handles) {
            if (handle && IsWindow(handle)) {
                DestroyWindow(handle);
                handle = nullptr;
            }
        }
        ip_addr_handles.clear();
    }

    HWND ip_addr::create(uintptr_t ip_addr_id,
                         HWND parent_window_handle,
                         LPARAM lparam,
                         int32_t x,
                         int32_t y,
                         int32_t width,
                         int32_t height,
                         core::WindowStyle window_style) {
        HWND result = CreateWindowExW(
                0L, L"SysIPAddress32", nullptr,
                static_cast<uint32_t>(window_style), x, y, width, height,
                parent_window_handle, reinterpret_cast<HMENU>(ip_addr_id),
                reinterpret_cast<CREATESTRUCT *>(lparam)->hInstance, nullptr);
        if (!result) {
            error_code = GetLastError();
            return nullptr;
        }
        ip_addr_rwlock.write_lock();
        ip_addr_handles.push_back(result);
        ip_addr_rwlock.write_unlock();
        return result;
    }

    HWND ip_addr::create(const char *ip_addr_name,
                         uintptr_t ip_addr_id,
                         HWND parent_window_handle,
                         LPARAM lparam,
                         int32_t x,
                         int32_t y,
                         int32_t width,
                         int32_t height,
                         core::WindowStyle window_style) {
        HWND result = CreateWindowExA(
                0L, "SysIPAddress32", ip_addr_name,
                static_cast<uint32_t>(window_style), x, y, width, height,
                parent_window_handle, reinterpret_cast<HMENU>(ip_addr_id),
                reinterpret_cast<CREATESTRUCT *>(lparam)->hInstance, nullptr);
        if (!result) {
            error_code = GetLastError();
            return nullptr;
        }
        ip_addr_rwlock.write_lock();
        ip_addr_handles.push_back(result);
        ip_addr_rwlock.write_unlock();
        return result;
    }

    HWND ip_addr::create(const wchar_t *ip_addr_name,
                         uintptr_t ip_addr_id,
                         HWND parent_window_handle,
                         LPARAM lparam,
                         int32_t x,
                         int32_t y,
                         int32_t width,
                         int32_t height,
                         core::WindowStyle window_style) {
        HWND result = CreateWindowExW(
                0L, L"SysIPAddress32", ip_addr_name,
                static_cast<uint32_t>(window_style), x, y, width, height,
                parent_window_handle, reinterpret_cast<HMENU>(ip_addr_id),
                reinterpret_cast<CREATESTRUCT *>(lparam)->hInstance, nullptr);
        if (!result) {
            error_code = GetLastError();
            return nullptr;
        }
        ip_addr_rwlock.write_lock();
        ip_addr_handles.push_back(result);
        ip_addr_rwlock.write_unlock();
        return result;
    }

    bool ip_addr::destroy(HWND ip_addr_handle) {
        if (!ip_addr_handle || !IsWindow(ip_addr_handle)) {
            return false;
        }
        ip_addr_rwlock.write_lock();
        const auto it = std::find(ip_addr_handles.begin(),
                                  ip_addr_handles.end(), ip_addr_handle);
        if (it != ip_addr_handles.end()) {
            *it = nullptr;
        }
        ip_addr_rwlock.write_unlock();
        if (!DestroyWindow(ip_addr_handle)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    uint32_t ip_addr::make(uint8_t a, uint8_t b, uint8_t c, uint8_t d) {
        return MAKEIPADDRESS(a, b, c, d);
    }

    uint32_t ip_addr::make_range(uint8_t low, uint8_t high) {
        return MAKEIPRANGE(low, high);
    }

    uint8_t ip_addr::first(uint32_t ip) {
        return FIRST_IPADDRESS(ip);
    }

    uint8_t ip_addr::second(uint32_t ip) {
        return SECOND_IPADDRESS(ip);
    }

    uint8_t ip_addr::third(uint32_t ip) {
        return THIRD_IPADDRESS(ip);
    }

    uint8_t ip_addr::fourth(uint32_t ip) {
        return FOURTH_IPADDRESS(ip);
    }

    bool ip_addr::get(HWND ip_addr_handle, uint32_t *ip) {
        if (!ip) {
            return false;
        }
        const auto result = SendMessageW(ip_addr_handle, IPM_GETADDRESS, 0,
                                         reinterpret_cast<LPARAM>(ip));
        if (!result) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    void ip_addr::set(HWND ip_addr_handle, uint32_t ip) {
        SendMessageW(ip_addr_handle, IPM_SETADDRESS, 0, ip);
    }

    void ip_addr::clear(HWND ip_addr_handle) {
        SendMessageW(ip_addr_handle, IPM_CLEARADDRESS, 0, 0);
    }

    bool ip_addr::is_empty(HWND ip_addr_handle) {
        return SendMessageW(ip_addr_handle, IPM_ISBLANK, 0, 0);
    }

    void ip_addr::set_focus(HWND ip_addr_handle, uint8_t index) {
        SendMessageW(ip_addr_handle, IPM_SETFOCUS, index, 0);
    }

    bool ip_addr::set_range(HWND ip_addr_handle,
                            uint8_t index,
                            uint8_t low,
                            uint8_t high) {
        return SendMessageW(ip_addr_handle, IPM_SETRANGE, index,
                            MAKELONG(low, high));
    }

    std::string ip_addr::ip_to_string(uint32_t ip) {
        return std::to_string(ip);
    }

    std::wstring ip_addr::ip_to_wstring(uint32_t ip) {
        return std::to_wstring(ip);
    }
    bool ip_addr::ip_from_string(const std::string &ip, uint32_t *result) {
        if (ip.empty() || !result) {
            return false;
        }
        std::vector<std::string> parts;
        std::stringstream ss(ip);
        std::string part;
        while (std::getline(ss, part, '.')) {
            parts.push_back(part);
        }
        if (parts.size() != 4)
            return false;
        uint8_t octets[4] = {};
        for (int32_t i = 0; i < 4; ++i) {
            const auto &s = parts[i];
            if (s.empty() || s.length() > 3)
                return false;
            if (s.length() > 1 && s[0] == '0')
                return false;
            for (const char c : s) {
                if (!std::isdigit(static_cast<unsigned char>(c)))
                    return false;
            }
            uint32_t num = 0;
            for (const char c : s) {
                num = num * 10 + (c - '0');
                if (num > 255)
                    return false;
            }
            octets[i] = static_cast<uint8_t>(num);
        }
        *result = (static_cast<uint32_t>(octets[0]) << 24) |
                (static_cast<uint32_t>(octets[1]) << 16) |
                (static_cast<uint32_t>(octets[2]) << 8) |
                static_cast<uint32_t>(octets[3]);
        return true;
    }

    bool ip_addr::ip_from_wstring(const std::wstring &ip, uint32_t *result) {
        if (ip.empty() || !result) {
            return false;
        }
        std::vector<std::wstring> parts;
        std::wstringstream ss(ip);
        std::wstring part;
        while (std::getline(ss, part, L'.')) {
            parts.push_back(part);
        }
        if (parts.size() != 4)
            return false;
        uint8_t octets[4] = {};
        for (int32_t i = 0; i < 4; ++i) {
            const auto &s = parts[i];
            if (s.empty() || s.length() > 3)
                return false;
            if (s.length() > 1 && s[0] == L'0')
                return false;
            for (const wchar_t c : s) {
                if (!std::iswdigit(c))
                    return false;
            }
            uint32_t num = 0;
            for (const wchar_t c : s) {
                num = num * 10 + (c - L'0');
                if (num > 255)
                    return false;
            }
            octets[i] = static_cast<uint8_t>(num);
        }
        *result = (static_cast<uint32_t>(octets[0]) << 24) |
                (static_cast<uint32_t>(octets[1]) << 16) |
                (static_cast<uint32_t>(octets[2]) << 8) |
                static_cast<uint32_t>(octets[3]);
        return true;
    }

    uint32_t ip_addr::err_code() const {
        return error_code;
    }

    std::string ip_addr::err_string() const {
        std::string result = helper::convert::err_string(error_code);
        return result;
    }

    std::wstring ip_addr::err_wstring() const {
        std::wstring result = helper::convert::err_wstring(error_code);
        return result;
    }
} // namespace YanLib::ui::components
