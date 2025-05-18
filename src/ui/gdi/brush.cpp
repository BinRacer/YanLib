//
// Created by forkernel on 2025/5/3.
//

#include "brush.h"

namespace YanLib::ui::gdi {
    HBRUSH brush::create_solid_brush(COLORREF color) {
        return CreateSolidBrush(color);
    }

    HBRUSH brush::create_hatch_brush(int32_t hatch, COLORREF color) {
        return CreateHatchBrush(hatch, color);
    }

    HBRUSH brush::create_pattern_brush(HBITMAP bitmap_handle) {
        return CreatePatternBrush(bitmap_handle);
    }

    HBRUSH brush::create_brush_indirect(const LOGBRUSH* log_brush) {
        return CreateBrushIndirect(log_brush);
    }

    HBRUSH brush::create_dib_pattern_brush_pt(const void* packed_dib,
                                              uint32_t usage) {
        return CreateDIBPatternBrushPt(packed_dib, usage);
    }

    bool brush::get_brush_org(HDC dc_handle, POINT* point) {
        return GetBrushOrgEx(dc_handle, point);
    }

    bool
    brush::set_brush_org(HDC dc_handle, int32_t x, int32_t y, POINT* point) {
        return SetBrushOrgEx(dc_handle, x, y, point);
    }

    HBRUSH brush::get_sys_color_brush(int32_t index) {
        return GetSysColorBrush(index);
    }

    COLORREF brush::set_dc_brush_color(HDC dc_handle, COLORREF color) {
        return SetDCBrushColor(dc_handle, color);
    }

    uint32_t brush::get_sys_color(int32_t index) {
        return GetSysColor(index);
    }

    std::pair<bool, uint32_t>
    brush::set_sys_colors(const std::vector<int32_t> &ele,
                          const std::vector<COLORREF> &rgb) {
        uint32_t error_code = 0;
        if (!SetSysColors(static_cast<int32_t>(ele.size()), ele.data(),
                          rgb.data())) {
            error_code = GetLastError();
            return std::make_pair(false, error_code);
        }
        return std::make_pair(true, error_code);
    }
} // namespace YanLib::ui::gdi
