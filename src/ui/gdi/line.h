/* clang-format off */
/*
 * @file line.h
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
#ifndef LINE_H
#define LINE_H
#include <Windows.h>
#include <minwindef.h>
#include <wingdi.h>
#include <windef.h>
#include <cstdint>
#include <vector>
#include "gdi.h"
namespace YanLib::ui::gdi {
    class line {
    public:
        line(const line &other) = delete;

        line(line &&other) = delete;

        line &operator=(const line &other) = delete;

        line &operator=(line &&other) = delete;

        line() = default;

        ~line() = default;

        static bool to(HDC dc_handle, int32_t x, int32_t y);

        static bool dda(int32_t x_start,
                        int32_t y_start,
                        int32_t x_end,
                        int32_t y_end,
                        LINEDDAPROC line_dda_proc,
                        LPARAM data);

        static bool move_to(HDC dc_handle, int32_t x, int32_t y, POINT *point);

        static bool poly(HDC dc_handle, const std::vector<POINT> &point);

        static bool poly_to(HDC dc_handle, const std::vector<POINT> &point);

        static bool poly_poly(HDC dc_handle,
                              const std::vector<POINT> &point,
                              std::vector<uint32_t> &poly_count);

        static bool poly_poly_safe(HDC dc_handle,
                                   const std::vector<POINT> &point,
                                   std::vector<uint32_t> &poly_count);

        static bool poly_draw(HDC dc_handle,
                              const std::vector<POINT> &point,
                              const std::vector<PointType> &point_type);
    };
} // namespace YanLib::ui::gdi
#endif // LINE_H
