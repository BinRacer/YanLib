//
// Created by forkernel on 2025/5/4.
//

#include "clip.h"

namespace YanLib::ui::gdi {
    bool clip::select_clip_path(HDC dc_handle, int32_t mode) {
        return SelectClipPath(dc_handle, mode);
    }

    int32_t clip::select_clip_region(HDC dc_handle, HRGN region_handle) {
        return SelectClipRgn(dc_handle, region_handle);
    }

    int32_t clip::select_clip_region(HDC dc_handle, HRGN region_handle, int32_t mode) {
        return ExtSelectClipRgn(dc_handle, region_handle, mode);
    }

    int32_t clip::exclude_clip_rect(HDC dc_handle,
                                int32_t left,
                                int32_t top,
                                int32_t right,
                                int32_t bottom) {
        return ExcludeClipRect(dc_handle, left, top, right, bottom);
    }

    int32_t clip::intersect_clip_rect(HDC dc_handle,
                                  int32_t left,
                                  int32_t top,
                                  int32_t right,
                                  int32_t bottom) {
        return IntersectClipRect(dc_handle, left, top, right, bottom);
    }

    int32_t clip::offset_clip_region(HDC dc_handle, int32_t x, int32_t y) {
        return OffsetClipRgn(dc_handle, x, y);
    }

    bool clip::rect_visible(HDC dc_handle, const RECT *rect) {
        int32_t is_ok = RectVisible(dc_handle, rect);
        return is_ok == TRUE || is_ok == 2;
    }

    bool clip::point_visible(HDC dc_handle, int32_t x, int32_t y) {
        int32_t is_ok = PtVisible(dc_handle, x, y);
        return is_ok == TRUE;
    }

    int32_t clip::get_clip_box(HDC dc_handle, RECT *rect) {
        return GetClipBox(dc_handle, rect);
    }

    int32_t clip::get_clip_region(HDC dc_handle, HRGN region_handle) {
        return GetClipRgn(dc_handle, region_handle);
    }

    int32_t clip::get_meta_region(HDC dc_handle, HRGN region_handle) {
        return GetMetaRgn(dc_handle, region_handle);
    }

    int32_t clip::set_meta_region(HDC dc_handle) {
        return SetMetaRgn(dc_handle);
    }

    int32_t clip::get_random_region(HDC dc_handle, HRGN region_handle) {
        return GetRandomRgn(dc_handle, region_handle, SYSRGN);
    }
}
