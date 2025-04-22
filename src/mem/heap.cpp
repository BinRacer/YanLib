//
// Created by forkernel on 2025/4/4.
//

#include "heap.h"
#include "helper/convert.h"

namespace YanLib::mem {
    heap::~heap() {
        if (!heap_handles.empty()) {
            for (auto &heap_handle: heap_handles) {
                HeapDestroy(heap_handle);
                heap_handle = nullptr;
            }
            heap_handles.clear();
        }
    }

    HANDLE heap::create(DWORD options,
                        size_t initial_size,
                        size_t maximum_size) {
        HANDLE heap_handle = HeapCreate(options,
                                        initial_size,
                                        maximum_size);
        if (!heap_handle) {
            error_code = GetLastError();
            return nullptr;
        }
        heap_rwlock.write_lock();
        heap_handles.push_back(heap_handle);
        heap_rwlock.write_unlock();
        return heap_handle;
    }

    HANDLE heap::open() {
        HANDLE heap_handle = GetProcessHeap();
        if (!heap_handle) {
            error_code = GetLastError();
            return nullptr;
        }
        heap_rwlock.write_lock();
        heap_handles.push_back(heap_handle);
        heap_rwlock.write_unlock();
        return heap_handle;
    }

    void *heap::malloc(HANDLE heap_handle,
                       size_t size) const {
        return HeapAlloc(heap_handle,
                         HEAP_ZERO_MEMORY,
                         size);
    }

    void *heap::realloc(HANDLE heap_handle,
                        void *addr,
                        size_t new_size) const {
        return HeapReAlloc(heap_handle,
                           HEAP_ZERO_MEMORY,
                           addr,
                           new_size);
    }

    bool heap::free(HANDLE heap_handle, void *addr) {
        if (!HeapFree(heap_handle, 0, addr)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    size_t heap::size(HANDLE heap_handle, void *addr) const {
        return HeapSize(heap_handle, 0, addr);
    }

    bool heap::is_ok(HANDLE heap_handle, void *addr) const {
        return HeapValidate(heap_handle, 0, addr);
    }

    bool heap::lock(HANDLE heap_handle) {
        if (!HeapLock(heap_handle)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool heap::unlock(HANDLE heap_handle) {
        if (!HeapUnlock(heap_handle)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    DWORD heap::err_code() const {
        return error_code;
    }

    std::string heap::err_string() const {
        std::string result = helper::convert::err_string(error_code);
        return result;
    }

    std::wstring heap::err_wstring() const {
        std::wstring result = helper::convert::err_wstring(error_code);
        return result;
    }
}
