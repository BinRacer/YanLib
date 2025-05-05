//
// Created by forkernel on 2025/5/4.
//

#include "arc.h"

namespace YanLib::ui::gdi {
    bool arc::make_arc(HDC dc_handle,
                       int32_t x1, int32_t y1,
                       int32_t x2, int32_t y2,
                       int32_t x3, int32_t y3,
                       int32_t x4, int32_t y4) {
        return Arc(dc_handle,
                   x1, y1,
                   x2, y2,
                   x3, y3,
                   x4, y4);
    }

    bool arc::arc_to(HDC dc_handle,
                     int32_t left, int32_t top,
                     int32_t right, int32_t bottom,
                     int32_t xr1, int32_t yr1,
                     int32_t xr2, int32_t yr2) {
        return ArcTo(dc_handle,
                     left, top,
                     right, bottom,
                     xr1, yr1,
                     xr2, yr2);
    }

    bool arc::angle_arc(HDC dc_handle,
                        int32_t x,
                        int32_t y,
                        unsigned long r,
                        FLOAT start_angle,
                        FLOAT sweep_angle) {
        return AngleArc(dc_handle,
                        x,
                        y,
                        r,
                        start_angle,
                        sweep_angle);
    }

    int32_t arc::get_arc_direction(HDC dc_handle) {
        return GetArcDirection(dc_handle);
    }

    int32_t arc::set_arc_direction(HDC dc_handle, int32_t direction) {
        return SetArcDirection(dc_handle, direction);
    }

    bool arc::poly_draw(HDC dc_handle,
                        const POINT *point,
                        const uint8_t *point_type,
                        int32_t num) {
        return PolyDraw(dc_handle,
                        point,
                        point_type,
                        num);
    }
}
