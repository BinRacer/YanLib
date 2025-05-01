//
// Created by forkernel on 2025/5/1.
//

#ifndef DESKTOP_H
#define DESKTOP_H
#include <Windows.h>
#include <string>

namespace YanLib::ui {
    class desktop {
    private:
        DWORD error_code = 0;

    public:
        desktop(const desktop &other) = delete;

        desktop(desktop &&other) = delete;

        desktop &operator=(const desktop &other) = delete;

        desktop &operator=(desktop &&other) = delete;

        desktop() = default;

        ~desktop() = default;

        HDESK create_desktop(const wchar_t *desktop_name,
                             DWORD flag = 0,
                             ACCESS_MASK desired_access = DESKTOP_CREATEWINDOW |
                                                          DESKTOP_READOBJECTS |
                                                          DESKTOP_WRITEOBJECTS,
                             LPSECURITY_ATTRIBUTES security_attrs = nullptr,
                             ULONG heap_size = 1024);

        HDESK open_desktop(const wchar_t *desktop_name,
                           DWORD flag = 0,
                           bool is_inherit = false,
                           ACCESS_MASK desired_access = DESKTOP_READOBJECTS |
                                                        DESKTOP_WRITEOBJECTS);

        HDESK open_input_desktop(DWORD flag = 0,
                                 bool is_inherit = false,
                                 ACCESS_MASK desired_access = DESKTOP_READOBJECTS |
                                                              DESKTOP_WRITEOBJECTS);

        bool close_desktop(HDESK desktop_handle);

        bool enum_desktops(HWINSTA window_station_handle,
                           DESKTOPENUMPROCW enum_func,
                           LPARAM param);

        HDESK get_thread_desktop(DWORD tid);

        bool set_thread_desktop(HDESK desktop_handle);

        bool paint_desktop(HDC hdc);

        bool switch_desktop(HDESK desktop_handle);

        [[nodiscard]] DWORD err_code() const;

        [[nodiscard]] std::string err_string() const;

        [[nodiscard]] std::wstring err_wstring() const;
    };
}
#endif //DESKTOP_H
