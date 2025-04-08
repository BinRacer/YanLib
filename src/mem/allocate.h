//
// Created by forkernel on 2025/4/4.
//

#ifndef ALLOCATE_H
#define ALLOCATE_H
#include <Windows.h>
#include <string>
#include <list>
#include "../sync/rwlock.h"

namespace YanLib {
    namespace mem {
        class allocate {
        private:
            std::list<void *> lpMemory;
            DWORD error_code;
            sync::rwlock rwlock;

        public:
            allocate(const allocate &other) = delete;

            allocate(allocate &&other) = delete;

            allocate &operator=(const allocate &other) = delete;

            allocate &operator=(allocate &&other) = delete;

            allocate();

            ~allocate();

            void *malloc(size_t dwSize);

            bool free(void *lpAddr);

            void *malloc_reserve(size_t dwSize);

            bool free_reserve(void *lpAddr, size_t dwSize = 0);

            void *realloc(void *lpOldAddr, size_t dwNewSize);

            DWORD err_code() const;

            std::string err_string() const;

            std::wstring err_wstring() const;
        };
    }
}

#endif //ALLOCATE_H
