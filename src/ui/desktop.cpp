//
// Created by forkernel on 2025/5/1.
//

#include "desktop.h"
#include "helper/convert.h"

namespace YanLib::ui {
    HDESK desktop::create_desktop(const wchar_t *desktop_name,
                                  DWORD flag,
                                  ACCESS_MASK desired_access,
                                  LPSECURITY_ATTRIBUTES security_attrs,
                                  ULONG heap_size) {
        HDESK result = CreateDesktopExW(desktop_name,
                                        nullptr,
                                        nullptr,
                                        flag,
                                        desired_access,
                                        security_attrs,
                                        heap_size,
                                        nullptr);
        if (!result) {
            error_code = GetLastError();
        }
        return result;
    }

    HDESK desktop::open_desktop(const wchar_t *desktop_name,
                                DWORD flag,
                                bool is_inherit,
                                ACCESS_MASK desired_access) {
        HDESK result = OpenDesktopW(desktop_name,
                                    flag,
                                    is_inherit ? TRUE : FALSE,
                                    desired_access);
        if (!result) {
            error_code = GetLastError();
        }
        return result;
    }

    HDESK desktop::open_input_desktop(DWORD flag,
                                      bool is_inherit,
                                      ACCESS_MASK desired_access) {
        HDESK result = OpenInputDesktop(flag,
                                        is_inherit ? TRUE : FALSE,
                                        desired_access);
        if (!result) {
            error_code = GetLastError();
        }
        return result;
    }

    bool desktop::close_desktop(HDESK desktop_handle) {
        if (!CloseHandle(desktop_handle)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool desktop::enum_desktops(HWINSTA window_station_handle,
                                DESKTOPENUMPROCW enum_func,
                                LPARAM param) {
        if (!EnumDesktopsW(window_station_handle,
                           enum_func,
                           param)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    HDESK desktop::get_thread_desktop(DWORD tid) {
        HDESK result = GetThreadDesktop(tid);
        if (!result) {
            error_code = GetLastError();
        }
        return result;
    }

    bool desktop::set_thread_desktop(HDESK desktop_handle) {
        if (!SetThreadDesktop(desktop_handle)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool desktop::paint_desktop(HDC hdc) {
        return PaintDesktop(hdc);
    }

    bool desktop::switch_desktop(HDESK desktop_handle) {
        if (!SwitchDesktop(desktop_handle)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    DWORD desktop::err_code() const {
        return error_code;
    }

    std::string desktop::err_string() const {
        std::string result = helper::convert::err_string(error_code);
        return result;
    }

    std::wstring desktop::err_wstring() const {
        std::wstring result = helper::convert::err_wstring(error_code);
        return result;
    }
}
