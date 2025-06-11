/* clang-format off */
/*
 * @file allocate.h
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
#ifndef ALLOCATE_H
#define ALLOCATE_H
#include <string>
#include <vector>
#include "sync/rwlock.h"

namespace YanLib::mem {
    class allocate {
    private:
        std::vector<void *> mem_list = {};
        sync::rwlock rwlock = {};
        uint32_t error_code = 0;

    public:
        allocate(const allocate &other) = delete;

        allocate(allocate &&other) = delete;

        allocate &operator=(const allocate &other) = delete;

        allocate &operator=(allocate &&other) = delete;

        allocate() = default;

        ~allocate();

        void *malloc(size_t size);

        bool free(void *addr);

        void *malloc_reserve(size_t size);

        bool free_reserve(void *addr, size_t size = 0);

        void *realloc(void *old_addr, size_t new_size);

        [[nodiscard]] uint32_t err_code() const;

        [[nodiscard]] std::string err_string() const;

        [[nodiscard]] std::wstring err_wstring() const;
    };
} // namespace YanLib::mem

#endif // ALLOCATE_H
