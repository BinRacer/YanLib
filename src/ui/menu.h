//
// Created by forkernel on 2025/4/30.
//

#ifndef MENU_H
#define MENU_H
#include <Windows.h>
#include <string>

namespace YanLib::ui {
    class menu {
    private:
        DWORD error_code = 0;

    public:
        menu(const menu &other) = delete;

        menu(menu &&other) = delete;

        menu &operator=(const menu &other) = delete;

        menu &operator=(menu &&other) = delete;

        menu() = default;

        ~menu() = default;

        bool append_menu(HMENU menu_handle,
                         UINT flag,
                         UINT_PTR id_new_item,
                         const wchar_t *new_item);

        [[nodiscard]] DWORD err_code() const;

        [[nodiscard]] std::string err_string() const;

        [[nodiscard]] std::wstring err_wstring() const;
    };
}
#endif //MENU_H
