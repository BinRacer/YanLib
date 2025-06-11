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
#include <string>
#include <vector>
#include "sync/rwlock.h"

namespace YanLib::mem {
#ifndef MEMORYPROTECT
#define MEMORYPROTECT

    enum class MemoryProtect : uint32_t {
        // page
        NoAccess = PAGE_NOACCESS,
        ReadOnly = PAGE_READONLY,
        ReadWrite = PAGE_READWRITE,
        WriteCopy = PAGE_WRITECOPY,
        Execute = PAGE_EXECUTE,
        ExecuteRead = PAGE_EXECUTE_READ,
        ExecuteReadWrite = PAGE_EXECUTE_READWRITE,
        ExecuteWriteCopy = PAGE_EXECUTE_WRITECOPY,
        Guard = PAGE_GUARD,
        NoCache = PAGE_NOCACHE,
        WriteCombine = PAGE_WRITECOMBINE,
        GraphicsNoAccess = PAGE_GRAPHICS_NOACCESS,
        GraphicsReadOnly = PAGE_GRAPHICS_READONLY,
        GraphicsReadWrite = PAGE_GRAPHICS_READWRITE,
        GraphicsExecute = PAGE_GRAPHICS_EXECUTE,
        GraphicsExecuteRead = PAGE_GRAPHICS_EXECUTE_READ,
        GraphicsExecuteReadWrite = PAGE_GRAPHICS_EXECUTE_READWRITE,
        GraphicsCoherent = PAGE_GRAPHICS_COHERENT,
        GraphicsNoCache = PAGE_GRAPHICS_NOCACHE,
        EnclaveThreadControl = PAGE_ENCLAVE_THREAD_CONTROL,
        RevertToFileMap = PAGE_REVERT_TO_FILE_MAP,
        TargetsNoUpdate = PAGE_TARGETS_NO_UPDATE,
        TargetsInvalid = PAGE_TARGETS_INVALID,
        EnclaveUnvalidated = PAGE_ENCLAVE_UNVALIDATED,
        EnclaveMask = PAGE_ENCLAVE_MASK,
        EnclaveDeCommit = PAGE_ENCLAVE_DECOMMIT,
        EnclaveSSFirst = PAGE_ENCLAVE_SS_FIRST,
        EnclaveSSRest = PAGE_ENCLAVE_SS_REST,
        // security
        SecHugePages = SEC_HUGE_PAGES,
        SecPartitionOwnerHandle = SEC_PARTITION_OWNER_HANDLE,
        Sec64kPages = SEC_64K_PAGES,
        SecFile = SEC_FILE,
        SecImage = SEC_IMAGE,
        SecProtectedImage = SEC_PROTECTED_IMAGE,
        SecReserve = SEC_RESERVE,
        SecCommit = SEC_COMMIT,
        SecNoCache = SEC_NOCACHE,
        SecWriteCombine = SEC_WRITECOMBINE,
        SecLargePages = SEC_LARGE_PAGES,
        SecImageNoExecute = SEC_IMAGE_NO_EXECUTE,
    };

    inline MemoryProtect operator|(MemoryProtect a, MemoryProtect b) {
        return static_cast<MemoryProtect>(static_cast<uint32_t>(a) |
                                          static_cast<uint32_t>(b));
    }
#endif
#ifndef MEMORYACCESS
#define MEMORYACCESS

    enum class MemoryAccess : uint32_t {
        Read = FILE_MAP_READ,
        Write = FILE_MAP_WRITE,
        Execute = FILE_MAP_EXECUTE,
        AllAccess = FILE_MAP_ALL_ACCESS,
        Copy = FILE_MAP_COPY,
        Reserve = FILE_MAP_RESERVE,
        TargetsInvalid = FILE_MAP_TARGETS_INVALID,
        LargePages = FILE_MAP_LARGE_PAGES,
    };

    inline MemoryAccess operator|(MemoryAccess a, MemoryAccess b) {
        return static_cast<MemoryAccess>(static_cast<uint32_t>(a) |
                                         static_cast<uint32_t>(b));
    }
#endif

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
