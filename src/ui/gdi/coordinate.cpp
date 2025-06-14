/* clang-format off */
/*
 * @file coordinate.cpp
 * @date 2025-05-04
 * @license MIT License
 *
 * Copyright (c) 2025 BinRacer <native.lab@outlook.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
/* clang-format on */
#include "coordinate.h"

namespace YanLib::ui::gdi {
    bool coordinate::client_to_screen(HWND window_handle, POINT *point) {
        return ClientToScreen(window_handle, point);
    }

    bool coordinate::screen_to_client(HWND window_handle, POINT *point) {
        return ScreenToClient(window_handle, point);
    }

    bool coordinate::logic_point_to_physical_point(HWND window_handle,
                                                   POINT *point) {
        return LogicalToPhysicalPoint(window_handle, point);
    }

    bool coordinate::physical_point_to_logic_point(HWND window_handle,
                                                   POINT *point) {
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

    bool coordinate::get_curr_pos(HDC dc_handle, POINT *point) {
        return GetCurrentPositionEx(dc_handle, point);
    }

    bool coordinate::get_window_size(HDC dc_handle, SIZE *size) {
        return GetWindowExtEx(dc_handle, size);
    }

    bool coordinate::set_window_size(HDC dc_handle,
                                     int32_t x,
                                     int32_t y,
                                     SIZE *size) {
        return SetWindowExtEx(dc_handle, x, y, size);
    }

    bool coordinate::get_window_origin(HDC dc_handle, POINT *point) {
        return GetWindowOrgEx(dc_handle, point);
    }

    bool coordinate::set_window_origin(HDC dc_handle,
                                       int32_t x,
                                       int32_t y,
                                       POINT *point) {
        return SetWindowOrgEx(dc_handle, x, y, point);
    }

    bool coordinate::get_viewport_size(HDC dc_handle, SIZE *size) {
        return GetViewportExtEx(dc_handle, size);
    }

    bool coordinate::set_viewport_size(HDC dc_handle,
                                       int32_t x,
                                       int32_t y,
                                       SIZE *size) {
        return SetViewportExtEx(dc_handle, x, y, size);
    }

    bool coordinate::get_viewport_origin(HDC dc_handle, POINT *point) {
        return GetViewportOrgEx(dc_handle, point);
    }

    bool coordinate::set_viewport_origin(HDC dc_handle,
                                         int32_t x,
                                         int32_t y,
                                         POINT *point) {
        return SetViewportOrgEx(dc_handle, x, y, point);
    }

    bool coordinate::get_display_auto_rotation_preferences(
            OrientationPreference *orientation) {
        if (!orientation) {
            return false;
        }
        auto temp = static_cast<ORIENTATION_PREFERENCE>(*orientation);
        const bool is_ok = GetDisplayAutoRotationPreferences(&temp);
        *orientation = static_cast<OrientationPreference>(temp);
        return is_ok;
    }

    bool coordinate::set_display_auto_rotation_preferences(
            OrientationPreference orientation) {
        return SetDisplayAutoRotationPreferences(
                static_cast<ORIENTATION_PREFERENCE>(orientation));
    }

    GraphicsMode coordinate::get_graphics_mode(HDC dc_handle) {
        return static_cast<GraphicsMode>(GetGraphicsMode(dc_handle));
    }

    GraphicsMode coordinate::set_graphics_mode(HDC dc_handle,
                                               GraphicsMode mode) {
        return static_cast<GraphicsMode>(
                SetGraphicsMode(dc_handle, static_cast<int32_t>(mode)));
    }

    MappingMode coordinate::get_map_mode(HDC dc_handle) {
        return static_cast<MappingMode>(GetMapMode(dc_handle));
    }

    MappingMode coordinate::set_map_mode(HDC dc_handle, MappingMode mode) {
        return static_cast<MappingMode>(
                SetMapMode(dc_handle, static_cast<int32_t>(mode)));
    }

    bool coordinate::get_world_transform(HDC dc_handle, XFORM *xfrom) {
        return GetWorldTransform(dc_handle, xfrom);
    }

    bool coordinate::set_world_transform(HDC dc_handle, const XFORM *xfrom) {
        return SetWorldTransform(dc_handle, xfrom);
    }

    std::pair<int32_t, uint32_t>
    coordinate::transform_coordinate(HWND window_handle_from,
                                     HWND window_handle_to,
                                     std::vector<POINT> &point) {
        SetLastError(0);
        uint32_t result = MapWindowPoints(window_handle_from, window_handle_to,
                                          point.data(), point.size());
        uint32_t error_code = GetLastError();
        return std::make_pair(result, error_code);
    }

    bool coordinate::modify_world_transform(HDC dc_handle,
                                            const XFORM *xfrom,
                                            XFormMode mode) {
        return ModifyWorldTransform(dc_handle, xfrom,
                                    static_cast<uint32_t>(mode));
    }

    bool coordinate::offset_window_org(HDC dc_handle,
                                       int32_t x,
                                       int32_t y,
                                       POINT *point) {
        return OffsetWindowOrgEx(dc_handle, x, y, point);
    }

    bool coordinate::offset_viewport_org(HDC dc_handle,
                                         int32_t x,
                                         int32_t y,
                                         POINT *point) {
        return OffsetViewportOrgEx(dc_handle, x, y, point);
    }

    bool coordinate::scale_viewport(HDC dc_handle,
                                    int32_t x_mul_factor,
                                    int32_t x_div_factor,
                                    int32_t y_mul_factor,
                                    int32_t y_div_factor,
                                    SIZE *size) {
        return ScaleViewportExtEx(dc_handle, x_mul_factor, x_div_factor,
                                  y_mul_factor, y_div_factor, size);
    }

    bool coordinate::scale_window(HDC dc_handle,
                                  int32_t x_mul_factor,
                                  int32_t x_div_factor,
                                  int32_t y_mul_factor,
                                  int32_t y_div_factor,
                                  SIZE *size) {
        return ScaleWindowExtEx(dc_handle, x_mul_factor, x_div_factor,
                                y_mul_factor, y_div_factor, size);
    }

    bool coordinate::combine_transform(XFORM *xfrom_dst,
                                       const XFORM *xfrom_src1,
                                       const XFORM *xfrom_src2) {
        return CombineTransform(xfrom_dst, xfrom_src1, xfrom_src2);
    }
} // namespace YanLib::ui::gdi
