//
// Created by forkernel on 2025/5/4.
//

#include "coordinate.h"

namespace YanLib::ui::gdi {
    bool coordinate::client_to_screen(HWND hwnd, POINT *point) {
        return ClientToScreen(hwnd, point);
    }

    bool coordinate::screen_to_client(HWND hwnd, POINT *point) {
        return ScreenToClient(hwnd, point);
    }

    bool coordinate::device_point_to_logic_point(HDC dc_handle,
                                                 POINT *point,
                                                 int num) {
        return DPtoLP(dc_handle, point, num);
    }

    bool coordinate::logic_point_to_device_point(HDC dc_handle,
                                                 POINT *point,
                                                 int num) {
        return LPtoDP(dc_handle, point, num);
    }

    bool coordinate::get_current_position(HDC dc_handle, POINT *point) {
        return GetCurrentPositionEx(dc_handle, point);
    }

    bool coordinate::get_window(HDC dc_handle, SIZE *size) {
        return GetWindowExtEx(dc_handle, size);
    }

    bool coordinate::set_window(HDC dc_handle, int x, int y, SIZE *size) {
        return SetWindowExtEx(dc_handle, x, y, size);
    }

    bool coordinate::get_window_org(HDC dc_handle, POINT *point) {
        return GetWindowOrgEx(dc_handle, point);
    }

    bool coordinate::set_window_org(HDC dc_handle, int x, int y, POINT *point) {
        return SetWindowOrgEx(dc_handle, x, y, point);
    }

    bool coordinate::get_viewport(HDC dc_handle, SIZE *size) {
        return GetViewportExtEx(dc_handle, size);
    }

    bool coordinate::set_viewport(HDC dc_handle, int x, int y, SIZE *size) {
        return SetViewportExtEx(dc_handle, x, y, size);
    }

    bool coordinate::get_viewport_org(HDC dc_handle, POINT *point) {
        return GetViewportOrgEx(dc_handle, point);
    }

    bool coordinate::set_viewport_org(HDC dc_handle, int x, int y, POINT *point) {
        return SetViewportOrgEx(dc_handle, x, y, point);
    }

    bool coordinate::get_display_auto_rotation_preferences(
        ORIENTATION_PREFERENCE *orientation) {
        return GetDisplayAutoRotationPreferences(orientation);
    }

    bool coordinate::set_display_auto_rotation_preferences(
        ORIENTATION_PREFERENCE orientation) {
        return SetDisplayAutoRotationPreferences(orientation);
    }

    int coordinate::get_graphics_mode(HDC dc_handle) {
        return GetGraphicsMode(dc_handle);
    }

    int coordinate::set_graphics_mode(HDC dc_handle, int mode) {
        return SetGraphicsMode(dc_handle, mode);
    }

    int coordinate::get_map_mode(HDC dc_handle) {
        return GetMapMode(dc_handle);
    }

    int coordinate::set_map_mode(HDC dc_handle, int mode) {
        return SetMapMode(dc_handle, mode);
    }

    bool coordinate::get_world_transform(HDC dc_handle, XFORM *xfrom) {
        return GetWorldTransform(dc_handle, xfrom);
    }

    bool coordinate::set_world_transform(HDC dc_handle, const XFORM *xfrom) {
        return SetWorldTransform(dc_handle, xfrom);
    }

    std::pair<int, unsigned long> coordinate::map_window_points(HWND hwnd_from,
                                                        HWND hwnd_to,
                                                        POINT *point,
                                                        unsigned int num) {
        SetLastError(0);
        unsigned long result = MapWindowPoints(hwnd_from, hwnd_to, point, num);
        unsigned long error_code = GetLastError();
        return std::make_pair(result, error_code);
    }

    bool coordinate::modify_world_transform(HDC dc_handle,
                                            const XFORM *xfrom,
                                            unsigned long mode) {
        return ModifyWorldTransform(dc_handle, xfrom, mode);
    }

    bool coordinate::offset_window_org(HDC dc_handle,
                                       int x,
                                       int y,
                                       POINT *point) {
        return OffsetWindowOrgEx(dc_handle, x, y, point);
    }

    bool coordinate::offset_viewport_org(HDC dc_handle,
                                         int x,
                                         int y,
                                         POINT *point) {
        return OffsetViewportOrgEx(dc_handle, x, y, point);
    }

    bool coordinate::scale_viewport(HDC dc_handle,
                                    int x_mul_factor,
                                    int x_div_factor,
                                    int y_mul_factor,
                                    int y_div_factor, SIZE *size) {
        return ScaleViewportExtEx(dc_handle,
                                  x_mul_factor,
                                  x_div_factor,
                                  y_mul_factor,
                                  y_div_factor,
                                  size);
    }

    bool coordinate::scale_window(HDC dc_handle,
                                  int x_mul_factor,
                                  int x_div_factor,
                                  int y_mul_factor,
                                  int y_div_factor,
                                  SIZE *size) {
        return ScaleWindowExtEx(dc_handle,
                                x_mul_factor,
                                x_div_factor,
                                y_mul_factor,
                                y_div_factor,
                                size);
    }

    bool coordinate::combine_transform(XFORM *xfrom_dst,
                                       const XFORM *xfrom_src1,
                                       const XFORM *xfrom_src2) {
        return CombineTransform(xfrom_dst, xfrom_src1, xfrom_src2);
    }
}
