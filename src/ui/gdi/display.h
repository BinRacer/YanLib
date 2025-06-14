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
#include <cstdint>
#include <vector>

namespace YanLib::ui::gdi {
#ifndef STATEFLAG
#define STATEFLAG

    enum class StateFlag : uint32_t {
        AttachedToDesktop = DISPLAY_DEVICE_ATTACHED_TO_DESKTOP,
        MultiDriver = DISPLAY_DEVICE_MULTI_DRIVER,
        PrimaryDevice = DISPLAY_DEVICE_PRIMARY_DEVICE,
        MirroringDriver = DISPLAY_DEVICE_MIRRORING_DRIVER,
        VgaCompatible = DISPLAY_DEVICE_VGA_COMPATIBLE,
        Removable = DISPLAY_DEVICE_REMOVABLE,
        AccDriver = DISPLAY_DEVICE_ACC_DRIVER,
        ModeSpruned = DISPLAY_DEVICE_MODESPRUNED,
        RdpUdd = DISPLAY_DEVICE_RDPUDD,
        Remote = DISPLAY_DEVICE_REMOTE,
        Disconnect = DISPLAY_DEVICE_DISCONNECT,
        TsCompatible = DISPLAY_DEVICE_TS_COMPATIBLE,
        UnsafeModesOn = DISPLAY_DEVICE_UNSAFE_MODES_ON,
        Active = DISPLAY_DEVICE_ACTIVE,
        Attached = DISPLAY_DEVICE_ATTACHED,
    };
#endif
#ifndef SETTINGMODE
#define SETTINGMODE

    enum class SettingMode : uint32_t {
        Current = ENUM_CURRENT_SETTINGS,
        Registry = ENUM_REGISTRY_SETTINGS,
    };
#endif
#ifndef SETTINGFLAG
#define SETTINGFLAG

    enum class SettingFlag : uint32_t {
        RawMode = EDS_RAWMODE,
        RotatedMode = EDS_ROTATEDMODE,
    };

    inline SettingFlag operator|(SettingFlag a, SettingFlag b) {
        return static_cast<SettingFlag>(static_cast<uint32_t>(a) |
                                        static_cast<uint32_t>(b));
    }
#endif
#ifndef ORIENTATIONPREFERENCE
#define ORIENTATIONPREFERENCE

    enum class OrientationPreference : int32_t {
        None = ORIENTATION_PREFERENCE_NONE,
        Landscape = ORIENTATION_PREFERENCE_LANDSCAPE,
        Portrait = ORIENTATION_PREFERENCE_PORTRAIT,
        LandscapeFlipped = ORIENTATION_PREFERENCE_LANDSCAPE_FLIPPED,
        PortraitFlipped = ORIENTATION_PREFERENCE_PORTRAIT_FLIPPED,
    };

    inline OrientationPreference operator|(OrientationPreference a,
                                           OrientationPreference b) {
        return static_cast<OrientationPreference>(static_cast<int32_t>(a) |
                                                  static_cast<int32_t>(b));
    }
#endif
#ifndef GETDISPLAYCONFIG
#define GETDISPLAYCONFIG

    enum class GetDisplayConfig : uint32_t {
        AllPaths = QDC_ALL_PATHS,
        OnlyActivePaths = QDC_ONLY_ACTIVE_PATHS,
        DatabaseCurrent = QDC_DATABASE_CURRENT,
        VirtualModeAware = QDC_VIRTUAL_MODE_AWARE,
        IncludeHmd = QDC_INCLUDE_HMD,
        VirtualRefreshRateAware = QDC_VIRTUAL_REFRESH_RATE_AWARE,
    };

    inline GetDisplayConfig operator|(GetDisplayConfig a, GetDisplayConfig b) {
        return static_cast<GetDisplayConfig>(static_cast<uint32_t>(a) |
                                             static_cast<uint32_t>(b));
    }

    inline bool operator&(GetDisplayConfig a, GetDisplayConfig b) {
        return static_cast<uint32_t>(a) & static_cast<uint32_t>(b);
    }
#endif
#ifndef TOPOLOGYID
#define TOPOLOGYID

