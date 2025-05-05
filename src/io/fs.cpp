//
// Created by forkernel on 2025/4/3.
//

#include "fs.h"
#include "helper/convert.h"
#include <shlwapi.h>

#pragma comment(lib, "shlwapi.lib")

namespace YanLib::io {
    void fs::remove_tail_slash(std::wstring &path) {
        std::transform(path.begin(),
                       path.end(),
                       path.begin(),
                       [](const wchar_t ch) {
                           return (ch == L'/') ? L'\\' : ch;
                       });
        if (path.back() == L'\\') {
            path.pop_back();
        }
    }

    fs::~fs() {
        if (!file_handles.empty()) {
            for (auto &file_handle: file_handles) {
                CloseHandle(file_handle);
                file_handle = INVALID_HANDLE_VALUE;
            }
            file_handles.clear();
        }
    }

    HANDLE fs::open(const wchar_t *file_name,
                    unsigned long desired_access,
                    unsigned long share_mode,
                    SECURITY_ATTRIBUTES *security_attrs,
                    unsigned long creation_disposition,
                    unsigned long flags_and_attrs,
                    HANDLE template_file) {
        HANDLE file_handle = CreateFileW(file_name,
                                         desired_access,
                                         share_mode,
                                         security_attrs,
                                         creation_disposition,
                                         flags_and_attrs,
                                         template_file);
        if (file_handle == INVALID_HANDLE_VALUE) {
            error_code = GetLastError();
            return nullptr;
        }
        rwlock.write_lock();
        file_handles.push_back(file_handle);
        rwlock.write_unlock();
        return file_handle;
    }

    HANDLE fs::create(const wchar_t *file_name,
                      unsigned long desired_access,
                      unsigned long share_mode,
                      SECURITY_ATTRIBUTES *security_attrs,
                      unsigned long creation_disposition,
                      unsigned long flags_and_attrs,
                      HANDLE template_file) {
        HANDLE file_handle = CreateFileW(file_name,
                                         desired_access,
                                         share_mode,
                                         security_attrs,
                                         creation_disposition,
                                         flags_and_attrs,
                                         template_file);
        if (file_handle == INVALID_HANDLE_VALUE) {
            error_code = GetLastError();
            return nullptr;
        }
        rwlock.write_lock();
        file_handles.push_back(file_handle);
        rwlock.write_unlock();
        return file_handle;
    }

    HANDLE fs::touch(const wchar_t *file_name) {
        HANDLE file_handle = CreateFileW(file_name,
                                         GENERIC_READ | GENERIC_WRITE,
                                         FILE_SHARE_READ | FILE_SHARE_WRITE,
                                         nullptr,
                                         CREATE_NEW,
                                         FILE_ATTRIBUTE_NORMAL,
                                         nullptr);
        if (file_handle == INVALID_HANDLE_VALUE) {
            error_code = GetLastError();
            return nullptr;
        }
        rwlock.write_lock();
        file_handles.push_back(file_handle);
        rwlock.write_unlock();
        return file_handle;
    }

