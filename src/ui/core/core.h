/* clang-format off */
/*
 * @file core.h
 * @date 2025-06-17
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
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
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
#ifndef CORE_H
#define CORE_H
#include <WinUser.h>
#include <imm.h>
#include <winnt.h>
#include <CommCtrl.h>
#include <wingdi.h>
#include <reason.h>
#include <cstdint>
#include <string>
namespace YanLib::ui::core {
    enum class DesktopAccess : uint32_t {
        Delete = DELETE,
        ReadControl = READ_CONTROL,
        WriteDac = WRITE_DAC,
        WriteOwner = WRITE_OWNER,
        Synchronize = SYNCHRONIZE,
        ReadObjects = DESKTOP_READOBJECTS,
        CreateWindows = DESKTOP_CREATEWINDOW,
        CreateMenu = DESKTOP_CREATEMENU,
        HookControl = DESKTOP_HOOKCONTROL,
        JournalRecord = DESKTOP_JOURNALRECORD,
        JournalPlayback = DESKTOP_JOURNALPLAYBACK,
        Enumerate = DESKTOP_ENUMERATE,
        WriteObjects = DESKTOP_WRITEOBJECTS,
        SwitchDesktop = DESKTOP_SWITCHDESKTOP,
        GenericRead = GENERIC_READ,
        GenericWrite = GENERIC_WRITE,
        GenericExecute = GENERIC_EXECUTE,
        GenericAll = GENERIC_ALL,
    };

    inline DesktopAccess operator|(DesktopAccess a, DesktopAccess b) {
        return static_cast<DesktopAccess>(static_cast<uint32_t>(a) |
                                          static_cast<uint32_t>(b));
    }

    enum class StationAccess : uint32_t {
        Delete = DELETE,
        ReadControl = READ_CONTROL,
        WriteDac = WRITE_DAC,
        WriteOwner = WRITE_OWNER,
        Synchronize = SYNCHRONIZE,
        All = WINSTA_ALL_ACCESS,
        EnumDesktop = WINSTA_ENUMDESKTOPS,
        ReadAttrs = WINSTA_READATTRIBUTES,
        AccessClipboard = WINSTA_ACCESSCLIPBOARD,
        CreateDesktops = WINSTA_CREATEDESKTOP,
        WriteAttrs = WINSTA_WRITEATTRIBUTES,
        AccessGlobalAtoms = WINSTA_ACCESSGLOBALATOMS,
        ExitWindows = WINSTA_EXITWINDOWS,
        Enumerate = WINSTA_ENUMERATE,
        ReadScreen = WINSTA_READSCREEN,
        GenericRead = GENERIC_READ,
        GenericWrite = GENERIC_WRITE,
        GenericExecute = GENERIC_EXECUTE,
        GenericAll = GENERIC_ALL,
    };

    inline StationAccess operator|(StationAccess a, StationAccess b) {
        return static_cast<StationAccess>(static_cast<uint32_t>(a) |
                                          static_cast<uint32_t>(b));
    }

    enum class ButtonState : uint32_t {
        Unchecked = BST_UNCHECKED,
        Checked = BST_CHECKED,
        Indeterminate = BST_INDETERMINATE,
        Pushed = BST_PUSHED,
        Focus = BST_FOCUS,
        DropDownPushed = BST_DROPDOWNPUSHED,
        Hot = BST_HOT,
    };

    enum class DialogFileType : uint32_t {
        ReadWrite = DDL_READWRITE,
        ReadOnly = DDL_READONLY,
        Hidden = DDL_HIDDEN,
        System = DDL_SYSTEM,
        Directory = DDL_DIRECTORY,
        Archive = DDL_ARCHIVE,
        PostMsgs = DDL_POSTMSGS,
        Drives = DDL_DRIVES,
        Exclusive = DDL_EXCLUSIVE,
    };

    inline DialogFileType operator|(DialogFileType a, DialogFileType b) {
        return static_cast<DialogFileType>(static_cast<uint32_t>(a) |
                                     static_cast<uint32_t>(b));
    }

    enum class ItemDpiBehavior : uint32_t {
        Default = DCDC_DEFAULT,
        DisableFontUpdate = DCDC_DISABLE_FONT_UPDATE,
        DisableReLayout = DCDC_DISABLE_RELAYOUT,
    };

    enum class DialogDpiBehavior : uint32_t {
        Default = DDC_DEFAULT,
        DisableAll = DDC_DISABLE_ALL,
        DisableResize = DDC_DISABLE_RESIZE,
        DisableItemReLayout = DDC_DISABLE_CONTROL_RELAYOUT,
    };

    enum class IconFlag : uint32_t {
        DefaultColor = LR_DEFAULTCOLOR,
        MonoChrome = LR_MONOCHROME,
        Color = LR_COLOR,
        CopyReturnOrg = LR_COPYRETURNORG,
        CopyDeleteOrg = LR_COPYDELETEORG,
        LoadFromFile = LR_LOADFROMFILE,
        LoadTransParent = LR_LOADTRANSPARENT,
        DefaultSize = LR_DEFAULTSIZE,
        VgaColor = LR_VGACOLOR,
        LoadMap3dColors = LR_LOADMAP3DCOLORS,
        CreateDibSection = LR_CREATEDIBSECTION,
        CopyFromResource = LR_COPYFROMRESOURCE,
        Shared = LR_SHARED,
    };

    inline IconFlag operator|(IconFlag a, IconFlag b) {
        return static_cast<IconFlag>(static_cast<uint32_t>(a) |
                                     static_cast<uint32_t>(b));
    }

    enum class DrawIconFlag : uint32_t {
        Mask = DI_MASK,
        Image = DI_IMAGE,
        Normal = DI_NORMAL,
        Compat = DI_COMPAT,
        DefaultSize = DI_DEFAULTSIZE,
        NoMirror = DI_NOMIRROR,
    };

    inline DrawIconFlag operator|(DrawIconFlag a, DrawIconFlag b) {
        return static_cast<DrawIconFlag>(static_cast<uint32_t>(a) |
                                         static_cast<uint32_t>(b));
    }

    enum class ImageFlag : uint32_t {
        DefaultColor = LR_DEFAULTCOLOR,
        MonoChrome = LR_MONOCHROME,
        Color = LR_COLOR,
        CopyReturnOrg = LR_COPYRETURNORG,
        CopyDeleteOrg = LR_COPYDELETEORG,
        LoadFromFile = LR_LOADFROMFILE,
        LoadTransParent = LR_LOADTRANSPARENT,
        DefaultSize = LR_DEFAULTSIZE,
        VgaColor = LR_VGACOLOR,
        LoadMap3dColors = LR_LOADMAP3DCOLORS,
        CreateDibSection = LR_CREATEDIBSECTION,
        CopyFromResource = LR_COPYFROMRESOURCE,
        Shared = LR_SHARED,
    };

    inline ImageFlag operator|(ImageFlag a, ImageFlag b) {
        return static_cast<ImageFlag>(static_cast<uint32_t>(a) |
                                      static_cast<uint32_t>(b));
    }

    enum class KeyboardLayout : uint32_t {
        Activate = KLF_ACTIVATE,
        SubstituteOk = KLF_SUBSTITUTE_OK,
        ReOrder = KLF_REORDER,
        ReplaceLang = KLF_REPLACELANG,
        NoTellShell = KLF_NOTELLSHELL,
        SetForProcess = KLF_SETFORPROCESS,
        ShiftLock = KLF_SHIFTLOCK,
        Reset = KLF_RESET,
    };

    inline KeyboardLayout operator|(KeyboardLayout a, KeyboardLayout b) {
        return static_cast<KeyboardLayout>(static_cast<uint32_t>(a) |
                                           static_cast<uint32_t>(b));
    }

    enum class KeyboardID : uint32_t {
        AR_SA = 0x00000401,
        BG_BG = 0x00000402,
        CA_ES = 0x00000403,
        ZH_TW = 0x00000404,
        CS_CZ = 0x00000405,
        DA_DK = 0x00000406,
        DE_DE = 0x00000407,
        EL_GR = 0x00000408,
        EN_US = 0x00000409,
        ES_ES_TRADNL = 0x0000040A,
        FI_FI = 0x0000040B,
        FR_FR = 0x0000040C,
        HE_IL = 0x0000040D,
        HU_HU = 0x0000040E,
        IS_IS = 0x0000040F,
        IT_IT = 0x00000410,
        JA_JP = 0x00000411,
        KO_KR = 0x00000412,
        NL_NL = 0x00000413,
        NB_NO = 0x00000414,
        PL_PL = 0x00000415,
        PT_BR = 0x00000416,
        RM_CH = 0x00000417,
        RO_RO = 0x00000418,
        RU_RU = 0x00000419,
        HR_HR = 0x0000041A,
        SK_SK = 0x0000041B,
        SQ_AL = 0x0000041C,
        SV_SE = 0x0000041D,
        TH_TH = 0x0000041E,
        TR_TR = 0x0000041F,
        UR_PK = 0x00000420,
        ID_ID = 0x00000421,
        UK_UA = 0x00000422,
        BE_BY = 0x00000423,
        SL_SI = 0x00000424,
        ET_EE = 0x00000425,
        LV_LV = 0x00000426,
        LT_LT = 0x00000427,
        TG_CYRL_TJ = 0x00000428,
        FA_IR = 0x00000429,
        VI_VN = 0x0000042A,
        HY_AM = 0x0000042B,
        AZ_LATN_AZ = 0x0000042C,
        EU_ES = 0x0000042D,
        HSB_DE = 0x0000042E,
        MK_MK = 0x0000042F,
        ST_ZA = 0x00000430,
        TS_ZA = 0x00000431,
        TN_ZA = 0x00000432,
        VE_ZA = 0x00000433,
        XH_ZA = 0x00000434,
        ZU_ZA = 0x00000435,
        AF_ZA = 0x00000436,
        KA_GE = 0x00000437,
        FO_FO = 0x00000438,
        HI_IN = 0x00000439,
        MT_MT = 0x0000043A,
        SE_NO = 0x0000043B,
        YI_001 = 0x0000043D,
        MS_MY = 0x0000043E,
        KK_KZ = 0x0000043F,
        KY_KG = 0x00000440,
        SW_KE = 0x00000441,
        TK_TM = 0x00000442,
        UZ_LATN_UZ = 0x00000443,
        TT_RU = 0x00000444,
        BN_IN = 0x00000445,
        PA_IN = 0x00000446,
        GU_IN = 0x00000447,
        OR_IN = 0x00000448,
        TA_IN = 0x00000449,
        TE_IN = 0x0000044A,
        KN_IN = 0x0000044B,
        ML_IN = 0x0000044C,
        AS_IN = 0x0000044D,
        MR_IN = 0x0000044E,
        SA_IN = 0x0000044F,
        MN_MN = 0x00000450,
        BO_CN = 0x00000451,
        CY_GB = 0x00000452,
        KM_KH = 0x00000453,
        LO_LA = 0x00000454,
        MY_MM = 0x00000455,
        GL_ES = 0x00000456,
        KOK_IN = 0x00000457,
        SYR_SY = 0x0000045A,
        SI_LK = 0x0000045B,
        CHR_CHER_US = 0x0000045C,
        IU_CANS_CA = 0x0000045D,
        AM_ET = 0x0000045E,
        TZM_ARAB_MA = 0x0000045F,
        KS_ARAB = 0x00000460,
        NE_NP = 0x00000461,
        FY_NL = 0x00000462,
        PS_AF = 0x00000463,
        FIL_PH = 0x00000464,
        DV_MV = 0x00000465,
        FF_NG = 0x00000467,
        HA_LATN_NG = 0x00000468,
        YO_NG = 0x0000046A,
        QUZ_BO = 0x0000046B,
        NSO_ZA = 0x0000046C,
        BA_RU = 0x0000046D,
        LB_LU = 0x0000046E,
        KL_GL = 0x0000046F,
        IG_NG = 0x00000470,
        OM_ET = 0x00000472,
        TI_ET = 0x00000473,
        GN_PY = 0x00000474,
        HAW_US = 0x00000475,
        SO_SO = 0x00000477,
        II_CN = 0x00000478,
        ARN_CL = 0x0000047A,
        MOH_CA = 0x0000047C,
        BR_FR = 0x0000047E,
        UG_CN = 0x00000480,
        MI_NZ = 0x00000481,
        OC_FR = 0x00000482,
        CO_FR = 0x00000483,
        GSW_FR = 0x00000484,
        SAH_RU = 0x00000485,
        RW_RW = 0x00000487,
        WO_SN = 0x00000488,
        PRS_AF = 0x0000048C,
        GD_GB = 0x00000491,
        KU_ARAB_IQ = 0x00000492,
        ZH_CN = 0x00000804,
        DE_DE_PHONE_BOOK = 0x00010407,
    };

    inline std::wstring KbdIDToWString(KeyboardID id) {
        wchar_t buffer[9] = {};
        swprintf_s(buffer, sizeof(buffer) / sizeof(wchar_t), L"%08X", id);
        return buffer;
    }

    enum class ModifiersKey : uint32_t {
        Alt = MOD_ALT,
        Control = MOD_CONTROL,
        Shift = MOD_SHIFT,
        Win = MOD_WIN,
        NoRepeat = MOD_NOREPEAT,
    };

    inline ModifiersKey operator|(ModifiersKey a, ModifiersKey b) {
        return static_cast<ModifiersKey>(static_cast<uint32_t>(a) |
                                         static_cast<uint32_t>(b));
    }

    enum class ModKey6 : uint32_t {
        None = 0,
        Shift = 1,
        Control = 2,
        Alt = 4,
        HanKaKu = 8,
        Reserve1 = 16,
        Reserve2 = 32,
    };

    inline ModKey6 operator|(ModKey6 a, ModKey6 b) {
        return static_cast<ModKey6>(static_cast<uint32_t>(a) |
                                    static_cast<uint32_t>(b));
    }

    enum class VirtualKey : uint32_t {
        LButton = 0x01,
        RButton = 0x02,
        Cancel = 0x03,
        MButton = 0x04,
        XButton1 = 0x05,
        XButton2 = 0x06,
        Back = 0x08,
        Tab = 0x09,
        Clear = 0x0C,
        Return = 0x0D,
        Shift = 0x10,
        Control = 0x11,
        Menu = 0x12,
        Pause = 0x13,
        Capital = 0x14,
        Kana = 0x15,
        Hangul = 0x15,
        ImeOn = 0x16,
        Junja = 0x17,
        Final = 0x18,
        Hanja = 0x19,
        Kanji = 0x19,
        ImeOff = 0x1A,
        Escape = 0x1B,
        Convert = 0x1C,
        NonConvert = 0x1D,
        Accept = 0x1E,
        ModeChange = 0x1F,
        Space = 0x20,
        Prior = 0x21,
        Next = 0x22,
        End = 0x23,
        Home = 0x24,
        Left = 0x25,
        Up = 0x26,
        Right = 0x27,
        Down = 0x28,
        Select = 0x29,
        Print = 0x2A,
        Execute = 0x2B,
        Snapshot = 0x2C,
        Insert = 0x2D,
        Delete = 0x2E,
        Help = 0x2F,
        Digit0 = 0x30,
        Digit1 = 0x31,
        Digit2 = 0x32,
        Digit3 = 0x33,
        Digit4 = 0x34,
        Digit5 = 0x35,
        Digit6 = 0x36,
        Digit7 = 0x37,
        Digit8 = 0x38,
        Digit9 = 0x39,
        A = 0x41,
        B = 0x42,
        C = 0x43,
        D = 0x44,
        E = 0x45,
        F = 0x46,
        G = 0x47,
        H = 0x48,
        I = 0x49,
        J = 0x4A,
        K = 0x4B,
        L = 0x4C,
        M = 0x4D,
        N = 0x4E,
        O = 0x4F,
        P = 0x50,
        Q = 0x51,
        R = 0x52,
        S = 0x53,
        T = 0x54,
        U = 0x55,
        V = 0x56,
        W = 0x57,
        X = 0x58,
        Y = 0x59,
        Z = 0x5A,
        LWin = 0x5B,
        RWin = 0x5C,
        Apps = 0x5D,
        Sleep = 0x5F,
        Numpad0 = 0x60,
        Numpad1 = 0x61,
        Numpad2 = 0x62,
        Numpad3 = 0x63,
        Numpad4 = 0x64,
        Numpad5 = 0x65,
        Numpad6 = 0x66,
        Numpad7 = 0x67,
        Numpad8 = 0x68,
        Numpad9 = 0x69,
        Multiply = 0x6A,
        Add = 0x6B,
        Separator = 0x6C,
        Subtract = 0x6D,
        Decimal = 0x6E,
        Divide = 0x6F,
        F1 = 0x70,
        F2 = 0x71,
        F3 = 0x72,
        F4 = 0x73,
        F5 = 0x74,
        F6 = 0x75,
        F7 = 0x76,
        F8 = 0x77,
        F9 = 0x78,
        F10 = 0x79,
        F11 = 0x7A,
        F12 = 0x7B,
        F13 = 0x7C,
        F14 = 0x7D,
        F15 = 0x7E,
        F16 = 0x7F,
        F17 = 0x80,
        F18 = 0x81,
        F19 = 0x82,
        F20 = 0x83,
        F21 = 0x84,
        F22 = 0x85,
        F23 = 0x86,
        F24 = 0x87,
        NumLock = 0x90,
        Scroll = 0x91,
        LShift = 0xA0,
        RShift = 0xA1,
        LControl = 0xA2,
        RControl = 0xA3,
        LMenu = 0xA4,
        RMenu = 0xA5,
        BrowserBack = 0xA6,
        BrowserForward = 0xA7,
        BrowserRefresh = 0xA8,
        BrowserStop = 0xA9,
        BrowserSearch = 0xAA,
        BrowserFavorites = 0xAB,
        BrowserHome = 0xAC,
        VolumeMute = 0xAD,
        VolumeDown = 0xAE,
        VolumeUp = 0xAF,
        MediaNextTrack = 0xB0,
        MediaPrevTrack = 0xB1,
        MediaStop = 0xB2,
        MediaPlayPause = 0xB3,
        LaunchMail = 0xB4,
        LaunchMediaSelect = 0xB5,
        LaunchApp1 = 0xB6,
        LaunchApp2 = 0xB7,
        Oem1 = 0xBA,
        OemPlus = 0xBB,
        OemComma = 0xBC,
        OemMinus = 0xBD,
        OemPeriod = 0xBE,
        Oem2 = 0xBF,
        Oem3 = 0xC0,
        Oem4 = 0xDB,
        Oem5 = 0xDC,
        Oem6 = 0xDD,
        Oem7 = 0xDE,
        Oem8 = 0xDF,
        Oem102 = 0xE2,
        ProcessKey = 0xE5,
        Packet = 0xE7,
        Attn = 0xF6,
        CrSel = 0xF7,
        ExSel = 0xF8,
        ErEof = 0xF9,
        Play = 0xFA,
        Zoom = 0xFB,
        Pa1 = 0xFD,
        OemClear = 0xFE,
    };

    inline VirtualKey operator|(VirtualKey a, VirtualKey b) {
        return static_cast<VirtualKey>(static_cast<uint32_t>(a) |
                                       static_cast<uint32_t>(b));
    }

    enum class KeyEvent : uint32_t {
        ExtendedKey = KEYEVENTF_EXTENDEDKEY,
        KeyUp = KEYEVENTF_KEYUP,
        KeyDown = 0,
        Unicode = KEYEVENTF_UNICODE,
        ScanCode = KEYEVENTF_SCANCODE,
    };

    inline KeyEvent operator|(KeyEvent a, KeyEvent b) {
        return static_cast<KeyEvent>(static_cast<uint32_t>(a) |
                                     static_cast<uint32_t>(b));
    }

    enum class MapType : uint32_t {
        VkToVsc = MAPVK_VK_TO_VSC,
        VscToVk = MAPVK_VSC_TO_VK,
        VkToChar = MAPVK_VK_TO_CHAR,
        VscToVkEx = MAPVK_VSC_TO_VK_EX,
        VkToVscEx = MAPVK_VK_TO_VSC_EX,
    };

    enum class MenuFlag : uint32_t {
        // MF_* flag
        Insert = MF_INSERT,
        Change = MF_CHANGE,
        Append = MF_APPEND,
        Delete = MF_DELETE,
        Remove = MF_REMOVE,
        ByCommand = MF_BYCOMMAND,
        ByPosition = MF_BYPOSITION,
        Separator = MF_SEPARATOR,
        Enabled = MF_ENABLED,
        Grayed = MF_GRAYED,
        Disabled = MF_DISABLED,
        Unchecked = MF_UNCHECKED,
        Checked = MF_CHECKED,
        UseCheckBitmaps = MF_USECHECKBITMAPS,
        String = MF_STRING,
        Bitmap = MF_BITMAP,
        OwnerDraw = MF_OWNERDRAW,
        Popup = MF_POPUP,
        MenuBarBreak = MF_MENUBARBREAK,
        MenuBreak = MF_MENUBREAK,
        UnHiLite = MF_UNHILITE,
        HiLite = MF_HILITE,
        Default = MF_DEFAULT,
        SysMenu = MF_SYSMENU,
        Help = MF_HELP,
        RightJustify = MF_RIGHTJUSTIFY,
        MouseSelect = MF_MOUSESELECT,
        End = MF_END,
        // MFT_* flag
        TString = MFT_STRING,
        TBitmap = MFT_BITMAP,
        TMenuBarBreak = MFT_MENUBARBREAK,
        TMenuBreak = MFT_MENUBREAK,
        TOwnerDraw = MFT_OWNERDRAW,
        TRadioCheck = MFT_RADIOCHECK,
        TSeparator = MFT_SEPARATOR,
        TRightOrder = MFT_RIGHTORDER,
        TRightJustify = MFT_RIGHTJUSTIFY,
        // MFS_* flag
        SGrayed = MFS_GRAYED,
        SDisabled = MFS_DISABLED,
        SChecked = MFS_CHECKED,
        SHiLite = MFS_HILITE,
        SEnabled = MFS_ENABLED,
        SUnchecked = MFS_UNCHECKED,
        SUnHiLite = MFS_UNHILITE,
        SDefault = MFS_DEFAULT,
    };

    inline MenuFlag operator|(MenuFlag a, MenuFlag b) {
        return static_cast<MenuFlag>(static_cast<uint32_t>(a) |
                                     static_cast<uint32_t>(b));
    }

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

    enum class MenuSearch : uint32_t {
        Default = 0,
        ShowDisabled = GMDI_USEDISABLED,
        Recursion = GMDI_GOINTOPOPUPS,
    };

    inline MenuSearch operator|(MenuSearch a, MenuSearch b) {
        return static_cast<MenuSearch>(static_cast<uint32_t>(a) |
                                       static_cast<uint32_t>(b));
    }

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

    enum class FilterAction : uint32_t {
        Reset = MSGFLT_RESET,
        Allow = MSGFLT_ALLOW,
        Disallow = MSGFLT_DISALLOW,
    };

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

    enum class MouseEvent : uint32_t {
        Move = MOUSEEVENTF_MOVE,
        LeftDown = MOUSEEVENTF_LEFTDOWN,
        LeftUp = MOUSEEVENTF_LEFTUP,
        RightDown = MOUSEEVENTF_RIGHTDOWN,
        RightUp = MOUSEEVENTF_RIGHTUP,
        MiddleDown = MOUSEEVENTF_MIDDLEDOWN,
        MiddleUp = MOUSEEVENTF_MIDDLEUP,
        XDown = MOUSEEVENTF_XDOWN,
        XUp = MOUSEEVENTF_XUP,
        Wheel = MOUSEEVENTF_WHEEL,
        MoveNoCoalesce = MOUSEEVENTF_MOVE_NOCOALESCE,
        VirtualDesk = MOUSEEVENTF_VIRTUALDESK,
        Absolute = MOUSEEVENTF_ABSOLUTE,
    };

    inline MouseEvent operator|(MouseEvent a, MouseEvent b) {
        return static_cast<MouseEvent>(static_cast<uint32_t>(a) |
                                       static_cast<uint32_t>(b));
    }
    enum class PointerInputType : uint32_t {
        Pointer = PT_POINTER,
        Touch = PT_TOUCH,
        Pen = PT_PEN,
        Mouse = PT_MOUSE,
        TouchPad = PT_TOUCHPAD,
    };

    enum class PointerFlag : uint32_t {
        None = POINTER_FLAG_NONE,
        New = POINTER_FLAG_NEW,
        InRange = POINTER_FLAG_INRANGE,
        InContact = POINTER_FLAG_INCONTACT,
        FirstButton = POINTER_FLAG_FIRSTBUTTON,
        SecondButton = POINTER_FLAG_SECONDBUTTON,
        ThirdButton = POINTER_FLAG_THIRDBUTTON,
        FourthButton = POINTER_FLAG_FOURTHBUTTON,
        FifthButton = POINTER_FLAG_FIFTHBUTTON,
        Primary = POINTER_FLAG_PRIMARY,
        Confidence = POINTER_FLAG_CONFIDENCE,
        Canceled = POINTER_FLAG_CANCELED,
        Down = POINTER_FLAG_DOWN,
        Update = POINTER_FLAG_UPDATE,
        Up = POINTER_FLAG_UP,
        Wheel = POINTER_FLAG_WHEEL,
        HWheel = POINTER_FLAG_HWHEEL,
        CaptureChanged = POINTER_FLAG_CAPTURECHANGED,
        HasTransform = POINTER_FLAG_HASTRANSFORM,
    };

    inline PointerFlag operator|(PointerFlag a, PointerFlag b) {
        return static_cast<PointerFlag>(static_cast<uint32_t>(a) |
                                        static_cast<uint32_t>(b));
    }

    enum class RegisterFlag : uint32_t {
        Default = 0,
        FineTouch = TWF_FINETOUCH,
        WantPalm = TWF_WANTPALM,
    };

    inline RegisterFlag operator|(RegisterFlag f1, RegisterFlag f2) {
        return static_cast<RegisterFlag>(static_cast<uint32_t>(f1) |
                                         static_cast<uint32_t>(f2));
    }

    enum class PointerFeedback {
        Default = POINTER_FEEDBACK_DEFAULT,
        Indirect = POINTER_FEEDBACK_INDIRECT,
        None = POINTER_FEEDBACK_NONE,
    };

    inline PointerFeedback operator|(PointerFeedback f1, PointerFeedback f2) {
        return static_cast<PointerFeedback>(static_cast<uint32_t>(f1) |
                                            static_cast<uint32_t>(f2));
    }

    enum class TouchHitTesting : uint32_t {
        Default = TOUCH_HIT_TESTING_DEFAULT,
        Client = TOUCH_HIT_TESTING_CLIENT,
        None = TOUCH_HIT_TESTING_NONE,
    };

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

    enum class SearchFlag : uint32_t {
        Parent = GA_PARENT,
        Root = GA_ROOT,
        RootOwner = GA_ROOTOWNER,
    };

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

    enum class SearchFlag7 : uint32_t {
        HwndFirst = GW_HWNDFIRST,
        HwndLast = GW_HWNDLAST,
        HwndNext = GW_HWNDNEXT,
        HwndPrev = GW_HWNDPREV,
        Owner = GW_OWNER,
        Child = GW_CHILD,
        EnabledPopup = GW_ENABLEDPOPUP,
    };

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

    enum class LayeredFlag : uint32_t {
        None = 0,
        ColorKey = LWA_COLORKEY,
        Alpha = LWA_ALPHA,
    };

    inline LayeredFlag operator|(LayeredFlag a, LayeredFlag b) {
        return static_cast<LayeredFlag>(static_cast<uint32_t>(a) |
                                        static_cast<uint32_t>(b));
    }

    enum class AffinityFlag : uint32_t {
        None = WDA_NONE,
        Monitor = WDA_MONITOR,
        ExcludeFromCapture = WDA_EXCLUDEFROMCAPTURE,
    };

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

    enum class WindowWordOffset : int32_t {
        Hinstance = -6,
        HwndParent = -8,
        ID = -12,
    };

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

    enum class ResourceFlag : uint32_t {
        GdiObjects = GR_GDIOBJECTS,
        UserObjects = GR_USEROBJECTS,
        GdiObjectsPeak = GR_GDIOBJECTS_PEAK,
        UserObjectsPeak = GR_USEROBJECTS_PEAK,
    };

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

    enum class ClassStyle : uint32_t {
        VRedraw = CS_VREDRAW,
        HRedraw = CS_HREDRAW,
        DoubleClicks = CS_DBLCLKS,
        OwnDC = CS_OWNDC,
        ClassDC = CS_CLASSDC,
        ParentDC = CS_PARENTDC,
        NoClose = CS_NOCLOSE,
        SaveBits = CS_SAVEBITS,
        ByteAlignClient = CS_BYTEALIGNCLIENT,
        ByteAlignWindow = CS_BYTEALIGNWINDOW,
        GlobalClass = CS_GLOBALCLASS,
        Ime = CS_IME,
        DropShadow = CS_DROPSHADOW,
    };

    inline ClassStyle operator|(ClassStyle a, ClassStyle b) {
        return static_cast<ClassStyle>(static_cast<uint32_t>(a) |
                                       static_cast<uint32_t>(b));
    }

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

    enum class HookCode : int32_t {
        Action = HC_ACTION,
        GetNext = HC_GETNEXT,
        Skip = HC_SKIP,
        NoRemove = HC_NOREMOVE,
        NoRem = HC_NOREM,
        SysModalOn = HC_SYSMODALON,
        SysModalOff = HC_SYSMODALOFF,
    };

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
} // namespace YanLib::ui::core
#endif // CORE_H
