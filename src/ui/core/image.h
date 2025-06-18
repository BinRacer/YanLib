/* clang-format off */
/*
 * @file image.h
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
#ifndef IMAGE_H
#define IMAGE_H
#include <Windows.h>
#include <minwindef.h>
#include <windef.h>
#include <string>
#include <vector>
#include "sync/rwlock.h"
#include "core.h"
namespace YanLib::ui::core {
    class image {
    private:
        std::vector<HBITMAP> bitmap_handles = {};
        std::vector<HICON> icon_handles = {};
        std::vector<HCURSOR> cursor_handles = {};
        sync::rwlock bitmap_rwlock = {};
        sync::rwlock icon_rwlock = {};
        sync::rwlock cursor_rwlock = {};
        uint32_t error_code = 0;

    public:
        image(const image &other) = delete;

        image(image &&other) = delete;

        image &operator=(const image &other) = delete;

        image &operator=(image &&other) = delete;

        image() = default;

        ~image();

        HBITMAP load_bitmap(HINSTANCE instance_handle,
                            const char *image_name,
                            int32_t width,
                            int32_t height,
                            ImageFlag flag);

        HBITMAP load_bitmap(HINSTANCE instance_handle,
                            const wchar_t *image_name,
                            int32_t width,
                            int32_t height,
                            ImageFlag flag);

        HICON load_icon(HINSTANCE instance_handle,
                        const char *image_name,
                        int32_t width,
                        int32_t height,
                        ImageFlag flag);

        HICON load_icon(HINSTANCE instance_handle,
                        const wchar_t *image_name,
                        int32_t width,
                        int32_t height,
                        ImageFlag flag);

        HCURSOR load_cursor(HINSTANCE instance_handle,
                            const char *image_name,
                            int32_t width,
                            int32_t height,
                            ImageFlag flag);

        HCURSOR load_cursor(HINSTANCE instance_handle,
                            const wchar_t *image_name,
                            int32_t width,
                            int32_t height,
                            ImageFlag flag);

        HBITMAP
        copy_bitmap(HBITMAP bitmap_handle,
                    int32_t width,
                    int32_t height,
                    ImageFlag flag);

        HICON
        copy_icon(HICON icon_handle,
                  int32_t width,
                  int32_t height,
                  ImageFlag flag);

        HCURSOR
        copy_cursor(HCURSOR cursor_handle,
                    int32_t width,
                    int32_t height,
                    ImageFlag flag);

        bool destroy_bitmap(HBITMAP bitmap_handle);

        bool destroy_icon(HICON icon_handle);

        bool destroy_cursor(HCURSOR cursor_handle);

        [[nodiscard]] uint32_t err_code() const;

        [[nodiscard]] std::string err_string() const;

        [[nodiscard]] std::wstring err_wstring() const;
    };
} // namespace YanLib::ui::core
#endif // IMAGE_H
