//
// Created by forkernel on 2025/5/2.
//

#ifndef REGION_H
#define REGION_H
#include <Windows.h>

namespace YanLib::ui::gdi {
    class region {
    public:
        region(const region &other) = delete;

        region(region &&other) = delete;

        region &operator=(const region &other) = delete;

        region &operator=(region &&other) = delete;

        region() = default;

        ~region() = default;

        static HRGN create_rect_region(int x1, int y1, int x2, int y2);

        static HRGN create_rect_region_indirect(const RECT *rect);

        static HRGN create_round_rect_region(int x1,
                                             int y1,
                                             int x2,
                                             int y2,
                                             int w,
                                             int h);

        static HRGN create_elliptic_region(int x1, int y1, int x2, int y2);

        static HRGN create_elliptic_region_indirect(const RECT *rect);

        static HRGN create_polygon_region(const POINT *points,
                                          int points_count,
                                          int mode);

        static HRGN create_poly_polygon_region(const POINT *points,
                                               const INT *points_num,
                                               int poly_count,
                                               int mode);

        static bool fill_region(HDC dc_handle,
                                HRGN region_handle,
                                HBRUSH brush_handle);

        static HRGN ext_create_region(const XFORM *xfrom,
                                      DWORD size,
                                      const RGNDATA *buf);

        static bool frame_region(HDC dc_handle,
                                 HRGN region_handle,
                                 HBRUSH brush_handle,
                                 int w,
                                 int h);

        static int combine_region(HRGN region_handle_dst,
                                  HRGN region_handle_src1,
                                  HRGN region_handle_src2,
                                  int mode);

        static bool equal_region(HRGN region_handle1, HRGN region_handle2);

        static bool invert_region(HDC dc_handle, HRGN region_handle);

        static int offset_region(HRGN region_handle, int x, int y);

        static bool paint_region(HDC dc_handle, HRGN region_handle);

        static bool point_in_region(HRGN region_handle, int x, int y);

        static bool rect_in_region(HRGN region_handle, const RECT *rect);

        static int get_poly_fill_mode(HDC dc_handle);

        static int set_poly_fill_mode(HDC dc_handle, int mode);

        static BOOL set_rect_region(HRGN region_handle,
                                    int left,
                                    int top,
                                    int right,
                                    int bottom);

        static int get_region_box(HRGN region_handle, RECT* rect);

        static int get_update_region(HWND hwnd, HRGN region_handle, bool is_erase);

        static bool validate_region(HWND hwnd, HRGN region_handle);

        static bool invalidate_region(HWND hwnd, HRGN region_handle, bool is_erase);

        static int exclude_update_region(HDC dc_handle, HWND hwnd);
    };
}
#endif //REGION_H
