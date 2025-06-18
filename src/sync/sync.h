/* clang-format off */
/*
 * @file sync.h
 * @date 2025-06-17
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
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
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
#ifndef SYNC_H
#define SYNC_H
#include <synchapi.h>
#include <winnt.h>
#include <cstdint>
namespace YanLib::sync {
    enum class BarrierFlag : uint32_t {
        SpinOnly = SYNCHRONIZATION_BARRIER_FLAGS_SPIN_ONLY,
        BlockOnly = SYNCHRONIZATION_BARRIER_FLAGS_BLOCK_ONLY,
        NoDelete = SYNCHRONIZATION_BARRIER_FLAGS_NO_DELETE,
    };

    inline BarrierFlag operator|(BarrierFlag a, BarrierFlag b) {
        return static_cast<BarrierFlag>(static_cast<uint32_t>(a) |
                                        static_cast<uint32_t>(b));
    }

    enum class CondVarLockMode : uint32_t {
        Exclusive = 0,
        Shared = CONDITION_VARIABLE_LOCKMODE_SHARED,
    };

    enum class EventAccess : uint32_t {
        Delete = DELETE,
        ReadControl = READ_CONTROL,
        WriteDac = WRITE_DAC,
        WriteOwner = WRITE_OWNER,
        Synchronize = SYNCHRONIZE,
        All = EVENT_ALL_ACCESS,
        Modify = EVENT_MODIFY_STATE,
    };

    inline EventAccess operator|(EventAccess a, EventAccess b) {
        return static_cast<EventAccess>(static_cast<uint32_t>(a) |
                                        static_cast<uint32_t>(b));
    }

    enum class MutexAccess : uint32_t {
        Delete = DELETE,
        ReadControl = READ_CONTROL,
        WriteDac = WRITE_DAC,
        WriteOwner = WRITE_OWNER,
        Synchronize = SYNCHRONIZE,
        All = MUTEX_ALL_ACCESS,
        Modify = MUTEX_MODIFY_STATE,
    };

    inline MutexAccess operator|(MutexAccess a, MutexAccess b) {
        return static_cast<MutexAccess>(static_cast<uint32_t>(a) |
                                        static_cast<uint32_t>(b));
    }

    enum class SemaphoreAccess : uint32_t {
        Delete = DELETE,
        ReadControl = READ_CONTROL,
        WriteDac = WRITE_DAC,
        WriteOwner = WRITE_OWNER,
        Synchronize = SYNCHRONIZE,
        All = SEMAPHORE_ALL_ACCESS,
        Modify = SEMAPHORE_MODIFY_STATE,
    };

    inline SemaphoreAccess operator|(SemaphoreAccess a, SemaphoreAccess b) {
        return static_cast<SemaphoreAccess>(static_cast<uint32_t>(a) |
                                            static_cast<uint32_t>(b));
    }

    enum class TimerAccess : uint32_t {
        Delete = DELETE,
        ReadControl = READ_CONTROL,
        WriteDac = WRITE_DAC,
        WriteOwner = WRITE_OWNER,
        Synchronize = SYNCHRONIZE,
        All = TIMER_ALL_ACCESS,
        Modify = TIMER_MODIFY_STATE,
        Query = TIMER_QUERY_STATE,
    };

    inline TimerAccess operator|(TimerAccess a, TimerAccess b) {
        return static_cast<TimerAccess>(static_cast<uint32_t>(a) |
                                        static_cast<uint32_t>(b));
    }
} // namespace YanLib::sync
#endif // SYNC_H
