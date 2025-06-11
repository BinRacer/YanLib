/* clang-format off */
/*
 * @file processor.cpp
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
#include "processor.h"
#include "helper/convert.h"

namespace YanLib::sys {
    uint32_t processor::active_count(const uint16_t group_number) {
        const uint32_t count = GetActiveProcessorCount(group_number);
        if (!count) {
            error_code = GetLastError();
            return 0;
        }
        return count;
    }

    uint16_t processor::active_group_count() {
        return GetActiveProcessorGroupCount();
    }

    uint32_t processor::number() {
        return GetCurrentProcessorNumber();
    }

    void processor::number(PROCESSOR_NUMBER *processor_number) {
        GetCurrentProcessorNumberEx(processor_number);
    }

    bool processor::logic_info(SYSTEM_LOGICAL_PROCESSOR_INFORMATION *buffer,
                               uint32_t *real_size) {
        if (!real_size) {
            error_code = STATUS_ACCESS_VIOLATION;
            return false;
        }
        unsigned long temp = *real_size;
        if (!GetLogicalProcessorInformation(buffer, &temp)) {
            error_code = GetLastError();
            *real_size = temp;
            return false;
        }
        *real_size = temp;
        return true;
    }

    bool processor::logic_info(LOGICAL_PROCESSOR_RELATIONSHIP relationship_type,
                               SYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX *buffer,
                               uint32_t *real_size) {
        if (!real_size) {
            error_code = STATUS_ACCESS_VIOLATION;
            return false;
        }
        unsigned long temp = *real_size;
        if (!GetLogicalProcessorInformationEx(relationship_type, buffer,
                                              &temp)) {
            error_code = GetLastError();
            *real_size = temp;
            return false;
        }
        *real_size = temp;
        return true;
    }

    uint32_t processor::max_count(const uint16_t GroupNumber) {
        const uint32_t count = GetMaximumProcessorCount(GroupNumber);
        if (!count) {
            error_code = GetLastError();
            return 0;
        }
        return count;
    }

    uint16_t processor::max_group_count() {
        return GetMaximumProcessorGroupCount();
    }

    bool processor::idle_cycle_time(uint32_t *buffer_length,
                                    uint64_t *processor_idle_cycle_time) {
        if (!buffer_length) {
            error_code = STATUS_ACCESS_VIOLATION;
            return false;
        }
        unsigned long temp = *buffer_length;
        if (!QueryIdleProcessorCycleTime(&temp, processor_idle_cycle_time)) {
            error_code = GetLastError();
            *buffer_length = temp;
            return false;
        }
        *buffer_length = temp;
        return true;
    }

    bool processor::idle_cycle_time(uint16_t group,
                                    uint32_t *buffer_length,
                                    uint64_t *processor_idle_cycle_time) {
        if (!buffer_length) {
            error_code = STATUS_ACCESS_VIOLATION;
            return false;
        }
        unsigned long temp = *buffer_length;
        if (!QueryIdleProcessorCycleTimeEx(group, &temp,
                                           processor_idle_cycle_time)) {
            error_code = GetLastError();
            *buffer_length = temp;
            return false;
        }
        *buffer_length = temp;
        return true;
    }

    uint32_t processor::err_code() const {
        return error_code;
    }

    std::string processor::err_string() const {
        std::string result = helper::convert::err_string(error_code);
        return result;
    }

    std::wstring processor::err_wstring() const {
        std::wstring result = helper::convert::err_wstring(error_code);
        return result;
    }
} // namespace YanLib::sys
