/* clang-format off */
/*
 * @file mutex.h
 * @date 2025-04-02
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
#ifndef MUTEX_H
#define MUTEX_H
#include <Windows.h>
#include <string>

namespace YanLib::sync {
#ifndef MUTEXACCESS
#define MUTEXACCESS

    enum class MutexAccess : uint32_t {
        Delete = DELETE,
        ReadControl = READ_CONTROL,
        WriteDac = WRITE_DAC,
        WriteOwner = WRITE_OWNER,
        Synchronize = SYNCHRONIZE,
        All = MUTEX_ALL_ACCESS,
        Modify = MUTEX_MODIFY_STATE,
    };

    inline MutexAccess operator|(MutexAccess a, MutexAccess b) {
        return static_cast<MutexAccess>(static_cast<uint32_t>(a) |
                                        static_cast<uint32_t>(b));
    }
#endif
    class mutex {
    private:
        HANDLE mutex_handle;
        uint32_t error_code;

    public:
        mutex(const mutex &other) = delete;

        mutex(mutex &&other) = delete;

        mutex &operator=(const mutex &other) = delete;

        mutex &operator=(mutex &&other) = delete;

        mutex();

        ~mutex();

        bool create(SECURITY_ATTRIBUTES *sa = nullptr,
                    bool is_initial_owner = false,
                    const wchar_t *name = nullptr);

        bool open(const wchar_t *name,
                  MutexAccess access = MutexAccess::All,
                  bool is_inherit = false);

        bool lock(uint32_t milli_seconds = INFINITE);

        bool unlock();

        [[nodiscard]] uint32_t err_code() const;

        [[nodiscard]] std::string err_string() const;

        [[nodiscard]] std::wstring err_wstring() const;
    };
} // namespace YanLib::sync
#endif // MUTEX_H
