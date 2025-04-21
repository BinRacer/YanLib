//
// Created by forkernel on 2025/4/2.
//

#include "semaphore.h"
#include "helper/convert.h"

namespace YanLib::sync {
    semaphore::semaphore(): semaphore_handle(nullptr), error_code(0) {
    }

    semaphore::~semaphore() {
        if (semaphore_handle) {
            CloseHandle(semaphore_handle);
            semaphore_handle = nullptr;
        }
    }

    bool semaphore::create(LPSECURITY_ATTRIBUTES semaphore_attrs,
                           LONG initial_count,
                           LONG maximum_count,
                           const wchar_t *name) {
        semaphore_handle = CreateSemaphoreW(semaphore_attrs,
                                            initial_count,
                                            maximum_count,
                                            name);
        error_code = GetLastError();
        return semaphore_handle != nullptr;
    }

    bool semaphore::open(const wchar_t *name,
                         DWORD desired_access,
                         bool inherit_handle) {
        semaphore_handle = OpenSemaphoreW(desired_access,
                                          inherit_handle ? TRUE : FALSE,
                                          name);
        error_code = GetLastError();
        return semaphore_handle != nullptr;
    }

    bool semaphore::wait(DWORD milli_seconds) {
        if (semaphore_handle) {
            DWORD ret = WaitForSingleObject(semaphore_handle, milli_seconds);
            if (ret == WAIT_FAILED) {
                error_code = GetLastError();
            } else {
                error_code = ret;
            }
        }
        return error_code == WAIT_OBJECT_0;
    }

    bool semaphore::signal(LONG release_count, LPLONG previous_count) {
        if (semaphore_handle &&
            ReleaseSemaphore(semaphore_handle, release_count, previous_count)) {
            return true;
        }
        error_code = GetLastError();
        return false;
    }

    DWORD semaphore::err_code() const {
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
}
