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

    bool event::create(SECURITY_ATTRIBUTES* event_attrs,
                       bool is_manual_reset,
                       bool is_initial_state,
                       const wchar_t *name) {
        event_handle = CreateEventW(event_attrs,
                                    is_manual_reset ? TRUE : FALSE,
                                    is_initial_state ? TRUE : FALSE,
                                    name);
        error_code = GetLastError();
        return event_handle != nullptr;
    }

    bool event::open(const wchar_t *name,
                     unsigned long desired_access,
                     bool is_inherit_handle) {
        event_handle = OpenEventW(desired_access,
                                  is_inherit_handle ? TRUE : FALSE,
                                  name);
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

    bool event::wait(unsigned long milli_seconds) {
        if (event_handle) {
            unsigned long ret = WaitForSingleObject(event_handle, milli_seconds);
            if (ret == WAIT_FAILED) {
                error_code = GetLastError();
            } else {
                error_code = ret;
            }
        }
        return error_code == WAIT_OBJECT_0;
    }

    unsigned long event::err_code() const {
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
