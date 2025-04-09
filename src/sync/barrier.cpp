//
// Created by forkernel on 2025/4/2.
//

#include "barrier.h"
#include "../helper/convert.h"

namespace YanLib::sync {
    barrier::barrier(LONG lTotalThreads, LONG lSpinCount) {
        if (InitializeSynchronizationBarrier(&synchronization_barrier,
                                             lTotalThreads,
                                             lSpinCount)) {
            error_code = 0;
        }
        error_code = GetLastError();
    }

    barrier::~barrier() {
        DeleteSynchronizationBarrier(&synchronization_barrier);
    }

    bool barrier::enter(DWORD dwFlags) {
        const BOOL ret = EnterSynchronizationBarrier(&synchronization_barrier, dwFlags);
        return ret == TRUE;
    }

    bool barrier::wait(DWORD nCount,
                       const HANDLE *lpHandles,
                       BOOL bWaitAll,
                       DWORD dwMilliseconds) {
        DWORD ret = WaitForMultipleObjects(nCount,
                                           lpHandles,
                                           bWaitAll,
                                           dwMilliseconds);
        if (ret == WAIT_FAILED) {
            error_code = GetLastError();
        } else {
            error_code = ret;
        }

        return error_code != WAIT_FAILED && error_code != WAIT_TIMEOUT;
    }

    DWORD barrier::err_code() const {
        return error_code;
    }

    std::string barrier::err_string() const {
        std::string result = helper::convert::err_string(error_code);
        return result;
    }

    std::wstring barrier::err_wstring() const {
        std::wstring result = helper::convert::err_wstring(error_code);
        return result;
    }
}
