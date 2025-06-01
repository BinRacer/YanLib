//
// Created by forkernel on 2025/5/2.
//

#ifndef REGION_H
#define REGION_H
#include <utility>
#include <Windows.h>
#include <vector>

namespace YanLib::ui::gdi {
#ifndef FILLMODE
#define FILLMODE

    enum class FillMode : int32_t {
        Error = 0,
        Alternate = ALTERNATE,
        Winding = WINDING,
    };
#endif
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
    class region {
    public:
        region(const region &other) = delete;

        region(region &&other) = delete;

        region &operator=(const region &other) = delete;

        region &operator=(region &&other) = delete;

        region() = default;

        ~region() = default;

        static HRGN
        create_rect(int32_t left, int32_t top, int32_t right, int32_t bottom);

        static HRGN create_rect(const RECT *rect);

        static HRGN create_round_rect(int32_t left,
                                      int32_t top,
                                      int32_t right,
                                      int32_t bottom,
                                      int32_t width,
                                      int32_t height);

        static HRGN create_elliptic(int32_t left,
                                    int32_t top,
                                    int32_t right,
                                    int32_t bottom);

        static HRGN create_elliptic(const RECT *rect);

        static HRGN create_polygon(const std::vector<POINT> &point,
                                   FillMode mode);

        static HRGN create_poly_polygon(const std::vector<POINT> &point,
                                        const std::vector<int32_t> &poly_count,
                                        FillMode mode);

        static bool
        fill(HDC dc_handle, HRGN region_handle, HBRUSH brush_handle);

        static HRGN
        create(const XFORM *xfrom, const RGNDATA *buf, uint32_t size);

        static bool frame(HDC dc_handle,
                          HRGN region_handle,
                          HBRUSH brush_handle,
                          int32_t width,
                          int32_t height);

        static RegionFlag combine(HRGN region_handle_dst,
                                  HRGN region_handle_src1,
                                  HRGN region_handle_src2,
                                  RegionStyle style);

        static bool equal(HRGN region_handle1, HRGN region_handle2);

        static bool invert(HDC dc_handle, HRGN region_handle);

        static RegionFlag offset(HRGN region_handle, int32_t x, int32_t y);

        static bool paint(HDC dc_handle, HRGN region_handle);

        static bool contains_point(HRGN region_handle, int32_t x, int32_t y);

        static bool contains_rect(HRGN region_handle, const RECT *rect);

        static FillMode get_poly_fill_mode(HDC dc_handle);

        static FillMode set_poly_fill_mode(HDC dc_handle, FillMode mode);

        static bool set_rect(HRGN region_handle,
                             int32_t left,
                             int32_t top,
                             int32_t right,
                             int32_t bottom);

        static RegionFlag get_box(HRGN region_handle, RECT *rect);

        static RegionFlag get_update(HWND window_handle,
                                     HRGN region_handle,
                                     bool is_erase = true);

        static bool validate(HWND window_handle, HRGN region_handle);

        static bool invalidate(HWND window_handle,
                               HRGN region_handle,
                               bool is_erase = true);

        static RegionFlag exclude_update(HDC dc_handle, HWND window_handle);

        // std::pair<result, error_code>
        static std::pair<uint32_t, uint32_t>
        get_data(HRGN region_handle, RGNDATA *buf, uint32_t size);
    };
} // namespace YanLib::ui::gdi
#endif // REGION_H
