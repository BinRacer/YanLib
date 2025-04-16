//
// Created by forkernel on 2025/4/14.
//

#include "proc.h"

#include <algorithm>
#include <memory>

#include "security.h"
#include "helper/string.h"
#include "helper/convert.h"
#include "helper/autoclean.h"
#include <UserEnv.h>

#pragma comment(lib, "UserEnv.lib")

namespace YanLib::sys {
    proc::proc() {
        memset(&si, 0, sizeof(si));
        si.cb = sizeof(si);
        memset(&pi, 0, sizeof(pi));
    }

    proc::~proc() {
        if (hSnapshot != INVALID_HANDLE_VALUE) {
            CloseHandle(hSnapshot);
            hSnapshot = INVALID_HANDLE_VALUE;
        }
        if (isCreated) {
            if (pi.hThread) {
                CloseHandle(pi.hThread);
                pi.hThread = nullptr;
            }
            if (pi.hProcess) {
                CloseHandle(pi.hProcess);
                pi.hProcess = nullptr;
            }
        }
    }

    NTSTATUS proc::nt_query_info_proc(HANDLE ProcessHandle,
                                      PROCESSINFOCLASS ProcessInformationClass,
                                      PVOID ProcessInformation,
                                      ULONG ProcessInformationLength,
                                      PULONG ReturnLength) {
        typedef NTSTATUS (CALLBACK *pfn)(HANDLE ProcessHandle,
                                         PROCESSINFOCLASS ProcessInformationClass,
                                         PVOID ProcessInformation,
                                         ULONG ProcessInformationLength,
                                         PULONG ReturnLength OPTIONAL);
        NTSTATUS Status = -1;
        HMODULE hNTDLL = nullptr;
        do {
            hNTDLL = LoadLibraryW(L"ntdll.dll");
            if (!hNTDLL) {
                break;
            }
            pfn query_info_proc = reinterpret_cast<pfn>(
                GetProcAddress(hNTDLL, "NtQueryInformationProcess"));
            if (!query_info_proc) {
                break;
            }
            Status = query_info_proc(ProcessHandle,
                                     ProcessInformationClass,
                                     ProcessInformation,
                                     ProcessInformationLength,
                                     ReturnLength);
        } while (false);
        if (hNTDLL) {
            FreeLibrary(hNTDLL);
        }
        return Status;
    }

    bool proc::create(const wchar_t *lpApplicationName,
                      wchar_t *lpCommandLine,
                      LPSECURITY_ATTRIBUTES lpProcessAttributes,
                      LPSECURITY_ATTRIBUTES lpThreadAttributes,
                      BOOL bInheritHandles,
                      DWORD dwCreationFlags,
                      LPVOID lpEnvironment,
                      const wchar_t *lpCurrentDirectory) {
        if (isCreated) {
            return false;
        }
        if (!CreateProcessW(lpApplicationName,
                            lpCommandLine,
                            lpProcessAttributes,
                            lpThreadAttributes,
                            bInheritHandles,
                            dwCreationFlags,
                            lpEnvironment,
                            lpCurrentDirectory,
                            &si,
                            &pi)) {
            error_code = GetLastError();
            return false;
        }
        isCreated = true;
        return true;
    }

    bool proc::create_with_suspended(const wchar_t *lpApplicationName,
                                     wchar_t *lpCommandLine,
                                     LPSECURITY_ATTRIBUTES lpProcessAttributes,
                                     LPSECURITY_ATTRIBUTES lpThreadAttributes,
                                     BOOL bInheritHandles,
                                     DWORD dwCreationFlags,
                                     LPVOID lpEnvironment,
                                     const wchar_t *lpCurrentDirectory) {
        if (isCreated) {
            return false;
        }
        if (!CreateProcessW(lpApplicationName,
                            lpCommandLine,
                            lpProcessAttributes,
                            lpThreadAttributes,
                            bInheritHandles,
                            dwCreationFlags,
                            lpEnvironment,
                            lpCurrentDirectory,
                            &si,
                            &pi)) {
            error_code = GetLastError();
            return false;
        }
        isCreated = true;
        return true;
    }

