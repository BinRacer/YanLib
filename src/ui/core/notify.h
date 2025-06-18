/* clang-format off */
/*
 * @file notify.h
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
#ifndef NOTIFY_H
#define NOTIFY_H
#include <Windows.h>
#include <guiddef.h>
#include <windef.h>
#include <WinUser.h>
#include <Powrprof.h>
#include <string>
#include <vector>
#include "sync/rwlock.h"
#pragma comment(lib, "Powrprof.lib")
namespace YanLib::ui::core {
    class notify {
    private:
        std::vector<HDEVNOTIFY> device_handles = {};
        std::vector<HPOWERNOTIFY> power_handles = {};
        std::vector<HPOWERNOTIFY> power2_handles = {};
        std::vector<HWND> tooltip_handles = {};
        sync::rwlock device_rwlock = {};
        sync::rwlock power_rwlock = {};
        sync::rwlock power2_rwlock = {};
        sync::rwlock tooltip_rwlock = {};
        uint32_t error_code = 0;

    public:
        notify(const notify &other) = delete;

        notify(notify &&other) = delete;

        notify &operator=(const notify &other) = delete;

        notify &operator=(notify &&other) = delete;

        notify() = default;

        ~notify();

        HDEVNOTIFY register_device(HWND window_handle,
                                   void *notify_filter,
                                   bool notify_all = true);

        HDEVNOTIFY register_device(HANDLE service_handle,
                                   void *notify_filter,
                                   bool notify_all = true);

        bool unregister_device(HDEVNOTIFY device_notify_handle);

        HPOWERNOTIFY register_power_setting(HWND window_handle,
                                            const GUID *guid);

        HPOWERNOTIFY register_power_setting(HANDLE service_handle,
                                            const GUID *guid);

        bool unregister_power_setting(HPOWERNOTIFY power_notify_handle);

        HPOWERNOTIFY register_suspend_resume(HWND window_handle);

        HPOWERNOTIFY
        register_suspend_resume(DEVICE_NOTIFY_SUBSCRIBE_PARAMETERS *subscribe);

        bool unregister_suspend_resume(HPOWERNOTIFY power_notify_handle);

        bool register_tooltip_dismiss(HWND window_handle);

        bool unregister_tooltip_dismiss(HWND window_handle);

        [[nodiscard]] uint32_t err_code() const;

        [[nodiscard]] std::string err_string() const;

        [[nodiscard]] std::wstring err_wstring() const;
    };
} // namespace YanLib::ui::core
#endif // NOTIFY_H
