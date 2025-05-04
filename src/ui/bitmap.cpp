//
// Created by forkernel on 2025/4/30.
//

#include "bitmap.h"

namespace YanLib::ui {
    HBITMAP bitmap::create_bitmap(int width,
                                  int height,
                                  UINT planes,
                                  UINT bit_count,
                                  const void *bits) {
        return CreateBitmap(width, height, planes, bit_count, bits);
    }

    HBITMAP bitmap::create_bitmap_indirect(const BITMAP *bitmap) {
        return CreateBitmapIndirect(bitmap);
    }

    HBITMAP bitmap::create_compatible_bitmap(HDC dc_handle, int x, int y) {
        return CreateCompatibleBitmap(dc_handle, x, y);
    }

    HBITMAP bitmap::create_di_bitmap(HDC dc_handle,
                                     const BITMAPINFOHEADER *bitmap_info_header,
                                     DWORD flag,
                                     const void *bits,
                                     const BITMAPINFO *bitmap_info,
                                     UINT usage) {
        return CreateDIBitmap(dc_handle,
                              bitmap_info_header,
                              flag,
                              bits,
                              bitmap_info,
                              usage);
    }

    HBITMAP bitmap::create_dib_section(HDC dc_handle,
                                       const BITMAPINFO *bitmap_info,
                                       UINT usage,
                                       void **bits,
                                       HANDLE section_handle,
                                       DWORD offset) {
        return CreateDIBSection(dc_handle,
                                bitmap_info,
                                usage,
                                bits,
                                section_handle,
                                offset);
    }

    HBITMAP bitmap::load_bitmap(HINSTANCE hinstance_handle,
                                const wchar_t *bitmap_name) {
        return LoadBitmapW(hinstance_handle, bitmap_name);
    }

    bool bitmap::bit_blt(HDC dc_handle_dst,
                         int x,
                         int y,
                         int width,
                         int height,
                         HDC dc_handle_src,
                         int x1,
                         int y1,
                         DWORD rop) {
        return BitBlt(dc_handle_dst,
                      x,
                      y,
                      width,
                      height,
                      dc_handle_src,
                      x1,
                      y1,
                      rop);
    }

    bool bitmap::plg_blt(HDC dc_handle_dst,
                         const POINT *point,
                         HDC dc_handle_src,
                         int x_src,
                         int y_src,
                         int width,
                         int height,
                         HBITMAP bitmap_mask_handle,
                         int x_mask,
                         int y_mask) {
        return PlgBlt(dc_handle_dst,
                      point,
                      dc_handle_src,
                      x_src,
                      y_src,
                      width,
                      height,
                      bitmap_mask_handle,
                      x_mask,
                      y_mask);
    }

    bool bitmap::mask_blt(HDC dc_handle_dst,
                          int x_dst,
                          int y_dst,
                          int width,
                          int height,
                          HDC dc_handle_src,
                          int x_src,
                          int y_src,
                          HBITMAP bitmap_mask_handle,
                          int x_mask,
                          int y_mask,
                          DWORD rop) {
        return MaskBlt(dc_handle_dst,
                       x_dst,
                       y_dst,
                       width,
                       height,
                       dc_handle_src,
                       x_src,
                       y_src,
                       bitmap_mask_handle,
                       x_mask,
                       y_mask,
                       rop);
    }

    bool bitmap::stretch_blt(HDC dc_handle_dst,
                             int x_dst,
                             int y_dst,
                             int width_dst,
                             int height_dst,
                             HDC dc_handle_src,
                             int x_src,
                             int y_src,
                             int width_src,
                             int height_src,
                             DWORD rop) {
        return StretchBlt(dc_handle_dst,
                          x_dst,
                          y_dst,
                          width_dst,
                          height_dst,
                          dc_handle_src,
                          x_src,
                          y_src,
                          width_src,
                          height_src,
                          rop);
    }

    bool bitmap::pat_blt(HDC dc_handle,
                         int x,
                         int y,
                         int width,
                         int height,
                         DWORD rop) {
        return PatBlt(dc_handle,
                      x,
                      y,
                      width,
                      height,
                      rop);
    }

    bool bitmap::transparent_blt(HDC dc_handle_dst,
                                 int x_dst,
                                 int y_dst,
                                 int width_dst,
                                 int height_dst,
                                 HDC dc_handle_src,
                                 int x_src,
                                 int y_src,
                                 int width_src,
                                 int height_src,
                                 UINT transparent) {
        return TransparentBlt(dc_handle_dst,
                              x_dst,
                              y_dst,
                              width_dst,
                              height_dst,
                              dc_handle_src,
                              x_src,
                              y_src,
                              width_src,
                              height_src,
                              transparent);
    }