    bool proc::create_as_user(HANDLE hToken,
                              const wchar_t *lpApplicationName,
                              wchar_t *lpCommandLine,
                              LPSECURITY_ATTRIBUTES lpProcessAttributes,
                              LPSECURITY_ATTRIBUTES lpThreadAttributes,
                              BOOL bInheritHandles,
                              DWORD dwCreationFlags,
                              LPVOID lpEnvironment,
                              const wchar_t *lpCurrentDirectory) {
        if (!CreateProcessAsUserW(hToken,
                                  lpApplicationName,
                                  lpCommandLine,
                                  lpProcessAttributes,
                                  lpThreadAttributes,
                                  bInheritHandles,
                                  dwCreationFlags,
                                  lpEnvironment,
                                  lpCurrentDirectory,
                                  &si,
                                  &pi)) {
            error_code = GetLastError();
            return false;
        }
        isCreated = true;
        return true;
    }

    bool proc::create_session_zero(const wchar_t *lpApplicationName,
                                   wchar_t *lpCommandLine,
                                   LPSECURITY_ATTRIBUTES lpProcessAttributes,
                                   LPSECURITY_ATTRIBUTES lpThreadAttributes,
                                   BOOL bInheritHandles,
                                   DWORD dwCreationFlags,
                                   LPVOID lpEnvironment,
                                   const wchar_t *lpCurrentDirectory) {
        security security;
        helper::autoclean<HANDLE> hToken(nullptr);
        hToken = security.copy_token();
        if (!hToken.is_ok()) {
            error_code = security.err_code();
            return false;
        }
        void *env = nullptr;
        if (lpEnvironment) {
            env = lpEnvironment;
        } else {
            env = security.create_env_block(hToken);
            if (!env) {
                error_code = security.err_code();
                return false;
            }
        }
        if (!CreateProcessAsUserW(hToken,
                                  lpApplicationName,
                                  lpCommandLine,
                                  lpProcessAttributes,
                                  lpThreadAttributes,
                                  bInheritHandles,
                                  dwCreationFlags,
                                  env,
                                  lpCurrentDirectory,
                                  &si,
                                  &pi)) {
            error_code = GetLastError();
            if (!security.clear_env_block(env)) {
                error_code = security.err_code();
            }
            return false;
        }
        isCreated = true;
        if (!security.clear_env_block(env)) {
            error_code = security.err_code();
        }
        return true;
    }

    bool proc::win_exec(const char *lpCmdLine, UINT uCmdShow) {
        UINT uiRet = WinExec(lpCmdLine, uCmdShow);
        if (uiRet <= 31 && uiRet > 0) {
            error_code = uiRet;
        } else if (uiRet == 0) {
            error_code = ERROR_NOT_ENOUGH_SERVER_MEMORY;
        }
        if (uiRet > 31) {
            return true;
        }
        return false;
    }

    bool proc::shell_exec(const wchar_t *lpFile,
                          const wchar_t *lpParameters,
                          const wchar_t *lpDirectory,
                          INT nShowCmd,
                          HWND hwnd,
                          const wchar_t *lpOperation) {
        HINSTANCE hInstance = ShellExecuteW(hwnd,
                                            lpOperation,
                                            lpFile,
                                            lpParameters,
                                            lpDirectory,
                                            nShowCmd);
        auto uiRet = reinterpret_cast<uintptr_t>(hInstance);
        uiRet = uiRet & 0x00000000FFFFFFFF;
        if (uiRet <= 32 && uiRet > 0) {
            error_code = uiRet;
        } else if (uiRet == 0) {
            error_code = ERROR_NOT_ENOUGH_SERVER_MEMORY;
        }
        if (uiRet > 32) {
            return true;
        }
        return false;
    }

    HANDLE proc::child_thread_handle() const {
        if (isCreated) {
            return pi.hThread;
        }
        return nullptr;
    }

    HANDLE proc::child_proc_handle() const {
        if (isCreated) {
            return pi.hProcess;
        }
        return nullptr;
    }

    DWORD proc::child_thread_id() {
        if (isCreated) {
            DWORD id = GetThreadId(pi.hThread);
            if (!id) {
                error_code = GetLastError();
            }
            return id;
        }
        return 0;
    }

    DWORD proc::child_proc_id() {
        if (isCreated) {
            DWORD id = GetProcessId(pi.hProcess);
            if (!id) {
                error_code = GetLastError();
            }
            return id;
        }
        return 0;
    }

    bool proc::wait_child(DWORD dwMilliseconds) {
        if (isCreated) {
            DWORD dwRet = WaitForSingleObject(pi.hProcess, dwMilliseconds);
            if (dwRet == WAIT_OBJECT_0) {
                return true;
            }
            error_code = GetLastError();
        }
        return false;
    }

