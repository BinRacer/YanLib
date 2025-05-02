//
// Created by forkernel on 2025/5/2.
//

#ifndef DISPLAY_H
#define DISPLAY_H
#include <Windows.h>

namespace YanLib::ui {
    class display {
    public:
        display(const display &other) = delete;

        display(display &&other) = delete;

        display &operator=(const display &other) = delete;

        display &operator=(display &&other) = delete;

        display() = default;

        ~display() = default;

        static bool enum_display_devices(const wchar_t *device_name,
                                         DWORD device_index,
                                         PDISPLAY_DEVICEW display_device,
                                         DWORD flag);

        static bool enum_display_monitors(HDC hdc,
                                          LPCRECT rect,
                                          MONITORENUMPROC monitor_enum_proc,
                                          LPARAM data);

        static bool enum_display_settings(const wchar_t *device_name,
                                          DWORD mode,
                                          DEVMODEW *device_mode);

        static bool enum_display_settings(const wchar_t *device_name,
                                          DWORD mode,
                                          DEVMODEW *device_mode,
                                          DWORD flag);

        static LONG display_config_get_device_info(
            DISPLAYCONFIG_DEVICE_INFO_HEADER *request_packet);

        static LONG display_config_set_device_info(
            DISPLAYCONFIG_DEVICE_INFO_HEADER *request_packet);

        static bool get_display_auto_rotation_preferences(
            ORIENTATION_PREFERENCE *orientation);

        static bool set_display_auto_rotation_preferences(
            ORIENTATION_PREFERENCE orientation);

        static bool get_display_auto_rotation_preferences_by_pid(
            DWORD pid,
            ORIENTATION_PREFERENCE *orientation);

        static LONG get_display_config_buffer_sizes(
            UINT32 flag,
            UINT32 *num_path_array_elements,
            UINT32 *num_mode_info_array_elements);

        static LONG get_display_config(
            UINT32 flag,
            UINT32 *num_path_array_elements,
            DISPLAYCONFIG_PATH_INFO *path_array,
            UINT32 *num_mode_info_array_elements,
            DISPLAYCONFIG_MODE_INFO *mode_info_array,
            DISPLAYCONFIG_TOPOLOGY_ID *current_topology_id);

        static LONG set_display_config(
            UINT32 num_path_array_elements,
            DISPLAYCONFIG_PATH_INFO *path_array,
            UINT32 num_mode_info_array_elements,
            DISPLAYCONFIG_MODE_INFO *mode_info_array,
            UINT32 flag);

        static LONG change_display_settings(DEVMODEW *device_mode, DWORD flag);

        static LONG change_display_settings(const wchar_t *device_name,
                                            DEVMODEW *device_mode,
                                            HWND hwnd,
                                            DWORD flag,
                                            void *l_param);
    };
}
#endif //DISPLAY_H
