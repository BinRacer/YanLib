//
// Created by forkernel on 2025/4/14.
//

#include "proc.h"

#include <algorithm>
#include <memory>

#include "security.h"
#include "helper/convert.h"
#include "helper/autoclean.h"
#include <UserEnv.h>

#pragma comment(lib, "UserEnv.lib")

namespace YanLib::sys {
    proc::~proc() {
        if (curr_proc_env) {
            FreeEnvironmentStringsW(curr_proc_env);
        }
        if (!proc_infos.empty()) {
            for (auto &info: proc_infos) {
                if (info.hThread) {
                    CloseHandle(info.hThread);
                    info.hThread = nullptr;
                }
                if (info.hProcess) {
                    CloseHandle(info.hProcess);
                    info.hProcess = nullptr;
                }
            }
            proc_infos.clear();
        }
        if (!proc_handles.empty()) {
            for (auto &proc_handle: proc_handles) {
                CloseHandle(proc_handle);
                proc_handle = nullptr;
            }
            proc_handles.clear();
        }
    }

    NTSTATUS proc::nt_query_info_proc(HANDLE proc_handle,
                                      PROCESSINFOCLASS proc_info_class,
                                      void *proc_info,
                                      unsigned long proc_info_len,
                                      unsigned long *ret_len) {
        typedef NTSTATUS (CALLBACK *pfn)(HANDLE ProcessHandle,
                                         PROCESSINFOCLASS ProcessInformationClass,
                                         void *ProcessInformation,
                                         unsigned long ProcessInformationLength,
                                         unsigned long *ReturnLength OPTIONAL);
        NTSTATUS status = -1;
        HMODULE ntdll_module = nullptr;
        do {
            ntdll_module = LoadLibraryW(L"ntdll.dll");
            if (!ntdll_module) {
                error_code = GetLastError();
                break;
            }
            pfn query_info_proc = reinterpret_cast<pfn>(
                GetProcAddress(ntdll_module,
                               "NtQueryInformationProcess"));
            if (!query_info_proc) {
                error_code = GetLastError();
                break;
            }
            status = query_info_proc(proc_handle,
                                     proc_info_class,
                                     proc_info,
                                     proc_info_len,
                                     ret_len);
        } while (false);
        if (ntdll_module) {
            FreeLibrary(ntdll_module);
        }
        return status;
    }

    PROCESS_INFORMATION proc::create(
        const wchar_t *app_name,
        wchar_t *cmdline,
        SECURITY_ATTRIBUTES *proc_attrs,
        SECURITY_ATTRIBUTES *thread_attrs,
        bool is_inherit_handles,
        unsigned long create_flag,
        void *env,
        const wchar_t *curr_dir) {
        STARTUPINFOW si = {};
        PROCESS_INFORMATION pi = {};
        si.cb = sizeof(si);
        if (!CreateProcessW(app_name,
                            cmdline,
                            proc_attrs,
                            thread_attrs,
                            is_inherit_handles ? TRUE : FALSE,
                            create_flag,
                            env,
                            curr_dir,
                            &si,
                            &pi)) {
            error_code = GetLastError();
            return {};
        }
        proc_info_rwlock.write_lock();
        proc_infos.push_back(pi);
        proc_info_rwlock.write_unlock();
        return pi;
    }

    PROCESS_INFORMATION proc::create_with_suspended(
        const wchar_t *app_name,
        wchar_t *cmdline,
        SECURITY_ATTRIBUTES *proc_attrs,
        SECURITY_ATTRIBUTES *thread_attrs,
        bool is_inherit_handles,
        unsigned long create_flag,
        void *env,
        const wchar_t *curr_dir) {
        STARTUPINFOW si = {};
        PROCESS_INFORMATION pi = {};
        si.cb = sizeof(si);
        if (!CreateProcessW(app_name,
                            cmdline,
                            proc_attrs,
                            thread_attrs,
                            is_inherit_handles ? TRUE : FALSE,
                            create_flag,
                            env,
                            curr_dir,
                            &si,
                            &pi)) {
            error_code = GetLastError();
            return {};
        }
        proc_info_rwlock.write_lock();
        proc_infos.push_back(pi);
        proc_info_rwlock.write_unlock();
        return pi;
    }

