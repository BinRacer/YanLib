//
// Created by forkernel on 2025/5/4.
//

#ifndef CLIP_H
#define CLIP_H
#include <Windows.h>

namespace YanLib::ui {
    class clip {
    public:
        clip(const clip &other) = delete;

        clip(clip &&other) = delete;

        clip &operator=(const clip &other) = delete;

        clip &operator=(clip &&other) = delete;

        clip() = default;

        ~clip() = default;

        static bool select_clip_path(HDC dc_handle, int mode);

        static int select_clip_region(HDC dc_handle, HRGN region_handle);

        static int select_clip_region(HDC dc_handle, HRGN region_handle, int mode);

        static int exclude_clip_rect(HDC dc_handle,
                                     int left,
                                     int top,
                                     int right,
                                     int bottom);

        static int intersect_clip_rect(HDC dc_handle,
                                       int left,
                                       int top,
                                       int right,
                                       int bottom);

        static int offset_clip_region(HDC dc_handle, int x, int y);

        static bool rect_visible(HDC dc_handle, const RECT *rect);

        static bool point_visible(HDC dc_handle, int x, int y);

        static int get_clip_box(HDC dc_handle, RECT *rect);

        static int get_clip_region(HDC dc_handle, HRGN region_handle);

        static int get_meta_region(HDC dc_handle, HRGN region_handle);

        static int set_meta_region(HDC dc_handle);

        static int get_random_region(HDC dc_handle, HRGN region_handle);
    };
}
#endif //CLIP_H
