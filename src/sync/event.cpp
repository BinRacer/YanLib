//
// Created by forkernel on 2025/4/2.
//

#include "event.h"
#include "helper/convert.h"

namespace YanLib::sync {
    event::event(): event_handle(nullptr), error_code(0) {
    }

    event::~event() {
        if (event_handle) {
            CloseHandle(event_handle);
            event_handle = nullptr;
        }
    }

    bool event::create(LPSECURITY_ATTRIBUTES lpEventAttributes,
                       BOOL bManualReset,
                       BOOL bInitialState,
                       const wchar_t *lpName) {
        event_handle = CreateEventW(lpEventAttributes,
                                    bManualReset,
                                    bInitialState,
                                    lpName);
        error_code = GetLastError();
        return event_handle != nullptr;
    }

    bool event::open(const wchar_t *lpName,
                     DWORD dwDesiredAccess,
                     BOOL bInheritHandle) {
        event_handle = OpenEventW(dwDesiredAccess,
                                  bInheritHandle,
                                  lpName);
        error_code = GetLastError();
        return event_handle != nullptr;
    }

    bool event::on() {
        if (event_handle && SetEvent(event_handle)) {
            return true;
        }
        error_code = GetLastError();
        return false;
    }

    bool event::off() {
        if (event_handle && ResetEvent(event_handle)) {
            return true;
        }
        error_code = GetLastError();
        return false;
    }

    bool event::wait(DWORD dwMilliseconds) {
        if (event_handle) {
            DWORD ret = WaitForSingleObject(event_handle, dwMilliseconds);
            if (ret == WAIT_FAILED) {
                error_code = GetLastError();
            } else {
                error_code = ret;
            }
        }
        return error_code == WAIT_OBJECT_0;
    }

    DWORD event::err_code() const {
        return error_code;
    }

    std::string event::err_string() const {
        std::string result = helper::convert::err_string(error_code);
        return result;
    }

    std::wstring event::err_wstring() const {
        std::wstring result = helper::convert::err_wstring(error_code);
        return result;
    }
}
