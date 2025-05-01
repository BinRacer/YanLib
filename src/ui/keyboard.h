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
        DWORD error_code = 0;

    public:
        keyboard(const keyboard &other) = delete;

        keyboard(keyboard &&other) = delete;

        keyboard &operator=(const keyboard &other) = delete;

        keyboard &operator=(keyboard &&other) = delete;

        keyboard() = default;

        ~keyboard() = default;

        HKL load_keyboard_layout(const wchar_t *kl_id = L"00000804",
                                 UINT flag = KLF_ACTIVATE | KLF_SUBSTITUTE_OK);

        bool register_hot_key(HWND hwnd, int id, UINT modifiers, UINT vk);

        bool unregister_hot_key(HWND hwnd, int id);

        HKL activate_keyboard_layout(HKL hkl, UINT flag);

        bool unload_keyboard_layout(HKL hkl);

        HKL get_keyboard_layout(DWORD tid);

        int get_keyboard_layout_list(int hkl_count, HKL *hkl_buf);

        bool get_keyboard_layout_name(wchar_t *kl_id);

        bool get_keyboard_state(uint8_t *key_state);

        bool set_keyboard_state(uint8_t *key_state);

        int get_keyboard_type(int type_flag);

        int get_key_name_text(LONG param, wchar_t *buf, int cch_size);

        SHORT get_key_state(int vk);

        WORD get_key_state_lparam(LPARAM l_param);

        WORD get_key_state_wparam(WPARAM w_param);

        SHORT get_async_key_state(int vk);

        void send_keyboard_event(uint8_t vk,
                                 uint8_t scan,
                                 DWORD flag,
                                 ULONG_PTR extra_info);

        UINT map_virtual_key(UINT code, UINT map_type);

        UINT map_virtual_key(UINT code, UINT map_type, HKL hkl);

        DWORD oem_key_scan(WORD oem_char);

        SHORT vk_key_scan(wchar_t ch);

        SHORT vk_key_scan(wchar_t ch, HKL hkl);

        bool block_input(bool block_it);

        bool attach_thread_input(DWORD tid_from, DWORD tid_to, bool attach);

        [[nodiscard]] DWORD err_code() const;

        [[nodiscard]] std::string err_string() const;

        [[nodiscard]] std::wstring err_wstring() const;
    };
}
#endif //KEYBOARD_H
