//
// Created by forkernel on 2025/5/3.
//

#include "brush.h"

namespace YanLib::ui::gdi {
    HBRUSH brush::create_solid_brush(COLORREF color) {
        return CreateSolidBrush(color);
    }

    HBRUSH brush::create_hatch_brush(int hatch, COLORREF color) {
        return CreateHatchBrush(hatch, color);
    }

    HBRUSH brush::create_pattern_brush(HBITMAP bitmap_handle) {
        return CreatePatternBrush(bitmap_handle);
    }

    HBRUSH brush::create_brush_indirect(const LOGBRUSH *log_brush) {
        return CreateBrushIndirect(log_brush);
    }

    HBRUSH brush::create_dib_pattern_brush_pt(const void *packed_dib, unsigned int usage) {
        return CreateDIBPatternBrushPt(packed_dib, usage);
    }

    bool brush::get_brush_org(HDC dc_handle, POINT *point) {
        return GetBrushOrgEx(dc_handle, point);
    }

    bool brush::set_brush_org(HDC dc_handle, int x, int y, POINT *point) {
        return SetBrushOrgEx(dc_handle, x, y, point);
    }

    HBRUSH brush::get_sys_color_brush(int index) {
        return GetSysColorBrush(index);
    }

    COLORREF brush::set_dc_brush_color(HDC dc_handle, COLORREF color) {
        return SetDCBrushColor(dc_handle, color);
    }

    DWORD brush::get_sys_color(int index) {
        return GetSysColor(index);
    }

    std::pair<bool, unsigned long> brush::set_sys_colors(
        int ele_num,
        const INT *ele_array,
        const COLORREF *rgb_values) {
        unsigned long error_code = 0;
        if (!SetSysColors(ele_num, ele_array, rgb_values)) {
            error_code = GetLastError();
            return std::make_pair(false, error_code);
        }
        return std::make_pair(true, error_code);
    }
}
