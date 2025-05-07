//
// Created by forkernel on 2025/4/2.
//

#ifndef SEMAPHORE_H
#define SEMAPHORE_H
#include <Windows.h>
#include <string>

namespace YanLib::sync {
#ifndef SEMAPHOREACCESS
#define SEMAPHOREACCESS

enum class SemaphoreAccess : uint32_t {
    Delete      = DELETE,
    ReadControl = READ_CONTROL,
    WriteDac    = WRITE_DAC,
    WriteOwner  = WRITE_OWNER,
    Synchronize = SYNCHRONIZE,
    All         = SEMAPHORE_ALL_ACCESS,
    Modify      = SEMAPHORE_MODIFY_STATE,
};

inline SemaphoreAccess operator|(SemaphoreAccess a, SemaphoreAccess b) {
    return static_cast<SemaphoreAccess>(
        static_cast<uint32_t>(a) | static_cast<uint32_t>(b));
}
#endif

class semaphore {
private:
    HANDLE   semaphore_handle;
    uint32_t error_code;

public:
    semaphore(const semaphore &other)            = delete;

    semaphore(semaphore &&other)                 = delete;

    semaphore &operator=(const semaphore &other) = delete;

    semaphore &operator=(semaphore &&other)      = delete;

    semaphore();

    ~semaphore();

    bool create(SECURITY_ATTRIBUTES *sa            = nullptr,
        long                         initial_count = 1,
        long                         maximum_count = 1,
        const wchar_t               *name          = nullptr);

    bool open(const wchar_t *name,
        SemaphoreAccess      access         = SemaphoreAccess::All,
        bool                 inherit_handle = false);

    bool wait(uint32_t milli_seconds = INFINITE);

    bool signal(long release_count = 1, long *previous_count = nullptr);

    [[nodiscard]] uint32_t err_code() const;

    [[nodiscard]] std::string err_string() const;

    [[nodiscard]] std::wstring err_wstring() const;
};
} // namespace YanLib::sync
#endif // SEMAPHORE_H
