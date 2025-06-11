/* clang-format off */
/*
 * @file fence.cpp
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
#include "fence.h"

namespace YanLib::sync {
    fence::~fence() {
        DeleteCriticalSection(&critical_section);
    }

    void fence::init() {
        InitializeCriticalSection(&critical_section);
    }

    void fence::init_with_spin(uint32_t spin_count) {
        InitializeCriticalSectionAndSpinCount(&critical_section, spin_count);
    }

    uint32_t fence::set_spin_count(uint32_t spin_count) {
        return SetCriticalSectionSpinCount(&critical_section, spin_count);
    }

    void fence::lock() {
        EnterCriticalSection(&critical_section);
    }

    bool fence::try_lock() {
        return TryEnterCriticalSection(&critical_section);
    }

    void fence::unlock() {
        LeaveCriticalSection(&critical_section);
    }
} // namespace YanLib::sync
