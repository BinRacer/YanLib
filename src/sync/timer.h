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

        bool create(LPSECURITY_ATTRIBUTES lpTimerAttributes = nullptr,
                    BOOL bManualReset = FALSE,
                    const wchar_t *lpTimerName = nullptr);

        bool open(const wchar_t *lpTimerName,
                  DWORD dwDesiredAccess = TIMER_ALL_ACCESS,
                  BOOL bInheritHandle = FALSE);

        bool set_timer(const LARGE_INTEGER *lpDueTime,
                       LONG lPeriod = 1000, /* 1s */
                       PTIMERAPCROUTINE pfnCompletionRoutine = nullptr,
                       LPVOID lpArgToCompletionRoutine = nullptr,
                       BOOL fResume = FALSE);

        bool cancel_timer();

        bool wait(DWORD dwMilliseconds = INFINITE);

        DWORD err_code() const;

        std::string err_string() const;

        std::wstring err_wstring() const;
    };
}
#endif //TIMER_H
