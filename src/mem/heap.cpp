//
// Created by forkernel on 2025/4/4.
//

#include "heap.h"
#include "helper/convert.h"

namespace YanLib::mem {
    heap::heap() : heap_handle(nullptr), error_code(0) {
    }

    heap::~heap() {
        if (heap_handle) {
            HeapDestroy(heap_handle);
            heap_handle = nullptr;
        }
    }

    bool heap::create(DWORD options,
                      size_t initial_size,
                      size_t maximum_size) {
        // avoid create heap twice
        if (heap_handle) {
            return false;
        }
        heap_handle = HeapCreate(options,
                                 initial_size,
                                 maximum_size);
        if (!heap_handle) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool heap::open_proc_heap() {
        // avoid open heap twice
        if (heap_handle) {
            return false;
        }
        heap_handle = GetProcessHeap();
        if (!heap_handle) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    void *heap::malloc(size_t size) const {
        // don't call GetLastError()
        return HeapAlloc(heap_handle,
                         HEAP_ZERO_MEMORY,
                         size);
    }

    void *heap::realloc(void *addr, size_t new_size) const {
        // don't call GetLastError()
        return HeapReAlloc(heap_handle,
                           HEAP_ZERO_MEMORY,
                           addr,
                           new_size);
    }

    bool heap::free(void *addr) {
        if (!HeapFree(heap_handle, 0, addr)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    size_t heap::size(void *addr) const {
        // don't call GetLastError()
        return HeapSize(heap_handle, 0, addr);
    }

    bool heap::is_ok(void *addr) const {
        // don't call GetLastError()
        return HeapValidate(heap_handle, 0, addr);
    }

    bool heap::lock() {
        if (!HeapLock(heap_handle)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool heap::unlock() {
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
