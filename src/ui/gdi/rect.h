//
// Created by forkernel on 2025/5/2.
//

#ifndef RECT_H
#define RECT_H
#include <utility>
#include <Windows.h>

namespace YanLib::ui::gdi {
class rect {
public:
    rect(const rect &other)            = delete;

    rect(rect &&other)                 = delete;

    rect &operator=(const rect &other) = delete;

    rect &operator=(rect &&other)      = delete;

    rect()                             = default;

    ~rect()                            = default;

    static int32_t
    fill_rect(HDC dc_handle, const RECT *rect, HBRUSH brush_handle);

    static int32_t
    frame_rect(HDC dc_handle, const RECT *rect, HBRUSH brush_handle);

    static bool invert_rect(HDC dc_handle, const RECT *rect);

    static bool set_rect(RECT *rect,
        int32_t                x_left,
        int32_t                y_top,
        int32_t                x_right,
        int32_t                y_bottom);

    static bool copy_rect(RECT *rect_dst, const RECT *rect_src);

    static bool equal_rect(const RECT *rect1, const RECT *rect2);

    static bool inflate_rect(RECT *rect, int32_t x, int32_t y);

    static bool intersect_rect(RECT *rect_dst,
        const RECT                  *rect_src1,
        const RECT                  *rect_src2);

    static bool is_rect_empty(const RECT *rect);

    static bool offset_rect(RECT *rect, int32_t x, int32_t y);

    static bool point_in_rect(const RECT *rect, POINT point);

    static bool set_rect_empty(RECT *rect);

    static bool
    subtract_rect(RECT *rect_dst, const RECT *rect_src1, const RECT *rect_src2);

    static bool
    union_rect(RECT *rect_dst, const RECT *rect_src1, const RECT *rect_src2);

    static bool validate_rect(HWND window_handle, const RECT *rect);

    static bool
    invalidate_rect(HWND window_handle, const RECT *rect, bool is_erase);

    static bool draw_animated_rects(HWND window_handle,
        int32_t                          animate_id,
        const RECT                      *rect_from,
        const RECT                      *rect_to);

    static bool draw_focus_rect(HDC dc_handle, const RECT *rect);

    static uint32_t get_bounds_rect(HDC dc_handle, RECT *rect, uint32_t flag);

    static uint32_t
    set_bounds_rect(HDC dc_handle, const RECT *rect, uint32_t flag);

    static bool get_update_rect(HWND window_handle, RECT *rect, bool is_erase);

    // std::pair<result, error_code>
    static std::pair<bool, uint32_t> get_client_rect(HWND window_handle,
        RECT                                             *rect);
};
} // namespace YanLib::ui::gdi
#endif // RECT_H
