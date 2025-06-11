/* clang-format off */
/*
 * @file pen.cpp
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
#include "pen.h"

namespace YanLib::ui::gdi {
    HPEN pen::create(COLORREF color, int32_t width, PenStyle style) {
        return CreatePen(static_cast<int32_t>(style), width, color);
    }

    HPEN pen::create(const LOGPEN *log_pen) {
        return CreatePenIndirect(log_pen);
    }

    LOGPEN pen::make(COLORREF color, POINT width, PenStyle style) {
        LOGPEN result = {};
        result.lopnColor = color;
        result.lopnWidth = width;
        result.lopnStyle = static_cast<uint32_t>(style);
        return result;
    }

    HPEN pen::create(uint32_t width,
                     const LOGBRUSH *log_brush,
                     std::vector<uint32_t> &len,
                     PenStyle style) {
        return ExtCreatePen(static_cast<uint32_t>(style), width, log_brush,
                            len.size(),
                            len.empty() ? nullptr
                                        : reinterpret_cast<unsigned long *>(
                                                  len.data()));
    }

    HPEN pen::create_safe(uint32_t width,
                          const LOGBRUSH *log_brush,
                          std::vector<uint32_t> &len,
                          PenStyle style) {
        std::vector<unsigned long> temp(len.size());
        for (const auto &item : len) {
            temp.push_back(item);
        }
        HPEN result =
                ExtCreatePen(static_cast<uint32_t>(style), width, log_brush,
                             len.size(), temp.empty() ? nullptr : temp.data());
        for (const auto &item : temp) {
            len.push_back(item);
        }
        return result;
    }

    bool pen::destroy(HPEN pen_handle) {
        return DeleteObject(pen_handle);
    }

    COLORREF pen::set_dc_color(HDC dc_handle, COLORREF color) {
        return SetDCPenColor(dc_handle, color);
    }
} // namespace YanLib::ui::gdi
