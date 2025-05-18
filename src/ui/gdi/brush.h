//
// Created by forkernel on 2025/5/3.
//

#ifndef BRUSH_H
#define BRUSH_H
#include <utility>
#include <Windows.h>
#include <vector>

namespace YanLib::ui::gdi {
    class brush {
    public:
        brush(const brush &other) = delete;

        brush(brush &&other) = delete;

        brush &operator=(const brush &other) = delete;

        brush &operator=(brush &&other) = delete;

        brush() = default;

        ~brush() = default;

        static HBRUSH create_solid_brush(COLORREF color);

        static HBRUSH create_hatch_brush(int32_t hatch, COLORREF color);

        static HBRUSH create_pattern_brush(HBITMAP bitmap_handle);

        static HBRUSH create_brush_indirect(const LOGBRUSH* log_brush);

        static HBRUSH create_dib_pattern_brush_pt(const void* packed_dib,
                                                  uint32_t usage);

        static bool get_brush_org(HDC dc_handle, POINT* point);

        static bool
        set_brush_org(HDC dc_handle, int32_t x, int32_t y, POINT* point);

        static HBRUSH get_sys_color_brush(int32_t index);

        static COLORREF set_dc_brush_color(HDC dc_handle, COLORREF color);

        static uint32_t get_sys_color(int32_t index);

        // std::pair<result, error_code>
        static std::pair<bool, uint32_t>
        set_sys_colors(const std::vector<int32_t> &ele,
                       const std::vector<COLORREF> &rgb);
    };
} // namespace YanLib::ui::gdi
#endif // BRUSH_H
