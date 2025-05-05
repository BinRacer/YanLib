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
        rect(const rect &other) = delete;

        rect(rect &&other) = delete;

        rect &operator=(const rect &other) = delete;

        rect &operator=(rect &&other) = delete;

        rect() = default;

        ~rect() = default;

        static int fill_rect(HDC dc_handle, const RECT *rect, HBRUSH brush_handle);

        static int frame_rect(HDC dc_handle, const RECT *rect, HBRUSH brush_handle);

        static bool invert_rect(HDC dc_handle, const RECT *rect);

        static bool set_rect(RECT *rect,
                             int x_left,
                             int y_top,
                             int x_right,
                             int y_bottom);

        static bool copy_rect(RECT *rect_dst, const RECT *rect_src);

        static bool equal_rect(const RECT *rect1, const RECT *rect2);

        static bool inflate_rect(RECT *rect, int x, int y);

        static bool intersect_rect(RECT *rect_dst,
                                   const RECT *rect_src1,
                                   const RECT *rect_src2);

        static bool is_rect_empty(const RECT *rect);

        static bool offset_rect(RECT *rect, int x, int y);

        static bool point_in_rect(const RECT *rect, POINT point);

        static bool set_rect_empty(RECT *rect);

        static bool subtract_rect(RECT *rect_dst,
                                  const RECT *rect_src1,
                                  const RECT *rect_src2);

        static bool union_rect(RECT *rect_dst,
                               const RECT *rect_src1,
                               const RECT *rect_src2);

        static bool validate_rect(HWND hwnd, const RECT *rect);

        static bool invalidate_rect(HWND hwnd, const RECT *rect, bool is_erase);

        static bool draw_animated_rects(HWND hwnd,
                                        int animate_id,
                                        const RECT *rect_from,
                                        const RECT *rect_to);

        static bool draw_focus_rect(HDC dc_handle, const RECT *rect);

        static unsigned int get_bounds_rect(HDC dc_handle,
                                            RECT *rect,
                                            unsigned int flag);

        static unsigned int set_bounds_rect(HDC dc_handle,
                                            const RECT *rect,
                                            unsigned int flag);

        static bool get_update_rect(HWND hwnd,
                                    RECT *rect,
                                    bool is_erase);

        // std::pair<result, error_code>
        static std::pair<bool, unsigned long> get_client_rect(HWND hwnd, RECT *rect);
    };
}
#endif //RECT_H
