//
// Created by forkernel on 2025/4/2.
//

#ifndef MUTEX_H
#define MUTEX_H
#include <Windows.h>
#include <string>

namespace YanLib {
    namespace sync {
        class mutex {
        public:
            mutex(const mutex &other) = delete;

            mutex(mutex &&other) = delete;

            mutex &operator=(const mutex &other) = delete;

            mutex &operator=(mutex &&other) = delete;

            mutex();

            ~mutex();

            bool create(LPSECURITY_ATTRIBUTES lpMutexAttributes = nullptr,
                        BOOL bInitialOwner = FALSE,
                        const wchar_t * lpName = nullptr);

            bool open(const wchar_t * lpName,
                      DWORD dwDesiredAccess = MUTEX_ALL_ACCESS,
                      BOOL bInheritHandle = FALSE);

            bool lock(DWORD dwMilliseconds = INFINITE);

            bool unlock();

            DWORD err_code() const;

            std::string err_string() const;

            std::wstring err_wstring() const;
        };
    }
}
#endif //MUTEX_H
