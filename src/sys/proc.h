//
// Created by forkernel on 2025/4/14.
//

#ifndef PROC_H
#define PROC_H

#include <Windows.h>
#include <vector>
#include <string>
#include <winternl.h>
#include <psapi.h>
#include "sync/rwlock.h"

#pragma comment(lib, "ntdll.lib")

namespace YanLib::sys {
    class proc {
    private:
        std::vector<PROCESS_INFORMATION> proc_infos = {};
        std::vector<HANDLE> proc_handles = {};
        sync::rwlock proc_info_rwlock = {};
        sync::rwlock proc_handle_rwlock = {};
        wchar_t *curr_proc_env = nullptr;
        unsigned long error_code = 0;

        NTSTATUS nt_query_info_proc(HANDLE proc_handle,
                                    PROCESSINFOCLASS proc_info_class,
                                    void *proc_info,
                                    unsigned long proc_info_len,
                                    unsigned long *ret_len);

    public:
        proc(const proc &other) = delete;

        proc(proc &&other) = delete;

        proc &operator=(const proc &other) = delete;

        proc &operator=(proc &&other) = delete;

        proc() = default;

        ~proc();

        PROCESS_INFORMATION create(
            const wchar_t *app_name,
            wchar_t *cmdline = nullptr,
            SECURITY_ATTRIBUTES *proc_attrs = nullptr,
            SECURITY_ATTRIBUTES *thread_attrs = nullptr,
            bool is_inherit_handles = false,
            unsigned long create_flag = 0,
            void *env = nullptr,
            const wchar_t *curr_dir = nullptr);

        PROCESS_INFORMATION create_with_suspended(
            const wchar_t *app_name,
            wchar_t *cmdline = nullptr,
            SECURITY_ATTRIBUTES *proc_attrs = nullptr,
            SECURITY_ATTRIBUTES *thread_attrs = nullptr,
            bool is_inherit_handles = false,
            unsigned long create_flag = NORMAL_PRIORITY_CLASS |
                                CREATE_SUSPENDED,
            void *env = nullptr,
            const wchar_t *curr_dir = nullptr);

        PROCESS_INFORMATION create_as_user(
            HANDLE token_handle,
            const wchar_t *app_name,
            wchar_t *cmdline = nullptr,
            SECURITY_ATTRIBUTES *proc_attrs = nullptr,
            SECURITY_ATTRIBUTES *thread_attrs = nullptr,
            bool is_inherit_handles = false,
            unsigned long create_flag = NORMAL_PRIORITY_CLASS |
                                CREATE_UNICODE_ENVIRONMENT,
            void *env = nullptr,
            const wchar_t *curr_dir = nullptr);


        PROCESS_INFORMATION create_session_zero(
            const wchar_t *app_name,
            wchar_t *cmdline = nullptr,
            SECURITY_ATTRIBUTES *proc_attrs = nullptr,
            SECURITY_ATTRIBUTES *thread_attrs = nullptr,
            bool is_inherit_handles = false,
            unsigned long create_flag = NORMAL_PRIORITY_CLASS |
                                CREATE_UNICODE_ENVIRONMENT |
                                CREATE_NEW_CONSOLE,
            void *env = nullptr,
            const wchar_t *curr_dir = nullptr);

        PROCESS_INFORMATION create_with_logon(
            const wchar_t *username,
            const wchar_t *domain,
            const wchar_t *password,
            const wchar_t *app_name,
            wchar_t *cmdline = nullptr,
            unsigned long logon_flag = LOGON_WITH_PROFILE,
            unsigned long create_flag = NORMAL_PRIORITY_CLASS |
                                CREATE_NEW_CONSOLE |
                                CREATE_UNICODE_ENVIRONMENT,
            void *env = nullptr,
            const wchar_t *curr_dir = nullptr);

        PROCESS_INFORMATION create_with_token(
            HANDLE token_handle,
            const wchar_t *app_name,
            wchar_t *cmdline = nullptr,
            unsigned long logon_flag = LOGON_WITH_PROFILE,
            unsigned long create_flag = NORMAL_PRIORITY_CLASS |
                                CREATE_NEW_CONSOLE |
                                CREATE_UNICODE_ENVIRONMENT,
            void *env = nullptr,
            const wchar_t *curr_dir = nullptr);

