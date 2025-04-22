//
// Created by forkernel on 2025/4/4.
//

#ifndef ALLOCATE_H
#define ALLOCATE_H
#include <Windows.h>
#include <string>
#include <list>
#include "sync/rwlock.h"

namespace YanLib::mem {
    class allocate {
    private:
        std::list<void *> mem_list = {};
        sync::rwlock rwlock = {};
        DWORD error_code = 0;

    public:
        allocate(const allocate &other) = delete;

        allocate(allocate &&other) = delete;

        allocate &operator=(const allocate &other) = delete;

        allocate &operator=(allocate &&other) = delete;

        allocate() = default;

        ~allocate();

        void *malloc(size_t size);

        bool free(void *addr);

        void *malloc_reserve(size_t size);

        bool free_reserve(void *addr, size_t size = 0);

        void *realloc(void *old_addr, size_t new_size);

        [[nodiscard]] DWORD err_code() const;

        [[nodiscard]] std::string err_string() const;

        [[nodiscard]] std::wstring err_wstring() const;
    };
}

#endif //ALLOCATE_H
