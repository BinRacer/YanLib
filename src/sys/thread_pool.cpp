/* clang-format off */
/*
 * @file thread_pool.cpp
 * @date 2025-04-21
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
#include "thread_pool.h"
#include "helper/convert.h"

namespace YanLib::sys {
    thread_pool::~thread_pool() {
        for (auto &task : tasks) {
            CloseThreadpoolWork(task);
            task = nullptr;
        }
        tasks.clear();
        for (auto &timer : timers) {
            CloseThreadpoolTimer(timer);
            timer = nullptr;
        }
        timers.clear();
        for (auto &io : ios) {
            CloseThreadpoolIo(io);
            io = nullptr;
        }
        ios.clear();
        for (auto &waiter : waiters) {
            CloseThreadpoolWait(waiter);
            waiter = nullptr;
        }
        waiters.clear();
        if (group) {
            CloseThreadpoolCleanupGroup(group);
            group = nullptr;
        }
        cleanup();
    }

    void thread_pool::cleanup() {
        if (pool) {
            CloseThreadpool(pool);
            pool = nullptr;
        }
        DestroyThreadpoolEnvironment(&env);
        memset(&env, 0, sizeof(env));
    }

    bool thread_pool::create(uint32_t min, uint32_t max) {
        if (!pool) {
            cleanup();
        }
        bool result = false;
        do {
            pool = CreateThreadpool(nullptr);
            if (!pool) {
                error_code = GetLastError();
                break;
            }
            if (!SetThreadpoolThreadMinimum(pool, min)) {
                error_code = GetLastError();
                break;
            }
            SetThreadpoolThreadMaximum(pool, max);
            InitializeThreadpoolEnvironment(&env);
            SetThreadpoolCallbackPool(&env, pool);
            result = true;
        } while (false);
        return result;
    }

    void thread_pool::set_cleanup_group(
            PTP_CLEANUP_GROUP_CANCEL_CALLBACK cgc_callback) {
        if (group) {
            CloseThreadpoolCleanupGroup(group);
        }
        do {
            group = CreateThreadpoolCleanupGroup();
            if (!group) {
                error_code = GetLastError();
                break;
            }
            SetThreadpoolCallbackCleanupGroup(&env, group, cgc_callback);
        } while (false);
    }

    void thread_pool::run_early() {
        SetThreadpoolCallbackRunsLong(&env);
    }

    void thread_pool::keep_dll(HMODULE dll) {
        SetThreadpoolCallbackLibrary(&env, dll);
    }

    void thread_pool::set_priority(TP_CALLBACK_PRIORITY priority) {
        SetThreadpoolCallbackPriority(&env, priority);
    }

    bool thread_pool::get_stack_info(TP_POOL_STACK_INFORMATION *stack_info) {
        if (!QueryThreadpoolStackInformation(pool, stack_info)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool thread_pool::set_stack_info(TP_POOL_STACK_INFORMATION *stack_info) {
        if (!SetThreadpoolStackInformation(pool, stack_info)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    void thread_pool::run_persistent() {
        SetThreadpoolCallbackPersistent(&env);
    }

    bool thread_pool::submit(PTP_SIMPLE_CALLBACK simple_callback,
                             void *context) {
        if (!pool) {
            return false;
        }
        if (!TrySubmitThreadpoolCallback(simple_callback, context, &env)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    TP_WORK *thread_pool::create_task(PTP_WORK_CALLBACK work_callback,
                                      void *context) {
        if (!pool) {
            return nullptr;
        }
        TP_WORK *task = CreateThreadpoolWork(work_callback, context, &env);
        if (!task) {
            error_code = GetLastError();
            return nullptr;
        }
        tasks_rwlock.write_lock();
        tasks.push_back(task);
        tasks_rwlock.write_unlock();
        return task;
    }

    void thread_pool::submit_task(TP_WORK *work) {
        SubmitThreadpoolWork(work);
    }

    void thread_pool::wait_task(TP_WORK *work, const bool is_cancel_pending) {
        WaitForThreadpoolWorkCallbacks(work, is_cancel_pending ? TRUE : FALSE);
    }

    TP_TIMER *thread_pool::create_timer_task(PTP_TIMER_CALLBACK timer_callback,
                                             void *context) {
        if (!pool) {
            return nullptr;
        }
        TP_TIMER *timer = CreateThreadpoolTimer(timer_callback, context, &env);
        if (!timer) {
            error_code = GetLastError();
            return nullptr;
        }
        timers_rwlock.write_lock();
        timers.push_back(timer);
        timers_rwlock.write_unlock();
        return timer;
    }

    bool thread_pool::submit_timer_task(TP_TIMER *timer,
                                        FILETIME *due_time,
                                        uint32_t ms_period,
                                        const uint32_t window_length) {
        return SetThreadpoolTimerEx(timer, due_time, ms_period, window_length);
    }

    bool thread_pool::is_timer_set(TP_TIMER *timer) {
        return IsThreadpoolTimerSet(timer);
    }

    void thread_pool::wait_timer_task(TP_TIMER *timer,
                                      const bool is_cancel_pending) {
        WaitForThreadpoolTimerCallbacks(timer,
                                        is_cancel_pending ? TRUE : FALSE);
    }

    TP_IO *thread_pool::create_io_task(HANDLE file_handle,
                                       PTP_WIN32_IO_CALLBACK io_callback,
                                       void *context) {
        if (!pool || file_handle == INVALID_HANDLE_VALUE) {
            return nullptr;
        }
        TP_IO *io = CreateThreadpoolIo(file_handle, io_callback, context, &env);
        if (!io) {
            error_code = GetLastError();
            return nullptr;
        }
        ios_rwlock.write_lock();
        ios.push_back(io);
        ios_rwlock.write_unlock();
        return io;
    }

    void thread_pool::submit_io_task(TP_IO *io) {
        StartThreadpoolIo(io);
    }

    void thread_pool::cancel_io_task(TP_IO *io) {
        CancelThreadpoolIo(io);
    }

    void thread_pool::wait_io_task(TP_IO *io, const bool is_cancel_pending) {
        WaitForThreadpoolIoCallbacks(io, is_cancel_pending ? TRUE : FALSE);
    }

    TP_WAIT *thread_pool::create_wait_task(PTP_WAIT_CALLBACK wait_callback,
                                           void *context) {
        if (!pool) {
            return nullptr;
        }
        TP_WAIT *waiter = CreateThreadpoolWait(wait_callback, context, &env);
        if (!waiter) {
            error_code = GetLastError();
            return nullptr;
        }
        waiters_rwlock.write_lock();
        waiters.push_back(waiter);
        waiters_rwlock.write_unlock();
        return waiter;
    }

    void thread_pool::submit_wait_task(TP_WAIT *wait,
                                       HANDLE handle,
                                       FILETIME *timeout) {
        SetThreadpoolWait(wait, handle, timeout);
    }

    void thread_pool::wait_wait_task(TP_WAIT *wait,
                                     const bool is_cancel_pending) {
        WaitForThreadpoolWaitCallbacks(wait, is_cancel_pending ? TRUE : FALSE);
    }

    void thread_pool::wait_cleanup_member(const bool is_cancel_pending,
                                          void *context) const {
        CloseThreadpoolCleanupGroupMembers(group,
                                           is_cancel_pending ? TRUE : FALSE,
                                           context);
    }

    bool thread_pool::callback_maybe_run_long(TP_CALLBACK_INSTANCE *callback) {
        return CallbackMayRunLong(callback);
    }

    void thread_pool::detach_curr_thread_from_callback(
            TP_CALLBACK_INSTANCE *callback) {
        DisassociateCurrentThreadFromCallback(callback);
    }

    void thread_pool::free_library_when_callback_returns(
            TP_CALLBACK_INSTANCE *callback,
            HMODULE dll) {
        FreeLibraryWhenCallbackReturns(callback, dll);
    }

    void thread_pool::leave_critical_section_when_callback_returns(
            TP_CALLBACK_INSTANCE *callback,
            CRITICAL_SECTION *cs) {
        LeaveCriticalSectionWhenCallbackReturns(callback, cs);
    }

    void thread_pool::release_mutex_when_callback_returns(
            TP_CALLBACK_INSTANCE *callback,
            HANDLE mutex_handle) {
        ReleaseMutexWhenCallbackReturns(callback, mutex_handle);
    }

    void thread_pool::release_semaphore_when_callback_returns(
            TP_CALLBACK_INSTANCE *callback,
            HANDLE semaphore_handle,
            uint32_t count) {
        ReleaseSemaphoreWhenCallbackReturns(callback, semaphore_handle, count);
    }

    void
    thread_pool::set_event_when_callback_returns(TP_CALLBACK_INSTANCE *callback,
                                                 HANDLE event_handle) {
        SetEventWhenCallbackReturns(callback, event_handle);
    }

    uint32_t thread_pool::err_code() const {
        return error_code;
    }

    std::string thread_pool::err_string() const {
        std::string result = helper::convert::err_string(error_code);
        return result;
    }

    std::wstring thread_pool::err_wstring() const {
        std::wstring result = helper::convert::err_wstring(error_code);
        return result;
    }
} // namespace YanLib::sys
