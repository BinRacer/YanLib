//
// Created by forkernel on 2025/5/2.
//

#ifndef RECT_H
#define RECT_H
#include <utility>
#include <Windows.h>

namespace YanLib::ui::gdi {
#ifndef ANIMATIONTYPE
#define ANIMATIONTYPE

    enum class AnimationType : int32_t {
        Open = IDANI_OPEN,
        Caption = IDANI_CAPTION,
    };
#endif
#ifndef BOUNDFLAG
#define BOUNDFLAG

    enum class BoundFlag : uint32_t {
        Error = 0,
        Reset = DCB_RESET,
        Accumulate = DCB_ACCUMULATE,
        Dirty = DCB_DIRTY,
        Set = DCB_SET,
        Enable = DCB_ENABLE,
        Disable = DCB_DISABLE,
    };
#endif
    class rect {
    public:
        rect(const rect &other) = delete;

        rect(rect &&other) = delete;

        rect &operator=(const rect &other) = delete;

        rect &operator=(rect &&other) = delete;

        rect() = default;

        ~rect() = default;

        static int32_t
        fill(HDC dc_handle, const RECT *rect, HBRUSH brush_handle);

        static int32_t
        frame(HDC dc_handle, const RECT *rect, HBRUSH brush_handle);

        static bool invert(HDC dc_handle, const RECT *rect);

        static bool set(RECT *rect,
                        int32_t left,
                        int32_t top,
                        int32_t right,
                        int32_t bottom);

        static bool copy(RECT *rect_dst, const RECT *rect_src);

        static bool equal(const RECT *rect1, const RECT *rect2);

        static bool inflate(RECT *rect, int32_t x, int32_t y);

        static bool
        intersect(RECT *rect_dst, const RECT *rect_src1, const RECT *rect_src2);

        static bool is_empty(const RECT *rect);

        static bool offset(RECT *rect, int32_t x, int32_t y);

        static bool contains_point(const RECT *rect, POINT point);

        static bool empty(RECT *rect);

        static bool
        subtract(RECT *rect_dst, const RECT *rect_src1, const RECT *rect_src2);

        static bool
        unions(RECT *rect_dst, const RECT *rect_src1, const RECT *rect_src2);

        static bool validate(HWND window_handle, const RECT *rect);

        static bool
        invalidate(HWND window_handle, const RECT *rect, bool is_erase = true);

        static bool draw_animated(HWND window_handle,
                                  const RECT *rect_from,
                                  const RECT *rect_to,
                                  AnimationType type = AnimationType::Caption);

        static bool draw_focus(HDC dc_handle, const RECT *rect);

        static BoundFlag get_bounds(HDC dc_handle, RECT *rect, BoundFlag flag);

        static BoundFlag
        set_bounds(HDC dc_handle, const RECT *rect, BoundFlag flag);

        static bool
        get_update(HWND window_handle, RECT *rect, bool is_erase = true);

        // std::pair<result, error_code>
        static std::pair<bool, uint32_t> get_client(HWND window_handle,
                                                    RECT *rect);
    };
} // namespace YanLib::ui::gdi
#endif // RECT_H
