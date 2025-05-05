//
// Created by forkernel on 2025/5/5.
//

#ifndef PAINT_H
#define PAINT_H
#include <Windows.h>

namespace YanLib::ui::gdi {
    class paint {
    public:
        paint(const paint &other) = delete;

        paint(paint &&other) = delete;

        paint &operator=(const paint &other) = delete;

        paint &operator=(paint &&other) = delete;

        paint() = default;

        ~paint() = default;

        static HDC begin_paint(HWND hwnd, PAINTSTRUCT *paint_struct);

        static bool end_paint(HWND hwnd, const PAINTSTRUCT *paint_struct);

        static bool draw_caption(HWND hwnd,
                                 HDC dc_handle,
                                 const RECT *rect,
                                 unsigned int flag);

        static bool draw_edge(HDC dc_handle,
                              RECT *rect,
                              unsigned int edge,
                              unsigned int flag);

        static bool draw_state(HDC dc_handle,
                               HBRUSH brush_handle,
                               DRAWSTATEPROC draw_state_proc,
                               LPARAM l_param,
                               WPARAM w_param,
                               int x,
                               int y,
                               int width,
                               int height,
                               unsigned int flag);

        static bool draw_animated_rect(HWND hwnd,
                                       int animate_id,
                                       const RECT *rect_from,
                                       const RECT *rect_to);

        static bool draw_focus_rect(HDC dc_handle, const RECT *rect);

        static bool draw_frame_control(HDC hdc,
                                       RECT *rect,
                                       unsigned int type,
                                       unsigned int state);

        static unsigned long gdi_get_batch_limit();

        static unsigned long gdi_set_batch_limit(unsigned long limit);

        static COLORREF get_background_color(HDC dc_handle);

        static COLORREF set_background_color(HDC dc_handle, COLORREF color);

        static int get_background_mode(HDC dc_handle);

        static int set_background_mode(HDC dc_handle, int mode);

        static unsigned int get_bounds_rect(HDC dc_handle,
                                            RECT *rect,
                                            unsigned int flag);

        static unsigned int set_bounds_rect(HDC dc_handle,
                                            const RECT *rect,
                                            unsigned int flag);

        static int get_rop2(HDC dc_handle);

        static int set_rop2(HDC dc_handle, int mode);

        static int get_window_region(HWND hwnd, HRGN region_handle);

        static int set_window_region(HWND hwnd, HRGN region_handle, bool redraw);

        static bool validate_rect(HWND hwnd, const RECT *rect);

        static bool invalidate_rect(HWND hwnd, const RECT *rect, bool is_erase);

        static bool validate_region(HWND hwnd, HRGN region_handle);

        static bool invalidate_region(HWND hwnd, HRGN region_handle, bool is_erase);

        static bool lock_window_update(HWND hwnd);

        static bool update_window(HWND hwnd);

        static bool redraw_window(HWND hwnd,
                                  const RECT *rect,
                                  HRGN region_handle,
                                  unsigned int flag);

        static HDC get_window_dc(HWND hwnd);

        static HWND window_from_dc(HDC dc_handle);

        static bool paint_desktop(HDC dc_handle);

        static bool get_update_rect(HWND hwnd, RECT *rect, bool is_erase);

        static int get_update_region(HWND hwnd,
                                     HRGN region_handle,
                                     bool is_erase);

        static int exclude_update_region(HDC dc_handle, HWND hwnd);

        static int get_window_region_box(HWND hwnd, RECT *rect);

        static bool gray_string(HDC dc_handle,
                                HBRUSH brush_handle,
                                GRAYSTRINGPROC gray_string_proc,
                                LPARAM l_param,
                                int cch_size,
                                int x,
                                int y,
                                int width,
                                int height);

        static bool gdi_flush();
    };
}
#endif //PAINT_H
