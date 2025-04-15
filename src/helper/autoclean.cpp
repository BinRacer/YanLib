//
// Created by forkernel on 2025/4/15.
//

#include "autoclean.h"
#include <type_traits>
#include <Windows.h>

#include "sys/security.h"

namespace YanLib::helper {
    template<class T>
    autoclean<T>::autoclean(T value): _value(value) {
    }

    template<class T>
    autoclean<T>::~autoclean() {
        if (std::is_same_v<T, HANDLE>) {
            if (_value && _value != INVALID_HANDLE_VALUE) {
                CloseHandle(_value);
            }
        }
    }

    template<class T>
    T &autoclean<T>::get() const {
        return const_cast<T &>(_value);
    }

    template class autoclean<HANDLE>;
}
