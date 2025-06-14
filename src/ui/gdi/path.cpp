/* clang-format off */
/*
 * @file path.cpp
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
#include "path.h"

namespace YanLib::ui::gdi {
    bool path::begin(HDC dc_handle) {
        return BeginPath(dc_handle);
    }

    bool path::end(HDC dc_handle) {
        return EndPath(dc_handle);
    }

    int32_t path::get(HDC dc_handle,
                      std::vector<POINT> &point,
                      std::vector<PointType> &point_type) {
        if (point.size() != point_type.size()) {
            return 0;
        }
        return GetPath(dc_handle, point.data(),
                       reinterpret_cast<uint8_t *>(point_type.data()),
                       static_cast<int32_t>(point.size()));
    }

    bool path::fill(HDC dc_handle) {
        return FillPath(dc_handle);
    }

    bool path::abort(HDC dc_handle) {
        return AbortPath(dc_handle);
    }

    bool path::flatten(HDC dc_handle) {
        return FlattenPath(dc_handle);
    }

    bool path::stroke_and_fill(HDC dc_handle) {
        return StrokeAndFillPath(dc_handle);
    }

    bool path::stroke(HDC dc_handle) {
        return StrokePath(dc_handle);
    }

    bool path::widen(HDC dc_handle) {
        return WidenPath(dc_handle);
    }

    HRGN path::get_region(HDC dc_handle) {
        return PathToRegion(dc_handle);
    }

    bool path::close_figure(HDC dc_handle) {
        return CloseFigure(dc_handle);
    }

    bool path::get_miter_limit(HDC dc_handle, FLOAT *limit) {
        return GetMiterLimit(dc_handle, limit);
    }

    bool path::set_miter_limit(HDC dc_handle, FLOAT limit, FLOAT *old) {
        return SetMiterLimit(dc_handle, limit, old);
    }
} // namespace YanLib::ui::gdi
