//
// Created by forkernel on 2025/5/3.
//

#ifndef BRUSH_H
#define BRUSH_H
#include <Windows.h>

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

        static HBRUSH create_hatch_brush(int hatch, COLORREF color);

        static HBRUSH create_pattern_brush(HBITMAP bitmap_handle);

        static HBRUSH create_brush_indirect(const LOGBRUSH *log_brush);

        static HBRUSH create_dib_pattern_brush_pt(const void *packed_dib, UINT usage);

        static bool get_brush_org(HDC dc_handle, POINT *point);

        static bool set_brush_org(HDC dc_handle, int x, int y, POINT *point);

        static HBRUSH get_sys_color_brush(int index);

        static COLORREF set_dc_brush_color(HDC dc_handle, COLORREF color);
    };
}
#endif //BRUSH_H
