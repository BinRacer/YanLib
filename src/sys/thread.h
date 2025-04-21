//
// Created by forkernel on 2025/4/18.
//

#ifndef THREAD_H
#define THREAD_H
#include <Windows.h>
#include <string>
#include <unordered_map>
#include "sync/rwlock.h"

namespace YanLib::sys {
    class thread {
    private:
        std::unordered_map<DWORD, HANDLE> thread_records = {};
        sync::rwlock rwlock = {};
        DWORD error_code = 0;

    public:
        thread(const thread &other) = delete;

        thread(thread &&other) = delete;

        thread &operator=(const thread &other) = delete;

        thread &operator=(thread &&other) = delete;

        thread() = default;

        ~thread();

        bool create(LPTHREAD_START_ROUTINE start_addr,
                    void *params,
                    size_t stack_size = 0,
                    LPSECURITY_ATTRIBUTES security_attrs = nullptr);

        bool create_with_suspend(LPTHREAD_START_ROUTINE start_addr,
                                 void *params,
                                 size_t stack_size = 0,
                                 LPSECURITY_ATTRIBUTES security_attrs = nullptr);

        bool create_with_stack_reserve(LPTHREAD_START_ROUTINE start_addr,
                                       void *params,
                                       size_t stack_size,
                                       LPSECURITY_ATTRIBUTES security_attrs = nullptr);

        bool create_remote(HANDLE proc_handle,
                           LPTHREAD_START_ROUTINE start_addr,
                           void *params,
                           size_t stack_size = 0,
                           LPSECURITY_ATTRIBUTES security_attrs = nullptr);

        bool create_remote_with_suspend(HANDLE proc_handle,
                                        LPTHREAD_START_ROUTINE start_addr,
                                        void *params,
                                        size_t stack_size = 0,
                                        LPSECURITY_ATTRIBUTES security_attrs = nullptr);

        bool create_remote_with_stack_reserve(HANDLE proc_handle,
                                              LPTHREAD_START_ROUTINE start_addr,
                                              void *params,
                                              size_t stack_size,
                                              LPSECURITY_ATTRIBUTES security_attrs = nullptr);

        bool kill(HANDLE thread_handle, DWORD exit_code);

        void kill_all(DWORD exit_code);

        void exit(DWORD exit_code);

        HANDLE curr_thread_handle();

        HANDLE curr_process_handle();

        DWORD curr_thread_id();

        DWORD curr_process_id();

        HANDLE tid_to_handle(DWORD thread_id,
                             DWORD desired_access = THREAD_ALL_ACCESS,
                             bool is_inherit_handle = false);

        DWORD handle_to_pid(HANDLE thread_handle);

        std::vector<HANDLE> thread_handles();

        std::vector<DWORD> thread_ids();

        bool wait(HANDLE thread_handle, DWORD milli_seconds = INFINITE);

        bool wait_all(bool is_wait_all = true, DWORD milli_seconds = INFINITE);

        [[nodiscard]] DWORD err_code() const;

        [[nodiscard]] std::string err_string() const;

        [[nodiscard]] std::wstring err_wstring() const;
    };
}
#endif //THREAD_H
