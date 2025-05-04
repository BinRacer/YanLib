//
// Created by forkernel on 2025/5/4.
//

#ifndef COORDINATE_H
#define COORDINATE_H
#include <utility>
#include <Windows.h>

namespace YanLib::ui::gdi {
    class coordinate {
    public:
        coordinate(const coordinate &other) = delete;

        coordinate(coordinate &&other) = delete;

        coordinate &operator=(const coordinate &other) = delete;

        coordinate &operator=(coordinate &&other) = delete;

        coordinate() = default;

        ~coordinate() = default;

        static bool client_to_screen(HWND hwnd, POINT *point);

        static bool screen_to_client(HWND hwnd, POINT *point);

        static bool device_point_to_logic_point(HDC dc_handle,
                                                POINT *point,
                                                int num);

        static bool logic_point_to_device_point(HDC dc_handle,
                                                POINT *point,
                                                int num);

        static bool get_current_position(HDC dc_handle, POINT *point);

        static bool get_window(HDC dc_handle, SIZE *size);

        static bool set_window(HDC dc_handle, int x, int y, SIZE *size);

        static bool get_window_org(HDC dc_handle, POINT *point);

        static bool set_window_org(HDC dc_handle, int x, int y, POINT *point);

        static bool get_viewport(HDC dc_handle, SIZE *size);

        static bool set_viewport(HDC dc_handle, int x, int y, SIZE *size);

        static bool get_viewport_org(HDC dc_handle, POINT *point);

        static bool set_viewport_org(HDC dc_handle, int x, int y, POINT *point);

        static bool get_display_auto_rotation_preferences(
            ORIENTATION_PREFERENCE *orientation);

        static bool set_display_auto_rotation_preferences(
            ORIENTATION_PREFERENCE orientation);

        static int get_graphics_mode(HDC dc_handle);

        static int set_graphics_mode(HDC dc_handle, int mode);

        static int get_map_mode(HDC dc_handle);

        static int set_map_mode(HDC dc_handle, int mode);

        static bool get_world_transform(HDC dc_handle, XFORM *xfrom);

        static bool set_world_transform(HDC dc_handle, const XFORM *xfrom);

        // std::pair<result, error_code>
        static std::pair<int, DWORD> map_window_points(HWND hwnd_from,
                                                       HWND hwnd_to,
                                                       POINT *point,
                                                       UINT num);

        static bool modify_world_transform(HDC dc_handle,
                                           const XFORM *xfrom,
                                           DWORD mode);

        static bool offset_window_org(HDC dc_handle, int x, int y, POINT *point);

        static bool offset_viewport_org(HDC dc_handle, int x, int y, POINT *point);

        static bool scale_viewport(HDC dc_handle,
                                   int x_mul_factor,
                                   int x_div_factor,
                                   int y_mul_factor,
                                   int y_div_factor,
                                   SIZE *size);

        static bool scale_window(HDC dc_handle,
                                 int x_mul_factor,
                                 int x_div_factor,
                                 int y_mul_factor,
                                 int y_div_factor,
                                 SIZE *size);

        static bool combine_transform(XFORM *xfrom_dst,
                                      const XFORM *xfrom_src1,
                                      const XFORM *xfrom_src2);
    };
}
#endif //COORDINATE_H
