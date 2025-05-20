//
// Created by forkernel on 2025/4/2.
//

#ifndef BARRIER_H
#define BARRIER_H
#include <Windows.h>
#include <string>

namespace YanLib::sync {
#ifndef BARRIERFLAG
#define BARRIERFLAG

    enum class BarrierFlag : uint32_t {
        SpinOnly = SYNCHRONIZATION_BARRIER_FLAGS_SPIN_ONLY,
        BlockOnly = SYNCHRONIZATION_BARRIER_FLAGS_BLOCK_ONLY,
        NoDelete = SYNCHRONIZATION_BARRIER_FLAGS_NO_DELETE,
    };

    inline BarrierFlag operator|(BarrierFlag a, BarrierFlag b) {
        return static_cast<BarrierFlag>(static_cast<uint32_t>(a) |
                                        static_cast<uint32_t>(b));
    }
#endif
    class barrier {
    private:
        SYNCHRONIZATION_BARRIER synchronization_barrier{};
        uint32_t error_code;

    public:
        barrier(const barrier &other) = delete;

        barrier(barrier &&other) = delete;

        barrier &operator=(const barrier &other) = delete;

        barrier &operator=(barrier &&other) = delete;

        barrier() = delete;

        explicit barrier(int32_t total_threads, int32_t spin_count = -1);

        ~barrier();

        bool enter(BarrierFlag flag = BarrierFlag::BlockOnly);

        bool wait(uint32_t count,
                  const HANDLE *handles,
                  bool wait_all = false,
                  uint32_t milli_seconds = INFINITE);

        [[nodiscard]] uint32_t err_code() const;

        [[nodiscard]] std::string err_string() const;

        [[nodiscard]] std::wstring err_wstring() const;
    };
} // namespace YanLib::sync
#endif // BARRIER_H
