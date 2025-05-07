//
// Created by forkernel on 2025/5/4.
//

#include "monitor.h"

namespace YanLib::ui::gdi {
bool monitor::enum_display_monitors(HDC dc_handle,
    const RECT                         *rect,
    MONITORENUMPROC                     monitor_enum_proc,
    LPARAM                              data) {
    return EnumDisplayMonitors(dc_handle, rect, monitor_enum_proc, data);
}

HMONITOR monitor::monitor_from_point(POINT point, uint32_t flag) {
    return MonitorFromPoint(point, flag);
}

HMONITOR monitor::monitor_from_rect(const RECT *rect, uint32_t flag) {
    return MonitorFromRect(rect, flag);
}

HMONITOR monitor::monitor_from_window(HWND hwnd, uint32_t flag) {
    return MonitorFromWindow(hwnd, flag);
}

bool monitor::get_monitor_info(HMONITOR monitor_handle,
    MONITORINFO                        *monitor_info) {
    return GetMonitorInfoW(monitor_handle, monitor_info);
}

bool monitor::logical_to_physical_point_for_per_monitor_dpi(HWND hwnd,
    POINT                                                       *point) {
    return LogicalToPhysicalPointForPerMonitorDPI(hwnd, point);
}

bool monitor::physical_to_logical_point_for_per_monitor_dpi(HWND hwnd,
    POINT                                                       *point) {
    return PhysicalToLogicalPointForPerMonitorDPI(hwnd, point);
}

bool monitor::inherit_window_monitor(HWND hwnd, HWND hwnd_inherit) {
    return InheritWindowMonitor(hwnd, hwnd_inherit);
}
} // namespace YanLib::ui::gdi
