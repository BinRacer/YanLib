//
// Created by forkernel on 2025/4/22.
//

#include "fiber.h"
#include "helper/convert.h"
#include <random>

namespace YanLib::sys {
    fiber::~fiber() {
        for (auto &addr : fiber_addrs) {
            if (addr) {
                DeleteFiber(addr);
                addr = nullptr;
            }
        }
        fiber_addrs.clear();
    }

    void* fiber::create(LPFIBER_START_ROUTINE start_addr,
                        void* params,
                        size_t commit,
                        size_t reserve,
                        bool switch_float) {
        void* addr = CreateFiberEx(commit, reserve,
                                   switch_float ? FIBER_FLAG_FLOAT_SWITCH : 0,
                                   start_addr, params);
        if (!addr) {
            error_code = GetLastError();
            return nullptr;
        }
        fiber_lock.write_lock();
        fiber_addrs.push_back(addr);
        fiber_lock.write_unlock();
        return addr;
    }

    uint32_t fiber::fls_alloc(PFLS_CALLBACK_FUNCTION callback) {
        uint32_t index = FlsAlloc(callback);
        if (index == FLS_OUT_OF_INDEXES) {
            error_code = GetLastError();
        }
        return index;
    }

    bool fiber::fls_free(uint32_t index) {
        if (!FlsFree(index)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    void* fiber::fls_get_value(uint32_t index) {
        void* value = FlsGetValue(index);
        if (!value) {
            error_code = GetLastError();
        }
        return value;
    }

    bool fiber::fls_set_value(uint32_t index, void* value) {
        if (!FlsSetValue(index, value)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool fiber::is_fiber() {
        return IsThreadAFiber();
    }

    void fiber::switch_to_fiber(void* addr) {
        SwitchToFiber(addr);
    }

    void fiber::yield() {
        std::random_device rd = {};
        fiber_lock.read_lock();
        size_t index = rd() % fiber_addrs.size();
        if (index > fiber_addrs.size()) {
            index = fiber_addrs.size() - 1;
        }
        SwitchToFiber(fiber_addrs[index]);
        fiber_lock.read_lock();
    }

    void* fiber::thread_to_fiber(void* params, bool switch_float) {
        void* addr =
                ConvertThreadToFiberEx(params,
                                       switch_float ? FIBER_FLAG_FLOAT_SWITCH
                                                    : 0);
        if (!addr) {
            error_code = GetLastError();
            return nullptr;
        }
        fiber_lock.write_lock();
        fiber_addrs.push_back(addr);
        fiber_lock.write_unlock();
        return addr;
    }

    bool fiber::fiber_to_thread() {
        void* addr = GetCurrentFiber();
        if (!addr) {
            error_code = GetLastError();
            return false;
        }
        fiber_lock.write_lock();
        const auto it = std::find(fiber_addrs.begin(), fiber_addrs.end(), addr);
        if (it != fiber_addrs.end()) {
            *it = nullptr;
        }
        fiber_lock.write_unlock();
        if (!ConvertFiberToThread()) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    uint32_t fiber::err_code() const {
        return error_code;
    }

    std::string fiber::err_string() const {
        std::string result = helper::convert::err_string(error_code);
        return result;
    }

    std::wstring fiber::err_wstring() const {
        std::wstring result = helper::convert::err_wstring(error_code);
        return result;
    }
} // namespace YanLib::sys
