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
        unsigned long error_code = 0;

    public:
        desktop(const desktop &other) = delete;

        desktop(desktop &&other) = delete;

        desktop &operator=(const desktop &other) = delete;

        desktop &operator=(desktop &&other) = delete;

        desktop() = default;

        ~desktop() = default;

        HDESK create_desktop(const wchar_t *desktop_name,
                             unsigned long flag = 0,
                             ACCESS_MASK desired_access = DESKTOP_CREATEWINDOW |
                                                          DESKTOP_READOBJECTS |
                                                          DESKTOP_WRITEOBJECTS,
                             SECURITY_ATTRIBUTES *security_attrs = nullptr,
                             unsigned long heap_size = 1024);

        HDESK open_desktop(const wchar_t *desktop_name,
                           unsigned long flag = 0,
                           bool is_inherit = false,
                           ACCESS_MASK desired_access = DESKTOP_READOBJECTS |
                                                        DESKTOP_WRITEOBJECTS);

        HDESK open_input_desktop(unsigned long flag = 0,
                                 bool is_inherit = false,
                                 ACCESS_MASK desired_access = DESKTOP_READOBJECTS |
                                                              DESKTOP_WRITEOBJECTS);

        bool close_desktop(HDESK desktop_handle);


        bool enum_desktop_windows(HDESK desktop_handle,
                                  WNDENUMPROC fn,
                                  LPARAM l_param);

        bool enum_desktops(HWINSTA window_station_handle,
                           DESKTOPENUMPROCW enum_func,
                           LPARAM param);

        HWND get_desktop_window();

        HDESK get_thread_desktop(unsigned long tid);

        bool set_thread_desktop(HDESK desktop_handle);

        bool paint_desktop(HDC dc_handle);

        bool switch_desktop(HDESK desktop_handle);

        HWINSTA create_window_station(const wchar_t *window_station_name,
                                      unsigned long flag = 0,
                                      ACCESS_MASK desired_access = WINSTA_ALL_ACCESS,
                                      SECURITY_ATTRIBUTES *security_attrs = nullptr);

        HWINSTA open_window_station(const wchar_t *window_station_name,
                                    bool is_inherit = false,
                                    ACCESS_MASK desired_access = WINSTA_ALL_ACCESS);

        bool close_window_station(HWINSTA window_station_handle);

        bool enum_window_stations(WINSTAENUMPROCW enum_func, LPARAM param);

        HWINSTA get_process_window_station();

        bool set_process_window_station(HWINSTA window_station_handle);

        bool get_user_object_info(HANDLE desktop_or_window_station_handle,
                                  int index,
                                  void *info,
                                  unsigned long len,
                                  unsigned long *ret_len);

        bool set_user_object_information(HANDLE desktop_or_window_station_handle,
                                         int index,
                                         void *info,
                                         unsigned long len);

        [[nodiscard]] unsigned long err_code() const;

        [[nodiscard]] std::string err_string() const;

        [[nodiscard]] std::wstring err_wstring() const;
    };
}
#endif //DESKTOP_H