    bool bitmap::gradient_fill(HDC dc_handle,
                               TRIVERTEX *vertex,
                               ULONG vertex_num,
                               void *mesh,
                               ULONG mesh_num,
                               ULONG mode) {
        return GradientFill(dc_handle,
                            vertex,
                            vertex_num,
                            mesh,
                            mesh_num,
                            mode);
    }

    bool bitmap::ext_flood_fill(HDC dc_handle,
                                int x,
                                int y,
                                COLORREF color,
                                UINT type) {
        return ExtFloodFill(dc_handle,
                            x,
                            y,
                            color,
                            type);
    }

    int bitmap::stretch_di_bits(HDC dc_handle,
                                int x_dst,
                                int y_dst,
                                int width_dst,
                                int height_dst,
                                int x_src,
                                int y_src,
                                int width_src,
                                int height_src,
                                const void *bits,
                                const BITMAPINFO *bitmap_info,
                                UINT usage,
                                DWORD rop) {
        return StretchDIBits(dc_handle,
                             x_dst,
                             y_dst,
                             width_dst,
                             height_dst,
                             x_src,
                             y_src,
                             width_src,
                             height_src,
                             bits,
                             bitmap_info,
                             usage,
                             rop);
    }

    bool bitmap::alpha_blend(HDC dc_handle_dst,
                             int x_dst,
                             int y_dst,
                             int width_dst,
                             int height_dst,
                             HDC dc_handle_src,
                             int x_src,
                             int y_src,
                             int width_src,
                             int height_src,
                             BLENDFUNCTION blend_function) {
        return AlphaBlend(dc_handle_dst,
                          x_dst,
                          y_dst,
                          width_dst,
                          height_dst,
                          dc_handle_src,
                          x_src,
                          y_src,
                          width_src,
                          height_src,
                          blend_function);
    }

    bool bitmap::get_bitmap_dimension(HBITMAP bitmap_handle, SIZE *size) {
        return GetBitmapDimensionEx(bitmap_handle, size);
    }

    bool bitmap::set_bitmap_dimension(HBITMAP bitmap_handle,
                                      int width,
                                      int height,
                                      SIZE *size) {
        return SetBitmapDimensionEx(bitmap_handle, width, height, size);
    }

    UINT bitmap::get_dib_color_table(HDC dc_handle,
                                     UINT start_index,
                                     UINT entries,
                                     RGBQUAD *buf) {
        return GetDIBColorTable(dc_handle, start_index, entries, buf);
    }

    UINT bitmap::set_dib_color_table(HDC dc_handle,
                                     UINT start_index,
                                     UINT entries,
                                     const RGBQUAD *buf) {
        return SetDIBColorTable(dc_handle, start_index, entries, buf);
    }

    int bitmap::get_di_bits(HDC dc_handle,
                            HBITMAP bitmap_handle,
                            UINT start_line,
                            UINT line_num,
                            void *bits,
                            BITMAPINFO *bitmap_info,
                            UINT usage) {
        return GetDIBits(dc_handle,
                         bitmap_handle,
                         start_line,
                         line_num,
                         bits,
                         bitmap_info,
                         usage);
    }

    int bitmap::set_di_bits(HDC dc_handle,
                            HBITMAP bitmap_handle,
                            UINT start_line,
                            UINT line_num,
                            const void *bits,
                            const BITMAPINFO *bitmap_info,
                            UINT color_use) {
        return SetDIBits(dc_handle,
                         bitmap_handle,
                         start_line,
                         line_num,
                         bits,
                         bitmap_info,
                         color_use);
    }

    COLORREF bitmap::get_pixel(HDC dc_handle, int x, int y) {
        return GetPixel(dc_handle, x, y);
    }

    COLORREF bitmap::set_pixel(HDC dc_handle, int x, int y, COLORREF color) {
        return SetPixel(dc_handle, x, y, color);
    }

    bool bitmap::set_pixel_near(HDC dc_handle, int x, int y, COLORREF color) {
        return SetPixelV(dc_handle, x, y, color);
    }

    int bitmap::get_stretch_blt_mode(HDC dc_handle) {
        return GetStretchBltMode(dc_handle);
    }

    int bitmap::set_stretch_blt_mode(HDC dc_handle, int mode) {
        return SetStretchBltMode(dc_handle, mode);
    }

    int bitmap::set_di_bits_to_device(HDC dc_handle,
                                      int x_dst,
                                      int y_dst,
                                      DWORD width,
                                      DWORD height,
                                      int x_src,
                                      int y_src,
                                      UINT start_scan,
                                      UINT line_num,
                                      const void *bits,
                                      const BITMAPINFO *bitmap_info,
                                      UINT color_use) {
        return SetDIBitsToDevice(dc_handle,
                                 x_dst,
                                 y_dst,
                                 width,
                                 height,
                                 x_src,
                                 y_src,
                                 start_scan,
                                 line_num,
                                 bits,
                                 bitmap_info,
                                 color_use);
    }
}
