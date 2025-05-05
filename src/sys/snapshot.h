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
        std::unordered_set<unsigned long> pids{};
        std::vector<THREADENTRY32> threads{};
        std::unordered_set<unsigned long> thread_ids{};
        std::vector<MODULEENTRY32W> modules{};
        std::unordered_set<HMODULE> module_handles{};
        std::vector<HEAPLIST32> heaps{};
        std::unordered_set<ULONG_PTR> heap_ids{};
        unsigned long error_code = 0;

        void cleanup();

    public:
        snapshot(const snapshot &other) = delete;

        snapshot(snapshot &&other) = delete;

        snapshot &operator=(const snapshot &other) = delete;

        snapshot &operator=(snapshot &&other) = delete;

        snapshot() = default;

        ~snapshot();

        std::vector<PROCESSENTRY32W> ls_procs(unsigned long pid = 0);

        std::unordered_set<unsigned long> ls_pids(unsigned long pid = 0);

        void refresh_procs();

        bool pid_exists(unsigned long pid);

        unsigned long get_ppid(unsigned long pid);

        PROCESSENTRY32W find_proc(unsigned long pid);

        PROCESSENTRY32W find_proc(const wchar_t *proc_name);

        std::vector<THREADENTRY32> ls_threads(unsigned long pid = 0);

        std::unordered_set<unsigned long> ls_thread_ids(unsigned long pid = 0);

        void refresh_threads();

        bool tid_exists(unsigned long tid);

        unsigned long tid_to_pid(unsigned long tid);

        THREADENTRY32 find_thread(unsigned long tid);

        std::vector<THREADENTRY32> find_threads(unsigned long pid);

        std::vector<MODULEENTRY32W> ls_modules(unsigned long pid = 0);

        std::unordered_set<HMODULE> ls_module_handles(unsigned long pid = 0);

        void refresh_modules();

        MODULEENTRY32W find_module(const wchar_t *proc_name);

        MODULEENTRY32W find_module(const void *address);

        std::vector<HEAPLIST32> ls_heaps(unsigned long pid = 0);

        std::unordered_set<ULONG_PTR> ls_heap_ids(unsigned long pid = 0);

        void refresh_heaps();

        HEAPLIST32 find_heap(ULONG_PTR heap_id);

        std::vector<HEAPLIST32> find_heaps(unsigned long pid);

        std::vector<HEAPENTRY32> find_heap_blocks(HEAPLIST32 &heap_list);

        std::vector<HEAPENTRY32> find_heap_blocks(ULONG_PTR heap_id);

        std::vector<HEAPENTRY32> find_heap_blocks(unsigned long pid);

        HANDLE pid_to_handle(unsigned long pid,
                             unsigned long desired_access = PROCESS_ALL_ACCESS,
                             bool is_inherit_handle = false);

        unsigned long handle_to_pid(HANDLE proc_handle);

        bool is_heap(HANDLE proc_handle, void *address);

        bool is_heap(unsigned long pid, void *address);

        [[nodiscard]] unsigned long err_code() const;

        [[nodiscard]] std::string err_string() const;

        [[nodiscard]] std::wstring err_wstring() const;
    };
}
#endif //SNAPSHOT_H
