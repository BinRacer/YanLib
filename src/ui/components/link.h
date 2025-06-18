/* clang-format off */
/*
 * @file link.h
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
#ifndef LINK_H
#define LINK_H
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
#include "helper/convert.h"
#include "ui/core/core.h"
#include "components.h"
#pragma comment(lib, "ComCtl32.Lib")
#pragma comment(linker, "\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#pragma comment(lib, "User32.Lib")
namespace YanLib::ui::components {
    class link {
    private:
        std::vector<HWND> link_handles = {};
        sync::rwlock link_rwlock = {};
        uint32_t error_code = 0;

    public:
        link(const link &other) = delete;

        link(link &&other) = delete;

        link &operator=(const link &other) = delete;

        link &operator=(link &&other) = delete;

        link();

        ~link();

        HWND create(uintptr_t link_id,
                    HWND parent_window_handle,
                    LPARAM lparam,
                    int32_t x,
                    int32_t y,
                    int32_t width,
                    int32_t height,
                    LinkStyle style = LinkStyle::NoPrefix |
                            LinkStyle::UseVisualStyle |
                            LinkStyle::UseCustomText,
                    core::WindowStyle window_style = core::WindowStyle::Child |
                            core::WindowStyle::Visible | core::WindowStyle::TabStop);

        HWND create(const char *link_name,
                    uintptr_t link_id,
                    HWND parent_window_handle,
                    LPARAM lparam,
                    int32_t x,
                    int32_t y,
                    int32_t width,
                    int32_t height,
                    LinkStyle style = LinkStyle::NoPrefix |
                            LinkStyle::UseVisualStyle |
                            LinkStyle::UseCustomText,
                    core::WindowStyle window_style = core::WindowStyle::Child |
                            core::WindowStyle::Visible | core::WindowStyle::TabStop,
                    helper::CodePage code_page = helper::curr_code_page());

        HWND create(const wchar_t *link_name,
                    uintptr_t link_id,
                    HWND parent_window_handle,
                    LPARAM lparam,
                    int32_t x,
                    int32_t y,
                    int32_t width,
                    int32_t height,
                    LinkStyle style = LinkStyle::NoPrefix |
                            LinkStyle::UseVisualStyle |
                            LinkStyle::UseCustomText,
                    core::WindowStyle window_style = core::WindowStyle::Child |
                            core::WindowStyle::Visible | core::WindowStyle::TabStop);

        bool destroy(HWND link_handle);

        int64_t get_ideal_height(HWND link_handle);

        int64_t get_ideal_size(HWND link_handle, int32_t width, SIZE *size);

        bool get_item(HWND link_handle, LITEM *item);

        bool set_item(HWND link_handle, LITEM *item);

        bool hit_test(HWND link_handle, LHITTESTINFO *hit_test_info);

        [[nodiscard]] uint32_t err_code() const;

        [[nodiscard]] std::string err_string() const;

        [[nodiscard]] std::wstring err_wstring() const;
    };
} // namespace YanLib::ui::components
#endif // LINK_H
