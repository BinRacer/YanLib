//
// Created by forkernel on 2025/5/4.
//

#include "shape.h"

namespace YanLib::ui::gdi {
    bool shape::rectangle(HDC dc_handle, int32_t left, int32_t top, int32_t right, int32_t bottom) {
        return Rectangle(dc_handle, left, top, right, bottom);
    }

    int32_t shape::fill_rect(HDC dc_handle, const RECT *rect, HBRUSH brush_handle) {
        return FillRect(dc_handle, rect, brush_handle);
    }

    bool shape::round_rect(HDC dc_handle,
                           int32_t left, int32_t top,
                           int32_t right, int32_t bottom,
                           int32_t width, int32_t height) {
        return RoundRect(dc_handle, left, top, right, bottom, width, height);
    }

    int32_t shape::frame_rect(HDC dc_handle, const RECT *rect, HBRUSH brush_handle) {
        return FrameRect(dc_handle, rect, brush_handle);
    }

    bool shape::invert_rect(HDC dc_handle, const RECT *rect) {
        return InvertRect(dc_handle, rect);
    }

    bool shape::ellipse(HDC dc_handle, int32_t left, int32_t top, int32_t right, int32_t bottom) {
        return Ellipse(dc_handle, left, top, right, bottom);
    }

    bool shape::chord(HDC dc_handle,
                      int32_t x1, int32_t y1,
                      int32_t x2, int32_t y2,
                      int32_t x3, int32_t y3,
                      int32_t x4, int32_t y4) {
        return Chord(dc_handle,
                     x1, y1,
                     x2, y2,
                     x3, y3,
                     x4, y4);
    }

    bool shape::poly_gon(HDC dc_handle, const POINT *point, int32_t num) {
        return Polygon(dc_handle, point, num);
    }

    bool shape::poly_poly_gon(HDC dc_handle,
                              const POINT *point,
                              const int32_t *num_array,
                              int32_t num) {
        return PolyPolygon(dc_handle, point, num_array, num);
    }

    bool shape::pie(HDC dc_handle,
                    int32_t left, int32_t top,
                    int32_t right, int32_t bottom,
                    int32_t xr1, int32_t yr1,
                    int32_t xr2, int32_t yr2) {
        return Pie(dc_handle,
                   left, top,
                   right, bottom,
                   xr1, yr1,
                   xr2, yr2);
    }
}
