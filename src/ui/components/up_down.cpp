//
// Created by forkernel on 2025/6/4.
//

#include "up_down.h"
#include <windowsx.h>
#include "helper/convert.h"
namespace YanLib::ui::components {
    HWND up_down::create(uintptr_t up_down_id,
                         HWND parent_window_handle,
                         LPARAM lparam,
                         int32_t x,
                         int32_t y,
                         int32_t width,
                         int32_t height,
                         UpDownStyle style,
                         WindowStyle window_style) {
        INITCOMMONCONTROLSEX icc = {};
        icc.dwSize = sizeof(INITCOMMONCONTROLSEX);
        icc.dwICC = ICC_UPDOWN_CLASS;
        InitCommonControlsEx(&icc);
        HWND result = CreateWindowExW(0L, L"msctls_updown32", nullptr,
                                      static_cast<uint32_t>(window_style) |
                                              static_cast<uint32_t>(style),
                                      x, y, width, height, parent_window_handle,
                                      reinterpret_cast<HMENU>(up_down_id),
                                      reinterpret_cast<CREATESTRUCT *>(lparam)
                                              ->hInstance,
                                      nullptr);
        if (!result) {
            error_code = GetLastError();
        }
        return result;
    }

    HWND up_down::create(const char *up_down_name,
                         uintptr_t up_down_id,
                         HWND parent_window_handle,
                         LPARAM lparam,
                         int32_t x,
                         int32_t y,
                         int32_t width,
                         int32_t height,
                         UpDownStyle style,
                         WindowStyle window_style) {
        INITCOMMONCONTROLSEX icc = {};
        icc.dwSize = sizeof(INITCOMMONCONTROLSEX);
        icc.dwICC = ICC_UPDOWN_CLASS;
        InitCommonControlsEx(&icc);
        HWND result = CreateWindowExA(0L, "msctls_updown32", up_down_name,
                                      static_cast<uint32_t>(window_style) |
                                              static_cast<uint32_t>(style),
                                      x, y, width, height, parent_window_handle,
                                      reinterpret_cast<HMENU>(up_down_id),
                                      reinterpret_cast<CREATESTRUCT *>(lparam)
                                              ->hInstance,
                                      nullptr);
        if (!result) {
            error_code = GetLastError();
        }
        return result;
    }

    HWND up_down::create(const wchar_t *up_down_name,
                         uintptr_t up_down_id,
                         HWND parent_window_handle,
                         LPARAM lparam,
                         int32_t x,
                         int32_t y,
                         int32_t width,
                         int32_t height,
                         UpDownStyle style,
                         WindowStyle window_style) {
        INITCOMMONCONTROLSEX icc = {};
        icc.dwSize = sizeof(INITCOMMONCONTROLSEX);
        icc.dwICC = ICC_UPDOWN_CLASS;
        InitCommonControlsEx(&icc);
        HWND result = CreateWindowExW(0L, L"msctls_updown32", up_down_name,
                                      static_cast<uint32_t>(window_style) |
                                              static_cast<uint32_t>(style),
                                      x, y, width, height, parent_window_handle,
                                      reinterpret_cast<HMENU>(up_down_id),
                                      reinterpret_cast<CREATESTRUCT *>(lparam)
                                              ->hInstance,
                                      nullptr);
        if (!result) {
            error_code = GetLastError();
        }
        return result;
    }

    HWND up_down::get_buddy(HWND up_down_handle) {
        return reinterpret_cast<HWND>(
                SendMessageW(up_down_handle, UDM_GETBUDDY, 0, 0));
    }

    HWND up_down::set_buddy(HWND up_down_handle, HWND buddy_handle) {
        return reinterpret_cast<HWND>(
                SendMessageW(up_down_handle, UDM_SETBUDDY,
                             reinterpret_cast<WPARAM>(buddy_handle), 0));
    }

    int64_t up_down::get_accel(HWND up_down_handle,
                               std::vector<UDACCEL> &accel) {
        return SendMessageW(up_down_handle, UDM_GETACCEL, accel.size(),
                            reinterpret_cast<LPARAM>(accel.data()));
    }

    bool up_down::set_accel(HWND up_down_handle, std::vector<UDACCEL> &accel) {
        return SendMessageW(up_down_handle, UDM_SETACCEL, accel.size(),
                            reinterpret_cast<LPARAM>(accel.data()));
    }

    int64_t up_down::get_base(HWND up_down_handle) {
        return SendMessageW(up_down_handle, UDM_GETBASE, 0, 0);
    }

    int64_t up_down::set_base(HWND up_down_handle, int64_t base) {
        return SendMessageW(up_down_handle, UDM_SETBASE, base, 0);
    }

    std::pair<bool, uint16_t> up_down::get_pos(HWND up_down_handle) {
        auto result = static_cast<uint32_t>(
                SendMessageW(up_down_handle, UDM_GETPOS, 0, 0));
        return std::make_pair(!(HIWORD(result)), LOWORD(result));
    }

    uint16_t up_down::set_pos(HWND up_down_handle, uint16_t pos) {
        return SendMessageW(up_down_handle, UDM_SETPOS, 0, pos);
    }

    uint32_t up_down::get_pos32(HWND up_down_handle, bool *is_ok) {
        return static_cast<uint32_t>(
                SendMessageW(up_down_handle, UDM_GETPOS32, 0,
                             reinterpret_cast<LPARAM>(is_ok)));
    }

    uint32_t up_down::set_pos32(HWND up_down_handle, uint32_t pos) {
        return SendMessageW(up_down_handle, UDM_SETPOS32, 0, pos);
    }

    std::pair<uint16_t, uint16_t> up_down::get_range(HWND up_down_handle) {
        auto result = static_cast<uint32_t>(
                SendMessageW(up_down_handle, UDM_GETRANGE, 0, 0));
        return std::make_pair(HIWORD(result), LOWORD(result));
    }

    void up_down::set_range(HWND up_down_handle, uint16_t min, uint16_t max) {
        SendMessageW(up_down_handle, UDM_SETRANGE, 0, MAKELPARAM(max, min));
    }

    void
    up_down::get_range32(HWND up_down_handle, uint32_t *min, uint32_t *max) {
        SendMessageW(up_down_handle, UDM_GETRANGE32,
                     reinterpret_cast<WPARAM>(min),
                     reinterpret_cast<LPARAM>(max));
    }

    void up_down::set_range32(HWND up_down_handle, uint32_t min, uint32_t max) {
        SendMessageW(up_down_handle, UDM_SETRANGE32, min, max);
    }

    bool up_down::is_ansi_format(HWND up_down_handle) {
        return !SendMessageW(up_down_handle, UDM_GETUNICODEFORMAT, 0, 0);
    }

    bool up_down::is_unicode_format(HWND up_down_handle) {
        return SendMessageW(up_down_handle, UDM_GETUNICODEFORMAT, 0, 0);
    }

    void up_down::set_ansi_format(HWND up_down_handle) {
        SendMessageW(up_down_handle, UDM_SETUNICODEFORMAT, FALSE, 0);
    }

    void up_down::set_unicode_format(HWND up_down_handle) {
        SendMessageW(up_down_handle, UDM_SETUNICODEFORMAT, TRUE, 0);
    }

    uint32_t up_down::err_code() const {
        return error_code;
    }

    std::string up_down::err_string() const {
        std::string result = helper::convert::err_string(error_code);
        return result;
    }

    std::wstring up_down::err_wstring() const {
        std::wstring result = helper::convert::err_wstring(error_code);
        return result;
    }
} // namespace YanLib::ui::components
