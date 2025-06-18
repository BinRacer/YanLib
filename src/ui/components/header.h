/* clang-format off */
/*
 * @file header.h
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
#ifndef HEADER_H
#define HEADER_H
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
#include <vector>
#include <string>
#include "sync/rwlock.h"
#include "ui/core/core.h"
#include "components.h"
#pragma comment(lib, "ComCtl32.Lib")
#pragma comment(linker, "\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#pragma comment(lib, "User32.Lib")
namespace YanLib::ui::components {
    class header {
    private:
        std::vector<HWND> header_handles = {};
        sync::rwlock header_rwlock = {};
        uint32_t error_code = 0;

    public:
        header(const header &other) = delete;

        header(header &&other) = delete;

        header &operator=(const header &other) = delete;

        header &operator=(header &&other) = delete;

        header();

        ~header();

        HWND create(uintptr_t header_id,
                    HWND parent_window_handle,
                    LPARAM lparam,
                    int32_t x,
                    int32_t y,
                    int32_t width,
                    int32_t height,
                    HeaderStyle style = HeaderStyle::Buttons |
                            HeaderStyle::DragDrop | HeaderStyle::FilterBar |
                            HeaderStyle::HotTrack | HeaderStyle::CheckBoxes |
                            HeaderStyle::Overflow | HeaderStyle::Flat |
                            HeaderStyle::Horiz,
                    core::WindowStyle window_style = core::WindowStyle::Child |
                            core::WindowStyle::Visible | core::WindowStyle::Border);

        HWND create(const char *header_name,
                    uintptr_t header_id,
                    HWND parent_window_handle,
                    LPARAM lparam,
                    int32_t x,
                    int32_t y,
                    int32_t width,
                    int32_t height,
                    HeaderStyle style = HeaderStyle::Buttons |
                            HeaderStyle::DragDrop | HeaderStyle::FilterBar |
                            HeaderStyle::HotTrack | HeaderStyle::CheckBoxes |
                            HeaderStyle::Overflow | HeaderStyle::Flat |
                            HeaderStyle::Horiz,
                    core::WindowStyle window_style = core::WindowStyle::Child |
                            core::WindowStyle::Visible | core::WindowStyle::Border);

        HWND create(const wchar_t *header_name,
                    uintptr_t header_id,
                    HWND parent_window_handle,
                    LPARAM lparam,
                    int32_t x,
                    int32_t y,
                    int32_t width,
                    int32_t height,
                    HeaderStyle style = HeaderStyle::Buttons |
                            HeaderStyle::DragDrop | HeaderStyle::FilterBar |
                            HeaderStyle::HotTrack | HeaderStyle::CheckBoxes |
                            HeaderStyle::Overflow | HeaderStyle::Flat |
                            HeaderStyle::Horiz,
                    core::WindowStyle window_style = core::WindowStyle::Child |
                            core::WindowStyle::Visible | core::WindowStyle::Border);

        bool destroy(HWND header_handle);

        HIMAGELIST create_drag_image(HWND header_handle, int32_t index);

        HIMAGELIST get_image_list(HWND header_handle);

        HIMAGELIST set_image_list(HWND header_handle,
                                  HIMAGELIST image_list_handle);

        HIMAGELIST get_state_image_list(HWND header_handle);

        HIMAGELIST set_state_image_list(HWND header_handle,
                                        HIMAGELIST image_list_handle);

        int32_t get_bitmap_margin(HWND header_handle);

        int32_t set_bitmap_margin(HWND header_handle, int32_t width);

        bool clear_all_filters(HWND header_handle);

        bool clear_filter(HWND header_handle, int32_t index);

        bool set_filter(HWND header_handle,
                        int32_t index,
                        bool discard_change = false);

        int32_t insert_item(HWND header_handle,
                            const HDITEMW *item,
                            int32_t index = INT32_MAX);

        bool delete_item(HWND header_handle, int32_t index);

        bool get_item(HWND header_handle, HDITEMW *item, int32_t index);

        bool set_item(HWND header_handle, HDITEMW *item, int32_t index);

        int32_t get_item_count(HWND header_handle);

        bool get_item_rect(HWND header_handle, RECT *rect, int32_t index);

        bool
        get_item_drop_down_rect(HWND header_handle, RECT *rect, int32_t index);

        int32_t get_focused_item(HWND header_handle);

        bool set_focused_item(HWND header_handle, int32_t index);

        bool get_item_order(HWND header_handle, std::vector<int32_t> &order);

        bool set_item_order(HWND header_handle, std::vector<int32_t> &order);

        int32_t order_to_index(HWND header_handle, int32_t order);

        bool get_overflow_rect(HWND header_handle, RECT *rect);

        bool is_ansi_format(HWND header_handle);

        bool is_unicode_format(HWND header_handle);

        void set_unicode_format(HWND header_handle);

        void set_ansi_format(HWND header_handle);

        bool get_layout(HWND header_handle, HDLAYOUT *layout);

        int32_t set_filter_change_timeout(HWND header_handle,
                                          int32_t milli_seconds);

        int32_t set_hot_divider(HWND header_handle, uint32_t x, uint32_t y);

        int32_t set_hot_divider(HWND header_handle, uint32_t index);

        [[nodiscard]] uint32_t err_code() const;

        [[nodiscard]] std::string err_string() const;

        [[nodiscard]] std::wstring err_wstring() const;
    };
} // namespace YanLib::ui::components
#endif // HEADER_H
