//
// Created by forkernel on 2025/4/6.
//

#include "ftp.h"
#include "helper/convert.h"
#include "fs.h"

namespace YanLib::io {
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
        std::for_each(files.rbegin(), files.rend(),
                      [](auto &file) {
                          InternetCloseHandle(file);
                          file = nullptr;
                      });
        files.clear();
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

    bool ftp::url_crack(DWORD flag) {
        if (!InternetCrackUrlW(
            url.data(),
            url.size(),
            flag,
            &uc)) {
            error_code = GetLastError();
            return false;
        }
        _port = uc.nPort;
        return true;
    }

    bool ftp::open(const wchar_t *agent_name,
                   DWORD access_type,
                   const wchar_t *proxy,
                   const wchar_t *proxy_bypass,
                   DWORD flag) {
        internet_handle = InternetOpenW(agent_name,
                                        access_type,
                                        proxy,
                                        proxy_bypass,
                                        flag);
        if (!internet_handle) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool ftp::connect(DWORD service,
                      DWORD flag,
                      DWORD_PTR context) {
        session_read_handle = InternetConnectW(internet_handle,
                                               _hostname,
                                               _port,
                                               wcslen(_username) == 0 ? nullptr : _username,
                                               wcslen(_password) == 0 ? nullptr : _password,
                                               service,
                                               flag,
                                               context);
        if (!session_read_handle) {
            error_code = GetLastError();
            return false;
        }
        session_upload_handle = InternetConnectW(internet_handle,
                                                 _hostname,
                                                 _port,
                                                 wcslen(_username) == 0 ? nullptr : _username,
                                                 wcslen(_password) == 0 ? nullptr : _password,
                                                 service,
                                                 flag,
                                                 context);
        if (!session_upload_handle) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    HINTERNET ftp::open_file(const wchar_t *file_name,
                             DWORD access,
                             DWORD flag,
                             DWORD_PTR context) {
        HINTERNET file_handle = FtpOpenFileW(session_read_handle,
                                             file_name,
                                             access,
                                             flag,
                                             context);
        if (!file_handle) {
            error_code = GetLastError();
        }
        return file_handle;
    }

    HINTERNET ftp::create_file(const wchar_t *file_name,
                               DWORD access,
                               DWORD flag,
                               DWORD_PTR context) {
        HINTERNET file_handle = FtpOpenFileW(session_upload_handle,
                                             file_name,
                                             access,
                                             flag,
                                             context);
        if (!file_handle) {
            error_code = GetLastError();
        }
        return file_handle;
    }

    bool ftp::read(HINTERNET file_handle,
                   void* buf,
                   DWORD size,
                   LPDWORD ret_size) {
        if (!InternetReadFile(file_handle,
                              buf,
                              size,
                              ret_size)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    std::vector<uint8_t> ftp::read_bytes(HINTERNET file_handle,
                                         int32_t buffer_size) {
        if (buffer_size < 1024) {
            buffer_size = 1024;
        }
        std::vector<uint8_t> raw_data(buffer_size, '\0');
        DWORD bytes_read = 0;
        if (InternetReadFile(file_handle,
                             raw_data.data(),
                             buffer_size,
                             &bytes_read) && bytes_read > 0) {
            raw_data.resize(bytes_read);
            raw_data.shrink_to_fit();
            return raw_data;
        }
        error_code = GetLastError();
        return {};
    }

    bool ftp::write(HINTERNET file_handle,
                    LPCVOID buf,
                    DWORD size,
                    LPDWORD ret_size) {
        if (!InternetWriteFile(file_handle,
                               buf,
                               size,
                               ret_size)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    DWORD ftp::write_bytes(HINTERNET file_handle, std::vector<uint8_t> &vec) {
        DWORD bytes_read = 0;
        if (InternetWriteFile(file_handle,
                              vec.data(),
                              vec.size(),
                              &bytes_read) && bytes_read > 0) {
            return bytes_read;
        }
        error_code = GetLastError();
        return 0;
    }

    int64_t ftp::size(HINTERNET file_handle) {
        DWORD low = 0;
        DWORD high = 0;

        low = FtpGetFileSize(file_handle, &high);
        if (low == INVALID_FILE_SIZE) {
            error_code = GetLastError();
            return 0;
        }
        return (static_cast<int64_t>(high) << 32) | low;
    }

    std::wstring ftp::pwd() {
        wchar_t current_dir[MAX_PATH];
        DWORD buffer_size = MAX_PATH;
        if (!FtpGetCurrentDirectoryW(session_read_handle, current_dir, &buffer_size)) {
            error_code = GetLastError();
            return {};
        }
        return current_dir;
    }

    bool ftp::cd(const wchar_t *dir) {
        if (!FtpSetCurrentDirectoryW(session_read_handle, dir)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool ftp::ls(std::vector<std::wstring> &files,
                 std::vector<std::wstring> &dirs) {
        std::wstring current_dir = pwd();
        if (current_dir.empty()) {
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
        HINTERNET find_handle = FtpFindFirstFileW(
            session_read_handle,
            current_dir.data(),
            &file_data,
            INTERNET_FLAG_RELOAD,
            0
        );
        if (!find_handle) {
            error_code = GetLastError();
            return false;
        }
        do {
            if (wcscmp(file_data.cFileName, L".") != 0 &&
                wcscmp(file_data.cFileName, L"..") != 0) {
                if (file_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
                    dirs.push_back(file_data.cFileName);
                } else {
                    files.push_back(file_data.cFileName);
                }
            }
        } while (InternetFindNextFileW(find_handle, &file_data));
        InternetCloseHandle(find_handle);
        return true;
    }

    bool ftp::ls_full_path(std::vector<std::wstring> &files,
                           std::vector<std::wstring> &dirs) {
        std::wstring current_dir = pwd();
        std::wstring base_path = current_dir;
        std::wstring slash;
        if (current_dir.empty()) {
            return false;
        }
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
        HINTERNET find_handle = FtpFindFirstFileW(
            session_read_handle,
            current_dir.data(),
            &find_file_data,
            INTERNET_FLAG_RELOAD,
            0
        );
        if (!find_handle) {
            error_code = GetLastError();
            return false;
        }
        do {
            if (wcscmp(find_file_data.cFileName, L".") != 0 &&
                wcscmp(find_file_data.cFileName, L"..") != 0) {
                if (find_file_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
                    dirs.push_back(base_path + slash + find_file_data.cFileName);
                } else {
                    files.push_back(base_path + slash + find_file_data.cFileName);
                }
            }
        } while (InternetFindNextFileW(find_handle, &find_file_data));
        InternetCloseHandle(find_handle);
        return true;
    }

    bool ftp::mkdir(const wchar_t *dir) {
        if (!FtpCreateDirectoryW(session_read_handle, dir)) {
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

    bool ftp::rm(const wchar_t *file_name) {
        if (!FtpDeleteFileW(session_read_handle, file_name)) {
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

    std::vector<uint8_t> ftp::command(const wchar_t *command) {
        HINTERNET cmd_handle = nullptr;
        if (!FtpCommandW(session_read_handle,
                         TRUE,
                         FTP_TRANSFER_TYPE_BINARY,
                         command,
                         0,
                         &cmd_handle)) {
            error_code = GetLastError();
            if (cmd_handle) {
                InternetCloseHandle(cmd_handle);
            }
            return {};
        }
        std::vector<uint8_t> result;
        DWORD bytes_read = 0;
        constexpr DWORD buffer_size = 1024;
        uint8_t *buffer = new uint8_t[buffer_size];
        while (InternetReadFile(cmd_handle,
                                buffer,
                                buffer_size,
                                &bytes_read) && bytes_read > 0) {
            result.insert(result.end(), buffer, buffer + bytes_read);
        }
        delete[] buffer;
        result.shrink_to_fit();
        return result;
    }

    bool ftp::download(const wchar_t *remote_file,
                       const wchar_t *new_file,
                       BOOL is_fail_if_exists,
                       DWORD flags_and_attrs,
                       DWORD flag,
                       DWORD_PTR context) {
        if (!FtpGetFileW(session_read_handle,
                         remote_file,
                         new_file,
                         is_fail_if_exists,
                         flags_and_attrs,
                         flag, context)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool ftp::upload(const wchar_t *local_file,
                     const wchar_t *new_remote_file,
                     DWORD flag,
                     DWORD_PTR context) {
        if (!FtpPutFileW(session_upload_handle,
                         local_file,
                         new_remote_file,
                         flag, context)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    DWORD ftp::download2(HINTERNET remote_file,
                         const wchar_t *local_file) {
        DWORD error = 0;
        fs file;
        if (!file.create(local_file)) {
            return file.err_code();
        }
        constexpr DWORD buf_size = 4096;
        uint8_t *buf = new uint8_t[buf_size];
        memset(buf, 0, buf_size);
        DWORD bytes_read = 0;
        DWORD bytes_written = 0;
        do {
            if (!read(remote_file, buf, buf_size, &bytes_read)) {
                error = err_code();
                break;
            }
            if (bytes_read <= 0) break;
            if (!file.write(buf, bytes_read, &bytes_written)) {
                error = file.err_code();
                break;
            }
        } while (bytes_read > 0 && bytes_written > 0);
        delete[] buf;
        return error;
    }

    DWORD ftp::upload2(HINTERNET remote_file,
                       const wchar_t *local_file) {
        DWORD error = 0;
        fs file;
        if (!file.open(local_file)) {
            return file.err_code();
        }
        constexpr DWORD buf_size = 4096;
        uint8_t *buf = new uint8_t[buf_size];
        memset(buf, 0, buf_size);
        DWORD bytes_read = 0;
        DWORD bytes_written = 0;
        do {
            if (!file.read(buf, buf_size, &bytes_read)) {
                error = file.err_code();
                break;
            }
            if (bytes_read <= 0) break;
            if (!write(remote_file, buf, bytes_read, &bytes_written)) {
                error = err_code();
                break;
            }
        } while (bytes_read > 0 && bytes_written > 0);
        delete[] buf;
        return error;
    }

    DWORD ftp::err_code() const {
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
}
