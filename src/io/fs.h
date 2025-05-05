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
        unsigned long error_code = 0;

        static inline void remove_tail_slash(std::wstring &path);

    public:
        fs(const fs &other) = delete;

        fs(fs &&other) = delete;

        fs &operator=(const fs &other) = delete;

        fs &operator=(fs &&other) = delete;

        fs() = default;

        ~fs();

        HANDLE open(const wchar_t *file_name,
                    unsigned long desired_access = GENERIC_READ | GENERIC_WRITE,
                    unsigned long share_mode = FILE_SHARE_READ | FILE_SHARE_WRITE,
                    SECURITY_ATTRIBUTES *security_attrs = nullptr,
                    unsigned long creation_disposition = OPEN_EXISTING,
                    unsigned long flags_and_attrs = FILE_ATTRIBUTE_NORMAL,
                    HANDLE template_file = nullptr);

        HANDLE create(const wchar_t *file_name,
                      unsigned long desired_access = GENERIC_READ | GENERIC_WRITE,
                      unsigned long share_mode = FILE_SHARE_READ | FILE_SHARE_WRITE,
                      SECURITY_ATTRIBUTES *security_attrs = nullptr,
                      unsigned long creation_disposition = CREATE_ALWAYS,
                      unsigned long flags_and_attrs = FILE_ATTRIBUTE_NORMAL,
                      HANDLE template_file = nullptr);

        HANDLE touch(const wchar_t *file_name);

        bool read(HANDLE file_handle,
                  void *buf,
                  unsigned long size,
                  unsigned long* ret_size,
                  OVERLAPPED *overlapped = nullptr);

        typedef LPOVERLAPPED_COMPLETION_ROUTINE OVERLAPPED_COMPLETION_ROUTINE;

        bool read(HANDLE file_handle,
                  void *buf,
                  unsigned long size,
                  OVERLAPPED *overlapped,
                  OVERLAPPED_COMPLETION_ROUTINE completion_routine);

        bool write(HANDLE file_handle,
                   const void *buf,
                   unsigned long size,
                   unsigned long* ret_size,
                   OVERLAPPED *overlapped = nullptr);

        bool write(HANDLE file_handle,
                   const void *buf,
                   unsigned long size,
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

        unsigned long write_bytes(HANDLE file_handle,
                          const std::vector<uint8_t> &vec);

        unsigned long write_string(HANDLE file_handle,
                           const std::string &str);

        unsigned long write_wstring(HANDLE file_handle,
                            const std::wstring &wstr);

        int64_t seek(HANDLE file_handle,
                     int64_t offset,
                     unsigned long move_method = FILE_CURRENT);

        bool truncate(HANDLE file_handle);

        bool lock(HANDLE file_handle,
                  uint64_t offset = 0,
                  uint64_t range = UINT64_MAX);

        bool lock_async(HANDLE file_handle,
                        unsigned long flag = LOCKFILE_EXCLUSIVE_LOCK,
                        uint64_t range = UINT64_MAX,
                        OVERLAPPED *overlapped = nullptr,
                        unsigned long reserved = 0);

        bool unlock(HANDLE file_handle,
                    uint64_t offset = 0,
                    uint64_t range = UINT64_MAX);

        bool unlock_async(HANDLE file_handle,
                          uint64_t range = UINT64_MAX,
                          OVERLAPPED *overlapped = nullptr,
                          unsigned long reserved = 0);

        bool is_exists(const wchar_t *path_name);

        bool get_info(HANDLE file_handle,
                      FILE_INFO_BY_HANDLE_CLASS file_info_class,
                      void *file_info,
                      unsigned long file_info_size);

        bool set_info(HANDLE file_handle,
                      FILE_INFO_BY_HANDLE_CLASS file_info_class,
                      void *file_info,
                      unsigned long file_info_size);

        bool set_io_overlapped_range(HANDLE file_handle,
                                     uint8_t *overlapped_range_start,
                                     unsigned long length);

        struct VolumeInfo {
            wchar_t volume_name[MAX_PATH + 1];
            wchar_t file_system_name[MAX_PATH + 1];
            unsigned long serial_number;
            unsigned long file_system_flag;
        };

        bool get_volume_info(HANDLE file_handle, VolumeInfo *volume_info);

        std::wstring get_final_path_name(HANDLE file_handle,
                                         unsigned long flag = FILE_NAME_NORMALIZED);

        bool is_short_name_enabled(HANDLE file_handle);

        bool monitor_dir_change(HANDLE dir_handle,
                                void *buffer,
                                unsigned long buffer_length,
                                bool is_watch_subtree,
                                unsigned long notify_filter,
                                unsigned long* bytes_returned,
                                OVERLAPPED *overlapped,
                                OVERLAPPED_COMPLETION_ROUTINE completion_routine);

        unsigned long file_type(HANDLE file_handle);

        int64_t size(HANDLE file_handle);

        unsigned long get_attr(const wchar_t *file_name);

        bool set_attr(const wchar_t *file_name, unsigned long attr);

        unsigned int get_drive_type(const wchar_t *path_name);

        std::wstring get_volume_path_name(const wchar_t *file_name);

        std::wstring get_volume_path_names_for_volume_name(
            const wchar_t *volume_name);

        std::wstring get_volume_name_for_volume_mount_point(
            const wchar_t *volume_mount_point);

        bool delete_volume_mount_point(const wchar_t *volume_mount_point);

        std::wstring get_temp_path();

        std::wstring get_temp_file_name(const wchar_t *path_name,
                                        const wchar_t *prefix = nullptr,
                                        unsigned int unique = 0);

        std::wstring get_short_path_name(const wchar_t *long_path);

        std::wstring get_long_path_name(const wchar_t *short_path);

        std::wstring get_logical_drive_strings();

        unsigned long get_logica_drives();

        std::wstring get_full_path_name(const wchar_t *file_name);

        bool get_disk_space_info(const wchar_t *root_path,
                                 DISK_SPACE_INFORMATION *disk_space_info);

        struct DiskFreeSpace4 {
            unsigned long sectors_per_cluster;
            unsigned long bytes_per_sector;
            unsigned long number_of_free_clusters;
            unsigned long total_number_of_clusters;
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
                                unsigned long flag);

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

        [[nodiscard]] unsigned long err_code() const;

        [[nodiscard]] std::string err_string() const;

        [[nodiscard]] std::wstring err_wstring() const;
    };
}
#endif //DIRECTORY_H
