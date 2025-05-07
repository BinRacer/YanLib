//
// Created by forkernel on 2025/5/4.
//

#include "pen.h"

namespace YanLib::ui::gdi {
HPEN pen::create_pen(int32_t style, int32_t width, COLORREF color) {
    return CreatePen(style, width, color);
}

HPEN pen::create_pen_indirect(const LOGPEN *log_pen) {
    return CreatePenIndirect(log_pen);
}

HPEN pen::ext_create_pen(uint32_t pen_style,
    uint32_t                      width,
    const LOGBRUSH               *log_brush,
    std::vector<uint32_t>        &style) {
    return ExtCreatePen(pen_style, width, log_brush, style.size(),
        reinterpret_cast<unsigned long *>(style.data()));
}

COLORREF pen::set_dc_pen_color(HDC dc_handle, COLORREF color) {
    return SetDCPenColor(dc_handle, color);
}
} // namespace YanLib::ui::gdi
