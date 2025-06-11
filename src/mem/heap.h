/* clang-format off */
/*
 * @file heap.h
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
#ifndef HEAP_H
#define HEAP_H
#include <Windows.h>
#include <string>
#include <vector>
#include "sync/rwlock.h"

namespace YanLib::mem {
    class heap {
        std::vector<HANDLE> heap_handles = {};
        std::vector<std::pair<HANDLE, void *>> mem_list = {};
        sync::rwlock heap_rwlock = {};
        sync::rwlock mem_rwlock = {};
        uint32_t error_code = 0;

    public:
        heap(const heap &other) = delete;

        heap(heap &&other) = delete;

        heap &operator=(const heap &other) = delete;

        heap &operator=(heap &&other) = delete;

        heap() = default;

        ~heap();

        HANDLE create(uint32_t options = 0,
                      size_t initial_size = 0,
                      size_t maximum_size = 0);

        HANDLE open();

        void *malloc(HANDLE heap_handle, size_t size);

        void *realloc(HANDLE heap_handle, void *addr, size_t new_size);

        bool free(HANDLE heap_handle, void *addr);

        size_t size(HANDLE heap_handle, const void *addr) const;

        bool is_ok(HANDLE heap_handle, const void *addr) const;

        bool lock(HANDLE heap_handle);

        bool unlock(HANDLE heap_handle);

        [[nodiscard]] uint32_t err_code() const;

        [[nodiscard]] std::string err_string() const;

        [[nodiscard]] std::wstring err_wstring() const;
    };
} // namespace YanLib::mem
#endif // HEAP_H
