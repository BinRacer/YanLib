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
                                 unsigned int flag = KLF_ACTIVATE | KLF_SUBSTITUTE_OK);

        bool register_hot_key(HWND hwnd, int id, unsigned int modifiers, unsigned int vk);

        bool unregister_hot_key(HWND hwnd, int id);

        HKL activate_keyboard_layout(HKL hkl, unsigned int flag);

        bool unload_keyboard_layout(HKL hkl);

        HKL get_keyboard_layout(unsigned long tid);

        int get_keyboard_layout_list(int hkl_count, HKL *hkl_buf);

        bool get_keyboard_layout_name(wchar_t *kl_id);

        bool get_keyboard_state(uint8_t *key_state);

        bool set_keyboard_state(uint8_t *key_state);

        int get_keyboard_type(int type_flag);

        int get_key_name_text(long param, wchar_t *buf, int cch_size);

        short get_key_state(int vk);

        unsigned short get_key_state_lparam(LPARAM l_param);

        unsigned short get_key_state_wparam(WPARAM w_param);

        short get_async_key_state(int vk);

        void send_keyboard_event(uint8_t vk,
                                 uint8_t scan,
                                 unsigned long flag,
                                 ULONG_PTR extra_info);

        unsigned int map_virtual_key(unsigned int code, unsigned int map_type);

        unsigned int map_virtual_key(unsigned int code, unsigned int map_type, HKL hkl);

        unsigned long oem_key_scan(unsigned short oem_char);

        short vk_key_scan(wchar_t ch);

        short vk_key_scan(wchar_t ch, HKL hkl);

        HWND get_focus();

        HWND set_focus(HWND hwnd);

        int to_ascii(unsigned int vk,
                     unsigned int scan_code,
                     const uint8_t *key_state,
                     unsigned short *ch,
                     unsigned int flag);

        int to_ascii(unsigned int vk,
                     unsigned int scan_code,
                     const uint8_t *key_state,
                     unsigned short *ch,
                     unsigned int flag,
                     HKL hkl);

        int to_unicode(unsigned int vk,
                       unsigned int scan_code,
                       const uint8_t *key_state,
                       wchar_t *buf,
                       int cch_size,
                       unsigned int flag);

        int to_unicode(unsigned int vk,
                       unsigned int scan_code,
                       const uint8_t *key_state,
                       wchar_t *buf,
                       int cch_size,
                       unsigned int flag,
                       HKL hkl);

        bool get_input_state();

        bool block_input(bool block_it);

        bool attach_thread_input(unsigned long tid_from, unsigned long tid_to, bool attach);

        unsigned long wait_for_input_idle(HANDLE proc_handle, unsigned long milli_seconds);

        LRESULT default_raw_input_proc(RAWINPUT * *raw_input,
                                       int input,
                                       unsigned int cb_size_header);

        unsigned short get_rawinput_code_wparam(WPARAM w_param);

        unsigned int get_raw_input_buffer(RAWINPUT *data,
                                          unsigned int *cb_size,
                                          unsigned int cb_size_header);

        unsigned int get_raw_input_data(HRAWINPUT raw_input,
                                        unsigned int command,
                                        void *data,
                                        unsigned int *cb_size,
                                        unsigned int cb_size_header);

        unsigned int get_raw_input_device_info(HANDLE device_handle,
                                               unsigned int command,
                                               void *data,
                                               unsigned int *cb_size);

        unsigned int get_raw_input_device_list(RAWINPUTDEVICELIST *raw_input_device_list,
                                               unsigned int *num_devices,
                                               unsigned int cb_size);

        unsigned int get_registered_raw_input_devices(RAWINPUTDEVICE *raw_input_devices,
                                                      unsigned int *num_devices,
                                                      unsigned int cb_size);


        RAWINPUT *next_raw_input_block(RAWINPUT *raw_input);

        bool register_raw_input_devices(const RAWINPUTDEVICE *raw_input_devices,
                                        unsigned int num_devices,
                                        unsigned int cb_size);

        [[nodiscard]] unsigned long err_code() const;

        [[nodiscard]] std::string err_string() const;

        [[nodiscard]] std::wstring err_wstring() const;
    };
}
#endif //KEYBOARD_H
