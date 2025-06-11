//
// Created by BinRacer <native.lab@outlook.com> on 2025/4/2.
//

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
