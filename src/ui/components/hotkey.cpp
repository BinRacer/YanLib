//
// Created by forkernel on 2025/5/25.
//

#include "hotkey.h"
#include <windowsx.h>

namespace YanLib::components {
    HWND hotkey::create(uintptr_t hotkey_id,
                        HWND parent_window_handle,
                        LPARAM lparam,
                        int32_t x,
                        int32_t y,
                        int32_t width,
                        int32_t height,
                        WindowStyle window_style) {
        INITCOMMONCONTROLSEX icex = {};
        icex.dwSize = sizeof(INITCOMMONCONTROLSEX);
        icex.dwICC = ICC_HOTKEY_CLASS;
        InitCommonControlsEx(&icex);
        HWND result = CreateWindowExW(
                0L, L"msctls_hotkey32", nullptr,
                static_cast<uint32_t>(window_style), x, y, width, height,
                parent_window_handle, reinterpret_cast<HMENU>(hotkey_id),
                reinterpret_cast<CREATESTRUCT *>(lparam)->hInstance, nullptr);
        if (!result) {
            error_code = GetLastError();
        }
        return result;
    }

    std::pair<ModKey, VirtualKey> hotkey::get_hotkey(HWND hotkey_handle) {
        uint16_t hotkey = static_cast<uint16_t>(
                SendMessageW(hotkey_handle, HKM_GETHOTKEY, 0, 0));
        return std::make_pair(static_cast<ModKey>(LOBYTE(hotkey)),
                              static_cast<VirtualKey>(HIBYTE(hotkey)));
    }

    void hotkey::set_hotkey(HWND hotkey_handle, ModKey mod, VirtualKey vk) {
        uint16_t hotkey =
                static_cast<uint8_t>(mod) | (static_cast<uint8_t>(vk) << 8);
        SendMessageW(hotkey_handle, HKM_SETHOTKEY, hotkey, 0);
    }

    void hotkey::set_rules(HWND hotkey_handle,
                           RuleFlag rule,
                           std::vector<std::pair<ModKey, VirtualKey>> &hotkey) {
        std::vector<uint32_t> temp = {};
        temp.reserve(hotkey.size());
        for (const auto &[mod, vk] : hotkey) {
            temp.emplace_back(static_cast<uint8_t>(mod) |
                              (static_cast<uint8_t>(vk) << 8));
        }
        SendMessageW(hotkey_handle, HKM_SETRULES, static_cast<uint32_t>(rule),
                     reinterpret_cast<LPARAM>(temp.data()));
    }

    uint32_t hotkey::err_code() const {
        return error_code;
    }

    std::string hotkey::err_string() const {
        std::string result = helper::convert::err_string(error_code);
        return result;
    }

    std::wstring hotkey::err_wstring() const {
        std::wstring result = helper::convert::err_wstring(error_code);
        return result;
    }
} // namespace YanLib::components
