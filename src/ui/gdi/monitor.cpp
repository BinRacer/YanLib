/* clang-format off */
/*
 * @file monitor.cpp
 * @date 2025-05-04
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
#include "monitor.h"

namespace YanLib::ui::gdi {
    bool monitor::enum_monitor(HDC dc_handle,
                               const RECT *rect,
                               MONITORENUMPROC monitor_enum_proc,
                               LPARAM data) {
        return EnumDisplayMonitors(dc_handle, rect, monitor_enum_proc, data);
    }

    HMONITOR monitor::get_monitor(POINT point, MonitorFlag flag) {
        return MonitorFromPoint(point, static_cast<uint32_t>(flag));
    }

    HMONITOR monitor::get_monitor(const RECT *rect, MonitorFlag flag) {
        return MonitorFromRect(rect, static_cast<uint32_t>(flag));
    }

    HMONITOR monitor::get_monitor(HWND window_handle, MonitorFlag flag) {
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
