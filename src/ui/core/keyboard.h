/* clang-format off */
/*
 * @file keyboard.h
 * @date 2025-05-01
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
#ifndef KEYBOARD_H
#define KEYBOARD_H
#include <Windows.h>
#include <winnt.h>
#include <WinUser.h>
#include <windef.h>
#include <minwindef.h>
#include <vector>
#include <string>
#include "sync/rwlock.h"
#include "core.h"
namespace YanLib::ui::core {
    class keyboard {
    private:
        std::vector<HKL> layout_handles = {};
        std::vector<std::pair<HWND, int32_t>> hotkeys = {};
        sync::rwlock layout_rwlock = {};
        sync::rwlock hotkey_rwlock = {};
        uint32_t error_code = 0;

    public:
        keyboard(const keyboard &other) = delete;

        keyboard(keyboard &&other) = delete;

        keyboard &operator=(const keyboard &other) = delete;

        keyboard &operator=(keyboard &&other) = delete;

        keyboard() = default;

        ~keyboard();

        HKL load_layout(KeyboardID id = KeyboardID::ZH_CN,
                        KeyboardLayout layout = KeyboardLayout::Activate |
                                KeyboardLayout::SubstituteOk);

        bool register_hot_key(HWND window_handle,
                              int32_t id,
                              ModifiersKey mod_key,
                              VirtualKey vk);

        bool unregister_hot_key(HWND window_handle, int32_t id);

        HKL activate_layout(HKL layout_handle,
                            KeyboardLayout layout = KeyboardLayout::Activate |
                                    KeyboardLayout::SubstituteOk);

        bool unload_layout(HKL layout_handle);

        HKL get_layout(uint32_t tid);

        int32_t get_layout_list(std::vector<HKL> &layout_handle);

        bool get_layout_name(char *name);

        bool get_layout_name(wchar_t *name);

        bool get_state(uint8_t *key_state);

        bool set_state(uint8_t *key_state);

        int32_t get_type(int32_t type_flag);

        int32_t get_key_name(int32_t param, std::string &text);

        int32_t get_key_name(int32_t param, std::wstring &text);

        int16_t get_key_state(VirtualKey vk);

        uint16_t get_key_state_lparam(LPARAM lparam);

        uint16_t get_key_state_wparam(WPARAM wparam);

        int16_t get_async_key_state(VirtualKey vk);

        void send_event(VirtualKey vk,
                        uint8_t scan = 0,
                        KeyEvent kv = KeyEvent::ExtendedKey | KeyEvent::KeyDown,
                        uintptr_t extra_info = 0);

        uint32_t send_input(std::vector<INPUT> &input);

        uint8_t virtual_key_to_scan_code(VirtualKey vk,
                                         bool is_extended_key = false);

        VirtualKey scan_code_to_virtual_key(uint8_t scan_code,
                                            bool is_extended_key = false);

        uint32_t map_virtual_key(uint32_t code, MapType map_type);

        uint32_t
        map_virtual_key(uint32_t code, MapType map_type, HKL layout_handle);

        uint32_t oem_key_scan(uint16_t oem_char);

        bool vk_key_scan(char ch, ModKey6 *mod_key, VirtualKey *vk);

        bool vk_key_scan(wchar_t ch, ModKey6 *mod_key, VirtualKey *vk);

        bool vk_key_scan(char ch,
                         HKL layout_handle,
                         ModKey6 *mod_key,
                         VirtualKey *vk);

        bool vk_key_scan(wchar_t ch,
                         HKL layout_handle,
                         ModKey6 *mod_key,
                         VirtualKey *vk);

        HWND get_focus();

        HWND set_focus(HWND window_handle);

        int32_t to_ascii(VirtualKey vk,
                         uint32_t scan_code,
                         const uint8_t *key_state,
                         uint8_t *ch1,
                         uint8_t *ch2,
                         bool menu_active = false);

        int32_t to_ascii(VirtualKey vk,
                         HKL layout_handle,
                         uint32_t scan_code,
                         const uint8_t *key_state,
                         uint8_t *ch1,
                         uint8_t *ch2,
                         bool menu_active = false);

        int32_t to_unicode(VirtualKey vk,
                           uint32_t scan_code,
                           const uint8_t *key_state,
                           std::wstring &buf,
                           bool menu_active = false);

        int32_t to_unicode(VirtualKey vk,
                           HKL layout_handle,
                           uint32_t scan_code,
                           const uint8_t *key_state,
                           std::wstring &buf,
                           bool menu_active = false);

        bool is_any_input();

        bool block_input();

        bool resume_input();

        bool attach_input(uint32_t tid1, uint32_t tid2);

        bool detach_input(uint32_t tid1, uint32_t tid2);

        uint32_t wait_for_input_idle(HANDLE proc_handle,
                                     uint32_t milli_seconds);

        LRESULT default_raw_input_proc(RAWINPUT **raw_input,
                                       int32_t input,
                                       uint32_t header_size);

        uint16_t get_raw_input_code_wparam(WPARAM wparam);

        uint32_t get_raw_input_buffer(RAWINPUT *buf,
                                      uint32_t *size,
                                      uint32_t header_size);

        uint32_t get_raw_input_data(HRAWINPUT raw_input,
                                    uint32_t command,
                                    void *buf,
                                    uint32_t *size,
                                    uint32_t header_size);

        uint32_t get_raw_input_device_info(HANDLE device_handle,
                                           uint32_t command,
                                           void *buf,
                                           uint32_t *size);

        uint32_t
        get_raw_input_device_list(RAWINPUTDEVICELIST raw_input_device_list[],
                                  uint32_t *real_num);

        uint32_t
        get_registered_raw_input_devices(RAWINPUTDEVICE raw_input_devices[],
                                         uint32_t *real_num);

        RAWINPUT *next_raw_input_block(RAWINPUT *raw_input);

        bool
        register_raw_input_devices(const RAWINPUTDEVICE raw_input_devices[],
                                   uint32_t num);

        [[nodiscard]] uint32_t err_code() const;

        [[nodiscard]] std::string err_string() const;

        [[nodiscard]] std::wstring err_wstring() const;
    };
} // namespace YanLib::ui::core
#endif // KEYBOARD_H
