//
// Created by BinRacer <native.lab@outlook.com> on 2025/4/2.
//

#include "event.h"
#include "helper/convert.h"

namespace YanLib::sync {
    event::event() : event_handle(nullptr), error_code(0) {
    }

    event::~event() {
        if (event_handle) {
            CloseHandle(event_handle);
            event_handle = nullptr;
        }
    }

    bool event::create(SECURITY_ATTRIBUTES *sa,
                       const bool is_manual_reset,
                       const bool is_initial_state,
                       const wchar_t *name) {
        event_handle = CreateEventW(sa, is_manual_reset ? TRUE : FALSE,
                                    is_initial_state ? TRUE : FALSE, name);
        error_code = GetLastError();
        return event_handle != nullptr;
    }

    bool event::open(const wchar_t *name,
                     EventAccess access,
                     const bool is_inherit) {
        event_handle = OpenEventW(static_cast<uint32_t>(access),
                                  is_inherit ? TRUE : FALSE, name);
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

    bool event::wait(const uint32_t milli_seconds) {
        if (event_handle) {
            if (const uint32_t ret =
                        WaitForSingleObject(event_handle, milli_seconds);
                ret == WAIT_FAILED) {
                error_code = GetLastError();
            } else {
                error_code = ret;
            }
        }
        return error_code == WAIT_OBJECT_0;
    }

    uint32_t event::err_code() const {
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
} // namespace YanLib::sync
