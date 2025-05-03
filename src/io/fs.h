//
// Created by forkernel on 2025/4/3.
//

#ifndef DIRECTORY_H
#define DIRECTORY_H
#include <Windows.h>
#include <vector>
#include <string>
#include <algorithm>
#include "sync/rwlock.h"

namespace YanLib::io {
    class fs {
    private:
        std::vector<HANDLE> file_handles = {};
        sync::rwlock rwlock = {};
        DWORD error_code = 0;

        static inline void remove_tail_slash(std::wstring &path);

    public:
        fs(const fs &other) = delete;

        fs(fs &&other) = delete;

        fs &operator=(const fs &other) = delete;

        fs &operator=(fs &&other) = delete;

        fs() = default;

        ~fs();

        HANDLE open(const wchar_t *file_name,
                    DWORD desired_access = GENERIC_READ | GENERIC_WRITE,
                    DWORD share_mode = FILE_SHARE_READ | FILE_SHARE_WRITE,
                    SECURITY_ATTRIBUTES *security_attrs = nullptr,
                    DWORD creation_disposition = OPEN_EXISTING,
                    DWORD flags_and_attrs = FILE_ATTRIBUTE_NORMAL,
                    HANDLE template_file = nullptr);

        HANDLE create(const wchar_t *file_name,
                      DWORD desired_access = GENERIC_READ | GENERIC_WRITE,
                      DWORD share_mode = FILE_SHARE_READ | FILE_SHARE_WRITE,
                      SECURITY_ATTRIBUTES *security_attrs = nullptr,
                      DWORD creation_disposition = CREATE_ALWAYS,
                      DWORD flags_and_attrs = FILE_ATTRIBUTE_NORMAL,
                      HANDLE template_file = nullptr);

        HANDLE touch(const wchar_t *file_name);

        bool read(HANDLE file_handle,
                  void *buf,
                  DWORD size,
                  DWORD* ret_size,
                  OVERLAPPED *overlapped = nullptr);

        typedef LPOVERLAPPED_COMPLETION_ROUTINE OVERLAPPED_COMPLETION_ROUTINE;

        bool read(HANDLE file_handle,
                  void *buf,
                  DWORD size,
                  OVERLAPPED *overlapped,
                  OVERLAPPED_COMPLETION_ROUTINE completion_routine);

        bool write(HANDLE file_handle,
                   const void *buf,
                   DWORD size,
                   DWORD* ret_size,
                   OVERLAPPED *overlapped = nullptr);

        bool write(HANDLE file_handle,
                   const void *buf,
                   DWORD size,
                   OVERLAPPED *overlapped,
                   OVERLAPPED_COMPLETION_ROUTINE completion_routine);


        std::vector<uint8_t> read_bytes(HANDLE file_handle,
                                        int32_t buffer_size = 1024);

        std::string read_string(HANDLE file_handle,
                                int32_t buffer_size = 1024);

        std::wstring read_wstring(HANDLE file_handle,
                                  int32_t buffer_size = 512);

        std::vector<uint8_t> read_bytes_to_end(HANDLE file_handle);

        std::string read_string_to_end(HANDLE file_handle);

        std::wstring read_wstring_to_end(HANDLE file_handle);

        DWORD write_bytes(HANDLE file_handle,
                          const std::vector<uint8_t> &vec);

        DWORD write_string(HANDLE file_handle,
                           const std::string &str);

        DWORD write_wstring(HANDLE file_handle,
                            const std::wstring &wstr);

        int64_t seek(HANDLE file_handle,
                     int64_t offset,
                     DWORD move_method = FILE_CURRENT);

        bool truncate(HANDLE file_handle);

        bool lock(HANDLE file_handle,
                  uint64_t offset = 0,
                  uint64_t range = UINT64_MAX);

        bool lock_async(HANDLE file_handle,
                        DWORD flag = LOCKFILE_EXCLUSIVE_LOCK,
                        uint64_t range = UINT64_MAX,
                        OVERLAPPED *overlapped = nullptr,
                        DWORD reserved = 0);

        bool unlock(HANDLE file_handle,
                    uint64_t offset = 0,
                    uint64_t range = UINT64_MAX);

        bool unlock_async(HANDLE file_handle,
                          uint64_t range = UINT64_MAX,
                          OVERLAPPED *overlapped = nullptr,
                          DWORD reserved = 0);

        bool is_exists(const wchar_t *path_name);

        bool get_info(HANDLE file_handle,
                      FILE_INFO_BY_HANDLE_CLASS file_info_class,
                      void *file_info,
                      DWORD file_info_size);

