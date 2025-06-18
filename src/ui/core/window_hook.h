/* clang-format off */
/*
 * @file window_hook.h
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
#ifndef WINDOW_HOOK_H
#define WINDOW_HOOK_H
#include <Windows.h>
#include <WinUser.h>
#include <minwindef.h>
#include <windef.h>
#include <string>
#include <vector>
#include "sync/rwlock.h"
#include "core.h"
namespace YanLib::ui::core {
    class window_hook {
    private:
        std::vector<HWND> shell_handles = {};
        std::vector<HHOOK> hook_handles = {};
        std::vector<HWINEVENTHOOK> event_handles = {};
        sync::rwlock shell_rwlock = {};
        sync::rwlock hook_rwlock = {};
        sync::rwlock event_rwlock = {};
        uint32_t error_code = 0;

    public:
        window_hook(const window_hook &other) = delete;

        window_hook(window_hook &&other) = delete;

        window_hook &operator=(const window_hook &other) = delete;

        window_hook &operator=(window_hook &&other) = delete;

        window_hook() = default;

        ~window_hook();

        bool register_shell(HWND window_handle);

        bool unregister_shell(HWND window_handle);

        HHOOK set_hook(HOOKPROC hook_proc,
                       HINSTANCE dll_handle = nullptr,
                       uint32_t tid = 0,
                       HookType hook_type = HookType::GetMsg);

        bool unset_hook(HHOOK hook_handle);

        LRESULT call_next(HHOOK hook_handle,
                          int32_t code,
                          WPARAM wparam,
                          LPARAM lparam);

        HWINEVENTHOOK set_event(WINEVENTPROC event_proc,
                                HMODULE dll_handle = nullptr,
                                uint32_t pid = 0,
                                uint32_t tid = 0,
                                WindowEvent min = WindowEvent::Min,
                                WindowEvent max = WindowEvent::Max,
                                EventFlag flag = EventFlag::OutOfContext |
                                        EventFlag::SkipOwnProcess);

        bool unset_event(HWINEVENTHOOK event_hook);

        bool is_event_installed(uint32_t event);

        void notify_event(HWND window_handle,
                          int32_t control_id,
                          ObjectID object_id = ObjectID::Client,
                          WindowEvent event = WindowEvent::ObjectCreate);

        [[nodiscard]] uint32_t err_code() const;

        [[nodiscard]] std::string err_string() const;

        [[nodiscard]] std::wstring err_wstring() const;
    };
} // namespace YanLib::ui::core
#endif // WINDOW_HOOK_H
