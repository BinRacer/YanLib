/* clang-format off */
/*
 * @file arc.cpp
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
#include "arc.h"

namespace YanLib::ui::gdi {
    bool arc::make(HDC dc_handle,
                   int32_t rect_left,
                   int32_t rect_top,
                   int32_t rect_right,
                   int32_t rect_bottom,
                   int32_t start_arc_x,
                   int32_t start_arc_y,
                   int32_t end_arc_x,
                   int32_t end_arc_y) {
        return Arc(dc_handle, rect_left, rect_top, rect_right, rect_bottom,
                   start_arc_x, start_arc_y, end_arc_x, end_arc_y);
    }

    bool arc::to(HDC dc_handle,
                 int32_t rect_left,
                 int32_t rect_top,
                 int32_t rect_right,
                 int32_t rect_bottom,
                 int32_t radial_x1,
                 int32_t radial_y1,
                 int32_t radial_x2,
                 int32_t radial_y2) {
        return ArcTo(dc_handle, rect_left, rect_top, rect_right, rect_bottom,
                     radial_x1, radial_y1, radial_x2, radial_y2);
    }

    bool arc::angle(HDC dc_handle,
                    int32_t x,
                    int32_t y,
                    uint32_t r,
                    FLOAT start_angle,
                    FLOAT sweep_angle) {
        return AngleArc(dc_handle, x, y, r, start_angle, sweep_angle);
    }

    int32_t arc::get_direction(HDC dc_handle) {
        return GetArcDirection(dc_handle);
    }

    int32_t arc::set_direction(HDC dc_handle, bool clock_wise) {
        return SetArcDirection(dc_handle,
                               clock_wise ? AD_CLOCKWISE : AD_COUNTERCLOCKWISE);
    }

    bool arc::poly_draw(HDC dc_handle,
                        const std::vector<POINT> &point,
                        const std::vector<PointType> &point_type) {
        if (point.size() != point_type.size()) {
            return false;
        }
        return PolyDraw(dc_handle, point.data(),
                        reinterpret_cast<const uint8_t *>(point_type.data()),
                        static_cast<int32_t>(point.size()));
    }
} // namespace YanLib::ui::gdi
