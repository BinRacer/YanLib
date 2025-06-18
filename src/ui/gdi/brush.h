/* clang-format off */
/*
 * @file brush.h
 * @date 2025-05-03
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
#ifndef BRUSH_H
#define BRUSH_H
#include <Windows.h>
#include <wingdi.h>
#include <windef.h>
#include <utility>
#include <vector>
#include "gdi.h"
namespace YanLib::ui::gdi {
    class brush {
    public:
        brush(const brush &other) = delete;

        brush(brush &&other) = delete;

        brush &operator=(const brush &other) = delete;

        brush &operator=(brush &&other) = delete;

        brush() = default;

        ~brush() = default;

        static HBRUSH create_solid(COLORREF color);

        static HBRUSH create_hatch(COLORREF color, HatchStyle hatch);

        static HBRUSH create_pattern(HBITMAP bitmap_handle);

        static HBRUSH create(const LOGBRUSH *log_brush);

        static LOGBRUSH
        make(BrushStyle brush, COLORREF color, HatchStyle hatch);

        static HBRUSH create_dib_pattern(const void *packed_dib,
                                         bool use_rgb = true);

        static bool destroy(HBRUSH hbrush);

        static bool get_origin(HDC dc_handle, POINT *point);

        static bool
        set_origin(HDC dc_handle, int32_t x, int32_t y, POINT *point);

        static HBRUSH get_system(ColorType type);

        static COLORREF get_dc_color(HDC dc_handle);

        static COLORREF set_dc_color(HDC dc_handle, COLORREF color);

        static COLORREF get_system_color(ColorType type);

        // std::pair<result, error_code>
        static std::pair<bool, uint32_t>
        set_system_color(const std::vector<int32_t> &ele,
                         const std::vector<COLORREF> &rgb);
    };
} // namespace YanLib::ui::gdi
#endif // BRUSH_H
