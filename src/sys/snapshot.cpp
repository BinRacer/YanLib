/* clang-format off */
/*
 * @file snapshot.cpp
 * @date 2025-04-22
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
#include "snapshot.h"
#include "helper/string.h"
#include "helper/convert.h"

namespace YanLib::sys {
    snapshot::~snapshot() {
        cleanup();
    }

    void snapshot::cleanup() {
        if (snapshot_handle != INVALID_HANDLE_VALUE) {
            CloseHandle(snapshot_handle);
            snapshot_handle = INVALID_HANDLE_VALUE;
        }
    }

    std::vector<PROCESSENTRY32W> snapshot::ls_procs(const uint32_t pid) {
        if (!procs.empty()) {
            return procs;
        }
        cleanup();
        PROCESSENTRY32W pe = {sizeof(PROCESSENTRY32W)};
        do {
            snapshot_handle = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, pid);
            if (snapshot_handle == INVALID_HANDLE_VALUE) {
                error_code = GetLastError();
                break;
            }
            if (!Process32FirstW(snapshot_handle, &pe)) {
                error_code = GetLastError();
                break;
            }
            procs.push_back(pe);
            while (Process32NextW(snapshot_handle, &pe)) {
                procs.push_back(pe);
            }
        } while (false);
        return procs;
    }

    std::unordered_set<uint32_t> snapshot::ls_pids(const uint32_t pid) {
        if (!pids.empty()) {
            return pids;
        }
        if (!procs.empty()) {
            for (const auto process : procs) {
                pids.insert(process.th32ProcessID);
            }
            return pids;
        }
        cleanup();
        PROCESSENTRY32W pe = {sizeof(PROCESSENTRY32W)};
        do {
            snapshot_handle = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, pid);
            if (snapshot_handle == INVALID_HANDLE_VALUE) {
                error_code = GetLastError();
                break;
            }
            if (!Process32FirstW(snapshot_handle, &pe)) {
                error_code = GetLastError();
                break;
            }
            pids.insert(pe.th32ProcessID);
            while (Process32NextW(snapshot_handle, &pe)) {
                pids.insert(pe.th32ProcessID);
            }
        } while (false);
        return pids;
    }

    void snapshot::refresh_procs() {
        procs.clear();
        pids.clear();
    }

    bool snapshot::pid_exists(const uint32_t pid) {
        if (pids.empty()) {
            ls_pids();
        }
        return pids.find(pid) != pids.end();
    }

    uint32_t snapshot::get_ppid(const uint32_t pid) {
        if (procs.empty()) {
            ls_procs();
        }
        for (const auto process : procs) {
            if (process.th32ProcessID == pid) {
                return process.th32ParentProcessID;
            }
        }
        return 0;
    }

    PROCESSENTRY32W snapshot::find_proc(const uint32_t pid) {
        if (procs.empty()) {
            ls_procs();
        }
        for (const auto process : procs) {
            if (process.th32ProcessID == pid) {
                return process;
            }
        }
        return {};
    }

    PROCESSENTRY32W snapshot::find_proc(const wchar_t *proc_name) {
        if (!proc_name || wcslen(proc_name) == 0) {
            return {};
        }
        if (procs.empty()) {
            ls_procs();
        }
        for (const auto process : procs) {
            if (helper::string::strstri(process.szExeFile, proc_name)) {
                return process;
            }
        }
        return {};
    }

    std::vector<THREADENTRY32> snapshot::ls_threads(const uint32_t pid) {
        if (!threads.empty()) {
            return threads;
        }
        cleanup();
        THREADENTRY32 te = {sizeof(THREADENTRY32)};
        do {
            snapshot_handle = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, pid);
            if (snapshot_handle == INVALID_HANDLE_VALUE) {
                error_code = GetLastError();
                break;
            }
            if (!Thread32First(snapshot_handle, &te)) {
                error_code = GetLastError();
                break;
            }
            threads.push_back(te);
            while (Thread32Next(snapshot_handle, &te)) {
                threads.push_back(te);
            }
        } while (false);
        return threads;
    }

    std::unordered_set<uint32_t> snapshot::ls_thread_ids(const uint32_t pid) {
        if (!thread_ids.empty()) {
            return thread_ids;
        }
        if (!threads.empty()) {
            for (const auto thread : threads) {
                thread_ids.insert(thread.th32ThreadID);
            }
            return thread_ids;
        }
        cleanup();
        THREADENTRY32 te = {sizeof(THREADENTRY32)};
        do {
            snapshot_handle = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, pid);
            if (snapshot_handle == INVALID_HANDLE_VALUE) {
                error_code = GetLastError();
                break;
            }
            if (!Thread32First(snapshot_handle, &te)) {
                error_code = GetLastError();
                break;
            }
            thread_ids.insert(te.th32ThreadID);
            while (Thread32Next(snapshot_handle, &te)) {
                thread_ids.insert(te.th32ThreadID);
            }
        } while (false);
        return thread_ids;
    }

    void snapshot::refresh_threads() {
        threads.clear();
        thread_ids.clear();
    }

    bool snapshot::tid_exists(uint32_t tid) {
        if (thread_ids.empty()) {
            ls_thread_ids();
        }
        return thread_ids.find(tid) != thread_ids.end();
    }

    uint32_t snapshot::tid_to_pid(uint32_t tid) {
        if (threads.empty()) {
            ls_threads();
        }
        for (const auto thread : threads) {
            if (thread.th32ThreadID == tid) {
                return thread.th32OwnerProcessID;
            }
        }
        return 0;
    }

    THREADENTRY32 snapshot::find_thread(uint32_t tid) {
        if (threads.empty()) {
            ls_threads();
        }
        for (const auto thread : threads) {
            if (thread.th32ThreadID == tid) {
                return thread;
            }
        }
        return {};
    }

    std::vector<THREADENTRY32> snapshot::find_threads(const uint32_t pid) {
        if (threads.empty()) {
            ls_threads();
        }
        std::vector<THREADENTRY32> result;
        for (auto thread : threads) {
            if (thread.th32OwnerProcessID == pid) {
                result.push_back(thread);
            }
        }
        return result;
    }

    std::vector<MODULEENTRY32W> snapshot::ls_modules(const uint32_t pid) {
        if (!modules.empty()) {
            return modules;
        }
        cleanup();
        MODULEENTRY32W me = {sizeof(MODULEENTRY32W)};
        do {
            snapshot_handle = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, pid);
            if (snapshot_handle == INVALID_HANDLE_VALUE) {
                error_code = GetLastError();
                break;
            }
            if (!Module32FirstW(snapshot_handle, &me)) {
                error_code = GetLastError();
                break;
            }
            modules.push_back(me);
            while (Module32NextW(snapshot_handle, &me)) {
                modules.push_back(me);
            }
        } while (false);
        return modules;
    }

    std::unordered_set<HMODULE>
    snapshot::ls_module_handles(const uint32_t pid) {
        if (!module_handles.empty()) {
            return module_handles;
        }
        if (!modules.empty()) {
            for (auto module : modules) {
                module_handles.insert(module.hModule);
            }
            return module_handles;
        }
        cleanup();
        MODULEENTRY32W me = {sizeof(MODULEENTRY32W)};
        do {
            snapshot_handle = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, pid);
            if (snapshot_handle == INVALID_HANDLE_VALUE) {
                error_code = GetLastError();
                break;
            }
            if (!Module32FirstW(snapshot_handle, &me)) {
                error_code = GetLastError();
                break;
            }
            module_handles.insert(me.hModule);
            while (Module32NextW(snapshot_handle, &me)) {
                module_handles.insert(me.hModule);
            }
        } while (false);
        return module_handles;
    }

    void snapshot::refresh_modules() {
        modules.clear();
        module_handles.clear();
    }

    MODULEENTRY32W snapshot::find_module(const wchar_t *proc_name) {
        if (!proc_name || wcslen(proc_name) == 0) {
            return {};
        }
        if (modules.empty()) {
            ls_modules();
        }
        for (const auto module : modules) {
            if (helper::string::strstri(module.szModule, proc_name) ||
                helper::string::strstri(module.szExePath, proc_name)) {
                return module;
            }
        }
        return {};
    }

    MODULEENTRY32W snapshot::find_module(const void *address) {
        if (!address) {
            return {};
        }
        if (modules.empty()) {
            ls_modules();
        }
        for (const auto module : modules) {
            if (module.modBaseAddr == address) {
                return module;
            }
        }
        return {};
    }

    std::vector<HEAPLIST32> snapshot::ls_heaps(const uint32_t pid) {
        if (!heaps.empty()) {
            return heaps;
        }
        cleanup();
        HEAPLIST32 he = {sizeof(HEAPLIST32)};
        do {
            snapshot_handle =
                    CreateToolhelp32Snapshot(TH32CS_SNAPHEAPLIST, pid);
            if (snapshot_handle == INVALID_HANDLE_VALUE) {
                error_code = GetLastError();
                break;
            }
            if (!Heap32ListFirst(snapshot_handle, &he)) {
                error_code = GetLastError();
                break;
            }
            heaps.push_back(he);
            while (Heap32ListNext(snapshot_handle, &he)) {
                heaps.push_back(he);
            }
        } while (false);
        return heaps;
    }

    std::unordered_set<uintptr_t> snapshot::ls_heap_ids(const uint32_t pid) {
        if (!heap_ids.empty()) {
            return heap_ids;
        }
        if (!heaps.empty()) {
            for (auto heap : heaps) {
                heap_ids.insert(heap.th32HeapID);
            }
            return heap_ids;
        }
        cleanup();
        HEAPLIST32 he = {sizeof(HEAPLIST32)};
        do {
            snapshot_handle =
                    CreateToolhelp32Snapshot(TH32CS_SNAPHEAPLIST, pid);
            if (snapshot_handle == INVALID_HANDLE_VALUE) {
                error_code = GetLastError();
                break;
            }
            if (!Heap32ListFirst(snapshot_handle, &he)) {
                error_code = GetLastError();
                break;
            }
            heap_ids.insert(he.th32HeapID);
            while (Heap32ListNext(snapshot_handle, &he)) {
                heap_ids.insert(he.th32HeapID);
            }
        } while (false);
        return heap_ids;
    }

    void snapshot::refresh_heaps() {
        heaps.clear();
        heap_ids.clear();
    }

    HEAPLIST32 snapshot::find_heap(uintptr_t heap_id) {
        if (heaps.empty()) {
            ls_heaps();
        }
        for (const auto heap : heaps) {
            if (heap.th32HeapID == heap_id) {
                return heap;
            }
        }
        return {};
    }

    std::vector<HEAPLIST32> snapshot::find_heaps(const uint32_t pid) {
        if (heaps.empty()) {
            ls_heaps();
        }
        std::vector<HEAPLIST32> result;
        for (auto heap : heaps) {
            if (heap.th32ProcessID == pid) {
                result.push_back(heap);
            }
        }
        return result;
    }

    std::vector<HEAPENTRY32>
    snapshot::find_heap_blocks(const HEAPLIST32 &heap_list) {
        HEAPENTRY32 he = {sizeof(HEAPENTRY32)};
        std::vector<HEAPENTRY32> result;
        do {
            if (!Heap32First(&he, heap_list.th32ProcessID,
                             heap_list.th32HeapID)) {
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

    std::vector<HEAPENTRY32> snapshot::find_heap_blocks(uintptr_t heap_id) {
        HEAPENTRY32 he = {sizeof(HEAPENTRY32)};
        std::vector<HEAPENTRY32> result;
        do {
            if (const HEAPLIST32 heap32 = find_heap(heap_id);
                !Heap32First(&he, heap32.th32ProcessID, heap_id)) {
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

    std::vector<HEAPENTRY32> snapshot::find_heap_blocks(const uint32_t pid) {
        HEAPENTRY32 he = {sizeof(HEAPENTRY32)};
        std::vector<HEAPENTRY32> result;
        do {
            const auto heaplists = find_heaps(pid);
            if (heaplists.empty()) {
                break;
            }
            for (const auto heaplist : heaplists) {
                if (!Heap32First(&he, heaplist.th32ProcessID,
                                 heaplist.th32HeapID)) {
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

    HANDLE
    snapshot::pid_to_handle(uint32_t pid,
                            ProcAccess access,
                            const bool is_inherit) {
        HANDLE proc_handle = OpenProcess(static_cast<uint32_t>(access),
                                         is_inherit ? TRUE : FALSE, pid);
        if (!proc_handle) {
            error_code = GetLastError();
        }
        return proc_handle;
    }

    uint32_t snapshot::handle_to_pid(HANDLE proc_handle) {
        const uint32_t pid = GetProcessId(proc_handle);
        if (!pid) {
            error_code = GetLastError();
        }
        return pid;
    }

    bool snapshot::is_heap(HANDLE proc_handle, const void *address) {
        if (!proc_handle) {
            return false;
        }
        const uint32_t pid = handle_to_pid(proc_handle);
        if (!pid) {
            return false;
        }
        const std::vector<HEAPENTRY32> blocks = find_heap_blocks(pid);
        if (blocks.empty()) {
            return false;
        }
        for (const auto block : blocks) {
            MEMORY_BASIC_INFORMATION mbi;
            if (!VirtualQueryEx(proc_handle,
                                reinterpret_cast<void *>(block.dwAddress), &mbi,
                                sizeof(mbi))) {
                error_code = GetLastError();
                break;
            }
            if (address >= static_cast<uint8_t *>(mbi.AllocationBase) &&
                address <= static_cast<uint8_t *>(mbi.AllocationBase) +
                                mbi.RegionSize) {
                return true;
            }
        }
        return false;
    }

    bool snapshot::is_heap(uint32_t pid, const void *address) {
        HANDLE proc_handle = nullptr;
        if (GetCurrentProcessId() == pid) {
            proc_handle = GetCurrentProcess();
        } else {
            proc_handle = pid_to_handle(pid);
        }
        if (!proc_handle) {
            return false;
        }
        const std::vector<HEAPENTRY32> blocks = find_heap_blocks(pid);
        if (blocks.empty()) {
            return false;
        }
        for (const auto block : blocks) {
            MEMORY_BASIC_INFORMATION mbi;
            if (!VirtualQueryEx(proc_handle,
                                reinterpret_cast<void *>(block.dwAddress), &mbi,
                                sizeof(mbi))) {
                error_code = GetLastError();
                break;
            }
            if (address >= static_cast<uint8_t *>(mbi.AllocationBase) &&
                address <= static_cast<uint8_t *>(mbi.AllocationBase) +
                                mbi.RegionSize) {
                return true;
            }
        }
        return false;
    }

    uint32_t snapshot::err_code() const {
        return error_code;
    }

    std::string snapshot::err_string() const {
        std::string result = helper::convert::err_string(error_code);
        return result;
    }

    std::wstring snapshot::err_wstring() const {
        std::wstring result = helper::convert::err_wstring(error_code);
        return result;
    }
} // namespace YanLib::sys
