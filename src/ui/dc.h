//
// Created by forkernel on 2025/5/2.
//

#ifndef DC_H
#define DC_H
#include <Windows.h>

namespace YanLib::ui {
    class dc {
    public:
        dc(const dc &other) = delete;

        dc(dc &&other) = delete;

        dc &operator=(const dc &other) = delete;

        dc &operator=(dc &&other) = delete;

        dc() = default;

        ~dc() = default;

        static HDC create_dc(const wchar_t *driver_name,
                             const wchar_t *device_name,
                             const wchar_t *port,
                             const DEVMODEW *device_mode);

        static HDC create_compatible_dc(HDC dc_handle);

        static HDC create_ic(const wchar_t *driver_name,
                             const wchar_t *device_name,
                             const wchar_t *port,
                             const DEVMODEW *device_mode);

        static HDC get_dc(HWND hwnd);

        static HDC get_dc(HWND hwnd, HRGN region_clip_handle, DWORD flag);

        static int release_dc(HWND hwnd, HDC dc_handle);

        static bool delete_dc(HDC dc_handle);

        static HDC get_window_dc(HWND hwnd);

        static HWND window_from_dc(HDC dc_handle);

        static bool scroll_dc(HDC dc_handle,
                              int x,
                              int y,
                              const RECT *rect_scroll,
                              const RECT *rect_clip,
                              HRGN region_update_handle,
                              LPRECT rect_update);

        static bool cancel_dc(HDC dc_handle);

        static HDC reset_dc(HDC dc_handle, const DEVMODEW *device_mode);

        static int save_dc(HDC dc_handle);

        static bool restore_dc(HDC dc_handle, int saved_dc_state);

        static COLORREF get_dc_brush_color(HDC dc_handle);

        static COLORREF set_dc_brush_color(HDC dc_handle, COLORREF color);

        static bool get_dc_org(HDC dc_handle, LPPOINT point);

        static COLORREF get_dc_pen_color(HDC dc_handle);

        static COLORREF set_dc_pen_color(HDC dc_handle, COLORREF color);

        static DWORD get_layout(HDC dc_handle);

        static DWORD set_layout(HDC dc_handle, DWORD value);

        static int get_object(HANDLE gdi_handle, int size, void *buf);

        static DWORD get_object_type(HGDIOBJ gdi_obj_handle);

        static HGDIOBJ get_stock_object(int type);

        static HGDIOBJ get_current_object(HDC dc_handle, UINT type);

        static HGDIOBJ select_object(HDC dc_handle, HGDIOBJ gdi_obj_handle);

        static bool delete_object(HGDIOBJ gdi_obj_handle);

        static int enum_objects(HDC dc_handle,
                                int type,
                                GOBJENUMPROC func,
                                LPARAM l_param);

        static int get_device_caps(HDC dc_handle, int index);

        static int device_capabilities(const wchar_t *device_name,
                                       const wchar_t *port,
                                       WORD capability,
                                       wchar_t *output,
                                       const DEVMODEW *device_mode);

        static int draw_escape(HDC dc_handle,
                               int escape_func,
                               int in_size,
                               const char *in);
    };
}
#endif //DC_H
