/* clang-format off */
/*
 * @file condvar.cpp
 * @date 2025-04-02
 * @license MIT License
 *
 * Copyright (c) 2025 BinRacer <native.lab@outlook.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
/* clang-format on */
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

    bool condVarCS::try_lock() {
        return TryEnterCriticalSection(&critical_section);
    }

    void condVarCS::unlock() {
        LeaveCriticalSection(&critical_section);
    }

    bool condVarCS::sleep(const uint32_t milli_seconds) {
        return SleepConditionVariableCS(&condition_variable, &critical_section,
                                        milli_seconds);
    }

    void condVarCS::wake() {
        WakeConditionVariable(&condition_variable);
    }

    void condVarCS::wake_all() {
        WakeAllConditionVariable(&condition_variable);
    }
} // namespace YanLib::sync

namespace sync {
    condVarSRW::condVarSRW() {
        InitializeConditionVariable(&condition_variable);
        InitializeSRWLock(&rw_lock);
    }

    void condVarSRW::read_lock() {
        AcquireSRWLockShared(&rw_lock);
    }

    bool condVarSRW::try_read_lock() {
        return TryAcquireSRWLockShared(&rw_lock);
    }

    void condVarSRW::read_unlock() {
        ReleaseSRWLockShared(&rw_lock);
    }

    void condVarSRW::write_lock() {
        AcquireSRWLockExclusive(&rw_lock);
    }

    bool condVarSRW::try_write_lock() {
        return TryAcquireSRWLockExclusive(&rw_lock);
    }

    void condVarSRW::write_unlock() {
        ReleaseSRWLockExclusive(&rw_lock);
    }

    bool condVarSRW::sleep(const uint32_t milli_seconds,
                           CondVarLockMode lock_mode) {
        return SleepConditionVariableSRW(&condition_variable, &rw_lock,
                                         milli_seconds,
                                         static_cast<uint32_t>(lock_mode));
    }

    void condVarSRW::wake() {
        WakeConditionVariable(&condition_variable);
    }

    void condVarSRW::wake_all() {
        WakeAllConditionVariable(&condition_variable);
    }
} // namespace sync
