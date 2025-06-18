/* clang-format off */
/*
 * @file sys.h
 * @date 2025-06-17
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
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
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
#ifndef SYS_H
#define SYS_H
#include <winnt.h>
#include <WinBase.h>
#include <WinUser.h>
#include <cstdint>
#include <tuple>
namespace YanLib::sys {
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

    enum class ProcCreateFlag : uint32_t {
        Default = 0,
        DebugProcess = DEBUG_PROCESS,
        DebugOnlyThisProcess = DEBUG_ONLY_THIS_PROCESS,
        CreateSuspended = CREATE_SUSPENDED,
        DetachedProcess = DETACHED_PROCESS,
        CreateNewConsole = CREATE_NEW_CONSOLE,
        NormalPriorityClass = NORMAL_PRIORITY_CLASS,
        IdlePriorityClass = IDLE_PRIORITY_CLASS,
        HighPriorityClass = HIGH_PRIORITY_CLASS,
        RealtimePriorityClass = REALTIME_PRIORITY_CLASS,
        CreateNewProcessGroup = CREATE_NEW_PROCESS_GROUP,
        CreateUnicodeEnvironment = CREATE_UNICODE_ENVIRONMENT,
        CreateSeparateWowVdm = CREATE_SEPARATE_WOW_VDM,
        CreateSharedWowVdm = CREATE_SHARED_WOW_VDM,
        CreateForceDos = CREATE_FORCEDOS,
        BelowNormalPriorityClass = BELOW_NORMAL_PRIORITY_CLASS,
        AboveNormalPriorityClass = ABOVE_NORMAL_PRIORITY_CLASS,
        InheritParentAffinity = INHERIT_PARENT_AFFINITY,
        InheritCallerPriority = INHERIT_CALLER_PRIORITY,
        CreateProtectedProcess = CREATE_PROTECTED_PROCESS,
        ExtendedStartupinfoPresent = EXTENDED_STARTUPINFO_PRESENT,
        ProcessModeBackgroundBegin = PROCESS_MODE_BACKGROUND_BEGIN,
        ProcessModeBackgroundEnd = PROCESS_MODE_BACKGROUND_END,
        CreateSecureProcess = CREATE_SECURE_PROCESS,
        CreateBreakawayFromJob = CREATE_BREAKAWAY_FROM_JOB,
        CreatePreserveCodeAuthzLevel = CREATE_PRESERVE_CODE_AUTHZ_LEVEL,
        CreateDefaultErrorMode = CREATE_DEFAULT_ERROR_MODE,
        CreateNoWindow = CREATE_NO_WINDOW,
        ProfileUser = PROFILE_USER,
        ProfileKernel = PROFILE_KERNEL,
        ProfileServer = PROFILE_SERVER,
        CreateIgnoreSystemDefault = CREATE_IGNORE_SYSTEM_DEFAULT,
    };

    inline ProcCreateFlag operator|(ProcCreateFlag a, ProcCreateFlag b) {
        return static_cast<ProcCreateFlag>(static_cast<uint32_t>(a) |
                                           static_cast<uint32_t>(b));
    }

    enum class LogonFlag : uint32_t {
        Default = 0,
        WithProfile = LOGON_WITH_PROFILE,
        NetCredentialsOnly = LOGON_NETCREDENTIALS_ONLY,
        ZeroPasswordBuffer = LOGON_ZERO_PASSWORD_BUFFER,
    };

    enum class ShowFlag : uint32_t {
        Hide = SW_HIDE,
        ShowNormal = SW_SHOWNORMAL,
        Normal = SW_NORMAL,
        ShowMinimized = SW_SHOWMINIMIZED,
        ShowMaximized = SW_SHOWMAXIMIZED,
        Maximize = SW_MAXIMIZE,
        ShowNoActivate = SW_SHOWNOACTIVATE,
        Show = SW_SHOW,
        Minimize = SW_MINIMIZE,
        ShowMinNoActive = SW_SHOWMINNOACTIVE,
        ShowNA = SW_SHOWNA,
        Restore = SW_RESTORE,
        ShowDefault = SW_SHOWDEFAULT,
        ForceMinimize = SW_FORCEMINIMIZE,
        Max = SW_MAX,
    };

    enum class ProcAccess : uint32_t {
        Delete = DELETE,
        ReadControl = READ_CONTROL,
        WriteDac = WRITE_DAC,
        WriteOwner = WRITE_OWNER,
        Synchronize = SYNCHRONIZE,
        All = PROCESS_ALL_ACCESS,
        Terminate = PROCESS_TERMINATE,
        CreateThread = PROCESS_CREATE_THREAD,
        SetSessionId = PROCESS_SET_SESSIONID,
        VmOperation = PROCESS_VM_OPERATION,
        VmRead = PROCESS_VM_READ,
        VmWrite = PROCESS_VM_WRITE,
        DupHandle = PROCESS_DUP_HANDLE,
        Create = PROCESS_CREATE_PROCESS,
        SetQuota = PROCESS_SET_QUOTA,
        SetInfo = PROCESS_SET_INFORMATION,
        QueryInfo = PROCESS_QUERY_INFORMATION,
        SuspendResume = PROCESS_SUSPEND_RESUME,
        QueryLimitedInfo = PROCESS_QUERY_LIMITED_INFORMATION,
        SetLimitedInfo = PROCESS_SET_LIMITED_INFORMATION,
    };

    inline ProcAccess operator|(ProcAccess a, ProcAccess b) {
        return static_cast<ProcAccess>(static_cast<uint32_t>(a) |
                                       static_cast<uint32_t>(b));
    }

    enum class AllocateType : uint32_t {
        Commit = MEM_COMMIT,
        Reserve = MEM_RESERVE,
        ReplacePlaceHolder = MEM_REPLACE_PLACEHOLDER,
        ReservePlaceHolder = MEM_RESERVE_PLACEHOLDER,
        Reset = MEM_RESET,
        TopDown = MEM_TOP_DOWN,
        WriteWatch = MEM_WRITE_WATCH,
        Physical = MEM_PHYSICAL,
        Rotate = MEM_ROTATE,
        DifferentImageBaseOk = MEM_DIFFERENT_IMAGE_BASE_OK,
        ResetUndo = MEM_RESET_UNDO,
        LargePages = MEM_LARGE_PAGES,
        Pages4MB = MEM_4MB_PAGES,
        Pages64K = MEM_64K_PAGES,
        UnmapWithTransientBoost = MEM_UNMAP_WITH_TRANSIENT_BOOST,
        CoalescePlaceHolders = MEM_COALESCE_PLACEHOLDERS,
        PreservePlaceHolder = MEM_PRESERVE_PLACEHOLDER,
        DeCommit = MEM_DECOMMIT,
        Release = MEM_RELEASE,
        Free = MEM_FREE,
    };

    inline AllocateType operator|(AllocateType a, AllocateType b) {
        return static_cast<AllocateType>(static_cast<uint32_t>(a) |
                                         static_cast<uint32_t>(b));
    }

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

    enum class TokenPolicy : uint8_t { Off, NoWriteUp, NewProcessMin, Unknown };

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

    enum class SystemPolicy : uint8_t {
        Zero,
        NoReadUp,
        NoWriteUp,
        NoExecuteUp,
        Unknown
    };

    typedef std::tuple<SecurityLevel, TokenPolicy, ResourceLevel, SystemPolicy>
            IntegrityLevel;

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

    enum class ThreadAccess : uint32_t {
        Delete = DELETE,
        ReadControl = READ_CONTROL,
        WriteDac = WRITE_DAC,
        WriteOwner = WRITE_OWNER,
        Synchronize = SYNCHRONIZE,
        All = THREAD_ALL_ACCESS,
        Terminate = THREAD_TERMINATE,
        SuspendResume = THREAD_SUSPEND_RESUME,
        GetContext = THREAD_GET_CONTEXT,
        SetContext = THREAD_SET_CONTEXT,
        QueryInfo = THREAD_QUERY_INFORMATION,
        SetInfo = THREAD_SET_INFORMATION,
        SetThreadToken = THREAD_SET_THREAD_TOKEN,
        Impersonate = THREAD_IMPERSONATE,
        DirectImpersonation = THREAD_DIRECT_IMPERSONATION,
        SetLimitedInfo = THREAD_SET_LIMITED_INFORMATION,
        QueryLimitedInfo = THREAD_QUERY_LIMITED_INFORMATION,
        Resume = THREAD_RESUME,
    };

    inline ThreadAccess operator|(ThreadAccess a, ThreadAccess b) {
        return static_cast<ThreadAccess>(static_cast<uint32_t>(a) |
                                         static_cast<uint32_t>(b));
    }
} // namespace YanLib::sys
#endif // SYS_H
