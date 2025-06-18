/* clang-format off */
/*
 * @file label.h
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
#ifndef LABEL_H
#define LABEL_H
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
    class label {
    private:
        std::vector<HWND> label_handles = {};
        sync::rwlock label_rwlock = {};
        uint32_t error_code = 0;

    public:
        label(const label &other) = delete;

        label(label &&other) = delete;

        label &operator=(const label &other) = delete;

        label &operator=(label &&other) = delete;

        label() = default;

        ~label();

        HWND create(uintptr_t label_id,
                    HWND parent_window_handle,
                    LPARAM lparam,
                    int32_t x,
                    int32_t y,
                    int32_t width,
                    int32_t height,
                    LabelStyle style = LabelStyle::Center,
                    core::WindowStyle window_style = core::WindowStyle::Child |
                            core::WindowStyle::Visible);

        HWND create(const char *label_name,
                    uintptr_t label_id,
                    HWND parent_window_handle,
                    LPARAM lparam,
                    int32_t x,
                    int32_t y,
                    int32_t width,
                    int32_t height,
                    LabelStyle style = LabelStyle::Center,
                    core::WindowStyle window_style = core::WindowStyle::Child |
                            core::WindowStyle::Visible);

        HWND create(const wchar_t *label_name,
                    uintptr_t label_id,
                    HWND parent_window_handle,
                    LPARAM lparam,
                    int32_t x,
                    int32_t y,
                    int32_t width,
                    int32_t height,
                    LabelStyle style = LabelStyle::Center,
                    core::WindowStyle window_style = core::WindowStyle::Child |
                            core::WindowStyle::Visible);

        bool destroy(HWND label_handle);

        bool enable(HWND label_handle);

        bool disable(HWND label_handle);

        HICON get_icon(HWND label_handle);

        HICON set_icon(HWND label_handle, HICON icon_handle);

        HBITMAP get_bitmap(HWND label_handle);

        HBITMAP set_bitmap(HWND label_handle, HBITMAP bitmap_handle);

        HCURSOR get_cursor(HWND label_handle);

        HCURSOR set_cursor(HWND label_handle, HCURSOR cursor_handle);

        HENHMETAFILE get_enh_metafile(HWND label_handle);

        HENHMETAFILE set_enh_metafile(HWND label_handle,
                                      HENHMETAFILE enh_metafile_handle);

        int32_t get_text(HWND label_handle, std::string &text);

        int32_t get_text(HWND label_handle, std::wstring &text);

        int32_t set_text(HWND label_handle, const std::string &text);

        int32_t set_text(HWND label_handle, const std::wstring &text);

        int32_t get_text_len(HWND label_handle);

        [[nodiscard]] uint32_t err_code() const;

        [[nodiscard]] std::string err_string() const;

        [[nodiscard]] std::wstring err_wstring() const;
    };
} // namespace YanLib::ui::components
#endif // LABEL_H