    enum class TopologyID : int32_t {
        Internal = DISPLAYCONFIG_TOPOLOGY_INTERNAL,
        Clone = DISPLAYCONFIG_TOPOLOGY_CLONE,
        Extend = DISPLAYCONFIG_TOPOLOGY_EXTEND,
        External = DISPLAYCONFIG_TOPOLOGY_EXTERNAL,
        ForceUint32 = DISPLAYCONFIG_TOPOLOGY_FORCE_UINT32,
    };

    inline TopologyID operator|(TopologyID a, TopologyID b) {
        return static_cast<TopologyID>(static_cast<int32_t>(a) |
                                       static_cast<int32_t>(b));
    }
#endif
#ifndef SETDISPLAYCONFIG
#define SETDISPLAYCONFIG

    enum class SetDisplayConfig : uint32_t {
        None = 0,
        TopologyInternal = SDC_TOPOLOGY_INTERNAL,
        TopologyClone = SDC_TOPOLOGY_CLONE,
        TopologyExtend = SDC_TOPOLOGY_EXTEND,
        TopologyExternal = SDC_TOPOLOGY_EXTERNAL,
        TopologySupplied = SDC_TOPOLOGY_SUPPLIED,
        UseDatabaseCurrent = SDC_USE_DATABASE_CURRENT,
        UseSuppliedDisplayConfig = SDC_USE_SUPPLIED_DISPLAY_CONFIG,
        Validate = SDC_VALIDATE,
        Apply = SDC_APPLY,
        NoOptimization = SDC_NO_OPTIMIZATION,
        SaveToDatabase = SDC_SAVE_TO_DATABASE,
        AllowChanges = SDC_ALLOW_CHANGES,
        PathPersistIfRequired = SDC_PATH_PERSIST_IF_REQUIRED,
        ForceModeEnumeration = SDC_FORCE_MODE_ENUMERATION,
        AllowPathOrderChanges = SDC_ALLOW_PATH_ORDER_CHANGES,
        VirtualModeAware = SDC_VIRTUAL_MODE_AWARE,
        VirtualRefreshRateAware = SDC_VIRTUAL_REFRESH_RATE_AWARE,
    };

    inline SetDisplayConfig operator|(SetDisplayConfig a, SetDisplayConfig b) {
        return static_cast<SetDisplayConfig>(static_cast<uint32_t>(a) |
                                             static_cast<uint32_t>(b));
    }
#endif
#ifndef CHANGEDISPLAYCONFIG
#define CHANGEDISPLAYCONFIG

    enum class ChangedDisplayConfig : uint32_t {
        None = 0,
        UpdateRegistry = CDS_UPDATEREGISTRY,
        Test = CDS_TEST,
        FullScreen = CDS_FULLSCREEN,
        Global = CDS_GLOBAL,
        SetPrimary = CDS_SET_PRIMARY,
        VideoParameters = CDS_VIDEOPARAMETERS,
        EnableUnsafeModes = CDS_ENABLE_UNSAFE_MODES,
        DisableUnsafeModes = CDS_DISABLE_UNSAFE_MODES,
        Reset = CDS_RESET,
        ResetEx = CDS_RESET_EX,
        NoReset = CDS_NORESET,
    };

    inline ChangedDisplayConfig operator|(ChangedDisplayConfig a,
                                          ChangedDisplayConfig b) {
        return static_cast<ChangedDisplayConfig>(static_cast<uint32_t>(a) |
                                                 static_cast<uint32_t>(b));
    }
#endif
#ifndef CHANGEDISPLAYCONFIGRESULT
#define CHANGEDISPLAYCONFIGRESULT

    enum class ChangedDisplayConfigResult : int32_t {
        Successful = DISP_CHANGE_SUCCESSFUL,
        Restart = DISP_CHANGE_RESTART,
        Failed = DISP_CHANGE_FAILED,
        BadMode = DISP_CHANGE_BADMODE,
        NotUpdated = DISP_CHANGE_NOTUPDATED,
        BadFlags = DISP_CHANGE_BADFLAGS,
        BadParam = DISP_CHANGE_BADPARAM,
        BadDualView = DISP_CHANGE_BADDUALVIEW,
    };
#endif
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
