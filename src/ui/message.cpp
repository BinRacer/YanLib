//
// Created by forkernel on 2025/4/29.
//

#include "message.h"
#include "helper/convert.h"

namespace YanLib::ui {
    bool message::get_message(LPMSG msg,
                              HWND hwnd,
                              UINT msg_filter_min,
                              UINT msg_filter_max) {
        int result = GetMessageW(msg,
                                 hwnd,
                                 msg_filter_min,
                                 msg_filter_max);
        if (result == -1) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    LPARAM message::get_message_extra_info() {
        return GetMessageExtraInfo();
    }

    LPARAM message::set_message_extra_info(LPARAM l_param) {
        return SetMessageExtraInfo(l_param);
    }

    POINTS message::get_message_pos() {
        DWORD result = GetMessagePos();
        return MAKEPOINTS(result);
    }

    POINTS message::get_unpredicted_message_pos() {
        DWORD result = GetUnpredictedMessagePos();
        return MAKEPOINTS(result);
    }

    LONG message::get_message_time() {
        return GetMessageTime();
    }

    bool message::peek_message(LPMSG msg,
                               HWND hwnd,
                               UINT msg_filter_min,
                               UINT msg_filter_max,
                               UINT remove_msg) {
        return PeekMessageW(msg,
                            hwnd,
                            msg_filter_min,
                            msg_filter_max,
                            remove_msg);
    }

    bool message::post_message(HWND hwnd,
                               UINT msg,
                               WPARAM w_param,
                               LPARAM l_param) {
        if (!PostMessageW(hwnd,
                          msg,
                          w_param,
                          l_param)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    void message::post_quit_message(int exit_code) {
        PostQuitMessage(exit_code);
    }

    bool message::post_thread_message(DWORD tid,
                                      UINT msg,
                                      WPARAM w_param,
                                      LPARAM l_param) {
        if (!PostThreadMessageW(tid,
                                msg,
                                w_param,
                                l_param)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool message::message_beep(UINT type) {
        if (!MessageBeep(type)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }


    UINT message::register_window_message(const wchar_t *message) {
        UINT result = RegisterWindowMessageW(message);
        if (!result) {
            error_code = GetLastError();
        }
        return result;
    }

    bool message::reply_message(LRESULT result) {
        return ReplyMessage(result);
    }

    LRESULT message::send_dialog_item_message(HWND hwnd_dialog,
                                              int id_dialog_item,
                                              UINT msg,
                                              WPARAM w_param,
                                              LPARAM l_param) {
        return SendDlgItemMessageW(hwnd_dialog,
                                   id_dialog_item,
                                   msg,
                                   w_param,
                                   l_param);
    }

    LRESULT message::send_message(HWND hwnd,
                                  UINT msg,
                                  WPARAM w_param,
                                  LPARAM l_param) {
        return SendMessageW(hwnd,
                            msg,
                            w_param,
                            l_param);
    }

    bool message::send_message_callback(HWND hwnd,
                                        UINT msg,
                                        WPARAM w_param,
                                        LPARAM l_param,
                                        SENDASYNCPROC result_callback,
                                        ULONG_PTR data) {
        if (!SendMessageCallbackW(hwnd,
                                  msg,
                                  w_param,
                                  l_param,
                                  result_callback,
                                  data)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    LRESULT message::send_message_timeout(HWND hwnd,
                                          UINT msg,
                                          WPARAM w_param,
                                          LPARAM l_param,
                                          UINT flag,
                                          UINT timeout,
                                          PDWORD_PTR result) {
        SetLastError(ERROR_SUCCESS);
        LRESULT ret = SendMessageTimeoutW(hwnd,
                                          msg,
                                          w_param,
                                          l_param,
                                          flag,
                                          timeout,
                                          result);
        error_code = GetLastError();
        return ret;
    }

    bool message::send_notify_message(HWND hwnd,
                                      UINT msg,
                                      WPARAM w_param,
                                      LPARAM l_param) {
        if (!SendNotifyMessageW(hwnd,
                                msg,
                                w_param,
                                l_param)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool message::skip_pointer_frame_messages(UINT32 pointer_id) {
        if (!SkipPointerFrameMessages(pointer_id)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool message::translate_message(const MSG *msg) {
        return TranslateMessage(msg);
    }

    bool message::wait_message() {
        if (!WaitMessage()) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    LRESULT message::dispatch_message(const MSG *msg) {
        return DispatchMessageW(msg);
    }

    bool message::call_message_filter(LPMSG msg, int code) {
        return CallMsgFilterW(msg, code);
    }

    bool message::get_current_input_message_source(
        INPUT_MESSAGE_SOURCE *input_message_source) {
        if (!GetCurrentInputMessageSource(input_message_source)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool message::in_send_message() {
        return InSendMessage();
    }

    DWORD message::in_send_message(void *reserved) {
        return InSendMessageEx(reserved);
    }

    bool message::is_dialog_message(HWND hwnd_dialog, LPMSG msg) {
        return IsDialogMessageW(hwnd_dialog, msg);
    }

    bool message::is_wow64_message() {
        return IsWow64Message();
    }

    long message::broadcast_system_message(DWORD flag,
                                           LPDWORD info,
                                           UINT msg,
                                           WPARAM w_param,
                                           LPARAM l_param) {
        long result = BroadcastSystemMessageW(flag,
                                              info,
                                              msg,
                                              w_param,
                                              l_param);
        if (!result) {
            error_code = GetLastError();
        }
        return result;
    }

    long message::broadcast_system_message(DWORD flag,
                                           LPDWORD info,
                                           UINT msg,
                                           WPARAM w_param,
                                           LPARAM l_param,
                                           PBSMINFO bsm_info) {
        long result = BroadcastSystemMessageExW(flag,
                                                info,
                                                msg,
                                                w_param,
                                                l_param,
                                                bsm_info);
        if (!result) {
            error_code = GetLastError();
        }
        return result;
    }

    bool message::change_window_message_filter(UINT message, DWORD flag) {
        if (!ChangeWindowMessageFilter(message, flag)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool
    message::change_window_message_filter(HWND hwnd,
                                          UINT message,
                                          DWORD action,
                                          PCHANGEFILTERSTRUCT change_filter_struct) {
        if (!ChangeWindowMessageFilterEx(hwnd,
                                         message,
                                         action,
                                         change_filter_struct)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    int message::message_box(HWND hwnd,
                             const wchar_t *text,
                             const wchar_t *caption,
                             UINT type) {
        int result = MessageBoxW(hwnd,
                                 text,
                                 caption,
                                 type);
        if (!result) {
            error_code = GetLastError();
        }
        return result;
    }

    int message::message_box(HWND hwnd,
                             const wchar_t *text,
                             const wchar_t *caption,
                             UINT type,
                             WORD language_id) {
        int result = MessageBoxExW(hwnd,
                                   text,
                                   caption,
                                   type,
                                   language_id);
        if (!result) {
            error_code = GetLastError();
        }
        return result;
    }

    int message::message_box_indirect(const MSGBOXPARAMSW *msgbox_param) {
        return MessageBoxIndirectW(msgbox_param);
    }


    DWORD message::err_code() const {
        return error_code;
    }

    std::string message::err_string() const {
        std::string result = helper::convert::err_string(error_code);
        return result;
    }

    std::wstring message::err_wstring() const {
        std::wstring result = helper::convert::err_wstring(error_code);
        return result;
    }
}
