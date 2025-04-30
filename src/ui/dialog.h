//
// Created by forkernel on 2025/4/30.
//

#ifndef DIALOG_H
#define DIALOG_H

#include <Windows.h>
#include <string>

namespace YanLib::ui {
    class dialog {
    private:
        DWORD error_code = 0;

    public:
        dialog(const dialog &other) = delete;

        dialog(dialog &&other) = delete;

        dialog &operator=(const dialog &other) = delete;

        dialog &operator=(dialog &&other) = delete;

        dialog() = default;

        ~dialog() = default;

        bool check_dialog_button(HWND hwnd_dialog,
                                 int id_button,
                                 UINT check);

        LRESULT default_dialog_proc(HWND hwnd_dialog,
                                    UINT msg,
                                    WPARAM w_param,
                                    LPARAM l_param);

        [[nodiscard]] DWORD err_code() const;

        [[nodiscard]] std::string err_string() const;

        [[nodiscard]] std::wstring err_wstring() const;
    };
}
#endif //DIALOG_H
