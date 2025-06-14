/* clang-format off */
/*
 * @file bitmap.cpp
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
#include "bitmap.h"

namespace YanLib::ui::gdi {
    HBITMAP bitmap::create(int32_t width,
                           int32_t height,
                           uint32_t planes,
                           uint32_t pixel_bits,
                           const std::vector<uint8_t> &bits) {
        return CreateBitmap(width, height, planes, pixel_bits, bits.data());
    }

    HBITMAP bitmap::create(const BITMAP *bitmap) {
        return CreateBitmapIndirect(bitmap);
    }

    HBITMAP bitmap::create_compatible(HDC dc_handle, int32_t x, int32_t y) {
        return CreateCompatibleBitmap(dc_handle, x, y);
    }

    HBITMAP bitmap::create_di(HDC dc_handle,
                              const BITMAPINFOHEADER *bitmap_info_header,
                              const std::vector<uint8_t> &bits,
                              const BITMAPINFO *bitmap_info,
                              bool use_rgb,
                              bool init) {
        return CreateDIBitmap(dc_handle, bitmap_info_header,
                              init ? CBM_INIT : 0, bits.data(), bitmap_info,
                              use_rgb ? DIB_RGB_COLORS : DIB_PAL_COLORS);
    }

    std::pair<HBITMAP, uint32_t>
    bitmap::create_dib_section(HDC dc_handle,
                               const BITMAPINFO *bitmap_info,
                               void **bits,
                               HANDLE section_handle,
                               uint32_t offset,
                               bool use_rgb) {
        HBITMAP result =
                CreateDIBSection(dc_handle, bitmap_info,
                                 use_rgb ? DIB_RGB_COLORS : DIB_PAL_COLORS,
                                 bits, section_handle, offset);
        uint32_t error_code = 0;
        if (!result) {
            error_code = GetLastError();
        }
        return std::make_pair(result, error_code);
    }

    HBITMAP bitmap::load(HINSTANCE instance_handle, const char *bitmap_name) {
        return LoadBitmapA(instance_handle, bitmap_name);
    }

    HBITMAP bitmap::load(HINSTANCE instance_handle,
                         const wchar_t *bitmap_name) {
        return LoadBitmapW(instance_handle, bitmap_name);
    }

    bool bitmap::destroy(HBITMAP bitmap_handle) {
        return DeleteObject(bitmap_handle);
    }

    std::pair<bool, uint32_t> bitmap::bit_blk(HDC dc_handle_dst,
                                              int32_t x,
                                              int32_t y,
                                              int32_t width,
                                              int32_t height,
                                              HDC dc_handle_src,
                                              int32_t x1,
                                              int32_t y1,
                                              TernaryRasterCode rop) {
        uint32_t error_code = 0;
        if (!BitBlt(dc_handle_dst, x, y, width, height, dc_handle_src, x1, y1,
                    static_cast<uint32_t>(rop))) {
            error_code = GetLastError();
            return std::make_pair(false, error_code);
        }
        return std::make_pair(true, error_code);
    }

    bool bitmap::plg_blt(HDC dc_handle_dst,
                         const POINT *point,
                         HDC dc_handle_src,
                         int32_t x_src,
                         int32_t y_src,
                         int32_t width,
                         int32_t height,
                         HBITMAP bitmap_mask_handle,
                         int32_t x_mask,
                         int32_t y_mask) {
        return PlgBlt(dc_handle_dst, point, dc_handle_src, x_src, y_src, width,
                      height, bitmap_mask_handle, x_mask, y_mask);
    }

    bool bitmap::mask_blt(HDC dc_handle_dst,
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
                          TernaryRasterCode background) {
        return MaskBlt(dc_handle_dst, x_dst, y_dst, width, height,
                       dc_handle_src, x_src, y_src, bitmap_mask_handle, x_mask,
                       y_mask,
                       MAKEROP4(static_cast<uint32_t>(foreground),
                                static_cast<uint32_t>(background)));
    }

    bool bitmap::stretch_blt(HDC dc_handle_dst,
                             int32_t x_dst,
                             int32_t y_dst,
                             int32_t width_dst,
                             int32_t height_dst,
                             HDC dc_handle_src,
                             int32_t x_src,
                             int32_t y_src,
                             int32_t width_src,
                             int32_t height_src,
                             TernaryRasterCode rop) {
        return StretchBlt(dc_handle_dst, x_dst, y_dst, width_dst, height_dst,
                          dc_handle_src, x_src, y_src, width_src, height_src,
                          static_cast<uint32_t>(rop));
    }

    bool bitmap::pat_blt(HDC dc_handle,
                         int32_t x,
                         int32_t y,
                         int32_t width,
                         int32_t height,
                         TernaryRasterCode rop) {
        return PatBlt(dc_handle, x, y, width, height,
                      static_cast<uint32_t>(rop));
    }

    bool bitmap::transparent_blt(HDC dc_handle_dst,
                                 int32_t x_dst,
                                 int32_t y_dst,
                                 int32_t width_dst,
                                 int32_t height_dst,
                                 HDC dc_handle_src,
                                 int32_t x_src,
                                 int32_t y_src,
                                 int32_t width_src,
                                 int32_t height_src,
                                 uint32_t transparent) {
        return TransparentBlt(dc_handle_dst, x_dst, y_dst, width_dst,
                              height_dst, dc_handle_src, x_src, y_src,
                              width_src, height_src, transparent);
    }

    bool bitmap::gradient_fill(HDC dc_handle,
                               std::vector<TRIVERTEX> &vertex,
                               std::vector<GRADIENT_TRIANGLE> &mesh,
                               GradientMode mode) {
        return GradientFill(dc_handle, vertex.data(), vertex.size(),
                            mesh.data(), mesh.size(),
                            static_cast<uint32_t>(mode));
    }

    bool bitmap::gradient_fill(HDC dc_handle,
                               std::vector<TRIVERTEX> &vertex,
                               std::vector<GRADIENT_RECT> &mesh,
                               GradientMode mode) {
        return GradientFill(dc_handle, vertex.data(), vertex.size(),
                            mesh.data(), mesh.size(),
                            static_cast<uint32_t>(mode));
    }

    bool bitmap::flood_fill(HDC dc_handle,
                            int32_t x,
                            int32_t y,
                            COLORREF color,
                            FloodFill type) {
        return ExtFloodFill(dc_handle, x, y, color,
                            static_cast<uint32_t>(type));
    }

    int32_t bitmap::stretch_di_bits(HDC dc_handle,
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
                                    bool use_rgb) {
        return StretchDIBits(dc_handle, x_dst, y_dst, width_dst, height_dst,
                             x_src, y_src, width_src, height_src, bits.data(),
                             bitmap_info,
                             use_rgb ? DIB_RGB_COLORS : DIB_PAL_COLORS,
                             static_cast<uint32_t>(rop));
    }

    bool bitmap::alpha_blend(HDC dc_handle_dst,
                             int32_t x_dst,
                             int32_t y_dst,
                             int32_t width_dst,
                             int32_t height_dst,
                             HDC dc_handle_src,
                             int32_t x_src,
                             int32_t y_src,
                             int32_t width_src,
                             int32_t height_src,
                             BLENDFUNCTION blend_function) {
        return AlphaBlend(dc_handle_dst, x_dst, y_dst, width_dst, height_dst,
                          dc_handle_src, x_src, y_src, width_src, height_src,
                          blend_function);
    }

    bool bitmap::get_bitmap_dimension(HBITMAP bitmap_handle, SIZE *size) {
        return GetBitmapDimensionEx(bitmap_handle, size);
    }

    bool bitmap::set_bitmap_dimension(HBITMAP bitmap_handle,
                                      int32_t width,
                                      int32_t height,
                                      SIZE *size) {
        return SetBitmapDimensionEx(bitmap_handle, width, height, size);
    }

    uint32_t bitmap::get_dib_color_table(HDC dc_handle,
                                         uint32_t index,
                                         std::vector<RGBQUAD> &rgb) {
        return GetDIBColorTable(dc_handle, index, rgb.size(), rgb.data());
    }

    uint32_t bitmap::set_dib_color_table(HDC dc_handle,
                                         uint32_t index,
                                         const std::vector<RGBQUAD> &rgb) {
        return SetDIBColorTable(dc_handle, index, rgb.size(), rgb.data());
    }

    int32_t bitmap::get_di_bits(HDC dc_handle,
                                HBITMAP bitmap_handle,
                                uint32_t start_line,
                                uint32_t line_num,
                                std::vector<uint8_t> &bits,
                                BITMAPINFO *bitmap_info,
                                bool use_rgb) {
        return GetDIBits(dc_handle, bitmap_handle, start_line, line_num,
                         bits.data(), bitmap_info,
                         use_rgb ? DIB_RGB_COLORS : DIB_PAL_COLORS);
    }

    int32_t bitmap::set_di_bits(HDC dc_handle,
                                HBITMAP bitmap_handle,
                                uint32_t start_line,
                                uint32_t line_num,
                                const std::vector<uint8_t> &bits,
                                const BITMAPINFO *bitmap_info,
                                bool use_rgb) {
        return SetDIBits(dc_handle, bitmap_handle, start_line, line_num,
                         bits.data(), bitmap_info,
                         use_rgb ? DIB_RGB_COLORS : DIB_PAL_COLORS);
    }

    COLORREF bitmap::get_pixel(HDC dc_handle, int32_t x, int32_t y) {
        return GetPixel(dc_handle, x, y);
    }

    COLORREF
    bitmap::set_pixel(HDC dc_handle, int32_t x, int32_t y, COLORREF color) {
        return SetPixel(dc_handle, x, y, color);
    }

    bool bitmap::set_pixel_near(HDC dc_handle,
                                int32_t x,
                                int32_t y,
                                COLORREF color) {
        return SetPixelV(dc_handle, x, y, color);
    }

    StretchMode bitmap::get_stretch_blt_mode(HDC dc_handle) {
        return static_cast<StretchMode>(GetStretchBltMode(dc_handle));
    }

    StretchMode bitmap::set_stretch_blt_mode(HDC dc_handle, StretchMode mode) {
        return static_cast<StretchMode>(
                SetStretchBltMode(dc_handle, static_cast<int32_t>(mode)));
    }

    int32_t bitmap::set_di_bits_to_device(HDC dc_handle,
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
                                          bool use_rgb) {
        return SetDIBitsToDevice(dc_handle, x_dst, y_dst, width, height, x_src,
                                 y_src, start_scan, line_num, bits.data(),
                                 bitmap_info,
                                 use_rgb ? DIB_RGB_COLORS : DIB_PAL_COLORS);
    }
} // namespace YanLib::ui::gdi