    bool proc::resume_child() {
        if (isCreated) {
            if (ResumeThread(pi.hThread) == -1) {
                error_code = GetLastError();
                return false;
            }
            return true;
        }
        return false;
    }

    HANDLE proc::curr_thread_handle() {
        return GetCurrentThread();
    }

    HANDLE proc::curr_proc_handle() {
        return GetCurrentProcess();
    }

    DWORD proc::curr_thread_id() {
        return GetCurrentThreadId();
    }

    DWORD proc::curr_proc_id() {
        return GetCurrentProcessId();
    }

    HANDLE proc::pid_to_handle(DWORD pid) {
        HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS,
                                      FALSE,
                                      pid);
        if (!hProcess) {
            error_code = GetLastError();
        }
        return hProcess;
    }

    DWORD proc::handle_to_pid(HANDLE hProcess) {
        DWORD pid = GetProcessId(hProcess);
        if (!pid) {
            error_code = GetLastError();
        }
        return pid;
    }

    std::vector<PROCESSENTRY32W> proc::ls_procs(DWORD pid) {
        if (!procs.empty()) {
            return procs;
        }
        if (hSnapshot != INVALID_HANDLE_VALUE) {
            CloseHandle(hSnapshot);
            hSnapshot = INVALID_HANDLE_VALUE;
        }
        PROCESSENTRY32W pe = {sizeof(PROCESSENTRY32W)};
        do {
            hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,
                                                 pid);
            if (hSnapshot == INVALID_HANDLE_VALUE) {
                error_code = GetLastError();
                break;
            }
            if (!Process32FirstW(hSnapshot, &pe)) {
                error_code = GetLastError();
                break;
            }
            procs.push_back(pe);
            while (Process32NextW(hSnapshot, &pe)) {
                procs.push_back(pe);
            }
        } while (false);
        return procs;
    }

    std::unordered_set<DWORD> proc::ls_pids(DWORD pid) {
        if (!pids.empty()) {
            return pids;
        }
        if (!procs.empty()) {
            for (auto process: procs) {
                pids.insert(process.th32ProcessID);
            }
            return pids;
        }
        if (hSnapshot != INVALID_HANDLE_VALUE) {
            CloseHandle(hSnapshot);
            hSnapshot = INVALID_HANDLE_VALUE;
        }
        PROCESSENTRY32W pe = {sizeof(PROCESSENTRY32W)};
        do {
            hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,
                                                 pid);
            if (hSnapshot == INVALID_HANDLE_VALUE) {
                error_code = GetLastError();
                break;
            }
            if (!Process32FirstW(hSnapshot, &pe)) {
                error_code = GetLastError();
                break;
            }
            pids.insert(pe.th32ProcessID);
            while (Process32NextW(hSnapshot, &pe)) {
                pids.insert(pe.th32ProcessID);
            }
        } while (false);
        return pids;
    }

    void proc::refresh_procs() {
        procs.clear();
        pids.clear();
    }

    bool proc::pid_exists(DWORD pid) {
        if (pids.empty()) {
            ls_pids();
        }
        return pids.find(pid) != pids.end();
    }

    DWORD proc::get_ppid(DWORD pid) {
        if (procs.empty()) {
            ls_procs();
        }
        for (auto process: procs) {
            if (process.th32ProcessID == pid) {
                return process.th32ParentProcessID;
            }
        }
        return 0;
    }

    PROCESSENTRY32W proc::find_proc(DWORD pid) {
        if (procs.empty()) {
            ls_procs();
        }
        for (auto process: procs) {
            if (process.th32ProcessID == pid) {
                return process;
            }
        }
        return {};
    }

    PROCESSENTRY32W proc::find_proc(const wchar_t *lpProcessName) {
        if (!lpProcessName || wcslen(lpProcessName) == 0) {
            return {};
        }
        if (procs.empty()) {
            ls_procs();
        }
        for (auto process: procs) {
            if (helper::string::strstr_case_insen(process.szExeFile,
                                                  lpProcessName)) {
                return process;
            }
        }
        return {};
    }

    std::vector<THREADENTRY32> proc::ls_threads(DWORD pid) {
        if (!threads.empty()) {
            return threads;
        }
        if (hSnapshot != INVALID_HANDLE_VALUE) {
            CloseHandle(hSnapshot);
            hSnapshot = INVALID_HANDLE_VALUE;
        }
        THREADENTRY32 te = {sizeof(THREADENTRY32)};
        do {
            hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD,
                                                 pid);
            if (hSnapshot == INVALID_HANDLE_VALUE) {
                error_code = GetLastError();
                break;
            }
            if (!Thread32First(hSnapshot, &te)) {
                error_code = GetLastError();
                break;
            }
            threads.push_back(te);
            while (Thread32Next(hSnapshot, &te)) {
                threads.push_back(te);
            }
        } while (false);
        return threads;
    }

    std::unordered_set<DWORD> proc::ls_tids(DWORD pid) {
        if (!tids.empty()) {
            return tids;
        }
        if (!threads.empty()) {
            for (auto thread: threads) {
                tids.insert(thread.th32ThreadID);
            }
            return tids;
        }
        if (hSnapshot != INVALID_HANDLE_VALUE) {
            CloseHandle(hSnapshot);
            hSnapshot = INVALID_HANDLE_VALUE;
        }
        THREADENTRY32 te = {sizeof(THREADENTRY32)};
        do {
            hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD,
                                                 pid);
            if (hSnapshot == INVALID_HANDLE_VALUE) {
                error_code = GetLastError();
                break;
            }
            if (!Thread32First(hSnapshot, &te)) {
                error_code = GetLastError();
                break;
            }
            tids.insert(te.th32ThreadID);
            while (Thread32Next(hSnapshot, &te)) {
                tids.insert(te.th32ThreadID);
            }
        } while (false);
        return tids;
    }

    void proc::refresh_threads() {
        threads.clear();
        tids.clear();
    }

    bool proc::tid_exists(DWORD tid) {
        if (tids.empty()) {
            ls_tids();
        }
        return tids.find(tid) != tids.end();
    }

    DWORD proc::get_pid(DWORD tid) {
        if (threads.empty()) {
            ls_threads();
        }
        for (auto thread: threads) {
            if (thread.th32ThreadID == tid) {
                return thread.th32OwnerProcessID;
            }
        }
        return 0;
    }

    THREADENTRY32 proc::find_thread(DWORD tid) {
        if (threads.empty()) {
            ls_threads();
        }
        for (auto thread: threads) {
            if (thread.th32ThreadID == tid) {
                return thread;
            }
        }
        return {};
    }

    std::vector<THREADENTRY32> proc::find_threads(DWORD pid) {
        if (threads.empty()) {
            ls_threads();
        }
        std::vector<THREADENTRY32> result;
        for (auto thread: threads) {
            if (thread.th32OwnerProcessID == pid) {
                result.push_back(thread);
            }
        }
        return result;
    }


    std::vector<MODULEENTRY32W> proc::ls_modules(DWORD pid) {
        if (!modules.empty()) {
            return modules;
        }
        if (hSnapshot != INVALID_HANDLE_VALUE) {
            CloseHandle(hSnapshot);
            hSnapshot = INVALID_HANDLE_VALUE;
        }
        MODULEENTRY32W me = {sizeof(MODULEENTRY32W)};
        do {
            hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE,
                                                 pid);
            if (hSnapshot == INVALID_HANDLE_VALUE) {
                error_code = GetLastError();
                break;
            }
            if (!Module32FirstW(hSnapshot, &me)) {
                error_code = GetLastError();
                break;
            }
            modules.push_back(me);
            while (Module32NextW(hSnapshot, &me)) {
                modules.push_back(me);
            }
        } while (false);
        return modules;
    }

    std::unordered_set<HMODULE> proc::ls_hmodules(DWORD pid) {
        if (!hmodules.empty()) {
            return hmodules;
        }
        if (!modules.empty()) {
            for (auto module: modules) {
                hmodules.insert(module.hModule);
            }
            return hmodules;
        }
        if (hSnapshot != INVALID_HANDLE_VALUE) {
            CloseHandle(hSnapshot);
            hSnapshot = INVALID_HANDLE_VALUE;
        }
        MODULEENTRY32W me = {sizeof(MODULEENTRY32W)};
        do {
            hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE,
                                                 pid);
            if (hSnapshot == INVALID_HANDLE_VALUE) {
                error_code = GetLastError();
                break;
            }
            if (!Module32FirstW(hSnapshot, &me)) {
                error_code = GetLastError();
                break;
            }
            hmodules.insert(me.hModule);
            while (Module32NextW(hSnapshot, &me)) {
                hmodules.insert(me.hModule);
            }
        } while (false);
        return hmodules;
    }

    void proc::refresh_modules() {
        modules.clear();
        hmodules.clear();
    }

    MODULEENTRY32W proc::find_module(const wchar_t *lpProcessName) {
        if (!lpProcessName || wcslen(lpProcessName) == 0) {
            return {};
        }
        if (modules.empty()) {
            ls_modules();
        }
        for (auto module: modules) {
            if (helper::string::strstr_case_insen(module.szModule,
                                                  lpProcessName) ||
                helper::string::strstr_case_insen(module.szExePath,
                                                  lpProcessName)) {
                return module;
            }
        }
        return {};
    }

    MODULEENTRY32W proc::find_module(const void *address) {
        if (!address) {
            return {};
        }
        if (modules.empty()) {
            ls_modules();
        }
        for (auto module: modules) {
            if (module.modBaseAddr == address) {
                return module;
            }
        }
        return {};
    }

    std::vector<HEAPLIST32> proc::ls_heaps(DWORD pid) {
        if (!heaps.empty()) {
            return heaps;
        }
        if (hSnapshot != INVALID_HANDLE_VALUE) {
            CloseHandle(hSnapshot);
            hSnapshot = INVALID_HANDLE_VALUE;
        }
        HEAPLIST32 he = {sizeof(HEAPLIST32)};
        do {
            hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPHEAPLIST,
                                                 pid);
            if (hSnapshot == INVALID_HANDLE_VALUE) {
                error_code = GetLastError();
                break;
            }
            if (!Heap32ListFirst(hSnapshot, &he)) {
                error_code = GetLastError();
                break;
            }
            heaps.push_back(he);
            while (Heap32ListNext(hSnapshot, &he)) {
                heaps.push_back(he);
            }
        } while (false);
        return heaps;
    }

    std::unordered_set<ULONG_PTR> proc::ls_heapids(DWORD pid) {
        if (!heapids.empty()) {
            return heapids;
        }
        if (!heaps.empty()) {
            for (auto heap: heaps) {
                heapids.insert(heap.th32HeapID);
            }
            return heapids;
        }
        if (hSnapshot != INVALID_HANDLE_VALUE) {
            CloseHandle(hSnapshot);
            hSnapshot = INVALID_HANDLE_VALUE;
        }
        HEAPLIST32 he = {sizeof(HEAPLIST32)};
        do {
            hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPHEAPLIST,
                                                 pid);
            if (hSnapshot == INVALID_HANDLE_VALUE) {
                error_code = GetLastError();
                break;
            }
            if (!Heap32ListFirst(hSnapshot, &he)) {
                error_code = GetLastError();
                break;
            }
            heapids.insert(he.th32HeapID);
            while (Heap32ListNext(hSnapshot, &he)) {
                heapids.insert(he.th32HeapID);
            }
        } while (false);
        return heapids;
    }

    void proc::refresh_heaps() {
        heaps.clear();
        heapids.clear();
    }

    HEAPLIST32 proc::find_heap(ULONG_PTR heapid) {
        if (heaps.empty()) {
            ls_heaps();
        }
        for (auto heap: heaps) {
            if (heap.th32HeapID == heapid) {
                return heap;
            }
        }
        return {};
    }

    std::vector<HEAPLIST32> proc::find_heaps(DWORD pid) {
        if (heaps.empty()) {
            ls_heaps();
        }
        std::vector<HEAPLIST32> result;
        for (auto heap: heaps) {
            if (heap.th32ProcessID == pid) {
                result.push_back(heap);
            }
        }
        return result;
    }

    std::vector<HEAPENTRY32>
    proc::find_heap_blocks(HEAPLIST32 &heaplist32) {
        HEAPENTRY32 he = {sizeof(HEAPENTRY32)};
        std::vector<HEAPENTRY32> result;
        do {
            if (!Heap32First(&he, heaplist32.th32ProcessID, heaplist32.th32HeapID)) {
                error_code = GetLastError();
                break;
            }
            result.push_back(he);
            while (Heap32Next(&he)) {
                result.push_back(he);
            }
        } while (false);
        return result;
    }

    std::vector<HEAPENTRY32> proc::find_heap_blocks(ULONG_PTR heapid) {
        HEAPENTRY32 he = {sizeof(HEAPENTRY32)};
        std::vector<HEAPENTRY32> result;
        do {
            HEAPLIST32 heaplist32 = find_heap(heapid);
            if (!Heap32First(&he, heaplist32.th32ProcessID, heapid)) {
                error_code = GetLastError();
                break;
            }
            result.push_back(he);
            while (Heap32Next(&he)) {
                result.push_back(he);
            }
        } while (false);
        return result;
    }

    std::vector<HEAPENTRY32> proc::find_heap_blocks(DWORD pid) {
        HEAPENTRY32 he = {sizeof(HEAPENTRY32)};
        std::vector<HEAPENTRY32> result;
        do {
            auto heaplists = find_heaps(pid);
            if (heaplists.empty()) {
                break;
            }
            for (auto heaplist: heaplists) {
                if (!Heap32First(&he, heaplist.th32ProcessID, heaplist.th32HeapID)) {
                    error_code = GetLastError();
                    break;
                }
                result.push_back(he);
                while (Heap32Next(&he)) {
                    result.push_back(he);
                }
            }
        } while (false);
        return result;
    }

    bool proc::is_heap(HANDLE hProcess, void *address) {
        if (!hProcess) {
            return false;
        }
        const DWORD pid = handle_to_pid(hProcess);
        if (!pid) {
            return false;
        }
        std::vector<HEAPENTRY32> blocks = find_heap_blocks(pid);
        if (blocks.empty()) {
            return false;
        }
        for (auto block: blocks) {
            MEMORY_BASIC_INFORMATION mbi;
            if (!VirtualQueryEx(hProcess,
                                reinterpret_cast<void *>(block.dwAddress),
                                &mbi,
                                sizeof(mbi))) {
                error_code = GetLastError();
                break;
            }
            if (address >= static_cast<uint8_t *>(mbi.AllocationBase) &&
                address <= static_cast<uint8_t *>(mbi.AllocationBase) + mbi.RegionSize) {
                return true;
            }
        }
        return false;
    }

    bool proc::is_heap(DWORD pid, void *address) {
        HANDLE hProc = nullptr;
        if (GetCurrentProcessId() == pid) {
            hProc = GetCurrentProcess();
        } else {
            hProc = pid_to_handle(pid);
        }
        if (!hProc) {
            return false;
        }
        std::vector<HEAPENTRY32> blocks = find_heap_blocks(pid);
        if (blocks.empty()) {
            return false;
        }
        for (auto block: blocks) {
            MEMORY_BASIC_INFORMATION mbi;
            if (!VirtualQueryEx(hProc,
                                reinterpret_cast<void *>(block.dwAddress),
                                &mbi,
                                sizeof(mbi))) {
                error_code = GetLastError();
                break;
            }
            if (address >= static_cast<uint8_t *>(mbi.AllocationBase) &&
                address <= static_cast<uint8_t *>(mbi.AllocationBase) + mbi.RegionSize) {
                return true;
            }
        }
        return false;
    }

    std::string proc::get_proc_name(HANDLE hProcess) {
        HANDLE hProc = hProcess ? hProcess : GetCurrentProcess();
        std::string name(MAX_PATH, '\0');
        DWORD dwSize = 0;
        if (!QueryFullProcessImageNameA(hProc,
                                        0,
                                        name.data(),
                                        &dwSize)) {
            error_code = GetLastError();
            return {};
        }
        name.resize(dwSize);
        return name;
    }

    std::wstring proc::get_proc_name_wide(HANDLE hProcess) {
        HANDLE hProc = hProcess ? hProcess : GetCurrentProcess();
        std::wstring name(MAX_PATH, L'\0');
        DWORD dwSize = 0;
        if (!QueryFullProcessImageNameW(hProc,
                                        0,
                                        name.data(),
                                        &dwSize)) {
            error_code = GetLastError();
            return {};
        }
        name.resize(dwSize);
        return name;
    }

    bool proc::runas_elevated_proc(const wchar_t *appName,
                                   const wchar_t *cmdline) {
        SHELLEXECUTEINFOW sei = {sizeof(SHELLEXECUTEINFO)};
        sei.lpVerb = L"runas";
        sei.lpFile = appName;
        sei.lpParameters = cmdline;
        sei.nShow = SW_SHOWNORMAL;
        if (!ShellExecuteExW(&sei)) {
            error_code = GetLastError();
        }
        return true;
    }

    void proc::kill_curr_proc(UINT ExitCode) {
        ExitProcess(ExitCode);
    }

    void *proc::get_module_image_base(MODULEENTRY32W &mEntry) {
        IMAGE_DOS_HEADER dos_header{};
        IMAGE_NT_HEADERS64 nt_headers64{};
        IMAGE_NT_HEADERS32 nt_headers32{};
        do {
            if (!Toolhelp32ReadProcessMemory(mEntry.th32ProcessID,
                                             mEntry.modBaseAddr,
                                             &dos_header,
                                             sizeof(dos_header),
                                             nullptr)) {
                break;
            }
            if (dos_header.e_magic != IMAGE_DOS_SIGNATURE) {
                break;
            }
            if (!Toolhelp32ReadProcessMemory(mEntry.th32ProcessID,
                                             mEntry.modBaseAddr + dos_header.e_lfanew,
                                             &nt_headers64,
                                             sizeof(nt_headers64),
                                             nullptr)) {
                break;
            }
            if (nt_headers64.Signature != IMAGE_NT_SIGNATURE) {
                break;
            }

            if (nt_headers64.FileHeader.Machine == IMAGE_FILE_MACHINE_AMD64 ||
                nt_headers64.FileHeader.Machine == IMAGE_FILE_MACHINE_ARM64) {
                return reinterpret_cast<void *>(nt_headers64.OptionalHeader.ImageBase);
            } else {
                if (!Toolhelp32ReadProcessMemory(mEntry.th32ProcessID,
                                                 mEntry.modBaseAddr + dos_header.e_lfanew,
                                                 &nt_headers32,
                                                 sizeof(nt_headers32),
                                                 nullptr)) {
                    break;
                }
                if (nt_headers32.Signature != IMAGE_NT_SIGNATURE) {
                    break;
                }
                return reinterpret_cast<void *>(
                    static_cast<int64_t>(
                        nt_headers32.OptionalHeader.ImageBase));
            }
        } while (false);
        return nullptr;
    }

    void *proc::get_curr_proc_image_base() {
        IMAGE_DOS_HEADER dos_header{};
        IMAGE_NT_HEADERS64 nt_headers64{};
        IMAGE_NT_HEADERS32 nt_headers32{};
        do {
            HMODULE hmodule = GetModuleHandleW(nullptr);
            if (!hmodule) {
                error_code = GetLastError();
                break;
            }
            auto *base = reinterpret_cast<uint8_t *>(hmodule);
            memcpy(&dos_header, base, sizeof(dos_header));
            if (dos_header.e_magic != IMAGE_DOS_SIGNATURE) {
                break;
            }
            memcpy(&nt_headers64,
                   base + dos_header.e_lfanew,
                   sizeof(nt_headers64));
            if (nt_headers64.Signature != IMAGE_NT_SIGNATURE) {
                break;
            }
            if (nt_headers64.FileHeader.Machine == IMAGE_FILE_MACHINE_AMD64 ||
                nt_headers64.FileHeader.Machine == IMAGE_FILE_MACHINE_ARM64) {
                return reinterpret_cast<void *>(nt_headers64.OptionalHeader.ImageBase);
            } else {
                memcpy(&nt_headers32,
                       base + dos_header.e_lfanew,
                       sizeof(nt_headers32));
                if (nt_headers32.Signature != IMAGE_NT_SIGNATURE) {
                    break;
                }
                return reinterpret_cast<void *>(
                    static_cast<int64_t>(
                        nt_headers32.OptionalHeader.ImageBase));
            }
        } while (false);
        return nullptr;
    }

    void *proc::get_proc_image_base(HANDLE hProcess) {
        HANDLE hProc = hProcess ? hProcess : GetCurrentProcess();
        PROCESS_BASIC_INFORMATION pbi;
        NTSTATUS status = nt_query_info_proc(hProc,
                                             ProcessBasicInformation,
                                             &pbi,
                                             sizeof(PROCESS_BASIC_INFORMATION),
                                             nullptr);
        if (!NT_SUCCESS(status)) {
            return nullptr;
        }
        void *baseAddr = pbi.PebBaseAddress->Reserved3[1];
        return baseAddr;
    }

    void *proc::get_proc_image_base(DWORD pid) {
        return get_proc_image_base(pid_to_handle(pid));
    }

    std::string proc::get_proc_cmdline(HANDLE hProcess) {
        std::wstring result = get_proc_cmdline_wide(hProcess);
        return helper::convert::wstr_to_str(result);
    }

    std::wstring proc::get_proc_cmdline_wide(HANDLE hProcess) {
        HANDLE hProc = hProcess ? hProcess : GetCurrentProcess();
        DWORD dwSize = 0;
        PROCESS_BASIC_INFORMATION pbi{};
        do {
            NTSTATUS status = nt_query_info_proc(hProc,
                                                 ProcessBasicInformation,
                                                 &pbi,
                                                 sizeof(pbi),
                                                 &dwSize);
            if (!NT_SUCCESS(status)) {
                break;
            }
            auto peb = std::make_unique<_peb>();
            size_t size = dwSize;
            if (!ReadProcessMemory(hProc,
                                   pbi.PebBaseAddress,
                                   peb.get(),
                                   sizeof(_peb),
                                   &size)) {
                error_code = GetLastError();
                break;
            }
            auto block = std::make_unique<_infoBlock>();
            if (!ReadProcessMemory(hProc,
                                   peb->InfoBlockAddress,
                                   block.get(),
                                   sizeof(_infoBlock),
                                   &size)) {
                error_code = GetLastError();
                break;
            }
            std::vector<wchar_t> cmdline(MAX_PATH + 1, L'\0');
            if (!ReadProcessMemory(hProc,
                                   block->wszCmdLineAddress,
                                   cmdline.data(),
                                   cmdline.size(),
                                   &size)) {
                error_code = GetLastError();
                break;
            }
            cmdline.resize(size);
            cmdline.shrink_to_fit();
            return cmdline.data();
        } while (false);
        return {};
    }

    std::string proc::get_proc_cmdline(DWORD pid) {
        return get_proc_cmdline(pid_to_handle(pid));
    }

    std::wstring proc::get_proc_cmdline_wide(DWORD pid) {
        return get_proc_cmdline_wide(pid_to_handle(pid));
    }

    std::string proc::get_proc_owner(HANDLE hProcess) {
        std::wstring result = get_proc_owner_wide(hProcess);
        return helper::convert::wstr_to_str(result);
    }

    std::wstring proc::get_proc_owner_wide(HANDLE hProcess) {
        HANDLE hProc = hProcess ? hProcess : GetCurrentProcess();
        helper::autoclean<HANDLE> hToken(nullptr);
        std::wstring result;
        security security;
        do {
            if (security.enable_privilege(GetCurrentProcess(),
                                          L"SeTcbPrivilege")) {
                break;
            }
            if (!OpenProcessToken(hProc,
                                  TOKEN_QUERY,
                                  hToken)) {
                error_code = GetLastError();
                break;
            }
            DWORD dwSize = 0;
            GetTokenInformation(hToken,
                                TokenUser,
                                nullptr,
                                0,
                                &dwSize);
            error_code = GetLastError();
            if (error_code != ERROR_INSUFFICIENT_BUFFER) {
                break;
            }
            std::vector<uint8_t> token_user(dwSize, 0);
            if (!GetTokenInformation(hToken,
                                     TokenUser,
                                     token_user.data(),
                                     token_user.size(),
                                     &dwSize)) {
                error_code = GetLastError();
                break;
            }
            SID_NAME_USE snu;
            TCHAR szUser[MAX_PATH];
            DWORD chUser = MAX_PATH;
            PDWORD pcchUser = &chUser;
            TCHAR szDomain[MAX_PATH];
            DWORD chDomain = MAX_PATH;
            PDWORD pcchDomain = &chDomain;
            if (!LookupAccountSidW(nullptr,
                                   reinterpret_cast<PTOKEN_USER>(
                                       token_user.data())->User.Sid,
                                   szUser,
                                   pcchUser,
                                   szDomain,
                                   pcchDomain,
                                   &snu)) {
                error_code = GetLastError();
                break;
            }
            result.assign(L"\\\\");
            result.append(szDomain);
            result.append(L"\\");
            result.append(szUser);
            if (security.disable_privilege(GetCurrentProcess(),
                                           L"SeTcbPrivilege")) {
                break;
            }
        } while (false);
        return result;
    }

    std::string proc::get_proc_owner(DWORD pid) {
        return get_proc_owner(pid_to_handle(pid));
    }

    std::wstring proc::get_proc_owner_wide(DWORD pid) {
        return get_proc_owner_wide(pid_to_handle(pid));
    }

    DWORD proc::err_code() const {
        return error_code;
    }

    std::string proc::err_string() const {
        std::string result = helper::convert::err_string(error_code);
        return result;
    }

    std::wstring proc::err_wstring() const {
        std::wstring result = helper::convert::err_wstring(error_code);
        return result;
    }
}
