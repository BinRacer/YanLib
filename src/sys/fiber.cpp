/* clang-format off */
/*
 * @file fiber.cpp
 * @date 2025-04-22
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
#include "fiber.h"
#include "helper/convert.h"
#include <random>

namespace YanLib::sys {
    fiber::~fiber() {
        for (auto &addr : fiber_addrs) {
            if (addr) {
                DeleteFiber(addr);
                addr = nullptr;
            }
        }
        fiber_addrs.clear();
    }

    void *fiber::create(LPFIBER_START_ROUTINE start_addr,
                        void *params,
                        const size_t commit,
                        const size_t reserve,
                        const bool switch_float) {
        void *addr = CreateFiberEx(commit, reserve,
                                   switch_float ? FIBER_FLAG_FLOAT_SWITCH : 0,
                                   start_addr, params);
        if (!addr) {
            error_code = GetLastError();
            return nullptr;
        }
        fiber_lock.write_lock();
        fiber_addrs.push_back(addr);
        fiber_lock.write_unlock();
        return addr;
    }

    uint32_t fiber::fls_alloc(PFLS_CALLBACK_FUNCTION callback) {
        const uint32_t index = FlsAlloc(callback);
        if (index == FLS_OUT_OF_INDEXES) {
            error_code = GetLastError();
        }
        return index;
    }

    bool fiber::fls_free(uint32_t index) {
        if (!FlsFree(index)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    void *fiber::fls_get_value(uint32_t index) {
        void *value = FlsGetValue(index);
        if (!value) {
            error_code = GetLastError();
        }
        return value;
    }

    bool fiber::fls_set_value(uint32_t index, void *value) {
        if (!FlsSetValue(index, value)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool fiber::is_fiber() {
        return IsThreadAFiber();
    }

    void fiber::switch_to_fiber(void *addr) {
        SwitchToFiber(addr);
    }

    void fiber::yield() {
        std::random_device rd = {};
        fiber_lock.read_lock();
        size_t index = rd() % fiber_addrs.size();
        if (index > fiber_addrs.size()) {
            index = fiber_addrs.size() - 1;
        }
        SwitchToFiber(fiber_addrs[index]);
        fiber_lock.read_lock();
    }

    void *fiber::thread_to_fiber(void *params, const bool switch_float) {
        void *addr =
                ConvertThreadToFiberEx(params,
                                       switch_float ? FIBER_FLAG_FLOAT_SWITCH
                                                    : 0);
        if (!addr) {
            error_code = GetLastError();
            return nullptr;
        }
        fiber_lock.write_lock();
        fiber_addrs.push_back(addr);
        fiber_lock.write_unlock();
        return addr;
    }

    bool fiber::fiber_to_thread() {
        const void *addr = GetCurrentFiber();
        if (!addr) {
            error_code = GetLastError();
            return false;
        }
        fiber_lock.write_lock();
        if (const auto it =
                    std::find(fiber_addrs.begin(), fiber_addrs.end(), addr);
            it != fiber_addrs.end()) {
            *it = nullptr;
        }
        fiber_lock.write_unlock();
        if (!ConvertFiberToThread()) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    uint32_t fiber::err_code() const {
        return error_code;
    }

    std::string fiber::err_string() const {
        std::string result = helper::convert::err_string(error_code);
        return result;
    }

    std::wstring fiber::err_wstring() const {
        std::wstring result = helper::convert::err_wstring(error_code);
        return result;
    }
} // namespace YanLib::sys
