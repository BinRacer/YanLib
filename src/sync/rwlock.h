//
// Created by forkernel on 2025/4/2.
//

#ifndef RWLOCK_H
#define RWLOCK_H
#include <Windows.h>

namespace YanLib::sync {
class rwlock {
private:
    SRWLOCK rw_lock{};

public:
    rwlock(const rwlock &other)            = delete;

    rwlock(rwlock &&other)                 = delete;

    rwlock &operator=(const rwlock &other) = delete;

    rwlock &operator=(rwlock &&other)      = delete;

    rwlock();

    ~rwlock() = default;

    void read_lock();

    bool try_read_lock();

    void read_unlock();

    void write_lock();

    bool try_write_lock();

    void write_unlock();
};
} // namespace YanLib::sync
#endif // RWLOCK_H
