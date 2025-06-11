//
// Created by BinRacer <native.lab@outlook.com> on 2025/5/18.
//

#include "window_behavior.h"
#include "helper/convert.h"
namespace YanLib::ui::core {
    DPI_HOSTING_BEHAVIOR window_behavior::get_dpi_hosting(HWND window_handle) {
        return GetWindowDpiHostingBehavior(window_handle);
    }

    DPI_HOSTING_BEHAVIOR window_behavior::get_thread_dpi_hosting() {
        return GetThreadDpiHostingBehavior();
    }

    DPI_HOSTING_BEHAVIOR
    window_behavior::set_thread_dpi_hosting(DPI_HOSTING_BEHAVIOR value) {
        return SetThreadDpiHostingBehavior(value);
    }
} // namespace YanLib::ui::core
