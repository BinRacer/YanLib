/* clang-format off */
/*
 * @file barrier.h
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
#ifndef BARRIER_H
#define BARRIER_H
#include <Windows.h>
#include <string>

namespace YanLib::sync {
#ifndef BARRIERFLAG
#define BARRIERFLAG

    enum class BarrierFlag : uint32_t {
        SpinOnly = SYNCHRONIZATION_BARRIER_FLAGS_SPIN_ONLY,
        BlockOnly = SYNCHRONIZATION_BARRIER_FLAGS_BLOCK_ONLY,
        NoDelete = SYNCHRONIZATION_BARRIER_FLAGS_NO_DELETE,
    };

    inline BarrierFlag operator|(BarrierFlag a, BarrierFlag b) {
        return static_cast<BarrierFlag>(static_cast<uint32_t>(a) |
                                        static_cast<uint32_t>(b));
    }
#endif
    class barrier {
    private:
        SYNCHRONIZATION_BARRIER synchronization_barrier{};
        uint32_t error_code;

    public:
        barrier(const barrier &other) = delete;

        barrier(barrier &&other) = delete;

        barrier &operator=(const barrier &other) = delete;

        barrier &operator=(barrier &&other) = delete;

        barrier() = delete;

        explicit barrier(int32_t total_threads, int32_t spin_count = -1);

        ~barrier();

        bool enter(BarrierFlag flag = BarrierFlag::BlockOnly);

        bool wait(uint32_t count,
                  HANDLE handles[],
                  bool wait_all = false,
                  uint32_t milli_seconds = INFINITE);

        [[nodiscard]] uint32_t err_code() const;

        [[nodiscard]] std::string err_string() const;

        [[nodiscard]] std::wstring err_wstring() const;
    };
} // namespace YanLib::sync
#endif // BARRIER_H
