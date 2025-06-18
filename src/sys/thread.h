/* clang-format off */
/*
 * @file thread.h
 * @date 2025-04-18
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
#ifndef THREAD_H
#define THREAD_H
#include <Windows.h>
#include <minwindef.h>
#include <WinBase.h>
#include <winnt.h>
#include <processthreadsapi.h>
#include <minwinbase.h>
#include <string>
#include <vector>
#include "sync/rwlock.h"
#include "sys.h"
namespace YanLib::sys {
    class thread {
    private:
        std::vector<std::pair<uint32_t, HANDLE>> thread_records = {};
        sync::rwlock thread_record_rwlock = {};
        std::vector<HANDLE> open_thread_handles = {};
        sync::rwlock open_thread_record_rwlock = {};
        uint32_t error_code = 0;

    public:
        thread(const thread &other) = delete;

        thread(thread &&other) = delete;

        thread &operator=(const thread &other) = delete;

        thread &operator=(thread &&other) = delete;

        thread() = default;

        ~thread();

        HANDLE create(LPTHREAD_START_ROUTINE start_addr,
                      void *params,
                      size_t stack_size = 0,
                      SECURITY_ATTRIBUTES *sa = nullptr);

        HANDLE create_with_suspend(LPTHREAD_START_ROUTINE start_addr,
                                   void *params,
                                   size_t stack_size = 0,
                                   SECURITY_ATTRIBUTES *sa = nullptr);

        HANDLE
        create_with_stack_reserve(LPTHREAD_START_ROUTINE start_addr,
                                  void *params,
                                  size_t stack_size,
                                  SECURITY_ATTRIBUTES *sa = nullptr);

        HANDLE create_remote(HANDLE proc_handle,
                             LPTHREAD_START_ROUTINE start_addr,
                             void *params,
                             size_t stack_size = 0,
                             LPPROC_THREAD_ATTRIBUTE_LIST attr_list = nullptr,
                             SECURITY_ATTRIBUTES *sa = nullptr);

        HANDLE create_remote_with_suspend(
                HANDLE proc_handle,
                LPTHREAD_START_ROUTINE start_addr,
                void *params,
                size_t stack_size = 0,
                LPPROC_THREAD_ATTRIBUTE_LIST attr_list = nullptr,
                SECURITY_ATTRIBUTES *sa = nullptr);

        HANDLE create_remote_with_stack_reserve(
                HANDLE proc_handle,
                LPTHREAD_START_ROUTINE start_addr,
                void *params,
                size_t stack_size,
                LPPROC_THREAD_ATTRIBUTE_LIST attr_list = nullptr,
                SECURITY_ATTRIBUTES *sa = nullptr);

        HANDLE curr_thread_handle();

        HANDLE curr_process_handle();

        uint32_t curr_thread_id();

        uint32_t curr_process_id();

        HANDLE tid_to_handle(uint32_t tid,
                             ThreadAccess access = ThreadAccess::All,
                             bool is_inherit = false);

        uint32_t handle_to_tid(HANDLE thread_handle);

        uint32_t handle_to_pid(HANDLE thread_handle);

        std::vector<HANDLE> thread_handles();

        std::vector<uint32_t> thread_ids();

        uint32_t tls_alloc();

        bool tls_free(uint32_t tls_index);

        void *tls_get(uint32_t tls_index);

        bool tls_set(uint32_t tls_index, void *tls_value);

        uint32_t wait_for_input_idle(HANDLE proc_handle,
                                     uint32_t milli_seconds);

        bool attach_thread_input(uint32_t id_attach,
                                 uint32_t id_attach_to,
                                 bool is_attach);

        bool init_proc_thread_attr_list(LPPROC_THREAD_ATTRIBUTE_LIST attr_list,
                                        uint32_t attr_count,
                                        SIZE_T *size);

        bool update_proc_thread_attr(LPPROC_THREAD_ATTRIBUTE_LIST attr_list,
                                     uintptr_t attr,
                                     void *value,
                                     size_t bytes_size,
                                     void *previous_value,
                                     SIZE_T *ret_size);

        void
        delete_proc_thread_attr_list(LPPROC_THREAD_ATTRIBUTE_LIST attr_list);

        uint32_t suspend(HANDLE thread_handle);

        uint32_t resume(HANDLE thread_handle);

        bool wait(HANDLE thread_handle, uint32_t milli_seconds = INFINITE);

        bool wait_all(bool is_wait_all = true,
                      uint32_t milli_seconds = INFINITE);

        void sleep(uint32_t milli_seconds);

        uint32_t sleep(uint32_t milli_seconds, bool alertable);

        bool yield();

        bool kill(HANDLE thread_handle, uint32_t exit_code);

        void kill_all(uint32_t exit_code);

        void exit(uint32_t exit_code);

        uint32_t exit_status(HANDLE thread_handle);

        bool thread_info(HANDLE thread_handle,
                         THREAD_INFORMATION_CLASS thread_info_class,
                         void *thread_info,
                         uint32_t thread_info_size);

        bool is_io_pending(HANDLE thread_handle);

        int32_t get_priority(HANDLE thread_handle);

        bool set_priority(HANDLE thread_handle, int32_t priority);

        uint32_t get_proc_priority(HANDLE proc_handle);

        bool set_proc_priority(HANDLE proc_handle, uint32_t priority);

        bool get_priority_boost(HANDLE thread_handle);

        bool set_priority_boost(HANDLE thread_handle,
                                bool is_disable_priority_boost);

        bool time_statistics(HANDLE thread_handle,
                             FILETIME *creation_time,
                             FILETIME *exit_time,
                             FILETIME *kernel_time,
                             FILETIME *user_time);

        HRESULT get_description(HANDLE thread_handle,
                                wchar_t **thread_description);

        HRESULT set_description(HANDLE thread_handle,
                                const wchar_t *thread_description);

        bool get_group_affinity(HANDLE thread_handle,
                                GROUP_AFFINITY *group_affinity);

        bool set_group_affinity(HANDLE thread_handle,
                                const GROUP_AFFINITY *group_affinity,
                                GROUP_AFFINITY *previous_group_affinity);

        bool get_ideal_processor(HANDLE thread_handle,
                                 PROCESSOR_NUMBER *ideal_processor);

        bool set_ideal_processor(HANDLE thread_handle,
                                 PROCESSOR_NUMBER *ideal_processor,
                                 PROCESSOR_NUMBER *previous_ideal_processor);

        bool get_info(HANDLE thread_handle,
                      THREAD_INFORMATION_CLASS thread_info_class,
                      void *thread_info,
                      uint32_t thread_information_size);

        bool set_info(HANDLE thread_handle,
                      THREAD_INFORMATION_CLASS thread_info_class,
                      void *thread_info,
                      uint32_t thread_information_size);

        bool
        query_idle_processor_cycle_time(uint16_t group,
                                        uint32_t *buffer_length,
                                        uint64_t *processor_idle_cycle_time);

        bool query_cycle_time(HANDLE thread_handle, uint64_t *cycle_time);

        uintptr_t set_affinity_mask(HANDLE thread_handle,
                                    uintptr_t thread_affinity_mask);

        bool set_stack_guarantee(uint32_t *bytes_stack);

        [[nodiscard]] uint32_t err_code() const;

        [[nodiscard]] std::string err_string() const;

        [[nodiscard]] std::wstring err_wstring() const;
    };
} // namespace YanLib::sys
#endif // THREAD_H
