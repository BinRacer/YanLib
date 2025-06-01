//
// Created by forkernel on 2025/5/4.
//

#ifndef ARC_H
#define ARC_H
#include <cstdint>
#include <Windows.h>
#include <vector>

namespace YanLib::ui::gdi {
#ifndef POINTTYPE
#define POINTTYPE

    enum class PointType : uint8_t {
        CloseFigure = PT_CLOSEFIGURE,
        LineTo = PT_LINETO,
        BezierTo = PT_BEZIERTO,
        MoveTo = PT_MOVETO,
    };

    inline PointType operator|(PointType a, PointType b) {
        return static_cast<PointType>(static_cast<uint8_t>(a) |
                                      static_cast<uint8_t>(b));
    }
#endif
    class arc {
    public:
        arc(const arc &other) = delete;

        arc(arc &&other) = delete;

        arc &operator=(const arc &other) = delete;

        arc &operator=(arc &&other) = delete;

        arc() = default;

        ~arc() = default;

        static bool make(HDC dc_handle,
                         int32_t rect_left,
                         int32_t rect_top,
                         int32_t rect_right,
                         int32_t rect_bottom,
                         int32_t start_arc_x,
                         int32_t start_arc_y,
                         int32_t end_arc_x,
                         int32_t end_arc_y);

        static bool to(HDC dc_handle,
                       int32_t rect_left,
                       int32_t rect_top,
                       int32_t rect_right,
                       int32_t rect_bottom,
                       int32_t radial_x1,
                       int32_t radial_y1,
                       int32_t radial_x2,
                       int32_t radial_y2);

        static bool angle(HDC dc_handle,
                          int32_t x,
                          int32_t y,
                          uint32_t r,
                          FLOAT start_angle,
                          FLOAT sweep_angle);

        static int32_t get_direction(HDC dc_handle);

        static int32_t set_direction(HDC dc_handle, bool clock_wise = true);

        static bool poly_draw(HDC dc_handle,
                              const std::vector<POINT> &point,
                              const std::vector<PointType> &point_type);
    };
} // namespace YanLib::ui::gdi
#endif // ARC_H
