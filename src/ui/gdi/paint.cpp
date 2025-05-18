//
// Created by forkernel on 2025/5/5.
//

#include "paint.h"

namespace YanLib::ui::gdi {
HDC paint::begin_paint(HWND window_handle, PAINTSTRUCT *paint_struct) {
    return BeginPaint(window_handle, paint_struct);
}

bool paint::end_paint(HWND window_handle, const PAINTSTRUCT *paint_struct) {
    return EndPaint(window_handle, paint_struct);
}

bool paint::draw_caption(HWND window_handle,
    HDC                       dc_handle,
    const RECT               *rect,
    uint32_t                  flag) {
    return DrawCaption(window_handle, dc_handle, rect, flag);
}

bool paint::draw_edge(HDC dc_handle, RECT *rect, uint32_t edge, uint32_t flag) {
    return DrawEdge(dc_handle, rect, edge, flag);
}

bool paint::draw_state(HDC dc_handle,
    HBRUSH                 brush_handle,
    DRAWSTATEPROC          draw_state_proc,
    LPARAM                 lparam,
    WPARAM                 wparam,
    int32_t                x,
    int32_t                y,
    int32_t                width,
    int32_t                height,
    uint32_t               flag) {
    return DrawStateW(dc_handle, brush_handle, draw_state_proc, lparam, wparam,
        x, y, width, height, flag);
}

bool paint::draw_frame_control(HDC hdc,
    RECT                          *rect,
    uint32_t                       type,
    uint32_t                       state) {
    return DrawFrameControl(hdc, rect, type, state);
}

uint32_t paint::gdi_get_batch_limit() {
    return GdiGetBatchLimit();
}

uint32_t paint::gdi_set_batch_limit(uint32_t limit) {
    return GdiSetBatchLimit(limit);
}

COLORREF paint::get_background_color(HDC dc_handle) {
    return GetBkColor(dc_handle);
}

COLORREF paint::set_background_color(HDC dc_handle, COLORREF color) {
    return SetBkColor(dc_handle, color);
}

int32_t paint::get_background_mode(HDC dc_handle) {
    return GetBkMode(dc_handle);
}

int32_t paint::set_background_mode(HDC dc_handle, int32_t mode) {
    return SetBkMode(dc_handle, mode);
}

int32_t paint::get_rop2(HDC dc_handle) {
    return GetROP2(dc_handle);
}

int32_t paint::set_rop2(HDC dc_handle, int32_t mode) {
    return SetROP2(dc_handle, mode);
}

bool paint::gray_string(HDC dc_handle,
    HBRUSH                  brush_handle,
    GRAYSTRINGPROC          gray_string_proc,
    LPARAM                  lparam,
    int32_t                 cch_size,
    int32_t                 x,
    int32_t                 y,
    int32_t                 width,
    int32_t                 height) {
    return GrayStringW(dc_handle, brush_handle, gray_string_proc, lparam,
        cch_size, x, y, width, height);
}

std::pair<int32_t, uint32_t>
paint::load_string(HINSTANCE instance_handle, uint32_t id, std::string &text) {
    int32_t result = LoadStringA(
        instance_handle, id, text.data(), static_cast<int>(text.size()));
    uint32_t error_code = GetLastError();
    return std::make_pair(result, error_code);
}

std::pair<int32_t, uint32_t>
paint::load_string(HINSTANCE instance_handle, uint32_t id, std::wstring &text) {
    int32_t result = LoadStringW(
        instance_handle, id, text.data(), static_cast<int>(text.size()));
    uint32_t error_code = GetLastError();
    return std::make_pair(result, error_code);
}

bool paint::gdi_flush() {
    return GdiFlush();
}
} // namespace YanLib::ui::gdi
