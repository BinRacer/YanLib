//
// Created by forkernel on 2025/4/21.
//

#include "thread_pool.h"
#include "helper/convert.h"

namespace YanLib::sys {
    thread_pool::~thread_pool() {
        if (!tasks.empty()) {
            for (auto &task: tasks) {
                CloseThreadpoolWork(task);
                task = nullptr;
            }
            tasks.clear();
        }
        if (!timers.empty()) {
            for (auto &timer: timers) {
                CloseThreadpoolTimer(timer);
                timer = nullptr;
            }
            timers.clear();
        }
        if (!ios.empty()) {
            for (auto &io: ios) {
                CloseThreadpoolIo(io);
                io = nullptr;
            }
            ios.clear();
        }
        if (!waiters.empty()) {
            for (auto &waiter: waiters) {
                CloseThreadpoolWait(waiter);
                waiter = nullptr;
            }
            waiters.clear();
        }
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

    bool thread_pool::create(DWORD min, DWORD max) {
        if (!pool) {
            cleanup();
        }
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
            return true;
        } while (false);
        return false;
    }

    void thread_pool::set_cleanup_group(PTP_CLEANUP_GROUP_CANCEL_CALLBACK cgc_callback) {
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

    bool thread_pool::get_stack_info(PTP_POOL_STACK_INFORMATION stack_info) {
        if (!QueryThreadpoolStackInformation(pool, stack_info)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool thread_pool::set_stack_info(PTP_POOL_STACK_INFORMATION stack_info) {
        if (!SetThreadpoolStackInformation(pool, stack_info)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    void thread_pool::run_persistent() {
        SetThreadpoolCallbackPersistent(&env);
    }

    bool thread_pool::submit(PTP_SIMPLE_CALLBACK simple_callback, void *context) {
        if (!pool) {
            return false;
        }
        if (!TrySubmitThreadpoolCallback(simple_callback, context, &env)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    PTP_WORK thread_pool::create_task(PTP_WORK_CALLBACK work_callback, void *context) {
        if (!pool) {
            return nullptr;
        }
        PTP_WORK task = CreateThreadpoolWork(work_callback, context, &env);
        if (!task) {
            error_code = GetLastError();
            return nullptr;
        }
        tasks_rwlock.write_lock();
        tasks.push_back(task);
        tasks_rwlock.write_unlock();
        return task;
    }

    void thread_pool::submit_task(PTP_WORK work) {
        SubmitThreadpoolWork(work);
    }

    void thread_pool::wait_task(PTP_WORK work, bool is_cancel_pending) {
        WaitForThreadpoolWorkCallbacks(work,
                                       is_cancel_pending ? TRUE : FALSE);
    }

    PTP_TIMER thread_pool::create_timer_task(PTP_TIMER_CALLBACK timer_callback,
                                             void *context) {
        if (!pool) {
            return nullptr;
        }
        PTP_TIMER timer = CreateThreadpoolTimer(timer_callback, context, &env);
        if (!timer) {
            error_code = GetLastError();
            return nullptr;
        }
        timers_rwlock.write_lock();
        timers.push_back(timer);
        timers_rwlock.write_unlock();
        return timer;
    }

    bool thread_pool::submit_timer_task(PTP_TIMER timer,
                                        PFILETIME due_time,
                                        DWORD ms_period,
                                        DWORD window_length) {
        return SetThreadpoolTimerEx(timer,
                                    due_time,
                                    window_length,
                                    window_length);
    }

    bool thread_pool::is_timer_set(PTP_TIMER timer) {
        return IsThreadpoolTimerSet(timer);
    }

    void thread_pool::wait_timer_task(PTP_TIMER timer, bool is_cancel_pending) {
        WaitForThreadpoolTimerCallbacks(timer,
                                        is_cancel_pending ? TRUE : FALSE);
    }

    PTP_IO thread_pool::create_io_task(HANDLE file_handle,
                                       PTP_WIN32_IO_CALLBACK io_callback,
                                       void *context) {
        if (!pool || file_handle == INVALID_HANDLE_VALUE) {
            return nullptr;
        }
        PTP_IO io = CreateThreadpoolIo(file_handle, io_callback, context, &env);
        if (!io) {
            error_code = GetLastError();
            return nullptr;
        }
        ios_rwlock.write_lock();
        ios.push_back(io);
        ios_rwlock.write_unlock();
        return io;
    }

    void thread_pool::submit_io_task(PTP_IO io) {
        StartThreadpoolIo(io);
    }

    void thread_pool::cancel_io_task(PTP_IO io) {
        CancelThreadpoolIo(io);
    }

    void thread_pool::wait_io_task(PTP_IO io, bool is_cancel_pending) {
        WaitForThreadpoolIoCallbacks(io,
                                     is_cancel_pending ? TRUE : FALSE);
    }

    PTP_WAIT thread_pool::create_wait_task(PTP_WAIT_CALLBACK wait_callback,
                                           void *context) {
        if (!pool) {
            return nullptr;
        }
        PTP_WAIT waiter = CreateThreadpoolWait(wait_callback, context, &env);
        if (!waiter) {
            error_code = GetLastError();
            return nullptr;
        }
        waiters_rwlock.write_lock();
        waiters.push_back(waiter);
        waiters_rwlock.write_unlock();
        return waiter;
    }

    void thread_pool::submit_wait_task(PTP_WAIT wait, HANDLE h, PFILETIME timeout) {
        SetThreadpoolWait(wait, h, timeout);
    }

    void thread_pool::wait_wait_task(PTP_WAIT wait, bool is_cancel_pending) {
        WaitForThreadpoolWaitCallbacks(wait,
                                       is_cancel_pending ? TRUE : FALSE);
    }

    void thread_pool::wait_cleanup_member(bool is_cancel_pending,
                                          void *context) {
        CloseThreadpoolCleanupGroupMembers(group,
                                           is_cancel_pending ? TRUE : FALSE,
                                           context);
    }

    bool
    thread_pool::callback_maybe_run_long(PTP_CALLBACK_INSTANCE callback_instance) {
        return CallbackMayRunLong(callback_instance);
    }

    void
    thread_pool::detach_curr_thread_from_callback(PTP_CALLBACK_INSTANCE callback_instance) {
        DisassociateCurrentThreadFromCallback(callback_instance);
    }

    void
    thread_pool::free_library_when_callback_returns(PTP_CALLBACK_INSTANCE callback_instance,
                                                    HMODULE dll) {
        FreeLibraryWhenCallbackReturns(callback_instance, dll);
    }

    void
    thread_pool::leave_critical_section_when_callback_returns(PTP_CALLBACK_INSTANCE callback_instance,
                                                              PCRITICAL_SECTION critical_section) {
        LeaveCriticalSectionWhenCallbackReturns(callback_instance, critical_section);
    }

    void
    thread_pool::release_mutex_when_callback_returns(PTP_CALLBACK_INSTANCE callback_instance,
                                                     HANDLE mutex_handle) {
        ReleaseMutexWhenCallbackReturns(callback_instance, mutex_handle);
    }

    void
    thread_pool::release_semaphore_when_callback_returns(PTP_CALLBACK_INSTANCE callback_instance,
                                                         HANDLE semaphore_handle,
                                                         DWORD count) {
        ReleaseSemaphoreWhenCallbackReturns(callback_instance, semaphore_handle, count);
    }

    void
    thread_pool::set_event_when_callback_returns(PTP_CALLBACK_INSTANCE callback_instance,
                                                 HANDLE event_handle) {
        SetEventWhenCallbackReturns(callback_instance, event_handle);
    }

    DWORD thread_pool::err_code() const {
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
}
