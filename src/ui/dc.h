//
// Created by forkernel on 2025/5/2.
//

#ifndef DC_H
#define DC_H
#include <Windows.h>
#include <string>

namespace YanLib::ui {
    class dc {
    private:
        DWORD error_code = 0;

    public:
        dc(const dc &other) = delete;

        dc(dc &&other) = delete;

        dc &operator=(const dc &other) = delete;

        dc &operator=(dc &&other) = delete;

        dc() = default;

        ~dc() = default;

        [[nodiscard]] DWORD err_code() const;

        [[nodiscard]] std::string err_string() const;

        [[nodiscard]] std::wstring err_wstring() const;
    };
}
#endif //DC_H
