//
// Created by forkernel on 2025/4/2.
//

#ifndef FENCE_H
#define FENCE_H
#include <Windows.h>

namespace YanLib {
    namespace sync {
        class fence {
        private:
            CRITICAL_SECTION critical_section{};

        public:
            fence(const fence &other) = delete;

            fence(fence &&other) = delete;

            fence &operator=(const fence &other) = delete;

            fence &operator=(fence &&other) = delete;

            fence() = delete;

            ~fence();

            void init();

            void init_with_spin(DWORD dwSpinCount = 4000);

            DWORD set_spin_count(DWORD dwSpinCount);

            void lock();

            BOOL try_lock();

            void unlock();
        };
    }
}
#endif //FENCE_H
