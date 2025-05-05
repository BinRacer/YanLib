//
// Created by forkernel on 2025/4/4.
//

#include "mmap.h"
#include "helper/convert.h"

namespace YanLib::mem {
    mmap::~mmap() {
        if (!addr_list.empty()) {
            for (auto &addr: addr_list) {
                if (addr) {
                    UnmapViewOfFile(addr);
                    addr = nullptr;
                }
            }
            addr_list.clear();
        }
        if (!mmap_handles.empty()) {
            for (auto &mmap_handle: mmap_handles) {
                CloseHandle(mmap_handle);
                mmap_handle = nullptr;
            }
            mmap_handles.clear();
        }
        if (!file_handles.empty()) {
            for (auto &file_handle: file_handles) {
                CloseHandle(file_handle);
                file_handle = INVALID_HANDLE_VALUE;
            }
            file_handles.clear();
        }
    }

    HANDLE mmap::create(const wchar_t *file_name,
                        const wchar_t *mmap_name,
                        SECURITY_ATTRIBUTES *file_mapping_attrs,
                        unsigned long protect_flag,
                        unsigned long max_high,
                        unsigned long max_low) {
        HANDLE file_handle = CreateFileW(file_name,
                                         GENERIC_READ | GENERIC_WRITE,
                                         FILE_SHARE_READ | FILE_SHARE_WRITE,
                                         nullptr,
                                         OPEN_EXISTING,
                                         FILE_ATTRIBUTE_NORMAL,
                                         nullptr);
        if (file_handle == INVALID_HANDLE_VALUE) {
            error_code = GetLastError();
            return nullptr;
        }
        file_rwlock.write_lock();
        file_handles.push_back(file_handle);
        file_rwlock.write_unlock();
        HANDLE mmap_handle = CreateFileMappingW(file_handle,
                                                file_mapping_attrs,
                                                protect_flag,
                                                max_high,
                                                max_low,
                                                mmap_name);
        if (!mmap_handle) {
            error_code = GetLastError();
            return nullptr;
        }
        mmap_rwlock.write_lock();
        mmap_handles.push_back(mmap_handle);
        mmap_rwlock.write_unlock();
        return mmap_handle;
    }

    HANDLE mmap::create(HANDLE file_handle,
                        const wchar_t *mmap_name,
                        SECURITY_ATTRIBUTES *file_mapping_attrs,
                        unsigned long protect_flag,
                        unsigned long max_high,
                        unsigned long max_low) {
        HANDLE mmap_handle = CreateFileMappingW(file_handle,
                                                file_mapping_attrs,
                                                protect_flag,
                                                max_high,
                                                max_low,
                                                mmap_name);
        if (!mmap_handle) {
            error_code = GetLastError();
            return nullptr;
        }
        mmap_rwlock.write_lock();
        mmap_handles.push_back(mmap_handle);
        mmap_rwlock.write_unlock();
        return mmap_handle;
    }

    HANDLE mmap::open(const wchar_t *mmap_name,
                      unsigned long desired_access,
                      bool is_inherit_handle) {
        HANDLE mmap_handle = OpenFileMappingW(desired_access,
                                              is_inherit_handle ? TRUE : FALSE,
                                              mmap_name);
        if (!mmap_handle) {
            error_code = GetLastError();
            return nullptr;
        }
        mmap_rwlock.write_lock();
        mmap_handles.push_back(mmap_handle);
        mmap_rwlock.write_unlock();
        return mmap_handle;
    }

    void *mmap::mmap_file(HANDLE mmap_handle,
                          unsigned long desired_access,
                          unsigned long file_offset_high,
                          unsigned long file_offset_low,
                          SIZE_T size) {
        void *address = MapViewOfFile(mmap_handle,
                                      desired_access,
                                      file_offset_high,
                                      file_offset_low,
                                      size);
        if (!address) {
            error_code = GetLastError();
            return nullptr;
        }
        addr_rwlock.write_lock();
        addr_list.push_back(address);
        addr_rwlock.write_unlock();
        return address;
    }

    bool mmap::unmap_file(void *addr) {
        if (!UnmapViewOfFile(addr)) {
            error_code = GetLastError();
            return false;
        }
        addr_rwlock.write_lock();
        const auto it = std::find(addr_list.begin(),
                                  addr_list.end(),
                                  addr);
        if (it != addr_list.end()) {
            *it = nullptr;
        }
        addr_rwlock.write_unlock();
        return true;
    }

    bool mmap::read(void *addr,
                    uint8_t *buf,
                    int64_t size,
                    uint64_t offset) const {
        if (!buf || !addr) {
            return false;
        }
        memcpy_s(buf,
                 size,
                 static_cast<uint8_t *>(addr) + offset,
                 size);
        return true;
    }

    bool mmap::write(void *addr,
                     uint8_t *buf,
                     int64_t size,
                     uint64_t offset) const {
        if (!buf || !addr) {
            return false;
        }
        memcpy_s(static_cast<uint8_t *>(addr) + offset,
                 size,
                 buf,
                 size);
        FlushViewOfFile(addr, 0);
        return true;
    }

    unsigned long mmap::err_code() const {
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
