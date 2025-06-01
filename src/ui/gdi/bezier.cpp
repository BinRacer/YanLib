//
// Created by forkernel on 2025/5/4.
//

#include "bezier.h"

namespace YanLib::ui::gdi {
    bool bezier::poly(HDC dc_handle, const std::vector<POINT> &point) {
        return PolyBezier(dc_handle, point.data(), point.size());
    }

    bool bezier::poly_to(HDC dc_handle, const std::vector<POINT> &point) {
        return PolyBezierTo(dc_handle, point.data(), point.size());
    }

    bool bezier::poly_draw(HDC dc_handle,
                           const std::vector<POINT> &point,
                           const std::vector<PointType> &point_type) {
        if (point.size() != point_type.size()) {
            return false;
        }
        return PolyDraw(dc_handle, point.data(),
                        reinterpret_cast<const uint8_t *>(point_type.data()),
                        static_cast<int32_t>(point.size()));
    }
} // namespace YanLib::ui::gdi
