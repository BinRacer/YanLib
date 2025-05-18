//
// Created by forkernel on 2025/5/4.
//

#ifndef PEN_H
#define PEN_H
#include <Windows.h>
#include <cstdint>
#include <vector>

namespace YanLib::ui::gdi {
    class pen {
    public:
        pen(const pen &other) = delete;

        pen(pen &&other) = delete;

        pen &operator=(const pen &other) = delete;

        pen &operator=(pen &&other) = delete;

        pen() = default;

        ~pen() = default;

        static HPEN create_pen(int32_t style, int32_t width, COLORREF color);

        static HPEN create_pen_indirect(const LOGPEN* log_pen);

        static HPEN ext_create_pen(uint32_t pen_style,
                                   uint32_t width,
                                   const LOGBRUSH* log_brush,
                                   std::vector<uint32_t> &style);

        static COLORREF set_dc_pen_color(HDC dc_handle, COLORREF color);
    };
} // namespace YanLib::ui::gdi
#endif // PEN_H
