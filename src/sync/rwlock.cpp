//
// Created by forkernel on 2025/4/2.
//

#include "rwlock.h"

namespace YanLib {
    namespace sync {
        rwlock::rwlock() {
            InitializeSRWLock(&rw_lock);
        }

        rwlock::~rwlock() {
        }

        void rwlock::read_lock() {
            AcquireSRWLockShared(&rw_lock);
        }

        BOOLEAN rwlock::try_read_lock() {
            return TryAcquireSRWLockShared(&rw_lock);
        }

        void rwlock::read_unlock() {
            ReleaseSRWLockShared(&rw_lock);
        }

        void rwlock::write_lock() {
            AcquireSRWLockExclusive(&rw_lock);
        }

        BOOLEAN rwlock::try_write_lock() {
            return TryAcquireSRWLockExclusive(&rw_lock);
        }

        void rwlock::write_unlock() {
            ReleaseSRWLockExclusive(&rw_lock);
        }
    }
}
