/* clang-format off */
/*
 * @file processor.h
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
#ifndef PROCESSOR_H
#define PROCESSOR_H
#include <Windows.h>
#include <string>

namespace YanLib::sys {
    class processor {
    private:
        uint32_t error_code = 0;

    public:
        processor(const processor &other) = delete;

        processor(processor &&other) = delete;

        processor &operator=(const processor &other) = delete;

        processor &operator=(processor &&other) = delete;

        processor() = default;

        ~processor() = default;

        uint32_t active_count(uint16_t group_number = ALL_PROCESSOR_GROUPS);

        uint16_t active_group_count();

        uint32_t number();

        void number(PROCESSOR_NUMBER *processor_number);

        bool logic_info(SYSTEM_LOGICAL_PROCESSOR_INFORMATION *buffer,
                        uint32_t *real_size);

        bool logic_info(LOGICAL_PROCESSOR_RELATIONSHIP relationship_type,
                        SYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX *buffer,
                        uint32_t *real_size);

        uint32_t max_count(uint16_t GroupNumber);

        uint16_t max_group_count();

        bool idle_cycle_time(uint32_t *buffer_length,
                             uint64_t *processor_idle_cycle_time);

        bool idle_cycle_time(uint16_t group,
                             uint32_t *buffer_length,
                             uint64_t *processor_idle_cycle_time);

        [[nodiscard]] uint32_t err_code() const;

        [[nodiscard]] std::string err_string() const;

        [[nodiscard]] std::wstring err_wstring() const;
    };
} // namespace YanLib::sys
#endif // PROCESSOR_H
