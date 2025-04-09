//
// Created by forkernel on 2025/4/4.
//

#ifndef HEAP_H
#define HEAP_H
#include <Windows.h>
#include <string>

namespace YanLib::mem {
    class heap {
        HANDLE hHeap;
        DWORD error_code;

    public:
        heap(const heap &other) = delete;

        heap(heap &&other) = delete;

        heap &operator=(const heap &other) = delete;

        heap &operator=(heap &&other) = delete;

        heap();

        ~heap();

        bool create(DWORD flOptions = 0,
                    size_t dwInitialSize = 0,
                    size_t dwMaximumSize = 0);

        bool open_proc_heap();

        void *malloc(size_t dwBytes) const;

        void *realloc(void *lpMem,
                      size_t dwNewBytes) const;

        bool free(void *lpMem);

        size_t size(void *lpMem) const;

        bool is_ok(void *lpMem) const;

        bool lock();

        bool unlock();

        DWORD err_code() const;

        std::string err_string() const;

        std::wstring err_wstring() const;
    };
}
#endif //HEAP_H
