//
// Created by forkernel on 2025/5/4.
//

#ifndef ARC_H
#define ARC_H
#include <cstdint>
#include <Windows.h>

namespace YanLib::ui::gdi {
    class arc {
    public:
        arc(const arc &other) = delete;

        arc(arc &&other) = delete;

        arc &operator=(const arc &other) = delete;

        arc &operator=(arc &&other) = delete;

        arc() = default;

        ~arc() = default;

        static bool make_arc(HDC dc_handle,
                             int32_t x1, int32_t y1,
                             int32_t x2, int32_t y2,
                             int32_t x3, int32_t y3,
                             int32_t x4, int32_t y4);

        static bool arc_to(HDC dc_handle,
                           int32_t left, int32_t top,
                           int32_t right, int32_t bottom,
                           int32_t xr1, int32_t yr1,
                           int32_t xr2, int32_t yr2);

        static bool angle_arc(HDC dc_handle,
                              int32_t x,
                              int32_t y,
                              unsigned long r,
                              FLOAT start_angle,
                              FLOAT sweep_angle);

        static int32_t get_arc_direction(HDC dc_handle);

        static int32_t set_arc_direction(HDC dc_handle, int32_t direction);

        static bool poly_draw(HDC dc_handle,
                              const POINT *point,
                              const uint8_t *point_type,
                              int32_t num);
    };
}
#endif //ARC_H
