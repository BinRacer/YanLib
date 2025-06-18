/* clang-format off */
/*
 * @file mmap.h
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
#ifndef MMAP_H
#define MMAP_H
#include <Windows.h>
#include <winnt.h>
#include <minwinbase.h>
#include <string>
#include <vector>
#include "sync/rwlock.h"
#include "mem.h"
namespace YanLib::mem {
    class mmap {
    private:
        std::vector<HANDLE> file_handles = {};
        std::vector<HANDLE> mmap_handles = {};
        std::vector<void *> addr_list = {};
        sync::rwlock file_rwlock = {};
        sync::rwlock mmap_rwlock = {};
        sync::rwlock addr_rwlock = {};
        uint32_t error_code = 0;

    public:
        mmap(const mmap &other) = delete;

        mmap(mmap &&other) noexcept = delete;

        mmap &operator=(const mmap &other) = delete;

        mmap &operator=(mmap &&other) noexcept = delete;

        mmap() = default;

        ~mmap();

        HANDLE create(const char *file_name,
                      const char *mmap_name = nullptr,
                      SECURITY_ATTRIBUTES *sa = nullptr,
                      MemoryProtect protect = MemoryProtect::ReadWrite,
                      uint32_t max_high = 0,
                      uint32_t max_low = 0);

        HANDLE create(const wchar_t *file_name,
                      const wchar_t *mmap_name = nullptr,
                      SECURITY_ATTRIBUTES *sa = nullptr,
                      MemoryProtect protect = MemoryProtect::ReadWrite,
                      uint32_t max_high = 0,
                      uint32_t max_low = 0);

        HANDLE create(HANDLE file_handle,
                      const char *mmap_name,
                      SECURITY_ATTRIBUTES *sa = nullptr,
                      MemoryProtect protect = MemoryProtect::ReadWrite,
                      uint32_t max_high = 0,
                      uint32_t max_low = 0);

        HANDLE create(HANDLE file_handle,
                      const wchar_t *mmap_name,
                      SECURITY_ATTRIBUTES *sa = nullptr,
                      MemoryProtect protect = MemoryProtect::ReadWrite,
                      uint32_t max_high = 0,
                      uint32_t max_low = 0);

        HANDLE open(const char *mmap_name,
                    MemoryAccess access = MemoryAccess::Read |
                            MemoryAccess::Write,
                    bool is_inherit = false);

        HANDLE open(const wchar_t *mmap_name,
                    MemoryAccess access = MemoryAccess::Read |
                            MemoryAccess::Write,
                    bool is_inherit = false);

        void *mmap_file(HANDLE mmap_handle,
                        MemoryAccess access = MemoryAccess::Read |
                                MemoryAccess::Write,
                        uint32_t offset_high = 0,
                        uint32_t offset_low = 0,
                        uint64_t size = 0);

        bool unmap_file(const void *addr);

        bool
        read(void *addr, uint8_t *buf, int64_t size, uint64_t offset = 0) const;

        bool write(void *addr,
                   const uint8_t *buf,
                   int64_t size,
                   uint64_t offset = 0) const;

        [[nodiscard]] uint32_t err_code() const;

        [[nodiscard]] std::string err_string() const;

        [[nodiscard]] std::wstring err_wstring() const;
    };
} // namespace YanLib::mem
#endif // MMAP_H
