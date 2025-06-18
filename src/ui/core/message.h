/* clang-format off */
/*
 * @file message.h
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
#ifndef MESSAGE_H
#define MESSAGE_H
#include <Windows.h>
#include <minwindef.h>
#include <WinUser.h>
#include <windef.h>
#include <string>
#include "core.h"
namespace YanLib::ui::core {
    class message {
    private:
        uint32_t error_code = 0;

    public:
        message(const message &other) = delete;

        message(message &&other) = delete;

        message &operator=(const message &other) = delete;

        message &operator=(message &&other) = delete;

        message() = default;

        ~message() = default;

        int32_t get(HWND window_handle,
                    MSG *msg,
                    uint32_t filter_min,
                    uint32_t filter_max);

        LPARAM get_extra_info();

        LPARAM set_extra_info(LPARAM lparam);

        POINTS get_pos();

        POINTS get_unpredicted_pos();

        int32_t get_time();

        bool peek(HWND window_handle,
                  MSG *msg /* RegularMessage */,
                  uint32_t filter_min,
                  uint32_t filter_max,
                  MessageRemove flag = MessageRemove::NoRemove);

        bool post(HWND window_handle,
                  uint32_t msg /* RegularMessage */,
                  WPARAM wparam,
                  LPARAM lparam);

        void quit(int32_t exit_code);

        bool post(uint32_t tid,
                  uint32_t msg /* RegularMessage */,
                  WPARAM wparam,
                  LPARAM lparam);

        bool beep(BeepType type = BeepType::IconAsterisk);

        uint32_t register_window(const char *message);

        uint32_t register_window(const wchar_t *message);

        bool reply(LRESULT result);

        LRESULT send_dialog_item(HWND dialog_handle,
                                 int32_t dialog_item_id,
                                 uint32_t msg /* RegularMessage */,
                                 WPARAM wparam,
                                 LPARAM lparam);

        LRESULT send(HWND window_handle,
                     uint32_t msg /* RegularMessage */,
                     WPARAM wparam,
                     LPARAM lparam);

        bool send_callback(HWND window_handle,
                           uint32_t msg /* RegularMessage */,
                           WPARAM wparam,
                           LPARAM lparam,
                           SENDASYNCPROC callback,
                           uintptr_t data);

        LRESULT send_timeout(HWND window_handle,
                             uint32_t msg /* RegularMessage */,
                             WPARAM wparam,
                             LPARAM lparam,
                             uintptr_t *result,
                             uint32_t milli_second,
                             SendTimeoutFlag flag = SendTimeoutFlag::Block);

        bool send_notify(HWND window_handle,
                         uint32_t msg /* RegularMessage */,
                         WPARAM wparam,
                         LPARAM lparam);

        bool skip_pointer_frame(uint32_t pointer_id);

        bool translate(const MSG *msg);

        bool wait();

        LRESULT dispatch(const MSG *msg);

        bool call_filter(MSG *msg, int32_t code);

        bool
        get_current_input_source(INPUT_MESSAGE_SOURCE *input_message_source);

        bool use_send_func();

        bool use_send_func(SendType *type);

        bool is_dialog(HWND dialog_handle, MSG *msg);

        bool is_wow64();

        int32_t broadcast_system(uint32_t msg /* RegularMessage */,
                                 WPARAM wparam,
                                 LPARAM lparam,
                                 BroadcastResult *info,
                                 BroadcastFlag flag);

        int32_t broadcast_system(uint32_t msg /* RegularMessage */,
                                 WPARAM wparam,
                                 LPARAM lparam,
                                 BSMINFO *bsm_info,
                                 BroadcastResult *info,
                                 BroadcastFlag flag);

        bool add_window_filter(uint32_t message);

        bool remove_window_filter(uint32_t message);

        bool change_window_filter(HWND window_handle,
                                  uint32_t message /* RegularMessage */,
                                  CHANGEFILTERSTRUCT *change_filter_struct,
                                  FilterAction action = FilterAction::Allow);

        MessageBoxResult box(HWND window_handle,
                             const char *text,
                             const char *caption,
                             MessageBoxType type = MessageBoxType::Ok |
                                     MessageBoxType::IconInformation);

        MessageBoxResult box(HWND window_handle,
                             const wchar_t *text,
                             const wchar_t *caption,
                             MessageBoxType type = MessageBoxType::Ok |
                                     MessageBoxType::IconInformation);

        MessageBoxResult
        ok_cancel(HWND window_handle,
                  const char *text,
                  const char *caption,
                  MessageBoxType type = MessageBoxType::IconInformation);

        MessageBoxResult
        ok_cancel(HWND window_handle,
                  const wchar_t *text,
                  const wchar_t *caption,
                  MessageBoxType type = MessageBoxType::IconInformation);

        MessageBoxResult abort_retry_ignore(
                HWND window_handle,
                const char *text,
                const char *caption,
                MessageBoxType type = MessageBoxType::IconInformation);

        MessageBoxResult abort_retry_ignore(
                HWND window_handle,
                const wchar_t *text,
                const wchar_t *caption,
                MessageBoxType type = MessageBoxType::IconInformation);

        MessageBoxResult
        yes_no(HWND window_handle,
               const char *text,
               const char *caption,
               MessageBoxType type = MessageBoxType::IconInformation);

        MessageBoxResult
        yes_no(HWND window_handle,
               const wchar_t *text,
               const wchar_t *caption,
               MessageBoxType type = MessageBoxType::IconInformation);

        MessageBoxResult
        yes_no_cancel(HWND window_handle,
                      const char *text,
                      const char *caption,
                      MessageBoxType type = MessageBoxType::IconInformation);

        MessageBoxResult
        yes_no_cancel(HWND window_handle,
                      const wchar_t *text,
                      const wchar_t *caption,
                      MessageBoxType type = MessageBoxType::IconInformation);

        MessageBoxResult
        retry_cancel(HWND window_handle,
                     const char *text,
                     const char *caption,
                     MessageBoxType type = MessageBoxType::IconInformation);

        MessageBoxResult
        retry_cancel(HWND window_handle,
                     const wchar_t *text,
                     const wchar_t *caption,
                     MessageBoxType type = MessageBoxType::IconInformation);

        MessageBoxResult cancel_try_continue(
                HWND window_handle,
                const char *text,
                const char *caption,
                MessageBoxType type = MessageBoxType::IconInformation);

        MessageBoxResult cancel_try_continue(
                HWND window_handle,
                const wchar_t *text,
                const wchar_t *caption,
                MessageBoxType type = MessageBoxType::IconInformation);

        // language_id = MAKELANGID(LANG_CHINESE, SUBLANG_DEFAULT);
        MessageBoxResult box(HWND window_handle,
                             const char *text,
                             const char *caption,
                             uint16_t language_id,
                             MessageBoxType type = MessageBoxType::Ok |
                                     MessageBoxType::IconInformation);

        // language_id = MAKELANGID(LANG_CHINESE, SUBLANG_DEFAULT);
        MessageBoxResult box(HWND window_handle,
                             const wchar_t *text,
                             const wchar_t *caption,
                             uint16_t language_id,
                             MessageBoxType type = MessageBoxType::Ok |
                                     MessageBoxType::IconInformation);

        int32_t box(const MSGBOXPARAMSA *msgbox_param);

        int32_t box(const MSGBOXPARAMSW *msgbox_param);

        // std::pair<current QueueType, still in queue QueueTyp>
        std::pair<QueueType, QueueType> get_queue_status(QueueType type);

        [[nodiscard]] uint32_t err_code() const;

        [[nodiscard]] std::string err_string() const;

        [[nodiscard]] std::wstring err_wstring() const;
    };
} // namespace YanLib::ui::core
#endif // MESSAGE_H
