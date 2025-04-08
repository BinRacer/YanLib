//
// Created by forkernel on 2025/4/2.
//

#ifndef BARRIER_H
#define BARRIER_H
#include <Windows.h>
#include <string>

namespace YanLib {
    namespace sync {
        class barrier {
        private:
            SYNCHRONIZATION_BARRIER synchronization_barrier{};
            DWORD error_code;

        public:
            barrier(const barrier &other) = delete;

            barrier(barrier &&other) = delete;

            barrier &operator=(const barrier &other) = delete;

            barrier &operator=(barrier &&other) = delete;

            barrier() = delete;

            explicit barrier(LONG lTotalThreads, LONG lSpinCount = -1);

            ~barrier();

            bool enter(DWORD dwFlags = SYNCHRONIZATION_BARRIER_FLAGS_BLOCK_ONLY);

            bool wait(DWORD nCount,
                      const HANDLE *lpHandles,
                      BOOL bWaitAll = TRUE,
                      DWORD dwMilliseconds = INFINITE);

            DWORD err_code() const;

            std::string err_string() const;

            std::wstring err_wstring() const;
        };
    }
}
#endif //BARRIER_H
