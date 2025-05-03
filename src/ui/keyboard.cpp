//
// Created by forkernel on 2025/5/1.
//

#include "keyboard.h"
#include "helper/convert.h"

namespace YanLib::ui {
    HKL keyboard::load_keyboard_layout(const wchar_t *kl_id, UINT flag) {
        HKL result = LoadKeyboardLayoutW(kl_id, flag);
        if (!result) {
            error_code = GetLastError();
        }
        return result;
    }

    bool keyboard::register_hot_key(HWND hwnd, int id, UINT modifiers, UINT vk) {
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

    HKL keyboard::activate_keyboard_layout(HKL hkl, UINT flag) {
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

    HKL keyboard::get_keyboard_layout(DWORD tid) {
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

    int keyboard::get_key_name_text(LONG param, wchar_t *buf, int cch_size) {
        int result = GetKeyNameTextW(param, buf, cch_size);
        if (!result) {
            error_code = GetLastError();
        }
        return result;
    }

    SHORT keyboard::get_key_state(int vk) {
        return GetKeyState(vk);
    }

    WORD keyboard::get_key_state_lparam(LPARAM l_param) {
        return GET_KEYSTATE_LPARAM(l_param);
    }

    WORD keyboard::get_key_state_wparam(WPARAM w_param) {
        return GET_KEYSTATE_WPARAM(w_param);
    }

    SHORT keyboard::get_async_key_state(int vk) {
        return GetAsyncKeyState(vk);
    }

    void keyboard::send_keyboard_event(uint8_t vk,
                                       uint8_t scan,
                                       DWORD flag,
                                       ULONG_PTR extra_info) {
        keybd_event(vk, scan, flag, extra_info);
    }

    UINT keyboard::map_virtual_key(UINT code, UINT map_type) {
        return MapVirtualKeyW(code, map_type);
    }

    UINT keyboard::map_virtual_key(UINT code, UINT map_type, HKL hkl) {
        return MapVirtualKeyExW(code, map_type, hkl);
    }

    DWORD keyboard::oem_key_scan(WORD oem_char) {
        return OemKeyScan(oem_char);
    }

    SHORT keyboard::vk_key_scan(wchar_t ch) {
        return VkKeyScanW(ch);
    }

    SHORT keyboard::vk_key_scan(wchar_t ch, HKL hkl) {
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

    int keyboard::to_ascii(UINT vk,
                           UINT scan_code,
                           const uint8_t *key_state,
                           WORD* ch,
                           UINT flag) {
        return ToAscii(vk, scan_code, key_state, ch, flag);
    }

    int keyboard::to_ascii(UINT vk,
                           UINT scan_code,
                           const uint8_t *key_state,
                           WORD* ch,
                           UINT flag,
                           HKL hkl) {
        return ToAsciiEx(vk,
                         scan_code,
                         key_state,
                         ch,
                         flag,
                         hkl);
    }

    int keyboard::to_unicode(UINT vk,
                             UINT scan_code,
                             const uint8_t *key_state,
                             wchar_t *buf,
                             int cch_size,
                             UINT flag) {
        return ToUnicode(vk,
                         scan_code,
                         key_state,
                         buf,
                         cch_size,
                         flag);
    }

    int keyboard::to_unicode(UINT vk,
                             UINT scan_code,
                             const uint8_t *key_state,
                             wchar_t *buf,
                             int cch_size,
                             UINT flag,
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

    bool keyboard::attach_thread_input(DWORD tid_from, DWORD tid_to, bool attach) {
        if (!AttachThreadInput(tid_from,
                               tid_to,
                               attach ? TRUE : FALSE)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    DWORD keyboard::wait_for_input_idle(HANDLE proc_handle, DWORD milli_seconds) {
        return WaitForInputIdle(proc_handle, milli_seconds);
    }

    LRESULT keyboard::default_raw_input_proc(RAWINPUT* *raw_input,
                                             INT input,
                                             UINT cb_size_header) {
        return DefRawInputProc(raw_input, input, cb_size_header);
    }

    WORD keyboard::get_rawinput_code_wparam(WPARAM w_param) {
        return GET_RAWINPUT_CODE_WPARAM(w_param);
    }

    UINT keyboard::get_raw_input_buffer(RAWINPUT* data,
                                        UINT* cb_size,
                                        UINT cb_size_header) {
        UINT result = GetRawInputBuffer(data, cb_size, cb_size_header);
        if (result == static_cast<UINT>(-1)) {
            error_code = GetLastError();
        }
        return result;
    }

    UINT keyboard::get_raw_input_data(HRAWINPUT raw_input,
                                      UINT command,
                                      void *data,
                                      UINT* cb_size,
                                      UINT cb_size_header) {
        return GetRawInputData(raw_input,
                               command,
                               data,
                               cb_size,
                               cb_size_header);
    }

    UINT keyboard::get_raw_input_device_info(HANDLE device_handle,
                                             UINT command,
                                             void *data,
                                             UINT* cb_size) {
        UINT result = GetRawInputDeviceInfoW(device_handle,
                                             command,
                                             data,
                                             cb_size);
        error_code = GetLastError();
        return result;
    }

    UINT
    keyboard::get_raw_input_device_list(RAWINPUTDEVICELIST* raw_input_device_list,
                                        UINT* num_devices,
                                        UINT cb_size) {
        UINT result = GetRawInputDeviceList(raw_input_device_list,
                                            num_devices,
                                            cb_size);
        if (result == static_cast<UINT>(-1)) {
            error_code = GetLastError();
        }
        return result;
    }

    UINT
    keyboard::get_registered_raw_input_devices(RAWINPUTDEVICE* raw_input_devices,
                                               UINT* num_devices,
                                               UINT cb_size) {
        UINT result = GetRegisteredRawInputDevices(raw_input_devices,
                                                   num_devices,
                                                   cb_size);
        if (result == static_cast<UINT>(-1)) {
            error_code = GetLastError();
        }
        return result;
    }

    RAWINPUT* keyboard::next_raw_input_block(RAWINPUT* raw_input) {
        typedef unsigned __int64 QWORD;
        return NEXTRAWINPUTBLOCK(raw_input);
    }

    bool keyboard::register_raw_input_devices(const RAWINPUTDEVICE* raw_input_devices,
                                              UINT num_devices,
                                              UINT cb_size) {
        if (!RegisterRawInputDevices(raw_input_devices,
                                     num_devices,
                                     cb_size)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    DWORD keyboard::err_code() const {
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
