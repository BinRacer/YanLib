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
        HANDLE file_handle;
        DWORD error_code;

        static inline void remove_tail_slash(std::wstring &path);

    public:
        fs(const fs &other) = delete;

        fs(fs &&other) = delete;

        fs &operator=(const fs &other) = delete;

        fs &operator=(fs &&other) = delete;

        fs();

        ~fs();

        bool open(const wchar_t *file_name,
                  DWORD desired_access = GENERIC_READ | GENERIC_WRITE,
                  DWORD share_mode = FILE_SHARE_READ | FILE_SHARE_WRITE,
                  LPSECURITY_ATTRIBUTES security_attrs = nullptr,
                  DWORD creation_disposition = OPEN_EXISTING,
                  DWORD flags_and_attrs = FILE_ATTRIBUTE_NORMAL,
                  HANDLE template_file = nullptr);

        bool create(const wchar_t *file_name,
                    DWORD desired_access = GENERIC_READ | GENERIC_WRITE,
                    DWORD share_mode = FILE_SHARE_READ | FILE_SHARE_WRITE,
                    LPSECURITY_ATTRIBUTES security_attrs = nullptr,
                    DWORD creation_disposition = CREATE_ALWAYS,
                    DWORD flags_and_attrs = FILE_ATTRIBUTE_NORMAL,
                    HANDLE template_file = nullptr);

        bool touch(const wchar_t *file_name);

        bool read(void *buf,
                  DWORD size,
                  LPDWORD ret_size,
                  LPOVERLAPPED overlapped = nullptr);

        bool write(LPCVOID buf,
                   DWORD size,
                   LPDWORD ret_size,
                   LPOVERLAPPED overlapped = nullptr);

        std::string read_string(int32_t buffer_size = 1024);

        std::wstring read_wstring(int32_t buffer_size = 512);

        std::string read_string_to_end();

        std::wstring read_wstring_to_end();

        std::vector<uint8_t> read_bytes(int32_t buffer_size = 1024);

        std::vector<uint8_t> read_bytes_to_end();

        DWORD write_string_to_file(const std::string &str);

        DWORD write_wstring_to_file(const std::wstring &wstr);

        DWORD write_bytes_to_file(const std::vector<uint8_t> &vec);

        int64_t size();

        static bool rm_file(const wchar_t *file_name);

        static bool is_file(const wchar_t *file_name);

        static bool is_dir(const wchar_t *path_name);

        static DWORD attr(const wchar_t *path_name);

        static bool mkdir(const wchar_t *path_name,
                          LPSECURITY_ATTRIBUTES security_attrs = nullptr);

        static bool mkdir_all(const wchar_t *path_name,
                              LPSECURITY_ATTRIBUTES security_attrs = nullptr);

        static bool rm_dir(const wchar_t *path_name);

        static bool rm_dir_all(const wchar_t *path_name);

        static void rm_dir_all_slow(const wchar_t *path_name);

        static std::vector<std::wstring> ls(const wchar_t *path_name);

        static std::vector<std::wstring> ls_full_path(const wchar_t *path_name);

        static std::vector<std::wstring> ls_all_files(const wchar_t *path_name);

        static std::vector<std::wstring> ls_all_dirs(const wchar_t *path_name);

        static bool copy(const wchar_t *existing_file_name,
                         const wchar_t *new_file_name);

        static bool copy_all(const wchar_t *existing_path_name,
                             const wchar_t *new_path_name);

        static bool rename(const wchar_t *existing_file_name,
                           const wchar_t *new_file_name);

        static bool replace(const wchar_t *existing_file_name,
                            const wchar_t *new_file_name);

        [[nodiscard]] DWORD err_code() const;

        [[nodiscard]] std::string err_string() const;

        [[nodiscard]] std::wstring err_wstring() const;
    };
}
#endif //DIRECTORY_H
