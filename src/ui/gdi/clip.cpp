/* clang-format off */
/*
 * @file clip.cpp
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
#include "clip.h"

namespace YanLib::ui::gdi {
    bool clip::select_region(HDC dc_handle, RegionStyle style) {
        return SelectClipPath(dc_handle, static_cast<int32_t>(style));
    }

    RegionFlag clip::select_region(HDC dc_handle, HRGN region_handle) {
        return static_cast<RegionFlag>(SelectClipRgn(dc_handle, region_handle));
    }

    RegionFlag
    clip::select_region(HDC dc_handle, HRGN region_handle, RegionStyle style) {
        return static_cast<RegionFlag>(
                ExtSelectClipRgn(dc_handle, region_handle,
                                 static_cast<int32_t>(style)));
    }

    RegionFlag clip::exclude_rect(HDC dc_handle,
                                  int32_t left,
                                  int32_t top,
                                  int32_t right,
                                  int32_t bottom) {
        return static_cast<RegionFlag>(
                ExcludeClipRect(dc_handle, left, top, right, bottom));
    }

    RegionFlag clip::intersect_rect(HDC dc_handle,
                                    int32_t left,
                                    int32_t top,
                                    int32_t right,
                                    int32_t bottom) {
        return static_cast<RegionFlag>(
                IntersectClipRect(dc_handle, left, top, right, bottom));
    }

    RegionFlag clip::offset_region(HDC dc_handle, int32_t x, int32_t y) {
        return static_cast<RegionFlag>(OffsetClipRgn(dc_handle, x, y));
    }

    bool clip::contains(HDC dc_handle, const RECT *rect) {
        const int32_t is_ok = RectVisible(dc_handle, rect);
        return is_ok == TRUE || is_ok == 2;
    }

    bool clip::contains(HDC dc_handle, int32_t x, int32_t y) {
        const int32_t is_ok = PtVisible(dc_handle, x, y);
        return is_ok == TRUE;
    }

    RegionFlag clip::get_border(HDC dc_handle, RECT *rect) {
        return static_cast<RegionFlag>(GetClipBox(dc_handle, rect));
    }

    int32_t clip::get_region(HDC dc_handle, HRGN region_handle) {
        return GetClipRgn(dc_handle, region_handle);
    }

    int32_t clip::get_meta_region(HDC dc_handle, HRGN region_handle) {
        return GetMetaRgn(dc_handle, region_handle);
    }

    RegionFlag clip::set_meta_region(HDC dc_handle) {
        return static_cast<RegionFlag>(SetMetaRgn(dc_handle));
    }

    int32_t clip::get_random_region(HDC dc_handle, HRGN region_handle) {
        return GetRandomRgn(dc_handle, region_handle, SYSRGN);
    }
} // namespace YanLib::ui::gdi
