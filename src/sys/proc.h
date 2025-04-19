//
// Created by forkernel on 2025/4/14.
//

#ifndef PROC_H
#define PROC_H

#include <Windows.h>
#include <tlhelp32.h>
#include <vector>
#include <unordered_set>
#include <string>
#include <winternl.h>

#pragma comment(lib, "ntdll.lib")

namespace YanLib::sys {
    class proc {
    private:
        STARTUPINFOW si{};
        PROCESS_INFORMATION pi{};
        wchar_t *curr_proc_env = nullptr;
        HANDLE snapshot_handle = INVALID_HANDLE_VALUE;
        std::vector<PROCESSENTRY32W> procs{};
        std::unordered_set<DWORD> pids{};
        std::vector<THREADENTRY32> threads{};
        std::unordered_set<DWORD> thread_ids{};
        std::vector<MODULEENTRY32W> modules{};
        std::unordered_set<HMODULE> module_handles{};
        std::vector<HEAPLIST32> heaps{};
        std::unordered_set<ULONG_PTR> heap_ids{};
        volatile bool proc_is_created = false;
        DWORD error_code = 0;

        // 0: kd> dt nt!_PEB
        // +0x000 InheritedAddressSpace : UChar
        // +0x001 ReadImageFileExecOptions : UChar
        // +0x002 BeingDebugged    : UChar
        // +0x003 BitField         : UChar
        // +0x003 ImageUsesLargePages : Pos 0, 1 Bit
        // +0x003 IsProtectedProcess : Pos 1, 1 Bit
        // +0x003 IsImageDynamicallyRelocated : Pos 2, 1 Bit
        // +0x003 SkipPatchingUser32Forwarders : Pos 3, 1 Bit
        // +0x003 IsPackagedProcess : Pos 4, 1 Bit
        // +0x003 IsAppContainer   : Pos 5, 1 Bit
        // +0x003 IsProtectedProcessLight : Pos 6, 1 Bit
        // +0x003 IsLongPathAwareProcess : Pos 7, 1 Bit
        // +0x004 Padding0         : [4] UChar
        // +0x008 Mutant           : Ptr64 Void
        // +0x010 ImageBaseAddress : Ptr64 Void
        // +0x018 Ldr              : Ptr64 _PEB_LDR_DATA
        // +0x020 ProcessParameters : Ptr64 _RTL_USER_PROCESS_PARAMETERS
        struct _peb {
            uint8_t fill[0x20];
            void *process_parameters;
        };

        // 0: kd> dt nt!_RTL_USER_PROCESS_PARAMETERS
        // +0x000 MaximumLength    : Uint4B
        // +0x004 Length           : Uint4B
        // +0x008 Flags            : Uint4B
        // +0x00c DebugFlags       : Uint4B
        // +0x010 ConsoleHandle    : Ptr64 Void
        // +0x018 ConsoleFlags     : Uint4B
        // +0x020 StandardInput    : Ptr64 Void
        // +0x028 StandardOutput   : Ptr64 Void
        // +0x030 StandardError    : Ptr64 Void
        // +0x038 CurrentDirectory : _CURDIR
        // +0x050 DllPath          : _UNICODE_STRING
        // +0x060 ImagePathName    : _UNICODE_STRING
        // +0x070 CommandLine      : _UNICODE_STRING
        // +0x080 Environment      : Ptr64 Void

        // 0: kd> dt _UNICODE_STRING
        // nt!_UNICODE_STRING
        // +0x000 Length           : Uint2B
        // +0x002 MaximumLength    : Uint2B
        // +0x008 Buffer           : Ptr64 Wchar
        struct _process_parameters {
            uint8_t fill[0x70 + 0x8];
            void *cmdline;
        };

        static NTSTATUS nt_query_info_proc(HANDLE proc_handle,
                                           PROCESSINFOCLASS proc_info_class,
                                           PVOID proc_info,
                                           ULONG proc_info_len,
                                           PULONG ret_len);

    public:
        proc(const proc &other) = delete;

        proc(proc &&other) = delete;

        proc &operator=(const proc &other) = delete;

        proc &operator=(proc &&other) = delete;

        proc();

        ~proc();

        bool create(const wchar_t *app_name,
                    wchar_t *cmdline = nullptr,
                    LPSECURITY_ATTRIBUTES proc_attrs = nullptr,
                    LPSECURITY_ATTRIBUTES thread_attrs = nullptr,
                    BOOL is_inherit_handles = FALSE,
                    DWORD create_flag = 0,
                    void* env = nullptr,
                    const wchar_t *curr_dir = nullptr);

        bool create_with_suspended(const wchar_t *app_name,
                                   wchar_t *cmdline = nullptr,
                                   LPSECURITY_ATTRIBUTES proc_attrs = nullptr,
                                   LPSECURITY_ATTRIBUTES thread_attrs = nullptr,
                                   BOOL is_inherit_handles = FALSE,
                                   DWORD create_flag = NORMAL_PRIORITY_CLASS |
                                                       CREATE_SUSPENDED,
                                   void* env = nullptr,
                                   const wchar_t *curr_dir = nullptr);

