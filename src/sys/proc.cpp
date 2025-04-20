//
// Created by forkernel on 2025/4/14.
//

#include "proc.h"

#include <algorithm>
#include <memory>

#include "security.h"
#include "helper/string.h"
#include "helper/convert.h"
#include "helper/autoclean.h"
#include <UserEnv.h>

#pragma comment(lib, "UserEnv.lib")

namespace YanLib::sys {
    proc::proc() {
        memset(&si, 0, sizeof(si));
        si.cb = sizeof(si);
        memset(&pi, 0, sizeof(pi));
    }

    proc::~proc() {
        if (curr_proc_env) {
            FreeEnvironmentStringsW(curr_proc_env);
        }
        if (snapshot_handle != INVALID_HANDLE_VALUE) {
            CloseHandle(snapshot_handle);
            snapshot_handle = INVALID_HANDLE_VALUE;
        }
        cleanup();
    }

    void proc::cleanup() {
        if (pi.hThread) {
            CloseHandle(pi.hThread);
            pi.hThread = nullptr;
        }
        if (pi.hProcess) {
            CloseHandle(pi.hProcess);
            pi.hProcess = nullptr;
        }
        memset(&si, 0, sizeof(si));
        si.cb = sizeof(si);
        memset(&pi, 0, sizeof(pi));
    }

