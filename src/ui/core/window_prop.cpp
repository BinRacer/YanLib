//
// Created by BinRacer <native.lab@outlook.com> on 2025/5/18.
//

#include "window_prop.h"
#include "helper/convert.h"
namespace YanLib::ui::core {
    int32_t window_prop::enum_prop(HWND window_handle,
                                   PROPENUMPROCA enum_func) {
        return EnumPropsA(window_handle, enum_func);
    }

    int32_t window_prop::enum_prop(HWND window_handle,
                                   PROPENUMPROCW enum_func) {
        return EnumPropsW(window_handle, enum_func);
    }

    int32_t window_prop::enum_prop(HWND window_handle,
                                   PROPENUMPROCEXA enum_func,
                                   LPARAM lparam) {
        return EnumPropsExA(window_handle, enum_func, lparam);
    }

    int32_t window_prop::enum_prop(HWND window_handle,
                                   PROPENUMPROCEXW enum_func,
                                   LPARAM lparam) {
        return EnumPropsExW(window_handle, enum_func, lparam);
    }

    void *window_prop::get_prop(HWND window_handle, const char *key) {
        return GetPropA(window_handle, key);
    }

    void *window_prop::get_prop(HWND window_handle, const wchar_t *key) {
        return GetPropW(window_handle, key);
    }

    bool
    window_prop::set_prop(HWND window_handle, const char *key, void *value) {
        if (!SetPropA(window_handle, key, value)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool
    window_prop::set_prop(HWND window_handle, const wchar_t *key, void *value) {
        if (!SetPropW(window_handle, key, value)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    void *window_prop::remove_prop(HWND window_handle, const char *key) {
        return RemovePropA(window_handle, key);
    }

    void *window_prop::remove_prop(HWND window_handle, const wchar_t *key) {
        return RemovePropW(window_handle, key);
    }
    uint32_t window_prop::err_code() const {
        return error_code;
    }

    std::string window_prop::err_string() const {
        std::string result = helper::convert::err_string(error_code);
        return result;
    }

    std::wstring window_prop::err_wstring() const {
        std::wstring result = helper::convert::err_wstring(error_code);
        return result;
    }
} // namespace YanLib::ui::core
