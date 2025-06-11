//
// Created by BinRacer <native.lab@outlook.com> on 2025/4/22.
//

#include "job.h"
#include "helper/convert.h"

namespace YanLib::sys {
    job::~job() {
        for (auto &handle : job_handles) {
            CloseHandle(handle);
            handle = nullptr;
        }
        job_handles.clear();
    }

    HANDLE job::create(const char *job_name, SECURITY_ATTRIBUTES *sa) {
        HANDLE job_handle = CreateJobObjectA(sa, job_name);
        if (!job_handle) {
            error_code = GetLastError();
            return nullptr;
        }
        rwlock.write_lock();
        job_handles.push_back(job_handle);
        rwlock.write_unlock();
        return job_handle;
    }

    HANDLE job::create(const wchar_t *job_name, SECURITY_ATTRIBUTES *sa) {
        HANDLE job_handle = CreateJobObjectW(sa, job_name);
        if (!job_handle) {
            error_code = GetLastError();
            return nullptr;
        }
        rwlock.write_lock();
        job_handles.push_back(job_handle);
        rwlock.write_unlock();
        return job_handle;
    }

    HANDLE
    job::open(const char *job_name, JobAccess access, const bool is_inherit) {
        HANDLE job_handle = OpenJobObjectA(static_cast<uint32_t>(access),
                                           is_inherit ? TRUE : FALSE, job_name);
        if (!job_handle) {
            error_code = GetLastError();
            return nullptr;
        }
        rwlock.write_lock();
        job_handles.push_back(job_handle);
        rwlock.write_unlock();
        return job_handle;
    }

    HANDLE
    job::open(const wchar_t *job_name,
              JobAccess access,
              const bool is_inherit) {
        HANDLE job_handle = OpenJobObjectW(static_cast<uint32_t>(access),
                                           is_inherit ? TRUE : FALSE, job_name);
        if (!job_handle) {
            error_code = GetLastError();
            return nullptr;
        }
        rwlock.write_lock();
        job_handles.push_back(job_handle);
        rwlock.write_unlock();
        return job_handle;
    }

    bool job::add(HANDLE job_handle, HANDLE proc_handle) {
        if (!AssignProcessToJobObject(job_handle, proc_handle)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool job::contains(HANDLE job_handle, HANDLE proc_handle) {
        int32_t is_ok = 0;
        if (!IsProcessInJob(proc_handle, job_handle, &is_ok)) {
            error_code = GetLastError();
        }
        return is_ok;
    }

    bool job::kill(HANDLE job_handle, uint32_t exit_code) {
        if (!TerminateJobObject(job_handle, exit_code)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool job::grant_access(HANDLE job_handle, HANDLE user_handle) {
        if (!UserHandleGrantAccess(user_handle, job_handle, TRUE)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool job::revoke_access(HANDLE job_handle, HANDLE user_handle) {
        if (!UserHandleGrantAccess(user_handle, job_handle, FALSE)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool job::get_info(HANDLE job_handle,
                       JOBOBJECTINFOCLASS job_object_info_class,
                       void *job_object_info,
                       uint32_t job_object_info_len,
                       uint32_t *real_size) {
        if (!real_size) {
            error_code = STATUS_ACCESS_VIOLATION;
            return false;
        }
        unsigned long temp = *real_size;
        if (!QueryInformationJobObject(job_handle, job_object_info_class,
                                       job_object_info, job_object_info_len,
                                       &temp)) {
            error_code = GetLastError();
            *real_size = temp;
            return false;
        }
        *real_size = temp;
        return true;
    }

    bool job::set_info(HANDLE job_handle,
                       JOBOBJECTINFOCLASS job_object_info_class,
                       void *job_object_info,
                       const uint32_t job_object_info_len) {
        if (!SetInformationJobObject(job_handle, job_object_info_class,
                                     job_object_info, job_object_info_len)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    uint32_t job::err_code() const {
        return error_code;
    }

    std::string job::err_string() const {
        std::string result = helper::convert::err_string(error_code);
        return result;
    }

    std::wstring job::err_wstring() const {
        std::wstring result = helper::convert::err_wstring(error_code);
        return result;
    }
} // namespace YanLib::sys
