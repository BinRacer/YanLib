/* clang-format off */
/*
 * @file heap.cpp
 * @date 2025-04-04
 * @license MIT License
 *
 * Copyright (c) 2025 BinRacer <native.lab@outlook.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
/* clang-format on */
#include "heap.h"
#include "helper/convert.h"

namespace YanLib::mem {
    heap::~heap() {
        if (!mem_list.empty()) {
            for (auto &[heap_handle, mem] : mem_list) {
                if (heap_handle && mem) {
                    HeapFree(heap_handle, 0, mem);
                    mem = nullptr;
                }
            }
        }
        if (!heap_handles.empty()) {
            for (auto &heap_handle : heap_handles) {
                if (heap_handle) {
                    HeapDestroy(heap_handle);
                    heap_handle = nullptr;
                }
            }
            heap_handles.clear();
        }
    }

    HANDLE
    heap::create(const uint32_t options,
                 const size_t initial_size,
                 const size_t maximum_size) {
        HANDLE heap_handle = HeapCreate(options, initial_size, maximum_size);
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

    void *heap::malloc(HANDLE heap_handle, size_t size) {
        void *addr = HeapAlloc(heap_handle, HEAP_ZERO_MEMORY, size);
        if (!addr) {
            return nullptr;
        }
        mem_rwlock.write_lock();
        mem_list.emplace_back(heap_handle, addr);
        mem_rwlock.write_unlock();
        return addr;
    }

    void *heap::realloc(HANDLE heap_handle, void *addr, size_t new_size) {
        void *address =
                HeapReAlloc(heap_handle, HEAP_ZERO_MEMORY, addr, new_size);
        if (!address) {
            return nullptr;
        }
        mem_rwlock.write_lock();
        mem_list.emplace_back(heap_handle, address);
        mem_rwlock.write_unlock();
        return address;
    }

    bool heap::free(HANDLE heap_handle, void *addr) {
        if (!heap_handle || !addr) {
            return false;
        }
        mem_rwlock.write_lock();
        const auto it = std::find(mem_list.begin(), mem_list.end(),
                                  std::make_pair(heap_handle, addr));
        if (it != mem_list.end()) {
            *it = std::make_pair(nullptr, nullptr);
        }
        mem_rwlock.write_unlock();
        if (!HeapFree(heap_handle, 0, addr)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    size_t heap::size(HANDLE heap_handle, const void *addr) const {
        return HeapSize(heap_handle, 0, addr);
    }

    bool heap::is_ok(HANDLE heap_handle, const void *addr) const {
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

    uint32_t heap::err_code() const {
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
} // namespace YanLib::mem
