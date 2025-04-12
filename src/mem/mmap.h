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
        HANDLE hFile;
        HANDLE hMapFile;
        uint8_t *lpMemory;
        DWORD error_code;

    public:
        mmap(const mmap &other) = delete;

        mmap(mmap &&other) noexcept = delete;

        mmap &operator=(const mmap &other) = delete;

        mmap &operator=(mmap &&other) noexcept = delete;

        mmap();

        ~mmap();

        bool create(const wchar_t *lpFileName,
                    const wchar_t *lpName = nullptr,
                    LPSECURITY_ATTRIBUTES lpFileMappingAttributes = nullptr,
                    DWORD flProtect = PAGE_READWRITE,
                    DWORD dwMaximumSizeHigh = 0,
                    DWORD dwMaximumSizeLow = 0);

        bool open(const wchar_t *lpName,
                  DWORD dwDesiredAccess = FILE_MAP_READ | FILE_MAP_WRITE,
                  BOOL bInheritHandle = FALSE);

        int64_t size();

        bool mmap_file(DWORD dwDesiredAccess = FILE_MAP_READ | FILE_MAP_WRITE,
                       DWORD dwFileOffsetHigh = 0,
                       DWORD dwFileOffsetLow = 0,
                       SIZE_T dwNumberOfBytesToMap = 0);

        bool unmap_file();

        bool read(uint8_t *lpBuffer, int64_t size, uint64_t offset = 0) const;

        bool write(uint8_t *lpBuffer, int64_t size, uint64_t offset = 0) const;

        DWORD err_code() const;

        std::string err_string() const;

        std::wstring err_wstring() const;
    };
}
#endif //MMAP_H
