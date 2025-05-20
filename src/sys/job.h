//
// Created by forkernel on 2025/4/22.
//

#ifndef JOB_H
#define JOB_H
#include <Windows.h>
#include <string>
#include <vector>
#include "sync/rwlock.h"

namespace YanLib::sys {
#ifndef JOBACCESS
#define JOBACCESS

    enum class JobAccess : uint32_t {
        Delete = DELETE,
        ReadControl = READ_CONTROL,
        WriteDac = WRITE_DAC,
        WriteOwner = WRITE_OWNER,
        Synchronize = SYNCHRONIZE,
        AssignProcess = JOB_OBJECT_ASSIGN_PROCESS,
        SetAttributes = JOB_OBJECT_SET_ATTRIBUTES,
        Query = JOB_OBJECT_QUERY,
        Terminate = JOB_OBJECT_TERMINATE,
        SetSecurityAttributes = JOB_OBJECT_SET_SECURITY_ATTRIBUTES,
        Impersonate = JOB_OBJECT_IMPERSONATE,
        All = JOB_OBJECT_ALL_ACCESS,
    };

    inline JobAccess operator|(JobAccess a, JobAccess b) {
        return static_cast<JobAccess>(static_cast<uint32_t>(a) |
                                      static_cast<uint32_t>(b));
    }
#endif

    class job {
    private:
        std::vector<HANDLE> job_handles = {};
        sync::rwlock rwlock = {};
        uint32_t error_code = 0;

    public:
        job(const job &other) = delete;

        job(job &&other) = delete;

        job &operator=(const job &other) = delete;

        job &operator=(job &&other) = delete;

        job() = default;

        ~job();

        HANDLE create(const char *job_name, SECURITY_ATTRIBUTES *sa = nullptr);

        HANDLE create(const wchar_t *job_name,
                      SECURITY_ATTRIBUTES *sa = nullptr);

        HANDLE open(const char *job_name,
                    JobAccess access = JobAccess::All,
                    bool is_inherit = false);

        HANDLE open(const wchar_t *job_name,
                    JobAccess access = JobAccess::All,
                    bool is_inherit = false);

        bool add(HANDLE job_handle, HANDLE proc_handle);

        bool contains(HANDLE job_handle, HANDLE proc_handle);

        bool kill(HANDLE job_handle, uint32_t exit_code);

        bool grant_access(HANDLE job_handle, HANDLE user_handle);

        bool revoke_access(HANDLE job_handle, HANDLE user_handle);

        bool get_info(HANDLE job_handle,
                      JOBOBJECTINFOCLASS job_object_info_class,
                      void *job_object_info,
                      uint32_t job_object_info_len,
                      uint32_t *real_size);

        bool set_info(HANDLE job_handle,
                      JOBOBJECTINFOCLASS job_object_info_class,
                      void *job_object_info,
                      uint32_t job_object_info_len);

        [[nodiscard]] uint32_t err_code() const;

        [[nodiscard]] std::string err_string() const;

        [[nodiscard]] std::wstring err_wstring() const;
    };
} // namespace YanLib::sys
#endif // JOB_H
