//
// Created by forkernel on 2025/5/2.
//

#include "region.h"

namespace YanLib::ui::gdi {
    HRGN region::create_rect_region(int32_t x1, int32_t y1, int32_t x2, int32_t y2) {
        return CreateRectRgn(x1, y1, x2, y2);
    }

    HRGN region::create_rect_region_indirect(const RECT *rect) {
        return CreateRectRgnIndirect(rect);
    }

    HRGN region::create_round_rect_region(int32_t x1,
                                          int32_t y1,
                                          int32_t x2,
                                          int32_t y2,
                                          int32_t w,
                                          int32_t h) {
        return CreateRoundRectRgn(x1, y1, x2, y2, w, h);
    }

    HRGN region::create_elliptic_region(int32_t x1, int32_t y1, int32_t x2, int32_t y2) {
        return CreateEllipticRgn(x1, y1, x2, y2);
    }

    HRGN region::create_elliptic_region_indirect(const RECT *rect) {
        return CreateEllipticRgnIndirect(rect);
    }

    HRGN region::create_polygon_region(const POINT *points,
                                       int32_t points_count,
                                       int32_t mode) {
        return CreatePolygonRgn(points, points_count, mode);
    }

    HRGN region::create_poly_polygon_region(const POINT *points,
                                            const int32_t *points_num,
                                            int32_t poly_count,
                                            int32_t mode) {
        return CreatePolyPolygonRgn(points, points_num, poly_count, mode);
    }

    bool region::fill_region(HDC dc_handle,
                             HRGN region_handle,
                             HBRUSH brush_handle) {
        return FillRgn(dc_handle, region_handle, brush_handle);
    }

    HRGN region::ext_create_region(const XFORM *xfrom,
                                   unsigned long size,
                                   const RGNDATA *buf) {
        return ExtCreateRegion(xfrom, size, buf);
    }

    bool region::frame_region(HDC dc_handle,
                              HRGN region_handle,
                              HBRUSH brush_handle,
                              int32_t w,
                              int32_t h) {
        return FrameRgn(dc_handle, region_handle, brush_handle, w, h);
    }

    int32_t region::combine_region(HRGN region_handle_dst,
                               HRGN region_handle_src1,
                               HRGN region_handle_src2,
                               int32_t mode) {
        return CombineRgn(region_handle_dst,
                          region_handle_src1,
                          region_handle_src2,
                          mode);
    }

    bool region::equal_region(HRGN region_handle1, HRGN region_handle2) {
        return EqualRgn(region_handle1, region_handle2);
    }

    bool region::invert_region(HDC dc_handle, HRGN region_handle) {
        return InvertRgn(dc_handle, region_handle);
    }

    int32_t region::offset_region(HRGN region_handle, int32_t x, int32_t y) {
        return OffsetRgn(region_handle, x, y);
    }

    bool region::paint_region(HDC dc_handle, HRGN region_handle) {
        return PaintRgn(dc_handle, region_handle);
    }

    bool region::point_in_region(HRGN region_handle, int32_t x, int32_t y) {
        return PtInRegion(region_handle, x, y);
    }

    bool region::rect_in_region(HRGN region_handle, const RECT *rect) {
        return RectInRegion(region_handle, rect);
    }

    int32_t region::get_poly_fill_mode(HDC dc_handle) {
        return GetPolyFillMode(dc_handle);
    }

    int32_t region::set_poly_fill_mode(HDC dc_handle, int32_t mode) {
        return SetPolyFillMode(dc_handle, mode);
    }

    BOOL region::set_rect_region(HRGN region_handle,
                                 int32_t left,
                                 int32_t top,
                                 int32_t right,
                                 int32_t bottom) {
        return SetRectRgn(region_handle, left, top, right, bottom);
    }

    int32_t region::get_region_box(HRGN region_handle, RECT *rect) {
        return GetRgnBox(region_handle, rect);
    }

    int32_t region::get_update_region(HWND hwnd, HRGN region_handle, bool is_erase) {
        return GetUpdateRgn(hwnd, region_handle, is_erase ? TRUE : FALSE);
    }

    bool region::validate_region(HWND hwnd, HRGN region_handle) {
        return ValidateRgn(hwnd, region_handle);
    }

    bool region::invalidate_region(HWND hwnd, HRGN region_handle, bool is_erase) {
        return InvalidateRgn(hwnd, region_handle, is_erase ? TRUE : FALSE);
    }

    int32_t region::exclude_update_region(HDC dc_handle, HWND hwnd) {
        return ExcludeUpdateRgn(dc_handle, hwnd);
    }

    std::pair<unsigned long, unsigned long> region::get_region_data(HRGN region_handle,
                                                                    unsigned long size,
                                                                    RGNDATA *buf) {
        unsigned long result = GetRegionData(region_handle, size, buf);
        unsigned long error_code = 0;
        if (!result) {
            error_code = GetLastError();
        }
        return std::make_pair(result, error_code);
    }
}
