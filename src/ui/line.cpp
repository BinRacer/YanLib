//
// Created by forkernel on 2025/5/4.
//

#include "line.h"

namespace YanLib::ui {
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

    bool line::arc(HDC dc_handle,
                   int x1, int y1,
                   int x2, int y2,
                   int x3, int y3,
                   int x4, int y4) {
        return Arc(dc_handle,
                   x1, y1,
                   x2, y2,
                   x3, y3,
                   x4, y4);
    }

    bool line::arc_to(HDC dc_handle,
                      int left, int top,
                      int right, int bottom,
                      int xr1, int yr1,
                      int xr2, int yr2) {
        return ArcTo(dc_handle,
                     left, top,
                     right, bottom,
                     xr1, yr1,
                     xr2, yr2);
    }

    bool line::angle_arc(HDC dc_handle,
                         int x,
                         int y,
                         DWORD r,
                         FLOAT start_angle,
                         FLOAT sweep_angle) {
        return AngleArc(dc_handle,
                        x,
                        y,
                        r,
                        start_angle,
                        sweep_angle);
    }

    int line::get_arc_direction(HDC dc_handle) {
        return GetArcDirection(dc_handle);
    }

    int line::set_arc_direction(HDC dc_handle, int direction) {
        return SetArcDirection(dc_handle, direction);
    }

    bool line::poly_bezier(HDC dc_handle, const POINT *point, DWORD num) {
        return PolyBezier(dc_handle, point, num);
    }

    bool line::poly_bezier_to(HDC dc_handle, const POINT *point, DWORD num) {
        return PolyBezierTo(dc_handle, point, num);
    }

    bool line::poly_line(HDC dc_handle, const POINT *point, DWORD num) {
        return Polyline(dc_handle, point, num);
    }

    bool line::poly_line_to(HDC dc_handle, const POINT *point, DWORD num) {
        return PolylineTo(dc_handle, point, num);
    }

    bool line::poly_poly_line(HDC dc_handle,
                              const POINT *point,
                              const DWORD *num_array,
                              DWORD num) {
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
