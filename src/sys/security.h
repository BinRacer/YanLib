//
// Created by forkernel on 2025/4/15.
//

#ifndef SECURITY_H
#define SECURITY_H
#include <Windows.h>
#include <string>
#include <tuple>

namespace YanLib::sys {
    class security {
    private:
        DWORD error_code = 0;

    public:
        security(const security &other) = delete;

        security(security &&other) = delete;

        security &operator=(const security &other) = delete;

        security &operator=(security &&other) = delete;

        security();

        ~security();

        // SE_DEBUG_NAME = TEXT("SeDebugPrivilege")
        bool enable_privilege(HANDLE ProcessHandle,
                              const wchar_t *szPrivilege = L"SeDebugPrivilege");

        // SE_DEBUG_NAME = TEXT("SeDebugPrivilege")
        bool disable_privilege(HANDLE ProcessHandle,
                               const wchar_t *szPrivilege = L"SeDebugPrivilege");

        // SE_DEBUG_NAME = TEXT("SeDebugPrivilege")
        bool enable_privilege(DWORD ProcessID,
                              const wchar_t *szPrivilege = L"SeDebugPrivilege");

        // SE_DEBUG_NAME = TEXT("SeDebugPrivilege")
        bool disable_privilege(DWORD ProcessID,
                               const wchar_t *szPrivilege = L"SeDebugPrivilege");

        // SE_DEBUG_NAME = TEXT("SeDebugPrivilege")
        bool enable_debug(HANDLE ProcessHandle);

        // SE_DEBUG_NAME = TEXT("SeDebugPrivilege")
        bool disable_debug(HANDLE ProcessHandle);

        // SE_DEBUG_NAME = TEXT("SeDebugPrivilege")
        bool enable_debug(DWORD ProcessID);

        // SE_DEBUG_NAME = TEXT("SeDebugPrivilege")
        bool disable_debug(DWORD ProcessID);

        // SE_SECURITY_NAME = TEXT("SeSecurityPrivilege")
        bool enable_sacl(HANDLE ProcessHandle);

        // SE_SECURITY_NAME = TEXT("SeSecurityPrivilege")
        bool disable_sacl(HANDLE ProcessHandle);

        // SE_SECURITY_NAME = TEXT("SeSecurityPrivilege")
        bool enable_sacl(DWORD ProcessID);

        // SE_SECURITY_NAME = TEXT("SeSecurityPrivilege")
        bool disable_sacl(DWORD ProcessID);

        std::pair<TOKEN_ELEVATION_TYPE, bool>
        check_proc_elevation(HANDLE ProcessHandle = nullptr);

        enum SecurityLevel {
            SECURITY_UNTRUSTED,
            SECURITY_LOW,
            SECURITY_MEDIUM,
            SECURITY_MEDIUM_PLUS,
            SECURITY_HIGH,
            SECURITY_SYSTEM,
            SECURITY_PROTECTED_PROCESS,
            SECURITY_UNKNOWN,
        };

        enum TokenPolicy {
            TOKEN_OFF,
            TOKEN_NO_WRITE_UP,
            TOKEN_NEW_PROCESS_MIN,
            TOKEN_UNKNOWN
        };

        enum ResourceLevel {
            RESOURCE_LOW,
            RESOURCE_MEDIUM,
            RESOURCE_MEDIUM_PLUS,
            RESOURCE_HIGH,
            RESOURCE_SYSTEM,
            RESOURCE_PROTECTED_PROCESS,
            RESOURCE_NOT_SET,
            RESOURCE_UNKNOWN,
        };

        enum SystemPolicy {
            SYSTEM_ZERO,
            SYSTEM_NO_READ_UP,
            SYSTEM_NO_WRITE_UP,
            SYSTEM_NO_NO_EXECUTE_UP,
            SYSTEM_UNKNOWN
        };

        std::tuple<SecurityLevel,
            TokenPolicy,
            ResourceLevel,
            SystemPolicy>
        check_proc_integrity_level(HANDLE ProcessHandle = nullptr);

        DWORD err_code() const;

        std::string err_string() const;

        std::wstring err_wstring() const;
    };
}


#endif //SECURITY_H
