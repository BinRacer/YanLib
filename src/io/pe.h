//
// Created by forkernel on 2025/4/24.
//

#ifndef PE_H
#define PE_H
#include <Windows.h>
#include <string>

namespace YanLib::io {
    class pe {
    private:
        PIMAGE_DOS_HEADER dos_header = nullptr;
        PIMAGE_NT_HEADERS32 nt_headers32 = nullptr;
        PIMAGE_NT_HEADERS64 nt_headers64 = nullptr;
        DWORD error_code = 0;
        bool is_32bit = false;

        pe() = default;

    public:
        pe(const pe &other) = delete;

        pe(pe &&other) = delete;

        pe &operator=(const pe &other) = delete;

        pe &operator=(pe &&other) = delete;

        ~pe() = default;

        [[nodiscard]] DWORD err_code() const;

        [[nodiscard]] std::string err_string() const;

        [[nodiscard]] std::wstring err_wstring() const;
    };
}
#endif //PE_H
