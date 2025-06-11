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
#include <string>

namespace YanLib::ui::core {
#ifndef MESSAGEREMOVE
#define MESSAGEREMOVE

    enum class MessageRemove : uint32_t {
        NoRemove = PM_NOREMOVE,
        Remove = PM_REMOVE,
        NoYield = PM_NOYIELD,
        QSInput = PM_QS_INPUT,
        QSPostMessage = PM_QS_POSTMESSAGE,
        QSPaint = PM_QS_PAINT,
        QSSendMessage = PM_QS_SENDMESSAGE,
    };

    inline MessageRemove operator|(MessageRemove a, MessageRemove b) {
        return static_cast<MessageRemove>(static_cast<uint32_t>(a) |
                                          static_cast<uint32_t>(b));
    }
#endif
#ifndef REGULARMESSAGE
#define REGULARMESSAGE

    enum class RegularMessage : uint32_t {
        Null = WM_NULL,
        Create = WM_CREATE,
        Destroy = WM_DESTROY,
        Move = WM_MOVE,
        Size = WM_SIZE,
        Activate = WM_ACTIVATE,
        SetFocus = WM_SETFOCUS,
        KillFocus = WM_KILLFOCUS,
        Enable = WM_ENABLE,
        SetRedraw = WM_SETREDRAW,
        SetText = WM_SETTEXT,
        GetText = WM_GETTEXT,
        GetTextLength = WM_GETTEXTLENGTH,
        Paint = WM_PAINT,
        Close = WM_CLOSE,
        QueryEndSession = WM_QUERYENDSESSION,
        QueryOpen = WM_QUERYOPEN,
        EndSession = WM_ENDSESSION,
        Quit = WM_QUIT,
        EraseBackground = WM_ERASEBKGND,
        SysColorChange = WM_SYSCOLORCHANGE,
        ShowWindow = WM_SHOWWINDOW,
        WinIniChange = WM_WININICHANGE,
        SettingChange = WM_SETTINGCHANGE,
        DevModeChange = WM_DEVMODECHANGE,
        ActivateApp = WM_ACTIVATEAPP,
        FontChange = WM_FONTCHANGE,
        TimeChange = WM_TIMECHANGE,
        CancelMode = WM_CANCELMODE,
        SetCursor = WM_SETCURSOR,
        MouseActivate = WM_MOUSEACTIVATE,
        ChildActivate = WM_CHILDACTIVATE,
        QueueSync = WM_QUEUESYNC,
        GetMinMaxInfo = WM_GETMINMAXINFO,
        PaintIcon = WM_PAINTICON,
        IconEraseBackground = WM_ICONERASEBKGND,
        NextDialogCtl = WM_NEXTDLGCTL,
        SpoolerStatus = WM_SPOOLERSTATUS,
        DrawItem = WM_DRAWITEM,
        MeasureItem = WM_MEASUREITEM,
        DeleteItem = WM_DELETEITEM,
        VKeyToItem = WM_VKEYTOITEM,
        CharToItem = WM_CHARTOITEM,
        SetFont = WM_SETFONT,
        GetFont = WM_GETFONT,
        SetHotKey = WM_SETHOTKEY,
        GetHotKey = WM_GETHOTKEY,
        QueryDragIcon = WM_QUERYDRAGICON,
        CompareItem = WM_COMPAREITEM,
        GetObj = WM_GETOBJECT,
        Compacting = WM_COMPACTING,
        WindowPosChanging = WM_WINDOWPOSCHANGING,
        WindowPosChanged = WM_WINDOWPOSCHANGED,
        Power = WM_POWER,
        CopyData = WM_COPYDATA,
        CancelJournal = WM_CANCELJOURNAL,
        Notify = WM_NOTIFY,
        InputLangChangeRequest = WM_INPUTLANGCHANGEREQUEST,
        InputLangChange = WM_INPUTLANGCHANGE,
        TCard = WM_TCARD,
        Help = WM_HELP,
        UserChanged = WM_USERCHANGED,
        NotifyFormat = WM_NOTIFYFORMAT,
        ContextMenu = WM_CONTEXTMENU,
        StyleChanging = WM_STYLECHANGING,
        StyleChanged = WM_STYLECHANGED,
        DisplayChange = WM_DISPLAYCHANGE,
        GetIcon = WM_GETICON,
        SetIcon = WM_SETICON,
        NcCreate = WM_NCCREATE,
        NcDestroy = WM_NCDESTROY,
        NcCalcSize = WM_NCCALCSIZE,
        NcHitTest = WM_NCHITTEST,
        NcPaint = WM_NCPAINT,
        NcActivate = WM_NCACTIVATE,
        GetDialogCode = WM_GETDLGCODE,
        SyncPaint = WM_SYNCPAINT,
        NcMouseMove = WM_NCMOUSEMOVE,
        NcLButtonDown = WM_NCLBUTTONDOWN,
        NcLButtonUp = WM_NCLBUTTONUP,
        NcLButtonDoubleClick = WM_NCLBUTTONDBLCLK,
        NcRButtonDown = WM_NCRBUTTONDOWN,
        NcRButtonUp = WM_NCRBUTTONUP,
        NcRButtonDoubleClick = WM_NCRBUTTONDBLCLK,
        NcMButtonDown = WM_NCMBUTTONDOWN,
        NcMButtonUp = WM_NCMBUTTONUP,
        NcMButtonDoubleClick = WM_NCMBUTTONDBLCLK,
        NcXButtonDown = WM_NCXBUTTONDOWN,
        NcXButtonUp = WM_NCXBUTTONUP,
        NcXButtonDoubleClick = WM_NCXBUTTONDBLCLK,
        InputDeviceChange = WM_INPUT_DEVICE_CHANGE,
        Input = WM_INPUT,
        KeyFirst = WM_KEYFIRST,
        KeyDown = WM_KEYDOWN,
        KeyUp = WM_KEYUP,
        Char = WM_CHAR,
        DeadChar = WM_DEADCHAR,
        SysKeyDown = WM_SYSKEYDOWN,
        SysKeyUp = WM_SYSKEYUP,
        SysChar = WM_SYSCHAR,
        SysDeadChar = WM_SYSDEADCHAR,
        UniChar = WM_UNICHAR,
        KeyLast = WM_KEYLAST,
        ImeStartComposition = WM_IME_STARTCOMPOSITION,
        ImeEndComposition = WM_IME_ENDCOMPOSITION,
        ImeComposition = WM_IME_COMPOSITION,
        ImeKeyLast = WM_IME_KEYLAST,
        InitDialog = WM_INITDIALOG,
        Command = WM_COMMAND,
        SysCommand = WM_SYSCOMMAND,
        Timer = WM_TIMER,
        HScroll = WM_HSCROLL,
        VScroll = WM_VSCROLL,
        InitMenu = WM_INITMENU,
        InitMenuPopup = WM_INITMENUPOPUP,
        Gesture = WM_GESTURE,
        GestureNotify = WM_GESTURENOTIFY,
        MenuSelect = WM_MENUSELECT,
        MenuChar = WM_MENUCHAR,
        EnterIdle = WM_ENTERIDLE,
        MenuRButtonUp = WM_MENURBUTTONUP,
        MenuDrag = WM_MENUDRAG,
        MenuGetObject = WM_MENUGETOBJECT,
        UnInitMenuPopup = WM_UNINITMENUPOPUP,
        MenuCommand = WM_MENUCOMMAND,
        ChangeUIState = WM_CHANGEUISTATE,
        UpdateUIState = WM_UPDATEUISTATE,
        QueryUIState = WM_QUERYUISTATE,
        CtlColorMsgBox = WM_CTLCOLORMSGBOX,
        CtlColorEdit = WM_CTLCOLOREDIT,
        CtlColorListBox = WM_CTLCOLORLISTBOX,
        CtlColorBtn = WM_CTLCOLORBTN,
        CtlColorDialog = WM_CTLCOLORDLG,
        CtlColorScrollBar = WM_CTLCOLORSCROLLBAR,
        CtlColorStatic = WM_CTLCOLORSTATIC,
        MouseFirst = WM_MOUSEFIRST,
        MouseMove = WM_MOUSEMOVE,
        LButtonDown = WM_LBUTTONDOWN,
        LButtonUp = WM_LBUTTONUP,
        LButtonDoubleClick = WM_LBUTTONDBLCLK,
        RButtonDown = WM_RBUTTONDOWN,
        RButtonUp = WM_RBUTTONUP,
        RButtonDoubleClick = WM_RBUTTONDBLCLK,
        MButtonDown = WM_MBUTTONDOWN,
        MButtonUp = WM_MBUTTONUP,
        MButtonDoubleClick = WM_MBUTTONDBLCLK,
        MouseWheel = WM_MOUSEWHEEL,
        XButtonDown = WM_XBUTTONDOWN,
        XButtonUp = WM_XBUTTONUP,
        XButtonDoubleClick = WM_XBUTTONDBLCLK,
        MouseHWheel = WM_MOUSEHWHEEL,
        MouseLast = WM_MOUSELAST,
        ParentNotify = WM_PARENTNOTIFY,
        EnterMenuLoop = WM_ENTERMENULOOP,
        ExitMenuLoop = WM_EXITMENULOOP,
        NextMenu = WM_NEXTMENU,
        Sizing = WM_SIZING,
        CaptureChanged = WM_CAPTURECHANGED,
        Moving = WM_MOVING,
        PowerBroadcast = WM_POWERBROADCAST,
        DeviceChange = WM_DEVICECHANGE,
        MDICreate = WM_MDICREATE,
        MDIDestroy = WM_MDIDESTROY,
        MDIActivate = WM_MDIACTIVATE,
        MDIRestore = WM_MDIRESTORE,
        MDINext = WM_MDINEXT,
        MDIMaximize = WM_MDIMAXIMIZE,
        MDITile = WM_MDITILE,
        MDICascade = WM_MDICASCADE,
        MDIIconArrange = WM_MDIICONARRANGE,
        MDIGetActive = WM_MDIGETACTIVE,
        MDISetMenu = WM_MDISETMENU,
        EnterSizeMove = WM_ENTERSIZEMOVE,
        ExitSizeMove = WM_EXITSIZEMOVE,
        DropFiles = WM_DROPFILES,
        MDIRefreshMenu = WM_MDIREFRESHMENU,
        PointerDeviceChange = WM_POINTERDEVICECHANGE,
        PointerDeviceInRange = WM_POINTERDEVICEINRANGE,
        PointerDeviceOutOfRange = WM_POINTERDEVICEOUTOFRANGE,
        Touch = WM_TOUCH,
        NcPointerUpdate = WM_NCPOINTERUPDATE,
        NcPointerDown = WM_NCPOINTERDOWN,
        NcPointerUp = WM_NCPOINTERUP,
        PointerUpdate = WM_POINTERUPDATE,
        PointerDown = WM_POINTERDOWN,
        PointerUp = WM_POINTERUP,
        PointerEnter = WM_POINTERENTER,
        PointerLeave = WM_POINTERLEAVE,
        PointerActivate = WM_POINTERACTIVATE,
        PointerCaptureChanged = WM_POINTERCAPTURECHANGED,
        TouchHitTesting = WM_TOUCHHITTESTING,
        PointerWheel = WM_POINTERWHEEL,
        PointerHWheel = WM_POINTERHWHEEL,
        PointerRoutedTo = WM_POINTERROUTEDTO,
        PointerRoutedAway = WM_POINTERROUTEDAWAY,
        PointerRoutedReleased = WM_POINTERROUTEDRELEASED,
        ImeSetContext = WM_IME_SETCONTEXT,
        ImeNotify = WM_IME_NOTIFY,
        ImeControl = WM_IME_CONTROL,
        ImeCompositionFull = WM_IME_COMPOSITIONFULL,
        ImeSelect = WM_IME_SELECT,
        ImeChar = WM_IME_CHAR,
        ImeRequest = WM_IME_REQUEST,
        ImeKeyDown = WM_IME_KEYDOWN,
        ImeKeyUp = WM_IME_KEYUP,
        MouseHover = WM_MOUSEHOVER,
        MouseLeave = WM_MOUSELEAVE,
        NcMouseHover = WM_NCMOUSEHOVER,
        NcMouseLeave = WM_NCMOUSELEAVE,
        WtsSessionChange = WM_WTSSESSION_CHANGE,
        TabletFirst = WM_TABLET_FIRST,
        TabletLast = WM_TABLET_LAST,
        DpiChanged = WM_DPICHANGED,
        DpiChangedBeforeParent = WM_DPICHANGED_BEFOREPARENT,
        DpiChangedAfterParent = WM_DPICHANGED_AFTERPARENT,
        GetDpiScaledSize = WM_GETDPISCALEDSIZE,
        Cut = WM_CUT,
        Copy = WM_COPY,
        Paste = WM_PASTE,
        Clear = WM_CLEAR,
        Undo = WM_UNDO,
        RenderFormat = WM_RENDERFORMAT,
        RenderAllFormats = WM_RENDERALLFORMATS,
        DestroyClipboard = WM_DESTROYCLIPBOARD,
        DrawClipboard = WM_DRAWCLIPBOARD,
        PaintClipboard = WM_PAINTCLIPBOARD,
        VScrollClipboard = WM_VSCROLLCLIPBOARD,
        SizeClipboard = WM_SIZECLIPBOARD,
        AskCbFormatName = WM_ASKCBFORMATNAME,
        ChangeCbChain = WM_CHANGECBCHAIN,
        HScrollClipboard = WM_HSCROLLCLIPBOARD,
        QueryNewPalette = WM_QUERYNEWPALETTE,
        PaletteIsChanging = WM_PALETTEISCHANGING,
        PaletteChanged = WM_PALETTECHANGED,
        Hotkey = WM_HOTKEY,
        Print = WM_PRINT,
        PrintClient = WM_PRINTCLIENT,
        AppCommand = WM_APPCOMMAND,
        ThemeChanged = WM_THEMECHANGED,
        ClipboardUpdate = WM_CLIPBOARDUPDATE,
        DwmCompositionChanged = WM_DWMCOMPOSITIONCHANGED,
        DwmNCRenderingChanged = WM_DWMNCRENDERINGCHANGED,
        DwmColorizationColorChanged = WM_DWMCOLORIZATIONCOLORCHANGED,
        DwmWindowMaximizedChange = WM_DWMWINDOWMAXIMIZEDCHANGE,
        DwmSendIconicThumbnail = WM_DWMSENDICONICTHUMBNAIL,
        DwmSendIconicLivePreviewBitmap = WM_DWMSENDICONICLIVEPREVIEWBITMAP,
        GetTitleBarInfoEx = WM_GETTITLEBARINFOEX,
        HandheldFirst = WM_HANDHELDFIRST,
        HandheldLast = WM_HANDHELDLAST,
        AfxFirst = WM_AFXFIRST,
        AfxLast = WM_AFXLAST,
        PenWinFirst = WM_PENWINFIRST,
        PenWinLast = WM_PENWINLAST,
        App = WM_APP,
        User = WM_USER,
        TooltipDismiss = WM_TOOLTIPDISMISS,
    };
#endif
#ifndef BEEPTYPE
#define BEEPTYPE

