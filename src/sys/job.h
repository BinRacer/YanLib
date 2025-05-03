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
    class job {
    private:
        std::vector<HANDLE> job_handles = {};
        sync::rwlock rwlock = {};
        DWORD error_code = 0;

    public:
        job(const job &other) = delete;

        job(job &&other) = delete;

        job &operator=(const job &other) = delete;

        job &operator=(job &&other) = delete;

        job() = default;

        ~job();

        HANDLE create(const wchar_t *job_name,
                      SECURITY_ATTRIBUTES* security_attrs = nullptr);

        HANDLE open(const wchar_t *job_name,
                    DWORD desired_access = JOB_ALL_ACCESS,
                    bool is_inherit_handle = false);

        bool add(HANDLE job_handle, HANDLE proc_handle);

        bool contains(HANDLE job_handle, HANDLE proc_handle);

        bool kill(HANDLE job_handle, UINT exit_code);

        bool grant_access(HANDLE job_handle, HANDLE user_handle);

        bool revoke_access(HANDLE job_handle, HANDLE user_handle);

        bool get_info(HANDLE job_handle,
                      JOBOBJECTINFOCLASS job_object_info_class,
                      void *job_object_info,
                      DWORD job_object_info_len,
                      DWORD* ret_len);

        bool set_info(HANDLE job_handle,
                      JOBOBJECTINFOCLASS job_object_info_class,
                      void *job_object_info,
                      DWORD job_object_info_len);

        [[nodiscard]] DWORD err_code() const;

        [[nodiscard]] std::string err_string() const;

        [[nodiscard]] std::wstring err_wstring() const;
    };
}
#endif //JOB_H
