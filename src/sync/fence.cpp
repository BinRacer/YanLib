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

    void fence::init_with_spin(DWORD spin_count) {
        InitializeCriticalSectionAndSpinCount(&critical_section, spin_count);
    }

    DWORD fence::set_spin_count(DWORD spin_count) {
        return SetCriticalSectionSpinCount(&critical_section, spin_count);
    }

    void fence::lock() {
        EnterCriticalSection(&critical_section);
    }

    bool fence::try_lock() {
        return TryEnterCriticalSection(&critical_section);
    }

    void fence::unlock() {
        LeaveCriticalSection(&critical_section);
    }
}
