/* clang-format off */
/*
 * @file thread_pool.h
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
#ifndef THREAD_POOL_H
#define THREAD_POOL_H
#include <Windows.h>
#include <string>
#include <vector>
#include "sync/rwlock.h"

namespace YanLib::sys {
    class thread_pool {
    private:
        TP_POOL *pool = nullptr;
        TP_CALLBACK_ENVIRON env = {};
        TP_CLEANUP_GROUP *group = nullptr;
        std::vector<TP_WORK *> tasks = {};
        std::vector<TP_TIMER *> timers = {};
        std::vector<TP_IO *> ios = {};
        std::vector<TP_WAIT *> waiters = {};
        sync::rwlock tasks_rwlock = {};
        sync::rwlock timers_rwlock = {};
        sync::rwlock ios_rwlock = {};
        sync::rwlock waiters_rwlock = {};
        uint32_t error_code = 0;

        void cleanup();

    public:
        thread_pool(const thread_pool &other) = delete;

        thread_pool(thread_pool &&other) = delete;

        thread_pool &operator=(const thread_pool &other) = delete;

        thread_pool &operator=(thread_pool &&other) = delete;

        thread_pool() = default;

        ~thread_pool();

        bool create(uint32_t min, uint32_t max);

        void set_cleanup_group(PTP_CLEANUP_GROUP_CANCEL_CALLBACK cgc_callback);

        void run_early();

        void keep_dll(HMODULE dll);

        void set_priority(
                TP_CALLBACK_PRIORITY priority = TP_CALLBACK_PRIORITY_NORMAL);

        bool get_stack_info(TP_POOL_STACK_INFORMATION *stack_info);

        bool set_stack_info(TP_POOL_STACK_INFORMATION *stack_info);

        void run_persistent();

        bool submit(PTP_SIMPLE_CALLBACK simple_callback, void *context);

        TP_WORK *create_task(PTP_WORK_CALLBACK work_callback, void *context);

        void submit_task(TP_WORK *work);

        void wait_task(TP_WORK *work, bool is_cancel_pending = false);

        TP_TIMER *create_timer_task(PTP_TIMER_CALLBACK timer_callback,
                                    void *context);

        bool submit_timer_task(TP_TIMER *timer,
                               FILETIME *due_time,
                               uint32_t ms_period,
                               uint32_t window_length = 0);

        bool is_timer_set(TP_TIMER *timer);

        void wait_timer_task(TP_TIMER *timer, bool is_cancel_pending = false);

        TP_IO *create_io_task(HANDLE file_handle,
                              PTP_WIN32_IO_CALLBACK io_callback,
                              void *context);

        void submit_io_task(TP_IO *io);

        void cancel_io_task(TP_IO *io);

        void wait_io_task(TP_IO *io, bool is_cancel_pending = false);

        TP_WAIT *create_wait_task(PTP_WAIT_CALLBACK wait_callback,
                                  void *context);

        void submit_wait_task(TP_WAIT *wait, HANDLE handle, FILETIME *timeout);

        void wait_wait_task(TP_WAIT *wait, bool is_cancel_pending = false);

        void wait_cleanup_member(bool is_cancel_pending = false,
                                 void *context = nullptr) const;

        static bool callback_maybe_run_long(TP_CALLBACK_INSTANCE *callback);

        static void
        detach_curr_thread_from_callback(TP_CALLBACK_INSTANCE *callback);

        static void
        free_library_when_callback_returns(TP_CALLBACK_INSTANCE *callback,
                                           HMODULE dll);

        static void leave_critical_section_when_callback_returns(
                TP_CALLBACK_INSTANCE *callback,
                CRITICAL_SECTION *cs);

        static void
        release_mutex_when_callback_returns(TP_CALLBACK_INSTANCE *callback,
                                            HANDLE mutex_handle);

        static void
        release_semaphore_when_callback_returns(TP_CALLBACK_INSTANCE *callback,
                                                HANDLE semaphore_handle,
                                                uint32_t count);

        static void
        set_event_when_callback_returns(TP_CALLBACK_INSTANCE *callback,
                                        HANDLE event_handle);

        [[nodiscard]] uint32_t err_code() const;

        [[nodiscard]] std::string err_string() const;

        [[nodiscard]] std::wstring err_wstring() const;
    };
} // namespace YanLib::sys
#endif // THREAD_POOL_H
