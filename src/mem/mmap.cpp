//
// Created by forkernel on 2025/4/4.
//

#include "mmap.h"
#include "helper/convert.h"

namespace YanLib::mem {
    mmap::mmap()
        : hFile(INVALID_HANDLE_VALUE),
          hMapFile(nullptr),
          lpMemory(nullptr),
          error_code(0) {
    }

    mmap::~mmap() {
        if (lpMemory) {
            UnmapViewOfFile(lpMemory);
            lpMemory = nullptr;
        }
        if (hMapFile) {
            CloseHandle(hMapFile);
            hMapFile = nullptr;
        }
        if (hFile != INVALID_HANDLE_VALUE) {
            CloseHandle(hFile);
            hFile = INVALID_HANDLE_VALUE;
        }
    }

    bool mmap::create(const wchar_t *lpFileName,
                      const wchar_t *lpName,
                      LPSECURITY_ATTRIBUTES lpFileMappingAttributes,
                      DWORD flProtect,
                      DWORD dwMaximumSizeHigh,
                      DWORD dwMaximumSizeLow) {
        // avoid create map twice
        if (hFile != INVALID_HANDLE_VALUE || hMapFile) {
            return false;
        }

        hFile = CreateFileW(lpFileName,
                            GENERIC_READ | GENERIC_WRITE,
                            FILE_SHARE_READ | FILE_SHARE_WRITE,
                            nullptr,
                            OPEN_EXISTING,
                            FILE_ATTRIBUTE_NORMAL,
                            nullptr);
        if (hFile == INVALID_HANDLE_VALUE) {
            error_code = GetLastError();
            return false;
        }
        hMapFile = CreateFileMappingW(hFile,
                                      lpFileMappingAttributes,
                                      flProtect,
                                      dwMaximumSizeHigh,
                                      dwMaximumSizeLow,
                                      lpName);
        if (!hMapFile) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool mmap::open(const wchar_t *lpName,
                    DWORD dwDesiredAccess,
                    BOOL bInheritHandle) {
        // avoid open map twice
        if (hFile != INVALID_HANDLE_VALUE || hMapFile) {
            return false;
        }

        hMapFile = OpenFileMappingW(dwDesiredAccess,
                                    bInheritHandle,
                                    lpName);
        if (!hMapFile) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    int64_t mmap::size() {
        if (hFile == INVALID_HANDLE_VALUE) {
            return 0;
        }
        LARGE_INTEGER lpFileSize{};
        if (!GetFileSizeEx(hFile, &lpFileSize)) {
            error_code = GetLastError();
        }
        return lpFileSize.QuadPart;
    }

    bool mmap::mmap_file(DWORD dwDesiredAccess,
                         DWORD dwFileOffsetHigh,
                         DWORD dwFileOffsetLow,
                         SIZE_T dwNumberOfBytesToMap) {
        lpMemory = static_cast<uint8_t *>(MapViewOfFile(hMapFile,
                                                        dwDesiredAccess,
                                                        dwFileOffsetHigh,
                                                        dwFileOffsetLow,
                                                        dwNumberOfBytesToMap));
        if (!lpMemory) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool mmap::unmap_file() {
        if (!UnmapViewOfFile(lpMemory)) {
            error_code = GetLastError();
            return false;
        }
        lpMemory = nullptr;
        return true;
    }

    bool mmap::read(uint8_t *lpBuffer, int64_t size, uint64_t offset) const {
        if (!lpBuffer && !lpMemory) {
            return false;
        }
        memcpy_s(lpBuffer,
                 size,
                 lpMemory + offset,
                 size);
        return true;
    }

    bool mmap::write(uint8_t *lpBuffer, int64_t size, uint64_t offset) const {
        if (!lpBuffer && !lpMemory) {
            return false;
        }
        memcpy_s(lpMemory + offset,
                 size,
                 lpBuffer,
                 size);
        FlushViewOfFile(lpMemory, 0);
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