    enum class BeepType : uint32_t {
        Default = 0xFFFFFFFF,
        IconAsterisk = MB_ICONASTERISK,
        IconExclamation = MB_ICONEXCLAMATION,
        IconError = MB_ICONERROR,
        IconHand = MB_ICONHAND,
        IconInformation = MB_ICONINFORMATION,
        IconQuestion = MB_ICONQUESTION,
        IconStop = MB_ICONSTOP,
        IconWarning = MB_ICONWARNING,
        Ok = MB_OK,
    };

    inline BeepType operator|(BeepType a, BeepType b) {
        return static_cast<BeepType>(static_cast<uint32_t>(a) |
                                     static_cast<uint32_t>(b));
    }
#endif
#ifndef SENDTIMEOUTFLAG
#define SENDTIMEOUTFLAG

    enum class SendTimeoutFlag : uint32_t {
        Normal = SMTO_NORMAL,
        Block = SMTO_BLOCK,
        AbortIfHung = SMTO_ABORTIFHUNG,
        NoTimeoutIfNotHung = SMTO_NOTIMEOUTIFNOTHUNG,
        ErrorOnExit = SMTO_ERRORONEXIT,
    };

    inline SendTimeoutFlag operator|(SendTimeoutFlag a, SendTimeoutFlag b) {
        return static_cast<SendTimeoutFlag>(static_cast<uint32_t>(a) |
                                            static_cast<uint32_t>(b));
    }
#endif
#ifndef SENDTYPE
#define SENDTYPE

