//
// Created by forkernel on 2025/4/18.
//

#ifndef THREAD_H
#define THREAD_H
#include <Windows.h>
#include <string>

namespace YanLib::sys {
    class thread {
    private:
        DWORD error_code = 0;

    public:
        thread(const thread &other) = delete;

        thread(thread &&other) = delete;

        thread &operator=(const thread &other) = delete;

        thread &operator=(thread &&other) = delete;

        thread() = default;

        ~thread() = default;

        [[nodiscard]] DWORD err_code() const;

        [[nodiscard]] std::string err_string() const;

        [[nodiscard]] std::wstring err_wstring() const;
    };
}
#endif //THREAD_H
