/* clang-format off */
/*
 * @file job.h
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
