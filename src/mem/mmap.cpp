//
// Created by forkernel on 2025/4/4.
//

#include "mmap.h"
#include "helper/convert.h"

namespace YanLib::mem {
    mmap::mmap()
        : file_handle(INVALID_HANDLE_VALUE),
          map_file_handle(nullptr),
          address(nullptr),
          error_code(0) {
    }

    mmap::~mmap() {
        if (address) {
            UnmapViewOfFile(address);
            address = nullptr;
        }
        if (map_file_handle) {
            CloseHandle(map_file_handle);
            map_file_handle = nullptr;
        }
        if (file_handle != INVALID_HANDLE_VALUE) {
            CloseHandle(file_handle);
            file_handle = INVALID_HANDLE_VALUE;
        }
    }

    bool mmap::create(const wchar_t *file_name,
                      const wchar_t *mmap_name,
                      LPSECURITY_ATTRIBUTES file_mapping_attrs,
                      DWORD protect_flag,
                      DWORD max_high,
                      DWORD max_low) {
        // avoid create map twice
        if (file_handle != INVALID_HANDLE_VALUE || map_file_handle) {
            return false;
        }

        file_handle = CreateFileW(file_name,
                            GENERIC_READ | GENERIC_WRITE,
                            FILE_SHARE_READ | FILE_SHARE_WRITE,
                            nullptr,
                            OPEN_EXISTING,
                            FILE_ATTRIBUTE_NORMAL,
                            nullptr);
        if (file_handle == INVALID_HANDLE_VALUE) {
            error_code = GetLastError();
            return false;
        }
        map_file_handle = CreateFileMappingW(file_handle,
                                      file_mapping_attrs,
                                      protect_flag,
                                      max_high,
                                      max_low,
                                      mmap_name);
        if (!map_file_handle) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool mmap::open(const wchar_t *mmap_name,
                    DWORD desired_access,
                    BOOL is_inherit_handle) {
        // avoid open map twice
        if (file_handle != INVALID_HANDLE_VALUE || map_file_handle) {
            return false;
        }

        map_file_handle = OpenFileMappingW(desired_access,
                                    is_inherit_handle,
                                    mmap_name);
        if (!map_file_handle) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    int64_t mmap::size() {
        if (file_handle == INVALID_HANDLE_VALUE) {
            return 0;
        }
        LARGE_INTEGER file_size{};
        if (!GetFileSizeEx(file_handle, &file_size)) {
            error_code = GetLastError();
        }
        return file_size.QuadPart;
    }

    bool mmap::mmap_file(DWORD desired_access,
                         DWORD file_offset_high,
                         DWORD file_offset_low,
                         SIZE_T size) {
        address = static_cast<uint8_t *>(MapViewOfFile(map_file_handle,
                                                        desired_access,
                                                        file_offset_high,
                                                        file_offset_low,
                                                        size));
        if (!address) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool mmap::unmap_file() {
        if (!UnmapViewOfFile(address)) {
            error_code = GetLastError();
            return false;
        }
        address = nullptr;
        return true;
    }

    bool mmap::read(uint8_t *buf, int64_t size, uint64_t offset) const {
        if (!buf && !address) {
            return false;
        }
        memcpy_s(buf,
                 size,
                 address + offset,
                 size);
        return true;
    }

    bool mmap::write(uint8_t *buf, int64_t size, uint64_t offset) const {
        if (!buf && !address) {
            return false;
        }
        memcpy_s(address + offset,
                 size,
                 buf,
                 size);
        FlushViewOfFile(address, 0);
        return true;
    }

    DWORD mmap::err_code() const {
        return error_code;
    }

    std::string mmap::err_string() const {
        std::string result = helper::convert::err_string(error_code);
        return result;
    }

    std::wstring mmap::err_wstring() const {
        std::wstring result = helper::convert::err_wstring(error_code);
        return result;
    }
}
