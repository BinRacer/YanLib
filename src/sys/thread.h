//
// Created by forkernel on 2025/4/18.
//

#ifndef THREAD_H
#define THREAD_H
#include <Windows.h>
#include <string>
#include <vector>
#include "sync/rwlock.h"

namespace YanLib::sys {
    class thread {
    private:
        std::vector<std::pair<unsigned long, HANDLE> > thread_records = {};
        sync::rwlock thread_record_rwlock = {};
        std::vector<HANDLE> open_thread_handles = {};
        sync::rwlock open_thread_record_rwlock = {};
        unsigned long error_code = 0;

    public:
        thread(const thread &other) = delete;

        thread(thread &&other) = delete;

        thread &operator=(const thread &other) = delete;

        thread &operator=(thread &&other) = delete;

        thread() = default;

        ~thread();

        HANDLE create(
            LPTHREAD_START_ROUTINE start_addr,
            void *params,
            size_t stack_size = 0,
            SECURITY_ATTRIBUTES *security_attrs = nullptr);

        HANDLE create_with_suspend(
            LPTHREAD_START_ROUTINE start_addr,
            void *params,
            size_t stack_size = 0,
            SECURITY_ATTRIBUTES *security_attrs = nullptr);

        HANDLE create_with_stack_reserve(
            LPTHREAD_START_ROUTINE start_addr,
            void *params,
            size_t stack_size,
            SECURITY_ATTRIBUTES *security_attrs = nullptr);

        HANDLE create_remote(
            HANDLE proc_handle,
            LPTHREAD_START_ROUTINE start_addr,
            void *params,
            size_t stack_size = 0,
            LPPROC_THREAD_ATTRIBUTE_LIST attr_list = nullptr,
            SECURITY_ATTRIBUTES *security_attrs = nullptr);

        HANDLE create_remote_with_suspend(
            HANDLE proc_handle,
            LPTHREAD_START_ROUTINE start_addr,
            void *params,
            size_t stack_size = 0,
            LPPROC_THREAD_ATTRIBUTE_LIST attr_list = nullptr,
            SECURITY_ATTRIBUTES *security_attrs = nullptr);

        HANDLE create_remote_with_stack_reserve(
            HANDLE proc_handle,
            LPTHREAD_START_ROUTINE start_addr,
            void *params,
            size_t stack_size,
            LPPROC_THREAD_ATTRIBUTE_LIST attr_list = nullptr,
            SECURITY_ATTRIBUTES *security_attrs = nullptr);

        HANDLE curr_thread_handle();

        HANDLE curr_process_handle();

        unsigned long curr_thread_id();

        unsigned long curr_process_id();

        HANDLE tid_to_handle(
            unsigned long thread_id,
            unsigned long desired_access = THREAD_ALL_ACCESS,
            bool is_inherit_handle = false);

        unsigned long handle_to_tid(HANDLE thread_handle);

        unsigned long handle_to_pid(HANDLE thread_handle);

        std::vector<HANDLE> thread_handles();

        std::vector<unsigned long> thread_ids();

        unsigned long tls_alloc();

        bool tls_free(unsigned long tls_index);

        void *tls_get(unsigned long tls_index);

        bool tls_set(unsigned long tls_index, void *tls_value);

        unsigned long wait_for_input_idle(HANDLE proc_handle,
                                          unsigned long milli_seconds);

        bool attach_thread_input(unsigned long id_attach,
                                 unsigned long id_attach_to,
                                 bool is_attach);

        bool init_proc_thread_attr_list(
            LPPROC_THREAD_ATTRIBUTE_LIST attr_list,
            unsigned long attr_count,
            unsigned long flag,
            SIZE_T *size);

        bool update_proc_thread_attr(
            LPPROC_THREAD_ATTRIBUTE_LIST attr_list,
            unsigned long flag,
            DWORD_PTR attr,
            void *value,
            size_t bytes_size,
            void *previous_value,
            SIZE_T *ret_size);

        void delete_proc_thread_attr_list(
            LPPROC_THREAD_ATTRIBUTE_LIST attr_list);

        unsigned long suspend(HANDLE thread_handle);

        unsigned long resume(HANDLE thread_handle);

        bool wait(HANDLE thread_handle,
                  unsigned long milli_seconds = INFINITE);

        bool wait_all(bool is_wait_all = true,
                      unsigned long milli_seconds = INFINITE);

        void sleep(unsigned long milli_seconds);

        unsigned long sleep(unsigned long milli_seconds, bool alertable);

        bool yield();

        bool kill(HANDLE thread_handle, unsigned long exit_code);

        void kill_all(unsigned long exit_code);

        void exit(unsigned long exit_code);

        unsigned long exit_status(HANDLE thread_handle);

        bool thread_info(HANDLE thread_handle,
                         THREAD_INFORMATION_CLASS thread_info_class,
                         void *thread_info,
                         unsigned long thread_info_size);

        bool is_io_pending(HANDLE thread_handle);

        int get_priority(HANDLE thread_handle);

        bool set_priority(HANDLE thread_handle, int priority);

        unsigned long get_proc_priority(HANDLE proc_handle);

        bool set_proc_priority(HANDLE proc_handle, unsigned long priority);

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

        bool set_group_affinity(
            HANDLE thread_handle,
            const GROUP_AFFINITY *group_affinity,
            GROUP_AFFINITY *previous_group_affinity);

        bool get_ideal_processor(HANDLE thread_handle,
                                 PROCESSOR_NUMBER *ideal_processor);

        bool set_ideal_processor(
            HANDLE thread_handle,
            PROCESSOR_NUMBER *ideal_processor,
            PROCESSOR_NUMBER *previous_ideal_processor);

        bool get_info(HANDLE thread_handle,
                      THREAD_INFORMATION_CLASS thread_info_class,
                      void *thread_info,
                      unsigned long thread_information_size);

        bool set_info(HANDLE thread_handle,
                      THREAD_INFORMATION_CLASS thread_info_class,
                      void *thread_info,
                      unsigned long thread_information_size);

        bool query_idle_processor_cycle_time(
            unsigned short group,
            unsigned long *buffer_length,
            unsigned long long *processor_idle_cycle_time);

        bool query_cycle_time(HANDLE thread_handle,
                              unsigned long long *cycle_time);

        DWORD_PTR set_affinity_mask(HANDLE thread_handle,
                                    DWORD_PTR thread_affinity_mask);

        bool set_stack_guarantee(unsigned long *bytes_stack);

        [[nodiscard]] unsigned long err_code() const;

        [[nodiscard]] std::string err_string() const;

        [[nodiscard]] std::wstring err_wstring() const;
    };
}
#endif //THREAD_H
