/* clang-format off */
/*
 * @file window_hook.cpp
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
#include "window_hook.h"
#include "helper/convert.h"

namespace YanLib::ui::core {
    window_hook::~window_hook() {
        for (auto &window : shell_handles) {
            if (window && IsWindow(window)) {
                DeregisterShellHookWindow(window);
                window = nullptr;
            }
        }
        shell_handles.clear();
        for (auto &hook : hook_handles) {
            if (hook) {
                UnhookWindowsHookEx(hook);
                hook = nullptr;
            }
        }
        hook_handles.clear();
        for (auto &event : event_handles) {
            if (event) {
                UnhookWinEvent(event);
                event = nullptr;
            }
        }
        event_handles.clear();
    }

    bool window_hook::register_shell(HWND window_handle) {
        if (const bool is_ok = RegisterShellHookWindow(window_handle); !is_ok) {
            return false;
        }
        shell_rwlock.write_lock();
        shell_handles.push_back(window_handle);
        shell_rwlock.write_unlock();
        return true;
    }

    bool window_hook::unregister_shell(HWND window_handle) {
        if (!window_handle) {
            return false;
        }
        shell_rwlock.write_lock();
        const auto it = std::find(shell_handles.begin(), shell_handles.end(),
                                  window_handle);
        if (it != shell_handles.end()) {
            *it = nullptr;
        }
        shell_rwlock.write_unlock();
        return DeregisterShellHookWindow(window_handle);
    }

    HHOOK window_hook::set_hook(HOOKPROC hook_proc,
                                HINSTANCE dll_handle,
                                uint32_t tid,
                                HookType hook_type) {
        HHOOK result = SetWindowsHookExW(static_cast<int32_t>(hook_type),
                                         hook_proc, dll_handle, tid);
        if (!result) {
            error_code = GetLastError();
            return nullptr;
        }
        hook_rwlock.write_lock();
        hook_handles.push_back(result);
        hook_rwlock.write_unlock();
        return result;
    }

    bool window_hook::unset_hook(HHOOK hook_handle) {
        if (!hook_handle) {
            return false;
        }
        hook_rwlock.write_lock();
        const auto it = std::find(hook_handles.begin(), hook_handles.end(),
                                  hook_handle);
        if (it != hook_handles.end()) {
            *it = nullptr;
        }
        hook_rwlock.write_unlock();
        if (!UnhookWindowsHookEx(hook_handle)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    LRESULT window_hook::call_next(HHOOK hook_handle,
                                   int32_t code,
                                   WPARAM wparam,
                                   LPARAM lparam) {
        return CallNextHookEx(hook_handle, code, wparam, lparam);
    }

    HWINEVENTHOOK window_hook::set_event(WINEVENTPROC event_proc,
                                         HMODULE dll_handle,
                                         uint32_t pid,
                                         uint32_t tid,
                                         WindowEvent min,
                                         WindowEvent max,
                                         EventFlag flag) {
        HWINEVENTHOOK result = SetWinEventHook(static_cast<uint32_t>(min),
                                               static_cast<uint32_t>(max),
                                               dll_handle, event_proc, pid, tid,
                                               static_cast<uint32_t>(flag));
        if (!result) {
            return nullptr;
        }
        event_rwlock.write_lock();
        event_handles.push_back(result);
        event_rwlock.write_unlock();
        return result;
    }

    bool window_hook::unset_event(HWINEVENTHOOK event_hook) {
        if (!event_hook) {
            return false;
        }
        event_rwlock.write_lock();
        const auto it = std::find(event_handles.begin(), event_handles.end(),
                                  event_hook);
        if (it != event_handles.end()) {
            *it = nullptr;
        }
        event_rwlock.write_unlock();
        return UnhookWinEvent(event_hook);
    }

    bool window_hook::is_event_installed(uint32_t event) {
        return IsWinEventHookInstalled(event);
    }

    void window_hook::notify_event(HWND window_handle,
                                   int32_t control_id,
                                   ObjectID object_id,
                                   WindowEvent event) {
        NotifyWinEvent(static_cast<uint32_t>(event), window_handle,
                       static_cast<int32_t>(object_id), control_id);
    }

    uint32_t window_hook::err_code() const {
        return error_code;
    }

    std::string window_hook::err_string() const {
        std::string result = helper::convert::err_string(error_code);
        return result;
    }

    std::wstring window_hook::err_wstring() const {
        std::wstring result = helper::convert::err_wstring(error_code);
        return result;
    }
} // namespace YanLib::ui::core
