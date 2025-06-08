//
// Created by forkernel on 2025/4/4.
//

#include "allocate.h"
#include <Windows.h>
#include "helper/convert.h"

namespace YanLib::mem {
    allocate::~allocate() {
        for (auto &mem : mem_list) {
            if (mem) {
                VirtualFree(mem, 0, MEM_RELEASE);
                mem = nullptr;
            }
        }
    }

    void *allocate::malloc(size_t size) {
        void *address = VirtualAlloc(nullptr, size, MEM_RESERVE | MEM_COMMIT,
                                     PAGE_READWRITE);
        if (!address) {
            error_code = GetLastError();
            return nullptr;
        }
        rwlock.write_lock();
        mem_list.push_back(address);
        rwlock.write_unlock();
        return address;
    }

    bool allocate::free(void *addr) {
        if (!addr) {
            return false;
        }
        rwlock.write_lock();
        if (const auto it = std::find(mem_list.begin(), mem_list.end(), addr);
            it != mem_list.end()) {
            *it = nullptr;
        }
        rwlock.write_unlock();
        if (!VirtualFree(addr, 0, MEM_RELEASE)) {
            error_code = GetLastError();
            return false;
        }
        addr = nullptr;
        return true;
    }

    void *allocate::malloc_reserve(size_t size) {
        void *address =
                VirtualAlloc(nullptr, size, MEM_RESERVE, PAGE_READWRITE);
        if (!address) {
            error_code = GetLastError();
            return nullptr;
        }
        rwlock.write_lock();
        mem_list.push_back(address);
        rwlock.write_unlock();
        return address;
    }

    bool allocate::free_reserve(void *addr, size_t size) {
        if (!addr) {
            return false;
        }
        rwlock.write_lock();
        if (const auto it = std::find(mem_list.begin(), mem_list.end(), addr);
            it != mem_list.end()) {
            *it = nullptr;
        }
        rwlock.write_unlock();
        if (!VirtualFree(addr, size, MEM_DECOMMIT)) {
            error_code = GetLastError();
            return false;
        }
        addr = nullptr;
        return true;
    }

    void *allocate::realloc(void *old_addr, size_t new_size) {
        free(old_addr);
        return malloc(new_size);
    }

    uint32_t allocate::err_code() const {
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
} // namespace YanLib::mem
