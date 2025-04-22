//
// Created by forkernel on 2025/4/22.
//

#ifndef SNAPSHOT_H
#define SNAPSHOT_H
#include <Windows.h>
#include <tlhelp32.h>
#include <vector>
#include <unordered_set>
#include <string>

namespace YanLib::sys {
    class snapshot {
    private:
        HANDLE snapshot_handle = INVALID_HANDLE_VALUE;
        std::vector<PROCESSENTRY32W> procs{};
        std::unordered_set<DWORD> pids{};
        std::vector<THREADENTRY32> threads{};
        std::unordered_set<DWORD> thread_ids{};
        std::vector<MODULEENTRY32W> modules{};
        std::unordered_set<HMODULE> module_handles{};
        std::vector<HEAPLIST32> heaps{};
        std::unordered_set<ULONG_PTR> heap_ids{};
        DWORD error_code = 0;

        void cleanup();

    public:
        snapshot(const snapshot &other) = delete;

        snapshot(snapshot &&other) = delete;

        snapshot &operator=(const snapshot &other) = delete;

        snapshot &operator=(snapshot &&other) = delete;

        snapshot() = default;

        ~snapshot();

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

        HANDLE pid_to_handle(DWORD pid,
                     DWORD desired_access = PROCESS_ALL_ACCESS,
                     bool is_inherit_handle = false);

        DWORD handle_to_pid(HANDLE proc_handle);

        bool is_heap(HANDLE proc_handle, void *address);

        bool is_heap(DWORD pid, void *address);

        [[nodiscard]] DWORD err_code() const;

        [[nodiscard]] std::string err_string() const;

        [[nodiscard]] std::wstring err_wstring() const;
    };
}
#endif //SNAPSHOT_H
