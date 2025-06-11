/* clang-format off */
/*
 * @file line.cpp
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
#include "line.h"

namespace YanLib::ui::gdi {
    bool line::to(HDC dc_handle, int32_t x, int32_t y) {
        return LineTo(dc_handle, x, y);
    }

    bool line::dda(int32_t x_start,
                   int32_t y_start,
                   int32_t x_end,
                   int32_t y_end,
                   LINEDDAPROC line_dda_proc,
                   LPARAM data) {
        return LineDDA(x_start, y_start, x_end, y_end, line_dda_proc, data);
    }

    bool line::move_to(HDC dc_handle, int32_t x, int32_t y, POINT *point) {
        return MoveToEx(dc_handle, x, y, point);
    }

    bool line::poly(HDC dc_handle, const std::vector<POINT> &point) {
        return Polyline(dc_handle, point.data(),
                        static_cast<int32_t>(point.size()));
    }

    bool line::poly_to(HDC dc_handle, const std::vector<POINT> &point) {
        return PolylineTo(dc_handle, point.data(),
                          static_cast<int32_t>(point.size()));
    }

    bool line::poly_poly(HDC dc_handle,
                         const std::vector<POINT> &point,
                         std::vector<uint32_t> &poly_count) {
        return PolyPolyline(dc_handle, point.data(),
                            reinterpret_cast<unsigned long *>(
                                    poly_count.data()),
                            poly_count.size());
    }

    bool line::poly_poly_safe(HDC dc_handle,
                              const std::vector<POINT> &point,
                              std::vector<uint32_t> &poly_count) {
        std::vector<unsigned long> temp(point.size());
        for (const auto &count : poly_count) {
            temp.push_back(count);
        }
        const bool is_ok = PolyPolyline(dc_handle, point.data(), temp.data(),
                                        poly_count.size());
        poly_count.clear();
        for (const auto &count : temp) {
            poly_count.push_back(count);
        }
        return is_ok;
    }

    bool line::poly_draw(HDC dc_handle,
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
