//
// Created by forkernel on 2025/4/2.
//

#ifndef MUTEX_H
#define MUTEX_H
#include <Windows.h>
#include <string>

namespace YanLib::sync {
#ifndef MUTEXACCESS
#define MUTEXACCESS

enum class MutexAccess : uint32_t {
    Delete      = DELETE,
    ReadControl = READ_CONTROL,
    WriteDac    = WRITE_DAC,
    WriteOwner  = WRITE_OWNER,
    Synchronize = SYNCHRONIZE,
    All         = MUTEX_ALL_ACCESS,
    Modify      = MUTEX_MODIFY_STATE,
};

inline MutexAccess operator|(MutexAccess a, MutexAccess b) {
    return static_cast<MutexAccess>(
        static_cast<uint32_t>(a) | static_cast<uint32_t>(b));
}
#endif
class mutex {
private:
    HANDLE   mutex_handle;
    uint32_t error_code;

public:
    mutex(const mutex &other)            = delete;

    mutex(mutex &&other)                 = delete;

    mutex &operator=(const mutex &other) = delete;

    mutex &operator=(mutex &&other)      = delete;

    mutex();

    ~mutex();

    bool create(SECURITY_ATTRIBUTES *sa               = nullptr,
        bool                         is_initial_owner = false,
        const wchar_t               *name             = nullptr);

    bool open(const wchar_t *name,
        MutexAccess          access     = MutexAccess::All,
        bool                 is_inherit = false);

    bool lock(uint32_t milli_seconds = INFINITE);

    bool unlock();

    [[nodiscard]] uint32_t err_code() const;

    [[nodiscard]] std::string err_string() const;

    [[nodiscard]] std::wstring err_wstring() const;
};
} // namespace YanLib::sync
#endif // MUTEX_H
