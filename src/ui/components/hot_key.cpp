//
// Created by BinRacer <native.lab@outlook.com> on 2025/5/25.
//

#include "hot_key.h"
#include <windowsx.h>
#include "helper/convert.h"
namespace YanLib::ui::components {
    HWND hot_key::create(uintptr_t hot_key_id,
                         HWND parent_window_handle,
                         LPARAM lparam,
                         int32_t x,
                         int32_t y,
                         int32_t width,
                         int32_t height,
                         WindowStyle window_style) {
        INITCOMMONCONTROLSEX icc = {};
        icc.dwSize = sizeof(INITCOMMONCONTROLSEX);
        icc.dwICC = ICC_HOTKEY_CLASS;
        InitCommonControlsEx(&icc);
        HWND result = CreateWindowExW(
                0L, L"msctls_hotkey32", nullptr,
                static_cast<uint32_t>(window_style), x, y, width, height,
                parent_window_handle, reinterpret_cast<HMENU>(hot_key_id),
                reinterpret_cast<CREATESTRUCT *>(lparam)->hInstance, nullptr);
        if (!result) {
            error_code = GetLastError();
        }
        return result;
    }

    HWND hot_key::create(const char *hot_key_name,
                         uintptr_t hot_key_id,
                         HWND parent_window_handle,
                         LPARAM lparam,
                         int32_t x,
                         int32_t y,
                         int32_t width,
                         int32_t height,
                         WindowStyle window_style) {
        INITCOMMONCONTROLSEX icc = {};
        icc.dwSize = sizeof(INITCOMMONCONTROLSEX);
        icc.dwICC = ICC_HOTKEY_CLASS;
        InitCommonControlsEx(&icc);
        HWND result = CreateWindowExA(
                0L, "msctls_hotkey32", hot_key_name,
                static_cast<uint32_t>(window_style), x, y, width, height,
                parent_window_handle, reinterpret_cast<HMENU>(hot_key_id),
                reinterpret_cast<CREATESTRUCT *>(lparam)->hInstance, nullptr);
        if (!result) {
            error_code = GetLastError();
        }
        return result;
    }

    HWND hot_key::create(const wchar_t *hot_key_name,
                         uintptr_t hot_key_id,
                         HWND parent_window_handle,
                         LPARAM lparam,
                         int32_t x,
                         int32_t y,
                         int32_t width,
                         int32_t height,
                         WindowStyle window_style) {
        INITCOMMONCONTROLSEX icc = {};
        icc.dwSize = sizeof(INITCOMMONCONTROLSEX);
        icc.dwICC = ICC_HOTKEY_CLASS;
        InitCommonControlsEx(&icc);
        HWND result = CreateWindowExW(
                0L, L"msctls_hotkey32", hot_key_name,
                static_cast<uint32_t>(window_style), x, y, width, height,
                parent_window_handle, reinterpret_cast<HMENU>(hot_key_id),
                reinterpret_cast<CREATESTRUCT *>(lparam)->hInstance, nullptr);
        if (!result) {
            error_code = GetLastError();
        }
        return result;
    }

    std::pair<ModifiersKey, VirtualKey>
    hot_key::get_hotkey(HWND hot_key_handle) {
        const auto hot_key = static_cast<uint16_t>(
                SendMessageW(hot_key_handle, HKM_GETHOTKEY, 0, 0));
        return std::make_pair(static_cast<ModifiersKey>(LOBYTE(hot_key)),
                              static_cast<VirtualKey>(HIBYTE(hot_key)));
    }

    void
    hot_key::set_hotkey(HWND hot_key_handle, ModifiersKey mod, VirtualKey vk) {
        const uint16_t hot_key =
                static_cast<uint8_t>(mod) | (static_cast<uint8_t>(vk) << 8);
        SendMessageW(hot_key_handle, HKM_SETHOTKEY, hot_key, 0);
    }

    void hot_key::set_rules(
            HWND hot_key_handle,
            RuleFlag rule,
            std::vector<std::pair<ModifiersKey, VirtualKey>> &hot_key) {
        std::vector<uint32_t> temp = {};
        temp.reserve(hot_key.size());
        for (const auto &[mod, vk] : hot_key) {
            temp.emplace_back(static_cast<uint8_t>(mod) |
                              (static_cast<uint8_t>(vk) << 8));
        }
        SendMessageW(hot_key_handle, HKM_SETRULES, static_cast<uint32_t>(rule),
                     reinterpret_cast<LPARAM>(temp.data()));
    }

    uint32_t hot_key::err_code() const {
        return error_code;
    }

    std::string hot_key::err_string() const {
        std::string result = helper::convert::err_string(error_code);
        return result;
    }

    std::wstring hot_key::err_wstring() const {
        std::wstring result = helper::convert::err_wstring(error_code);
        return result;
    }
} // namespace YanLib::ui::components
