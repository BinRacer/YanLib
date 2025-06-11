/* clang-format off */
/*
 * @file timer.cpp
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
#include "timer.h"
#include "helper/convert.h"

namespace YanLib::sync {
    timer::timer() : timer_handle(nullptr), error_code(0) {
    }

    timer::~timer() {
        if (timer_handle) {
            CloseHandle(timer_handle);
            timer_handle = nullptr;
        }
    }

    bool timer::create(SECURITY_ATTRIBUTES *sa,
                       const bool is_manual_reset,
                       const wchar_t *timer_name) {
        timer_handle = CreateWaitableTimerW(sa, is_manual_reset ? TRUE : FALSE,
                                            timer_name);
        error_code = GetLastError();
        return timer_handle != nullptr;
    }

    bool timer::open(const wchar_t *timer_name,
                     TimerAccess access,
                     const bool is_inherit) {
        timer_handle =
                OpenWaitableTimerW(static_cast<uint32_t>(access),
                                   is_inherit ? TRUE : FALSE, timer_name);
        error_code = GetLastError();
        return timer_handle != nullptr;
    }

    bool timer::set_timer(const LARGE_INTEGER *due_time,
                          const int32_t period,
                          PTIMERAPCROUTINE completion_routine,
                          void *param,
                          const bool is_resume) {
        // SYSTEMTIME st = {0};
        // FILETIME ftLocal, ftUTC;
        // LARGE_INTEGER li;
        // st.wYear = 2025;
        // st.wMonth = 1;
        // st.wDay = 1;
        // st.wHour = 23;
        // st.wMinute = 59;
        // st.wSecond = 59;
        // st.wMilliseconds = 0;
        // SystemTimeToFileTime(&st, &ftLocal);
        // LocalFileTimeToFileTime(&ftLocal, &ftUTC);
        // li.LowPart = ftUTC.dwLowDateTime;
        // li.HighPart = ftUTC.dwHighDateTime;
        // SetWaitableTimer(timer_handle,
        //                  &li,
        //                  1000, /* 1s */
        //                  nullptr,
        //                  nullptr,
        //                  FALSE);

        if (timer_handle &&
            SetWaitableTimer(timer_handle, due_time, period, completion_routine,
                             param, is_resume ? TRUE : FALSE)) {
            return true;
        }
        error_code = GetLastError();
        return false;
    }

    bool timer::cancel_timer() {
        if (timer_handle && CancelWaitableTimer(timer_handle)) {
            return true;
        }
        error_code = GetLastError();
        return false;
    }

    bool timer::wait(const uint32_t milli_seconds) {
        if (timer_handle) {
            if (const uint32_t ret =
                        WaitForSingleObject(timer_handle, milli_seconds);
                ret == WAIT_FAILED) {
                error_code = GetLastError();
            } else {
                error_code = ret;
            }
        }
        return error_code == WAIT_OBJECT_0;
    }

    uint32_t timer::err_code() const {
        return error_code;
    }

    std::string timer::err_string() const {
        std::string result = helper::convert::err_string(error_code);
        return result;
    }

    std::wstring timer::err_wstring() const {
        std::wstring result = helper::convert::err_wstring(error_code);
        return result;
    }
} // namespace YanLib::sync
