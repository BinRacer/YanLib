//
// Created by forkernel on 2025/5/4.
//

#ifndef SHAPE_H
#define SHAPE_H
#include <Windows.h>
#include <cstdint>
#include <vector>

namespace YanLib::ui::gdi {
class shape {
public:
    shape(const shape &other)            = delete;

    shape(shape &&other)                 = delete;

    shape &operator=(const shape &other) = delete;

    shape &operator=(shape &&other)      = delete;

    shape()                              = default;

    ~shape()                             = default;

    static bool rectangle(HDC dc_handle,
        int32_t               left,
        int32_t               top,
        int32_t               right,
        int32_t               bottom);

    static int32_t
    fill_rect(HDC dc_handle, const RECT *rect, HBRUSH brush_handle);

    static bool round_rect(HDC dc_handle,
        int32_t                left,
        int32_t                top,
        int32_t                right,
        int32_t                bottom,
        int32_t                width,
        int32_t                height);

    static int32_t
    frame_rect(HDC dc_handle, const RECT *rect, HBRUSH brush_handle);

    static bool invert_rect(HDC dc_handle, const RECT *rect);

    static bool ellipse(HDC dc_handle,
        int32_t             left,
        int32_t             top,
        int32_t             right,
        int32_t             bottom);

    static bool chord(HDC dc_handle,
        int32_t           x1,
        int32_t           y1,
        int32_t           x2,
        int32_t           y2,
        int32_t           x3,
        int32_t           y3,
        int32_t           x4,
        int32_t           y4);

    static bool poly_gon(HDC dc_handle, const std::vector<POINT> &point);

    static bool poly_poly_gon(HDC   dc_handle,
        const std::vector<POINT>   &point,
        const std::vector<int32_t> &poly_count);

    static bool pie(HDC dc_handle,
        int32_t         left,
        int32_t         top,
        int32_t         right,
        int32_t         bottom,
        int32_t         xr1,
        int32_t         yr1,
        int32_t         xr2,
        int32_t         yr2);
};
} // namespace YanLib::ui::gdi
#endif // SHAPE_H
