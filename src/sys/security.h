/* clang-format off */
/*
 * @file security.h
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
#ifndef SECURITY_H
#define SECURITY_H
#include <Windows.h>
#include <string>
#include <tuple>
#include <vector>
#include "sync/rwlock.h"

namespace YanLib::sys {
#ifndef SECURITYLEVEL
#define SECURITYLEVEL

    enum class SecurityLevel : uint8_t {
        Untrusted,
        Low,
        Medium,
        MediumPlus,
        High,
        System,
        ProtectedProcess,
        Unknown,
    };
#endif
#ifndef TOKENPOLICY
#define TOKENPOLICY

    enum class TokenPolicy : uint8_t { Off, NoWriteUp, NewProcessMin, Unknown };
#endif
#ifndef RESOURCELEVEL
#define RESOURCELEVEL

    enum class ResourceLevel : uint8_t {
        Low,
        Medium,
        MediumPlus,
        High,
        System,
        ProtectedProcess,
        NotSet,
        Unknown,
    };
#endif
#ifndef SYSTEMPOLICY
#define SYSTEMPOLICY

    enum class SystemPolicy : uint8_t {
        Zero,
        NoReadUp,
        NoWriteUp,
        NoExecuteUp,
        Unknown
    };
#endif
    typedef std::tuple<SecurityLevel, TokenPolicy, ResourceLevel, SystemPolicy>
            IntegrityLevel;

#ifndef TOKENACCESS
#define TOKENACCESS

    enum class TokenAccess : uint32_t {
        Delete = DELETE,
        ReadControl = READ_CONTROL,
        WriteDac = WRITE_DAC,
        WriteOwner = WRITE_OWNER,
        All = TOKEN_ALL_ACCESS,
        Read = TOKEN_READ,
        Write = TOKEN_WRITE,
        Execute = TOKEN_EXECUTE,
        Query = TOKEN_QUERY,
        QuerySource = TOKEN_QUERY_SOURCE,
        Duplicate = TOKEN_DUPLICATE,
        Impersonate = TOKEN_IMPERSONATE,
        AssignPrimary = TOKEN_ASSIGN_PRIMARY,
        AdjustPrivileges = TOKEN_ADJUST_PRIVILEGES,
        AdjustGroups = TOKEN_ADJUST_GROUPS,
        AdjustDefault = TOKEN_ADJUST_DEFAULT,
        AdjustSessionId = TOKEN_ADJUST_SESSIONID,
        TrustConstraintMask = TOKEN_TRUST_CONSTRAINT_MASK,
        TrustAllowedMask = TOKEN_TRUST_ALLOWED_MASK,
        AccessPseudoHandleWin8 = TOKEN_ACCESS_PSEUDO_HANDLE_WIN8,
        AccessPseudoHandle = TOKEN_ACCESS_PSEUDO_HANDLE,
    };

    inline TokenAccess operator|(TokenAccess a, TokenAccess b) {
        return static_cast<TokenAccess>(static_cast<uint32_t>(a) |
                                        static_cast<uint32_t>(b));
    }
#endif

    class security {
    private:
        void *env = nullptr;
        std::vector<HANDLE> token_handles = {};
        sync::rwlock rwlock = {};
        uint32_t error_code = 0;

        void cleanup();

    public:
        security(const security &other) = delete;

        security(security &&other) = delete;

        security &operator=(const security &other) = delete;

        security &operator=(security &&other) = delete;

        security() = default;

        ~security();

        [[nodiscard]] uint32_t curr_session_id() const;

        HANDLE curr_session_token(uint32_t session_id = 0);

        HANDLE open_proc_token(HANDLE proc_handle,
                               TokenAccess access = TokenAccess::Duplicate |
                                       TokenAccess::Query);

        HANDLE open_thread_token(HANDLE thread_handle,
                                 TokenAccess access = TokenAccess::Duplicate |
                                         TokenAccess::Query,
                                 bool open_as_self = true);

        HANDLE
        copy_token(HANDLE existing_token_handle = nullptr,
                   SECURITY_ATTRIBUTES *sa = nullptr,
                   SECURITY_IMPERSONATION_LEVEL sil = SecurityIdentification,
                   TOKEN_TYPE token_type = TokenPrimary);

        void *create_env_block(HANDLE token_handle, bool is_inherit = false);

        SECURITY_ATTRIBUTES
        create_attrs(bool is_inherit = true,
                     PSECURITY_DESCRIPTOR security_descriptor = nullptr);

        SECURITY_DESCRIPTOR create_descriptor(bool is_dacl_present = true,
                                              ACL *acl = nullptr,
                                              bool is_dacl_defaulted = false);

        bool is_valid_descriptor(PSECURITY_DESCRIPTOR security_descriptor);

        // SE_DEBUG_NAME = TEXT("SeDebugPrivilege")
        bool enable_privilege(HANDLE proc_handle,
                              const wchar_t *privilege = L"SeDebugPrivilege");

        // SE_DEBUG_NAME = TEXT("SeDebugPrivilege")
        bool disable_privilege(HANDLE proc_handle,
                               const wchar_t *privilege = L"SeDebugPrivilege");

        // SE_DEBUG_NAME = TEXT("SeDebugPrivilege")
        bool enable_privilege(uint32_t pid,
                              const wchar_t *privilege = L"SeDebugPrivilege");

        // SE_DEBUG_NAME = TEXT("SeDebugPrivilege")
        bool disable_privilege(uint32_t pid,
                               const wchar_t *privilege = L"SeDebugPrivilege");

        // SE_DEBUG_NAME = TEXT("SeDebugPrivilege")
        bool enable_debug(HANDLE proc_handle);

        // SE_DEBUG_NAME = TEXT("SeDebugPrivilege")
        bool disable_debug(HANDLE proc_handle);

        // SE_DEBUG_NAME = TEXT("SeDebugPrivilege")
        bool enable_debug(uint32_t pid);

        // SE_DEBUG_NAME = TEXT("SeDebugPrivilege")
        bool disable_debug(uint32_t pid);

        // SE_SECURITY_NAME = TEXT("SeSecurityPrivilege")
        bool enable_sacl(HANDLE proc_handle);

        // SE_SECURITY_NAME = TEXT("SeSecurityPrivilege")
        bool disable_sacl(HANDLE proc_handle);

        // SE_SECURITY_NAME = TEXT("SeSecurityPrivilege")
        bool enable_sacl(uint32_t pid);

        // SE_SECURITY_NAME = TEXT("SeSecurityPrivilege")
        bool disable_sacl(uint32_t pid);

        std::pair<TOKEN_ELEVATION_TYPE, bool>
        check_proc_elevation(HANDLE proc_handle = nullptr);

        IntegrityLevel check_proc_integrity_level(HANDLE proc_handle = nullptr);

        [[nodiscard]] uint32_t err_code() const;

        [[nodiscard]] std::string err_string() const;

        [[nodiscard]] std::wstring err_wstring() const;
    };
} // namespace YanLib::sys

#endif // SECURITY_H
