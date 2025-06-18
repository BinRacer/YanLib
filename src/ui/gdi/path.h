/* clang-format off */
/*
 * @file path.h
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
#ifndef PATH_H
#define PATH_H
#include <Windows.h>
#include <minwindef.h>
#include <windef.h>
#include <cstdint>
#include <vector>
#include "gdi.h"
namespace YanLib::ui::gdi {
    class path {
    public:
        path(const path &other) = delete;

        path(path &&other) = delete;

        path &operator=(const path &other) = delete;

        path &operator=(path &&other) = delete;

        path() = default;

        ~path() = default;

        static bool begin(HDC dc_handle);

        static bool end(HDC dc_handle);

        static int32_t get(HDC dc_handle,
                           std::vector<POINT> &point,
                           std::vector<PointType> &point_type);

        static bool fill(HDC dc_handle);

        static bool abort(HDC dc_handle);

        static bool flatten(HDC dc_handle);

        static bool stroke_and_fill(HDC dc_handle);

        static bool stroke(HDC dc_handle);

        static bool widen(HDC dc_handle);

        static HRGN get_region(HDC dc_handle);

        static bool close_figure(HDC dc_handle);

        static bool get_miter_limit(HDC dc_handle, FLOAT *limit);

        static bool set_miter_limit(HDC dc_handle, FLOAT limit, FLOAT *old);
    };
} // namespace YanLib::ui::gdi
#endif // PATH_H
