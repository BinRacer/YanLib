//
// Created by BinRacer <native.lab@outlook.com> on 2025/5/4.
//

#ifndef PATH_H
#define PATH_H
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
    class path {
    public:
        path(const path &other) = delete;

        path(path &&other) = delete;

        path &operator=(const path &other) = delete;

        path &operator=(path &&other) = delete;

        path() = default;

        ~path() = default;

        static bool begin(HDC dc_handle);

        static bool end(HDC dc_handle);

        static int32_t get(HDC dc_handle,
                           std::vector<POINT> &point,
                           std::vector<PointType> &point_type);

        static bool fill(HDC dc_handle);

        static bool abort(HDC dc_handle);

        static bool flatten(HDC dc_handle);

        static bool stroke_and_fill(HDC dc_handle);

        static bool stroke(HDC dc_handle);

        static bool widen(HDC dc_handle);

        static HRGN get_region(HDC dc_handle);

        static bool close_figure(HDC dc_handle);

        static bool get_miter_limit(HDC dc_handle, FLOAT *limit);

        static bool set_miter_limit(HDC dc_handle, FLOAT limit, FLOAT *old);
    };
} // namespace YanLib::ui::gdi
#endif // PATH_H
