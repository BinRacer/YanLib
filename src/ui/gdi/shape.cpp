//
// Created by forkernel on 2025/5/4.
//

#include "shape.h"

namespace YanLib::ui::gdi {
    bool shape::rectangle(HDC dc_handle, int left, int top, int right, int bottom) {
        return Rectangle(dc_handle, left, top, right, bottom);
    }

    int shape::fill_rect(HDC dc_handle, const RECT *rect, HBRUSH brush_handle) {
        return FillRect(dc_handle, rect, brush_handle);
    }

    bool shape::round_rect(HDC dc_handle,
                           int left, int top,
                           int right, int bottom,
                           int width, int height) {
        return RoundRect(dc_handle, left, top, right, bottom, width, height);
    }

    int shape::frame_rect(HDC dc_handle, const RECT *rect, HBRUSH brush_handle) {
        return FrameRect(dc_handle, rect, brush_handle);
    }

    bool shape::invert_rect(HDC dc_handle, const RECT *rect) {
        return InvertRect(dc_handle, rect);
    }

    bool shape::ellipse(HDC dc_handle, int left, int top, int right, int bottom) {
        return Ellipse(dc_handle, left, top, right, bottom);
    }

    bool shape::chord(HDC dc_handle,
                      int x1, int y1,
                      int x2, int y2,
                      int x3, int y3,
                      int x4, int y4) {
        return Chord(dc_handle,
                     x1, y1,
                     x2, y2,
                     x3, y3,
                     x4, y4);
    }

    bool shape::poly_gon(HDC dc_handle, const POINT *point, int num) {
        return Polygon(dc_handle, point, num);
    }

    bool shape::poly_poly_gon(HDC dc_handle,
                              const POINT *point,
                              const INT *num_array,
                              int num) {
        return PolyPolygon(dc_handle, point, num_array, num);
    }

    bool shape::pie(HDC dc_handle,
                    int left, int top,
                    int right, int bottom,
                    int xr1, int yr1,
                    int xr2, int yr2) {
        return Pie(dc_handle,
                   left, top,
                   right, bottom,
                   xr1, yr1,
                   xr2, yr2);
    }
}
