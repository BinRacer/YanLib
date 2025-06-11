/* clang-format off */
/*
 * @file window.h
 * @date 2025-04-28
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
#ifndef WINDOW_H
#define WINDOW_H
#include <Windows.h>
#include <vector>
#include <string>
#include "sync/rwlock.h"
#include "helper/convert.h"
namespace YanLib::ui::core {
#ifndef WINDOWSTYLE
#define WINDOWSTYLE

    enum class WindowStyle : uint32_t {
        Overlapped = WS_OVERLAPPED,
        Popup = WS_POPUP,
        Child = WS_CHILD,
        Minimize = WS_MINIMIZE,
        Visible = WS_VISIBLE,
        Disabled = WS_DISABLED,
        ClipSiblings = WS_CLIPSIBLINGS,
        ClipChildren = WS_CLIPCHILDREN,
        Maximize = WS_MAXIMIZE,
        Caption = WS_CAPTION,
        Border = WS_BORDER,
        DialogFrame = WS_DLGFRAME,
        VScroll = WS_VSCROLL,
        HScroll = WS_HSCROLL,
        SysMenu = WS_SYSMENU,
        ThickFrame = WS_THICKFRAME,
        Group = WS_GROUP,
        TabStop = WS_TABSTOP,
        MinimizeBox = WS_MINIMIZEBOX,
        MaximizeBox = WS_MAXIMIZEBOX,
        Tiled = WS_TILED,
        Iconic = WS_ICONIC,
        SizeBox = WS_SIZEBOX,
        TiledWindow = WS_TILEDWINDOW,
        OverlappedWindow = WS_OVERLAPPEDWINDOW,
        PopupWindow = WS_POPUPWINDOW,
        ChildWindow = WS_CHILDWINDOW,
    };

    inline WindowStyle operator|(WindowStyle a, WindowStyle b) {
        return static_cast<WindowStyle>(static_cast<uint32_t>(a) |
                                        static_cast<uint32_t>(b));
    }
#endif
#ifndef WINDOWEXTENDSTYLE
#define WINDOWEXTENDSTYLE

    enum class WindowExtendStyle : uint32_t {
        None = 0,
        DialogModalFrame = WS_EX_DLGMODALFRAME,
        NoParentNotify = WS_EX_NOPARENTNOTIFY,
        TopMost = WS_EX_TOPMOST,
        AcceptFiles = WS_EX_ACCEPTFILES,
        Transparent = WS_EX_TRANSPARENT,
        MdiChild = WS_EX_MDICHILD,
        ToolWindow = WS_EX_TOOLWINDOW,
        WindowEdge = WS_EX_WINDOWEDGE,
        ClientEdge = WS_EX_CLIENTEDGE,
        ContextHelp = WS_EX_CONTEXTHELP,
        Right = WS_EX_RIGHT,
        Left = WS_EX_LEFT,
        RtlReading = WS_EX_RTLREADING,
        LtrReading = WS_EX_LTRREADING,
        LeftScrollBar = WS_EX_LEFTSCROLLBAR,
        RightScrollBar = WS_EX_RIGHTSCROLLBAR,
        ControlParent = WS_EX_CONTROLPARENT,
        StaticEdge = WS_EX_STATICEDGE,
        AppWindow = WS_EX_APPWINDOW,
        OverlappedWindow = WS_EX_OVERLAPPEDWINDOW,
        PaletteWindow = WS_EX_PALETTEWINDOW,
        Layered = WS_EX_LAYERED,
        NoInheritLayout = WS_EX_NOINHERITLAYOUT,
        NoRedirectionBitmap = WS_EX_NOREDIRECTIONBITMAP,
        LayoutRtl = WS_EX_LAYOUTRTL,
        Composited = WS_EX_COMPOSITED,
        NoActivate = WS_EX_NOACTIVATE,
    };

    inline WindowExtendStyle operator|(WindowExtendStyle a,
                                       WindowExtendStyle b) {
        return static_cast<WindowExtendStyle>(static_cast<uint32_t>(a) |
                                              static_cast<uint32_t>(b));
    }
#endif
#ifndef SHOWTYPE
#define SHOWTYPE

    enum class ShowType : int32_t {
        Hide = SW_HIDE,
        ShowNormal = SW_SHOWNORMAL,
        Normal = SW_NORMAL,
        ShowMinimized = SW_SHOWMINIMIZED,
        ShowMaximized = SW_SHOWMAXIMIZED,
        Maximize = SW_MAXIMIZE,
        ShowNoActivate = SW_SHOWNOACTIVATE,
        Show = SW_SHOW,
        Minimize = SW_MINIMIZE,
        ShowMinNoActive = SW_SHOWMINNOACTIVE,
        ShowNa = SW_SHOWNA,
        Restore = SW_RESTORE,
        ShowDefault = SW_SHOWDEFAULT,
        ForceMinimize = SW_FORCEMINIMIZE,
        Max = SW_MAX,
    };
#endif
#ifndef UPDATELAYEREDFLAG
#define UPDATELAYEREDFLAG

    enum class UpdateLayeredFlag : uint32_t {
        None = 0,
        ColorKey = ULW_COLORKEY,
        Alpha = ULW_ALPHA,
        Opaque = ULW_OPAQUE,
        ExtendNoResize = ULW_EX_NORESIZE,
    };

    inline UpdateLayeredFlag operator|(UpdateLayeredFlag a,
                                       UpdateLayeredFlag b) {
        return static_cast<UpdateLayeredFlag>(static_cast<uint32_t>(a) |
                                              static_cast<uint32_t>(b));
    }
#endif
#ifndef ANIMATEFLAG
#define ANIMATEFLAG

    enum class AnimateFlag : uint32_t {
        HorPositive = AW_HOR_POSITIVE,
        HorNegative = AW_HOR_NEGATIVE,
        VerPositive = AW_VER_POSITIVE,
        VerNegative = AW_VER_NEGATIVE,
        Center = AW_CENTER,
        Hide = AW_HIDE,
        Activate = AW_ACTIVATE,
        Slide = AW_SLIDE,
        Blend = AW_BLEND,
    };

    inline AnimateFlag operator|(AnimateFlag a, AnimateFlag b) {
        return static_cast<AnimateFlag>(static_cast<uint32_t>(a) |
                                        static_cast<uint32_t>(b));
    }
#endif
#ifndef EXITCODE
#define EXITCODE

    enum class ExitCode : uint32_t {
        LogOff = EWX_LOGOFF,
        Shutdown = EWX_SHUTDOWN,
        Reboot = EWX_REBOOT,
        Force = EWX_FORCE,
        PowerOff = EWX_POWEROFF,
        ForceIfHung = EWX_FORCEIFHUNG,
        QuickResolve = EWX_QUICKRESOLVE,
        ReStartApps = EWX_RESTARTAPPS,
        HybridShutdown = EWX_HYBRID_SHUTDOWN,
        BootOptions = EWX_BOOTOPTIONS,
        ArSo = EWX_ARSO,
        CheckSafeForServer = EWX_CHECK_SAFE_FOR_SERVER,
        SystemInitiated = EWX_SYSTEM_INITIATED,
    };

    inline ExitCode operator|(ExitCode a, ExitCode b) {
        return static_cast<ExitCode>(static_cast<uint32_t>(a) |
                                     static_cast<uint32_t>(b));
    }

#endif
#ifndef REASONCODE
#define REASONCODE

    enum class ReasonCode : uint32_t {
        // Flags used by the various UIs.
        CommentRequired = SHTDN_REASON_FLAG_COMMENT_REQUIRED,
        DirtyProblemIdRequired = SHTDN_REASON_FLAG_DIRTY_PROBLEM_ID_REQUIRED,
        CleanUI = SHTDN_REASON_FLAG_CLEAN_UI,
        DirtyUI = SHTDN_REASON_FLAG_DIRTY_UI,
        MobileUIReserved = SHTDN_REASON_FLAG_MOBILE_UI_RESERVED,
        // Flags that end up in the event log code.
        UserDefined = SHTDN_REASON_FLAG_USER_DEFINED,
        Planned = SHTDN_REASON_FLAG_PLANNED,
        // Microsoft major reasons.
        MajorOther = SHTDN_REASON_MAJOR_OTHER,
        MajorNone = SHTDN_REASON_MAJOR_NONE,
        MajorHardware = SHTDN_REASON_MAJOR_HARDWARE,
        MajorOperatingSystem = SHTDN_REASON_MAJOR_OPERATINGSYSTEM,
        MajorSoftware = SHTDN_REASON_MAJOR_SOFTWARE,
        MajorApplication = SHTDN_REASON_MAJOR_APPLICATION,
        MajorSystem = SHTDN_REASON_MAJOR_SYSTEM,
        MajorPower = SHTDN_REASON_MAJOR_POWER,
        MajorLegacyApi = SHTDN_REASON_MAJOR_LEGACY_API,
        // Microsoft minor reasons.
        MinorOther = SHTDN_REASON_MINOR_OTHER,
        MinorNone = SHTDN_REASON_MINOR_NONE,
        MinorMaintenance = SHTDN_REASON_MINOR_MAINTENANCE,
        MinorInstallation = SHTDN_REASON_MINOR_INSTALLATION,
        MinorUpgrade = SHTDN_REASON_MINOR_UPGRADE,
        MinorReconfig = SHTDN_REASON_MINOR_RECONFIG,
        MinorHung = SHTDN_REASON_MINOR_HUNG,
        MinorUnstable = SHTDN_REASON_MINOR_UNSTABLE,
        MinorDisk = SHTDN_REASON_MINOR_DISK,
        MinorProcessor = SHTDN_REASON_MINOR_PROCESSOR,
        MinorNetworkCard = SHTDN_REASON_MINOR_NETWORKCARD,
        MinorPowerSupply = SHTDN_REASON_MINOR_POWER_SUPPLY,
        MinorCordUnplugged = SHTDN_REASON_MINOR_CORDUNPLUGGED,
        MinorEnvironment = SHTDN_REASON_MINOR_ENVIRONMENT,
        MinorHardwareDriver = SHTDN_REASON_MINOR_HARDWARE_DRIVER,
        MinorOtherDriver = SHTDN_REASON_MINOR_OTHERDRIVER,
        MinorBluescreen = SHTDN_REASON_MINOR_BLUESCREEN,
        MinorServicePack = SHTDN_REASON_MINOR_SERVICEPACK,
        MinorHotfix = SHTDN_REASON_MINOR_HOTFIX,
        MinorSecurityFix = SHTDN_REASON_MINOR_SECURITYFIX,
        MinorSecurity = SHTDN_REASON_MINOR_SECURITY,
        MinorNetworkConnectivity = SHTDN_REASON_MINOR_NETWORK_CONNECTIVITY,
        MinorWmi = SHTDN_REASON_MINOR_WMI,
        MinorServicePackUninstall = SHTDN_REASON_MINOR_SERVICEPACK_UNINSTALL,
        MinorHotfixUninstall = SHTDN_REASON_MINOR_HOTFIX_UNINSTALL,
        MinorSecurityFixUninstall = SHTDN_REASON_MINOR_SECURITYFIX_UNINSTALL,
        MinorMmc = SHTDN_REASON_MINOR_MMC,
        MinorSystemRestore = SHTDN_REASON_MINOR_SYSTEMRESTORE,
        MinorTermSrv = SHTDN_REASON_MINOR_TERMSRV,
        MinorDcPromotion = SHTDN_REASON_MINOR_DC_PROMOTION,
        MinorDcDemotion = SHTDN_REASON_MINOR_DC_DEMOTION,
        Unknown = SHTDN_REASON_UNKNOWN,
        LegacyApi = SHTDN_REASON_LEGACY_API,
        // This mask cuts out UI flags.
        ValidBitMask = SHTDN_REASON_VALID_BIT_MASK
    };

    inline ReasonCode operator|(ReasonCode a, ReasonCode b) {
        return static_cast<ReasonCode>(static_cast<uint32_t>(a) |
                                       static_cast<uint32_t>(b));
    }
#endif
#ifndef REDRAWFLAG
#define REDRAWFLAG

    enum class RedrawFlag : uint32_t {
        Invalidate = RDW_INVALIDATE,
        InternalPaint = RDW_INTERNALPAINT,
        Erase = RDW_ERASE,
        Validate = RDW_VALIDATE,
        NoInternalPaint = RDW_NOINTERNALPAINT,
        NoErase = RDW_NOERASE,
        NoChildren = RDW_NOCHILDREN,
        AllChildren = RDW_ALLCHILDREN,
        UpdateNow = RDW_UPDATENOW,
        EraseNow = RDW_ERASENOW,
        Frame = RDW_FRAME,
        NoFrame = RDW_NOFRAME,
    };

    inline RedrawFlag operator|(RedrawFlag a, RedrawFlag b) {
        return static_cast<RedrawFlag>(static_cast<uint32_t>(a) |
                                       static_cast<uint32_t>(b));
    }
#endif
#ifndef TILESTYLE
#define TILESTYLE

    enum class TileStyle : uint32_t {
        Vertical = MDITILE_VERTICAL,
        Horizontal = MDITILE_HORIZONTAL,
        SkipDisabled = MDITILE_SKIPDISABLED,
        ZOrder = MDITILE_ZORDER,
    };

    inline TileStyle operator|(TileStyle a, TileStyle b) {
        return static_cast<TileStyle>(static_cast<uint32_t>(a) |
                                      static_cast<uint32_t>(b));
    }
#endif
#ifndef SEARCHFLAG
#define SEARCHFLAG

    enum class SearchFlag : uint32_t {
        Parent = GA_PARENT,
        Root = GA_ROOT,
        RootOwner = GA_ROOTOWNER,
    };
#endif
#ifndef SEARCHFLAG4
#define SEARCHFLAG4

    enum class SearchFlag4 : uint32_t {
        All = CWP_ALL,
        SkipInVisible = CWP_SKIPINVISIBLE,
        SkipDisabled = CWP_SKIPDISABLED,
        SkipTransparent = CWP_SKIPTRANSPARENT,
    };

    inline SearchFlag4 operator|(SearchFlag4 a, SearchFlag4 b) {
        return static_cast<SearchFlag4>(static_cast<uint32_t>(a) |
                                        static_cast<uint32_t>(b));
    }
#endif
#ifndef SEARCHFLAG6
#define SEARCHFLAG6

    enum class SearchFlag7 : uint32_t {
        HwndFirst = GW_HWNDFIRST,
        HwndLast = GW_HWNDLAST,
        HwndNext = GW_HWNDNEXT,
        HwndPrev = GW_HWNDPREV,
        Owner = GW_OWNER,
        Child = GW_CHILD,
        EnabledPopup = GW_ENABLEDPOPUP,
    };
#endif
#ifndef LAYOUT
#define LAYOUT

    enum class Layout : uint32_t {
        Error = GDI_ERROR,
        RightToLeft = LAYOUT_RTL,
        BottomToTop = LAYOUT_BTT,
        VerticalBeforeHorizontal = LAYOUT_VBH,
        OrientationMask = LAYOUT_ORIENTATIONMASK,
        BitmapOrientationPreserved = LAYOUT_BITMAPORIENTATIONPRESERVED,
    };

    inline Layout operator|(Layout a, Layout b) {
        return static_cast<Layout>(static_cast<uint32_t>(a) |
                                   static_cast<uint32_t>(b));
    }
#endif
#ifndef POSFLAG
#define POSFLAG

    enum class PosFlag : uint32_t {
        NoSize = SWP_NOSIZE,
        NoMove = SWP_NOMOVE,
        NoZOrder = SWP_NOZORDER,
        NoRedraw = SWP_NOREDRAW,
        NoActivate = SWP_NOACTIVATE,
        FrameChanged = SWP_FRAMECHANGED,
        ShowWindow = SWP_SHOWWINDOW,
        HideWindow = SWP_HIDEWINDOW,
        NoCopyBits = SWP_NOCOPYBITS,
        NoOwnerZOrder = SWP_NOOWNERZORDER,
        NoSendChanging = SWP_NOSENDCHANGING,
        DrawFrame = SWP_DRAWFRAME,
        NoRepos = SWP_NOREPOSITION,
        DeferErase = SWP_DEFERERASE,
        AsyncWindowPos = SWP_ASYNCWINDOWPOS,
    };

    inline PosFlag operator|(PosFlag a, PosFlag b) {
        return static_cast<PosFlag>(static_cast<uint32_t>(a) |
                                    static_cast<uint32_t>(b));
    }
#endif
#ifndef TRACKPOPUPMENU
#define TRACKPOPUPMENU

    enum class TrackPopup : uint32_t {
        LeftButton = TPM_LEFTBUTTON,
        RightButton = TPM_RIGHTBUTTON,
        LeftAlign = TPM_LEFTALIGN,
        CenterAlign = TPM_CENTERALIGN,
        RightAlign = TPM_RIGHTALIGN,
        TopAlign = TPM_TOPALIGN,
        VCenterAlign = TPM_VCENTERALIGN,
        BottomAlign = TPM_BOTTOMALIGN,
        Horizontal = TPM_HORIZONTAL,
        Vertical = TPM_VERTICAL,
        NoNotify = TPM_NONOTIFY,
        ReturnCmd = TPM_RETURNCMD,
        Recurse = TPM_RECURSE,
        HorPosAnimation = TPM_HORPOSANIMATION,
        HorNegAnimation = TPM_HORNEGANIMATION,
        VerPosAnimation = TPM_VERPOSANIMATION,
        VerNegAnimation = TPM_VERNEGANIMATION,
        NoAnimation = TPM_NOANIMATION,
        LayoutRtl = TPM_LAYOUTRTL,
        WorkArea = TPM_WORKAREA,
    };

    inline TrackPopup operator|(TrackPopup a, TrackPopup b) {
        return static_cast<TrackPopup>(static_cast<uint32_t>(a) |
                                       static_cast<uint32_t>(b));
    }

#endif
#ifndef LAYEREDFLAG
#define LAYEREDFLAG

    enum class LayeredFlag : uint32_t {
        None = 0,
        ColorKey = LWA_COLORKEY,
        Alpha = LWA_ALPHA,
    };

    inline LayeredFlag operator|(LayeredFlag a, LayeredFlag b) {
        return static_cast<LayeredFlag>(static_cast<uint32_t>(a) |
                                        static_cast<uint32_t>(b));
    }
#endif
#ifndef AFFINITYFLAG
#define AFFINITYFLAG

    enum class AffinityFlag : uint32_t {
        None = WDA_NONE,
        Monitor = WDA_MONITOR,
        ExcludeFromCapture = WDA_EXCLUDEFROMCAPTURE,
    };
#endif
#ifndef FEEDBACKTYPE
#define FEEDBACKTYPE

    enum class FeedbackType : int32_t {
        TouchContactVisualization = FEEDBACK_TOUCH_CONTACTVISUALIZATION,
        PenBarrelVisualization = FEEDBACK_PEN_BARRELVISUALIZATION,
        PenTap = FEEDBACK_PEN_TAP,
        PenDoubleTap = FEEDBACK_PEN_DOUBLETAP,
        PenPressAndHold = FEEDBACK_PEN_PRESSANDHOLD,
        PenRightTap = FEEDBACK_PEN_RIGHTTAP,
        TouchTap = FEEDBACK_TOUCH_TAP,
        TouchDoubleTap = FEEDBACK_TOUCH_DOUBLETAP,
        TouchPressAndHold = FEEDBACK_TOUCH_PRESSANDHOLD,
        TouchRightTap = FEEDBACK_TOUCH_RIGHTTAP,
        GesturePressAndTap = FEEDBACK_GESTURE_PRESSANDTAP,
        Max = FEEDBACK_MAX,
    };
#endif
#ifndef WINDOWLONGOFFSET
#define WINDOWLONGOFFSET

    enum class WindowLongOffset : int32_t {
        WindowProc = -4,
        Hinstance = -6,
        HwndParent = -8,
        Style = -16,
        ExtendStyle = -20,
        UserData = -21,
        ID = -12,
        // dialog
        MsgResult = 0,
        DialogProc = 4,
        User = 8,
    };
#endif
#ifndef WINDOWWORDOFFSET
#define WINDOWWORDOFFSET

    enum class WindowWordOffset : int32_t {
        Hinstance = -6,
        HwndParent = -8,
        ID = -12,
    };
#endif
#ifndef HELPCOMMAND
#define HELPCOMMAND

    enum class HelpCommand : uint32_t {
        Context = HELP_CONTEXT,
        Quit = HELP_QUIT,
        Index = HELP_INDEX,
        Contents = HELP_CONTENTS,
        HelpOnHelp = HELP_HELPONHELP,
        SetIndex = HELP_SETINDEX,
        SetContents = HELP_SETCONTENTS,
        ContextPopup = HELP_CONTEXTPOPUP,
        ForceFile = HELP_FORCEFILE,
        Key = HELP_KEY,
        Command = HELP_COMMAND,
        PartialKey = HELP_PARTIALKEY,
        Multikey = HELP_MULTIKEY,
        SetWinPos = HELP_SETWINPOS,
        ContextMenu = HELP_CONTEXTMENU,
        Finder = HELP_FINDER,
        WmHelp = HELP_WM_HELP,
        SetPopupPos = HELP_SETPOPUP_POS,
        TCard = HELP_TCARD,
        TCardData = HELP_TCARD_DATA,
        TCardOtherCaller = HELP_TCARD_OTHER_CALLER,
    };

    inline HelpCommand operator|(HelpCommand a, HelpCommand b) {
        return static_cast<HelpCommand>(static_cast<uint32_t>(a) |
                                        static_cast<uint32_t>(b));
    }
#endif
#ifndef RESOURCEFLAG
#define RESOURCEFLAG

    enum class ResourceFlag : uint32_t {
        GdiObjects = GR_GDIOBJECTS,
        UserObjects = GR_USEROBJECTS,
        GdiObjectsPeak = GR_GDIOBJECTS_PEAK,
        UserObjectsPeak = GR_USEROBJECTS_PEAK,
    };
#endif
#ifndef METRICSCODE
#define METRICSCODE

    enum class MetricCode : int32_t {
        ScreenWidth = SM_CXSCREEN,
        ScreenHeight = SM_CYSCREEN,
        VScrollWidth = SM_CXVSCROLL,
        HScrollHeight = SM_CYHSCROLL,
        CaptionHeight = SM_CYCAPTION,
        BorderWidth = SM_CXBORDER,
        BorderHeight = SM_CYBORDER,
        DialogFrameWidth = SM_CXDLGFRAME,
        DialogFrameHeight = SM_CYDLGFRAME,
        VThumbHeight = SM_CYVTHUMB,
        HThumbWidth = SM_CXHTHUMB,
        IconWidth = SM_CXICON,
        IconHeight = SM_CYICON,
        CursorWidth = SM_CXCURSOR,
        CursorHeight = SM_CYCURSOR,
        MenuHeight = SM_CYMENU,
        FullScreenWidth = SM_CXFULLSCREEN,
        FullScreenHeight = SM_CYFULLSCREEN,
        KanjiWindowHeight = SM_CYKANJIWINDOW,
        MousePresent = SM_MOUSEPRESENT,
        VScrollHeight = SM_CYVSCROLL,
        HScrollWidth = SM_CXHSCROLL,
        Debug = SM_DEBUG,
        SwapButton = SM_SWAPBUTTON,
        Reserved1 = SM_RESERVED1,
        Reserved2 = SM_RESERVED2,
        Reserved3 = SM_RESERVED3,
        Reserved4 = SM_RESERVED4,
        MinWidth = SM_CXMIN,
        MinHeight = SM_CYMIN,
        SizeWidth = SM_CXSIZE,
        SizeHeight = SM_CYSIZE,
        FrameWidth = SM_CXFRAME,
        FrameHeight = SM_CYFRAME,
        MinTrackWidth = SM_CXMINTRACK,
        MinTrackHeight = SM_CYMINTRACK,
        DoubleClkWidth = SM_CXDOUBLECLK,
        DoubleClkHeight = SM_CYDOUBLECLK,
        IconSpacingWidth = SM_CXICONSPACING,
        IconSpacingHeight = SM_CYICONSPACING,
        MenuDropAlignment = SM_MENUDROPALIGNMENT,
        PenWindows = SM_PENWINDOWS,
        DoubleClicksEnabled = SM_DBCSENABLED,
        CMouseButtons = SM_CMOUSEBUTTONS,
        FixedFrameWidth = SM_CXFIXEDFRAME,
        FixedFrameHeight = SM_CYFIXEDFRAME,
        SizeFrameWidth = SM_CXSIZEFRAME,
        SizeFrameHeight = SM_CYSIZEFRAME,
        Secure = SM_SECURE,
        EdgeWidth = SM_CXEDGE,
        EdgeHeight = SM_CYEDGE,
        MinSpacingWidth = SM_CXMINSPACING,
        MinSpacingHeight = SM_CYMINSPACING,
        SmIconWidth = SM_CXSMICON,
        SmIconHeight = SM_CYSMICON,
        SmCaptionHeight = SM_CYSMCAPTION,
        SmSizeWidth = SM_CXSMSIZE,
        SmSizeHeight = SM_CYSMSIZE,
        MenuSizeWidth = SM_CXMENUSIZE,
        MenuSizeHeight = SM_CYMENUSIZE,
        Arrange = SM_ARRANGE,
        MinimizedWidth = SM_CXMINIMIZED,
        MinimizedHeight = SM_CYMINIMIZED,
        MaxTrackWidth = SM_CXMAXTRACK,
        MaxTrackHeight = SM_CYMAXTRACK,
        MaximizedWidth = SM_CXMAXIMIZED,
        MaximizedHeight = SM_CYMAXIMIZED,
        Network = SM_NETWORK,
        CleanBoot = SM_CLEANBOOT,
        DragWidth = SM_CXDRAG,
        DragHeight = SM_CYDRAG,
        ShowSounds = SM_SHOWSOUNDS,
        MenuCheckWidth = SM_CXMENUCHECK,
        MenuCheckHeight = SM_CYMENUCHECK,
        SlowMachine = SM_SLOWMACHINE,
        MiddleEastEnabled = SM_MIDEASTENABLED,
        MouseWheelPresent = SM_MOUSEWHEELPRESENT,
        XVirtualScreen = SM_XVIRTUALSCREEN,
        YVirtualScreen = SM_YVIRTUALSCREEN,
        VirtualScreenWidth = SM_CXVIRTUALSCREEN,
        VirtualScreenHeight = SM_CYVIRTUALSCREEN,
        CMonitors = SM_CMONITORS,
        SameDisplayFormat = SM_SAMEDISPLAYFORMAT,
        ImEnabled = SM_IMMENABLED,
        FocusBorderWidth = SM_CXFOCUSBORDER,
        FocusBorderHeight = SM_CYFOCUSBORDER,
        TabletPC = SM_TABLETPC,
        MediaCenter = SM_MEDIACENTER,
        Starter = SM_STARTER,
        ServerR2 = SM_SERVERR2,
        MouseHorizontalWheelPresent = SM_MOUSEHORIZONTALWHEELPRESENT,
        PaddedBorderWidth = SM_CXPADDEDBORDER,
        Digitizer = SM_DIGITIZER,
        MaximumTouches = SM_MAXIMUMTOUCHES,
        CMetrics = SM_CMETRICS,
        RemoteSession = SM_REMOTESESSION,
        ShuttingDown = SM_SHUTTINGDOWN,
        RemoteControl = SM_REMOTECONTROL,
        CaretBlinkingEnabled = SM_CARETBLINKINGENABLED,
        ConvertibleSlateMode = SM_CONVERTIBLESLATEMODE,
        SystemDocked = SM_SYSTEMDOCKED,
    };
#endif
#ifndef SYSTEMPARAMETER
#define SYSTEMPARAMETER

    enum class SystemParameter : uint32_t {
        GetBeep = SPI_GETBEEP,
        SetBeep = SPI_SETBEEP,
        GetMouse = SPI_GETMOUSE,
        SetMouse = SPI_SETMOUSE,
        GetBorder = SPI_GETBORDER,
        SetBorder = SPI_SETBORDER,
        GetKeyboardSpeed = SPI_GETKEYBOARDSPEED,
        SetKeyboardSpeed = SPI_SETKEYBOARDSPEED,
        LangDriver = SPI_LANGDRIVER,
        IconHorizontalSpacing = SPI_ICONHORIZONTALSPACING,
        GetScreenSaverTimeout = SPI_GETSCREENSAVETIMEOUT,
        SetScreenSaverTimeout = SPI_SETSCREENSAVETIMEOUT,
        GetScreenSaveActive = SPI_GETSCREENSAVEACTIVE,
        SetScreenSaveActive = SPI_SETSCREENSAVEACTIVE,
        GetGridGranularity = SPI_GETGRIDGRANULARITY,
        SetGridGranularity = SPI_SETGRIDGRANULARITY,
        SetDeskWallpaper = SPI_SETDESKWALLPAPER,
        SetDeskPattern = SPI_SETDESKPATTERN,
        GetKeyboardDelay = SPI_GETKEYBOARDDELAY,
        SetKeyboardDelay = SPI_SETKEYBOARDDELAY,
        IconVerticalSpacing = SPI_ICONVERTICALSPACING,
        GetIconTitleWrap = SPI_GETICONTITLEWRAP,
        SetIconTitleWrap = SPI_SETICONTITLEWRAP,
        GetMenuDropAlignment = SPI_GETMENUDROPALIGNMENT,
        SetMenuDropAlignment = SPI_SETMENUDROPALIGNMENT,
        SetDoubleClickWidth = SPI_SETDOUBLECLKWIDTH,
        SetDoubleClickHeight = SPI_SETDOUBLECLKHEIGHT,
        GetIconTitleLogFont = SPI_GETICONTITLELOGFONT,
        SetDoubleClickTime = SPI_SETDOUBLECLICKTIME,
        SetMouseButtonSwap = SPI_SETMOUSEBUTTONSWAP,
        SetIconTitleLogFont = SPI_SETICONTITLELOGFONT,
        GetFastTaskSwitch = SPI_GETFASTTASKSWITCH,
        SetFastTaskSwitch = SPI_SETFASTTASKSWITCH,
        SetDragFullWindows = SPI_SETDRAGFULLWINDOWS,
        GetDragFullWindows = SPI_GETDRAGFULLWINDOWS,
        GetNonClientMetrics = SPI_GETNONCLIENTMETRICS,
        SetNonClientMetrics = SPI_SETNONCLIENTMETRICS,
        GetMinimizedMetrics = SPI_GETMINIMIZEDMETRICS,
        SetMinimizedMetrics = SPI_SETMINIMIZEDMETRICS,
        GetIconMetrics = SPI_GETICONMETRICS,
        SetIconMetrics = SPI_SETICONMETRICS,
        SetWorkArea = SPI_SETWORKAREA,
        GetWorkArea = SPI_GETWORKAREA,
        SetPenWindows = SPI_SETPENWINDOWS,
        GetHighContrast = SPI_GETHIGHCONTRAST,
        SetHighContrast = SPI_SETHIGHCONTRAST,
        GetKeyboardPref = SPI_GETKEYBOARDPREF,
        SetKeyboardPref = SPI_SETKEYBOARDPREF,
        GetScreenReader = SPI_GETSCREENREADER,
        SetScreenReader = SPI_SETSCREENREADER,
        GetAnimation = SPI_GETANIMATION,
        SetAnimation = SPI_SETANIMATION,
        GetFontSmoothing = SPI_GETFONTSMOOTHING,
        SetFontSmoothing = SPI_SETFONTSMOOTHING,
        SetDragWidth = SPI_SETDRAGWIDTH,
        SetDragHeight = SPI_SETDRAGHEIGHT,
        SetHandheld = SPI_SETHANDHELD,
        GetLowPowerTimeout = SPI_GETLOWPOWERTIMEOUT,
        GetPowerOffTimeout = SPI_GETPOWEROFFTIMEOUT,
        SetLowPowerTimeout = SPI_SETLOWPOWERTIMEOUT,
        SetPowerOffTimeout = SPI_SETPOWEROFFTIMEOUT,
        GetLowPowerActive = SPI_GETLOWPOWERACTIVE,
        GetPowerOffActive = SPI_GETPOWEROFFACTIVE,
        SetLowPowerActive = SPI_SETLOWPOWERACTIVE,
        SetPowerOffActive = SPI_SETPOWEROFFACTIVE,
        SetCursors = SPI_SETCURSORS,
        SetIcons = SPI_SETICONS,
        GetDefaultInputLang = SPI_GETDEFAULTINPUTLANG,
        SetDefaultInputLang = SPI_SETDEFAULTINPUTLANG,
        SetLangToggle = SPI_SETLANGTOGGLE,
        GetWindowsExtension = SPI_GETWINDOWSEXTENSION,
        SetMouseTrails = SPI_SETMOUSETRAILS,
        GetMouseTrails = SPI_GETMOUSETRAILS,
        SetScreenSaverRunning = SPI_SETSCREENSAVERRUNNING,
        ScreenSaverRunning = SPI_SCREENSAVERRUNNING,
        GetFilterKeys = SPI_GETFILTERKEYS,
        SetFilterKeys = SPI_SETFILTERKEYS,
        GetToggleKeys = SPI_GETTOGGLEKEYS,
        SetToggleKeys = SPI_SETTOGGLEKEYS,
        GetMouseKeys = SPI_GETMOUSEKEYS,
        SetMouseKeys = SPI_SETMOUSEKEYS,
        GetShowSounds = SPI_GETSHOWSOUNDS,
        SetShowSounds = SPI_SETSHOWSOUNDS,
        GetStickyKeys = SPI_GETSTICKYKEYS,
        SetStickyKeys = SPI_SETSTICKYKEYS,
        GetAccessTimeout = SPI_GETACCESSTIMEOUT,
        SetAccessTimeout = SPI_SETACCESSTIMEOUT,
        GetSerialKeys = SPI_GETSERIALKEYS,
        SetSerialKeys = SPI_SETSERIALKEYS,
        GetSoundSentry = SPI_GETSOUNDSENTRY,
        SetSoundSentry = SPI_SETSOUNDSENTRY,
        GetSnapToDefButton = SPI_GETSNAPTODEFBUTTON,
        SetSnapToDefButton = SPI_SETSNAPTODEFBUTTON,
        GetMouseHoverWidth = SPI_GETMOUSEHOVERWIDTH,
        SetMouseHoverWidth = SPI_SETMOUSEHOVERWIDTH,
        GetMouseHoverHeight = SPI_GETMOUSEHOVERHEIGHT,
        SetMouseHoverHeight = SPI_SETMOUSEHOVERHEIGHT,
        GetMouseHoverTime = SPI_GETMOUSEHOVERTIME,
        SetMouseHoverTime = SPI_SETMOUSEHOVERTIME,
        GetWheelScrollLines = SPI_GETWHEELSCROLLLINES,
        SetWheelScrollLines = SPI_SETWHEELSCROLLLINES,
        GetMenuShowDelay = SPI_GETMENUSHOWDELAY,
        SetMenuShowDelay = SPI_SETMENUSHOWDELAY,
        GetWheelScrollChars = SPI_GETWHEELSCROLLCHARS,
        SetWheelScrollChars = SPI_SETWHEELSCROLLCHARS,
        GetShowImeUi = SPI_GETSHOWIMEUI,
        SetShowImeUi = SPI_SETSHOWIMEUI,
        GetMouseSpeed = SPI_GETMOUSESPEED,
        SetMouseSpeed = SPI_SETMOUSESPEED,
        GetScreenSaverRunning = SPI_GETSCREENSAVERRUNNING,
        GetDeskWallpaper = SPI_GETDESKWALLPAPER,
        GetAudioDescription = SPI_GETAUDIODESCRIPTION,
        SetAudioDescription = SPI_SETAUDIODESCRIPTION,
        GetScreenSaverSecure = SPI_GETSCREENSAVESECURE,
        SetScreenSaverSecure = SPI_SETSCREENSAVESECURE,
        GetHungAppTimeout = SPI_GETHUNGAPPTIMEOUT,
        SetHungAppTimeout = SPI_SETHUNGAPPTIMEOUT,
        GetWaitToKillTimeout = SPI_GETWAITTOKILLTIMEOUT,
        SetWaitToKillTimeout = SPI_SETWAITTOKILLTIMEOUT,
        GetWaitToKillServiceTimeout = SPI_GETWAITTOKILLSERVICETIMEOUT,
        SetWaitToKillServiceTimeout = SPI_SETWAITTOKILLSERVICETIMEOUT,
        GetMouseDockThreshold = SPI_GETMOUSEDOCKTHRESHOLD,
        SetMouseDockThreshold = SPI_SETMOUSEDOCKTHRESHOLD,
        GetPenDockThreshold = SPI_GETPENDOCKTHRESHOLD,
        SetPenDockThreshold = SPI_SETPENDOCKTHRESHOLD,
        GetWinArranging = SPI_GETWINARRANGING,
        SetWinArranging = SPI_SETWINARRANGING,
        GetMouseDragOutThreshold = SPI_GETMOUSEDRAGOUTTHRESHOLD,
        SetMouseDragOutThreshold = SPI_SETMOUSEDRAGOUTTHRESHOLD,
        GetPenDragOutThreshold = SPI_GETPENDRAGOUTTHRESHOLD,
        SetPenDragOutThreshold = SPI_SETPENDRAGOUTTHRESHOLD,
        GetMouseSideMoveThreshold = SPI_GETMOUSESIDEMOVETHRESHOLD,
        SetMouseSideMoveThreshold = SPI_SETMOUSESIDEMOVETHRESHOLD,
        GetPenSideMoveThreshold = SPI_GETPENSIDEMOVETHRESHOLD,
        SetPenSideMoveThreshold = SPI_SETPENSIDEMOVETHRESHOLD,
        GetDragFromMaximize = SPI_GETDRAGFROMMAXIMIZE,
        SetDragFromMaximize = SPI_SETDRAGFROMMAXIMIZE,
        GetSnapSizing = SPI_GETSNAPSIZING,
        SetSnapSizing = SPI_SETSNAPSIZING,
        GetDockMoving = SPI_GETDOCKMOVING,
        SetDockMoving = SPI_SETDOCKMOVING,
    };
#endif
#ifndef SYSTEMPARAMETERFLAG
#define SYSTEMPARAMETERFLAG

    enum class SystemParameterFlag : uint32_t {
        None = 0,
        UpdateIniFile = SPIF_UPDATEINIFILE,
        SendWinIniChange = SPIF_SENDWININICHANGE,
        SendChange = SPIF_SENDCHANGE,
    };

    inline SystemParameterFlag operator|(SystemParameterFlag a,
                                         SystemParameterFlag b) {
        return static_cast<SystemParameterFlag>(static_cast<uint32_t>(a) |
                                                static_cast<uint32_t>(b));
    }
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
#ifndef WAITFLAG
#define WAITFLAG

    enum class WaitFlag : uint32_t {
        None = 0,
        WaitAll = MWMO_WAITALL,
        AlertAble = MWMO_ALERTABLE,
        InputAvailable = MWMO_INPUTAVAILABLE,
    };

    inline WaitFlag operator|(WaitFlag a, WaitFlag b) {
        return static_cast<WaitFlag>(static_cast<uint32_t>(a) |
                                     static_cast<uint32_t>(b));
    }
#endif
#ifndef ROTATESTATE
#define ROTATESTATE

    enum class RotateState : int32_t {
        Enabled = AR_ENABLED,
        Disabled = AR_DISABLED,
        Suppressed = AR_SUPPRESSED,
        RemoteSession = AR_REMOTESESSION,
        MultiMon = AR_MULTIMON,
        NoSensor = AR_NOSENSOR,
        NotSupported = AR_NOT_SUPPORTED,
        Docked = AR_DOCKED,
        Laptop = AR_LAPTOP,
    };
#endif
    class window {
    private:
        std::vector<HWND> window_handles = {};
        std::vector<HWND> shutdown_handles = {};
        sync::rwlock window_rwlock = {};
        sync::rwlock shutdown_rwlock = {};
        uint32_t error_code = 0;

    public:
        window(const window &other) = delete;

        window(window &&other) = delete;

        window &operator=(const window &other) = delete;

        window &operator=(window &&other) = delete;

        window() = default;

        ~window();

        HWND create(const char *class_name,
                    const char *window_name,
                    HINSTANCE instance_handle,
                    void *param = nullptr,
                    HWND parent_window_handle = nullptr,
                    HMENU menu_handle = nullptr,
                    int32_t x = CW_USEDEFAULT,
                    int32_t y = CW_USEDEFAULT,
                    int32_t width = CW_USEDEFAULT,
                    int32_t height = CW_USEDEFAULT,
                    WindowStyle style = WindowStyle::OverlappedWindow,
                    WindowExtendStyle extend_style = WindowExtendStyle::None);

        HWND create(const wchar_t *class_name,
                    const wchar_t *window_name,
                    HINSTANCE instance_handle,
                    void *param = nullptr,
                    HWND parent_window_handle = nullptr,
                    HMENU menu_handle = nullptr,
                    int32_t x = CW_USEDEFAULT,
                    int32_t y = CW_USEDEFAULT,
                    int32_t width = CW_USEDEFAULT,
                    int32_t height = CW_USEDEFAULT,
                    WindowStyle style = WindowStyle::OverlappedWindow,
                    WindowExtendStyle extend_style = WindowExtendStyle::None);

        HWND create_mdi(const char *class_name,
                        const char *window_name,
                        HINSTANCE instance_handle,
                        LPARAM lparam,
                        HWND parent_window_handle,
                        int32_t x = CW_USEDEFAULT,
                        int32_t y = CW_USEDEFAULT,
                        int32_t width = CW_USEDEFAULT,
                        int32_t height = CW_USEDEFAULT,
                        WindowStyle style = WindowStyle::OverlappedWindow);

        HWND create_mdi(const wchar_t *class_name,
                        const wchar_t *window_name,
                        HINSTANCE instance_handle,
                        LPARAM lparam,
                        HWND parent_window_handle,
                        int32_t x = CW_USEDEFAULT,
                        int32_t y = CW_USEDEFAULT,
                        int32_t width = CW_USEDEFAULT,
                        int32_t height = CW_USEDEFAULT,
                        WindowStyle style = WindowStyle::OverlappedWindow);

        bool show(HWND window_handle, ShowType cmd_show = ShowType::ShowNormal);

        bool show_async(HWND window_handle,
                        ShowType cmd_show = ShowType::ShowNormal);

        bool update(HWND window_handle);

        bool update_layered(HWND window_handle,
                            HDC hdc_dst,
                            POINT *coordinate_dst,
                            SIZE *size,
                            HDC hdc_src,
                            POINT *coordinate_src,
                            COLORREF color_ref,
                            BLENDFUNCTION *blend_fn,
                            UpdateLayeredFlag flag = UpdateLayeredFlag::Alpha);

        bool lock_update(HWND window_handle);

        bool unlock_update();

        bool animate(HWND window_handle,
                     uint32_t milli_second = 200,
                     AnimateFlag flag = AnimateFlag::Hide | AnimateFlag::Blend);

        bool close(HWND window_handle);
#ifdef WINNT
        bool close(HWND window_handle, bool is_force);
#endif
        bool exit(ExitCode exit_code = ExitCode::Shutdown |
                          ExitCode::HybridShutdown | ExitCode::PowerOff,
                  ReasonCode reason_code = ReasonCode::MajorApplication |
                          ReasonCode::MinorMaintenance | ReasonCode::Planned);

        bool shutdown(ReasonCode reason_code = ReasonCode::MajorApplication |
                              ReasonCode::MinorMaintenance |
                              ReasonCode::Planned);

        bool reboot(ReasonCode reason_code = ReasonCode::MajorApplication |
                            ReasonCode::MinorMaintenance | ReasonCode::Planned);

        bool logoff(ReasonCode reason_code = ReasonCode::MajorApplication |
                            ReasonCode::MinorMaintenance | ReasonCode::Planned);

        bool hibernate(bool wakeup_events_disabled = false);

        bool create_shutdown_reason(
                HWND window_handle,
                const std::string &reason,
                helper::CodePage code_page = helper::curr_code_page());

        bool create_shutdown_reason(HWND window_handle,
                                    const std::wstring &reason);

        bool destroy_shutdown_reason(HWND window_handle);

        bool query_shutdown_reason(
                HWND window_handle,
                const std::string &reason,
                uint32_t *real_size,
                helper::CodePage code_page = helper::curr_code_page());

        bool query_shutdown_reason(HWND window_handle,
                                   std::wstring &reason,
                                   uint32_t *real_size);

        bool destroy(HWND window_handle);

        bool enable_input(HWND window_handle);

        bool disable_input(HWND window_handle);

        bool enumerate(WNDENUMPROC enum_func, LPARAM lparam = 0);

        bool enumerate_child(HWND parent_window_handle,
                             WNDENUMPROC enum_func,
                             LPARAM lparam = 0);

        bool enumerate(uint32_t tid, WNDENUMPROC fn, LPARAM lparam = 0);

        HWND find(const char *class_name, const char *window_name);

        HWND find(const wchar_t *class_name, const wchar_t *window_name);

        HWND find(HWND parent_window_handle,
                  const char *class_name,
                  const char *window_name);

        HWND find(HWND parent_window_handle,
                  const wchar_t *class_name,
                  const wchar_t *window_name);

        bool flash(HWND window_handle, bool invert = true);

        bool flash(FLASHWINFO *flash_info);

        bool move(HWND window_handle,
                  int32_t x,
                  int32_t y,
                  int32_t width,
                  int32_t height,
                  bool repaint = true);

        bool print(HWND window_handle, HDC dc_handle, bool client_only = false);

        bool redraw(HWND window_handle,
                    HRGN region_handle,
                    const RECT *rect,
                    RedrawFlag flag = RedrawFlag::Invalidate |
                            RedrawFlag::Erase | RedrawFlag::UpdateNow |
                            RedrawFlag::AllChildren);

        bool maximize(HWND window_handle);

        bool minimize(HWND window_handle);

        bool hide(HWND window_handle);

        bool restore(HWND window_handle);

        bool restore_minimize(HWND window_handle);

        uint16_t tile(HWND parent_window_handle,
                      const RECT *rect,
                      const std::vector<HWND> &child,
                      TileStyle style = TileStyle::Vertical |
                              TileStyle::SkipDisabled);

        HWND get_parent(HWND window_handle);

        HWND set_parent(HWND windows_handle, HWND parent_window_handle);

        HWND get_ancestor(HWND window_handle,
                          SearchFlag flag = SearchFlag::Root);

        bool show_popup(HWND window_handle);

        bool hide_popup(HWND window_handle);

        HWND get_last_active_popup(HWND window_handle);

        bool is_pending(HWND window_handle);

        bool is_window(HWND window_handle);

        bool is_arranged(HWND window_handle);

        bool is_enabled(HWND window_handle);

        bool is_unicode(HWND window_handle);

        bool is_visible(HWND window_handle);

        bool is_minimize(HWND window_handle);

        bool is_maximize(HWND window_handle);

        bool is_child(HWND window_handle, HWND child_window_handle);

        bool is_popup_exist();

        uint32_t arrange_minimize(HWND window_handle);

        bool get_proc_default_layout(Layout *layout);

        bool set_proc_default_layout(Layout layout);

        bool set_pos(HWND window_handle,
                     HWND insert_after_window_handle = nullptr,
                     int32_t x = CW_USEDEFAULT,
                     int32_t y = CW_USEDEFAULT,
                     int32_t width = CW_USEDEFAULT,
                     int32_t height = CW_USEDEFAULT,
                     PosFlag flag = PosFlag::NoZOrder | PosFlag::ShowWindow);

        bool calc_popup_pos(const POINT *anchor_coordinate,
                            const SIZE *window_size,
                            RECT *popup_pos,
                            RECT *exclude_rect = nullptr,
                            TrackPopup flag = TrackPopup::RightAlign |
                                    TrackPopup::BottomAlign |
                                    TrackPopup::ReturnCmd |
                                    TrackPopup::LeftButton);

        HWND find_top_child(HWND parent_window_handle, POINT coordinate);

        HWND find_top_child(HWND parent_window_handle,
                            POINT coordinate,
                            SearchFlag4 flag = SearchFlag4::All);

        HWND find_real_child(HWND parent_window_handle, POINT coordinate);

        HWND find_by_physical_point(POINT coordinate);

        HWND find_by_logical_point(POINT coordinate);

        int32_t transform_coordinate(HWND from_window_handle,
                                     HWND to_window_handle,
                                     std::vector<POINT> &coordinates);

        bool adjust_to_top(HWND window_handle);

        LRESULT call_proc(WNDPROC prev_wnd_func,
                          HWND window_handle,
                          uint32_t msg,
                          WPARAM wparam,
                          LPARAM lparam);

        LRESULT default_proc(HWND window_handle,
                             uint32_t msg,
                             WPARAM wparam,
                             LPARAM lparam);

        LRESULT default_mdi_proc(HWND window_handle,
                                 HWND client_mdi_window_handle,
                                 uint32_t msg,
                                 WPARAM wparam,
                                 LPARAM lparam);

        LRESULT default_mdi_child_proc(HWND window_handle,
                                       uint32_t msg,
                                       WPARAM wparam,
                                       LPARAM lparam);

        uint16_t cascade(HWND parent_window_handle,
                         uint32_t how,
                         const RECT *rect,
                         const std::vector<HWND> &child);

        void disable_proc_ghosting();

        HWND get_active();

        HWND set_active(HWND window_handle);

        uint32_t get_dpi(HWND window_handle);

        HWND get_foreground();

        bool set_foreground(HWND window_handle);

        bool allow_set_foreground(uint32_t pid);

        bool lock_set_foreground();

        bool unlock_set_foreground();

        bool get_layered_attrs(HWND window_handle,
                               COLORREF *color_ref,
                               uint8_t *alpha,
                               LayeredFlag *flag);

        bool set_layered_attrs(HWND window_handle,
                               COLORREF color_ref,
                               uint8_t alpha,
                               LayeredFlag flag);

        HWND find(HWND window_handle, SearchFlag7 flag = SearchFlag7::Child);

        HWND find_next(HWND window_handle);

        HWND find_prev(HWND window_handle);

        HWND find_first(HWND window_handle);

        HWND find_last(HWND window_handle);

        HWND find_owner(HWND window_handle);

        HWND find_shell();

        HWND find_top(HWND window_handle);

        uint32_t get_context_help_id(HWND window_handle);

        bool set_context_help_id(HWND window_handle, uint32_t param);

        bool get_display_affinity(HWND window_handle, AffinityFlag *affinity);

        bool set_display_affinity(HWND window_handle, AffinityFlag affinity);

        bool get_feedback_setting(HWND window_handle,
                                  FeedbackType feedback,
                                  bool *config,
                                  bool include_ancestor = false);

        bool set_feedback_setting(HWND window_handle,
                                  FeedbackType feedback,
                                  const void *config,
                                  uint32_t size);

        bool get_info(HWND window_handle, WINDOWINFO *window_info);

        // can fill offset with WindowLongOffset enum
        int32_t get_long(HWND window_handle, int32_t offset);

        // can fill offset with WindowLongOffset enum
        int32_t set_long(HWND window_handle, int32_t offset, int32_t value);

        // can fill offset with WindowLongOffset enum
        intptr_t get_long_ptr(HWND window_handle, int32_t offset);

        // can fill offset with WindowLongOffset enum
        intptr_t
        set_long_ptr(HWND window_handle, int32_t offset, intptr_t value);

        // can fill offset with WindowWordOffset enum
        uint16_t get_word(HWND window_handle, int32_t offset);

        uint32_t get_module_file_name(HWND window_handle,
                                      std::string &file_name);

        uint32_t get_module_file_name(HWND window_handle,
                                      std::wstring &file_name);

        bool get_placement(HWND window_handle,
                           WINDOWPLACEMENT *window_placement);

        bool set_placement(HWND window_handle,
                           const WINDOWPLACEMENT *window_placement);

        bool get_rect(HWND window_handle, RECT *rect);

        bool calc_rect(RECT *rect, WindowStyle style, bool include_menu = true);

        bool calc_rect(RECT *rect,
                       WindowStyle style,
                       WindowExtendStyle extend_style = WindowExtendStyle::None,
                       bool include_menu = true);

        bool calc_rect_for_dpi(
                RECT *rect,
                uint32_t dpi,
                WindowStyle style,
                WindowExtendStyle extend_style = WindowExtendStyle::None,
                bool include_menu = true);

        int32_t get_region(HWND window_handle, HRGN region_handle);

        int32_t
        set_region(HWND window_handle, HRGN region_handle, bool redraw = true);

        int32_t get_region_box(HWND window_handle, RECT *rect);

        int32_t get_text(HWND window_handle, std::string &text);

        int32_t get_text(HWND window_handle, std::wstring &text);

        bool set_text(HWND window_handle, const std::string &text);

        bool set_text(HWND window_handle, const std::wstring &text);

        int32_t get_text_length(HWND window_handle);

        uint32_t get_thread_id(HWND window_handle);

        uint32_t get_proc_id(HWND window_handle);

        // std::pair<tid, pid>
        std::pair<uint32_t, uint32_t>
        get_window_tid_and_pid(HWND window_handle);

        int32_t
        get_direct_text(HWND window_handle,
                        std::string &text,
                        helper::CodePage code_page = helper::curr_code_page());

        int32_t get_direct_text(HWND window_handle, std::wstring &text);

        uint32_t get_class_name(HWND window_handle, std::string &class_name);

        uint32_t get_class_name(HWND window_handle, std::wstring &class_name);

        void switch_window(HWND window_handle, bool UseAccelerator = false);

        bool show_help(HWND window_handle,
                       const char *help,
                       uintptr_t data,
                       HelpCommand cmd);

        bool show_help(HWND window_handle,
                       const wchar_t *help,
                       uintptr_t data,
                       HelpCommand cmd);

        uint32_t get_gui_resources(HANDLE proc_handle, ResourceFlag flag);

        bool get_gui_thread_info(uint32_t tid, GUITHREADINFO *gui_thread_info);

        bool convert_to_gui_thread();

        bool is_gui_thread();

        bool get_alt_tab_info(HWND window_handle,
                              int32_t icon_index,
                              ALTTABINFO *alt_tab_info,
                              std::string &item_text);

        bool get_alt_tab_info(HWND window_handle,
                              int32_t icon_index,
                              ALTTABINFO *alt_tab_info,
                              std::wstring &item_text);

        uintptr_t set_timer(HWND window_handle,
                            uintptr_t event_id,
                            TIMERPROC timer_func,
                            uint32_t timeout_ms = 1000);

        uintptr_t set_mixed_timer(
                HWND window_handle,
                uintptr_t event_id,
                TIMERPROC timer_func,
                uint32_t timeout_ms = 1000,
                uint32_t tolerance_delay_ms = TIMERV_DEFAULT_COALESCING);

        bool kill_timer(HWND window_handle, uintptr_t event_id);

        int32_t get_system_metrics(MetricCode code);

        int32_t get_system_metrics_for_dpi(MetricCode code, uint32_t dpi);

        bool system_params_info(SystemParameter action,
                                uint32_t key,
                                void *value,
                                SystemParameterFlag flag);

        bool system_paras_info_for_dpi(SystemParameter action,
                                       uint32_t key,
                                       void *value,
                                       uint32_t dpi,
                                       SystemParameterFlag flag);

        bool get_user_object_security(HANDLE obj_handle,
                                      PSECURITY_INFORMATION si,
                                      PSECURITY_DESCRIPTOR sd,
                                      uint32_t size,
                                      uint32_t *real_size);

        bool set_user_object_security(HANDLE obj_handle,
                                      PSECURITY_INFORMATION si,
                                      PSECURITY_DESCRIPTOR sd);

        uint32_t wait_for_multiple_objects(const std::vector<HANDLE> &handles,
                                           QueueType type,
                                           uint32_t milli_seconds,
                                           bool wait_all);

        uint32_t wait_for_multiple_objects(const std::vector<HANDLE> &handles,
                                           QueueType type,
                                           uint32_t milli_seconds,
                                           WaitFlag flag);

        bool sound_sentry();

        bool grant_access(HANDLE user_handle,
                          HANDLE job_handle,
                          bool is_grant = true);

        bool set_additional_foreground_boost_procs(
                HWND top_level_window_handle,
                std::vector<HANDLE> &proc_handles);

        bool get_title_bar_info(HWND window_handle,
                                TITLEBARINFO *title_bar_info);

        bool get_auto_rotation_state(RotateState *state);

        helper::CodePage get_code_page();

        bool get_combo_box_info(HWND combo_handle,
                                COMBOBOXINFO *combo_box_info);

        uint32_t get_list_box_info(HWND window_handle);

        bool enable_non_client_dpi_scaling(HWND window_handle);

        uint32_t get_dpi_for_system();

        uint32_t get_system_dpi(HANDLE proc_handle);

        int16_t get_app_command(LPARAM lparam);

        uint16_t get_device(LPARAM lparam);

        uint16_t get_flags(LPARAM lparam);

        int16_t get_nc_hit_test(WPARAM wparam);

        int16_t get_wheel_delta(WPARAM wparam);

        wchar_t *make_int_resource(uint16_t value);

        bool is_int_resource(uint16_t value);

        WPARAM make_wparam(int32_t low, int32_t high);

        LPARAM make_lparam(int32_t low, int32_t high);

        LRESULT make_lresult(int32_t low, int32_t high);

        uint16_t get_xbutton(WPARAM wparam);

        POINT points_to_point(POINTS points);

        POINTS point_to_points(POINT point);

        [[nodiscard]] uint32_t err_code() const;

        [[nodiscard]] std::string err_string() const;

        [[nodiscard]] std::wstring err_wstring() const;
    };
} // namespace YanLib::ui::core
#endif // WINDOW_H
