//
// Created by forkernel on 2025/4/2.
//

#ifndef TIMER_H
#define TIMER_H
#include <Windows.h>
#include <string>

namespace YanLib::sync {
#ifndef TIMERACCESS
#define TIMERACCESS

    enum class TimerAccess : uint32_t {
        Delete = DELETE,
        ReadControl = READ_CONTROL,
        WriteDac = WRITE_DAC,
        WriteOwner = WRITE_OWNER,
        Synchronize = SYNCHRONIZE,
        All = TIMER_ALL_ACCESS,
        Modify = TIMER_MODIFY_STATE,
        Query = TIMER_QUERY_STATE,
    };

    inline TimerAccess operator|(TimerAccess a, TimerAccess b) {
        return static_cast<TimerAccess>(static_cast<uint32_t>(a) |
                                        static_cast<uint32_t>(b));
    }
#endif

    class timer {
    private:
        HANDLE timer_handle;
        uint32_t error_code;

    public:
        timer(const timer &other) = delete;

        timer(timer &&other) = delete;

        timer &operator=(const timer &other) = delete;

        timer &operator=(timer &&other) = delete;

        timer();

        ~timer();

        bool create(SECURITY_ATTRIBUTES *sa = nullptr,
                    bool is_manual_reset = false,
                    const wchar_t *timer_name = nullptr);

        bool open(const wchar_t *timer_name,
                  TimerAccess access = TimerAccess::All,
                  bool is_inherit = false);

        bool set_timer(const LARGE_INTEGER *due_time,
                       int32_t period = 1000 /* 1s */,
                       PTIMERAPCROUTINE completion_routine = nullptr,
                       void *param = nullptr,
                       bool is_resume = false);

        bool cancel_timer();

        bool wait(uint32_t milli_seconds = INFINITE);

        [[nodiscard]] uint32_t err_code() const;

        [[nodiscard]] std::string err_string() const;

        [[nodiscard]] std::wstring err_wstring() const;
    };
} // namespace YanLib::sync
#endif // TIMER_H
