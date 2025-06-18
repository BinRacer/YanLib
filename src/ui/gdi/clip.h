/* clang-format off */
/*
 * @file clip.h
 * @date 2025-05-04
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
#ifndef CLIP_H
#define CLIP_H
#include <Windows.h>
#include <minwindef.h>
#include <windef.h>
#include <cstdint>
#include "gdi.h"
namespace YanLib::ui::gdi {
    class clip {
    public:
        clip(const clip &other) = delete;

        clip(clip &&other) = delete;

        clip &operator=(const clip &other) = delete;

        clip &operator=(clip &&other) = delete;

        clip() = default;

        ~clip() = default;

        static bool select_region(HDC dc_handle, RegionStyle style);

        static RegionFlag select_region(HDC dc_handle, HRGN region_handle);

        static RegionFlag
        select_region(HDC dc_handle, HRGN region_handle, RegionStyle style);

        static RegionFlag exclude_rect(HDC dc_handle,
                                       int32_t left,
                                       int32_t top,
                                       int32_t right,
                                       int32_t bottom);

        static RegionFlag intersect_rect(HDC dc_handle,
                                         int32_t left,
                                         int32_t top,
                                         int32_t right,
                                         int32_t bottom);

        static RegionFlag offset_region(HDC dc_handle, int32_t x, int32_t y);

        static bool contains(HDC dc_handle, const RECT *rect);

        static bool contains(HDC dc_handle, int32_t x, int32_t y);

        static RegionFlag get_border(HDC dc_handle, RECT *rect);

        static int32_t get_region(HDC dc_handle, HRGN region_handle);

        static int32_t get_meta_region(HDC dc_handle, HRGN region_handle);

        static RegionFlag set_meta_region(HDC dc_handle);

        static int32_t get_random_region(HDC dc_handle, HRGN region_handle);
    };
} // namespace YanLib::ui::gdi
#endif // CLIP_H
