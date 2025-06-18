/* clang-format off */
/*
 * @file ip_addr.h
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
#ifndef IP_ADDR_H
#define IP_ADDR_H
#ifndef UNICODE
#define UNICODE
#endif
#ifndef _UNICODE
#define _UNICODE
#endif
#include <Windows.h>
#include <CommCtrl.h>
#include <minwindef.h>
#include <windef.h>
#include <cstdint>
#include <string>
#include <sstream>
#include <cwctype>
#include <vector>
#include "sync/rwlock.h"
#include "ui/core/core.h"
#include "components.h"
#pragma comment(lib, "ComCtl32.Lib")
#pragma comment(linker, "\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#pragma comment(lib, "User32.Lib")
namespace YanLib::ui::components {
    class ip_addr {
    private:
        std::vector<HWND> ip_addr_handles = {};
        sync::rwlock ip_addr_rwlock = {};
        uint32_t error_code = 0;

    public:
        ip_addr(const ip_addr &other) = delete;

        ip_addr(ip_addr &&other) = delete;

        ip_addr &operator=(const ip_addr &other) = delete;

        ip_addr &operator=(ip_addr &&other) = delete;

        ip_addr();

        ~ip_addr();

        HWND create(uintptr_t ip_addr_id,
                    HWND parent_window_handle,
                    LPARAM lparam,
                    int32_t x,
                    int32_t y,
                    int32_t width,
                    int32_t height,
                    core::WindowStyle window_style = core::WindowStyle::Child |
                            core::WindowStyle::Visible | core::WindowStyle::Border);

        HWND create(const char *ip_addr_name,
                    uintptr_t ip_addr_id,
                    HWND parent_window_handle,
                    LPARAM lparam,
                    int32_t x,
                    int32_t y,
                    int32_t width,
                    int32_t height,
                    core::WindowStyle window_style = core::WindowStyle::Child |
                            core::WindowStyle::Visible | core::WindowStyle::Border);

        HWND create(const wchar_t *ip_addr_name,
                    uintptr_t ip_addr_id,
                    HWND parent_window_handle,
                    LPARAM lparam,
                    int32_t x,
                    int32_t y,
                    int32_t width,
                    int32_t height,
                    core::WindowStyle window_style = core::WindowStyle::Child |
                            core::WindowStyle::Visible | core::WindowStyle::Border);

        bool destroy(HWND ip_addr_handle);

        uint32_t make(uint8_t a, uint8_t b, uint8_t c, uint8_t d);

        uint32_t make_range(uint8_t low, uint8_t high);

        uint8_t first(uint32_t ip);

        uint8_t second(uint32_t ip);

        uint8_t third(uint32_t ip);

        uint8_t fourth(uint32_t ip);

        bool get(HWND ip_addr_handle, uint32_t *ip);

        void set(HWND ip_addr_handle, uint32_t ip);

        void clear(HWND ip_addr_handle);

        bool is_empty(HWND ip_addr_handle);

        void set_focus(HWND ip_addr_handle, uint8_t index);

        bool set_range(HWND ip_addr_handle,
                       uint8_t index,
                       uint8_t low = 0,
                       uint8_t high = 255);

        std::string ip_to_string(uint32_t ip);

        std::wstring ip_to_wstring(uint32_t ip);

        bool ip_from_string(const std::string &ip, uint32_t *result);

        bool ip_from_wstring(const std::wstring &ip, uint32_t *result);

        [[nodiscard]] uint32_t err_code() const;

        [[nodiscard]] std::string err_string() const;

        [[nodiscard]] std::wstring err_wstring() const;
    };
} // namespace YanLib::ui::components
#endif // IP_ADDR_H
