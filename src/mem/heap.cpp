//
// Created by forkernel on 2025/4/4.
//

#include "heap.h"
#include "../helper/convert.h"

namespace YanLib {
    namespace mem {
        heap::heap() : hHeap(nullptr), error_code(0) {
        }

        heap::~heap() {
            if (!hHeap) {
                HeapDestroy(hHeap);
            }
        }

        bool heap::create(DWORD flOptions,
                          size_t dwInitialSize,
                          size_t dwMaximumSize) {
            // avoid create heap twice
            if (hHeap) {
                return false;
            }
            hHeap = HeapCreate(flOptions,
                               dwInitialSize,
                               dwMaximumSize);
            if (!hHeap) {
                error_code = GetLastError();
                return false;
            }
            return true;
        }

        bool heap::open_proc_heap() {
            // avoid open heap twice
            if (hHeap) {
                return false;
            }
            hHeap = GetProcessHeap();
            if (!hHeap) {
                error_code = GetLastError();
                return false;
            }
            return true;
        }

        void *heap::malloc(size_t dwBytes) const {
            // don't call GetLastError()
            return HeapAlloc(hHeap,
                             HEAP_ZERO_MEMORY,
                             dwBytes);
        }

        void *heap::realloc(void *lpMem, size_t dwNewBytes) const {
            // don't call GetLastError()
            return HeapReAlloc(hHeap,
                               HEAP_ZERO_MEMORY,
                               lpMem,
                               dwNewBytes);
        }

        bool heap::free(void *lpMem) {
            if (!HeapFree(hHeap, 0, lpMem)) {
                error_code = GetLastError();
                return false;
            }
            return true;
        }

        size_t heap::size(void *lpMem) const {
            // don't call GetLastError()
            return HeapSize(hHeap, 0, lpMem);
        }

        bool heap::is_ok(void *lpMem) const {
            // don't call GetLastError()
            return HeapValidate(hHeap, 0, lpMem);
        }

        bool heap::lock() {
            if (!HeapLock(hHeap)) {
                error_code = GetLastError();
                return false;
            }
            return true;
        }

        bool heap::unlock() {
            if (!HeapUnlock(hHeap)) {
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
}
