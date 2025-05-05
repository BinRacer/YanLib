//
// Created by forkernel on 2025/5/4.
//

#include "bezier.h"

namespace YanLib::ui::gdi {
    bool bezier::poly_bezier(HDC dc_handle, const POINT *point, unsigned long num) {
        return PolyBezier(dc_handle, point, num);
    }

    bool bezier::poly_bezier_to(HDC dc_handle, const POINT *point, unsigned long num) {
        return PolyBezierTo(dc_handle, point, num);
    }

    bool bezier::poly_draw(HDC dc_handle,
                           const POINT *point,
                           const uint8_t *point_type,
                           int num) {
        return PolyDraw(dc_handle,
                        point,
                        point_type,
                        num);
    }
}
