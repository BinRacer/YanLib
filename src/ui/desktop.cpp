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
        if (!CloseDesktop(desktop_handle)) {
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

    HWINSTA desktop::create_window_station(const wchar_t *window_station_name,
                                           DWORD flag,
                                           ACCESS_MASK desired_access,
                                           LPSECURITY_ATTRIBUTES security_attrs) {
        HWINSTA result = CreateWindowStationW(window_station_name,
                                              flag,
                                              desired_access,
                                              security_attrs);
        if (!result) {
            error_code = GetLastError();
        }
        return result;
    }

    HWINSTA desktop::open_window_station(const wchar_t *window_station_name,
                                         bool is_inherit,
                                         ACCESS_MASK desired_access) {
        HWINSTA result = OpenWindowStationW(window_station_name,
                                            is_inherit ? TRUE : FALSE,
                                            desired_access);
        if (!result) {
            error_code = GetLastError();
        }
        return result;
    }

    bool desktop::close_window_station(HWINSTA window_station_handle) {
        if (!CloseWindowStation(window_station_handle)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool desktop::enum_window_stations(WINSTAENUMPROCW enum_func, LPARAM param) {
        if (!EnumWindowStationsW(enum_func, param)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    HWINSTA desktop::get_process_window_station() {
        HWINSTA result = GetProcessWindowStation();
        if (!result) {
            error_code = GetLastError();
        }
        return result;
    }

    bool desktop::set_process_window_station(HWINSTA window_station_handle) {
        if (!SetProcessWindowStation(window_station_handle)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool desktop::get_user_object_info(HANDLE desktop_or_window_station_handle,
                                       int index,
                                       void *info,
                                       DWORD len,
                                       LPDWORD ret_len) {
        if (!GetUserObjectInformationW(desktop_or_window_station_handle,
                                       index,
                                       info,
                                       len,
                                       ret_len)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool
    desktop::set_user_object_information(HANDLE desktop_or_window_station_handle,
                                         int index,
                                         void *info,
                                         DWORD len) {
        if (!SetUserObjectInformationW(desktop_or_window_station_handle,
                                       index,
                                       info,
                                       len)) {
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
