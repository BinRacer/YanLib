//
// Created by forkernel on 2025/4/2.
//

#include "mutex.h"
#include "../helper/convert.h"

namespace YanLib {
    namespace sync {
        mutex::mutex(): mutex_handle(nullptr), error_code(0) {
        }

        mutex::~mutex() {
            if (mutex_handle) {
                CloseHandle(mutex_handle);
            }
        }

        bool mutex::create(LPSECURITY_ATTRIBUTES lpMutexAttributes,
                           BOOL bInitialOwner,
                           const wchar_t *lpName) {
            mutex_handle = CreateMutexW(lpMutexAttributes, bInitialOwner, lpName);
            error_code = GetLastError();
            return mutex_handle != nullptr;
        }

        bool mutex::open(const wchar_t *lpName,
                         DWORD dwDesiredAccess,
                         BOOL bInheritHandle) {
            mutex_handle = OpenMutexW(dwDesiredAccess, bInheritHandle, lpName);
            error_code = GetLastError();
            return mutex_handle != nullptr;
        }

        bool mutex::lock(DWORD dwMilliseconds) {
            if (mutex_handle) {
                DWORD ret = WaitForSingleObject(mutex_handle, dwMilliseconds);
                if (ret == WAIT_FAILED) {
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

        DWORD mutex::err_code() const {
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
    }
}
