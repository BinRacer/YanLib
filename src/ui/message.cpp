//
// Created by forkernel on 2025/4/29.
//

#include "message.h"
#include "helper/convert.h"

namespace YanLib::ui {
    bool message::get_message(MSG *msg,
                              HWND hwnd,
                              uint32_t msg_filter_min,
                              uint32_t msg_filter_max) {
        int32_t result = GetMessageW(msg,
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
        unsigned long result = GetMessagePos();
        return MAKEPOINTS(result);
    }

    POINTS message::get_unpredicted_message_pos() {
        unsigned long result = GetUnpredictedMessagePos();
        return MAKEPOINTS(result);
    }

    long message::get_message_time() {
        return GetMessageTime();
    }

    bool message::peek_message(MSG *msg,
                               HWND hwnd,
                               uint32_t msg_filter_min,
                               uint32_t msg_filter_max,
                               uint32_t remove_msg) {
        return PeekMessageW(msg,
                            hwnd,
                            msg_filter_min,
                            msg_filter_max,
                            remove_msg);
    }

    bool message::post_message(HWND hwnd,
                               uint32_t msg,
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

    void message::post_quit_message(int32_t exit_code) {
        PostQuitMessage(exit_code);
    }

    bool message::post_thread_message(unsigned long tid,
                                      uint32_t msg,
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

    bool message::message_beep(uint32_t type) {
        if (!MessageBeep(type)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }


    uint32_t message::register_window_message(const wchar_t *message) {
        uint32_t result = RegisterWindowMessageW(message);
        if (!result) {
            error_code = GetLastError();
        }
        return result;
    }

    bool message::reply_message(LRESULT result) {
        return ReplyMessage(result);
    }

    LRESULT message::send_dialog_item_message(HWND hwnd_dialog,
                                              int32_t id_dialog_item,
                                              uint32_t msg,
                                              WPARAM w_param,
                                              LPARAM l_param) {
        return SendDlgItemMessageW(hwnd_dialog,
                                   id_dialog_item,
                                   msg,
                                   w_param,
                                   l_param);
    }

    LRESULT message::send_message(HWND hwnd,
                                  uint32_t msg,
                                  WPARAM w_param,
                                  LPARAM l_param) {
        return SendMessageW(hwnd,
                            msg,
                            w_param,
                            l_param);
    }

    bool message::send_message_callback(HWND hwnd,
                                        uint32_t msg,
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
                                          uint32_t msg,
                                          WPARAM w_param,
                                          LPARAM l_param,
                                          uint32_t flag,
                                          uint32_t timeout,
                                          DWORD_PTR *result) {
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
                                      uint32_t msg,
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

    bool message::skip_pointer_frame_messages(uint32_t pointer_id) {
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

    bool message::call_message_filter(MSG *msg, int32_t code) {
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

    unsigned long message::in_send_message(void *reserved) {
        return InSendMessageEx(reserved);
    }

    bool message::is_dialog_message(HWND hwnd_dialog, MSG *msg) {
        return IsDialogMessageW(hwnd_dialog, msg);
    }

    bool message::is_wow64_message() {
        return IsWow64Message();
    }

    long message::broadcast_system_message(unsigned long flag,
                                           unsigned long *info,
                                           uint32_t msg,
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

    long message::broadcast_system_message(unsigned long flag,
                                           unsigned long *info,
                                           uint32_t msg,
                                           WPARAM w_param,
                                           LPARAM l_param,
                                           BSMINFO *bsm_info) {
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

    bool message::change_window_message_filter(uint32_t message, unsigned long flag) {
        if (!ChangeWindowMessageFilter(message, flag)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool
    message::change_window_message_filter(HWND hwnd,
                                          uint32_t message,
                                          unsigned long action,
                                          CHANGEFILTERSTRUCT *change_filter_struct) {
        if (!ChangeWindowMessageFilterEx(hwnd,
                                         message,
                                         action,
                                         change_filter_struct)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    int32_t message::message_box(HWND hwnd,
                                 const wchar_t *text,
                                 const wchar_t *caption,
                                 uint32_t type) {
        int32_t result = MessageBoxW(hwnd,
                                     text,
                                     caption,
                                     type);
        if (!result) {
            error_code = GetLastError();
        }
        return result;
    }

    int32_t message::message_box(HWND hwnd,
                                 const wchar_t *text,
                                 const wchar_t *caption,
                                 uint32_t type,
                                 uint16_t language_id) {
        int32_t result = MessageBoxExW(hwnd,
                                       text,
                                       caption,
                                       type,
                                       language_id);
        if (!result) {
            error_code = GetLastError();
        }
        return result;
    }

    int32_t message::message_box_indirect(const MSGBOXPARAMSW *msgbox_param) {
        return MessageBoxIndirectW(msgbox_param);
    }

    unsigned long message::get_queue_status(uint32_t flag) {
        return GetQueueStatus(flag);
    }

    unsigned long message::err_code() const {
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
