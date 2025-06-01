//
// Created by forkernel on 2025/5/4.
//

#include "monitor.h"

namespace YanLib::ui::gdi {
    bool monitor::enum_display(HDC dc_handle,
                               const RECT *rect,
                               MONITORENUMPROC monitor_enum_proc,
                               LPARAM data) {
        return EnumDisplayMonitors(dc_handle, rect, monitor_enum_proc, data);
    }

    HMONITOR monitor::get(POINT point, MonitorFlag flag) {
        return MonitorFromPoint(point, static_cast<uint32_t>(flag));
    }

    HMONITOR monitor::get(const RECT *rect, MonitorFlag flag) {
        return MonitorFromRect(rect, static_cast<uint32_t>(flag));
    }

    HMONITOR monitor::get(HWND window_handle, MonitorFlag flag) {
        return MonitorFromWindow(window_handle, static_cast<uint32_t>(flag));
    }

    bool monitor::get_info(HMONITOR monitor_handle, MONITORINFO *monitor_info) {
        return GetMonitorInfoW(monitor_handle, monitor_info);
    }

    bool monitor::logical_to_physical_point_for_per_dpi(HWND window_handle,
                                                        POINT *point) {
        return LogicalToPhysicalPointForPerMonitorDPI(window_handle, point);
    }

    bool monitor::physical_to_logical_point_for_per_dpi(HWND window_handle,
                                                        POINT *point) {
        return PhysicalToLogicalPointForPerMonitorDPI(window_handle, point);
    }

    bool monitor::inherit_window(HWND window_handle,
                                 HWND inherit_window_handle) {
        return InheritWindowMonitor(window_handle, inherit_window_handle);
    }
} // namespace YanLib::ui::gdi
