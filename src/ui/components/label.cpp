//
// Created by forkernel on 2025/5/31.
//

#include "label.h"
#include <windowsx.h>
#include "helper/convert.h"
namespace YanLib::components {
    HWND label::create(uintptr_t label_id,
                       HWND parent_window_handle,
                       LPARAM lparam,
                       int32_t x,
                       int32_t y,
                       int32_t width,
                       int32_t height,
                       LabelStyle style,
                       WindowStyle window_style) {
        HWND result = CreateWindowExW(0L, L"Static", nullptr,
                                      static_cast<uint32_t>(window_style) |
                                              static_cast<uint32_t>(style),
                                      x, y, width, height, parent_window_handle,
                                      reinterpret_cast<HMENU>(label_id),
                                      reinterpret_cast<CREATESTRUCT *>(lparam)
                                              ->hInstance,
                                      nullptr);
        if (!result) {
            error_code = GetLastError();
        }
        return result;
    }

    HWND label::create(const char *label_name,
                       uintptr_t label_id,
                       HWND parent_window_handle,
                       LPARAM lparam,
                       int32_t x,
                       int32_t y,
                       int32_t width,
                       int32_t height,
                       LabelStyle style,
                       WindowStyle window_style) {
        HWND result = CreateWindowExA(0L, "Static", label_name,
                                      static_cast<uint32_t>(window_style) |
                                              static_cast<uint32_t>(style),
                                      x, y, width, height, parent_window_handle,
                                      reinterpret_cast<HMENU>(label_id),
                                      reinterpret_cast<CREATESTRUCT *>(lparam)
                                              ->hInstance,
                                      nullptr);
        if (!result) {
            error_code = GetLastError();
        }
        return result;
    }

    HWND label::create(const wchar_t *label_name,
                       uintptr_t label_id,
                       HWND parent_window_handle,
                       LPARAM lparam,
                       int32_t x,
                       int32_t y,
                       int32_t width,
                       int32_t height,
                       LabelStyle style,
                       WindowStyle window_style) {
        HWND result = CreateWindowExW(0L, L"Static", label_name,
                                      static_cast<uint32_t>(window_style) |
                                              static_cast<uint32_t>(style),
                                      x, y, width, height, parent_window_handle,
                                      reinterpret_cast<HMENU>(label_id),
                                      reinterpret_cast<CREATESTRUCT *>(lparam)
                                              ->hInstance,
                                      nullptr);
        if (!result) {
            error_code = GetLastError();
        }
        return result;
    }

    bool label::enable(HWND label_handle) {
        return Static_Enable(label_handle, TRUE);
    }

    bool label::disable(HWND label_handle) {
        return Static_Enable(label_handle, FALSE);
    }

    HICON label::get_icon(HWND label_handle) {
        return reinterpret_cast<HICON>(
                SendMessageW(label_handle, STM_GETICON, 0, 0));
    }

    HICON label::set_icon(HWND label_handle, HICON icon_handle) {
        return Static_SetIcon(label_handle, icon_handle);
    }

    HBITMAP label::get_bitmap(HWND label_handle) {
        return reinterpret_cast<HBITMAP>(
                SendMessageW(label_handle, STM_GETIMAGE, IMAGE_BITMAP, 0));
    }

    HBITMAP label::set_bitmap(HWND label_handle, HBITMAP bitmap_handle) {
        return reinterpret_cast<HBITMAP>(
                SendMessageW(label_handle, STM_SETIMAGE, IMAGE_BITMAP,
                             reinterpret_cast<LPARAM>(bitmap_handle)));
    }

    HCURSOR label::get_cursor(HWND label_handle) {
        return reinterpret_cast<HCURSOR>(
                SendMessageW(label_handle, STM_GETIMAGE, IMAGE_CURSOR, 0));
    }

    HCURSOR label::set_cursor(HWND label_handle, HCURSOR cursor_handle) {
        return reinterpret_cast<HCURSOR>(
                SendMessageW(label_handle, STM_SETIMAGE, IMAGE_CURSOR,
                             reinterpret_cast<LPARAM>(cursor_handle)));
    }

    HENHMETAFILE label::get_enh_metafile(HWND label_handle) {
        return reinterpret_cast<HENHMETAFILE>(
                SendMessageW(label_handle, STM_GETIMAGE, IMAGE_ENHMETAFILE, 0));
    }

    HENHMETAFILE label::set_enh_metafile(HWND label_handle,
                                         HENHMETAFILE enh_metafile_handle) {
        return reinterpret_cast<HENHMETAFILE>(
                SendMessageW(label_handle, STM_SETIMAGE, IMAGE_ENHMETAFILE,
                             reinterpret_cast<LPARAM>(enh_metafile_handle)));
    }

    int32_t label::get_text(HWND label_handle, std::string &text) {
        int32_t result = GetWindowTextA(label_handle, text.data(),
                                        static_cast<int32_t>(text.size()));
        if (!result) {
            error_code = GetLastError();
        }
        return result;
    }

    int32_t label::get_text(HWND label_handle, std::wstring &text) {
        int32_t result = GetWindowTextW(label_handle, text.data(),
                                        static_cast<int32_t>(text.size()));
        if (!result) {
            error_code = GetLastError();
        }
        return result;
    }

    int32_t label::set_text(HWND label_handle, const std::string &text) {
        int32_t result = SetWindowTextA(label_handle, text.data());
        if (!result) {
            error_code = GetLastError();
        }
        return result;
    }

    int32_t label::set_text(HWND label_handle, const std::wstring &text) {
        int32_t result = SetWindowTextW(label_handle, text.data());
        if (!result) {
            error_code = GetLastError();
        }
        return result;
    }

    int32_t label::get_text_len(HWND label_handle) {
        int32_t result = GetWindowTextLengthA(label_handle);
        if (!result) {
            error_code = GetLastError();
        }
        return result;
    }

    uint32_t label::err_code() const {
        return error_code;
    }

    std::string label::err_string() const {
        std::string result = helper::convert::err_string(error_code);
        return result;
    }

    std::wstring label::err_wstring() const {
        std::wstring result = helper::convert::err_wstring(error_code);
        return result;
    }
} // namespace YanLib::components
