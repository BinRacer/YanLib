/* clang-format off */
/*
 * @file rect.h
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
#ifndef RECT_H
#define RECT_H
#include <utility>
#include <Windows.h>

namespace YanLib::ui::gdi {
#ifndef ANIMATIONTYPE
#define ANIMATIONTYPE

    enum class AnimationType : int32_t {
        Open = IDANI_OPEN,
        Caption = IDANI_CAPTION,
    };
#endif
#ifndef BOUNDFLAG
#define BOUNDFLAG

    enum class BoundFlag : uint32_t {
        Error = 0,
        Reset = DCB_RESET,
        Accumulate = DCB_ACCUMULATE,
        Dirty = DCB_DIRTY,
        Set = DCB_SET,
        Enable = DCB_ENABLE,
        Disable = DCB_DISABLE,
    };
#endif
    class rect {
    public:
        rect(const rect &other) = delete;

        rect(rect &&other) = delete;

        rect &operator=(const rect &other) = delete;

        rect &operator=(rect &&other) = delete;

        rect() = default;

        ~rect() = default;

        static int32_t
        fill(HDC dc_handle, const RECT *rect, HBRUSH brush_handle);

        static int32_t
        frame(HDC dc_handle, const RECT *rect, HBRUSH brush_handle);

        static bool invert(HDC dc_handle, const RECT *rect);

        static bool set(RECT *rect,
                        int32_t left,
                        int32_t top,
                        int32_t right,
                        int32_t bottom);

        static bool copy(RECT *rect_dst, const RECT *rect_src);

        static bool equal(const RECT *rect1, const RECT *rect2);

        static bool inflate(RECT *rect, int32_t x, int32_t y);

        static bool
        intersect(RECT *rect_dst, const RECT *rect_src1, const RECT *rect_src2);

        static bool is_empty(const RECT *rect);

        static bool offset(RECT *rect, int32_t x, int32_t y);

        static bool contains_point(const RECT *rect, POINT point);

        static bool empty(RECT *rect);

        static bool
        subtract(RECT *rect_dst, const RECT *rect_src1, const RECT *rect_src2);

        static bool
        unions(RECT *rect_dst, const RECT *rect_src1, const RECT *rect_src2);

        static bool validate(HWND window_handle, const RECT *rect);

        static bool
        invalidate(HWND window_handle, const RECT *rect, bool is_erase = true);

        static bool draw_animated(HWND window_handle,
                                  const RECT *rect_from,
                                  const RECT *rect_to,
                                  AnimationType type = AnimationType::Caption);

        static bool draw_focus(HDC dc_handle, const RECT *rect);

        static BoundFlag get_bounds(HDC dc_handle, RECT *rect, BoundFlag flag);

        static BoundFlag
        set_bounds(HDC dc_handle, const RECT *rect, BoundFlag flag);

        static bool
        get_update(HWND window_handle, RECT *rect, bool is_erase = true);

        // std::pair<result, error_code>
        static std::pair<bool, uint32_t> get_client(HWND window_handle,
                                                    RECT *rect);
    };
} // namespace YanLib::ui::gdi
#endif // RECT_H
