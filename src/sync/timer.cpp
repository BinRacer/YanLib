//
// Created by forkernel on 2025/4/2.
//

#include "timer.h"
#include "helper/convert.h"

namespace YanLib::sync {
    timer::timer(): timer_handle(nullptr), error_code(0) {
    }

    timer::~timer() {
        if (timer_handle) {
            CloseHandle(timer_handle);
            timer_handle = nullptr;
        }
    }

    bool timer::create(SECURITY_ATTRIBUTES *timer_attrs,
                       bool is_manual_reset,
                       const wchar_t *timer_name) {
        timer_handle = CreateWaitableTimerW(timer_attrs,
                                            is_manual_reset ? TRUE : FALSE,
                                            timer_name);
        error_code = GetLastError();
        return timer_handle != nullptr;
    }

    bool timer::open(const wchar_t *timer_name,
                     unsigned long desired_access,
                     bool is_inherit_handle) {
        timer_handle = OpenWaitableTimerW(desired_access,
                                          is_inherit_handle ? TRUE : FALSE,
                                          timer_name);
        error_code = GetLastError();
        return timer_handle != nullptr;
    }

    bool timer::set_timer(const LARGE_INTEGER *due_time,
                          long period,
                          PTIMERAPCROUTINE pfn_completion_routine,
                          void *arg_to_completion_routine,
                          bool is_resume) {
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

        if (timer_handle && SetWaitableTimer(timer_handle,
                                             due_time,
                                             period,
                                             pfn_completion_routine,
                                             arg_to_completion_routine,
                                             is_resume ? TRUE : FALSE)) {
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

    bool timer::wait(unsigned long milli_seconds) {
        if (timer_handle) {
            unsigned long ret = WaitForSingleObject(timer_handle, milli_seconds);
            if (ret == WAIT_FAILED) {
                error_code = GetLastError();
            } else {
                error_code = ret;
            }
        }
        return error_code == WAIT_OBJECT_0;
    }

    unsigned long timer::err_code() const {
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
}
