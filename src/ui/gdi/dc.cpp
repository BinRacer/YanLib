//
// Created by forkernel on 2025/5/2.
//

#include "dc.h"

namespace YanLib::ui::gdi {
HDC dc::create_dc(const char *driver_name,
    const char               *device_name,
    const char               *port,
    const DEVMODEA           *device_mode) {
    return CreateDCA(driver_name, device_name, port, device_mode);
}

HDC dc::create_dc(const wchar_t *driver_name,
    const wchar_t               *device_name,
    const wchar_t               *port,
    const DEVMODEW              *device_mode) {
    return CreateDCW(driver_name, device_name, port, device_mode);
}

HDC dc::create_compatible_dc(HDC dc_handle) {
    return CreateCompatibleDC(dc_handle);
}

HDC dc::create_ic(const char *driver_name,
    const char               *device_name,
    const char               *port,
    const DEVMODEA           *device_mode) {
    return CreateICA(driver_name, device_name, port, device_mode);
}

HDC dc::create_ic(const wchar_t *driver_name,
    const wchar_t               *device_name,
    const wchar_t               *port,
    const DEVMODEW              *device_mode) {
    return CreateICW(driver_name, device_name, port, device_mode);
}

HDC dc::get_dc(HWND hwnd) {
    return GetDC(hwnd);
}

HDC dc::get_dc(HWND hwnd, HRGN region_clip_handle, uint32_t flag) {
    return GetDCEx(hwnd, region_clip_handle, flag);
}

int32_t dc::release_dc(HWND hwnd, HDC dc_handle) {
    return ReleaseDC(hwnd, dc_handle);
}

bool dc::delete_dc(HDC dc_handle) {
    return DeleteDC(dc_handle);
}

std::pair<bool, uint32_t> dc::scroll_dc(HDC dc_handle,
    int32_t                                 x,
    int32_t                                 y,
    const RECT                             *rect_scroll,
    const RECT                             *rect_clip,
    HRGN                                    region_update_handle,
    RECT                                   *rect_update) {
    uint32_t error_code = 0;
    if (!ScrollDC(dc_handle, x, y, rect_scroll, rect_clip, region_update_handle,
            rect_update)) {
        error_code = GetLastError();
        return std::make_pair(false, error_code);
    }
    return std::make_pair(true, error_code);
}

std::pair<uint32_t, uint32_t> dc::get_layout(HDC dc_handle) {
    uint32_t result     = GetLayout(dc_handle);
    uint32_t error_code = 0;
    if (result == GDI_ERROR) {
        error_code = GetLastError();
    }
    return std::make_pair(result, error_code);
}

uint32_t dc::set_layout(HDC dc_handle, uint32_t value) {
    return SetLayout(dc_handle, value);
}

HDC dc::get_window_dc(HWND hwnd) {
    return GetWindowDC(hwnd);
}

HWND dc::window_from_dc(HDC dc_handle) {
    return WindowFromDC(dc_handle);
}

bool dc::cancel_dc(HDC dc_handle) {
    return CancelDC(dc_handle);
}

HDC dc::reset_dc(HDC dc_handle, const DEVMODEA *device_mode) {
    return ResetDCA(dc_handle, device_mode);
}

HDC dc::reset_dc(HDC dc_handle, const DEVMODEW *device_mode) {
    return ResetDCW(dc_handle, device_mode);
}

int32_t dc::save_dc(HDC dc_handle) {
    return SaveDC(dc_handle);
}

bool dc::restore_dc(HDC dc_handle, int32_t saved_dc_state) {
    return RestoreDC(dc_handle, saved_dc_state);
}

COLORREF dc::get_dc_brush_color(HDC dc_handle) {
    return GetDCBrushColor(dc_handle);
}

COLORREF dc::set_dc_brush_color(HDC dc_handle, COLORREF color) {
    return SetDCBrushColor(dc_handle, color);
}

bool dc::get_dc_org(HDC dc_handle, POINT *point) {
    return GetDCOrgEx(dc_handle, point);
}

COLORREF dc::get_dc_pen_color(HDC dc_handle) {
    return GetDCPenColor(dc_handle);
}

COLORREF dc::set_dc_pen_color(HDC dc_handle, COLORREF color) {
    return SetDCPenColor(dc_handle, color);
}

int32_t dc::get_object(HANDLE gdi_handle, int32_t size, void *buf) {
    return GetObjectW(gdi_handle, size, buf);
}

uint32_t dc::get_object_type(HGDIOBJ gdi_obj_handle) {
    return GetObjectType(gdi_obj_handle);
}

HGDIOBJ dc::get_stock_object(int32_t type) {
    return GetStockObject(type);
}

HGDIOBJ dc::get_current_object(HDC dc_handle, uint32_t type) {
    return GetCurrentObject(dc_handle, type);
}

HGDIOBJ dc::select_object(HDC dc_handle, HGDIOBJ gdi_obj_handle) {
    return SelectObject(dc_handle, gdi_obj_handle);
}

bool dc::delete_object(HGDIOBJ gdi_obj_handle) {
    return DeleteObject(gdi_obj_handle);
}

int32_t dc::enum_objects(HDC dc_handle,
    int32_t                  type,
    GOBJENUMPROC             func,
    LPARAM                   lparam) {
    return EnumObjects(dc_handle, type, func, lparam);
}

int32_t dc::get_device_caps(HDC dc_handle, int32_t index) {
    return GetDeviceCaps(dc_handle, index);
}

int32_t dc::device_capabilities(const char *device_name,
    const char                             *port,
    uint16_t                                capability,
    char                                   *output,
    const DEVMODEA                         *device_mode) {
    return DeviceCapabilitiesA(
        device_name, port, capability, output, device_mode);
}

int32_t dc::device_capabilities(const wchar_t *device_name,
    const wchar_t                             *port,
    uint16_t                                   capability,
    wchar_t                                   *output,
    const DEVMODEW                            *device_mode) {
    return DeviceCapabilitiesW(
        device_name, port, capability, output, device_mode);
}

int32_t dc::draw_escape(HDC dc_handle,
    int32_t                 escape_func,
    int32_t                 size,
    const char             *buf) {
    return DrawEscape(dc_handle, escape_func, size, buf);
}
} // namespace YanLib::ui::gdi
