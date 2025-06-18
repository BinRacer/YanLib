/* clang-format off */
/*
 * @file fence.h
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
#ifndef FENCE_H
#define FENCE_H
#include <Windows.h>
#include <minwinbase.h>
#include <cstdint>

namespace YanLib::sync {
    class fence {
    private:
        CRITICAL_SECTION critical_section{};

    public:
        fence(const fence &other) = delete;

        fence(fence &&other) = delete;

        fence &operator=(const fence &other) = delete;

        fence &operator=(fence &&other) = delete;

        fence() = delete;

        ~fence();

        void init();

        void init_with_spin(uint32_t spin_count = 4000);

        uint32_t set_spin_count(uint32_t spin_count);

        void lock();

        bool try_lock();

        void unlock();
    };
} // namespace YanLib::sync
#endif // FENCE_H
