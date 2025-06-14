/* clang-format off */
/*
 * @file notify.cpp
 * @date 2025-05-18
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
#include "notify.h"
#include "helper/convert.h"
namespace YanLib::ui::core {
    notify::~notify() {
        for (auto &device : device_handles) {
            if (device) {
                UnregisterDeviceNotification(device);
                device = nullptr;
            }
        }
        device_handles.clear();
        for (auto &power : power_handles) {
            if (power) {
                UnregisterPowerSettingNotification(power);
                power = nullptr;
            }
        }
        power_handles.clear();
        for (auto &power2 : power2_handles) {
            if (power2) {
                UnregisterSuspendResumeNotification(power2);
                power2 = nullptr;
            }
        }
        power2_handles.clear();
        for (auto &tooltip : tooltip_handles) {
            if (tooltip && IsWindow(tooltip)) {
                RegisterForTooltipDismissNotification(tooltip, TDF_UNREGISTER);
                tooltip = nullptr;
            }
        }
        tooltip_handles.clear();
    }

    HDEVNOTIFY notify::register_device(HWND window_handle,
                                       void *notify_filter,
                                       bool notify_all) {
        HDEVNOTIFY result = RegisterDeviceNotificationW(
                window_handle, notify_filter,
                DEVICE_NOTIFY_WINDOW_HANDLE |
                        (notify_all ? DEVICE_NOTIFY_ALL_INTERFACE_CLASSES : 0));
        if (!result) {
            error_code = GetLastError();
            return nullptr;
        }
        device_rwlock.write_lock();
        device_handles.push_back(result);
        device_rwlock.write_unlock();
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
            return nullptr;
        }
        device_rwlock.write_lock();
        device_handles.push_back(result);
        device_rwlock.write_unlock();
        return result;
    }

    bool notify::unregister_device(HDEVNOTIFY device_notify_handle) {
        if (!device_notify_handle) {
            return false;
        }
        device_rwlock.write_lock();
        const auto it = std::find(device_handles.begin(), device_handles.end(),
                                  device_notify_handle);
        if (it != device_handles.end()) {
            *it = nullptr;
        }
        device_rwlock.write_unlock();
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
            return nullptr;
        }
        power_rwlock.write_lock();
        power_handles.push_back(result);
        power_rwlock.write_unlock();
        return result;
    }

    HPOWERNOTIFY notify::register_power_setting(HANDLE service_handle,
                                                const GUID *guid) {
        HPOWERNOTIFY result =
                RegisterPowerSettingNotification(service_handle, guid,
                                                 DEVICE_NOTIFY_SERVICE_HANDLE);
        if (!result) {
            error_code = GetLastError();
            return nullptr;
        }
        power_rwlock.write_lock();
        power_handles.push_back(result);
        power_rwlock.write_unlock();
        return result;
    }

    bool notify::unregister_power_setting(HPOWERNOTIFY power_notify_handle) {
        if (!power_notify_handle) {
            return false;
        }
        power_rwlock.write_lock();
        const auto it = std::find(power_handles.begin(), power_handles.end(),
                                  power_notify_handle);
        if (it != power_handles.end()) {
            *it = nullptr;
        }
        power_rwlock.write_unlock();
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
            return nullptr;
        }
        power2_rwlock.write_lock();
        power2_handles.push_back(result);
        power2_rwlock.write_unlock();
        return result;
    }

    HPOWERNOTIFY notify::register_suspend_resume(
            DEVICE_NOTIFY_SUBSCRIBE_PARAMETERS *subscribe) {
        HPOWERNOTIFY result =
                RegisterSuspendResumeNotification(subscribe,
                                                  DEVICE_NOTIFY_CALLBACK);
        if (!result) {
            error_code = GetLastError();
            return nullptr;
        }
        power2_rwlock.write_lock();
        power2_handles.push_back(result);
        power2_rwlock.write_unlock();
        return result;
    }

    bool notify::unregister_suspend_resume(HPOWERNOTIFY power_notify_handle) {
        if (!power_notify_handle) {
            return false;
        }
        power2_rwlock.write_lock();
        const auto it = std::find(power2_handles.begin(), power2_handles.end(),
                                  power_notify_handle);
        if (it != power2_handles.end()) {
            *it = nullptr;
        }
        power2_rwlock.write_unlock();
        if (!UnregisterSuspendResumeNotification(power_notify_handle)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool notify::register_tooltip_dismiss(HWND window_handle) {
        const bool is_ok = RegisterForTooltipDismissNotification(window_handle,
                                                                 TDF_REGISTER);
        if (!is_ok) {
            return false;
        }
        tooltip_rwlock.write_lock();
        tooltip_handles.push_back(window_handle);
        tooltip_rwlock.write_unlock();
        return is_ok;
    }

    bool notify::unregister_tooltip_dismiss(HWND window_handle) {
        if (!window_handle) {
            return false;
        }
        tooltip_rwlock.write_lock();
        const auto it = std::find(tooltip_handles.begin(),
                                  tooltip_handles.end(), window_handle);
        if (it != tooltip_handles.end()) {
            *it = nullptr;
        }
        tooltip_rwlock.write_unlock();
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
} // namespace YanLib::ui::core
