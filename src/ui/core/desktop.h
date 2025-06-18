/* clang-format off */
/*
 * @file desktop.h
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
#ifndef DESKTOP_H
#define DESKTOP_H
#include <Windows.h>
#include <WinUser.h>
#include <windef.h>
#include <winnt.h>
#include <minwinbase.h>
#include <string>
#include <vector>
#include "sync/rwlock.h"
#include "core.h"
namespace YanLib::ui::core {
    class desktop {
    private:
        std::vector<HDESK> desktop_handles = {};
        sync::rwlock rwlock = {};
        uint32_t error_code = 0;

    public:
        desktop(const desktop &other) = delete;

        desktop(desktop &&other) = delete;

        desktop &operator=(const desktop &other) = delete;

        desktop &operator=(desktop &&other) = delete;

        desktop() = default;

        ~desktop();

        HDESK create(const char *desktop_name,
                     bool allow_hook = false,
                     DesktopAccess access = DesktopAccess::CreateWindows |
                             DesktopAccess::ReadObjects |
                             DesktopAccess::WriteObjects,
                     SECURITY_ATTRIBUTES *sa = nullptr,
                     uint32_t heap_size = 1024);

        HDESK create(const wchar_t *desktop_name,
                     bool allow_hook = false,
                     DesktopAccess access = DesktopAccess::CreateWindows |
                             DesktopAccess::ReadObjects |
                             DesktopAccess::WriteObjects,
                     SECURITY_ATTRIBUTES *sa = nullptr,
                     uint32_t heap_size = 1024);

        HDESK open(const char *desktop_name,
                   bool allow_hook = false,
                   bool is_inherit = false,
                   DesktopAccess access = DesktopAccess::ReadObjects |
                           DesktopAccess::WriteObjects);

        HDESK open(const wchar_t *desktop_name,
                   bool allow_hook = false,
                   bool is_inherit = false,
                   DesktopAccess access = DesktopAccess::ReadObjects |
                           DesktopAccess::WriteObjects);

        HDESK open_input(uint32_t flag = 0,
                         bool is_inherit = false,
                         DesktopAccess access = DesktopAccess::ReadObjects |
                                 DesktopAccess::WriteObjects);

        bool destroy(HDESK desktop_handle);

        bool enum_windows(HDESK desktop_handle, WNDENUMPROC fn, LPARAM lparam);

        bool enum_desktops(HWINSTA window_station_handle,
                           DESKTOPENUMPROCA enum_func,
                           LPARAM lparam);

        bool enum_desktops(HWINSTA window_station_handle,
                           DESKTOPENUMPROCW enum_func,
                           LPARAM lparam);

        HWND get_window();

        HDESK get_thread_desktop(uint32_t tid);

        bool set_thread_desktop(HDESK desktop_handle);

        bool paint(HDC dc_handle);

        bool switch_desktop(HDESK desktop_handle);

        [[nodiscard]] uint32_t err_code() const;

        [[nodiscard]] std::string err_string() const;

        [[nodiscard]] std::wstring err_wstring() const;
    };
} // namespace YanLib::ui::core

namespace YanLib::ui::core {
    class window_station {
    private:
        std::vector<HWINSTA> window_station_handles = {};
        sync::rwlock rwlock = {};
        uint32_t error_code = 0;

    public:
        window_station(const window_station &other) = delete;

        window_station(window_station &&other) = delete;

        window_station &operator=(const window_station &other) = delete;

        window_station &operator=(window_station &&other) = delete;

        window_station() = default;

        ~window_station();

        HWINSTA create(const char *window_station_name,
                       uint32_t flag = 0,
                       StationAccess access = StationAccess::All,
                       SECURITY_ATTRIBUTES *sa = nullptr);

        HWINSTA create(const wchar_t *window_station_name,
                       uint32_t flag = 0,
                       StationAccess access = StationAccess::All,
                       SECURITY_ATTRIBUTES *sa = nullptr);

        HWINSTA open(const char *window_station_name,
                     bool is_inherit = false,
                     StationAccess access = StationAccess::All);

        HWINSTA open(const wchar_t *window_station_name,
                     bool is_inherit = false,
                     StationAccess access = StationAccess::All);

        bool destroy(HWINSTA window_station_handle);

        bool lock();

        bool enum_window_stations(WINSTAENUMPROCA enum_func, LPARAM lparam);

        bool enum_window_stations(WINSTAENUMPROCW enum_func, LPARAM lparam);

        HWINSTA get_process_window_station();

        bool set_process_window_station(HWINSTA window_station_handle);

        bool get_user_object_info(HANDLE desktop_or_station_handle,
                                  int32_t index,
                                  void *buf,
                                  uint32_t size,
                                  uint32_t *real_size);

        bool set_user_object_info(HANDLE desktop_or_station_handle,
                                  int32_t index,
                                  void *buf,
                                  uint32_t size);

        [[nodiscard]] uint32_t err_code() const;

        [[nodiscard]] std::string err_string() const;

        [[nodiscard]] std::wstring err_wstring() const;
    };
} // namespace YanLib::ui::core
#endif // DESKTOP_H
