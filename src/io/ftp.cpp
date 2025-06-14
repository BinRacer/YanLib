/* clang-format off */
/*
 * @file ftp.cpp
 * @date 2025-04-06
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
#include "ftp.h"
#include "fs.h"

namespace YanLib::io {
    ftp::ftp(const std::string &input_url, helper::CodePage code_page) {
        uc.dwStructSize = sizeof(uc);
        uc.dwSchemeLength = _countof(scheme) - 1;
        uc.dwHostNameLength = _countof(_hostname) - 1;
        uc.dwUserNameLength = _countof(_username) - 1;
        uc.dwPasswordLength = _countof(_password) - 1;
        uc.dwUrlPathLength = _countof(urlpath) - 1;
        uc.dwExtraInfoLength = _countof(extra_info) - 1;
        uc.lpszScheme = scheme;
        uc.lpszHostName = _hostname;
        uc.lpszUserName = _username;
        uc.lpszPassword = _password;
        uc.lpszUrlPath = urlpath;
        uc.lpszExtraInfo = extra_info;
        url = helper::convert::str_to_wstr(input_url, code_page);
    }

    ftp::ftp(const std::wstring &input_url) {
        uc.dwStructSize = sizeof(uc);
        uc.dwSchemeLength = _countof(scheme) - 1;
        uc.dwHostNameLength = _countof(_hostname) - 1;
        uc.dwUserNameLength = _countof(_username) - 1;
        uc.dwPasswordLength = _countof(_password) - 1;
        uc.dwUrlPathLength = _countof(urlpath) - 1;
        uc.dwExtraInfoLength = _countof(extra_info) - 1;
        uc.lpszScheme = scheme;
        uc.lpszHostName = _hostname;
        uc.lpszUserName = _username;
        uc.lpszPassword = _password;
        uc.lpszUrlPath = urlpath;
        uc.lpszExtraInfo = extra_info;
        url = input_url;
    }

    ftp::ftp(const std::string &ip,
             const uint16_t &port,
             const std::string &username,
             const std::string &password,
             helper::CodePage code_page) {
        uc.dwStructSize = sizeof(uc);
        uc.dwSchemeLength = _countof(scheme) - 1;
        uc.dwHostNameLength = _countof(_hostname) - 1;
        uc.dwUserNameLength = _countof(_username) - 1;
        uc.dwPasswordLength = _countof(_password) - 1;
        uc.dwUrlPathLength = _countof(urlpath) - 1;
        uc.dwExtraInfoLength = _countof(extra_info) - 1;
        uc.lpszScheme = scheme;
        uc.lpszHostName = _hostname;
        uc.lpszUserName = _username;
        uc.lpszPassword = _password;
        uc.lpszUrlPath = urlpath;
        uc.lpszExtraInfo = extra_info;
        std::wstring _url;
        _url.append(L"ftp://");
        _url.append(helper::convert::str_to_wstr(username, code_page));
        _url.append(L":");
        _url.append(helper::convert::str_to_wstr(password, code_page));
        _url.append(L"@");
        _url.append(helper::convert::str_to_wstr(ip, code_page));
        _url.append(L":");
        _url.append(std::to_wstring(port));
        _url.append(L"/");
        url = _url;
    }

    ftp::ftp(const std::wstring &ip,
             const uint16_t &port,
             const std::wstring &username,
             const std::wstring &password) {
        uc.dwStructSize = sizeof(uc);
        uc.dwSchemeLength = _countof(scheme) - 1;
        uc.dwHostNameLength = _countof(_hostname) - 1;
        uc.dwUserNameLength = _countof(_username) - 1;
        uc.dwPasswordLength = _countof(_password) - 1;
        uc.dwUrlPathLength = _countof(urlpath) - 1;
        uc.dwExtraInfoLength = _countof(extra_info) - 1;
        uc.lpszScheme = scheme;
        uc.lpszHostName = _hostname;
        uc.lpszUserName = _username;
        uc.lpszPassword = _password;
        uc.lpszUrlPath = urlpath;
        uc.lpszExtraInfo = extra_info;
        std::wstring _url;
        _url.append(L"ftp://");
        _url.append(username);
        _url.append(L":");
        _url.append(password);
        _url.append(L"@");
        _url.append(ip);
        _url.append(L":");
        _url.append(std::to_wstring(port));
        _url.append(L"/");
        url = _url;
    }

    ftp::~ftp() {
        for (auto &file_handle : file_handles) {
            if (file_handle) {
                InternetCloseHandle(file_handle);
                file_handle = nullptr;
            }
        }
        file_handles.clear();
        if (session_read_handle) {
            InternetCloseHandle(session_read_handle);
            session_read_handle = nullptr;
        }
        if (session_upload_handle) {
            InternetCloseHandle(session_upload_handle);
            session_upload_handle = nullptr;
        }
        if (internet_handle) {
            InternetCloseHandle(internet_handle);
            internet_handle = nullptr;
        }
    }

    bool ftp::url_crack(const uint32_t flag) {
        if (!InternetCrackUrlW(url.data(), url.size(), flag, &uc)) {
            error_code = GetLastError();
            return false;
        }
        _port = uc.nPort;
        return true;
    }

    bool ftp::open(const char *agent_name,
                   const uint32_t access_type,
                   const char *proxy,
                   const char *proxy_bypass,
                   const uint32_t flag) {
        internet_handle = InternetOpenA(agent_name, access_type, proxy,
                                        proxy_bypass, flag);
        if (!internet_handle) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool ftp::open(const wchar_t *agent_name,
                   const uint32_t access_type,
                   const wchar_t *proxy,
                   const wchar_t *proxy_bypass,
                   const uint32_t flag) {
        internet_handle = InternetOpenW(agent_name, access_type, proxy,
                                        proxy_bypass, flag);
        if (!internet_handle) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool ftp::connect(const uint32_t service,
                      const uint32_t flag,
                      const uintptr_t context) {
        session_read_handle =
                InternetConnectW(internet_handle, _hostname, _port,
                                 wcslen(_username) == 0 ? nullptr : _username,
                                 wcslen(_password) == 0 ? nullptr : _password,
                                 service, flag, context);
        if (!session_read_handle) {
            error_code = GetLastError();
            return false;
        }
        session_upload_handle =
                InternetConnectW(internet_handle, _hostname, _port,
                                 wcslen(_username) == 0 ? nullptr : _username,
                                 wcslen(_password) == 0 ? nullptr : _password,
                                 service, flag, context);
        if (!session_upload_handle) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    HINTERNET ftp::open_file(const char *file_name,
                             const uint32_t access,
                             const uint32_t flag,
                             const uintptr_t context) {
        HINTERNET file_handle = FtpOpenFileA(session_read_handle, file_name,
                                             access, flag, context);
        if (!file_handle) {
            error_code = GetLastError();
            return nullptr;
        }
        rwlock.write_lock();
        file_handles.push_back(file_handle);
        rwlock.write_unlock();
        return file_handle;
    }

    HINTERNET ftp::open_file(const wchar_t *file_name,
                             const uint32_t access,
                             const uint32_t flag,
                             const uintptr_t context) {
        HINTERNET file_handle = FtpOpenFileW(session_read_handle, file_name,
                                             access, flag, context);
        if (!file_handle) {
            error_code = GetLastError();
            return nullptr;
        }
        rwlock.write_lock();
        file_handles.push_back(file_handle);
        rwlock.write_unlock();
        return file_handle;
    }

    HINTERNET ftp::create_file(const char *file_name,
                               const uint32_t access,
                               const uint32_t flag,
                               const uintptr_t context) {
        HINTERNET file_handle = FtpOpenFileA(session_upload_handle, file_name,
                                             access, flag, context);
        if (!file_handle) {
            error_code = GetLastError();
            return nullptr;
        }
        rwlock.write_lock();
        file_handles.push_back(file_handle);
        rwlock.write_unlock();
        return file_handle;
    }

    HINTERNET ftp::create_file(const wchar_t *file_name,
                               const uint32_t access,
                               const uint32_t flag,
                               const uintptr_t context) {
        HINTERNET file_handle = FtpOpenFileW(session_upload_handle, file_name,
                                             access, flag, context);
        if (!file_handle) {
            error_code = GetLastError();
            return nullptr;
        }
        rwlock.write_lock();
        file_handles.push_back(file_handle);
        rwlock.write_unlock();
        return file_handle;
    }

    bool ftp::read(HINTERNET file_handle,
                   void *buf,
                   uint32_t size,
                   uint32_t *ret_size) {
        if (!ret_size) {
            error_code = STATUS_ACCESS_VIOLATION;
            return false;
        }
        unsigned long temp = *ret_size;
        if (!InternetReadFile(file_handle, buf, size, &temp)) {
            error_code = GetLastError();
            *ret_size = temp;
            return false;
        }
        *ret_size = temp;
        return true;
    }

    std::vector<uint8_t> ftp::read_bytes(HINTERNET file_handle,
                                         int32_t buffer_size) {
        if (buffer_size < 0) {
            buffer_size = 1;
        }
        std::vector<uint8_t> raw_data(buffer_size, '\0');
        unsigned long bytes_read = 0;
        if (InternetReadFile(file_handle, raw_data.data(), buffer_size,
                             &bytes_read) &&
            bytes_read > 0) {
            raw_data.resize(bytes_read);
            raw_data.shrink_to_fit();
            return raw_data;
        }
        error_code = GetLastError();
        return {};
    }

    bool ftp::write(HINTERNET file_handle,
                    const void *buf,
                    uint32_t size,
                    uint32_t *ret_size) {
        if (!ret_size) {
            error_code = STATUS_ACCESS_VIOLATION;
            return false;
        }
        unsigned long temp = *ret_size;
        if (!InternetWriteFile(file_handle, buf, size, &temp)) {
            error_code = GetLastError();
            *ret_size = temp;
            return false;
        }
        *ret_size = temp;
        return true;
    }

    uint32_t ftp::write_bytes(HINTERNET file_handle,
                              const std::vector<uint8_t> &data) {
        unsigned long bytes_read = 0;
        if (InternetWriteFile(file_handle, data.data(), data.size(),
                              &bytes_read) &&
            bytes_read > 0) {
            return bytes_read;
        }
        error_code = GetLastError();
        return 0;
    }

    int64_t ftp::size(HINTERNET file_handle) {
        uint32_t low = 0;
        unsigned long high = 0;

        low = FtpGetFileSize(file_handle, &high);
        if (low == INVALID_FILE_SIZE) {
            error_code = GetLastError();
            return 0;
        }
        return (static_cast<int64_t>(high) << 32) | low;
    }

    bool ftp::pwd(std::string &path) {
        path.resize(MAX_PATH + 1, '\0');
        unsigned long size = MAX_PATH;
        if (!FtpGetCurrentDirectoryA(session_read_handle, path.data(), &size)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool ftp::pwd(std::wstring &path) {
        path.resize(MAX_PATH + 1, L'\0');
        unsigned long size = MAX_PATH;
        if (!FtpGetCurrentDirectoryW(session_read_handle, path.data(), &size)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool ftp::cd(const char *dir) {
        if (!FtpSetCurrentDirectoryA(session_read_handle, dir)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool ftp::cd(const wchar_t *dir) {
        if (!FtpSetCurrentDirectoryW(session_read_handle, dir)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool ftp::ls(std::vector<std::string> &files,
                 std::vector<std::string> &dirs) {
        std::string current_dir;
        if (!pwd(current_dir) || current_dir.empty()) {
            return false;
        }
        if (current_dir.back() == '/' || current_dir.back() == '\\') {
            current_dir.append("*.*");
        } else {
            if (current_dir.find('\\') != std::wstring::npos) {
                current_dir.append("\\*.*");
            } else {
                current_dir.append("/*.*");
            }
        }
        WIN32_FIND_DATAA file_data;
        HINTERNET find_handle =
                FtpFindFirstFileA(session_read_handle, current_dir.data(),
                                  &file_data, INTERNET_FLAG_RELOAD, 0);
        if (!find_handle) {
            error_code = GetLastError();
            return false;
        }
        do {
            if (strcmp(file_data.cFileName, ".") != 0 &&
                strcmp(file_data.cFileName, "..") != 0) {
                if (file_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
                    dirs.emplace_back(file_data.cFileName);
                } else {
                    files.emplace_back(file_data.cFileName);
                }
            }
        } while (InternetFindNextFileA(find_handle, &file_data));
        InternetCloseHandle(find_handle);
        return true;
    }

    bool ftp::ls(std::vector<std::wstring> &files,
                 std::vector<std::wstring> &dirs) {
        std::wstring current_dir;
        if (!pwd(current_dir) || current_dir.empty()) {
            return false;
        }
        if (current_dir.back() == L'/' || current_dir.back() == L'\\') {
            current_dir.append(L"*.*");
        } else {
            if (current_dir.find(L'\\') != std::wstring::npos) {
                current_dir.append(L"\\*.*");
            } else {
                current_dir.append(L"/*.*");
            }
        }
        WIN32_FIND_DATAW file_data;
        HINTERNET find_handle =
                FtpFindFirstFileW(session_read_handle, current_dir.data(),
                                  &file_data, INTERNET_FLAG_RELOAD, 0);
        if (!find_handle) {
            error_code = GetLastError();
            return false;
        }
        do {
            if (wcscmp(file_data.cFileName, L".") != 0 &&
                wcscmp(file_data.cFileName, L"..") != 0) {
                if (file_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
                    dirs.emplace_back(file_data.cFileName);
                } else {
                    files.emplace_back(file_data.cFileName);
                }
            }
        } while (InternetFindNextFileW(find_handle, &file_data));
        InternetCloseHandle(find_handle);
        return true;
    }

    bool ftp::ls_full_path(std::vector<std::string> &files,
                           std::vector<std::string> &dirs) {
        std::string current_dir;
        if (!pwd(current_dir) || current_dir.empty()) {
            return false;
        }
        const std::string base_path = current_dir;
        std::string slash;
        if (current_dir.back() == '/') {
            current_dir.append("*.*");
            slash = "";
        } else if (current_dir.back() == '\\') {
            current_dir.append("*.*");
            slash = "";
        } else {
            if (current_dir.find('\\') != std::wstring::npos) {
                current_dir.append("\\*.*");
                slash = "\\";
            } else {
                current_dir.append("/*.*");
                slash = "/";
            }
        }
        WIN32_FIND_DATAA find_file_data;
        HINTERNET find_handle =
                FtpFindFirstFileA(session_read_handle, current_dir.data(),
                                  &find_file_data, INTERNET_FLAG_RELOAD, 0);
        if (!find_handle) {
            error_code = GetLastError();
            return false;
        }
        do {
            if (strcmp(find_file_data.cFileName, ".") != 0 &&
                strcmp(find_file_data.cFileName, "..") != 0) {
                if (find_file_data.dwFileAttributes &
                    FILE_ATTRIBUTE_DIRECTORY) {
                    dirs.push_back(base_path + slash +
                                   find_file_data.cFileName);
                } else {
                    files.push_back(base_path + slash +
                                    find_file_data.cFileName);
                }
            }
        } while (InternetFindNextFileA(find_handle, &find_file_data));
        InternetCloseHandle(find_handle);
        return true;
    }

    bool ftp::ls_full_path(std::vector<std::wstring> &files,
                           std::vector<std::wstring> &dirs) {
        std::wstring current_dir;
        if (!pwd(current_dir) || current_dir.empty()) {
            return false;
        }
        const std::wstring base_path = current_dir;
        std::wstring slash;
        if (current_dir.back() == L'/') {
            current_dir.append(L"*.*");
            slash = L"";
        } else if (current_dir.back() == L'\\') {
            current_dir.append(L"*.*");
            slash = L"";
        } else {
            if (current_dir.find(L'\\') != std::wstring::npos) {
                current_dir.append(L"\\*.*");
                slash = L"\\";
            } else {
                current_dir.append(L"/*.*");
                slash = L"/";
            }
        }
        WIN32_FIND_DATAW find_file_data;
        HINTERNET find_handle =
                FtpFindFirstFileW(session_read_handle, current_dir.data(),
                                  &find_file_data, INTERNET_FLAG_RELOAD, 0);
        if (!find_handle) {
            error_code = GetLastError();
            return false;
        }
        do {
            if (wcscmp(find_file_data.cFileName, L".") != 0 &&
                wcscmp(find_file_data.cFileName, L"..") != 0) {
                if (find_file_data.dwFileAttributes &
                    FILE_ATTRIBUTE_DIRECTORY) {
                    dirs.push_back(base_path + slash +
                                   find_file_data.cFileName);
                } else {
                    files.push_back(base_path + slash +
                                    find_file_data.cFileName);
                }
            }
        } while (InternetFindNextFileW(find_handle, &find_file_data));
        InternetCloseHandle(find_handle);
        return true;
    }

    bool ftp::mkdir(const char *dir) {
        if (!FtpCreateDirectoryA(session_read_handle, dir)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool ftp::mkdir(const wchar_t *dir) {
        if (!FtpCreateDirectoryW(session_read_handle, dir)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool ftp::rmdir(const char *dir) {
        if (!FtpRemoveDirectoryA(session_read_handle, dir)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool ftp::rmdir(const wchar_t *dir) {
        if (!FtpRemoveDirectoryW(session_read_handle, dir)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool ftp::rm(const char *file_name) {
        if (!FtpDeleteFileA(session_read_handle, file_name)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool ftp::rm(const wchar_t *file_name) {
        if (!FtpDeleteFileW(session_read_handle, file_name)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool ftp::rename(const char *existing_name, const char *new_name) {
        if (!FtpRenameFileA(session_read_handle, existing_name, new_name)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool ftp::rename(const wchar_t *existing_name, const wchar_t *new_name) {
        if (!FtpRenameFileW(session_read_handle, existing_name, new_name)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    std::vector<uint8_t> ftp::command(const char *command) {
        HINTERNET cmd_handle = nullptr;
        if (!FtpCommandA(session_read_handle, TRUE, FTP_TRANSFER_TYPE_BINARY,
                         command, 0, &cmd_handle)) {
            error_code = GetLastError();
            if (cmd_handle) {
                InternetCloseHandle(cmd_handle);
            }
            return {};
        }
        std::vector<uint8_t> result;
        unsigned long bytes_read = 0;
        std::vector<uint8_t> buffer(1024, '\0');
        while (InternetReadFile(cmd_handle, buffer.data(), buffer.size(),
                                &bytes_read) &&
               bytes_read > 0) {
            result.insert(result.end(), buffer.data(),
                          buffer.data() + bytes_read);
        }
        result.shrink_to_fit();
        return result;
    }

    std::vector<uint8_t> ftp::command(const wchar_t *command) {
        HINTERNET cmd_handle = nullptr;
        if (!FtpCommandW(session_read_handle, TRUE, FTP_TRANSFER_TYPE_BINARY,
                         command, 0, &cmd_handle)) {
            error_code = GetLastError();
            if (cmd_handle) {
                InternetCloseHandle(cmd_handle);
            }
            return {};
        }
        std::vector<uint8_t> result;
        unsigned long bytes_read = 0;
        std::vector<uint8_t> buffer(1024, '\0');
        while (InternetReadFile(cmd_handle, buffer.data(), buffer.size(),
                                &bytes_read) &&
               bytes_read > 0) {
            result.insert(result.end(), buffer.data(),
                          buffer.data() + bytes_read);
        }
        result.shrink_to_fit();
        return result;
    }

    bool ftp::download(const char *remote_file,
                       const char *new_file,
                       const bool is_fail_if_exists,
                       const uint32_t flags_and_attrs,
                       const uint32_t flag,
                       const uintptr_t context) {
        if (!FtpGetFileA(session_read_handle, remote_file, new_file,
                         is_fail_if_exists ? TRUE : FALSE, flags_and_attrs,
                         flag, context)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool ftp::download(const wchar_t *remote_file,
                       const wchar_t *new_file,
                       const bool is_fail_if_exists,
                       const uint32_t flags_and_attrs,
                       const uint32_t flag,
                       const uintptr_t context) {
        if (!FtpGetFileW(session_read_handle, remote_file, new_file,
                         is_fail_if_exists ? TRUE : FALSE, flags_and_attrs,
                         flag, context)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool ftp::upload(const char *local_file,
                     const char *new_remote_file,
                     const uint32_t flag,
                     const uintptr_t context) {
        if (!FtpPutFileA(session_upload_handle, local_file, new_remote_file,
                         flag, context)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool ftp::upload(const wchar_t *local_file,
                     const wchar_t *new_remote_file,
                     const uint32_t flag,
                     const uintptr_t context) {
        if (!FtpPutFileW(session_upload_handle, local_file, new_remote_file,
                         flag, context)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    uint32_t ftp::download2(HINTERNET remote_file, const char *local_file) {
        uint32_t error = 0;
        fs file(local_file, DesiredAccess::Read | DesiredAccess::Write,
                ShareMode::Read | ShareMode::Write, nullptr,
                CreationDisposition::CreateAlways);
        if (!file.is_ok()) {
            return file.err_code();
        }
        constexpr uint32_t buf_size = 4096;
        std::vector<uint8_t> buf(buf_size, '\0');
        uint32_t bytes_read = 0;
        uint32_t bytes_written = 0;
        do {
            if (!read(remote_file, buf.data(), buf_size, &bytes_read)) {
                error = err_code();
                break;
            }
            if (bytes_read <= 0)
                break;
            if (!file.write(buf.data(), bytes_read, &bytes_written)) {
                error = file.err_code();
                break;
            }
        } while (bytes_read > 0 && bytes_written > 0);
        return error;
    }

    uint32_t ftp::download2(HINTERNET remote_file, const wchar_t *local_file) {
        uint32_t error = 0;
        fs file(local_file, DesiredAccess::Read | DesiredAccess::Write,
                ShareMode::Read | ShareMode::Write, nullptr,
                CreationDisposition::CreateAlways);
        if (!file.is_ok()) {
            return file.err_code();
        }
        constexpr uint32_t buf_size = 4096;
        std::vector<uint8_t> buf(buf_size, '\0');
        uint32_t bytes_read = 0;
        uint32_t bytes_written = 0;
        do {
            if (!read(remote_file, buf.data(), buf_size, &bytes_read)) {
                error = err_code();
                break;
            }
            if (bytes_read <= 0)
                break;
            if (!file.write(buf.data(), bytes_read, &bytes_written)) {
                error = file.err_code();
                break;
            }
        } while (bytes_read > 0 && bytes_written > 0);
        return error;
    }

    uint32_t ftp::upload2(HINTERNET remote_file, const char *local_file) {
        uint32_t error = 0;
        fs file(local_file);
        if (!file.is_ok()) {
            return file.err_code();
        }
        constexpr uint32_t buf_size = 4096;
        std::vector<uint8_t> buf(buf_size, '\0');
        uint32_t bytes_read = 0;
        uint32_t bytes_written = 0;
        do {
            if (!file.read(buf.data(), buf_size, &bytes_read)) {
                error = file.err_code();
                break;
            }
            if (bytes_read <= 0)
                break;
            if (!write(remote_file, buf.data(), bytes_read, &bytes_written)) {
                error = err_code();
                break;
            }
        } while (bytes_read > 0 && bytes_written > 0);
        return error;
    }

    uint32_t ftp::upload2(HINTERNET remote_file, const wchar_t *local_file) {
        uint32_t error = 0;
        fs file(local_file);
        if (!file.is_ok()) {
            return file.err_code();
        }
        constexpr uint32_t buf_size = 4096;
        std::vector<uint8_t> buf(buf_size, '\0');
        uint32_t bytes_read = 0;
        uint32_t bytes_written = 0;
        do {
            if (!file.read(buf.data(), buf_size, &bytes_read)) {
                error = file.err_code();
                break;
            }
            if (bytes_read <= 0)
                break;
            if (!write(remote_file, buf.data(), bytes_read, &bytes_written)) {
                error = err_code();
                break;
            }
        } while (bytes_read > 0 && bytes_written > 0);
        return error;
    }

    uint32_t ftp::err_code() const {
        return error_code;
    }

    std::string ftp::err_string() const {
        std::string result = helper::convert::err_string(error_code);
        return result;
    }

    std::wstring ftp::err_wstring() const {
        std::wstring result = helper::convert::err_wstring(error_code);
        return result;
    }
} // namespace YanLib::io
