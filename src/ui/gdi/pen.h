//
// Created by BinRacer <native.lab@outlook.com> on 2025/5/4.
//

#ifndef PEN_H
#define PEN_H
#include <Windows.h>
#include <cstdint>
#include <vector>

namespace YanLib::ui::gdi {
#ifndef PENSTYLE
#define PENSTYLE

    enum class PenStyle : uint32_t {
        Solid = PS_SOLID,
        Dash = PS_DASH,             // -------
        Dot = PS_DOT,               // .......
        DashDot = PS_DASHDOT,       // _._._._
        DashDotDot = PS_DASHDOTDOT, // _.._.._
        Null = PS_NULL,
        InsideFrame = PS_INSIDEFRAME,
        UserStyle = PS_USERSTYLE,
        Alternate = PS_ALTERNATE,
        StyleMask = PS_STYLE_MASK,
        EndCapRound = PS_ENDCAP_ROUND,
        EndCapSquare = PS_ENDCAP_SQUARE,
        EndCapFlat = PS_ENDCAP_FLAT,
        EndCapMask = PS_ENDCAP_MASK,
        JoinRound = PS_JOIN_ROUND,
        JoinBevel = PS_JOIN_BEVEL,
        JoinMiter = PS_JOIN_MITER,
        JoinMask = PS_JOIN_MASK,
        Cosmetic = PS_COSMETIC,
        Geometric = PS_GEOMETRIC,
        TypeMask = PS_TYPE_MASK
    };

    inline PenStyle operator|(PenStyle a, PenStyle b) {
        return static_cast<PenStyle>(static_cast<uint32_t>(a) |
                                     static_cast<uint32_t>(b));
    }
#endif
    class pen {
    public:
        pen(const pen &other) = delete;

        pen(pen &&other) = delete;

        pen &operator=(const pen &other) = delete;

        pen &operator=(pen &&other) = delete;

        pen() = default;

        ~pen() = default;

        static HPEN create(COLORREF color,
                           int32_t width = 0,
                           PenStyle style = PenStyle::Solid);

        static HPEN create(const LOGPEN *log_pen);

        static LOGPEN
        make(COLORREF color, POINT width, PenStyle style = PenStyle::Solid);

        static HPEN create(uint32_t width,
                           const LOGBRUSH *log_brush,
                           std::vector<uint32_t> &len,
                           PenStyle style = PenStyle::Solid);

        static HPEN create_safe(uint32_t width,
                                const LOGBRUSH *log_brush,
                                std::vector<uint32_t> &len,
                                PenStyle style = PenStyle::Solid);

        static bool destroy(HPEN pen_handle);

        static COLORREF set_dc_color(HDC dc_handle, COLORREF color);
    };
} // namespace YanLib::ui::gdi
#endif // PEN_H
