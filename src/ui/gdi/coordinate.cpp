//
// Created by forkernel on 2025/5/4.
//

#include "coordinate.h"

namespace YanLib::ui::gdi {
    bool coordinate::client_to_screen(HWND window_handle, POINT* point) {
        return ClientToScreen(window_handle, point);
    }

    bool coordinate::screen_to_client(HWND window_handle, POINT* point) {
        return ScreenToClient(window_handle, point);
    }

    bool coordinate::logic_point_to_physical_point(HWND window_handle,
                                                   POINT* point) {
        return LogicalToPhysicalPoint(window_handle, point);
    }

    bool coordinate::physical_point_to_logic_point(HWND window_handle,
                                                   POINT* point) {
        return PhysicalToLogicalPoint(window_handle, point);
    }

    bool coordinate::device_point_to_logic_point(HDC dc_handle,
                                                 std::vector<POINT> &point) {
        return DPtoLP(dc_handle, point.data(),
                      static_cast<int32_t>(point.size()));
    }

    bool coordinate::logic_point_to_device_point(HDC dc_handle,
                                                 std::vector<POINT> &point) {
        return LPtoDP(dc_handle, point.data(),
                      static_cast<int32_t>(point.size()));
    }

    bool coordinate::get_current_position(HDC dc_handle, POINT* point) {
        return GetCurrentPositionEx(dc_handle, point);
    }

    bool coordinate::get_window(HDC dc_handle, SIZE* size) {
        return GetWindowExtEx(dc_handle, size);
    }

    bool
    coordinate::set_window(HDC dc_handle, int32_t x, int32_t y, SIZE* size) {
        return SetWindowExtEx(dc_handle, x, y, size);
    }

    bool coordinate::get_window_org(HDC dc_handle, POINT* point) {
        return GetWindowOrgEx(dc_handle, point);
    }

    bool coordinate::set_window_org(HDC dc_handle,
                                    int32_t x,
                                    int32_t y,
                                    POINT* point) {
        return SetWindowOrgEx(dc_handle, x, y, point);
    }

    bool coordinate::get_viewport(HDC dc_handle, SIZE* size) {
        return GetViewportExtEx(dc_handle, size);
    }

    bool
    coordinate::set_viewport(HDC dc_handle, int32_t x, int32_t y, SIZE* size) {
        return SetViewportExtEx(dc_handle, x, y, size);
    }

    bool coordinate::get_viewport_org(HDC dc_handle, POINT* point) {
        return GetViewportOrgEx(dc_handle, point);
    }

    bool coordinate::set_viewport_org(HDC dc_handle,
                                      int32_t x,
                                      int32_t y,
                                      POINT* point) {
        return SetViewportOrgEx(dc_handle, x, y, point);
    }

    bool coordinate::get_display_auto_rotation_preferences(
            ORIENTATION_PREFERENCE* orientation) {
        return GetDisplayAutoRotationPreferences(orientation);
    }

    bool coordinate::set_display_auto_rotation_preferences(
            ORIENTATION_PREFERENCE orientation) {
        return SetDisplayAutoRotationPreferences(orientation);
    }

    int32_t coordinate::get_graphics_mode(HDC dc_handle) {
        return GetGraphicsMode(dc_handle);
    }

    int32_t coordinate::set_graphics_mode(HDC dc_handle, int32_t mode) {
        return SetGraphicsMode(dc_handle, mode);
    }

    int32_t coordinate::get_map_mode(HDC dc_handle) {
        return GetMapMode(dc_handle);
    }

    int32_t coordinate::set_map_mode(HDC dc_handle, int32_t mode) {
        return SetMapMode(dc_handle, mode);
    }

    bool coordinate::get_world_transform(HDC dc_handle, XFORM* xfrom) {
        return GetWorldTransform(dc_handle, xfrom);
    }

    bool coordinate::set_world_transform(HDC dc_handle, const XFORM* xfrom) {
        return SetWorldTransform(dc_handle, xfrom);
    }

    std::pair<int32_t, uint32_t>
    coordinate::map_window_points(HWND from_window_handle,
                                  HWND to_window_handle,
                                  std::vector<POINT> &point) {
        SetLastError(0);
        uint32_t result = MapWindowPoints(from_window_handle, to_window_handle,
                                          point.data(), point.size());
        uint32_t error_code = GetLastError();
        return std::make_pair(result, error_code);
    }

    bool coordinate::modify_world_transform(HDC dc_handle,
                                            const XFORM* xfrom,
                                            uint32_t mode) {
        return ModifyWorldTransform(dc_handle, xfrom, mode);
    }

    bool coordinate::offset_window_org(HDC dc_handle,
                                       int32_t x,
                                       int32_t y,
                                       POINT* point) {
        return OffsetWindowOrgEx(dc_handle, x, y, point);
    }

    bool coordinate::offset_viewport_org(HDC dc_handle,
                                         int32_t x,
                                         int32_t y,
                                         POINT* point) {
        return OffsetViewportOrgEx(dc_handle, x, y, point);
    }

    bool coordinate::scale_viewport(HDC dc_handle,
                                    int32_t x_mul_factor,
                                    int32_t x_div_factor,
                                    int32_t y_mul_factor,
                                    int32_t y_div_factor,
                                    SIZE* size) {
        return ScaleViewportExtEx(dc_handle, x_mul_factor, x_div_factor,
                                  y_mul_factor, y_div_factor, size);
    }

    bool coordinate::scale_window(HDC dc_handle,
                                  int32_t x_mul_factor,
                                  int32_t x_div_factor,
                                  int32_t y_mul_factor,
                                  int32_t y_div_factor,
                                  SIZE* size) {
        return ScaleWindowExtEx(dc_handle, x_mul_factor, x_div_factor,
                                y_mul_factor, y_div_factor, size);
    }

    bool coordinate::combine_transform(XFORM* xfrom_dst,
                                       const XFORM* xfrom_src1,
                                       const XFORM* xfrom_src2) {
        return CombineTransform(xfrom_dst, xfrom_src1, xfrom_src2);
    }
} // namespace YanLib::ui::gdi
