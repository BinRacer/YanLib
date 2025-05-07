//
// Created by forkernel on 2025/5/4.
//

#ifndef BEZIER_H
#define BEZIER_H
#include <cstdint>
#include <Windows.h>
#include <vector>

namespace YanLib::ui::gdi {
class bezier {
public:
    bezier(const bezier &other)            = delete;

    bezier(bezier &&other)                 = delete;

    bezier &operator=(const bezier &other) = delete;

    bezier &operator=(bezier &&other)      = delete;

    bezier()                               = default;

    ~bezier()                              = default;

    static bool poly_bezier(HDC dc_handle, const std::vector<POINT> &point);

    static bool poly_bezier_to(HDC dc_handle, const std::vector<POINT> &point);

    static bool poly_draw(HDC       dc_handle,
        const std::vector<POINT>   &point,
        const std::vector<uint8_t> &point_type);
};
} // namespace YanLib::ui::gdi
#endif // BEZIER_H
