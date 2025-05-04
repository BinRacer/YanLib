//
// Created by forkernel on 2025/5/4.
//

#ifndef MONITOR_H
#define MONITOR_H
#include <Windows.h>

namespace YanLib::ui::gdi {
    class monitor {
    public:
        monitor(const monitor &other) = delete;

        monitor(monitor &&other) = delete;

        monitor &operator=(const monitor &other) = delete;

        monitor &operator=(monitor &&other) = delete;

        monitor() = default;

        ~monitor() = default;

        static bool enum_display_monitors(HDC dc_handle,
                                          const RECT *rect,
                                          MONITORENUMPROC monitor_enum_proc,
                                          LPARAM data);

        static HMONITOR monitor_from_point(POINT point, DWORD flag);

        static HMONITOR monitor_from_rect(const RECT *rect, DWORD flag);

        static bool get_monitor_info(HMONITOR monitor_handle,
                                     MONITORINFO *monitor_info);

        static bool logical_to_physical_point_for_per_monitor_dpi(HWND hwnd,
                                                                  POINT *point);

        static bool physical_to_logical_point_for_per_monitor_dpi(HWND hwnd,
                                                                  POINT *point);
    };
}
#endif //MONITOR_H
