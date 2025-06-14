/* clang-format off */
/*
 * @file semaphore.cpp
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
#include "semaphore.h"
#include "helper/convert.h"

namespace YanLib::sync {
    semaphore::semaphore() : semaphore_handle(nullptr), error_code(0) {
    }

    semaphore::~semaphore() {
        if (semaphore_handle) {
            CloseHandle(semaphore_handle);
            semaphore_handle = nullptr;
        }
    }

    bool semaphore::create(SECURITY_ATTRIBUTES *sa,
                           const int32_t initial_count,
                           const int32_t maximum_count,
                           const wchar_t *name) {
        semaphore_handle =
                CreateSemaphoreW(sa, initial_count, maximum_count, name);
        error_code = GetLastError();
        return semaphore_handle != nullptr;
    }

    bool semaphore::open(const wchar_t *name,
                         SemaphoreAccess access,
                         const bool inherit_handle) {
        semaphore_handle = OpenSemaphoreW(static_cast<uint32_t>(access),
                                          inherit_handle ? TRUE : FALSE, name);
        error_code = GetLastError();
        return semaphore_handle != nullptr;
    }

    bool semaphore::wait(const uint32_t milli_seconds) {
        if (semaphore_handle) {
            if (const uint32_t ret =
                        WaitForSingleObject(semaphore_handle, milli_seconds);
                ret == WAIT_FAILED) {
                error_code = GetLastError();
            } else {
                error_code = ret;
            }
        }
        return error_code == WAIT_OBJECT_0;
    }

    bool semaphore::signal(const int32_t release_count,
                           int32_t *previous_count) {
        long prev = 0;
        if (semaphore_handle &&
            ReleaseSemaphore(semaphore_handle, release_count, &prev)) {
            *previous_count = prev;
            return true;
        }
        error_code = GetLastError();
        *previous_count = prev;
        return false;
    }

    uint32_t semaphore::err_code() const {
        return error_code;
    }

    std::string semaphore::err_string() const {
        std::string result = helper::convert::err_string(error_code);
        return result;
    }

    std::wstring semaphore::err_wstring() const {
        std::wstring result = helper::convert::err_wstring(error_code);
        return result;
    }
} // namespace YanLib::sync
