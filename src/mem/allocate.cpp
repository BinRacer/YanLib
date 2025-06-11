/* clang-format off */
/*
 * @file allocate.cpp
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
