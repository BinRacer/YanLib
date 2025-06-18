/* clang-format off */
/*
 * @file paint.h
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
#ifndef PAINT_H
#define PAINT_H
#include <Windows.h>
#include <minwindef.h>
#include <WinUser.h>
#include <windef.h>
#include <utility>
#include <string>
#include "gdi.h"
namespace YanLib::ui::gdi {
    class paint {
    public:
        paint(const paint &other) = delete;

        paint(paint &&other) = delete;

        paint &operator=(const paint &other) = delete;

        paint &operator=(paint &&other) = delete;

        paint() = default;

        ~paint() = default;

        static HDC begin(HWND window_handle, PAINTSTRUCT *paint_struct);

        static bool end(HWND window_handle, const PAINTSTRUCT *paint_struct);

        static bool draw_caption(HWND window_handle,
                                 HDC dc_handle,
                                 const RECT *rect,
                                 DrawOption option);

        static bool draw_edge(HDC dc_handle,
                              RECT *rect,
                              BorderStyle border = BorderStyle::Raised,
                              BorderFlag flag = BorderFlag::Rect);

        static bool draw_state(HDC dc_handle,
                               HBRUSH brush_handle,
                               DRAWSTATEPROC draw_state_proc,
                               LPARAM lparam,
                               WPARAM wparam,
                               int32_t x,
                               int32_t y,
                               int32_t width,
                               int32_t height,
                               ImageTypeState flag);

        static bool draw_frame_control(HDC hdc,
                                       RECT *rect,
                                       FrameType type,
                                       FrameState state);

        static uint32_t get_gdi_batch_limit();

        static uint32_t set_gdi_batch_limit(uint32_t limit);

        static COLORREF get_background_color(HDC dc_handle);

        static COLORREF set_background_color(HDC dc_handle, COLORREF color);

        static BackGroundMode get_background_mode(HDC dc_handle);

        static BackGroundMode set_background_mode(HDC dc_handle,
                                                  BackGroundMode mode);

        static BinaryRasterCode get_rop2(HDC dc_handle);

        static BinaryRasterCode set_rop2(HDC dc_handle, BinaryRasterCode mode);

        static bool gray_string(HDC dc_handle,
                                HBRUSH brush_handle,
                                GRAYSTRINGPROC gray_string_proc,
                                LPARAM lparam,
                                int32_t char_num,
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
