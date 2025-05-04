//
// Created by forkernel on 2025/5/4.
//

#include "clip.h"

#include "brush.h"

namespace YanLib::ui {
    bool clip::select_clip_path(HDC dc_handle, int mode) {
        return SelectClipPath(dc_handle, mode);
    }

    int clip::select_clip_region(HDC dc_handle, HRGN region_handle) {
        return SelectClipRgn(dc_handle, region_handle);
    }

    int clip::select_clip_region(HDC dc_handle, HRGN region_handle, int mode) {
        return ExtSelectClipRgn(dc_handle, region_handle, mode);
    }

    int clip::exclude_clip_rect(HDC dc_handle,
                                int left,
                                int top,
                                int right,
                                int bottom) {
        return ExcludeClipRect(dc_handle, left, top, right, bottom);
    }

    int clip::intersect_clip_rect(HDC dc_handle,
                                  int left,
                                  int top,
                                  int right,
                                  int bottom) {
        return IntersectClipRect(dc_handle, left, top, right, bottom);
    }

    int clip::offset_clip_region(HDC dc_handle, int x, int y) {
        return OffsetClipRgn(dc_handle, x, y);
    }

    bool clip::rect_visible(HDC dc_handle, const RECT *rect) {
        return RectVisible(dc_handle, rect);
    }

    bool clip::point_visible(HDC dc_handle, int x, int y) {
        return PtVisible(dc_handle, x, y);
    }

    int clip::get_clip_box(HDC dc_handle, RECT *rect) {
        return GetClipBox(dc_handle, rect);
    }

    int clip::get_clip_region(HDC dc_handle, HRGN region_handle) {
        return GetClipRgn(dc_handle, region_handle);
    }

    int clip::get_meta_region(HDC dc_handle, HRGN region_handle) {
        return GetMetaRgn(dc_handle, region_handle);
    }

    int clip::set_meta_region(HDC dc_handle) {
        return SetMetaRgn(dc_handle);
    }

    int clip::get_random_region(HDC dc_handle, HRGN region_handle) {
        return GetRandomRgn(dc_handle, region_handle, SYSRGN);
    }
}
