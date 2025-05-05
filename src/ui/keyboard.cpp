//
// Created by forkernel on 2025/5/1.
//

#include "keyboard.h"
#include "helper/convert.h"

namespace YanLib::ui {
    HKL keyboard::load_keyboard_layout(const wchar_t *kl_id, unsigned int flag) {
        HKL result = LoadKeyboardLayoutW(kl_id, flag);
        if (!result) {
            error_code = GetLastError();
        }
        return result;
    }

    bool keyboard::register_hot_key(HWND hwnd, int id, unsigned int modifiers, unsigned int vk) {
        if (!RegisterHotKey(hwnd, id, modifiers, vk)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool keyboard::unregister_hot_key(HWND hwnd, int id) {
        if (!UnregisterHotKey(hwnd, id)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    HKL keyboard::activate_keyboard_layout(HKL hkl, unsigned int flag) {
        HKL result = ActivateKeyboardLayout(hkl, flag);
        if (!result) {
            error_code = GetLastError();
        }
        return result;
    }

    bool keyboard::unload_keyboard_layout(HKL hkl) {
        if (!UnloadKeyboardLayout(hkl)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    HKL keyboard::get_keyboard_layout(unsigned long tid) {
        return GetKeyboardLayout(tid);
    }

    int keyboard::get_keyboard_layout_list(int hkl_count, HKL *hkl_buf) {
        int result = GetKeyboardLayoutList(hkl_count, hkl_buf);
        if (!result) {
            error_code = GetLastError();
        }
        return result;
    }

    bool keyboard::get_keyboard_layout_name(wchar_t *kl_id) {
        if (!GetKeyboardLayoutNameW(kl_id)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool keyboard::get_keyboard_state(uint8_t *key_state) {
        if (!GetKeyboardState(key_state)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool keyboard::set_keyboard_state(uint8_t *key_state) {
        if (!SetKeyboardState(key_state)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    int keyboard::get_keyboard_type(int type_flag) {
        int result = GetKeyboardType(type_flag);
        if (type_flag != 1 && !result) {
            error_code = GetLastError();
        }
        return result;
    }

    int keyboard::get_key_name_text(long param, wchar_t *buf, int cch_size) {
        int result = GetKeyNameTextW(param, buf, cch_size);
        if (!result) {
            error_code = GetLastError();
        }
        return result;
    }

    short keyboard::get_key_state(int vk) {
        return GetKeyState(vk);
    }

    unsigned short keyboard::get_key_state_lparam(LPARAM l_param) {
        return GET_KEYSTATE_LPARAM(l_param);
    }

    unsigned short keyboard::get_key_state_wparam(WPARAM w_param) {
        return GET_KEYSTATE_WPARAM(w_param);
    }

    short keyboard::get_async_key_state(int vk) {
        return GetAsyncKeyState(vk);
    }

    void keyboard::send_keyboard_event(uint8_t vk,
                                       uint8_t scan,
                                       unsigned long flag,
                                       ULONG_PTR extra_info) {
        keybd_event(vk, scan, flag, extra_info);
    }

    unsigned int keyboard::map_virtual_key(unsigned int code, unsigned int map_type) {
        return MapVirtualKeyW(code, map_type);
    }

    unsigned int keyboard::map_virtual_key(unsigned int code, unsigned int map_type, HKL hkl) {
        return MapVirtualKeyExW(code, map_type, hkl);
    }

    unsigned long keyboard::oem_key_scan(unsigned short oem_char) {
        return OemKeyScan(oem_char);
    }

    short keyboard::vk_key_scan(wchar_t ch) {
        return VkKeyScanW(ch);
    }

    short keyboard::vk_key_scan(wchar_t ch, HKL hkl) {
        return VkKeyScanExW(ch, hkl);
    }

    HWND keyboard::get_focus() {
        return GetFocus();
    }

    HWND keyboard::set_focus(HWND hwnd) {
        HWND result = SetFocus(hwnd);
        if (!result) {
            error_code = GetLastError();
        }
        return result;
    }

    int keyboard::to_ascii(unsigned int vk,
                           unsigned int scan_code,
                           const uint8_t *key_state,
                           unsigned short *ch,
                           unsigned int flag) {
        return ToAscii(vk, scan_code, key_state, ch, flag);
    }

    int keyboard::to_ascii(unsigned int vk,
                           unsigned int scan_code,
                           const uint8_t *key_state,
                           unsigned short *ch,
                           unsigned int flag,
                           HKL hkl) {
        return ToAsciiEx(vk,
                         scan_code,
                         key_state,
                         ch,
                         flag,
                         hkl);
    }

    int keyboard::to_unicode(unsigned int vk,
                             unsigned int scan_code,
                             const uint8_t *key_state,
                             wchar_t *buf,
                             int cch_size,
                             unsigned int flag) {
        return ToUnicode(vk,
                         scan_code,
                         key_state,
                         buf,
                         cch_size,
                         flag);
    }

    int keyboard::to_unicode(unsigned int vk,
                             unsigned int scan_code,
                             const uint8_t *key_state,
                             wchar_t *buf,
                             int cch_size,
                             unsigned int flag,
                             HKL hkl) {
        return ToUnicodeEx(vk,
                           scan_code,
                           key_state,
                           buf,
                           cch_size,
                           flag,
                           hkl);
    }

    bool keyboard::get_input_state() {
        return GetInputState();
    }

    bool keyboard::block_input(bool block_it) {
        if (!BlockInput(block_it ? TRUE : FALSE)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool keyboard::attach_thread_input(unsigned long tid_from, unsigned long tid_to, bool attach) {
        if (!AttachThreadInput(tid_from,
                               tid_to,
                               attach ? TRUE : FALSE)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    unsigned long keyboard::wait_for_input_idle(HANDLE proc_handle, unsigned long milli_seconds) {
        return WaitForInputIdle(proc_handle, milli_seconds);
    }

    LRESULT keyboard::default_raw_input_proc(RAWINPUT * *raw_input,
                                             int input,
                                             unsigned int cb_size_header) {
        return DefRawInputProc(raw_input, input, cb_size_header);
    }

    unsigned short keyboard::get_rawinput_code_wparam(WPARAM w_param) {
        return GET_RAWINPUT_CODE_WPARAM(w_param);
    }

    unsigned int keyboard::get_raw_input_buffer(RAWINPUT *data,
                                                unsigned int *cb_size,
                                                unsigned int cb_size_header) {
        unsigned int result = GetRawInputBuffer(data, cb_size, cb_size_header);
        if (result == static_cast<unsigned int>(-1)) {
            error_code = GetLastError();
        }
        return result;
    }

    unsigned int keyboard::get_raw_input_data(HRAWINPUT raw_input,
                                              unsigned int command,
                                              void *data,
                                              unsigned int *cb_size,
                                              unsigned int cb_size_header) {
        return GetRawInputData(raw_input,
                               command,
                               data,
                               cb_size,
                               cb_size_header);
    }

    unsigned int keyboard::get_raw_input_device_info(HANDLE device_handle,
                                                     unsigned int command,
                                                     void *data,
                                                     unsigned int *cb_size) {
        unsigned int result = GetRawInputDeviceInfoW(device_handle,
                                                     command,
                                                     data,
                                                     cb_size);
        error_code = GetLastError();
        return result;
    }

    unsigned int
    keyboard::get_raw_input_device_list(RAWINPUTDEVICELIST *raw_input_device_list,
                                        unsigned int *num_devices,
                                        unsigned int cb_size) {
        unsigned int result = GetRawInputDeviceList(raw_input_device_list,
                                                    num_devices,
                                                    cb_size);
        if (result == static_cast<unsigned int>(-1)) {
            error_code = GetLastError();
        }
        return result;
    }

    unsigned int
    keyboard::get_registered_raw_input_devices(RAWINPUTDEVICE *raw_input_devices,
                                               unsigned int *num_devices,
                                               unsigned int cb_size) {
        unsigned int result = GetRegisteredRawInputDevices(raw_input_devices,
                                                           num_devices,
                                                           cb_size);
        if (result == static_cast<unsigned int>(-1)) {
            error_code = GetLastError();
        }
        return result;
    }

    RAWINPUT *keyboard::next_raw_input_block(RAWINPUT *raw_input) {
        typedef unsigned __int64 QWORD;
        return NEXTRAWINPUTBLOCK(raw_input);
    }

    bool keyboard::register_raw_input_devices(const RAWINPUTDEVICE *raw_input_devices,
                                              unsigned int num_devices,
                                              unsigned int cb_size) {
        if (!RegisterRawInputDevices(raw_input_devices,
                                     num_devices,
                                     cb_size)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    unsigned long keyboard::err_code() const {
        return error_code;
    }

    std::string keyboard::err_string() const {
        std::string result = helper::convert::err_string(error_code);
        return result;
    }

    std::wstring keyboard::err_wstring() const {
        std::wstring result = helper::convert::err_wstring(error_code);
        return result;
    }
}
