//
// Created by forkernel on 2025/5/2.
//

#ifndef DC_H
#define DC_H
#include <utility>
#include <Windows.h>

namespace YanLib::ui::gdi {
    class dc {
    public:
        dc(const dc &other) = delete;

        dc(dc &&other) = delete;

        dc &operator=(const dc &other) = delete;

        dc &operator=(dc &&other) = delete;

        dc() = default;

        ~dc() = default;

        static HDC create_dc(const char* driver_name,
                             const char* device_name,
                             const char* port,
                             const DEVMODEA* device_mode);

        static HDC create_dc(const wchar_t* driver_name,
                             const wchar_t* device_name,
                             const wchar_t* port,
                             const DEVMODEW* device_mode);

        static HDC create_compatible_dc(HDC dc_handle);

        static HDC create_ic(const char* driver_name,
                             const char* device_name,
                             const char* port,
                             const DEVMODEA* device_mode);

        static HDC create_ic(const wchar_t* driver_name,
                             const wchar_t* device_name,
                             const wchar_t* port,
                             const DEVMODEW* device_mode);

        static HDC get_dc(HWND window_handle);

        static HDC
        get_dc(HWND window_handle, HRGN region_clip_handle, uint32_t flag);

        static int32_t release_dc(HWND window_handle, HDC dc_handle);

        static bool delete_dc(HDC dc_handle);

        // std::pair<result, error_code>
        static std::pair<bool, uint32_t> scroll_dc(HDC dc_handle,
                                                   int32_t x,
                                                   int32_t y,
                                                   const RECT* rect_scroll,
                                                   const RECT* rect_clip,
                                                   HRGN region_update_handle,
                                                   RECT* rect_update);

        // std::pair<result, error_code>
        static std::pair<uint32_t, uint32_t> get_layout(HDC dc_handle);

        static uint32_t set_layout(HDC dc_handle, uint32_t value);

        static HDC get_window_dc(HWND window_handle);

        static HWND window_from_dc(HDC dc_handle);

        static bool cancel_dc(HDC dc_handle);

        static HDC reset_dc(HDC dc_handle, const DEVMODEA* device_mode);

        static HDC reset_dc(HDC dc_handle, const DEVMODEW* device_mode);

        static int32_t save_dc(HDC dc_handle);

        static bool restore_dc(HDC dc_handle, int32_t saved_dc_state);

        static COLORREF get_dc_brush_color(HDC dc_handle);

        static COLORREF set_dc_brush_color(HDC dc_handle, COLORREF color);

        static bool get_dc_org(HDC dc_handle, POINT* point);

        static COLORREF get_dc_pen_color(HDC dc_handle);

        static COLORREF set_dc_pen_color(HDC dc_handle, COLORREF color);

        static int32_t get_object(HANDLE gdi_handle, int32_t size, void* buf);

        static uint32_t get_object_type(HGDIOBJ gdi_obj_handle);

        static HGDIOBJ get_stock_object(int32_t type);

        static HGDIOBJ get_current_object(HDC dc_handle, uint32_t type);

        static HGDIOBJ select_object(HDC dc_handle, HGDIOBJ gdi_obj_handle);

        static bool delete_object(HGDIOBJ gdi_obj_handle);

        static int32_t enum_objects(HDC dc_handle,
                                    int32_t type,
                                    GOBJENUMPROC func,
                                    LPARAM lparam);

        static int32_t get_device_caps(HDC dc_handle, int32_t index);

        static int32_t device_capabilities(const char* device_name,
                                           const char* port,
                                           uint16_t capability,
                                           char* output,
                                           const DEVMODEA* device_mode);

        static int32_t device_capabilities(const wchar_t* device_name,
                                           const wchar_t* port,
                                           uint16_t capability,
                                           wchar_t* output,
                                           const DEVMODEW* device_mode);

        static int32_t draw_escape(HDC dc_handle,
                                   int32_t escape_func,
                                   int32_t size,
                                   const char* buf);
    };
} // namespace YanLib::ui::gdi
#endif // DC_H
