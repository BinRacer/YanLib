//
// Created by forkernel on 2025/4/4.
//

#ifndef MMAP_H
#define MMAP_H
#include <Windows.h>
#include <string>

namespace YanLib::mem {
    class mmap {
    private:
        HANDLE file_handle;
        HANDLE map_file_handle;
        uint8_t *address;
        DWORD error_code;

    public:
        mmap(const mmap &other) = delete;

        mmap(mmap &&other) noexcept = delete;

        mmap &operator=(const mmap &other) = delete;

        mmap &operator=(mmap &&other) noexcept = delete;

        mmap();

        ~mmap();

        bool create(const wchar_t *file_name,
                    const wchar_t *mmap_name = nullptr,
                    LPSECURITY_ATTRIBUTES file_mapping_attrs = nullptr,
                    DWORD protect_flag = PAGE_READWRITE,
                    DWORD max_high = 0,
                    DWORD max_low = 0);

        bool open(const wchar_t *mmap_name,
                  DWORD desired_access = FILE_MAP_READ | FILE_MAP_WRITE,
                  bool is_inherit_handle = false);

        int64_t size();

        bool mmap_file(DWORD desired_access = FILE_MAP_READ | FILE_MAP_WRITE,
                       DWORD file_offset_high = 0,
                       DWORD file_offset_low = 0,
                       SIZE_T size = 0);

        bool unmap_file();

        bool read(uint8_t *buf, int64_t size, uint64_t offset = 0) const;

        bool write(uint8_t *buf, int64_t size, uint64_t offset = 0) const;

        [[nodiscard]] DWORD err_code() const;

        [[nodiscard]] std::string err_string() const;

        [[nodiscard]] std::wstring err_wstring() const;
    };
}
#endif //MMAP_H
