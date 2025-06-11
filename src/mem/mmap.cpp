/* clang-format off */
/*
 * @file mmap.cpp
 * @date 2025-04-04
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
#include "mmap.h"
#include "helper/convert.h"

namespace YanLib::mem {
    mmap::~mmap() {
        for (auto &addr : addr_list) {
            if (addr) {
                UnmapViewOfFile(addr);
                addr = nullptr;
            }
        }
        addr_list.clear();
        for (auto &mmap_handle : mmap_handles) {
            CloseHandle(mmap_handle);
            mmap_handle = nullptr;
        }
        mmap_handles.clear();
        for (auto &file_handle : file_handles) {
            CloseHandle(file_handle);
            file_handle = INVALID_HANDLE_VALUE;
        }
        file_handles.clear();
    }

    HANDLE mmap::create(const char *file_name,
                        const char *mmap_name,
                        SECURITY_ATTRIBUTES *sa,
                        MemoryProtect protect,
                        const uint32_t max_high,
                        const uint32_t max_low) {
        HANDLE file_handle =
                CreateFileA(file_name, GENERIC_READ | GENERIC_WRITE,
                            FILE_SHARE_READ | FILE_SHARE_WRITE, nullptr,
                            OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
        if (file_handle == INVALID_HANDLE_VALUE) {
            error_code = GetLastError();
            return nullptr;
        }
        file_rwlock.write_lock();
        file_handles.push_back(file_handle);
        file_rwlock.write_unlock();
        HANDLE mmap_handle = CreateFileMappingA(file_handle, sa,
                                                static_cast<uint32_t>(protect),
                                                max_high, max_low, mmap_name);
        if (!mmap_handle) {
            error_code = GetLastError();
            return nullptr;
        }
        mmap_rwlock.write_lock();
        mmap_handles.push_back(mmap_handle);
        mmap_rwlock.write_unlock();
        return mmap_handle;
    }

    HANDLE mmap::create(const wchar_t *file_name,
                        const wchar_t *mmap_name,
                        SECURITY_ATTRIBUTES *sa,
                        MemoryProtect protect,
                        const uint32_t max_high,
                        const uint32_t max_low) {
        HANDLE file_handle =
                CreateFileW(file_name, GENERIC_READ | GENERIC_WRITE,
                            FILE_SHARE_READ | FILE_SHARE_WRITE, nullptr,
                            OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
        if (file_handle == INVALID_HANDLE_VALUE) {
            error_code = GetLastError();
            return nullptr;
        }
        file_rwlock.write_lock();
        file_handles.push_back(file_handle);
        file_rwlock.write_unlock();
        HANDLE mmap_handle = CreateFileMappingW(file_handle, sa,
                                                static_cast<uint32_t>(protect),
                                                max_high, max_low, mmap_name);
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
                        const char *mmap_name,
                        SECURITY_ATTRIBUTES *sa,
                        MemoryProtect protect,
                        const uint32_t max_high,
                        const uint32_t max_low) {
        HANDLE mmap_handle = CreateFileMappingA(file_handle, sa,
                                                static_cast<uint32_t>(protect),
                                                max_high, max_low, mmap_name);
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
                        SECURITY_ATTRIBUTES *sa,
                        MemoryProtect protect,
                        const uint32_t max_high,
                        const uint32_t max_low) {
        HANDLE mmap_handle = CreateFileMappingW(file_handle, sa,
                                                static_cast<uint32_t>(protect),
                                                max_high, max_low, mmap_name);
        if (!mmap_handle) {
            error_code = GetLastError();
            return nullptr;
        }
        mmap_rwlock.write_lock();
        mmap_handles.push_back(mmap_handle);
        mmap_rwlock.write_unlock();
        return mmap_handle;
    }

    HANDLE
    mmap::open(const char *mmap_name,
               MemoryAccess access,
               const bool is_inherit) {
        HANDLE mmap_handle =
                OpenFileMappingA(static_cast<uint32_t>(access),
                                 is_inherit ? TRUE : FALSE, mmap_name);
        if (!mmap_handle) {
            error_code = GetLastError();
            return nullptr;
        }
        mmap_rwlock.write_lock();
        mmap_handles.push_back(mmap_handle);
        mmap_rwlock.write_unlock();
        return mmap_handle;
    }

    HANDLE
    mmap::open(const wchar_t *mmap_name,
               MemoryAccess access,
               const bool is_inherit) {
        HANDLE mmap_handle =
                OpenFileMappingW(static_cast<uint32_t>(access),
                                 is_inherit ? TRUE : FALSE, mmap_name);
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
                          MemoryAccess access,
                          const uint32_t offset_high,
                          const uint32_t offset_low,
                          const SIZE_T size) {
        void *address =
                MapViewOfFile(mmap_handle, static_cast<uint32_t>(access),
                              offset_high, offset_low, size);
        if (!address) {
            error_code = GetLastError();
            return nullptr;
        }
        addr_rwlock.write_lock();
        addr_list.push_back(address);
        addr_rwlock.write_unlock();
        return address;
    }

    bool mmap::unmap_file(const void *addr) {
        if (!addr) {
            return false;
        }
        addr_rwlock.write_lock();
        if (const auto it = std::find(addr_list.begin(), addr_list.end(), addr);
            it != addr_list.end()) {
            *it = nullptr;
        }
        addr_rwlock.write_unlock();
        if (!UnmapViewOfFile(addr)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool mmap::read(void *addr,
                    uint8_t *buf,
                    const int64_t size,
                    const uint64_t offset) const {
        if (!buf || !addr) {
            return false;
        }
        memcpy_s(buf, size, static_cast<uint8_t *>(addr) + offset, size);
        return true;
    }

    bool mmap::write(void *addr,
                     const uint8_t *buf,
                     const int64_t size,
                     const uint64_t offset) const {
        if (!buf || !addr) {
            return false;
        }
        memcpy_s(static_cast<uint8_t *>(addr) + offset, size, buf, size);
        FlushViewOfFile(addr, 0);
        return true;
    }

    uint32_t mmap::err_code() const {
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
} // namespace YanLib::mem
