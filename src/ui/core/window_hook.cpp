//
// Created by forkernel on 2025/5/18.
//

#include "window_hook.h"
#include "helper/convert.h"

namespace YanLib::ui::core {
    bool window_hook::register_shell(HWND window_handle) {
        return RegisterShellHookWindow(window_handle);
    }

    bool window_hook::unregister_shell(HWND window_handle) {
        return DeregisterShellHookWindow(window_handle);
    }

    HHOOK window_hook::set(HOOKPROC hook_proc,
                           HINSTANCE dll_handle,
                           uint32_t tid,
                           HookType hook_type) {
        HHOOK result = SetWindowsHookExW(static_cast<int32_t>(hook_type),
                                         hook_proc, dll_handle, tid);
        if (!result) {
            error_code = GetLastError();
        }
        return result;
    }

    bool window_hook::unset(HHOOK hook_handle) {
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
        return SetWinEventHook(static_cast<uint32_t>(min),
                               static_cast<uint32_t>(max), dll_handle,
                               event_proc, pid, tid,
                               static_cast<uint32_t>(flag));
    }

    bool window_hook::unset_event(HWINEVENTHOOK event_hook) {
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