        bool win_exec(const char *cmdline, unsigned int show_flag = SW_SHOWDEFAULT);

        bool shell_exec(const wchar_t *file_name,
                        const wchar_t *params = nullptr,
                        const wchar_t *dir = nullptr,
                        int show_flag = SW_SHOWDEFAULT,
                        HWND hwnd = nullptr,
                        const wchar_t *operation = nullptr);

        bool runas_elevated(const wchar_t *app_name,
                            const wchar_t *cmdline = nullptr);

        bool fake_proc(HANDLE proc_handle,
                       const wchar_t *app_name,
                       const wchar_t *cmdline);

        bool wait_child(HANDLE child_proc_handle, unsigned long milli_seconds = INFINITE);

        bool resume_child(HANDLE child_thread_handle);

        HANDLE thread_handle();

        HANDLE proc_handle();

        unsigned long thread_id();

        unsigned long proc_id();

        HANDLE pid_to_handle(unsigned long pid,
                             unsigned long desired_access = PROCESS_ALL_ACCESS,
                             bool is_inherit_handle = false);

        unsigned long handle_to_pid(HANDLE proc_handle);


        bool kill(HANDLE proc_handle, unsigned int exit_code);

        void exit(unsigned int exit_code);

        unsigned long exit_status(HANDLE proc_handle);

        STARTUPINFOW startup_info();

        void *malloc(HANDLE proc_handle,
                     size_t size,
                     void *addr = nullptr,
                     unsigned long allocate_flag = MEM_COMMIT | MEM_RESERVE,
                     unsigned long protect_flag = PAGE_READWRITE);

        bool free(HANDLE proc_handle,
                  void *addr,
                  size_t size = 0,
                  unsigned long free_type = MEM_RELEASE);

        void *malloc_reserve(HANDLE proc_handle,
                             size_t size,
                             void *addr = nullptr,
                             unsigned long allocate_type = MEM_RESERVE,
                             unsigned long protect_flag = PAGE_READWRITE);

        bool free_reserve(HANDLE proc_handle,
                          void *addr,
                          size_t size,
                          unsigned long free_type = MEM_DECOMMIT);

        bool mem_guard_attr(HANDLE proc_handle,
                            void *addr,
                            size_t size,
                            unsigned long new_protect_flag,
                            unsigned long *old_protect_flag);

        bool query_mem(HANDLE proc_handle,
                       const void *address,
                       MEMORY_BASIC_INFORMATION *buffer,
                       size_t len);

        bool global_mem_status(MEMORYSTATUSEX *buffer);

        bool read(HANDLE proc_handle,
                  const void *base_addr,
                  void *buf,
                  size_t size,
                  size_t *bytes_read);

        bool write(HANDLE proc_handle,
                   void *base_addr,
                   const void *buf,
                   size_t size,
                   size_t *bytes_written);

        std::vector<uint8_t> read(HANDLE proc_handle,
                                  const void *base_addr,
                                  size_t size);

        bool write(HANDLE proc_handle,
                   void *base_addr,
                   std::vector<uint8_t> &buf);

        void flush_write_buffer();

        std::wstring env_strings();

        std::wstring get_env_var(std::wstring var_name);

        bool set_env_var(std::wstring var_name, std::wstring var_value);

        std::wstring cmdline();

        std::string cmdline(HANDLE proc_handle);

        std::wstring cmdline_wide(HANDLE proc_handle);

        std::string cmdline(unsigned long pid);

        std::wstring cmdline_wide(unsigned long pid);

        std::string owner(HANDLE proc_handle);

        std::wstring owner_wide(HANDLE proc_handle);

        std::string owner(unsigned long pid);

        std::wstring owner_wide(unsigned long pid);

        std::string image_name(HANDLE proc_handle = nullptr);

        std::wstring image_name_wide(HANDLE proc_handle = nullptr);

        void *image_base();

        void *image_base(HANDLE proc_handle);