    enum class SendType : uint32_t {
        NoSend = ISMEX_NOSEND,
        Send = ISMEX_SEND,
        Notify = ISMEX_NOTIFY,
        Callback = ISMEX_CALLBACK,
        Replied = ISMEX_REPLIED,
    };

    inline SendType operator|(SendType a, SendType b) {
        return static_cast<SendType>(static_cast<uint32_t>(a) |
                                     static_cast<uint32_t>(b));
    }
#endif
#ifndef BROADCASTFLAG
#define BROADCASTFLAG

    enum class BroadcastFlag : uint32_t {
        Query = BSF_QUERY,
        IgnoreCurrentTask = BSF_IGNORECURRENTTASK,
        FlushDisk = BSF_FLUSHDISK,
        NoHang = BSF_NOHANG,
        Post = BSF_POSTMESSAGE,
        ForceIfHung = BSF_FORCEIFHUNG,
        NoTimeoutIfNotHung = BSF_NOTIMEOUTIFNOTHUNG,
        AllowSFW = BSF_ALLOWSFW,
        SendNotify = BSF_SENDNOTIFYMESSAGE,
        ReturnHDesk = BSF_RETURNHDESK,
        LUid = BSF_LUID,
    };

    inline BroadcastFlag operator|(BroadcastFlag a, BroadcastFlag b) {
        return static_cast<BroadcastFlag>(static_cast<uint32_t>(a) |
                                          static_cast<uint32_t>(b));
    }
#endif
#ifndef BROADCASTRESULT
#define BROADCASTRESULT

