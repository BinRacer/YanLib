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

        bool create(LPSECURITY_ATTRIBUTES lpSemaphoreAttributes = nullptr,
                    LONG lInitialCount = 1,
                    LONG lMaximumCount = 1,
                    const wchar_t *lpName = nullptr);

        bool open(const wchar_t *lpName,
                  DWORD dwDesiredAccess = SEMAPHORE_ALL_ACCESS,
                  BOOL bInheritHandle = FALSE);

        bool wait(DWORD dwMilliseconds = INFINITE);

        bool signal(LONG lReleaseCount = 1, LPLONG lpPreviousCount = nullptr);

        DWORD err_code() const;

        std::string err_string() const;

        std::wstring err_wstring() const;
    };
}
#endif //SEMAPHORE_H
