//
// Created by forkernel on 2025/4/3.
//

#include "fs.h"
#include "../helper/convert.h"

namespace YanLib::io {
    void fs::remove_tail_slash(std::wstring &path) {
        std::transform(path.begin(),
                       path.end(),
                       path.begin(),
                       [](wchar_t c) { return (c == L'/') ? L'\\' : c; });
        if (path.back() == L'\\') {
            path.pop_back();
        }
    }

    bool fs::is_protect_dirs(const wchar_t *lpPathName) {
        if (wcsstr(lpPathName, L"C:\\Program Files") ||
            wcsstr(lpPathName, L"C:\\Program Files (x86)") ||
            wcsstr(lpPathName, L"C:\\Windows") ||
            wcsstr(lpPathName, L"C:\\ProgramData")) {
            return true;
        }
        return false;
    }

    fs::fs() : hFile(INVALID_HANDLE_VALUE), error_code(0) {
    }

    fs::~fs() {
        if (hFile != INVALID_HANDLE_VALUE) {
            CloseHandle(hFile);
        }
    }

    bool fs::open(const wchar_t *lpFileName,
                  DWORD dwDesiredAccess,
                  DWORD dwShareMode,
                  LPSECURITY_ATTRIBUTES lpSecurityAttributes,
                  DWORD dwCreationDisposition,
                  DWORD dwFlagsAndAttributes,
                  HANDLE hTemplateFile) {
        // avoid open file twice
        if (hFile != INVALID_HANDLE_VALUE) {
            return false;
        }
        hFile = CreateFileW(lpFileName,
                            dwDesiredAccess,
                            dwShareMode,
                            lpSecurityAttributes,
                            dwCreationDisposition,
                            dwFlagsAndAttributes,
                            hTemplateFile);
        if (hFile == INVALID_HANDLE_VALUE) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool fs::create(const wchar_t *lpFileName,
                    DWORD dwDesiredAccess,
                    DWORD dwShareMode,
                    LPSECURITY_ATTRIBUTES lpSecurityAttributes,
                    DWORD dwCreationDisposition,
                    DWORD dwFlagsAndAttributes,
                    HANDLE hTemplateFile) {
        // avoid create file twice
        if (hFile != INVALID_HANDLE_VALUE) {
            return false;
        }
        hFile = CreateFileW(lpFileName,
                            dwDesiredAccess,
                            dwShareMode,
                            lpSecurityAttributes,
                            dwCreationDisposition,
                            dwFlagsAndAttributes,
                            hTemplateFile);
        if (hFile == INVALID_HANDLE_VALUE) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool fs::touch(const wchar_t *lpFileName) {
        // avoid touch file twice
        if (hFile != INVALID_HANDLE_VALUE) {
            return false;
        }
        hFile = CreateFileW(lpFileName,
                            GENERIC_READ | GENERIC_WRITE,
                            FILE_SHARE_READ | FILE_SHARE_WRITE,
                            nullptr,
                            CREATE_NEW,
                            FILE_ATTRIBUTE_NORMAL,
                            nullptr);
        if (hFile == INVALID_HANDLE_VALUE) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool fs::read(LPVOID lpBuffer,
                  DWORD nNumberOfBytesToRead,
                  LPDWORD lpNumberOfBytesRead,
                  LPOVERLAPPED lpOverlapped) {
        if (ReadFile(hFile,
                     lpBuffer,
                     nNumberOfBytesToRead,
                     lpNumberOfBytesRead,
                     lpOverlapped)) {
            return true;
        }
        error_code = GetLastError();
        return false;
    }

    bool fs::write(LPCVOID lpBuffer,
                   DWORD nNumberOfBytesToWrite,
                   LPDWORD lpNumberOfBytesWritten,
                   LPOVERLAPPED lpOverlapped) {
        if (WriteFile(hFile,
                      lpBuffer,
                      nNumberOfBytesToWrite,
                      lpNumberOfBytesWritten,
                      lpOverlapped)) {
            return true;
        }
        error_code = GetLastError();
        return false;
    }

    std::string fs::read_string(int32_t bufferSize) {
        if (bufferSize <= 1024) {
            bufferSize = 1024;
        }
        std::string rawData(bufferSize, '\0');
        DWORD bytesRead = 0;
        if (ReadFile(
                hFile,
                rawData.data(),
                bufferSize,
                &bytesRead,
                nullptr) && bytesRead > 0) {
            rawData.resize(bytesRead);
            rawData.shrink_to_fit();
            return rawData;
        }
        error_code = GetLastError();
        return {};
    }

    std::wstring fs::read_wstring(int32_t bufferSize) {
        if (bufferSize < 512) {
            bufferSize = 512;
        }
        std::wstring rawData(bufferSize, L'\0');
        DWORD bytesRead = 0;
        if (ReadFile(
                hFile,
                rawData.data(),
                bufferSize * sizeof(wchar_t),
                &bytesRead,
                nullptr) && bytesRead > 0) {
            rawData.resize(bytesRead);
            rawData.shrink_to_fit();
            return rawData;
        }
        error_code = GetLastError();
        return {};
    }

    std::string fs::read_string_to_end() {
        constexpr DWORD bufferSize = 4096;
        char *buf = new char[bufferSize];
        memset(buf, 0, bufferSize);
        std::string rawData;
        rawData.reserve(bufferSize);
        DWORD bytesRead = 0;
        BOOL bRet = FALSE;
        do {
            bRet = ReadFile(
                hFile,
                buf,
                bufferSize,
                &bytesRead,
                nullptr);
            if (bRet && bytesRead > 0) {
                rawData.insert(rawData.end(),
                               buf,
                               buf + bytesRead);
            } else {
                error_code = GetLastError();
            }
        } while (bRet && bytesRead > 0);
        delete[] buf;
        rawData.shrink_to_fit();
        return rawData;
    }

    std::wstring fs::read_wstring_to_end() {
        constexpr DWORD bufferSize = 2048;
        wchar_t *buf = new wchar_t[bufferSize];
        memset(buf, 0, bufferSize * sizeof(wchar_t));
        std::wstring rawData;
        rawData.reserve(bufferSize);
        DWORD bytesRead = 0;
        BOOL bRet = FALSE;
        do {
            bRet = ReadFile(
                hFile,
                buf,
                bufferSize * sizeof(wchar_t),
                &bytesRead,
                nullptr);
            if (bRet && bytesRead > 0) {
                rawData.insert(rawData.end(),
                               buf,
                               buf + bytesRead / sizeof(wchar_t));
            } else {
                error_code = GetLastError();
            }
        } while (bRet && bytesRead > 0);
        delete[] buf;
        rawData.shrink_to_fit();
        return rawData;
    }

    std::vector<uint8_t> fs::read_bytes(int32_t bufferSize) {
        if (bufferSize < 1024) {
            bufferSize = 1024;
        }
        std::vector<uint8_t> rawData(bufferSize, '\0');
        DWORD bytesRead = 0;
        if (ReadFile(
                hFile,
                rawData.data(),
                bufferSize,
                &bytesRead,
                nullptr) && bytesRead > 0) {
            rawData.resize(bytesRead);
            rawData.shrink_to_fit();
            return rawData;
        }
        error_code = GetLastError();
        return {};
    }

    std::vector<uint8_t> fs::read_bytes_to_end() {
        constexpr DWORD bufferSize = 4096;
        uint8_t *buf = new uint8_t[bufferSize];
        memset(buf, 0, bufferSize);
        std::vector<uint8_t> rawData;
        rawData.reserve(bufferSize);
        DWORD bytesRead = 0;
        BOOL bRet = FALSE;
        do {
            bRet = ReadFile(
                hFile,
                buf,
                bufferSize,
                &bytesRead,
                nullptr);
            if (bRet && bytesRead > 0) {
                rawData.insert(rawData.end(),
                               buf,
                               buf + bytesRead);
            } else {
                error_code = GetLastError();
            }
        } while (bRet && bytesRead > 0);
        delete[] buf;
        rawData.shrink_to_fit();
        return rawData;
    }

    DWORD fs::write_string_to_file(const std::string &str) {
        if (str.empty()) {
            return 0;
        }
        DWORD numberOfBytesWritten = 0;
        if (!WriteFile(hFile,
                       str.data(),
                       str.size(),
                       &numberOfBytesWritten,
                       nullptr)) {
            error_code = GetLastError();
        }
        return numberOfBytesWritten;
    }

    DWORD fs::write_wstring_to_file(const std::wstring &wstr) {
        if (wstr.empty()) {
            return 0;
        }
        DWORD numberOfBytesWritten = 0;
        if (!WriteFile(hFile,
                       wstr.data(),
                       wstr.size() * sizeof(wchar_t),
                       &numberOfBytesWritten,
                       nullptr)) {
            error_code = GetLastError();
        }
        return numberOfBytesWritten;
    }

    DWORD fs::write_bytes_to_file(const std::vector<uint8_t> &vec) {
        if (vec.empty()) {
            return 0;
        }
        DWORD numberOfBytesWritten = 0;
        if (!WriteFile(hFile,
                       vec.data(),
                       vec.size(),
                       &numberOfBytesWritten,
                       nullptr)) {
            error_code = GetLastError();
        }
        return numberOfBytesWritten;
    }

    int64_t fs::size() {
        LARGE_INTEGER lpFileSize{};
        if (!GetFileSizeEx(hFile, &lpFileSize)) {
            error_code = GetLastError();
        }
        return lpFileSize.QuadPart;
    }

    bool fs::rm_file(const wchar_t *lpFileName) {
        return (!is_protect_dirs(lpFileName)) &&
               DeleteFileW(lpFileName);
    }

    bool fs::is_file(const wchar_t *lpFileName) {
        const DWORD attr = GetFileAttributesW(lpFileName);
        return (attr != INVALID_FILE_ATTRIBUTES) &&
               (!(attr & FILE_ATTRIBUTE_DIRECTORY));
    }

    bool fs::is_dir(const wchar_t *lpPathName) {
        const DWORD attr = GetFileAttributesW(lpPathName);
        return (attr != INVALID_FILE_ATTRIBUTES) &&
               (attr & FILE_ATTRIBUTE_DIRECTORY);
    }

    DWORD fs::attr(const wchar_t *lpPathName) {
        return GetFileAttributesW(lpPathName);
    }


    bool fs::mkdir(const wchar_t *lpPathName,
                   LPSECURITY_ATTRIBUTES
                   lpSecurityAttributes) {
        return CreateDirectoryW(lpPathName, lpSecurityAttributes);
    }

    bool fs::mkdir_all(const wchar_t *lpPathName,
                       LPSECURITY_ATTRIBUTES lpSecurityAttributes) {
        std::wstring pathName(lpPathName);
        std::vector<std::wstring> dirs;
        std::wstring currentDir;

        for (const wchar_t ch: pathName) {
            if (ch == L'\\' || ch == L'/') {
                dirs.push_back(currentDir);
            }
            currentDir += ch;
        }
        dirs.push_back(currentDir);

        for (const std::wstring &dir: dirs) {
            if (!is_dir(dir.data())) {
                if (!CreateDirectoryW(dir.data(),
                                      lpSecurityAttributes)) {
                    if (GetLastError() != ERROR_ALREADY_EXISTS) {
                        return false;
                    }
                }
            }
        }
        return true;
    }

    bool fs::rm_dir(const wchar_t *lpPathName) {
        return (!is_protect_dirs(lpPathName)) &&
               RemoveDirectoryW(lpPathName);
    }

    bool fs::rm_dir_all(const wchar_t *lpPathName) {
        if (is_protect_dirs(lpPathName)) {
            return false;
        }

        SHFILEOPSTRUCTW op;
        memset(&op, 0, sizeof(op));

        wchar_t szPath[MAX_PATH + 2] = {0};
        wcscpy_s(szPath, MAX_PATH, lpPathName);
        szPath[wcslen(lpPathName) + 1] = L'\0';

        op.wFunc = FO_DELETE;
        op.pFrom = szPath;
        op.fFlags = FOF_NOCONFIRMATION | FOF_SILENT | FOF_NOERRORUI;

        int result = SHFileOperationW(&op);
        return (result == 0) && !op.fAnyOperationsAborted;
    }

    void fs::rm_dir_all_slow(const wchar_t *lpPathName) {
        if (is_protect_dirs(lpPathName)) {
            return;
        }
        std::vector<std::wstring> dirs = ls_all_dirs(lpPathName);
        std::vector<std::wstring> files = ls_all_files(lpPathName);

        std::for_each(files.rbegin(), files.rend(),
                      [](const std::wstring &file) {
                          rm_file(file.data());
                      });
        std::for_each(dirs.rbegin(), dirs.rend(),
                      [](const std::wstring &dir) {
                          rm_dir(dir.data());
                      });
    }

    std::vector<std::wstring> fs::ls(const wchar_t *lpPathName) {
        std::vector<std::wstring> result;
        std::wstring pathName(lpPathName);
        WIN32_FIND_DATAW findData;

        remove_tail_slash(pathName);

        std::wstring basePath = pathName;
        pathName.append(L"\\*.*");

        HANDLE hFind = FindFirstFileW(pathName.data(), &findData);
        if (hFind == INVALID_HANDLE_VALUE) {
            return result;
        }
        do {
            if (wcscmp(findData.cFileName, L".") != 0 &&
                wcscmp(findData.cFileName, L"..") != 0) {
                result.push_back(findData.cFileName);
            }
        } while (FindNextFileW(hFind, &findData));
        FindClose(hFind);
        return result;
    }

    std::vector<std::wstring> fs::ls_full_path(const wchar_t *lpPathName) {
        std::vector<std::wstring> result;
        std::wstring pathName(lpPathName);
        WIN32_FIND_DATAW findData;

        remove_tail_slash(pathName);

        std::wstring basePath = pathName;
        pathName.append(L"\\*.*");

        HANDLE hFind = FindFirstFileW(pathName.data(), &findData);
        if (hFind == INVALID_HANDLE_VALUE) {
            return result;
        }
        do {
            if (wcscmp(findData.cFileName, L".") != 0 &&
                wcscmp(findData.cFileName, L"..") != 0) {
                result.push_back(basePath + L"\\" + findData.cFileName);
            }
        } while (FindNextFileW(hFind, &findData));
        FindClose(hFind);
        return result;
    }

    std::vector<std::wstring> fs::ls_all_files(const wchar_t *lpPathName) {
        std::vector<std::wstring> result;
        result.reserve(64);

        std::wstring pathName(lpPathName);
        WIN32_FIND_DATAW findData;

        remove_tail_slash(pathName);

        std::vector<std::wstring> stack;
        stack.reserve(64);
        stack.push_back(pathName + L"\\*.*");

        while (!stack.empty()) {
            std::wstring searchPath = stack.back();
            stack.pop_back();

            HANDLE hFind = FindFirstFileW(searchPath.data(), &findData);
            if (hFind != INVALID_HANDLE_VALUE) {
                do {
                    if (wcscmp(findData.cFileName, L".") == 0 ||
                        wcscmp(findData.cFileName, L"..") == 0)
                        continue;
                    std::wstring fullPath = searchPath.substr(
                                                0,
                                                searchPath.size() - 3)
                                            + findData.cFileName;
                    if (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
                        stack.push_back(fullPath + L"\\*.*");
                    } else {
                        result.push_back(fullPath);
                    }
                } while (FindNextFileW(hFind, &findData));
                FindClose(hFind);
            }
        }
        return result;
    }

    std::vector<std::wstring> fs::ls_all_dirs(const wchar_t *lpPathName) {
        std::vector<std::wstring> result;
        result.reserve(64);

        std::wstring pathName(lpPathName);
        WIN32_FIND_DATAW findData;

        remove_tail_slash(pathName);

        result.push_back(pathName);
        std::vector<std::wstring> stack;
        stack.reserve(64);

        stack.push_back(pathName + L"\\*.*");
        while (!stack.empty()) {
            std::wstring searchPath = stack.back();
            stack.pop_back();

            HANDLE hFind = FindFirstFileW(searchPath.data(), &findData);
            if (hFind != INVALID_HANDLE_VALUE) {
                do {
                    if (wcscmp(findData.cFileName, L".") == 0 ||
                        wcscmp(findData.cFileName, L"..") == 0)
                        continue;
                    std::wstring fullPath = searchPath.substr(
                                                0,
                                                searchPath.size() - 3)
                                            + findData.cFileName;
                    if (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
                        stack.push_back(fullPath + L"\\*.*");
                        result.push_back(fullPath);
                    }
                } while (FindNextFileW(hFind, &findData));
                FindClose(hFind);
            }
        }
        return result;
    }

    bool fs::copy(const wchar_t *lpExistingFileName,
                  const wchar_t *lpNewFileName) {
        return CopyFileW(lpExistingFileName,
                         lpNewFileName,
                         false);
    }

    bool fs::copy_all(const wchar_t *lpExistingPathName,
                      const wchar_t *lpNewPathName) {
        SHFILEOPSTRUCTW FileOp;
        memset(&FileOp, 0, sizeof(FileOp));

        WCHAR szFrom[MAX_PATH + 2] = {0};
        WCHAR szTo[MAX_PATH + 2] = {0};

        wcscpy_s(szFrom, MAX_PATH, lpExistingPathName);
        wcscpy_s(szTo, MAX_PATH, lpNewPathName);

        szFrom[wcslen(lpExistingPathName) + 1] = L'\0';
        szTo[wcslen(lpNewPathName) + 1] = L'\0';

        FileOp.wFunc = FO_COPY;
        FileOp.pFrom = szFrom;
        FileOp.pTo = szTo;
        FileOp.fFlags = FOF_NOCONFIRMMKDIR | FOF_NOCONFIRMATION | FOF_NO_UI;
        int result = SHFileOperationW(&FileOp);
        return (result == 0) && !FileOp.fAnyOperationsAborted;
    }

    bool fs::rename(const wchar_t *lpExistingFileName,
                    const wchar_t *lpNewFileName) {
        return MoveFileExW(lpExistingFileName,
                           lpNewFileName,
                           MOVEFILE_COPY_ALLOWED);
    }

    bool fs::replace(const wchar_t *lpExistingFileName,
                     const wchar_t *lpNewFileName) {
        return MoveFileExW(lpExistingFileName,
                           lpNewFileName,
                           MOVEFILE_REPLACE_EXISTING);
    }

    DWORD fs::err_code() const {
        return error_code;
    }

    std::string fs::err_string() const {
        std::string result = helper::convert::err_string(error_code);
        return result;
    }

    std::wstring fs::err_wstring() const {
        std::wstring result = helper::convert::err_wstring(error_code);
        return result;
    }
}
