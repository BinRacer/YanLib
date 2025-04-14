//
// Created by forkernel on 2025/4/14.
//

#ifndef PROC_H
#define PROC_H
#include <Windows.h>
#include <tlhelp32.h>
#include <vector>
#include <set>

namespace YanLib::sys {
    class proc {
    private:
        STARTUPINFOW si{};
        PROCESS_INFORMATION pi{};
        std::vector<PROCESSENTRY32W> procs{};
        std::set<DWORD> pids{};
        std::vector<THREADENTRY32> threads{};
        std::set<DWORD> tids{};
        std::vector<MODULEENTRY32W> modules{};
        std::set<HMODULE> hmodules{};
        std::vector<HEAPLIST32> heaps{};
        std::set<ULONG_PTR> heapids{};
        HANDLE hSnapshot = INVALID_HANDLE_VALUE;
        bool isCreated = false;
        DWORD error_code = 0;

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

        std::set<DWORD> ls_pids(DWORD pid = 0);

        void refresh_procs();

        bool pid_exists(DWORD pid);

        DWORD get_ppid(DWORD pid);

        PROCESSENTRY32W find_proc(DWORD pid);

        PROCESSENTRY32W find_proc(const wchar_t *lpProcessName);

        std::vector<THREADENTRY32> ls_threads(DWORD pid = 0);

        std::set<DWORD> ls_tids(DWORD pid = 0);

        void refresh_threads();

        bool tid_exists(DWORD tid);

        DWORD get_pid(DWORD tid);

        THREADENTRY32 find_thread(DWORD tid);

        std::vector<THREADENTRY32> find_threads(DWORD pid);

        std::vector<MODULEENTRY32W> ls_modules(DWORD pid = 0);

        std::set<HMODULE> ls_hmodules(DWORD pid = 0);

        void refresh_modules();

        MODULEENTRY32W find_module(const wchar_t *lpProcessName);

        MODULEENTRY32W find_module(const void *address);

        std::vector<HEAPLIST32> ls_heaps(DWORD pid = 0);

        std::set<ULONG_PTR> ls_heapids(DWORD pid = 0);

        void refresh_heaps();

        HEAPLIST32 find_heap(ULONG_PTR heapid);

        std::vector<HEAPLIST32> find_heaps(DWORD pid);

        std::vector<HEAPENTRY32> find_heap_blocks(HEAPLIST32 heaplist32);

        std::vector<HEAPENTRY32> find_heap_blocks(ULONG_PTR heapid);

        std::vector<HEAPENTRY32> find_heap_blocks(DWORD pid);

        bool is_heap(HANDLE hProcess, void *address);

        bool is_heap(DWORD pid, void *address);

        // SE_DEBUG_NAME = TEXT("SeDebugPrivilege")
        static bool enable_privilege(HANDLE ProcessHandle,
                                     const wchar_t *szPrivilege = L"SeDebugPrivilege");

        // SE_DEBUG_NAME = TEXT("SeDebugPrivilege")
        static bool disable_privilege(HANDLE ProcessHandle,
                                      const wchar_t *szPrivilege = L"SeDebugPrivilege");

        // SE_DEBUG_NAME = TEXT("SeDebugPrivilege")
        static bool enable_privilege(DWORD ProcessID,
                                     const wchar_t *szPrivilege = L"SeDebugPrivilege");

        // SE_DEBUG_NAME = TEXT("SeDebugPrivilege")
        static bool disable_privilege(DWORD ProcessID,
                                      const wchar_t *szPrivilege = L"SeDebugPrivilege");

        // SE_DEBUG_NAME = TEXT("SeDebugPrivilege")
        static bool enable_debug(HANDLE ProcessHandle);

        // SE_DEBUG_NAME = TEXT("SeDebugPrivilege")
        static bool disable_debug(HANDLE ProcessHandle);

        // SE_SECURITY_NAME = TEXT("SeSecurityPrivilege")
        static bool enable_sacl(HANDLE ProcessHandle);

        // SE_SECURITY_NAME = TEXT("SeSecurityPrivilege")
        static bool disable_sacl(HANDLE ProcessHandle);
    };
}
#endif //PROC_H
