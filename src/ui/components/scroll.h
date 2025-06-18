/* clang-format off */
/*
 * @file scroll.h
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
#ifndef SCROLL_H
#define SCROLL_H
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
#include <WinUser.h>
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
    class scroll {
    private:
        std::vector<HWND> scroll_handles = {};
        sync::rwlock scroll_rwlock = {};
        uint32_t error_code = 0;

    public:
        scroll(const scroll &other) = delete;

        scroll(scroll &&other) = delete;

        scroll &operator=(const scroll &other) = delete;

        scroll &operator=(scroll &&other) = delete;

        scroll() = default;

        ~scroll();

        HWND create(uintptr_t scroll_id,
                    HWND parent_window_handle,
                    LPARAM lparam,
                    int32_t x,
                    int32_t y,
                    int32_t width,
                    int32_t height,
                    ScrollStyle style = ScrollStyle::Vert |
                            ScrollStyle::RightAlign,
                    core::WindowStyle window_style = core::WindowStyle::Child |
                            core::WindowStyle::Visible);

        HWND create(const char *scroll_name,
                    uintptr_t scroll_id,
                    HWND parent_window_handle,
                    LPARAM lparam,
                    int32_t x,
                    int32_t y,
                    int32_t width,
                    int32_t height,
                    ScrollStyle style = ScrollStyle::Vert |
                            ScrollStyle::RightAlign,
                    core::WindowStyle window_style = core::WindowStyle::Child |
                            core::WindowStyle::Visible);

        HWND create(const wchar_t *scroll_name,
                    uintptr_t scroll_id,
                    HWND parent_window_handle,
                    LPARAM lparam,
                    int32_t x,
                    int32_t y,
                    int32_t width,
                    int32_t height,
                    ScrollStyle style = ScrollStyle::Vert |
                            ScrollStyle::RightAlign,
                    core::WindowStyle window_style = core::WindowStyle::Child |
                            core::WindowStyle::Visible);

        bool destroy(HWND scroll_handle);

        bool enable(HWND scroll_handle,
                    ScrollType scroll_type = ScrollType::Both,
                    ArrowType arrow_type = ArrowType::EnableBoth);

        bool show(HWND scroll_handle,
                  ScrollType scroll_type = ScrollType::Both);

        bool hide(HWND scroll_handle,
                  ScrollType scroll_type = ScrollType::Both);

        bool get_info(HWND scroll_handle,
                      SCROLLBARINFO *scroll_bar_info,
                      core::ObjectID object_id = core::ObjectID::VScroll);

        bool get_info(HWND scroll_handle,
                      SCROLLINFO *scroll_info,
                      ScrollType scroll_type = ScrollType::Vert);

        int32_t set_info(HWND scroll_handle,
                         SCROLLINFO *scroll_info,
                         ScrollType scroll_type = ScrollType::Vert,
                         bool is_redraw = true);

        int32_t get_pos(HWND scroll_handle,
                        ScrollType scroll_type = ScrollType::Vert);

        int32_t set_pos(HWND scroll_handle,
                        int32_t pos,
                        ScrollType scroll_type = ScrollType::Vert,
                        bool is_redraw = true);

        bool get_range(HWND scroll_handle,
                       int32_t *min_pos,
                       int32_t *max_pos,
                       ScrollType scroll_type = ScrollType::Vert);

        bool set_range(HWND scroll_handle,
                       int32_t min_pos,
                       int32_t max_pos,
                       ScrollType scroll_type = ScrollType::Vert,
                       bool is_redraw = true);

        bool scroll_dc(HDC dc_handle,
                       int32_t x,
                       int32_t y,
                       const RECT *rect_scroll,
                       const RECT *rect_clip = nullptr,
                       HRGN region_update_handle = nullptr,
                       RECT *rect_update = nullptr);

        bool scroll_window(HWND scroll_handle,
                           int32_t x_amount,
                           int32_t y_amount,
                           const RECT *rect = nullptr,
                           const RECT *clip_rect = nullptr);

        int32_t scroll_window_extend(HWND scroll_handle,
                                     int32_t dx,
                                     int32_t dy,
                                     const RECT *rect_scroll = nullptr,
                                     const RECT *rect_clip = nullptr,
                                     HRGN region_handle_update = nullptr,
                                     RECT *rect_update = nullptr,
                                     ScrollFlag flag = ScrollFlag::InValidate |
                                             ScrollFlag::Erase);

        [[nodiscard]] uint32_t err_code() const;

        [[nodiscard]] std::string err_string() const;

        [[nodiscard]] std::wstring err_wstring() const;
    };
} // namespace YanLib::ui::components
#endif // SCROLL_H
