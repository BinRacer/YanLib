/* clang-format off */
/*
 * @file dc.h
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
#ifndef DC_H
#define DC_H
#include <Windows.h>
#include <minwindef.h>
#include <wingdi.h>
#include <windef.h>
#include <utility>
#include "ui/core/core.h"
#include "gdi.h"
namespace YanLib::ui::gdi {
    class dc {
    public:
        dc(const dc &other) = delete;

        dc(dc &&other) = delete;

        dc &operator=(const dc &other) = delete;

        dc &operator=(dc &&other) = delete;

        dc() = default;

        ~dc() = default;

        static HDC create(const char *driver_name /* "DISPLAY" */,
                          const char *device_name = nullptr,
                          const DEVMODEA *device_mode = nullptr);

        static HDC create(const wchar_t *driver_name /* L"DISPLAY" */,
                          const wchar_t *device_name = nullptr,
                          const DEVMODEW *device_mode = nullptr);

        static HDC create_compatible(HDC dc_handle);

        static HDC create_ic(const char *driver_name /* L"WINSPOOL" */,
                             const char *device_name
                             /* L"Microsoft Print to PDF" */,
                             const DEVMODEA *device_mode = nullptr);

        static HDC create_ic(const wchar_t *driver_name /* L"WINSPOOL" */,
                             const wchar_t *device_name
                             /* L"Microsoft Print to PDF" */,
                             const DEVMODEW *device_mode = nullptr);

        static HDC get(HWND window_handle);

        static HDC get(HWND window_handle,
                       HRGN region_clip_handle /* nullptr */,
                       DCFlag flag = DCFlag::Window | DCFlag::Cache |
                               DCFlag::ClipSiblings);

        static int32_t release(HWND window_handle, HDC dc_handle);

        static bool destroy(HDC dc_handle);

        // std::pair<result, error_code>
        static std::pair<bool, uint32_t>
        scroll(HDC dc_handle,
               int32_t x,
               int32_t y,
               const RECT *rect_scroll,
               const RECT *rect_clip = nullptr,
               HRGN region_update_handle = nullptr,
               RECT *rect_update = nullptr);

        // std::pair<core::Layout, error_code>
        static std::pair<core::Layout, uint32_t> get_layout(HDC dc_handle);

        static core::Layout set_layout(HDC dc_handle, core::Layout layout);

        static HDC get_window_dc(HWND window_handle);

        static HWND get_window(HDC dc_handle);

        static bool cancel(HDC dc_handle);

        static HDC reset(HDC dc_handle, const DEVMODEA *device_mode);

        static HDC reset(HDC dc_handle, const DEVMODEW *device_mode);

        static int32_t save(HDC dc_handle);

        static bool restore(HDC dc_handle, int32_t saved_dc_state);

        static COLORREF get_brush_color(HDC dc_handle);

        static COLORREF set_brush_color(HDC dc_handle, COLORREF color);

        static bool get_origin(HDC dc_handle, POINT *point);

        static COLORREF get_pen_color(HDC dc_handle);

        static COLORREF set_pen_color(HDC dc_handle, COLORREF color);

        static int32_t get_object(HANDLE gdi_handle, void *buf, int32_t size);

        static ObjectType get_object_type(HGDIOBJ gdi_obj_handle);

        static HGDIOBJ get_stock_object(StockLogicalObject type);

        static HGDIOBJ get_curr_object(HDC dc_handle, ObjectType type);

        static HGDIOBJ select_object(HDC dc_handle, HGDIOBJ gdi_obj_handle);

        static bool destroy_object(HGDIOBJ gdi_obj_handle);

        static int32_t enum_objects(HDC dc_handle,
                                    GOBJENUMPROC func,
                                    LPARAM lparam,
                                    ObjectType type);

        static int32_t get_device_caps(HDC dc_handle, DeviceParameter param);

        static int32_t device_capabilities(
                const char *device_name /* "Microsoft Print to PDF" */,
                const char *port /* "PORTPROMPT:" */,
                DeviceCapability capability /* DeviceCapability::PaperNames */,
                char *output,
                const DEVMODEA *device_mode = nullptr);

        static int32_t device_capabilities(
                const wchar_t *device_name /* L"Microsoft Print to PDF" */,
                const wchar_t *port /* L"PORTPROMPT:" */,
                DeviceCapability capability /* DeviceCapability::PaperNames */,
                wchar_t *output,
                const DEVMODEW *device_mode = nullptr);

        static int32_t draw_escape(HDC dc_handle,
                                   int32_t escape_func,
                                   const char *buf,
                                   int32_t size);
    };
} // namespace YanLib::ui::gdi
#endif // DC_H