        bool create_as_user(HANDLE token_handle,
                            const wchar_t *app_name,
                            wchar_t *cmdline = nullptr,
                            LPSECURITY_ATTRIBUTES proc_attrs = nullptr,
                            LPSECURITY_ATTRIBUTES thread_attrs = nullptr,
                            BOOL is_inherit_handles = FALSE,
                            DWORD create_flag = NORMAL_PRIORITY_CLASS |
                                                CREATE_UNICODE_ENVIRONMENT,
                            void* env = nullptr,
                            const wchar_t *curr_dir = nullptr);


        bool create_session_zero(const wchar_t *app_name,
                                 wchar_t *cmdline = nullptr,
                                 LPSECURITY_ATTRIBUTES proc_attrs = nullptr,
                                 LPSECURITY_ATTRIBUTES thread_attrs = nullptr,
                                 BOOL is_inherit_handles = FALSE,
                                 DWORD create_flag = NORMAL_PRIORITY_CLASS |
                                                     CREATE_UNICODE_ENVIRONMENT |
                                                     CREATE_NEW_CONSOLE,
                                 void* env = nullptr,
                                 const wchar_t *curr_dir = nullptr);

        bool create_with_logon(const wchar_t *username,
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

        bool create_with_token(HANDLE token_handle,
                               LPCWSTR app_name,
                               LPWSTR cmdline = nullptr,
                               DWORD logon_flag = LOGON_WITH_PROFILE,
                               DWORD create_flag = NORMAL_PRIORITY_CLASS |
                                                   CREATE_NEW_CONSOLE |
                                                   CREATE_UNICODE_ENVIRONMENT,
                               void* env = nullptr,
                               LPCWSTR curr_dir = nullptr);

        bool win_exec(const char *cmdline, UINT show_flag = SW_SHOWDEFAULT);

        bool shell_exec(const wchar_t *file_name,
                        const wchar_t *params = nullptr,
                        const wchar_t *dir = nullptr,
                        INT show_flag = SW_SHOWDEFAULT,
                        HWND hwnd = nullptr,
                        const wchar_t *operation = nullptr);

        bool runas_elevated(const wchar_t *app_name,
                            const wchar_t *cmdline = nullptr);

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

        void *module_image_base(MODULEENTRY32W &module_entry);

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

        DWORD exit_status(HANDLE proc_handle);

        void kill(UINT exit_code);

        bool fake_proc(HANDLE proc_handle,
                       const wchar_t *app_name,
                       const wchar_t *cmdline);

        HANDLE thread_handle();

        HANDLE proc_handle();

        DWORD thread_id();

        DWORD proc_id();

        HANDLE pid_to_handle(DWORD pid,
                             DWORD desired_access = PROCESS_ALL_ACCESS,
                             BOOL is_inherit_handle = FALSE);

        DWORD handle_to_pid(HANDLE proc_handle);

        HANDLE child_thread_handle() const;

        HANDLE child_proc_handle() const;

        DWORD child_thread_id();

        DWORD child_proc_id();

        bool wait_child(DWORD milli_seconds = INFINITE);

        bool resume_child();

        std::vector<PROCESSENTRY32W> ls_procs(DWORD pid = 0);

        std::unordered_set<DWORD> ls_pids(DWORD pid = 0);

        void refresh_procs();

        bool pid_exists(DWORD pid);

        DWORD get_ppid(DWORD pid);

        PROCESSENTRY32W find_proc(DWORD pid);

        PROCESSENTRY32W find_proc(const wchar_t *proc_name);

        std::vector<THREADENTRY32> ls_threads(DWORD pid = 0);

        std::unordered_set<DWORD> ls_thread_ids(DWORD pid = 0);

        void refresh_threads();

        bool tid_exists(DWORD tid);

        DWORD tid_to_pid(DWORD tid);

        THREADENTRY32 find_thread(DWORD tid);

        std::vector<THREADENTRY32> find_threads(DWORD pid);

        std::vector<MODULEENTRY32W> ls_modules(DWORD pid = 0);

        std::unordered_set<HMODULE> ls_module_handles(DWORD pid = 0);

        void refresh_modules();

        MODULEENTRY32W find_module(const wchar_t *proc_name);

        MODULEENTRY32W find_module(const void *address);

        std::vector<HEAPLIST32> ls_heaps(DWORD pid = 0);

        std::unordered_set<ULONG_PTR> ls_heap_ids(DWORD pid = 0);

        void refresh_heaps();

        HEAPLIST32 find_heap(ULONG_PTR heap_id);

        std::vector<HEAPLIST32> find_heaps(DWORD pid);

        std::vector<HEAPENTRY32> find_heap_blocks(HEAPLIST32 &heap_list);

        std::vector<HEAPENTRY32> find_heap_blocks(ULONG_PTR heap_id);

        std::vector<HEAPENTRY32> find_heap_blocks(DWORD pid);

        bool is_heap(HANDLE proc_handle, void *address);

        bool is_heap(DWORD pid, void *address);

        DWORD err_code() const;

        std::string err_string() const;

        std::wstring err_wstring() const;
    };
}
#endif //PROC_H
