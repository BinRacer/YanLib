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

    bool semaphore::create(LPSECURITY_ATTRIBUTES lpSemaphoreAttributes,
                           LONG lInitialCount,
                           LONG lMaximumCount,
                           const wchar_t *lpName) {
        semaphore_handle = CreateSemaphoreW(lpSemaphoreAttributes,
                                            lInitialCount,
                                            lMaximumCount,
                                            lpName);
        error_code = GetLastError();
        return semaphore_handle != nullptr;
    }

    bool semaphore::open(const wchar_t *lpName,
                         DWORD dwDesiredAccess,
                         BOOL bInheritHandle) {
        semaphore_handle = OpenSemaphoreW(dwDesiredAccess, bInheritHandle, lpName);
        error_code = GetLastError();
        return semaphore_handle != nullptr;
    }

    bool semaphore::wait(DWORD dwMilliseconds) {
        if (semaphore_handle) {
            DWORD ret = WaitForSingleObject(semaphore_handle, dwMilliseconds);
            if (ret == WAIT_FAILED) {
                error_code = GetLastError();
            } else {
                error_code = ret;
            }
        }
        return error_code == WAIT_OBJECT_0;
    }

    bool semaphore::signal(LONG lReleaseCount, LPLONG lpPreviousCount) {
        if (semaphore_handle &&
            ReleaseSemaphore(semaphore_handle, lReleaseCount, lpPreviousCount)) {
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
