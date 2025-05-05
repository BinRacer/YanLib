//
// Created by forkernel on 2025/4/22.
//

#include "processor.h"
#include "helper/convert.h"

namespace YanLib::sys {
    unsigned long processor::active_count(unsigned short group_number) {
        unsigned long count = GetActiveProcessorCount(group_number);
        if (!count) {
            error_code = GetLastError();
            return 0;
        }
        return count;
    }

    unsigned short processor::active_group_count() {
        return GetActiveProcessorGroupCount();
    }

    unsigned long processor::number() {
        return GetCurrentProcessorNumber();
    }

    void processor::number(PROCESSOR_NUMBER *processor_number) {
        GetCurrentProcessorNumberEx(processor_number);
    }

    bool processor::logic_info(SYSTEM_LOGICAL_PROCESSOR_INFORMATION *buffer,
                               unsigned long *ret_len) {
        if (!GetLogicalProcessorInformation(buffer, ret_len)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool processor::logic_info(LOGICAL_PROCESSOR_RELATIONSHIP relationship_type,
                               SYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX *buffer,
                               unsigned long *ret_len) {
        if (!GetLogicalProcessorInformationEx(relationship_type, buffer, ret_len)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    unsigned long processor::max_count(unsigned short GroupNumber) {
        unsigned long count = GetMaximumProcessorCount(GroupNumber);
        if (!count) {
            error_code = GetLastError();
            return 0;
        }
        return count;
    }

    unsigned short processor::max_group_count() {
        return GetMaximumProcessorGroupCount();
    }

    bool processor::idle_cycle_time(unsigned long *buffer_length,
                                    unsigned long long *processor_idle_cycle_time) {
        if (!QueryIdleProcessorCycleTime(buffer_length,
                                         processor_idle_cycle_time)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool processor::idle_cycle_time(unsigned short group,
                                    unsigned long *buffer_length,
                                    unsigned long long *processor_idle_cycle_time) {
        if (!QueryIdleProcessorCycleTimeEx(group,
                                           buffer_length,
                                           processor_idle_cycle_time)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    unsigned long processor::err_code() const {
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
}
