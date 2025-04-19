//
// Created by forkernel on 2025/4/4.
//

#include "allocate.h"
#include "helper/convert.h"

namespace YanLib::mem {
    allocate::allocate(): memory_ptr_list({}),
                          error_code(0) {
    }

    allocate::~allocate() {
        rwlock.write_lock();
        if (!memory_ptr_list.empty()) {
            while (memory_ptr_list.back() != nullptr) {
                VirtualFree(memory_ptr_list.back(),
                            0,
                            MEM_RELEASE);
                memory_ptr_list.back() = nullptr;
                memory_ptr_list.pop_back();
            }
        }
        rwlock.write_unlock();
    }

    void *allocate::malloc(size_t size) {
        void *address = VirtualAlloc(nullptr,
                                     size,
                                     MEM_RESERVE | MEM_COMMIT,
                                     PAGE_READWRITE);
        if (!address) {
            error_code = GetLastError();
            return nullptr;
        }
        rwlock.write_lock();
        memory_ptr_list.push_back(address);
        rwlock.write_unlock();
        return address;
    }

    bool allocate::free(void *addr) {
        rwlock.write_lock();
        memory_ptr_list.remove_if([addr](void *ele)-> bool {
            return ele == addr;
        });
        rwlock.write_unlock();
        if (!VirtualFree(addr,
                         0,
                         MEM_RELEASE)) {
            error_code = GetLastError();
            return false;
        }
        addr = nullptr;
        return true;
    }

    void *allocate::malloc_reserve(size_t size) {
        void *address = VirtualAlloc(nullptr,
                                     size,
                                     MEM_RESERVE,
                                     PAGE_READWRITE);
        if (!address) {
            error_code = GetLastError();
            return nullptr;
        }
        rwlock.write_lock();
        memory_ptr_list.push_back(address);
        rwlock.write_unlock();
        return address;
    }

    bool allocate::free_reserve(void *addr, size_t size) {
        rwlock.write_lock();
        memory_ptr_list.remove_if([addr](void *ele)-> bool {
            return ele == addr;
        });
        rwlock.write_unlock();
        if (!VirtualFree(addr,
                         size,
                         MEM_DECOMMIT)) {
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
