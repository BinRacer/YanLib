//
// Created by forkernel on 2025/4/2.
//

#include "condvar.h"
#include "helper/convert.h"

namespace YanLib::sync {
    condVarCS::condVarCS() {
        InitializeConditionVariable(&condition_variable);
        InitializeCriticalSection(&critical_section);
    }

    condVarCS::~condVarCS() {
        DeleteCriticalSection(&critical_section);
    }

    void condVarCS::lock() {
        EnterCriticalSection(&critical_section);
    }

    BOOL condVarCS::try_lock() {
        return TryEnterCriticalSection(&critical_section);
    }

    void condVarCS::unlock() {
        LeaveCriticalSection(&critical_section);
    }

    bool condVarCS::sleep(DWORD milli_seconds) {
        return SleepConditionVariableCS(&condition_variable,
                                        &critical_section,
                                        milli_seconds);
    }

    void condVarCS::wake() {
        WakeConditionVariable(&condition_variable);
    }

    void condVarCS::wake_all() {
        WakeAllConditionVariable(&condition_variable);
    }
}

namespace sync {
    condVarSRW::condVarSRW() {
        InitializeConditionVariable(&condition_variable);
        InitializeSRWLock(&rw_lock);
    }

    condVarSRW::~condVarSRW() {
    }

    void condVarSRW::read_lock() {
        AcquireSRWLockShared(&rw_lock);
    }

    BOOLEAN condVarSRW::try_read_lock() {
        return TryAcquireSRWLockShared(&rw_lock);
    }

    void condVarSRW::read_unlock() {
        ReleaseSRWLockShared(&rw_lock);
    }

    void condVarSRW::write_lock() {
        AcquireSRWLockExclusive(&rw_lock);
    }

    BOOLEAN condVarSRW::try_write_lock() {
        return TryAcquireSRWLockExclusive(&rw_lock);
    }

    void condVarSRW::write_unlock() {
        ReleaseSRWLockExclusive(&rw_lock);
    }

    bool condVarSRW::sleep(DWORD milli_seconds, ULONG flag) {
        return SleepConditionVariableSRW(&condition_variable,
                                         &rw_lock,
                                         milli_seconds,
                                         flag);
    }

    void condVarSRW::wake() {
        WakeConditionVariable(&condition_variable);
    }

    void condVarSRW::wake_all() {
        WakeAllConditionVariable(&condition_variable);
    }
}
