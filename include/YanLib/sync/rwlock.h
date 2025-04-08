//
// Created by forkernel on 2025/4/2.
//

#ifndef RWLOCK_H
#define RWLOCK_H
#include <Windows.h>

namespace YanLib {
    namespace sync {
        class rwlock {
        public:
            rwlock(const rwlock &other) = delete;

            rwlock(rwlock &&other) = delete;

            rwlock &operator=(const rwlock &other) = delete;

            rwlock &operator=(rwlock &&other) = delete;

            rwlock();

            ~rwlock();

            void read_lock();

            BOOLEAN try_read_lock();

            void read_unlock();

            void write_lock();

            BOOLEAN try_write_lock();

            void write_unlock();
        };
    }
}
#endif //RWLOCK_H
