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

HMONITOR monitor::monitor_from_window(HWND window_handle, uint32_t flag) {
    return MonitorFromWindow(window_handle, flag);
}

bool monitor::get_monitor_info(HMONITOR monitor_handle,
    MONITORINFO                        *monitor_info) {
    return GetMonitorInfoW(monitor_handle, monitor_info);
}

bool monitor::logical_to_physical_point_for_per_monitor_dpi(HWND window_handle,
    POINT                                                       *point) {
    return LogicalToPhysicalPointForPerMonitorDPI(window_handle, point);
}

bool monitor::physical_to_logical_point_for_per_monitor_dpi(HWND window_handle,
    POINT                                                       *point) {
    return PhysicalToLogicalPointForPerMonitorDPI(window_handle, point);
}

bool monitor::inherit_window_monitor(HWND window_handle,
    HWND                                  inherit_window_handle) {
    return InheritWindowMonitor(window_handle, inherit_window_handle);
}
} // namespace YanLib::ui::gdi