    bool fs::read(HANDLE file_handle,
                  void *buf,
                  unsigned long size,
                  unsigned long *ret_size,
                  OVERLAPPED *overlapped) {
        if (!ReadFile(file_handle,
                      buf,
                      size,
                      ret_size,
                      overlapped)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool fs::read(HANDLE file_handle,
                  void *buf,
                  unsigned long size,
                  OVERLAPPED *overlapped,
                  OVERLAPPED_COMPLETION_ROUTINE completion_routine) {
        if (!ReadFileEx(file_handle,
                        buf,
                        size,
                        overlapped,
                        completion_routine)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool fs::write(HANDLE file_handle,
                   const void *buf,
                   unsigned long size,
                   unsigned long *ret_size,
                   OVERLAPPED *overlapped) {
        if (!WriteFile(file_handle,
                       buf,
                       size,
                       ret_size,
                       overlapped)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool fs::write(HANDLE file_handle,
                   const void *buf,
                   unsigned long size,
                   OVERLAPPED *overlapped,
                   OVERLAPPED_COMPLETION_ROUTINE completion_routine) {
        if (!WriteFileEx(file_handle,
                         buf,
                         size,
                         overlapped,
                         completion_routine)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    std::vector<uint8_t> fs::read_bytes(HANDLE file_handle,
                                        int32_t buffer_size) {
        if (buffer_size <= 0) {
            buffer_size = 1;
        }
        std::vector<uint8_t> raw_data(buffer_size, '\0');
        unsigned long bytes_read = 0;
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

    std::string fs::read_string(HANDLE file_handle,
                                int32_t buffer_size) {
        if (buffer_size <= 0) {
            buffer_size = 1;
        }
        std::string raw_data(buffer_size, '\0');
        unsigned long bytes_read = 0;
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

    std::wstring fs::read_wstring(HANDLE file_handle,
                                  int32_t buffer_size) {
        if (buffer_size <= 0) {
            buffer_size = 1;
        }
        std::wstring raw_data(buffer_size, L'\0');
        unsigned long bytes_read = 0;
        if (ReadFile(
                file_handle,
                raw_data.data(),
                buffer_size * sizeof(wchar_t),
                &bytes_read,
                nullptr) && bytes_read > 0) {
            raw_data.resize(bytes_read / sizeof(wchar_t));
            raw_data.shrink_to_fit();
            return raw_data;
        }
        error_code = GetLastError();
        return {};
    }

    std::vector<uint8_t> fs::read_bytes_to_end(HANDLE file_handle) {
        constexpr unsigned long buffer_size = 4096;
        uint8_t *buf = new uint8_t[buffer_size];
        memset(buf, 0, buffer_size);
        std::vector<uint8_t> raw_data;
        raw_data.reserve(buffer_size);
        unsigned long bytes_read = 0;
        bool ret = false;
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

    std::string fs::read_string_to_end(HANDLE file_handle) {
        constexpr unsigned long buffer_size = 4096;
        char *buf = new char[buffer_size];
        memset(buf, 0, buffer_size);
        std::string raw_data;
        raw_data.reserve(buffer_size);
        unsigned long bytes_read = 0;
        bool ret = false;
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

    std::wstring fs::read_wstring_to_end(HANDLE file_handle) {
        constexpr unsigned long buffer_size = 2048;
        wchar_t *buf = new wchar_t[buffer_size];
        memset(buf, 0, buffer_size * sizeof(wchar_t));
        std::wstring raw_data;
        raw_data.reserve(buffer_size);
        unsigned long bytes_read = 0;
        bool ret = false;
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
                                buf + (bytes_read / sizeof(wchar_t)));
            } else {
                error_code = GetLastError();
            }
        } while (ret && bytes_read > 0);
        delete[] buf;
        raw_data.shrink_to_fit();
        return raw_data;
    }

    unsigned long fs::write_bytes(HANDLE file_handle,
                                  const std::vector<uint8_t> &vec) {
        if (vec.empty()) {
            return 0;
        }
        unsigned long bytes_written = 0;
        if (!WriteFile(file_handle,
                       vec.data(),
                       vec.size(),
                       &bytes_written,
                       nullptr)) {
            error_code = GetLastError();
        }
        return bytes_written;
    }

    unsigned long fs::write_string(HANDLE file_handle,
                                   const std::string &str) {
        if (str.empty()) {
            return 0;
        }
        unsigned long bytes_written = 0;
        if (!WriteFile(file_handle,
                       str.data(),
                       str.size(),
                       &bytes_written,
                       nullptr)) {
            error_code = GetLastError();
        }
        return bytes_written;
    }

    unsigned long fs::write_wstring(HANDLE file_handle,
                                    const std::wstring &wstr) {
        if (wstr.empty()) {
            return 0;
        }
        unsigned long bytes_written = 0;
        if (!WriteFile(file_handle,
                       wstr.data(),
                       wstr.size() * sizeof(wchar_t),
                       &bytes_written,
                       nullptr)) {
            error_code = GetLastError();
        }
        return bytes_written / sizeof(wchar_t);
    }

    int64_t fs::seek(HANDLE file_handle,
                     int64_t offset,
                     unsigned long move_method) {
        LARGE_INTEGER move = {};
        move.QuadPart = offset;
        LARGE_INTEGER new_pos = {};
        if (!SetFilePointerEx(file_handle,
                              move,
                              &new_pos,
                              move_method)) {
            error_code = GetLastError();
            return 0;
        }
        return new_pos.QuadPart;
    }

    bool fs::truncate(HANDLE file_handle) {
        if (!SetEndOfFile(file_handle)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool fs::lock(HANDLE file_handle,
                  uint64_t offset,
                  uint64_t range) {
        auto offset_low = static_cast<unsigned long>(offset & 0xFFFFFFFF);
        auto offset_high = static_cast<unsigned long>(offset >> 32);
        auto range_low = static_cast<unsigned long>(range & 0xFFFFFFFF);
        auto range_high = static_cast<unsigned long>(range >> 32);
        if (!LockFile(file_handle,
                      offset_low,
                      offset_high,
                      range_low,
                      range_high)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool fs::lock_async(HANDLE file_handle,
                        unsigned long flag,
                        uint64_t range,
                        OVERLAPPED *overlapped,
                        unsigned long reserved) {
        auto low = static_cast<unsigned long>(range & 0xFFFFFFFF);
        auto high = static_cast<unsigned long>(range >> 32);
        if (!LockFileEx(file_handle,
                        flag,
                        reserved,
                        low,
                        high,
                        overlapped)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool fs::unlock(HANDLE file_handle,
                    uint64_t offset,
                    uint64_t range) {
        auto offset_low = static_cast<unsigned long>(offset & 0xFFFFFFFF);
        auto offset_high = static_cast<unsigned long>(offset >> 32);
        auto range_low = static_cast<unsigned long>(range & 0xFFFFFFFF);
        auto range_high = static_cast<unsigned long>(range >> 32);
        if (!UnlockFile(file_handle,
                        offset_low,
                        offset_high,
                        range_low,
                        range_high)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool fs::unlock_async(HANDLE file_handle,
                          uint64_t range,
                          OVERLAPPED *overlapped,
                          unsigned long reserved) {
        auto low = static_cast<unsigned long>(range & 0xFFFFFFFF);
        auto high = static_cast<unsigned long>(range >> 32);
        if (!UnlockFileEx(file_handle,
                          reserved,
                          low,
                          high,
                          overlapped)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool fs::is_exists(const wchar_t *path_name) {
        if (!PathFileExistsW(path_name)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool fs::get_info(HANDLE file_handle,
                      FILE_INFO_BY_HANDLE_CLASS file_info_class,
                      void *file_info,
                      unsigned long file_info_size) {
        if (!GetFileInformationByHandleEx(file_handle,
                                          file_info_class,
                                          file_info,
                                          file_info_size)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool fs::set_info(HANDLE file_handle,
                      FILE_INFO_BY_HANDLE_CLASS file_info_class,
                      void *file_info,
                      unsigned long file_info_size) {
        if (!SetFileInformationByHandle(file_handle,
                                        file_info_class,
                                        file_info,
                                        file_info_size)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool fs::set_io_overlapped_range(HANDLE file_handle,
                                     uint8_t *overlapped_range_start,
                                     unsigned long length) {
        if (!SetFileIoOverlappedRange(file_handle,
                                      overlapped_range_start,
                                      length)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool fs::get_volume_info(HANDLE file_handle,
                             VolumeInfo *volume_info) {
        memset(volume_info, 0, size(volume_info));
        unsigned long size = 0;
        if (!GetVolumeInformationByHandleW(file_handle,
                                           volume_info->volume_name,
                                           MAX_PATH,
                                           &(volume_info->serial_number),
                                           &size,
                                           &(volume_info->file_system_flag),
                                           volume_info->file_system_name,
                                           MAX_PATH)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    std::wstring fs::get_final_path_name(HANDLE file_handle,
                                         unsigned long flag) {
        unsigned long size = GetFinalPathNameByHandleW(file_handle,
                                                       nullptr,
                                                       0,
                                                       flag);
        std::wstring buffer(size, L'\0');
        size = GetFinalPathNameByHandleW(file_handle,
                                         buffer.data(),
                                         buffer.size(),
                                         flag);
        if (!size) {
            error_code = GetLastError();
            return {};
        }
        buffer.resize(size);
        while (buffer.back() == L'\0') {
            buffer.pop_back();
        }
        return buffer;
    }

    bool fs::is_short_name_enabled(HANDLE file_handle) {
        int is_ok = 0;
        if (!AreShortNamesEnabled(file_handle, &is_ok)) {
            error_code = GetLastError();
        }
        return is_ok;
    }

    bool fs::monitor_dir_change(HANDLE dir_handle,
                                void *buffer,
                                unsigned long buffer_length,
                                bool is_watch_subtree,
                                unsigned long notify_filter,
                                unsigned long *bytes_returned,
                                OVERLAPPED *overlapped,
                                OVERLAPPED_COMPLETION_ROUTINE completion_routine) {
        if (!ReadDirectoryChangesW(dir_handle,
                                   buffer,
                                   buffer_length,
                                   is_watch_subtree ? TRUE : FALSE,
                                   notify_filter,
                                   bytes_returned,
                                   overlapped,
                                   completion_routine)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    unsigned long fs::file_type(HANDLE file_handle) {
        unsigned long ret = GetFileType(file_handle);
        if (ret == FILE_TYPE_UNKNOWN) {
            error_code = GetLastError();
        }
        return ret;
    }

    int64_t fs::size(HANDLE file_handle) {
        LARGE_INTEGER file_size{};
        if (!GetFileSizeEx(file_handle, &file_size)) {
            error_code = GetLastError();
        }
        return file_size.QuadPart;
    }

    unsigned long fs::get_attr(const wchar_t *file_name) {
        unsigned long attr = GetFileAttributesW(file_name);
        if (attr == INVALID_FILE_ATTRIBUTES) {
            error_code = GetLastError();
            return 0;
        }
        return attr;
    }

    bool fs::set_attr(const wchar_t *file_name, unsigned long attr) {
        if (!SetFileAttributesW(file_name, attr)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    unsigned int fs::get_drive_type(const wchar_t *path_name) {
        return GetDriveTypeW(path_name);
    }

    std::wstring fs::get_volume_path_name(const wchar_t *file_name) {
        std::wstring buffer(MAX_PATH + 1, L'\0');
        if (!GetVolumePathNameW(file_name,
                                buffer.data(),
                                MAX_PATH)) {
            error_code = GetLastError();
            return {};
        }
        while (buffer.back() == L'\0') {
            buffer.pop_back();
        }
        return buffer;
    }

    std::wstring fs::get_volume_path_names_for_volume_name(
        const wchar_t *volume_name) {
        unsigned long size = 0;
        if (!GetVolumePathNamesForVolumeNameW(volume_name,
                                              nullptr,
                                              0,
                                              &size)) {
            if (GetLastError() == ERROR_MORE_DATA) {
                std::wstring buffer(size, L'\0');
                if (!GetVolumePathNamesForVolumeNameW(volume_name,
                                                      buffer.data(),
                                                      buffer.size(),
                                                      &size)) {
                    error_code = GetLastError();
                    return {};
                }
                buffer.resize(size);
                while (buffer.back() == L'\0') {
                    buffer.pop_back();
                }
                return buffer;
            }
        }
        return {};
    }

    std::wstring fs::get_volume_name_for_volume_mount_point(
        const wchar_t *volume_mount_point) {
        std::wstring buffer(MAX_PATH + 1, L'\0');
        if (!GetVolumeNameForVolumeMountPointW(volume_mount_point,
                                               buffer.data(),
                                               MAX_PATH)) {
            error_code = GetLastError();
            return {};
        }
        while (buffer.back() == L'\0') {
            buffer.pop_back();
        }
        return buffer;
    }

    bool fs::delete_volume_mount_point(const wchar_t *volume_mount_point) {
        if (!DeleteVolumeMountPointW(volume_mount_point)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    std::wstring fs::get_temp_path() {
        std::wstring buffer(MAX_PATH + 1, L'\0');
        unsigned long size = GetTempPathW(MAX_PATH,
                                          buffer.data());
        if (!size) {
            error_code = GetLastError();
            return {};
        }
        buffer.resize(size);
        while (buffer.back() == L'\0') {
            buffer.pop_back();
        }
        return buffer;
    }

    std::wstring fs::get_temp_file_name(const wchar_t *path_name,
                                        const wchar_t *prefix,
                                        unsigned int unique) {
        std::wstring buffer(MAX_PATH + 1, L'\0');
        if (!GetTempFileNameW(path_name,
                              prefix,
                              unique, buffer.data())) {
            error_code = GetLastError();
            return {};
        }
        while (buffer.back() == L'\0') {
            buffer.pop_back();
        }
        return buffer;
    }

    std::wstring fs::get_short_path_name(const wchar_t *long_path) {
        unsigned long size = GetShortPathNameW(long_path,
                                               nullptr,
                                               0);
        std::wstring buffer(size, L'\0');
        size = GetShortPathNameW(long_path,
                                 buffer.data(),
                                 buffer.size());
        if (!size) {
            error_code = GetLastError();
            return {};
        }
        buffer.resize(size);
        while (buffer.back() == L'\0') {
            buffer.pop_back();
        }
        return buffer;
    }

    std::wstring fs::get_long_path_name(const wchar_t *short_path) {
        unsigned long size = GetLongPathNameW(short_path,
                                              nullptr,
                                              0);
        std::wstring buffer(size, L'\0');
        size = GetLongPathNameW(short_path,
                                buffer.data(),
                                buffer.size());
        if (!size) {
            error_code = GetLastError();
            return {};
        }
        buffer.resize(size);
        while (buffer.back() == L'\0') {
            buffer.pop_back();
        }
        return buffer;
    }

    std::wstring fs::get_logical_drive_strings() {
        unsigned long size = GetLogicalDriveStringsW(0,
                                                     nullptr);
        std::wstring buffer(size, L'\0');
        size = GetLogicalDriveStringsW(buffer.size(),
                                       buffer.data());
        if (!size) {
            error_code = GetLastError();
            return {};
        }
        buffer.resize(size);
        while (buffer.back() == L'\0') {
            buffer.pop_back();
        }
        return buffer;
    }

    unsigned long fs::get_logica_drives() {
        return GetLogicalDrives();
    }

    std::wstring fs::get_full_path_name(const wchar_t *file_name) {
        unsigned long size = GetFullPathNameW(file_name,
                                              0,
                                              nullptr,
                                              nullptr);
        std::wstring buffer(size, L'\0');
        size = GetFullPathNameW(file_name,
                                buffer.size(),
                                buffer.data(),
                                nullptr);
        if (!size) {
            error_code = GetLastError();
            return {};
        }
        buffer.resize(size);
        while (buffer.back() == L'\0') {
            buffer.pop_back();
        }
        return buffer;
    }

    bool fs::get_disk_space_info(const wchar_t *root_path,
                                 DISK_SPACE_INFORMATION *disk_space_info) {
        HRESULT is_ok = GetDiskSpaceInformationW(root_path, disk_space_info);
        if (is_ok != S_OK) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool fs::get_disk_free_space(const wchar_t *root_path_name,
                                 DiskFreeSpace4 *disk_free_space4) {
        if (!GetDiskFreeSpaceW(root_path_name,
                               &(disk_free_space4->sectors_per_cluster),
                               &(disk_free_space4->bytes_per_sector),
                               &(disk_free_space4->number_of_free_clusters),
                               &(disk_free_space4->total_number_of_clusters))) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool fs::get_disk_free_space(const wchar_t *directory_name,
                                 DiskFreeSpace3 *disk_free_space3) {
        ULARGE_INTEGER free_bytes_available_to_caller = {};
        ULARGE_INTEGER total_number_of_bytes = {};
        ULARGE_INTEGER total_number_of_free_bytes = {};
        if (!GetDiskFreeSpaceExW(directory_name,
                                 &free_bytes_available_to_caller,
                                 &total_number_of_bytes,
                                 &total_number_of_free_bytes)) {
            error_code = GetLastError();
            return false;
        }
        disk_free_space3->free_bytes_available_to_caller =
                free_bytes_available_to_caller.QuadPart;
        disk_free_space3->total_number_of_bytes =
                total_number_of_bytes.QuadPart;
        disk_free_space3->total_number_of_free_bytes =
                total_number_of_free_bytes.QuadPart;
        return true;
    }

    int64_t fs::get_compressed_file_size(const wchar_t *file_name) {
        unsigned long high = 0;
        unsigned long low = GetCompressedFileSizeW(file_name, &high);
        if (low == INVALID_FILE_SIZE) {
            error_code = GetLastError();
            if (error_code != NO_ERROR) {
                return 0;
            }
        }
        return (static_cast<int64_t>(high) << 32) | low;
    }

    std::wstring fs::get_dos_device(const wchar_t *device_name) {
        size_t buff_size = MAX_PATH;
        std::wstring buffer(buff_size + 1, L'\0');
        unsigned long size = QueryDosDeviceW(device_name,
                                             buffer.data(),
                                             MAX_PATH);
        while (!size) {
            error_code = GetLastError();
            if (error_code != ERROR_INSUFFICIENT_BUFFER) {
                return {};
            }
            buff_size = buff_size * 2;
            buffer.resize(buff_size + 1, L'\0');
            size = QueryDosDeviceW(device_name,
                                   buffer.data(),
                                   buff_size);
        }
        while (buffer.back() == L'\0') {
            buffer.pop_back();
        }
        return buffer;
    }

    std::vector<std::wstring> fs::get_dos_device() {
        size_t buff_size = 4096;
        std::wstring buffer(buff_size, L'\0');
        unsigned long size = QueryDosDeviceW(nullptr,
                                             buffer.data(),
                                             buff_size - 1);
        while (!size) {
            error_code = GetLastError();
            if (error_code != ERROR_INSUFFICIENT_BUFFER) {
                return {};
            }
            buff_size = buff_size * 2;
            buffer.resize(buff_size, L'\0');
            size = QueryDosDeviceW(nullptr,
                                   buffer.data(),
                                   buff_size - 1);
        }
        while (buffer.back() == L'\0') {
            buffer.pop_back();
        }
        std::vector<std::wstring> result;
        size_t start = 0;
        size_t end = buffer.find(L'\0');
        while (end != std::wstring::npos) {
            result.push_back(buffer.substr(start, end - start));
            start = end + 1;
            end = buffer.find(L'\0', start);
        }
        if (start < buffer.size()) {
            result.push_back(buffer.substr(start));
        }
        return result;
    }

    bool fs::control_dos_device(const wchar_t *device_name,
                                const wchar_t *target_path,
                                unsigned long flag) {
        if (!DefineDosDeviceW(flag,
                              device_name,
                              target_path)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    std::vector<std::wstring> fs::ls_volume_name() {
        do {
            std::vector<std::wstring> result;
            std::wstring volume_name(MAX_PATH + 1, L'\0');
            HANDLE file_handle = FindFirstVolumeW(volume_name.data(),
                                                  volume_name.size());
            if (file_handle == INVALID_HANDLE_VALUE) {
                break;
            }
            do {
                result.push_back(volume_name.data());
            } while (FindNextVolumeW(file_handle,
                                     volume_name.data(),
                                     volume_name.size()));
            FindVolumeClose(file_handle);
            return result;
        } while (false);
        return {};
    }

    std::vector<std::wstring> fs::ls_device_name() {
        std::vector<std::wstring> volumes = ls_volume_name();
        std::vector<std::wstring> devices;
        if (volumes.empty()) {
            return {};
        }
        for (auto volume: volumes) {
            if (volume.back() == L'\\') {
                volume.pop_back();
            }
            std::wstring device_name(MAX_PATH + 1, L'\0');
            if (!QueryDosDeviceW(volume.data() + 4,
                                 device_name.data(),
                                 device_name.size())) {
                break;
            }
            devices.push_back(device_name.data());
        }
        return devices;
    }

    std::vector<WIN32_FIND_STREAM_DATA> fs::ls_stream_data(
        const wchar_t *file_name) {
        do {
            std::vector<WIN32_FIND_STREAM_DATA> result;
            WIN32_FIND_STREAM_DATA stream_data = {};
            HANDLE file_handle = FindFirstStreamW(file_name,
                                                  FindStreamInfoStandard,
                                                  &stream_data,
                                                  0);
            if (file_handle == INVALID_HANDLE_VALUE) {
                break;
            }
            do {
                result.push_back(stream_data);
            } while (FindNextStreamW(file_handle,
                                     &stream_data));
            FindClose(file_handle);
            return result;
        } while (false);
        return {};
    }

    bool fs::rm_file(const wchar_t *file_name) {
        return DeleteFileW(file_name);
    }

    bool fs::is_file(const wchar_t *file_name) {
        const unsigned long attr = GetFileAttributesW(file_name);
        return (attr != INVALID_FILE_ATTRIBUTES) &&
               (!(attr & FILE_ATTRIBUTE_DIRECTORY));
    }

    bool fs::is_dir(const wchar_t *path_name) {
        const unsigned long attr = GetFileAttributesW(path_name);
        return (attr != INVALID_FILE_ATTRIBUTES) &&
               (attr & FILE_ATTRIBUTE_DIRECTORY);
    }

    bool fs::mkdir(const wchar_t *path_name,
                   SECURITY_ATTRIBUTES *
                   security_attrs) {
        return CreateDirectoryW(path_name, security_attrs);
    }

    bool fs::mkdir_all(const wchar_t *path_name,
                       SECURITY_ATTRIBUTES *security_attrs) {
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
        return RemoveDirectoryW(path_name);
    }

    bool fs::rm_dir_all(const wchar_t *path_name) {
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

    std::vector<WIN32_FIND_DATAW> fs::ls_detail(const wchar_t *path_name) {
        std::vector<WIN32_FIND_DATAW> result;
        std::wstring path(path_name);
        remove_tail_slash(path);
        path.append(L"\\*.*");
        WIN32_FIND_DATAW find_data;
        HANDLE find_handle = FindFirstFileW(path.data(), &find_data);
        if (find_handle == INVALID_HANDLE_VALUE) {
            return result;
        }
        do {
            if (wcscmp(find_data.cFileName, L".") != 0 &&
                wcscmp(find_data.cFileName, L"..") != 0) {
                result.emplace_back(find_data);
            }
        } while (FindNextFileW(find_handle, &find_data));
        FindClose(find_handle);
        return result;
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
                result.emplace_back(find_data.cFileName);
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

            HANDLE find_handle = FindFirstFileW(search_path.data(),
                                                &find_data);
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
                  const wchar_t *new_file_name,
                  bool fail_if_exists) {
        return CopyFileW(existing_file_name,
                         new_file_name,
                         fail_if_exists ? TRUE : FALSE);
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
                           MOVEFILE_COPY_ALLOWED |
                           MOVEFILE_WRITE_THROUGH);
    }

    bool fs::replace(const wchar_t *existing_file_name,
                     const wchar_t *new_file_name) {
        return MoveFileExW(existing_file_name,
                           new_file_name,
                           MOVEFILE_REPLACE_EXISTING |
                           MOVEFILE_WRITE_THROUGH);
    }

    unsigned long fs::err_code() const {
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
