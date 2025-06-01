//
// Created by forkernel on 2025/5/4.
//

#ifndef MONITOR_H
#define MONITOR_H
#include <Windows.h>
#include <cstdint>

namespace YanLib::ui::gdi {
#ifndef MONITORFLAG
#define MONITORFLAG

    enum class MonitorFlag : uint32_t {
        Null = MONITOR_DEFAULTTONULL,
        Primary = MONITOR_DEFAULTTOPRIMARY,
        Nearest = MONITOR_DEFAULTTONEAREST,
    };
#endif
    class monitor {
    public:
        monitor(const monitor &other) = delete;

        monitor(monitor &&other) = delete;

        monitor &operator=(const monitor &other) = delete;

        monitor &operator=(monitor &&other) = delete;

        monitor() = default;

        ~monitor() = default;

        static bool enum_display(HDC dc_handle,
                                 const RECT *rect,
                                 MONITORENUMPROC monitor_enum_proc,
                                 LPARAM data);

        static HMONITOR get(POINT point,
                            MonitorFlag flag = MonitorFlag::Primary);

        static HMONITOR get(const RECT *rect,
                            MonitorFlag flag = MonitorFlag::Primary);

        static HMONITOR get(HWND window_handle,
                            MonitorFlag flag = MonitorFlag::Primary);

        static bool get_info(HMONITOR monitor_handle,
                             MONITORINFO *monitor_info);

        static bool logical_to_physical_point_for_per_dpi(HWND window_handle,
                                                          POINT *point);

        static bool physical_to_logical_point_for_per_dpi(HWND window_handle,
                                                          POINT *point);

        static bool inherit_window(HWND window_handle,
                                   HWND inherit_window_handle);
    };
} // namespace YanLib::ui::gdi
#endif // MONITOR_H
