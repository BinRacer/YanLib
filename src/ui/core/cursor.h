/* clang-format off */
/*
 * @file cursor.h
 * @date 2025-04-30
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
#ifndef CURSOR_H
#define CURSOR_H
#include <Windows.h>
#include <winnt.h>
#include <WinUser.h>
#include <minwindef.h>
#include <windef.h>
#include <string>
#include <vector>
#include "sync/rwlock.h"
namespace YanLib::ui::core {
    class cursor {
    private:
        std::vector<HCURSOR> cursor_handles = {};
        sync::rwlock rwlock = {};
        uint32_t error_code = 0;

    public:
        cursor(const cursor &other) = delete;

        cursor(cursor &&other) = delete;

        cursor &operator=(const cursor &other) = delete;

        cursor &operator=(cursor &&other) = delete;

        cursor() = default;

        ~cursor();

        HCURSOR create(HINSTANCE instance_handle,
                       int32_t x_hotspot,
                       int32_t y_hotspot,
                       int32_t width,
                       int32_t height,
                       const void *and_plane,
                       const void *xor_plane);

        HCURSOR load(HINSTANCE instance_handle, const char *cursor_name);

        HCURSOR load(HINSTANCE instance_handle, const wchar_t *cursor_name);

        HCURSOR load(const char *file_name);

        HCURSOR load(const wchar_t *file_name);

        bool clip(const RECT *rect);

        HCURSOR copy(HCURSOR cursor_handle);

        HCURSOR get_cursor();

        HCURSOR set_cursor(HCURSOR cursor_handle);

        bool get_info(CURSORINFO *cursor_info);

        bool get_pos(POINT *point);

        bool set_pos(int32_t x, int32_t y);

        bool get_clip(RECT *rect);

        bool get_physical_pos(POINT *point);

        bool set_physical_pos(int32_t x, int32_t y);

        bool get_pointer_id(uint32_t pointer_id, uint32_t *cursor_id);

        bool get_pointer_device(HANDLE device_handle,
                                uint32_t *cursor_count,
                                POINTER_DEVICE_CURSOR_INFO cursor[]);

        bool set_system_cursor(HCURSOR cursor_handle, uint32_t id);

        uint32_t set_thread_scaling(
                uint32_t cursor_dpi = CURSOR_CREATION_SCALING_DEFAULT);

        int32_t show_cursor();

        int32_t hide_cursor();

        bool destroy(HCURSOR cursor_handle);

        [[nodiscard]] uint32_t err_code() const;

        [[nodiscard]] std::string err_string() const;

        [[nodiscard]] std::wstring err_wstring() const;
    };
} // namespace YanLib::ui::core
#endif // CURSOR_H
