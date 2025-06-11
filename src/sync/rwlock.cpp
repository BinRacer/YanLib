//
// Created by BinRacer <native.lab@outlook.com> on 2025/4/2.
//

#include "rwlock.h"

namespace YanLib::sync {
    rwlock::rwlock() {
        InitializeSRWLock(&rw_lock);
    }

    void rwlock::read_lock() {
        AcquireSRWLockShared(&rw_lock);
    }

    bool rwlock::try_read_lock() {
        return TryAcquireSRWLockShared(&rw_lock);
    }

    void rwlock::read_unlock() {
        ReleaseSRWLockShared(&rw_lock);
    }

    void rwlock::write_lock() {
        AcquireSRWLockExclusive(&rw_lock);
    }

    bool rwlock::try_write_lock() {
        return TryAcquireSRWLockExclusive(&rw_lock);
    }

    void rwlock::write_unlock() {
        ReleaseSRWLockExclusive(&rw_lock);
    }
} // namespace YanLib::sync
