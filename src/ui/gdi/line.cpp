//
// Created by forkernel on 2025/5/4.
//

#include "line.h"

namespace YanLib::ui::gdi {
    bool line::to(HDC dc_handle, int32_t x, int32_t y) {
        return LineTo(dc_handle, x, y);
    }

    bool line::dda(int32_t x_start,
                   int32_t y_start,
                   int32_t x_end,
                   int32_t y_end,
                   LINEDDAPROC line_dda_proc,
                   LPARAM data) {
        return LineDDA(x_start, y_start, x_end, y_end, line_dda_proc, data);
    }

    bool line::move_to(HDC dc_handle, int32_t x, int32_t y, POINT *point) {
        return MoveToEx(dc_handle, x, y, point);
    }

    bool line::poly(HDC dc_handle, const std::vector<POINT> &point) {
        return Polyline(dc_handle, point.data(),
                        static_cast<int32_t>(point.size()));
    }

    bool line::poly_to(HDC dc_handle, const std::vector<POINT> &point) {
        return PolylineTo(dc_handle, point.data(),
                          static_cast<int32_t>(point.size()));
    }

    bool line::poly_poly(HDC dc_handle,
                         const std::vector<POINT> &point,
                         std::vector<uint32_t> &poly_count) {
        return PolyPolyline(dc_handle, point.data(),
                            reinterpret_cast<unsigned long *>(
                                    poly_count.data()),
                            poly_count.size());
    }

    bool line::poly_poly_safe(HDC dc_handle,
                              const std::vector<POINT> &point,
                              std::vector<uint32_t> &poly_count) {
        std::vector<unsigned long> temp(point.size());
        for (const auto &count : poly_count) {
            temp.push_back(count);
        }
        bool is_ok = PolyPolyline(dc_handle, point.data(), temp.data(),
                                  poly_count.size());
        poly_count.clear();
        for (const auto &count : temp) {
            poly_count.push_back(count);
        }
        return is_ok;
    }

    bool line::poly_draw(HDC dc_handle,
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
