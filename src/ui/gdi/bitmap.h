//
// Created by forkernel on 2025/4/30.
//

#ifndef BITMAP_H
#define BITMAP_H
#include <utility>
#include <Windows.h>

namespace YanLib::ui::gdi {
    class bitmap {
    public:
        bitmap(const bitmap &other) = delete;

        bitmap(bitmap &&other) = delete;

        bitmap &operator=(const bitmap &other) = delete;

        bitmap &operator=(bitmap &&other) = delete;

        bitmap() = default;

        ~bitmap() = default;

        static HBITMAP create_bitmap(int32_t width,
                                     int32_t height,
                                     uint32_t planes,
                                     uint32_t bit_count,
                                     const void *bits);

        static HBITMAP create_bitmap_indirect(const BITMAP *bitmap);

        static HBITMAP create_compatible_bitmap(HDC dc_handle, int32_t x, int32_t y);

        static HBITMAP create_di_bitmap(HDC dc_handle,
                                        const BITMAPINFOHEADER *bitmap_info_header,
                                        unsigned long flag,
                                        const void *bits,
                                        const BITMAPINFO *bitmap_info,
                                        uint32_t usage);

        // std::pair<result, error_code>
        static std::pair<HBITMAP, unsigned long> create_dib_section(
            HDC dc_handle,
            const BITMAPINFO *bitmap_info,
            uint32_t usage,
            void **bits,
            HANDLE section_handle,
            unsigned long offset);

        static HBITMAP load_bitmap(HINSTANCE hinstance_handle,
                                   const wchar_t *bitmap_name);

        // std::pair<result, error_code>
        static std::pair<bool, unsigned long> bit_blt(HDC dc_handle_dst,
                                              int32_t x,
                                              int32_t y,
                                              int32_t width,
                                              int32_t height,
                                              HDC dc_handle_src,
                                              int32_t x1,
                                              int32_t y1,
                                              unsigned long rop);

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
                             unsigned long rop);

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
                                unsigned long rop);

        static bool pat_blt(HDC dc_handle,
                            int32_t x,
                            int32_t y,
                            int32_t width,
                            int32_t height,
                            unsigned long rop);

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
                                  TRIVERTEX *vertex,
                                  unsigned long vertex_num,
                                  void *mesh,
                                  unsigned long mesh_num,
                                  unsigned long mode);

        static bool ext_flood_fill(HDC dc_handle,
                                   int32_t x,
                                   int32_t y,
                                   COLORREF color,
                                   uint32_t type);

        static int32_t stretch_di_bits(HDC dc_handle,
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
                                   unsigned long rop);

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
                                        uint32_t start_index,
                                        uint32_t entries,
                                        RGBQUAD *buf);

        static uint32_t set_dib_color_table(HDC dc_handle,
                                        uint32_t start_index,
                                        uint32_t entries,
                                        const RGBQUAD *buf);

        static int32_t get_di_bits(HDC dc_handle,
                               HBITMAP bitmap_handle,
                               uint32_t start_line,
                               uint32_t line_num,
                               void *bits,
                               BITMAPINFO *bitmap_info,
                               uint32_t usage);

        static int32_t set_di_bits(HDC dc_handle,
                               HBITMAP bitmap_handle,
                               uint32_t start_line,
                               uint32_t line_num,
                               const void *bits,
                               const BITMAPINFO *bitmap_info,
                               uint32_t color_use);

        static COLORREF get_pixel(HDC dc_handle, int32_t x, int32_t y);

        static COLORREF set_pixel(HDC dc_handle, int32_t x, int32_t y, COLORREF color);

        static bool set_pixel_near(HDC dc_handle, int32_t x, int32_t y, COLORREF color);

        static int32_t get_stretch_blt_mode(HDC dc_handle);

        static int32_t set_stretch_blt_mode(HDC dc_handle, int32_t mode);

        static int32_t set_di_bits_to_device(HDC dc_handle,
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
                                         uint32_t color_use);
    };
}
#endif //BITMAP_H
