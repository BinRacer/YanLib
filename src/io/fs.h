//
// Created by forkernel on 2025/4/3.
//

#ifndef FSANDFSUTIL_H
#define FSANDFSUTIL_H
#include <Windows.h>
#include <vector>
#include <string>
#include <algorithm>

namespace YanLib::io {
    enum class DesiredAccess : unsigned long {
        NONE = 0,
        READ = GENERIC_READ,
        WRITE = GENERIC_WRITE,
        READ_WRITE = GENERIC_READ | GENERIC_WRITE,
        EXECUTE = GENERIC_EXECUTE,
        READ_EXECUTE = GENERIC_READ | GENERIC_EXECUTE,
        WRITE_EXECUTE = GENERIC_WRITE | GENERIC_EXECUTE,
        READ_WRITE_EXECUTE = GENERIC_READ | GENERIC_WRITE | GENERIC_EXECUTE,
        ALL = GENERIC_ALL,
    };

    enum class ShareMode : unsigned long {
        NONE = 0,
        READ = FILE_SHARE_READ,
        WRITE = FILE_SHARE_WRITE,
        READ_WRITE = FILE_SHARE_READ | FILE_SHARE_WRITE,
        ON_DELETE = FILE_SHARE_DELETE,
        READ_DELETE = FILE_SHARE_READ | FILE_SHARE_DELETE,
        WRITE_DELETE = FILE_SHARE_WRITE | FILE_SHARE_DELETE,
        READ_WRITE_DELETE = FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
    };

    enum class CreationDisposition : unsigned long {
        FILE_CREATE_NEW = CREATE_NEW,
        FILE_CREATE_ALWAYS = CREATE_ALWAYS,
        FILE_OPEN_EXISTING = OPEN_EXISTING,
        FILE_OPEN_ALWAYS = OPEN_ALWAYS,
        FILE_TRUNCATE_EXISTING = TRUNCATE_EXISTING,
    };

    enum class MoveMethod : unsigned long {
        BEGIN = FILE_BEGIN,
        CURRENT = FILE_CURRENT,
        END = FILE_END,
    };

    enum class LockMode : unsigned long {
        EXCLUSIVE_LOCK = LOCKFILE_EXCLUSIVE_LOCK,
        TRY_EXCLUSIVE_LOCK = LOCKFILE_EXCLUSIVE_LOCK | LOCKFILE_FAIL_IMMEDIATELY,
    };

    struct VolumeInfoA {
        char volume_name[MAX_PATH + 1];
        char file_system_name[MAX_PATH + 1];
        unsigned long serial_number;
        unsigned long file_system_flag;
    };

    struct VolumeInfoW {
        wchar_t volume_name[MAX_PATH + 1];
        wchar_t file_system_name[MAX_PATH + 1];
        unsigned long serial_number;
        unsigned long file_system_flag;
    };

    struct DiskFreeSpace4 {
        unsigned long sectors_per_cluster;
        unsigned long bytes_per_sector;
        unsigned long number_of_free_clusters;
        unsigned long total_number_of_clusters;
    };

    struct DiskFreeSpace3 {
        uint64_t free_bytes_available_to_caller;
        uint64_t total_number_of_bytes;
        uint64_t total_number_of_free_bytes;
    };

    class fs {
    private:
        HANDLE file_handle = INVALID_HANDLE_VALUE;
        volatile bool is_open_failed = false;
        unsigned long error_code = 0;

        static inline void remove_tail_slash(std::string &path);

        static inline void remove_tail_slash(std::wstring &path);

    public:
        fs(const fs &other) = delete;

        fs(fs &&other) = delete;

        fs &operator=(const fs &other) = delete;

        fs &operator=(fs &&other) = delete;

        fs() = delete;

        explicit fs(const char *file_name,
                    DesiredAccess desired_access = DesiredAccess::READ_WRITE,
                    ShareMode share_mode = ShareMode::READ_WRITE,
                    SECURITY_ATTRIBUTES *security_attrs = nullptr,
                    CreationDisposition creation_disposition =
                            CreationDisposition::FILE_OPEN_EXISTING,
                    unsigned long flags_and_attrs = FILE_ATTRIBUTE_NORMAL,
                    HANDLE template_file = nullptr);

        explicit fs(const wchar_t *file_name,
                    DesiredAccess desired_access = DesiredAccess::READ_WRITE,
                    ShareMode share_mode = ShareMode::READ_WRITE,
                    SECURITY_ATTRIBUTES *security_attrs = nullptr,
                    CreationDisposition creation_disposition =
                            CreationDisposition::FILE_OPEN_EXISTING,
                    unsigned long flags_and_attrs = FILE_ATTRIBUTE_NORMAL,
                    HANDLE template_file = nullptr);

        ~fs();

        [[nodiscard]] bool is_ok() const;

        bool read(void *buf,
                  unsigned long size,
                  unsigned long *bytes_read,
                  OVERLAPPED *overlapped = nullptr);

        typedef LPOVERLAPPED_COMPLETION_ROUTINE OVERLAPPED_COMPLETION_ROUTINE;

        bool read(void *buf,
                  unsigned long size,
                  OVERLAPPED *overlapped,
                  OVERLAPPED_COMPLETION_ROUTINE completion_routine);

        bool write(const void *buf,
                   unsigned long size,
                   unsigned long *bytes_written,
                   OVERLAPPED *overlapped = nullptr);

        bool write(const void *buf,
                   unsigned long size,
                   OVERLAPPED *overlapped,
                   OVERLAPPED_COMPLETION_ROUTINE completion_routine);


        std::vector<uint8_t> read_bytes(int32_t buffer_size = 1024);

        std::string read_string(int32_t buffer_size = 1024);

