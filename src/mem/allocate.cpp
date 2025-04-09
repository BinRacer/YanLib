//
// Created by forkernel on 2025/4/4.
//

#include "allocate.h"
#include "../helper/convert.h"

namespace YanLib::mem {
    allocate::allocate(): lpMemory({}),
                          error_code(0) {
    }

    allocate::~allocate() {
        rwlock.write_lock();
        if (!lpMemory.empty()) {
            while (lpMemory.back() != nullptr) {
                VirtualFree(lpMemory.back(),
                            0,
                            MEM_RELEASE);
                lpMemory.back() = nullptr;
                lpMemory.pop_back();
            }
        }
        rwlock.write_unlock();
    }

    void *allocate::malloc(size_t dwSize) {
        void *lpAddr = VirtualAlloc(nullptr,
                                    dwSize,
                                    MEM_RESERVE | MEM_COMMIT,
                                    PAGE_READWRITE);
        if (!lpAddr) {
            error_code = GetLastError();
            return nullptr;
        }
        rwlock.write_lock();
        lpMemory.push_back(lpAddr);
        rwlock.write_unlock();
        return lpAddr;
    }

    bool allocate::free(void *lpAddr) {
        rwlock.write_lock();
        lpMemory.remove_if([lpAddr](void *ele)-> bool {
            return ele == lpAddr;
        });
        rwlock.write_unlock();
        if (!VirtualFree(lpAddr,
                         0,
                         MEM_RELEASE)) {
            error_code = GetLastError();
            return false;
        }
        lpAddr = nullptr;
        return true;
    }

    void *allocate::malloc_reserve(size_t dwSize) {
        void *lpAddr = VirtualAlloc(nullptr,
                                    dwSize,
                                    MEM_RESERVE,
                                    PAGE_READWRITE);
        if (!lpAddr) {
            error_code = GetLastError();
            return nullptr;
        }
        rwlock.write_lock();
        lpMemory.push_back(lpAddr);
        rwlock.write_unlock();
        return lpAddr;
    }

    bool allocate::free_reserve(void *lpAddr, size_t dwSize) {
        rwlock.write_lock();
        lpMemory.remove_if([lpAddr](void *ele)-> bool {
            return ele == lpAddr;
        });
        rwlock.write_unlock();
        if (!VirtualFree(lpAddr,
                         dwSize,
                         MEM_DECOMMIT)) {
            error_code = GetLastError();
            return false;
        }
        lpAddr = nullptr;
        return true;
    }

    void *allocate::realloc(void *lpOldAddr, size_t dwNewSize) {
        free(lpOldAddr);
        return malloc(dwNewSize);
    }

    DWORD allocate::err_code() const {
        return error_code;
    }

    std::string allocate::err_string() const {
        std::string result = helper::convert::err_string(error_code);
        return result;
    }

    std::wstring allocate::err_wstring() const {
        std::wstring result = helper::convert::err_wstring(error_code);
        return result;
    }
}
