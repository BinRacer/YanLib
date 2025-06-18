/* clang-format off */
/*
 * @file page.h
 * @date 2025-05-28
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
#ifndef PAGE_H
#define PAGE_H
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
    class page {
    private:
        std::vector<HWND> pages_handles = {};
        sync::rwlock pages_rwlock = {};
        uint32_t error_code = 0;

    public:
        page(const page &other) = delete;

        page(page &&other) = delete;

        page &operator=(const page &other) = delete;

        page &operator=(page &&other) = delete;

        page();

        ~page();

        HWND create(uintptr_t page_id,
                    HWND parent_window_handle,
                    LPARAM lparam,
                    int32_t x,
                    int32_t y,
                    int32_t width,
                    int32_t height,
                    PageStyle style = PageStyle::Horizontal |
                            PageStyle::AutoScroll,
                    core::WindowStyle window_style = core::WindowStyle::Child |
                            core::WindowStyle::Visible);

        HWND create(const char *page_name,
                    uintptr_t page_id,
                    HWND parent_window_handle,
                    LPARAM lparam,
                    int32_t x,
                    int32_t y,
                    int32_t width,
                    int32_t height,
                    PageStyle style = PageStyle::Horizontal |
                            PageStyle::AutoScroll,
                    core::WindowStyle window_style = core::WindowStyle::Child |
                            core::WindowStyle::Visible);

        HWND create(const wchar_t *page_name,
                    uintptr_t page_id,
                    HWND parent_window_handle,
                    LPARAM lparam,
                    int32_t x,
                    int32_t y,
                    int32_t width,
                    int32_t height,
                    PageStyle style = PageStyle::Horizontal |
                            PageStyle::AutoScroll,
                    core::WindowStyle window_style = core::WindowStyle::Child |
                            core::WindowStyle::Visible);

        bool destroy(HWND page_handle);

        void enable_forward_mouse(HWND page_handle);

        void disable_forward_mouse(HWND page_handle);

        COLORREF get_background_color(HWND page_handle);

        COLORREF set_background_color(HWND page_handle, COLORREF color);

        int32_t get_border(HWND page_handle);

        int32_t set_border(HWND page_handle, int32_t border);

        int32_t get_button_size(HWND page_handle);

        int32_t set_button_size(HWND page_handle, int32_t size);

        PageButtonState get_button_state(HWND page_handle,
                                         PageButtonIndex index);

        void get_drop_target(HWND page_handle, IDropTarget **target);

        int32_t get_pos(HWND page_handle);

        void set_pos(HWND page_handle, int32_t pos);

        void recalc_size(HWND page_handle);

        void set_child(HWND page_handle, HWND child_window_handle);

        void set_scroll_info(HWND page_handle,
                             uint32_t timeout_ms,
                             uint32_t line_num,
                             uint32_t per_line_pixels);

        [[nodiscard]] uint32_t err_code() const;

        [[nodiscard]] std::string err_string() const;

        [[nodiscard]] std::wstring err_wstring() const;
    };
} // namespace YanLib::ui::components
#endif // PAGE_H
