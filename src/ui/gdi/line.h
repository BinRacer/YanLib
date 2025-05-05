//
// Created by forkernel on 2025/5/4.
//

#ifndef LINE_H
#define LINE_H
#include <cstdint>
#include <Windows.h>

namespace YanLib::ui::gdi {
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

        static bool poly_line(HDC dc_handle, const POINT *point, unsigned long num);

        static bool poly_line_to(HDC dc_handle, const POINT *point, unsigned long num);

        static bool poly_poly_line(HDC dc_handle,
                                   const POINT *point,
                                   const unsigned long *num_array,
                                   unsigned long num);

        static bool poly_draw(HDC dc_handle,
                              const POINT *point,
                              const uint8_t *point_type,
                              int num);
    };
}
#endif //LINE_H