    enum class BroadcastResult : uint32_t {
        AllComponents = BSM_ALLCOMPONENTS,
        VXds = BSM_VXDS,
        NetDriver = BSM_NETDRIVER,
        InstallableDrivers = BSM_INSTALLABLEDRIVERS,
        Applications = BSM_APPLICATIONS,
        AllDesktops = BSM_ALLDESKTOPS,
        QueryDeny = BROADCAST_QUERY_DENY,
    };

    inline BroadcastResult operator|(BroadcastResult a, BroadcastResult b) {
        return static_cast<BroadcastResult>(static_cast<uint32_t>(a) |
                                            static_cast<uint32_t>(b));
    }
#endif
#ifndef FILTERACTION
#define FILTERACTION

    enum class FilterAction : uint32_t {
        Reset = MSGFLT_RESET,
        Allow = MSGFLT_ALLOW,
        Disallow = MSGFLT_DISALLOW,
    };
#endif
#ifndef MESSAGEBOXTYPE
#define MESSAGEBOXTYPE

    enum class MessageBoxType : uint32_t {
        // button
        Ok = MB_OK,
        OkCancel = MB_OKCANCEL,
        AbortRetryIgnore = MB_ABORTRETRYIGNORE,
        YesNoCancel = MB_YESNOCANCEL,
        YesNo = MB_YESNO,
        RetryCancel = MB_RETRYCANCEL,
        CancelTryContinue = MB_CANCELTRYCONTINUE,
        // icon
        IconHand = MB_ICONHAND,
        IconQuestion = MB_ICONQUESTION,
        IconExclamation = MB_ICONEXCLAMATION,
        IconAsterisk = MB_ICONASTERISK,
        UserIcon = MB_USERICON,
        IconWarning = MB_ICONWARNING,
        IconError = MB_ICONERROR,
        IconInformation = MB_ICONINFORMATION,
        IconStop = MB_ICONSTOP,
        // default button
        DefButton1 = MB_DEFBUTTON1,
        DefButton2 = MB_DEFBUTTON2,
        DefButton3 = MB_DEFBUTTON3,
        DefButton4 = MB_DEFBUTTON4,
        // modal
        AppModal = MB_APPLMODAL,
        SystemModal = MB_SYSTEMMODAL,
        TaskModal = MB_TASKMODAL,
        // misc
        Help = MB_HELP,
        NoFocus = MB_NOFOCUS,
        SetForeground = MB_SETFOREGROUND,
        DefaultDesktopOnly = MB_DEFAULT_DESKTOP_ONLY,
        TopMost = MB_TOPMOST,
        Right = MB_RIGHT,
        RtlReading = MB_RTLREADING,
        ServiceNotification = MB_SERVICE_NOTIFICATION,
        ServiceNotificationNt3x = MB_SERVICE_NOTIFICATION_NT3X,
        // mask
        TypeMask = MB_TYPEMASK,
        IconMask = MB_ICONMASK,
        DefMask = MB_DEFMASK,
        ModeMask = MB_MODEMASK,
        MiscMask = MB_MISCMASK
    };

