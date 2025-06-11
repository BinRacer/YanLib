/* clang-format off */
/*
 * @file snapshot.h
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
#ifndef SNAPSHOT_H
#define SNAPSHOT_H
#include <Windows.h>
#include <tlhelp32.h>
#include <vector>
#include <unordered_set>
#include <string>

namespace YanLib::sys {
#ifndef TOKENACCESS
#define TOKENACCESS

    enum class ProcAccess : uint32_t {
        Delete = DELETE,
        ReadControl = READ_CONTROL,
        WriteDac = WRITE_DAC,
        WriteOwner = WRITE_OWNER,
        Synchronize = SYNCHRONIZE,
        All = PROCESS_ALL_ACCESS,
        Terminate = PROCESS_TERMINATE,
        CreateThread = PROCESS_CREATE_THREAD,
        SetSessionId = PROCESS_SET_SESSIONID,
        VmOperation = PROCESS_VM_OPERATION,
        VmRead = PROCESS_VM_READ,
        VmWrite = PROCESS_VM_WRITE,
        DupHandle = PROCESS_DUP_HANDLE,
        Create = PROCESS_CREATE_PROCESS,
        SetQuota = PROCESS_SET_QUOTA,
        SetInfo = PROCESS_SET_INFORMATION,
        QueryInfo = PROCESS_QUERY_INFORMATION,
        SuspendResume = PROCESS_SUSPEND_RESUME,
        QueryLimitedInfo = PROCESS_QUERY_LIMITED_INFORMATION,
        SetLimitedInfo = PROCESS_SET_LIMITED_INFORMATION,
    };

    inline ProcAccess operator|(ProcAccess a, ProcAccess b) {
        return static_cast<ProcAccess>(static_cast<uint32_t>(a) |
                                       static_cast<uint32_t>(b));
    }
#endif

    class snapshot {
    private:
        HANDLE snapshot_handle = INVALID_HANDLE_VALUE;
        std::vector<PROCESSENTRY32W> procs{};
        std::unordered_set<uint32_t> pids{};
        std::vector<THREADENTRY32> threads{};
        std::unordered_set<uint32_t> thread_ids{};
        std::vector<MODULEENTRY32W> modules{};
        std::unordered_set<HMODULE> module_handles{};
        std::vector<HEAPLIST32> heaps{};
        std::unordered_set<uintptr_t> heap_ids{};
        uint32_t error_code = 0;

        void cleanup();

    public:
        snapshot(const snapshot &other) = delete;

        snapshot(snapshot &&other) = delete;

        snapshot &operator=(const snapshot &other) = delete;

        snapshot &operator=(snapshot &&other) = delete;

        snapshot() = default;

        ~snapshot();

        std::vector<PROCESSENTRY32W> ls_procs(uint32_t pid = 0);

        std::unordered_set<uint32_t> ls_pids(uint32_t pid = 0);

        void refresh_procs();

        bool pid_exists(uint32_t pid);

        uint32_t get_ppid(uint32_t pid);

        PROCESSENTRY32W find_proc(uint32_t pid);

        PROCESSENTRY32W find_proc(const wchar_t *proc_name);

        std::vector<THREADENTRY32> ls_threads(uint32_t pid = 0);

        std::unordered_set<uint32_t> ls_thread_ids(uint32_t pid = 0);

        void refresh_threads();

        bool tid_exists(uint32_t tid);

        uint32_t tid_to_pid(uint32_t tid);

        THREADENTRY32 find_thread(uint32_t tid);

        std::vector<THREADENTRY32> find_threads(uint32_t pid);

        std::vector<MODULEENTRY32W> ls_modules(uint32_t pid = 0);

        std::unordered_set<HMODULE> ls_module_handles(uint32_t pid = 0);

        void refresh_modules();

        MODULEENTRY32W find_module(const wchar_t *proc_name);

        MODULEENTRY32W find_module(const void *address);

        std::vector<HEAPLIST32> ls_heaps(uint32_t pid = 0);

        std::unordered_set<uintptr_t> ls_heap_ids(uint32_t pid = 0);

        void refresh_heaps();

        HEAPLIST32 find_heap(uintptr_t heap_id);

        std::vector<HEAPLIST32> find_heaps(uint32_t pid);

        std::vector<HEAPENTRY32> find_heap_blocks(const HEAPLIST32 &heap_list);

        std::vector<HEAPENTRY32> find_heap_blocks(uintptr_t heap_id);

        std::vector<HEAPENTRY32> find_heap_blocks(uint32_t pid);

        HANDLE pid_to_handle(uint32_t pid,
                             ProcAccess access = ProcAccess::All,
                             bool is_inherit = false);

        uint32_t handle_to_pid(HANDLE proc_handle);

        bool is_heap(HANDLE proc_handle, const void *address);

        bool is_heap(uint32_t pid, const void *address);

        [[nodiscard]] uint32_t err_code() const;

        [[nodiscard]] std::string err_string() const;

        [[nodiscard]] std::wstring err_wstring() const;
    };
} // namespace YanLib::sys
#endif // SNAPSHOT_H
