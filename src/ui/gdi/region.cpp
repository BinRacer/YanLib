/* clang-format off */
/*
 * @file region.cpp
 * @date 2025-05-02
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
#include "region.h"

namespace YanLib::ui::gdi {
    HRGN region::create_rect(int32_t left,
                             int32_t top,
                             int32_t right,
                             int32_t bottom) {
        return CreateRectRgn(left, top, right, bottom);
    }

    HRGN region::create_rect(const RECT *rect) {
        return CreateRectRgnIndirect(rect);
    }

    bool region::destroy_rect(HRGN region_handle) {
        return DeleteObject(region_handle);
    }

    HRGN region::create_round_rect(int32_t left,
                                   int32_t top,
                                   int32_t right,
                                   int32_t bottom,
                                   int32_t width,
                                   int32_t height) {
        return CreateRoundRectRgn(left, top, right, bottom, width, height);
    }

    bool region::destroy_round_rect(HRGN region_handle) {
        return DeleteObject(region_handle);
    }

    HRGN region::create_elliptic(int32_t left,
                                 int32_t top,
                                 int32_t right,
                                 int32_t bottom) {
        return CreateEllipticRgn(left, top, right, bottom);
    }

    HRGN region::create_elliptic(const RECT *rect) {
        return CreateEllipticRgnIndirect(rect);
    }

    bool region::destroy_elliptic(HRGN region_handle) {
        return DeleteObject(region_handle);
    }

    HRGN region::create_polygon(const std::vector<POINT> &point,
                                FillMode mode) {
        return CreatePolygonRgn(point.data(),
                                static_cast<int32_t>(point.size()),
                                static_cast<int32_t>(mode));
    }

    bool region::destroy_polygon(HRGN region_handle) {
        return DeleteObject(region_handle);
    }

    HRGN region::create_poly_polygon(const std::vector<POINT> &point,
                                     const std::vector<int32_t> &poly_count,
                                     FillMode mode) {
        return CreatePolyPolygonRgn(point.data(), poly_count.data(),
                                    static_cast<int32_t>(poly_count.size()),
                                    static_cast<int32_t>(mode));
    }

    bool region::destroy_poly_polygon(HRGN region_handle) {
        return DeleteObject(region_handle);
    }

    bool region::fill(HDC dc_handle, HRGN region_handle, HBRUSH brush_handle) {
        return FillRgn(dc_handle, region_handle, brush_handle);
    }

    HRGN region::create(const XFORM *xfrom, const RGNDATA *buf, uint32_t size) {
        return ExtCreateRegion(xfrom, size, buf);
    }

    bool region::destroy(HRGN region_handle) {
        return DeleteObject(region_handle);
    }

    bool region::frame(HDC dc_handle,
                       HRGN region_handle,
                       HBRUSH brush_handle,
                       int32_t width,
                       int32_t height) {
        return FrameRgn(dc_handle, region_handle, brush_handle, width, height);
    }

    RegionFlag region::combine(HRGN region_handle_dst,
                               HRGN region_handle_src1,
                               HRGN region_handle_src2,
                               RegionStyle style) {
        return static_cast<RegionFlag>(
                CombineRgn(region_handle_dst, region_handle_src1,
                           region_handle_src2, static_cast<int32_t>(style)));
    }

    bool region::equal(HRGN region_handle1, HRGN region_handle2) {
        return EqualRgn(region_handle1, region_handle2);
    }

    bool region::invert(HDC dc_handle, HRGN region_handle) {
        return InvertRgn(dc_handle, region_handle);
    }

    RegionFlag region::offset(HRGN region_handle, int32_t x, int32_t y) {
        return static_cast<RegionFlag>(OffsetRgn(region_handle, x, y));
    }

    bool region::paint(HDC dc_handle, HRGN region_handle) {
        return PaintRgn(dc_handle, region_handle);
    }

    bool region::contains_point(HRGN region_handle, int32_t x, int32_t y) {
        return PtInRegion(region_handle, x, y);
    }

    bool region::contains_rect(HRGN region_handle, const RECT *rect) {
        return RectInRegion(region_handle, rect);
    }

    FillMode region::get_poly_fill_mode(HDC dc_handle) {
        return static_cast<FillMode>(GetPolyFillMode(dc_handle));
    }

    FillMode region::set_poly_fill_mode(HDC dc_handle, FillMode mode) {
        return static_cast<FillMode>(
                SetPolyFillMode(dc_handle, static_cast<int32_t>(mode)));
    }

    bool region::set_rect(HRGN region_handle,
                          int32_t left,
                          int32_t top,
                          int32_t right,
                          int32_t bottom) {
        return SetRectRgn(region_handle, left, top, right, bottom);
    }

    RegionFlag region::get_box(HRGN region_handle, RECT *rect) {
        return static_cast<RegionFlag>(GetRgnBox(region_handle, rect));
    }

    RegionFlag
    region::get_update(HWND window_handle, HRGN region_handle, bool is_erase) {
        return static_cast<RegionFlag>(GetUpdateRgn(window_handle,
                                                    region_handle,
                                                    is_erase ? TRUE : FALSE));
    }

    bool region::validate(HWND window_handle, HRGN region_handle) {
        return ValidateRgn(window_handle, region_handle);
    }

    bool
    region::invalidate(HWND window_handle, HRGN region_handle, bool is_erase) {
        return InvalidateRgn(window_handle, region_handle,
                             is_erase ? TRUE : FALSE);
    }

    RegionFlag region::exclude_update(HDC dc_handle, HWND window_handle) {
        return static_cast<RegionFlag>(
                ExcludeUpdateRgn(dc_handle, window_handle));
    }

    std::pair<uint32_t, uint32_t>
    region::get_data(HRGN region_handle, RGNDATA *buf, uint32_t size) {
        uint32_t result = GetRegionData(region_handle, size, buf);
        uint32_t error_code = 0;
        if (!result) {
            error_code = GetLastError();
        }
        return std::make_pair(result, error_code);
    }
} // namespace YanLib::ui::gdi