    inline MessageBoxType operator|(MessageBoxType a, MessageBoxType b) {
        return static_cast<MessageBoxType>(static_cast<uint32_t>(a) |
                                           static_cast<uint32_t>(b));
    }
#endif
#ifndef MESSAGEBOXRESULT
#define MESSAGEBOXRESULT

    enum class MessageBoxResult : int32_t {
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
#ifndef QUEUETYPE
#define QUEUETYPE

    enum class QueueType : uint32_t {
        Key = QS_KEY,
        MouseMove = QS_MOUSEMOVE,
        MouseButton = QS_MOUSEBUTTON,
        Post = QS_POSTMESSAGE,
        Timer = QS_TIMER,
        Paint = QS_PAINT,
        Send = QS_SENDMESSAGE,
        HotKey = QS_HOTKEY,
        AllPost = QS_ALLPOSTMESSAGE,
        Rawinput = QS_RAWINPUT,
        Touch = QS_TOUCH,
        Pointer = QS_POINTER,
        Mouse = QS_MOUSE,
        Input = QS_INPUT,
        AllEvents = QS_ALLEVENTS,
        AllInput = QS_ALLINPUT,
    };

    inline QueueType operator|(QueueType a, QueueType b) {
        return static_cast<QueueType>(static_cast<uint32_t>(a) |
                                      static_cast<uint32_t>(b));
    }

#endif

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

        bool get(HWND window_handle,
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
