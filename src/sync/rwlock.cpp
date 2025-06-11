/* clang-format off */
/*
 * @file rwlock.cpp
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
