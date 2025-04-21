//
// Created by forkernel on 2025/4/2.
//

#include "mutex.h"
#include "helper/convert.h"

namespace YanLib::sync {
    mutex::mutex(): mutex_handle(nullptr), error_code(0) {
    }

    mutex::~mutex() {
        if (mutex_handle) {
            CloseHandle(mutex_handle);
            mutex_handle = nullptr;
        }
    }

    bool mutex::create(LPSECURITY_ATTRIBUTES mutex_attrs,
                       bool is_initial_owner,
                       const wchar_t *name) {
        mutex_handle = CreateMutexW(mutex_attrs,
                                    is_initial_owner ? TRUE : FALSE,
                                    name);
        error_code = GetLastError();
        return mutex_handle != nullptr;
    }

    bool mutex::open(const wchar_t *name,
                     DWORD desired_access,
                     bool is_inherit_handle) {
        mutex_handle = OpenMutexW(desired_access,
                                  is_inherit_handle ? TRUE : FALSE,
                                  name);
        error_code = GetLastError();
        return mutex_handle != nullptr;
    }

    bool mutex::lock(DWORD milli_seconds) {
        if (mutex_handle) {
            DWORD ret = WaitForSingleObject(mutex_handle, milli_seconds);
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
