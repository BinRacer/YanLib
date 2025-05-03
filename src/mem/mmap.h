//
// Created by forkernel on 2025/4/4.
//

#ifndef MMAP_H
#define MMAP_H
#include <Windows.h>
#include <string>
#include <vector>
#include "sync/rwlock.h"

namespace YanLib::mem {
    class mmap {
    private:
        std::vector<HANDLE> file_handles = {};
        std::vector<HANDLE> mmap_handles = {};
        std::vector<void *> addr_list = {};
        sync::rwlock file_rwlock = {};
        sync::rwlock mmap_rwlock = {};
        sync::rwlock addr_rwlock = {};
        DWORD error_code = 0;

    public:
        mmap(const mmap &other) = delete;

        mmap(mmap &&other) noexcept = delete;

        mmap &operator=(const mmap &other) = delete;

        mmap &operator=(mmap &&other) noexcept = delete;

        mmap() = default;

        ~mmap();

        HANDLE create(const wchar_t *file_name,
                      const wchar_t *mmap_name = nullptr,
                      SECURITY_ATTRIBUTES* file_mapping_attrs = nullptr,
                      DWORD protect_flag = PAGE_READWRITE,
                      DWORD max_high = 0,
                      DWORD max_low = 0);

        HANDLE create(HANDLE file_handle = INVALID_HANDLE_VALUE,
                      const wchar_t *mmap_name = nullptr,
                      SECURITY_ATTRIBUTES* file_mapping_attrs = nullptr,
                      DWORD protect_flag = PAGE_READWRITE,
                      DWORD max_high = 0,
                      DWORD max_low = 0);

        HANDLE open(const wchar_t *mmap_name,
                    DWORD desired_access = FILE_MAP_READ | FILE_MAP_WRITE,
                    bool is_inherit_handle = false);

        void *mmap_file(HANDLE mmap_handle,
                        DWORD desired_access = FILE_MAP_READ | FILE_MAP_WRITE,
                        DWORD file_offset_high = 0,
                        DWORD file_offset_low = 0,
                        SIZE_T size = 0);

        bool unmap_file(void *addr);

        bool read(void *addr,
                  uint8_t *buf,
                  int64_t size,
                  uint64_t offset = 0) const;

        bool write(void *addr,
                   uint8_t *buf,
                   int64_t size,
                   uint64_t offset = 0) const;

        [[nodiscard]] DWORD err_code() const;

        [[nodiscard]] std::string err_string() const;

        [[nodiscard]] std::wstring err_wstring() const;
    };
}
#endif //MMAP_H
