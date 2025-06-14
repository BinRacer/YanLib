/* clang-format off */
/*
 * @file condvar.h
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
#ifndef CONDVAR_H
#define CONDVAR_H
#include <Windows.h>
#include <cstdint>

namespace YanLib::sync {
    class condVarCS {
    private:
        CONDITION_VARIABLE condition_variable{};
        CRITICAL_SECTION critical_section{};

    public:
        condVarCS(const condVarCS &other) = delete;

        condVarCS(condVarCS &&other) = delete;

        condVarCS &operator=(const condVarCS &other) = delete;

        condVarCS &operator=(condVarCS &&other) = delete;

        condVarCS();

        ~condVarCS();

        void lock();

        bool try_lock();

        void unlock();

        bool sleep(uint32_t milli_seconds = INFINITE);

        void wake();

        void wake_all();
    };
} // namespace YanLib::sync

namespace sync {
#ifndef CONDVARLOCKMODE
#define CONDVARLOCKMODE

    enum class CondVarLockMode : uint32_t {
        Exclusive = 0,
        Shared = CONDITION_VARIABLE_LOCKMODE_SHARED,
    };
#endif

    class condVarSRW {
    private:
        CONDITION_VARIABLE condition_variable{};
        SRWLOCK rw_lock{};

    public:
        condVarSRW(const condVarSRW &other) = delete;

        condVarSRW(condVarSRW &&other) noexcept = delete;

        condVarSRW &operator=(const condVarSRW &other) = delete;

        condVarSRW &operator=(condVarSRW &&other) noexcept = delete;

        condVarSRW();

        ~condVarSRW() = default;

        void read_lock();

        bool try_read_lock();

        void read_unlock();

        void write_lock();

        bool try_write_lock();

        void write_unlock();

        bool sleep(uint32_t milli_seconds = INFINITE,
                   CondVarLockMode lock_mode = CondVarLockMode::Shared);

        void wake();

        void wake_all();
    };
} // namespace sync
#endif // CONDVAR_H
