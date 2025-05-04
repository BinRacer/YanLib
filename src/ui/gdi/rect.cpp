//
// Created by forkernel on 2025/5/2.
//

#include "rect.h"

namespace YanLib::ui::gdi {
    int rect::fill_rect(HDC dc_handle, const RECT *rect, HBRUSH brush_handle) {
        return FillRect(dc_handle, rect, brush_handle);
    }

    int rect::frame_rect(HDC dc_handle, const RECT *rect, HBRUSH brush_handle) {
        return FrameRect(dc_handle, rect, brush_handle);
    }

    bool rect::invert_rect(HDC dc_handle, const RECT *rect) {
        return InvertRect(dc_handle, rect);
    }

    bool rect::set_rect(RECT *rect,
                        int x_left,
                        int y_top,
                        int x_right,
                        int y_bottom) {
        return SetRect(rect, x_left, y_top, x_right, y_bottom);
    }

    bool rect::copy_rect(RECT *rect_dst, const RECT *rect_src) {
        return CopyRect(rect_dst, rect_src);
    }

    bool rect::equal_rect(const RECT *rect1, const RECT *rect2) {
        return EqualRect(rect1, rect2);
    }

    bool rect::inflate_rect(RECT *rect, int x, int y) {
        return InflateRect(rect, x, y);
    }

    bool rect::intersect_rect(RECT *rect_dst,
                              const RECT *rect_src1,
                              const RECT *rect_src2) {
        return IntersectRect(rect_dst, rect_src1, rect_src2);
    }

    bool rect::is_rect_empty(const RECT *rect) {
        return IsRectEmpty(rect);
    }

    bool rect::offset_rect(RECT *rect, int x, int y) {
        return OffsetRect(rect, x, y);
    }

    bool rect::point_in_rect(const RECT *rect, POINT point) {
        return PtInRect(rect, point);
    }

    bool rect::set_rect_empty(RECT *rect) {
        return SetRectEmpty(rect);
    }

    bool rect::subtract_rect(RECT *rect_dst,
                             const RECT *rect_src1,
                             const RECT *rect_src2) {
        return SubtractRect(rect_dst, rect_src1, rect_src2);
    }

    bool rect::union_rect(RECT *rect_dst,
                          const RECT *rect_src1,
                          const RECT *rect_src2) {
        return UnionRect(rect_dst, rect_src1, rect_src2);
    }

    bool rect::validate_rect(HWND hwnd, const RECT *rect) {
        return ValidateRect(hwnd, rect);
    }

    bool rect::invalidate_rect(HWND hwnd, const RECT *rect, bool is_erase) {
        return InvalidateRect(hwnd, rect, is_erase ? TRUE : FALSE);
    }

    bool rect::draw_animated_rects(HWND hwnd,
                                   int animate_id,
                                   const RECT *rect_from,
                                   const RECT *rect_to) {
        return DrawAnimatedRects(hwnd, animate_id, rect_from, rect_to);
    }

    bool rect::get_update_rect(HWND hwnd, RECT *rect, bool is_erase) {
        return GetUpdateRect(hwnd, rect, is_erase);
    }
}
