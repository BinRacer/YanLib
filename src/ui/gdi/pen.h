//
// Created by forkernel on 2025/5/4.
//

#ifndef PEN_H
#define PEN_H
#include <Windows.h>

namespace YanLib::ui::gdi {
    class pen {
    public:
        pen(const pen &other) = delete;

        pen(pen &&other) = delete;

        pen &operator=(const pen &other) = delete;

        pen &operator=(pen &&other) = delete;

        pen() = default;

        ~pen() = default;

        static HPEN create_pen(int style, int width, COLORREF color);

        static HPEN create_pen_indirect(const LOGPEN *log_pen);

        static HPEN ext_create_pen(DWORD pen_style,
                                   DWORD width,
                                   const LOGBRUSH *log_brush,
                                   DWORD style_num,
                                   const DWORD *style_array);

        static COLORREF set_dc_pen_color(HDC dc_handle, COLORREF color);
    };
}
#endif //PEN_H
