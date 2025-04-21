//
// Created by forkernel on 2025/4/18.
//

#include "thread.h"
#include "helper/convert.h"

namespace YanLib::sys {
    thread::~thread() {
        if (!thread_records.empty()) {
            for (auto [key, value]: thread_records) {
                CloseHandle(value);
            }
            thread_records.clear();
        }
    }

    bool thread::create(LPTHREAD_START_ROUTINE start_addr,
                        void *params,
                        size_t stack_size,
                        LPSECURITY_ATTRIBUTES security_attrs) {
        DWORD tid = 0;
        HANDLE thread_handle = CreateThread(security_attrs,
                                            stack_size,
                                            start_addr,
                                            params,
                                            0,
                                            &tid);
        if (!thread_handle) {
            error_code = GetLastError();
            return false;
        }
        rwlock.write_lock();
        thread_records.emplace(tid, thread_handle);
        rwlock.write_unlock();
        return true;
    }

    bool thread::create_with_suspend(LPTHREAD_START_ROUTINE start_addr,
                                     void *params,
                                     size_t stack_size,
                                     LPSECURITY_ATTRIBUTES security_attrs) {
        DWORD tid = 0;
        HANDLE thread_handle = CreateThread(security_attrs,
                                            stack_size,
                                            start_addr,
                                            params,
                                            CREATE_SUSPENDED,
                                            &tid);
        if (!thread_handle) {
            error_code = GetLastError();
            return false;
        }
        rwlock.write_lock();
        thread_records.emplace(tid, thread_handle);
        rwlock.write_unlock();
        return true;
    }

    bool thread::create_with_stack_reserve(LPTHREAD_START_ROUTINE start_addr,
                                           void *params,
                                           size_t stack_size,
                                           LPSECURITY_ATTRIBUTES security_attrs) {
        DWORD tid = 0;
        HANDLE thread_handle = CreateThread(security_attrs,
                                            stack_size,
                                            start_addr,
                                            params,
                                            STACK_SIZE_PARAM_IS_A_RESERVATION,
                                            &tid);
        if (!thread_handle) {
            error_code = GetLastError();
            return false;
        }
        rwlock.write_lock();
        thread_records.emplace(tid, thread_handle);
        rwlock.write_unlock();
        return true;
    }

    bool thread::create_remote(HANDLE proc_handle,
                               LPTHREAD_START_ROUTINE start_addr,
                               void *params,
                               size_t stack_size,
                               LPSECURITY_ATTRIBUTES security_attrs) {
        DWORD tid = 0;
        HANDLE thread_handle = CreateRemoteThread(proc_handle,
                                                  security_attrs,
                                                  stack_size,
                                                  start_addr,
                                                  params,
                                                  0,
                                                  &tid);
        if (!thread_handle) {
            error_code = GetLastError();
            return false;
        }
        rwlock.write_lock();
        thread_records.emplace(tid, thread_handle);
        rwlock.write_unlock();
        return true;
    }

    bool thread::create_remote_with_suspend(HANDLE proc_handle,
                                            LPTHREAD_START_ROUTINE start_addr,
                                            void *params,
                                            size_t stack_size,
                                            LPSECURITY_ATTRIBUTES security_attrs) {
        DWORD tid = 0;
        HANDLE thread_handle = CreateRemoteThread(proc_handle,
                                                  security_attrs,
                                                  stack_size,
                                                  start_addr,
                                                  params,
                                                  CREATE_SUSPENDED,
                                                  &tid);
        if (!thread_handle) {
            error_code = GetLastError();
            return false;
        }
        rwlock.write_lock();
        thread_records.emplace(tid, thread_handle);
        rwlock.write_unlock();
        return true;
    }

    bool thread::create_remote_with_stack_reserve(HANDLE proc_handle,
                                                  LPTHREAD_START_ROUTINE start_addr,
                                                  void *params,
                                                  size_t stack_size,
                                                  LPSECURITY_ATTRIBUTES security_attrs) {
        DWORD tid = 0;
        HANDLE thread_handle = CreateRemoteThread(proc_handle,
                                                  security_attrs,
                                                  stack_size,
                                                  start_addr,
                                                  params,
                                                  STACK_SIZE_PARAM_IS_A_RESERVATION,
                                                  &tid);
        if (!thread_handle) {
            error_code = GetLastError();
            return false;
        }
        rwlock.write_lock();
        thread_records.emplace(tid, thread_handle);
        rwlock.write_unlock();
        return true;
    }

    bool thread::kill(HANDLE thread_handle, DWORD exit_code) {
        if (!TerminateThread(thread_handle, exit_code)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    void thread::kill_all(DWORD exit_code) {
        rwlock.read_lock();
        for (auto [key, value]: thread_records) {
            TerminateThread(value, exit_code);
        }
    }

    void thread::exit(DWORD exit_code) {
        ExitThread(exit_code);
    }

    HANDLE thread::curr_thread_handle() {
        return GetCurrentThread();
    }

    HANDLE thread::curr_process_handle() {
        return GetCurrentProcess();
    }

    DWORD thread::curr_thread_id() {
        return GetCurrentThreadId();
    }

    DWORD thread::curr_process_id() {
        return GetCurrentProcessId();
    }

    HANDLE thread::tid_to_handle(DWORD thread_id,
                                 DWORD desired_access,
                                 bool is_inherit_handle) {
        HANDLE thread_handle = OpenThread(desired_access,
                                          is_inherit_handle ? TRUE : FALSE,
                                          thread_id);
        if (!thread_handle) {
            error_code = GetLastError();
        }
        return thread_handle;
    }

    DWORD thread::handle_to_pid(HANDLE thread_handle) {
        return GetProcessIdOfThread(thread_handle);
    }

    std::vector<HANDLE> thread::thread_handles() {
        std::vector<HANDLE> thread_handles;
        rwlock.read_lock();
        for (auto [key, value]: thread_records) {
            thread_handles.push_back(value);
        }
        rwlock.read_unlock();
        return thread_handles;
    }

    std::vector<DWORD> thread::thread_ids() {
        std::vector<DWORD> thread_ids;
        rwlock.read_lock();
        for (auto [key, value]: thread_records) {
            thread_ids.push_back(key);
        }
        rwlock.read_unlock();
        return thread_ids;
    }

    bool thread::wait(HANDLE thread_handle, DWORD milli_seconds) {
        DWORD ret = WaitForSingleObject(thread_handle, milli_seconds);
        if (ret == WAIT_OBJECT_0) {
            return true;
        }
        return false;
    }

    bool thread::wait_all(bool is_wait_all, DWORD milli_seconds) {
        std::vector<HANDLE> thread_handles = thread::thread_handles();
        DWORD ret = WaitForMultipleObjects(thread_handles.size(),
                                           thread_handles.data(),
                                           is_wait_all ? TRUE : FALSE,
                                           milli_seconds);
        if (ret >= WAIT_OBJECT_0 &&
            ret <= WAIT_OBJECT_0 + thread_handles.size() - 1) {
            return true;
        }
        return false;
    }

    DWORD thread::err_code() const {
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
}