        void *image_base(unsigned long pid);

        unsigned long get_priority(HANDLE proc_handle);

        bool set_priority(HANDLE proc_handle, unsigned long priority);

        int get_thread_priority(HANDLE thread_handle);

        bool set_thread_priority(HANDLE thread_handle, int priority);

        unsigned long handle_count(HANDLE proc_handle);

        unsigned long gui_handle_count(HANDLE proc_handle,
                               unsigned long flag = GR_GDIOBJECTS);

        unsigned long processor_num();

        bool get_info(HANDLE proc_handle,
                      PROCESS_INFORMATION_CLASS proc_info_class,
                      void *proc_info,
                      unsigned long proc_info_size);

        bool set_info(HANDLE proc_handle,
                      PROCESS_INFORMATION_CLASS proc_info_class,
                      void *proc_info,
                      unsigned long proc_info_size);

        bool get_mem_info(HANDLE proc_handle,
                          PPROCESS_MEMORY_COUNTERS mem_counters,
                          unsigned long mem_counters_size);

        bool get_module_info(HANDLE proc_handle,
                             HMODULE module_handle,
                             MODULEINFO *mod_info,
                             unsigned long mod_info_size);

        bool logical_processor_info(SYSTEM_LOGICAL_PROCESSOR_INFORMATION *buf,
                                    unsigned long *ret_len);

        bool get_affinity_mask(HANDLE proc_handle,
                               DWORD_PTR* proc_affinity_mask,
                               DWORD_PTR* system_affinity_mask);

        bool set_affinity_mask(HANDLE proc_handle,
                               DWORD_PTR proc_affinity_mask);

        bool get_group_affinity(HANDLE proc_handle,
                                unsigned short *group_count,
                                unsigned short *group_array);

        bool io_counters(HANDLE proc_handle,
                         IO_COUNTERS *io_counters);

        bool get_mitigation_policy(HANDLE proc_handle,
                                   PROCESS_MITIGATION_POLICY mitigation_policy,
                                   void *buffer,
                                   size_t len);

        bool set_mitigation_policy(PROCESS_MITIGATION_POLICY mitigation_policy,
                                   void *buffer,
                                   size_t len);

        bool get_priority_boost(HANDLE proc_handle);

        bool set_priority_boost(HANDLE proc_handle,
                                bool is_disable_priority_boost);

        bool get_shutdown_params(unsigned long *level,
                                 unsigned long *flag);

        bool set_shutdown_params(unsigned long level,
                                 unsigned long flag);

        bool time_statistics(HANDLE proc_handle,
                             FILETIME *creation_time,
                             FILETIME *exit_time,
                             FILETIME *kernel_time,
                             FILETIME *user_time);

        unsigned long system_version(unsigned long pid);

        bool get_working_set_size(HANDLE proc_handle,
                                  SIZE_T *min_working_set_size,
                                  SIZE_T *max_working_set_size);

        bool set_working_set_size(HANDLE proc_handle,
                                  size_t min_working_set_size,
                                  size_t max_working_set_size);

        bool get_processor_system_cycle_time(
            unsigned short group,
            SYSTEM_PROCESSOR_CYCLE_TIME_INFORMATION *buffer,
            unsigned long *ret_len);

        bool is_microsoft_store_app(HANDLE proc_handle);

        bool is_exe_search_path(const wchar_t *exe_name);

        bool query_full_image_name(HANDLE proc_handle,
                                   unsigned long flag,
                                   wchar_t *exe_name,
                                   unsigned long *size);

        bool get_affinity_update_mode(HANDLE proc_handle,
                                      unsigned long *flag);

        bool set_affinity_update_mode(HANDLE proc_handle,
                                      unsigned long flag);

        bool all_thread_cycle_time(HANDLE proc_handle,
                                   unsigned long long *cycle_time);

        bool set_restriction_exemption(bool is_enable_exemption);

        [[nodiscard]] unsigned long err_code() const;

        [[nodiscard]] std::string err_string() const;

        [[nodiscard]] std::wstring err_wstring() const;
    };
}
#endif //PROC_H
