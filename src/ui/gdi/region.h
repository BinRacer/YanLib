//
// Created by forkernel on 2025/5/2.
//

#ifndef REGION_H
#define REGION_H
#include <utility>
#include <Windows.h>
#include <vector>

namespace YanLib::ui::gdi {
class region {
public:
    region(const region &other)            = delete;

    region(region &&other)                 = delete;

    region &operator=(const region &other) = delete;

    region &operator=(region &&other)      = delete;

    region()                               = default;

    ~region()                              = default;

    static HRGN
    create_rect_region(int32_t x1, int32_t y1, int32_t x2, int32_t y2);

    static HRGN create_rect_region_indirect(const RECT *rect);

    static HRGN create_round_rect_region(int32_t x1,
        int32_t                                  y1,
        int32_t                                  x2,
        int32_t                                  y2,
        int32_t                                  width,
        int32_t                                  height);

    static HRGN
    create_elliptic_region(int32_t x1, int32_t y1, int32_t x2, int32_t y2);

    static HRGN create_elliptic_region_indirect(const RECT *rect);

    static HRGN create_polygon_region(const std::vector<POINT> &point,
        int32_t                                                 mode);

    static HRGN create_poly_polygon_region(const std::vector<POINT> &point,
        const std::vector<int32_t>                                  &poly_count,
        int32_t                                                      mode);

    static bool
    fill_region(HDC dc_handle, HRGN region_handle, HBRUSH brush_handle);

    static HRGN
    ext_create_region(const XFORM *xfrom, uint32_t size, const RGNDATA *buf);

    static bool frame_region(HDC dc_handle,
        HRGN                     region_handle,
        HBRUSH                   brush_handle,
        int32_t                  width,
        int32_t                  height);

    static int32_t combine_region(HRGN region_handle_dst,
        HRGN                           region_handle_src1,
        HRGN                           region_handle_src2,
        int32_t                        mode);

    static bool equal_region(HRGN region_handle1, HRGN region_handle2);

    static bool invert_region(HDC dc_handle, HRGN region_handle);

    static int32_t offset_region(HRGN region_handle, int32_t x, int32_t y);

    static bool paint_region(HDC dc_handle, HRGN region_handle);

    static bool point_in_region(HRGN region_handle, int32_t x, int32_t y);

    static bool rect_in_region(HRGN region_handle, const RECT *rect);

    static int32_t get_poly_fill_mode(HDC dc_handle);

    static int32_t set_poly_fill_mode(HDC dc_handle, int32_t mode);

    static bool set_rect_region(HRGN region_handle,
        int32_t                      left,
        int32_t                      top,
        int32_t                      right,
        int32_t                      bottom);

    static int32_t get_region_box(HRGN region_handle, RECT *rect);

    static int32_t
    get_update_region(HWND hwnd, HRGN region_handle, bool is_erase);

    static bool validate_region(HWND hwnd, HRGN region_handle);

    static bool invalidate_region(HWND hwnd, HRGN region_handle, bool is_erase);

    static int32_t exclude_update_region(HDC dc_handle, HWND hwnd);

    // std::pair<result, error_code>
    static std::pair<uint32_t, uint32_t>
    get_region_data(HRGN region_handle, uint32_t size, RGNDATA *buf);
};
} // namespace YanLib::ui::gdi
#endif // REGION_H
