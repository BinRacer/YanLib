/* clang-format off */
/*
 * @file bezier.cpp
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
#include "bezier.h"

namespace YanLib::ui::gdi {
    bool bezier::poly(HDC dc_handle, const std::vector<POINT> &point) {
        return PolyBezier(dc_handle, point.data(), point.size());
    }

    bool bezier::poly_to(HDC dc_handle, const std::vector<POINT> &point) {
        return PolyBezierTo(dc_handle, point.data(), point.size());
    }

    bool bezier::poly_draw(HDC dc_handle,
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
