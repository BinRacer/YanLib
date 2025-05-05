//
// Created by forkernel on 2025/4/30.
//

#include "bitmap.h"

namespace YanLib::ui::gdi {
    HBITMAP bitmap::create_bitmap(int32_t width,
                                  int32_t height,
                                  uint32_t planes,
                                  uint32_t bit_count,
                                  const void *bits) {
        return CreateBitmap(width, height, planes, bit_count, bits);
    }

    HBITMAP bitmap::create_bitmap_indirect(const BITMAP *bitmap) {
        return CreateBitmapIndirect(bitmap);
    }

    HBITMAP bitmap::create_compatible_bitmap(HDC dc_handle, int32_t x, int32_t y) {
        return CreateCompatibleBitmap(dc_handle, x, y);
    }

    HBITMAP bitmap::create_di_bitmap(HDC dc_handle,
                                     const BITMAPINFOHEADER *bitmap_info_header,
                                     unsigned long flag,
                                     const void *bits,
                                     const BITMAPINFO *bitmap_info,
                                     uint32_t usage) {
        return CreateDIBitmap(dc_handle,
                              bitmap_info_header,
                              flag,
                              bits,
                              bitmap_info,
                              usage);
    }

    std::pair<HBITMAP, unsigned long> bitmap::create_dib_section(
        HDC dc_handle,
        const BITMAPINFO *bitmap_info,
        uint32_t usage,
        void **bits,
        HANDLE section_handle,
        unsigned long offset) {
        HBITMAP result = CreateDIBSection(dc_handle,
                                          bitmap_info,
                                          usage,
                                          bits,
                                          section_handle,
                                          offset);
        unsigned long error_code = 0;
        if (!result) {
            error_code = GetLastError();
        }
        return std::make_pair(result, error_code);
    }

    HBITMAP bitmap::load_bitmap(HINSTANCE hinstance_handle,
                                const wchar_t *bitmap_name) {
        return LoadBitmapW(hinstance_handle, bitmap_name);
    }

    std::pair<bool, unsigned long> bitmap::bit_blt(HDC dc_handle_dst,
                                           int32_t x,
                                           int32_t y,
                                           int32_t width,
                                           int32_t height,
                                           HDC dc_handle_src,
                                           int32_t x1,
                                           int32_t y1,
                                           unsigned long rop) {
        unsigned long error_code = 0;
        if (!BitBlt(dc_handle_dst,
                    x,
                    y,
                    width,
                    height,
                    dc_handle_src,
                    x1,
                    y1,
                    rop)) {
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
                          unsigned long rop) {
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
                             int32_t x_dst,
                             int32_t y_dst,
                             int32_t width_dst,
                             int32_t height_dst,
                             HDC dc_handle_src,
                             int32_t x_src,
                             int32_t y_src,
                             int32_t width_src,
                             int32_t height_src,
                             unsigned long rop) {
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
                         int32_t x,
                         int32_t y,
                         int32_t width,
                         int32_t height,
                         unsigned long rop) {
        return PatBlt(dc_handle,
                      x,
                      y,
                      width,
                      height,
                      rop);
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
                               unsigned long vertex_num,
                               void *mesh,
                               unsigned long mesh_num,
                               unsigned long mode) {
        return GradientFill(dc_handle,
                            vertex,
                            vertex_num,
                            mesh,
                            mesh_num,
                            mode);
    }

    bool bitmap::ext_flood_fill(HDC dc_handle,
                                int32_t x,
                                int32_t y,
                                COLORREF color,
                                uint32_t type) {
        return ExtFloodFill(dc_handle,
                            x,
                            y,
                            color,
                            type);
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
                                const void *bits,
                                const BITMAPINFO *bitmap_info,
                                uint32_t usage,
                                unsigned long rop) {
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
                                      int32_t width,
                                      int32_t height,
                                      SIZE *size) {
        return SetBitmapDimensionEx(bitmap_handle, width, height, size);
    }

    uint32_t bitmap::get_dib_color_table(HDC dc_handle,
                                     uint32_t start_index,
                                     uint32_t entries,
                                     RGBQUAD *buf) {
        return GetDIBColorTable(dc_handle, start_index, entries, buf);
    }

    uint32_t bitmap::set_dib_color_table(HDC dc_handle,
                                     uint32_t start_index,
                                     uint32_t entries,
                                     const RGBQUAD *buf) {
        return SetDIBColorTable(dc_handle, start_index, entries, buf);
    }

    int32_t bitmap::get_di_bits(HDC dc_handle,
                            HBITMAP bitmap_handle,
                            uint32_t start_line,
                            uint32_t line_num,
                            void *bits,
                            BITMAPINFO *bitmap_info,
                            uint32_t usage) {
        return GetDIBits(dc_handle,
                         bitmap_handle,
                         start_line,
                         line_num,
                         bits,
                         bitmap_info,
                         usage);
    }

    int32_t bitmap::set_di_bits(HDC dc_handle,
                            HBITMAP bitmap_handle,
                            uint32_t start_line,
                            uint32_t line_num,
                            const void *bits,
                            const BITMAPINFO *bitmap_info,
                            uint32_t color_use) {
        return SetDIBits(dc_handle,
                         bitmap_handle,
                         start_line,
                         line_num,
                         bits,
                         bitmap_info,
                         color_use);
    }

    COLORREF bitmap::get_pixel(HDC dc_handle, int32_t x, int32_t y) {
        return GetPixel(dc_handle, x, y);
    }

    COLORREF bitmap::set_pixel(HDC dc_handle, int32_t x, int32_t y, COLORREF color) {
        return SetPixel(dc_handle, x, y, color);
    }

    bool bitmap::set_pixel_near(HDC dc_handle, int32_t x, int32_t y, COLORREF color) {
        return SetPixelV(dc_handle, x, y, color);
    }

    int32_t bitmap::get_stretch_blt_mode(HDC dc_handle) {
        return GetStretchBltMode(dc_handle);
    }

    int32_t bitmap::set_stretch_blt_mode(HDC dc_handle, int32_t mode) {
        return SetStretchBltMode(dc_handle, mode);
    }

    int32_t bitmap::set_di_bits_to_device(HDC dc_handle,
                                      int32_t x_dst,
                                      int32_t y_dst,
                                      unsigned long width,
                                      unsigned long height,
                                      int32_t x_src,
                                      int32_t y_src,
                                      uint32_t start_scan,
                                      uint32_t line_num,
                                      const void *bits,
                                      const BITMAPINFO *bitmap_info,
                                      uint32_t color_use) {
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
