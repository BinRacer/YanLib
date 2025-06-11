/* clang-format off */
/*
 * @file autoclean.h
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
#ifndef AUTOCLEAN_H
#define AUTOCLEAN_H

namespace YanLib::helper {
    template <typename T, bool is_file = false> class autoclean {
    private:
        T _value;

        void cleanup();

    public:
        autoclean(const autoclean &other) = delete;

        autoclean(autoclean &&other) = delete;

        autoclean &operator=(const autoclean &other) = delete;

        autoclean &operator=(autoclean &&other) = delete;

        autoclean() = delete;

        explicit autoclean(T value);

        explicit autoclean(T &value);

        ~autoclean();

        operator T &();

        operator T *();

        autoclean &operator=(const T &other);

        autoclean &operator=(T &&other);

        [[nodiscard]] bool is_ok() const;
    };
} // namespace YanLib::helper
#endif // AUTOCLEAN_H
