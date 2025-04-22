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
        sync::rwlock rwlock = {};
        wchar_t *curr_proc_env = nullptr;
        DWORD error_code = 0;

        static NTSTATUS nt_query_info_proc(HANDLE proc_handle,
                                           PROCESSINFOCLASS proc_info_class,
                                           void *proc_info,
                                           ULONG proc_info_len,
                                           PULONG ret_len);

    public:
        proc(const proc &other) = delete;

        proc(proc &&other) = delete;

        proc &operator=(const proc &other) = delete;

        proc &operator=(proc &&other) = delete;

        proc() = default;

        ~proc();

        PROCESS_INFORMATION
        create(const wchar_t *app_name,
               wchar_t *cmdline = nullptr,
               LPSECURITY_ATTRIBUTES proc_attrs = nullptr,
               LPSECURITY_ATTRIBUTES thread_attrs = nullptr,
               bool is_inherit_handles = false,
               DWORD create_flag = 0,
               void *env = nullptr,
               const wchar_t *curr_dir = nullptr);

        PROCESS_INFORMATION
        create_with_suspended(const wchar_t *app_name,
                              wchar_t *cmdline = nullptr,
                              LPSECURITY_ATTRIBUTES proc_attrs = nullptr,
                              LPSECURITY_ATTRIBUTES thread_attrs = nullptr,
                              bool is_inherit_handles = false,
                              DWORD create_flag = NORMAL_PRIORITY_CLASS |
                                                  CREATE_SUSPENDED,
                              void *env = nullptr,
                              const wchar_t *curr_dir = nullptr);

        PROCESS_INFORMATION
        create_as_user(HANDLE token_handle,
                       const wchar_t *app_name,
                       wchar_t *cmdline = nullptr,
                       LPSECURITY_ATTRIBUTES proc_attrs = nullptr,
                       LPSECURITY_ATTRIBUTES thread_attrs = nullptr,
                       bool is_inherit_handles = false,
                       DWORD create_flag = NORMAL_PRIORITY_CLASS |
                                           CREATE_UNICODE_ENVIRONMENT,
                       void *env = nullptr,
                       const wchar_t *curr_dir = nullptr);


        PROCESS_INFORMATION
        create_session_zero(const wchar_t *app_name,
                            wchar_t *cmdline = nullptr,
                            LPSECURITY_ATTRIBUTES proc_attrs = nullptr,
                            LPSECURITY_ATTRIBUTES thread_attrs = nullptr,
                            bool is_inherit_handles = false,
                            DWORD create_flag = NORMAL_PRIORITY_CLASS |
                                                CREATE_UNICODE_ENVIRONMENT |
                                                CREATE_NEW_CONSOLE,
                            void *env = nullptr,
                            const wchar_t *curr_dir = nullptr);

        PROCESS_INFORMATION
        create_with_logon(const wchar_t *username,
                          const wchar_t *domain,
                          const wchar_t *password,
                          const wchar_t *app_name,
                          wchar_t *cmdline = nullptr,
                          DWORD logon_flag = LOGON_WITH_PROFILE,
                          DWORD create_flag = NORMAL_PRIORITY_CLASS |
                                              CREATE_NEW_CONSOLE |
                                              CREATE_UNICODE_ENVIRONMENT,
                          void *env = nullptr,
                          const wchar_t *curr_dir = nullptr);

        PROCESS_INFORMATION
        create_with_token(HANDLE token_handle,
                          const wchar_t *app_name,
                          wchar_t *cmdline = nullptr,
                          DWORD logon_flag = LOGON_WITH_PROFILE,
                          DWORD create_flag = NORMAL_PRIORITY_CLASS |
                                              CREATE_NEW_CONSOLE |
                                              CREATE_UNICODE_ENVIRONMENT,
                          void *env = nullptr,
                          const wchar_t *curr_dir = nullptr);

        bool win_exec(const char *cmdline, UINT show_flag = SW_SHOWDEFAULT);

        bool shell_exec(const wchar_t *file_name,
                        const wchar_t *params = nullptr,
                        const wchar_t *dir = nullptr,
                        INT show_flag = SW_SHOWDEFAULT,
                        HWND hwnd = nullptr,
                        const wchar_t *operation = nullptr);

        bool runas_elevated(const wchar_t *app_name,
                            const wchar_t *cmdline = nullptr);

        bool fake_proc(HANDLE proc_handle,
                       const wchar_t *app_name,
                       const wchar_t *cmdline);

        bool wait_child(HANDLE child_proc_handle, DWORD milli_seconds = INFINITE);

        bool resume_child(HANDLE child_thread_handle);

        HANDLE thread_handle();

        HANDLE proc_handle();

        DWORD thread_id();

        DWORD proc_id();

        HANDLE pid_to_handle(DWORD pid,
                             DWORD desired_access = PROCESS_ALL_ACCESS,
                             bool is_inherit_handle = false);

        DWORD handle_to_pid(HANDLE proc_handle);


        bool kill(HANDLE proc_handle, UINT exit_code);

        void exit(UINT exit_code);

        DWORD exit_status(HANDLE proc_handle);

        STARTUPINFOW startup_info();

        void *malloc(HANDLE proc_handle,
                     size_t size,
                     void *addr = nullptr,
                     DWORD allocate_flag = MEM_COMMIT | MEM_RESERVE,
                     DWORD protect_flag = PAGE_READWRITE);

        bool free(HANDLE proc_handle,
                  void *addr,
                  size_t size = 0,
                  DWORD free_type = MEM_RELEASE);

        void *malloc_reserve(HANDLE proc_handle,
                             size_t size,
                             void *addr = nullptr,
                             DWORD allocate_type = MEM_RESERVE,
                             DWORD protect_flag = PAGE_READWRITE);

        bool free_reserve(HANDLE proc_handle,
                          void *addr,
                          size_t size,
                          DWORD free_type = MEM_DECOMMIT);

        bool mem_guard_attr(HANDLE proc_handle,
                            void *addr,
                            size_t size,
                            DWORD new_protect_flag,
                            PDWORD old_protect_flag);

        bool query_mem(HANDLE proc_handle,
                       const void *address,
                       PMEMORY_BASIC_INFORMATION buffer,
                       size_t len);

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

        std::string cmdline(DWORD pid);

        std::wstring cmdline_wide(DWORD pid);

        std::string owner(HANDLE proc_handle);

        std::wstring owner_wide(HANDLE proc_handle);

        std::string owner(DWORD pid);

        std::wstring owner_wide(DWORD pid);

        std::string image_name(HANDLE proc_handle = nullptr);

        std::wstring image_name_wide(HANDLE proc_handle = nullptr);

        void *image_base();

        void *image_base(HANDLE proc_handle);

        void *image_base(DWORD pid);

        DWORD get_priority(HANDLE proc_handle);

        bool set_priority(HANDLE proc_handle, DWORD priority);

        int get_thread_priority(HANDLE thread_handle);

        bool set_thread_priority(HANDLE thread_handle, int priority);

        DWORD handle_count(HANDLE proc_handle);

        DWORD gui_handle_count(HANDLE proc_handle,
                               DWORD flag = GR_GDIOBJECTS);

        DWORD processor_num();

        bool get_info(HANDLE proc_handle,
                      PROCESS_INFORMATION_CLASS proc_info_class,
                      void *proc_info,
                      DWORD proc_info_size);

        bool set_info(HANDLE proc_handle,
                      PROCESS_INFORMATION_CLASS proc_info_class,
                      void *proc_info,
                      DWORD proc_info_size);

        bool get_mem_info(HANDLE proc_handle,
                          PPROCESS_MEMORY_COUNTERS mem_counters,
                          DWORD mem_counters_size);

        bool get_module_info(HANDLE proc_handle,
                             HMODULE module_handle,
                             LPMODULEINFO mod_info,
                             DWORD mod_info_size);

        bool logical_processor_info(PSYSTEM_LOGICAL_PROCESSOR_INFORMATION buf,
                                    PDWORD ret_len);

        bool get_affinity_mask(HANDLE proc_handle,
                               PDWORD_PTR proc_affinity_mask,
                               PDWORD_PTR system_affinity_mask);

        bool set_affinity_mask(HANDLE proc_handle,
                               DWORD_PTR proc_affinity_mask);

        bool get_group_affinity(HANDLE proc_handle,
                                PUSHORT group_count,
                                PUSHORT group_array);

        bool io_counters(HANDLE proc_handle,
                         PIO_COUNTERS io_counters);

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

        bool get_shutdown_params(LPDWORD level,
                                 LPDWORD flag);

        bool set_shutdown_params(DWORD level,
                                 DWORD flag);

        bool time_statistics(HANDLE proc_handle,
                             LPFILETIME creation_time,
                             LPFILETIME exit_time,
                             LPFILETIME kernel_time,
                             LPFILETIME user_time);

        DWORD system_version(DWORD pid);

        bool get_working_set_size(HANDLE proc_handle,
                                  PSIZE_T min_working_set_size,
                                  PSIZE_T max_working_set_size);

        bool set_working_set_size(HANDLE proc_handle,
                                  size_t min_working_set_size,
                                  size_t max_working_set_size);

        bool get_processor_system_cycle_time(USHORT group,
                                             PSYSTEM_PROCESSOR_CYCLE_TIME_INFORMATION buffer,
                                             PDWORD ret_len);

        bool is_microsoft_store_app(HANDLE proc_handle);

        bool is_exe_search_path(const wchar_t *exe_name);

        bool query_full_image_name(HANDLE proc_handle,
                                   DWORD flag,
                                   wchar_t *exe_name,
                                   PDWORD size);

        bool get_affinity_update_mode(HANDLE proc_handle,
                                      LPDWORD flag);

        bool set_affinity_update_mode(HANDLE proc_handle,
                                      DWORD flag);

        bool all_thread_cycle_time(HANDLE proc_handle,
                                   PULONG64 cycle_time);

        bool set_restriction_exemption(bool is_enable_exemption);

        [[nodiscard]] DWORD err_code() const;

        [[nodiscard]] std::string err_string() const;

        [[nodiscard]] std::wstring err_wstring() const;
    };
}
#endif //PROC_H
