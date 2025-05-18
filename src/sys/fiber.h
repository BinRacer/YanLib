//
// Created by forkernel on 2025/4/22.
//

#ifndef FIBER_H
#define FIBER_H
#include <Windows.h>
#include <string>
#include <vector>
#include "sync/rwlock.h"

namespace YanLib::sys {
    class fiber {
    private:
        std::vector<void*> fiber_addrs = {};
        sync::rwlock fiber_lock = {};
        uint32_t error_code = 0;

    public:
        fiber(const fiber &other) = delete;

        fiber(fiber &&other) = delete;

        fiber &operator=(const fiber &other) = delete;

        fiber &operator=(fiber &&other) = delete;

        fiber() = default;

        ~fiber();

        void* create(LPFIBER_START_ROUTINE start_addr,
                     void* params,
                     size_t commit = 0,
                     size_t reserve = 0,
                     bool switch_float = true);

        uint32_t fls_alloc(PFLS_CALLBACK_FUNCTION callback);

        bool fls_free(uint32_t index);

        void* fls_get_value(uint32_t index);

        bool fls_set_value(uint32_t index, void* value);

        bool is_fiber();

        void switch_to_fiber(void* addr);

        void yield();

        void* thread_to_fiber(void* params, bool switch_float = true);

        bool fiber_to_thread();

        [[nodiscard]] uint32_t err_code() const;

        [[nodiscard]] std::string err_string() const;

        [[nodiscard]] std::wstring err_wstring() const;
    };
} // namespace YanLib::sys
#endif // FIBER_H
