/* clang-format off */
/*
 * @file desktop.cpp
 * @date 2025-05-01
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
#include "desktop.h"

#include <complex>

#include "helper/convert.h"

namespace YanLib::ui::core {
    desktop::~desktop() {
        for (auto &desktop : desktop_handles) {
            if (desktop) {
                CloseDesktop(desktop);
                desktop = nullptr;
            }
        }
        desktop_handles.clear();
    }

    HDESK desktop::create(const char *desktop_name,
                          bool allow_hook,
                          DesktopAccess access,
                          SECURITY_ATTRIBUTES *sa,
                          uint32_t heap_size) {
        HDESK result =
                CreateDesktopExA(desktop_name, nullptr, nullptr,
                                 allow_hook ? DF_ALLOWOTHERACCOUNTHOOK : 0,
                                 static_cast<uint32_t>(access), sa, heap_size,
                                 nullptr);
        if (!result) {
            error_code = GetLastError();
            return nullptr;
        }
        rwlock.write_lock();
        desktop_handles.push_back(result);
        rwlock.write_unlock();
        return result;
    }

    HDESK desktop::create(const wchar_t *desktop_name,
                          bool allow_hook,
                          DesktopAccess access,
                          SECURITY_ATTRIBUTES *sa,
                          uint32_t heap_size) {
        HDESK result =
                CreateDesktopExW(desktop_name, nullptr, nullptr,
                                 allow_hook ? DF_ALLOWOTHERACCOUNTHOOK : 0,
                                 static_cast<uint32_t>(access), sa, heap_size,
                                 nullptr);
        if (!result) {
            error_code = GetLastError();
            return nullptr;
        }
        rwlock.write_lock();
        desktop_handles.push_back(result);
        rwlock.write_unlock();
        return result;
    }

    HDESK desktop::open(const char *desktop_name,
                        bool allow_hook,
                        bool is_inherit,
                        DesktopAccess access) {
        HDESK result = OpenDesktopA(desktop_name,
                                    allow_hook ? DF_ALLOWOTHERACCOUNTHOOK : 0,
                                    is_inherit ? TRUE : FALSE,
                                    static_cast<uint32_t>(access));
        if (!result) {
            error_code = GetLastError();
            return nullptr;
        }
        rwlock.write_lock();
        desktop_handles.push_back(result);
        rwlock.write_unlock();
        return result;
    }

    HDESK desktop::open(const wchar_t *desktop_name,
                        bool allow_hook,
                        bool is_inherit,
                        DesktopAccess access) {
        HDESK result = OpenDesktopW(desktop_name,
                                    allow_hook ? DF_ALLOWOTHERACCOUNTHOOK : 0,
                                    is_inherit ? TRUE : FALSE,
                                    static_cast<uint32_t>(access));
        if (!result) {
            error_code = GetLastError();
            return nullptr;
        }
        rwlock.write_lock();
        desktop_handles.push_back(result);
        rwlock.write_unlock();
        return result;
    }

    HDESK
    desktop::open_input(uint32_t flag, bool is_inherit, DesktopAccess access) {
        HDESK result = OpenInputDesktop(flag, is_inherit ? TRUE : FALSE,
                                        static_cast<uint32_t>(access));
        if (!result) {
            error_code = GetLastError();
            return nullptr;
        }
        rwlock.write_lock();
        desktop_handles.push_back(result);
        rwlock.write_unlock();
        return result;
    }

    bool desktop::destroy(HDESK desktop_handle) {
        if (!desktop_handle) {
            return false;
        }
        rwlock.write_lock();
        const auto it = std::find(desktop_handles.begin(),
                                  desktop_handles.end(), desktop_handle);
        if (it != desktop_handles.end()) {
            *it = nullptr;
        }
        rwlock.write_unlock();
        if (!CloseDesktop(desktop_handle)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool
    desktop::enum_windows(HDESK desktop_handle, WNDENUMPROC fn, LPARAM lparam) {
        if (!EnumDesktopWindows(desktop_handle, fn, lparam)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool desktop::enum_desktops(HWINSTA window_station_handle,
                                DESKTOPENUMPROCA enum_func,
                                LPARAM lparam) {
        if (!EnumDesktopsA(window_station_handle, enum_func, lparam)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool desktop::enum_desktops(HWINSTA window_station_handle,
                                DESKTOPENUMPROCW enum_func,
                                LPARAM lparam) {
        if (!EnumDesktopsW(window_station_handle, enum_func, lparam)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    HWND desktop::get_window() {
        return GetDesktopWindow();
    }

    HDESK desktop::get_thread_desktop(uint32_t tid) {
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

    bool desktop::paint(HDC dc_handle) {
        return PaintDesktop(dc_handle);
    }

    bool desktop::switch_desktop(HDESK desktop_handle) {
        if (!SwitchDesktop(desktop_handle)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    uint32_t desktop::err_code() const {
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
} // namespace YanLib::ui::core

namespace YanLib::ui::core {
    window_station::~window_station() {
        for (auto &station : window_station_handles) {
            if (station) {
                CloseWindowStation(station);
                station = nullptr;
            }
        }
        window_station_handles.clear();
    }

    HWINSTA window_station::create(const char *window_station_name,
                                   uint32_t flag,
                                   StationAccess access,
                                   SECURITY_ATTRIBUTES *sa) {
        HWINSTA result =
                CreateWindowStationA(window_station_name, flag,
                                     static_cast<uint32_t>(access), sa);
        if (!result) {
            error_code = GetLastError();
            return nullptr;
        }
        rwlock.write_lock();
        window_station_handles.push_back(result);
        rwlock.write_unlock();
        return result;
    }

    HWINSTA window_station::create(const wchar_t *window_station_name,
                                   uint32_t flag,
                                   StationAccess access,
                                   SECURITY_ATTRIBUTES *sa) {
        HWINSTA result =
                CreateWindowStationW(window_station_name, flag,
                                     static_cast<uint32_t>(access), sa);
        if (!result) {
            error_code = GetLastError();
            return nullptr;
        }
        rwlock.write_lock();
        window_station_handles.push_back(result);
        rwlock.write_unlock();
        return result;
    }

    HWINSTA window_station::open(const char *window_station_name,
                                 bool is_inherit,
                                 StationAccess access) {
        HWINSTA result = OpenWindowStationA(window_station_name,
                                            is_inherit ? TRUE : FALSE,
                                            static_cast<uint32_t>(access));
        if (!result) {
            error_code = GetLastError();
            return nullptr;
        }
        rwlock.write_lock();
        window_station_handles.push_back(result);
        rwlock.write_unlock();
        return result;
    }

    HWINSTA window_station::open(const wchar_t *window_station_name,
                                 bool is_inherit,
                                 StationAccess access) {
        HWINSTA result = OpenWindowStationW(window_station_name,
                                            is_inherit ? TRUE : FALSE,
                                            static_cast<uint32_t>(access));
        if (!result) {
            error_code = GetLastError();
            return nullptr;
        }
        rwlock.write_lock();
        window_station_handles.push_back(result);
        rwlock.write_unlock();
        return result;
    }

    bool window_station::destroy(HWINSTA window_station_handle) {
        if (!window_station_handle) {
            return false;
        }
        rwlock.write_lock();
        const auto it =
                std::find(window_station_handles.begin(),
                          window_station_handles.end(), window_station_handle);
        if (it != window_station_handles.end()) {
            *it = nullptr;
        }
        rwlock.write_unlock();
        if (!CloseWindowStation(window_station_handle)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool window_station::lock() {
        if (!LockWorkStation()) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool window_station::enum_window_stations(WINSTAENUMPROCA enum_func,
                                              LPARAM lparam) {
        if (!EnumWindowStationsA(enum_func, lparam)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool window_station::enum_window_stations(WINSTAENUMPROCW enum_func,
                                              LPARAM lparam) {
        if (!EnumWindowStationsW(enum_func, lparam)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    HWINSTA window_station::get_process_window_station() {
        HWINSTA result = GetProcessWindowStation();
        if (!result) {
            error_code = GetLastError();
        }
        return result;
    }

    bool
    window_station::set_process_window_station(HWINSTA window_station_handle) {
        if (!SetProcessWindowStation(window_station_handle)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool window_station::get_user_object_info(HANDLE desktop_or_station_handle,
                                              int32_t index,
                                              void *buf,
                                              uint32_t size,
                                              uint32_t *real_size) {
        if (!real_size) {
            error_code = STATUS_ACCESS_VIOLATION;
            return false;
        }
        unsigned long temp = *real_size;
        if (!GetUserObjectInformationW(desktop_or_station_handle, index, buf,
                                       size, &temp)) {
            error_code = GetLastError();
            *real_size = temp;
            return false;
        }
        *real_size = temp;
        return true;
    }

    bool window_station::set_user_object_info(HANDLE desktop_or_station_handle,
                                              int32_t index,
                                              void *buf,
                                              uint32_t size) {
        if (!SetUserObjectInformationW(desktop_or_station_handle, index, buf,
                                       size)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    uint32_t window_station::err_code() const {
        return error_code;
    }

    std::string window_station::err_string() const {
        std::string result = helper::convert::err_string(error_code);
        return result;
    }

    std::wstring window_station::err_wstring() const {
        std::wstring result = helper::convert::err_wstring(error_code);
        return result;
    }
} // namespace YanLib::ui::core
