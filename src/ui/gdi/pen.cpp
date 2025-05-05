//
// Created by forkernel on 2025/5/4.
//

#include "pen.h"

namespace YanLib::ui::gdi {
    HPEN pen::create_pen(int style, int width, COLORREF color) {
        return CreatePen(style, width, color);
    }

    HPEN pen::create_pen_indirect(const LOGPEN *log_pen) {
        return CreatePenIndirect(log_pen);
    }

    HPEN pen::ext_create_pen(unsigned long pen_style,
                             unsigned long width,
                             const LOGBRUSH *log_brush,
                             unsigned long style_num,
                             const unsigned long *style_array) {
        return ExtCreatePen(pen_style,
                            width,
                            log_brush,
                            style_num,
                            style_array);
    }

    COLORREF pen::set_dc_pen_color(HDC dc_handle, COLORREF color) {
        return SetDCPenColor(dc_handle, color);
    }
}
