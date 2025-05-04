//
// Created by forkernel on 2025/4/30.
//

#ifndef BITMAP_H
#define BITMAP_H
#include <Windows.h>

namespace YanLib::ui {
    class bitmap {
    public:
        bitmap(const bitmap &other) = delete;

        bitmap(bitmap &&other) = delete;

        bitmap &operator=(const bitmap &other) = delete;

        bitmap &operator=(bitmap &&other) = delete;

        bitmap() = default;

        ~bitmap() = default;

        static HBITMAP create_bitmap(int width,
                                     int height,
                                     UINT planes,
                                     UINT bit_count,
                                     const void *bits);

        static HBITMAP create_bitmap_indirect(const BITMAP *bitmap);

        static HBITMAP create_compatible_bitmap(HDC dc_handle, int x, int y);

        static HBITMAP create_di_bitmap(HDC dc_handle,
                                        const BITMAPINFOHEADER *bitmap_info_header,
                                        DWORD flag,
                                        const void *bits,
                                        const BITMAPINFO *bitmap_info,
                                        UINT usage);

        // need to call GetLastError() to get error details
        static HBITMAP create_dib_section(HDC dc_handle,
                                          const BITMAPINFO *bitmap_info,
                                          UINT usage,
                                          void **bits,
                                          HANDLE section_handle,
                                          DWORD offset);

        static HBITMAP load_bitmap(HINSTANCE hinstance_handle,
                                   const wchar_t *bitmap_name);

        // need to call GetLastError() to get error details
        static bool bit_blt(HDC dc_handle_dst,
                            int x,
                            int y,
                            int width,
                            int height,
                            HDC dc_handle_src,
                            int x1,
                            int y1,
                            DWORD rop);

        static bool plg_blt(HDC dc_handle_dst,
                            const POINT *point,
                            HDC dc_handle_src,
                            int x_src,
                            int y_src,
                            int width,
                            int height,
                            HBITMAP bitmap_mask_handle,
                            int x_mask,
                            int y_mask);

        static bool mask_blt(HDC dc_handle_dst,
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
                             DWORD rop);

        static bool stretch_blt(HDC dc_handle_dst,
                                int x_dst,
                                int y_dst,
                                int width_dst,
                                int height_dst,
                                HDC dc_handle_src,
                                int x_src,
                                int y_src,
                                int width_src,
                                int height_src,
                                DWORD rop);

        static bool pat_blt(HDC dc_handle,
                            int x,
                            int y,
                            int width,
                            int height,
                            DWORD rop);

        static bool transparent_blt(HDC dc_handle_dst,
                                    int x_dst,
                                    int y_dst,
                                    int width_dst,
                                    int height_dst,
                                    HDC dc_handle_src,
                                    int x_src,
                                    int y_src,
                                    int width_src,
                                    int height_src,
                                    UINT transparent);

        static bool gradient_fill(HDC dc_handle,
                                  TRIVERTEX *vertex,
                                  ULONG vertex_num,
                                  void *mesh,
                                  ULONG mesh_num,
                                  ULONG mode);

        static bool ext_flood_fill(HDC dc_handle,
                                   int x,
                                   int y,
                                   COLORREF color,
                                   UINT type);

        static int stretch_di_bits(HDC dc_handle,
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
                                   DWORD rop);

        static bool alpha_blend(HDC dc_handle_dst,
                                int x_dst,
                                int y_dst,
                                int width_dst,
                                int height_dst,
                                HDC dc_handle_src,
                                int x_src,
                                int y_src,
                                int width_src,
                                int height_src,
                                BLENDFUNCTION blend_function);

        static bool get_bitmap_dimension(HBITMAP bitmap_handle, SIZE *size);

        static bool set_bitmap_dimension(HBITMAP bitmap_handle,
                                         int width,
                                         int height,
                                         SIZE *size);

        static UINT get_dib_color_table(HDC dc_handle,
                                        UINT start_index,
                                        UINT entries,
                                        RGBQUAD *buf);

        static UINT set_dib_color_table(HDC dc_handle,
                                        UINT start_index,
                                        UINT entries,
                                        const RGBQUAD *buf);

        static int get_di_bits(HDC dc_handle,
                               HBITMAP bitmap_handle,
                               UINT start_line,
                               UINT line_num,
                               void *bits,
                               BITMAPINFO *bitmap_info,
                               UINT usage);

        static int set_di_bits(HDC dc_handle,
                               HBITMAP bitmap_handle,
                               UINT start_line,
                               UINT line_num,
                               const void *bits,
                               const BITMAPINFO *bitmap_info,
                               UINT color_use);

        static COLORREF get_pixel(HDC dc_handle, int x, int y);

        static COLORREF set_pixel(HDC dc_handle, int x, int y, COLORREF color);

        static bool set_pixel_near(HDC dc_handle, int x, int y, COLORREF color);

        static int get_stretch_blt_mode(HDC dc_handle);

        static int set_stretch_blt_mode(HDC dc_handle, int mode);

        static int set_di_bits_to_device(HDC dc_handle,
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
                                         UINT color_use);
    };
}
#endif //BITMAP_H
