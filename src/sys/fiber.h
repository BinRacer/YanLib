/* clang-format off */
/*
 * @file fiber.h
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
#ifndef FIBER_H
#define FIBER_H
#include <Windows.h>
#include <string>
#include <vector>
#include "sync/rwlock.h"

namespace YanLib::sys {
    class fiber {
    private:
        std::vector<void *> fiber_addrs = {};
        sync::rwlock fiber_lock = {};
        uint32_t error_code = 0;

    public:
        fiber(const fiber &other) = delete;

        fiber(fiber &&other) = delete;

        fiber &operator=(const fiber &other) = delete;

        fiber &operator=(fiber &&other) = delete;

        fiber() = default;

        ~fiber();

        void *create(LPFIBER_START_ROUTINE start_addr,
                     void *params,
                     size_t commit = 0,
                     size_t reserve = 0,
                     bool switch_float = true);

        uint32_t fls_alloc(PFLS_CALLBACK_FUNCTION callback);

        bool fls_free(uint32_t index);

        void *fls_get_value(uint32_t index);

        bool fls_set_value(uint32_t index, void *value);

        bool is_fiber();

        void switch_to_fiber(void *addr);

        void yield();

        void *thread_to_fiber(void *params, bool switch_float = true);

        bool fiber_to_thread();

        [[nodiscard]] uint32_t err_code() const;

        [[nodiscard]] std::string err_string() const;

        [[nodiscard]] std::wstring err_wstring() const;
    };
} // namespace YanLib::sys
#endif // FIBER_H
