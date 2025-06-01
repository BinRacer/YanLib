//
// Created by forkernel on 2025/5/4.
//

#include "clip.h"

namespace YanLib::ui::gdi {
    bool clip::select_region(HDC dc_handle, RegionStyle style) {
        return SelectClipPath(dc_handle, static_cast<int32_t>(style));
    }

    RegionFlag clip::select_region(HDC dc_handle, HRGN region_handle) {
        return static_cast<RegionFlag>(SelectClipRgn(dc_handle, region_handle));
    }

    RegionFlag
    clip::select_region(HDC dc_handle, HRGN region_handle, RegionStyle style) {
        return static_cast<RegionFlag>(
                ExtSelectClipRgn(dc_handle, region_handle,
                                 static_cast<int32_t>(style)));
    }

    RegionFlag clip::exclude_rect(HDC dc_handle,
                                  int32_t left,
                                  int32_t top,
                                  int32_t right,
                                  int32_t bottom) {
        return static_cast<RegionFlag>(
                ExcludeClipRect(dc_handle, left, top, right, bottom));
    }

    RegionFlag clip::intersect_rect(HDC dc_handle,
                                    int32_t left,
                                    int32_t top,
                                    int32_t right,
                                    int32_t bottom) {
        return static_cast<RegionFlag>(
                IntersectClipRect(dc_handle, left, top, right, bottom));
    }

    RegionFlag clip::offset_region(HDC dc_handle, int32_t x, int32_t y) {
        return static_cast<RegionFlag>(OffsetClipRgn(dc_handle, x, y));
    }

    bool clip::contains(HDC dc_handle, const RECT *rect) {
        int32_t is_ok = RectVisible(dc_handle, rect);
        return is_ok == TRUE || is_ok == 2;
    }

    bool clip::contains(HDC dc_handle, int32_t x, int32_t y) {
        int32_t is_ok = PtVisible(dc_handle, x, y);
        return is_ok == TRUE;
    }

    RegionFlag clip::get_border(HDC dc_handle, RECT *rect) {
        return static_cast<RegionFlag>(GetClipBox(dc_handle, rect));
    }

    int32_t clip::get_region(HDC dc_handle, HRGN region_handle) {
        return GetClipRgn(dc_handle, region_handle);
    }

    int32_t clip::get_meta_region(HDC dc_handle, HRGN region_handle) {
        return GetMetaRgn(dc_handle, region_handle);
    }

    RegionFlag clip::set_meta_region(HDC dc_handle) {
        return static_cast<RegionFlag>(SetMetaRgn(dc_handle));
    }

    int32_t clip::get_random_region(HDC dc_handle, HRGN region_handle) {
        return GetRandomRgn(dc_handle, region_handle, SYSRGN);
    }
} // namespace YanLib::ui::gdi
