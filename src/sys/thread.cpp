/* clang-format off */
/*
 * @file thread.cpp
 * @date 2025-04-18
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
#include "thread.h"
#include "helper/convert.h"

namespace YanLib::sys {
    thread::~thread() {
        for (auto &[key, value] : thread_records) {
            CloseHandle(value);
            value = nullptr;
        }
        thread_records.clear();
        for (auto &thread_handle : open_thread_handles) {
            CloseHandle(thread_handle);
            thread_handle = nullptr;
        }
        open_thread_handles.clear();
    }

    HANDLE thread::create(LPTHREAD_START_ROUTINE start_addr,
                          void *params,
                          size_t stack_size,
                          SECURITY_ATTRIBUTES *sa) {
        unsigned long tid = 0;
        HANDLE thread_handle =
                CreateThread(sa, stack_size, start_addr, params, 0, &tid);
        if (!thread_handle) {
            error_code = GetLastError();
            return nullptr;
        }
        thread_record_rwlock.write_lock();
        thread_records.emplace_back(tid, thread_handle);
        thread_record_rwlock.write_unlock();
        return thread_handle;
    }

    HANDLE thread::create_with_suspend(LPTHREAD_START_ROUTINE start_addr,
                                       void *params,
                                       size_t stack_size,
                                       SECURITY_ATTRIBUTES *sa) {
        unsigned long tid = 0;
        HANDLE thread_handle = CreateThread(sa, stack_size, start_addr, params,
                                            CREATE_SUSPENDED, &tid);
        if (!thread_handle) {
            error_code = GetLastError();
            return nullptr;
        }
        thread_record_rwlock.write_lock();
        thread_records.emplace_back(tid, thread_handle);
        thread_record_rwlock.write_unlock();
        return thread_handle;
    }

    HANDLE
    thread::create_with_stack_reserve(LPTHREAD_START_ROUTINE start_addr,
                                      void *params,
                                      size_t stack_size,
                                      SECURITY_ATTRIBUTES *sa) {
        unsigned long tid = 0;
        HANDLE thread_handle =
                CreateThread(sa, stack_size, start_addr, params,
                             STACK_SIZE_PARAM_IS_A_RESERVATION, &tid);
        if (!thread_handle) {
            error_code = GetLastError();
            return nullptr;
        }
        thread_record_rwlock.write_lock();
        thread_records.emplace_back(tid, thread_handle);
        thread_record_rwlock.write_unlock();
        return thread_handle;
    }

    HANDLE thread::create_remote(HANDLE proc_handle,
                                 LPTHREAD_START_ROUTINE start_addr,
                                 void *params,
                                 size_t stack_size,
                                 LPPROC_THREAD_ATTRIBUTE_LIST attr_list,
                                 SECURITY_ATTRIBUTES *sa) {
        unsigned long tid = 0;
        HANDLE thread_handle =
                CreateRemoteThreadEx(proc_handle, sa, stack_size, start_addr,
                                     params, 0, attr_list, &tid);
        if (!thread_handle) {
            error_code = GetLastError();
            return nullptr;
        }
        thread_record_rwlock.write_lock();
        thread_records.emplace_back(tid, thread_handle);
        thread_record_rwlock.write_unlock();
        return thread_handle;
    }

    HANDLE
    thread::create_remote_with_suspend(HANDLE proc_handle,
                                       LPTHREAD_START_ROUTINE start_addr,
                                       void *params,
                                       size_t stack_size,
                                       LPPROC_THREAD_ATTRIBUTE_LIST attr_list,
                                       SECURITY_ATTRIBUTES *sa) {
        unsigned long tid = 0;
        HANDLE thread_handle =
                CreateRemoteThreadEx(proc_handle, sa, stack_size, start_addr,
                                     params, CREATE_SUSPENDED, attr_list, &tid);
        if (!thread_handle) {
            error_code = GetLastError();
            return nullptr;
        }
        thread_record_rwlock.write_lock();
        thread_records.emplace_back(tid, thread_handle);
        thread_record_rwlock.write_unlock();
        return thread_handle;
    }

    HANDLE thread::create_remote_with_stack_reserve(
            HANDLE proc_handle,
            LPTHREAD_START_ROUTINE start_addr,
            void *params,
            size_t stack_size,
            LPPROC_THREAD_ATTRIBUTE_LIST attr_list,
            SECURITY_ATTRIBUTES *sa) {
        unsigned long tid = 0;
        HANDLE thread_handle =
                CreateRemoteThreadEx(proc_handle, sa, stack_size, start_addr,
                                     params, STACK_SIZE_PARAM_IS_A_RESERVATION,
                                     attr_list, &tid);
        if (!thread_handle) {
            error_code = GetLastError();
            return nullptr;
        }
        thread_record_rwlock.write_lock();
        thread_records.emplace_back(tid, thread_handle);
        thread_record_rwlock.write_unlock();
        return thread_handle;
    }

    HANDLE thread::curr_thread_handle() {
        return GetCurrentThread();
    }

    HANDLE thread::curr_process_handle() {
        return GetCurrentProcess();
    }

    uint32_t thread::curr_thread_id() {
        return GetCurrentThreadId();
    }

    uint32_t thread::curr_process_id() {
        return GetCurrentProcessId();
    }

    HANDLE
    thread::tid_to_handle(uint32_t tid,
                          ThreadAccess access,
                          const bool is_inherit) {
        HANDLE thread_handle = OpenThread(static_cast<uint32_t>(access),
                                          is_inherit ? TRUE : FALSE, tid);
        if (!thread_handle) {
            error_code = GetLastError();
            return nullptr;
        }
        open_thread_record_rwlock.write_lock();
        open_thread_handles.push_back(thread_handle);
        open_thread_record_rwlock.write_unlock();
        return thread_handle;
    }

    uint32_t thread::handle_to_tid(HANDLE thread_handle) {
        const uint32_t thread_id = GetThreadId(thread_handle);
        if (!thread_handle) {
            error_code = GetLastError();
        }
        return thread_id;
    }

    uint32_t thread::handle_to_pid(HANDLE thread_handle) {
        const uint32_t pid = GetProcessIdOfThread(thread_handle);
        if (!pid) {
            error_code = GetLastError();
        }
        return pid;
    }

    std::vector<HANDLE> thread::thread_handles() {
        std::vector<HANDLE> thread_handles;
        thread_record_rwlock.read_lock();
        for (auto [key, value] : thread_records) {
            thread_handles.push_back(value);
        }
        thread_record_rwlock.read_unlock();
        return thread_handles;
    }

    std::vector<uint32_t> thread::thread_ids() {
        std::vector<uint32_t> thread_ids;
        thread_record_rwlock.read_lock();
        for (auto [key, value] : thread_records) {
            thread_ids.push_back(key);
        }
        thread_record_rwlock.read_unlock();
        return thread_ids;
    }

    uint32_t thread::tls_alloc() {
        const uint32_t tls_index = TlsAlloc();
        if (tls_index == TLS_OUT_OF_INDEXES) {
            error_code = GetLastError();
        }
        return tls_index;
    }

    bool thread::tls_free(uint32_t tls_index) {
        if (!TlsFree(tls_index)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    void *thread::tls_get(uint32_t tls_index) {
        void *tls_value = TlsGetValue(tls_index);
        if (!tls_value) {
            error_code = GetLastError();
        }
        return tls_value;
    }

    bool thread::tls_set(uint32_t tls_index, void *tls_value) {
        if (!TlsSetValue(tls_index, tls_value)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    uint32_t thread::wait_for_input_idle(HANDLE proc_handle,
                                         uint32_t milli_seconds) {
        return WaitForInputIdle(proc_handle, milli_seconds);
    }

    bool thread::attach_thread_input(uint32_t id_attach,
                                     uint32_t id_attach_to,
                                     bool is_attach) {
        if (!AttachThreadInput(id_attach, id_attach_to,
                               is_attach ? TRUE : FALSE)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool
    thread::init_proc_thread_attr_list(LPPROC_THREAD_ATTRIBUTE_LIST attr_list,
                                       uint32_t attr_count,
                                       SIZE_T *size) {
        if (!InitializeProcThreadAttributeList(attr_list, attr_count, 0,
                                               size)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool thread::update_proc_thread_attr(LPPROC_THREAD_ATTRIBUTE_LIST attr_list,
                                         uintptr_t attr,
                                         void *value,
                                         size_t bytes_size,
                                         void *previous_value,
                                         SIZE_T *ret_size) {
        if (!UpdateProcThreadAttribute(attr_list, 0, attr, value, bytes_size,
                                       previous_value, ret_size)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    void thread::delete_proc_thread_attr_list(
            LPPROC_THREAD_ATTRIBUTE_LIST attr_list) {
        DeleteProcThreadAttributeList(attr_list);
    }

    uint32_t thread::suspend(HANDLE thread_handle) {
        const uint32_t ret = SuspendThread(thread_handle);
        if (ret == static_cast<uint32_t>(-1)) {
            error_code = GetLastError();
        }
        return ret;
    }

    uint32_t thread::resume(HANDLE thread_handle) {
        const uint32_t ret = ResumeThread(thread_handle);
        if (ret == static_cast<uint32_t>(-1)) {
            error_code = GetLastError();
        }
        return ret;
    }

    bool thread::wait(HANDLE thread_handle, uint32_t milli_seconds) {
        if (const uint32_t ret =
                    WaitForSingleObject(thread_handle, milli_seconds);
            ret == WAIT_OBJECT_0) {
            return true;
        }
        return false;
    }

    bool thread::wait_all(const bool is_wait_all, uint32_t milli_seconds) {
        const std::vector<HANDLE> thread_handles = thread::thread_handles();
        const uint32_t ret = WaitForMultipleObjects(thread_handles.size(),
                                                    thread_handles.data(),
                                                    is_wait_all ? TRUE : FALSE,
                                                    milli_seconds);
        if (ret >= WAIT_OBJECT_0 &&
            ret <= WAIT_OBJECT_0 + thread_handles.size() - 1) {
            return true;
        }
        return false;
    }

    void thread::sleep(uint32_t milli_seconds) {
        Sleep(milli_seconds);
    }

    uint32_t thread::sleep(uint32_t milli_seconds, bool alertable) {
        return SleepEx(milli_seconds, alertable ? TRUE : FALSE);
    }

    bool thread::yield() {
        return SwitchToThread();
    }

    bool thread::kill(HANDLE thread_handle, uint32_t exit_code) {
        if (!TerminateThread(thread_handle, exit_code)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    void thread::kill_all(uint32_t exit_code) {
        thread_record_rwlock.read_lock();
        for (auto [key, value] : thread_records) {
            TerminateThread(value, exit_code);
        }
    }

    void thread::exit(uint32_t exit_code) {
        ExitThread(exit_code);
    }

    uint32_t thread::exit_status(HANDLE thread_handle) {
        unsigned long exit_code = 0;
        if (!GetExitCodeThread(thread_handle, &exit_code)) {
            error_code = GetLastError();
        }
        return exit_code;
    }

    bool thread::thread_info(HANDLE thread_handle,
                             THREAD_INFORMATION_CLASS thread_info_class,
                             void *thread_info,
                             uint32_t thread_info_size) {
        if (!get_info(thread_handle, thread_info_class, thread_info,
                      thread_info_size)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool thread::is_io_pending(HANDLE thread_handle) {
        int32_t is_ok = 0;
        if (!GetThreadIOPendingFlag(thread_handle, &is_ok)) {
            error_code = GetLastError();
        }
        return is_ok;
    }

    int32_t thread::get_priority(HANDLE thread_handle) {
        const int32_t priority = GetThreadPriority(thread_handle);
        if (priority == THREAD_PRIORITY_ERROR_RETURN) {
            error_code = GetLastError();
        }
        return priority;
    }

    bool thread::set_priority(HANDLE thread_handle, int32_t priority) {
        if (!SetThreadPriority(thread_handle, priority)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    uint32_t thread::get_proc_priority(HANDLE proc_handle) {
        const uint32_t priority = GetPriorityClass(proc_handle);
        if (!priority) {
            error_code = GetLastError();
        }
        return priority;
    }

    bool thread::set_proc_priority(HANDLE proc_handle, uint32_t priority) {
        if (!SetPriorityClass(proc_handle, priority)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool thread::get_priority_boost(HANDLE thread_handle) {
        int32_t is_disable_priority_boost = 0;
        if (!GetThreadPriorityBoost(thread_handle,
                                    &is_disable_priority_boost)) {
            error_code = GetLastError();
        }
        return is_disable_priority_boost;
    }

    bool thread::set_priority_boost(HANDLE thread_handle,
                                    bool is_disable_priority_boost) {
        if (!SetThreadPriorityBoost(thread_handle,
                                    is_disable_priority_boost ? TRUE : FALSE)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool thread::time_statistics(HANDLE thread_handle,
                                 FILETIME *creation_time,
                                 FILETIME *exit_time,
                                 FILETIME *kernel_time,
                                 FILETIME *user_time) {
        if (!GetThreadTimes(thread_handle, creation_time, exit_time,
                            kernel_time, user_time)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    HRESULT thread::get_description(HANDLE thread_handle,
                                    wchar_t **thread_description) {
        return GetThreadDescription(thread_handle, thread_description);
    }

    HRESULT thread::set_description(HANDLE thread_handle,
                                    const wchar_t *thread_description) {
        return SetThreadDescription(thread_handle, thread_description);
    }

    bool thread::get_group_affinity(HANDLE thread_handle,
                                    GROUP_AFFINITY *group_affinity) {
        if (!GetThreadGroupAffinity(thread_handle, group_affinity)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool thread::set_group_affinity(HANDLE thread_handle,
                                    const GROUP_AFFINITY *group_affinity,
                                    GROUP_AFFINITY *previous_group_affinity) {
        if (!SetThreadGroupAffinity(thread_handle, group_affinity,
                                    previous_group_affinity)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool thread::get_ideal_processor(HANDLE thread_handle,
                                     PROCESSOR_NUMBER *ideal_processor) {
        if (!GetThreadIdealProcessorEx(thread_handle, ideal_processor)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool
    thread::set_ideal_processor(HANDLE thread_handle,
                                PROCESSOR_NUMBER *ideal_processor,
                                PROCESSOR_NUMBER *previous_ideal_processor) {
        if (!SetThreadIdealProcessorEx(thread_handle, ideal_processor,
                                       previous_ideal_processor)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool thread::get_info(HANDLE thread_handle,
                          THREAD_INFORMATION_CLASS thread_info_class,
                          void *thread_info,
                          const uint32_t thread_information_size) {
        if (!GetThreadInformation(thread_handle, thread_info_class, thread_info,
                                  thread_information_size)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool thread::set_info(HANDLE thread_handle,
                          THREAD_INFORMATION_CLASS thread_info_class,
                          void *thread_info,
                          const uint32_t thread_information_size) {
        if (!SetThreadInformation(thread_handle, thread_info_class, thread_info,
                                  thread_information_size)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool thread::query_idle_processor_cycle_time(
            uint16_t group,
            uint32_t *buffer_length,
            uint64_t *processor_idle_cycle_time) {
        if (!buffer_length) {
            error_code = STATUS_ACCESS_VIOLATION;
            return false;
        }
        unsigned long temp = *buffer_length;
        if (QueryIdleProcessorCycleTimeEx(group, &temp,
                                          processor_idle_cycle_time)) {
            error_code = GetLastError();
            *buffer_length = temp;
            return false;
        }
        *buffer_length = temp;
        return true;
    }

    bool thread::query_cycle_time(HANDLE thread_handle, uint64_t *cycle_time) {
        if (!QueryThreadCycleTime(thread_handle, cycle_time)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    uintptr_t thread::set_affinity_mask(HANDLE thread_handle,
                                        const uintptr_t thread_affinity_mask) {
        const uintptr_t ret =
                SetThreadAffinityMask(thread_handle, thread_affinity_mask);
        if (!ret) {
            error_code = GetLastError();
        }
        return ret;
    }

    bool thread::set_stack_guarantee(uint32_t *bytes_stack) {
        if (!bytes_stack) {
            error_code = STATUS_ACCESS_VIOLATION;
            return false;
        }
        unsigned long temp = *bytes_stack;
        if (!SetThreadStackGuarantee(&temp)) {
            error_code = GetLastError();
            *bytes_stack = temp;
            return false;
        }
        *bytes_stack = temp;
        return true;
    }

    uint32_t thread::err_code() const {
        return error_code;
    }

    std::string thread::err_string() const {
        std::string result = helper::convert::err_string(error_code);
        return result;
    }

    std::wstring thread::err_wstring() const {
        std::wstring result = helper::convert::err_wstring(error_code);
        return result;
    }
} // namespace YanLib::sys
