//
// Created by forkernel on 2025/4/22.
//

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
