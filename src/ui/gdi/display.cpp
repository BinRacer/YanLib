//
// Created by forkernel on 2025/5/2.
//

#include "display.h"

namespace YanLib::ui::gdi {
    bool display::enum_devices(const char *device_name,
                               uint32_t device_index,
                               DISPLAY_DEVICEA *display_device,
                               bool interface_name) {
        return EnumDisplayDevicesA(device_name, device_index, display_device,
                                   interface_name
                                           ? EDD_GET_DEVICE_INTERFACE_NAME
                                           : 0);
    }

    bool display::enum_devices(const wchar_t *device_name,
                               uint32_t device_index,
                               DISPLAY_DEVICEW *display_device,
                               bool interface_name) {
        return EnumDisplayDevicesW(device_name, device_index, display_device,
                                   interface_name
                                           ? EDD_GET_DEVICE_INTERFACE_NAME
                                           : 0);
    }

    bool display::enum_settings(const char *device_name,
                                DEVMODEA *device_mode,
                                SettingMode mode) {
        return EnumDisplaySettingsA(device_name, static_cast<uint32_t>(mode),
                                    device_mode);
    }

    bool display::enum_settings(const wchar_t *device_name,
                                DEVMODEW *device_mode,
                                SettingMode mode) {
        return EnumDisplaySettingsW(device_name, static_cast<uint32_t>(mode),
                                    device_mode);
    }

    bool display::enum_settings(const char *device_name,
                                DEVMODEA *device_mode,
                                SettingMode mode,
                                SettingFlag flag) {
        return EnumDisplaySettingsExA(device_name, static_cast<uint32_t>(mode),
                                      device_mode, static_cast<uint32_t>(flag));
    }

    bool display::enum_settings(const wchar_t *device_name,
                                DEVMODEW *device_mode,
                                SettingMode mode,
                                SettingFlag flag) {
        return EnumDisplaySettingsExW(device_name, static_cast<uint32_t>(mode),
                                      device_mode, static_cast<uint32_t>(flag));
    }

    int32_t display::config_get_device_info(
            DISPLAYCONFIG_DEVICE_INFO_HEADER *request_packet) {
        return DisplayConfigGetDeviceInfo(request_packet);
    }

    int32_t display::config_set_device_info(
            DISPLAYCONFIG_DEVICE_INFO_HEADER *request_packet) {
        return DisplayConfigSetDeviceInfo(request_packet);
    }

    bool
    display::get_auto_rotation_preferences(OrientationPreference *orientation) {
        if (!orientation) {
            return false;
        }
        auto temp = static_cast<ORIENTATION_PREFERENCE>(*orientation);
        bool is_ok = GetDisplayAutoRotationPreferences(&temp);
        *orientation = static_cast<OrientationPreference>(temp);
        return is_ok;
    }

    bool
    display::set_auto_rotation_preferences(OrientationPreference orientation) {
        return SetDisplayAutoRotationPreferences(
                static_cast<ORIENTATION_PREFERENCE>(orientation));
    }

    bool display::get_auto_rotation_preferences_by_pid(
            uint32_t pid,
            OrientationPreference *orientation) {
        HMODULE kernel32 = nullptr;
        bool result = false;
        do {
            if (!orientation) {
                break;
            }
            kernel32 = LoadLibraryW(L"kernel32.dll");
            if (!kernel32) {
                break;
            }
            typedef int32_t(WINAPI * prototype)(_In_ uint32_t,
                                                _Out_ ORIENTATION_PREFERENCE *,
                                                _Out_ int32_t *);
            auto func = reinterpret_cast<prototype>(GetProcAddress(
                    kernel32, "GetDisplayAutoRotationPreferencesByProcessId"));
            if (!func) {
                break;
            }
            auto temp = static_cast<ORIENTATION_PREFERENCE>(*orientation);
            int32_t is_ok = 0;
            result = func(pid, &temp, &is_ok);
            *orientation = static_cast<OrientationPreference>(temp);
        } while (false);
        if (kernel32) {
            FreeLibrary(kernel32);
        }
        return result;
    }

    int32_t display::get_config_buffer_size(uint32_t *path_info_num,
                                            uint32_t *mode_info_num,
                                            GetDisplayConfig flag) {
        return GetDisplayConfigBufferSizes(static_cast<uint32_t>(flag),
                                           path_info_num, mode_info_num);
    }

    int32_t display::get_config(uint32_t *real_path_info_num,
                                DISPLAYCONFIG_PATH_INFO path_info[],
                                uint32_t *real_model_info_num,
                                DISPLAYCONFIG_MODE_INFO mode_info[],
                                TopologyID *id,
                                GetDisplayConfig flag) {
        if (flag & GetDisplayConfig::DatabaseCurrent) {
            if (!id) {
                return ERROR_INVALID_PARAMETER;
            }
            auto temp = static_cast<DISPLAYCONFIG_TOPOLOGY_ID>(*id);
            bool is_ok =
                    QueryDisplayConfig(static_cast<uint32_t>(flag),
                                       real_path_info_num, path_info,
                                       real_model_info_num, mode_info, &temp);
            *id = static_cast<TopologyID>(temp);
            return is_ok;
        }
        return QueryDisplayConfig(static_cast<uint32_t>(flag),
                                  real_path_info_num, path_info,
                                  real_model_info_num, mode_info, nullptr);
    }

    int32_t display::set_config(std::vector<DISPLAYCONFIG_PATH_INFO> &path_info,
                                std::vector<DISPLAYCONFIG_MODE_INFO> &mode_info,
                                SetDisplayConfig flag) {
        return ::SetDisplayConfig(path_info.size(), path_info.data(),
                                  mode_info.size(), mode_info.data(),
                                  static_cast<uint32_t>(flag));
    }

    ChangedDisplayConfigResult
    display::change_settings(DEVMODEA *device_mode, ChangedDisplayConfig flag) {
        return static_cast<ChangedDisplayConfigResult>(
                ChangeDisplaySettingsA(device_mode,
                                       static_cast<uint32_t>(flag)));
    }

    ChangedDisplayConfigResult
    display::change_settings(DEVMODEW *device_mode, ChangedDisplayConfig flag) {
        return static_cast<ChangedDisplayConfigResult>(
                ChangeDisplaySettingsW(device_mode,
                                       static_cast<uint32_t>(flag)));
    }

    int32_t display::change_settings(const char *device_name,
                                     DEVMODEA *device_mode,
                                     void *lparam,
                                     ChangedDisplayConfig flag) {
        return ChangeDisplaySettingsExA(device_name, device_mode, nullptr,
                                        static_cast<uint32_t>(flag), lparam);
    }

    int32_t display::change_settings(const wchar_t *device_name,
                                     DEVMODEW *device_mode,
                                     void *lparam,
                                     ChangedDisplayConfig flag) {
        return ChangeDisplaySettingsExW(device_name, device_mode, nullptr,
                                        static_cast<uint32_t>(flag), lparam);
    }
} // namespace YanLib::ui::gdi
