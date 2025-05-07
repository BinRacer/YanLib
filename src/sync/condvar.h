//
// Created by forkernel on 2025/4/2.
//

#ifndef CONDVAR_H
#define CONDVAR_H
#include <Windows.h>
#include <cstdint>

namespace YanLib::sync {
class condVarCS {
private:
    CONDITION_VARIABLE condition_variable{};
    CRITICAL_SECTION   critical_section{};

public:
    condVarCS(const condVarCS &other)            = delete;

    condVarCS(condVarCS &&other)                 = delete;

    condVarCS &operator=(const condVarCS &other) = delete;

    condVarCS &operator=(condVarCS &&other)      = delete;

    condVarCS();

    ~condVarCS();

    void lock();

    bool try_lock();

    void unlock();

    bool sleep(uint32_t milli_seconds = INFINITE);

    void wake();

    void wake_all();
};
} // namespace YanLib::sync

namespace sync {
#ifndef CONDVARLOCKMODE
#define CONDVARLOCKMODE

enum class CondVarLockMode : uint32_t {
    Exclusive = 0,
    Shared    = CONDITION_VARIABLE_LOCKMODE_SHARED,
};
#endif

class condVarSRW {
private:
    CONDITION_VARIABLE condition_variable{};
    SRWLOCK            rw_lock{};

public:
    condVarSRW(const condVarSRW &other)                = delete;

    condVarSRW(condVarSRW &&other) noexcept            = delete;

    condVarSRW &operator=(const condVarSRW &other)     = delete;

    condVarSRW &operator=(condVarSRW &&other) noexcept = delete;

    condVarSRW();

    ~condVarSRW() = default;

    void read_lock();

    bool try_read_lock();

    void read_unlock();

    void write_lock();

    bool try_write_lock();

    void write_unlock();

    bool sleep(uint32_t milli_seconds = INFINITE,
        CondVarLockMode lock_mode     = CondVarLockMode::Shared);

    void wake();

    void wake_all();
};
} // namespace sync
#endif // CONDVAR_H
