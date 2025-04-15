//
// Created by forkernel on 2025/4/15.
//

#include "security.h"
#include "../helper/convert.h"
#include "../helper/autoclean.h"
#include <shlobj.h>
#include <aclapi.h>
#include <vector>

namespace YanLib::sys {
    security::security() {
    }

    security::~security() {
    }

    bool security::enable_privilege(HANDLE ProcessHandle,
                                    const wchar_t *szPrivilege) {
        helper::autoclean<HANDLE> hToken({});
        do {
            if (!OpenProcessToken(ProcessHandle,
                                  TOKEN_ADJUST_PRIVILEGES,
                                  &(hToken.get()))) {
                error_code = GetLastError();
                break;
            }
            TOKEN_PRIVILEGES tp;
            tp.PrivilegeCount = 1;
            if (!LookupPrivilegeValueW(nullptr,
                                       szPrivilege,
                                       &tp.Privileges[0].Luid)) {
                error_code = GetLastError();
                break;
            }
            tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
            if (!AdjustTokenPrivileges(hToken.get(),
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

    bool security::disable_privilege(HANDLE ProcessHandle,
                                     const wchar_t *szPrivilege) {
        helper::autoclean<HANDLE> hToken({});
        do {
            if (!OpenProcessToken(ProcessHandle,
                                  TOKEN_ADJUST_PRIVILEGES,
                                  &(hToken.get()))) {
                error_code = GetLastError();
                break;
            }
            TOKEN_PRIVILEGES tp;
            tp.PrivilegeCount = 1;
            if (!LookupPrivilegeValueW(nullptr,
                                       szPrivilege,
                                       &tp.Privileges[0].Luid)) {
                error_code = GetLastError();
                break;
            }
            tp.Privileges[0].Attributes = 0;
            if (!AdjustTokenPrivileges(hToken.get(),
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

    bool security::enable_privilege(DWORD ProcessID, const wchar_t *szPrivilege) {
        do {
            helper::autoclean<HANDLE> ProcessHandle({});
            ProcessHandle.get() = OpenProcess(PROCESS_ALL_ACCESS,
                                              FALSE,
                                              ProcessID);
            if (!ProcessHandle.get()) {
                error_code = GetLastError();
                break;
            }
            return enable_privilege(ProcessHandle.get(), szPrivilege);
        } while (false);
        return false;
    }

    bool security::disable_privilege(DWORD ProcessID, const wchar_t *szPrivilege) {
        do {
            helper::autoclean<HANDLE> ProcessHandle({});
            ProcessHandle.get() = OpenProcess(PROCESS_ALL_ACCESS,
                                              FALSE,
                                              ProcessID);
            if (!ProcessHandle.get()) {
                error_code = GetLastError();
                break;
            }
            return enable_privilege(ProcessHandle.get(), szPrivilege);
        } while (false);
        return false;
    }

    bool security::enable_debug(HANDLE ProcessHandle) {
        return enable_privilege(ProcessHandle, L"SeDebugPrivilege");
    }

    bool security::disable_debug(HANDLE ProcessHandle) {
        return disable_privilege(ProcessHandle, L"SeDebugPrivilege");
    }

    bool security::enable_debug(DWORD ProcessID) {
        return enable_privilege(ProcessID, L"SeDebugPrivilege");
    }

    bool security::disable_debug(DWORD ProcessID) {
        return disable_privilege(ProcessID, L"SeDebugPrivilege");
    }

    bool security::enable_sacl(HANDLE ProcessHandle) {
        return enable_privilege(ProcessHandle, L"SeSecurityPrivilege");
    }

    bool security::disable_sacl(HANDLE ProcessHandle) {
        return disable_privilege(ProcessHandle, L"SeSecurityPrivilege");
    }

    bool security::enable_sacl(DWORD ProcessID) {
        return enable_privilege(ProcessID, L"SeSecurityPrivilege");
    }

    bool security::disable_sacl(DWORD ProcessID) {
        return disable_privilege(ProcessID, L"SeSecurityPrivilege");
    }

    std::pair<TOKEN_ELEVATION_TYPE, bool>
    security::check_proc_elevation(HANDLE ProcessHandle) {
        HANDLE hProc = ProcessHandle ? ProcessHandle : GetCurrentProcess();
        helper::autoclean<HANDLE> hToken({});
        helper::autoclean<HANDLE> hFilterToken({});
        TOKEN_ELEVATION_TYPE token_type = TokenElevationTypeDefault;
        BOOL is_admin = FALSE;
        DWORD dwSize = 0;
        do {
            if (!OpenProcessToken(hProc,
                                  TOKEN_QUERY,
                                  &(hToken.get()))) {
                error_code = GetLastError();
                break;
            }
            if (!GetTokenInformation(hToken.get(),
                                     TokenElevationType,
                                     &token_type,
                                     sizeof(TOKEN_ELEVATION_TYPE),
                                     &dwSize)) {
                error_code = GetLastError();
                break;
            }
            uint8_t adminSID[SECURITY_MAX_SID_SIZE] = {};
            dwSize = sizeof(adminSID);
            if (!CreateWellKnownSid(WinBuiltinAdministratorsSid,
                                    nullptr,
                                    &adminSID,
                                    &dwSize)) {
                error_code = GetLastError();
                break;
            }
            if (token_type != TokenElevationTypeLimited) {
                is_admin = IsUserAnAdmin();
                break;
            }
            if (!GetTokenInformation(hToken.get(),
                                     TokenLinkedToken,
                                     &(hFilterToken.get()),
                                     sizeof(HANDLE),
                                     &dwSize)) {
                error_code = GetLastError();
                break;
            }
            if (!CheckTokenMembership(hFilterToken.get(), &adminSID, &is_admin)) {
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
    security::check_proc_integrity_level(HANDLE ProcessHandle) {
        HANDLE hProc = ProcessHandle ? ProcessHandle : GetCurrentProcess();
        helper::autoclean<HANDLE> hToken({});
        SecurityLevel securityLevel = SECURITY_UNKNOWN;
        TokenPolicy tokenPolicy = TOKEN_UNKNOWN;
        ResourceLevel resourceLevel = RESOURCE_UNKNOWN;
        SystemPolicy systemPolicy = SYSTEM_UNKNOWN;
        do {
            if (!OpenProcessToken(hProc,
                                  TOKEN_READ,
                                  &(hToken.get()))) {
                error_code = GetLastError();
                break;
            }
            DWORD dwSize = 0;
            if (!GetTokenInformation(hToken.get(),
                                     TokenIntegrityLevel,
                                     nullptr,
                                     0,
                                     &dwSize)) {
                error_code = GetLastError();
                if (error_code != ERROR_INSUFFICIENT_BUFFER) {
                    break;
                }
            }
            std::vector<uint8_t> buf(dwSize, '\0');
            PTOKEN_MANDATORY_LABEL tokenInfo = reinterpret_cast<PTOKEN_MANDATORY_LABEL>(buf.data());
            if (!GetTokenInformation(hToken.get(),
                                     TokenIntegrityLevel,
                                     tokenInfo,
                                     dwSize,
                                     &dwSize)) {
                error_code = GetLastError();
                break;
            }
            auto authCount = GetSidSubAuthorityCount(tokenInfo->Label.Sid);
            error_code = GetLastError();
            if (error_code != ERROR_SUCCESS) {
                break;
            }
            auto integrity_level = GetSidSubAuthority(tokenInfo->Label.Sid,
                                                      *authCount - 1);
            error_code = GetLastError();
            if (error_code != ERROR_SUCCESS) {
                break;
            }
            switch (*integrity_level) {
                case SECURITY_MANDATORY_UNTRUSTED_RID:
                    securityLevel = SECURITY_UNTRUSTED;
                    break;
                case SECURITY_MANDATORY_LOW_RID:
                    securityLevel = SECURITY_LOW;
                    break;
                case SECURITY_MANDATORY_MEDIUM_RID:
                    securityLevel = SECURITY_MEDIUM;
                    break;
                case SECURITY_MANDATORY_MEDIUM_PLUS_RID:
                    securityLevel = SECURITY_MEDIUM_PLUS;
                    break;
                case SECURITY_MANDATORY_HIGH_RID:
                    securityLevel = SECURITY_HIGH;
                    break;
                case SECURITY_MANDATORY_SYSTEM_RID:
                    securityLevel = SECURITY_SYSTEM;
                    break;
                case SECURITY_MANDATORY_PROTECTED_PROCESS_RID:
                    securityLevel = SECURITY_PROTECTED_PROCESS;
                    break;
                default:
                    securityLevel = SECURITY_UNKNOWN;
            }

            dwSize = sizeof(DWORD);
            DWORD policy = TOKEN_MANDATORY_POLICY_OFF;
            if (!GetTokenInformation(hToken.get(),
                                     TokenMandatoryPolicy,
                                     &policy,
                                     dwSize, &dwSize)) {
                error_code = GetLastError();
                break;
            }
            if (policy == TOKEN_MANDATORY_POLICY_OFF) {
                tokenPolicy = TOKEN_OFF;
            } else if ((policy & TOKEN_MANDATORY_POLICY_VALID_MASK) == 0) {
                tokenPolicy = TOKEN_UNKNOWN;
            } else if (policy & TOKEN_MANDATORY_POLICY_NO_WRITE_UP) {
                tokenPolicy = TOKEN_NO_WRITE_UP;
            } else if (policy & TOKEN_MANDATORY_POLICY_NEW_PROCESS_MIN) {
                tokenPolicy = TOKEN_NEW_PROCESS_MIN;
            }

            PACL sacl = nullptr;
            PSECURITY_DESCRIPTOR sd = nullptr;
            DWORD dwRet = ERROR_SUCCESS;
            dwRet = GetSecurityInfo(hProc,
                                    SE_KERNEL_OBJECT,
                                    LABEL_SECURITY_INFORMATION,
                                    nullptr,
                                    nullptr,
                                    nullptr,
                                    &sacl,
                                    &sd);
            if (dwRet != ERROR_SUCCESS) {
                error_code = dwRet;
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
            if (!GetAce(sacl, 0, reinterpret_cast<void **>(&ace))) {
                error_code = GetLastError();
                break;
            }
            if (!ace) {
                break;
            }
            SID *pSID = reinterpret_cast<SID *>(&ace->SidStart);
            resource = pSID->SubAuthority[0];
            resource_policy = ace->Mask;

            switch (resource) {
                case SECURITY_MANDATORY_UNTRUSTED_RID:
                    resourceLevel = RESOURCE_NOT_SET;
                    break;
                case SECURITY_MANDATORY_LOW_RID:
                    resourceLevel = RESOURCE_LOW;
                    break;
                case SECURITY_MANDATORY_MEDIUM_RID:
                    resourceLevel = RESOURCE_MEDIUM;
                    break;
                case SECURITY_MANDATORY_MEDIUM_PLUS_RID:
                    resourceLevel = RESOURCE_MEDIUM_PLUS;
                    break;
                case SECURITY_MANDATORY_HIGH_RID:
                    resourceLevel = RESOURCE_HIGH;
                    break;
                case SECURITY_MANDATORY_SYSTEM_RID:
                    resourceLevel = RESOURCE_SYSTEM;
                    break;
                case SECURITY_MANDATORY_PROTECTED_PROCESS_RID:
                    resourceLevel = RESOURCE_PROTECTED_PROCESS;
                    break;
                default:
                    resourceLevel = RESOURCE_UNKNOWN;
            }

            if (resource_policy == 0) {
                systemPolicy = SYSTEM_ZERO;
            } else if ((resource_policy & TOKEN_MANDATORY_POLICY_VALID_MASK) == 0) {
                systemPolicy = SYSTEM_UNKNOWN;
            } else if ((resource_policy & SYSTEM_MANDATORY_LABEL_NO_READ_UP) ==
                       SYSTEM_MANDATORY_LABEL_NO_READ_UP) {
                systemPolicy = SYSTEM_NO_READ_UP;
            } else if ((resource_policy & SYSTEM_MANDATORY_LABEL_NO_WRITE_UP) ==
                       SYSTEM_MANDATORY_LABEL_NO_WRITE_UP) {
                systemPolicy = SYSTEM_NO_WRITE_UP;
            } else if ((resource_policy & SYSTEM_MANDATORY_LABEL_NO_EXECUTE_UP) ==
                       SYSTEM_MANDATORY_LABEL_NO_EXECUTE_UP) {
                systemPolicy = SYSTEM_NO_NO_EXECUTE_UP;
            }
        } while (false);
        return std::make_tuple(securityLevel,
                               tokenPolicy,
                               resourceLevel,
                               systemPolicy);
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
