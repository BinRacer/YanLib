//
// Created by forkernel on 2025/5/4.
//

#ifndef CLIP_H
#define CLIP_H
#include <Windows.h>
#include <cstdint>

namespace YanLib::ui::gdi {
#ifndef REGIONSTYLE
#define REGIONSTYLE

    enum class RegionStyle : int32_t {
        And = RGN_AND,
        Or = RGN_OR,
        Xor = RGN_XOR,
        Diff = RGN_DIFF,
        Copy = RGN_COPY,
    };
#endif
#ifndef REGIONFLAG
#define REGIONFLAG

    enum class RegionFlag : int32_t {
        Error = ERROR,
        NullRegion = NULLREGION,
        SimpleRegion = SIMPLEREGION,
        ComplexRegion = COMPLEXREGION,
    };
#endif
    class clip {
    public:
        clip(const clip &other) = delete;

        clip(clip &&other) = delete;

        clip &operator=(const clip &other) = delete;

        clip &operator=(clip &&other) = delete;

        clip() = default;

        ~clip() = default;

        static bool select_region(HDC dc_handle, RegionStyle style);

        static RegionFlag select_region(HDC dc_handle, HRGN region_handle);

        static RegionFlag
        select_region(HDC dc_handle, HRGN region_handle, RegionStyle style);

        static RegionFlag exclude_rect(HDC dc_handle,
                                       int32_t left,
                                       int32_t top,
                                       int32_t right,
                                       int32_t bottom);

        static RegionFlag intersect_rect(HDC dc_handle,
                                         int32_t left,
                                         int32_t top,
                                         int32_t right,
                                         int32_t bottom);

        static RegionFlag offset_region(HDC dc_handle, int32_t x, int32_t y);

        static bool contains(HDC dc_handle, const RECT *rect);

        static bool contains(HDC dc_handle, int32_t x, int32_t y);

        static RegionFlag get_border(HDC dc_handle, RECT *rect);

        static int32_t get_region(HDC dc_handle, HRGN region_handle);

        static int32_t get_meta_region(HDC dc_handle, HRGN region_handle);

        static RegionFlag set_meta_region(HDC dc_handle);

        static int32_t get_random_region(HDC dc_handle, HRGN region_handle);
    };
} // namespace YanLib::ui::gdi
#endif // CLIP_H
