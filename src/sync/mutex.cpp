/* clang-format off */
/*
 * @file mutex.cpp
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
#include "mutex.h"
#include "helper/convert.h"

namespace YanLib::sync {
    mutex::mutex() : mutex_handle(nullptr), error_code(0) {
    }

    mutex::~mutex() {
        if (mutex_handle) {
            CloseHandle(mutex_handle);
            mutex_handle = nullptr;
        }
    }

    bool mutex::create(SECURITY_ATTRIBUTES *sa,
                       const bool is_initial_owner,
                       const wchar_t *name) {
        mutex_handle = CreateMutexW(sa, is_initial_owner ? TRUE : FALSE, name);
        error_code = GetLastError();
        return mutex_handle != nullptr;
    }

    bool mutex::open(const wchar_t *name,
                     MutexAccess access,
                     const bool is_inherit) {
        mutex_handle = OpenMutexW(static_cast<uint32_t>(access),
                                  is_inherit ? TRUE : FALSE, name);
        error_code = GetLastError();
        return mutex_handle != nullptr;
    }

    bool mutex::lock(const uint32_t milli_seconds) {
        if (mutex_handle) {
            if (const uint32_t ret =
                        WaitForSingleObject(mutex_handle, milli_seconds);
                ret == WAIT_FAILED) {
                error_code = GetLastError();
            } else {
                error_code = ret;
            }
        }
        return error_code == WAIT_OBJECT_0;
    }

    bool mutex::unlock() {
        if (mutex_handle && ReleaseMutex(mutex_handle)) {
            return true;
        }
        error_code = GetLastError();
        return false;
    }

    uint32_t mutex::err_code() const {
        return error_code;
    }

    std::string mutex::err_string() const {
        std::string result = helper::convert::err_string(error_code);
        return result;
    }

    std::wstring mutex::err_wstring() const {
        std::wstring result = helper::convert::err_wstring(error_code);
        return result;
    }
} // namespace YanLib::sync
