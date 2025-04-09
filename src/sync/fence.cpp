//
// Created by forkernel on 2025/4/2.
//

#include "fence.h"

namespace YanLib::sync {
    fence::~fence() {
        DeleteCriticalSection(&critical_section);
    }

    void fence::init() {
        InitializeCriticalSection(&critical_section);
    }

    void fence::init_with_spin(DWORD dwSpinCount) {
        InitializeCriticalSectionAndSpinCount(&critical_section, dwSpinCount);
    }

    DWORD fence::set_spin_count(DWORD dwSpinCount) {
        return SetCriticalSectionSpinCount(&critical_section, dwSpinCount);
    }

    void fence::lock() {
        EnterCriticalSection(&critical_section);
    }

    BOOL fence::try_lock() {
        return TryEnterCriticalSection(&critical_section);
    }

    void fence::unlock() {
        LeaveCriticalSection(&critical_section);
    }
}
