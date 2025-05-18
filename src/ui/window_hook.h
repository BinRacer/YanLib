//
// Created by forkernel on 2025/5/18.
//

#ifndef WINDOW_HOOK_H
#define WINDOW_HOOK_H
#include <Windows.h>
#include <string>
namespace YanLib::ui {
class window_hook {
private:
    uint32_t error_code = 0;

public:
    window_hook(const window_hook &other)            = delete;

    window_hook(window_hook &&other)                 = delete;

    window_hook &operator=(const window_hook &other) = delete;

    window_hook &operator=(window_hook &&other)      = delete;

    window_hook()                                    = default;

    ~window_hook()                                   = default;

    bool register_shell(HWND window_handle);

    bool unregister_shell(HWND window_handle);

    HHOOK
    set(int32_t   hook_type,
        HOOKPROC  hook_proc,
        HINSTANCE dll_handle,
        uint32_t  tid);

    bool unset(HHOOK hook_handle);

    LRESULT
    call_next(HHOOK hook_handle, int32_t code, WPARAM wparam, LPARAM lparam);

    HWINEVENTHOOK set_event(uint32_t event_min,
        uint32_t                     event_max,
        HMODULE                      dll_handle,
        WINEVENTPROC                 event_proc,
        uint32_t                     pid,
        uint32_t                     tid,
        uint32_t                     flag);

    bool unset_event(HWINEVENTHOOK event_hook);

    bool is_event_installed(uint32_t event);

    void notify_event(uint32_t event,
        HWND                   window_handle,
        int32_t                object_id,
        int32_t                child_id);

    [[nodiscard]] uint32_t err_code() const;

    [[nodiscard]] std::string err_string() const;

    [[nodiscard]] std::wstring err_wstring() const;
};
} // namespace YanLib::ui
#endif // WINDOW_HOOK_H
