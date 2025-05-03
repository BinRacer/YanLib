//
// Created by forkernel on 2025/4/21.
//

#ifndef THREAD_POOL_H
#define THREAD_POOL_H
#include <Windows.h>
#include <string>
#include <vector>
#include "sync/rwlock.h"

namespace YanLib::sys {
    class thread_pool {
    private:
        TP_POOL* pool = nullptr;
        TP_CALLBACK_ENVIRON env = {};
        TP_CLEANUP_GROUP* group = nullptr;
        std::vector<TP_WORK *> tasks = {};
        std::vector<TP_TIMER *> timers = {};
        std::vector<TP_IO *> ios = {};
        std::vector<TP_WAIT *> waiters = {};
        sync::rwlock tasks_rwlock = {};
        sync::rwlock timers_rwlock = {};
        sync::rwlock ios_rwlock = {};
        sync::rwlock waiters_rwlock = {};
        DWORD error_code = 0;

        void cleanup();

    public:
        thread_pool(const thread_pool &other) = delete;

        thread_pool(thread_pool &&other) = delete;

        thread_pool &operator=(const thread_pool &other) = delete;

        thread_pool &operator=(thread_pool &&other) = delete;

        thread_pool() = default;

        ~thread_pool();

        bool create(DWORD min, DWORD max);

        void set_cleanup_group(PTP_CLEANUP_GROUP_CANCEL_CALLBACK cgc_callback);

        void run_early();

        void keep_dll(HMODULE dll);

        void set_priority(TP_CALLBACK_PRIORITY priority = TP_CALLBACK_PRIORITY_NORMAL);

        bool get_stack_info(TP_POOL_STACK_INFORMATION *stack_info);

        bool set_stack_info(TP_POOL_STACK_INFORMATION *stack_info);

        void run_persistent();

        bool submit(PTP_SIMPLE_CALLBACK simple_callback, void *context);

        TP_WORK *create_task(PTP_WORK_CALLBACK work_callback,
                             void *context);

        void submit_task(TP_WORK *work);

        void wait_task(TP_WORK *work,
                       bool is_cancel_pending = false);

        TP_TIMER *create_timer_task(PTP_TIMER_CALLBACK timer_callback,
                                    void *context);

        bool submit_timer_task(TP_TIMER *timer,
                               FILETIME *due_time,
                               DWORD ms_period,
                               DWORD window_length = 0);

        bool is_timer_set(TP_TIMER *timer);

        void wait_timer_task(TP_TIMER *timer,
                             bool is_cancel_pending = false);

        TP_IO *create_io_task(HANDLE file_handle,
                              PTP_WIN32_IO_CALLBACK io_callback,
                              void *context);

        void submit_io_task(TP_IO *io);

        void cancel_io_task(TP_IO *io);

        void wait_io_task(TP_IO *io,
                          bool is_cancel_pending = false);

        TP_WAIT *create_wait_task(PTP_WAIT_CALLBACK wait_callback,
                                  void *context);

        void submit_wait_task(TP_WAIT *wait,
                              HANDLE h,
                              FILETIME *timeout);

        void wait_wait_task(TP_WAIT *wait,
                            bool is_cancel_pending = false);

        void wait_cleanup_member(bool is_cancel_pending = false,
                                 void *context = nullptr);

        static bool callback_maybe_run_long(
            TP_CALLBACK_INSTANCE *callback_instance);

        static void detach_curr_thread_from_callback(
            TP_CALLBACK_INSTANCE *callback_instance);

        static void free_library_when_callback_returns(
            TP_CALLBACK_INSTANCE *callback_instance,
            HMODULE dll);

        static void leave_critical_section_when_callback_returns(
            TP_CALLBACK_INSTANCE *callback_instance,
            CRITICAL_SECTION *critical_section);

        static void release_mutex_when_callback_returns(
            TP_CALLBACK_INSTANCE *callback_instance,
            HANDLE mutex_handle);

        static void release_semaphore_when_callback_returns(
            TP_CALLBACK_INSTANCE *callback_instance,
            HANDLE semaphore_handle,
            DWORD count);

        static void set_event_when_callback_returns(
            TP_CALLBACK_INSTANCE *callback_instance,
            HANDLE event_handle);

        [[nodiscard]] DWORD err_code() const;

        [[nodiscard]] std::string err_string() const;

        [[nodiscard]] std::wstring err_wstring() const;
    };
}
#endif //THREAD_POOL_H
