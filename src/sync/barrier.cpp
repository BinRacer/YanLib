//
// Created by BinRacer <native.lab@outlook.com> on 2025/4/2.
//

#include "barrier.h"
#include "helper/convert.h"

namespace YanLib::sync {
    barrier::barrier(int32_t total_threads, const int32_t spin_count) {
        if (InitializeSynchronizationBarrier(&synchronization_barrier,
                                             total_threads, spin_count)) {
            error_code = 0;
        }
        error_code = GetLastError();
    }

    barrier::~barrier() {
        DeleteSynchronizationBarrier(&synchronization_barrier);
    }

    bool barrier::enter(BarrierFlag flag) {
        return EnterSynchronizationBarrier(&synchronization_barrier,
                                           static_cast<uint32_t>(flag));
    }

    bool barrier::wait(uint32_t count,
                       HANDLE handles[],
                       const bool wait_all,
                       const uint32_t milli_seconds) {
        const uint32_t ret =
                WaitForMultipleObjects(count, handles, wait_all ? TRUE : FALSE,
                                       milli_seconds);
        if (ret == WAIT_FAILED) {
            error_code = GetLastError();
        } else {
            error_code = ret;
        }

        return error_code != WAIT_FAILED && error_code != WAIT_TIMEOUT;
    }

    uint32_t barrier::err_code() const {
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
} // namespace YanLib::sync
