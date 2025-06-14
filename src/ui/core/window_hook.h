/* clang-format off */
/*
 * @file window_hook.h
 * @date 2025-05-18
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
#ifndef WINDOW_HOOK_H
#define WINDOW_HOOK_H
#include <Windows.h>
#include <string>
#include <vector>
#include "sync/rwlock.h"
namespace YanLib::ui::core {
#ifndef HOOKTYPE
#define HOOKTYPE

    enum class HookType : int32_t {
        Min = WH_MIN,
        MsgFilter = WH_MSGFILTER,
        JournalRecord = WH_JOURNALRECORD,
        JournalPlayback = WH_JOURNALPLAYBACK,
        Keyboard = WH_KEYBOARD,
        GetMsg = WH_GETMESSAGE,
        CallWndProc = WH_CALLWNDPROC,
        CBT = WH_CBT,
        SysMsgFilter = WH_SYSMSGFILTER,
        Mouse = WH_MOUSE,
#if defined(_WIN32_WINDOWS)
        HardWare = WH_HARDWARE,
#endif
        Debug = WH_DEBUG,
        Shell = WH_SHELL,
        ForegroundIdle = WH_FOREGROUNDIDLE,
        CallWndProcRet = WH_CALLWNDPROCRET,
        KeyboardLowLevel = WH_KEYBOARD_LL,
        MouseLowLevel = WH_MOUSE_LL,
        Max = WH_MAX,
        MinHook = WH_MINHOOK,
        MaxHook = WH_MAXHOOK,
    };
#endif
#ifndef HOOKCODE
#define HOOKCODE

    enum class HookCode : int32_t {
        Action = HC_ACTION,
        GetNext = HC_GETNEXT,
        Skip = HC_SKIP,
        NoRemove = HC_NOREMOVE,
        NoRem = HC_NOREM,
        SysModalOn = HC_SYSMODALON,
        SysModalOff = HC_SYSMODALOFF,
    };
#endif
#ifndef CBTHOOKCODE
#define CBTHOOKCODE

    enum class CBTHookCode : int32_t {
        MoveSize = HCBT_MOVESIZE,
        MinMax = HCBT_MINMAX,
        QS = HCBT_QS,
        CreateWnd = HCBT_CREATEWND,
        DestroyWnd = HCBT_DESTROYWND,
        Activate = HCBT_ACTIVATE,
        ClickSkipped = HCBT_CLICKSKIPPED,
        KeySkipped = HCBT_KEYSKIPPED,
        SysCommand = HCBT_SYSCOMMAND,
        SetFocus = HCBT_SETFOCUS,
    };
#endif
#ifndef WINDOWEVENT
#define WINDOWEVENT

    enum class WindowEvent : uint32_t {
        Min = EVENT_MIN,
        Max = EVENT_MAX,
        SystemSound = EVENT_SYSTEM_SOUND,
        SystemAlert = EVENT_SYSTEM_ALERT,
        SystemForeground = EVENT_SYSTEM_FOREGROUND,
        SystemMenuStart = EVENT_SYSTEM_MENUSTART,
        SystemMenuEnd = EVENT_SYSTEM_MENUEND,
        SystemMenuPopupStart = EVENT_SYSTEM_MENUPOPUPSTART,
        SystemMenuPopupEnd = EVENT_SYSTEM_MENUPOPUPEND,
        SystemCaptureStart = EVENT_SYSTEM_CAPTURESTART,
        SystemCaptureEnd = EVENT_SYSTEM_CAPTUREEND,
        SystemMoveSizeStart = EVENT_SYSTEM_MOVESIZESTART,
        SystemMoveSizeEnd = EVENT_SYSTEM_MOVESIZEEND,
        SystemContextHelpStart = EVENT_SYSTEM_CONTEXTHELPSTART,
        SystemContextHelpEnd = EVENT_SYSTEM_CONTEXTHELPEND,
        SystemDragDropStart = EVENT_SYSTEM_DRAGDROPSTART,
        SystemDragDropEnd = EVENT_SYSTEM_DRAGDROPEND,
        SystemDialogStart = EVENT_SYSTEM_DIALOGSTART,
        SystemDialogEnd = EVENT_SYSTEM_DIALOGEND,
        SystemScrollingStart = EVENT_SYSTEM_SCROLLINGSTART,
        SystemScrollingEnd = EVENT_SYSTEM_SCROLLINGEND,
        SystemSwitchStart = EVENT_SYSTEM_SWITCHSTART,
        SystemSwitchEnd = EVENT_SYSTEM_SWITCHEND,
        SystemMinimizeStart = EVENT_SYSTEM_MINIMIZESTART,
        SystemMinimizeEnd = EVENT_SYSTEM_MINIMIZEEND,
        SystemDesktopSwitch = EVENT_SYSTEM_DESKTOPSWITCH,
        SystemSwitcherAppGrabbed = EVENT_SYSTEM_SWITCHER_APPGRABBED,
        SystemSwitcherAppOverTarget = EVENT_SYSTEM_SWITCHER_APPOVERTARGET,
        SystemSwitcherAppDropped = EVENT_SYSTEM_SWITCHER_APPDROPPED,
        SystemSwitcherCancelled = EVENT_SYSTEM_SWITCHER_CANCELLED,
        SystemImeKeyNotification = EVENT_SYSTEM_IME_KEY_NOTIFICATION,
        SystemEnd = EVENT_SYSTEM_END,
        OemDefinedStart = EVENT_OEM_DEFINED_START,
        OemDefinedEnd = EVENT_OEM_DEFINED_END,
        UiaEventIdStart = EVENT_UIA_EVENTID_START,
        UiaEventIdEnd = EVENT_UIA_EVENTID_END,
        UiaPropIdStart = EVENT_UIA_PROPID_START,
        UiaPropIdEnd = EVENT_UIA_PROPID_END,
        ConsoleCaret = EVENT_CONSOLE_CARET,
        ConsoleUpdateRegion = EVENT_CONSOLE_UPDATE_REGION,
        ConsoleUpdateSimple = EVENT_CONSOLE_UPDATE_SIMPLE,
        ConsoleUpdateScroll = EVENT_CONSOLE_UPDATE_SCROLL,
        ConsoleLayout = EVENT_CONSOLE_LAYOUT,
        ConsoleStartApplication = EVENT_CONSOLE_START_APPLICATION,
        ConsoleEndApplication = EVENT_CONSOLE_END_APPLICATION,
        ConsoleEnd = EVENT_CONSOLE_END,
        ObjectCreate = EVENT_OBJECT_CREATE,
        ObjectDestroy = EVENT_OBJECT_DESTROY,
        ObjectShow = EVENT_OBJECT_SHOW,
        ObjectHide = EVENT_OBJECT_HIDE,
        ObjectReorder = EVENT_OBJECT_REORDER,
        ObjectFocus = EVENT_OBJECT_FOCUS,
        ObjectSelection = EVENT_OBJECT_SELECTION,
        ObjectSelectionAdd = EVENT_OBJECT_SELECTIONADD,
        ObjectSelectionRemove = EVENT_OBJECT_SELECTIONREMOVE,
        ObjectSelectionWithin = EVENT_OBJECT_SELECTIONWITHIN,
        ObjectStateChange = EVENT_OBJECT_STATECHANGE,
        ObjectLocationChange = EVENT_OBJECT_LOCATIONCHANGE,
        ObjectNameChange = EVENT_OBJECT_NAMECHANGE,
        ObjectDescriptionChange = EVENT_OBJECT_DESCRIPTIONCHANGE,
        ObjectValueChange = EVENT_OBJECT_VALUECHANGE,
        ObjectParentChange = EVENT_OBJECT_PARENTCHANGE,
        ObjectHelpChange = EVENT_OBJECT_HELPCHANGE,
        ObjectDefActionChange = EVENT_OBJECT_DEFACTIONCHANGE,
        ObjectAcceleratorChange = EVENT_OBJECT_ACCELERATORCHANGE,
        ObjectInvoked = EVENT_OBJECT_INVOKED,
        ObjectTextSelectionChanged = EVENT_OBJECT_TEXTSELECTIONCHANGED,
        ObjectContentScrolled = EVENT_OBJECT_CONTENTSCROLLED,
        SystemArrangementPreview = EVENT_SYSTEM_ARRANGMENTPREVIEW,
        ObjectCloaked = EVENT_OBJECT_CLOAKED,
        ObjectUncloaked = EVENT_OBJECT_UNCLOAKED,
        ObjectLiveRegionChanged = EVENT_OBJECT_LIVEREGIONCHANGED,
        ObjectHostedObjectsInvalidated = EVENT_OBJECT_HOSTEDOBJECTSINVALIDATED,
        ObjectDragStart = EVENT_OBJECT_DRAGSTART,
        ObjectDragCancel = EVENT_OBJECT_DRAGCANCEL,
        ObjectDragComplete = EVENT_OBJECT_DRAGCOMPLETE,
        ObjectDragEnter = EVENT_OBJECT_DRAGENTER,
        ObjectDragLeave = EVENT_OBJECT_DRAGLEAVE,
        ObjectDragDropped = EVENT_OBJECT_DRAGDROPPED,
        ObjectImeShow = EVENT_OBJECT_IME_SHOW,
        ObjectImeHide = EVENT_OBJECT_IME_HIDE,
        ObjectImeChange = EVENT_OBJECT_IME_CHANGE,
        ObjectTextEditConversionTargetChanged =
                EVENT_OBJECT_TEXTEDIT_CONVERSIONTARGETCHANGED,
        ObjectEnd = EVENT_OBJECT_END,
        AiaStart = EVENT_AIA_START,
        AiaEnd = EVENT_AIA_END,
    };

    inline WindowEvent operator|(WindowEvent a, WindowEvent b) {
        return static_cast<WindowEvent>(static_cast<uint32_t>(a) |
                                        static_cast<uint32_t>(b));
    }
#endif
#ifndef EVENTFLAG
#define EVENTFLAG

    enum class EventFlag : uint32_t {
        OutOfContext = WINEVENT_OUTOFCONTEXT,
        SkipOwnThread = WINEVENT_SKIPOWNTHREAD,
        SkipOwnProcess = WINEVENT_SKIPOWNPROCESS,
        InContext = WINEVENT_INCONTEXT,

    };

    inline EventFlag operator|(EventFlag a, EventFlag b) {
        return static_cast<EventFlag>(static_cast<uint32_t>(a) |
                                      static_cast<uint32_t>(b));
    }
#endif
#ifndef OBJECTID
#define OBJECTID

    enum class ObjectID : int32_t {
        Window = OBJID_WINDOW,
        SysMenu = OBJID_SYSMENU,
        TitleBar = OBJID_TITLEBAR,
        Menu = OBJID_MENU,
        Client = OBJID_CLIENT,
        VScroll = OBJID_VSCROLL,
        HScroll = OBJID_HSCROLL,
        SizeGrip = OBJID_SIZEGRIP,
        Caret = OBJID_CARET,
        Cursor = OBJID_CURSOR,
        Alert = OBJID_ALERT,
        Sound = OBJID_SOUND,
        QueryClassNameIDX = OBJID_QUERYCLASSNAMEIDX,
        NativeOM = OBJID_NATIVEOM,
    };
#endif
    class window_hook {
    private:
        std::vector<HWND> shell_handles = {};
        std::vector<HHOOK> hook_handles = {};
        std::vector<HWINEVENTHOOK> event_handles = {};
        sync::rwlock shell_rwlock = {};
        sync::rwlock hook_rwlock = {};
        sync::rwlock event_rwlock = {};
        uint32_t error_code = 0;

    public:
        window_hook(const window_hook &other) = delete;

        window_hook(window_hook &&other) = delete;

        window_hook &operator=(const window_hook &other) = delete;

        window_hook &operator=(window_hook &&other) = delete;

        window_hook() = default;

        ~window_hook();

        bool register_shell(HWND window_handle);

        bool unregister_shell(HWND window_handle);

        HHOOK set_hook(HOOKPROC hook_proc,
                       HINSTANCE dll_handle = nullptr,
                       uint32_t tid = 0,
                       HookType hook_type = HookType::GetMsg);

        bool unset_hook(HHOOK hook_handle);

        LRESULT call_next(HHOOK hook_handle,
                          int32_t code,
                          WPARAM wparam,
                          LPARAM lparam);

        HWINEVENTHOOK set_event(WINEVENTPROC event_proc,
                                HMODULE dll_handle = nullptr,
                                uint32_t pid = 0,
                                uint32_t tid = 0,
                                WindowEvent min = WindowEvent::Min,
                                WindowEvent max = WindowEvent::Max,
                                EventFlag flag = EventFlag::OutOfContext |
                                        EventFlag::SkipOwnProcess);

        bool unset_event(HWINEVENTHOOK event_hook);

        bool is_event_installed(uint32_t event);

        void notify_event(HWND window_handle,
                          int32_t control_id,
                          ObjectID object_id = ObjectID::Client,
                          WindowEvent event = WindowEvent::ObjectCreate);

        [[nodiscard]] uint32_t err_code() const;

        [[nodiscard]] std::string err_string() const;

        [[nodiscard]] std::wstring err_wstring() const;
    };
} // namespace YanLib::ui::core
#endif // WINDOW_HOOK_H
