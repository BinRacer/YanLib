//
// Created by forkernel on 2025/4/2.
//

#include "barrier.h"
#include "helper/convert.h"

namespace YanLib::sync {
    barrier::barrier(long total_threads, long spin_count) {
        if (InitializeSynchronizationBarrier(&synchronization_barrier,
                                             total_threads,
                                             spin_count)) {
            error_code = 0;
        }
        error_code = GetLastError();
    }

    barrier::~barrier() {
        DeleteSynchronizationBarrier(&synchronization_barrier);
    }

    bool barrier::enter(unsigned long flag) {
        return EnterSynchronizationBarrier(&synchronization_barrier, flag);
    }

    bool barrier::wait(unsigned long count,
                       const HANDLE *handles,
                       bool wait_all,
                       unsigned long milli_seconds) {
        unsigned long ret = WaitForMultipleObjects(count,
                                           handles,
                                           wait_all ? TRUE : FALSE,
                                           milli_seconds);
        if (ret == WAIT_FAILED) {
            error_code = GetLastError();
        } else {
            error_code = ret;
        }

        return error_code != WAIT_FAILED && error_code != WAIT_TIMEOUT;
    }

    unsigned long barrier::err_code() const {
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