        std::vector<uint8_t> read_bytes_to_end();

        std::string read_string_to_end();

        unsigned long write_bytes(const std::vector<uint8_t> &data);

        unsigned long write_string(const std::string &data);

        int64_t seek(int64_t offset,
                     MoveMethod move_method = MoveMethod::CURRENT);

        bool truncate();

        bool lock(uint64_t offset = 0,
                  uint64_t range = UINT64_MAX);

        bool lock_async(LockMode lock_mode = LockMode::EXCLUSIVE_LOCK,
                        uint64_t range = UINT64_MAX,
                        OVERLAPPED *overlapped = nullptr);

        bool unlock(uint64_t offset = 0,
                    uint64_t range = UINT64_MAX);

        bool unlock_async(uint64_t range = UINT64_MAX,
                          OVERLAPPED *overlapped = nullptr);

        bool get_info(FILE_INFO_BY_HANDLE_CLASS file_info_class,
                      void *file_info,
                      unsigned long file_info_size);

        bool set_info(FILE_INFO_BY_HANDLE_CLASS file_info_class,
                      void *file_info,
                      unsigned long file_info_size);

        bool set_io_overlapped_range(uint8_t *overlapped_range_start,
                                     unsigned long length);

        bool get_volume_info(VolumeInfoA *volume_info);

        bool get_volume_info(VolumeInfoW *volume_info);

        std::string get_final_path_name(
            unsigned long flag = FILE_NAME_NORMALIZED);

        std::wstring get_final_path_name_wide(
            unsigned long flag = FILE_NAME_NORMALIZED);

        bool is_short_name_enabled();

        bool monitor_dir_change(void *buffer,
                                unsigned long buffer_length,
                                bool is_watch_subtree,
                                unsigned long notify_filter,
                                unsigned long *bytes_returned,
                                OVERLAPPED *overlapped,
                                OVERLAPPED_COMPLETION_ROUTINE completion_routine);

        unsigned long file_type();

        int64_t size();

        [[nodiscard]] unsigned long err_code() const;

        [[nodiscard]] std::string err_string() const;

        [[nodiscard]] std::wstring err_wstring() const;
    };

    class fs_util {
    private:
        unsigned long error_code = 0;

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
                   DesiredAccess desired_access = DesiredAccess::READ_WRITE,
                   ShareMode share_mode = ShareMode::READ_WRITE,
                   SECURITY_ATTRIBUTES *security_attrs = nullptr,
                   CreationDisposition creation_disposition =
                           CreationDisposition::FILE_CREATE_NEW,
                   unsigned long flags_and_attrs = FILE_ATTRIBUTE_NORMAL,
                   HANDLE template_file = nullptr);

        bool touch(const wchar_t *file_name,
                   DesiredAccess desired_access = DesiredAccess::READ_WRITE,
                   ShareMode share_mode = ShareMode::READ_WRITE,
                   SECURITY_ATTRIBUTES *security_attrs = nullptr,
                   CreationDisposition creation_disposition =
                           CreationDisposition::FILE_CREATE_NEW,
                   unsigned long flags_and_attrs = FILE_ATTRIBUTE_NORMAL,
                   HANDLE template_file = nullptr);

        bool is_exists(const char *path_name);

        bool is_exists(const wchar_t *path_name);

        unsigned long get_attr(const char *file_name);

        unsigned long get_attr(const wchar_t *file_name);

        bool set_attr(const char *file_name, unsigned long attr);

        bool set_attr(const wchar_t *file_name, unsigned long attr);

        uint32_t get_drive_type(const char *path_name);

        uint32_t get_drive_type(const wchar_t *path_name);

        std::string get_volume_path_name(const char *file_name);

        std::wstring get_volume_path_name(const wchar_t *file_name);

        std::string get_volume_path_names_for_volume_name(
            const char *volume_name);

        std::wstring get_volume_path_names_for_volume_name(
            const wchar_t *volume_name);

        std::string get_volume_name_for_volume_mount_point(
            const char *volume_mount_point);

        std::wstring get_volume_name_for_volume_mount_point(
            const wchar_t *volume_mount_point);

        bool delete_volume_mount_point(const char *volume_mount_point);

        bool delete_volume_mount_point(const wchar_t *volume_mount_point);

        std::string get_temp_path();

        std::wstring get_temp_path_wide();

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

        std::string get_logical_drive_strings();

        std::wstring get_logical_drive_strings_wide();

        unsigned long get_logica_drives();

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

        std::vector<std::string> get_dos_device();

        std::vector<std::wstring> get_dos_device_wide();

        bool control_dos_device(const char *device_name,
                                const char *target_path,
                                unsigned long flag);

        bool control_dos_device(const wchar_t *device_name,
                                const wchar_t *target_path,
                                unsigned long flag);

        std::vector<std::string> ls_volume_name();

        std::vector<std::wstring> ls_volume_name_wide();

        std::vector<std::string> ls_device_name();

        std::vector<std::wstring> ls_device_name_wide();

        std::vector<WIN32_FIND_STREAM_DATA> ls_stream_data(
            const char *file_name);

        std::vector<WIN32_FIND_STREAM_DATA> ls_stream_data(
            const wchar_t *file_name);

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

        bool rename(const char *existing_file_name,
                    const char *new_file_name);

        bool rename(const wchar_t *existing_file_name,
                    const wchar_t *new_file_name);

        bool replace(const char *existing_file_name,
                     const char *new_file_name);

        bool replace(const wchar_t *existing_file_name,
                     const wchar_t *new_file_name);

        [[nodiscard]] unsigned long err_code() const;

        [[nodiscard]] std::string err_string() const;

        [[nodiscard]] std::wstring err_wstring() const;
    };
}
#endif //FSANDFSUTIL_H
