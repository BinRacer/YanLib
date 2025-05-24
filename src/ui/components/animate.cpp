//
// Created by forkernel on 2025/5/24.
//

#include "animate.h"
#include <windowsx.h>
namespace YanLib::components {
    HWND animate::create(uintptr_t animate_id,
                         HWND parent_window_handle,
                         LPARAM lparam,
                         AnimateStyle style,
                         WindowStyle window_style) {
        HWND result = CreateWindowExW(0L, L"SysAnimate32", nullptr,
                                      static_cast<uint32_t>(window_style) |
                                              static_cast<uint32_t>(style),
                                      0, 0, 0, 0, parent_window_handle,
                                      reinterpret_cast<HMENU>(animate_id),
                                      reinterpret_cast<CREATESTRUCT *>(lparam)
                                              ->hInstance,
                                      nullptr);
        if (!result) {
            error_code = GetLastError();
        }
        return result;
    }

    bool animate::open(HWND animate_handle,
                       char *file_name,
                       helper::CodePage code_page) {
        return Animate_Open(animate_handle,
                            helper::convert::str_to_wstr(file_name, code_page)
                                    .data());
    }

    bool animate::open(HWND animate_handle, wchar_t *file_name) {
        return Animate_Open(animate_handle, file_name);
    }

    bool animate::open(HWND animate_handle,
                       HINSTANCE dll_handle,
                       char *file_name,
                       helper::CodePage code_page) {
        return Animate_OpenEx(animate_handle, dll_handle,
                              helper::convert::str_to_wstr(file_name, code_page)
                                      .data());
    }

    bool animate::open(HWND animate_handle,
                       HINSTANCE dll_handle,
                       wchar_t *file_name) {
        return Animate_OpenEx(animate_handle, dll_handle, file_name);
    }

    void animate::close(HWND animate_handle) {
        Animate_Close(animate_handle);
    }

    bool animate::play(HWND animate_handle,
                       uint32_t from,
                       uint32_t to,
                       uint32_t repeat) {
        return Animate_Play(animate_handle, from, to, repeat);
    }

    bool animate::seek(HWND animate_handle, uint32_t frame_index) {
        return Animate_Seek(animate_handle, frame_index);
    }

    bool animate::stop(HWND animate_handle) {
        return Animate_Stop(animate_handle);
    }

    bool animate::is_playing(HWND animate_handle) {
        return Animate_IsPlaying(animate_handle);
    }

    uint32_t animate::err_code() const {
        return error_code;
    }

    std::string animate::err_string() const {
        std::string result = helper::convert::err_string(error_code);
        return result;
    }

    std::wstring animate::err_wstring() const {
        std::wstring result = helper::convert::err_wstring(error_code);
        return result;
    }
} // namespace YanLib::components
