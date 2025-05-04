//
// Created by forkernel on 2025/5/4.
//

#include "arc.h"

namespace YanLib::ui::gdi {
    bool arc::make_arc(HDC dc_handle,
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

    bool arc::arc_to(HDC dc_handle,
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

    bool arc::angle_arc(HDC dc_handle,
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

    int arc::get_arc_direction(HDC dc_handle) {
        return GetArcDirection(dc_handle);
    }

    int arc::set_arc_direction(HDC dc_handle, int direction) {
        return SetArcDirection(dc_handle, direction);
    }

    bool arc::poly_draw(HDC dc_handle,
                        const POINT *point,
                        const uint8_t *point_type,
                        int num) {
        return PolyDraw(dc_handle,
                        point,
                        point_type,
                        num);
    }
}
