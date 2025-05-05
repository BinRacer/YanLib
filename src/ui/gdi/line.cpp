//
// Created by forkernel on 2025/5/4.
//

#include "line.h"

namespace YanLib::ui::gdi {
    bool line::line_to(HDC dc_handle, int32_t x, int32_t y) {
        return LineTo(dc_handle, x, y);
    }

    bool line::line_dda(int32_t x_start,
                        int32_t y_start,
                        int32_t x_end,
                        int32_t y_end,
                        LINEDDAPROC line_dda_proc,
                        LPARAM data) {
        return LineDDA(x_start,
                       y_start,
                       x_end,
                       y_end,
                       line_dda_proc,
                       data);
    }

    bool line::move_to(HDC dc_handle, int32_t x, int32_t y, POINT *point) {
        return MoveToEx(dc_handle, x, y, point);
    }

    bool line::poly_line(HDC dc_handle, const POINT *point, unsigned long num) {
        return Polyline(dc_handle, point, num);
    }

    bool line::poly_line_to(HDC dc_handle, const POINT *point, unsigned long num) {
        return PolylineTo(dc_handle, point, num);
    }

    bool line::poly_poly_line(HDC dc_handle,
                              const POINT *point,
                              const unsigned long *num_array,
                              unsigned long num) {
        return PolyPolyline(dc_handle,
                            point,
                            num_array,
                            num);
    }

    bool line::poly_draw(HDC dc_handle,
                         const POINT *point,
                         const uint8_t *point_type,
                         int32_t num) {
        return PolyDraw(dc_handle,
                        point,
                        point_type,
                        num);
    }
}