    NTSTATUS proc::nt_query_info_proc(HANDLE proc_handle,
                                      PROCESSINFOCLASS proc_info_class,
                                      PVOID proc_info,
                                      ULONG proc_info_len,
                                      PULONG ret_len) {
        typedef NTSTATUS (CALLBACK *pfn)(HANDLE ProcessHandle,
                                         PROCESSINFOCLASS ProcessInformationClass,
                                         PVOID ProcessInformation,
                                         ULONG ProcessInformationLength,
                                         PULONG ReturnLength OPTIONAL);
        NTSTATUS status = -1;
        HMODULE ntdll_module = nullptr;
        do {
            ntdll_module = LoadLibraryW(L"ntdll.dll");
            if (!ntdll_module) {
                break;
            }
            pfn query_info_proc = reinterpret_cast<pfn>(
                GetProcAddress(ntdll_module, "NtQueryInformationProcess"));
            if (!query_info_proc) {
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

    bool proc::create(const wchar_t *app_name,
                      wchar_t *cmdline,
                      LPSECURITY_ATTRIBUTES proc_attrs,
                      LPSECURITY_ATTRIBUTES thread_attrs,
                      BOOL is_inherit_handles,
                      DWORD create_flag,
                      void *env,
                      const wchar_t *curr_dir) {
        cleanup();
        if (!CreateProcessW(app_name,
                            cmdline,
                            proc_attrs,
                            thread_attrs,
                            is_inherit_handles,
                            create_flag,
                            env,
                            curr_dir,
                            &si,
                            &pi)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool proc::create_with_suspended(const wchar_t *app_name,
                                     wchar_t *cmdline,
                                     LPSECURITY_ATTRIBUTES proc_attrs,
                                     LPSECURITY_ATTRIBUTES thread_attrs,
                                     BOOL is_inherit_handles,
                                     DWORD create_flag,
                                     void *env,
                                     const wchar_t *curr_dir) {
        cleanup();
        if (!CreateProcessW(app_name,
                            cmdline,
                            proc_attrs,
                            thread_attrs,
                            is_inherit_handles,
                            create_flag,
                            env,
                            curr_dir,
                            &si,
                            &pi)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool proc::create_as_user(HANDLE token_handle,
                              const wchar_t *app_name,
                              wchar_t *cmdline,
                              LPSECURITY_ATTRIBUTES proc_attrs,
                              LPSECURITY_ATTRIBUTES thread_attrs,
                              BOOL is_inherit_handles,
                              DWORD create_flag,
                              void *env,
                              const wchar_t *curr_dir) {
        cleanup();
        security security;
        void *environment = nullptr;
        if (env) {
            environment = env;
        } else {
            environment = security.create_env_block(token_handle);
            if (!environment) {
                error_code = security.err_code();
                return false;
            }
        }
        if (!CreateProcessAsUserW(token_handle,
                                  app_name,
                                  cmdline,
                                  proc_attrs,
                                  thread_attrs,
                                  is_inherit_handles,
                                  create_flag,
                                  environment,
                                  curr_dir,
                                  &si,
                                  &pi)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool proc::create_session_zero(const wchar_t *app_name,
                                   wchar_t *cmdline,
                                   LPSECURITY_ATTRIBUTES proc_attrs,
                                   LPSECURITY_ATTRIBUTES thread_attrs,
                                   BOOL is_inherit_handles,
                                   DWORD create_flag,
                                   void *env,
                                   const wchar_t *curr_dir) {
        cleanup();
        security security;
        helper::autoclean<HANDLE> token_handle(nullptr);
        token_handle = security.copy_token();
        if (!token_handle.is_ok()) {
            error_code = security.err_code();
            return false;
        }
        void *environment = nullptr;
        if (env) {
            environment = env;
        } else {
            environment = security.create_env_block(token_handle);
            if (!environment) {
                error_code = security.err_code();
                return false;
            }
        }
        if (!CreateProcessAsUserW(token_handle,
                                  app_name,
                                  cmdline,
                                  proc_attrs,
                                  thread_attrs,
                                  is_inherit_handles,
                                  create_flag,
                                  environment,
                                  curr_dir,
                                  &si,
                                  &pi)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool proc::create_with_logon(const wchar_t *username,
                                 const wchar_t *domain,
                                 const wchar_t *password,
                                 const wchar_t *app_name,
                                 wchar_t *cmdline,
                                 DWORD logon_flag,
                                 DWORD create_flag,
                                 void *env,
                                 const wchar_t *curr_dir) {
        cleanup();
        security security;
        helper::autoclean<HANDLE> token_handle(nullptr);
        token_handle = security.copy_token();
        if (!token_handle.is_ok()) {
            error_code = security.err_code();
            return false;
        }
        void *environment = nullptr;
        if (env) {
            environment = env;
        } else {
            environment = security.create_env_block(token_handle);
            if (!environment) {
                error_code = security.err_code();
                return false;
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
            return false;
        }
        return true;
    }

    bool proc::create_with_token(HANDLE token_handle,
                                 const wchar_t *app_name,
                                 wchar_t *cmdline,
                                 DWORD logon_flag,
                                 DWORD create_flag,
                                 void *env,
                                 const wchar_t *curr_dir) {
        cleanup();
        security security;
        void *environment = nullptr;
        if (env) {
            environment = env;
        } else {
            environment = security.create_env_block(token_handle);
            if (!environment) {
                error_code = security.err_code();
                return false;
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
            return false;
        }
        return true;
    }

    bool proc::win_exec(const char *cmdline, UINT show_flag) {
        UINT ret = WinExec(cmdline, show_flag);
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
                          INT show_flag,
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

    void *proc::malloc(HANDLE proc_handle,
                       size_t size,
                       void *addr,
                       DWORD allocate_flag,
                       DWORD protect_flag) {
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
                    DWORD free_type) {
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
                               DWORD allocate_type,
                               DWORD protect_flag) {
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
                            DWORD free_type) {
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
                              DWORD new_protect_flag,
                              PDWORD old_protect_flag) {
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
        DWORD size = GetEnvironmentVariableW(var_name.data(),
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
        if (!SetEnvironmentVariableW(var_name.data(), var_value.data())) {
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
        HANDLE process_handle = proc_handle ? proc_handle : GetCurrentProcess();
        DWORD ret_size = 0;
        PROCESS_BASIC_INFORMATION pbi{};
        do {
            NTSTATUS status = nt_query_info_proc(process_handle,
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
            std::vector<wchar_t> cmdline(MAX_PATH + 1, L'\0');
            if (!ReadProcessMemory(process_handle,
                                   block->cmdline,
                                   cmdline.data(),
                                   cmdline.size(),
                                   &size)) {
                error_code = GetLastError();
                break;
            }
            cmdline.resize(size);
            cmdline.shrink_to_fit();
            return cmdline.data();
        } while (false);
        return {};
    }

    std::string proc::cmdline(DWORD pid) {
        return cmdline(pid_to_handle(pid));
    }

    std::wstring proc::cmdline_wide(DWORD pid) {
        return cmdline_wide(pid_to_handle(pid));
    }

    std::string proc::owner(HANDLE proc_handle) {
        std::wstring result = owner_wide(proc_handle);
        return helper::convert::wstr_to_str(result);
    }

    std::wstring proc::owner_wide(HANDLE proc_handle) {
        HANDLE process_handle = proc_handle ? proc_handle : GetCurrentProcess();
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
            DWORD size = 0;
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
            DWORD user_size = MAX_PATH;
            PDWORD user_size_ptr = &user_size;
            TCHAR domain[MAX_PATH];
            DWORD domain_size = MAX_PATH;
            PDWORD domain_size_ptr = &domain_size;
            if (!LookupAccountSidW(nullptr,
                                   reinterpret_cast<PTOKEN_USER>(
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

    std::string proc::owner(DWORD pid) {
        return owner(pid_to_handle(pid));
    }

    std::wstring proc::owner_wide(DWORD pid) {
        return owner_wide(pid_to_handle(pid));
    }


    std::string proc::image_name(HANDLE proc_handle) {
        HANDLE process_handle = proc_handle ? proc_handle : GetCurrentProcess();
        std::string name(MAX_PATH, '\0');
        DWORD size = 0;
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
        HANDLE process_handle = proc_handle ? proc_handle : GetCurrentProcess();
        std::wstring name(MAX_PATH, L'\0');
        DWORD size = 0;
        if (!QueryFullProcessImageNameW(process_handle,
                                        0,
                                        name.data(),
                                        &size)) {
            error_code = GetLastError();
            return {};
        }
        name.resize(size);
        return name;
    }

    void *proc::module_image_base(MODULEENTRY32W &module_entry) {
        IMAGE_DOS_HEADER dos_header{};
        IMAGE_NT_HEADERS64 nt_headers64{};
        IMAGE_NT_HEADERS32 nt_headers32{};
        do {
            if (!Toolhelp32ReadProcessMemory(module_entry.th32ProcessID,
                                             module_entry.modBaseAddr,
                                             &dos_header,
                                             sizeof(dos_header),
                                             nullptr)) {
                break;
            }
            if (dos_header.e_magic != IMAGE_DOS_SIGNATURE) {
                break;
            }
            if (!Toolhelp32ReadProcessMemory(module_entry.th32ProcessID,
                                             module_entry.modBaseAddr + dos_header.e_lfanew,
                                             &nt_headers64,
                                             sizeof(nt_headers64),
                                             nullptr)) {
                break;
            }
            if (nt_headers64.Signature != IMAGE_NT_SIGNATURE) {
                break;
            }

            if (nt_headers64.FileHeader.Machine == IMAGE_FILE_MACHINE_AMD64 ||
                nt_headers64.FileHeader.Machine == IMAGE_FILE_MACHINE_ARM64) {
                return reinterpret_cast<void *>(nt_headers64.OptionalHeader.ImageBase);
            } else {
                if (!Toolhelp32ReadProcessMemory(module_entry.th32ProcessID,
                                                 module_entry.modBaseAddr + dos_header.e_lfanew,
                                                 &nt_headers32,
                                                 sizeof(nt_headers32),
                                                 nullptr)) {
                    break;
                }
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
                return reinterpret_cast<void *>(nt_headers64.OptionalHeader.ImageBase);
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
        HANDLE process_handle = proc_handle ? proc_handle : GetCurrentProcess();
        PROCESS_BASIC_INFORMATION pbi;
        NTSTATUS status = nt_query_info_proc(process_handle,
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

    void *proc::image_base(DWORD pid) {
        return image_base(pid_to_handle(pid));
    }

    DWORD proc::get_priority(HANDLE proc_handle) {
        DWORD priority = GetPriorityClass(proc_handle);
        if (!priority) {
            error_code = GetLastError();
        }
        return priority;
    }

    bool proc::set_priority(HANDLE proc_handle, DWORD priority) {
        if (!SetPriorityClass(proc_handle, priority)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    int proc::get_thread_priority(HANDLE thread_handle) {
        int priority = GetThreadPriority(thread_handle);
        if (!priority) {
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

    DWORD proc::handle_count(HANDLE proc_handle) {
        DWORD count = 0;
        if (!GetProcessHandleCount(proc_handle, &count)) {
            error_code = GetLastError();
        }
        return count;
    }

    DWORD proc::gui_handle_count(HANDLE proc_handle, DWORD flag) {
        DWORD count = GetGuiResources(proc_handle, flag);
        if (!count) {
            error_code = GetLastError();
        }
        return count;
    }

    DWORD proc::processor_num() {
        return GetCurrentProcessorNumber();
    }

    DWORD proc::exit_status(HANDLE proc_handle) {
        DWORD exit_status = 0;
        if (!GetExitCodeProcess(proc_handle, &exit_status)) {
            error_code = GetLastError();
        }
        return exit_status;
    }

    void proc::kill(UINT exit_code) {
        ExitProcess(exit_code);
    }

    bool proc::fake_proc(HANDLE proc_handle,
                         const wchar_t *app_name,
                         const wchar_t *cmdline) {
        DWORD size = 0;
        PROCESS_BASIC_INFORMATION pbi{};
        do {
            NTSTATUS status = nt_query_info_proc(proc_handle,
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
            USHORT len = (wcslen(cmdline) + 1) * sizeof(wchar_t);
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

    HANDLE proc::thread_handle() {
        return GetCurrentThread();
    }

    HANDLE proc::proc_handle() {
        return GetCurrentProcess();
    }

    DWORD proc::thread_id() {
        return GetCurrentThreadId();
    }

    DWORD proc::proc_id() {
        return GetCurrentProcessId();
    }

    HANDLE proc::pid_to_handle(DWORD pid,
                               DWORD desired_access,
                               BOOL is_inherit_handle) {
        HANDLE proc_handle = OpenProcess(desired_access,
                                         is_inherit_handle,
                                         pid);
        if (!proc_handle) {
            error_code = GetLastError();
        }
        return proc_handle;
    }

    DWORD proc::handle_to_pid(HANDLE proc_handle) {
        DWORD pid = GetProcessId(proc_handle);
        if (!pid) {
            error_code = GetLastError();
        }
        return pid;
    }

    bool proc::is_heap(HANDLE proc_handle, void *address) {
        if (!proc_handle) {
            return false;
        }
        const DWORD pid = handle_to_pid(proc_handle);
        if (!pid) {
            return false;
        }
        std::vector<HEAPENTRY32> blocks = find_heap_blocks(pid);
        if (blocks.empty()) {
            return false;
        }
        for (auto block: blocks) {
            MEMORY_BASIC_INFORMATION mbi;
            if (!VirtualQueryEx(proc_handle,
                                reinterpret_cast<void *>(block.dwAddress),
                                &mbi,
                                sizeof(mbi))) {
                error_code = GetLastError();
                break;
            }
            if (address >= static_cast<uint8_t *>(mbi.AllocationBase) &&
                address <= static_cast<uint8_t *>(mbi.AllocationBase) + mbi.RegionSize) {
                return true;
            }
        }
        return false;
    }

    bool proc::is_heap(DWORD pid, void *address) {
        HANDLE proc_handle = nullptr;
        if (GetCurrentProcessId() == pid) {
            proc_handle = GetCurrentProcess();
        } else {
            proc_handle = pid_to_handle(pid);
        }
        if (!proc_handle) {
            return false;
        }
        std::vector<HEAPENTRY32> blocks = find_heap_blocks(pid);
        if (blocks.empty()) {
            return false;
        }
        for (auto block: blocks) {
            MEMORY_BASIC_INFORMATION mbi;
            if (!VirtualQueryEx(proc_handle,
                                reinterpret_cast<void *>(block.dwAddress),
                                &mbi,
                                sizeof(mbi))) {
                error_code = GetLastError();
                break;
            }
            if (address >= static_cast<uint8_t *>(mbi.AllocationBase) &&
                address <= static_cast<uint8_t *>(mbi.AllocationBase) + mbi.RegionSize) {
                return true;
            }
        }
        return false;
    }

    HANDLE proc::child_thread_handle() const {
        return pi.hThread;
    }

    HANDLE proc::child_proc_handle() const {
        return pi.hProcess;
    }

    DWORD proc::child_thread_id() {
        if (pi.hThread) {
            DWORD id = GetThreadId(pi.hThread);
            if (!id) {
                error_code = GetLastError();
            }
            return id;
        }
        return 0;
    }

    DWORD proc::child_proc_id() {
        if (pi.hProcess) {
            DWORD id = GetProcessId(pi.hProcess);
            if (!id) {
                error_code = GetLastError();
            }
            return id;
        }
        return 0;
    }

    bool proc::wait_child(DWORD milli_seconds) {
        if (pi.hProcess) {
            DWORD ret = WaitForSingleObject(pi.hProcess, milli_seconds);
            if (ret == WAIT_OBJECT_0) {
                return true;
            }
            error_code = GetLastError();
        }
        return false;
    }

    bool proc::resume_child() {
        if (pi.hThread) {
            if (ResumeThread(pi.hThread) == -1) {
                error_code = GetLastError();
                return false;
            }
            return true;
        }
        return false;
    }

    std::vector<PROCESSENTRY32W> proc::ls_procs(DWORD pid) {
        if (!procs.empty()) {
            return procs;
        }
        if (snapshot_handle != INVALID_HANDLE_VALUE) {
            CloseHandle(snapshot_handle);
            snapshot_handle = INVALID_HANDLE_VALUE;
        }
        PROCESSENTRY32W pe = {sizeof(PROCESSENTRY32W)};
        do {
            snapshot_handle = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,
                                                       pid);
            if (snapshot_handle == INVALID_HANDLE_VALUE) {
                error_code = GetLastError();
                break;
            }
            if (!Process32FirstW(snapshot_handle, &pe)) {
                error_code = GetLastError();
                break;
            }
            procs.push_back(pe);
            while (Process32NextW(snapshot_handle, &pe)) {
                procs.push_back(pe);
            }
        } while (false);
        return procs;
    }

    std::unordered_set<DWORD> proc::ls_pids(DWORD pid) {
        if (!pids.empty()) {
            return pids;
        }
        if (!procs.empty()) {
            for (auto process: procs) {
                pids.insert(process.th32ProcessID);
            }
            return pids;
        }
        if (snapshot_handle != INVALID_HANDLE_VALUE) {
            CloseHandle(snapshot_handle);
            snapshot_handle = INVALID_HANDLE_VALUE;
        }
        PROCESSENTRY32W pe = {sizeof(PROCESSENTRY32W)};
        do {
            snapshot_handle = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,
                                                       pid);
            if (snapshot_handle == INVALID_HANDLE_VALUE) {
                error_code = GetLastError();
                break;
            }
            if (!Process32FirstW(snapshot_handle, &pe)) {
                error_code = GetLastError();
                break;
            }
            pids.insert(pe.th32ProcessID);
            while (Process32NextW(snapshot_handle, &pe)) {
                pids.insert(pe.th32ProcessID);
            }
        } while (false);
        return pids;
    }

    void proc::refresh_procs() {
        procs.clear();
        pids.clear();
    }

    bool proc::pid_exists(DWORD pid) {
        if (pids.empty()) {
            ls_pids();
        }
        return pids.find(pid) != pids.end();
    }

    DWORD proc::get_ppid(DWORD pid) {
        if (procs.empty()) {
            ls_procs();
        }
        for (auto process: procs) {
            if (process.th32ProcessID == pid) {
                return process.th32ParentProcessID;
            }
        }
        return 0;
    }

    PROCESSENTRY32W proc::find_proc(DWORD pid) {
        if (procs.empty()) {
            ls_procs();
        }
        for (auto process: procs) {
            if (process.th32ProcessID == pid) {
                return process;
            }
        }
        return {};
    }

    PROCESSENTRY32W proc::find_proc(const wchar_t *proc_name) {
        if (!proc_name || wcslen(proc_name) == 0) {
            return {};
        }
        if (procs.empty()) {
            ls_procs();
        }
        for (auto process: procs) {
            if (helper::string::strstr_case_insen(process.szExeFile,
                                                  proc_name)) {
                return process;
            }
        }
        return {};
    }

    std::vector<THREADENTRY32> proc::ls_threads(DWORD pid) {
        if (!threads.empty()) {
            return threads;
        }
        if (snapshot_handle != INVALID_HANDLE_VALUE) {
            CloseHandle(snapshot_handle);
            snapshot_handle = INVALID_HANDLE_VALUE;
        }
        THREADENTRY32 te = {sizeof(THREADENTRY32)};
        do {
            snapshot_handle = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD,
                                                       pid);
            if (snapshot_handle == INVALID_HANDLE_VALUE) {
                error_code = GetLastError();
                break;
            }
            if (!Thread32First(snapshot_handle, &te)) {
                error_code = GetLastError();
                break;
            }
            threads.push_back(te);
            while (Thread32Next(snapshot_handle, &te)) {
                threads.push_back(te);
            }
        } while (false);
        return threads;
    }

    std::unordered_set<DWORD> proc::ls_thread_ids(DWORD pid) {
        if (!thread_ids.empty()) {
            return thread_ids;
        }
        if (!threads.empty()) {
            for (auto thread: threads) {
                thread_ids.insert(thread.th32ThreadID);
            }
            return thread_ids;
        }
        if (snapshot_handle != INVALID_HANDLE_VALUE) {
            CloseHandle(snapshot_handle);
            snapshot_handle = INVALID_HANDLE_VALUE;
        }
        THREADENTRY32 te = {sizeof(THREADENTRY32)};
        do {
            snapshot_handle = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD,
                                                       pid);
            if (snapshot_handle == INVALID_HANDLE_VALUE) {
                error_code = GetLastError();
                break;
            }
            if (!Thread32First(snapshot_handle, &te)) {
                error_code = GetLastError();
                break;
            }
            thread_ids.insert(te.th32ThreadID);
            while (Thread32Next(snapshot_handle, &te)) {
                thread_ids.insert(te.th32ThreadID);
            }
        } while (false);
        return thread_ids;
    }

    void proc::refresh_threads() {
        threads.clear();
        thread_ids.clear();
    }

    bool proc::tid_exists(DWORD tid) {
        if (thread_ids.empty()) {
            ls_thread_ids();
        }
        return thread_ids.find(tid) != thread_ids.end();
    }

    DWORD proc::tid_to_pid(DWORD tid) {
        if (threads.empty()) {
            ls_threads();
        }
        for (auto thread: threads) {
            if (thread.th32ThreadID == tid) {
                return thread.th32OwnerProcessID;
            }
        }
        return 0;
    }

    THREADENTRY32 proc::find_thread(DWORD tid) {
        if (threads.empty()) {
            ls_threads();
        }
        for (auto thread: threads) {
            if (thread.th32ThreadID == tid) {
                return thread;
            }
        }
        return {};
    }

    std::vector<THREADENTRY32> proc::find_threads(DWORD pid) {
        if (threads.empty()) {
            ls_threads();
        }
        std::vector<THREADENTRY32> result;
        for (auto thread: threads) {
            if (thread.th32OwnerProcessID == pid) {
                result.push_back(thread);
            }
        }
        return result;
    }


    std::vector<MODULEENTRY32W> proc::ls_modules(DWORD pid) {
        if (!modules.empty()) {
            return modules;
        }
        if (snapshot_handle != INVALID_HANDLE_VALUE) {
            CloseHandle(snapshot_handle);
            snapshot_handle = INVALID_HANDLE_VALUE;
        }
        MODULEENTRY32W me = {sizeof(MODULEENTRY32W)};
        do {
            snapshot_handle = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE,
                                                       pid);
            if (snapshot_handle == INVALID_HANDLE_VALUE) {
                error_code = GetLastError();
                break;
            }
            if (!Module32FirstW(snapshot_handle, &me)) {
                error_code = GetLastError();
                break;
            }
            modules.push_back(me);
            while (Module32NextW(snapshot_handle, &me)) {
                modules.push_back(me);
            }
        } while (false);
        return modules;
    }

    std::unordered_set<HMODULE> proc::ls_module_handles(DWORD pid) {
        if (!module_handles.empty()) {
            return module_handles;
        }
        if (!modules.empty()) {
            for (auto module: modules) {
                module_handles.insert(module.hModule);
            }
            return module_handles;
        }
        if (snapshot_handle != INVALID_HANDLE_VALUE) {
            CloseHandle(snapshot_handle);
            snapshot_handle = INVALID_HANDLE_VALUE;
        }
        MODULEENTRY32W me = {sizeof(MODULEENTRY32W)};
        do {
            snapshot_handle = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE,
                                                       pid);
            if (snapshot_handle == INVALID_HANDLE_VALUE) {
                error_code = GetLastError();
                break;
            }
            if (!Module32FirstW(snapshot_handle, &me)) {
                error_code = GetLastError();
                break;
            }
            module_handles.insert(me.hModule);
            while (Module32NextW(snapshot_handle, &me)) {
                module_handles.insert(me.hModule);
            }
        } while (false);
        return module_handles;
    }

    void proc::refresh_modules() {
        modules.clear();
        module_handles.clear();
    }

    MODULEENTRY32W proc::find_module(const wchar_t *proc_name) {
        if (!proc_name || wcslen(proc_name) == 0) {
            return {};
        }
        if (modules.empty()) {
            ls_modules();
        }
        for (auto module: modules) {
            if (helper::string::strstr_case_insen(module.szModule,
                                                  proc_name) ||
                helper::string::strstr_case_insen(module.szExePath,
                                                  proc_name)) {
                return module;
            }
        }
        return {};
    }

    MODULEENTRY32W proc::find_module(const void *address) {
        if (!address) {
            return {};
        }
        if (modules.empty()) {
            ls_modules();
        }
        for (auto module: modules) {
            if (module.modBaseAddr == address) {
                return module;
            }
        }
        return {};
    }

    std::vector<HEAPLIST32> proc::ls_heaps(DWORD pid) {
        if (!heaps.empty()) {
            return heaps;
        }
        if (snapshot_handle != INVALID_HANDLE_VALUE) {
            CloseHandle(snapshot_handle);
            snapshot_handle = INVALID_HANDLE_VALUE;
        }
        HEAPLIST32 he = {sizeof(HEAPLIST32)};
        do {
            snapshot_handle = CreateToolhelp32Snapshot(TH32CS_SNAPHEAPLIST,
                                                       pid);
            if (snapshot_handle == INVALID_HANDLE_VALUE) {
                error_code = GetLastError();
                break;
            }
            if (!Heap32ListFirst(snapshot_handle, &he)) {
                error_code = GetLastError();
                break;
            }
            heaps.push_back(he);
            while (Heap32ListNext(snapshot_handle, &he)) {
                heaps.push_back(he);
            }
        } while (false);
        return heaps;
    }

    std::unordered_set<ULONG_PTR> proc::ls_heap_ids(DWORD pid) {
        if (!heap_ids.empty()) {
            return heap_ids;
        }
        if (!heaps.empty()) {
            for (auto heap: heaps) {
                heap_ids.insert(heap.th32HeapID);
            }
            return heap_ids;
        }
        if (snapshot_handle != INVALID_HANDLE_VALUE) {
            CloseHandle(snapshot_handle);
            snapshot_handle = INVALID_HANDLE_VALUE;
        }
        HEAPLIST32 he = {sizeof(HEAPLIST32)};
        do {
            snapshot_handle = CreateToolhelp32Snapshot(TH32CS_SNAPHEAPLIST,
                                                       pid);
            if (snapshot_handle == INVALID_HANDLE_VALUE) {
                error_code = GetLastError();
                break;
            }
            if (!Heap32ListFirst(snapshot_handle, &he)) {
                error_code = GetLastError();
                break;
            }
            heap_ids.insert(he.th32HeapID);
            while (Heap32ListNext(snapshot_handle, &he)) {
                heap_ids.insert(he.th32HeapID);
            }
        } while (false);
        return heap_ids;
    }

    void proc::refresh_heaps() {
        heaps.clear();
        heap_ids.clear();
    }

    HEAPLIST32 proc::find_heap(ULONG_PTR heap_id) {
        if (heaps.empty()) {
            ls_heaps();
        }
        for (auto heap: heaps) {
            if (heap.th32HeapID == heap_id) {
                return heap;
            }
        }
        return {};
    }

    std::vector<HEAPLIST32> proc::find_heaps(DWORD pid) {
        if (heaps.empty()) {
            ls_heaps();
        }
        std::vector<HEAPLIST32> result;
        for (auto heap: heaps) {
            if (heap.th32ProcessID == pid) {
                result.push_back(heap);
            }
        }
        return result;
    }

    std::vector<HEAPENTRY32>
    proc::find_heap_blocks(HEAPLIST32 &heap_list) {
        HEAPENTRY32 he = {sizeof(HEAPENTRY32)};
        std::vector<HEAPENTRY32> result;
        do {
            if (!Heap32First(&he, heap_list.th32ProcessID, heap_list.th32HeapID)) {
                error_code = GetLastError();
                break;
            }
            result.push_back(he);
            while (Heap32Next(&he)) {
                result.push_back(he);
            }
        } while (false);
        return result;
    }

    std::vector<HEAPENTRY32> proc::find_heap_blocks(ULONG_PTR heap_id) {
        HEAPENTRY32 he = {sizeof(HEAPENTRY32)};
        std::vector<HEAPENTRY32> result;
        do {
            HEAPLIST32 heaplist32 = find_heap(heap_id);
            if (!Heap32First(&he, heaplist32.th32ProcessID, heap_id)) {
                error_code = GetLastError();
                break;
            }
            result.push_back(he);
            while (Heap32Next(&he)) {
                result.push_back(he);
            }
        } while (false);
        return result;
    }

    std::vector<HEAPENTRY32> proc::find_heap_blocks(DWORD pid) {
        HEAPENTRY32 he = {sizeof(HEAPENTRY32)};
        std::vector<HEAPENTRY32> result;
        do {
            auto heaplists = find_heaps(pid);
            if (heaplists.empty()) {
                break;
            }
            for (auto heaplist: heaplists) {
                if (!Heap32First(&he, heaplist.th32ProcessID, heaplist.th32HeapID)) {
                    error_code = GetLastError();
                    break;
                }
                result.push_back(he);
                while (Heap32Next(&he)) {
                    result.push_back(he);
                }
            }
        } while (false);
        return result;
    }

    DWORD proc::err_code() const {
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
