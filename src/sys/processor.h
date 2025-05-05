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
        unsigned long error_code = 0;

    public:
        processor(const processor &other) = delete;

        processor(processor &&other) = delete;

        processor &operator=(const processor &other) = delete;

        processor &operator=(processor &&other) = delete;

        processor() = default;

        ~processor() = default;

        unsigned long active_count(unsigned short group_number = ALL_PROCESSOR_GROUPS);

        unsigned short active_group_count();

        unsigned long number();

        void number(PROCESSOR_NUMBER* processor_number);

        bool logic_info(SYSTEM_LOGICAL_PROCESSOR_INFORMATION* buffer,
                        unsigned long* ret_len);

        bool logic_info(LOGICAL_PROCESSOR_RELATIONSHIP relationship_type,
                        SYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX* buffer,
                        unsigned long* ret_len);

        unsigned long max_count(unsigned short GroupNumber);

        unsigned short max_group_count();

        bool idle_cycle_time(unsigned long* buffer_length,
                             unsigned long long* processor_idle_cycle_time);

        bool idle_cycle_time(unsigned short group,
                             unsigned long* buffer_length,
                             unsigned long long* processor_idle_cycle_time);

        [[nodiscard]] unsigned long err_code() const;

        [[nodiscard]] std::string err_string() const;

        [[nodiscard]] std::wstring err_wstring() const;
    };
}
#endif //PROCESSOR_H
