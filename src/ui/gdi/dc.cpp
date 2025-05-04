//
// Created by forkernel on 2025/5/2.
//

#include "dc.h"

namespace YanLib::ui::gdi {
    HDC dc::create_dc(const wchar_t *driver_name,
                      const wchar_t *device_name,
                      const wchar_t *port,
                      const DEVMODEW *device_mode) {
        return CreateDCW(driver_name, device_name, port, device_mode);
    }

    HDC dc::create_compatible_dc(HDC dc_handle) {
        return CreateCompatibleDC(dc_handle);
    }

    HDC dc::create_ic(const wchar_t *driver_name,
                      const wchar_t *device_name,
                      const wchar_t *port,
                      const DEVMODEW *device_mode) {
        return CreateICW(driver_name, device_name, port, device_mode);
    }

    HDC dc::get_dc(HWND hwnd) {
        return GetDC(hwnd);
    }

    HDC dc::get_dc(HWND hwnd, HRGN region_clip_handle, DWORD flag) {
        return GetDCEx(hwnd, region_clip_handle, flag);
    }

    int dc::release_dc(HWND hwnd, HDC dc_handle) {
        return ReleaseDC(hwnd, dc_handle);
    }

    bool dc::delete_dc(HDC dc_handle) {
        return DeleteDC(dc_handle);
    }

    std::pair<bool, DWORD> dc::scroll_dc(HDC dc_handle,
                                         int x,
                                         int y,
                                         const RECT *rect_scroll,
                                         const RECT *rect_clip,
                                         HRGN region_update_handle,
                                         RECT *rect_update) {
        DWORD error_code = 0;
        if (!ScrollDC(dc_handle,
                      x,
                      y,
                      rect_scroll,
                      rect_clip,
                      region_update_handle,
                      rect_update)) {
            error_code = GetLastError();
            return std::make_pair(false, error_code);
        }
        return std::make_pair(true, error_code);
    }

    std::pair<DWORD, DWORD> dc::get_layout(HDC dc_handle) {
        DWORD result = GetLayout(dc_handle);
        DWORD error_code = 0;
        if (result == GDI_ERROR) {
            error_code = GetLastError();
        }
        return std::make_pair(result, error_code);
    }

    DWORD dc::set_layout(HDC dc_handle, DWORD value) {
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

    HDC dc::reset_dc(HDC dc_handle, const DEVMODEW *device_mode) {
        return ResetDCW(dc_handle, device_mode);
    }

    int dc::save_dc(HDC dc_handle) {
        return SaveDC(dc_handle);
    }

    bool dc::restore_dc(HDC dc_handle, int saved_dc_state) {
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

    int dc::get_object(HANDLE gdi_handle, int size, void *buf) {
        return GetObjectW(gdi_handle, size, buf);
    }

    DWORD dc::get_object_type(HGDIOBJ gdi_obj_handle) {
        return GetObjectType(gdi_obj_handle);
    }

    HGDIOBJ dc::get_stock_object(int type) {
        return GetStockObject(type);
    }

    HGDIOBJ dc::get_current_object(HDC dc_handle, UINT type) {
        return GetCurrentObject(dc_handle, type);
    }

    HGDIOBJ dc::select_object(HDC dc_handle, HGDIOBJ gdi_obj_handle) {
        return SelectObject(dc_handle, gdi_obj_handle);
    }

    bool dc::delete_object(HGDIOBJ gdi_obj_handle) {
        return DeleteObject(gdi_obj_handle);
    }

    int dc::enum_objects(HDC dc_handle, int type, GOBJENUMPROC func, LPARAM l_param) {
        return EnumObjects(dc_handle, type, func, l_param);
    }

    int dc::get_device_caps(HDC dc_handle, int index) {
        return GetDeviceCaps(dc_handle, index);
    }

    int dc::device_capabilities(const wchar_t *device_name,
                                const wchar_t *port,
                                WORD capability,
                                wchar_t *output,
                                const DEVMODEW *device_mode) {
        return DeviceCapabilitiesW(device_name,
                                   port,
                                   capability,
                                   output,
                                   device_mode);
    }

    int dc::draw_escape(HDC dc_handle, int escape_func, int in_size, const char *in) {
        return DrawEscape(dc_handle, escape_func, in_size, in);
    }
}
