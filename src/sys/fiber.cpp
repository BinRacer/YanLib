//
// Created by forkernel on 2025/4/22.
//

#include "fiber.h"
#include "helper/convert.h"
#include <random>

namespace YanLib::sys {
    fiber::~fiber() {
        if (!fiber_addrs.empty()) {
            for (auto &addr: fiber_addrs) {
                DeleteFiber(addr);
                addr = nullptr;
            }
            fiber_addrs.clear();
        }
    }

    void *fiber::create(LPFIBER_START_ROUTINE start_addr,
                        void *params,
                        size_t commit,
                        size_t reserve,
                        DWORD flag) {
        void *addr = CreateFiberEx(commit,
                                   reserve,
                                   flag,
                                   start_addr,
                                   params);
        if (!addr) {
            error_code = GetLastError();
            return nullptr;
        }
        fiber_lock.write_lock();
        fiber_addrs.push_back(addr);
        fiber_lock.write_unlock();
        return addr;
    }

    DWORD fiber::fls_alloc(PFLS_CALLBACK_FUNCTION callback) {
        DWORD index = FlsAlloc(callback);
        if (index == FLS_OUT_OF_INDEXES) {
            error_code = GetLastError();
        }
        return index;
    }

    bool fiber::fls_free(DWORD index) {
        if (!FlsFree(index)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    void *fiber::fls_get_value(DWORD index) {
        void *value = FlsGetValue(index);
        if (!value) {
            error_code = GetLastError();
        }
        return value;
    }

    bool fiber::fls_set_value(DWORD index, void *value) {
        if (!FlsSetValue(index, value)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool fiber::is_fiber() {
        return IsThreadAFiber();
    }

    void fiber::switch_to_fiber(void *addr) {
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

    void *fiber::thread_to_fiber(void *params, DWORD flag) {
        void *addr = ConvertThreadToFiberEx(params, flag);
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
        void *addr = GetCurrentFiber();
        if (!addr) {
            error_code = GetLastError();
            return false;
        }
        fiber_lock.write_lock();
        fiber_addrs.erase(
            std::remove_if(fiber_addrs.begin(),
                           fiber_addrs.end(),
                           [addr](const void *fiber_addr) {
                               return fiber_addr == addr;
                           }),
            fiber_addrs.end());
        fiber_lock.write_unlock();
        if (!ConvertFiberToThread()) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    DWORD fiber::err_code() const {
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
}
