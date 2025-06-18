/* clang-format off */
/*
 * @file rwlock.h
 * @date 2025-04-02
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
#ifndef RWLOCK_H
#define RWLOCK_H
#include <Windows.h>
#include <synchapi.h>
namespace YanLib::sync {
    class rwlock {
    private:
        SRWLOCK rw_lock{};

    public:
        rwlock(const rwlock &other) = delete;

        rwlock(rwlock &&other) = delete;

        rwlock &operator=(const rwlock &other) = delete;

        rwlock &operator=(rwlock &&other) = delete;

        rwlock();

        ~rwlock() = default;

        void read_lock();

        bool try_read_lock();

        void read_unlock();

        void write_lock();

        bool try_write_lock();

        void write_unlock();
    };
} // namespace YanLib::sync
#endif // RWLOCK_H
