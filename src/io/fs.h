//
// Created by forkernel on 2025/4/3.
//

#ifndef DIRECTORY_H
#define DIRECTORY_H
#include <Windows.h>
#include <vector>
#include <string>
#include <algorithm>

namespace YanLib::io {
    class fs {
    private:
        HANDLE hFile;
        DWORD error_code;

        static inline void remove_tail_slash(std::wstring &path);

        static inline bool is_protect_dirs(const wchar_t *lpPathName);

    public:
        fs(const fs &other) = delete;

        fs(fs &&other) = delete;

        fs &operator=(const fs &other) = delete;

        fs &operator=(fs &&other) = delete;

        fs();

        ~fs();

        bool open(const wchar_t *lpFileName,
                  DWORD dwDesiredAccess = GENERIC_READ | GENERIC_WRITE,
                  DWORD dwShareMode = FILE_SHARE_READ | FILE_SHARE_WRITE,
                  LPSECURITY_ATTRIBUTES lpSecurityAttributes = nullptr,
                  DWORD dwCreationDisposition = OPEN_EXISTING,
                  DWORD dwFlagsAndAttributes = FILE_ATTRIBUTE_NORMAL,
                  HANDLE hTemplateFile = nullptr);

        bool create(const wchar_t *lpFileName,
                    DWORD dwDesiredAccess = GENERIC_READ | GENERIC_WRITE,
                    DWORD dwShareMode = FILE_SHARE_READ | FILE_SHARE_WRITE,
                    LPSECURITY_ATTRIBUTES lpSecurityAttributes = nullptr,
                    DWORD dwCreationDisposition = CREATE_ALWAYS,
                    DWORD dwFlagsAndAttributes = FILE_ATTRIBUTE_NORMAL,
                    HANDLE hTemplateFile = nullptr);

        bool touch(const wchar_t *lpFileName);

        bool read(LPVOID lpBuffer,
                  DWORD nNumberOfBytesToRead,
                  LPDWORD lpNumberOfBytesRead,
                  LPOVERLAPPED lpOverlapped = nullptr);

        bool write(LPCVOID lpBuffer,
                   DWORD nNumberOfBytesToWrite,
                   LPDWORD lpNumberOfBytesWritten,
                   LPOVERLAPPED lpOverlapped = nullptr);

        std::string read_string(int32_t bufferSize = 1024);

        std::wstring read_wstring(int32_t bufferSize = 512);

        std::string read_string_to_end();

        std::wstring read_wstring_to_end();

        std::vector<unsigned char> read_bytes(int32_t bufferSize = 1024);

        std::vector<unsigned char> read_bytes_to_end();

        DWORD write_string_to_file(const std::string &str);

        DWORD write_wstring_to_file(const std::wstring &wstr);

        DWORD write_bytes_to_file(const std::vector<unsigned char> &vec);

        int64_t size();

        static bool rm_file(const wchar_t *lpFileName);

        static bool is_file(const wchar_t *lpFileName);

        static bool is_dir(const wchar_t *lpPathName);

        static DWORD attr(const wchar_t *lpPathName);

        static bool mkdir(const wchar_t *lpPathName,
                          LPSECURITY_ATTRIBUTES lpSecurityAttributes = nullptr);

        static bool mkdir_all(const wchar_t *lpPathName,
                              LPSECURITY_ATTRIBUTES lpSecurityAttributes = nullptr);

        static bool rm_dir(const wchar_t *lpPathName);

        static bool rm_dir_all(const wchar_t *lpPathName);

        static void rm_dir_all_slow(const wchar_t *lpPathName);

        static std::vector<std::wstring> ls(const wchar_t *lpPathName);

        static std::vector<std::wstring> ls_full_path(const wchar_t *lpPathName);

        static std::vector<std::wstring> ls_all_files(const wchar_t *lpPathName);

        static std::vector<std::wstring> ls_all_dirs(const wchar_t *lpPathName);

        static bool copy(const wchar_t *lpExistingFileName,
                         const wchar_t *lpNewFileName);

        static bool copy_all(const wchar_t *lpExistingPathName,
                             const wchar_t *lpNewPathName);

        static bool rename(const wchar_t *lpExistingFileName,
                           const wchar_t *lpNewFileName);

        static bool replace(const wchar_t *lpExistingFileName,
                            const wchar_t *lpNewFileName);

        DWORD err_code() const;

        std::string err_string() const;

        std::wstring err_wstring() const;
    };
}
#endif //DIRECTORY_H
