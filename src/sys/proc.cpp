//
// Created by forkernel on 2025/4/14.
//

#include "proc.h"
#include "../helper/string.h"

namespace YanLib::sys {
    proc::proc() {
        memset(&si, 0, sizeof(si));
        si.cb = sizeof(si);
        memset(&pi, 0, sizeof(pi));
    }

    proc::~proc() {
        if (hSnapshot != INVALID_HANDLE_VALUE) {
            CloseHandle(hSnapshot);
        }
        if (isCreated) {
            if (pi.hThread) {
                CloseHandle(pi.hThread);
            }
            if (pi.hProcess) {
                CloseHandle(pi.hProcess);
            }
        }
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

    HANDLE proc::thread_handle() const {
        if (isCreated) {
            return pi.hThread;
        }
        return nullptr;
    }

    HANDLE proc::proc_handle() const {
        if (isCreated) {
            return pi.hProcess;
        }
        return nullptr;
    }

    DWORD proc::thread_id() {
        if (isCreated) {
            DWORD id = GetThreadId(pi.hThread);
            if (!id) {
                error_code = GetLastError();
            }
            return id;
        }
        return 0;
    }

    DWORD proc::proc_id() {
        if (isCreated) {
            DWORD id = GetProcessId(pi.hProcess);
            if (!id) {
                error_code = GetLastError();
            }
            return id;
        }
        return 0;
    }

    bool proc::wait(DWORD dwMilliseconds) {
        if (isCreated) {
            DWORD dwRet = WaitForSingleObject(pi.hProcess, dwMilliseconds);
            if (dwRet == WAIT_OBJECT_0) {
                return true;
            }
            error_code = GetLastError();
        }
        return false;
    }

    bool proc::resume() {
        if (isCreated) {
            if (ResumeThread(pi.hThread) == -1) {
                error_code = GetLastError();
                return false;
            }
            return true;
        }
        return false;
    }

    std::vector<PROCESSENTRY32W> proc::ls_procs(DWORD pid) {
        if (!procs.empty()) {
            return procs;
        }
        if (hSnapshot != INVALID_HANDLE_VALUE) {
            CloseHandle(hSnapshot);
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

    std::set<DWORD> proc::ls_pids(DWORD pid) {
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
        return pids.contains(pid);
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

    HANDLE proc::pid_to_handle(DWORD pid) {
        return OpenProcess(PROCESS_ALL_ACCESS,
                           FALSE,
                           pid);
    }

    DWORD proc::handle_to_pid(HANDLE hProcess) {
        return GetProcessId(hProcess);
    }

    std::vector<THREADENTRY32> proc::ls_threads(DWORD pid) {
        if (!threads.empty()) {
            return threads;
        }
        if (hSnapshot != INVALID_HANDLE_VALUE) {
            CloseHandle(hSnapshot);
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

    std::set<DWORD> proc::ls_tids(DWORD pid) {
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
        return tids.contains(tid);
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

    std::set<HMODULE> proc::ls_hmodules(DWORD pid) {
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

    std::set<ULONG_PTR> proc::ls_heapids(DWORD pid) {
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
    proc::find_heap_blocks(HEAPLIST32 heaplist32) {
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
            error_code = GetLastError();
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
            error_code = GetLastError();
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

    bool proc::enable_privilege(HANDLE ProcessHandle,
                                const wchar_t *szPrivilege) {
        do {
            HANDLE hToken;
            if (!OpenProcessToken(ProcessHandle,
                                  TOKEN_ADJUST_PRIVILEGES,
                                  &hToken)) {
                break;
            }
            TOKEN_PRIVILEGES tp;
            tp.PrivilegeCount = 1;
            if (!LookupPrivilegeValueW(nullptr,
                                       szPrivilege,
                                       &tp.Privileges[0].Luid)) {
                break;
            }
            tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
            if (!AdjustTokenPrivileges(hToken,
                                       FALSE,
                                       &tp,
                                       sizeof(tp),
                                       nullptr,
                                       nullptr)) {
                break;
            }
            bool is_ok = (GetLastError() == ERROR_SUCCESS);
            CloseHandle(hToken);
            return is_ok;
        } while (false);
        return false;
    }

    bool proc::disable_privilege(HANDLE ProcessHandle,
                                 const wchar_t *szPrivilege) {
        do {
            HANDLE hToken;
            if (!OpenProcessToken(ProcessHandle,
                                  TOKEN_ADJUST_PRIVILEGES,
                                  &hToken)) {
                break;
            }
            TOKEN_PRIVILEGES tp;
            tp.PrivilegeCount = 1;
            if (!LookupPrivilegeValueW(nullptr,
                                       szPrivilege,
                                       &tp.Privileges[0].Luid)) {
                break;
            }
            tp.Privileges[0].Attributes = 0;
            if (!AdjustTokenPrivileges(hToken,
                                       FALSE,
                                       &tp,
                                       sizeof(tp),
                                       nullptr,
                                       nullptr)) {
                break;
            }
            bool is_ok = (GetLastError() == ERROR_SUCCESS);
            CloseHandle(hToken);
            return is_ok;
        } while (false);
        return false;
    }

    bool proc::enable_privilege(DWORD ProcessID, const wchar_t *szPrivilege) {
        do {
            HANDLE ProcessHandle = OpenProcess(PROCESS_ALL_ACCESS,
                                               FALSE,
                                               ProcessID);
            if (!ProcessHandle) {
                break;
            }
            return enable_privilege(ProcessHandle, szPrivilege);
        } while (false);
        return false;
    }

    bool proc::disable_privilege(DWORD ProcessID, const wchar_t *szPrivilege) {
        do {
            HANDLE ProcessHandle = OpenProcess(PROCESS_ALL_ACCESS,
                                               FALSE,
                                               ProcessID);
            if (!ProcessHandle) {
                break;
            }
            return enable_privilege(ProcessHandle, szPrivilege);
        } while (false);
        return false;
    }

    bool proc::enable_debug(HANDLE ProcessHandle) {
        return enable_privilege(ProcessHandle, L"SeDebugPrivilege");
    }

    bool proc::disable_debug(HANDLE ProcessHandle) {
        return disable_privilege(ProcessHandle, L"SeDebugPrivilege");
    }

    bool proc::enable_sacl(HANDLE ProcessHandle) {
        return enable_privilege(ProcessHandle, L"SeSecurityPrivilege");
    }

    bool proc::disable_sacl(HANDLE ProcessHandle) {
        return disable_privilege(ProcessHandle, L"SeSecurityPrivilege");
    }
}
