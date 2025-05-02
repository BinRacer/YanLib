//
// Created by forkernel on 2025/5/2.
//

#include "display.h"

namespace YanLib::ui {
    bool display::enum_display_devices(const wchar_t *device_name,
                                       DWORD device_index,
                                       PDISPLAY_DEVICEW display_device,
                                       DWORD flag) {
        return EnumDisplayDevicesW(device_name,
                                   device_index,
                                   display_device,
                                   flag);
    }

    bool display::enum_display_monitors(HDC hdc,
                                        LPCRECT rect,
                                        MONITORENUMPROC monitor_enum_proc,
                                        LPARAM data) {
        return EnumDisplayMonitors(hdc, rect, monitor_enum_proc, data);
    }

    bool display::enum_display_settings(const wchar_t *device_name,
                                        DWORD mode,
                                        DEVMODEW *device_mode) {
        return EnumDisplaySettingsW(device_name, mode, device_mode);
    }

    bool display::enum_display_settings(const wchar_t *device_name,
                                        DWORD mode,
                                        DEVMODEW *device_mode,
                                        DWORD flag) {
        return EnumDisplaySettingsExW(device_name,
                                      mode,
                                      device_mode,
                                      flag);
    }

    LONG display::display_config_get_device_info(
        DISPLAYCONFIG_DEVICE_INFO_HEADER *request_packet) {
        return DisplayConfigGetDeviceInfo(request_packet);
    }

    LONG display::display_config_set_device_info(
        DISPLAYCONFIG_DEVICE_INFO_HEADER *request_packet) {
        return DisplayConfigSetDeviceInfo(request_packet);
    }

    bool display::get_display_auto_rotation_preferences(
        ORIENTATION_PREFERENCE *orientation) {
        return GetDisplayAutoRotationPreferences(orientation);
    }

    bool display::set_display_auto_rotation_preferences(
        ORIENTATION_PREFERENCE orientation) {
        return SetDisplayAutoRotationPreferences(orientation);
    }

    bool display::get_display_auto_rotation_preferences_by_pid(
        DWORD pid, ORIENTATION_PREFERENCE *orientation) {
        int is_ok = 0;
        if (!GetDisplayAutoRotationPreferencesByProcessId(pid,
                                                          orientation,
                                                          &is_ok)) {
            return false;
        }
        return is_ok;
    }

    LONG display::get_display_config_buffer_sizes(
        UINT32 flag,
        UINT32 *num_path_array_elements,
        UINT32 *num_mode_info_array_elements) {
        return GetDisplayConfigBufferSizes(flag,
                                           num_path_array_elements,
                                           num_mode_info_array_elements);
    }

    LONG display::get_display_config(
        UINT32 flag,
        UINT32 *num_path_array_elements,
        DISPLAYCONFIG_PATH_INFO *path_array,
        UINT32 *num_mode_info_array_elements,
        DISPLAYCONFIG_MODE_INFO *mode_info_array,
        DISPLAYCONFIG_TOPOLOGY_ID *current_topology_id) {
        return QueryDisplayConfig(flag,
                                  num_path_array_elements,
                                  path_array,
                                  num_mode_info_array_elements,
                                  mode_info_array,
                                  current_topology_id);
    }

    LONG display::set_display_config(
        UINT32 num_path_array_elements,
        DISPLAYCONFIG_PATH_INFO *path_array,
        UINT32 num_mode_info_array_elements,
        DISPLAYCONFIG_MODE_INFO *mode_info_array,
        UINT32 flag) {
        return SetDisplayConfig(num_path_array_elements,
                                path_array,
                                num_mode_info_array_elements,
                                mode_info_array,
                                flag);
    }

    LONG display::change_display_settings(DEVMODEW *device_mode, DWORD flag) {
        return ChangeDisplaySettingsW(device_mode, flag);
    }

    LONG display::change_display_settings(const wchar_t *device_name,
                                          DEVMODEW *device_mode,
                                          HWND hwnd,
                                          DWORD flag,
                                          void *l_param) {
        return ChangeDisplaySettingsExW(device_name,
                                        device_mode,
                                        hwnd,
                                        flag,
                                        l_param);
    }
}
