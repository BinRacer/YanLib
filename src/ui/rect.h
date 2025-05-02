//
// Created by forkernel on 2025/5/2.
//

#ifndef RECT_H
#define RECT_H
#include <Windows.h>

namespace YanLib::ui {
    class rect {
    public:
        rect(const rect &other) = delete;

        rect(rect &&other) = delete;

        rect &operator=(const rect &other) = delete;

        rect &operator=(rect &&other) = delete;

        rect() = default;

        ~rect() = default;

        static int fill_rect(HDC dc_handle, const RECT *rect, HBRUSH brush_handle);

        static int frame_rect(HDC dc_handle, const RECT *rect, HBRUSH brush_handle);

        static bool invert_rect(HDC dc_handle, const RECT *rect);

        static bool set_rect(LPRECT rect,
                             int x_left,
                             int y_top,
                             int x_right,
                             int y_bottom);

        static bool copy_rect(LPRECT rect_dst, const RECT *rect_src);

        static bool equal_rect(const RECT *rect1, const RECT *rect2);

        static bool inflate_rect(LPRECT rect, int x, int y);

        static bool intersect_rect(LPRECT rect_dst,
                                   const RECT *rect_src1,
                                   const RECT *rect_src2);

        static bool is_rect_empty(const RECT *rect);

        static bool offset_rect(LPRECT rect, int x, int y);

        static bool point_in_rect(const RECT *rect, POINT point);

        static bool set_rect_empty(LPRECT rect);

        static bool subtract_rect(LPRECT rect_dst,
                                  const RECT *rect_src1,
                                  const RECT *rect_src2);

        static bool union_rect(LPRECT rect_dst,
                               const RECT *rect_src1,
                               const RECT *rect_src2);

        static bool validate_rect(HWND hwnd, const RECT *rect);

        static bool invalidate_rect(HWND hwnd, const RECT *rect, bool is_erase);

        static bool draw_animated_rects(HWND hwnd,
                                        int animate_id,
                                        const RECT *rect_from,
                                        const RECT *rect_to);

        static bool get_client_rect(HWND hwnd, LPRECT rect);

        static bool get_update_rect(HWND hwnd,
                                    LPRECT rect,
                                    bool is_erase);
    };
}
#endif //RECT_H
