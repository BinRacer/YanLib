//
// Created by forkernel on 2025/5/4.
//

#include "line.h"

namespace YanLib::ui::gdi {
    bool line::line_to(HDC dc_handle, int x, int y) {
        return LineTo(dc_handle, x, y);
    }

    bool line::line_dda(int x_start,
                        int y_start,
                        int x_end,
                        int y_end,
                        LINEDDAPROC line_dda_proc,
                        LPARAM data) {
        return LineDDA(x_start,
                       y_start,
                       x_end,
                       y_end,
                       line_dda_proc,
                       data);
    }

    bool line::move_to(HDC dc_handle, int x, int y, POINT *point) {
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
                         int num) {
        return PolyDraw(dc_handle,
                        point,
                        point_type,
                        num);
    }
}
