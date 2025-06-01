//
// Created by forkernel on 2025/5/18.
//

#ifndef WINDOW_BEHAVIOR_H
#define WINDOW_BEHAVIOR_H
#include <Windows.h>

namespace YanLib::ui {
    class window_behavior {
    public:
        window_behavior(const window_behavior &other) = delete;

        window_behavior(window_behavior &&other) = delete;

        window_behavior &operator=(const window_behavior &other) = delete;

        window_behavior &operator=(window_behavior &&other) = delete;

        window_behavior() = default;

        ~window_behavior() = default;

        static DPI_HOSTING_BEHAVIOR get_dpi_hosting(HWND window_handle);

        static DPI_HOSTING_BEHAVIOR get_thread_dpi_hosting();

        static DPI_HOSTING_BEHAVIOR
        set_thread_dpi_hosting(DPI_HOSTING_BEHAVIOR value);
    };
} // namespace YanLib::ui
#endif // WINDOW_BEHAVIOR_H
