//
// Created by forkernel on 2025/4/2.
//

#ifndef BARRIER_H
#define BARRIER_H
#include <Windows.h>
#include <string>

namespace YanLib::sync {
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

        explicit barrier(LONG total_threads, LONG spin_count = -1);

        ~barrier();

        bool enter(DWORD flag = SYNCHRONIZATION_BARRIER_FLAGS_BLOCK_ONLY);

        bool wait(DWORD count,
                  const HANDLE *handles,
                  BOOL wait_all = TRUE,
                  DWORD milli_seconds = INFINITE);

        DWORD err_code() const;

        std::string err_string() const;

        std::wstring err_wstring() const;
    };
}
#endif //BARRIER_H
