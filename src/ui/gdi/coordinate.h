//
// Created by BinRacer <native.lab@outlook.com> on 2025/5/4.
//

#ifndef COORDINATE_H
#define COORDINATE_H
#include <utility>
#include <Windows.h>
#include <vector>

namespace YanLib::ui::gdi {
#ifndef ORIENTATIONPREFERENCE
#define ORIENTATIONPREFERENCE

    enum class OrientationPreference : int32_t {
        None = ORIENTATION_PREFERENCE_NONE,
        Landscape = ORIENTATION_PREFERENCE_LANDSCAPE,
        Portrait = ORIENTATION_PREFERENCE_PORTRAIT,
        LandscapeFlipped = ORIENTATION_PREFERENCE_LANDSCAPE_FLIPPED,
        PortraitFlipped = ORIENTATION_PREFERENCE_PORTRAIT_FLIPPED,
    };

    inline OrientationPreference operator|(OrientationPreference a,
                                           OrientationPreference b) {
        return static_cast<OrientationPreference>(static_cast<int32_t>(a) |
                                                  static_cast<int32_t>(b));
    }
#endif
#ifndef GRAPHICSMODE
#define GRAPHICSMODE

    enum class GraphicsMode : int32_t {
        None = 0,
        Compatible = GM_COMPATIBLE,
        Advanced = GM_ADVANCED,
    };
#endif
#ifndef MAPPINGMODE
#define MAPPINGMODE

    enum class MappingMode : int32_t {
        Text = MM_TEXT,
        LoMetric = MM_LOMETRIC,
        HiMetric = MM_HIMETRIC,
        LoEnglish = MM_LOENGLISH,
        HiEnglish = MM_HIENGLISH,
        TwIps = MM_TWIPS,
        IsoTropic = MM_ISOTROPIC,
        AnIsoTropic = MM_ANISOTROPIC,
    };

    inline MappingMode operator|(MappingMode a, MappingMode b) {
        return static_cast<MappingMode>(static_cast<int32_t>(a) |
                                        static_cast<int32_t>(b));
    }
#endif
#ifndef XFORMMODE
#define XFORMMODE

    enum class XFormMode : uint32_t {
        Identity = MWT_IDENTITY,
        LeftMultiply = MWT_LEFTMULTIPLY,
        RightMultiply = MWT_RIGHTMULTIPLY,
    };
#endif
    class coordinate {
    public:
        coordinate(const coordinate &other) = delete;

        coordinate(coordinate &&other) = delete;

        coordinate &operator=(const coordinate &other) = delete;

        coordinate &operator=(coordinate &&other) = delete;

        coordinate() = default;

        ~coordinate() = default;

        static bool client_to_screen(HWND window_handle, POINT *point);

        static bool screen_to_client(HWND window_handle, POINT *point);

        static bool logic_point_to_physical_point(HWND window_handle,
                                                  POINT *point);

        static bool physical_point_to_logic_point(HWND window_handle,
                                                  POINT *point);

        static bool device_point_to_logic_point(HDC dc_handle,
                                                std::vector<POINT> &point);

        static bool logic_point_to_device_point(HDC dc_handle,
                                                std::vector<POINT> &point);

        static bool get_curr_pos(HDC dc_handle, POINT *point);

        static bool get_window_size(HDC dc_handle, SIZE *size);

        static bool
        set_window_size(HDC dc_handle, int32_t x, int32_t y, SIZE *size);

        static bool get_window_origin(HDC dc_handle, POINT *point);

        static bool
        set_window_origin(HDC dc_handle, int32_t x, int32_t y, POINT *point);

        static bool get_viewport_size(HDC dc_handle, SIZE *size);

        static bool
        set_viewport_size(HDC dc_handle, int32_t x, int32_t y, SIZE *size);

        static bool get_viewport_origin(HDC dc_handle, POINT *point);

        static bool
        set_viewport_origin(HDC dc_handle, int32_t x, int32_t y, POINT *point);

        static bool get_display_auto_rotation_preferences(
                OrientationPreference *orientation);

        static bool set_display_auto_rotation_preferences(
                OrientationPreference orientation);

        static GraphicsMode get_graphics_mode(HDC dc_handle);

        static GraphicsMode set_graphics_mode(HDC dc_handle, GraphicsMode mode);

        static MappingMode get_map_mode(HDC dc_handle);

        static MappingMode set_map_mode(HDC dc_handle, MappingMode mode);

        static bool get_world_transform(HDC dc_handle, XFORM *xfrom);

        static bool set_world_transform(HDC dc_handle, const XFORM *xfrom);

        // std::pair<result, error_code>
        static std::pair<int32_t, uint32_t>
        transform_coordinate(HWND window_handle_from,
                             HWND window_handle_to,
                             std::vector<POINT> &point);

        static bool modify_world_transform(HDC dc_handle,
                                           const XFORM *xfrom,
                                           XFormMode mode);

        static bool
        offset_window_org(HDC dc_handle, int32_t x, int32_t y, POINT *point);

        static bool
        offset_viewport_org(HDC dc_handle, int32_t x, int32_t y, POINT *point);

        static bool scale_viewport(HDC dc_handle,
                                   int32_t x_mul_factor,
                                   int32_t x_div_factor,
                                   int32_t y_mul_factor,
                                   int32_t y_div_factor,
                                   SIZE *size);

        static bool scale_window(HDC dc_handle,
                                 int32_t x_mul_factor,
                                 int32_t x_div_factor,
                                 int32_t y_mul_factor,
                                 int32_t y_div_factor,
                                 SIZE *size);

        static bool combine_transform(XFORM *xfrom_dst,
                                      const XFORM *xfrom_src1,
                                      const XFORM *xfrom_src2);
    };
} // namespace YanLib::ui::gdi
#endif // COORDINATE_H
