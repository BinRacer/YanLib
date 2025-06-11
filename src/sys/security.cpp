/* clang-format off */
/*
 * @file security.cpp
 * @date 2025-04-15
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
#include "security.h"
#include "helper/convert.h"
#include "helper/autoclean.h"
#include <shlobj.h>
#include <aclapi.h>
#include <memory>
#include <vector>
#include <WtsApi32.h>
#include <UserEnv.h>
#pragma comment(lib, "WtsApi32.Lib")
#pragma comment(lib, "UserEnv.Lib")

namespace YanLib::sys {
    security::~security() {
        cleanup();
        for (auto &token_handle : token_handles) {
            CloseHandle(token_handle);
            token_handle = nullptr;
        }
        token_handles.clear();
    }

    void security::cleanup() {
        if (env) {
            DestroyEnvironmentBlock(env);
            env = nullptr;
        }
    }

    uint32_t security::curr_session_id() const {
        return WTSGetActiveConsoleSessionId();
    }

    HANDLE security::curr_session_token(const uint32_t session_id) {
        const uint32_t id = (session_id == 0) ? curr_session_id() : session_id;
        HANDLE token;
        if (!WTSQueryUserToken(id, &token)) {
            error_code = GetLastError();
            return nullptr;
        }
        rwlock.write_lock();
        token_handles.push_back(token);
        rwlock.write_unlock();
        return token;
    }

    HANDLE security::open_proc_token(HANDLE proc_handle, TokenAccess access) {
        HANDLE token = nullptr;
        if (!OpenProcessToken(proc_handle, static_cast<uint32_t>(access),
                              &token)) {
            error_code = GetLastError();
            return nullptr;
        }
        rwlock.write_lock();
        token_handles.push_back(token);
        rwlock.write_unlock();
        return token;
    }

    HANDLE security::open_thread_token(HANDLE thread_handle,
                                       TokenAccess access,
                                       const bool open_as_self) {
        HANDLE token = nullptr;
        if (!OpenThreadToken(thread_handle, static_cast<uint32_t>(access),
                             open_as_self ? TRUE : FALSE, &token)) {
            error_code = GetLastError();
            return nullptr;
        }
        rwlock.write_lock();
        token_handles.push_back(token);
        rwlock.write_unlock();
        return token;
    }

    HANDLE security::copy_token(HANDLE existing_token_handle,
                                SECURITY_ATTRIBUTES *sa,
                                const SECURITY_IMPERSONATION_LEVEL sil,
                                const TOKEN_TYPE token_type) {
        HANDLE token_handle = existing_token_handle ? existing_token_handle
                                                    : curr_session_token();
        if (!token_handle) {
            return nullptr;
        }
        HANDLE ret_token = nullptr;
        if (!DuplicateTokenEx(token_handle, MAXIMUM_ALLOWED, sa, sil,
                              token_type, &ret_token)) {
            error_code = GetLastError();
            return nullptr;
        }
        rwlock.write_lock();
        token_handles.push_back(ret_token);
        rwlock.write_unlock();
        return ret_token;
    }

    void *security::create_env_block(HANDLE token_handle,
                                     const bool is_inherit) {
        if (env) {
            cleanup();
        }
        if (!CreateEnvironmentBlock(&env, token_handle,
                                    is_inherit ? TRUE : FALSE)) {
            error_code = GetLastError();
            return nullptr;
        }
        return env;
    }

    SECURITY_ATTRIBUTES
    security::create_attrs(const bool is_inherit,
                           PSECURITY_DESCRIPTOR security_descriptor) {
        SECURITY_ATTRIBUTES attrs;
        attrs.nLength = sizeof(SECURITY_ATTRIBUTES);
        attrs.bInheritHandle = is_inherit ? TRUE : FALSE;
        attrs.lpSecurityDescriptor = security_descriptor;
        return attrs;
    }

    SECURITY_DESCRIPTOR
    security::create_descriptor(const bool is_dacl_present,
                                ACL *acl,
                                const bool is_dacl_defaulted) {
        SECURITY_DESCRIPTOR sd{};
        do {
            if (!InitializeSecurityDescriptor(&sd,
                                              SECURITY_DESCRIPTOR_REVISION)) {
                error_code = GetLastError();
                break;
            }
            if (!SetSecurityDescriptorDacl(&sd, is_dacl_present ? TRUE : FALSE,
                                           acl,
                                           is_dacl_defaulted ? TRUE : FALSE)) {
                error_code = GetLastError();
                break;
            }
        } while (false);
        return sd;
    }

    bool
    security::is_valid_descriptor(PSECURITY_DESCRIPTOR security_descriptor) {
        return IsValidSecurityDescriptor(security_descriptor);
    }

    bool security::enable_privilege(HANDLE proc_handle,
                                    const wchar_t *privilege) {
        helper::autoclean<HANDLE> token_handle(nullptr);
        bool result = false;
        do {
            if (!OpenProcessToken(proc_handle, TOKEN_ADJUST_PRIVILEGES,
                                  token_handle)) {
                error_code = GetLastError();
                break;
            }
            TOKEN_PRIVILEGES tp;
            tp.PrivilegeCount = 1;
            if (!LookupPrivilegeValueW(nullptr, privilege,
                                       &tp.Privileges[0].Luid)) {
                error_code = GetLastError();
                break;
            }
            tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
            if (!AdjustTokenPrivileges(token_handle, FALSE, &tp, sizeof(tp),
                                       nullptr, nullptr)) {
                error_code = GetLastError();
                break;
            }
            result = (GetLastError() == ERROR_SUCCESS);
        } while (false);
        return result;
    }

    bool security::disable_privilege(HANDLE proc_handle,
                                     const wchar_t *privilege) {
        helper::autoclean<HANDLE> token_handle(nullptr);
        bool result = false;
        do {
            if (!OpenProcessToken(proc_handle, TOKEN_ADJUST_PRIVILEGES,
                                  token_handle)) {
                error_code = GetLastError();
                break;
            }
            TOKEN_PRIVILEGES tp;
            tp.PrivilegeCount = 1;
            if (!LookupPrivilegeValueW(nullptr, privilege,
                                       &tp.Privileges[0].Luid)) {
                error_code = GetLastError();
                break;
            }
            tp.Privileges[0].Attributes = 0;
            if (!AdjustTokenPrivileges(token_handle, FALSE, &tp, sizeof(tp),
                                       nullptr, nullptr)) {
                error_code = GetLastError();
                break;
            }
            result = (GetLastError() == ERROR_SUCCESS);
        } while (false);
        return result;
    }

    bool security::enable_privilege(uint32_t pid, const wchar_t *privilege) {
        bool result = false;
        do {
            helper::autoclean<HANDLE> proc_handle(nullptr);
            proc_handle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
            if (!proc_handle.is_ok()) {
                error_code = GetLastError();
                break;
            }
            result = enable_privilege(proc_handle, privilege);
        } while (false);
        return result;
    }

    bool security::disable_privilege(uint32_t pid, const wchar_t *privilege) {
        bool result = false;
        do {
            helper::autoclean<HANDLE> proc_handle(nullptr);
            proc_handle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
            if (!proc_handle.is_ok()) {
                error_code = GetLastError();
                break;
            }
            result = enable_privilege(proc_handle, privilege);
        } while (false);
        return result;
    }

    bool security::enable_debug(HANDLE proc_handle) {
        return enable_privilege(proc_handle, L"SeDebugPrivilege");
    }

    bool security::disable_debug(HANDLE proc_handle) {
        return disable_privilege(proc_handle, L"SeDebugPrivilege");
    }

    bool security::enable_debug(const uint32_t pid) {
        return enable_privilege(pid, L"SeDebugPrivilege");
    }

    bool security::disable_debug(const uint32_t pid) {
        return disable_privilege(pid, L"SeDebugPrivilege");
    }

    bool security::enable_sacl(HANDLE proc_handle) {
        return enable_privilege(proc_handle, L"SeSecurityPrivilege");
    }

    bool security::disable_sacl(HANDLE proc_handle) {
        return disable_privilege(proc_handle, L"SeSecurityPrivilege");
    }

    bool security::enable_sacl(const uint32_t pid) {
        return enable_privilege(pid, L"SeSecurityPrivilege");
    }

    bool security::disable_sacl(const uint32_t pid) {
        return disable_privilege(pid, L"SeSecurityPrivilege");
    }

    std::pair<TOKEN_ELEVATION_TYPE, bool>
    security::check_proc_elevation(HANDLE proc_handle) {
        HANDLE process_handle = proc_handle ? proc_handle : GetCurrentProcess();
        helper::autoclean<HANDLE> token_handle(nullptr);
        helper::autoclean<HANDLE> filter_token_handle(nullptr);
        TOKEN_ELEVATION_TYPE token_type = TokenElevationTypeDefault;
        int32_t is_admin = 0;
        unsigned long size = 0;
        do {
            if (!OpenProcessToken(process_handle, TOKEN_QUERY, token_handle)) {
                error_code = GetLastError();
                break;
            }
            if (!GetTokenInformation(token_handle, TokenElevationType,
                                     &token_type, sizeof(TOKEN_ELEVATION_TYPE),
                                     &size)) {
                error_code = GetLastError();
                break;
            }
            uint8_t admin_sid[SECURITY_MAX_SID_SIZE] = {};
            size = sizeof(admin_sid);
            if (!CreateWellKnownSid(WinBuiltinAdministratorsSid, nullptr,
                                    &admin_sid, &size)) {
                error_code = GetLastError();
                break;
            }
            if (token_type != TokenElevationTypeLimited) {
                is_admin = IsUserAnAdmin();
                break;
            }
            if (!GetTokenInformation(token_handle, TokenLinkedToken,
                                     &filter_token_handle, sizeof(HANDLE),
                                     &size)) {
                error_code = GetLastError();
                break;
            }
            if (!CheckTokenMembership(filter_token_handle, &admin_sid,
                                      &is_admin)) {
                error_code = GetLastError();
                break;
            }
        } while (false);
        return std::make_pair(token_type, is_admin);
    }

    IntegrityLevel security::check_proc_integrity_level(HANDLE proc_handle) {
        HANDLE process_handle = proc_handle ? proc_handle : GetCurrentProcess();
        helper::autoclean<HANDLE> token_handle(nullptr);
        auto security_level = SecurityLevel::Unknown;
        auto token_policy = TokenPolicy::Unknown;
        auto resource_level = ResourceLevel::Unknown;
        auto system_policy = SystemPolicy::Unknown;
        do {
            if (!OpenProcessToken(process_handle, TOKEN_READ, token_handle)) {
                error_code = GetLastError();
                break;
            }
            unsigned long size = 0;
            if (!GetTokenInformation(token_handle, TokenIntegrityLevel, nullptr,
                                     0, &size)) {
                error_code = GetLastError();
                if (error_code != ERROR_INSUFFICIENT_BUFFER) {
                    break;
                }
            }
            std::vector<uint8_t> buf(size, '\0');
            const auto token_info =
                    reinterpret_cast<TOKEN_MANDATORY_LABEL *>(buf.data());
            if (!GetTokenInformation(token_handle, TokenIntegrityLevel,
                                     token_info, size, &size)) {
                error_code = GetLastError();
                break;
            }
            const auto auth_count =
                    GetSidSubAuthorityCount(token_info->Label.Sid);
            error_code = GetLastError();
            if (error_code != ERROR_SUCCESS) {
                break;
            }
            const auto integrity_level =
                    GetSidSubAuthority(token_info->Label.Sid, *auth_count - 1);
            error_code = GetLastError();
            if (error_code != ERROR_SUCCESS) {
                break;
            }
            switch (*integrity_level) {
                case SECURITY_MANDATORY_UNTRUSTED_RID:
                    security_level = SecurityLevel::Untrusted;
                    break;
                case SECURITY_MANDATORY_LOW_RID:
                    security_level = SecurityLevel::Low;
                    break;
                case SECURITY_MANDATORY_MEDIUM_RID:
                    security_level = SecurityLevel::Medium;
                    break;
                case SECURITY_MANDATORY_MEDIUM_PLUS_RID:
                    security_level = SecurityLevel::MediumPlus;
                    break;
                case SECURITY_MANDATORY_HIGH_RID:
                    security_level = SecurityLevel::High;
                    break;
                case SECURITY_MANDATORY_SYSTEM_RID:
                    security_level = SecurityLevel::System;
                    break;
                case SECURITY_MANDATORY_PROTECTED_PROCESS_RID:
                    security_level = SecurityLevel::ProtectedProcess;
                    break;
                default:
                    security_level = SecurityLevel::Unknown;
            }

            size = sizeof(uint32_t);
            uint32_t policy = TOKEN_MANDATORY_POLICY_OFF;
            if (!GetTokenInformation(token_handle, TokenMandatoryPolicy,
                                     &policy, size, &size)) {
                error_code = GetLastError();
                break;
            }
            if (policy == TOKEN_MANDATORY_POLICY_OFF) {
                token_policy = TokenPolicy::Off;
            } else if ((policy & TOKEN_MANDATORY_POLICY_VALID_MASK) == 0) {
                token_policy = TokenPolicy::Unknown;
            } else if (policy & TOKEN_MANDATORY_POLICY_NO_WRITE_UP) {
                token_policy = TokenPolicy::NoWriteUp;
            } else if (policy & TOKEN_MANDATORY_POLICY_NEW_PROCESS_MIN) {
                token_policy = TokenPolicy::NewProcessMin;
            }

            ACL *sacl = nullptr;
            PSECURITY_DESCRIPTOR sd = nullptr;
            uint32_t ret = ERROR_SUCCESS;
            ret = GetSecurityInfo(process_handle, SE_KERNEL_OBJECT,
                                  LABEL_SECURITY_INFORMATION, nullptr, nullptr,
                                  nullptr, &sacl, &sd);
            if (ret != ERROR_SUCCESS) {
                error_code = ret;
                break;
            }
            if (!sacl) {
                break;
            }
            uint32_t resource = 0;
            uint32_t resource_policy = 0;
            SYSTEM_MANDATORY_LABEL_ACE *ace = nullptr;
            if (sacl->AceCount <= 0) {
                break;
            }
            if (!GetAce(sacl, 0, reinterpret_cast<void **>(&ace))) {
                error_code = GetLastError();
                break;
            }
            if (!ace) {
                break;
            }
            const auto sid_ptr = reinterpret_cast<SID *>(&ace->SidStart);
            resource = sid_ptr->SubAuthority[0];
            resource_policy = ace->Mask;

            switch (resource) {
                case SECURITY_MANDATORY_UNTRUSTED_RID:
                    resource_level = ResourceLevel::NotSet;
                    break;
                case SECURITY_MANDATORY_LOW_RID:
                    resource_level = ResourceLevel::Low;
                    break;
                case SECURITY_MANDATORY_MEDIUM_RID:
                    resource_level = ResourceLevel::Medium;
                    break;
                case SECURITY_MANDATORY_MEDIUM_PLUS_RID:
                    resource_level = ResourceLevel::MediumPlus;
                    break;
                case SECURITY_MANDATORY_HIGH_RID:
                    resource_level = ResourceLevel::High;
                    break;
                case SECURITY_MANDATORY_SYSTEM_RID:
                    resource_level = ResourceLevel::System;
                    break;
                case SECURITY_MANDATORY_PROTECTED_PROCESS_RID:
                    resource_level = ResourceLevel::ProtectedProcess;
                    break;
                default:
                    resource_level = ResourceLevel::Unknown;
            }

            if (resource_policy == 0) {
                system_policy = SystemPolicy::Zero;
            } else if ((resource_policy & TOKEN_MANDATORY_POLICY_VALID_MASK) ==
                       0) {
                system_policy = SystemPolicy::Unknown;
            } else if ((resource_policy & SYSTEM_MANDATORY_LABEL_NO_READ_UP) ==
                       SYSTEM_MANDATORY_LABEL_NO_READ_UP) {
                system_policy = SystemPolicy::NoReadUp;
            } else if ((resource_policy & SYSTEM_MANDATORY_LABEL_NO_WRITE_UP) ==
                       SYSTEM_MANDATORY_LABEL_NO_WRITE_UP) {
                system_policy = SystemPolicy::NoWriteUp;
            } else if ((resource_policy &
                        SYSTEM_MANDATORY_LABEL_NO_EXECUTE_UP) ==
                       SYSTEM_MANDATORY_LABEL_NO_EXECUTE_UP) {
                system_policy = SystemPolicy::NoExecuteUp;
            }
        } while (false);
        return std::make_tuple(security_level, token_policy, resource_level,
                               system_policy);
    }

    uint32_t security::err_code() const {
        return error_code;
    }

    std::string security::err_string() const {
        std::string result = helper::convert::err_string(error_code);
        return result;
    }

    std::wstring security::err_wstring() const {
        std::wstring result = helper::convert::err_wstring(error_code);
        return result;
    }
} // namespace YanLib::sys