    PROCESS_INFORMATION proc::create_as_user(
        HANDLE token_handle,
        const wchar_t *app_name,
        wchar_t *cmdline,
        SECURITY_ATTRIBUTES *proc_attrs,
        SECURITY_ATTRIBUTES *thread_attrs,
        bool is_inherit_handles,
        unsigned long create_flag,
        void *env,
        const wchar_t *curr_dir) {
        STARTUPINFOW si = {};
        PROCESS_INFORMATION pi = {};
        si.cb = sizeof(si);
        security security;
        void *environment = nullptr;
        if (env) {
            environment = env;
        } else {
            environment = security.create_env_block(token_handle);
            if (!environment) {
                error_code = security.err_code();
                return {};
            }
        }
        if (!CreateProcessAsUserW(token_handle,
                                  app_name,
                                  cmdline,
                                  proc_attrs,
                                  thread_attrs,
                                  is_inherit_handles ? TRUE : FALSE,
                                  create_flag,
                                  environment,
                                  curr_dir,
                                  &si,
                                  &pi)) {
            error_code = GetLastError();
            return {};
        }
        proc_info_rwlock.write_lock();
        proc_infos.push_back(pi);
        proc_info_rwlock.write_unlock();
        return pi;
    }

    PROCESS_INFORMATION proc::create_session_zero(
        const wchar_t *app_name,
        wchar_t *cmdline,
        SECURITY_ATTRIBUTES *proc_attrs,
        SECURITY_ATTRIBUTES *thread_attrs,
        bool is_inherit_handles,
        unsigned long create_flag,
        void *env,
        const wchar_t *curr_dir) {
        STARTUPINFOW si = {};
        PROCESS_INFORMATION pi = {};
        si.cb = sizeof(si);
        security security;
        helper::autoclean<HANDLE> token_handle(nullptr);
        token_handle = security.copy_token();
        if (!token_handle.is_ok()) {
            error_code = security.err_code();
            return {};
        }
        void *environment = nullptr;
        if (env) {
            environment = env;
        } else {
            environment = security.create_env_block(token_handle);
            if (!environment) {
                error_code = security.err_code();
                return {};
            }
        }
        if (!CreateProcessAsUserW(token_handle,
                                  app_name,
                                  cmdline,
                                  proc_attrs,
                                  thread_attrs,
                                  is_inherit_handles ? TRUE : FALSE,
                                  create_flag,
                                  environment,
                                  curr_dir,
                                  &si,
                                  &pi)) {
            error_code = GetLastError();
            return {};
        }
        proc_info_rwlock.write_lock();
        proc_infos.push_back(pi);
        proc_info_rwlock.write_unlock();
        return pi;
    }

    PROCESS_INFORMATION proc::create_with_logon(
        const wchar_t *username,
        const wchar_t *domain,
        const wchar_t *password,
        const wchar_t *app_name,
        wchar_t *cmdline,
        unsigned long logon_flag,
        unsigned long create_flag,
        void *env,
        const wchar_t *curr_dir) {
        STARTUPINFOW si = {};
        PROCESS_INFORMATION pi = {};
        si.cb = sizeof(si);
        security security;
        helper::autoclean<HANDLE> token_handle(nullptr);
        token_handle = security.copy_token();
        if (!token_handle.is_ok()) {
            error_code = security.err_code();
            return {};
        }
        void *environment = nullptr;
        if (env) {
            environment = env;
        } else {
            environment = security.create_env_block(token_handle);
            if (!environment) {
                error_code = security.err_code();
                return {};
            }
        }
        if (!CreateProcessWithLogonW(username,
                                     domain,
                                     password,
                                     logon_flag,
                                     app_name,
                                     cmdline,
                                     create_flag,
                                     environment,
                                     curr_dir,
                                     &si,
                                     &pi)) {
            error_code = GetLastError();
            return {};
        }
        proc_info_rwlock.write_lock();
        proc_infos.push_back(pi);
        proc_info_rwlock.write_unlock();
        return pi;
    }

    PROCESS_INFORMATION proc::create_with_token(
        HANDLE token_handle,
        const wchar_t *app_name,
        wchar_t *cmdline,
        unsigned long logon_flag,
        unsigned long create_flag,
        void *env,
        const wchar_t *curr_dir) {
        STARTUPINFOW si = {};
        PROCESS_INFORMATION pi = {};
        si.cb = sizeof(si);
        security security;
        void *environment = nullptr;
        if (env) {
            environment = env;
        } else {
            environment = security.create_env_block(token_handle);
            if (!environment) {
                error_code = security.err_code();
                return {};
            }
        }
        if (!CreateProcessWithTokenW(token_handle,
                                     logon_flag,
                                     app_name,
                                     cmdline,
                                     create_flag,
                                     env,
                                     curr_dir,
                                     &si,
                                     &pi)) {
            error_code = GetLastError();
            return {};
        }
        proc_info_rwlock.write_lock();
        proc_infos.push_back(pi);
        proc_info_rwlock.write_unlock();
        return pi;
    }

    bool proc::win_exec(const char *cmdline, unsigned int show_flag) {
        unsigned int ret = WinExec(cmdline, show_flag);
        if (ret <= 31 && ret > 0) {
            error_code = ret;
        } else if (ret == 0) {
            error_code = ERROR_NOT_ENOUGH_SERVER_MEMORY;
        }
        if (ret > 31) {
            return true;
        }
        return false;
    }

