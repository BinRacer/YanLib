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
        unsigned long error_code = 0;

    public:
        message(const message &other) = delete;

        message(message &&other) = delete;

        message &operator=(const message &other) = delete;

        message &operator=(message &&other) = delete;

        message() = default;

        ~message() = default;

        bool get_message(MSG* msg,
                         HWND hwnd,
                         unsigned int msg_filter_min,
                         unsigned int msg_filter_max);

        LPARAM get_message_extra_info();

        LPARAM set_message_extra_info(LPARAM l_param);

        POINTS get_message_pos();

        POINTS get_unpredicted_message_pos();

        long get_message_time();

        bool peek_message(MSG* msg,
                          HWND hwnd,
                          unsigned int msg_filter_min,
                          unsigned int msg_filter_max,
                          unsigned int remove_msg);

        bool post_message(HWND hwnd,
                          unsigned int msg,
                          WPARAM w_param,
                          LPARAM l_param);

        void post_quit_message(int exit_code);

        bool post_thread_message(unsigned long tid,
                                 unsigned int msg,
                                 WPARAM w_param,
                                 LPARAM l_param);

        bool message_beep(unsigned int type);

        unsigned int register_window_message(const wchar_t *message);

        bool reply_message(LRESULT result);

        LRESULT send_dialog_item_message(HWND hwnd_dialog,
                                         int id_dialog_item,
                                         unsigned int msg,
                                         WPARAM w_param,
                                         LPARAM l_param);

        LRESULT send_message(HWND hwnd,
                             unsigned int msg,
                             WPARAM w_param,
                             LPARAM l_param);

        bool send_message_callback(HWND hwnd,
                                   unsigned int msg,
                                   WPARAM w_param,
                                   LPARAM l_param,
                                   SENDASYNCPROC result_callback,
                                   ULONG_PTR data);

        LRESULT send_message_timeout(HWND hwnd,
                                     unsigned int msg,
                                     WPARAM w_param,
                                     LPARAM l_param,
                                     unsigned int flag,
                                     unsigned int timeout,
                                     DWORD_PTR* result);

        bool send_notify_message(HWND hwnd,
                                 unsigned int msg,
                                 WPARAM w_param,
                                 LPARAM l_param);

        bool skip_pointer_frame_messages(unsigned int pointer_id);

        bool translate_message(const MSG *msg);

        bool wait_message();

        LRESULT dispatch_message(const MSG *msg);

        bool call_message_filter(MSG* msg, int code);

        bool get_current_input_message_source(
            INPUT_MESSAGE_SOURCE *input_message_source);

        bool in_send_message();

        unsigned long in_send_message(void *reserved);

        bool is_dialog_message(HWND hwnd_dialog, MSG* msg);

        bool is_wow64_message();

        long broadcast_system_message(unsigned long flag,
                                      unsigned long* info,
                                      unsigned int msg,
                                      WPARAM w_param,
                                      LPARAM l_param);

        long broadcast_system_message(unsigned long flag,
                                      unsigned long* info,
                                      unsigned int msg,
                                      WPARAM w_param,
                                      LPARAM l_param,
                                      BSMINFO* bsm_info);

        bool change_window_message_filter(unsigned int message, unsigned long flag);

        bool change_window_message_filter(HWND hwnd,
                                          unsigned int message,
                                          unsigned long action,
                                          CHANGEFILTERSTRUCT* change_filter_struct);

        int message_box(HWND hwnd,
                        const wchar_t *text,
                        const wchar_t *caption,
                        unsigned int type);

        int message_box(HWND hwnd,
                        const wchar_t *text,
                        const wchar_t *caption,
                        unsigned int type,
                        unsigned short language_id);

        int message_box_indirect(const MSGBOXPARAMSW *msgbox_param);


        [[nodiscard]] unsigned long err_code() const;

        [[nodiscard]] std::string err_string() const;

        [[nodiscard]] std::wstring err_wstring() const;
    };
}
#endif //MESSAGE_H
