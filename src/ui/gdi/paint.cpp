/* clang-format off */
/*
 * @file paint.cpp
 * @date 2025-05-05
 * @license MIT License
 *
 * Copyright (c) 2025 BinRacer <native.lab@outlook.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
/* clang-format on */
#include "paint.h"

namespace YanLib::ui::gdi {
    HDC paint::begin(HWND window_handle, PAINTSTRUCT *paint_struct) {
        return BeginPaint(window_handle, paint_struct);
    }

    bool paint::end(HWND window_handle, const PAINTSTRUCT *paint_struct) {
        return EndPaint(window_handle, paint_struct);
    }

    bool paint::draw_caption(HWND window_handle,
                             HDC dc_handle,
                             const RECT *rect,
                             DrawOption option) {
        return DrawCaption(window_handle, dc_handle, rect,
                           static_cast<uint32_t>(option));
    }

    bool paint::draw_edge(HDC dc_handle,
                          RECT *rect,
                          BorderStyle border,
                          BorderFlag flag) {
        return DrawEdge(dc_handle, rect, static_cast<uint32_t>(border),
                        static_cast<uint32_t>(flag));
    }

    bool paint::draw_state(HDC dc_handle,
                           HBRUSH brush_handle,
                           DRAWSTATEPROC draw_state_proc,
                           LPARAM lparam,
                           WPARAM wparam,
                           int32_t x,
                           int32_t y,
                           int32_t width,
                           int32_t height,
                           ImageTypeState flag) {
        return DrawStateW(dc_handle, brush_handle, draw_state_proc, lparam,
                          wparam, x, y, width, height,
                          static_cast<uint32_t>(flag));
    }

    bool paint::draw_frame_control(HDC hdc,
                                   RECT *rect,
                                   FrameType type,
                                   FrameState state) {
        return DrawFrameControl(hdc, rect, static_cast<uint32_t>(type),
                                static_cast<uint32_t>(state));
    }

    uint32_t paint::get_gdi_batch_limit() {
        return GdiGetBatchLimit();
    }

    uint32_t paint::set_gdi_batch_limit(uint32_t limit) {
        return GdiSetBatchLimit(limit);
    }

    COLORREF paint::get_background_color(HDC dc_handle) {
        return GetBkColor(dc_handle);
    }

    COLORREF paint::set_background_color(HDC dc_handle, COLORREF color) {
        return SetBkColor(dc_handle, color);
    }

    BackGroundMode paint::get_background_mode(HDC dc_handle) {
        return static_cast<BackGroundMode>(GetBkMode(dc_handle));
    }

    BackGroundMode paint::set_background_mode(HDC dc_handle,
                                              BackGroundMode mode) {
        return static_cast<BackGroundMode>(
                SetBkMode(dc_handle, static_cast<int32_t>(mode)));
    }

    BinaryRasterCode paint::get_rop2(HDC dc_handle) {
        return static_cast<BinaryRasterCode>(GetROP2(dc_handle));
    }

    BinaryRasterCode paint::set_rop2(HDC dc_handle, BinaryRasterCode mode) {
        return static_cast<BinaryRasterCode>(
                SetROP2(dc_handle, static_cast<int32_t>(mode)));
    }

    bool paint::gray_string(HDC dc_handle,
                            HBRUSH brush_handle,
                            GRAYSTRINGPROC gray_string_proc,
                            LPARAM lparam,
                            int32_t char_num,
                            int32_t x,
                            int32_t y,
                            int32_t width,
                            int32_t height) {
        return GrayStringW(dc_handle, brush_handle, gray_string_proc, lparam,
                           char_num, x, y, width, height);
    }

    std::pair<int32_t, uint32_t> paint::load_string(HINSTANCE instance_handle,
                                                    uint32_t id,
                                                    std::string &text) {
        int32_t result = LoadStringA(instance_handle, id, text.data(),
                                     static_cast<int32_t>(text.size()));
        uint32_t error_code = GetLastError();
        return std::make_pair(result, error_code);
    }

    std::pair<int32_t, uint32_t> paint::load_string(HINSTANCE instance_handle,
                                                    uint32_t id,
                                                    std::wstring &text) {
        int32_t result = LoadStringW(instance_handle, id, text.data(),
                                     static_cast<int32_t>(text.size()));
        uint32_t error_code = GetLastError();
        return std::make_pair(result, error_code);
    }

    bool paint::gdi_flush() {
        return GdiFlush();
    }
} // namespace YanLib::ui::gdi
