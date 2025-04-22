//
// Created by forkernel on 2025/4/4.
//

#ifndef HEAP_H
#define HEAP_H
#include <Windows.h>
#include <string>
#include <vector>
#include "sync/rwlock.h"

namespace YanLib::mem {
    class heap {
        std::vector<HANDLE> heap_handles = {};
        sync::rwlock heap_rwlock = {};
        DWORD error_code = 0;

    public:
        heap(const heap &other) = delete;

        heap(heap &&other) = delete;

        heap &operator=(const heap &other) = delete;

        heap &operator=(heap &&other) = delete;

        heap() = default;

        ~heap();

        HANDLE create(DWORD options = 0,
                      size_t initial_size = 0,
                      size_t maximum_size = 0);

        HANDLE open();

        void *malloc(HANDLE heap_handle,
                     size_t size) const;

        void *realloc(HANDLE heap_handle,
                      void *addr,
                      size_t new_size) const;

        bool free(HANDLE heap_handle,
                  void *addr);

        size_t size(HANDLE heap_handle,
                    void *addr) const;

        bool is_ok(HANDLE heap_handle,
                   void *addr) const;

        bool lock(HANDLE heap_handle);

        bool unlock(HANDLE heap_handle);

        [[nodiscard]] DWORD err_code() const;

        [[nodiscard]] std::string err_string() const;

        [[nodiscard]] std::wstring err_wstring() const;
    };
}
#endif //HEAP_H
