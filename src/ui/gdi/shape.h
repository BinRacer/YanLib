/* clang-format off */
/*
 * @file shape.h
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
#ifndef SHAPE_H
#define SHAPE_H
#include <Windows.h>
#include <cstdint>
#include <vector>

namespace YanLib::ui::gdi {
    class shape {
    public:
        shape(const shape &other) = delete;

        shape(shape &&other) = delete;

        shape &operator=(const shape &other) = delete;

        shape &operator=(shape &&other) = delete;

        shape() = default;

        ~shape() = default;

        static bool rectangle(HDC dc_handle,
                              int32_t left,
                              int32_t top,
                              int32_t right,
                              int32_t bottom);

        static int32_t
        fill_rect(HDC dc_handle, const RECT *rect, HBRUSH brush_handle);

        static bool round_rect(HDC dc_handle,
                               int32_t left,
                               int32_t top,
                               int32_t right,
                               int32_t bottom,
                               int32_t width,
                               int32_t height);

        static int32_t
        frame_rect(HDC dc_handle, const RECT *rect, HBRUSH brush_handle);

        static bool invert_rect(HDC dc_handle, const RECT *rect);

        static bool ellipse(HDC dc_handle,
                            int32_t left,
                            int32_t top,
                            int32_t right,
                            int32_t bottom);

        static bool chord(HDC dc_handle,
                          int32_t rect_left,
                          int32_t rect_top,
                          int32_t rect_right,
                          int32_t rect_bottom,
                          int32_t start_radial_x,
                          int32_t start_radial_y,
                          int32_t end_radial_x,
                          int32_t end_radial_y);

        static bool poly_gon(HDC dc_handle, const std::vector<POINT> &point);

        static bool poly_poly_gon(HDC dc_handle,
                                  const std::vector<POINT> &point,
                                  const std::vector<int32_t> &poly_count);

        static bool pie(HDC dc_handle,
                        int32_t left,
                        int32_t top,
                        int32_t right,
                        int32_t bottom,
                        int32_t start_radial_x,
                        int32_t start_radial_y,
                        int32_t end_radial_x,
                        int32_t end_radial_y);
    };
} // namespace YanLib::ui::gdi
#endif // SHAPE_H
