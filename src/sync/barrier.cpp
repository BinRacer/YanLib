/* clang-format off */
/*
 * @file barrier.cpp
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
#include "barrier.h"
#include "helper/convert.h"

namespace YanLib::sync {
    barrier::barrier(int32_t total_threads, const int32_t spin_count) {
        if (InitializeSynchronizationBarrier(&synchronization_barrier,
                                             total_threads, spin_count)) {
            error_code = 0;
        }
        error_code = GetLastError();
    }

    barrier::~barrier() {
        DeleteSynchronizationBarrier(&synchronization_barrier);
    }

    bool barrier::enter(BarrierFlag flag) {
        return EnterSynchronizationBarrier(&synchronization_barrier,
                                           static_cast<uint32_t>(flag));
    }

    bool barrier::wait(uint32_t count,
                       HANDLE handles[],
                       const bool wait_all,
                       const uint32_t milli_seconds) {
        const uint32_t ret =
                WaitForMultipleObjects(count, handles, wait_all ? TRUE : FALSE,
                                       milli_seconds);
        if (ret == WAIT_FAILED) {
            error_code = GetLastError();
        } else {
            error_code = ret;
        }

        return error_code != WAIT_FAILED && error_code != WAIT_TIMEOUT;
    }

    uint32_t barrier::err_code() const {
        return error_code;
    }

    std::string barrier::err_string() const {
        std::string result = helper::convert::err_string(error_code);
        return result;
    }

    std::wstring barrier::err_wstring() const {
        std::wstring result = helper::convert::err_wstring(error_code);
        return result;
    }
} // namespace YanLib::sync