    bool proc::shell_exec(const wchar_t *file_name,
                          const wchar_t *params,
                          const wchar_t *dir,
                          int show_flag,
                          HWND hwnd,
                          const wchar_t *operation) {
        HINSTANCE instance = ShellExecuteW(hwnd,
                                           operation,
                                           file_name,
                                           params,
                                           dir,
                                           show_flag);
        auto ret = reinterpret_cast<uintptr_t>(instance);
        ret = ret & 0x00000000FFFFFFFF;
        if (ret <= 32 && ret > 0) {
            error_code = ret;
        } else if (ret == 0) {
            error_code = ERROR_NOT_ENOUGH_SERVER_MEMORY;
        }
        if (ret > 32) {
            return true;
        }
        return false;
    }

    bool proc::runas_elevated(const wchar_t *app_name,
                              const wchar_t *cmdline) {
        SHELLEXECUTEINFOW sei = {sizeof(SHELLEXECUTEINFO)};
        sei.lpVerb = L"runas";
        sei.lpFile = app_name;
        sei.lpParameters = cmdline;
        sei.nShow = SW_SHOWNORMAL;
        if (!ShellExecuteExW(&sei)) {
            error_code = GetLastError();
        }
        return true;
    }

    bool proc::fake_proc(HANDLE proc_handle,
                         const wchar_t *app_name,
                         const wchar_t *cmdline) {
        unsigned long size = 0;
        PROCESS_BASIC_INFORMATION pbi{};
        do {
            NTSTATUS status = nt_query_info_proc(
                proc_handle,
                ProcessBasicInformation,
                &pbi,
                sizeof(pbi),
                &size);
            if (!NT_SUCCESS(status)) {
                break;
            }
            auto peb = std::make_unique<PEB>();
            size_t ret_size = size;
            if (!ReadProcessMemory(proc_handle,
                                   pbi.PebBaseAddress,
                                   peb.get(),
                                   sizeof(PEB),
                                   &ret_size)) {
                error_code = GetLastError();
                break;
            }
            auto params = std::make_unique<RTL_USER_PROCESS_PARAMETERS>();
            if (!ReadProcessMemory(proc_handle,
                                   peb->ProcessParameters,
                                   params.get(),
                                   sizeof(RTL_USER_PROCESS_PARAMETERS),
                                   &ret_size)) {
                error_code = GetLastError();
                break;
            }
            unsigned short len = (wcslen(cmdline) + 1) * sizeof(wchar_t);
            if (!WriteProcessMemory(proc_handle,
                                    params->CommandLine.Buffer,
                                    cmdline,
                                    len,
                                    nullptr)) {
                error_code = GetLastError();
                break;
            }
            if (!WriteProcessMemory(proc_handle,
                                    &params->CommandLine.Length,
                                    &len,
                                    sizeof(len),
                                    nullptr)) {
                error_code = GetLastError();
                break;
            }
            len = (wcslen(app_name) + 1) * sizeof(wchar_t);
            if (!WriteProcessMemory(proc_handle,
                                    params->ImagePathName.Buffer,
                                    app_name,
                                    len,
                                    nullptr)) {
                error_code = GetLastError();
                break;
            }
            if (!WriteProcessMemory(proc_handle,
                                    &params->ImagePathName.Length,
                                    &len,
                                    sizeof(len),
                                    nullptr)) {
                error_code = GetLastError();
                break;
            }
            return true;
        } while (false);
        return false;
    }

    bool proc::wait_child(HANDLE child_proc_handle, unsigned long milli_seconds) {
        if (child_proc_handle) {
            unsigned long ret = WaitForSingleObject(child_proc_handle, milli_seconds);
            if (ret == WAIT_OBJECT_0) {
                return true;
            }
            error_code = GetLastError();
        }
        return false;
    }

    bool proc::resume_child(HANDLE child_thread_handle) {
        if (child_thread_handle) {
            if (ResumeThread(child_thread_handle) == static_cast<unsigned long>(-1)) {
                error_code = GetLastError();
                return false;
            }
            return true;
        }
        return false;
    }

    HANDLE proc::thread_handle() {
        return GetCurrentThread();
    }

    HANDLE proc::proc_handle() {
        return GetCurrentProcess();
    }

    unsigned long proc::thread_id() {
        return GetCurrentThreadId();
    }

    unsigned long proc::proc_id() {
        return GetCurrentProcessId();
    }

    HANDLE proc::pid_to_handle(unsigned long pid,
                               unsigned long desired_access,
                               bool is_inherit_handle) {
        HANDLE proc_handle = OpenProcess(desired_access,
                                         is_inherit_handle ? TRUE : FALSE,
                                         pid);
        if (!proc_handle) {
            error_code = GetLastError();
            return nullptr;
        }
        proc_handle_rwlock.write_lock();
        proc_handles.push_back(proc_handle);
        proc_handle_rwlock.write_unlock();
        return proc_handle;
    }

