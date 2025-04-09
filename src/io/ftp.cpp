//
// Created by forkernel on 2025/4/6.
//

#include "ftp.h"
#include "../helper/convert.h"
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
             const unsigned short &port,
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
        if (hSessionRead) {
            InternetCloseHandle(hSessionRead);
            hSessionRead = nullptr;
        }
        if (hSessionUpload) {
            InternetCloseHandle(hSessionUpload);
            hSessionUpload = nullptr;
        }
        if (hInternet) {
            InternetCloseHandle(hInternet);
            hInternet = nullptr;
        }
    }

    bool ftp::url_crack(DWORD dwFlags) {
        if (!InternetCrackUrlW(
            url.data(),
            url.size(),
            dwFlags,
            &uc)) {
            error_code = GetLastError();
            return false;
        }
        _port = uc.nPort;
        return true;
    }

    bool ftp::open(const wchar_t *lpszAgent,
                   DWORD dwAccessType,
                   const wchar_t *lpszProxy,
                   const wchar_t *lpszProxyBypass,
                   DWORD dwFlags) {
        hInternet = InternetOpenW(lpszAgent,
                                  dwAccessType,
                                  lpszProxy,
                                  lpszProxyBypass,
                                  dwFlags);
        if (!hInternet) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool ftp::connect(DWORD dwService,
                      DWORD dwFlags,
                      DWORD_PTR dwContext) {
        hSessionRead = InternetConnectW(hInternet,
                                        _hostname,
                                        _port,
                                        wcslen(_username) == 0 ? nullptr : _username,
                                        wcslen(_password) == 0 ? nullptr : _password,
                                        dwService,
                                        dwFlags,
                                        dwContext);
        if (!hSessionRead) {
            error_code = GetLastError();
            return false;
        }
        hSessionUpload = InternetConnectW(hInternet,
                                          _hostname,
                                          _port,
                                          wcslen(_username) == 0 ? nullptr : _username,
                                          wcslen(_password) == 0 ? nullptr : _password,
                                          dwService,
                                          dwFlags,
                                          dwContext);
        if (!hSessionUpload) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    HINTERNET ftp::open_file(const wchar_t *lpszFileName,
                             DWORD dwAccess,
                             DWORD dwFlags,
                             DWORD_PTR dwContext) {
        HINTERNET hFile = FtpOpenFileW(hSessionRead,
                                       lpszFileName,
                                       dwAccess,
                                       dwFlags,
                                       dwContext);
        if (!hFile) {
            error_code = GetLastError();
        }
        return hFile;
    }

    HINTERNET ftp::create_file(const wchar_t *lpszFileName,
                               DWORD dwAccess,
                               DWORD dwFlags,
                               DWORD_PTR dwContext) {
        HINTERNET hFile = FtpOpenFileW(hSessionUpload,
                                       lpszFileName,
                                       dwAccess,
                                       dwFlags,
                                       dwContext);
        if (!hFile) {
            error_code = GetLastError();
        }
        return hFile;
    }

    bool ftp::read(HINTERNET hFile,
                   LPVOID lpBuffer,
                   DWORD dwNumberOfBytesToRead,
                   LPDWORD lpdwNumberOfBytesRead) {
        if (!InternetReadFile(hFile,
                              lpBuffer,
                              dwNumberOfBytesToRead,
                              lpdwNumberOfBytesRead)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    std::vector<unsigned char> ftp::read_bytes(HINTERNET hFile,
                                               int32_t bufferSize) {
        if (bufferSize < 1024) {
            bufferSize = 1024;
        }
        std::vector<unsigned char> rawData(bufferSize, '\0');
        DWORD bytesRead = 0;
        if (InternetReadFile(hFile,
                             rawData.data(),
                             bufferSize,
                             &bytesRead) && bytesRead > 0) {
            rawData.resize(bytesRead);
            rawData.shrink_to_fit();
            return rawData;
        }
        error_code = GetLastError();
        return {};
    }

    bool ftp::write(HINTERNET hFile,
                    LPCVOID lpBuffer,
                    DWORD dwNumberOfBytesToWrite,
                    LPDWORD lpdwNumberOfBytesWritten) {
        if (!InternetWriteFile(hFile,
                               lpBuffer,
                               dwNumberOfBytesToWrite,
                               lpdwNumberOfBytesWritten)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    DWORD ftp::write_bytes(HINTERNET hFile, std::vector<unsigned char> &vec) {
        DWORD bytesRead = 0;
        if (InternetWriteFile(hFile,
                              vec.data(),
                              vec.size(),
                              &bytesRead) && bytesRead > 0) {
            return bytesRead;
        }
        error_code = GetLastError();
        return 0;
    }

    int64_t ftp::size(HINTERNET hFile) {
        DWORD dwLow = 0;
        DWORD dwHigh = 0;

        dwLow = FtpGetFileSize(hFile, &dwHigh);
        if (dwLow == INVALID_FILE_SIZE) {
            error_code = GetLastError();
            return 0;
        }
        return (static_cast<int64_t>(dwHigh) << 32) | dwLow;
    }

    std::wstring ftp::pwd() {
        wchar_t szCurrentDir[MAX_PATH];
        DWORD dwBufferSize = MAX_PATH;
        if (!FtpGetCurrentDirectoryW(hSessionRead, szCurrentDir, &dwBufferSize)) {
            error_code = GetLastError();
            return {};
        }
        return szCurrentDir;
    }

    bool ftp::cd(const wchar_t *lpszDirectory) {
        if (!FtpSetCurrentDirectoryW(hSessionRead, lpszDirectory)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool ftp::ls(std::vector<std::wstring> &files,
                 std::vector<std::wstring> &dirs) {
        std::wstring currentDir = pwd();
        if (currentDir.empty()) {
            return false;
        }
        if (currentDir.back() == L'/' || currentDir.back() == L'\\') {
            currentDir.append(L"*.*");
        } else {
            if (currentDir.find(L'\\') != std::wstring::npos) {
                currentDir.append(L"\\*.*");
            } else {
                currentDir.append(L"/*.*");
            }
        }
        WIN32_FIND_DATAW findFileData;
        HINTERNET hFind = FtpFindFirstFileW(
            hSessionRead,
            currentDir.data(),
            &findFileData,
            INTERNET_FLAG_RELOAD,
            0
        );
        if (!hFind) {
            error_code = GetLastError();
            return false;
        }
        do {
            if (wcscmp(findFileData.cFileName, L".") != 0 &&
                wcscmp(findFileData.cFileName, L"..") != 0) {
                if (findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
                    dirs.push_back(findFileData.cFileName);
                } else {
                    files.push_back(findFileData.cFileName);
                }
            }
        } while (InternetFindNextFileW(hFind, &findFileData));
        InternetCloseHandle(hFind);
        return true;
    }

    bool ftp::ls_full_path(std::vector<std::wstring> &files,
                           std::vector<std::wstring> &dirs) {
        std::wstring currentDir = pwd();
        std::wstring basePath = currentDir;
        std::wstring slash;
        if (currentDir.empty()) {
            return false;
        }
        if (currentDir.back() == L'/') {
            currentDir.append(L"*.*");
            slash = L"";
        } else if (currentDir.back() == L'\\') {
            currentDir.append(L"*.*");
            slash = L"";
        } else {
            if (currentDir.find(L'\\') != std::wstring::npos) {
                currentDir.append(L"\\*.*");
                slash = L"\\";
            } else {
                currentDir.append(L"/*.*");
                slash = L"/";
            }
        }
        WIN32_FIND_DATAW findFileData;
        HINTERNET hFind = FtpFindFirstFileW(
            hSessionRead,
            currentDir.data(),
            &findFileData,
            INTERNET_FLAG_RELOAD,
            0
        );
        if (!hFind) {
            error_code = GetLastError();
            return false;
        }
        do {
            if (wcscmp(findFileData.cFileName, L".") != 0 &&
                wcscmp(findFileData.cFileName, L"..") != 0) {
                if (findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
                    dirs.push_back(basePath + slash + findFileData.cFileName);
                } else {
                    files.push_back(basePath + slash + findFileData.cFileName);
                }
            }
        } while (InternetFindNextFileW(hFind, &findFileData));
        InternetCloseHandle(hFind);
        return true;
    }

    bool ftp::mkdir(const wchar_t *lpszDirectory) {
        if (!FtpCreateDirectoryW(hSessionRead, lpszDirectory)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool ftp::rmdir(const wchar_t *lpszDirectory) {
        if (!FtpRemoveDirectoryW(hSessionRead, lpszDirectory)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool ftp::rm(const wchar_t *lpszFileName) {
        if (!FtpDeleteFileW(hSessionRead, lpszFileName)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool ftp::rename(const wchar_t *lpszExisting, const wchar_t *lpszNew) {
        if (!FtpRenameFileW(hSessionRead, lpszExisting, lpszNew)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    std::vector<unsigned char> ftp::command(const wchar_t *lpszCommand) {
        HINTERNET hCmdHandle = nullptr;
        if (!FtpCommandW(hSessionRead,
                         TRUE,
                         FTP_TRANSFER_TYPE_BINARY,
                         lpszCommand,
                         0,
                         &hCmdHandle)) {
            error_code = GetLastError();
            if (hCmdHandle) {
                InternetCloseHandle(hCmdHandle);
            }
            return {};
        }
        std::vector<unsigned char> result;
        DWORD bytesRead = 0;
        constexpr DWORD bufferSize = 1024;
        unsigned char *buffer = new unsigned char[bufferSize];
        while (InternetReadFile(hCmdHandle,
                                buffer,
                                bufferSize,
                                &bytesRead) && bytesRead > 0) {
            result.insert(result.end(), buffer, buffer + bytesRead);
        }
        delete[] buffer;
        result.shrink_to_fit();
        return result;
    }

    bool ftp::download(const wchar_t *lpszRemoteFile,
                       const wchar_t *lpszNewFile,
                       BOOL fFailIfExists,
                       DWORD dwFlagsAndAttributes,
                       DWORD dwFlags,
                       DWORD_PTR dwContext) {
        if (!FtpGetFileW(hSessionRead,
                         lpszRemoteFile,
                         lpszNewFile,
                         fFailIfExists,
                         dwFlagsAndAttributes,
                         dwFlags, dwContext)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool ftp::upload(const wchar_t *lpszLocalFile,
                     const wchar_t *lpszNewRemoteFile,
                     DWORD dwFlags,
                     DWORD_PTR dwContext) {
        if (!FtpPutFileW(hSessionUpload,
                         lpszLocalFile,
                         lpszNewRemoteFile,
                         dwFlags, dwContext)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    DWORD ftp::download2(HINTERNET remote_file,
                         const wchar_t *local_file) {
        DWORD dwError = 0;
        fs file;
        if (!file.create(local_file)) {
            return file.err_code();
        }
        constexpr DWORD bufSize = 4096;
        unsigned char *buf = new unsigned char[bufSize];
        memset(buf, 0, bufSize);
        DWORD dwRead = 0;
        DWORD dwWritten = 0;
        do {
            if (!read(remote_file, buf, bufSize, &dwRead)) {
                dwError = err_code();
                break;
            }
            if (dwRead <= 0) break;
            if (!file.write(buf, dwRead, &dwWritten)) {
                dwError = file.err_code();
                break;
            }
        } while (dwRead > 0 && dwWritten > 0);
        delete[] buf;
        return dwError;
    }

    DWORD ftp::upload2(HINTERNET remote_file,
                       const wchar_t *local_file) {
        DWORD dwError = 0;
        fs file;
        if (!file.open(local_file)) {
            return file.err_code();
        }
        constexpr DWORD bufSize = 4096;
        unsigned char *buf = new unsigned char[bufSize];
        memset(buf, 0, bufSize);
        DWORD dwRead = 0;
        DWORD dwWritten = 0;
        do {
            if (!file.read(buf, bufSize, &dwRead)) {
                dwError = file.err_code();
                break;
            }
            if (dwRead <= 0) break;
            if (!write(remote_file, buf, dwRead, &dwWritten)) {
                dwError = err_code();
                break;
            }
        } while (dwRead > 0 && dwWritten > 0);
        delete[] buf;
        return dwError;
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
