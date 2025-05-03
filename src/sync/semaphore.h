//
// Created by forkernel on 2025/4/2.
//

#ifndef SEMAPHORE_H
#define SEMAPHORE_H
#include <Windows.h>
#include <string>

namespace YanLib::sync {
    class semaphore {
    private:
        HANDLE semaphore_handle;
        DWORD error_code;

    public:
        semaphore(const semaphore &other) = delete;

        semaphore(semaphore &&other) = delete;

        semaphore &operator=(const semaphore &other) = delete;

        semaphore &operator=(semaphore &&other) = delete;

        semaphore();

        ~semaphore();

        bool create(SECURITY_ATTRIBUTES* semaphore_attrs = nullptr,
                    LONG initial_count = 1,
                    LONG maximum_count = 1,
                    const wchar_t *name = nullptr);

        bool open(const wchar_t *name,
                  DWORD desired_access = SEMAPHORE_ALL_ACCESS,
                  bool inherit_handle = false);

        bool wait(DWORD milli_seconds = INFINITE);

        bool signal(LONG release_count = 1, LONG* previous_count = nullptr);

        [[nodiscard]] DWORD err_code() const;

        [[nodiscard]] std::string err_string() const;

        [[nodiscard]] std::wstring err_wstring() const;
    };
}
#endif //SEMAPHORE_H
