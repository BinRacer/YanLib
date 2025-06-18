/* clang-format off */
/*
 * @file fs.h
 * @date 2025-04-03
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
#ifndef FSANDFSUTIL_H
#define FSANDFSUTIL_H
#include <Windows.h>
#include <handleapi.h>
#include <minwinbase.h>
#include <winnt.h>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdint>
#include "helper/convert.h"
#include "io.h"
namespace YanLib::io {
    class fs {
    private:
        HANDLE file_handle = INVALID_HANDLE_VALUE;
        volatile bool is_open_failed = false;
        uint32_t error_code = 0;

        static inline void remove_tail_slash(std::string &path);

        static inline void remove_tail_slash(std::wstring &path);

    public:
        fs(const fs &other) = delete;

        fs(fs &&other) = delete;

        fs &operator=(const fs &other) = delete;

        fs &operator=(fs &&other) = delete;

        fs() = delete;

        explicit fs(const char *file_name,
                    DesiredAccess desired_access = DesiredAccess::Read |
                            DesiredAccess::Write,
                    ShareMode share_mode = ShareMode::Read | ShareMode::Write,
                    SECURITY_ATTRIBUTES *security_attrs = nullptr,
                    CreationDisposition creation_disposition =
                            CreationDisposition::OpenExisting,
                    FlagAndAttr flag_and_attr = FlagAndAttr::Normal,
                    HANDLE template_file = nullptr);

        explicit fs(const wchar_t *file_name,
                    DesiredAccess desired_access = DesiredAccess::Read |
                            DesiredAccess::Write,
                    ShareMode share_mode = ShareMode::Read | ShareMode::Write,
                    SECURITY_ATTRIBUTES *security_attrs = nullptr,
                    CreationDisposition creation_disposition =
                            CreationDisposition::OpenExisting,
                    FlagAndAttr flag_and_attr = FlagAndAttr::Normal,
                    HANDLE template_file = nullptr);

        ~fs();

        [[nodiscard]] bool is_ok() const;

        bool read(void *buf,
                  uint32_t size,
                  uint32_t *bytes_read,
                  OVERLAPPED *overlapped = nullptr);

        typedef LPOVERLAPPED_COMPLETION_ROUTINE OVERLAPPED_COMPLETION_ROUTINE;

        bool read(void *buf,
                  uint32_t size,
                  OVERLAPPED *overlapped,
                  OVERLAPPED_COMPLETION_ROUTINE completion_routine);

        bool write(const void *buf,
                   uint32_t size,
                   uint32_t *bytes_written,
                   OVERLAPPED *overlapped = nullptr);

        bool write(const void *buf,
                   uint32_t size,
                   OVERLAPPED *overlapped,
                   OVERLAPPED_COMPLETION_ROUTINE completion_routine);

        std::vector<uint8_t> read_bytes(int32_t buffer_size = 1024);

        std::string read_string(int32_t buffer_size = 1024);

        std::vector<uint8_t> read_bytes_to_end();

        std::string read_string_to_end();

        uint32_t write_bytes(const std::vector<uint8_t> &data);

        uint32_t write_string(const std::string &data);

        int64_t seek(int64_t offset,
                     MoveMethod move_method = MoveMethod::Current);

        bool truncate();

        bool lock(uint64_t offset = 0, uint64_t range = UINT64_MAX);

        bool lock_async(LockMode lock_mode = LockMode::ExclusiveLock,
                        uint64_t range = UINT64_MAX,
                        OVERLAPPED *overlapped = nullptr);

        bool unlock(uint64_t offset = 0, uint64_t range = UINT64_MAX);

        bool unlock_async(uint64_t range = UINT64_MAX,
                          OVERLAPPED *overlapped = nullptr);

        bool get_info(FILE_INFO_BY_HANDLE_CLASS file_info_class,
                      void *file_info,
                      uint32_t file_info_size);

        bool set_info(FILE_INFO_BY_HANDLE_CLASS file_info_class,
                      void *file_info,
                      uint32_t file_info_size);

        bool set_io_overlapped_range(uint8_t *overlapped_range_start,
                                     uint32_t length);

        bool
        get_volume_info(VolumeInfoA *volume_info,
                        helper::CodePage code_page = helper::curr_code_page());

        bool get_volume_info(VolumeInfoW *volume_info);

        bool get_final_path_name(
                std::string &path_name,
                PathNameType type = PathNameType::Normalized,
                helper::CodePage code_page = helper::curr_code_page());

        bool get_final_path_name(std::wstring &path_name,
                                 PathNameType type = PathNameType::Normalized);

        bool is_short_name_enabled();

        bool
        monitor_dir_change(void *buffer,
                           uint32_t buffer_length,
                           bool is_watch_subtree,
                           uint32_t notify_filter,
                           uint32_t *bytes_returned,
                           OVERLAPPED *overlapped,
                           OVERLAPPED_COMPLETION_ROUTINE completion_routine);

        FileType file_type();

        int64_t size();

        [[nodiscard]] HANDLE expose_handle() const;

        [[nodiscard]] uint32_t err_code() const;

        [[nodiscard]] std::string err_string() const;

        [[nodiscard]] std::wstring err_wstring() const;
    };

    class fs_util {
    private:
        uint32_t error_code = 0;

        static inline void remove_tail_slash(std::string &path);

        static inline void remove_tail_slash(std::wstring &path);

    public:
        fs_util(const fs_util &other) = delete;

        fs_util(fs_util &&other) = delete;

        fs_util &operator=(const fs_util &other) = delete;

        fs_util &operator=(fs_util &&other) = delete;

        fs_util() = default;

        ~fs_util() = default;

        bool touch(const char *file_name,
                   DesiredAccess desired_access = DesiredAccess::Read |
                           DesiredAccess::Write,
                   ShareMode share_mode = ShareMode::Read | ShareMode::Write,
                   SECURITY_ATTRIBUTES *security_attrs = nullptr,
                   CreationDisposition creation_disposition =
                           CreationDisposition::CreateNew,
                   FlagAndAttr flag_and_attr = FlagAndAttr::Normal,
                   HANDLE template_file = nullptr);

        bool touch(const wchar_t *file_name,
                   DesiredAccess desired_access = DesiredAccess::Read |
                           DesiredAccess::Write,
                   ShareMode share_mode = ShareMode::Read | ShareMode::Write,
                   SECURITY_ATTRIBUTES *security_attrs = nullptr,
                   CreationDisposition creation_disposition =
                           CreationDisposition::CreateNew,
                   FlagAndAttr flag_and_attr = FlagAndAttr::Normal,
                   HANDLE template_file = nullptr);

        bool is_exists(const char *path_name);

        bool is_exists(const wchar_t *path_name);

        uint32_t get_attr(const char *file_name);

        uint32_t get_attr(const wchar_t *file_name);

        bool set_attr(const char *file_name, uint32_t attr);

        bool set_attr(const wchar_t *file_name, uint32_t attr);

        DriveType get_drive_type(const char *path_name);

        DriveType get_drive_type(const wchar_t *path_name);

        std::string get_volume_path_name(const char *file_name);

        std::wstring get_volume_path_name(const wchar_t *file_name);

        std::string
        get_volume_path_names_for_volume_name(const char *volume_name);

        std::wstring
        get_volume_path_names_for_volume_name(const wchar_t *volume_name);

        std::string
        get_volume_name_for_volume_mount_point(const char *volume_mount_point);

        std::wstring get_volume_name_for_volume_mount_point(
                const wchar_t *volume_mount_point);

        bool delete_volume_mount_point(const char *volume_mount_point);

        bool delete_volume_mount_point(const wchar_t *volume_mount_point);

        bool get_temp_path(std::string &path);

        bool get_temp_path(std::wstring &path);

        std::string get_temp_file_name(const char *path_name,
                                       const char *prefix = nullptr,
                                       uint32_t unique = 0);

        std::wstring get_temp_file_name(const wchar_t *path_name,
                                        const wchar_t *prefix = nullptr,
                                        uint32_t unique = 0);

        std::string get_short_path_name(const char *long_path);

        std::wstring get_short_path_name(const wchar_t *long_path);

        std::string get_long_path_name(const char *short_path);

        std::wstring get_long_path_name(const wchar_t *short_path);

        bool get_logical_drive_strings(std::string &drive);

        bool get_logical_drive_strings(std::wstring &drive);

        uint32_t get_logica_drives();

        std::string get_full_path_name(const char *file_name);

        std::wstring get_full_path_name(const wchar_t *file_name);

        bool get_disk_space_info(const char *root_path,
                                 DISK_SPACE_INFORMATION *disk_space_info);

        bool get_disk_space_info(const wchar_t *root_path,
                                 DISK_SPACE_INFORMATION *disk_space_info);

        bool get_disk_free_space(const char *root_path_name,
                                 DiskFreeSpace4 *disk_free_space4);

        bool get_disk_free_space(const wchar_t *root_path_name,
                                 DiskFreeSpace4 *disk_free_space4);

        bool get_disk_free_space(const char *directory_name,
                                 DiskFreeSpace3 *disk_free_space3);

        bool get_disk_free_space(const wchar_t *directory_name,
                                 DiskFreeSpace3 *disk_free_space3);

        int64_t get_compressed_file_size(const char *file_name);

        int64_t get_compressed_file_size(const wchar_t *file_name);

        std::string get_dos_device(const char *device_name);

        std::wstring get_dos_device(const wchar_t *device_name);

        bool get_dos_device(std::vector<std::string> &dos_device);

        bool get_dos_device(std::vector<std::wstring> &dos_device);

        bool control_dos_device(const char *device_name,
                                const char *target_path,
                                DosControlCode code);

        bool control_dos_device(const wchar_t *device_name,
                                const wchar_t *target_path,
                                DosControlCode code);

        bool ls_volume_name(std::vector<std::string> &volume_names);

        bool ls_volume_name(std::vector<std::wstring> &volume_names);

        bool ls_device_name(std::vector<std::string> &device_names);

        bool ls_device_name(std::vector<std::wstring> &device_names);

        std::vector<WIN32_FIND_STREAM_DATA>
        ls_stream_data(const char *file_name,
                       helper::CodePage code_page = helper::curr_code_page());

        std::vector<WIN32_FIND_STREAM_DATA>
        ls_stream_data(const wchar_t *file_name);

        bool rm_file(const char *file_name);

        bool rm_file(const wchar_t *file_name);

        bool is_file(const char *file_name);

        bool is_file(const wchar_t *file_name);

        bool is_dir(const char *path_name);

        bool is_dir(const wchar_t *path_name);

        bool mkdir(const char *path_name,
                   SECURITY_ATTRIBUTES *security_attrs = nullptr);

        bool mkdir(const wchar_t *path_name,
                   SECURITY_ATTRIBUTES *security_attrs = nullptr);

        bool mkdir_all(const char *path_name,
                       SECURITY_ATTRIBUTES *security_attrs = nullptr);

        bool mkdir_all(const wchar_t *path_name,
                       SECURITY_ATTRIBUTES *security_attrs = nullptr);

        bool rm_dir(const char *path_name);

        bool rm_dir(const wchar_t *path_name);

        bool rm_dir_all(const char *path_name);

        bool rm_dir_all(const wchar_t *path_name);

        void rm_dir_all_slow(const char *path_name);

        void rm_dir_all_slow(const wchar_t *path_name);

        std::vector<WIN32_FIND_DATAA> ls_detail(const char *path_name);

        std::vector<WIN32_FIND_DATAW> ls_detail(const wchar_t *path_name);

        std::vector<std::string> ls(const char *path_name);

        std::vector<std::wstring> ls(const wchar_t *path_name);

        std::vector<std::string> ls_full_path(const char *path_name);

        std::vector<std::wstring> ls_full_path(const wchar_t *path_name);

        std::vector<std::string> ls_all_files(const char *path_name);

        std::vector<std::wstring> ls_all_files(const wchar_t *path_name);

        std::vector<std::string> ls_all_dirs(const char *path_name);

        std::vector<std::wstring> ls_all_dirs(const wchar_t *path_name);

        bool copy(const char *existing_file_name,
                  const char *new_file_name,
                  bool fail_if_exists = false);

        bool copy(const wchar_t *existing_file_name,
                  const wchar_t *new_file_name,
                  bool fail_if_exists = false);

        bool copy_all(const char *existing_path_name,
                      const char *new_path_name);

        bool copy_all(const wchar_t *existing_path_name,
                      const wchar_t *new_path_name);

        bool rename(const char *existing_file_name, const char *new_file_name);

        bool rename(const wchar_t *existing_file_name,
                    const wchar_t *new_file_name);

        bool replace(const char *existing_file_name, const char *new_file_name);

        bool replace(const wchar_t *existing_file_name,
                     const wchar_t *new_file_name);

        [[nodiscard]] uint32_t err_code() const;

        [[nodiscard]] std::string err_string() const;

        [[nodiscard]] std::wstring err_wstring() const;
    };
} // namespace YanLib::io
#endif // FSANDFSUTIL_H
