//
// Created by forkernel on 2025/5/4.
//

#ifndef LINE_H
#define LINE_H
#include <cstdint>
#include <Windows.h>
#include <vector>

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

        static bool move_to(HDC dc_handle, int32_t x, int32_t y, POINT* point);

        static bool poly_line(HDC dc_handle, const std::vector<POINT> &point);

        static bool poly_line_to(HDC dc_handle,
                                 const std::vector<POINT> &point);

        static bool poly_poly_line(HDC dc_handle,
                                   const std::vector<POINT> &point,
                                   std::vector<uint32_t> &poly_count);

        static bool poly_draw(HDC dc_handle,
                              const std::vector<POINT> &point,
                              const std::vector<uint8_t> &point_type);
    };
} // namespace YanLib::ui::gdi
#endif // LINE_H
