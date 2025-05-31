//
// Created by forkernel on 2025/5/31.
//

#include "scroll.h"
#include <windowsx.h>
#include "helper/convert.h"
namespace YanLib::components {
    HWND scroll::create(uintptr_t scroll_id,
                        HWND parent_window_handle,
                        LPARAM lparam,
                        int32_t x,
                        int32_t y,
                        int32_t width,
                        int32_t height,
                        ScrollStyle style,
                        WindowStyle window_style) {
        HWND result = CreateWindowExW(0L, L"ScrollBar", nullptr,
                                      static_cast<uint32_t>(window_style) |
                                              static_cast<uint32_t>(style),
                                      x, y, width, height, parent_window_handle,
                                      reinterpret_cast<HMENU>(scroll_id),
                                      reinterpret_cast<CREATESTRUCT *>(lparam)
                                              ->hInstance,
                                      nullptr);
        if (!result) {
            error_code = GetLastError();
        }
        return result;
    }

    HWND scroll::create(const char *scroll_name,
                        uintptr_t scroll_id,
                        HWND parent_window_handle,
                        LPARAM lparam,
                        int32_t x,
                        int32_t y,
                        int32_t width,
                        int32_t height,
                        ScrollStyle style,
                        WindowStyle window_style) {
        HWND result = CreateWindowExA(0L, "ScrollBar", scroll_name,
                                      static_cast<uint32_t>(window_style) |
                                              static_cast<uint32_t>(style),
                                      x, y, width, height, parent_window_handle,
                                      reinterpret_cast<HMENU>(scroll_id),
                                      reinterpret_cast<CREATESTRUCT *>(lparam)
                                              ->hInstance,
                                      nullptr);
        if (!result) {
            error_code = GetLastError();
        }
        return result;
    }

    HWND scroll::create(const wchar_t *scroll_name,
                        uintptr_t scroll_id,
                        HWND parent_window_handle,
                        LPARAM lparam,
                        int32_t x,
                        int32_t y,
                        int32_t width,
                        int32_t height,
                        ScrollStyle style,
                        WindowStyle window_style) {
        HWND result = CreateWindowExW(0L, L"ScrollBar", scroll_name,
                                      static_cast<uint32_t>(window_style) |
                                              static_cast<uint32_t>(style),
                                      x, y, width, height, parent_window_handle,
                                      reinterpret_cast<HMENU>(scroll_id),
                                      reinterpret_cast<CREATESTRUCT *>(lparam)
                                              ->hInstance,
                                      nullptr);
        if (!result) {
            error_code = GetLastError();
        }
        return result;
    }

    bool scroll::enable(HWND window_handle,
                        ScrollType scroll_type,
                        ArrowType arrow_type) {
        if (!EnableScrollBar(window_handle, static_cast<uint32_t>(scroll_type),
                             static_cast<uint32_t>(arrow_type))) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool scroll::show(HWND window_handle, ScrollType scroll_type) {
        if (!ShowScrollBar(window_handle, static_cast<int32_t>(scroll_type),
                           TRUE)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool scroll::hide(HWND window_handle, ScrollType scroll_type) {
        if (!ShowScrollBar(window_handle, static_cast<int32_t>(scroll_type),
                           FALSE)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool scroll::get_info(HWND window_handle,
                          SCROLLBARINFO *scroll_bar_info,
                          ObjectID object_id) {
        if (!GetScrollBarInfo(window_handle, static_cast<int32_t>(object_id),
                              scroll_bar_info)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool scroll::get_info(HWND window_handle,
                          SCROLLINFO *scroll_info,
                          ScrollType scroll_type) {
        if (!GetScrollInfo(window_handle, static_cast<int32_t>(scroll_type),
                           scroll_info)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    int32_t scroll::set_info(HWND window_handle,
                             SCROLLINFO *scroll_info,
                             ScrollType scroll_type,
                             bool is_redraw) {
        return SetScrollInfo(window_handle, static_cast<int32_t>(scroll_type),
                             scroll_info, is_redraw ? TRUE : FALSE);
    }

    int32_t scroll::get_pos(HWND window_handle, ScrollType scroll_type) {
        int32_t result =
                GetScrollPos(window_handle, static_cast<int32_t>(scroll_type));
        if (!result) {
            error_code = GetLastError();
        }
        return result;
    }

    int32_t scroll::set_pos(HWND window_handle,
                            int32_t pos,
                            ScrollType scroll_type,
                            bool is_redraw) {
        int32_t result =
                SetScrollPos(window_handle, static_cast<int32_t>(scroll_type),
                             pos, is_redraw ? TRUE : FALSE);
        if (!result) {
            error_code = GetLastError();
        }
        return result;
    }

    bool scroll::get_range(HWND window_handle,
                           int32_t *min_pos,
                           int32_t *max_pos,
                           ScrollType scroll_type) {
        if (!GetScrollRange(window_handle, static_cast<int32_t>(scroll_type),
                            min_pos, max_pos)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool scroll::set_range(HWND window_handle,
                           int32_t min_pos,
                           int32_t max_pos,
                           ScrollType scroll_type,
                           bool is_redraw) {
        if (!SetScrollRange(window_handle, static_cast<int32_t>(scroll_type),
                            min_pos, max_pos, is_redraw ? TRUE : FALSE)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool scroll::scroll_dc(HDC dc_handle,
                           int32_t x,
                           int32_t y,
                           const RECT *rect_scroll,
                           const RECT *rect_clip,
                           HRGN region_update_handle,
                           RECT *rect_update) {
        if (!ScrollDC(dc_handle, x, y, rect_scroll, rect_clip,
                      region_update_handle, rect_update)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool scroll::scroll_window(HWND window_handle,
                               int32_t x_amount,
                               int32_t y_amount,
                               const RECT *rect,
                               const RECT *clip_rect) {
        if (!ScrollWindow(window_handle, x_amount, y_amount, rect, clip_rect)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    int32_t scroll::scroll_window_extend(HWND window_handle,
                                         int32_t dx,
                                         int32_t dy,
                                         const RECT *rect_scroll,
                                         const RECT *rect_clip,
                                         HRGN region_handle_update,
                                         RECT *rect_update,
                                         ScrollFlag flag) {
        int32_t result =
                ScrollWindowEx(window_handle, dx, dy, rect_scroll, rect_clip,
                               region_handle_update, rect_update,
                               static_cast<uint32_t>(flag));
        if (!result) {
            error_code = GetLastError();
        }
        return result;
    }

    uint32_t scroll::err_code() const {
        return error_code;
    }

    std::string scroll::err_string() const {
        std::string result = helper::convert::err_string(error_code);
        return result;
    }

    std::wstring scroll::err_wstring() const {
        std::wstring result = helper::convert::err_wstring(error_code);
        return result;
    }
} // namespace YanLib::components
