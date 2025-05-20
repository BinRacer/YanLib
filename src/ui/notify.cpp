//
// Created by forkernel on 2025/5/18.
//

#include "notify.h"
#include "helper/convert.h"
namespace YanLib::ui {
    HDEVNOTIFY notify::register_device(HWND window_handle,
                                       void *notify_filter,
                                       bool notify_all) {
        HDEVNOTIFY result = RegisterDeviceNotificationW(
                window_handle, notify_filter,
                DEVICE_NOTIFY_WINDOW_HANDLE |
                        (notify_all ? DEVICE_NOTIFY_ALL_INTERFACE_CLASSES : 0));
        if (!result) {
            error_code = GetLastError();
        }
        return result;
    }

    HDEVNOTIFY notify::register_device(HANDLE service_handle,
                                       void *notify_filter,
                                       bool notify_all) {
        HDEVNOTIFY result = RegisterDeviceNotificationW(
                service_handle, notify_filter,
                DEVICE_NOTIFY_SERVICE_HANDLE |
                        (notify_all ? DEVICE_NOTIFY_ALL_INTERFACE_CLASSES : 0));
        if (!result) {
            error_code = GetLastError();
        }
        return result;
    }

    bool notify::unregister_device(HDEVNOTIFY device_notify_handle) {
        if (!UnregisterDeviceNotification(device_notify_handle)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    HPOWERNOTIFY notify::register_power_setting(HWND window_handle,
                                                const GUID *guid) {
        HPOWERNOTIFY result =
                RegisterPowerSettingNotification(window_handle, guid,
                                                 DEVICE_NOTIFY_WINDOW_HANDLE);
        if (!result) {
            error_code = GetLastError();
        }
        return result;
    }

    HPOWERNOTIFY notify::register_power_setting(HANDLE service_handle,
                                                const GUID *guid) {
        HPOWERNOTIFY result =
                RegisterPowerSettingNotification(service_handle, guid,
                                                 DEVICE_NOTIFY_SERVICE_HANDLE);
        if (!result) {
            error_code = GetLastError();
        }
        return result;
    }

    bool notify::unregister_power_setting(HPOWERNOTIFY power_notify_handle) {
        if (!UnregisterPowerSettingNotification(power_notify_handle)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    HPOWERNOTIFY notify::register_suspend_resume(HWND window_handle) {
        HPOWERNOTIFY result =
                RegisterSuspendResumeNotification(window_handle,
                                                  DEVICE_NOTIFY_WINDOW_HANDLE);
        if (!result) {
            error_code = GetLastError();
        }
        return result;
    }

    HPOWERNOTIFY notify::register_suspend_resume(
            DEVICE_NOTIFY_SUBSCRIBE_PARAMETERS *subscribe) {
        HPOWERNOTIFY result =
                RegisterSuspendResumeNotification(subscribe,
                                                  DEVICE_NOTIFY_CALLBACK);
        if (!result) {
            error_code = GetLastError();
        }
        return result;
    }

    bool notify::unregister_suspend_resume(HPOWERNOTIFY power_notify_handle) {
        if (!UnregisterSuspendResumeNotification(power_notify_handle)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool notify::register_tooltip_dismiss(HWND window_handle) {
        return RegisterForTooltipDismissNotification(window_handle,
                                                     TDF_REGISTER);
    }

    bool notify::unregister_tooltip_dismiss(HWND window_handle) {
        return RegisterForTooltipDismissNotification(window_handle,
                                                     TDF_UNREGISTER);
    }
    uint32_t notify::err_code() const {
        return error_code;
    }

    std::string notify::err_string() const {
        std::string result = helper::convert::err_string(error_code);
        return result;
    }

    std::wstring notify::err_wstring() const {
        std::wstring result = helper::convert::err_wstring(error_code);
        return result;
    }
} // namespace YanLib::ui
