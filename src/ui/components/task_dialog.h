/* clang-format off */
/*
 * @file task_dialog.h
 * @date 2025-06-01
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
#ifndef TASK_DIALOG_H
#define TASK_DIALOG_H
#ifndef UNICODE
#define UNICODE
#endif
#ifndef _UNICODE
#define _UNICODE
#endif
#include <Windows.h>
#include <CommCtrl.h>
#include <cstdint>
#include <string>
#include <vector>
#include "helper/convert.h"
#pragma comment(lib, "ComCtl32.Lib")
#pragma comment(linker, "\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#pragma comment(lib, "User32.Lib")
namespace YanLib::ui::components {
#ifndef TDBUTTONFLAG
#define TDBUTTONFLAG
    enum class TDButtonFlag : uint32_t {
        None = 0,
        Ok = TDCBF_OK_BUTTON,
        Yes = TDCBF_YES_BUTTON,
        No = TDCBF_NO_BUTTON,
        Cancel = TDCBF_CANCEL_BUTTON,
        Retry = TDCBF_RETRY_BUTTON,
        Close = TDCBF_CLOSE_BUTTON,
    };
    inline TDButtonFlag operator|(TDButtonFlag a, TDButtonFlag b) {
        return static_cast<TDButtonFlag>(static_cast<uint32_t>(a) |
                                         static_cast<uint32_t>(b));
    }
#endif
#ifndef TDBUTTONRESULT
#define TDBUTTONRESULT
    enum class TDButtonResult : int32_t {
        Error = 0,
        Ok = IDOK,
        Cancel = IDCANCEL,
        Abort = IDABORT,
        Retry = IDRETRY,
        Ignore = IDIGNORE,
        Yes = IDYES,
        No = IDNO,
        Close = IDCLOSE,
        Help = IDHELP,
        TryAgain = IDTRYAGAIN,
        Continue = IDCONTINUE,
        Timeout = IDTIMEOUT,
    };
#endif
#ifndef TASKDIALOGFLAG
#define TASKDIALOGFLAG
    enum class TaskDialogFlag : uint32_t {
        EnableHyperlinks = TDF_ENABLE_HYPERLINKS,
        UseHiconMain = TDF_USE_HICON_MAIN,
        UseHiconFooter = TDF_USE_HICON_FOOTER,
        AllowDialogCancellation = TDF_ALLOW_DIALOG_CANCELLATION,
        UseCommandLinks = TDF_USE_COMMAND_LINKS,
        UseCommandLinksNoIcon = TDF_USE_COMMAND_LINKS_NO_ICON,
        ExpandFooterArea = TDF_EXPAND_FOOTER_AREA,
        ExpandedByDefault = TDF_EXPANDED_BY_DEFAULT,
        VerificationFlagChecked = TDF_VERIFICATION_FLAG_CHECKED,
        ShowProgressBar = TDF_SHOW_PROGRESS_BAR,
        ShowMarqueeProgressBar = TDF_SHOW_MARQUEE_PROGRESS_BAR,
        CallbackTimer = TDF_CALLBACK_TIMER,
        PositionRelativeToWindow = TDF_POSITION_RELATIVE_TO_WINDOW,
        RtlLayout = TDF_RTL_LAYOUT,
        NoDefaultRadioButton = TDF_NO_DEFAULT_RADIO_BUTTON,
        CanBeMinimized = TDF_CAN_BE_MINIMIZED,
        NoSetForeground = TDF_NO_SET_FOREGROUND,
        SizeToContent = TDF_SIZE_TO_CONTENT,
    };
    inline TaskDialogFlag operator|(TaskDialogFlag a, TaskDialogFlag b) {
        return static_cast<TaskDialogFlag>(static_cast<uint32_t>(a) |
                                           static_cast<uint32_t>(b));
    }
#endif
#ifndef TASKDIALOGELEMENT
#define TASKDIALOGELEMENT
    enum class TaskDialogElement : uint32_t {
        Content = TDE_CONTENT,
        ExpandedInformation = TDE_EXPANDED_INFORMATION,
        Footer = TDE_FOOTER,
        MainInstruction = TDE_MAIN_INSTRUCTION,
    };
#endif
#ifndef PROGRESSSTATE
#define PROGRESSSTATE
    enum class ProgressState : uint32_t {
        Normal = PBST_NORMAL,
        Error = PBST_ERROR,
        Paused = PBST_PAUSED,
    };
#endif
#ifndef TASKDIALOGICONTYPE
#define TASKDIALOGICONTYPE
    enum class TaskDialogIconType : uint32_t {
        Main = TDIE_ICON_MAIN,
        Footer = TDIE_ICON_FOOTER,
    };
#endif
#ifndef TASKDIALOGMESSAGE
#define TASKDIALOGMESSAGE
    enum class TaskDialogMessage : uint32_t {
        NavigatePage = TDM_NAVIGATE_PAGE,
        ClickButton = TDM_CLICK_BUTTON,
        SetMarqueeProgressBar = TDM_SET_MARQUEE_PROGRESS_BAR,
        SetProgressBarState = TDM_SET_PROGRESS_BAR_STATE,
        SetProgressBarRange = TDM_SET_PROGRESS_BAR_RANGE,
        SetProgressBarPos = TDM_SET_PROGRESS_BAR_POS,
        SetProgressBarMarquee = TDM_SET_PROGRESS_BAR_MARQUEE,
        SetElementText = TDM_SET_ELEMENT_TEXT,
        ClickRadioButton = TDM_CLICK_RADIO_BUTTON,
        EnableButton = TDM_ENABLE_BUTTON,
        EnableRadioButton = TDM_ENABLE_RADIO_BUTTON,
        ClickVerification = TDM_CLICK_VERIFICATION,
        UpdateElementText = TDM_UPDATE_ELEMENT_TEXT,
        SetButtonElevationRequiredState =
                TDM_SET_BUTTON_ELEVATION_REQUIRED_STATE,
        UpdateIcon = TDM_UPDATE_ICON,
    };
#endif
#ifndef TASKDIALOGNOTIFY
#define TASKDIALOGNOTIFY
    enum class TaskDialogNotify : uint32_t {
        ButtonClicked = TDN_BUTTON_CLICKED,
        Created = TDN_CREATED,
        Destroyed = TDN_DESTROYED,
        DialogConstructed = TDN_DIALOG_CONSTRUCTED,
        ExpandoButtonClicked = TDN_EXPANDO_BUTTON_CLICKED,
        Help = TDN_HELP,
        HyperlinkClicked = TDN_HYPERLINK_CLICKED,
        Navigated = TDN_NAVIGATED,
        RadioButtonClicked = TDN_RADIO_BUTTON_CLICKED,
        Timer = TDN_TIMER,
        VerificationClicked = TDN_VERIFICATION_CLICKED,
    };
#endif
    class task_dialog {
    public:
        task_dialog(const task_dialog &other) = delete;

        task_dialog(task_dialog &&other) = delete;

        task_dialog &operator=(const task_dialog &other) = delete;

        task_dialog &operator=(task_dialog &&other) = delete;

        task_dialog() = default;

        ~task_dialog() = default;

        static bool create(HWND parent_window_handle,
                           HINSTANCE instance_handle,
                           TDButtonResult *button_result,
                           const wchar_t *title = nullptr,
                           const wchar_t *main_instruction = nullptr,
                           const wchar_t *content = nullptr,
                           TDButtonFlag flag = TDButtonFlag::Ok,
                           const wchar_t *icon = nullptr);

        static bool create(const TASKDIALOGCONFIG *config,
                           TDButtonResult *button_result = nullptr,
                           TDButtonResult *radio_result = nullptr,
                           bool *verify_checked = nullptr);

        static TASKDIALOGCONFIG
        make_config(HWND parent_window_handle,
                    HINSTANCE instance_handle,
                    std::vector<TASKDIALOG_BUTTON> &normal_buttons,
                    TDButtonResult default_button,
                    std::vector<TASKDIALOG_BUTTON> &radio_buttons,
                    TDButtonResult default_radio,
                    PFTASKDIALOGCALLBACK callback,
                    intptr_t callback_data = 0,
                    TaskDialogFlag dialog_flag =
                            TaskDialogFlag::AllowDialogCancellation |
                            TaskDialogFlag::UseCommandLinks |
                            TaskDialogFlag::EnableHyperlinks,
                    TDButtonFlag button_flag = TDButtonFlag::Ok,
                    const wchar_t *title = nullptr,
                    HICON main_icon = nullptr,
                    const wchar_t *main_instruction = nullptr,
                    const wchar_t *content = nullptr,
                    const wchar_t *verify_text = nullptr,
                    const wchar_t *expand_info = nullptr,
                    const wchar_t *expand_control_text = nullptr,
                    const wchar_t *collapse_control_text = nullptr,
                    HICON footer_icon = nullptr,
                    const wchar_t *footer = nullptr,
                    uint32_t width = 0);

        static void click_button(HWND task_dialog_handle, int32_t button_id);

        static void click_radio(HWND task_dialog_handle, int32_t radio_id);

        static void click_verify(HWND task_dialog_handle,
                                 bool checked = true,
                                 bool focus = true);

        static void enable_button(HWND task_dialog_handle, int32_t button_id);

        static void disable_button(HWND task_dialog_handle, int32_t button_id);

        static void enable_radio(HWND task_dialog_handle, int32_t radio_id);

        static void disable_radio(HWND task_dialog_handle, int32_t radio_id);

        static void navigate_page(HWND task_dialog_handle,
                                  TASKDIALOGCONFIG *config);

        static void set_button_elevation_required_state(HWND task_dialog_handle,
                                                        int32_t button_id,
                                                        bool elevation = true);

        static void set_link_elevation_required_state(HWND task_dialog_handle,
                                                      int32_t link_id,
                                                      bool elevation = true);

        static void
        set_element_text(HWND task_dialog_handle,
                         TaskDialogElement element,
                         std::string &text,
                         helper::CodePage code_page = helper::curr_code_page());

        static void set_element_text(HWND task_dialog_handle,
                                     TaskDialogElement element,
                                     std::wstring &text);

        static void update_element_text(
                HWND task_dialog_handle,
                TaskDialogElement element,
                std::string &text,
                helper::CodePage code_page = helper::curr_code_page());

        static void update_element_text(HWND task_dialog_handle,
                                        TaskDialogElement element,
                                        std::wstring &text);

        static void update_icon(HWND task_dialog_handle,
                                TaskDialogIconType type,
                                HICON icon_handle);

        static void
        update_icon(HWND task_dialog_handle,
                    TaskDialogIconType type,
                    std::string &icon,
                    helper::CodePage code_page = helper::curr_code_page());

        static void update_icon(HWND task_dialog_handle,
                                TaskDialogIconType type,
                                std::wstring &icon);

        static void show_marquee_progress(HWND task_dialog_handle);

        static void hide_marquee_progress(HWND task_dialog_handle);

        static void start_marquee_progress(HWND task_dialog_handle,
                                           int32_t milli_seconds = 0);

        static void stop_marquee_progress(HWND task_dialog_handle,
                                          int32_t milli_seconds = 0);

        static int64_t set_progress_pos(HWND task_dialog_handle, int64_t pos);

        // std::pair<min, max>
        static std::pair<uint32_t, uint32_t>
        set_progress_range(HWND task_dialog_handle, uint32_t min, uint32_t max);

        static bool set_progress_state(HWND task_dialog_handle,
                                       ProgressState state);
    };
} // namespace YanLib::ui::components
#endif // TASK_DIALOG_H
