/* clang-format off */
/*
 * @file rect.cpp
 * @date 2025-05-02
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
#include "rect.h"

namespace YanLib::ui::gdi {
    int32_t rect::fill(HDC dc_handle, const RECT *rect, HBRUSH brush_handle) {
        return FillRect(dc_handle, rect, brush_handle);
    }

    int32_t rect::frame(HDC dc_handle, const RECT *rect, HBRUSH brush_handle) {
        return FrameRect(dc_handle, rect, brush_handle);
    }

    bool rect::invert(HDC dc_handle, const RECT *rect) {
        return InvertRect(dc_handle, rect);
    }

    bool rect::set(RECT *rect,
                   int32_t left,
                   int32_t top,
                   int32_t right,
                   int32_t bottom) {
        return SetRect(rect, left, top, right, bottom);
    }

    bool rect::copy(RECT *rect_dst, const RECT *rect_src) {
        return CopyRect(rect_dst, rect_src);
    }

    bool rect::equal(const RECT *rect1, const RECT *rect2) {
        return EqualRect(rect1, rect2);
    }

    bool rect::inflate(RECT *rect, int32_t x, int32_t y) {
        return InflateRect(rect, x, y);
    }

    bool rect::intersect(RECT *rect_dst,
                         const RECT *rect_src1,
                         const RECT *rect_src2) {
        return IntersectRect(rect_dst, rect_src1, rect_src2);
    }

    bool rect::is_empty(const RECT *rect) {
        return IsRectEmpty(rect);
    }

    bool rect::offset(RECT *rect, int32_t x, int32_t y) {
        return OffsetRect(rect, x, y);
    }

    bool rect::contains_point(const RECT *rect, POINT point) {
        return PtInRect(rect, point);
    }

    bool rect::empty(RECT *rect) {
        return SetRectEmpty(rect);
    }

    bool rect::subtract(RECT *rect_dst,
                        const RECT *rect_src1,
                        const RECT *rect_src2) {
        return SubtractRect(rect_dst, rect_src1, rect_src2);
    }

    bool
    rect::unions(RECT *rect_dst, const RECT *rect_src1, const RECT *rect_src2) {
        return UnionRect(rect_dst, rect_src1, rect_src2);
    }

    bool rect::validate(HWND window_handle, const RECT *rect) {
        return ValidateRect(window_handle, rect);
    }

    bool rect::invalidate(HWND window_handle, const RECT *rect, bool is_erase) {
        return InvalidateRect(window_handle, rect, is_erase ? TRUE : FALSE);
    }

    bool rect::draw_animated(HWND window_handle,
                             const RECT *rect_from,
                             const RECT *rect_to,
                             AnimationType type) {
        return DrawAnimatedRects(window_handle, static_cast<int32_t>(type),
                                 rect_from, rect_to);
    }

    bool rect::draw_focus(HDC dc_handle, const RECT *rect) {
        return DrawFocusRect(dc_handle, rect);
    }

    BoundFlag rect::get_bounds(HDC dc_handle, RECT *rect, BoundFlag flag) {
        return static_cast<BoundFlag>(
                GetBoundsRect(dc_handle, rect, static_cast<uint32_t>(flag)));
    }

    BoundFlag
    rect::set_bounds(HDC dc_handle, const RECT *rect, BoundFlag flag) {
        return static_cast<BoundFlag>(
                SetBoundsRect(dc_handle, rect, static_cast<uint32_t>(flag)));
    }

    bool rect::get_update(HWND window_handle, RECT *rect, bool is_erase) {
        return GetUpdateRect(window_handle, rect, is_erase);
    }

    std::pair<bool, uint32_t> rect::get_client(HWND window_handle, RECT *rect) {
        uint32_t error_code = 0;
        if (!GetClientRect(window_handle, rect)) {
            error_code = GetLastError();
            return std::make_pair(false, error_code);
        }
        return std::make_pair(true, error_code);
    }
} // namespace YanLib::ui::gdi
