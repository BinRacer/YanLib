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

        static bool line_to(HDC dc_handle, int32_t x, int32_t y);

        static bool line_dda(int32_t x_start,
                             int32_t y_start,
                             int32_t x_end,
                             int32_t y_end,
                             LINEDDAPROC line_dda_proc,
                             LPARAM data);

        static bool move_to(HDC dc_handle, int32_t x, int32_t y, POINT *point);

        static bool poly_line(HDC dc_handle, const POINT *point, unsigned long num);

        static bool poly_line_to(HDC dc_handle, const POINT *point, unsigned long num);

        static bool poly_poly_line(HDC dc_handle,
                                   const POINT *point,
                                   const unsigned long *num_array,
                                   unsigned long num);

        static bool poly_draw(HDC dc_handle,
                              const POINT *point,
                              const uint8_t *point_type,
                              int32_t num);
    };
}
#endif //LINE_H
