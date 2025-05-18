//
// Created by forkernel on 2025/5/2.
//

#include "display.h"

namespace YanLib::ui::gdi {
bool display::enum_display_devices(const char *device_name,
    uint32_t                                   device_index,
    DISPLAY_DEVICEA                           *display_device,
    uint32_t                                   flag) {
    return EnumDisplayDevicesA(device_name, device_index, display_device, flag);
}

bool display::enum_display_devices(const wchar_t *device_name,
    uint32_t                                      device_index,
    DISPLAY_DEVICEW                              *display_device,
    uint32_t                                      flag) {
    return EnumDisplayDevicesW(device_name, device_index, display_device, flag);
}

bool display::enum_display_settings(const char *device_name,
    uint32_t                                    mode,
    DEVMODEA                                   *device_mode) {
    return EnumDisplaySettingsA(device_name, mode, device_mode);
}

bool display::enum_display_settings(const wchar_t *device_name,
    uint32_t                                       mode,
    DEVMODEW                                      *device_mode) {
    return EnumDisplaySettingsW(device_name, mode, device_mode);
}

bool display::enum_display_settings(const char *device_name,
    uint32_t                                    mode,
    DEVMODEA                                   *device_mode,
    uint32_t                                    flag) {
    return EnumDisplaySettingsExA(device_name, mode, device_mode, flag);
}

bool display::enum_display_settings(const wchar_t *device_name,
    uint32_t                                       mode,
    DEVMODEW                                      *device_mode,
    uint32_t                                       flag) {
    return EnumDisplaySettingsExW(device_name, mode, device_mode, flag);
}

long display::display_config_get_device_info(
    DISPLAYCONFIG_DEVICE_INFO_HEADER *request_packet) {
    return DisplayConfigGetDeviceInfo(request_packet);
}

long display::display_config_set_device_info(
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

bool display::get_display_auto_rotation_preferences_by_pid(uint32_t pid,
    ORIENTATION_PREFERENCE *orientation) {
    int32_t is_ok = 0;
    if (!GetDisplayAutoRotationPreferencesByProcessId(
            pid, orientation, &is_ok)) {
        return false;
    }
    return is_ok;
}

long display::get_display_config_buffer_sizes(uint32_t flag,
    uint32_t                                          *num_path_array_elements,
    uint32_t *num_mode_info_array_elements) {
    return GetDisplayConfigBufferSizes(
        flag, num_path_array_elements, num_mode_info_array_elements);
}

long display::get_display_config(uint32_t flag,
    uint32_t                             *real_path_info_num,
    DISPLAYCONFIG_PATH_INFO               path_info[],
    uint32_t                             *real_model_info_num,
    DISPLAYCONFIG_MODE_INFO               mode_info[],
    DISPLAYCONFIG_TOPOLOGY_ID            *curr_id) {
    return QueryDisplayConfig(flag, real_path_info_num, path_info,
        real_model_info_num, mode_info, curr_id);
}

long display::set_display_config(
    std::vector<DISPLAYCONFIG_PATH_INFO> &path_info,
    std::vector<DISPLAYCONFIG_MODE_INFO> &mode_info,
    uint32_t                              flag) {
    return SetDisplayConfig(path_info.size(), path_info.data(),
        mode_info.size(), mode_info.data(), flag);
}

long display::change_display_settings(DEVMODEA *device_mode, uint32_t flag) {
    return ChangeDisplaySettingsA(device_mode, flag);
}

long display::change_display_settings(DEVMODEW *device_mode, uint32_t flag) {
    return ChangeDisplaySettingsW(device_mode, flag);
}

long display::change_display_settings(const char *device_name,
    DEVMODEA                                     *device_mode,
    HWND                                          window_handle,
    uint32_t                                      flag,
    void                                         *lparam) {
    return ChangeDisplaySettingsExA(
        device_name, device_mode, window_handle, flag, lparam);
}

long display::change_display_settings(const wchar_t *device_name,
    DEVMODEW                                        *device_mode,
    HWND                                             window_handle,
    uint32_t                                         flag,
    void                                            *lparam) {
    return ChangeDisplaySettingsExW(
        device_name, device_mode, window_handle, flag, lparam);
}
} // namespace YanLib::ui::gdi