    unsigned long proc::handle_to_pid(HANDLE proc_handle) {
        unsigned long pid = GetProcessId(proc_handle);
        if (!pid) {
            error_code = GetLastError();
        }
        return pid;
    }

    bool proc::kill(HANDLE proc_handle, unsigned int exit_code) {
        if (!TerminateProcess(proc_handle, exit_code)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    void proc::exit(unsigned int exit_code) {
        ExitProcess(exit_code);
    }

    unsigned long proc::exit_status(HANDLE proc_handle) {
        unsigned long exit_status = 0;
        if (!GetExitCodeProcess(proc_handle, &exit_status)) {
            error_code = GetLastError();
        }
        return exit_status;
    }

    STARTUPINFOW proc::startup_info() {
        STARTUPINFOW startup_info;
        GetStartupInfoW(&startup_info);
        return startup_info;
    }

    void *proc::malloc(HANDLE proc_handle,
                       size_t size,
                       void *addr,
                       unsigned long allocate_flag,
                       unsigned long protect_flag) {
        void *address = VirtualAllocEx(proc_handle,
                                       addr,
                                       size,
                                       allocate_flag,
                                       protect_flag);
        if (!address) {
            error_code = GetLastError();
        }
        return address;
    }

    bool proc::free(HANDLE proc_handle,
                    void *addr,
                    size_t size,
                    unsigned long free_type) {
        if (free_type & MEM_RELEASE) {
            size = 0;
        }
        if (!VirtualFreeEx(proc_handle,
                           addr,
                           size,
                           free_type)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    void *proc::malloc_reserve(HANDLE proc_handle,
                               size_t size,
                               void *addr,
                               unsigned long allocate_type,
                               unsigned long protect_flag) {
        void *address = VirtualAllocEx(proc_handle,
                                       addr,
                                       size,
                                       allocate_type,
                                       protect_flag);
        if (!address) {
            error_code = GetLastError();
        }
        return address;
    }

    bool proc::free_reserve(HANDLE proc_handle,
                            void *addr,
                            size_t size,
                            unsigned long free_type) {
        if (!VirtualFreeEx(proc_handle,
                           addr,
                           size,
                           free_type)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool proc::mem_guard_attr(HANDLE proc_handle,
                              void *addr,
                              size_t size,
                              unsigned long new_protect_flag,
                              unsigned long *old_protect_flag) {
        if (!VirtualProtectEx(proc_handle,
                              addr,
                              size,
                              new_protect_flag,
                              old_protect_flag)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool proc::query_mem(HANDLE proc_handle,
                         const void *address,
                         MEMORY_BASIC_INFORMATION *buffer,
                         size_t len) {
        if (!VirtualQueryEx(proc_handle,
                            address,
                            buffer,
                            len)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool proc::global_mem_status(MEMORYSTATUSEX *buffer) {
        if (!GlobalMemoryStatusEx(buffer)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool proc::read(HANDLE proc_handle,
                    const void *base_addr,
                    void *buf,
                    size_t size,
                    size_t *bytes_read) {
        if (!ReadProcessMemory(proc_handle,
                               base_addr,
                               buf,
                               size,
                               bytes_read)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool proc::write(HANDLE proc_handle,
                     void *base_addr,
                     const void *buf,
                     size_t size,
                     size_t *bytes_written) {
        if (!WriteProcessMemory(proc_handle,
                                base_addr,
                                buf,
                                size,
                                bytes_written)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    std::vector<uint8_t> proc::read(HANDLE proc_handle,
                                    const void *base_addr,
                                    size_t size) {
        std::vector<uint8_t> buffer(size, 0);
        size_t bytes_read = 0;
        if (!ReadProcessMemory(proc_handle,
                               base_addr,
                               buffer.data(),
                               buffer.size(),
                               &bytes_read)) {
            error_code = GetLastError();
            return {};
        }
        buffer.resize(bytes_read);
        buffer.shrink_to_fit();
        return buffer;
    }

    bool proc::write(HANDLE proc_handle,
                     void *base_addr,
                     std::vector<uint8_t> &buf) {
        if (buf.empty()) {
            return false;
        }
        size_t bytes_write = 0;
        if (!WriteProcessMemory(proc_handle,
                                base_addr,
                                buf.data(),
                                buf.size(),
                                &bytes_write)) {
            error_code = GetLastError();
            return false;
        }
        if (bytes_write != buf.size()) {
            return false;
        }
        return true;
    }

    void proc::flush_write_buffer() {
        FlushProcessWriteBuffers();
    }

    std::wstring proc::env_strings() {
        if (curr_proc_env) {
            return curr_proc_env;
        }
        curr_proc_env = GetEnvironmentStringsW();
        if (!curr_proc_env) {
            error_code = GetLastError();
        }
        return curr_proc_env;
    }

    std::wstring proc::get_env_var(std::wstring var_name) {
        std::wstring var_value;
        unsigned long size = GetEnvironmentVariableW(var_name.data(),
                                                     var_value.data(),
                                                     var_value.size());
        if (size <= 0) {
            error_code = GetLastError();
            return {};
        }
        var_value.resize(size);
        size = GetEnvironmentVariableW(var_name.data(),
                                       var_value.data(),
                                       var_value.size());
        if (size <= 0) {
            error_code = GetLastError();
            return {};
        }
        return var_value;
    }

    bool proc::set_env_var(std::wstring var_name, std::wstring var_value) {
        if (!SetEnvironmentVariableW(var_name.data(),
                                     var_value.data())) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    std::wstring proc::cmdline() {
        return GetCommandLineW();
    }

    std::string proc::cmdline(HANDLE proc_handle) {
        std::wstring result = cmdline_wide(proc_handle);
        return helper::convert::wstr_to_str(result);
    }

    std::wstring proc::cmdline_wide(HANDLE proc_handle) {
        // 0: kd> dt nt!_PEB
        // +0x000 InheritedAddressSpace : UChar
        // +0x001 ReadImageFileExecOptions : UChar
        // +0x002 BeingDebugged    : UChar
        // +0x003 BitField         : UChar
        // +0x003 ImageUsesLargePages : Pos 0, 1 Bit
        // +0x003 IsProtectedProcess : Pos 1, 1 Bit
        // +0x003 IsImageDynamicallyRelocated : Pos 2, 1 Bit
        // +0x003 SkipPatchingUser32Forwarders : Pos 3, 1 Bit
        // +0x003 IsPackagedProcess : Pos 4, 1 Bit
        // +0x003 IsAppContainer   : Pos 5, 1 Bit
        // +0x003 IsProtectedProcessLight : Pos 6, 1 Bit
        // +0x003 IsLongPathAwareProcess : Pos 7, 1 Bit
        // +0x004 Padding0         : [4] UChar
        // +0x008 Mutant           : Ptr64 Void
        // +0x010 ImageBaseAddress : Ptr64 Void
        // +0x018 Ldr              : Ptr64 _PEB_LDR_DATA
        // +0x020 ProcessParameters : Ptr64 _RTL_USER_PROCESS_PARAMETERS
        struct _peb {
            uint8_t fill[0x20];
            void *process_parameters;
        };

        // 0: kd> dt nt!_RTL_USER_PROCESS_PARAMETERS
        // +0x000 MaximumLength    : Uint4B
        // +0x004 Length           : Uint4B
        // +0x008 Flags            : Uint4B
        // +0x00c DebugFlags       : Uint4B
        // +0x010 ConsoleHandle    : Ptr64 Void
        // +0x018 ConsoleFlags     : Uint4B
        // +0x020 StandardInput    : Ptr64 Void
        // +0x028 StandardOutput   : Ptr64 Void
        // +0x030 StandardError    : Ptr64 Void
        // +0x038 CurrentDirectory : _CURDIR
        // +0x050 DllPath          : _UNICODE_STRING
        // +0x060 ImagePathName    : _UNICODE_STRING
        // +0x070 CommandLine      : _UNICODE_STRING
        // +0x080 Environment      : Ptr64 Void

        // 0: kd> dt _UNICODE_STRING
        // nt!_UNICODE_STRING
        // +0x000 Length           : Uint2B
        // +0x002 MaximumLength    : Uint2B
        // +0x008 Buffer           : Ptr64 Wchar
        struct _process_parameters {
            uint8_t fill[0x70 + 0x8];
            void *cmdline;
        };
        HANDLE process_handle = proc_handle
                                    ? proc_handle
                                    : GetCurrentProcess();
        unsigned long ret_size = 0;
        PROCESS_BASIC_INFORMATION pbi{};
        do {
            NTSTATUS status = nt_query_info_proc(
                process_handle,
                ProcessBasicInformation,
                &pbi,
                sizeof(pbi),
                &ret_size);
            if (!NT_SUCCESS(status)) {
                break;
            }
            auto peb = std::make_unique<_peb>();
            size_t size = ret_size;
            if (!ReadProcessMemory(process_handle,
                                   pbi.PebBaseAddress,
                                   peb.get(),
                                   sizeof(_peb),
                                   &size)) {
                error_code = GetLastError();
                break;
            }
            auto block = std::make_unique<_process_parameters>();
            if (!ReadProcessMemory(process_handle,
                                   peb->process_parameters,
                                   block.get(),
                                   sizeof(_process_parameters),
                                   &size)) {
                error_code = GetLastError();
                break;
            }
            std::wstring cmdline(MAX_PATH + 1, L'\0');
            if (!ReadProcessMemory(process_handle,
                                   block->cmdline,
                                   cmdline.data(),
                                   cmdline.size(),
                                   &size)) {
                error_code = GetLastError();
                break;
            }
            cmdline.resize(size);
            while (cmdline.back() == L'\0') {
                cmdline.pop_back();
            }
            cmdline.shrink_to_fit();
            return cmdline;
        } while (false);
        return {};
    }

    std::string proc::cmdline(unsigned long pid) {
        return cmdline(pid_to_handle(pid));
    }

    std::wstring proc::cmdline_wide(unsigned long pid) {
        return cmdline_wide(pid_to_handle(pid));
    }

    std::string proc::owner(HANDLE proc_handle) {
        std::wstring result = owner_wide(proc_handle);
        return helper::convert::wstr_to_str(result);
    }

    std::wstring proc::owner_wide(HANDLE proc_handle) {
        HANDLE process_handle = proc_handle
                                    ? proc_handle
                                    : GetCurrentProcess();
        helper::autoclean<HANDLE> token_handle(nullptr);
        std::wstring result;
        security security;
        do {
            if (security.enable_privilege(GetCurrentProcess(),
                                          L"SeTcbPrivilege")) {
                break;
            }
            if (!OpenProcessToken(process_handle,
                                  TOKEN_QUERY,
                                  token_handle)) {
                error_code = GetLastError();
                break;
            }
            unsigned long size = 0;
            GetTokenInformation(token_handle,
                                TokenUser,
                                nullptr,
                                0,
                                &size);
            error_code = GetLastError();
            if (error_code != ERROR_INSUFFICIENT_BUFFER) {
                break;
            }
            std::vector<uint8_t> token_user(size, 0);
            if (!GetTokenInformation(token_handle,
                                     TokenUser,
                                     token_user.data(),
                                     token_user.size(),
                                     &size)) {
                error_code = GetLastError();
                break;
            }
            SID_NAME_USE snu;
            TCHAR user[MAX_PATH];
            unsigned long user_size = MAX_PATH;
            unsigned long *user_size_ptr = &user_size;
            TCHAR domain[MAX_PATH];
            unsigned long domain_size = MAX_PATH;
            unsigned long *domain_size_ptr = &domain_size;
            if (!LookupAccountSidW(nullptr,
                                   reinterpret_cast<TOKEN_USER *>(
                                       token_user.data())->User.Sid,
                                   user,
                                   user_size_ptr,
                                   domain,
                                   domain_size_ptr,
                                   &snu)) {
                error_code = GetLastError();
                break;
            }
            result.assign(L"\\\\");
            result.append(domain);
            result.append(L"\\");
            result.append(user);
            if (security.disable_privilege(GetCurrentProcess(),
                                           L"SeTcbPrivilege")) {
                break;
            }
        } while (false);
        return result;
    }

    std::string proc::owner(unsigned long pid) {
        return owner(pid_to_handle(pid));
    }

    std::wstring proc::owner_wide(unsigned long pid) {
        return owner_wide(pid_to_handle(pid));
    }


    std::string proc::image_name(HANDLE proc_handle) {
        HANDLE process_handle = proc_handle
                                    ? proc_handle
                                    : GetCurrentProcess();
        std::string name(MAX_PATH, '\0');
        unsigned long size = 0;
        if (!QueryFullProcessImageNameA(process_handle,
                                        0,
                                        name.data(),
                                        &size)) {
            error_code = GetLastError();
            return {};
        }
        name.resize(size);
        return name;
    }

    std::wstring proc::image_name_wide(HANDLE proc_handle) {
        HANDLE process_handle = proc_handle
                                    ? proc_handle
                                    : GetCurrentProcess();
        std::wstring name(MAX_PATH, L'\0');
        unsigned long size = 0;
        if (!QueryFullProcessImageNameW(process_handle,
                                        0,
                                        name.data(),
                                        &size)) {
            error_code = GetLastError();
            return {};
        }
        name.resize(size);
        while (name.back() == L'\0') {
            name.pop_back();
        }
        return name;
    }

    void *proc::image_base() {
        IMAGE_DOS_HEADER dos_header{};
        IMAGE_NT_HEADERS64 nt_headers64{};
        IMAGE_NT_HEADERS32 nt_headers32{};
        do {
            HMODULE hmodule = GetModuleHandleW(nullptr);
            if (!hmodule) {
                error_code = GetLastError();
                break;
            }
            auto *base = reinterpret_cast<uint8_t *>(hmodule);
            memcpy(&dos_header, base, sizeof(dos_header));
            if (dos_header.e_magic != IMAGE_DOS_SIGNATURE) {
                break;
            }
            memcpy(&nt_headers64,
                   base + dos_header.e_lfanew,
                   sizeof(nt_headers64));
            if (nt_headers64.Signature != IMAGE_NT_SIGNATURE) {
                break;
            }
            if (nt_headers64.FileHeader.Machine == IMAGE_FILE_MACHINE_AMD64 ||
                nt_headers64.FileHeader.Machine == IMAGE_FILE_MACHINE_ARM64) {
                return reinterpret_cast<void *>(
                    nt_headers64.OptionalHeader.ImageBase);
            } else {
                memcpy(&nt_headers32,
                       base + dos_header.e_lfanew,
                       sizeof(nt_headers32));
                if (nt_headers32.Signature != IMAGE_NT_SIGNATURE) {
                    break;
                }
                return reinterpret_cast<void *>(
                    static_cast<int64_t>(
                        nt_headers32.OptionalHeader.ImageBase));
            }
        } while (false);
        return nullptr;
    }

    void *proc::image_base(HANDLE proc_handle) {
        HANDLE process_handle = proc_handle
                                    ? proc_handle
                                    : GetCurrentProcess();
        PROCESS_BASIC_INFORMATION pbi;
        NTSTATUS status = nt_query_info_proc(
            process_handle,
            ProcessBasicInformation,
            &pbi,
            sizeof(PROCESS_BASIC_INFORMATION),
            nullptr);
        if (!NT_SUCCESS(status)) {
            return nullptr;
        }
        void *baseAddr = pbi.PebBaseAddress->Reserved3[1];
        return baseAddr;
    }

    void *proc::image_base(unsigned long pid) {
        return image_base(pid_to_handle(pid));
    }

    unsigned long proc::get_priority(HANDLE proc_handle) {
        unsigned long priority = GetPriorityClass(proc_handle);
        if (!priority) {
            error_code = GetLastError();
        }
        return priority;
    }

    bool proc::set_priority(HANDLE proc_handle, unsigned long priority) {
        if (!SetPriorityClass(proc_handle, priority)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    int proc::get_thread_priority(HANDLE thread_handle) {
        int priority = GetThreadPriority(thread_handle);
        if (priority == THREAD_PRIORITY_ERROR_RETURN) {
            error_code = GetLastError();
        }
        return priority;
    }

    bool proc::set_thread_priority(HANDLE thread_handle, int priority) {
        if (!SetThreadPriority(thread_handle, priority)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    unsigned long proc::handle_count(HANDLE proc_handle) {
        unsigned long count = 0;
        if (!GetProcessHandleCount(proc_handle, &count)) {
            error_code = GetLastError();
        }
        return count;
    }

    unsigned long proc::gui_handle_count(HANDLE proc_handle, unsigned long flag) {
        unsigned long count = GetGuiResources(proc_handle, flag);
        if (!count) {
            error_code = GetLastError();
        }
        return count;
    }

    unsigned long proc::processor_num() {
        return GetCurrentProcessorNumber();
    }

    bool proc::get_info(HANDLE proc_handle,
                        PROCESS_INFORMATION_CLASS proc_info_class,
                        void *proc_info,
                        unsigned long proc_info_size) {
        if (!GetProcessInformation(proc_handle,
                                   proc_info_class,
                                   proc_info,
                                   proc_info_size)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool proc::set_info(HANDLE proc_handle,
                        PROCESS_INFORMATION_CLASS proc_info_class,
                        void *proc_info,
                        unsigned long proc_info_size) {
        if (!SetProcessInformation(proc_handle,
                                   proc_info_class,
                                   proc_info,
                                   proc_info_size)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool proc::get_mem_info(HANDLE proc_handle,
                            PPROCESS_MEMORY_COUNTERS mem_counters,
                            unsigned long mem_counters_size) {
        if (!GetProcessMemoryInfo(proc_handle,
                                  mem_counters,
                                  mem_counters_size)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool proc::get_module_info(HANDLE proc_handle,
                               HMODULE module_handle,
                               MODULEINFO *mod_info,
                               unsigned long mod_info_size) {
        if (!GetModuleInformation(proc_handle,
                                  module_handle,
                                  mod_info,
                                  mod_info_size)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool proc::logical_processor_info(
        SYSTEM_LOGICAL_PROCESSOR_INFORMATION *buf,
        unsigned long *ret_len) {
        if (!GetLogicalProcessorInformation(buf, ret_len)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool proc::get_affinity_mask(HANDLE proc_handle,
                                 DWORD_PTR *proc_affinity_mask,
                                 DWORD_PTR *system_affinity_mask) {
        if (!GetProcessAffinityMask(proc_handle,
                                    proc_affinity_mask,
                                    system_affinity_mask)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool proc::set_affinity_mask(HANDLE proc_handle,
                                 DWORD_PTR proc_affinity_mask) {
        if (!SetProcessAffinityMask(proc_handle,
                                    proc_affinity_mask)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool proc::get_group_affinity(HANDLE proc_handle,
                                  unsigned short *group_count,
                                  unsigned short *group_array) {
        if (!GetProcessGroupAffinity(proc_handle,
                                     group_count,
                                     group_array)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool proc::io_counters(HANDLE proc_handle,
                           IO_COUNTERS *io_counters) {
        if (!GetProcessIoCounters(proc_handle,
                                  io_counters)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool proc::get_mitigation_policy(
        HANDLE proc_handle,
        PROCESS_MITIGATION_POLICY mitigation_policy,
        void *buffer,
        size_t len) {
        if (!GetProcessMitigationPolicy(proc_handle,
                                        mitigation_policy,
                                        buffer,
                                        len)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool proc::set_mitigation_policy(
        PROCESS_MITIGATION_POLICY mitigation_policy,
        void *buffer,
        size_t len) {
        if (!SetProcessMitigationPolicy(mitigation_policy,
                                        buffer,
                                        len)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool proc::get_priority_boost(HANDLE proc_handle) {
        int is_disable_priority_boost = 0;
        if (!GetProcessPriorityBoost(proc_handle,
                                     &is_disable_priority_boost)) {
            error_code = GetLastError();
        }
        return is_disable_priority_boost;
    }

    bool proc::set_priority_boost(HANDLE proc_handle,
                                  bool is_disable_priority_boost) {
        if (!SetProcessPriorityBoost(proc_handle,
                                     is_disable_priority_boost
                                         ? TRUE
                                         : FALSE)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool proc::get_shutdown_params(unsigned long *level, unsigned long *flag) {
        if (!GetProcessShutdownParameters(level, flag)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool proc::set_shutdown_params(unsigned long level, unsigned long flag) {
        if (!SetProcessShutdownParameters(level, flag)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool proc::time_statistics(HANDLE proc_handle,
                               FILETIME *creation_time,
                               FILETIME *exit_time,
                               FILETIME *kernel_time,
                               FILETIME *user_time) {
        if (!GetProcessTimes(proc_handle,
                             creation_time,
                             exit_time,
                             kernel_time,
                             user_time)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    unsigned long proc::system_version(unsigned long pid) {
        unsigned long version = GetProcessVersion(pid);
        if (!version) {
            error_code = GetLastError();
        }
        return version;
    }

    bool proc::get_working_set_size(HANDLE proc_handle,
                                    SIZE_T *min_working_set_size,
                                    SIZE_T *max_working_set_size) {
        if (GetProcessWorkingSetSize(proc_handle,
                                     min_working_set_size,
                                     max_working_set_size)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool proc::set_working_set_size(HANDLE proc_handle,
                                    size_t min_working_set_size,
                                    size_t max_working_set_size) {
        if (SetProcessWorkingSetSize(proc_handle,
                                     min_working_set_size,
                                     max_working_set_size)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool proc::get_processor_system_cycle_time(
        unsigned short group,
        SYSTEM_PROCESSOR_CYCLE_TIME_INFORMATION *buffer,
        unsigned long *ret_len) {
        if (!GetProcessorSystemCycleTime(group,
                                         buffer,
                                         ret_len)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool proc::is_microsoft_store_app(HANDLE proc_handle) {
        if (!IsImmersiveProcess(proc_handle)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool proc::is_exe_search_path(const wchar_t *exe_name) {
        return NeedCurrentDirectoryForExePathW(exe_name);
    }

    bool proc::query_full_image_name(HANDLE proc_handle,
                                     unsigned long flag,
                                     wchar_t *exe_name,
                                     unsigned long *size) {
        if (!QueryFullProcessImageNameW(proc_handle,
                                        flag,
                                        exe_name,
                                        size)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool proc::get_affinity_update_mode(HANDLE proc_handle,
                                        unsigned long *flag) {
        if (!QueryProcessAffinityUpdateMode(proc_handle,
                                            flag)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool proc::set_affinity_update_mode(HANDLE proc_handle, unsigned long flag) {
        if (!SetProcessAffinityUpdateMode(proc_handle,
                                          flag)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool proc::all_thread_cycle_time(HANDLE proc_handle,
                                     unsigned long long *cycle_time) {
        if (!QueryProcessCycleTime(proc_handle,
                                   cycle_time)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool proc::set_restriction_exemption(bool is_enable_exemption) {
        if (!SetProcessRestrictionExemption(
            is_enable_exemption ? TRUE : FALSE)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    unsigned long proc::err_code() const {
        return error_code;
    }

    std::string proc::err_string() const {
        std::string result = helper::convert::err_string(error_code);
        return result;
    }

    std::wstring proc::err_wstring() const {
        std::wstring result = helper::convert::err_wstring(error_code);
        return result;
    }
}
