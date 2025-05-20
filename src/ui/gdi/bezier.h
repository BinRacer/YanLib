//
// Created by forkernel on 2025/5/4.
//

#ifndef BEZIER_H
#define BEZIER_H
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
    class bezier {
    public:
        bezier(const bezier &other) = delete;

        bezier(bezier &&other) = delete;

        bezier &operator=(const bezier &other) = delete;

        bezier &operator=(bezier &&other) = delete;

        bezier() = default;

        ~bezier() = default;

        static bool poly(HDC dc_handle, const std::vector<POINT> &point);

        static bool poly_to(HDC dc_handle, const std::vector<POINT> &point);

        static bool poly_draw(HDC dc_handle,
                              const std::vector<POINT> &point,
                              const std::vector<PointType> &point_type);
    };
} // namespace YanLib::ui::gdi
#endif // BEZIER_H
