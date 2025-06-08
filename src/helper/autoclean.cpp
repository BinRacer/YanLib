//
// Created by forkernel on 2025/4/15.
//

#include "autoclean.h"
#include <type_traits>
#include <Windows.h>

namespace YanLib::helper {
    template <typename T, bool is_file>
    autoclean<T, is_file>::autoclean(T value) : _value(value) {
    }

    template <typename T, bool is_file>
    autoclean<T, is_file>::autoclean(T &value) : _value(value) {
    }

    template <typename T, bool is_file> autoclean<T, is_file>::~autoclean() {
        cleanup();
    }

    template <typename T, bool is_file> void autoclean<T, is_file>::cleanup() {
        if (std::is_same_v<T, HANDLE>) {
            if (is_file && _value && _value != INVALID_HANDLE_VALUE) {
                CloseHandle(_value);
                _value = INVALID_HANDLE_VALUE;
            } else if (_value) {
                CloseHandle(_value);
                _value = nullptr;
            }
        }
    }

    template <typename T, bool is_file> autoclean<T, is_file>::operator T &() {
        return _value;
    }

    template <typename T, bool is_file> autoclean<T, is_file>::operator T *() {
        return &_value;
    }

    template <typename T, bool is_file>
    autoclean<T, is_file> &autoclean<T, is_file>::operator=(const T &other) {
        if (_value == other) {
            return *this;
        }
        cleanup();
        _value = std::move(other);
        return *this;
    }

    template <typename T, bool is_file>
    autoclean<T, is_file> &autoclean<T, is_file>::operator=(T &&other) {
        if (_value == other) {
            return *this;
        }
        cleanup();
        _value = std::move(other);
        return *this;
    }

    template <typename T, bool is_file>
    bool autoclean<T, is_file>::is_ok() const {
        if (is_file) {
            return _value && _value != INVALID_HANDLE_VALUE;
        }
        return _value;
    }

    template class autoclean<HANDLE, true>;
    template class autoclean<HANDLE, false>;
} // namespace YanLib::helper
