//
// Created by forkernel on 2025/5/5.
//

#include "paint.h"

namespace YanLib::ui::gdi {
    HDC paint::begin_paint(HWND hwnd, PAINTSTRUCT *paint_struct) {
        return BeginPaint(hwnd, paint_struct);
    }

    bool paint::end_paint(HWND hwnd, const PAINTSTRUCT *paint_struct) {
        return EndPaint(hwnd, paint_struct);
    }

    bool paint::draw_caption(HWND hwnd,
                             HDC dc_handle,
                             const RECT *rect,
                             UINT flag) {
        return DrawCaption(hwnd, dc_handle, rect, flag);
    }

    bool paint::draw_edge(HDC dc_handle,
                          RECT *rect,
                          UINT edge,
                          UINT flag) {
        return DrawEdge(dc_handle, rect, edge, flag);
    }

    bool paint::draw_state(HDC dc_handle,
                           HBRUSH brush_handle,
                           DRAWSTATEPROC draw_state_proc,
                           LPARAM l_param,
                           WPARAM w_param,
                           int x,
                           int y,
                           int width,
                           int height,
                           UINT flag) {
        return DrawStateW(dc_handle,
                          brush_handle,
                          draw_state_proc,
                          l_param,
                          w_param,
                          x,
                          y,
                          width,
                          height,
                          flag);
    }

    bool paint::draw_animated_rect(HWND hwnd,
                                   int animate_id,
                                   const RECT *rect_from,
                                   const RECT *rect_to) {
        return DrawAnimatedRects(hwnd, animate_id, rect_from, rect_to);
    }

    bool paint::draw_focus_rect(HDC dc_handle, const RECT *rect) {
        return DrawFocusRect(dc_handle, rect);
    }

    bool paint::draw_frame_control(HDC hdc,
                                   RECT *rect,
                                   UINT type,
                                   UINT state) {
        return DrawFrameControl(hdc, rect, type, state);
    }

    DWORD paint::gdi_get_batch_limit() {
        return GdiGetBatchLimit();
    }

    DWORD paint::gdi_set_batch_limit(DWORD limit) {
        return GdiSetBatchLimit(limit);
    }

    COLORREF paint::get_background_color(HDC dc_handle) {
        return GetBkColor(dc_handle);
    }

    COLORREF paint::set_background_color(HDC dc_handle, COLORREF color) {
        return SetBkColor(dc_handle, color);
    }

    int paint::get_background_mode(HDC dc_handle) {
        return GetBkMode(dc_handle);
    }

    int paint::set_background_mode(HDC dc_handle, int mode) {
        return SetBkMode(dc_handle, mode);
    }

    UINT paint::get_bounds_rect(HDC dc_handle, RECT *rect, UINT flag) {
        return GetBoundsRect(dc_handle, rect, flag);
    }

    UINT paint::set_bounds_rect(HDC dc_handle, const RECT *rect, UINT flag) {
        return SetBoundsRect(dc_handle, rect, flag);
    }

    int paint::get_rop2(HDC dc_handle) {
        return GetROP2(dc_handle);
    }

    int paint::set_rop2(HDC dc_handle, int mode) {
        return SetROP2(dc_handle, mode);
    }

    int paint::get_window_region(HWND hwnd, HRGN region_handle) {
        return GetWindowRgn(hwnd, region_handle);
    }

    int paint::set_window_region(HWND hwnd, HRGN region_handle, bool redraw) {
        return SetWindowRgn(hwnd, region_handle, redraw ? TRUE : FALSE);
    }

    bool paint::validate_rect(HWND hwnd, const RECT *rect) {
        return ValidateRect(hwnd, rect);
    }

    bool paint::invalidate_rect(HWND hwnd, const RECT *rect, bool is_erase) {
        return InvalidateRect(hwnd, rect, is_erase ? TRUE : FALSE);
    }

    bool paint::validate_region(HWND hwnd, HRGN region_handle) {
        return ValidateRgn(hwnd, region_handle);
    }

    bool paint::invalidate_region(HWND hwnd, HRGN region_handle, bool is_erase) {
        return InvalidateRgn(hwnd, region_handle, is_erase ? TRUE : FALSE);
    }

    bool paint::lock_window_update(HWND hwnd) {
        return LockWindowUpdate(hwnd);
    }

    bool paint::update_window(HWND hwnd) {
        return UpdateWindow(hwnd);
    }

    bool paint::redraw_window(HWND hwnd,
                              const RECT *rect,
                              HRGN region_handle,
                              UINT flag) {
        return RedrawWindow(hwnd, rect, region_handle, flag);
    }

    HDC paint::get_window_dc(HWND hwnd) {
        return GetWindowDC(hwnd);
    }

    HWND paint::window_from_dc(HDC dc_handle) {
        return WindowFromDC(dc_handle);
    }

    bool paint::paint_desktop(HDC dc_handle) {
        return PaintDesktop(dc_handle);
    }

    bool paint::get_update_rect(HWND hwnd, RECT *rect, bool is_erase) {
        return GetUpdateRect(hwnd, rect, is_erase ? TRUE : FALSE);
    }

    int paint::get_update_region(HWND hwnd, HRGN region_handle, bool is_erase) {
        return GetUpdateRgn(hwnd, region_handle, is_erase ? TRUE : FALSE);
    }

    int paint::exclude_update_region(HDC dc_handle, HWND hwnd) {
        return ExcludeUpdateRgn(dc_handle, hwnd);
    }

    int paint::get_window_region_box(HWND hwnd, RECT *rect) {
        return GetWindowRgnBox(hwnd, rect);
    }

    bool paint::gray_string(HDC dc_handle,
                            HBRUSH brush_handle,
                            GRAYSTRINGPROC gray_string_proc,
                            LPARAM l_param,
                            int cch_size,
                            int x,
                            int y,
                            int width,
                            int height) {
        return GrayStringW(dc_handle,
                           brush_handle,
                           gray_string_proc,
                           l_param,
                           cch_size,
                           x,
                           y,
                           width,
                           height);
    }

    bool paint::gdi_flush() {
        return GdiFlush();
    }
}
