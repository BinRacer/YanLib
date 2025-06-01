//
// Created by forkernel on 2025/5/4.
//

#ifndef LINE_H
#define LINE_H
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
    class line {
    public:
        line(const line &other) = delete;

        line(line &&other) = delete;

        line &operator=(const line &other) = delete;

        line &operator=(line &&other) = delete;

        line() = default;

        ~line() = default;

        static bool to(HDC dc_handle, int32_t x, int32_t y);

        static bool dda(int32_t x_start,
                        int32_t y_start,
                        int32_t x_end,
                        int32_t y_end,
                        LINEDDAPROC line_dda_proc,
                        LPARAM data);

        static bool move_to(HDC dc_handle, int32_t x, int32_t y, POINT *point);

        static bool poly(HDC dc_handle, const std::vector<POINT> &point);

        static bool poly_to(HDC dc_handle, const std::vector<POINT> &point);

        static bool poly_poly(HDC dc_handle,
                              const std::vector<POINT> &point,
                              std::vector<uint32_t> &poly_count);

        static bool poly_poly_safe(HDC dc_handle,
                                   const std::vector<POINT> &point,
                                   std::vector<uint32_t> &poly_count);

        static bool poly_draw(HDC dc_handle,
                              const std::vector<POINT> &point,
                              const std::vector<PointType> &point_type);
    };
} // namespace YanLib::ui::gdi
#endif // LINE_H
