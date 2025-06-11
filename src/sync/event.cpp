/* clang-format off */
/*
 * @file event.cpp
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
