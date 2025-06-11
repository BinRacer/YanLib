/* clang-format off */
/*
 * @file shape.cpp
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
#include "shape.h"

namespace YanLib::ui::gdi {
    bool shape::rectangle(HDC dc_handle,
                          int32_t left,
                          int32_t top,
                          int32_t right,
                          int32_t bottom) {
        return Rectangle(dc_handle, left, top, right, bottom);
    }

    int32_t
    shape::fill_rect(HDC dc_handle, const RECT *rect, HBRUSH brush_handle) {
        return FillRect(dc_handle, rect, brush_handle);
    }

    bool shape::round_rect(HDC dc_handle,
                           int32_t left,
                           int32_t top,
                           int32_t right,
                           int32_t bottom,
                           int32_t width,
                           int32_t height) {
        return RoundRect(dc_handle, left, top, right, bottom, width, height);
    }

    int32_t
    shape::frame_rect(HDC dc_handle, const RECT *rect, HBRUSH brush_handle) {
        return FrameRect(dc_handle, rect, brush_handle);
    }

    bool shape::invert_rect(HDC dc_handle, const RECT *rect) {
        return InvertRect(dc_handle, rect);
    }

    bool shape::ellipse(HDC dc_handle,
                        int32_t left,
                        int32_t top,
                        int32_t right,
                        int32_t bottom) {
        return Ellipse(dc_handle, left, top, right, bottom);
    }

    bool shape::chord(HDC dc_handle,
                      int32_t rect_left,
                      int32_t rect_top,
                      int32_t rect_right,
                      int32_t rect_bottom,
                      int32_t start_radial_x,
                      int32_t start_radial_y,
                      int32_t end_radial_x,
                      int32_t end_radial_y) {
        return Chord(dc_handle, rect_left, rect_top, rect_right, rect_bottom,
                     start_radial_x, start_radial_y, end_radial_x,
                     end_radial_y);
    }

    bool shape::poly_gon(HDC dc_handle, const std::vector<POINT> &point) {
        return Polygon(dc_handle, point.data(),
                       static_cast<int32_t>(point.size()));
    }

    bool shape::poly_poly_gon(HDC dc_handle,
                              const std::vector<POINT> &point,
                              const std::vector<int32_t> &poly_count) {
        return PolyPolygon(dc_handle, point.data(), poly_count.data(),
                           static_cast<int32_t>(poly_count.size()));
    }

    bool shape::pie(HDC dc_handle,
                    int32_t left,
                    int32_t top,
                    int32_t right,
                    int32_t bottom,
                    int32_t start_radial_x,
                    int32_t start_radial_y,
                    int32_t end_radial_x,
                    int32_t end_radial_y) {
        return Pie(dc_handle, left, top, right, bottom, start_radial_x,
                   start_radial_y, end_radial_x, end_radial_y);
    }
} // namespace YanLib::ui::gdi
