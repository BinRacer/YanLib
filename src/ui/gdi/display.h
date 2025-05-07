//
// Created by forkernel on 2025/5/2.
//

#ifndef DISPLAY_H
#define DISPLAY_H
#include <Windows.h>
#include <cstdint>
#include <vector>

namespace YanLib::ui::gdi {
class display {
public:
    display(const display &other)            = delete;

    display(display &&other)                 = delete;

    display &operator=(const display &other) = delete;

    display &operator=(display &&other)      = delete;

    display()                                = default;

    ~display()                               = default;

    static bool enum_display_devices(const char *device_name,
        uint32_t                                 device_index,
        DISPLAY_DEVICEA                         *display_device,
        uint32_t                                 flag);

    static bool enum_display_devices(const wchar_t *device_name,
        uint32_t                                    device_index,
        DISPLAY_DEVICEW                            *display_device,
        uint32_t                                    flag);

    static bool enum_display_settings(const char *device_name,
        uint32_t                                  mode,
        DEVMODEA                                 *device_mode);

    static bool enum_display_settings(const wchar_t *device_name,
        uint32_t                                     mode,
        DEVMODEW                                    *device_mode);

    static bool enum_display_settings(const char *device_name,
        uint32_t                                  mode,
        DEVMODEA                                 *device_mode,
        uint32_t                                  flag);

    static bool enum_display_settings(const wchar_t *device_name,
        uint32_t                                     mode,
        DEVMODEW                                    *device_mode,
        uint32_t                                     flag);

    static long display_config_get_device_info(
        DISPLAYCONFIG_DEVICE_INFO_HEADER *request_packet);

    static long display_config_set_device_info(
        DISPLAYCONFIG_DEVICE_INFO_HEADER *request_packet);

    static bool get_display_auto_rotation_preferences(
        ORIENTATION_PREFERENCE *orientation);

    static bool set_display_auto_rotation_preferences(
        ORIENTATION_PREFERENCE orientation);

    static bool get_display_auto_rotation_preferences_by_pid(uint32_t pid,
        ORIENTATION_PREFERENCE *orientation);

    static long get_display_config_buffer_sizes(uint32_t flag,
        uint32_t *num_path_array_elements,
        uint32_t *num_mode_info_array_elements);

    static long get_display_config(uint32_t flag,
        uint32_t                           *real_path_info_num,
        DISPLAYCONFIG_PATH_INFO             path_info[],
        uint32_t                           *real_model_info_num,
        DISPLAYCONFIG_MODE_INFO             mode_info[],
        DISPLAYCONFIG_TOPOLOGY_ID          *curr_id);

    static long set_display_config(
        std::vector<DISPLAYCONFIG_PATH_INFO> &path_info,
        std::vector<DISPLAYCONFIG_MODE_INFO> &mode_info,
        uint32_t                              flag);

    static long change_display_settings(DEVMODEA *device_mode, uint32_t flag);

    static long change_display_settings(DEVMODEW *device_mode, uint32_t flag);

    static long change_display_settings(const char *device_name,
        DEVMODEA                                   *device_mode,
        HWND                                        hwnd,
        uint32_t                                    flag,
        void                                       *lparam);

    static long change_display_settings(const wchar_t *device_name,
        DEVMODEW                                      *device_mode,
        HWND                                           hwnd,
        uint32_t                                       flag,
        void                                          *lparam);
};
} // namespace YanLib::ui::gdi
#endif // DISPLAY_H
