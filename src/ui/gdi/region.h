/* clang-format off */
/*
 * @file region.h
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
#ifndef REGION_H
#define REGION_H
#include <Windows.h>
#include <wingdi.h>
#include <windef.h>
#include <minwindef.h>
#include <utility>
#include <vector>
#include "gdi.h"
namespace YanLib::ui::gdi {
    class region {
    public:
        region(const region &other) = delete;

        region(region &&other) = delete;

        region &operator=(const region &other) = delete;

        region &operator=(region &&other) = delete;

        region() = default;

        ~region() = default;

        static HRGN
        create_rect(int32_t left, int32_t top, int32_t right, int32_t bottom);

        static HRGN create_rect(const RECT *rect);

        static bool destroy_rect(HRGN region_handle);

        static HRGN create_round_rect(int32_t left,
                                      int32_t top,
                                      int32_t right,
                                      int32_t bottom,
                                      int32_t width,
                                      int32_t height);

        static bool destroy_round_rect(HRGN region_handle);

        static HRGN create_elliptic(int32_t left,
                                    int32_t top,
                                    int32_t right,
                                    int32_t bottom);

        static HRGN create_elliptic(const RECT *rect);

        static bool destroy_elliptic(HRGN region_handle);

        static HRGN create_polygon(const std::vector<POINT> &point,
                                   FillMode mode);

        static bool destroy_polygon(HRGN region_handle);

        static HRGN create_poly_polygon(const std::vector<POINT> &point,
                                        const std::vector<int32_t> &poly_count,
                                        FillMode mode);

        static bool destroy_poly_polygon(HRGN region_handle);

        static bool
        fill(HDC dc_handle, HRGN region_handle, HBRUSH brush_handle);

        static HRGN
        create(const XFORM *xfrom, const RGNDATA *buf, uint32_t size);

        static bool destroy(HRGN region_handle);

        static bool frame(HDC dc_handle,
                          HRGN region_handle,
                          HBRUSH brush_handle,
                          int32_t width,
                          int32_t height);

        static RegionFlag combine(HRGN region_handle_dst,
                                  HRGN region_handle_src1,
                                  HRGN region_handle_src2,
                                  RegionStyle style);

        static bool equal(HRGN region_handle1, HRGN region_handle2);

        static bool invert(HDC dc_handle, HRGN region_handle);

        static RegionFlag offset(HRGN region_handle, int32_t x, int32_t y);

        static bool paint(HDC dc_handle, HRGN region_handle);

        static bool contains_point(HRGN region_handle, int32_t x, int32_t y);

        static bool contains_rect(HRGN region_handle, const RECT *rect);

        static FillMode get_poly_fill_mode(HDC dc_handle);

        static FillMode set_poly_fill_mode(HDC dc_handle, FillMode mode);

        static bool set_rect(HRGN region_handle,
                             int32_t left,
                             int32_t top,
                             int32_t right,
                             int32_t bottom);

        static RegionFlag get_box(HRGN region_handle, RECT *rect);

        static RegionFlag get_update(HWND window_handle,
                                     HRGN region_handle,
                                     bool is_erase = true);

        static bool validate(HWND window_handle, HRGN region_handle);

        static bool invalidate(HWND window_handle,
                               HRGN region_handle,
                               bool is_erase = true);

        static RegionFlag exclude_update(HDC dc_handle, HWND window_handle);

        // std::pair<result, error_code>
        static std::pair<uint32_t, uint32_t>
        get_data(HRGN region_handle, RGNDATA *buf, uint32_t size);
    };
} // namespace YanLib::ui::gdi
#endif // REGION_H
