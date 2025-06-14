/* clang-format off */
/*
 * @file fs.cpp
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
#include "fs.h"
#include <memory>
#include <shlwapi.h>
#pragma comment(lib, "ShLwApi.Lib")

namespace YanLib::io {
    void fs::remove_tail_slash(std::string &path) {
        std::transform(path.begin(), path.end(), path.begin(),
                       [](const char ch) {
                           return (ch == '/') ? '\\' : ch;
                       });
        if (path.back() == '\\') {
            path.pop_back();
        }
    }

    void fs::remove_tail_slash(std::wstring &path) {
        std::transform(path.begin(), path.end(), path.begin(),
                       [](const wchar_t ch) {
                           return (ch == L'/') ? L'\\' : ch;
                       });
        if (path.back() == L'\\') {
            path.pop_back();
        }
    }

    fs::fs(const char *file_name,
           DesiredAccess desired_access,
           ShareMode share_mode,
           SECURITY_ATTRIBUTES *security_attrs,
           CreationDisposition creation_disposition,
           FlagAndAttr flag_and_attr,
           HANDLE template_file) {
        file_handle =
                CreateFileA(file_name, static_cast<uint32_t>(desired_access),
                            static_cast<uint32_t>(share_mode), security_attrs,
                            static_cast<uint32_t>(creation_disposition),
                            static_cast<uint32_t>(flag_and_attr),
                            template_file);
        if (file_handle == INVALID_HANDLE_VALUE) {
            error_code = GetLastError();
            is_open_failed = true;
        }
    }

    fs::fs(const wchar_t *file_name,
           DesiredAccess desired_access,
           ShareMode share_mode,
           SECURITY_ATTRIBUTES *security_attrs,
           CreationDisposition creation_disposition,
           FlagAndAttr flag_and_attr,
           HANDLE template_file) {
        file_handle =
                CreateFileW(file_name, static_cast<uint32_t>(desired_access),
                            static_cast<uint32_t>(share_mode), security_attrs,
                            static_cast<uint32_t>(creation_disposition),
                            static_cast<uint32_t>(flag_and_attr),
                            template_file);
        if (file_handle == INVALID_HANDLE_VALUE) {
            error_code = GetLastError();
            is_open_failed = true;
        }
    }

    fs::~fs() {
        if (file_handle != INVALID_HANDLE_VALUE) {
            CloseHandle(file_handle);
            file_handle = INVALID_HANDLE_VALUE;
        }
    }

    bool fs::is_ok() const {
        return !is_open_failed;
    }

    bool fs::read(void *buf,
                  uint32_t size,
                  uint32_t *bytes_read,
                  OVERLAPPED *overlapped) {
        if (!bytes_read) {
            error_code = STATUS_ACCESS_VIOLATION;
            return false;
        }
        unsigned long temp = *bytes_read;
        if (!ReadFile(file_handle, buf, size, &temp, overlapped)) {
            error_code = GetLastError();
            *bytes_read = temp;
            return false;
        }
        *bytes_read = temp;
        return true;
    }

    bool fs::read(void *buf,
                  uint32_t size,
                  OVERLAPPED *overlapped,
                  OVERLAPPED_COMPLETION_ROUTINE completion_routine) {
        if (!ReadFileEx(file_handle, buf, size, overlapped,
                        completion_routine)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool fs::write(const void *buf,
                   uint32_t size,
                   uint32_t *bytes_written,
                   OVERLAPPED *overlapped) {
        if (!bytes_written) {
            error_code = STATUS_ACCESS_VIOLATION;
            return false;
        }
        unsigned long temp = *bytes_written;
        if (!WriteFile(file_handle, buf, size, &temp, overlapped)) {
            error_code = GetLastError();
            *bytes_written = temp;
            return false;
        }
        *bytes_written = temp;
        return true;
    }

    bool fs::write(const void *buf,
                   uint32_t size,
                   OVERLAPPED *overlapped,
                   OVERLAPPED_COMPLETION_ROUTINE completion_routine) {
        if (!WriteFileEx(file_handle, buf, size, overlapped,
                         completion_routine)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    std::vector<uint8_t> fs::read_bytes(int32_t buffer_size) {
        if (buffer_size <= 0) {
            buffer_size = 1;
        }
        std::vector<uint8_t> raw_data(buffer_size, '\0');
        unsigned long bytes_read = 0;
        if (ReadFile(file_handle, raw_data.data(), buffer_size, &bytes_read,
                     nullptr) &&
            bytes_read > 0) {
            raw_data.resize(bytes_read);
            raw_data.shrink_to_fit();
            return raw_data;
        }
        error_code = GetLastError();
        return {};
    }

    std::string fs::read_string(int32_t buffer_size) {
        if (buffer_size <= 0) {
            buffer_size = 1;
        }
        std::string raw_data(buffer_size, '\0');
        unsigned long bytes_read = 0;
        if (ReadFile(file_handle, raw_data.data(), buffer_size, &bytes_read,
                     nullptr) &&
            bytes_read > 0) {
            raw_data.resize(bytes_read);
            raw_data.shrink_to_fit();
            return raw_data;
        }
        error_code = GetLastError();
        return {};
    }

    std::vector<uint8_t> fs::read_bytes_to_end() {
        std::vector<uint8_t> buf(4096, '\0');
        std::vector<uint8_t> raw_data;
        raw_data.reserve(4096);
        unsigned long bytes_read = 0;
        do {
            if (ReadFile(file_handle, buf.data(), buf.size(), &bytes_read,
                         nullptr) &&
                bytes_read > 0) {
                raw_data.insert(raw_data.end(), buf.data(),
                                buf.data() + bytes_read);
            } else {
                error_code = GetLastError();
                break;
            }
        } while (bytes_read > 0);
        raw_data.shrink_to_fit();
        return raw_data;
    }

    std::string fs::read_string_to_end() {
        std::string buf(4096, '\0');
        std::string raw_data;
        raw_data.reserve(4096);
        unsigned long bytes_read = 0;
        do {
            if (ReadFile(file_handle, buf.data(), buf.size(), &bytes_read,
                         nullptr) &&
                bytes_read > 0) {
                raw_data.insert(raw_data.end(), buf.data(),
                                buf.data() + bytes_read);
            } else {
                error_code = GetLastError();
                break;
            }
        } while (bytes_read > 0);
        raw_data.shrink_to_fit();
        return raw_data;
    }

    uint32_t fs::write_bytes(const std::vector<uint8_t> &data) {
        if (data.empty()) {
            return 0;
        }
        unsigned long bytes_written = 0;
        if (!WriteFile(file_handle, data.data(), data.size(), &bytes_written,
                       nullptr)) {
            error_code = GetLastError();
        }
        return bytes_written;
    }

    uint32_t fs::write_string(const std::string &data) {
        if (data.empty()) {
            return 0;
        }
        unsigned long bytes_written = 0;
        if (!WriteFile(file_handle, data.data(), data.size(), &bytes_written,
                       nullptr)) {
            error_code = GetLastError();
        }
        return bytes_written;
    }

    int64_t fs::seek(int64_t offset, MoveMethod move_method) {
        LARGE_INTEGER move = {};
        move.QuadPart = offset;
        LARGE_INTEGER new_pos = {};
        if (!SetFilePointerEx(file_handle, move, &new_pos,
                              static_cast<uint32_t>(move_method))) {
            error_code = GetLastError();
            return 0;
        }
        return new_pos.QuadPart;
    }

    bool fs::truncate() {
        if (!SetEndOfFile(file_handle)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool fs::lock(const uint64_t offset, const uint64_t range) {
        const auto offset_low = static_cast<uint32_t>(offset & 0xFFFFFFFF);
        const auto offset_high = static_cast<uint32_t>(offset >> 32);
        const auto range_low = static_cast<uint32_t>(range & 0xFFFFFFFF);
        if (const auto range_high = static_cast<uint32_t>(range >> 32);
            !LockFile(file_handle, offset_low, offset_high, range_low,
                      range_high)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool fs::lock_async(LockMode lock_mode,
                        const uint64_t range,
                        OVERLAPPED *overlapped) {
        const auto low = static_cast<uint32_t>(range & 0xFFFFFFFF);
        if (const auto high = static_cast<uint32_t>(range >> 32);
            !LockFileEx(file_handle, static_cast<uint32_t>(lock_mode), 0, low,
                        high, overlapped)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool fs::unlock(const uint64_t offset, const uint64_t range) {
        const auto offset_low = static_cast<uint32_t>(offset & 0xFFFFFFFF);
        const auto offset_high = static_cast<uint32_t>(offset >> 32);
        const auto range_low = static_cast<uint32_t>(range & 0xFFFFFFFF);
        if (const auto range_high = static_cast<uint32_t>(range >> 32);
            !UnlockFile(file_handle, offset_low, offset_high, range_low,
                        range_high)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool fs::unlock_async(const uint64_t range, OVERLAPPED *overlapped) {
        const auto low = static_cast<uint32_t>(range & 0xFFFFFFFF);
        if (const auto high = static_cast<uint32_t>(range >> 32);
            !UnlockFileEx(file_handle, 0, low, high, overlapped)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool fs::get_info(FILE_INFO_BY_HANDLE_CLASS file_info_class,
                      void *file_info,
                      uint32_t file_info_size) {
        if (!GetFileInformationByHandleEx(file_handle, file_info_class,
                                          file_info, file_info_size)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool fs::set_info(FILE_INFO_BY_HANDLE_CLASS file_info_class,
                      void *file_info,
                      uint32_t file_info_size) {
        if (!SetFileInformationByHandle(file_handle, file_info_class, file_info,
                                        file_info_size)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool fs::set_io_overlapped_range(uint8_t *overlapped_range_start,
                                     uint32_t length) {
        if (!SetFileIoOverlappedRange(file_handle, overlapped_range_start,
                                      length)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool fs::get_volume_info(VolumeInfoA *volume_info,
                             helper::CodePage code_page) {
        if (!volume_info) {
            error_code = STATUS_ACCESS_VIOLATION;
            return false;
        }
        memset(volume_info, 0, sizeof(VolumeInfoA));
        const auto volume_info_wide = std::make_unique<VolumeInfoW>();
        memset(volume_info_wide.get(), 0, sizeof(VolumeInfoW));
        if (get_volume_info(volume_info_wide.get())) {
            const auto volume_name =
                    helper::convert::wstr_to_str(volume_info_wide->volume_name,
                                                 code_page);
            const auto file_system_name = helper::convert::wstr_to_str(
                    volume_info_wide->file_system_name, code_page);
            memcpy_s(volume_info->volume_name, MAX_PATH, volume_name.data(),
                     volume_name.size());
            memcpy_s(volume_info->file_system_name, MAX_PATH,
                     file_system_name.data(), file_system_name.size());
            volume_info->serial_number = volume_info_wide->serial_number;
            volume_info->file_system_flag = volume_info_wide->file_system_flag;
            return true;
        }
        return false;
    }

    bool fs::get_volume_info(VolumeInfoW *volume_info) {
        if (!volume_info) {
            error_code = STATUS_ACCESS_VIOLATION;
            return false;
        }
        memset(volume_info, 0, sizeof(VolumeInfoW));
        unsigned long size = 0;
        unsigned long serial_number = 0;
        unsigned long file_system_flag = 0;
        if (!GetVolumeInformationByHandleW(file_handle,
                                           volume_info->volume_name, MAX_PATH,
                                           &serial_number, &size,
                                           &file_system_flag,
                                           volume_info->file_system_name,
                                           MAX_PATH)) {
            error_code = GetLastError();
            volume_info->serial_number = serial_number;
            volume_info->file_system_flag = file_system_flag;
            return false;
        }
        volume_info->serial_number = serial_number;
        volume_info->file_system_flag = file_system_flag;
        return true;
    }

    bool fs::get_final_path_name(std::string &path_name,
                                 PathNameType type,
                                 helper::CodePage code_page) {
        std::wstring src;
        if (!get_final_path_name(src, type)) {
            return false;
        }
        path_name.clear();
        path_name.append(helper::convert::wstr_to_str(src, code_page));
        return true;
    }

    bool fs::get_final_path_name(std::wstring &path_name, PathNameType type) {
        uint32_t size = GetFinalPathNameByHandleW(file_handle, nullptr, 0,
                                                  static_cast<uint32_t>(type));
        path_name.resize(size, L'\0');
        size = GetFinalPathNameByHandleW(file_handle, path_name.data(),
                                         path_name.size(),
                                         static_cast<uint32_t>(type));
        if (!size) {
            error_code = GetLastError();
            return false;
        }
        path_name.resize(size);
        while (path_name.back() == L'\0') {
            path_name.pop_back();
        }
        return true;
    }

    bool fs::is_short_name_enabled() {
        int32_t is_ok = 0;
        if (!AreShortNamesEnabled(file_handle, &is_ok)) {
            error_code = GetLastError();
        }
        return is_ok;
    }

    bool
    fs::monitor_dir_change(void *buffer,
                           uint32_t buffer_length,
                           bool is_watch_subtree,
                           uint32_t notify_filter,
                           uint32_t *bytes_returned,
                           OVERLAPPED *overlapped,
                           OVERLAPPED_COMPLETION_ROUTINE completion_routine) {
        if (!bytes_returned) {
            error_code = STATUS_ACCESS_VIOLATION;
            return false;
        }
        unsigned long temp = *bytes_returned;
        if (!ReadDirectoryChangesW(file_handle, buffer, buffer_length,
                                   is_watch_subtree ? TRUE : FALSE,
                                   notify_filter, &temp, overlapped,
                                   completion_routine)) {
            error_code = GetLastError();
            *bytes_returned = temp;
            return false;
        }
        *bytes_returned = temp;
        return true;
    }

    FileType fs::file_type() {
        uint32_t ret = GetFileType(file_handle);
        if (ret == FILE_TYPE_UNKNOWN) {
            error_code = GetLastError();
        }
        return static_cast<FileType>(ret);
    }

    int64_t fs::size() {
        LARGE_INTEGER file_size{};
        if (!GetFileSizeEx(file_handle, &file_size)) {
            error_code = GetLastError();
        }
        return file_size.QuadPart;
    }

    HANDLE fs::expose_handle() const {
        return file_handle;
    }

    uint32_t fs::err_code() const {
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
} // namespace YanLib::io

namespace YanLib::io {
    void fs_util::remove_tail_slash(std::string &path) {
        std::transform(path.begin(), path.end(), path.begin(),
                       [](const char ch) {
                           return (ch == '/') ? '\\' : ch;
                       });
        if (path.back() == '\\') {
            path.pop_back();
        }
    }

    void fs_util::remove_tail_slash(std::wstring &path) {
        std::transform(path.begin(), path.end(), path.begin(),
                       [](const wchar_t ch) {
                           return (ch == L'/') ? L'\\' : ch;
                       });
        if (path.back() == L'\\') {
            path.pop_back();
        }
    }

    bool fs_util::touch(const char *file_name,
                        DesiredAccess desired_access,
                        ShareMode share_mode,
                        SECURITY_ATTRIBUTES *security_attrs,
                        CreationDisposition creation_disposition,
                        FlagAndAttr flag_and_attr,
                        HANDLE template_file) {
        HANDLE file_handle =
                CreateFileA(file_name, static_cast<uint32_t>(desired_access),
                            static_cast<uint32_t>(share_mode), security_attrs,
                            static_cast<uint32_t>(creation_disposition),
                            static_cast<uint32_t>(flag_and_attr),
                            template_file);
        if (file_handle == INVALID_HANDLE_VALUE) {
            error_code = GetLastError();
            return false;
        }
        CloseHandle(file_handle);
        return true;
    }

    bool fs_util::touch(const wchar_t *file_name,
                        DesiredAccess desired_access,
                        ShareMode share_mode,
                        SECURITY_ATTRIBUTES *security_attrs,
                        CreationDisposition creation_disposition,
                        FlagAndAttr flag_and_attr,
                        HANDLE template_file) {
        HANDLE file_handle =
                CreateFileW(file_name, static_cast<uint32_t>(desired_access),
                            static_cast<uint32_t>(share_mode), security_attrs,
                            static_cast<uint32_t>(creation_disposition),
                            static_cast<uint32_t>(flag_and_attr),
                            template_file);
        if (file_handle == INVALID_HANDLE_VALUE) {
            error_code = GetLastError();
            return false;
        }
        CloseHandle(file_handle);
        return true;
    }

    bool fs_util::is_exists(const char *path_name) {
        if (!PathFileExistsA(path_name)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool fs_util::is_exists(const wchar_t *path_name) {
        if (!PathFileExistsW(path_name)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    uint32_t fs_util::get_attr(const char *file_name) {
        const uint32_t attr = GetFileAttributesA(file_name);
        if (attr == INVALID_FILE_ATTRIBUTES) {
            error_code = GetLastError();
            return 0;
        }
        return attr;
    }

    uint32_t fs_util::get_attr(const wchar_t *file_name) {
        const uint32_t attr = GetFileAttributesW(file_name);
        if (attr == INVALID_FILE_ATTRIBUTES) {
            error_code = GetLastError();
            return 0;
        }
        return attr;
    }

    bool fs_util::set_attr(const char *file_name, uint32_t attr) {
        if (!SetFileAttributesA(file_name, attr)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool fs_util::set_attr(const wchar_t *file_name, uint32_t attr) {
        if (!SetFileAttributesW(file_name, attr)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    DriveType fs_util::get_drive_type(const char *path_name) {
        return static_cast<DriveType>(GetDriveTypeA(path_name));
    }

    DriveType fs_util::get_drive_type(const wchar_t *path_name) {
        return static_cast<DriveType>(GetDriveTypeW(path_name));
    }

    std::string fs_util::get_volume_path_name(const char *file_name) {
        std::string buffer(MAX_PATH + 1, '\0');
        if (!GetVolumePathNameA(file_name, buffer.data(), MAX_PATH)) {
            error_code = GetLastError();
            return {};
        }
        while (buffer.back() == '\0') {
            buffer.pop_back();
        }
        return buffer;
    }

    std::wstring fs_util::get_volume_path_name(const wchar_t *file_name) {
        std::wstring buffer(MAX_PATH + 1, L'\0');
        if (!GetVolumePathNameW(file_name, buffer.data(), MAX_PATH)) {
            error_code = GetLastError();
            return {};
        }
        while (buffer.back() == L'\0') {
            buffer.pop_back();
        }
        return buffer;
    }

    std::string
    fs_util::get_volume_path_names_for_volume_name(const char *volume_name) {
        unsigned long size = 0;
        if (!GetVolumePathNamesForVolumeNameA(volume_name, nullptr, 0, &size)) {
            if (GetLastError() == ERROR_MORE_DATA) {
                std::string buffer(size, '\0');
                if (!GetVolumePathNamesForVolumeNameA(volume_name,
                                                      buffer.data(),
                                                      buffer.size(), &size)) {
                    error_code = GetLastError();
                    return {};
                }
                buffer.resize(size);
                while (buffer.back() == '\0') {
                    buffer.pop_back();
                }
                return buffer;
            }
        }
        return {};
    }

    std::wstring
    fs_util::get_volume_path_names_for_volume_name(const wchar_t *volume_name) {
        unsigned long size = 0;
        if (!GetVolumePathNamesForVolumeNameW(volume_name, nullptr, 0, &size)) {
            if (GetLastError() == ERROR_MORE_DATA) {
                std::wstring buffer(size, L'\0');
                if (!GetVolumePathNamesForVolumeNameW(volume_name,
                                                      buffer.data(),
                                                      buffer.size(), &size)) {
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

    std::string fs_util::get_volume_name_for_volume_mount_point(
            const char *volume_mount_point) {
        std::string buffer(MAX_PATH + 1, '\0');
        if (!GetVolumeNameForVolumeMountPointA(volume_mount_point,
                                               buffer.data(), MAX_PATH)) {
            error_code = GetLastError();
            return {};
        }
        while (buffer.back() == '\0') {
            buffer.pop_back();
        }
        return buffer;
    }

    std::wstring fs_util::get_volume_name_for_volume_mount_point(
            const wchar_t *volume_mount_point) {
        std::wstring buffer(MAX_PATH + 1, L'\0');
        if (!GetVolumeNameForVolumeMountPointW(volume_mount_point,
                                               buffer.data(), MAX_PATH)) {
            error_code = GetLastError();
            return {};
        }
        while (buffer.back() == L'\0') {
            buffer.pop_back();
        }
        return buffer;
    }

    bool fs_util::delete_volume_mount_point(const char *volume_mount_point) {
        if (!DeleteVolumeMountPointA(volume_mount_point)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool fs_util::delete_volume_mount_point(const wchar_t *volume_mount_point) {
        if (!DeleteVolumeMountPointW(volume_mount_point)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool fs_util::get_temp_path(std::string &path) {
        path.resize(MAX_PATH + 1, '\0');
        const uint32_t size = GetTempPathA(MAX_PATH, path.data());
        if (!size) {
            error_code = GetLastError();
            return false;
        }
        path.resize(size);
        while (path.back() == '\0') {
            path.pop_back();
        }
        return true;
    }

    bool fs_util::get_temp_path(std::wstring &path) {
        path.resize(MAX_PATH + 1, L'\0');
        const uint32_t size = GetTempPathW(MAX_PATH, path.data());
        if (!size) {
            error_code = GetLastError();
            return false;
        }
        path.resize(size);
        while (path.back() == L'\0') {
            path.pop_back();
        }
        return true;
    }

    std::string fs_util::get_temp_file_name(const char *path_name,
                                            const char *prefix,
                                            const uint32_t unique) {
        std::string buffer(MAX_PATH + 1, '\0');
        if (!GetTempFileNameA(path_name, prefix, unique, buffer.data())) {
            error_code = GetLastError();
            return {};
        }
        while (buffer.back() == '\0') {
            buffer.pop_back();
        }
        return buffer;
    }

    std::wstring fs_util::get_temp_file_name(const wchar_t *path_name,
                                             const wchar_t *prefix,
                                             const uint32_t unique) {
        std::wstring buffer(MAX_PATH + 1, L'\0');
        if (!GetTempFileNameW(path_name, prefix, unique, buffer.data())) {
            error_code = GetLastError();
            return {};
        }
        while (buffer.back() == L'\0') {
            buffer.pop_back();
        }
        return buffer;
    }

    std::string fs_util::get_short_path_name(const char *long_path) {
        uint32_t size = GetShortPathNameA(long_path, nullptr, 0);
        std::string buffer(size, '\0');
        size = GetShortPathNameA(long_path, buffer.data(), buffer.size());
        if (!size) {
            error_code = GetLastError();
            return {};
        }
        buffer.resize(size);
        while (buffer.back() == '\0') {
            buffer.pop_back();
        }
        return buffer;
    }

    std::wstring fs_util::get_short_path_name(const wchar_t *long_path) {
        uint32_t size = GetShortPathNameW(long_path, nullptr, 0);
        std::wstring buffer(size, L'\0');
        size = GetShortPathNameW(long_path, buffer.data(), buffer.size());
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

    std::string fs_util::get_long_path_name(const char *short_path) {
        uint32_t size = GetLongPathNameA(short_path, nullptr, 0);
        std::string buffer(size, '\0');
        size = GetLongPathNameA(short_path, buffer.data(), buffer.size());
        if (!size) {
            error_code = GetLastError();
            return {};
        }
        buffer.resize(size);
        while (buffer.back() == '\0') {
            buffer.pop_back();
        }
        return buffer;
    }

    std::wstring fs_util::get_long_path_name(const wchar_t *short_path) {
        uint32_t size = GetLongPathNameW(short_path, nullptr, 0);
        std::wstring buffer(size, L'\0');
        size = GetLongPathNameW(short_path, buffer.data(), buffer.size());
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

    bool fs_util::get_logical_drive_strings(std::string &drive) {
        uint32_t size = GetLogicalDriveStringsA(0, nullptr);
        drive.resize(size, '\0');
        size = GetLogicalDriveStringsA(drive.size(), drive.data());
        if (!size) {
            error_code = GetLastError();
            return false;
        }
        drive.resize(size);
        while (drive.back() == '\0') {
            drive.pop_back();
        }
        return true;
    }

    bool fs_util::get_logical_drive_strings(std::wstring &drive) {
        uint32_t size = GetLogicalDriveStringsW(0, nullptr);
        drive.resize(size, L'\0');
        size = GetLogicalDriveStringsW(drive.size(), drive.data());
        if (!size) {
            error_code = GetLastError();
            return false;
        }
        drive.resize(size);
        while (drive.back() == L'\0') {
            drive.pop_back();
        }
        return true;
    }

    uint32_t fs_util::get_logica_drives() {
        return GetLogicalDrives();
    }

    std::string fs_util::get_full_path_name(const char *file_name) {
        uint32_t size = GetFullPathNameA(file_name, 0, nullptr, nullptr);
        std::string buffer(size, '\0');
        size = GetFullPathNameA(file_name, buffer.size(), buffer.data(),
                                nullptr);
        if (!size) {
            error_code = GetLastError();
            return {};
        }
        buffer.resize(size);
        while (buffer.back() == '\0') {
            buffer.pop_back();
        }
        return buffer;
    }

    std::wstring fs_util::get_full_path_name(const wchar_t *file_name) {
        uint32_t size = GetFullPathNameW(file_name, 0, nullptr, nullptr);
        std::wstring buffer(size, L'\0');
        size = GetFullPathNameW(file_name, buffer.size(), buffer.data(),
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

    bool fs_util::get_disk_space_info(const char *root_path,
                                      DISK_SPACE_INFORMATION *disk_space_info) {
        if (const HRESULT is_ok =
                    GetDiskSpaceInformationA(root_path, disk_space_info);
            is_ok != S_OK) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool fs_util::get_disk_space_info(const wchar_t *root_path,
                                      DISK_SPACE_INFORMATION *disk_space_info) {
        if (const HRESULT is_ok =
                    GetDiskSpaceInformationW(root_path, disk_space_info);
            is_ok != S_OK) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool fs_util::get_disk_free_space(const char *root_path_name,
                                      DiskFreeSpace4 *disk_free_space4) {
        if (!disk_free_space4) {
            error_code = STATUS_ACCESS_VIOLATION;
            return false;
        }
        unsigned long sectors_per_cluster = 0;
        unsigned long bytes_per_sector = 0;
        unsigned long number_of_free_clusters = 0;
        unsigned long total_number_of_clusters = 0;
        if (!GetDiskFreeSpaceA(root_path_name, &sectors_per_cluster,
                               &bytes_per_sector, &number_of_free_clusters,
                               &total_number_of_clusters)) {
            error_code = GetLastError();
            disk_free_space4->sectors_per_cluster = sectors_per_cluster;
            disk_free_space4->bytes_per_sector = bytes_per_sector;
            disk_free_space4->number_of_free_clusters = number_of_free_clusters;
            disk_free_space4->total_number_of_clusters =
                    total_number_of_clusters;
            return false;
        }
        disk_free_space4->sectors_per_cluster = sectors_per_cluster;
        disk_free_space4->bytes_per_sector = bytes_per_sector;
        disk_free_space4->number_of_free_clusters = number_of_free_clusters;
        disk_free_space4->total_number_of_clusters = total_number_of_clusters;
        return true;
    }

    bool fs_util::get_disk_free_space(const wchar_t *root_path_name,
                                      DiskFreeSpace4 *disk_free_space4) {
        if (!disk_free_space4) {
            error_code = STATUS_ACCESS_VIOLATION;
            return false;
        }
        unsigned long sectors_per_cluster = 0;
        unsigned long bytes_per_sector = 0;
        unsigned long number_of_free_clusters = 0;
        unsigned long total_number_of_clusters = 0;
        if (!GetDiskFreeSpaceW(root_path_name, &sectors_per_cluster,
                               &bytes_per_sector, &number_of_free_clusters,
                               &total_number_of_clusters)) {
            error_code = GetLastError();
            disk_free_space4->sectors_per_cluster = sectors_per_cluster;
            disk_free_space4->bytes_per_sector = bytes_per_sector;
            disk_free_space4->number_of_free_clusters = number_of_free_clusters;
            disk_free_space4->total_number_of_clusters =
                    total_number_of_clusters;
            return false;
        }
        disk_free_space4->sectors_per_cluster = sectors_per_cluster;
        disk_free_space4->bytes_per_sector = bytes_per_sector;
        disk_free_space4->number_of_free_clusters = number_of_free_clusters;
        disk_free_space4->total_number_of_clusters = total_number_of_clusters;
        return true;
    }

    bool fs_util::get_disk_free_space(const char *directory_name,
                                      DiskFreeSpace3 *disk_free_space3) {
        if (!disk_free_space3) {
            error_code = STATUS_ACCESS_VIOLATION;
            return false;
        }
        ULARGE_INTEGER free_bytes_available_to_caller = {};
        ULARGE_INTEGER total_number_of_bytes = {};
        ULARGE_INTEGER total_number_of_free_bytes = {};
        if (!GetDiskFreeSpaceExA(directory_name,
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

    bool fs_util::get_disk_free_space(const wchar_t *directory_name,
                                      DiskFreeSpace3 *disk_free_space3) {
        if (!disk_free_space3) {
            error_code = STATUS_ACCESS_VIOLATION;
            return false;
        }
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

    int64_t fs_util::get_compressed_file_size(const char *file_name) {
        unsigned long high = 0;
        const uint32_t low = GetCompressedFileSizeA(file_name, &high);
        if (low == INVALID_FILE_SIZE) {
            error_code = GetLastError();
            if (error_code != NO_ERROR) {
                return 0;
            }
        }
        return (static_cast<int64_t>(high) << 32) | low;
    }

    int64_t fs_util::get_compressed_file_size(const wchar_t *file_name) {
        unsigned long high = 0;
        const uint32_t low = GetCompressedFileSizeW(file_name, &high);
        if (low == INVALID_FILE_SIZE) {
            error_code = GetLastError();
            if (error_code != NO_ERROR) {
                return 0;
            }
        }
        return (static_cast<int64_t>(high) << 32) | low;
    }

    std::string fs_util::get_dos_device(const char *device_name) {
        size_t buff_size = MAX_PATH;
        std::string buffer(buff_size + 1, '\0');
        uint32_t size = QueryDosDeviceA(device_name, buffer.data(), MAX_PATH);
        while (!size) {
            error_code = GetLastError();
            if (error_code != ERROR_INSUFFICIENT_BUFFER) {
                return {};
            }
            buff_size = buff_size * 2;
            buffer.resize(buff_size + 1, '\0');
            size = QueryDosDeviceA(device_name, buffer.data(), buff_size);
        }
        while (buffer.back() == '\0') {
            buffer.pop_back();
        }
        return buffer;
    }

    std::wstring fs_util::get_dos_device(const wchar_t *device_name) {
        size_t buff_size = MAX_PATH;
        std::wstring buffer(buff_size + 1, L'\0');
        uint32_t size = QueryDosDeviceW(device_name, buffer.data(), MAX_PATH);
        while (!size) {
            error_code = GetLastError();
            if (error_code != ERROR_INSUFFICIENT_BUFFER) {
                return {};
            }
            buff_size = buff_size * 2;
            buffer.resize(buff_size + 1, L'\0');
            size = QueryDosDeviceW(device_name, buffer.data(), buff_size);
        }
        while (buffer.back() == L'\0') {
            buffer.pop_back();
        }
        return buffer;
    }

    bool fs_util::get_dos_device(std::vector<std::string> &dos_device) {
        size_t buff_size = 4096;
        std::string buffer(buff_size, '\0');
        uint32_t size = QueryDosDeviceA(nullptr, buffer.data(), buff_size - 1);
        while (!size) {
            error_code = GetLastError();
            if (error_code != ERROR_INSUFFICIENT_BUFFER) {
                return false;
            }
            buff_size = buff_size * 2;
            buffer.resize(buff_size, '\0');
            size = QueryDosDeviceA(nullptr, buffer.data(), buff_size - 1);
        }
        while (buffer.back() == '\0') {
            buffer.pop_back();
        }
        size_t start = 0;
        size_t end = buffer.find('\0');
        while (end != std::string::npos) {
            dos_device.push_back(buffer.substr(start, end - start));
            start = end + 1;
            end = buffer.find('\0', start);
        }
        if (start < buffer.size()) {
            dos_device.push_back(buffer.substr(start));
        }
        return true;
    }

    bool fs_util::get_dos_device(std::vector<std::wstring> &dos_device) {
        size_t buff_size = 4096;
        std::wstring buffer(buff_size, L'\0');
        uint32_t size = QueryDosDeviceW(nullptr, buffer.data(), buff_size - 1);
        while (!size) {
            error_code = GetLastError();
            if (error_code != ERROR_INSUFFICIENT_BUFFER) {
                return false;
            }
            buff_size = buff_size * 2;
            buffer.resize(buff_size, L'\0');
            size = QueryDosDeviceW(nullptr, buffer.data(), buff_size - 1);
        }
        while (buffer.back() == L'\0') {
            buffer.pop_back();
        }
        size_t start = 0;
        size_t end = buffer.find(L'\0');
        while (end != std::wstring::npos) {
            dos_device.push_back(buffer.substr(start, end - start));
            start = end + 1;
            end = buffer.find(L'\0', start);
        }
        if (start < buffer.size()) {
            dos_device.push_back(buffer.substr(start));
        }
        return true;
    }

    bool fs_util::control_dos_device(const char *device_name,
                                     const char *target_path,
                                     DosControlCode code) {
        if (!DefineDosDeviceA(static_cast<uint32_t>(code), device_name,
                              target_path)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool fs_util::control_dos_device(const wchar_t *device_name,
                                     const wchar_t *target_path,
                                     DosControlCode code) {
        if (!DefineDosDeviceW(static_cast<uint32_t>(code), device_name,
                              target_path)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool fs_util::ls_volume_name(std::vector<std::string> &volume_names) {
        bool result = false;
        do {
            std::string volume_name(MAX_PATH + 1, '\0');
            HANDLE file_handle =
                    FindFirstVolumeA(volume_name.data(), volume_name.size());
            if (file_handle == INVALID_HANDLE_VALUE) {
                error_code = GetLastError();
                break;
            }
            do {
                volume_names.emplace_back(volume_name.data());
            } while (FindNextVolumeA(file_handle, volume_name.data(),
                                     volume_name.size()));
            if (!FindVolumeClose(file_handle)) {
                error_code = GetLastError();
                break;
            }
            result = true;
        } while (false);
        return result;
    }

    bool fs_util::ls_volume_name(std::vector<std::wstring> &volume_names) {
        bool result = false;
        do {
            std::wstring volume_name(MAX_PATH + 1, L'\0');
            HANDLE file_handle =
                    FindFirstVolumeW(volume_name.data(), volume_name.size());
            if (file_handle == INVALID_HANDLE_VALUE) {
                error_code = GetLastError();
                break;
            }
            do {
                volume_names.emplace_back(volume_name.data());
            } while (FindNextVolumeW(file_handle, volume_name.data(),
                                     volume_name.size()));
            if (!FindVolumeClose(file_handle)) {
                error_code = GetLastError();
                break;
            }
            result = true;
        } while (false);
        return result;
    }

    bool fs_util::ls_device_name(std::vector<std::string> &device_names) {
        std::vector<std::string> volumes;
        if (!ls_volume_name(volumes) || volumes.empty()) {
            return false;
        }
        device_names.clear();
        for (auto volume : volumes) {
            if (volume.back() == '\\') {
                volume.pop_back();
            }
            std::string device_name(MAX_PATH + 1, '\0');
            if (!QueryDosDeviceA(volume.data() + 4, device_name.data(),
                                 device_name.size())) {
                error_code = GetLastError();
                break;
            }
            device_names.emplace_back(device_name.data());
        }
        return true;
    }

    bool fs_util::ls_device_name(std::vector<std::wstring> &device_names) {
        std::vector<std::wstring> volumes;
        if (!ls_volume_name(volumes) || volumes.empty()) {
            return false;
        }
        device_names.clear();
        for (auto volume : volumes) {
            if (volume.back() == L'\\') {
                volume.pop_back();
            }
            std::wstring device_name(MAX_PATH + 1, L'\0');
            if (!QueryDosDeviceW(volume.data() + 4, device_name.data(),
                                 device_name.size())) {
                error_code = GetLastError();
                break;
            }
            device_names.emplace_back(device_name.data());
        }
        return true;
    }

    std::vector<WIN32_FIND_STREAM_DATA>
    fs_util::ls_stream_data(const char *file_name, helper::CodePage code_page) {
        const std::wstring result =
                helper::convert::str_to_wstr(file_name, code_page);
        if (result.empty()) {
            return {};
        }
        return ls_stream_data(result.data());
    }

    std::vector<WIN32_FIND_STREAM_DATA>
    fs_util::ls_stream_data(const wchar_t *file_name) {
        std::vector<WIN32_FIND_STREAM_DATA> result = {};
        do {
            WIN32_FIND_STREAM_DATA stream_data = {};
            HANDLE file_handle =
                    FindFirstStreamW(file_name, FindStreamInfoStandard,
                                     &stream_data, 0);
            if (file_handle == INVALID_HANDLE_VALUE) {
                error_code = GetLastError();
                break;
            }
            do {
                result.push_back(stream_data);
            } while (FindNextStreamW(file_handle, &stream_data));
            if (!FindClose(file_handle)) {
                error_code = GetLastError();
            }
        } while (false);
        return result;
    }

    bool fs_util::rm_file(const char *file_name) {
        if (!DeleteFileA(file_name)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool fs_util::rm_file(const wchar_t *file_name) {
        if (!DeleteFileW(file_name)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool fs_util::is_file(const char *file_name) {
        const uint32_t attr = GetFileAttributesA(file_name);
        if (attr == INVALID_FILE_ATTRIBUTES) {
            error_code = GetLastError();
        }
        return (attr != INVALID_FILE_ATTRIBUTES) &&
                (!(attr & FILE_ATTRIBUTE_DIRECTORY));
    }

    bool fs_util::is_file(const wchar_t *file_name) {
        const uint32_t attr = GetFileAttributesW(file_name);
        if (attr == INVALID_FILE_ATTRIBUTES) {
            error_code = GetLastError();
        }
        return (attr != INVALID_FILE_ATTRIBUTES) &&
                (!(attr & FILE_ATTRIBUTE_DIRECTORY));
    }

    bool fs_util::is_dir(const char *path_name) {
        const uint32_t attr = GetFileAttributesA(path_name);
        if (attr == INVALID_FILE_ATTRIBUTES) {
            error_code = GetLastError();
        }
        return (attr != INVALID_FILE_ATTRIBUTES) &&
                (attr & FILE_ATTRIBUTE_DIRECTORY);
    }

    bool fs_util::is_dir(const wchar_t *path_name) {
        const uint32_t attr = GetFileAttributesW(path_name);
        if (attr == INVALID_FILE_ATTRIBUTES) {
            error_code = GetLastError();
        }
        return (attr != INVALID_FILE_ATTRIBUTES) &&
                (attr & FILE_ATTRIBUTE_DIRECTORY);
    }

    bool fs_util::mkdir(const char *path_name,
                        SECURITY_ATTRIBUTES *security_attrs) {
        if (!CreateDirectoryA(path_name, security_attrs)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool fs_util::mkdir(const wchar_t *path_name,
                        SECURITY_ATTRIBUTES *security_attrs) {
        if (!CreateDirectoryW(path_name, security_attrs)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool fs_util::mkdir_all(const char *path_name,
                            SECURITY_ATTRIBUTES *security_attrs) {
        const std::string path(path_name);
        std::vector<std::string> dirs;
        std::string currentDir;

        for (const char ch : path) {
            if (ch == '\\' || ch == '/') {
                dirs.push_back(currentDir);
            }
            currentDir += ch;
        }
        dirs.push_back(currentDir);

        for (const std::string &dir : dirs) {
            if (!is_dir(dir.data())) {
                if (!CreateDirectoryA(dir.data(), security_attrs)) {
                    error_code = GetLastError();
                    if (error_code != ERROR_ALREADY_EXISTS) {
                        return false;
                    }
                }
            }
        }
        return true;
    }

    bool fs_util::mkdir_all(const wchar_t *path_name,
                            SECURITY_ATTRIBUTES *security_attrs) {
        const std::wstring path(path_name);
        std::vector<std::wstring> dirs;
        std::wstring currentDir;

        for (const wchar_t ch : path) {
            if (ch == L'\\' || ch == L'/') {
                dirs.push_back(currentDir);
            }
            currentDir += ch;
        }
        dirs.push_back(currentDir);

        for (const std::wstring &dir : dirs) {
            if (!is_dir(dir.data())) {
                if (!CreateDirectoryW(dir.data(), security_attrs)) {
                    error_code = GetLastError();
                    if (error_code != ERROR_ALREADY_EXISTS) {
                        return false;
                    }
                }
            }
        }
        return true;
    }

    bool fs_util::rm_dir(const char *path_name) {
        if (!RemoveDirectoryA(path_name)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool fs_util::rm_dir(const wchar_t *path_name) {
        if (!RemoveDirectoryW(path_name)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool fs_util::rm_dir_all(const char *path_name) {
        SHFILEOPSTRUCTA op = {};

        char path[MAX_PATH + 2] = {};
        strcpy_s(path, MAX_PATH, path_name);
        path[strlen(path_name) + 1] = '\0';

        op.wFunc = FO_DELETE;
        op.pFrom = path;
        op.fFlags = FOF_NOCONFIRMATION | FOF_SILENT | FOF_NOERRORUI;

        const int32_t result = SHFileOperationA(&op);
        return (result == 0) && !op.fAnyOperationsAborted;
    }

    bool fs_util::rm_dir_all(const wchar_t *path_name) {
        SHFILEOPSTRUCTW op = {};

        wchar_t path[MAX_PATH + 2] = {};
        wcscpy_s(path, MAX_PATH, path_name);
        path[wcslen(path_name) + 1] = L'\0';

        op.wFunc = FO_DELETE;
        op.pFrom = path;
        op.fFlags = FOF_NOCONFIRMATION | FOF_SILENT | FOF_NOERRORUI;

        const int32_t result = SHFileOperationW(&op);
        return (result == 0) && !op.fAnyOperationsAborted;
    }

    void fs_util::rm_dir_all_slow(const char *path_name) {
        std::vector<std::string> dirs = ls_all_dirs(path_name);
        std::vector<std::string> files = ls_all_files(path_name);

        std::for_each(files.rbegin(), files.rend(),
                      [this](const std::string &file) {
                          rm_file(file.data());
                      });
        std::for_each(dirs.rbegin(), dirs.rend(),
                      [this](const std::string &dir) {
                          rm_dir(dir.data());
                      });
    }

    void fs_util::rm_dir_all_slow(const wchar_t *path_name) {
        std::vector<std::wstring> dirs = ls_all_dirs(path_name);
        std::vector<std::wstring> files = ls_all_files(path_name);

        std::for_each(files.rbegin(), files.rend(),
                      [this](const std::wstring &file) {
                          rm_file(file.data());
                      });
        std::for_each(dirs.rbegin(), dirs.rend(),
                      [this](const std::wstring &dir) {
                          rm_dir(dir.data());
                      });
    }

    std::vector<WIN32_FIND_DATAA> fs_util::ls_detail(const char *path_name) {
        std::vector<WIN32_FIND_DATAA> result;
        std::string path(path_name);
        remove_tail_slash(path);
        path.append("\\*.*");
        WIN32_FIND_DATAA find_data;
        HANDLE find_handle = FindFirstFileA(path.data(), &find_data);
        if (find_handle == INVALID_HANDLE_VALUE) {
            error_code = GetLastError();
            return result;
        }
        do {
            if (strcmp(find_data.cFileName, ".") != 0 &&
                strcmp(find_data.cFileName, "..") != 0) {
                result.emplace_back(find_data);
            }
        } while (FindNextFileA(find_handle, &find_data));
        if (!FindClose(find_handle)) {
            error_code = GetLastError();
        }
        return result;
    }

    std::vector<WIN32_FIND_DATAW> fs_util::ls_detail(const wchar_t *path_name) {
        std::vector<WIN32_FIND_DATAW> result;
        std::wstring path(path_name);
        remove_tail_slash(path);
        path.append(L"\\*.*");
        WIN32_FIND_DATAW find_data;
        HANDLE find_handle = FindFirstFileW(path.data(), &find_data);
        if (find_handle == INVALID_HANDLE_VALUE) {
            error_code = GetLastError();
            return result;
        }
        do {
            if (wcscmp(find_data.cFileName, L".") != 0 &&
                wcscmp(find_data.cFileName, L"..") != 0) {
                result.emplace_back(find_data);
            }
        } while (FindNextFileW(find_handle, &find_data));
        if (!FindClose(find_handle)) {
            error_code = GetLastError();
        }
        return result;
    }

    std::vector<std::string> fs_util::ls(const char *path_name) {
        std::vector<std::string> result;
        std::string path(path_name);
        WIN32_FIND_DATAA find_data;

        remove_tail_slash(path);

        std::string base_path = path;
        path.append("\\*.*");

        HANDLE find_handle = FindFirstFileA(path.data(), &find_data);
        if (find_handle == INVALID_HANDLE_VALUE) {
            error_code = GetLastError();
            return result;
        }
        do {
            if (strcmp(find_data.cFileName, ".") != 0 &&
                strcmp(find_data.cFileName, "..") != 0) {
                result.emplace_back(find_data.cFileName);
            }
        } while (FindNextFileA(find_handle, &find_data));
        if (!FindClose(find_handle)) {
            error_code = GetLastError();
        }
        return result;
    }

    std::vector<std::wstring> fs_util::ls(const wchar_t *path_name) {
        std::vector<std::wstring> result;
        std::wstring path(path_name);
        WIN32_FIND_DATAW find_data;

        remove_tail_slash(path);

        std::wstring base_path = path;
        path.append(L"\\*.*");

        HANDLE find_handle = FindFirstFileW(path.data(), &find_data);
        if (find_handle == INVALID_HANDLE_VALUE) {
            error_code = GetLastError();
            return result;
        }
        do {
            if (wcscmp(find_data.cFileName, L".") != 0 &&
                wcscmp(find_data.cFileName, L"..") != 0) {
                result.emplace_back(find_data.cFileName);
            }
        } while (FindNextFileW(find_handle, &find_data));
        if (!FindClose(find_handle)) {
            error_code = GetLastError();
        }
        return result;
    }

    std::vector<std::string> fs_util::ls_full_path(const char *path_name) {
        std::vector<std::string> result;
        std::string path(path_name);
        WIN32_FIND_DATAA find_data;

        remove_tail_slash(path);

        const std::string base_path = path;
        path.append("\\*.*");

        HANDLE find_handle = FindFirstFileA(path.data(), &find_data);
        if (find_handle == INVALID_HANDLE_VALUE) {
            error_code = GetLastError();
            return result;
        }
        do {
            if (strcmp(find_data.cFileName, ".") != 0 &&
                strcmp(find_data.cFileName, "..") != 0) {
                result.push_back(base_path + "\\" + find_data.cFileName);
            }
        } while (FindNextFileA(find_handle, &find_data));
        if (!FindClose(find_handle)) {
            error_code = GetLastError();
        }
        return result;
    }

    std::vector<std::wstring> fs_util::ls_full_path(const wchar_t *path_name) {
        std::vector<std::wstring> result;
        std::wstring path(path_name);
        WIN32_FIND_DATAW find_data;

        remove_tail_slash(path);

        const std::wstring base_path = path;
        path.append(L"\\*.*");

        HANDLE find_handle = FindFirstFileW(path.data(), &find_data);
        if (find_handle == INVALID_HANDLE_VALUE) {
            error_code = GetLastError();
            return result;
        }
        do {
            if (wcscmp(find_data.cFileName, L".") != 0 &&
                wcscmp(find_data.cFileName, L"..") != 0) {
                result.push_back(base_path + L"\\" + find_data.cFileName);
            }
        } while (FindNextFileW(find_handle, &find_data));
        if (!FindClose(find_handle)) {
            error_code = GetLastError();
        }
        return result;
    }

    std::vector<std::string> fs_util::ls_all_files(const char *path_name) {
        std::vector<std::string> result;
        result.reserve(64);

        std::string path(path_name);
        WIN32_FIND_DATAA find_data;

        remove_tail_slash(path);

        std::vector<std::string> stack;
        stack.reserve(64);
        stack.push_back(path + "\\*.*");

        while (!stack.empty()) {
            std::string search_path = stack.back();
            stack.pop_back();

            if (HANDLE find_handle =
                        FindFirstFileA(search_path.data(), &find_data);
                find_handle != INVALID_HANDLE_VALUE) {
                do {
                    if (strcmp(find_data.cFileName, ".") == 0 ||
                        strcmp(find_data.cFileName, "..") == 0)
                        continue;
                    std::string full_path =
                            search_path.substr(0, search_path.size() - 3) +
                            find_data.cFileName;
                    if (find_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
                        stack.push_back(full_path + "\\*.*");
                    } else {
                        result.push_back(full_path);
                    }
                } while (FindNextFileA(find_handle, &find_data));
                if (!FindClose(find_handle)) {
                    error_code = GetLastError();
                }
            } else {
                error_code = GetLastError();
            }
        }
        return result;
    }

    std::vector<std::wstring> fs_util::ls_all_files(const wchar_t *path_name) {
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

            if (HANDLE find_handle =
                        FindFirstFileW(search_path.data(), &find_data);
                find_handle != INVALID_HANDLE_VALUE) {
                do {
                    if (wcscmp(find_data.cFileName, L".") == 0 ||
                        wcscmp(find_data.cFileName, L"..") == 0)
                        continue;
                    std::wstring full_path =
                            search_path.substr(0, search_path.size() - 3) +
                            find_data.cFileName;
                    if (find_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
                        stack.push_back(full_path + L"\\*.*");
                    } else {
                        result.push_back(full_path);
                    }
                } while (FindNextFileW(find_handle, &find_data));
                if (!FindClose(find_handle)) {
                    error_code = GetLastError();
                }
            } else {
                error_code = GetLastError();
            }
        }
        return result;
    }

    std::vector<std::string> fs_util::ls_all_dirs(const char *path_name) {
        std::vector<std::string> result;
        result.reserve(64);

        std::string path(path_name);
        WIN32_FIND_DATAA find_data;

        remove_tail_slash(path);

        result.push_back(path);
        std::vector<std::string> stack;
        stack.reserve(64);

        stack.push_back(path + "\\*.*");
        while (!stack.empty()) {
            std::string search_path = stack.back();
            stack.pop_back();

            if (HANDLE find_handle =
                        FindFirstFileA(search_path.data(), &find_data);
                find_handle != INVALID_HANDLE_VALUE) {
                do {
                    if (strcmp(find_data.cFileName, ".") == 0 ||
                        strcmp(find_data.cFileName, "..") == 0)
                        continue;
                    std::string full_path =
                            search_path.substr(0, search_path.size() - 3) +
                            find_data.cFileName;
                    if (find_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
                        stack.push_back(full_path + "\\*.*");
                        result.push_back(full_path);
                    }
                } while (FindNextFileA(find_handle, &find_data));
                if (!FindClose(find_handle)) {
                    error_code = GetLastError();
                }
            } else {
                error_code = GetLastError();
            }
        }
        return result;
    }

    std::vector<std::wstring> fs_util::ls_all_dirs(const wchar_t *path_name) {
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

            if (HANDLE find_handle =
                        FindFirstFileW(search_path.data(), &find_data);
                find_handle != INVALID_HANDLE_VALUE) {
                do {
                    if (wcscmp(find_data.cFileName, L".") == 0 ||
                        wcscmp(find_data.cFileName, L"..") == 0)
                        continue;
                    std::wstring full_path =
                            search_path.substr(0, search_path.size() - 3) +
                            find_data.cFileName;
                    if (find_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
                        stack.push_back(full_path + L"\\*.*");
                        result.push_back(full_path);
                    }
                } while (FindNextFileW(find_handle, &find_data));
                if (!FindClose(find_handle)) {
                    error_code = GetLastError();
                }
            } else {
                error_code = GetLastError();
            }
        }
        return result;
    }

    bool fs_util::copy(const char *existing_file_name,
                       const char *new_file_name,
                       const bool fail_if_exists) {
        if (!CopyFileA(existing_file_name, new_file_name,
                       fail_if_exists ? TRUE : FALSE)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool fs_util::copy(const wchar_t *existing_file_name,
                       const wchar_t *new_file_name,
                       const bool fail_if_exists) {
        if (!CopyFileW(existing_file_name, new_file_name,
                       fail_if_exists ? TRUE : FALSE)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool fs_util::copy_all(const char *existing_path_name,
                           const char *new_path_name) {
        SHFILEOPSTRUCTA file_op = {};

        char from[MAX_PATH + 2] = {};
        char to[MAX_PATH + 2] = {};

        strcpy_s(from, MAX_PATH, existing_path_name);
        strcpy_s(to, MAX_PATH, new_path_name);

        from[strlen(existing_path_name) + 1] = '\0';
        to[strlen(new_path_name) + 1] = '\0';

        file_op.wFunc = FO_COPY;
        file_op.pFrom = from;
        file_op.pTo = to;
        file_op.fFlags = FOF_NOCONFIRMMKDIR | FOF_NOCONFIRMATION | FOF_NO_UI;
        const int32_t result = SHFileOperationA(&file_op);
        return (result == 0) && !file_op.fAnyOperationsAborted;
    }

    bool fs_util::copy_all(const wchar_t *existing_path_name,
                           const wchar_t *new_path_name) {
        SHFILEOPSTRUCTW file_op = {};

        wchar_t from[MAX_PATH + 2] = {};
        wchar_t to[MAX_PATH + 2] = {};

        wcscpy_s(from, MAX_PATH, existing_path_name);
        wcscpy_s(to, MAX_PATH, new_path_name);

        from[wcslen(existing_path_name) + 1] = L'\0';
        to[wcslen(new_path_name) + 1] = L'\0';

        file_op.wFunc = FO_COPY;
        file_op.pFrom = from;
        file_op.pTo = to;
        file_op.fFlags = FOF_NOCONFIRMMKDIR | FOF_NOCONFIRMATION | FOF_NO_UI;
        const int32_t result = SHFileOperationW(&file_op);
        return (result == 0) && !file_op.fAnyOperationsAborted;
    }

    bool fs_util::rename(const char *existing_file_name,
                         const char *new_file_name) {
        if (!MoveFileExA(existing_file_name, new_file_name,
                         MOVEFILE_COPY_ALLOWED | MOVEFILE_WRITE_THROUGH)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool fs_util::rename(const wchar_t *existing_file_name,
                         const wchar_t *new_file_name) {
        if (!MoveFileExW(existing_file_name, new_file_name,
                         MOVEFILE_COPY_ALLOWED | MOVEFILE_WRITE_THROUGH)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool fs_util::replace(const char *existing_file_name,
                          const char *new_file_name) {
        if (!MoveFileExA(existing_file_name, new_file_name,
                         MOVEFILE_REPLACE_EXISTING | MOVEFILE_WRITE_THROUGH)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool fs_util::replace(const wchar_t *existing_file_name,
                          const wchar_t *new_file_name) {
        if (!MoveFileExW(existing_file_name, new_file_name,
                         MOVEFILE_REPLACE_EXISTING | MOVEFILE_WRITE_THROUGH)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    uint32_t fs_util::err_code() const {
        return error_code;
    }

    std::string fs_util::err_string() const {
        std::string result = helper::convert::err_string(error_code);
        return result;
    }

    std::wstring fs_util::err_wstring() const {
        std::wstring result = helper::convert::err_wstring(error_code);
        return result;
    }
} // namespace YanLib::io
