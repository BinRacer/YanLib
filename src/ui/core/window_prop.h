//
// Created by BinRacer <native.lab@outlook.com> on 2025/5/18.
//

#ifndef WINDOW_PROP_H
#define WINDOW_PROP_H
#include <Windows.h>
#include <string>

namespace YanLib::ui::core {
    class window_prop {
    private:
        uint32_t error_code = 0;

    public:
        window_prop(const window_prop &other) = delete;

        window_prop(window_prop &&other) = delete;

        window_prop &operator=(const window_prop &other) = delete;

        window_prop &operator=(window_prop &&other) = delete;

        window_prop() = default;

        ~window_prop() = default;

        int32_t enum_prop(HWND window_handle, PROPENUMPROCA enum_func);

        int32_t enum_prop(HWND window_handle, PROPENUMPROCW enum_func);

        int32_t
        enum_prop(HWND window_handle, PROPENUMPROCEXA enum_func, LPARAM lparam);

        int32_t
        enum_prop(HWND window_handle, PROPENUMPROCEXW enum_func, LPARAM lparam);

        void *get_prop(HWND window_handle, const char *key);

        void *get_prop(HWND window_handle, const wchar_t *key);

        bool set_prop(HWND window_handle, const char *key, void *value);

        bool set_prop(HWND window_handle, const wchar_t *key, void *value);

        void *remove_prop(HWND window_handle, const char *key);

        void *remove_prop(HWND window_handle, const wchar_t *key);

        [[nodiscard]] uint32_t err_code() const;

        [[nodiscard]] std::string err_string() const;

        [[nodiscard]] std::wstring err_wstring() const;
    };
} // namespace YanLib::ui::core
#endif // WINDOW_PROP_H
