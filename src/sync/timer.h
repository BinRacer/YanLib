//
// Created by forkernel on 2025/4/2.
//

#ifndef TIMER_H
#define TIMER_H
#include <Windows.h>
#include <string>

namespace YanLib::sync {
    class timer {
    private:
        HANDLE timer_handle;
        DWORD error_code;

    public:
        timer(const timer &other) = delete;

        timer(timer &&other) = delete;

        timer &operator=(const timer &other) = delete;

        timer &operator=(timer &&other) = delete;

        timer();

        ~timer();

        bool create(LPSECURITY_ATTRIBUTES timer_attrs = nullptr,
                    bool is_manual_reset = false,
                    const wchar_t *timer_name = nullptr);

        bool open(const wchar_t *timer_name,
                  DWORD desired_access = TIMER_ALL_ACCESS,
                  bool is_inherit_handle = false);

        bool set_timer(const LARGE_INTEGER *due_time,
                       LONG period = 1000, /* 1s */
                       PTIMERAPCROUTINE pfn_completion_routine = nullptr,
                       void *arg_to_completion_routine = nullptr,
                       bool is_resume = false);

        bool cancel_timer();

        bool wait(DWORD milli_seconds = INFINITE);

        [[nodiscard]] DWORD err_code() const;

        [[nodiscard]] std::string err_string() const;

        [[nodiscard]] std::wstring err_wstring() const;
    };
}
#endif //TIMER_H
