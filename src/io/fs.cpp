//
// Created by forkernel on 2025/4/3.
//

#include "fs.h"
#include "helper/convert.h"

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

    bool fs::is_protect_dirs(const wchar_t *path_name) {
        if (wcsstr(path_name, L"C:\\Program Files") ||
            wcsstr(path_name, L"C:\\Program Files (x86)") ||
            wcsstr(path_name, L"C:\\Windows") ||
            wcsstr(path_name, L"C:\\ProgramData")) {
            return true;
        }
        return false;
    }

    fs::fs() : file_handle(INVALID_HANDLE_VALUE), error_code(0) {
    }

    fs::~fs() {
        if (file_handle != INVALID_HANDLE_VALUE) {
            CloseHandle(file_handle);
            file_handle = INVALID_HANDLE_VALUE;
        }
    }

    bool fs::open(const wchar_t *file_name,
                  DWORD desired_access,
                  DWORD share_mode,
                  LPSECURITY_ATTRIBUTES security_attrs,
                  DWORD creation_disposition,
                  DWORD flags_and_attrs,
                  HANDLE template_file) {
        // avoid open file twice
        if (file_handle != INVALID_HANDLE_VALUE) {
            return false;
        }
        file_handle = CreateFileW(file_name,
                                  desired_access,
                                  share_mode,
                                  security_attrs,
                                  creation_disposition,
                                  flags_and_attrs,
                                  template_file);
        if (file_handle == INVALID_HANDLE_VALUE) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool fs::create(const wchar_t *file_name,
                    DWORD desired_access,
                    DWORD share_mode,
                    LPSECURITY_ATTRIBUTES security_attrs,
                    DWORD creation_disposition,
                    DWORD flags_and_attrs,
                    HANDLE template_file) {
        // avoid create file twice
        if (file_handle != INVALID_HANDLE_VALUE) {
            return false;
        }
        file_handle = CreateFileW(file_name,
                                  desired_access,
                                  share_mode,
                                  security_attrs,
                                  creation_disposition,
                                  flags_and_attrs,
                                  template_file);
        if (file_handle == INVALID_HANDLE_VALUE) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool fs::touch(const wchar_t *file_name) {
        // avoid touch file twice
        if (file_handle != INVALID_HANDLE_VALUE) {
            return false;
        }
        file_handle = CreateFileW(file_name,
                                  GENERIC_READ | GENERIC_WRITE,
                                  FILE_SHARE_READ | FILE_SHARE_WRITE,
                                  nullptr,
                                  CREATE_NEW,
                                  FILE_ATTRIBUTE_NORMAL,
                                  nullptr);
        if (file_handle == INVALID_HANDLE_VALUE) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool fs::read(LPVOID buf,
                  DWORD size,
                  LPDWORD ret_size,
                  LPOVERLAPPED overlapped) {
        if (ReadFile(file_handle,
                     buf,
                     size,
                     ret_size,
                     overlapped)) {
            return true;
        }
        error_code = GetLastError();
        return false;
    }

    bool fs::write(LPCVOID buf,
                   DWORD size,
                   LPDWORD ret_size,
                   LPOVERLAPPED overlapped) {
        if (WriteFile(file_handle,
                      buf,
                      size,
                      ret_size,
                      overlapped)) {
            return true;
        }
        error_code = GetLastError();
        return false;
    }

    std::string fs::read_string(int32_t buffer_size) {
        if (buffer_size <= 1024) {
            buffer_size = 1024;
        }
        std::string raw_data(buffer_size, '\0');
        DWORD bytes_read = 0;
        if (ReadFile(
                file_handle,
                raw_data.data(),
                buffer_size,
                &bytes_read,
                nullptr) && bytes_read > 0) {
            raw_data.resize(bytes_read);
            raw_data.shrink_to_fit();
            return raw_data;
        }
        error_code = GetLastError();
        return {};
    }

    std::wstring fs::read_wstring(int32_t buffer_size) {
        if (buffer_size < 512) {
            buffer_size = 512;
        }
        std::wstring raw_data(buffer_size, L'\0');
        DWORD bytes_read = 0;
        if (ReadFile(
                file_handle,
                raw_data.data(),
                buffer_size * sizeof(wchar_t),
                &bytes_read,
                nullptr) && bytes_read > 0) {
            raw_data.resize(bytes_read);
            raw_data.shrink_to_fit();
            return raw_data;
        }
        error_code = GetLastError();
        return {};
    }

    std::string fs::read_string_to_end() {
        constexpr DWORD buffer_size = 4096;
        char *buf = new char[buffer_size];
        memset(buf, 0, buffer_size);
        std::string raw_data;
        raw_data.reserve(buffer_size);
        DWORD bytes_read = 0;
        BOOL ret = FALSE;
        do {
            ret = ReadFile(
                file_handle,
                buf,
                buffer_size,
                &bytes_read,
                nullptr);
            if (ret && bytes_read > 0) {
                raw_data.insert(raw_data.end(),
                                buf,
                                buf + bytes_read);
            } else {
                error_code = GetLastError();
            }
        } while (ret && bytes_read > 0);
        delete[] buf;
        raw_data.shrink_to_fit();
        return raw_data;
    }

    std::wstring fs::read_wstring_to_end() {
        constexpr DWORD buffer_size = 2048;
        wchar_t *buf = new wchar_t[buffer_size];
        memset(buf, 0, buffer_size * sizeof(wchar_t));
        std::wstring raw_data;
        raw_data.reserve(buffer_size);
        DWORD bytes_read = 0;
        BOOL ret = FALSE;
        do {
            ret = ReadFile(
                file_handle,
                buf,
                buffer_size * sizeof(wchar_t),
                &bytes_read,
                nullptr);
            if (ret && bytes_read > 0) {
                raw_data.insert(raw_data.end(),
                                buf,
                                buf + bytes_read / sizeof(wchar_t));
            } else {
                error_code = GetLastError();
            }
        } while (ret && bytes_read > 0);
        delete[] buf;
        raw_data.shrink_to_fit();
        return raw_data;
    }

    std::vector<uint8_t> fs::read_bytes(int32_t buffer_size) {
        if (buffer_size < 1024) {
            buffer_size = 1024;
        }
        std::vector<uint8_t> raw_data(buffer_size, '\0');
        DWORD bytes_read = 0;
        if (ReadFile(
                file_handle,
                raw_data.data(),
                buffer_size,
                &bytes_read,
                nullptr) && bytes_read > 0) {
            raw_data.resize(bytes_read);
            raw_data.shrink_to_fit();
            return raw_data;
        }
        error_code = GetLastError();
        return {};
    }

    std::vector<uint8_t> fs::read_bytes_to_end() {
        constexpr DWORD buffer_size = 4096;
        uint8_t *buf = new uint8_t[buffer_size];
        memset(buf, 0, buffer_size);
        std::vector<uint8_t> raw_data;
        raw_data.reserve(buffer_size);
        DWORD bytes_read = 0;
        BOOL ret = FALSE;
        do {
            ret = ReadFile(
                file_handle,
                buf,
                buffer_size,
                &bytes_read,
                nullptr);
            if (ret && bytes_read > 0) {
                raw_data.insert(raw_data.end(),
                                buf,
                                buf + bytes_read);
            } else {
                error_code = GetLastError();
            }
        } while (ret && bytes_read > 0);
        delete[] buf;
        raw_data.shrink_to_fit();
        return raw_data;
    }

    DWORD fs::write_string_to_file(const std::string &str) {
        if (str.empty()) {
            return 0;
        }
        DWORD bytes_written = 0;
        if (!WriteFile(file_handle,
                       str.data(),
                       str.size(),
                       &bytes_written,
                       nullptr)) {
            error_code = GetLastError();
        }
        return bytes_written;
    }

    DWORD fs::write_wstring_to_file(const std::wstring &wstr) {
        if (wstr.empty()) {
            return 0;
        }
        DWORD bytes_written = 0;
        if (!WriteFile(file_handle,
                       wstr.data(),
                       wstr.size() * sizeof(wchar_t),
                       &bytes_written,
                       nullptr)) {
            error_code = GetLastError();
        }
        return bytes_written;
    }

    DWORD fs::write_bytes_to_file(const std::vector<uint8_t> &vec) {
        if (vec.empty()) {
            return 0;
        }
        DWORD bytes_written = 0;
        if (!WriteFile(file_handle,
                       vec.data(),
                       vec.size(),
                       &bytes_written,
                       nullptr)) {
            error_code = GetLastError();
        }
        return bytes_written;
    }

    int64_t fs::size() {
        LARGE_INTEGER file_size{};
        if (!GetFileSizeEx(file_handle, &file_size)) {
            error_code = GetLastError();
        }
        return file_size.QuadPart;
    }

    bool fs::rm_file(const wchar_t *file_name) {
        return (!is_protect_dirs(file_name)) &&
               DeleteFileW(file_name);
    }

    bool fs::is_file(const wchar_t *file_name) {
        const DWORD attr = GetFileAttributesW(file_name);
        return (attr != INVALID_FILE_ATTRIBUTES) &&
               (!(attr & FILE_ATTRIBUTE_DIRECTORY));
    }

    bool fs::is_dir(const wchar_t *path_name) {
        const DWORD attr = GetFileAttributesW(path_name);
        return (attr != INVALID_FILE_ATTRIBUTES) &&
               (attr & FILE_ATTRIBUTE_DIRECTORY);
    }

    DWORD fs::attr(const wchar_t *path_name) {
        return GetFileAttributesW(path_name);
    }


    bool fs::mkdir(const wchar_t *path_name,
                   LPSECURITY_ATTRIBUTES
                   security_attrs) {
        return CreateDirectoryW(path_name, security_attrs);
    }

    bool fs::mkdir_all(const wchar_t *path_name,
                       LPSECURITY_ATTRIBUTES security_attrs) {
        std::wstring path(path_name);
        std::vector<std::wstring> dirs;
        std::wstring currentDir;

        for (const wchar_t ch: path) {
            if (ch == L'\\' || ch == L'/') {
                dirs.push_back(currentDir);
            }
            currentDir += ch;
        }
        dirs.push_back(currentDir);

        for (const std::wstring &dir: dirs) {
            if (!is_dir(dir.data())) {
                if (!CreateDirectoryW(dir.data(),
                                      security_attrs)) {
                    if (GetLastError() != ERROR_ALREADY_EXISTS) {
                        return false;
                    }
                }
            }
        }
        return true;
    }

    bool fs::rm_dir(const wchar_t *path_name) {
        return (!is_protect_dirs(path_name)) &&
               RemoveDirectoryW(path_name);
    }

    bool fs::rm_dir_all(const wchar_t *path_name) {
        if (is_protect_dirs(path_name)) {
            return false;
        }

        SHFILEOPSTRUCTW op = {};

        wchar_t szPath[MAX_PATH + 2] = {};
        wcscpy_s(szPath, MAX_PATH, path_name);
        szPath[wcslen(path_name) + 1] = L'\0';

        op.wFunc = FO_DELETE;
        op.pFrom = szPath;
        op.fFlags = FOF_NOCONFIRMATION | FOF_SILENT | FOF_NOERRORUI;

        int result = SHFileOperationW(&op);
        return (result == 0) && !op.fAnyOperationsAborted;
    }

    void fs::rm_dir_all_slow(const wchar_t *path_name) {
        if (is_protect_dirs(path_name)) {
            return;
        }
        std::vector<std::wstring> dirs = ls_all_dirs(path_name);
        std::vector<std::wstring> files = ls_all_files(path_name);

        std::for_each(files.rbegin(), files.rend(),
                      [](const std::wstring &file) {
                          rm_file(file.data());
                      });
        std::for_each(dirs.rbegin(), dirs.rend(),
                      [](const std::wstring &dir) {
                          rm_dir(dir.data());
                      });
    }

    std::vector<std::wstring> fs::ls(const wchar_t *path_name) {
        std::vector<std::wstring> result;
        std::wstring path(path_name);
        WIN32_FIND_DATAW find_data;

        remove_tail_slash(path);

        std::wstring base_path = path;
        path.append(L"\\*.*");

        HANDLE find_handle = FindFirstFileW(path.data(), &find_data);
        if (find_handle == INVALID_HANDLE_VALUE) {
            return result;
        }
        do {
            if (wcscmp(find_data.cFileName, L".") != 0 &&
                wcscmp(find_data.cFileName, L"..") != 0) {
                result.push_back(find_data.cFileName);
            }
        } while (FindNextFileW(find_handle, &find_data));
        FindClose(find_handle);
        return result;
    }

    std::vector<std::wstring> fs::ls_full_path(const wchar_t *path_name) {
        std::vector<std::wstring> result;
        std::wstring path(path_name);
        WIN32_FIND_DATAW find_data;

        remove_tail_slash(path);

        std::wstring base_path = path;
        path.append(L"\\*.*");

        HANDLE find_handle = FindFirstFileW(path.data(), &find_data);
        if (find_handle == INVALID_HANDLE_VALUE) {
            return result;
        }
        do {
            if (wcscmp(find_data.cFileName, L".") != 0 &&
                wcscmp(find_data.cFileName, L"..") != 0) {
                result.push_back(base_path + L"\\" + find_data.cFileName);
            }
        } while (FindNextFileW(find_handle, &find_data));
        FindClose(find_handle);
        return result;
    }

    std::vector<std::wstring> fs::ls_all_files(const wchar_t *path_name) {
        std::vector<std::wstring> result;
        result.reserve(64);

        std::wstring path(path_name);
        WIN32_FIND_DATAW find_data;

        remove_tail_slash(path);

        std::vector<std::wstring> stack;
        stack.reserve(64);
        stack.push_back(path + L"\\*.*");

        while (!stack.empty()) {
            std::wstring search_path = stack.back();
            stack.pop_back();

            HANDLE find_handle = FindFirstFileW(search_path.data(), &find_data);
            if (find_handle != INVALID_HANDLE_VALUE) {
                do {
                    if (wcscmp(find_data.cFileName, L".") == 0 ||
                        wcscmp(find_data.cFileName, L"..") == 0)
                        continue;
                    std::wstring full_path = search_path.substr(
                                                 0,
                                                 search_path.size() - 3)
                                             + find_data.cFileName;
                    if (find_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
                        stack.push_back(full_path + L"\\*.*");
                    } else {
                        result.push_back(full_path);
                    }
                } while (FindNextFileW(find_handle, &find_data));
                FindClose(find_handle);
            }
        }
        return result;
    }

    std::vector<std::wstring> fs::ls_all_dirs(const wchar_t *path_name) {
        std::vector<std::wstring> result;
        result.reserve(64);

        std::wstring path(path_name);
        WIN32_FIND_DATAW find_data;

        remove_tail_slash(path);

        result.push_back(path);
        std::vector<std::wstring> stack;
        stack.reserve(64);

        stack.push_back(path + L"\\*.*");
        while (!stack.empty()) {
            std::wstring search_path = stack.back();
            stack.pop_back();

            HANDLE find_handle = FindFirstFileW(search_path.data(), &find_data);
            if (find_handle != INVALID_HANDLE_VALUE) {
                do {
                    if (wcscmp(find_data.cFileName, L".") == 0 ||
                        wcscmp(find_data.cFileName, L"..") == 0)
                        continue;
                    std::wstring full_path = search_path.substr(
                                                 0,
                                                 search_path.size() - 3)
                                             + find_data.cFileName;
                    if (find_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
                        stack.push_back(full_path + L"\\*.*");
                        result.push_back(full_path);
                    }
                } while (FindNextFileW(find_handle, &find_data));
                FindClose(find_handle);
            }
        }
        return result;
    }

    bool fs::copy(const wchar_t *existing_file_name,
                  const wchar_t *new_file_name) {
        return CopyFileW(existing_file_name,
                         new_file_name,
                         false);
    }

    bool fs::copy_all(const wchar_t *existing_path_name,
                      const wchar_t *new_path_name) {
        SHFILEOPSTRUCTW file_op = {};

        WCHAR from[MAX_PATH + 2] = {};
        WCHAR to[MAX_PATH + 2] = {};

        wcscpy_s(from, MAX_PATH, existing_path_name);
        wcscpy_s(to, MAX_PATH, new_path_name);

        from[wcslen(existing_path_name) + 1] = L'\0';
        to[wcslen(new_path_name) + 1] = L'\0';

        file_op.wFunc = FO_COPY;
        file_op.pFrom = from;
        file_op.pTo = to;
        file_op.fFlags = FOF_NOCONFIRMMKDIR | FOF_NOCONFIRMATION | FOF_NO_UI;
        int result = SHFileOperationW(&file_op);
        return (result == 0) && !file_op.fAnyOperationsAborted;
    }

    bool fs::rename(const wchar_t *existing_file_name,
                    const wchar_t *new_file_name) {
        return MoveFileExW(existing_file_name,
                           new_file_name,
                           MOVEFILE_COPY_ALLOWED);
    }

    bool fs::replace(const wchar_t *existing_file_name,
                     const wchar_t *new_file_name) {
        return MoveFileExW(existing_file_name,
                           new_file_name,
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
