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
        void *env = nullptr;
        DWORD error_code = 0;

        void cleanup();

    public:
        security(const security &other) = delete;

        security(security &&other) = delete;

        security &operator=(const security &other) = delete;

        security &operator=(security &&other) = delete;

        security() = default;

        ~security();

        [[nodiscard]] DWORD curr_session_id() const;

        HANDLE curr_session_token(ULONG session_id = 0);

        HANDLE copy_token(HANDLE existing_token_handle = nullptr,
                          DWORD desired_access = MAXIMUM_ALLOWED,
                          LPSECURITY_ATTRIBUTES token_attrs = nullptr,
                          SECURITY_IMPERSONATION_LEVEL impersonation_level = SecurityIdentification,
                          TOKEN_TYPE token_type = TokenPrimary);

        void *create_env_block(HANDLE token_handle,
                               bool is_inherit = false);

        SECURITY_ATTRIBUTES create_attrs(bool is_inherit = true,
                                         PSECURITY_DESCRIPTOR security_descriptor = nullptr);

        SECURITY_DESCRIPTOR create_descriptor(bool is_dacl_present = true,
                                              PACL pDacl = nullptr,
                                              bool is_dacl_defaulted = false);

        bool is_valid_descriptor(PSECURITY_DESCRIPTOR security_descriptor);

        // SE_DEBUG_NAME = TEXT("SeDebugPrivilege")
        bool enable_privilege(HANDLE proc_handle,
                              const wchar_t *privilege = L"SeDebugPrivilege");

        // SE_DEBUG_NAME = TEXT("SeDebugPrivilege")
        bool disable_privilege(HANDLE proc_handle,
                               const wchar_t *privilege = L"SeDebugPrivilege");

        // SE_DEBUG_NAME = TEXT("SeDebugPrivilege")
        bool enable_privilege(DWORD pid,
                              const wchar_t *privilege = L"SeDebugPrivilege");

        // SE_DEBUG_NAME = TEXT("SeDebugPrivilege")
        bool disable_privilege(DWORD pid,
                               const wchar_t *privilege = L"SeDebugPrivilege");

        // SE_DEBUG_NAME = TEXT("SeDebugPrivilege")
        bool enable_debug(HANDLE proc_handle);

        // SE_DEBUG_NAME = TEXT("SeDebugPrivilege")
        bool disable_debug(HANDLE proc_handle);

        // SE_DEBUG_NAME = TEXT("SeDebugPrivilege")
        bool enable_debug(DWORD pid);

        // SE_DEBUG_NAME = TEXT("SeDebugPrivilege")
        bool disable_debug(DWORD pid);

        // SE_SECURITY_NAME = TEXT("SeSecurityPrivilege")
        bool enable_sacl(HANDLE proc_handle);

        // SE_SECURITY_NAME = TEXT("SeSecurityPrivilege")
        bool disable_sacl(HANDLE proc_handle);

        // SE_SECURITY_NAME = TEXT("SeSecurityPrivilege")
        bool enable_sacl(DWORD pid);

        // SE_SECURITY_NAME = TEXT("SeSecurityPrivilege")
        bool disable_sacl(DWORD pid);

        std::pair<TOKEN_ELEVATION_TYPE, bool>
        check_proc_elevation(HANDLE proc_handle = nullptr);

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
        check_proc_integrity_level(HANDLE proc_handle = nullptr);

        [[nodiscard]] DWORD err_code() const;

        [[nodiscard]] std::string err_string() const;

        [[nodiscard]] std::wstring err_wstring() const;
    };
}


#endif //SECURITY_H
