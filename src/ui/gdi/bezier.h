/* clang-format off */
/*
 * @file bezier.h
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
#ifndef BEZIER_H
#define BEZIER_H
#include <Windows.h>
#include <windef.h>
#include <vector>
#include "gdi.h"
namespace YanLib::ui::gdi {
    class bezier {
    public:
        bezier(const bezier &other) = delete;

        bezier(bezier &&other) = delete;

        bezier &operator=(const bezier &other) = delete;

        bezier &operator=(bezier &&other) = delete;

        bezier() = default;

        ~bezier() = default;

        static bool poly(HDC dc_handle, const std::vector<POINT> &point);

        static bool poly_to(HDC dc_handle, const std::vector<POINT> &point);

        static bool poly_draw(HDC dc_handle,
                              const std::vector<POINT> &point,
                              const std::vector<PointType> &point_type);
    };
} // namespace YanLib::ui::gdi
#endif // BEZIER_H
