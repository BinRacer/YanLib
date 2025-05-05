//
// Created by forkernel on 2025/5/1.
//

#ifndef KEYBOARD_H
#define KEYBOARD_H
#include <Windows.h>
#include <string>

namespace YanLib::ui {
    class keyboard {
    private:
        unsigned long error_code = 0;

    public:
        keyboard(const keyboard &other) = delete;

        keyboard(keyboard &&other) = delete;

        keyboard &operator=(const keyboard &other) = delete;

        keyboard &operator=(keyboard &&other) = delete;

        keyboard() = default;

        ~keyboard() = default;

        HKL load_keyboard_layout(const wchar_t *kl_id = L"00000804",
                                 uint32_t flag = KLF_ACTIVATE | KLF_SUBSTITUTE_OK);

        bool register_hot_key(HWND hwnd, int32_t id, uint32_t modifiers, uint32_t vk);

        bool unregister_hot_key(HWND hwnd, int32_t id);

        HKL activate_keyboard_layout(HKL hkl, uint32_t flag);

        bool unload_keyboard_layout(HKL hkl);

        HKL get_keyboard_layout(unsigned long tid);

        int32_t get_keyboard_layout_list(int32_t hkl_count, HKL *hkl_buf);

        bool get_keyboard_layout_name(wchar_t *kl_id);

        bool get_keyboard_state(uint8_t *key_state);

        bool set_keyboard_state(uint8_t *key_state);

        int32_t get_keyboard_type(int32_t type_flag);

        int32_t get_key_name_text(long param, wchar_t *buf, int32_t cch_size);

        int16_t get_key_state(int32_t vk);

        uint16_t get_key_state_lparam(LPARAM l_param);

        uint16_t get_key_state_wparam(WPARAM w_param);

        int16_t get_async_key_state(int32_t vk);

        void send_keyboard_event(uint8_t vk,
                                 uint8_t scan,
                                 unsigned long flag,
                                 ULONG_PTR extra_info);

        uint32_t map_virtual_key(uint32_t code, uint32_t map_type);

        uint32_t map_virtual_key(uint32_t code, uint32_t map_type, HKL hkl);

        unsigned long oem_key_scan(uint16_t oem_char);

        int16_t vk_key_scan(wchar_t ch);

        int16_t vk_key_scan(wchar_t ch, HKL hkl);

        HWND get_focus();

        HWND set_focus(HWND hwnd);

        int32_t to_ascii(uint32_t vk,
                     uint32_t scan_code,
                     const uint8_t *key_state,
                     uint16_t *ch,
                     uint32_t flag);

        int32_t to_ascii(uint32_t vk,
                     uint32_t scan_code,
                     const uint8_t *key_state,
                     uint16_t *ch,
                     uint32_t flag,
                     HKL hkl);

        int32_t to_unicode(uint32_t vk,
                       uint32_t scan_code,
                       const uint8_t *key_state,
                       wchar_t *buf,
                       int32_t cch_size,
                       uint32_t flag);

        int32_t to_unicode(uint32_t vk,
                       uint32_t scan_code,
                       const uint8_t *key_state,
                       wchar_t *buf,
                       int32_t cch_size,
                       uint32_t flag,
                       HKL hkl);

        bool get_input_state();

        bool block_input(bool block_it);

        bool attach_thread_input(unsigned long tid_from, unsigned long tid_to, bool attach);

        unsigned long wait_for_input_idle(HANDLE proc_handle, unsigned long milli_seconds);

        LRESULT default_raw_input_proc(RAWINPUT * *raw_input,
                                       int32_t input,
                                       uint32_t cb_size_header);

        uint16_t get_rawinput_code_wparam(WPARAM w_param);

        uint32_t get_raw_input_buffer(RAWINPUT *data,
                                          uint32_t *cb_size,
                                          uint32_t cb_size_header);

        uint32_t get_raw_input_data(HRAWINPUT raw_input,
                                        uint32_t command,
                                        void *data,
                                        uint32_t *cb_size,
                                        uint32_t cb_size_header);

        uint32_t get_raw_input_device_info(HANDLE device_handle,
                                               uint32_t command,
                                               void *data,
                                               uint32_t *cb_size);

        uint32_t get_raw_input_device_list(RAWINPUTDEVICELIST *raw_input_device_list,
                                               uint32_t *num_devices,
                                               uint32_t cb_size);

        uint32_t get_registered_raw_input_devices(RAWINPUTDEVICE *raw_input_devices,
                                                      uint32_t *num_devices,
                                                      uint32_t cb_size);


        RAWINPUT *next_raw_input_block(RAWINPUT *raw_input);

        bool register_raw_input_devices(const RAWINPUTDEVICE *raw_input_devices,
                                        uint32_t num_devices,
                                        uint32_t cb_size);

        [[nodiscard]] unsigned long err_code() const;

        [[nodiscard]] std::string err_string() const;

        [[nodiscard]] std::wstring err_wstring() const;
    };
}
#endif //KEYBOARD_H
