//
// Created by forkernel on 2025/4/15.
//

#include "security.h"
#include "helper/convert.h"
#include "helper/autoclean.h"
#include <shlobj.h>
#include <aclapi.h>
#include <memory>
#include <vector>
#include <WtsApi32.h>
#include <UserEnv.h>
#pragma comment(lib, "WtsApi32.lib")
#pragma comment(lib, "UserEnv.lib")

namespace YanLib::sys {
    security::~security() {
        cleanup();
        if (!token_handles.empty()) {
            for (auto &token_handle: token_handles) {
                CloseHandle(token_handle);
                token_handle = nullptr;
            }
            token_handles.clear();
        }
    }

    void security::cleanup() {
        if (env) {
            DestroyEnvironmentBlock(env);
            env = nullptr;
        }
    }

    DWORD security::curr_session_id() const {
        return WTSGetActiveConsoleSessionId();
    }

    HANDLE security::curr_session_token(ULONG session_id) {
        ULONG id = (session_id == 0) ? curr_session_id() : session_id;
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

    HANDLE security::copy_token(
        HANDLE existing_token_handle,
        DWORD desired_access,
        SECURITY_ATTRIBUTES *token_attrs,
        SECURITY_IMPERSONATION_LEVEL impersonation_level,
        TOKEN_TYPE token_type) {
        HANDLE token_handle = existing_token_handle
                                  ? existing_token_handle
                                  : curr_session_token();
        if (!token_handle) {
            return nullptr;
        }
        HANDLE ret_token = nullptr;
        if (!DuplicateTokenEx(token_handle,
                              desired_access,
                              token_attrs,
                              impersonation_level,
                              token_type,
                              &ret_token)) {
            error_code = GetLastError();
            return nullptr;
        }
        rwlock.write_lock();
        token_handles.push_back(ret_token);
        rwlock.write_unlock();
        return ret_token;
    }

    void *security::create_env_block(HANDLE token_handle, bool is_inherit) {
        if (env) {
            cleanup();
        }
        if (!CreateEnvironmentBlock(&env,
                                    token_handle,
                                    is_inherit ? TRUE : FALSE)) {
            error_code = GetLastError();
            return nullptr;
        }
        return env;
    }

    SECURITY_ATTRIBUTES security::create_attrs(
        bool is_inherit,
        PSECURITY_DESCRIPTOR security_descriptor) {
        SECURITY_ATTRIBUTES attrs;
        attrs.nLength = sizeof(SECURITY_ATTRIBUTES);
        attrs.bInheritHandle = is_inherit ? TRUE : FALSE;
        attrs.lpSecurityDescriptor = security_descriptor;
        return attrs;
    }

    SECURITY_DESCRIPTOR security::create_descriptor(bool is_dacl_present,
                                                    ACL *acl,
                                                    bool is_dacl_defaulted) {
        SECURITY_DESCRIPTOR sd;
        do {
            if (!InitializeSecurityDescriptor(
                &sd,
                SECURITY_DESCRIPTOR_REVISION)) {
                error_code = GetLastError();
                break;
            }
            if (!SetSecurityDescriptorDacl(&sd,
                                           is_dacl_present
                                               ? TRUE
                                               : FALSE,
                                           acl,
                                           is_dacl_defaulted
                                               ? TRUE
                                               : FALSE)) {
                error_code = GetLastError();
                break;
            }
        } while (false);
        return sd;
    }

    bool security::is_valid_descriptor(PSECURITY_DESCRIPTOR security_descriptor) {
        return IsValidSecurityDescriptor(security_descriptor);
    }

    bool security::enable_privilege(HANDLE proc_handle,
                                    const wchar_t *privilege) {
        helper::autoclean<HANDLE> token_handle(nullptr);
        do {
            if (!OpenProcessToken(proc_handle,
                                  TOKEN_ADJUST_PRIVILEGES,
                                  token_handle)) {
                error_code = GetLastError();
                break;
            }
            TOKEN_PRIVILEGES tp;
            tp.PrivilegeCount = 1;
            if (!LookupPrivilegeValueW(nullptr,
                                       privilege,
                                       &tp.Privileges[0].Luid)) {
                error_code = GetLastError();
                break;
            }
            tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
            if (!AdjustTokenPrivileges(token_handle,
                                       FALSE,
                                       &tp,
                                       sizeof(tp),
                                       nullptr,
                                       nullptr)) {
                error_code = GetLastError();
                break;
            }
            return (GetLastError() == ERROR_SUCCESS);
        } while (false);
        return false;
    }

    bool security::disable_privilege(HANDLE proc_handle,
                                     const wchar_t *privilege) {
        helper::autoclean<HANDLE> token_handle(nullptr);
        do {
            if (!OpenProcessToken(proc_handle,
                                  TOKEN_ADJUST_PRIVILEGES,
                                  token_handle)) {
                error_code = GetLastError();
                break;
            }
            TOKEN_PRIVILEGES tp;
            tp.PrivilegeCount = 1;
            if (!LookupPrivilegeValueW(nullptr,
                                       privilege,
                                       &tp.Privileges[0].Luid)) {
                error_code = GetLastError();
                break;
            }
            tp.Privileges[0].Attributes = 0;
            if (!AdjustTokenPrivileges(token_handle,
                                       FALSE,
                                       &tp,
                                       sizeof(tp),
                                       nullptr,
                                       nullptr)) {
                error_code = GetLastError();
                break;
            }
            return (GetLastError() == ERROR_SUCCESS);
        } while (false);
        return false;
    }

    bool security::enable_privilege(DWORD pid, const wchar_t *privilege) {
        do {
            helper::autoclean<HANDLE> proc_handle(nullptr);
            proc_handle = OpenProcess(PROCESS_ALL_ACCESS,
                                      FALSE,
                                      pid);
            if (!proc_handle.is_ok()) {
                error_code = GetLastError();
                break;
            }
            return enable_privilege(proc_handle, privilege);
        } while (false);
        return false;
    }

    bool security::disable_privilege(DWORD pid, const wchar_t *privilege) {
        do {
            helper::autoclean<HANDLE> proc_handle(nullptr);
            proc_handle = OpenProcess(PROCESS_ALL_ACCESS,
                                      FALSE,
                                      pid);
            if (!proc_handle.is_ok()) {
                error_code = GetLastError();
                break;
            }
            return enable_privilege(proc_handle, privilege);
        } while (false);
        return false;
    }

    bool security::enable_debug(HANDLE proc_handle) {
        return enable_privilege(proc_handle, L"SeDebugPrivilege");
    }

    bool security::disable_debug(HANDLE proc_handle) {
        return disable_privilege(proc_handle, L"SeDebugPrivilege");
    }

    bool security::enable_debug(DWORD pid) {
        return enable_privilege(pid, L"SeDebugPrivilege");
    }

    bool security::disable_debug(DWORD pid) {
        return disable_privilege(pid, L"SeDebugPrivilege");
    }

    bool security::enable_sacl(HANDLE proc_handle) {
        return enable_privilege(proc_handle, L"SeSecurityPrivilege");
    }

    bool security::disable_sacl(HANDLE proc_handle) {
        return disable_privilege(proc_handle, L"SeSecurityPrivilege");
    }

    bool security::enable_sacl(DWORD pid) {
        return enable_privilege(pid, L"SeSecurityPrivilege");
    }

    bool security::disable_sacl(DWORD pid) {
        return disable_privilege(pid, L"SeSecurityPrivilege");
    }

    std::pair<TOKEN_ELEVATION_TYPE, bool> security::check_proc_elevation(
        HANDLE proc_handle) {
        HANDLE process_handle = proc_handle ? proc_handle : GetCurrentProcess();
        helper::autoclean<HANDLE> token_handle(nullptr);
        helper::autoclean<HANDLE> filter_token_handle(nullptr);
        TOKEN_ELEVATION_TYPE token_type = TokenElevationTypeDefault;
        int is_admin = 0;
        DWORD size = 0;
        do {
            if (!OpenProcessToken(process_handle,
                                  TOKEN_QUERY,
                                  token_handle)) {
                error_code = GetLastError();
                break;
            }
            if (!GetTokenInformation(
                token_handle,
                TokenElevationType,
                &token_type,
                sizeof(TOKEN_ELEVATION_TYPE),
                &size)) {
                error_code = GetLastError();
                break;
            }
            uint8_t admin_sid[SECURITY_MAX_SID_SIZE] = {};
            size = sizeof(admin_sid);
            if (!CreateWellKnownSid(WinBuiltinAdministratorsSid,
                                    nullptr,
                                    &admin_sid,
                                    &size)) {
                error_code = GetLastError();
                break;
            }
            if (token_type != TokenElevationTypeLimited) {
                is_admin = IsUserAnAdmin();
                break;
            }
            if (!GetTokenInformation(token_handle,
                                     TokenLinkedToken,
                                     &filter_token_handle,
                                     sizeof(HANDLE),
                                     &size)) {
                error_code = GetLastError();
                break;
            }
            if (!CheckTokenMembership(filter_token_handle,
                                      &admin_sid,
                                      &is_admin)) {
                error_code = GetLastError();
                break;
            }
        } while (false);
        return std::make_pair(token_type, is_admin);
    }

    std::tuple<security::SecurityLevel,
        security::TokenPolicy,
        security::ResourceLevel,
        security::SystemPolicy>
    security::check_proc_integrity_level(HANDLE proc_handle) {
        HANDLE process_handle = proc_handle
                                    ? proc_handle
                                    : GetCurrentProcess();
        helper::autoclean<HANDLE> token_handle(nullptr);
        SecurityLevel security_level = SECURITY_UNKNOWN;
        TokenPolicy token_policy = TOKEN_UNKNOWN;
        ResourceLevel resource_level = RESOURCE_UNKNOWN;
        SystemPolicy system_policy = SYSTEM_UNKNOWN;
        do {
            if (!OpenProcessToken(process_handle,
                                  TOKEN_READ,
                                  token_handle)) {
                error_code = GetLastError();
                break;
            }
            DWORD size = 0;
            if (!GetTokenInformation(token_handle,
                                     TokenIntegrityLevel,
                                     nullptr,
                                     0,
                                     &size)) {
                error_code = GetLastError();
                if (error_code != ERROR_INSUFFICIENT_BUFFER) {
                    break;
                }
            }
            std::vector<uint8_t> buf(size, '\0');
            auto token_info =
                    reinterpret_cast<TOKEN_MANDATORY_LABEL *>(buf.data());
            if (!GetTokenInformation(token_handle,
                                     TokenIntegrityLevel,
                                     token_info,
                                     size,
                                     &size)) {
                error_code = GetLastError();
                break;
            }
            auto auth_count =
                    GetSidSubAuthorityCount(token_info->Label.Sid);
            error_code = GetLastError();
            if (error_code != ERROR_SUCCESS) {
                break;
            }
            auto integrity_level =
                    GetSidSubAuthority(token_info->Label.Sid,
                                       *auth_count - 1);
            error_code = GetLastError();
            if (error_code != ERROR_SUCCESS) {
                break;
            }
            switch (*integrity_level) {
                case SECURITY_MANDATORY_UNTRUSTED_RID:
                    security_level = SECURITY_UNTRUSTED;
                    break;
                case SECURITY_MANDATORY_LOW_RID:
                    security_level = SECURITY_LOW;
                    break;
                case SECURITY_MANDATORY_MEDIUM_RID:
                    security_level = SECURITY_MEDIUM;
                    break;
                case SECURITY_MANDATORY_MEDIUM_PLUS_RID:
                    security_level = SECURITY_MEDIUM_PLUS;
                    break;
                case SECURITY_MANDATORY_HIGH_RID:
                    security_level = SECURITY_HIGH;
                    break;
                case SECURITY_MANDATORY_SYSTEM_RID:
                    security_level = SECURITY_SYSTEM;
                    break;
                case SECURITY_MANDATORY_PROTECTED_PROCESS_RID:
                    security_level = SECURITY_PROTECTED_PROCESS;
                    break;
                default:
                    security_level = SECURITY_UNKNOWN;
            }

            size = sizeof(DWORD);
            DWORD policy = TOKEN_MANDATORY_POLICY_OFF;
            if (!GetTokenInformation(token_handle,
                                     TokenMandatoryPolicy,
                                     &policy,
                                     size, &size)) {
                error_code = GetLastError();
                break;
            }
            if (policy == TOKEN_MANDATORY_POLICY_OFF) {
                token_policy = TOKEN_OFF;
            } else if ((policy & TOKEN_MANDATORY_POLICY_VALID_MASK) == 0) {
                token_policy = TOKEN_UNKNOWN;
            } else if (policy & TOKEN_MANDATORY_POLICY_NO_WRITE_UP) {
                token_policy = TOKEN_NO_WRITE_UP;
            } else if (policy & TOKEN_MANDATORY_POLICY_NEW_PROCESS_MIN) {
                token_policy = TOKEN_NEW_PROCESS_MIN;
            }

            ACL *sacl = nullptr;
            PSECURITY_DESCRIPTOR sd = nullptr;
            DWORD ret = ERROR_SUCCESS;
            ret = GetSecurityInfo(process_handle,
                                  SE_KERNEL_OBJECT,
                                  LABEL_SECURITY_INFORMATION,
                                  nullptr,
                                  nullptr,
                                  nullptr,
                                  &sacl,
                                  &sd);
            if (ret != ERROR_SUCCESS) {
                error_code = ret;
                break;
            }
            if (!sacl) {
                break;
            }
            DWORD resource = 0;
            DWORD resource_policy = 0;
            SYSTEM_MANDATORY_LABEL_ACE *ace = nullptr;
            if (sacl->AceCount <= 0) {
                break;
            }
            if (!GetAce(sacl,
                        0,
                        reinterpret_cast<void **>(&ace))) {
                error_code = GetLastError();
                break;
            }
            if (!ace) {
                break;
            }
            SID *sid_ptr = reinterpret_cast<SID *>(&ace->SidStart);
            resource = sid_ptr->SubAuthority[0];
            resource_policy = ace->Mask;

            switch (resource) {
                case SECURITY_MANDATORY_UNTRUSTED_RID:
                    resource_level = RESOURCE_NOT_SET;
                    break;
                case SECURITY_MANDATORY_LOW_RID:
                    resource_level = RESOURCE_LOW;
                    break;
                case SECURITY_MANDATORY_MEDIUM_RID:
                    resource_level = RESOURCE_MEDIUM;
                    break;
                case SECURITY_MANDATORY_MEDIUM_PLUS_RID:
                    resource_level = RESOURCE_MEDIUM_PLUS;
                    break;
                case SECURITY_MANDATORY_HIGH_RID:
                    resource_level = RESOURCE_HIGH;
                    break;
                case SECURITY_MANDATORY_SYSTEM_RID:
                    resource_level = RESOURCE_SYSTEM;
                    break;
                case SECURITY_MANDATORY_PROTECTED_PROCESS_RID:
                    resource_level = RESOURCE_PROTECTED_PROCESS;
                    break;
                default:
                    resource_level = RESOURCE_UNKNOWN;
            }

            if (resource_policy == 0) {
                system_policy = SYSTEM_ZERO;
            } else if ((resource_policy & TOKEN_MANDATORY_POLICY_VALID_MASK)
                       == 0) {
                system_policy = SYSTEM_UNKNOWN;
            } else if ((resource_policy & SYSTEM_MANDATORY_LABEL_NO_READ_UP)
                       == SYSTEM_MANDATORY_LABEL_NO_READ_UP) {
                system_policy = SYSTEM_NO_READ_UP;
            } else if ((resource_policy & SYSTEM_MANDATORY_LABEL_NO_WRITE_UP)
                       == SYSTEM_MANDATORY_LABEL_NO_WRITE_UP) {
                system_policy = SYSTEM_NO_WRITE_UP;
            } else if ((resource_policy & SYSTEM_MANDATORY_LABEL_NO_EXECUTE_UP)
                       == SYSTEM_MANDATORY_LABEL_NO_EXECUTE_UP) {
                system_policy = SYSTEM_NO_NO_EXECUTE_UP;
            }
        } while (false);
        return std::make_tuple(security_level,
                               token_policy,
                               resource_level,
                               system_policy);
    }

    DWORD security::err_code() const {
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
}
