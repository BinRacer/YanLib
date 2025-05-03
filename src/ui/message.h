//
// Created by forkernel on 2025/4/29.
//

#ifndef MESSAGE_H
#define MESSAGE_H
#include <Windows.h>
#include <string>

namespace YanLib::ui {
    class message {
    private:
        DWORD error_code = 0;

    public:
        message(const message &other) = delete;

        message(message &&other) = delete;

        message &operator=(const message &other) = delete;

        message &operator=(message &&other) = delete;

        message() = default;

        ~message() = default;

        bool get_message(MSG* msg,
                         HWND hwnd,
                         UINT msg_filter_min,
                         UINT msg_filter_max);

        LPARAM get_message_extra_info();

        LPARAM set_message_extra_info(LPARAM l_param);

        POINTS get_message_pos();

        POINTS get_unpredicted_message_pos();

        LONG get_message_time();

        bool peek_message(MSG* msg,
                          HWND hwnd,
                          UINT msg_filter_min,
                          UINT msg_filter_max,
                          UINT remove_msg);

        bool post_message(HWND hwnd,
                          UINT msg,
                          WPARAM w_param,
                          LPARAM l_param);

        void post_quit_message(int exit_code);

        bool post_thread_message(DWORD tid,
                                 UINT msg,
                                 WPARAM w_param,
                                 LPARAM l_param);

        bool message_beep(UINT type);

        UINT register_window_message(const wchar_t *message);

        bool reply_message(LRESULT result);

        LRESULT send_dialog_item_message(HWND hwnd_dialog,
                                         int id_dialog_item,
                                         UINT msg,
                                         WPARAM w_param,
                                         LPARAM l_param);

        LRESULT send_message(HWND hwnd,
                             UINT msg,
                             WPARAM w_param,
                             LPARAM l_param);

        bool send_message_callback(HWND hwnd,
                                   UINT msg,
                                   WPARAM w_param,
                                   LPARAM l_param,
                                   SENDASYNCPROC result_callback,
                                   ULONG_PTR data);

        LRESULT send_message_timeout(HWND hwnd,
                                     UINT msg,
                                     WPARAM w_param,
                                     LPARAM l_param,
                                     UINT flag,
                                     UINT timeout,
                                     PDWORD_PTR result);

        bool send_notify_message(HWND hwnd,
                                 UINT msg,
                                 WPARAM w_param,
                                 LPARAM l_param);

        bool skip_pointer_frame_messages(UINT32 pointer_id);

        bool translate_message(const MSG *msg);

        bool wait_message();

        LRESULT dispatch_message(const MSG *msg);

        bool call_message_filter(MSG* msg, int code);

        bool get_current_input_message_source(
            INPUT_MESSAGE_SOURCE *input_message_source);

        bool in_send_message();

        DWORD in_send_message(void *reserved);

        bool is_dialog_message(HWND hwnd_dialog, MSG* msg);

        bool is_wow64_message();

        long broadcast_system_message(DWORD flag,
                                      DWORD* info,
                                      UINT msg,
                                      WPARAM w_param,
                                      LPARAM l_param);

        long broadcast_system_message(DWORD flag,
                                      DWORD* info,
                                      UINT msg,
                                      WPARAM w_param,
                                      LPARAM l_param,
                                      BSMINFO* bsm_info);

        bool change_window_message_filter(UINT message, DWORD flag);

        bool change_window_message_filter(HWND hwnd,
                                          UINT message,
                                          DWORD action,
                                          CHANGEFILTERSTRUCT* change_filter_struct);

        int message_box(HWND hwnd,
                        const wchar_t *text,
                        const wchar_t *caption,
                        UINT type);

        int message_box(HWND hwnd,
                        const wchar_t *text,
                        const wchar_t *caption,
                        UINT type,
                        WORD language_id);

        int message_box_indirect(const MSGBOXPARAMSW *msgbox_param);


        [[nodiscard]] DWORD err_code() const;

        [[nodiscard]] std::string err_string() const;

        [[nodiscard]] std::wstring err_wstring() const;
    };
}
#endif //MESSAGE_H
