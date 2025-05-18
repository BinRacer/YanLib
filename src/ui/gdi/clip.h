//
// Created by forkernel on 2025/5/4.
//

#ifndef CLIP_H
#define CLIP_H
#include <Windows.h>
#include <cstdint>

namespace YanLib::ui::gdi {
    class clip {
    public:
        clip(const clip &other) = delete;

        clip(clip &&other) = delete;

        clip &operator=(const clip &other) = delete;

        clip &operator=(clip &&other) = delete;

        clip() = default;

        ~clip() = default;

        static bool select_clip_path(HDC dc_handle, int32_t mode);

        static int32_t select_clip_region(HDC dc_handle, HRGN region_handle);

        static int32_t
        select_clip_region(HDC dc_handle, HRGN region_handle, int32_t mode);

        static int32_t exclude_clip_rect(HDC dc_handle,
                                         int32_t left,
                                         int32_t top,
                                         int32_t right,
                                         int32_t bottom);

        static int32_t intersect_clip_rect(HDC dc_handle,
                                           int32_t left,
                                           int32_t top,
                                           int32_t right,
                                           int32_t bottom);

        static int32_t offset_clip_region(HDC dc_handle, int32_t x, int32_t y);

        static bool rect_visible(HDC dc_handle, const RECT* rect);

        static bool point_visible(HDC dc_handle, int32_t x, int32_t y);

        static int32_t get_clip_box(HDC dc_handle, RECT* rect);

        static int32_t get_clip_region(HDC dc_handle, HRGN region_handle);

        static int32_t get_meta_region(HDC dc_handle, HRGN region_handle);

        static int32_t set_meta_region(HDC dc_handle);

        static int32_t get_random_region(HDC dc_handle, HRGN region_handle);
    };
} // namespace YanLib::ui::gdi
#endif // CLIP_H
