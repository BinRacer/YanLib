//
// Created by forkernel on 2025/4/2.
//

#ifndef EVENT_H
#define EVENT_H
#include <Windows.h>
#include <string>

namespace YanLib::sync {
    class event {
    private:
        HANDLE event_handle;
        unsigned long error_code;

    public:
        event(const event &other) = delete;

        event(event &&other) = delete;

        event &operator=(const event &other) = delete;

        event &operator=(event &&other) = delete;

        event();

        ~event();

        bool create(SECURITY_ATTRIBUTES* event_attrs = nullptr,
                    bool is_manual_reset = false,
                    bool is_initial_state = false,
                    const wchar_t *name = nullptr);

        bool open(const wchar_t *name,
                  unsigned long desired_access = EVENT_ALL_ACCESS,
                  bool is_inherit_handle = false);

        bool on();

        bool off();

        bool wait(unsigned long milli_seconds = INFINITE);

        [[nodiscard]] unsigned long err_code() const;

        [[nodiscard]] std::string err_string() const;

        [[nodiscard]] std::wstring err_wstring() const;
    };
}
#endif //EVENT_H
