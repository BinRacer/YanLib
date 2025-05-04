//
// Created by forkernel on 2025/5/2.
//

#include "region.h"

namespace YanLib::ui::gdi {
    HRGN region::create_rect_region(int x1, int y1, int x2, int y2) {
        return CreateRectRgn(x1, y1, x2, y2);
    }

    HRGN region::create_rect_region_indirect(const RECT *rect) {
        return CreateRectRgnIndirect(rect);
    }

    HRGN region::create_round_rect_region(int x1,
                                          int y1,
                                          int x2,
                                          int y2,
                                          int w,
                                          int h) {
        return CreateRoundRectRgn(x1, y1, x2, y2, w, h);
    }

    HRGN region::create_elliptic_region(int x1, int y1, int x2, int y2) {
        return CreateEllipticRgn(x1, y1, x2, y2);
    }

    HRGN region::create_elliptic_region_indirect(const RECT *rect) {
        return CreateEllipticRgnIndirect(rect);
    }

    HRGN region::create_polygon_region(const POINT *points,
                                       int points_count,
                                       int mode) {
        return CreatePolygonRgn(points, points_count, mode);
    }

    HRGN region::create_poly_polygon_region(const POINT *points,
                                            const INT *points_num,
                                            int poly_count,
                                            int mode) {
        return CreatePolyPolygonRgn(points, points_num, poly_count, mode);
    }

    bool region::fill_region(HDC dc_handle,
                             HRGN region_handle,
                             HBRUSH brush_handle) {
        return FillRgn(dc_handle, region_handle, brush_handle);
    }

    HRGN region::ext_create_region(const XFORM *xfrom,
                                   DWORD size,
                                   const RGNDATA *buf) {
        return ExtCreateRegion(xfrom, size, buf);
    }

    bool region::frame_region(HDC dc_handle,
                              HRGN region_handle,
                              HBRUSH brush_handle,
                              int w,
                              int h) {
        return FrameRgn(dc_handle, region_handle, brush_handle, w, h);
    }

    int region::combine_region(HRGN region_handle_dst,
                               HRGN region_handle_src1,
                               HRGN region_handle_src2,
                               int mode) {
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

    int region::offset_region(HRGN region_handle, int x, int y) {
        return OffsetRgn(region_handle, x, y);
    }

    bool region::paint_region(HDC dc_handle, HRGN region_handle) {
        return PaintRgn(dc_handle, region_handle);
    }

    bool region::point_in_region(HRGN region_handle, int x, int y) {
        return PtInRegion(region_handle, x, y);
    }

    bool region::rect_in_region(HRGN region_handle, const RECT *rect) {
        return RectInRegion(region_handle, rect);
    }

    int region::get_poly_fill_mode(HDC dc_handle) {
        return GetPolyFillMode(dc_handle);
    }

    int region::set_poly_fill_mode(HDC dc_handle, int mode) {
        return SetPolyFillMode(dc_handle, mode);
    }

    BOOL region::set_rect_region(HRGN region_handle,
                                 int left,
                                 int top,
                                 int right,
                                 int bottom) {
        return SetRectRgn(region_handle, left, top, right, bottom);
    }

    int region::get_region_box(HRGN region_handle, RECT *rect) {
        return GetRgnBox(region_handle, rect);
    }

    int region::get_update_region(HWND hwnd, HRGN region_handle, bool is_erase) {
        return GetUpdateRgn(hwnd, region_handle, is_erase ? TRUE : FALSE);
    }

    bool region::validate_region(HWND hwnd, HRGN region_handle) {
        return ValidateRgn(hwnd, region_handle);
    }

    bool region::invalidate_region(HWND hwnd, HRGN region_handle, bool is_erase) {
        return InvalidateRgn(hwnd, region_handle, is_erase ? TRUE : FALSE);
    }

    int region::exclude_update_region(HDC dc_handle, HWND hwnd) {
        return ExcludeUpdateRgn(dc_handle, hwnd);
    }
}
