/* clang-format off */
/*
 * @file event.h
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
#ifndef EVENT_H
#define EVENT_H
#include <Windows.h>
#include <string>

namespace YanLib::sync {
#ifndef EVENTACCESS
#define EVENTACCESS

    enum class EventAccess : uint32_t {
        Delete = DELETE,
        ReadControl = READ_CONTROL,
        WriteDac = WRITE_DAC,
        WriteOwner = WRITE_OWNER,
        Synchronize = SYNCHRONIZE,
        All = EVENT_ALL_ACCESS,
        Modify = EVENT_MODIFY_STATE,
    };

    inline EventAccess operator|(EventAccess a, EventAccess b) {
        return static_cast<EventAccess>(static_cast<uint32_t>(a) |
                                        static_cast<uint32_t>(b));
    }
#endif

    class event {
    private:
        HANDLE event_handle;
        uint32_t error_code;

    public:
        event(const event &other) = delete;

        event(event &&other) = delete;

        event &operator=(const event &other) = delete;

        event &operator=(event &&other) = delete;

        event();

        ~event();

        bool create(SECURITY_ATTRIBUTES *sa = nullptr,
                    bool is_manual_reset = false,
                    bool is_initial_state = false,
                    const wchar_t *name = nullptr);

        bool open(const wchar_t *name,
                  EventAccess access = EventAccess::All,
                  bool is_inherit = false);

        bool on();

        bool off();

        bool wait(uint32_t milli_seconds = INFINITE);

        [[nodiscard]] uint32_t err_code() const;

        [[nodiscard]] std::string err_string() const;

        [[nodiscard]] std::wstring err_wstring() const;
    };
} // namespace YanLib::sync
#endif // EVENT_H
