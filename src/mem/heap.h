//
// Created by forkernel on 2025/4/4.
//

#ifndef HEAP_H
#define HEAP_H
#include <Windows.h>
#include <string>

namespace YanLib::mem {
    class heap {
        HANDLE heap_handle;
        DWORD error_code;

    public:
        heap(const heap &other) = delete;

        heap(heap &&other) = delete;

        heap &operator=(const heap &other) = delete;

        heap &operator=(heap &&other) = delete;

        heap();

        ~heap();

        bool create(DWORD options = 0,
                    size_t initial_size = 0,
                    size_t maximum_size = 0);

        bool open_proc_heap();

        [[nodiscard]] void *malloc(size_t size) const;

        void *realloc(void *addr,
                      size_t new_size) const;

        bool free(void *addr);

        size_t size(void *addr) const;

        bool is_ok(void *addr) const;

        bool lock();

        bool unlock();

        [[nodiscard]] DWORD err_code() const;

        [[nodiscard]] std::string err_string() const;

        [[nodiscard]] std::wstring err_wstring() const;
    };
}
#endif //HEAP_H
