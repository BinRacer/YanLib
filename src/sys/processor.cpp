//
// Created by forkernel on 2025/4/22.
//

#include "processor.h"
#include "helper/convert.h"

namespace YanLib::sys {
uint32_t processor::active_count(uint16_t group_number) {
    uint32_t count = GetActiveProcessorCount(group_number);
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
    uint32_t                                                    *real_size) {
    if (!GetLogicalProcessorInformation(
            buffer, reinterpret_cast<unsigned long *>(real_size))) {
        error_code = GetLastError();
        return false;
    }
    return true;
}

bool processor::logic_info(LOGICAL_PROCESSOR_RELATIONSHIP relationship_type,
    SYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX              *buffer,
    uint32_t                                             *real_size) {
    if (!GetLogicalProcessorInformationEx(relationship_type, buffer,
            reinterpret_cast<unsigned long *>(real_size))) {
        error_code = GetLastError();
        return false;
    }
    return true;
}

uint32_t processor::max_count(uint16_t GroupNumber) {
    uint32_t count = GetMaximumProcessorCount(GroupNumber);
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
    uint64_t                             *processor_idle_cycle_time) {
    if (!QueryIdleProcessorCycleTime(
            reinterpret_cast<unsigned long *>(buffer_length),
            processor_idle_cycle_time)) {
        error_code = GetLastError();
        return false;
    }
    return true;
}

bool processor::idle_cycle_time(uint16_t group,
    uint32_t                            *buffer_length,
    uint64_t                            *processor_idle_cycle_time) {
    if (!QueryIdleProcessorCycleTimeEx(group,
            reinterpret_cast<unsigned long *>(buffer_length),
            processor_idle_cycle_time)) {
        error_code = GetLastError();
        return false;
    }
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
