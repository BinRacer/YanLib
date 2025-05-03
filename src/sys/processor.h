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
        DWORD error_code = 0;

    public:
        processor(const processor &other) = delete;

        processor(processor &&other) = delete;

        processor &operator=(const processor &other) = delete;

        processor &operator=(processor &&other) = delete;

        processor() = default;

        ~processor() = default;

        DWORD active_count(WORD group_number = ALL_PROCESSOR_GROUPS);

        WORD active_group_count();

        DWORD number();

        void number(PPROCESSOR_NUMBER processor_number);

        bool logic_info(PSYSTEM_LOGICAL_PROCESSOR_INFORMATION buffer,
                        DWORD* ret_len);

        bool logic_info(LOGICAL_PROCESSOR_RELATIONSHIP relationship_type,
                        PSYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX buffer,
                        DWORD* ret_len);

        DWORD max_count(WORD GroupNumber);

        WORD max_group_count();

        bool idle_cycle_time(ULONG* buffer_length,
                             ULONG64* processor_idle_cycle_time);

        bool idle_cycle_time(USHORT group,
                             ULONG* buffer_length,
                             ULONG64* processor_idle_cycle_time);

        [[nodiscard]] DWORD err_code() const;

        [[nodiscard]] std::string err_string() const;

        [[nodiscard]] std::wstring err_wstring() const;
    };
}
#endif //PROCESSOR_H
