/* clang-format off */
/*
 * @file proc.cpp
 * @date 2025-04-14
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
#include "proc.h"
#include "security.h"
#include "helper/autoclean.h"
#include <complex>
#include <memory>
#include <UserEnv.h>

#pragma comment(lib, "UserEnv.Lib")

namespace YanLib::sys {
    proc::~proc() {
        for (auto &info : proc_infos) {
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
        for (auto &proc_handle : proc_handles) {
            CloseHandle(proc_handle);
            proc_handle = nullptr;
        }
        proc_handles.clear();
    }

    NTSTATUS proc::nt_query_info_proc(HANDLE proc_handle,
                                      PROCESSINFOCLASS proc_info_class,
                                      void *proc_info,
                                      uint32_t proc_info_len,
                                      uint32_t *real_size) {
        typedef NTSTATUS(CALLBACK *
                         prototype)(HANDLE ProcessHandle,
                                    PROCESSINFOCLASS ProcessInformationClass,
                                    void *ProcessInformation,
                                    uint32_t ProcessInformationLength,
                                    uint32_t *ReturnLength OPTIONAL);
        NTSTATUS status = -1;
        HMODULE ntdll = nullptr;
        do {
            ntdll = LoadLibraryW(L"ntdll.dll");
            if (!ntdll) {
                error_code = GetLastError();
                break;
            }
            const auto func = reinterpret_cast<prototype>(
                    GetProcAddress(ntdll, "NtQueryInformationProcess"));
            if (!func) {
                error_code = GetLastError();
                break;
            }
            status = func(proc_handle, proc_info_class, proc_info,
                          proc_info_len, real_size);
        } while (false);
        if (ntdll) {
            FreeLibrary(ntdll);
        }
        return status;
    }

    PROCESS_INFORMATION proc::create(const char *app_name,
                                     char *cmdline,
                                     SECURITY_ATTRIBUTES *proc_attrs,
                                     SECURITY_ATTRIBUTES *thread_attrs,
                                     const bool is_inherit,
                                     const ProcCreateFlag create_flag,
                                     void *env,
                                     const char *curr_dir) {
        STARTUPINFOA si = {};
        PROCESS_INFORMATION pi = {};
        si.cb = sizeof(si);
        if (!CreateProcessA(app_name, cmdline, proc_attrs, thread_attrs,
                            is_inherit ? TRUE : FALSE,
                            static_cast<uint32_t>(create_flag), env, curr_dir,
                            &si, &pi)) {
            error_code = GetLastError();
            return {};
        }
        proc_info_rwlock.write_lock();
        proc_infos.push_back(pi);
        proc_info_rwlock.write_unlock();
        return pi;
    }

    PROCESS_INFORMATION proc::create(const wchar_t *app_name,
                                     wchar_t *cmdline,
                                     SECURITY_ATTRIBUTES *proc_attrs,
                                     SECURITY_ATTRIBUTES *thread_attrs,
                                     const bool is_inherit,
                                     const ProcCreateFlag create_flag,
                                     void *env,
                                     const wchar_t *curr_dir) {
        STARTUPINFOW si = {};
        PROCESS_INFORMATION pi = {};
        si.cb = sizeof(si);
        if (!CreateProcessW(app_name, cmdline, proc_attrs, thread_attrs,
                            is_inherit ? TRUE : FALSE,
                            static_cast<uint32_t>(create_flag), env, curr_dir,
                            &si, &pi)) {
            error_code = GetLastError();
            return {};
        }
        proc_info_rwlock.write_lock();
        proc_infos.push_back(pi);
        proc_info_rwlock.write_unlock();
        return pi;
    }

    PROCESS_INFORMATION
    proc::create_with_suspended(const char *app_name,
                                char *cmdline,
                                SECURITY_ATTRIBUTES *proc_attrs,
                                SECURITY_ATTRIBUTES *thread_attrs,
                                const bool is_inherit,
                                const ProcCreateFlag create_flag,
                                void *env,
                                const char *curr_dir) {
        STARTUPINFOA si = {};
        PROCESS_INFORMATION pi = {};
        si.cb = sizeof(si);
        if (!CreateProcessA(app_name, cmdline, proc_attrs, thread_attrs,
                            is_inherit ? TRUE : FALSE,
                            static_cast<uint32_t>(create_flag), env, curr_dir,
                            &si, &pi)) {
            error_code = GetLastError();
            return {};
        }
        proc_info_rwlock.write_lock();
        proc_infos.push_back(pi);
        proc_info_rwlock.write_unlock();
        return pi;
    }

    PROCESS_INFORMATION
    proc::create_with_suspended(const wchar_t *app_name,
                                wchar_t *cmdline,
                                SECURITY_ATTRIBUTES *proc_attrs,
                                SECURITY_ATTRIBUTES *thread_attrs,
                                const bool is_inherit,
                                const ProcCreateFlag create_flag,
                                void *env,
                                const wchar_t *curr_dir) {
        STARTUPINFOW si = {};
        PROCESS_INFORMATION pi = {};
        si.cb = sizeof(si);
        if (!CreateProcessW(app_name, cmdline, proc_attrs, thread_attrs,
                            is_inherit ? TRUE : FALSE,
                            static_cast<uint32_t>(create_flag), env, curr_dir,
                            &si, &pi)) {
            error_code = GetLastError();
            return {};
        }
        proc_info_rwlock.write_lock();
        proc_infos.push_back(pi);
        proc_info_rwlock.write_unlock();
        return pi;
    }

    PROCESS_INFORMATION proc::create_as_user(HANDLE token_handle,
                                             const char *app_name,
                                             char *cmdline,
                                             SECURITY_ATTRIBUTES *proc_attrs,
                                             SECURITY_ATTRIBUTES *thread_attrs,
                                             const bool is_inherit,
                                             const ProcCreateFlag create_flag,
                                             void *env,
                                             const char *curr_dir) {
        STARTUPINFOA si = {};
        PROCESS_INFORMATION pi = {};
        si.cb = sizeof(si);
        void *environment = nullptr;
        if (env) {
            environment = env;
        } else {
            security security;
            environment = security.create_env_block(token_handle);
            if (!environment) {
                error_code = security.err_code();
                return {};
            }
        }
        if (!CreateProcessAsUserA(token_handle, app_name, cmdline, proc_attrs,
                                  thread_attrs, is_inherit ? TRUE : FALSE,
                                  static_cast<uint32_t>(create_flag),
                                  environment, curr_dir, &si, &pi)) {
            error_code = GetLastError();
            return {};
        }
        proc_info_rwlock.write_lock();
        proc_infos.push_back(pi);
        proc_info_rwlock.write_unlock();
        return pi;
    }

    PROCESS_INFORMATION proc::create_as_user(HANDLE token_handle,
                                             const wchar_t *app_name,
                                             wchar_t *cmdline,
                                             SECURITY_ATTRIBUTES *proc_attrs,
                                             SECURITY_ATTRIBUTES *thread_attrs,
                                             const bool is_inherit,
                                             const ProcCreateFlag create_flag,
                                             void *env,
                                             const wchar_t *curr_dir) {
        STARTUPINFOW si = {};
        PROCESS_INFORMATION pi = {};
        si.cb = sizeof(si);
        void *environment = nullptr;
        if (env) {
            environment = env;
        } else {
            security security;
            environment = security.create_env_block(token_handle);
            if (!environment) {
                error_code = security.err_code();
                return {};
            }
        }
        if (!CreateProcessAsUserW(token_handle, app_name, cmdline, proc_attrs,
                                  thread_attrs, is_inherit ? TRUE : FALSE,
                                  static_cast<uint32_t>(create_flag),
                                  environment, curr_dir, &si, &pi)) {
            error_code = GetLastError();
            return {};
        }
        proc_info_rwlock.write_lock();
        proc_infos.push_back(pi);
        proc_info_rwlock.write_unlock();
        return pi;
    }

    PROCESS_INFORMATION
    proc::create_with_logon(const char *username,
                            const char *domain,
                            const char *password,
                            const char *app_name,
                            const char *cmdline,
                            const LogonFlag logon_flag,
                            const ProcCreateFlag create_flag,
                            void *env,
                            const char *curr_dir,
                            helper::CodePage code_page) {
        const std::wstring user =
                helper::convert::str_to_wstr(username, code_page);
        const std::wstring dom =
                helper::convert::str_to_wstr(domain, code_page);
        const std::wstring pass =
                helper::convert::str_to_wstr(password, code_page);
        const std::wstring app =
                helper::convert::str_to_wstr(app_name, code_page);
        std::wstring cmd = helper::convert::str_to_wstr(cmdline, code_page);
        const std::wstring curr =
                helper::convert::str_to_wstr(curr_dir, code_page);
        return create_with_logon(user.data(), dom.data(), pass.data(),
                                 app.data(), cmd.data(), logon_flag,
                                 create_flag, env, curr.data());
    }

    PROCESS_INFORMATION
    proc::create_with_logon(const wchar_t *username,
                            const wchar_t *domain,
                            const wchar_t *password,
                            const wchar_t *app_name,
                            wchar_t *cmdline,
                            const LogonFlag logon_flag,
                            const ProcCreateFlag create_flag,
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
        if (!CreateProcessWithLogonW(username, domain, password,
                                     static_cast<uint32_t>(logon_flag),
                                     app_name, cmdline,
                                     static_cast<uint32_t>(create_flag),
                                     environment, curr_dir, &si, &pi)) {
            error_code = GetLastError();
            return {};
        }
        proc_info_rwlock.write_lock();
        proc_infos.push_back(pi);
        proc_info_rwlock.write_unlock();
        return pi;
    }

    PROCESS_INFORMATION
    proc::create_with_token(HANDLE token_handle,
                            const char *app_name,
                            const char *cmdline,
                            const LogonFlag logon_flag,
                            const ProcCreateFlag create_flag,
                            void *env,
                            const char *curr_dir,
                            helper::CodePage code_page) {
        const std::wstring app =
                helper::convert::str_to_wstr(app_name, code_page);
        std::wstring cmd = helper::convert::str_to_wstr(cmdline, code_page);
        const std::wstring curr =
                helper::convert::str_to_wstr(curr_dir, code_page);
        return create_with_token(token_handle, app.data(), cmd.data(),
                                 logon_flag, create_flag, env, curr.data());
    }

    PROCESS_INFORMATION
    proc::create_with_token(HANDLE token_handle,
                            const wchar_t *app_name,
                            wchar_t *cmdline,
                            const LogonFlag logon_flag,
                            const ProcCreateFlag create_flag,
                            void *env,
                            const wchar_t *curr_dir) {
        STARTUPINFOW si = {};
        PROCESS_INFORMATION pi = {};
        si.cb = sizeof(si);
        void *environment = nullptr;
        if (env) {
            environment = env;
        } else {
            security security;
            environment = security.create_env_block(token_handle);
            if (!environment) {
                error_code = security.err_code();
                return {};
            }
        }
        if (!CreateProcessWithTokenW(token_handle,
                                     static_cast<uint32_t>(logon_flag),
                                     app_name, cmdline,
                                     static_cast<uint32_t>(create_flag),
                                     environment, curr_dir, &si, &pi)) {
            error_code = GetLastError();
            return {};
        }
        proc_info_rwlock.write_lock();
        proc_infos.push_back(pi);
        proc_info_rwlock.write_unlock();
        return pi;
    }

    bool proc::win_exec(const char *cmdline, ShowType show_flag) {
        const uint32_t ret = WinExec(cmdline, static_cast<uint32_t>(show_flag));
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

    bool proc::shell_exec(const char *file_name,
                          const char *params,
                          const char *dir,
                          ShowType show_flag,
                          HWND window_handle,
                          const char *operation) {
        HINSTANCE instance =
                ShellExecuteA(window_handle, operation, file_name, params, dir,
                              static_cast<int32_t>(show_flag));
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

    bool proc::shell_exec(const wchar_t *file_name,
                          const wchar_t *params,
                          const wchar_t *dir,
                          ShowType show_flag,
                          HWND window_handle,
                          const wchar_t *operation) {
        HINSTANCE instance =
                ShellExecuteW(window_handle, operation, file_name, params, dir,
                              static_cast<int32_t>(show_flag));
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

    bool proc::runas_elevated(const char *app_name, const char *cmdline) {
        SHELLEXECUTEINFOA sei = {sizeof(SHELLEXECUTEINFOA)};
        sei.lpVerb = "runas";
        sei.lpFile = app_name;
        sei.lpParameters = cmdline;
        sei.nShow = SW_SHOWNORMAL;
        if (!ShellExecuteExA(&sei)) {
            error_code = GetLastError();
        }
        return true;
    }

    bool proc::runas_elevated(const wchar_t *app_name, const wchar_t *cmdline) {
        SHELLEXECUTEINFOW sei = {sizeof(SHELLEXECUTEINFOW)};
        sei.lpVerb = L"runas";
        sei.lpFile = app_name;
        sei.lpParameters = cmdline;
        sei.nShow = SW_SHOWNORMAL;
        if (!ShellExecuteExW(&sei)) {
            error_code = GetLastError();
        }
        return true;
    }

    bool proc::wait_child(HANDLE child_proc_handle, uint32_t milli_seconds) {
        if (child_proc_handle) {
            const uint32_t ret =
                    WaitForSingleObject(child_proc_handle, milli_seconds);
            if (ret == WAIT_OBJECT_0) {
                return true;
            }
            error_code = GetLastError();
        }
        return false;
    }

    bool proc::resume_child(HANDLE child_thread_handle) {
        if (child_thread_handle) {
            if (ResumeThread(child_thread_handle) ==
                static_cast<uint32_t>(-1)) {
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

    uint32_t proc::thread_id() {
        return GetCurrentThreadId();
    }

    uint32_t proc::proc_id() {
        return GetCurrentProcessId();
    }

    HANDLE
    proc::pid_to_handle(uint32_t pid,
                        ProcAccess access,
                        const bool is_inherit) {
        HANDLE proc_handle = OpenProcess(static_cast<uint32_t>(access),
                                         is_inherit ? TRUE : FALSE, pid);
        if (!proc_handle) {
            error_code = GetLastError();
            return nullptr;
        }
        proc_handle_rwlock.write_lock();
        proc_handles.push_back(proc_handle);
        proc_handle_rwlock.write_unlock();
        return proc_handle;
    }

    uint32_t proc::handle_to_pid(HANDLE proc_handle) {
        const uint32_t pid = GetProcessId(proc_handle);
        if (!pid) {
            error_code = GetLastError();
        }
        return pid;
    }

    bool proc::kill(HANDLE proc_handle, uint32_t exit_code) {
        if (!TerminateProcess(proc_handle, exit_code)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    void proc::exit(uint32_t exit_code) {
        ExitProcess(exit_code);
    }

    uint32_t proc::exit_status(HANDLE proc_handle) {
        unsigned long exit_status = 0;
        if (!GetExitCodeProcess(proc_handle, &exit_status)) {
            error_code = GetLastError();
        }
        return exit_status;
    }

    bool proc::get_startup_info(STARTUPINFOA *info) {
        if (!info) {
            error_code = STATUS_ACCESS_VIOLATION;
            return false;
        }
        GetStartupInfoA(info);
        return true;
    }

    bool proc::get_startup_info(STARTUPINFOW *info) {
        if (!info) {
            error_code = STATUS_ACCESS_VIOLATION;
            return false;
        }
        GetStartupInfoW(info);
        return true;
    }

    void *proc::malloc(HANDLE proc_handle,
                       size_t size,
                       void *addr,
                       AllocateType type,
                       MemoryProtect protect) {
        void *address = VirtualAllocEx(proc_handle, addr, size,
                                       static_cast<uint32_t>(type),
                                       static_cast<uint32_t>(protect));
        if (!address) {
            error_code = GetLastError();
        }
        return address;
    }

    bool
    proc::free(HANDLE proc_handle, void *addr, size_t size, AllocateType type) {
        if (static_cast<uint32_t>(type) & MEM_RELEASE) {
            size = 0;
        }
        if (!VirtualFreeEx(proc_handle, addr, size,
                           static_cast<uint32_t>(type))) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    void *proc::malloc_reserve(HANDLE proc_handle,
                               size_t size,
                               void *addr,
                               AllocateType type,
                               MemoryProtect protect) {
        void *address = VirtualAllocEx(proc_handle, addr, size,
                                       static_cast<uint32_t>(type),
                                       static_cast<uint32_t>(protect));
        if (!address) {
            error_code = GetLastError();
        }
        return address;
    }

    bool proc::free_reserve(HANDLE proc_handle,
                            void *addr,
                            size_t size,
                            AllocateType type) {
        if (!VirtualFreeEx(proc_handle, addr, size,
                           static_cast<uint32_t>(type))) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool proc::mem_guard_attr(HANDLE proc_handle,
                              void *addr,
                              size_t size,
                              MemoryProtect protect,
                              MemoryProtect *old_protect) {
        if (!old_protect) {
            error_code = STATUS_ACCESS_VIOLATION;
            return false;
        }
        auto temp = static_cast<unsigned long>(*old_protect);
        if (!VirtualProtectEx(proc_handle, addr, size,
                              static_cast<uint32_t>(protect), &temp)) {
            error_code = GetLastError();
            *old_protect = static_cast<MemoryProtect>(temp);
            return false;
        }
        *old_protect = static_cast<MemoryProtect>(temp);
        return true;
    }

    bool proc::query_mem(HANDLE proc_handle,
                         const void *address,
                         MEMORY_BASIC_INFORMATION *buffer,
                         const size_t len) {
        if (!VirtualQueryEx(proc_handle, address, buffer, len)) {
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
        if (!ReadProcessMemory(proc_handle, base_addr, buf, size, bytes_read)) {
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
        if (!WriteProcessMemory(proc_handle, base_addr, buf, size,
                                bytes_written)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    std::vector<uint8_t>
    proc::read(HANDLE proc_handle, const void *base_addr, size_t size) {
        std::vector<uint8_t> buffer(size, 0);
        size_t bytes_read = 0;
        if (!ReadProcessMemory(proc_handle, base_addr, buffer.data(),
                               buffer.size(), &bytes_read)) {
            error_code = GetLastError();
            return {};
        }
        buffer.resize(bytes_read);
        buffer.shrink_to_fit();
        return buffer;
    }

    bool proc::write(HANDLE proc_handle,
                     void *base_addr,
                     const std::vector<uint8_t> &buf) {
        if (buf.empty()) {
            return false;
        }
        size_t bytes_write = 0;
        if (!WriteProcessMemory(proc_handle, base_addr, buf.data(), buf.size(),
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

    bool proc::get_env(std::string &env, helper::CodePage code_page) {
        env.clear();
        std::wstring src;
        if (!get_env(src)) {
            return false;
        }
        env = helper::convert::wstr_to_str(src, code_page);
        return true;
    }

    bool proc::get_env(std::wstring &env) {
        env.clear();
        const auto env_block = GetEnvironmentStringsW();
        if (!env_block) {
            return false;
        }
        auto current = env_block;
        while (*current != L'\0') {
            env += current;
            env += L'\n';
            current += wcslen(current) + 1;
        }
        if (!FreeEnvironmentStringsW(env_block)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool proc::get_env(std::vector<std::string> &env,
                       helper::CodePage code_page) {
        env.clear();
        std::vector<std::wstring> src;
        if (!get_env(src)) {
            return false;
        }
        for (const auto &line : src) {
            env.push_back(helper::convert::wstr_to_str(line, code_page));
        }
        return true;
    }

    bool proc::get_env(std::vector<std::wstring> &env) {
        env.clear();
        const auto env_block = GetEnvironmentStringsW();
        if (!env_block) {
            return false;
        }
        auto current = env_block;
        while (*current != L'\0') {
            std::wstring tmp;
            tmp += current;
            tmp += L'\n';
            env.push_back(tmp);
            current += wcslen(current) + 1;
        }
        if (!FreeEnvironmentStringsW(env_block)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool proc::get_env(std::unordered_map<std::string, std::string> &env,
                       helper::CodePage code_page) {
        env.clear();
        std::unordered_map<std::wstring, std::wstring> src;
        if (!get_env(src)) {
            return false;
        }
        for (const auto &[key, value] : src) {
            env.emplace(helper::convert::wstr_to_str(key, code_page),
                        helper::convert::wstr_to_str(value, code_page));
        }
        return true;
    }

    bool proc::get_env(std::unordered_map<std::wstring, std::wstring> &env) {
        env.clear();
        const auto env_block = GetEnvironmentStringsW();
        if (!env_block) {
            return false;
        }
        auto current = env_block;
        while (*current != L'\0') {
            std::wstring tmp;
            tmp += current;
            const size_t pos = tmp.find(L'=');
            auto key = tmp.substr(0, pos);
            auto value = tmp.substr(pos + 1);
            env.emplace(key, value);
            current += wcslen(current) + 1;
        }
        if (!FreeEnvironmentStringsW(env_block)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    std::string proc::get_env_var(const std::string &var_name) {
        std::string var_value;
        uint32_t size =
                GetEnvironmentVariableA(var_name.data(), var_value.data(),
                                        var_value.size());
        if (size <= 0) {
            error_code = GetLastError();
            return {};
        }
        var_value.resize(size);
        size = GetEnvironmentVariableA(var_name.data(), var_value.data(),
                                       var_value.size());
        if (size <= 0) {
            error_code = GetLastError();
            return {};
        }
        while (var_value.back() == '\0') {
            var_value.pop_back();
        }
        return var_value;
    }

    std::wstring proc::get_env_var(const std::wstring &var_name) {
        std::wstring var_value;
        uint32_t size =
                GetEnvironmentVariableW(var_name.data(), var_value.data(),
                                        var_value.size());
        if (size <= 0) {
            error_code = GetLastError();
            return {};
        }
        var_value.resize(size);
        size = GetEnvironmentVariableW(var_name.data(), var_value.data(),
                                       var_value.size());
        if (size <= 0) {
            error_code = GetLastError();
            return {};
        }
        while (var_value.back() == '\0') {
            var_value.pop_back();
        }
        return var_value;
    }

    bool proc::set_env_var(const std::string &var_name,
                           const std::string &var_value) {
        if (!SetEnvironmentVariableA(var_name.data(),
                                     var_name.empty() ? nullptr
                                                      : var_value.data())) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool proc::set_env_var(const std::wstring &var_name,
                           const std::wstring &var_value) {
        if (!SetEnvironmentVariableW(var_name.data(),
                                     var_name.empty() ? nullptr
                                                      : var_value.data())) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    void proc::get_cmdline(std::string &cmdline) {
        cmdline.clear();
        cmdline = GetCommandLineA();
    }

    void proc::get_cmdline(std::wstring &cmdline) {
        cmdline.clear();
        cmdline = GetCommandLineW();
    }

    bool proc::get_cmdline(HANDLE proc_handle,
                           std::string &cmdline,
                           helper::CodePage code_page) {
        std::wstring src;
        if (!get_cmdline(proc_handle, src) || src.empty()) {
            return false;
        }
        cmdline = helper::convert::wstr_to_str(src, code_page);
        return true;
    }

    bool proc::get_cmdline(HANDLE proc_handle, std::wstring &cmdline) {
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
        uint32_t ret_size = 0;
        PROCESS_BASIC_INFORMATION pbi{};
        bool result = false;
        do {
            const NTSTATUS status =
                    nt_query_info_proc(process_handle, ProcessBasicInformation,
                                       &pbi, sizeof(pbi), &ret_size);
            if (!NT_SUCCESS(status)) {
                break;
            }
            const auto peb = std::make_unique<_peb>();
            size_t size = ret_size;
            if (!ReadProcessMemory(process_handle, pbi.PebBaseAddress,
                                   peb.get(), sizeof(_peb), &size)) {
                error_code = GetLastError();
                break;
            }
            const auto block = std::make_unique<_process_parameters>();
            if (!ReadProcessMemory(process_handle, peb->process_parameters,
                                   block.get(), sizeof(_process_parameters),
                                   &size)) {
                error_code = GetLastError();
                break;
            }
            cmdline.resize(MAX_PATH + 1, L'\0');
            if (!ReadProcessMemory(process_handle, block->cmdline,
                                   cmdline.data(), cmdline.size(), &size)) {
                error_code = GetLastError();
                break;
            }
            cmdline.resize(size);
            while (cmdline.back() == L'\0') {
                cmdline.pop_back();
            }
            cmdline.shrink_to_fit();
            result = true;
        } while (false);
        return result;
    }

    bool proc::get_cmdline(uint32_t pid, std::string &cmdline) {
        cmdline.clear();
        HANDLE proc_handle = pid_to_handle(pid);
        if (!proc_handle) {
            return false;
        }
        return get_cmdline(proc_handle, cmdline);
    }

    bool proc::get_cmdline(uint32_t pid, std::wstring &cmdline) {
        cmdline.clear();
        HANDLE proc_handle = pid_to_handle(pid);
        if (!proc_handle) {
            return false;
        }
        return get_cmdline(proc_handle, cmdline);
    }

    bool proc::get_owner(HANDLE proc_handle,
                         std::string &owner,
                         helper::CodePage code_page) {
        std::wstring src;
        if (!get_owner(proc_handle, src) || src.empty()) {
            return false;
        }
        owner = helper::convert::wstr_to_str(src, code_page);
        return true;
    }

    bool proc::get_owner(HANDLE proc_handle, std::wstring &owner) {
        owner.clear();
        HANDLE process_handle = proc_handle ? proc_handle : GetCurrentProcess();
        helper::autoclean<HANDLE> token_handle(nullptr);
        security security;
        bool result = false;
        do {
            if (security.enable_privilege(GetCurrentProcess(),
                                          L"SeTcbPrivilege")) {
                break;
            }
            if (!OpenProcessToken(process_handle, TOKEN_QUERY, token_handle)) {
                error_code = GetLastError();
                break;
            }
            unsigned long size = 0;
            GetTokenInformation(token_handle, TokenUser, nullptr, 0, &size);
            error_code = GetLastError();
            if (error_code != ERROR_INSUFFICIENT_BUFFER) {
                break;
            }
            std::vector<uint8_t> token_user(size, 0);
            if (!GetTokenInformation(token_handle, TokenUser, token_user.data(),
                                     token_user.size(), &size)) {
                error_code = GetLastError();
                break;
            }
            SID_NAME_USE snu;
            wchar_t user[MAX_PATH];
            unsigned long user_size = MAX_PATH;
            unsigned long *user_size_ptr = &user_size;
            wchar_t domain[MAX_PATH];
            unsigned long domain_size = MAX_PATH;
            if (unsigned long *domain_size_ptr = &domain_size;
                !LookupAccountSidW(nullptr,
                                   reinterpret_cast<TOKEN_USER *>(
                                           token_user.data())
                                           ->User.Sid,
                                   user, user_size_ptr, domain, domain_size_ptr,
                                   &snu)) {
                error_code = GetLastError();
                break;
            }
            owner.assign(L"\\\\");
            owner.append(domain);
            owner.append(L"\\");
            owner.append(user);
            if (security.disable_privilege(GetCurrentProcess(),
                                           L"SeTcbPrivilege")) {
                break;
            }
            result = true;
        } while (false);
        return result;
    }

    bool proc::get_owner(uint32_t pid, std::string &owner) {
        HANDLE proc_handle = pid_to_handle(pid);
        if (!proc_handle) {
            return false;
        }
        return get_owner(proc_handle, owner);
    }

    bool proc::get_owner(uint32_t pid, std::wstring &owner) {
        HANDLE proc_handle = pid_to_handle(pid);
        if (!proc_handle) {
            return false;
        }
        return get_owner(proc_handle, owner);
    }

    bool proc::get_image_name(HANDLE proc_handle,
                              std::string &image_name,
                              const bool native_name) {
        HANDLE process_handle = proc_handle ? proc_handle : GetCurrentProcess();
        image_name.resize(MAX_PATH, '\0');
        unsigned long size = MAX_PATH;
        if (!QueryFullProcessImageNameA(process_handle,
                                        native_name ? PROCESS_NAME_NATIVE : 0,
                                        image_name.data(), &size)) {
            error_code = GetLastError();
            return false;
        }
        image_name.resize(size);
        while (image_name.back() == '\0') {
            image_name.pop_back();
        }
        return true;
    }

    bool proc::get_image_name(HANDLE proc_handle,
                              std::wstring &image_name,
                              const bool native_name) {
        HANDLE process_handle = proc_handle ? proc_handle : GetCurrentProcess();
        image_name.resize(MAX_PATH, L'\0');
        unsigned long size = MAX_PATH;
        if (!QueryFullProcessImageNameW(process_handle,
                                        native_name ? PROCESS_NAME_NATIVE : 0,
                                        image_name.data(), &size)) {
            error_code = GetLastError();
            return false;
        }
        image_name.resize(size);
        while (image_name.back() == L'\0') {
            image_name.pop_back();
        }
        return true;
    }

    void *proc::image_base() {
        IMAGE_DOS_HEADER dos_header{};
        IMAGE_NT_HEADERS64 nt_headers64{};
        IMAGE_NT_HEADERS32 nt_headers32{};
        void *result = nullptr;
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
            memcpy(&nt_headers64, base + dos_header.e_lfanew,
                   sizeof(nt_headers64));
            if (nt_headers64.Signature != IMAGE_NT_SIGNATURE) {
                break;
            }
            if (nt_headers64.FileHeader.Machine == IMAGE_FILE_MACHINE_AMD64 ||
                nt_headers64.FileHeader.Machine == IMAGE_FILE_MACHINE_ARM64) {
                result = reinterpret_cast<void *>(
                        nt_headers64.OptionalHeader.ImageBase);
            } else {
                memcpy(&nt_headers32, base + dos_header.e_lfanew,
                       sizeof(nt_headers32));
                if (nt_headers32.Signature != IMAGE_NT_SIGNATURE) {
                    break;
                }
                result = reinterpret_cast<void *>(static_cast<int64_t>(
                        nt_headers32.OptionalHeader.ImageBase));
            }
        } while (false);
        return result;
    }

    void *proc::image_base(HANDLE proc_handle) {
        HANDLE process_handle = proc_handle ? proc_handle : GetCurrentProcess();
        PROCESS_BASIC_INFORMATION pbi;
        const NTSTATUS status =
                nt_query_info_proc(process_handle, ProcessBasicInformation,
                                   &pbi, sizeof(PROCESS_BASIC_INFORMATION),
                                   nullptr);
        if (!NT_SUCCESS(status)) {
            return nullptr;
        }
        void *baseAddr = pbi.PebBaseAddress->Reserved3[1];
        return baseAddr;
    }

    void *proc::image_base(const uint32_t pid) {
        return image_base(pid_to_handle(pid));
    }

    uint32_t proc::get_priority(HANDLE proc_handle) {
        const uint32_t priority = GetPriorityClass(proc_handle);
        if (!priority) {
            error_code = GetLastError();
        }
        return priority;
    }

    bool proc::set_priority(HANDLE proc_handle, uint32_t priority) {
        if (!SetPriorityClass(proc_handle, priority)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    int32_t proc::get_thread_priority(HANDLE thread_handle) {
        const int32_t priority = GetThreadPriority(thread_handle);
        if (priority == THREAD_PRIORITY_ERROR_RETURN) {
            error_code = GetLastError();
        }
        return priority;
    }

    bool proc::set_thread_priority(HANDLE thread_handle, int32_t priority) {
        if (!SetThreadPriority(thread_handle, priority)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    uint32_t proc::handle_count(HANDLE proc_handle) {
        unsigned long count = 0;
        if (!GetProcessHandleCount(proc_handle, &count)) {
            error_code = GetLastError();
        }
        return count;
    }

    uint32_t proc::processor_num() {
        return GetCurrentProcessorNumber();
    }

    bool proc::get_info(HANDLE proc_handle,
                        PROCESS_INFORMATION_CLASS proc_info_class,
                        void *proc_info,
                        uint32_t proc_info_size) {
        if (!GetProcessInformation(proc_handle, proc_info_class, proc_info,
                                   proc_info_size)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool proc::set_info(HANDLE proc_handle,
                        PROCESS_INFORMATION_CLASS proc_info_class,
                        void *proc_info,
                        uint32_t proc_info_size) {
        if (!SetProcessInformation(proc_handle, proc_info_class, proc_info,
                                   proc_info_size)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool proc::get_mem_info(HANDLE proc_handle,
                            PPROCESS_MEMORY_COUNTERS mem_counters,
                            const uint32_t mem_counters_size) {
        if (!GetProcessMemoryInfo(proc_handle, mem_counters,
                                  mem_counters_size)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool proc::get_module_info(HANDLE proc_handle,
                               HMODULE module_handle,
                               MODULEINFO *mod_info,
                               uint32_t mod_info_size) {
        if (!GetModuleInformation(proc_handle, module_handle, mod_info,
                                  mod_info_size)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool proc::logical_processor_info(SYSTEM_LOGICAL_PROCESSOR_INFORMATION *buf,
                                      uint32_t *real_size) {
        if (!real_size) {
            error_code = STATUS_ACCESS_VIOLATION;
            return false;
        }
        unsigned long temp = *real_size;
        if (!GetLogicalProcessorInformation(buf, &temp)) {
            error_code = GetLastError();
            *real_size = temp;
            return false;
        }
        *real_size = temp;
        return true;
    }

    bool proc::get_affinity_mask(HANDLE proc_handle,
                                 uintptr_t *proc_affinity_mask,
                                 uintptr_t *system_affinity_mask) {
        if (!GetProcessAffinityMask(proc_handle, proc_affinity_mask,
                                    system_affinity_mask)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool proc::set_affinity_mask(HANDLE proc_handle,
                                 const uintptr_t proc_affinity_mask) {
        if (!SetProcessAffinityMask(proc_handle, proc_affinity_mask)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool proc::get_group_affinity(HANDLE proc_handle,
                                  uint16_t *group_count,
                                  uint16_t *group_array) {
        if (!GetProcessGroupAffinity(proc_handle, group_count, group_array)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool proc::io_counters(HANDLE proc_handle, IO_COUNTERS *io_counters) {
        if (!GetProcessIoCounters(proc_handle, io_counters)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool
    proc::get_mitigation_policy(HANDLE proc_handle,
                                PROCESS_MITIGATION_POLICY mitigation_policy,
                                void *buffer,
                                const size_t len) {
        if (!GetProcessMitigationPolicy(proc_handle, mitigation_policy, buffer,
                                        len)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool
    proc::set_mitigation_policy(PROCESS_MITIGATION_POLICY mitigation_policy,
                                void *buffer,
                                const size_t len) {
        if (!SetProcessMitigationPolicy(mitigation_policy, buffer, len)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool proc::get_priority_boost(HANDLE proc_handle) {
        int32_t is_disable_priority_boost = 0;
        if (!GetProcessPriorityBoost(proc_handle, &is_disable_priority_boost)) {
            error_code = GetLastError();
        }
        return is_disable_priority_boost;
    }

    bool proc::set_priority_boost(HANDLE proc_handle,
                                  bool is_disable_priority_boost) {
        if (!SetProcessPriorityBoost(proc_handle,
                                     is_disable_priority_boost ? TRUE
                                                               : FALSE)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool proc::get_shutdown_params(uint32_t *level, bool *show_retry_dialog) {
        if (!level || !show_retry_dialog) {
            error_code = STATUS_ACCESS_VIOLATION;
            return false;
        }
        unsigned long temp = *level;
        unsigned long flag = *show_retry_dialog;
        if (!GetProcessShutdownParameters(&temp, &flag)) {
            error_code = GetLastError();
            *show_retry_dialog = flag == SHUTDOWN_NORETRY;
            *level = temp;
            return false;
        }
        *show_retry_dialog = flag == SHUTDOWN_NORETRY;
        *level = temp;
        return true;
    }

    bool proc::set_shutdown_params(uint32_t level, bool show_retry_dialog) {
        if (const uint32_t flag = show_retry_dialog ? SHUTDOWN_NORETRY : 0;
            !SetProcessShutdownParameters(level, flag)) {
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
        if (!GetProcessTimes(proc_handle, creation_time, exit_time, kernel_time,
                             user_time)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    uint32_t proc::system_version(const uint32_t pid) {
        const uint32_t version = GetProcessVersion(pid);
        if (!version) {
            error_code = GetLastError();
        }
        return version;
    }

    bool proc::get_working_set_size(HANDLE proc_handle,
                                    SIZE_T *min_working_set_size,
                                    SIZE_T *max_working_set_size) {
        if (GetProcessWorkingSetSize(proc_handle, min_working_set_size,
                                     max_working_set_size)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool proc::set_working_set_size(HANDLE proc_handle,
                                    size_t min_working_set_size,
                                    size_t max_working_set_size) {
        if (SetProcessWorkingSetSize(proc_handle, min_working_set_size,
                                     max_working_set_size)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool proc::get_processor_system_cycle_time(
            uint16_t group,
            SYSTEM_PROCESSOR_CYCLE_TIME_INFORMATION *buffer,
            uint32_t *real_size) {
        if (!real_size) {
            error_code = STATUS_ACCESS_VIOLATION;
            return false;
        }
        unsigned long temp = *real_size;
        if (!GetProcessorSystemCycleTime(group, buffer, &temp)) {
            error_code = GetLastError();
            *real_size = temp;
            return false;
        }
        *real_size = temp;
        return true;
    }

    bool proc::is_microsoft_store_app(HANDLE proc_handle) {
        if (!IsImmersiveProcess(proc_handle)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool proc::is_exe_search_path(const char *exe_name) {
        return NeedCurrentDirectoryForExePathA(exe_name);
    }

    bool proc::is_exe_search_path(const wchar_t *exe_name) {
        return NeedCurrentDirectoryForExePathW(exe_name);
    }

    bool proc::get_affinity_update_mode(HANDLE proc_handle, bool *auto_update) {
        if (!auto_update) {
            error_code = STATUS_ACCESS_VIOLATION;
            return false;
        }
        unsigned long flag = 0;
        if (!QueryProcessAffinityUpdateMode(proc_handle, &flag)) {
            error_code = GetLastError();
            *auto_update = flag;
            return false;
        }
        *auto_update = flag;
        return true;
    }

    bool proc::set_affinity_update_mode(HANDLE proc_handle, bool auto_update) {
        if (const uint32_t flag =
                    auto_update ? PROCESS_AFFINITY_ENABLE_AUTO_UPDATE : 0;
            !SetProcessAffinityUpdateMode(proc_handle, flag)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool proc::all_thread_cycle_time(HANDLE proc_handle, uint64_t *cycle_time) {
        if (!QueryProcessCycleTime(proc_handle, cycle_time)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool proc::set_restriction_exemption(bool is_enable_exemption) {
        if (!SetProcessRestrictionExemption(is_enable_exemption ? TRUE
                                                                : FALSE)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    uint32_t proc::err_code() const {
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
} // namespace YanLib::sys
