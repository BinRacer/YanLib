//
// Created by forkernel on 2025/4/2.
//

#ifndef CONDVAR_H
#define CONDVAR_H
#include <Windows.h>

namespace YanLib {
    namespace sync {
        class condVarCS {
        public:
            condVarCS(const condVarCS &other) = delete;

            condVarCS(condVarCS &&other) = delete;

            condVarCS &operator=(const condVarCS &other) = delete;

            condVarCS &operator=(condVarCS &&other) = delete;

            condVarCS();

            ~condVarCS();

            void lock();

            BOOL try_lock();

            void unlock();

            bool sleep(DWORD dwMilliseconds = INFINITE);

            void wake();

            void wake_all();

            DWORD err_code() const;
        };
    }

    namespace sync {
        class condVarSRW {
        public:
            condVarSRW(const condVarSRW &other) = delete;

            condVarSRW(condVarSRW &&other) noexcept = delete;

            condVarSRW &operator=(const condVarSRW &other) = delete;

            condVarSRW &operator=(condVarSRW &&other) noexcept = delete;

            condVarSRW();

            ~condVarSRW();

            void read_lock();

            BOOLEAN try_read_lock();

            void read_unlock();

            void write_lock();

            BOOLEAN try_write_lock();

            void write_unlock();

            bool sleep(DWORD dwMilliseconds = INFINITE,
                       ULONG Flags = CONDITION_VARIABLE_LOCKMODE_SHARED);

            void wake();

            void wake_all();
        };
    }
}
#endif //CONDVAR_H
