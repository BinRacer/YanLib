/* clang-format off */
/*
 * @file rich_edit.h
 * @date 2025-05-30
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
#ifndef RICH_EDIT_H
#define RICH_EDIT_H
#ifndef UNICODE
#define UNICODE
#endif
#ifndef _UNICODE
#define _UNICODE
#endif
#include <Windows.h>
#include <CommCtrl.h>
#include <Richedit.h>
#include <Richole.h>
#include <tom.h>
#include <cstdint>
#include <string>
#include <vector>
#include "sync/rwlock.h"
#include "helper/convert.h"
#pragma comment(lib, "ComCtl32.Lib")
#pragma comment(linker, "\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#pragma comment(lib, "User32.Lib")
namespace YanLib::ui::components {
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
#ifndef RICHEDITSTYLE
#define RICHEDITSTYLE
    enum class RichEditStyle : uint32_t {
        Left = ES_LEFT,
        Center = ES_CENTER,
        Right = ES_RIGHT,
        Multiline = ES_MULTILINE,
        Uppercase = ES_UPPERCASE,
        Lowercase = ES_LOWERCASE,
        Password = ES_PASSWORD,
        AutoVScroll = ES_AUTOVSCROLL,
        AutoHScroll = ES_AUTOHSCROLL,
        NoHideSel = ES_NOHIDESEL,
        OemConvert = ES_OEMCONVERT,
        ReadOnly = ES_READONLY,
        WantReturn = ES_WANTRETURN,
        Number = ES_NUMBER,
        SaveSelect = ES_SAVESEL,
        Sunken = ES_SUNKEN,
        DisableNoScroll = ES_DISABLENOSCROLL,
        SelectionBar = ES_SELECTIONBAR,
        NoOleDragDrop = ES_NOOLEDRAGDROP,
        NoCallOleInit = ES_EX_NOCALLOLEINIT,
        Vertical = ES_VERTICAL,
        NoIme = ES_NOIME,
        SelfIme = ES_SELFIME,
    };
    inline RichEditStyle operator|(RichEditStyle a, RichEditStyle b) {
        return static_cast<RichEditStyle>(static_cast<uint32_t>(a) |
                                          static_cast<uint32_t>(b));
    }
#endif
#ifndef REAUTOURLDETECT
#define REAUTOURLDETECT
    enum class REAutoUrlDetect : uint32_t {
        DisableUrl = 0,
        EnableUrl = AURL_ENABLEURL,
        EnableEmailAddr = AURL_ENABLEEMAILADDR,
        EnableTelNo = AURL_ENABLETELNO,
        EnableEAUrls = AURL_ENABLEEAURLS,
        EnableDriveLetters = AURL_ENABLEDRIVELETTERS,
        DisableMixedLGC = AURL_DISABLEMIXEDLGC,
    };
#endif
#ifndef RESELECTTYPE
#define RESELECTTYPE
    enum class RESelectType : uint32_t {
        Empty = SEL_EMPTY,
        Text = SEL_TEXT,
        Object = SEL_OBJECT,
        MultiChar = SEL_MULTICHAR,
        MultiObject = SEL_MULTIOBJECT,
    };
    inline RESelectType operator|(RESelectType a, RESelectType b) {
        return static_cast<RESelectType>(static_cast<uint32_t>(a) |
                                         static_cast<uint32_t>(b));
    }
#endif
#ifndef REFINDSTYLE
#define REFINDSTYLE
    enum class REFindStyle : uint32_t {
        Down = FR_DOWN,
        WholeWord = FR_WHOLEWORD,
        MatchCase = FR_MATCHCASE,
        FindNext = FR_FINDNEXT,
        Replace = FR_REPLACE,
        ReplaceAll = FR_REPLACEALL,
        DialogTerm = FR_DIALOGTERM,
        ShowHelp = FR_SHOWHELP,
        EnableHook = FR_ENABLEHOOK,
        EnableTemplate = FR_ENABLETEMPLATE,
        NoUpDown = FR_NOUPDOWN,
        NoMatchCase = FR_NOMATCHCASE,
        NoWholeWord = FR_NOWHOLEWORD,
        EnableTemplateHandle = FR_ENABLETEMPLATEHANDLE,
        HideUpDown = FR_HIDEUPDOWN,
        HideMatchCase = FR_HIDEMATCHCASE,
        HideWholeWord = FR_HIDEWHOLEWORD,
        Raw = FR_RAW,
        ShowWrapAround = FR_SHOWWRAPAROUND,
        NoWrapAround = FR_NOWRAPAROUND,
        WrapAround = FR_WRAPAROUND,
        MatchDiac = FR_MATCHDIAC,
        MatchKashida = FR_MATCHKASHIDA,
        MatchAlefhamza = FR_MATCHALEFHAMZA,
    };
    inline REFindStyle operator|(REFindStyle a, REFindStyle b) {
        return static_cast<REFindStyle>(static_cast<uint32_t>(a) |
                                        static_cast<uint32_t>(b));
    }
#endif
#ifndef REWORDBREAKSTYLE
#define REWORDBREAKSTYLE
    enum class REWordBreakStyle : uint32_t {
        Classify = WB_CLASSIFY,
        MoveWordLeft = WB_MOVEWORDLEFT,
        MoveWordRight = WB_MOVEWORDRIGHT,
        LeftBreak = WB_LEFTBREAK,
        RightBreak = WB_RIGHTBREAK,
        MoveWordPrev = WB_MOVEWORDPREV,
        MoveWordNext = WB_MOVEWORDNEXT,
        PrevBreak = WB_PREVBREAK,
        NextBreak = WB_NEXTBREAK,
    };
    inline REWordBreakStyle operator|(REWordBreakStyle a, REWordBreakStyle b) {
        return static_cast<REWordBreakStyle>(static_cast<uint32_t>(a) |
                                             static_cast<uint32_t>(b));
    }
#endif
#ifndef RECHARFORMATSTYLE
#define RECHARFORMATSTYLE
    enum class RECharFormatStyle : uint32_t {
        Selection = SCF_SELECTION,
        Word = SCF_WORD,
        Default = SCF_DEFAULT,
        All = SCF_ALL,
        UseUIRules = SCF_USEUIRULES,
        AssociateFont = SCF_ASSOCIATEFONT,
        NoKeyboardUpdate = SCF_NOKBUPDATE,
        AssociateFont2 = SCF_ASSOCIATEFONT2,
        SmartFont = SCF_SMARTFONT,
        CharRepFromLcid = SCF_CHARREPFROMLCID,
        DontSetDefault = SPF_DONTSETDEFAULT,
        SetDefault = SPF_SETDEFAULT,
    };
    inline RECharFormatStyle operator|(RECharFormatStyle a,
                                       RECharFormatStyle b) {
        return static_cast<RECharFormatStyle>(static_cast<uint32_t>(a) |
                                              static_cast<uint32_t>(b));
    }
#endif
#ifndef RETEXTMODE
#define RETEXTMODE
    enum class RETextMode : uint32_t {
        PlainText = TM_PLAINTEXT,
        RichText = TM_RICHTEXT,
        SingleLevelUndo = TM_SINGLELEVELUNDO,
        MultiLevelUndo = TM_MULTILEVELUNDO,
        SingleCodePage = TM_SINGLECODEPAGE,
        MultiCodePage = TM_MULTICODEPAGE
    };
    inline RETextMode operator|(RETextMode a, RETextMode b) {
        return static_cast<RETextMode>(static_cast<uint32_t>(a) |
                                       static_cast<uint32_t>(b));
    }
#endif
#ifndef REOPTIONOP
#define REOPTIONOP
    enum class REOptionOP : uint32_t {
        Set = ECOOP_SET,
        Or = ECOOP_OR,
        And = ECOOP_AND,
        Xor = ECOOP_XOR,
    };
#endif
#ifndef REOPTION
#define REOPTION
    enum class REOption : uint32_t {
        AutoWordSelection = ECO_AUTOWORDSELECTION,
        AutoVScroll = ECO_AUTOVSCROLL,
        AutoHScroll = ECO_AUTOHSCROLL,
        NoHideSelect = ECO_NOHIDESEL,
        ReadOnly = ECO_READONLY,
        WantReturn = ECO_WANTRETURN,
        SaveSel = ECO_SAVESEL,
        SelectionBar = ECO_SELECTIONBAR,
        Vertical = ECO_VERTICAL,
    };
    inline REOption operator|(REOption a, REOption b) {
        return static_cast<REOption>(static_cast<uint32_t>(a) |
                                     static_cast<uint32_t>(b));
    }
#endif
#ifndef IMECOMPMODE
#define IMECOMPMODE
    enum class ImeCompMode : uint32_t {
        NotOpen = ICM_NOTOPEN,
        Level3 = ICM_LEVEL3,
        Level2 = ICM_LEVEL2,
        Level2_5 = ICM_LEVEL2_5,
        Level2Sui = ICM_LEVEL2_SUI,
        Ctf = ICM_CTF,
    };
#endif
#ifndef IMEPROPERTY
#define IMEPROPERTY
    enum class ImeProperty : uint32_t {
        AtCaret = IME_PROP_AT_CARET,
        SpecialUI = IME_PROP_SPECIAL_UI,
        CandListStartFrom1 = IME_PROP_CANDLIST_START_FROM_1,
        Unicode = IME_PROP_UNICODE,
        CompleteOnUnselect = IME_PROP_COMPLETE_ON_UNSELECT,
        AcceptWideVKey = 0x00000080,
    };
    inline ImeProperty operator|(ImeProperty a, ImeProperty b) {
        return static_cast<ImeProperty>(static_cast<uint32_t>(a) |
                                        static_cast<uint32_t>(b));
    }
#endif
#ifndef IMEVERSION
#define IMEVERSION
    enum class ImeVersion : uint32_t {
        Version0310 = IMEVER_0310,
        Version0400 = IMEVER_0400,
    };
#endif
#ifndef IMEUICAP
#define IMEUICAP
    enum class ImeUICap : uint32_t {
        Cap2700 = UI_CAP_2700,
        CapRot90 = UI_CAP_ROT90,
        CapRotAny = UI_CAP_ROTANY,
    };
    inline ImeUICap operator|(ImeUICap a, ImeUICap b) {
        return static_cast<ImeUICap>(static_cast<uint32_t>(a) |
                                     static_cast<uint32_t>(b));
    }
#endif
#ifndef IMECOMPSTRCAP
#define IMECOMPSTRCAP
    enum class ImeCompStrCap : uint32_t {
        CompStr = SCS_CAP_COMPSTR,
        MakeRead = SCS_CAP_MAKEREAD,
        SetReconvertString = SCS_CAP_SETRECONVERTSTRING,
    };
    inline ImeCompStrCap operator|(ImeCompStrCap a, ImeCompStrCap b) {
        return static_cast<ImeCompStrCap>(static_cast<uint32_t>(a) |
                                          static_cast<uint32_t>(b));
    }
#endif
#ifndef IMESELECTCAP
#define IMESELECTCAP
    enum class ImeSelectCap : uint32_t {
        Conversion = SELECT_CAP_CONVERSION,
        Sentence = SELECT_CAP_SENTENCE,
    };
    inline ImeSelectCap operator|(ImeSelectCap a, ImeSelectCap b) {
        return static_cast<ImeSelectCap>(static_cast<uint32_t>(a) |
                                         static_cast<uint32_t>(b));
    }
#endif
#ifndef IMECONVERSIONMODE
#define IMECONVERSIONMODE
    enum class ImeConversionMode : uint32_t {
        Alphanumeric = IME_CMODE_ALPHANUMERIC,
        Native = IME_CMODE_NATIVE,
        Chinese = IME_CMODE_CHINESE,
        Hangul = IME_CMODE_HANGUL,
        Japanese = IME_CMODE_JAPANESE,
        Katakana = IME_CMODE_KATAKANA,
        Language = IME_CMODE_LANGUAGE,
        FullShape = IME_CMODE_FULLSHAPE,
        Roman = IME_CMODE_ROMAN,
        CharCode = IME_CMODE_CHARCODE,
        HanjaConvert = IME_CMODE_HANJACONVERT,
        NativeSymbol = IME_CMODE_NATIVESYMBOL,
    };
    inline ImeConversionMode operator|(ImeConversionMode a,
                                       ImeConversionMode b) {
        return static_cast<ImeConversionMode>(static_cast<uint32_t>(a) |
                                              static_cast<uint32_t>(b));
    }
#endif
#ifndef IMESENTENCEMODE
#define IMESENTENCEMODE
    enum class ImeSentenceMode : uint32_t {
        None = IME_SMODE_NONE,
        Plauralclause = IME_SMODE_PLAURALCLAUSE,
        SingleConvert = IME_SMODE_SINGLECONVERT,
        Automatic = IME_SMODE_AUTOMATIC,
        PhrasePredict = IME_SMODE_PHRASEPREDICT,
        Conversation = IME_SMODE_CONVERSATION,
        Reserved = IME_SMODE_RESERVED,
    };
    inline ImeSentenceMode operator|(ImeSentenceMode a, ImeSentenceMode b) {
        return static_cast<ImeSentenceMode>(static_cast<uint32_t>(a) |
                                            static_cast<uint32_t>(b));
    }
#endif
#ifndef IMELANGOPTION
#define IMELANGOPTION

    enum class ImeLangOption : uint32_t {
        AutoKeyboard = IMF_AUTOKEYBOARD,
        AutoFont = IMF_AUTOFONT,
        ImeCancelComplete = IMF_IMECANCELCOMPLETE,
        ImeAlwaysSendNotify = IMF_IMEALWAYSSENDNOTIFY,
        AutoFontSizeAdjust = IMF_AUTOFONTSIZEADJUST,
        UIFonts = IMF_UIFONTS,
        NoImplicitLang = IMF_NOIMPLICITLANG,
        DualFont = IMF_DUALFONT,
        NokbdlidFixup = IMF_NOKBDLIDFIXUP,
        NoRRFFontSubstitute = IMF_NORTFFONTSUBSTITUTE,
        SpellChecking = IMF_SPELLCHECKING,
        TkbPrediction = IMF_TKBPREDICTION,
        ImeUIIntegration = IMF_IMEUIINTEGRATION,
    };
    inline ImeLangOption operator|(ImeLangOption a, ImeLangOption b) {
        return static_cast<ImeLangOption>(static_cast<uint32_t>(a) |
                                          static_cast<uint32_t>(b));
    }
#endif
#ifndef REMODEBIAS
#define REMODEBIAS
    enum class REModeBias : uint32_t {
        Default = CTFMODEBIAS_DEFAULT,
        Filename = CTFMODEBIAS_FILENAME,
        Name = CTFMODEBIAS_NAME,
        Reading = CTFMODEBIAS_READING,
        Datetime = CTFMODEBIAS_DATETIME,
        Conversation = CTFMODEBIAS_CONVERSATION,
        Numeric = CTFMODEBIAS_NUMERIC,
        Hiragana = CTFMODEBIAS_HIRAGANA,
        Katakana = CTFMODEBIAS_KATAKANA,
        Hangul = CTFMODEBIAS_HANGUL,
        HalfWidthKatakana = CTFMODEBIAS_HALFWIDTHKATAKANA,
        FullWidthAlphanumeric = CTFMODEBIAS_FULLWIDTHALPHANUMERIC,
        HalfWidthAlphanumeric = CTFMODEBIAS_HALFWIDTHALPHANUMERIC,
    };
    inline REModeBias operator|(REModeBias a, REModeBias b) {
        return static_cast<REModeBias>(static_cast<uint32_t>(a) |
                                       static_cast<uint32_t>(b));
    }
#endif
#ifndef RICHEDITEXTENDSTYLE
#define RICHEDITEXTENDSTYLE
    enum class RichEditExtendStyle : uint32_t {
        EmulateSysEdit = SES_EMULATESYSEDIT,
        BeepOnMaxText = SES_BEEPONMAXTEXT,
        ExtendBackColor = SES_EXTENDBACKCOLOR,
        MapCps = SES_MAPCPS,
        HyperLinkToolTips = SES_HYPERLINKTOOLTIPS,
        Emulate10 = SES_EMULATE10,
        DefaultLatinLiga = SES_DEFAULTLATINLIGA,
        UseCRLF = SES_USECRLF,
        NoFocusLinkNotify = SES_NOFOCUSLINKNOTIFY,
        UseAimm = SES_USEAIMM,
        NoIme = SES_NOIME,
        AllowBeeps = SES_ALLOWBEEPS,
        Uppercase = SES_UPPERCASE,
        Lowercase = SES_LOWERCASE,
        NoInputSequenceCheck = SES_NOINPUTSEQUENCECHK,
        BiDirection = SES_BIDI,
        ScrollOnKillFocus = SES_SCROLLONKILLFOCUS,
        XLTCRCRLFToCR = SES_XLTCRCRLFTOCR,
        DraftMode = SES_DRAFTMODE,
        UseCTF = SES_USECTF,
        HideGridLines = SES_HIDEGRIDLINES,
        UseAtFont = SES_USEATFONT,
        CustomLook = SES_CUSTOMLOOK,
        LBScrollNotify = SES_LBSCROLLNOTIFY,
        CTFAllowEmbed = SES_CTFALLOWEMBED,
        CTFAllowSmartTag = SES_CTFALLOWSMARTTAG,
        CTFAllowProofing = SES_CTFALLOWPROOFING,
        LogicalCaret = SES_LOGICALCARET,
        WordDragDrop = SES_WORDDRAGDROP,
        SmartDragDrop = SES_SMARTDRAGDROP,
        MultiSelect = SES_MULTISELECT,
        CTFNoLock = SES_CTFNOLOCK,
        NoEALineHeightAdjust = SES_NOEALINEHEIGHTADJUST,
        Max = SES_MAX,
    };
    inline RichEditExtendStyle operator|(RichEditExtendStyle a,
                                         RichEditExtendStyle b) {
        return static_cast<RichEditExtendStyle>(static_cast<uint32_t>(a) |
                                                static_cast<uint32_t>(b));
    }
#endif
#ifndef RICHEDITEXTENDSTYLE2
#define RICHEDITEXTENDSTYLE2
    enum class RichEditExtendStyle2 : uint32_t {
        NoTable = SES_EX_NOTABLE,
        NoMath = SES_EX_NOMATH,
        HandleFriendlyUrl = SES_EX_HANDLEFRIENDLYURL,
        NoTheming = SES_EX_NOTHEMING,
        NoAcetateSelection = SES_EX_NOACETATESELECTION,
        UseSingleLine = SES_EX_USESINGLELINE,
        MultiTouch = SES_EX_MULTITOUCH,
        HideTempFormat = SES_EX_HIDETEMPFORMAT,
        UseMouseWparam = SES_EX_USEMOUSEWPARAM,
    };
    inline RichEditExtendStyle2 operator|(RichEditExtendStyle2 a,
                                          RichEditExtendStyle2 b) {
        return static_cast<RichEditExtendStyle2>(static_cast<uint32_t>(a) |
                                                 static_cast<uint32_t>(b));
    }
#endif
#ifndef REELLIPSISMODE
#define REELLIPSISMODE
    enum class REEllipsisMode : uint32_t {
        Mask = ELLIPSIS_MASK,
        None = ELLIPSIS_NONE,
        End = ELLIPSIS_END,
        Word = ELLIPSIS_WORD,
    };
#endif
#ifndef REEVENTMASK
#define REEVENTMASK
    enum class REventMask : uint32_t {
        None = ENM_NONE,
        Change = ENM_CHANGE,
        Update = ENM_UPDATE,
        Scroll = ENM_SCROLL,
        ScrollEvents = ENM_SCROLLEVENTS,
        DragDropDone = ENM_DRAGDROPDONE,
        ParagraphExpanded = ENM_PARAGRAPHEXPANDED,
        PageChange = ENM_PAGECHANGE,
        ClipFormat = ENM_CLIPFORMAT,
        KeyEvents = ENM_KEYEVENTS,
        MouseEvents = ENM_MOUSEEVENTS,
        RequestResize = ENM_REQUESTRESIZE,
        SelectChange = ENM_SELCHANGE,
        DropFiles = ENM_DROPFILES,
        Protected = ENM_PROTECTED,
        CorrectText = ENM_CORRECTTEXT,
        ImeChange = ENM_IMECHANGE,
        LangChange = ENM_LANGCHANGE,
        ObjectPositions = ENM_OBJECTPOSITIONS,
        Link = ENM_LINK,
        LowFIRTF = ENM_LOWFIRTF,
        StartComposition = ENM_STARTCOMPOSITION,
        EndComposition = ENM_ENDCOMPOSITION,
        GroupTypingChange = ENM_GROUPTYPINGCHANGE,
        HideLinkTooltip = ENM_HIDELINKTOOLTIP,
    };
    inline REventMask operator|(REventMask a, REventMask b) {
        return static_cast<REventMask>(static_cast<uint32_t>(a) |
                                       static_cast<uint32_t>(b));
    }
#endif
#ifndef REREDOSTATE
#define REREDOSTATE
    enum class RERedoState : uint32_t {
        Unknown = UID_UNKNOWN,
        Typing = UID_TYPING,
        Delete = UID_DELETE,
        DragDrop = UID_DRAGDROP,
        Cut = UID_CUT,
        Paste = UID_PASTE,
        AutoTable = UID_AUTOTABLE,
    };
#endif
#ifndef REUNDOSTATE
#define REUNDOSTATE
    enum class REUndoState : uint32_t {
        Unknown = UID_UNKNOWN,
        Typing = UID_TYPING,
        Delete = UID_DELETE,
        DragDrop = UID_DRAGDROP,
        Cut = UID_CUT,
        Paste = UID_PASTE,
        AutoTable = UID_AUTOTABLE,
    };
#endif
#ifndef RESTORYTYPE
#define RESTORYTYPE
    typedef tomConstants REStoryType;
#endif
#ifndef REGETTEXTFLAG
#define REGETTEXTFLAG
    enum class REGetTextFlag : uint32_t {
        Default = GT_DEFAULT,
        UseCRLF = GT_USECRLF,
        Selection = GT_SELECTION,
        RawText = GT_RAWTEXT,
        NoHiddenText = GT_NOHIDDENTEXT,
    };
    inline REGetTextFlag operator|(REGetTextFlag a, REGetTextFlag b) {
        return static_cast<REGetTextFlag>(static_cast<uint32_t>(a) |
                                          static_cast<uint32_t>(b));
    }
#endif
#ifndef RESETTEXTFLAG
#define RESETTEXTFLAG
    enum class RESetTextFlag : uint32_t {
        Default = ST_DEFAULT,
        KeepUndo = ST_KEEPUNDO,
        Selection = ST_SELECTION,
        NewChars = ST_NEWCHARS,
        Unicode = ST_UNICODE,
        PlaceholderText = 0x10,
        PlainTextOnly = 0x20,
    };
    inline RESetTextFlag operator|(RESetTextFlag a, RESetTextFlag b) {
        return static_cast<RESetTextFlag>(static_cast<uint32_t>(a) |
                                          static_cast<uint32_t>(b));
    }
#endif
#ifndef REGETTEXTLENFLAG
#define REGETTEXTLENFLAG
    enum class REGetTextLenFlag : uint32_t {
        Default = GTL_DEFAULT,
        UseCRLF = GTL_USECRLF,
        Precise = GTL_PRECISE,
        Close = GTL_CLOSE,
        NumChars = GTL_NUMCHARS,
        NumBytes = GTL_NUMBYTES,
    };
    inline REGetTextLenFlag operator|(REGetTextLenFlag a, REGetTextLenFlag b) {
        return static_cast<REGetTextLenFlag>(static_cast<uint32_t>(a) |
                                             static_cast<uint32_t>(b));
    }
#endif
#ifndef RETOUCHOPTION
#define RETOUCHOPTION
    enum class RETouchOption : uint32_t {
        ShowHandles = RTO_SHOWHANDLES,
        DisableHandles = RTO_DISABLEHANDLES,
        ReadingMode = RTO_READINGMODE,
    };
#endif
#ifndef RETYPOGRAPHYOPTION
#define RETYPOGRAPHYOPTION
    enum class RETypographyOption : uint32_t {
        AdvancedTypography = TO_ADVANCEDTYPOGRAPHY,
        SimpleLineBreak = TO_SIMPLELINEBREAK,
        DisableCustomTextOut = TO_DISABLECUSTOMTEXTOUT,
        AdvancedLayout = TO_ADVANCEDLAYOUT,
    };
    inline RETypographyOption operator|(RETypographyOption a,
                                        RETypographyOption b) {
        return static_cast<RETypographyOption>(static_cast<uint32_t>(a) |
                                               static_cast<uint32_t>(b));
    }
#endif
#ifndef REPAGEROTATE
#define REPAGEROTATE
    enum class REPageRotate : uint32_t {
        Rotate0 = EPR_0,
        Rotate270 = EPR_270,
        Rotate180 = EPR_180,
        Rotate90 = EPR_90,
        RotateSE = EPR_SE,
    };
#endif
#ifndef RESTREAMFORMAT
#define RESTREAMFORMAT
    enum class REStreamFormat : uint32_t {
        Text = SF_TEXT,
        RTF = SF_RTF,
        RTFNoObjs = SF_RTFNOOBJS,
        Textized = SF_TEXTIZED,
        Unicode = SF_UNICODE,
        UseCodePage = SF_USECODEPAGE,
        NcRFOrNonAscii = SF_NCRFORNONASCII,
        RTFVal = SF_RTFVAL,
        Writextrapar = SFF_WRITEXTRAPAR,
        Selection = SFF_SELECTION,
        PlainRTF = SFF_PLAINRTF,
        PersistViewScale = SFF_PERSISTVIEWSCALE,
        KeepDocInfo = SFF_KEEPDOCINFO,
        Pwd = SFF_PWD,
    };
    inline REStreamFormat operator|(REStreamFormat a, REStreamFormat b) {
        return static_cast<REStreamFormat>(static_cast<uint32_t>(a) |
                                           static_cast<uint32_t>(b));
    }
#endif
#ifndef RICHEDITMESSAGE
#define RICHEDITMESSAGE
    enum class RichEditMessage : uint32_t {
        AutoUrlDetect = EM_AUTOURLDETECT,
        CallAutoCorrectProc = EM_CALLAUTOCORRECTPROC,
        CanPaste = EM_CANPASTE,
        CanRedo = EM_CANREDO,
        ConvPosition = EM_CONVPOSITION,
        DisplayBand = EM_DISPLAYBAND,
        ExGetSelect = EM_EXGETSEL,
        ExLimitText = EM_EXLIMITTEXT,
        ExLineFromChar = EM_EXLINEFROMCHAR,
        ExSetSelect = EM_EXSETSEL,
        FindTextA = EM_FINDTEXT,
        FindTextEx = EM_FINDTEXTEX,
        FindTextExW = EM_FINDTEXTEXW,
        FindTextW = EM_FINDTEXTW,
        FindWordBreak = EM_FINDWORDBREAK,
        FormatRange = EM_FORMATRANGE,
        GetAutoCorrectProc = EM_GETAUTOCORRECTPROC,
        GetAutoUrlDetect = EM_GETAUTOURLDETECT,
        GetBidiOptions = EM_GETBIDIOPTIONS,
        GetCharFormat = EM_GETCHARFORMAT,
        GetCtfModeBias = EM_GETCTFMODEBIAS,
        GetCtfOpenStatus = EM_GETCTFOPENSTATUS,
        GetEditStyle = EM_GETEDITSTYLE,
        GetEditStyleEx = EM_GETEDITSTYLEEX,
        GetEllipsisMode = EM_GETELLIPSISMODE,
        GetEllipsisState = EM_GETELLIPSISSTATE,
        GetEventMask = EM_GETEVENTMASK,
        GetHyphenateInfo = EM_GETHYPHENATEINFO,
        GetImeColor = EM_GETIMECOLOR,
        GetImeCompMode = EM_GETIMECOMPMODE,
        GetImeCompText = EM_GETIMECOMPTEXT,
        GetImeModeBias = EM_GETIMEMODEBIAS,
        GetImeOptions = EM_GETIMEOPTIONS,
        GetImeProperty = EM_GETIMEPROPERTY,
        GetLangOptions = EM_GETLANGOPTIONS,
        GetOleInterface = EM_GETOLEINTERFACE,
        GetOptions = EM_GETOPTIONS,
        GetPageRotate = EM_GETPAGEROTATE,
        GetParaFormat = EM_GETPARAFORMAT,
        GetPunctuation = EM_GETPUNCTUATION,
        GetRedoName = EM_GETREDONAME,
        GetScrollPos = EM_GETSCROLLPOS,
        GetSelectText = EM_GETSELTEXT,
        GetStoryType = EM_GETSTORYTYPE,
        GetTableParams = EM_GETTABLEPARMS,
        GetTextEx = EM_GETTEXTEX,
        GetTextLengthEx = EM_GETTEXTLENGTHEX,
        GetTextMode = EM_GETTEXTMODE,
        GetTextRange = EM_GETTEXTRANGE,
        GetTouchOptions = EM_GETTOUCHOPTIONS,
        GetTypographyOptions = EM_GETTYPOGRAPHYOPTIONS,
        GetUndoName = EM_GETUNDONAME,
        GetWordBreakProcEx = EM_GETWORDBREAKPROCEX,
        GetWordWrapMode = EM_GETWORDWRAPMODE,
        GetZoom = EM_GETZOOM,
        HideSelection = EM_HIDESELECTION,
        InsertImage = EM_INSERTIMAGE,
        InsertTable = EM_INSERTTABLE,
        IsIme = EM_ISIME,
        PasteSpecial = EM_PASTESPECIAL,
        ReConversion = EM_RECONVERSION,
        Redo = EM_REDO,
        RequestResize = EM_REQUESTRESIZE,
        SelectionType = EM_SELECTIONTYPE,
        SetAutoCorrectProc = EM_SETAUTOCORRECTPROC,
        SetBidiOptions = EM_SETBIDIOPTIONS,
        SetBackgroundColor = EM_SETBKGNDCOLOR,
        SetCharFormat = EM_SETCHARFORMAT,
        SetCtfModeBias = EM_SETCTFMODEBIAS,
        SetCtfOpenStatus = EM_SETCTFOPENSTATUS,
        SetEditStyle = EM_SETEDITSTYLE,
        SetEditStyleEx = EM_SETEDITSTYLEEX,
        SetEllipsisMode = EM_SETELLIPSISMODE,
        SetEventMask = EM_SETEVENTMASK,
        SetFontSize = EM_SETFONTSIZE,
        SetHyphenateInfo = EM_SETHYPHENATEINFO,
        SetImeColor = EM_SETIMECOLOR,
        SetImeModeBias = EM_SETIMEMODEBIAS,
        SetImeOptions = EM_SETIMEOPTIONS,
        SetLangOptions = EM_SETLANGOPTIONS,
        SetOleCallback = EM_SETOLECALLBACK,
        SetOptions = EM_SETOPTIONS,
        SetParaFormat = EM_SETPARAFORMAT,
        SetPageRotate = EM_SETPAGEROTATE,
        SetPalette = EM_SETPALETTE,
        SetPunctuation = EM_SETPUNCTUATION,
        SetScrollPos = EM_SETSCROLLPOS,
        SetStoryType = EM_SETSTORYTYPE,
        SetTableParams = EM_SETTABLEPARMS,
        SetTargetDevice = EM_SETTARGETDEVICE,
        SetTextEx = EM_SETTEXTEX,
        SetTextMode = EM_SETTEXTMODE,
        SetTouchOptions = EM_SETTOUCHOPTIONS,
        SetTypographyOptions = EM_SETTYPOGRAPHYOPTIONS,
        SetUiaName = EM_SETUIANAME,
        SetUndoLimit = EM_SETUNDOLIMIT,
        SetWordBreakProcEx = EM_SETWORDBREAKPROCEX,
        SetWordWrapMode = EM_SETWORDWRAPMODE,
        SetZoom = EM_SETZOOM,
        ShowScrollBar = EM_SHOWSCROLLBAR,
        StopGroupTyping = EM_STOPGROUPTYPING,
        StreamIn = EM_STREAMIN,
        StreamOut = EM_STREAMOUT
    };
#endif
#ifndef RICHEDITNOTIFY
#define RICHEDITNOTIFY
    enum class RichEditNotify : uint32_t {
        Change = EN_CHANGE,
        AlignLtr = EN_ALIGNLTR,
        AlignRtl = EN_ALIGNRTL,
        ClipFormat = EN_CLIPFORMAT,
        CorrectText = EN_CORRECTTEXT,
        DragDropDone = EN_DRAGDROPDONE,
        DropFiles = EN_DROPFILES,
        EndComposition = EN_ENDCOMPOSITION,
        ImeChange = EN_IMECHANGE,
        Link = EN_LINK,
        LowfiRTF = EN_LOWFIRTF,
        MsgFilter = EN_MSGFILTER,
        ObjectPositions = EN_OBJECTPOSITIONS,
        OleOpFailed = EN_OLEOPFAILED,
        ParagraphExpanded = EN_PARAGRAPHEXPANDED,
        Protected = EN_PROTECTED,
        RequestResize = EN_REQUESTRESIZE,
        SaveClipboard = EN_SAVECLIPBOARD,
        SelectChange = EN_SELCHANGE,
        StartComposition = EN_STARTCOMPOSITION,
        StopNoUndo = EN_STOPNOUNDO,
    };
#endif
    class rich_edit {
    private:
        HMODULE rich_edit_dll = nullptr;
        std::vector<HWND> rich_edit_handles = {};
        sync::rwlock rich_edit_rwlock = {};
        uint32_t error_code = 0;

    public:
        rich_edit(const rich_edit &other) = delete;

        rich_edit(rich_edit &&other) = delete;

        rich_edit &operator=(const rich_edit &other) = delete;

        rich_edit &operator=(rich_edit &&other) = delete;

        rich_edit();

        ~rich_edit();

        HWND create(uintptr_t rich_edit_id,
                    HWND parent_window_handle,
                    LPARAM lparam,
                    int32_t x,
                    int32_t y,
                    int32_t width,
                    int32_t height,
                    RichEditStyle style = RichEditStyle::Multiline |
                            RichEditStyle::AutoHScroll |
                            RichEditStyle::AutoVScroll | RichEditStyle::Left |
                            RichEditStyle::WantReturn,
                    WindowStyle window_style = WindowStyle::Child |
                            WindowStyle::Visible | WindowStyle::Border |
                            WindowStyle::TabStop);

        HWND create(const char *rich_edit_name,
                    uintptr_t rich_edit_id,
                    HWND parent_window_handle,
                    LPARAM lparam,
                    int32_t x,
                    int32_t y,
                    int32_t width,
                    int32_t height,
                    RichEditStyle style = RichEditStyle::Multiline |
                            RichEditStyle::AutoHScroll |
                            RichEditStyle::AutoVScroll | RichEditStyle::Left |
                            RichEditStyle::WantReturn,
                    WindowStyle window_style = WindowStyle::Child |
                            WindowStyle::Visible | WindowStyle::Border |
                            WindowStyle::TabStop);

        HWND create(const wchar_t *rich_edit_name,
                    uintptr_t rich_edit_id,
                    HWND parent_window_handle,
                    LPARAM lparam,
                    int32_t x,
                    int32_t y,
                    int32_t width,
                    int32_t height,
                    RichEditStyle style = RichEditStyle::Multiline |
                            RichEditStyle::AutoHScroll |
                            RichEditStyle::AutoVScroll | RichEditStyle::Left |
                            RichEditStyle::WantReturn,
                    WindowStyle window_style = WindowStyle::Child |
                            WindowStyle::Visible | WindowStyle::Border |
                            WindowStyle::TabStop);

        bool destroy(HWND rich_edit_handle);

        bool is_auto_url_detect_enabled(HWND rich_edit_handle);

        bool
        set_auto_url_detect(HWND rich_edit_handle,
                            REAutoUrlDetect state = REAutoUrlDetect::EnableUrl);

        AutoCorrectProc get_auto_correct_proc(HWND rich_edit_handle);

        bool set_auto_correct_proc(HWND rich_edit_handle, AutoCorrectProc func);

        bool call_auto_correct_proc(HWND rich_edit_handle, wchar_t ch);

        void get_select(HWND rich_edit_handle, CHARRANGE *range);

        void set_select(HWND rich_edit_handle, CHARRANGE *range);

        int64_t
        get_select_text(HWND rich_edit_handle,
                        std::string &text,
                        helper::CodePage code_page = helper::curr_code_page());

        int64_t get_select_text(HWND rich_edit_handle, std::wstring &text);

        void show_select(HWND rich_edit_handle);

        void hide_select(HWND rich_edit_handle);

        RESelectType get_select_type(HWND rich_edit_handle);

        int64_t find_text(HWND rich_edit_handle,
                          FINDTEXTA *text,
                          REFindStyle style = REFindStyle::Down |
                                  REFindStyle::FindNext);

        int64_t find_text2(HWND rich_edit_handle,
                           FINDTEXTEXA *text,
                           REFindStyle style = REFindStyle::Down |
                                   REFindStyle::FindNext);

        int64_t find_text(HWND rich_edit_handle,
                          FINDTEXTW *text,
                          REFindStyle style = REFindStyle::Down |
                                  REFindStyle::FindNext);

        int64_t find_text2(HWND rich_edit_handle,
                           FINDTEXTEXW *text,
                           REFindStyle style = REFindStyle::Down |
                                   REFindStyle::FindNext);

        int64_t find_word_break(HWND rich_edit_handle,
                                int64_t index,
                                REWordBreakStyle style);

        int64_t format_range(HWND rich_edit_handle,
                             FORMATRANGE *range,
                             bool render = true);

        bool display_band(HWND rich_edit_handle, RECT *rect);

        void
        get_char_format(HWND rich_edit_handle,
                        CHARFORMATW *format,
                        RECharFormatStyle style = RECharFormatStyle::Selection);

        void
        get_char_format(HWND rich_edit_handle,
                        CHARFORMAT2W *format,
                        RECharFormatStyle style = RECharFormatStyle::Selection);

        bool
        set_char_format(HWND rich_edit_handle,
                        CHARFORMATW *format,
                        RECharFormatStyle style = RECharFormatStyle::Selection);

        bool
        set_char_format(HWND rich_edit_handle,
                        CHARFORMAT2W *format,
                        RECharFormatStyle style = RECharFormatStyle::Selection);

        void get_para_format(HWND rich_edit_handle, PARAFORMAT *format);

        void get_para_format(HWND rich_edit_handle, PARAFORMAT2 *format);

        bool set_para_format(HWND rich_edit_handle, PARAFORMAT *format);

        bool set_para_format(HWND rich_edit_handle, PARAFORMAT2 *format);

        RETextMode get_text_mode(HWND rich_edit_handle);

        bool set_text_mode(HWND rich_edit_handle, RETextMode mode);

        REOption get_option(HWND rich_edit_handle);

        REOption
        set_option(HWND rich_edit_handle, REOptionOP op, REOption option);

        ImeCompMode get_ime_comp_mode(HWND rich_edit_handle);

        int64_t get_ime_comp_text(
                HWND rich_edit_handle,
                std::string &buf,
                helper::CodePage code_page = helper::curr_code_page());

        int64_t get_ime_comp_text(HWND rich_edit_handle, std::wstring &buf);

        bool has_ime_mode_bias(HWND rich_edit_handle);

        void set_ime_mode_bias(HWND rich_edit_handle);

        void unset_ime_mode_bias(HWND rich_edit_handle);

        ImeProperty get_ime_property(HWND rich_edit_handle);

        ImeVersion get_ime_version(HWND rich_edit_handle);

        ImeUICap get_ime_ui(HWND rich_edit_handle);

        ImeCompStrCap get_ime_comp_str(HWND rich_edit_handle);

        ImeSelectCap get_ime_select(HWND rich_edit_handle);

        ImeConversionMode get_ime_conversion_mode(HWND rich_edit_handle);

        ImeSentenceMode get_ime_sentence_mode(HWND rich_edit_handle);

        bool is_ime(HWND rich_edit_handle);

        ImeLangOption get_ime_lang_option(HWND rich_edit_handle);

        void set_ime_lang_option(HWND rich_edit_handle, ImeLangOption option);

        REModeBias get_mode_bias(HWND rich_edit_handle);

        void set_mode_bias(HWND rich_edit_handle, REModeBias mode);

        bool is_tsf_keyboard_open(HWND rich_edit_handle);

        bool open_tsf_keyboard(HWND rich_edit_handle);

        bool close_tsf_keyboard(HWND rich_edit_handle);

        RichEditExtendStyle get_rich_edit_extend_style(HWND rich_edit_handle);

        RichEditExtendStyle2 get_rich_edit_extend_style2(HWND rich_edit_handle);

        void set_rich_edit_extend_style(HWND rich_edit_handle,
                                        RichEditExtendStyle style,
                                        RichEditExtendStyle mask);

        void set_rich_edit_extend_style2(HWND rich_edit_handle,
                                         RichEditExtendStyle style,
                                         RichEditExtendStyle mask);

        bool get_ellipsis_mode(HWND rich_edit_handle, REEllipsisMode mode);

        bool set_ellipsis_mode(HWND rich_edit_handle, REEllipsisMode mode);

        bool is_ellipsis_display(HWND rich_edit_handle);

        REventMask get_event_mask(HWND rich_edit_handle);

        REventMask set_event_mask(HWND rich_edit_handle, REventMask mask);

        void get_hyphenate_info(HWND rich_edit_handle, HYPHENATEINFO *info);

        void set_hyphenate_info(HWND rich_edit_handle, HYPHENATEINFO *info);

        void get_bidirection_options(HWND rich_edit_handle,
                                     BIDIOPTIONS *option);

        void set_bidirection_options(HWND rich_edit_handle,
                                     BIDIOPTIONS *option);

        void get_scroll_pos(HWND rich_edit_handle, POINT *point);

        void set_scroll_pos(HWND rich_edit_handle, POINT *point);

        void show_vert_scroll_bar(HWND rich_edit_handle);

        void hide_vert_scroll_bar(HWND rich_edit_handle);

        void show_horiz_scroll_bar(HWND rich_edit_handle);

        void hide_horiz_scroll_bar(HWND rich_edit_handle);

        void show_both_scroll_bar(HWND rich_edit_handle);

        void hide_both_scroll_bar(HWND rich_edit_handle);

        bool
        get_zoom(HWND rich_edit_handle, int32_t numerator, int32_t denominator);

        bool
        set_zoom(HWND rich_edit_handle, int32_t numerator, int32_t denominator);

        bool can_redo(HWND rich_edit_handle);

        bool redo(HWND rich_edit_handle);

        RERedoState get_redo_state(HWND rich_edit_handle);

        REUndoState get_undo_state(HWND rich_edit_handle);

        int64_t set_undo_limit(HWND rich_edit_handle, int64_t limit = 100);

        REStoryType get_story_type(HWND rich_edit_handle, int64_t index);

        REStoryType
        set_story_type(HWND rich_edit_handle, int64_t index, REStoryType type);

        bool get_table(HWND rich_edit_handle,
                       TABLEROWPARMS *row,
                       TABLECELLPARMS *cell);

        bool set_table(HWND rich_edit_handle,
                       TABLEROWPARMS *row,
                       TABLECELLPARMS *cell);

        bool insert_table(HWND rich_edit_handle,
                          TABLEROWPARMS *row,
                          TABLECELLPARMS *cell);

        // text->cb = buf.size()
        int64_t get_text(HWND rich_edit_handle,
                         GETTEXTEX *text,
                         std::string &buf,
                         helper::CodePage code_page = helper::curr_code_page());

        // text->cb = buf.size() * sizeof(wchar_t)
        int64_t
        get_text(HWND rich_edit_handle, GETTEXTEX *text, std::wstring &buf);

        int64_t get_text(HWND rich_edit_handle,
                         std::string &buf,
                         REGetTextFlag flag = REGetTextFlag::Default,
                         const char *default_char = nullptr,
                         int32_t *used_default_char = nullptr,
                         helper::CodePage code_page = helper::curr_code_page());

        int64_t get_text(HWND rich_edit_handle,
                         std::wstring &buf,
                         REGetTextFlag flag = REGetTextFlag::Default,
                         const char *default_char = nullptr,
                         int32_t *used_default_char = nullptr,
                         helper::CodePage code_page = helper::curr_code_page());

        int64_t set_text(HWND rich_edit_handle,
                         SETTEXTEX *text,
                         std::string &buf,
                         helper::CodePage code_page = helper::curr_code_page());

        int64_t
        set_text(HWND rich_edit_handle, SETTEXTEX *text, std::wstring &buf);

        int64_t set_text(HWND rich_edit_handle,
                         std::string &buf,
                         RESetTextFlag flag = RESetTextFlag::Default,
                         helper::CodePage code_page = helper::curr_code_page());

        int64_t set_text(HWND rich_edit_handle,
                         std::wstring &buf,
                         RESetTextFlag flag = RESetTextFlag::Default,
                         helper::CodePage code_page = helper::curr_code_page());


        int64_t get_text_len(HWND rich_edit_handle, GETTEXTLENGTHEX *text_len);

        int64_t
        get_text_len(HWND rich_edit_handle,
                     REGetTextLenFlag flag = REGetTextLenFlag::Default,
                     helper::CodePage code_page = helper::curr_code_page());

        int64_t get_text_range(HWND rich_edit_handle, TEXTRANGEW *text_range);

        int64_t
        get_text_range(HWND rich_edit_handle,
                       int32_t first,
                       int32_t last,
                       std::string &buf,
                       helper::CodePage code_page = helper::curr_code_page());

        int64_t get_text_range(HWND rich_edit_handle,
                               int32_t first,
                               int32_t last,
                               std::wstring &buf);

        bool get_touch_option(HWND rich_edit_handle, RETouchOption option);

        void set_touch_option(HWND rich_edit_handle,
                              RETouchOption option,
                              bool enable = true);

        RETypographyOption get_typography_option(HWND rich_edit_handle);

        bool set_typography_option(HWND rich_edit_handle,
                                   RETypographyOption option,
                                   RETypographyOption mask);

        EDITWORDBREAKPROCEX get_word_break_proc(HWND rich_edit_handle);

        EDITWORDBREAKPROCEX set_word_break_proc(HWND rich_edit_handle,
                                                EDITWORDBREAKPROCEX func);

        bool get_ole_interface(HWND rich_edit_handle, IRichEditOle **ole);

        bool set_ole_callback(HWND rich_edit_handle,
                              IRichEditOleCallback *callback);

        REPageRotate get_page_rotate(HWND rich_edit_handle);

        REPageRotate set_page_rotate(HWND rich_edit_handle,
                                     REPageRotate rotate);

        COLORREF set_background_color(HWND rich_edit_handle,
                                      COLORREF color,
                                      bool use_system_color = false);

        bool set_font_size(HWND rich_edit_handle, int32_t size);

        void set_palette(HWND rich_edit_handle, HPALETTE palette_handle);

        bool
        set_target_device(HWND rich_edit_handle, HDC dc_handle, int32_t width);

        bool
        set_uia_name(HWND rich_edit_handle,
                     std::string &name,
                     helper::CodePage code_page = helper::curr_code_page());

        bool set_uia_name(HWND rich_edit_handle, std::wstring &name);

        bool can_paste(HWND rich_edit_handle, int64_t paste_format = 0);

        bool insert_image(HWND rich_edit_handle,
                          RICHEDIT_IMAGE_PARAMETERS *image);

        void paste_special(HWND rich_edit_handle,
                           int64_t paste_format,
                           REPASTESPECIAL *paste);

        void reconversion(HWND rich_edit_handle);

        void request_resize(HWND rich_edit_handle);

        void stop_group_typing(HWND rich_edit_handle);

        int64_t stream_in(HWND rich_edit_handle,
                          EDITSTREAM *stream,
                          REStreamFormat format);

        int64_t stream_out(HWND rich_edit_handle,
                           EDITSTREAM *stream,
                           REStreamFormat format);

        void set_text_limit(HWND rich_edit_handle, int32_t limit = 0);

        int64_t line_from_char(HWND rich_edit_handle, int64_t char_index);

        [[nodiscard]] uint32_t err_code() const;

        [[nodiscard]] std::string err_string() const;

        [[nodiscard]] std::wstring err_wstring() const;
    };
} // namespace YanLib::ui::components
#endif // RICH_EDIT_H
