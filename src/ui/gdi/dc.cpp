/* clang-format off */
/*
 * @file dc.cpp
 * @date 2025-05-02
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
#include "dc.h"

namespace YanLib::ui::gdi {
    HDC dc::create(const char *driver_name,
                   const char *device_name,
                   const DEVMODEA *device_mode) {
        return CreateDCA(driver_name, device_name, nullptr, device_mode);
    }

    HDC dc::create(const wchar_t *driver_name,
                   const wchar_t *device_name,
                   const DEVMODEW *device_mode) {
        return CreateDCW(driver_name, device_name, nullptr, device_mode);
    }

    HDC dc::create_compatible(HDC dc_handle) {
        return CreateCompatibleDC(dc_handle);
    }

    HDC dc::create_ic(const char *driver_name,
                      const char *device_name,
                      const DEVMODEA *device_mode) {
        return CreateICA(driver_name, device_name, nullptr, device_mode);
    }

    HDC dc::create_ic(const wchar_t *driver_name,
                      const wchar_t *device_name,
                      const DEVMODEW *device_mode) {
        return CreateICW(driver_name, device_name, nullptr, device_mode);
    }

    HDC dc::get(HWND window_handle) {
        return GetDC(window_handle);
    }

    HDC dc::get(HWND window_handle, HRGN region_clip_handle, DCFlag flag) {
        return GetDCEx(window_handle, region_clip_handle,
                       static_cast<uint32_t>(flag));
    }

    int32_t dc::release(HWND window_handle, HDC dc_handle) {
        return ReleaseDC(window_handle, dc_handle);
    }

    bool dc::destroy(HDC dc_handle) {
        return DeleteDC(dc_handle);
    }

    std::pair<bool, uint32_t> dc::scroll(HDC dc_handle,
                                         int32_t x,
                                         int32_t y,
                                         const RECT *rect_scroll,
                                         const RECT *rect_clip,
                                         HRGN region_update_handle,
                                         RECT *rect_update) {
        uint32_t error_code = 0;
        if (!ScrollDC(dc_handle, x, y, rect_scroll, rect_clip,
                      region_update_handle, rect_update)) {
            error_code = GetLastError();
            return std::make_pair(false, error_code);
        }
        return std::make_pair(true, error_code);
    }

    std::pair<core::Layout, uint32_t> dc::get_layout(HDC dc_handle) {
        auto result = static_cast<core::Layout>(GetLayout(dc_handle));
        uint32_t error_code = 0;
        if (result == core::Layout::Error) {
            error_code = GetLastError();
        }
        return std::make_pair(result, error_code);
    }

    core::Layout dc::set_layout(HDC dc_handle, core::Layout layout) {
        return static_cast<core::Layout>(
                SetLayout(dc_handle, static_cast<uint32_t>(layout)));
    }

    HDC dc::get_window_dc(HWND window_handle) {
        return GetWindowDC(window_handle);
    }

    HWND dc::get_window(HDC dc_handle) {
        return WindowFromDC(dc_handle);
    }

    bool dc::cancel(HDC dc_handle) {
        return CancelDC(dc_handle);
    }

    HDC dc::reset(HDC dc_handle, const DEVMODEA *device_mode) {
        return ResetDCA(dc_handle, device_mode);
    }

    HDC dc::reset(HDC dc_handle, const DEVMODEW *device_mode) {
        return ResetDCW(dc_handle, device_mode);
    }

    int32_t dc::save(HDC dc_handle) {
        return SaveDC(dc_handle);
    }

    bool dc::restore(HDC dc_handle, int32_t saved_dc_state) {
        return RestoreDC(dc_handle, saved_dc_state);
    }

    COLORREF dc::get_brush_color(HDC dc_handle) {
        return GetDCBrushColor(dc_handle);
    }

    COLORREF dc::set_brush_color(HDC dc_handle, COLORREF color) {
        return SetDCBrushColor(dc_handle, color);
    }

    bool dc::get_origin(HDC dc_handle, POINT *point) {
        return GetDCOrgEx(dc_handle, point);
    }

    COLORREF dc::get_pen_color(HDC dc_handle) {
        return GetDCPenColor(dc_handle);
    }

    COLORREF dc::set_pen_color(HDC dc_handle, COLORREF color) {
        return SetDCPenColor(dc_handle, color);
    }

    int32_t dc::get_object(HANDLE gdi_handle, void *buf, int32_t size) {
        return GetObjectW(gdi_handle, size, buf);
    }

    ObjectType dc::get_object_type(HGDIOBJ gdi_obj_handle) {
        return static_cast<ObjectType>(GetObjectType(gdi_obj_handle));
    }

    HGDIOBJ dc::get_stock_object(StockLogicalObject type) {
        return GetStockObject(static_cast<int32_t>(type));
    }

    HGDIOBJ dc::get_curr_object(HDC dc_handle, ObjectType type) {
        return GetCurrentObject(dc_handle, static_cast<uint32_t>(type));
    }

    HGDIOBJ dc::select_object(HDC dc_handle, HGDIOBJ gdi_obj_handle) {
        return SelectObject(dc_handle, gdi_obj_handle);
    }

    bool dc::destroy_object(HGDIOBJ gdi_obj_handle) {
        return DeleteObject(gdi_obj_handle);
    }

    int32_t dc::enum_objects(HDC dc_handle,
                             GOBJENUMPROC func,
                             LPARAM lparam,
                             ObjectType type) {
        return EnumObjects(dc_handle, static_cast<int32_t>(type), func, lparam);
    }

    int32_t dc::get_device_caps(HDC dc_handle, DeviceParameter param) {
        return GetDeviceCaps(dc_handle, static_cast<int32_t>(param));
    }

    int32_t dc::device_capabilities(const char *device_name,
                                    const char *port,
                                    DeviceCapability capability,
                                    char *output,
                                    const DEVMODEA *device_mode) {
        return DeviceCapabilitiesA(device_name, port,
                                   static_cast<uint16_t>(capability), output,
                                   device_mode);
    }

    int32_t dc::device_capabilities(const wchar_t *device_name,
                                    const wchar_t *port,
                                    DeviceCapability capability,
                                    wchar_t *output,
                                    const DEVMODEW *device_mode) {
        return DeviceCapabilitiesW(device_name, port,
                                   static_cast<uint16_t>(capability), output,
                                   device_mode);
    }

    int32_t dc::draw_escape(HDC dc_handle,
                            int32_t escape_func,
                            const char *buf,
                            int32_t size) {
        return DrawEscape(dc_handle, escape_func, size, buf);
    }
} // namespace YanLib::ui::gdi
