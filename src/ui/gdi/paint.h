//
// Created by forkernel on 2025/5/5.
//

#ifndef PAINT_H
#define PAINT_H
#include <utility>
#include <Windows.h>
#include <string>

namespace YanLib::ui::gdi {
    class paint {
    public:
        paint(const paint &other) = delete;

        paint(paint &&other) = delete;

        paint &operator=(const paint &other) = delete;

        paint &operator=(paint &&other) = delete;

        paint() = default;

        ~paint() = default;

        static HDC begin_paint(HWND window_handle, PAINTSTRUCT* paint_struct);

        static bool end_paint(HWND window_handle,
                              const PAINTSTRUCT* paint_struct);

        static bool draw_caption(HWND window_handle,
                                 HDC dc_handle,
                                 const RECT* rect,
                                 uint32_t flag);

        static bool
        draw_edge(HDC dc_handle, RECT* rect, uint32_t edge, uint32_t flag);

        static bool draw_state(HDC dc_handle,
                               HBRUSH brush_handle,
                               DRAWSTATEPROC draw_state_proc,
                               LPARAM lparam,
                               WPARAM wparam,
                               int32_t x,
                               int32_t y,
                               int32_t width,
                               int32_t height,
                               uint32_t flag);

        static bool
        draw_frame_control(HDC hdc, RECT* rect, uint32_t type, uint32_t state);

        static uint32_t gdi_get_batch_limit();

        static uint32_t gdi_set_batch_limit(uint32_t limit);

        static COLORREF get_background_color(HDC dc_handle);

        static COLORREF set_background_color(HDC dc_handle, COLORREF color);

        static int32_t get_background_mode(HDC dc_handle);

        static int32_t set_background_mode(HDC dc_handle, int32_t mode);

        static int32_t get_rop2(HDC dc_handle);

        static int32_t set_rop2(HDC dc_handle, int32_t mode);

        static bool gray_string(HDC dc_handle,
                                HBRUSH brush_handle,
                                GRAYSTRINGPROC gray_string_proc,
                                LPARAM lparam,
                                int32_t cch_size,
                                int32_t x,
                                int32_t y,
                                int32_t width,
                                int32_t height);

        static std::pair<int32_t, uint32_t>
        load_string(HINSTANCE instance_handle, uint32_t id, std::string &text);

        static std::pair<int32_t, uint32_t>
        load_string(HINSTANCE instance_handle, uint32_t id, std::wstring &text);

        static bool gdi_flush();
    };
} // namespace YanLib::ui::gdi
#endif // PAINT_H
