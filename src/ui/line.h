//
// Created by forkernel on 2025/5/4.
//

#ifndef LINE_H
#define LINE_H
#include <cstdint>
#include <Windows.h>

namespace YanLib::ui {
    class line {
    public:
        line(const line &other) = delete;

        line(line &&other) = delete;

        line &operator=(const line &other) = delete;

        line &operator=(line &&other) = delete;

        line() = default;

        ~line() = default;

        static bool line_to(HDC dc_handle, int x, int y);

        static bool line_dda(int x_start,
                             int y_start,
                             int x_end,
                             int y_end,
                             LINEDDAPROC line_dda_proc,
                             LPARAM data);

        static bool move_to(HDC dc_handle, int x, int y, POINT *point);

        static bool arc(HDC dc_handle,
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
                              DWORD r,
                              FLOAT start_angle,
                              FLOAT sweep_angle);

        static int get_arc_direction(HDC dc_handle);

        static int set_arc_direction(HDC dc_handle, int direction);

        static bool poly_bezier(HDC dc_handle, const POINT *point, DWORD num);

        static bool poly_bezier_to(HDC dc_handle, const POINT *point, DWORD num);

        static bool poly_line(HDC dc_handle, const POINT *point, DWORD num);

        static bool poly_line_to(HDC dc_handle, const POINT *point, DWORD num);

        static bool poly_poly_line(HDC dc_handle,
                                   const POINT *point,
                                   const DWORD *num_array,
                                   DWORD num);

        static bool poly_draw(HDC dc_handle,
                              const POINT *point,
                              const uint8_t *point_type,
                              int num);
    };
}
#endif //LINE_H
