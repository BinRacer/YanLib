//
// Created by forkernel on 2025/5/1.
//

#include "keyboard.h"
#include "helper/convert.h"

namespace YanLib::ui {
    HKL keyboard::load_layout(KeyboardID id, KeyboardLayout layout) {
        HKL result = LoadKeyboardLayoutW(KbdIDToWString(id).data(),
                                         static_cast<uint32_t>(layout));
        if (!result) {
            error_code = GetLastError();
        }
        return result;
    }

    bool keyboard::register_hot_key(HWND window_handle,
                                    int32_t id,
                                    ModKey mod_key,
                                    VirtualKey vk) {
        if (!RegisterHotKey(window_handle, id, static_cast<uint32_t>(mod_key),
                            static_cast<uint32_t>(vk))) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool keyboard::unregister_hot_key(HWND window_handle, int32_t id) {
        if (!UnregisterHotKey(window_handle, id)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    HKL keyboard::activate_layout(HKL layout_handle, KeyboardLayout layout) {
        HKL result = ActivateKeyboardLayout(layout_handle,
                                            static_cast<uint32_t>(layout));
        if (!result) {
            error_code = GetLastError();
        }
        return result;
    }

    bool keyboard::unload_layout(HKL layout_handle) {
        if (!UnloadKeyboardLayout(layout_handle)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    HKL keyboard::get_layout(uint32_t tid) {
        return GetKeyboardLayout(tid);
    }

    int32_t keyboard::get_layout_list(std::vector<HKL> &layout_handle) {
        int32_t result = GetKeyboardLayoutList(static_cast<int32_t>(
                                                       layout_handle.size()),
                                               layout_handle.data());
        if (!result) {
            error_code = GetLastError();
        }
        return result;
    }

    bool keyboard::get_layout_name(char *name) {
        if (!GetKeyboardLayoutNameA(name)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool keyboard::get_layout_name(wchar_t *name) {
        if (!GetKeyboardLayoutNameW(name)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool keyboard::get_state(uint8_t *key_state) {
        if (!GetKeyboardState(key_state)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool keyboard::set_state(uint8_t *key_state) {
        if (!SetKeyboardState(key_state)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    int32_t keyboard::get_type(int32_t type_flag) {
        int32_t result = GetKeyboardType(type_flag);
        if (type_flag != 1 && !result) {
            error_code = GetLastError();
        }
        return result;
    }

    int32_t keyboard::get_key_name(int32_t param, std::string &text) {
        int32_t result = GetKeyNameTextA(param, text.data(),
                                         static_cast<int32_t>(text.size()));
        if (!result) {
            error_code = GetLastError();
        }
        return result;
    }

    int32_t keyboard::get_key_name(int32_t param, std::wstring &text) {
        int32_t result = GetKeyNameTextW(param, text.data(),
                                         static_cast<int32_t>(text.size()));
        if (!result) {
            error_code = GetLastError();
        }
        return result;
    }

    int16_t keyboard::get_key_state(VirtualKey vk) {
        return GetKeyState(static_cast<int32_t>(vk));
    }

    uint16_t keyboard::get_key_state_lparam(LPARAM lparam) {
        return GET_KEYSTATE_LPARAM(lparam);
    }

    uint16_t keyboard::get_key_state_wparam(WPARAM wparam) {
        return GET_KEYSTATE_WPARAM(wparam);
    }

    int16_t keyboard::get_async_key_state(VirtualKey vk) {
        return GetAsyncKeyState(static_cast<int32_t>(vk));
    }

    void keyboard::send_event(VirtualKey vk,
                              uint8_t scan,
                              KeyEvent kv,
                              uintptr_t extra_info) {
        keybd_event(static_cast<uint8_t>(vk), scan, static_cast<uint32_t>(kv),
                    extra_info);
    }

    uint32_t keyboard::send_input(std::vector<INPUT> &input) {
        uint32_t result = SendInput(input.size(), input.data(), sizeof(INPUT));
        if (!result) {
            error_code = GetLastError();
        }
        return result;
    }

    uint8_t keyboard::virtual_key_to_scan_code(VirtualKey vk,
                                               bool is_extended_key) {
        UINT scanCode =
                MapVirtualKeyW(static_cast<uint32_t>(vk), MAPVK_VK_TO_VSC);
        if (is_extended_key) {
            scanCode |= 0xE000;
        }
        return static_cast<uint8_t>(scanCode & 0xFF);
    }

    VirtualKey keyboard::scan_code_to_virtual_key(uint8_t scan_code,
                                                  bool is_extended_key) {
        UINT full_scan_code = scan_code | (is_extended_key ? 0xE000 : 0x0000);
        UINT vk = MapVirtualKeyW(full_scan_code, MAPVK_VSC_TO_VK_EX);
        return static_cast<VirtualKey>(vk);
    }

    uint32_t keyboard::map_virtual_key(uint32_t code, MapType map_type) {
        return MapVirtualKeyW(code, static_cast<uint32_t>(map_type));
    }

    uint32_t keyboard::map_virtual_key(uint32_t code,
                                       MapType map_type,
                                       HKL layout_handle) {
        return MapVirtualKeyExW(code, static_cast<uint32_t>(map_type),
                                layout_handle);
    }

    uint32_t keyboard::oem_key_scan(uint16_t oem_char) {
        return OemKeyScan(oem_char);
    }

    bool keyboard::vk_key_scan(char ch, ModKey6 *mod_key, VirtualKey *vk) {
        if (!mod_key || !vk) {
            return false;
        }
        int16_t result = VkKeyScanA(ch);
        if (result == -1) {
            return false;
        }
        *vk = static_cast<VirtualKey>(LOBYTE(result));
        *mod_key = static_cast<ModKey6>(HIBYTE(result));
        return true;
    }

    bool keyboard::vk_key_scan(wchar_t ch, ModKey6 *mod_key, VirtualKey *vk) {
        if (!mod_key || !vk) {
            return false;
        }
        int16_t result = VkKeyScanW(ch);
        if (result == -1) {
            return false;
        }
        *vk = static_cast<VirtualKey>(LOBYTE(result));
        *mod_key = static_cast<ModKey6>(HIBYTE(result));
        return true;
    }

    bool keyboard::vk_key_scan(char ch,
                               HKL layout_handle,
                               ModKey6 *mod_key,
                               VirtualKey *vk) {
        if (!mod_key || !vk) {
            return false;
        }
        int16_t result = VkKeyScanExA(ch, layout_handle);
        if (result == -1) {
            return false;
        }
        *vk = static_cast<VirtualKey>(LOBYTE(result));
        *mod_key = static_cast<ModKey6>(HIBYTE(result));
        return true;
    }

    bool keyboard::vk_key_scan(wchar_t ch,
                               HKL layout_handle,
                               ModKey6 *mod_key,
                               VirtualKey *vk) {
        if (!mod_key || !vk) {
            return false;
        }
        int16_t result = VkKeyScanExW(ch, layout_handle);
        if (result == -1) {
            return false;
        }
        *vk = static_cast<VirtualKey>(LOBYTE(result));
        *mod_key = static_cast<ModKey6>(HIBYTE(result));
        return true;
    }

    HWND keyboard::get_focus() {
        return GetFocus();
    }

    HWND keyboard::set_focus(HWND window_handle) {
        HWND result = SetFocus(window_handle);
        if (!result) {
            error_code = GetLastError();
        }
        return result;
    }

    int32_t keyboard::to_ascii(VirtualKey vk,
                               uint32_t scan_code,
                               const uint8_t *key_state,
                               uint8_t *ch1,
                               uint8_t *ch2,
                               bool menu_active) {
        if (!ch1 || !ch2) {
            return 0;
        }
        uint16_t ch = 0;
        int32_t result = ToAscii(static_cast<uint32_t>(vk), scan_code,
                                 key_state, &ch, menu_active ? 1 : 0);
        if (result == 1) {
            *ch1 = static_cast<uint8_t>(ch & 0xFF);
        }
        else if (result == 2) {
            *ch1 = static_cast<uint8_t>(ch & 0xFF);
            *ch2 = static_cast<uint8_t>((ch >> 8) & 0xFF);
        }
        return result;
    }

    int32_t keyboard::to_ascii(VirtualKey vk,
                               HKL layout_handle,
                               uint32_t scan_code,
                               const uint8_t *key_state,
                               uint8_t *ch1,
                               uint8_t *ch2,
                               bool menu_active) {
        if (!ch1 || !ch2) {
            return 0;
        }
        uint16_t ch = 0;
        int32_t result =
                ToAsciiEx(static_cast<uint32_t>(vk), scan_code, key_state, &ch,
                          menu_active ? 1 : 0, layout_handle);
        if (result == 1) {
            *ch1 = static_cast<uint8_t>(ch & 0xFF);
        }
        else if (result == 2) {
            *ch1 = static_cast<uint8_t>(ch & 0xFF);
            *ch2 = static_cast<uint8_t>((ch >> 8) & 0xFF);
        }
        return result;
    }

    int32_t keyboard::to_unicode(VirtualKey vk,
                                 uint32_t scan_code,
                                 const uint8_t *key_state,
                                 std::wstring &buf,
                                 bool menu_active) {
        return ToUnicode(static_cast<uint32_t>(vk), scan_code, key_state,
                         buf.data(), static_cast<int32_t>(buf.size()),
                         2 | (menu_active ? 1 : 0));
    }

    int32_t keyboard::to_unicode(VirtualKey vk,
                                 HKL layout_handle,
                                 uint32_t scan_code,
                                 const uint8_t *key_state,
                                 std::wstring &buf,
                                 bool menu_active) {
        return ToUnicodeEx(static_cast<uint32_t>(vk), scan_code, key_state,
                           buf.data(), static_cast<int32_t>(buf.size()),
                           2 | (menu_active ? 1 : 0), layout_handle);
    }

    bool keyboard::is_any_input() {
        return GetInputState();
    }

    bool keyboard::block_input() {
        if (!BlockInput(TRUE)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool keyboard::resume_input() {
        if (!BlockInput(FALSE)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool keyboard::attach_input(uint32_t tid1, uint32_t tid2) {
        if (tid1 == tid2) {
            return false;
        }
        if (!AttachThreadInput(tid1, tid2, TRUE)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool keyboard::detach_input(uint32_t tid1, uint32_t tid2) {
        if (tid1 == tid2) {
            return false;
        }
        if (!AttachThreadInput(tid1, tid2, FALSE)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    uint32_t keyboard::wait_for_input_idle(HANDLE proc_handle,
                                           uint32_t milli_seconds) {
        return WaitForInputIdle(proc_handle, milli_seconds);
    }

    LRESULT keyboard::default_raw_input_proc(RAWINPUT **raw_input,
                                             int32_t input,
                                             uint32_t header_size) {
        return DefRawInputProc(raw_input, input, header_size);
    }

    uint16_t keyboard::get_raw_input_code_wparam(WPARAM wparam) {
        return GET_RAWINPUT_CODE_WPARAM(wparam);
    }

    uint32_t keyboard::get_raw_input_buffer(RAWINPUT *buf,
                                            uint32_t *size,
                                            uint32_t header_size) {
        uint32_t result = GetRawInputBuffer(buf, size, header_size);
        if (result == static_cast<uint32_t>(-1)) {
            error_code = GetLastError();
        }
        return result;
    }

    uint32_t keyboard::get_raw_input_data(HRAWINPUT raw_input,
                                          uint32_t command,
                                          void *buf,
                                          uint32_t *size,
                                          uint32_t header_size) {
        return GetRawInputData(raw_input, command, buf, size, header_size);
    }

    uint32_t keyboard::get_raw_input_device_info(HANDLE device_handle,
                                                 uint32_t command,
                                                 void *buf,
                                                 uint32_t *size) {
        uint32_t result =
                GetRawInputDeviceInfoW(device_handle, command, buf, size);
        error_code = GetLastError();
        return result;
    }

    uint32_t keyboard::get_raw_input_device_list(
            RAWINPUTDEVICELIST raw_input_device_list[],
            uint32_t *real_num) {
        uint32_t result = GetRawInputDeviceList(raw_input_device_list, real_num,
                                                sizeof(RAWINPUTDEVICELIST));
        if (result == static_cast<uint32_t>(-1)) {
            error_code = GetLastError();
        }
        return result;
    }

    uint32_t keyboard::get_registered_raw_input_devices(
            RAWINPUTDEVICE raw_input_devices[],
            uint32_t *real_num) {
        uint32_t result =
                GetRegisteredRawInputDevices(raw_input_devices, real_num,
                                             sizeof(RAWINPUTDEVICE));
        if (result == static_cast<uint32_t>(-1)) {
            error_code = GetLastError();
        }
        return result;
    }

    RAWINPUT *keyboard::next_raw_input_block(RAWINPUT *raw_input) {
        typedef unsigned __int64 QWORD;
        return NEXTRAWINPUTBLOCK(raw_input);
    }

    bool keyboard::register_raw_input_devices(
            const RAWINPUTDEVICE raw_input_devices[],
            uint32_t num) {
        if (!RegisterRawInputDevices(raw_input_devices, num,
                                     sizeof(RAWINPUTDEVICE))) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    uint32_t keyboard::err_code() const {
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
} // namespace YanLib::ui
