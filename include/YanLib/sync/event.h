//
// Created by forkernel on 2025/4/2.
//

#ifndef EVENT_H
#define EVENT_H
#include <Windows.h>
#include <string>

namespace YanLib {
    namespace sync {
        class event {
        public:
            event(const event &other) = delete;

            event(event &&other) = delete;

            event &operator=(const event &other) = delete;

            event &operator=(event &&other) = delete;

            event();

            ~event();

            bool create(LPSECURITY_ATTRIBUTES lpEventAttributes = nullptr,
                        BOOL bManualReset = FALSE,
                        BOOL bInitialState = FALSE,
                        const wchar_t *lpName = nullptr);

            bool open(const wchar_t *lpName,
                      DWORD dwDesiredAccess = EVENT_ALL_ACCESS,
                      BOOL bInheritHandle = FALSE);

            bool on();

            bool off();

            bool wait(DWORD dwMilliseconds = INFINITE);

            DWORD err_code() const;

            std::string err_string() const;

            std::wstring err_wstring() const;
        };
    }
}
#endif //EVENT_H
