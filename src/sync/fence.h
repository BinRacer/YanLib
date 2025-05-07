//
// Created by forkernel on 2025/4/2.
//

#ifndef FENCE_H
#define FENCE_H
#include <Windows.h>
#include <cstdint>

namespace YanLib::sync {
class fence {
private:
    CRITICAL_SECTION critical_section{};

public:
    fence(const fence &other)            = delete;

    fence(fence &&other)                 = delete;

    fence &operator=(const fence &other) = delete;

    fence &operator=(fence &&other)      = delete;

    fence()                              = delete;

    ~fence();

    void init();

    void init_with_spin(uint32_t spin_count = 4000);

    uint32_t set_spin_count(uint32_t spin_count);

    void lock();

    bool try_lock();

    void unlock();
};
} // namespace YanLib::sync
#endif // FENCE_H
