//
// Created by forkernel on 2025/5/2.
//

#ifndef DISPLAY_H
#define DISPLAY_H
#include <Windows.h>

namespace YanLib::ui::gdi {
    class display {
    public:
        display(const display &other) = delete;

        display(display &&other) = delete;

        display &operator=(const display &other) = delete;

        display &operator=(display &&other) = delete;

        display() = default;

        ~display() = default;

        static bool enum_display_devices(const wchar_t *device_name,
                                         unsigned long device_index,
                                         DISPLAY_DEVICEW *display_device,
                                         unsigned long flag);

        static bool enum_display_settings(const wchar_t *device_name,
                                          unsigned long mode,
                                          DEVMODEW *device_mode);

        static bool enum_display_settings(const wchar_t *device_name,
                                          unsigned long mode,
                                          DEVMODEW *device_mode,
                                          unsigned long flag);

        static long display_config_get_device_info(
            DISPLAYCONFIG_DEVICE_INFO_HEADER *request_packet);

        static long display_config_set_device_info(
            DISPLAYCONFIG_DEVICE_INFO_HEADER *request_packet);

        static bool get_display_auto_rotation_preferences(
            ORIENTATION_PREFERENCE *orientation);

        static bool set_display_auto_rotation_preferences(
            ORIENTATION_PREFERENCE orientation);

        static bool get_display_auto_rotation_preferences_by_pid(
            unsigned long pid,
            ORIENTATION_PREFERENCE *orientation);

        static long get_display_config_buffer_sizes(
            unsigned int flag,
            unsigned int *num_path_array_elements,
            unsigned int *num_mode_info_array_elements);

        static long get_display_config(
            unsigned int flag,
            unsigned int *num_path_array_elements,
            DISPLAYCONFIG_PATH_INFO *path_array,
            unsigned int *num_mode_info_array_elements,
            DISPLAYCONFIG_MODE_INFO *mode_info_array,
            DISPLAYCONFIG_TOPOLOGY_ID *current_topology_id);

        static long set_display_config(
            unsigned int num_path_array_elements,
            DISPLAYCONFIG_PATH_INFO *path_array,
            unsigned int num_mode_info_array_elements,
            DISPLAYCONFIG_MODE_INFO *mode_info_array,
            unsigned int flag);

        static long change_display_settings(DEVMODEW *device_mode, unsigned long flag);

        static long change_display_settings(const wchar_t *device_name,
                                            DEVMODEW *device_mode,
                                            HWND hwnd,
                                            unsigned long flag,
                                            void *l_param);
    };
}
#endif //DISPLAY_H
