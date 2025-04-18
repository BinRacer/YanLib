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
        std::vector<PROCESSENTRY32W> procs{};
        std::unordered_set<DWORD> pids{};
        std::vector<THREADENTRY32> threads{};
        std::unordered_set<DWORD> tids{};
        std::vector<MODULEENTRY32W> modules{};
        std::unordered_set<HMODULE> hmodules{};
        std::vector<HEAPLIST32> heaps{};
        std::unordered_set<ULONG_PTR> heapids{};
        HANDLE hSnapshot = INVALID_HANDLE_VALUE;
        bool isCreated = false;
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
            uint8_t Filler[0x20];
            void *InfoBlockAddress;
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
        struct _infoBlock {
            uint8_t Filler[0x70 + 0x8];
            void *wszCmdLineAddress;
        };

        static NTSTATUS nt_query_info_proc(HANDLE ProcessHandle,
                                           PROCESSINFOCLASS ProcessInformationClass,
                                           PVOID ProcessInformation,
                                           ULONG ProcessInformationLength,
                                           PULONG ReturnLength);

    public:
        proc(const proc &other) = delete;

        proc(proc &&other) = delete;

        proc &operator=(const proc &other) = delete;

        proc &operator=(proc &&other) = delete;

        proc();

        ~proc();

        bool create(const wchar_t *lpApplicationName,
                    wchar_t *lpCommandLine = nullptr,
                    LPSECURITY_ATTRIBUTES lpProcessAttributes = nullptr,
                    LPSECURITY_ATTRIBUTES lpThreadAttributes = nullptr,
                    BOOL bInheritHandles = FALSE,
                    DWORD dwCreationFlags = 0,
                    LPVOID lpEnvironment = nullptr,
                    const wchar_t *lpCurrentDirectory = nullptr);

        bool create_with_suspended(const wchar_t *lpApplicationName,
                                   wchar_t *lpCommandLine = nullptr,
                                   LPSECURITY_ATTRIBUTES lpProcessAttributes = nullptr,
                                   LPSECURITY_ATTRIBUTES lpThreadAttributes = nullptr,
                                   BOOL bInheritHandles = FALSE,
                                   DWORD dwCreationFlags = NORMAL_PRIORITY_CLASS |
                                                           CREATE_UNICODE_ENVIRONMENT |
                                                           CREATE_SUSPENDED,
                                   LPVOID lpEnvironment = nullptr,
                                   const wchar_t *lpCurrentDirectory = nullptr);

        bool create_as_user(HANDLE hToken,
                            const wchar_t *lpApplicationName,
                            wchar_t *lpCommandLine = nullptr,
                            LPSECURITY_ATTRIBUTES lpProcessAttributes = nullptr,
                            LPSECURITY_ATTRIBUTES lpThreadAttributes = nullptr,
                            BOOL bInheritHandles = FALSE,
                            DWORD dwCreationFlags = NORMAL_PRIORITY_CLASS |
                                                    CREATE_UNICODE_ENVIRONMENT,
                            LPVOID lpEnvironment = nullptr,
                            const wchar_t *lpCurrentDirectory = nullptr);


        bool create_session_zero(const wchar_t *lpApplicationName,
                                 wchar_t *lpCommandLine = nullptr,
                                 LPSECURITY_ATTRIBUTES lpProcessAttributes = nullptr,
                                 LPSECURITY_ATTRIBUTES lpThreadAttributes = nullptr,
                                 BOOL bInheritHandles = FALSE,
                                 DWORD dwCreationFlags = NORMAL_PRIORITY_CLASS |
                                                         CREATE_NEW_CONSOLE |
                                                         CREATE_UNICODE_ENVIRONMENT,
                                 LPVOID lpEnvironment = nullptr,
                                 const wchar_t *lpCurrentDirectory = nullptr);

        bool win_exec(const char *lpCmdLine, UINT uCmdShow = SW_SHOWDEFAULT);

        bool shell_exec(const wchar_t *lpFile,
                        const wchar_t *lpParameters = nullptr,
                        const wchar_t *lpDirectory = nullptr,
                        INT nShowCmd = SW_SHOWDEFAULT,
                        HWND hwnd = nullptr,
                        const wchar_t *lpOperation = nullptr);

        void *malloc(HANDLE hProcess,
                     size_t dwSize,
                     void *lpAddress = nullptr,
                     DWORD flAllocationType = MEM_COMMIT | MEM_RESERVE,
                     DWORD flProtect = PAGE_READWRITE);

        bool free(HANDLE hProcess,
                  void *lpAddress,
                  size_t dwSize = 0,
                  DWORD dwFreeType = MEM_RELEASE);

        void *malloc_reserve(HANDLE hProcess,
                             size_t dwSize,
                             void *lpAddress = nullptr,
                             DWORD flAllocationType = MEM_RESERVE,
                             DWORD flProtect = PAGE_READWRITE);

        bool free_reserve(HANDLE hProcess,
                          void *lpAddress,
                          size_t dwSize,
                          DWORD dwFreeType = MEM_DECOMMIT);

        bool mem_guard_attr(HANDLE hProcess,
                            void *lpAddress,
                            size_t dwSize,
                            DWORD flNewProtect,
                            PDWORD lpflOldProtect);

        bool read(HANDLE hProcess,
                  const void *lpBaseAddress,
                  void *lpBuffer,
                  size_t nSize,
                  size_t *lpNumberOfBytesRead);

        bool write(HANDLE hProcess,
                   void *lpBaseAddress,
                   const void *lpBuffer,
                   size_t nSize,
                   size_t *lpNumberOfBytesWritten);

        std::vector<uint8_t> read(HANDLE hProcess,
                                  const void *lpBaseAddress,
                                  size_t nSize);

        bool write(HANDLE hProcess,
                   void *lpBaseAddress,
                   std::vector<uint8_t> &buf);

        HANDLE child_thread_handle() const;

        HANDLE child_proc_handle() const;

        DWORD child_thread_id();

        DWORD child_proc_id();

        bool wait_child(DWORD dwMilliseconds = INFINITE);

        bool resume_child();

        HANDLE curr_thread_handle();

        HANDLE curr_proc_handle();

        DWORD curr_thread_id();

        DWORD curr_proc_id();

        HANDLE pid_to_handle(DWORD pid);

        DWORD handle_to_pid(HANDLE hProcess);

        std::vector<PROCESSENTRY32W> ls_procs(DWORD pid = 0);

        std::unordered_set<DWORD> ls_pids(DWORD pid = 0);

        void refresh_procs();

        bool pid_exists(DWORD pid);

        DWORD get_ppid(DWORD pid);

        PROCESSENTRY32W find_proc(DWORD pid);

        PROCESSENTRY32W find_proc(const wchar_t *lpProcessName);

        std::vector<THREADENTRY32> ls_threads(DWORD pid = 0);

        std::unordered_set<DWORD> ls_tids(DWORD pid = 0);

        void refresh_threads();

        bool tid_exists(DWORD tid);

        DWORD get_pid(DWORD tid);

        THREADENTRY32 find_thread(DWORD tid);

        std::vector<THREADENTRY32> find_threads(DWORD pid);

        std::vector<MODULEENTRY32W> ls_modules(DWORD pid = 0);

        std::unordered_set<HMODULE> ls_hmodules(DWORD pid = 0);

        void refresh_modules();

        MODULEENTRY32W find_module(const wchar_t *lpProcessName);

        MODULEENTRY32W find_module(const void *address);

        std::vector<HEAPLIST32> ls_heaps(DWORD pid = 0);

        std::unordered_set<ULONG_PTR> ls_heapids(DWORD pid = 0);

        void refresh_heaps();

        HEAPLIST32 find_heap(ULONG_PTR heapid);

        std::vector<HEAPLIST32> find_heaps(DWORD pid);

        std::vector<HEAPENTRY32> find_heap_blocks(HEAPLIST32 &heaplist32);

        std::vector<HEAPENTRY32> find_heap_blocks(ULONG_PTR heapid);

        std::vector<HEAPENTRY32> find_heap_blocks(DWORD pid);

        bool is_heap(HANDLE hProcess, void *address);

        bool is_heap(DWORD pid, void *address);

        std::string get_proc_name(HANDLE hProcess = nullptr);

        std::wstring get_proc_name_wide(HANDLE hProcess = nullptr);

        bool runas_elevated_proc(const wchar_t *appName,
                                 const wchar_t *cmdline = nullptr);

        void kill_curr_proc(UINT ExitCode);

        void *get_module_image_base(MODULEENTRY32W &mEntry);

        void *get_curr_proc_image_base();

        void *get_proc_image_base(HANDLE hProcess);

        void *get_proc_image_base(DWORD pid);

        std::string get_proc_cmdline(HANDLE hProcess);

        std::wstring get_proc_cmdline_wide(HANDLE hProcess);

        std::string get_proc_cmdline(DWORD pid);

        std::wstring get_proc_cmdline_wide(DWORD pid);

        std::string get_proc_owner(HANDLE hProcess);

        std::wstring get_proc_owner_wide(HANDLE hProcess);

        std::string get_proc_owner(DWORD pid);

        std::wstring get_proc_owner_wide(DWORD pid);

        bool fake_proc(HANDLE hProcess,
                       const wchar_t *appName,
                       const wchar_t *cmdline);

        DWORD err_code() const;

        std::string err_string() const;

        std::wstring err_wstring() const;
    };
}
#endif //PROC_H
