/* clang-format off */
/*
 * @file icon.h
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
#ifndef ICON_H
#define ICON_H
#include <Windows.h>
#include <WinUser.h>
#include <minwindef.h>
#include <windef.h>
#include <vector>
#include <string>
#include "sync/rwlock.h"
#include "core.h"
namespace YanLib::ui::core {
    class icon {
    private:
        std::vector<HICON> icon_handles = {};
        sync::rwlock rwlock = {};
        uint32_t error_code = 0;

    public:
        icon(const icon &other) = delete;

        icon(icon &&other) = delete;

        icon &operator=(const icon &other) = delete;

        icon &operator=(icon &&other) = delete;

        icon() = default;

        ~icon();

        HICON create(HINSTANCE instance_handle,
                     int32_t width,
                     int32_t height,
                     uint8_t planes,
                     uint8_t bits_pixel,
                     const uint8_t *and_bits,
                     const uint8_t *xor_bits);

        HICON create(uint8_t *res_buf,
                     uint32_t res_size,
                     bool is_icon,
                     uint32_t version);

        HICON create(uint8_t *res_buf,
                     uint32_t res_size,
                     bool is_icon,
                     uint32_t version,
                     int32_t desired_width,
                     int32_t desired_height,
                     IconFlag flag);

        HICON create(ICONINFO *icon_info);

        HICON load(HINSTANCE instance_handle, const char *icon_name);

        HICON load(HINSTANCE instance_handle, const wchar_t *icon_name);

        HICON copy(HICON icon_handle);

        bool draw(HDC dc_handle, int32_t x, int32_t y, HICON icon_handle);

        bool draw(HDC dc_handle,
                  int32_t left,
                  int32_t top,
                  HICON icon_handle,
                  int32_t width,
                  int32_t height,
                  uint32_t step_if_ani_cur,
                  HBRUSH hbr_flicker_free_draw,
                  DrawIconFlag flag);

        bool destroy(HICON icon_handle);

        bool get_info(HICON icon_handle, ICONINFO *icon_info);

        bool get_info(HICON icon_handle, ICONINFOEXA *icon_info);

        bool get_info(HICON icon_handle, ICONINFOEXW *icon_info);

        int32_t lookup_icon_id(uint8_t *res_buf, bool is_icon);

        int32_t lookup_icon_id(uint8_t *res_buf,
                               bool is_icon,
                               int32_t desired_width,
                               int32_t desired_height,
                               IconFlag flag);

        uint32_t extract(const char *file_name,
                         int32_t icon_index,
                         int32_t icon_width,
                         int32_t icon_height,
                         std::vector<HICON> &icon_handle,
                         uint32_t *icon_id,
                         IconFlag flag);

        uint32_t extract(const wchar_t *file_name,
                         int32_t icon_index,
                         int32_t icon_width,
                         int32_t icon_height,
                         std::vector<HICON> &icon_handle,
                         uint32_t *icon_id,
                         IconFlag flag);

        [[nodiscard]] uint32_t err_code() const;

        [[nodiscard]] std::string err_string() const;

        [[nodiscard]] std::wstring err_wstring() const;
    };
} // namespace YanLib::ui::core
#endif // ICON_H
