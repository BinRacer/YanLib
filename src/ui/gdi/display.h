/* clang-format off */
/*
 * @file display.h
 * @date 2025-05-02
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
#ifndef DISPLAY_H
#define DISPLAY_H
#include <Windows.h>
#include <wingdi.h>
#include <cstdint>
#include <vector>
#include "gdi.h"
namespace YanLib::ui::gdi {
    class display {
    public:
        display(const display &other) = delete;

        display(display &&other) = delete;

        display &operator=(const display &other) = delete;

        display &operator=(display &&other) = delete;

        display() = default;

        ~display() = default;

        static bool enum_devices(const char *device_name /* nullptr */,
                                 uint32_t device_index,
                                 DISPLAY_DEVICEA *display_device,
                                 bool interface_name = false);

        static bool enum_devices(const wchar_t *device_name /* nullptr */,
                                 uint32_t device_index,
                                 DISPLAY_DEVICEW *display_device,
                                 bool interface_name = false);

        static bool enum_settings(const char *device_name,
                                  DEVMODEA *device_mode,
                                  SettingMode mode = SettingMode::Current);

        static bool enum_settings(const wchar_t *device_name,
                                  DEVMODEW *device_mode,
                                  SettingMode mode = SettingMode::Current);

        static bool enum_settings(const char *device_name,
                                  DEVMODEA *device_mode,
                                  SettingMode mode = SettingMode::Current,
                                  SettingFlag flag = SettingFlag::RawMode);

        static bool enum_settings(const wchar_t *device_name,
                                  DEVMODEW *device_mode,
                                  SettingMode mode = SettingMode::Current,
                                  SettingFlag flag = SettingFlag::RawMode);

        static int32_t config_get_device_info(
                DISPLAYCONFIG_DEVICE_INFO_HEADER *request_packet);

        static int32_t config_set_device_info(
                DISPLAYCONFIG_DEVICE_INFO_HEADER *request_packet);

        static bool
        get_auto_rotation_preferences(OrientationPreference *orientation);

        static bool
        set_auto_rotation_preferences(OrientationPreference orientation);

        static bool get_auto_rotation_preferences_by_pid(
                uint32_t pid,
                OrientationPreference *orientation);

        static int32_t get_config_buffer_size(uint32_t *path_info_num,
                                              uint32_t *mode_info_num,
                                              GetDisplayConfig flag);

        static int32_t get_config(uint32_t *real_path_info_num,
                                  DISPLAYCONFIG_PATH_INFO path_info[],
                                  uint32_t *real_model_info_num,
                                  DISPLAYCONFIG_MODE_INFO mode_info[],
                                  TopologyID *id,
                                  GetDisplayConfig flag);

        static int32_t
        set_config(std::vector<DISPLAYCONFIG_PATH_INFO> &path_info,
                   std::vector<DISPLAYCONFIG_MODE_INFO> &mode_info,
                   SetDisplayConfig flag);

        static ChangedDisplayConfigResult
        change_settings(DEVMODEA *device_mode, ChangedDisplayConfig flag);

        static ChangedDisplayConfigResult
        change_settings(DEVMODEW *device_mode, ChangedDisplayConfig flag);

        static int32_t change_settings(const char *device_name,
                                       DEVMODEA *device_mode,
                                       void *lparam,
                                       ChangedDisplayConfig flag);

        static int32_t change_settings(const wchar_t *device_name,
                                       DEVMODEW *device_mode,
                                       void *lparam,
                                       ChangedDisplayConfig flag);
    };
} // namespace YanLib::ui::gdi
#endif // DISPLAY_H
