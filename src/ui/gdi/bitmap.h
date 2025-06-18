/* clang-format off */
/*
 * @file bitmap.h
 * @date 2025-04-30
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
#ifndef BITMAP_H
#define BITMAP_H
#include <Windows.h>
#include <minwindef.h>
#include <winnt.h>
#include <wingdi.h>
#include <windef.h>
#include <utility>
#include <vector>
#include "gdi.h"
#pragma comment(lib, "MSImg32.Lib")
namespace YanLib::ui::gdi {
    class bitmap {
    public:
        bitmap(const bitmap &other) = delete;

        bitmap(bitmap &&other) = delete;

        bitmap &operator=(const bitmap &other) = delete;

        bitmap &operator=(bitmap &&other) = delete;

        bitmap() = default;

        ~bitmap() = default;

        // bits.size() =
        //    (((width * planes * pixel_bits + 15) >> 4) << 1) * height;
        // pixel_bits = 1, 24, 32
        static HBITMAP create(int32_t width,
                              int32_t height,
                              uint32_t planes,
                              uint32_t pixel_bits,
                              const std::vector<uint8_t> &bits);

        static HBITMAP create(const BITMAP *bitmap);

        static HBITMAP create_compatible(HDC dc_handle, int32_t x, int32_t y);

        static HBITMAP create_di(HDC dc_handle,
                                 const BITMAPINFOHEADER *bitmap_info_header,
                                 const std::vector<uint8_t> &bits,
                                 const BITMAPINFO *bitmap_info,
                                 bool use_rgb = true,
                                 bool init = true);

        // std::pair<result, error_code>
        static std::pair<HBITMAP, uint32_t>
        create_dib_section(HDC dc_handle,
                           const BITMAPINFO *bitmap_info,
                           void **bits,
                           HANDLE section_handle,
                           uint32_t offset,
                           bool use_rgb = true);

        static HBITMAP load(HINSTANCE instance_handle, const char *bitmap_name);

        static HBITMAP load(HINSTANCE instance_handle,
                            const wchar_t *bitmap_name);

        static bool destroy(HBITMAP bitmap_handle);

        // std::pair<result, error_code>
        static std::pair<bool, uint32_t> bit_blk(HDC dc_handle_dst,
                                                 int32_t x,
                                                 int32_t y,
                                                 int32_t width,
                                                 int32_t height,
                                                 HDC dc_handle_src,
                                                 int32_t x1,
                                                 int32_t y1,
                                                 TernaryRasterCode rop);

        static bool plg_blt(HDC dc_handle_dst,
                            const POINT *point,
                            HDC dc_handle_src,
                            int32_t x_src,
                            int32_t y_src,
                            int32_t width,
                            int32_t height,
                            HBITMAP bitmap_mask_handle,
                            int32_t x_mask,
                            int32_t y_mask);

        static bool mask_blt(HDC dc_handle_dst,
                             int32_t x_dst,
                             int32_t y_dst,
                             int32_t width,
                             int32_t height,
                             HDC dc_handle_src,
                             int32_t x_src,
                             int32_t y_src,
                             HBITMAP bitmap_mask_handle,
                             int32_t x_mask,
                             int32_t y_mask,
                             TernaryRasterCode foreground,
                             TernaryRasterCode background);

        static bool stretch_blt(HDC dc_handle_dst,
                                int32_t x_dst,
                                int32_t y_dst,
                                int32_t width_dst,
                                int32_t height_dst,
                                HDC dc_handle_src,
                                int32_t x_src,
                                int32_t y_src,
                                int32_t width_src,
                                int32_t height_src,
                                TernaryRasterCode rop);

        static bool pat_blt(HDC dc_handle,
                            int32_t x,
                            int32_t y,
                            int32_t width,
                            int32_t height,
                            TernaryRasterCode rop);

        static bool transparent_blt(HDC dc_handle_dst,
                                    int32_t x_dst,
                                    int32_t y_dst,
                                    int32_t width_dst,
                                    int32_t height_dst,
                                    HDC dc_handle_src,
                                    int32_t x_src,
                                    int32_t y_src,
                                    int32_t width_src,
                                    int32_t height_src,
                                    uint32_t transparent);

        static bool gradient_fill(HDC dc_handle,
                                  std::vector<TRIVERTEX> &vertex,
                                  std::vector<GRADIENT_TRIANGLE> &mesh,
                                  GradientMode mode);

        static bool gradient_fill(HDC dc_handle,
                                  std::vector<TRIVERTEX> &vertex,
                                  std::vector<GRADIENT_RECT> &mesh,
                                  GradientMode mode);

        static bool flood_fill(HDC dc_handle,
                               int32_t x,
                               int32_t y,
                               COLORREF color,
                               FloodFill type = FloodFill::Border);

        static int32_t stretch_di_bits(HDC dc_handle,
                                       int32_t x_dst,
                                       int32_t y_dst,
                                       int32_t width_dst,
                                       int32_t height_dst,
                                       int32_t x_src,
                                       int32_t y_src,
                                       int32_t width_src,
                                       int32_t height_src,
                                       const std::vector<uint8_t> &bits,
                                       const BITMAPINFO *bitmap_info,
                                       TernaryRasterCode rop,
                                       bool use_rgb = true);

        static bool alpha_blend(HDC dc_handle_dst,
                                int32_t x_dst,
                                int32_t y_dst,
                                int32_t width_dst,
                                int32_t height_dst,
                                HDC dc_handle_src,
                                int32_t x_src,
                                int32_t y_src,
                                int32_t width_src,
                                int32_t height_src,
                                BLENDFUNCTION blend_function);

        static bool get_bitmap_dimension(HBITMAP bitmap_handle, SIZE *size);

        static bool set_bitmap_dimension(HBITMAP bitmap_handle,
                                         int32_t width,
                                         int32_t height,
                                         SIZE *size);

        static uint32_t get_dib_color_table(HDC dc_handle,
                                            uint32_t index,
                                            std::vector<RGBQUAD> &rgb);

        static uint32_t set_dib_color_table(HDC dc_handle,
                                            uint32_t index,
                                            const std::vector<RGBQUAD> &rgb);

        static int32_t get_di_bits(HDC dc_handle,
                                   HBITMAP bitmap_handle,
                                   uint32_t start_line,
                                   uint32_t line_num,
                                   std::vector<uint8_t> &bits,
                                   BITMAPINFO *bitmap_info,
                                   bool use_rgb = true);

        static int32_t set_di_bits(HDC dc_handle,
                                   HBITMAP bitmap_handle,
                                   uint32_t start_line,
                                   uint32_t line_num,
                                   const std::vector<uint8_t> &bits,
                                   const BITMAPINFO *bitmap_info,
                                   bool use_rgb = true);

        static COLORREF get_pixel(HDC dc_handle, int32_t x, int32_t y);

        static COLORREF
        set_pixel(HDC dc_handle, int32_t x, int32_t y, COLORREF color);

        static bool
        set_pixel_near(HDC dc_handle, int32_t x, int32_t y, COLORREF color);

        static StretchMode get_stretch_blt_mode(HDC dc_handle);

        static StretchMode set_stretch_blt_mode(HDC dc_handle,
                                                StretchMode mode);

        static int32_t set_di_bits_to_device(HDC dc_handle,
                                             int32_t x_dst,
                                             int32_t y_dst,
                                             uint32_t width,
                                             uint32_t height,
                                             int32_t x_src,
                                             int32_t y_src,
                                             uint32_t start_scan,
                                             uint32_t line_num,
                                             const std::vector<uint8_t> &bits,
                                             const BITMAPINFO *bitmap_info,
                                             bool use_rgb = true);
    };
} // namespace YanLib::ui::gdi
#endif // BITMAP_H
