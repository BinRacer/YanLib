//
// Created by forkernel on 2025/5/2.
//

#include "rect.h"

namespace YanLib::ui::gdi {
int32_t rect::fill_rect(HDC dc_handle, const RECT *rect, HBRUSH brush_handle) {
    return FillRect(dc_handle, rect, brush_handle);
}

int32_t rect::frame_rect(HDC dc_handle, const RECT *rect, HBRUSH brush_handle) {
    return FrameRect(dc_handle, rect, brush_handle);
}

bool rect::invert_rect(HDC dc_handle, const RECT *rect) {
    return InvertRect(dc_handle, rect);
}

bool rect::set_rect(RECT *rect,
    int32_t               x_left,
    int32_t               y_top,
    int32_t               x_right,
    int32_t               y_bottom) {
    return SetRect(rect, x_left, y_top, x_right, y_bottom);
}

bool rect::copy_rect(RECT *rect_dst, const RECT *rect_src) {
    return CopyRect(rect_dst, rect_src);
}

bool rect::equal_rect(const RECT *rect1, const RECT *rect2) {
    return EqualRect(rect1, rect2);
}

bool rect::inflate_rect(RECT *rect, int32_t x, int32_t y) {
    return InflateRect(rect, x, y);
}

bool rect::intersect_rect(RECT *rect_dst,
    const RECT                 *rect_src1,
    const RECT                 *rect_src2) {
    return IntersectRect(rect_dst, rect_src1, rect_src2);
}

bool rect::is_rect_empty(const RECT *rect) {
    return IsRectEmpty(rect);
}

bool rect::offset_rect(RECT *rect, int32_t x, int32_t y) {
    return OffsetRect(rect, x, y);
}

bool rect::point_in_rect(const RECT *rect, POINT point) {
    return PtInRect(rect, point);
}

bool rect::set_rect_empty(RECT *rect) {
    return SetRectEmpty(rect);
}

bool rect::subtract_rect(RECT *rect_dst,
    const RECT                *rect_src1,
    const RECT                *rect_src2) {
    return SubtractRect(rect_dst, rect_src1, rect_src2);
}

bool rect::union_rect(RECT *rect_dst,
    const RECT             *rect_src1,
    const RECT             *rect_src2) {
    return UnionRect(rect_dst, rect_src1, rect_src2);
}

bool rect::validate_rect(HWND window_handle, const RECT *rect) {
    return ValidateRect(window_handle, rect);
}

bool rect::invalidate_rect(HWND window_handle,
    const RECT                 *rect,
    bool                        is_erase) {
    return InvalidateRect(window_handle, rect, is_erase ? TRUE : FALSE);
}

bool rect::draw_animated_rects(HWND window_handle,
    int32_t                         animate_id,
    const RECT                     *rect_from,
    const RECT                     *rect_to) {
    return DrawAnimatedRects(window_handle, animate_id, rect_from, rect_to);
}

bool rect::draw_focus_rect(HDC dc_handle, const RECT *rect) {
    return DrawFocusRect(dc_handle, rect);
}

uint32_t rect::get_bounds_rect(HDC dc_handle, RECT *rect, uint32_t flag) {
    return GetBoundsRect(dc_handle, rect, flag);
}

uint32_t rect::set_bounds_rect(HDC dc_handle, const RECT *rect, uint32_t flag) {
    return SetBoundsRect(dc_handle, rect, flag);
}

bool rect::get_update_rect(HWND window_handle, RECT *rect, bool is_erase) {
    return GetUpdateRect(window_handle, rect, is_erase);
}

std::pair<bool, uint32_t> rect::get_client_rect(HWND window_handle,
    RECT                                            *rect) {
    uint32_t error_code = 0;
    if (!GetClientRect(window_handle, rect)) {
        error_code = GetLastError();
        return std::make_pair(false, error_code);
    }
    return std::make_pair(true, error_code);
}
} // namespace YanLib::ui::gdi
