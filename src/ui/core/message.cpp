/* clang-format off */
/*
 * @file message.cpp
 * @date 2025-04-29
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
#include "message.h"
#include "helper/convert.h"

namespace YanLib::ui::core {
    int32_t message::get(HWND window_handle,
                         MSG *msg,
                         uint32_t filter_min,
                         uint32_t filter_max) {
        const int32_t result =
                GetMessageW(msg, window_handle, filter_min, filter_max);
        if (result == -1) {
            error_code = GetLastError();
        }
        return result;
    }

    LPARAM message::get_extra_info() {
        return GetMessageExtraInfo();
    }

    LPARAM message::set_extra_info(LPARAM lparam) {
        return SetMessageExtraInfo(lparam);
    }

    POINTS message::get_pos() {
        uint32_t result = GetMessagePos();
        return MAKEPOINTS(result);
    }

    POINTS message::get_unpredicted_pos() {
        uint32_t result = GetUnpredictedMessagePos();
        return MAKEPOINTS(result);
    }

    int32_t message::get_time() {
        return GetMessageTime();
    }

    bool message::peek(HWND window_handle,
                       MSG *msg,
                       uint32_t filter_min,
                       uint32_t filter_max,
                       MessageRemove flag) {
        return PeekMessageW(msg, window_handle, filter_min, filter_max,
                            static_cast<uint32_t>(flag));
    }

    bool message::post(HWND window_handle,
                       uint32_t msg,
                       WPARAM wparam,
                       LPARAM lparam) {
        if (!PostMessageW(window_handle, msg, wparam, lparam)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    void message::quit(int32_t exit_code) {
        PostQuitMessage(exit_code);
    }

    bool
    message::post(uint32_t tid, uint32_t msg, WPARAM wparam, LPARAM lparam) {
        if (!PostThreadMessageW(tid, msg, wparam, lparam)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool message::beep(BeepType type) {
        if (!MessageBeep(static_cast<uint32_t>(type))) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    uint32_t message::register_window(const char *message) {
        const uint32_t result = RegisterWindowMessageA(message);
        if (!result) {
            error_code = GetLastError();
        }
        return result;
    }

    uint32_t message::register_window(const wchar_t *message) {
        const uint32_t result = RegisterWindowMessageW(message);
        if (!result) {
            error_code = GetLastError();
        }
        return result;
    }

    bool message::reply(LRESULT result) {
        return ReplyMessage(result);
    }

    LRESULT message::send_dialog_item(HWND dialog_handle,
                                      int32_t dialog_item_id,
                                      uint32_t msg,
                                      WPARAM wparam,
                                      LPARAM lparam) {
        return SendDlgItemMessageW(dialog_handle, dialog_item_id, msg, wparam,
                                   lparam);
    }

    LRESULT message::send(HWND window_handle,
                          uint32_t msg,
                          WPARAM wparam,
                          LPARAM lparam) {
        return SendMessageW(window_handle, msg, wparam, lparam);
    }

    bool message::send_callback(HWND window_handle,
                                uint32_t msg,
                                WPARAM wparam,
                                LPARAM lparam,
                                SENDASYNCPROC callback,
                                uintptr_t data) {
        if (!SendMessageCallbackW(window_handle, msg, wparam, lparam, callback,
                                  data)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    LRESULT message::send_timeout(HWND window_handle,
                                  uint32_t msg,
                                  WPARAM wparam,
                                  LPARAM lparam,
                                  uintptr_t *result,
                                  uint32_t milli_second,
                                  SendTimeoutFlag flag) {
        SetLastError(ERROR_SUCCESS);
        const LRESULT ret =
                SendMessageTimeoutW(window_handle, msg, wparam, lparam,
                                    static_cast<uint32_t>(flag), milli_second,
                                    result);
        error_code = GetLastError();
        return ret;
    }

    bool message::send_notify(HWND window_handle,
                              uint32_t msg,
                              WPARAM wparam,
                              LPARAM lparam) {
        if (!SendNotifyMessageW(window_handle, msg, wparam, lparam)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool message::skip_pointer_frame(uint32_t pointer_id) {
        if (!SkipPointerFrameMessages(pointer_id)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool message::translate(const MSG *msg) {
        return TranslateMessage(msg);
    }

    bool message::wait() {
        if (!WaitMessage()) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    LRESULT message::dispatch(const MSG *msg) {
        return DispatchMessageW(msg);
    }

    bool message::call_filter(MSG *msg, int32_t code) {
        return CallMsgFilterW(msg, code);
    }

    bool message::get_current_input_source(
            INPUT_MESSAGE_SOURCE *input_message_source) {
        if (!GetCurrentInputMessageSource(input_message_source)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool message::use_send_func() {
        return InSendMessage();
    }

    bool message::use_send_func(SendType *type) {
        if (!type) {
            error_code = STATUS_ACCESS_VIOLATION;
            return false;
        }
        *type = static_cast<SendType>(InSendMessageEx(nullptr));
        if (*type == SendType::NoSend) {
            return false;
        }
        return true;
    }

    bool message::is_dialog(HWND dialog_handle, MSG *msg) {
        return IsDialogMessageW(dialog_handle, msg);
    }

    bool message::is_wow64() {
        return IsWow64Message();
    }

    int32_t message::broadcast_system(uint32_t msg,
                                      WPARAM wparam,
                                      LPARAM lparam,
                                      BroadcastResult *info,
                                      BroadcastFlag flag) {
        if (!info) {
            error_code = STATUS_ACCESS_VIOLATION;
            return false;
        }
        auto temp = static_cast<unsigned long>(*info);
        const int32_t result =
                BroadcastSystemMessageW(static_cast<uint32_t>(flag), &temp, msg,
                                        wparam, lparam);
        *info = static_cast<BroadcastResult>(temp);
        if (!result) {
            error_code = GetLastError();
        }
        return result;
    }

    int32_t message::broadcast_system(uint32_t msg /* RegularMessage */,
                                      WPARAM wparam,
                                      LPARAM lparam,
                                      BSMINFO *bsm_info,
                                      BroadcastResult *info,
                                      BroadcastFlag flag) {
        if (!info) {
            error_code = STATUS_ACCESS_VIOLATION;
            return false;
        }
        auto temp = static_cast<unsigned long>(*info);
        const int32_t result =
                BroadcastSystemMessageExW(static_cast<uint32_t>(flag), &temp,
                                          msg, wparam, lparam, bsm_info);
        *info = static_cast<BroadcastResult>(temp);
        if (!result) {
            error_code = GetLastError();
        }
        return result;
    }

    bool message::add_window_filter(uint32_t message) {
        if (!ChangeWindowMessageFilter(message, MSGFLT_ADD)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool message::remove_window_filter(uint32_t message) {
        if (!ChangeWindowMessageFilter(message, MSGFLT_REMOVE)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool message::change_window_filter(HWND window_handle,
                                       uint32_t message,
                                       CHANGEFILTERSTRUCT *change_filter_struct,
                                       FilterAction action) {
        if (!ChangeWindowMessageFilterEx(window_handle, message,
                                         static_cast<uint32_t>(action),
                                         change_filter_struct)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    MessageBoxResult message::box(HWND window_handle,
                                  const char *text,
                                  const char *caption,
                                  MessageBoxType type) {
        int32_t result = MessageBoxA(window_handle, text, caption,
                                     static_cast<uint32_t>(type));
        if (!result) {
            error_code = GetLastError();
        }
        return static_cast<MessageBoxResult>(result);
    }

    MessageBoxResult message::box(HWND window_handle,
                                  const wchar_t *text,
                                  const wchar_t *caption,
                                  MessageBoxType type) {
        int32_t result = MessageBoxW(window_handle, text, caption,
                                     static_cast<uint32_t>(type));
        if (!result) {
            error_code = GetLastError();
        }
        return static_cast<MessageBoxResult>(result);
    }

    MessageBoxResult message::ok_cancel(HWND window_handle,
                                        const char *text,
                                        const char *caption,
                                        MessageBoxType type) {
        int32_t result = MessageBoxA(window_handle, text, caption,
                                     static_cast<uint32_t>(
                                             type | MessageBoxType::OkCancel));
        if (!result) {
            error_code = GetLastError();
        }
        return static_cast<MessageBoxResult>(result);
    }

    MessageBoxResult message::ok_cancel(HWND window_handle,
                                        const wchar_t *text,
                                        const wchar_t *caption,
                                        MessageBoxType type) {
        int32_t result = MessageBoxW(window_handle, text, caption,
                                     static_cast<uint32_t>(
                                             type | MessageBoxType::OkCancel));
        if (!result) {
            error_code = GetLastError();
        }
        return static_cast<MessageBoxResult>(result);
    }

    MessageBoxResult message::abort_retry_ignore(HWND window_handle,
                                                 const char *text,
                                                 const char *caption,
                                                 MessageBoxType type) {
        int32_t result =
                MessageBoxA(window_handle, text, caption,
                            static_cast<uint32_t>(
                                    type | MessageBoxType::AbortRetryIgnore));
        if (!result) {
            error_code = GetLastError();
        }
        return static_cast<MessageBoxResult>(result);
    }

    MessageBoxResult message::abort_retry_ignore(HWND window_handle,
                                                 const wchar_t *text,
                                                 const wchar_t *caption,
                                                 MessageBoxType type) {
        int32_t result =
                MessageBoxW(window_handle, text, caption,
                            static_cast<uint32_t>(
                                    type | MessageBoxType::AbortRetryIgnore));
        if (!result) {
            error_code = GetLastError();
        }
        return static_cast<MessageBoxResult>(result);
    }

    MessageBoxResult message::yes_no(HWND window_handle,
                                     const char *text,
                                     const char *caption,
                                     MessageBoxType type) {
        int32_t result = MessageBoxA(window_handle, text, caption,
                                     static_cast<uint32_t>(
                                             type | MessageBoxType::YesNo));
        if (!result) {
            error_code = GetLastError();
        }
        return static_cast<MessageBoxResult>(result);
    }

    MessageBoxResult message::yes_no(HWND window_handle,
                                     const wchar_t *text,
                                     const wchar_t *caption,
                                     MessageBoxType type) {
        int32_t result = MessageBoxW(window_handle, text, caption,
                                     static_cast<uint32_t>(
                                             type | MessageBoxType::YesNo));
        if (!result) {
            error_code = GetLastError();
        }
        return static_cast<MessageBoxResult>(result);
    }

    MessageBoxResult message::yes_no_cancel(HWND window_handle,
                                            const char *text,
                                            const char *caption,
                                            MessageBoxType type) {
        int32_t result =
                MessageBoxA(window_handle, text, caption,
                            static_cast<uint32_t>(type |
                                                  MessageBoxType::YesNoCancel));
        if (!result) {
            error_code = GetLastError();
        }
        return static_cast<MessageBoxResult>(result);
    }

    MessageBoxResult message::yes_no_cancel(HWND window_handle,
                                            const wchar_t *text,
                                            const wchar_t *caption,
                                            MessageBoxType type) {
        int32_t result =
                MessageBoxW(window_handle, text, caption,
                            static_cast<uint32_t>(type |
                                                  MessageBoxType::YesNoCancel));
        if (!result) {
            error_code = GetLastError();
        }
        return static_cast<MessageBoxResult>(result);
    }

    MessageBoxResult message::retry_cancel(HWND window_handle,
                                           const char *text,
                                           const char *caption,
                                           MessageBoxType type) {
        int32_t result =
                MessageBoxA(window_handle, text, caption,
                            static_cast<uint32_t>(type |
                                                  MessageBoxType::RetryCancel));
        if (!result) {
            error_code = GetLastError();
        }
        return static_cast<MessageBoxResult>(result);
    }

    MessageBoxResult message::retry_cancel(HWND window_handle,
                                           const wchar_t *text,
                                           const wchar_t *caption,
                                           MessageBoxType type) {
        int32_t result =
                MessageBoxW(window_handle, text, caption,
                            static_cast<uint32_t>(type |
                                                  MessageBoxType::RetryCancel));
        if (!result) {
            error_code = GetLastError();
        }
        return static_cast<MessageBoxResult>(result);
    }

    MessageBoxResult message::cancel_try_continue(HWND window_handle,
                                                  const char *text,
                                                  const char *caption,
                                                  MessageBoxType type) {
        int32_t result =
                MessageBoxA(window_handle, text, caption,
                            static_cast<uint32_t>(
                                    type | MessageBoxType::CancelTryContinue));
        if (!result) {
            error_code = GetLastError();
        }
        return static_cast<MessageBoxResult>(result);
    }

    MessageBoxResult message::cancel_try_continue(HWND window_handle,
                                                  const wchar_t *text,
                                                  const wchar_t *caption,
                                                  MessageBoxType type) {
        int32_t result =
                MessageBoxW(window_handle, text, caption,
                            static_cast<uint32_t>(
                                    type | MessageBoxType::CancelTryContinue));
        if (!result) {
            error_code = GetLastError();
        }
        return static_cast<MessageBoxResult>(result);
    }

    MessageBoxResult message::box(HWND window_handle,
                                  const char *text,
                                  const char *caption,
                                  uint16_t language_id,
                                  MessageBoxType type) {
        int32_t result =
                MessageBoxExA(window_handle, text, caption,
                              static_cast<uint32_t>(type), language_id);
        if (!result) {
            error_code = GetLastError();
        }
        return static_cast<MessageBoxResult>(result);
    }

    MessageBoxResult message::box(HWND window_handle,
                                  const wchar_t *text,
                                  const wchar_t *caption,
                                  uint16_t language_id,
                                  MessageBoxType type) {
        int32_t result =
                MessageBoxExW(window_handle, text, caption,
                              static_cast<uint32_t>(type), language_id);
        if (!result) {
            error_code = GetLastError();
        }
        return static_cast<MessageBoxResult>(result);
    }

    int32_t message::box(const MSGBOXPARAMSA *msgbox_param) {
        return MessageBoxIndirectA(msgbox_param);
    }

    int32_t message::box(const MSGBOXPARAMSW *msgbox_param) {
        return MessageBoxIndirectW(msgbox_param);
    }

    std::pair<QueueType, QueueType> message::get_queue_status(QueueType type) {
        const uint32_t status = GetQueueStatus(static_cast<uint32_t>(type));
        auto current = static_cast<QueueType>(HIWORD(status));
        auto still = static_cast<QueueType>(LOWORD(status));
        return std::make_pair(current, still);
    }

    uint32_t message::err_code() const {
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
} // namespace YanLib::ui::core
