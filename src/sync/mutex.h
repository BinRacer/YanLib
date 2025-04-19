//
// Created by forkernel on 2025/4/2.
//

#ifndef MUTEX_H
#define MUTEX_H
#include <Windows.h>
#include <string>

namespace YanLib::sync {
    class mutex {
    private:
        HANDLE mutex_handle;
        DWORD error_code;

    public:
        mutex(const mutex &other) = delete;

        mutex(mutex &&other) = delete;

        mutex &operator=(const mutex &other) = delete;

        mutex &operator=(mutex &&other) = delete;

        mutex();

        ~mutex();

        bool create(LPSECURITY_ATTRIBUTES mutex_attrs = nullptr,
                    BOOL is_initial_owner = FALSE,
                    const wchar_t *name = nullptr);

        bool open(const wchar_t *name,
                  DWORD desired_access = MUTEX_ALL_ACCESS,
                  BOOL is_inherit_handle = FALSE);

        bool lock(DWORD milli_seconds = INFINITE);

        bool unlock();

        DWORD err_code() const;

        std::string err_string() const;

        std::wstring err_wstring() const;
    };
}
#endif //MUTEX_H
