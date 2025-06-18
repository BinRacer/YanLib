/* clang-format off */
/*
 * @file proc.h
 * @date 2025-04-14
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
#ifndef PROC_H
#define PROC_H
#include <Windows.h>
#include <winternl.h>
#include <psapi.h>
#include <minwinbase.h>
#include <WinBase.h>
#include <minwindef.h>
#include <winnt.h>
#include <processthreadsapi.h>
#include <vector>
#include <string>
#include <unordered_map>
#include "helper/convert.h"
#include "sync/rwlock.h"
#include "mem/mem.h"
#include "sys.h"
#pragma comment(lib, "ntdll.lib")
namespace YanLib::sys {
    class proc {
    private:
        std::vector<PROCESS_INFORMATION> proc_infos = {};
        std::vector<HANDLE> proc_handles = {};
        sync::rwlock proc_info_rwlock = {};
        sync::rwlock proc_handle_rwlock = {};
        uint32_t error_code = 0;

        NTSTATUS nt_query_info_proc(HANDLE proc_handle,
                                    PROCESSINFOCLASS proc_info_class,
                                    void *proc_info,
                                    uint32_t proc_info_len,
                                    uint32_t *real_size);

    public:
        proc(const proc &other) = delete;

        proc(proc &&other) = delete;

        proc &operator=(const proc &other) = delete;

        proc &operator=(proc &&other) = delete;

        proc() = default;

        ~proc();

        PROCESS_INFORMATION
        create(const char *app_name,
               char *cmdline = nullptr,
               SECURITY_ATTRIBUTES *proc_attrs = nullptr,
               SECURITY_ATTRIBUTES *thread_attrs = nullptr,
               bool is_inherit = false,
               ProcCreateFlag create_flag = ProcCreateFlag::Default,
               void *env = nullptr,
               const char *curr_dir = nullptr);

        PROCESS_INFORMATION
        create(const wchar_t *app_name,
               wchar_t *cmdline = nullptr,
               SECURITY_ATTRIBUTES *proc_attrs = nullptr,
               SECURITY_ATTRIBUTES *thread_attrs = nullptr,
               bool is_inherit = false,
               ProcCreateFlag create_flag = ProcCreateFlag::Default,
               void *env = nullptr,
               const wchar_t *curr_dir = nullptr);

        PROCESS_INFORMATION
        create_with_suspended(const char *app_name,
                              char *cmdline = nullptr,
                              SECURITY_ATTRIBUTES *proc_attrs = nullptr,
                              SECURITY_ATTRIBUTES *thread_attrs = nullptr,
                              bool is_inherit = false,
                              ProcCreateFlag create_flag =
                                      ProcCreateFlag::NormalPriorityClass |
                                      ProcCreateFlag::CreateSuspended,
                              void *env = nullptr,
                              const char *curr_dir = nullptr);

        PROCESS_INFORMATION
        create_with_suspended(const wchar_t *app_name,
                              wchar_t *cmdline = nullptr,
                              SECURITY_ATTRIBUTES *proc_attrs = nullptr,
                              SECURITY_ATTRIBUTES *thread_attrs = nullptr,
                              bool is_inherit = false,
                              ProcCreateFlag create_flag =
                                      ProcCreateFlag::NormalPriorityClass |
                                      ProcCreateFlag::CreateSuspended,
                              void *env = nullptr,
                              const wchar_t *curr_dir = nullptr);

        PROCESS_INFORMATION
        create_as_user(HANDLE token_handle,
                       const char *app_name,
                       char *cmdline = nullptr,
                       SECURITY_ATTRIBUTES *proc_attrs = nullptr,
                       SECURITY_ATTRIBUTES *thread_attrs = nullptr,
                       bool is_inherit = false,
                       ProcCreateFlag create_flag =
                               ProcCreateFlag::NormalPriorityClass |
                               ProcCreateFlag::CreateUnicodeEnvironment,
                       void *env = nullptr,
                       const char *curr_dir = nullptr);

        PROCESS_INFORMATION
        create_as_user(HANDLE token_handle,
                       const wchar_t *app_name,
                       wchar_t *cmdline = nullptr,
                       SECURITY_ATTRIBUTES *proc_attrs = nullptr,
                       SECURITY_ATTRIBUTES *thread_attrs = nullptr,
                       bool is_inherit = false,
                       ProcCreateFlag create_flag =
                               ProcCreateFlag::NormalPriorityClass |
                               ProcCreateFlag::CreateUnicodeEnvironment,
                       void *env = nullptr,
                       const wchar_t *curr_dir = nullptr);

        PROCESS_INFORMATION create_with_logon(
                const char *username,
                const char *domain,
                const char *password,
                const char *app_name,
                const char *cmdline = nullptr,
                LogonFlag logon_flag = LogonFlag::WithProfile,
                ProcCreateFlag create_flag =
                        ProcCreateFlag::NormalPriorityClass |
                        ProcCreateFlag::CreateUnicodeEnvironment |
                        ProcCreateFlag::CreateNewConsole,
                void *env = nullptr,
                const char *curr_dir = nullptr,
                helper::CodePage code_page = helper::curr_code_page());

        PROCESS_INFORMATION
        create_with_logon(const wchar_t *username,
                          const wchar_t *domain,
                          const wchar_t *password,
                          const wchar_t *app_name,
                          wchar_t *cmdline = nullptr,
                          LogonFlag logon_flag = LogonFlag::WithProfile,
                          ProcCreateFlag create_flag =
                                  ProcCreateFlag::NormalPriorityClass |
                                  ProcCreateFlag::CreateUnicodeEnvironment |
                                  ProcCreateFlag::CreateNewConsole,
                          void *env = nullptr,
                          const wchar_t *curr_dir = nullptr);

        PROCESS_INFORMATION create_with_token(
                HANDLE token_handle,
                const char *app_name,
                const char *cmdline = nullptr,
                LogonFlag logon_flag = LogonFlag::WithProfile,
                ProcCreateFlag create_flag =
                        ProcCreateFlag::NormalPriorityClass |
                        ProcCreateFlag::CreateUnicodeEnvironment |
                        ProcCreateFlag::CreateNewConsole,
                void *env = nullptr,
                const char *curr_dir = nullptr,
                helper::CodePage code_page = helper::curr_code_page());

        PROCESS_INFORMATION
        create_with_token(HANDLE token_handle,
                          const wchar_t *app_name,
                          wchar_t *cmdline = nullptr,
                          LogonFlag logon_flag = LogonFlag::WithProfile,
                          ProcCreateFlag create_flag =
                                  ProcCreateFlag::NormalPriorityClass |
                                  ProcCreateFlag::CreateUnicodeEnvironment |
                                  ProcCreateFlag::CreateNewConsole,
                          void *env = nullptr,
                          const wchar_t *curr_dir = nullptr);

        bool win_exec(const char *cmdline,
                      ShowFlag show_flag = ShowFlag::ShowDefault);

        bool shell_exec(const char *file_name,
                        const char *params = nullptr,
                        const char *dir = nullptr,
                        ShowFlag show_flag = ShowFlag::ShowDefault,
                        HWND window_handle = nullptr,
                        const char *operation = nullptr);

        bool shell_exec(const wchar_t *file_name,
                        const wchar_t *params = nullptr,
                        const wchar_t *dir = nullptr,
                        ShowFlag show_flag = ShowFlag::ShowDefault,
                        HWND window_handle = nullptr,
                        const wchar_t *operation = nullptr);

        bool runas_elevated(const char *app_name,
                            const char *cmdline = nullptr);

        bool runas_elevated(const wchar_t *app_name,
                            const wchar_t *cmdline = nullptr);

        bool wait_child(HANDLE child_proc_handle,
                        uint32_t milli_seconds = INFINITE);

        bool resume_child(HANDLE child_thread_handle);

        HANDLE thread_handle();

        HANDLE proc_handle();

        uint32_t thread_id();

        uint32_t proc_id();

        HANDLE pid_to_handle(uint32_t pid,
                             ProcAccess access = ProcAccess::All,
                             bool is_inherit = false);

        uint32_t handle_to_pid(HANDLE proc_handle);

        bool kill(HANDLE proc_handle, uint32_t exit_code);

        void exit(uint32_t exit_code);

        uint32_t exit_status(HANDLE proc_handle);

        bool get_startup_info(STARTUPINFOA *info);

        bool get_startup_info(STARTUPINFOW *info);

        void *malloc(HANDLE proc_handle,
                     size_t size,
                     void *addr = nullptr,
                     AllocateType type = AllocateType::Commit |
                             AllocateType::Reserve,
                     mem::MemoryProtect protect = mem::MemoryProtect::ReadWrite);

        bool free(HANDLE proc_handle,
                  void *addr,
                  size_t size = 0,
                  AllocateType type = AllocateType::Release);

        void *malloc_reserve(HANDLE proc_handle,
                             size_t size,
                             void *addr = nullptr,
                             AllocateType type = AllocateType::Reserve,
                             mem::MemoryProtect protect = mem::MemoryProtect::ReadWrite);

        bool free_reserve(HANDLE proc_handle,
                          void *addr,
                          size_t size,
                          AllocateType type = AllocateType::DeCommit);

        bool mem_guard_attr(HANDLE proc_handle,
                            void *addr,
                            size_t size,
                            mem::MemoryProtect protect,
                            mem::MemoryProtect *old_protect);

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

        std::vector<uint8_t>
        read(HANDLE proc_handle, const void *base_addr, size_t size);

        bool write(HANDLE proc_handle,
                   void *base_addr,
                   const std::vector<uint8_t> &buf);

        void flush_write_buffer();

        bool get_env(std::string &env,
                     helper::CodePage code_page = helper::curr_code_page());

        bool get_env(std::wstring &env);

        bool get_env(std::vector<std::string> &env,
                     helper::CodePage code_page = helper::curr_code_page());

        bool get_env(std::vector<std::wstring> &env);

        bool get_env(std::unordered_map<std::string, std::string> &env,
                     helper::CodePage code_page = helper::curr_code_page());

        bool get_env(std::unordered_map<std::wstring, std::wstring> &env);

        std::string get_env_var(const std::string &var_name);

        std::wstring get_env_var(const std::wstring &var_name);

        bool set_env_var(const std::string &var_name,
                         const std::string &var_value);

        bool set_env_var(const std::wstring &var_name,
                         const std::wstring &var_value);

        void get_cmdline(std::string &cmdline);

        void get_cmdline(std::wstring &cmdline);

        bool get_cmdline(HANDLE proc_handle,
                         std::string &cmdline,
                         helper::CodePage code_page = helper::curr_code_page());

        bool get_cmdline(HANDLE proc_handle, std::wstring &cmdline);

        bool get_cmdline(uint32_t pid, std::string &cmdline);

        bool get_cmdline(uint32_t pid, std::wstring &cmdline);

        bool get_owner(HANDLE proc_handle,
                       std::string &owner,
                       helper::CodePage code_page = helper::curr_code_page());

        bool get_owner(HANDLE proc_handle, std::wstring &owner);

        bool get_owner(uint32_t pid, std::string &owner);

        bool get_owner(uint32_t pid, std::wstring &owner);

        bool get_image_name(HANDLE proc_handle,
                            std::string &image_name,
                            bool native_name = false);

        bool get_image_name(HANDLE proc_handle,
                            std::wstring &image_name,
                            bool native_name = false);

        void *image_base();

        void *image_base(HANDLE proc_handle);

        void *image_base(uint32_t pid);

        uint32_t get_priority(HANDLE proc_handle);

        bool set_priority(HANDLE proc_handle, uint32_t priority);

        int32_t get_thread_priority(HANDLE thread_handle);

        bool set_thread_priority(HANDLE thread_handle, int32_t priority);

        uint32_t handle_count(HANDLE proc_handle);

        uint32_t processor_num();

        bool get_info(HANDLE proc_handle,
                      PROCESS_INFORMATION_CLASS proc_info_class,
                      void *proc_info,
                      uint32_t proc_info_size);

        bool set_info(HANDLE proc_handle,
                      PROCESS_INFORMATION_CLASS proc_info_class,
                      void *proc_info,
                      uint32_t proc_info_size);

        bool get_mem_info(HANDLE proc_handle,
                          PPROCESS_MEMORY_COUNTERS mem_counters,
                          uint32_t mem_counters_size);

        bool get_module_info(HANDLE proc_handle,
                             HMODULE module_handle,
                             MODULEINFO *mod_info,
                             uint32_t mod_info_size);

        bool logical_processor_info(SYSTEM_LOGICAL_PROCESSOR_INFORMATION *buf,
                                    uint32_t *real_size);

        bool get_affinity_mask(HANDLE proc_handle,
                               uintptr_t *proc_affinity_mask,
                               uintptr_t *system_affinity_mask);

        bool set_affinity_mask(HANDLE proc_handle,
                               uintptr_t proc_affinity_mask);

        bool get_group_affinity(HANDLE proc_handle,
                                uint16_t *group_count,
                                uint16_t *group_array);

        bool io_counters(HANDLE proc_handle, IO_COUNTERS *io_counters);

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

        bool get_shutdown_params(uint32_t *level, bool *show_retry_dialog);

        bool set_shutdown_params(uint32_t level, bool show_retry_dialog);

        bool time_statistics(HANDLE proc_handle,
                             FILETIME *creation_time,
                             FILETIME *exit_time,
                             FILETIME *kernel_time,
                             FILETIME *user_time);

        uint32_t system_version(uint32_t pid);

        bool get_working_set_size(HANDLE proc_handle,
                                  SIZE_T *min_working_set_size,
                                  SIZE_T *max_working_set_size);

        bool set_working_set_size(HANDLE proc_handle,
                                  size_t min_working_set_size,
                                  size_t max_working_set_size);

        bool get_processor_system_cycle_time(
                uint16_t group,
                SYSTEM_PROCESSOR_CYCLE_TIME_INFORMATION *buffer,
                uint32_t *real_size);

        bool is_microsoft_store_app(HANDLE proc_handle);

        bool is_exe_search_path(const char *exe_name);

        bool is_exe_search_path(const wchar_t *exe_name);

        bool get_affinity_update_mode(HANDLE proc_handle, bool *auto_update);

        bool set_affinity_update_mode(HANDLE proc_handle, bool auto_update);

        bool all_thread_cycle_time(HANDLE proc_handle, uint64_t *cycle_time);

        bool set_restriction_exemption(bool is_enable_exemption);

        [[nodiscard]] uint32_t err_code() const;

        [[nodiscard]] std::string err_string() const;

        [[nodiscard]] std::wstring err_wstring() const;
    };
} // namespace YanLib::sys
#endif // PROC_H
