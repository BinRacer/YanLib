/* clang-format off */
/*
 * @file semaphore.h
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
#ifndef SEMAPHORE_H
#define SEMAPHORE_H
#include <Windows.h>
#include <string>

namespace YanLib::sync {
#ifndef SEMAPHOREACCESS
#define SEMAPHOREACCESS

    enum class SemaphoreAccess : uint32_t {
        Delete = DELETE,
        ReadControl = READ_CONTROL,
        WriteDac = WRITE_DAC,
        WriteOwner = WRITE_OWNER,
        Synchronize = SYNCHRONIZE,
        All = SEMAPHORE_ALL_ACCESS,
        Modify = SEMAPHORE_MODIFY_STATE,
    };

    inline SemaphoreAccess operator|(SemaphoreAccess a, SemaphoreAccess b) {
        return static_cast<SemaphoreAccess>(static_cast<uint32_t>(a) |
                                            static_cast<uint32_t>(b));
    }
#endif

    class semaphore {
    private:
        HANDLE semaphore_handle;
        uint32_t error_code;

    public:
        semaphore(const semaphore &other) = delete;

        semaphore(semaphore &&other) = delete;

        semaphore &operator=(const semaphore &other) = delete;

        semaphore &operator=(semaphore &&other) = delete;

        semaphore();

        ~semaphore();

        bool create(SECURITY_ATTRIBUTES *sa = nullptr,
                    int32_t initial_count = 1,
                    int32_t maximum_count = 1,
                    const wchar_t *name = nullptr);

        bool open(const wchar_t *name,
                  SemaphoreAccess access = SemaphoreAccess::All,
                  bool inherit_handle = false);

        bool wait(uint32_t milli_seconds = INFINITE);

        bool signal(int32_t release_count = 1,
                    int32_t *previous_count = nullptr);

        [[nodiscard]] uint32_t err_code() const;

        [[nodiscard]] std::string err_string() const;

        [[nodiscard]] std::wstring err_wstring() const;
    };
} // namespace YanLib::sync
#endif // SEMAPHORE_H
