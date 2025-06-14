/* clang-format off */
/*
 * @file timer.h
 * @date 2025-04-02
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
