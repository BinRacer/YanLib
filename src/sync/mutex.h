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
        unsigned long error_code;

    public:
        mutex(const mutex &other) = delete;

        mutex(mutex &&other) = delete;

        mutex &operator=(const mutex &other) = delete;

        mutex &operator=(mutex &&other) = delete;

        mutex();

        ~mutex();

        bool create(SECURITY_ATTRIBUTES* mutex_attrs = nullptr,
                    bool is_initial_owner = false,
                    const wchar_t *name = nullptr);

        bool open(const wchar_t *name,
                  unsigned long desired_access = MUTEX_ALL_ACCESS,
                  bool is_inherit_handle = false);

        bool lock(unsigned long milli_seconds = INFINITE);

        bool unlock();

        [[nodiscard]] unsigned long err_code() const;

        [[nodiscard]] std::string err_string() const;

        [[nodiscard]] std::wstring err_wstring() const;
    };
}
#endif //MUTEX_H
