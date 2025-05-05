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
                             int x1, int y1,
                             int x2, int y2,
                             int x3, int y3,
                             int x4, int y4);

        static bool arc_to(HDC dc_handle,
                           int left, int top,
                           int right, int bottom,
                           int xr1, int yr1,
                           int xr2, int yr2);

        static bool angle_arc(HDC dc_handle,
                              int x,
                              int y,
                              unsigned long r,
                              FLOAT start_angle,
                              FLOAT sweep_angle);

        static int get_arc_direction(HDC dc_handle);

        static int set_arc_direction(HDC dc_handle, int direction);

        static bool poly_draw(HDC dc_handle,
                              const POINT *point,
                              const uint8_t *point_type,
                              int num);
    };
}
#endif //ARC_H