        bool set_info(HANDLE file_handle,
                      FILE_INFO_BY_HANDLE_CLASS file_info_class,
                      void *file_info,
                      DWORD file_info_size);

        bool set_io_overlapped_range(HANDLE file_handle,
                                     uint8_t *overlapped_range_start,
                                     ULONG length);

        struct VolumeInfo {
            wchar_t volume_name[MAX_PATH + 1];
            wchar_t file_system_name[MAX_PATH + 1];
            DWORD serial_number;
            DWORD file_system_flag;
        };

        bool get_volume_info(HANDLE file_handle, VolumeInfo *volume_info);

        std::wstring get_final_path_name(HANDLE file_handle,
                                         DWORD flag = FILE_NAME_NORMALIZED);

        bool is_short_name_enabled(HANDLE file_handle);

        bool monitor_dir_change(HANDLE dir_handle,
                                void *buffer,
                                DWORD buffer_length,
                                bool is_watch_subtree,
                                DWORD notify_filter,
                                DWORD* bytes_returned,
                                OVERLAPPED *overlapped,
                                OVERLAPPED_COMPLETION_ROUTINE completion_routine);

        DWORD file_type(HANDLE file_handle);

        int64_t size(HANDLE file_handle);

        DWORD get_attr(const wchar_t *file_name);

        bool set_attr(const wchar_t *file_name, DWORD attr);

        UINT get_drive_type(const wchar_t *path_name);

        std::wstring get_volume_path_name(const wchar_t *file_name);

        std::wstring get_volume_path_names_for_volume_name(
            const wchar_t *volume_name);

        std::wstring get_volume_name_for_volume_mount_point(
            const wchar_t *volume_mount_point);

        bool delete_volume_mount_point(const wchar_t *volume_mount_point);

        std::wstring get_temp_path();

        std::wstring get_temp_file_name(const wchar_t *path_name,
                                        const wchar_t *prefix = nullptr,
                                        UINT unique = 0);

        std::wstring get_short_path_name(const wchar_t *long_path);

        std::wstring get_long_path_name(const wchar_t *short_path);

        std::wstring get_logical_drive_strings();

        DWORD get_logica_drives();

        std::wstring get_full_path_name(const wchar_t *file_name);

        bool get_disk_space_info(const wchar_t *root_path,
                                 DISK_SPACE_INFORMATION *disk_space_info);

        struct DiskFreeSpace4 {
            DWORD sectors_per_cluster;
            DWORD bytes_per_sector;
            DWORD number_of_free_clusters;
            DWORD total_number_of_clusters;
        };

        bool get_disk_free_space(const wchar_t *root_path_name,
                                 DiskFreeSpace4 *disk_free_space4);

        struct DiskFreeSpace3 {
            uint64_t free_bytes_available_to_caller;
            uint64_t total_number_of_bytes;
            uint64_t total_number_of_free_bytes;
        };

        bool get_disk_free_space(const wchar_t *directory_name,
                                 DiskFreeSpace3 *disk_free_space3);

        int64_t get_compressed_file_size(const wchar_t *file_name);

        std::wstring get_dos_device(const wchar_t *device_name);

        std::vector<std::wstring> get_dos_device();

        bool control_dos_device(const wchar_t *device_name,
                                const wchar_t *target_path,
                                DWORD flag);

        static std::vector<std::wstring> ls_volume_name();

        static std::vector<std::wstring> ls_device_name();

        static std::vector<WIN32_FIND_STREAM_DATA> ls_stream_data(
            const wchar_t *file_name);

        static bool rm_file(const wchar_t *file_name);

        static bool is_file(const wchar_t *file_name);

        static bool is_dir(const wchar_t *path_name);

        static bool mkdir(const wchar_t *path_name,
                          SECURITY_ATTRIBUTES *security_attrs = nullptr);

        static bool mkdir_all(const wchar_t *path_name,
                              SECURITY_ATTRIBUTES *security_attrs = nullptr);

        static bool rm_dir(const wchar_t *path_name);

        static bool rm_dir_all(const wchar_t *path_name);

        static void rm_dir_all_slow(const wchar_t *path_name);

        static std::vector<WIN32_FIND_DATAW> ls_detail(const wchar_t *path_name);

        static std::vector<std::wstring> ls(const wchar_t *path_name);

        static std::vector<std::wstring> ls_full_path(const wchar_t *path_name);

        static std::vector<std::wstring> ls_all_files(const wchar_t *path_name);

        static std::vector<std::wstring> ls_all_dirs(const wchar_t *path_name);

        static bool copy(const wchar_t *existing_file_name,
                         const wchar_t *new_file_name,
                         bool fail_if_exists = false);

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
