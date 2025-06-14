/* clang-format off */
/*
 * @file autoclean.cpp
 * @date 2025-04-15
 * @license MIT License
 *
 * Copyright (c) 2025 BinRacer <native.lab@outlook.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
/* clang-format on */
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
