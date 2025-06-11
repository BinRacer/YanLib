/* clang-format off */
/*
 * @file brush.cpp
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
#include "brush.h"

namespace YanLib::ui::gdi {
    HBRUSH brush::create_solid(COLORREF color) {
        return CreateSolidBrush(color);
    }

    HBRUSH brush::create_hatch(COLORREF color, HatchStyle hatch) {
        return CreateHatchBrush(static_cast<int32_t>(hatch), color);
    }

    HBRUSH brush::create_pattern(HBITMAP bitmap_handle) {
        return CreatePatternBrush(bitmap_handle);
    }

    HBRUSH brush::create(const LOGBRUSH *log_brush) {
        return CreateBrushIndirect(log_brush);
    }

    LOGBRUSH brush::make(BrushStyle brush, COLORREF color, HatchStyle hatch) {
        LOGBRUSH result = {};
        result.lbStyle = static_cast<uint32_t>(brush);
        result.lbColor = color;
        result.lbHatch = static_cast<uintptr_t>(hatch);
        return result;
    }

    HBRUSH brush::create_dib_pattern(const void *packed_dib, bool use_rgb) {
        return CreateDIBPatternBrushPt(packed_dib,
                                       use_rgb ? DIB_RGB_COLORS
                                               : DIB_PAL_COLORS);
    }

    bool brush::destroy(HBRUSH hbrush) {
        return DeleteObject(hbrush);
    }

    bool brush::get_origin(HDC dc_handle, POINT *point) {
        return GetBrushOrgEx(dc_handle, point);
    }

    bool brush::set_origin(HDC dc_handle, int32_t x, int32_t y, POINT *point) {
        return SetBrushOrgEx(dc_handle, x, y, point);
    }

    HBRUSH brush::get_system(ColorType type) {
        return GetSysColorBrush(static_cast<int32_t>(type));
    }

    COLORREF brush::get_dc_color(HDC dc_handle) {
        return GetDCBrushColor(dc_handle);
    }

    COLORREF brush::set_dc_color(HDC dc_handle, COLORREF color) {
        return SetDCBrushColor(dc_handle, color);
    }

    COLORREF brush::get_system_color(ColorType type) {
        return GetSysColor(static_cast<int32_t>(type));
    }

    std::pair<bool, uint32_t>
    brush::set_system_color(const std::vector<int32_t> &ele,
                            const std::vector<COLORREF> &rgb) {
        uint32_t error_code = 0;
        if (!SetSysColors(static_cast<int32_t>(ele.size()), ele.data(),
                          rgb.data())) {
            error_code = GetLastError();
            return std::make_pair(false, error_code);
        }
        return std::make_pair(true, error_code);
    }
} // namespace YanLib::ui::gdi
