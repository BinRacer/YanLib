//
// Created by BinRacer <native.lab@outlook.com> on 2025/5/4.
//

#ifndef SHAPE_H
#define SHAPE_H
#include <Windows.h>
#include <cstdint>
#include <vector>

namespace YanLib::ui::gdi {
    class shape {
    public:
        shape(const shape &other) = delete;

        shape(shape &&other) = delete;

        shape &operator=(const shape &other) = delete;

        shape &operator=(shape &&other) = delete;

        shape() = default;

        ~shape() = default;

        static bool rectangle(HDC dc_handle,
                              int32_t left,
                              int32_t top,
                              int32_t right,
                              int32_t bottom);

        static int32_t
        fill_rect(HDC dc_handle, const RECT *rect, HBRUSH brush_handle);

        static bool round_rect(HDC dc_handle,
                               int32_t left,
                               int32_t top,
                               int32_t right,
                               int32_t bottom,
                               int32_t width,
                               int32_t height);

        static int32_t
        frame_rect(HDC dc_handle, const RECT *rect, HBRUSH brush_handle);

        static bool invert_rect(HDC dc_handle, const RECT *rect);

        static bool ellipse(HDC dc_handle,
                            int32_t left,
                            int32_t top,
                            int32_t right,
                            int32_t bottom);

        static bool chord(HDC dc_handle,
                          int32_t rect_left,
                          int32_t rect_top,
                          int32_t rect_right,
                          int32_t rect_bottom,
                          int32_t start_radial_x,
                          int32_t start_radial_y,
                          int32_t end_radial_x,
                          int32_t end_radial_y);

        static bool poly_gon(HDC dc_handle, const std::vector<POINT> &point);

        static bool poly_poly_gon(HDC dc_handle,
                                  const std::vector<POINT> &point,
                                  const std::vector<int32_t> &poly_count);

        static bool pie(HDC dc_handle,
                        int32_t left,
                        int32_t top,
                        int32_t right,
                        int32_t bottom,
                        int32_t start_radial_x,
                        int32_t start_radial_y,
                        int32_t end_radial_x,
                        int32_t end_radial_y);
    };
} // namespace YanLib::ui::gdi
#endif // SHAPE_H
