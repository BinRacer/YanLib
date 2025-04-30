//
// Created by forkernel on 2025/4/30.
//

#ifndef CLIPBOARD_H
#define CLIPBOARD_H
#include <Windows.h>
#include <string>

namespace YanLib::ui {
    class clipboard {
    private:
        DWORD error_code = 0;

    public:
        clipboard(const clipboard &other) = delete;

        clipboard(clipboard &&other) = delete;

        clipboard &operator=(const clipboard &other) = delete;

        clipboard &operator=(clipboard &&other) = delete;

        clipboard() = default;

        ~clipboard() = default;

        [[nodiscard]] DWORD err_code() const;

        [[nodiscard]] std::string err_string() const;

        [[nodiscard]] std::wstring err_wstring() const;
    };
}
#endif //CLIPBOARD_H
