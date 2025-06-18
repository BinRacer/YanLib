/* clang-format off */
/*
 * @file components.h
 * @date 2025-06-18
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
#ifndef COMPONENTS_H
#define COMPONENTS_H
#include <WinUser.h>
#include <CommCtrl.h>
#include <WinNls.h>
#include <minwindef.h>
#include <windef.h>
#include <dpa_dsa.h>
#include <wingdi.h>
#include <winnt.h>
#include <prsht.h>
#include <Richedit.h>
#include <ime_cmodes.h>
#include <TOM.h>
#include <cstdint>
namespace YanLib::ui::components {
    enum class AnimateStyle : uint32_t {
        Center = ACS_CENTER,
        Transparent = ACS_TRANSPARENT,
        AutoPlay = ACS_AUTOPLAY,
        Timer = ACS_TIMER,
    };

    inline AnimateStyle operator|(AnimateStyle a, AnimateStyle b) {
        return static_cast<AnimateStyle>(static_cast<uint32_t>(a) |
                                         static_cast<uint32_t>(b));
    }

    enum class AnimateMessage : uint32_t {
        IsPlaying = ACM_ISPLAYING,
        Open = ACM_OPEN,
        Play = ACM_PLAY,
        Stop = ACM_STOP,
    };

    enum class AnimateNotify : uint32_t {
        Start = ACN_START,
        Stop = ACN_STOP,
    };

    enum class ButtonStyle : uint32_t {
        PushButton = BS_PUSHBUTTON,
        DefPushButton = BS_DEFPUSHBUTTON,
        CheckBox = BS_CHECKBOX,
        AutoCheckBox = BS_AUTOCHECKBOX,
        RadioButton = BS_RADIOBUTTON,
        ThreeState = BS_3STATE,
        AutoThreeState = BS_AUTO3STATE,
        GroupBox = BS_GROUPBOX,
        UserButton = BS_USERBUTTON,
        AutoRadioButton = BS_AUTORADIOBUTTON,
        PushBox = BS_PUSHBOX,
        OwnerDraw = BS_OWNERDRAW,
        TypeMask = BS_TYPEMASK,
        LeftText = BS_LEFTTEXT,
        Text = BS_TEXT,
        Icon = BS_ICON,
        Bitmap = BS_BITMAP,
        Left = BS_LEFT,
        Right = BS_RIGHT,
        Center = BS_CENTER,
        Top = BS_TOP,
        Bottom = BS_BOTTOM,
        VertCenter = BS_VCENTER,
        PushLike = BS_PUSHLIKE,
        MultiLine = BS_MULTILINE,
        Notify = BS_NOTIFY,
        Flat = BS_FLAT,
        RightButton = BS_RIGHTBUTTON,
    };

    inline ButtonStyle operator|(ButtonStyle a, ButtonStyle b) {
        return static_cast<ButtonStyle>(static_cast<uint32_t>(a) |
                                        static_cast<uint32_t>(b));
    }

    enum class TextAlign : uint32_t {
        Left = BS_LEFT,
        Right = BS_RIGHT,
        Center = BS_CENTER,
        Top = BS_TOP,
        Bottom = BS_BOTTOM,
        VertCenter = BS_VCENTER,
    };

    inline TextAlign operator|(TextAlign a, TextAlign b) {
        return static_cast<TextAlign>(static_cast<uint32_t>(a) |
                                      static_cast<uint32_t>(b));
    }

    enum class ButtonMessage : uint32_t {
        GetIdealSize = BCM_GETIDEALSIZE,
        GetImageList = BCM_GETIMAGELIST,
        GetNote = BCM_GETNOTE,
        GetNoteLength = BCM_GETNOTELENGTH,
        GetSplitInfo = BCM_GETSPLITINFO,
        GetTextMargin = BCM_GETTEXTMARGIN,
        SetDropDownState = BCM_SETDROPDOWNSTATE,
        SetImageList = BCM_SETIMAGELIST,
        SetNote = BCM_SETNOTE,
        SetShield = BCM_SETSHIELD,
        SetSplitInfo = BCM_SETSPLITINFO,
        SetTextMargin = BCM_SETTEXTMARGIN,
        Click = BM_CLICK,
        GetCheck = BM_GETCHECK,
        GetImage = BM_GETIMAGE,
        GetState = BM_GETSTATE,
        SetCheck = BM_SETCHECK,
        SetDontClick = BM_SETDONTCLICK,
        SetImage = BM_SETIMAGE,
        SetState = BM_SETSTATE,
        SetStyle = BM_SETSTYLE,
    };

    enum class ButtonNotify : uint32_t {
        DropDown = BCN_DROPDOWN,
        HotItemChange = BCN_HOTITEMCHANGE,
        Clicked = BN_CLICKED,
        DoubleClick = BN_DBLCLK,
        Disable = BN_DISABLE,
        DoubleClicked = BN_DOUBLECLICKED,
        HiLite = BN_HILITE,
        KillFocus = BN_KILLFOCUS,
        Paint = BN_PAINT,
        Pushed = BN_PUSHED,
        SetFocus = BN_SETFOCUS,
        UnHiLite = BN_UNHILITE,
        Unpushed = BN_UNPUSHED,
        CustomDraw = NM_CUSTOMDRAW,
        CtlColorBtn = WM_CTLCOLORBTN,
    };

    enum class CalendarStyle : uint32_t {
        DayState = MCS_DAYSTATE,
        MultiSelect = MCS_MULTISELECT,
        WeekNumbers = MCS_WEEKNUMBERS,
        NoTodayCircle = MCS_NOTODAYCIRCLE,
        NoToday = MCS_NOTODAY,
        NoTrailingDates = MCS_NOTRAILINGDATES,
        ShortDaysOfWeek = MCS_SHORTDAYSOFWEEK,
        NoSelectChangeOnNav = MCS_NOSELCHANGEONNAV,
    };

    inline CalendarStyle operator|(CalendarStyle a, CalendarStyle b) {
        return static_cast<CalendarStyle>(static_cast<uint32_t>(a) |
                                          static_cast<uint32_t>(b));
    }

    enum class CalendarId : uint32_t {
        GREGORIAN = CAL_GREGORIAN,
        GREGORIAN_US = CAL_GREGORIAN_US,
        JAPAN = CAL_JAPAN,
        TAIWAN = CAL_TAIWAN,
        KOREA = CAL_KOREA,
        HIJRI = CAL_HIJRI,
        THAI = CAL_THAI,
        HEBREW = CAL_HEBREW,
        GREGORIAN_ME_FRENCH = CAL_GREGORIAN_ME_FRENCH,
        GREGORIAN_ARABIC = CAL_GREGORIAN_ARABIC,
        GREGORIAN_XLIT_ENGLISH = CAL_GREGORIAN_XLIT_ENGLISH,
        GREGORIAN_XLIT_FRENCH = CAL_GREGORIAN_XLIT_FRENCH,
        PERSIAN = CAL_PERSIAN,
        UMALQURA = CAL_UMALQURA,

    };

    enum class CalendarColorCode : uint32_t {
        Background = MCSC_BACKGROUND,
        Text = MCSC_TEXT,
        TitleBackground = MCSC_TITLEBK,
        TitleText = MCSC_TITLETEXT,
        MonthBackground = MCSC_MONTHBK,
        TrailingText = MCSC_TRAILINGTEXT,
    };

    enum class CalendarView : uint32_t {
        Month = MCMV_MONTH,
        Year = MCMV_YEAR,
        Decade = MCMV_DECADE,
        Century = MCMV_CENTURY,
    };

    enum class CalendarWeekDay : uint32_t {
        Monday = 0,
        Tuesday,
        Wednesday,
        Thursday,
        Friday,
        Saturday,
        Sunday
    };

    enum class CalendarMonth : uint32_t {
        January = 1,
        February,
        March,
        April,
        May,
        June,
        July,
        August,
        September,
        October,
        November,
        December
    };

    enum class CalendarMessage : uint32_t {
        GetCalendarBorder = MCM_GETCALENDARBORDER,
        GetCalendarCount = MCM_GETCALENDARCOUNT,
        GetCalendarGridInfo = MCM_GETCALENDARGRIDINFO,
        GetCalendarId = MCM_GETCALID,
        GetColor = MCM_GETCOLOR,
        GetCurrentView = MCM_GETCURRENTVIEW,
        GetCurrentSelect = MCM_GETCURSEL,
        GetFirstDayOfWeek = MCM_GETFIRSTDAYOFWEEK,
        GetMaxSelCount = MCM_GETMAXSELCOUNT,
        GetMaxTodayWidth = MCM_GETMAXTODAYWIDTH,
        GetMinRequestRect = MCM_GETMINREQRECT,
        GetMonthDelta = MCM_GETMONTHDELTA,
        GetMonthRange = MCM_GETMONTHRANGE,
        GetRange = MCM_GETRANGE,
        GetSelectRange = MCM_GETSELRANGE,
        GetToday = MCM_GETTODAY,
        GetUnicodeFormat = MCM_GETUNICODEFORMAT,
        HitTest = MCM_HITTEST,
        SetCalendarBorder = MCM_SETCALENDARBORDER,
        SetCalendarId = MCM_SETCALID,
        SetColor = MCM_SETCOLOR,
        SetCurrentView = MCM_SETCURRENTVIEW,
        SetCurrentSelect = MCM_SETCURSEL,
        SetDayState = MCM_SETDAYSTATE,
        SetFirstDayOfWeek = MCM_SETFIRSTDAYOFWEEK,
        SetMaxSelectCount = MCM_SETMAXSELCOUNT,
        SetMonthDelta = MCM_SETMONTHDELTA,
        SetRange = MCM_SETRANGE,
        SetSelectRange = MCM_SETSELRANGE,
        SetToday = MCM_SETTODAY,
        SetUnicodeFormat = MCM_SETUNICODEFORMAT,
        SizeRectToMin = MCM_SIZERECTTOMIN
    };

    enum class CalendarNotify : uint32_t {
        GetDayState = MCN_GETDAYSTATE,
        SelectChange = MCN_SELCHANGE,
        Select = MCN_SELECT,
        ViewChange = MCN_VIEWCHANGE,
        ReleasedCapture = NM_RELEASEDCAPTURE,
    };

    enum class ComboBoxStyle : uint32_t {
        Simple = CBS_SIMPLE,
        DropDown = CBS_DROPDOWN,
        DropDownList = CBS_DROPDOWNLIST,
        OwnerDrawFixed = CBS_OWNERDRAWFIXED,
        OwnerDrawVariable = CBS_OWNERDRAWVARIABLE,
        AutoHorizScroll = CBS_AUTOHSCROLL,
        OemConvert = CBS_OEMCONVERT,
        Sort = CBS_SORT,
        HasStrings = CBS_HASSTRINGS,
        NoIntegralHeight = CBS_NOINTEGRALHEIGHT,
        DisableNoScroll = CBS_DISABLENOSCROLL,
        Uppercase = CBS_UPPERCASE,
        Lowercase = CBS_LOWERCASE,
    };

    inline ComboBoxStyle operator|(ComboBoxStyle a, ComboBoxStyle b) {
        return static_cast<ComboBoxStyle>(static_cast<uint32_t>(a) |
                                          static_cast<uint32_t>(b));
    }

    enum class ComboFileType : uint32_t {
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

    inline ComboFileType operator|(ComboFileType a, ComboFileType b) {
        return static_cast<ComboFileType>(static_cast<uint32_t>(a) |
                                          static_cast<uint32_t>(b));
    }

    enum class ComboBoxMessage : uint32_t {
        AddString = CB_ADDSTRING,
        DeleteString = CB_DELETESTRING,
        Dir = CB_DIR,
        FindString = CB_FINDSTRING,
        FindStringExact = CB_FINDSTRINGEXACT,
        GetComboBoxInfo = CB_GETCOMBOBOXINFO,
        GetCount = CB_GETCOUNT,
        GetCueBanner = CB_GETCUEBANNER,
        GetCurrentSelect = CB_GETCURSEL,
        GetDroppedControlRect = CB_GETDROPPEDCONTROLRECT,
        GetDroppedState = CB_GETDROPPEDSTATE,
        GetDroppedWidth = CB_GETDROPPEDWIDTH,
        GetEditSel = CB_GETEDITSEL,
        GetExtendedUI = CB_GETEXTENDEDUI,
        GetHorizontalExtent = CB_GETHORIZONTALEXTENT,
        GetItemData = CB_GETITEMDATA,
        GetItemHeight = CB_GETITEMHEIGHT,
        GetLBText = CB_GETLBTEXT,
        GetLBTextLen = CB_GETLBTEXTLEN,
        GetLocale = CB_GETLOCALE,
        GetMinVisible = CB_GETMINVISIBLE,
        GetTopIndex = CB_GETTOPINDEX,
        InitStorage = CB_INITSTORAGE,
        InsertString = CB_INSERTSTRING,
        LimitText = CB_LIMITTEXT,
        ResetContent = CB_RESETCONTENT,
        SelectString = CB_SELECTSTRING,
        SetCueBanner = CB_SETCUEBANNER,
        SetCurrentSelect = CB_SETCURSEL,
        SetDroppedWidth = CB_SETDROPPEDWIDTH,
        SetEditSel = CB_SETEDITSEL,
        SetExtendedUI = CB_SETEXTENDEDUI,
        SetHorizontalExtent = CB_SETHORIZONTALEXTENT,
        SetItemData = CB_SETITEMDATA,
        SetItemHeight = CB_SETITEMHEIGHT,
        SetLocale = CB_SETLOCALE,
        SetMinVisible = CB_SETMINVISIBLE,
        SetTopIndex = CB_SETTOPINDEX,
        ShowDropDown = CB_SHOWDROPDOWN,
    };

    enum class ComboBoxNotify : int32_t {
        CloseUp = CBN_CLOSEUP,
        DoubleClick = CBN_DBLCLK,
        DropDown = CBN_DROPDOWN,
        EditChange = CBN_EDITCHANGE,
        EditUpdate = CBN_EDITUPDATE,
        ErrSpace = CBN_ERRSPACE,
        KillFocus = CBN_KILLFOCUS,
        SelChange = CBN_SELCHANGE,
        SelEndCancel = CBN_SELENDCANCEL,
        SelEndOK = CBN_SELENDOK,
        SetFocus = CBN_SETFOCUS,
        CompareItem = WM_COMPAREITEM,
        DrawItem = WM_DRAWITEM,
        MeasureItem = WM_MEASUREITEM
    };

    enum class DateTimeStyle : uint32_t {
        UpDown = DTS_UPDOWN,
        ShowNone = DTS_SHOWNONE,
        ShortDateFormat = DTS_SHORTDATEFORMAT,
        LongDateFormat = DTS_LONGDATEFORMAT,
        ShortDateCenturyFormat = DTS_SHORTDATECENTURYFORMAT,
        TimeFormat = DTS_TIMEFORMAT,
        AppCanParse = DTS_APPCANPARSE,
        RightAlign = DTS_RIGHTALIGN,

    };

    inline DateTimeStyle operator|(DateTimeStyle a, DateTimeStyle b) {
        return static_cast<DateTimeStyle>(static_cast<uint32_t>(a) |
                                          static_cast<uint32_t>(b));
    }

    enum class MonthCode : int32_t {
        Background = MCSC_BACKGROUND,
        Text = MCSC_TEXT,
        TitleBackground = MCSC_TITLEBK,
        TitleText = MCSC_TITLETEXT,
        MonthBackground = MCSC_MONTHBK,
        TrailingText = MCSC_TRAILINGTEXT,
    };

    inline MonthCode operator|(MonthCode a, MonthCode b) {
        return static_cast<MonthCode>(static_cast<int32_t>(a) |
                                      static_cast<int32_t>(b));
    }

    enum class MonthStyle : uint32_t {
        DayState = MCS_DAYSTATE,
        MultiSelect = MCS_MULTISELECT,
        WeekNumbers = MCS_WEEKNUMBERS,
        NoTodayCircle = MCS_NOTODAYCIRCLE,
        NoToday = MCS_NOTODAY,
        NoTrailingDates = MCS_NOTRAILINGDATES,
        ShortDaysOfWeek = MCS_SHORTDAYSOFWEEK,
        NoSelChangeOnNav = MCS_NOSELCHANGEONNAV,
    };

    inline MonthStyle operator|(MonthStyle a, MonthStyle b) {
        return static_cast<MonthStyle>(static_cast<uint32_t>(a) |
                                       static_cast<uint32_t>(b));
    }

    enum class DateTimeMessage : uint32_t {
        CloseMonthCalendar = DTM_CLOSEMONTHCAL,
        GetDateTimePickerInfo = DTM_GETDATETIMEPICKERINFO,
        GetIdealSize = DTM_GETIDEALSIZE,
        GetMonthControlColor = DTM_GETMCCOLOR,
        GetMonthControlFont = DTM_GETMCFONT,
        GetMonthControlStyle = DTM_GETMCSTYLE,
        GetMonthCalendar = DTM_GETMONTHCAL,
        GetRange = DTM_GETRANGE,
        GetSystemTime = DTM_GETSYSTEMTIME,
        SetFormat = DTM_SETFORMAT,
        SetMonthControlColor = DTM_SETMCCOLOR,
        SetMonthControlFont = DTM_SETMCFONT,
        SetMonthControlStyle = DTM_SETMCSTYLE,
        SetRange = DTM_SETRANGE,
        SetSystemTime = DTM_SETSYSTEMTIME,
    };

    enum class DateTimeNotify : uint32_t {
        CloseUp = DTN_CLOSEUP,
        DatetimeChange = DTN_DATETIMECHANGE,
        DropDown = DTN_DROPDOWN,
        Format = DTN_FORMAT,
        FormatQuery = DTN_FORMATQUERY,
        UserString = DTN_USERSTRING,
        Keydown = DTN_WMKEYDOWN,
        KillFocus = NM_KILLFOCUS,
        SetFocus = NM_SETFOCUS,
    };

    enum class EditStyle : uint32_t {
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
        Number = ES_NUMBER
    };

    inline EditStyle operator|(EditStyle a, EditStyle b) {
        return static_cast<EditStyle>(static_cast<uint32_t>(a) |
                                      static_cast<uint32_t>(b));
    }

    enum class EditMessage : uint32_t {
        CanUndo = EM_CANUNDO,
        CharFromPos = EM_CHARFROMPOS,
        EmptyUndoBuffer = EM_EMPTYUNDOBUFFER,
        FmtLines = EM_FMTLINES,
        GetCueBanner = EM_GETCUEBANNER,
        GetFirstVisibleLine = EM_GETFIRSTVISIBLELINE,
        GetHandle = EM_GETHANDLE,
        GetHiLite = EM_GETHILITE,
        GetImeStatus = EM_GETIMESTATUS,
        GetLimitText = EM_GETLIMITTEXT,
        GetLine = EM_GETLINE,
        GetLineCount = EM_GETLINECOUNT,
        GetMargins = EM_GETMARGINS,
        GetModify = EM_GETMODIFY,
        GetPasswordChar = EM_GETPASSWORDCHAR,
        GetRect = EM_GETRECT,
        GetSelect = EM_GETSEL,
        GetThumb = EM_GETTHUMB,
        GetWordBreakProc = EM_GETWORDBREAKPROC,
        HideBalloonTip = EM_HIDEBALLOONTIP,
        LimitText = EM_LIMITTEXT,
        LineFromChar = EM_LINEFROMCHAR,
        LineIndex = EM_LINEINDEX,
        LineLength = EM_LINELENGTH,
        LineScroll = EM_LINESCROLL,
        NoSetFocus = EM_NOSETFOCUS,
        PosFromChar = EM_POSFROMCHAR,
        ReplaceSel = EM_REPLACESEL,
        Scroll = EM_SCROLL,
        ScrollCaret = EM_SCROLLCARET,
        SetCueBanner = EM_SETCUEBANNER,
        SetHandle = EM_SETHANDLE,
        SetHiLite = EM_SETHILITE,
        SetImeStatus = EM_SETIMESTATUS,
        SetLimitText = EM_SETLIMITTEXT,
        SetMargins = EM_SETMARGINS,
        SetModify = EM_SETMODIFY,
        SetPasswordChar = EM_SETPASSWORDCHAR,
        SetReadOnly = EM_SETREADONLY,
        SetRect = EM_SETRECT,
        SetRectNP = EM_SETRECTNP,
        SetSelect = EM_SETSEL,
        SetTabStops = EM_SETTABSTOPS,
        SetWordBreakProc = EM_SETWORDBREAKPROC,
        ShowBalloonTip = EM_SHOWBALLOONTIP,
        TakeFocus = EM_TAKEFOCUS,
        Undo = EM_UNDO,
        WmUndo = WM_UNDO
    };

    enum class EditNotify : uint32_t {
        AlignLtrEc = EN_ALIGN_LTR_EC,
        AlignRtlEc = EN_ALIGN_RTL_EC,
        Change = EN_CHANGE,
        ErrSpace = EN_ERRSPACE,
        HScroll = EN_HSCROLL,
        KillFocus = EN_KILLFOCUS,
        MaxText = EN_MAXTEXT,
        SetFocus = EN_SETFOCUS,
        Update = EN_UPDATE,
        VScroll = EN_VSCROLL,
        CtlColorEdit = WM_CTLCOLOREDIT,
    };

    enum class CommonStyle : uint32_t {
        Top = CCS_TOP,
        NoMoveY = CCS_NOMOVEY,
        Bottom = CCS_BOTTOM,
        NoResize = CCS_NORESIZE,
        NoParentAlign = CCS_NOPARENTALIGN,
        Adjustable = CCS_ADJUSTABLE,
        NoDivider = CCS_NODIVIDER,
        Vert = CCS_VERT,
        Left = CCS_LEFT,
        Right = CCS_RIGHT,
        NoMoveX = CCS_NOMOVEX,
    };

    inline CommonStyle operator|(CommonStyle a, CommonStyle b) {
        return static_cast<CommonStyle>(static_cast<uint32_t>(a) |
                                        static_cast<uint32_t>(b));
    }

    enum class InitCommControlsFlag : uint32_t {
        ListView = ICC_LISTVIEW_CLASSES, // listview, header
        TreeView = ICC_TREEVIEW_CLASSES, // treeview, tooltips
        Bar = ICC_BAR_CLASSES,         // toolbar, statusbar, trackbar, tooltips
        Tab = ICC_TAB_CLASSES,         // tab, tooltips
        UpDown = ICC_UPDOWN_CLASS,     // updown
        Progress = ICC_PROGRESS_CLASS, // progress
        HotKey = ICC_HOTKEY_CLASS,     // hotkey
        Animate = ICC_ANIMATE_CLASS,   // animate
        Win95 = ICC_WIN95_CLASSES,
        Date = ICC_DATE_CLASSES,     // month picker, date picker, time picker,
                                     // updown
        UserEx = ICC_USEREX_CLASSES, // comboex
        Cool = ICC_COOL_CLASSES,     // rebar (coolbar) control
        Internet = ICC_INTERNET_CLASSES,
        PageScroller = ICC_PAGESCROLLER_CLASS, // page scroller
        NativeFntCtl = ICC_NATIVEFNTCTL_CLASS, // native font control
        Standard = ICC_STANDARD_CLASSES,
        Link = ICC_LINK_CLASS,
    };

    inline InitCommControlsFlag operator|(InitCommControlsFlag a,
                                          InitCommControlsFlag b) {
        return static_cast<InitCommControlsFlag>(static_cast<uint32_t>(a) |
                                                 static_cast<uint32_t>(b));
    }

    enum class GeneralLangID : uint16_t {
        Neutral = LANG_NEUTRAL,
        Invariant = LANG_INVARIANT,
        Afrikaans = LANG_AFRIKAANS,
        Albanian = LANG_ALBANIAN,
        Alsatian = LANG_ALSATIAN,
        Amharic = LANG_AMHARIC,
        Arabic = LANG_ARABIC,
        Armenian = LANG_ARMENIAN,
        Assamese = LANG_ASSAMESE,
        Azeri = LANG_AZERI,
        Azerbaijani = LANG_AZERBAIJANI,
        Bangla = LANG_BANGLA,
        Bashkir = LANG_BASHKIR,
        Basque = LANG_BASQUE,
        Belarusian = LANG_BELARUSIAN,
        Bengali = LANG_BENGALI,
        Breton = LANG_BRETON,
        Bosnian = LANG_BOSNIAN,
        BosnianNeutral = LANG_BOSNIAN_NEUTRAL,
        Bulgarian = LANG_BULGARIAN,
        Catalan = LANG_CATALAN,
        CentralKurdish = LANG_CENTRAL_KURDISH,
        Cherokee = LANG_CHEROKEE,
        Chinese = LANG_CHINESE,
        ChineseSimplified = LANG_CHINESE_SIMPLIFIED,
        ChineseTraditional = LANG_CHINESE_TRADITIONAL,
        Corsican = LANG_CORSICAN,
        Croatian = LANG_CROATIAN,
        Czech = LANG_CZECH,
        Danish = LANG_DANISH,
        Dari = LANG_DARI,
        Divehi = LANG_DIVEHI,
        Dutch = LANG_DUTCH,
        English = LANG_ENGLISH,
        Estonian = LANG_ESTONIAN,
        Faeroese = LANG_FAEROESE,
        Farsi = LANG_FARSI,
        Filipino = LANG_FILIPINO,
        Finnish = LANG_FINNISH,
        French = LANG_FRENCH,
        Frisian = LANG_FRISIAN,
        Fulah = LANG_FULAH,
        Galician = LANG_GALICIAN,
        Georgian = LANG_GEORGIAN,
        German = LANG_GERMAN,
        Greek = LANG_GREEK,
        Greenlandic = LANG_GREENLANDIC,
        Gujarati = LANG_GUJARATI,
        Hausa = LANG_HAUSA,
        Hawaiian = LANG_HAWAIIAN,
        Hebrew = LANG_HEBREW,
        Hindi = LANG_HINDI,
        Hungarian = LANG_HUNGARIAN,
        Icelandic = LANG_ICELANDIC,
        Igbo = LANG_IGBO,
        Indonesian = LANG_INDONESIAN,
        Inuktitut = LANG_INUKTITUT,
        Irish = LANG_IRISH,
        Italian = LANG_ITALIAN,
        Japanese = LANG_JAPANESE,
        Kannada = LANG_KANNADA,
        Kashmiri = LANG_KASHMIRI,
        Kazak = LANG_KAZAK,
        Khmer = LANG_KHMER,
        Kiche = LANG_KICHE,
        Kinyarwanda = LANG_KINYARWANDA,
        Konkani = LANG_KONKANI,
        Korean = LANG_KOREAN,
        Kyrgyz = LANG_KYRGYZ,
        Lao = LANG_LAO,
        Latvian = LANG_LATVIAN,
        Lithuanian = LANG_LITHUANIAN,
        LowerSorbian = LANG_LOWER_SORBIAN,
        Luxembourgish = LANG_LUXEMBOURGISH,
        Macedonian = LANG_MACEDONIAN,
        Malay = LANG_MALAY,
        Malayalam = LANG_MALAYALAM,
        Maltese = LANG_MALTESE,
        Manipuri = LANG_MANIPURI,
        Maori = LANG_MAORI,
        Mapudungun = LANG_MAPUDUNGUN,
        Marathi = LANG_MARATHI,
        Mohawk = LANG_MOHAWK,
        Mongolian = LANG_MONGOLIAN,
        Nepali = LANG_NEPALI,
        Norwegian = LANG_NORWEGIAN,
        Occitan = LANG_OCCITAN,
        Odia = LANG_ODIA,
        Oriya = LANG_ORIYA,
        Pashto = LANG_PASHTO,
        Persian = LANG_PERSIAN,
        Polish = LANG_POLISH,
        Portuguese = LANG_PORTUGUESE,
        Pular = LANG_PULAR,
        Punjabi = LANG_PUNJABI,
        Quechua = LANG_QUECHUA,
        Romanian = LANG_ROMANIAN,
        Romansh = LANG_ROMANSH,
        Russian = LANG_RUSSIAN,
        Sakha = LANG_SAKHA,
        Sami = LANG_SAMI,
        Sanskrit = LANG_SANSKRIT,
        ScottishGaelic = LANG_SCOTTISH_GAELIC,
        Serbian = LANG_SERBIAN,
        SerbianNeutral = LANG_SERBIAN_NEUTRAL,
        Sindhi = LANG_SINDHI,
        Sinhalese = LANG_SINHALESE,
        Slovak = LANG_SLOVAK,
        Slovenian = LANG_SLOVENIAN,
        Sotho = LANG_SOTHO,
        Spanish = LANG_SPANISH,
        Swahili = LANG_SWAHILI,
        Swedish = LANG_SWEDISH,
        Syriac = LANG_SYRIAC,
        Tajik = LANG_TAJIK,
        Tamazight = LANG_TAMAZIGHT,
        Tamil = LANG_TAMIL,
        Tatar = LANG_TATAR,
        Telugu = LANG_TELUGU,
        Thai = LANG_THAI,
        Tibetan = LANG_TIBETAN,
        Tigrigna = LANG_TIGRIGNA,
        Tigrinya = LANG_TIGRINYA,
        Tswana = LANG_TSWANA,
        Turkish = LANG_TURKISH,
        Turkmen = LANG_TURKMEN,
        Uighur = LANG_UIGHUR,
        Ukrainian = LANG_UKRAINIAN,
        UpperSorbian = LANG_UPPER_SORBIAN,
        Urdu = LANG_URDU,
        Uzbek = LANG_UZBEK,
        Valencian = LANG_VALENCIAN,
        Vietnamese = LANG_VIETNAMESE,
        Welsh = LANG_WELSH,
        Wolof = LANG_WOLOF,
        Xhosa = LANG_XHOSA,
        Yakut = LANG_YAKUT,
        Yi = LANG_YI,
        Yoruba = LANG_YORUBA,
        Zulu = LANG_ZULU
    };

    enum class GeneralSubLangId : uint16_t {
        Neutral = SUBLANG_NEUTRAL,
        Default = SUBLANG_DEFAULT,
        SysDefault = SUBLANG_SYS_DEFAULT,
        CustomDefault = SUBLANG_CUSTOM_DEFAULT,
        CustomUnspecified = SUBLANG_CUSTOM_UNSPECIFIED,
        UiCustomDefault = SUBLANG_UI_CUSTOM_DEFAULT,
        AfrikaansSouthAfrica = SUBLANG_AFRIKAANS_SOUTH_AFRICA,
        AlbanianAlbania = SUBLANG_ALBANIAN_ALBANIA,
        AlsatianFrance = SUBLANG_ALSATIAN_FRANCE,
        AmharicEthiopia = SUBLANG_AMHARIC_ETHIOPIA,
        ArabicSaudiArabia = SUBLANG_ARABIC_SAUDI_ARABIA,
        ArabicIraq = SUBLANG_ARABIC_IRAQ,
        ArabicEgypt = SUBLANG_ARABIC_EGYPT,
        ArabicLibya = SUBLANG_ARABIC_LIBYA,
        ArabicAlgeria = SUBLANG_ARABIC_ALGERIA,
        ArabicMorocco = SUBLANG_ARABIC_MOROCCO,
        ArabicTunisia = SUBLANG_ARABIC_TUNISIA,
        ArabicOman = SUBLANG_ARABIC_OMAN,
        ArabicYemen = SUBLANG_ARABIC_YEMEN,
        ArabicSyria = SUBLANG_ARABIC_SYRIA,
        ArabicJordan = SUBLANG_ARABIC_JORDAN,
        ArabicLebanon = SUBLANG_ARABIC_LEBANON,
        ArabicKuwait = SUBLANG_ARABIC_KUWAIT,
        ArabicUae = SUBLANG_ARABIC_UAE,
        ArabicBahrain = SUBLANG_ARABIC_BAHRAIN,
        ArabicQatar = SUBLANG_ARABIC_QATAR,
        ArmenianArmenia = SUBLANG_ARMENIAN_ARMENIA,
        AssameseIndia = SUBLANG_ASSAMESE_INDIA,
        AzeriLatin = SUBLANG_AZERI_LATIN,
        AzeriCyrillic = SUBLANG_AZERI_CYRILLIC,
        AzerbaijaniAzerbaijanLatin = SUBLANG_AZERBAIJANI_AZERBAIJAN_LATIN,
        AzerbaijaniAzerbaijanCyrillic = SUBLANG_AZERBAIJANI_AZERBAIJAN_CYRILLIC,
        BanglaIndia = SUBLANG_BANGLA_INDIA,
        BanglaBangladesh = SUBLANG_BANGLA_BANGLADESH,
        BashkirRussia = SUBLANG_BASHKIR_RUSSIA,
        BasqueBasque = SUBLANG_BASQUE_BASQUE,
        BelarusianBelarus = SUBLANG_BELARUSIAN_BELARUS,
        BengaliIndia = SUBLANG_BENGALI_INDIA,
        BengaliBangladesh = SUBLANG_BENGALI_BANGLADESH,
        BosnianBosniaHerzegovinaLatin =
                SUBLANG_BOSNIAN_BOSNIA_HERZEGOVINA_LATIN,
        BosnianBosniaHerzegovinaCyrillic =
                SUBLANG_BOSNIAN_BOSNIA_HERZEGOVINA_CYRILLIC,
        BretonFrance = SUBLANG_BRETON_FRANCE,
        BulgarianBulgaria = SUBLANG_BULGARIAN_BULGARIA,
        CatalanCatalan = SUBLANG_CATALAN_CATALAN,
        CentralKurdishIraq = SUBLANG_CENTRAL_KURDISH_IRAQ,
        CherokeeCherokee = SUBLANG_CHEROKEE_CHEROKEE,
        ChineseTraditional = SUBLANG_CHINESE_TRADITIONAL,
        ChineseSimplified = SUBLANG_CHINESE_SIMPLIFIED,
        ChineseHongKong = SUBLANG_CHINESE_HONGKONG,
        ChineseSingapore = SUBLANG_CHINESE_SINGAPORE,
        ChineseMacau = SUBLANG_CHINESE_MACAU,
        CorsicanFrance = SUBLANG_CORSICAN_FRANCE,
        CzechCzechRepublic = SUBLANG_CZECH_CZECH_REPUBLIC,
        CroatianCroatia = SUBLANG_CROATIAN_CROATIA,
        CroatianBosniaHerzegovinaLatin =
                SUBLANG_CROATIAN_BOSNIA_HERZEGOVINA_LATIN,
        DanishDenmark = SUBLANG_DANISH_DENMARK,
        DariAfghanistan = SUBLANG_DARI_AFGHANISTAN,
        DivehiMaldives = SUBLANG_DIVEHI_MALDIVES,
        Dutch = SUBLANG_DUTCH,
        DutchBelgian = SUBLANG_DUTCH_BELGIAN,
        EnglishUs = SUBLANG_ENGLISH_US,
        EnglishUk = SUBLANG_ENGLISH_UK,
        EnglishAus = SUBLANG_ENGLISH_AUS,
        EnglishCan = SUBLANG_ENGLISH_CAN,
        EnglishNz = SUBLANG_ENGLISH_NZ,
        EnglishEire = SUBLANG_ENGLISH_EIRE,
        EnglishSouthAfrica = SUBLANG_ENGLISH_SOUTH_AFRICA,
        EnglishJamaica = SUBLANG_ENGLISH_JAMAICA,
        EnglishCaribbean = SUBLANG_ENGLISH_CARIBBEAN,
        EnglishBelize = SUBLANG_ENGLISH_BELIZE,
        EnglishTrinidad = SUBLANG_ENGLISH_TRINIDAD,
        EnglishZimbabwe = SUBLANG_ENGLISH_ZIMBABWE,
        EnglishPhilippines = SUBLANG_ENGLISH_PHILIPPINES,
        EnglishIndia = SUBLANG_ENGLISH_INDIA,
        EnglishMalaysia = SUBLANG_ENGLISH_MALAYSIA,
        EnglishSingapore = SUBLANG_ENGLISH_SINGAPORE,
        EstonianEstonia = SUBLANG_ESTONIAN_ESTONIA,
        FaeroeseFaroeIslands = SUBLANG_FAEROESE_FAROE_ISLANDS,
        FilipinoPhilippines = SUBLANG_FILIPINO_PHILIPPINES,
        FinnishFinland = SUBLANG_FINNISH_FINLAND,
        French = SUBLANG_FRENCH,
        FrenchBelgian = SUBLANG_FRENCH_BELGIAN,
        FrenchCanadian = SUBLANG_FRENCH_CANADIAN,
        FrenchSwiss = SUBLANG_FRENCH_SWISS,
        FrenchLuxembourg = SUBLANG_FRENCH_LUXEMBOURG,
        FrenchMonaco = SUBLANG_FRENCH_MONACO,
        FrisianNetherlands = SUBLANG_FRISIAN_NETHERLANDS,
        FulahSenegal = SUBLANG_FULAH_SENEGAL,
        GalicianGalician = SUBLANG_GALICIAN_GALICIAN,
        GeorgianGeorgia = SUBLANG_GEORGIAN_GEORGIA,
        German = SUBLANG_GERMAN,
        GermanSwiss = SUBLANG_GERMAN_SWISS,
        GermanAustrian = SUBLANG_GERMAN_AUSTRIAN,
        GermanLuxembourg = SUBLANG_GERMAN_LUXEMBOURG,
        GermanLiechtenstein = SUBLANG_GERMAN_LIECHTENSTEIN,
        GreekGreece = SUBLANG_GREEK_GREECE,
        GreenlandicGreenland = SUBLANG_GREENLANDIC_GREENLAND,
        GujaratiIndia = SUBLANG_GUJARATI_INDIA,
        HausaNigeriaLatin = SUBLANG_HAUSA_NIGERIA_LATIN,
        HawaiianUs = SUBLANG_HAWAIIAN_US,
        HebrewIsrael = SUBLANG_HEBREW_ISRAEL,
        HindiIndia = SUBLANG_HINDI_INDIA,
        HungarianHungary = SUBLANG_HUNGARIAN_HUNGARY,
        IcelandicIceland = SUBLANG_ICELANDIC_ICELAND,
        IgboNigeria = SUBLANG_IGBO_NIGERIA,
        IndonesianIndonesia = SUBLANG_INDONESIAN_INDONESIA,
        InuktitutCanada = SUBLANG_INUKTITUT_CANADA,
        InuktitutCanadaLatin = SUBLANG_INUKTITUT_CANADA_LATIN,
        IrishIreland = SUBLANG_IRISH_IRELAND,
        Italian = SUBLANG_ITALIAN,
        ItalianSwiss = SUBLANG_ITALIAN_SWISS,
        JapaneseJapan = SUBLANG_JAPANESE_JAPAN,
        KannadaIndia = SUBLANG_KANNADA_INDIA,
        KashmiriSasia = SUBLANG_KASHMIRI_SASIA,
        KashmiriIndia = SUBLANG_KASHMIRI_INDIA,
        KazakKazakhstan = SUBLANG_KAZAK_KAZAKHSTAN,
        KhmerCambodia = SUBLANG_KHMER_CAMBODIA,
        KicheGuatemala = SUBLANG_KICHE_GUATEMALA,
        KinyarwandaRwanda = SUBLANG_KINYARWANDA_RWANDA,
        KonkaniIndia = SUBLANG_KONKANI_INDIA,
        Korean = SUBLANG_KOREAN,
        KyrgyzKyrgyzstan = SUBLANG_KYRGYZ_KYRGYZSTAN,
        LaoLao = SUBLANG_LAO_LAO,
        LatvianLatvia = SUBLANG_LATVIAN_LATVIA,
        Lithuanian = SUBLANG_LITHUANIAN,
        LowerSorbianGermany = SUBLANG_LOWER_SORBIAN_GERMANY,
        LuxembourgishLuxembourg = SUBLANG_LUXEMBOURGISH_LUXEMBOURG,
        MacedonianMacedonia = SUBLANG_MACEDONIAN_MACEDONIA,
        MalayMalaysia = SUBLANG_MALAY_MALAYSIA,
        MalayBruneiDarussalam = SUBLANG_MALAY_BRUNEI_DARUSSALAM,
        MalayalamIndia = SUBLANG_MALAYALAM_INDIA,
        MalteseMalta = SUBLANG_MALTESE_MALTA,
        MaoriNewZealand = SUBLANG_MAORI_NEW_ZEALAND,
        MapudungunChile = SUBLANG_MAPUDUNGUN_CHILE,
        MarathiIndia = SUBLANG_MARATHI_INDIA,
        MohawkMohawk = SUBLANG_MOHAWK_MOHAWK,
        MongolianCyrillicMongolia = SUBLANG_MONGOLIAN_CYRILLIC_MONGOLIA,
        MongolianPrc = SUBLANG_MONGOLIAN_PRC,
        NepaliIndia = SUBLANG_NEPALI_INDIA,
        NepaliNepal = SUBLANG_NEPALI_NEPAL,
        NorwegianBokmal = SUBLANG_NORWEGIAN_BOKMAL,
        NorwegianNynorsk = SUBLANG_NORWEGIAN_NYNORSK,
        OccitanFrance = SUBLANG_OCCITAN_FRANCE,
        OdiaIndia = SUBLANG_ODIA_INDIA,
        OriyaIndia = SUBLANG_ORIYA_INDIA,
        PashtoAfghanistan = SUBLANG_PASHTO_AFGHANISTAN,
        PersianIran = SUBLANG_PERSIAN_IRAN,
        PolishPoland = SUBLANG_POLISH_POLAND,
        Portuguese = SUBLANG_PORTUGUESE,
        PortugueseBrazilian = SUBLANG_PORTUGUESE_BRAZILIAN,
        PularSenegal = SUBLANG_PULAR_SENEGAL,
        PunjabiIndia = SUBLANG_PUNJABI_INDIA,
        PunjabiPakistan = SUBLANG_PUNJABI_PAKISTAN,
        QuechuaBolivia = SUBLANG_QUECHUA_BOLIVIA,
        QuechuaEcuador = SUBLANG_QUECHUA_ECUADOR,
        QuechuaPeru = SUBLANG_QUECHUA_PERU,
        RomanianRomania = SUBLANG_ROMANIAN_ROMANIA,
        RomanshSwitzerland = SUBLANG_ROMANSH_SWITZERLAND,
        RussianRussia = SUBLANG_RUSSIAN_RUSSIA,
        SakhaRussia = SUBLANG_SAKHA_RUSSIA,
        SamiNorthernNorway = SUBLANG_SAMI_NORTHERN_NORWAY,
        SamiNorthernSweden = SUBLANG_SAMI_NORTHERN_SWEDEN,
        SamiNorthernFinland = SUBLANG_SAMI_NORTHERN_FINLAND,
        SamiLuleNorway = SUBLANG_SAMI_LULE_NORWAY,
        SamiLuleSweden = SUBLANG_SAMI_LULE_SWEDEN,
        SamiSouthernNorway = SUBLANG_SAMI_SOUTHERN_NORWAY,
        SamiSouthernSweden = SUBLANG_SAMI_SOUTHERN_SWEDEN,
        SamiSkoltFinland = SUBLANG_SAMI_SKOLT_FINLAND,
        SamiInariFinland = SUBLANG_SAMI_INARI_FINLAND,
        SanskritIndia = SUBLANG_SANSKRIT_INDIA,
        ScottishGaelic = SUBLANG_SCOTTISH_GAELIC,
        SerbianBosniaHerzegovinaLatin =
                SUBLANG_SERBIAN_BOSNIA_HERZEGOVINA_LATIN,
        SerbianBosniaHerzegovinaCyrillic =
                SUBLANG_SERBIAN_BOSNIA_HERZEGOVINA_CYRILLIC,
        SerbianMontenegroLatin = SUBLANG_SERBIAN_MONTENEGRO_LATIN,
        SerbianMontenegroCyrillic = SUBLANG_SERBIAN_MONTENEGRO_CYRILLIC,
        SerbianSerbiaLatin = SUBLANG_SERBIAN_SERBIA_LATIN,
        SerbianSerbiaCyrillic = SUBLANG_SERBIAN_SERBIA_CYRILLIC,
        SerbianCroatia = SUBLANG_SERBIAN_CROATIA,
        SerbianLatin = SUBLANG_SERBIAN_LATIN,
        SerbianCyrillic = SUBLANG_SERBIAN_CYRILLIC,
        SindhiIndia = SUBLANG_SINDHI_INDIA,
        SindhiPakistan = SUBLANG_SINDHI_PAKISTAN,
        SindhiAfghanistan = SUBLANG_SINDHI_AFGHANISTAN,
        SinhaleseSriLanka = SUBLANG_SINHALESE_SRI_LANKA,
        SothoNorthernSouthAfrica = SUBLANG_SOTHO_NORTHERN_SOUTH_AFRICA,
        SlovakSlovakia = SUBLANG_SLOVAK_SLOVAKIA,
        SlovenianSlovenia = SUBLANG_SLOVENIAN_SLOVENIA,
        Spanish = SUBLANG_SPANISH,
        SpanishMexican = SUBLANG_SPANISH_MEXICAN,
        SpanishModern = SUBLANG_SPANISH_MODERN,
        SpanishGuatemala = SUBLANG_SPANISH_GUATEMALA,
        SpanishCostaRica = SUBLANG_SPANISH_COSTA_RICA,
        SpanishPanama = SUBLANG_SPANISH_PANAMA,
        SpanishDominicanRepublic = SUBLANG_SPANISH_DOMINICAN_REPUBLIC,
        SpanishVenezuela = SUBLANG_SPANISH_VENEZUELA,
        SpanishColombia = SUBLANG_SPANISH_COLOMBIA,
        SpanishPeru = SUBLANG_SPANISH_PERU,
        SpanishArgentina = SUBLANG_SPANISH_ARGENTINA,
        SpanishEcuador = SUBLANG_SPANISH_ECUADOR,
        SpanishChile = SUBLANG_SPANISH_CHILE,
        SpanishUruguay = SUBLANG_SPANISH_URUGUAY,
        SpanishParaguay = SUBLANG_SPANISH_PARAGUAY,
        SpanishBolivia = SUBLANG_SPANISH_BOLIVIA,
        SpanishElSalvador = SUBLANG_SPANISH_EL_SALVADOR,
        SpanishHonduras = SUBLANG_SPANISH_HONDURAS,
        SpanishNicaragua = SUBLANG_SPANISH_NICARAGUA,
        SpanishPuertoRico = SUBLANG_SPANISH_PUERTO_RICO,
        SpanishUs = SUBLANG_SPANISH_US,
        SwahiliKenya = SUBLANG_SWAHILI_KENYA,
        Swedish = SUBLANG_SWEDISH,
        SwedishFinland = SUBLANG_SWEDISH_FINLAND,
        SyriacSyria = SUBLANG_SYRIAC_SYRIA,
        TajikTajikistan = SUBLANG_TAJIK_TAJIKISTAN,
        TamazightAlgeriaLatin = SUBLANG_TAMAZIGHT_ALGERIA_LATIN,
        TamazightMoroccoTifinagh = SUBLANG_TAMAZIGHT_MOROCCO_TIFINAGH,
        TamilIndia = SUBLANG_TAMIL_INDIA,
        TamilSriLanka = SUBLANG_TAMIL_SRI_LANKA,
        TatarRussia = SUBLANG_TATAR_RUSSIA,
        TeluguIndia = SUBLANG_TELUGU_INDIA,
        ThaiThailand = SUBLANG_THAI_THAILAND,
        TibetanPrc = SUBLANG_TIBETAN_PRC,
        TigrignaEritrea = SUBLANG_TIGRIGNA_ERITREA,
        TigrinyaEritrea = SUBLANG_TIGRINYA_ERITREA,
        TigrinyaEthiopia = SUBLANG_TIGRINYA_ETHIOPIA,
        TswanaBotswana = SUBLANG_TSWANA_BOTSWANA,
        TswanaSouthAfrica = SUBLANG_TSWANA_SOUTH_AFRICA,
        TurkishTurkey = SUBLANG_TURKISH_TURKEY,
        TurkmenTurkmenistan = SUBLANG_TURKMEN_TURKMENISTAN,
        UighurPrc = SUBLANG_UIGHUR_PRC,
        UkrainianUkraine = SUBLANG_UKRAINIAN_UKRAINE,
        UpperSorbianGermany = SUBLANG_UPPER_SORBIAN_GERMANY,
        UrduPakistan = SUBLANG_URDU_PAKISTAN,
        UrduIndia = SUBLANG_URDU_INDIA,
        UzbekLatin = SUBLANG_UZBEK_LATIN,
        UzbekCyrillic = SUBLANG_UZBEK_CYRILLIC,
        ValencianValencia = SUBLANG_VALENCIAN_VALENCIA,
        VietnameseVietnam = SUBLANG_VIETNAMESE_VIETNAM,
        WelshUnitedKingdom = SUBLANG_WELSH_UNITED_KINGDOM,
        WolofSenegal = SUBLANG_WOLOF_SENEGAL,
        XhosaSouthAfrica = SUBLANG_XHOSA_SOUTH_AFRICA,
        YakutRussia = SUBLANG_YAKUT_RUSSIA,
        YiPrc = SUBLANG_YI_PRC,
        YorubaNigeria = SUBLANG_YORUBA_NIGERIA,
        ZuluSouthAfrica = SUBLANG_ZULU_SOUTH_AFRICA
    };

    enum class DPASearchOption : uint32_t {
        Sorted = DPAS_SORTED,
        InsertBefore = DPAS_INSERTBEFORE,
        InsertAfter = DPAS_INSERTAFTER,
    };

    inline DPASearchOption operator|(DPASearchOption a, DPASearchOption b) {
        return static_cast<DPASearchOption>(static_cast<uint32_t>(a) |
                                            static_cast<uint32_t>(b));
    }

    enum class DPAMergeOption : uint32_t {
        Sorted = DPAM_SORTED,
        Normal = DPAM_NORMAL,
        Union = DPAM_UNION,
        Intersect = DPAM_INTERSECT,
    };

    inline DPAMergeOption operator|(DPAMergeOption a, DPAMergeOption b) {
        return static_cast<DPAMergeOption>(static_cast<uint32_t>(a) |
                                           static_cast<uint32_t>(b));
    }

    enum class ReaderModeFlag : uint32_t {
        ZeroCursor = 1,
        VerticalOnly = 2,
        HorizontalOnly = 4,
    };

    inline ReaderModeFlag operator|(ReaderModeFlag a, ReaderModeFlag b) {
        return static_cast<ReaderModeFlag>(static_cast<uint32_t>(a) |
                                           static_cast<uint32_t>(b));
    }

    struct ReaderModeInfo;
    typedef int32_t(CALLBACK *ReaderScroll)(_In_ ReaderModeInfo *info,
                                            _In_ int32_t horiz,
                                            _In_ int32_t vert);
    typedef int32_t(CALLBACK *TranslateDispatch)(_In_ const MSG *msg);
    struct ReaderModeInfo {
        uint32_t size;
        HWND window_handle;
        uint32_t flag;
        RECT *rect;
        ReaderScroll scroll_callback;
        TranslateDispatch dispatch_callback;
        LPARAM lparam;
    };

    enum class NotifyFormatRet : int64_t {
        Error = 0,
        ANSI = NFR_ANSI,
        Unicode = NFR_UNICODE,
    };

    enum class GeneralMessage : uint32_t {
        DpiScale = CCM_DPISCALE,
        GetUnicodeFormat = CCM_GETUNICODEFORMAT,
        GetVersion = CCM_GETVERSION,
        SetUnicodeFormat = CCM_SETUNICODEFORMAT,
        SetVersion = CCM_SETVERSION,
        SetWindowTheme = CCM_SETWINDOWTHEME,
        Notify = WM_NOTIFY,
        NotifyFormat = WM_NOTIFYFORMAT,
    };

    enum class GeneralNotify : uint32_t {
        Char = NM_CHAR,
        CustomText = NM_CUSTOMTEXT,
        FontChanged = NM_FONTCHANGED,
        GetCustomSplitRect = NM_GETCUSTOMSPLITRECT,
        Hover = NM_HOVER,
        KeyDown = NM_KEYDOWN,
        KillFocus = NM_KILLFOCUS,
        LeftDown = NM_LDOWN,
        NcHitTest = NM_NCHITTEST,
        OutOfMemory = NM_OUTOFMEMORY,
        RightDown = NM_RDOWN,
        ReleasedCapture = NM_RELEASEDCAPTURE,
        Return = NM_RETURN,
        SetCursor = NM_SETCURSOR,
        SetFocus = NM_SETFOCUS,
        ThemeChanged = NM_THEMECHANGED,
        ToolTipsCreated = NM_TOOLTIPSCREATED,
        TVStateImageChanging = NM_TVSTATEIMAGECHANGING,
    };

    enum class HeaderStyle : uint32_t {
        Horiz = HDS_HORZ,
        Buttons = HDS_BUTTONS,
        HotTrack = HDS_HOTTRACK,
        Hidden = HDS_HIDDEN,
        DragDrop = HDS_DRAGDROP,
        FullDrag = HDS_FULLDRAG,
        FilterBar = HDS_FILTERBAR,
        Flat = HDS_FLAT,
        CheckBoxes = HDS_CHECKBOXES,
        NoSizing = HDS_NOSIZING,
        Overflow = HDS_OVERFLOW,
    };

    inline HeaderStyle operator|(HeaderStyle a, HeaderStyle b) {
        return static_cast<HeaderStyle>(static_cast<uint32_t>(a) |
                                        static_cast<uint32_t>(b));
    }

    enum class HeaderMessage : uint32_t {
        ClearFilter = HDM_CLEARFILTER,
        CreateDragImage = HDM_CREATEDRAGIMAGE,
        DeleteItem = HDM_DELETEITEM,
        EditFilter = HDM_EDITFILTER,
        GetBitmapMargin = HDM_GETBITMAPMARGIN,
        GetFocusedItem = HDM_GETFOCUSEDITEM,
        GetImageList = HDM_GETIMAGELIST,
        GetItem = HDM_GETITEM,
        GetItemCount = HDM_GETITEMCOUNT,
        GetItemDropDownRect = HDM_GETITEMDROPDOWNRECT,
        GetItemRect = HDM_GETITEMRECT,
        GetOrderArray = HDM_GETORDERARRAY,
        GetOverflowRect = HDM_GETOVERFLOWRECT,
        GetUnicodeFormat = HDM_GETUNICODEFORMAT,
        HitTest = HDM_HITTEST,
        InsertItem = HDM_INSERTITEM,
        Layout = HDM_LAYOUT,
        OrderToIndex = HDM_ORDERTOINDEX,
        SetBitmapMargin = HDM_SETBITMAPMARGIN,
        SetFilterChangeTimeout = HDM_SETFILTERCHANGETIMEOUT,
        SetFocusedItem = HDM_SETFOCUSEDITEM,
        SetHotDivider = HDM_SETHOTDIVIDER,
        SetImageList = HDM_SETIMAGELIST,
        SetItem = HDM_SETITEM,
        SetOrderArray = HDM_SETORDERARRAY,
        SetUnicodeFormat = HDM_SETUNICODEFORMAT,
    };

    enum class HeaderNotify : uint32_t {
        BeginDrag = HDN_BEGINDRAG,
        BeginFilterEdit = HDN_BEGINFILTEREDIT,
        BeginTrack = HDN_BEGINTRACK,
        DividerDblClick = HDN_DIVIDERDBLCLICK,
        DropDown = HDN_DROPDOWN,
        EndDrag = HDN_ENDDRAG,
        EndFilterEdit = HDN_ENDFILTEREDIT,
        FilterBtnClick = HDN_FILTERBTNCLICK,
        FilterChange = HDN_FILTERCHANGE,
        GetDispInfo = HDN_GETDISPINFO,
        ItemChanged = HDN_ITEMCHANGED,
        ItemChanging = HDN_ITEMCHANGING,
        ItemClick = HDN_ITEMCLICK,
        ItemDblClick = HDN_ITEMDBLCLICK,
        ItemKeyDown = HDN_ITEMKEYDOWN,
        ItemStateIconClick = HDN_ITEMSTATEICONCLICK,
        OverflowClick = HDN_OVERFLOWCLICK,
        Track = HDN_TRACK,
        CustomDraw = NM_CUSTOMDRAW,
        RightClick = NM_RCLICK,
        ReleasedCapture = NM_RELEASEDCAPTURE,
    };

    enum class HotKeyModifiersKey : uint8_t {
        None = 0,
        Alt = HOTKEYF_ALT,
        Control = HOTKEYF_CONTROL,
        Shift = HOTKEYF_SHIFT,
        Win = HOTKEYF_EXT,
    };

    inline HotKeyModifiersKey operator|(HotKeyModifiersKey a,
                                        HotKeyModifiersKey b) {
        return static_cast<HotKeyModifiersKey>(static_cast<uint8_t>(a) |
                                               static_cast<uint8_t>(b));
    }

    enum class HotKeyVirtualKey : uint8_t {
        None = 0,
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

    inline HotKeyVirtualKey operator|(HotKeyVirtualKey a, HotKeyVirtualKey b) {
        return static_cast<HotKeyVirtualKey>(static_cast<uint8_t>(a) |
                                             static_cast<uint8_t>(b));
    }

    enum class RuleFlag : uint32_t {
        None = HKCOMB_NONE,
        Shift = HKCOMB_S,
        Control = HKCOMB_C,
        Alt = HKCOMB_A,
        ShiftControl = HKCOMB_SC,
        ShiftAlt = HKCOMB_SA,
        ControlAlt = HKCOMB_CA,
        ShiftControlAlt = HKCOMB_SCA,
    };

    inline RuleFlag operator|(RuleFlag a, RuleFlag b) {
        return static_cast<RuleFlag>(static_cast<uint32_t>(a) |
                                     static_cast<uint32_t>(b));
    }

    enum class ILCreateFlag : uint32_t {
        Mask = ILC_MASK,
        Color = ILC_COLOR,
        ColorDdb = ILC_COLORDDB,
        Color4 = ILC_COLOR4,
        Color8 = ILC_COLOR8,
        Color16 = ILC_COLOR16,
        Color24 = ILC_COLOR24,
        Color32 = ILC_COLOR32,
        Palette = ILC_PALETTE,
        Mirror = ILC_MIRROR,
        PerItemMirror = ILC_PERITEMMIRROR,
        OriginalSize = ILC_ORIGINALSIZE,
        HighQualityScale = ILC_HIGHQUALITYSCALE,
    };

    inline ILCreateFlag operator|(ILCreateFlag a, ILCreateFlag b) {
        return static_cast<ILCreateFlag>(static_cast<uint32_t>(a) |
                                         static_cast<uint32_t>(b));
    }

    enum class ILDrawFlag : uint32_t {
        Normal = ILD_NORMAL,
        Transparent = ILD_TRANSPARENT,
        Mask = ILD_MASK,
        Image = ILD_IMAGE,
        Rop = ILD_ROP,
        Blend25 = ILD_BLEND25,
        Blend50 = ILD_BLEND50,
        OverlayMask = ILD_OVERLAYMASK,
        PreserveAlpha = ILD_PRESERVEALPHA,
        Scale = ILD_SCALE,
        DpiScale = ILD_DPISCALE,
        Async = ILD_ASYNC,
        Selected = ILD_SELECTED,
        Focus = ILD_FOCUS,
        Blend = ILD_BLEND,
    };

    inline ILDrawFlag operator|(ILDrawFlag a, ILDrawFlag b) {
        return static_cast<ILDrawFlag>(static_cast<uint32_t>(a) |
                                       static_cast<uint32_t>(b));
    }

    enum class IPAddrMessage : uint32_t {
        ClearAddress = IPM_CLEARADDRESS,
        GetAddress = IPM_GETADDRESS,
        IsBlank = IPM_ISBLANK,
        SetAddress = IPM_SETADDRESS,
        SetFocus = IPM_SETFOCUS,
        SetRange = IPM_SETRANGE,
    };

    enum class IPAddrNotify : uint32_t {
        FieldChanged = IPN_FIELDCHANGED,
    };

    enum class LabelStyle : uint32_t {
        Left = SS_LEFT,
        Center = SS_CENTER,
        Right = SS_RIGHT,
        Icon = SS_ICON,
        BlackRect = SS_BLACKRECT,
        GrayRect = SS_GRAYRECT,
        WhiteRect = SS_WHITERECT,
        BlackFrame = SS_BLACKFRAME,
        GrayFrame = SS_GRAYFRAME,
        WhiteFrame = SS_WHITEFRAME,
        UserItem = SS_USERITEM,
        Simple = SS_SIMPLE,
        LeftNoWordWrap = SS_LEFTNOWORDWRAP,
        OwnerDraw = SS_OWNERDRAW,
        Bitmap = SS_BITMAP,
        EnhMetaFile = SS_ENHMETAFILE,
        EtchedHorz = SS_ETCHEDHORZ,
        EtchedVert = SS_ETCHEDVERT,
        EtchedFrame = SS_ETCHEDFRAME,
        TypeMask = SS_TYPEMASK,
        RealSizeControl = SS_REALSIZECONTROL,
        NoPrefix = SS_NOPREFIX,
        Notify = SS_NOTIFY,
        CenterImage = SS_CENTERIMAGE,
        RightJust = SS_RIGHTJUST,
        RealSizeImage = SS_REALSIZEIMAGE,
        Sunken = SS_SUNKEN,
        EditControl = SS_EDITCONTROL,
        EndEllipsis = SS_ENDELLIPSIS,
        PathEllipsis = SS_PATHELLIPSIS,
        WordEllipsis = SS_WORDELLIPSIS,
        EllipsisMask = SS_ELLIPSISMASK
    };

    inline LabelStyle operator|(LabelStyle a, LabelStyle b) {
        return static_cast<LabelStyle>(static_cast<uint32_t>(a) |
                                       static_cast<uint32_t>(b));
    }

    enum class LabelMessage : uint32_t {
        GetIcon = STM_GETICON,
        GetImage = STM_GETIMAGE,
        SetIcon = STM_SETICON,
        SetImage = STM_SETIMAGE,
    };

    enum class LabelNotify : uint32_t {
        Clicked = STN_CLICKED,
        DoubleClick = STN_DBLCLK,
        Disable = STN_DISABLE,
        Enable = STN_ENABLE,
        CtlColorStatic = WM_CTLCOLORSTATIC,
    };

    enum class LinkStyle : uint32_t {
        Transparent = LWS_TRANSPARENT,
        IgnoreReturn = LWS_IGNORERETURN,
        NoPrefix = LWS_NOPREFIX,
        UseVisualStyle = LWS_USEVISUALSTYLE,
        UseCustomText = LWS_USECUSTOMTEXT,
        Right = LWS_RIGHT,
    };

    inline LinkStyle operator|(LinkStyle a, LinkStyle b) {
        return static_cast<LinkStyle>(static_cast<uint32_t>(a) |
                                      static_cast<uint32_t>(b));
    }

    enum class LinkMessage : uint32_t {
        GetIdealHeight = LM_GETIDEALHEIGHT,
        GetIdealSize = LM_GETIDEALSIZE,
        GetItem = LM_GETITEM,
        HitTest = LM_HITTEST,
        SetItem = LM_SETITEM,
    };

    enum class LinkNotify : uint32_t {
        Click = NM_CLICK,
    };

    enum class ListBoxStyle : uint32_t {
        Notify = LBS_NOTIFY,
        Sort = LBS_SORT,
        NoRedraw = LBS_NOREDRAW,
        MultipleSelect = LBS_MULTIPLESEL,
        OwnerDrawFixed = LBS_OWNERDRAWFIXED,
        OwnerDrawVariable = LBS_OWNERDRAWVARIABLE,
        HasStrings = LBS_HASSTRINGS,
        UseTabStops = LBS_USETABSTOPS,
        NoIntegralHeight = LBS_NOINTEGRALHEIGHT,
        MultiColumn = LBS_MULTICOLUMN,
        WantKeyboardInput = LBS_WANTKEYBOARDINPUT,
        ExtendedSelect = LBS_EXTENDEDSEL,
        DisableNoScroll = LBS_DISABLENOSCROLL,
        NoData = LBS_NODATA,
        NoSelect = LBS_NOSEL,
        ComboBox = LBS_COMBOBOX,
        Standard = LBS_STANDARD
    };

    inline ListBoxStyle operator|(ListBoxStyle a, ListBoxStyle b) {
        return static_cast<ListBoxStyle>(static_cast<uint32_t>(a) |
                                         static_cast<uint32_t>(b));
    }

    enum class ListFileType : uint32_t {
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

    inline ListFileType operator|(ListFileType a, ListFileType b) {
        return static_cast<ListFileType>(static_cast<uint32_t>(a) |
                                         static_cast<uint32_t>(b));
    }

    enum class ListBoxMessage : uint32_t {
        AddFile = LB_ADDFILE,
        AddString = LB_ADDSTRING,
        DeleteString = LB_DELETESTRING,
        Dir = LB_DIR,
        FindString = LB_FINDSTRING,
        FindStringExact = LB_FINDSTRINGEXACT,
        GetAnchorIndex = LB_GETANCHORINDEX,
        GetCaretIndex = LB_GETCARETINDEX,
        GetCount = LB_GETCOUNT,
        GetCurrentSelect = LB_GETCURSEL,
        GetHorizontalExtent = LB_GETHORIZONTALEXTENT,
        GetItemData = LB_GETITEMDATA,
        GetItemHeight = LB_GETITEMHEIGHT,
        GetItemRect = LB_GETITEMRECT,
        GetListBoxInfo = LB_GETLISTBOXINFO,
        GetLocale = LB_GETLOCALE,
        GetSelect = LB_GETSEL,
        GetSelCount = LB_GETSELCOUNT,
        GetSelItems = LB_GETSELITEMS,
        GetText = LB_GETTEXT,
        GetTextLen = LB_GETTEXTLEN,
        GetTopIndex = LB_GETTOPINDEX,
        InitStorage = LB_INITSTORAGE,
        InsertString = LB_INSERTSTRING,
        ItemFromPoint = LB_ITEMFROMPOINT,
        ResetContent = LB_RESETCONTENT,
        SelectString = LB_SELECTSTRING,
        SelItemRange = LB_SELITEMRANGE,
        SelItemRangeEx = LB_SELITEMRANGEEX,
        SetAnchorIndex = LB_SETANCHORINDEX,
        SetCaretIndex = LB_SETCARETINDEX,
        SetColumnWidth = LB_SETCOLUMNWIDTH,
        SetCount = LB_SETCOUNT,
        SetCurrentSelect = LB_SETCURSEL,
        SetHorizontalExtent = LB_SETHORIZONTALEXTENT,
        SetItemData = LB_SETITEMDATA,
        SetItemHeight = LB_SETITEMHEIGHT,
        SetLocale = LB_SETLOCALE,
        SetSelect = LB_SETSEL,
        SetTabStops = LB_SETTABSTOPS,
        SetTopIndex = LB_SETTOPINDEX
    };

    enum class ListBoxNotify : int32_t {
        BeginDrag = DL_BEGINDRAG,
        CancelDrag = DL_CANCELDRAG,
        Dragging = DL_DRAGGING,
        Dropped = DL_DROPPED,
        DoubleClick = LBN_DBLCLK,
        ErrSpace = LBN_ERRSPACE,
        KillFocus = LBN_KILLFOCUS,
        SelectCancel = LBN_SELCANCEL,
        SelectChange = LBN_SELCHANGE,
        SetFocus = LBN_SETFOCUS,
        CharToItem = WM_CHARTOITEM,
        CtlColorListBox = WM_CTLCOLORLISTBOX,
        DeleteItem = WM_DELETEITEM,
        VKeyToItem = WM_VKEYTOITEM
    };

    enum class ListViewStyle : uint32_t {
        Icon = LVS_ICON,
        Report = LVS_REPORT,
        SmallIcon = LVS_SMALLICON,
        List = LVS_LIST,
        TypeMask = LVS_TYPEMASK,
        SingleSel = LVS_SINGLESEL,
        ShowSelAlways = LVS_SHOWSELALWAYS,
        SortAscending = LVS_SORTASCENDING,
        SortDescending = LVS_SORTDESCENDING,
        ShareImageLists = LVS_SHAREIMAGELISTS,
        NoLabelWrap = LVS_NOLABELWRAP,
        AutoArrange = LVS_AUTOARRANGE,
        EditLabels = LVS_EDITLABELS,
        OwnerData = LVS_OWNERDATA,
        NoScroll = LVS_NOSCROLL,
        TypeStyleMask = LVS_TYPESTYLEMASK,
        AlignTop = LVS_ALIGNTOP,
        AlignLeft = LVS_ALIGNLEFT,
        AlignMask = LVS_ALIGNMASK,
        OwnerDrawFixed = LVS_OWNERDRAWFIXED,
        NoColumnHeader = LVS_NOCOLUMNHEADER,
        NoSortHeader = LVS_NOSORTHEADER
    };

    inline ListViewStyle operator|(ListViewStyle a, ListViewStyle b) {
        return static_cast<ListViewStyle>(static_cast<uint32_t>(a) |
                                          static_cast<uint32_t>(b));
    }

    enum class ListViewExtendStyle : uint32_t {
        GridLines = LVS_EX_GRIDLINES,
        SubItemImages = LVS_EX_SUBITEMIMAGES,
        CheckBoxes = LVS_EX_CHECKBOXES,
        TrackSelect = LVS_EX_TRACKSELECT,
        HeaderDragDrop = LVS_EX_HEADERDRAGDROP,
        FullRowSelect = LVS_EX_FULLROWSELECT,
        OneClickActivate = LVS_EX_ONECLICKACTIVATE,
        TwoClickActivate = LVS_EX_TWOCLICKACTIVATE,
        FlatScrollBar = LVS_EX_FLATSB,
        Regional = LVS_EX_REGIONAL,
        InfoTip = LVS_EX_INFOTIP,
        UnderlineHot = LVS_EX_UNDERLINEHOT,
        UnderlineCold = LVS_EX_UNDERLINECOLD,
        MultiWorkAreas = LVS_EX_MULTIWORKAREAS,
        LabelTip = LVS_EX_LABELTIP,
        BorderSelect = LVS_EX_BORDERSELECT,
        DoubleBuffer = LVS_EX_DOUBLEBUFFER,
        HideLabels = LVS_EX_HIDELABELS,
        SingleRow = LVS_EX_SINGLEROW,
        SnapToGrid = LVS_EX_SNAPTOGRID,
        SimpleSelect = LVS_EX_SIMPLESELECT,
        JustifyColumns = LVS_EX_JUSTIFYCOLUMNS,
        TransparentBackground = LVS_EX_TRANSPARENTBKGND,
        TransparentShadowText = LVS_EX_TRANSPARENTSHADOWTEXT,
        AutoAutoArrange = LVS_EX_AUTOAUTOARRANGE,
        HeaderInAllViews = LVS_EX_HEADERINALLVIEWS,
        AutoCheckSelect = LVS_EX_AUTOCHECKSELECT,
        AutoSizeColumns = LVS_EX_AUTOSIZECOLUMNS,
        ColumnSnapPoints = LVS_EX_COLUMNSNAPPOINTS,
        ColumnOverflow = LVS_EX_COLUMNOVERFLOW
    };

    inline ListViewExtendStyle operator|(ListViewExtendStyle a,
                                         ListViewExtendStyle b) {
        return static_cast<ListViewExtendStyle>(static_cast<uint32_t>(a) |
                                                static_cast<uint32_t>(b));
    }

    enum class LVAlignStyle : uint32_t {
        Default = LVA_DEFAULT,
        Left = LVA_ALIGNLEFT,
        Top = LVA_ALIGNTOP,
        SnapToGrid = LVA_SNAPTOGRID,
    };

    enum class LVItemState : uint32_t {
        Focused = LVIS_FOCUSED,
        Selected = LVIS_SELECTED,
        Cut = LVIS_CUT,
        DropHilited = LVIS_DROPHILITED,
        Glow = LVIS_GLOW,
        Activating = LVIS_ACTIVATING,
        OverlayMask = LVIS_OVERLAYMASK,
        StateImageMask = LVIS_STATEIMAGEMASK,
    };

    inline LVItemState operator|(LVItemState a, LVItemState b) {
        return static_cast<LVItemState>(static_cast<uint32_t>(a) |
                                        static_cast<uint32_t>(b));
    }

    enum class GroupRectType : uint32_t {
        Group = LVGGR_GROUP,
        Header = LVGGR_HEADER,
        Label = LVGGR_LABEL,
        SubSetLink = LVGGR_SUBSETLINK,
    };

    enum class GroupState : uint32_t {
        Normal = LVGS_NORMAL,
        Collapsed = LVGS_COLLAPSED,
        Hidden = LVGS_HIDDEN,
        NoHeader = LVGS_NOHEADER,
        Collapsible = LVGS_COLLAPSIBLE,
        Focused = LVGS_FOCUSED,
        Selected = LVGS_SELECTED,
        Subseted = LVGS_SUBSETED,
        SubsetLinkFocused = LVGS_SUBSETLINKFOCUSED,
    };

    inline GroupState operator|(GroupState a, GroupState b) {
        return static_cast<GroupState>(static_cast<uint32_t>(a) |
                                       static_cast<uint32_t>(b));
    }

    enum class LVILStyle : int32_t {
        Normal = LVSIL_NORMAL,
        Small = LVSIL_SMALL,
        State = LVSIL_STATE,
        GroupHeader = LVSIL_GROUPHEADER,
    };

    enum class LVICFlag : uint32_t {
        NoInvalidateAll = LVSICF_NOINVALIDATEALL,
        NoScroll = LVSICF_NOSCROLL,
    };

    inline LVICFlag operator|(LVICFlag a, LVICFlag b) {
        return static_cast<LVICFlag>(static_cast<uint32_t>(a) |
                                     static_cast<uint32_t>(b));
    }

    enum class LVIRCode : int32_t {
        Bounds = LVIR_BOUNDS,
        Icon = LVIR_ICON,
        Label = LVIR_LABEL,
        SelectBounds = LVIR_SELECTBOUNDS,
    };

    enum class LVNIFlag : uint32_t {
        All = LVNI_ALL,
        Focused = LVNI_FOCUSED,
        Selected = LVNI_SELECTED,
        Cut = LVNI_CUT,
        DropHilited = LVNI_DROPHILITED,
        StateMask = LVNI_STATEMASK,
        VisibleOrder = LVNI_VISIBLEORDER,
        Previous = LVNI_PREVIOUS,
        VisibleOnly = LVNI_VISIBLEONLY,
        SameGroupOnly = LVNI_SAMEGROUPONLY,
        Above = LVNI_ABOVE,
        Below = LVNI_BELOW,
        ToLeft = LVNI_TOLEFT,
        ToRight = LVNI_TORIGHT,
        DirectionMask = LVNI_DIRECTIONMASK,
    };

    inline LVNIFlag operator|(LVNIFlag a, LVNIFlag b) {
        return static_cast<LVNIFlag>(static_cast<uint32_t>(a) |
                                     static_cast<uint32_t>(b));
    }

    enum class ListViewMessage : uint32_t {
        ApproximateViewRect = LVM_APPROXIMATEVIEWRECT,
        Arrange = LVM_ARRANGE,
        CancelEditLabel = LVM_CANCELEDITLABEL,
        CreateDragImage = LVM_CREATEDRAGIMAGE,
        DeleteAllItems = LVM_DELETEALLITEMS,
        DeleteColumn = LVM_DELETECOLUMN,
        DeleteItem = LVM_DELETEITEM,
        EditLabel = LVM_EDITLABEL,
        EnableGroupView = LVM_ENABLEGROUPVIEW,
        EnsureVisible = LVM_ENSUREVISIBLE,
        FindItem = LVM_FINDITEM,
        GetBackgroundColor = LVM_GETBKCOLOR,
        GetBackgroundImage = LVM_GETBKIMAGE,
        GetCallbackMask = LVM_GETCALLBACKMASK,
        GetColumn = LVM_GETCOLUMN,
        GetColumnOrderArray = LVM_GETCOLUMNORDERARRAY,
        GetColumnWidth = LVM_GETCOLUMNWIDTH,
        GetCountPerPage = LVM_GETCOUNTPERPAGE,
        GetEditControl = LVM_GETEDITCONTROL,
        GetEmptyText = LVM_GETEMPTYTEXT,
        GetExtendedListViewStyle = LVM_GETEXTENDEDLISTVIEWSTYLE,
        GetFocusedGroup = LVM_GETFOCUSEDGROUP,
        GetFooterInfo = LVM_GETFOOTERINFO,
        GetFooterItem = LVM_GETFOOTERITEM,
        GetFooterItemRect = LVM_GETFOOTERITEMRECT,
        GetFooterRect = LVM_GETFOOTERRECT,
        GetGroupCount = LVM_GETGROUPCOUNT,
        GetGroupInfo = LVM_GETGROUPINFO,
        GetGroupInfoByIndex = LVM_GETGROUPINFOBYINDEX,
        GetGroupMetrics = LVM_GETGROUPMETRICS,
        GetGroupRect = LVM_GETGROUPRECT,
        GetGroupState = LVM_GETGROUPSTATE,
        GetHeader = LVM_GETHEADER,
        GetHotCursor = LVM_GETHOTCURSOR,
        GetHotItem = LVM_GETHOTITEM,
        GetHoverTime = LVM_GETHOVERTIME,
        GetImageList = LVM_GETIMAGELIST,
        GetInsertMark = LVM_GETINSERTMARK,
        GetInsertMarkColor = LVM_GETINSERTMARKCOLOR,
        GetInsertMarkRect = LVM_GETINSERTMARKRECT,
        GetISearchString = LVM_GETISEARCHSTRING,
        GetItem = LVM_GETITEM,
        GetItemCount = LVM_GETITEMCOUNT,
        GetItemIndexRect = LVM_GETITEMINDEXRECT,
        GetItemPosition = LVM_GETITEMPOSITION,
        GetItemRect = LVM_GETITEMRECT,
        GetItemSpacing = LVM_GETITEMSPACING,
        GetItemState = LVM_GETITEMSTATE,
        GetItemText = LVM_GETITEMTEXT,
        GetNextItem = LVM_GETNEXTITEM,
        GetNextItemIndex = LVM_GETNEXTITEMINDEX,
        GetNumberOfWorkAreas = LVM_GETNUMBEROFWORKAREAS,
        GetOrigin = LVM_GETORIGIN,
        GetOutlineColor = LVM_GETOUTLINECOLOR,
        GetSelectedColumn = LVM_GETSELECTEDCOLUMN,
        GetSelectedCount = LVM_GETSELECTEDCOUNT,
        GetSelectionMark = LVM_GETSELECTIONMARK,
        GetStringWidth = LVM_GETSTRINGWIDTH,
        GetSubItemRect = LVM_GETSUBITEMRECT,
        GetTextBackgroundColor = LVM_GETTEXTBKCOLOR,
        GetTextColor = LVM_GETTEXTCOLOR,
        GetTileInfo = LVM_GETTILEINFO,
        GetTileViewInfo = LVM_GETTILEVIEWINFO,
        GetToolTips = LVM_GETTOOLTIPS,
        GetTopIndex = LVM_GETTOPINDEX,
        GetUnicodeFormat = LVM_GETUNICODEFORMAT,
        GetView = LVM_GETVIEW,
        GetViewRect = LVM_GETVIEWRECT,
        GetWorkAreas = LVM_GETWORKAREAS,
        HasGroup = LVM_HASGROUP,
        HitTest = LVM_HITTEST,
        InsertColumn = LVM_INSERTCOLUMN,
        InsertGroup = LVM_INSERTGROUP,
        InsertGroupSorted = LVM_INSERTGROUPSORTED,
        InsertItem = LVM_INSERTITEM,
        InsertMarkHitTest = LVM_INSERTMARKHITTEST,
        IsGroupViewEnabled = LVM_ISGROUPVIEWENABLED,
        IsItemVisible = LVM_ISITEMVISIBLE,
        MapIdToIndex = LVM_MAPIDTOINDEX,
        MapIndexToId = LVM_MAPINDEXTOID,
        MoveGroup = LVM_MOVEGROUP,
        MoveItemToGroup = LVM_MOVEITEMTOGROUP,
        RedrawItems = LVM_REDRAWITEMS,
        RemoveAllGroups = LVM_REMOVEALLGROUPS,
        RemoveGroup = LVM_REMOVEGROUP,
        Scroll = LVM_SCROLL,
        SetBackgroundColor = LVM_SETBKCOLOR,
        SetBackgroundImage = LVM_SETBKIMAGE,
        SetCallbackMask = LVM_SETCALLBACKMASK,
        SetColumn = LVM_SETCOLUMN,
        SetColumnOrderArray = LVM_SETCOLUMNORDERARRAY,
        SetColumnWidth = LVM_SETCOLUMNWIDTH,
        SetExtendedListViewStyle = LVM_SETEXTENDEDLISTVIEWSTYLE,
        SetGroupInfo = LVM_SETGROUPINFO,
        SetGroupMetrics = LVM_SETGROUPMETRICS,
        SetHotCursor = LVM_SETHOTCURSOR,
        SetHotItem = LVM_SETHOTITEM,
        SetHoverTime = LVM_SETHOVERTIME,
        SetIconSpacing = LVM_SETICONSPACING,
        SetImageList = LVM_SETIMAGELIST,
        SetInfoTip = LVM_SETINFOTIP,
        SetInsertMark = LVM_SETINSERTMARK,
        SetInsertMarkColor = LVM_SETINSERTMARKCOLOR,
        SetItem = LVM_SETITEM,
        SetItemCount = LVM_SETITEMCOUNT,
        SetItemIndexState = LVM_SETITEMINDEXSTATE,
        SetItemPosition = LVM_SETITEMPOSITION,
        SetItemPosition32 = LVM_SETITEMPOSITION32,
        SetItemState = LVM_SETITEMSTATE,
        SetItemText = LVM_SETITEMTEXT,
        SetOutlineColor = LVM_SETOUTLINECOLOR,
        SetSelectedColumn = LVM_SETSELECTEDCOLUMN,
        SetSelectionMark = LVM_SETSELECTIONMARK,
        SetTextBackgroundColor = LVM_SETTEXTBKCOLOR,
        SetTextColor = LVM_SETTEXTCOLOR,
        SetTileInfo = LVM_SETTILEINFO,
        SetTileViewInfo = LVM_SETTILEVIEWINFO,
        SetToolTips = LVM_SETTOOLTIPS,
        SetUnicodeFormat = LVM_SETUNICODEFORMAT,
        SetView = LVM_SETVIEW,
        SetWorkAreas = LVM_SETWORKAREAS,
        SortGroups = LVM_SORTGROUPS,
        SortItems = LVM_SORTITEMS,
        SortItemsEx = LVM_SORTITEMSEX,
        SubItemHitTest = LVM_SUBITEMHITTEST,
        Update = LVM_UPDATE
    };

    enum class ListViewNotify : uint32_t {
        BeginDrag = LVN_BEGINDRAG,
        BeginLabelEdit = LVN_BEGINLABELEDIT,
        BeginRightDrag = LVN_BEGINRDRAG,
        BeginScroll = LVN_BEGINSCROLL,
        ColumnClick = LVN_COLUMNCLICK,
        ColumnDropDown = LVN_COLUMNDROPDOWN,
        ColumnOverflowClick = LVN_COLUMNOVERFLOWCLICK,
        DeleteAllItems = LVN_DELETEALLITEMS,
        DeleteItem = LVN_DELETEITEM,
        EndLabelEdit = LVN_ENDLABELEDIT,
        EndScroll = LVN_ENDSCROLL,
        GetDispInfo = LVN_GETDISPINFO,
        GetEmptyMarkup = LVN_GETEMPTYMARKUP,
        GetInfoTip = LVN_GETINFOTIP,
        HotTrack = LVN_HOTTRACK,
        IncrementalSearch = LVN_INCREMENTALSEARCH,
        InsertItem = LVN_INSERTITEM,
        ItemActivate = LVN_ITEMACTIVATE,
        ItemChanged = LVN_ITEMCHANGED,
        ItemChanging = LVN_ITEMCHANGING,
        KeyDown = LVN_KEYDOWN,
        LinkClick = LVN_LINKCLICK,
        MarqueeBegin = LVN_MARQUEEBEGIN,
        OdCacheHint = LVN_ODCACHEHINT,
        OdFindItem = LVN_ODFINDITEM,
        OdStateChanged = LVN_ODSTATECHANGED,
        SetDispInfo = LVN_SETDISPINFO,
        Click = NM_CLICK,
        CustomDraw = NM_CUSTOMDRAW,
        DoubleClick = NM_DBLCLK,
        Hover = NM_HOVER,
        KillFocus = NM_KILLFOCUS,
        RightClick = NM_RCLICK,
        RightDoubleClick = NM_RDBLCLK,
        ReleasedCapture = NM_RELEASEDCAPTURE,
        Return = NM_RETURN,
        SetFocus = NM_SETFOCUS
    };

    enum class PageStyle : uint32_t {
        Vertical = PGS_VERT,
        Horizontal = PGS_HORZ,
        AutoScroll = PGS_AUTOSCROLL,
        DragnDrop = PGS_DRAGNDROP,
    };

    inline PageStyle operator|(PageStyle a, PageStyle b) {
        return static_cast<PageStyle>(static_cast<uint32_t>(a) |
                                      static_cast<uint32_t>(b));
    }

    enum class PageButtonIndex : uint32_t {
        TopOrLeft = PGB_TOPORLEFT,
        BottomOrRight = PGB_BOTTOMORRIGHT,
    };

    enum class PageButtonState : uint32_t {
        Invisible = PGF_INVISIBLE,
        Normal = PGF_NORMAL,
        Grayed = PGF_GRAYED,
        Depressed = PGF_DEPRESSED,
        Hot = PGF_HOT,
    };

    inline PageButtonState operator|(PageButtonState a, PageButtonState b) {
        return static_cast<PageButtonState>(static_cast<uint32_t>(a) |
                                            static_cast<uint32_t>(b));
    }

    enum class PageMessage : uint32_t {
        ForwardMouse = PGM_FORWARDMOUSE,
        GetBackgroundColor = PGM_GETBKCOLOR,
        GetBorder = PGM_GETBORDER,
        GetButtonSize = PGM_GETBUTTONSIZE,
        GetButtonState = PGM_GETBUTTONSTATE,
        GetDropTarget = PGM_GETDROPTARGET,
        GetPos = PGM_GETPOS,
        RecalcSize = PGM_RECALCSIZE,
        SetBackgroundColor = PGM_SETBKCOLOR,
        SetBorder = PGM_SETBORDER,
        SetButtonSize = PGM_SETBUTTONSIZE,
        SetChild = PGM_SETCHILD,
        SetPos = PGM_SETPOS,
        SetScrollInfo = PGM_SETSCROLLINFO
    };

    enum class PageNotify : uint32_t {
        ReleasedCapture = NM_RELEASEDCAPTURE,
        CalcSize = PGN_CALCSIZE,
        HotItemChange = PGN_HOTITEMCHANGE,
        Scroll = PGN_SCROLL,
    };

    enum class ProgressStyle : uint32_t {
        Marquee = PBS_MARQUEE,
        Smooth = PBS_SMOOTH,
        SmoothReverse = PBS_SMOOTHREVERSE,
        Vertical = PBS_VERTICAL,
    };

    inline ProgressStyle operator|(ProgressStyle a, ProgressStyle b) {
        return static_cast<ProgressStyle>(static_cast<uint32_t>(a) |
                                          static_cast<uint32_t>(b));
    }

    enum class ProgressState : uint32_t {
        Normal = PBST_NORMAL,
        Error = PBST_ERROR,
        Paused = PBST_PAUSED,
    };

    enum class ProgressMessage : uint32_t {
        DeltaPos = PBM_DELTAPOS,
        GetBarColor = PBM_GETBARCOLOR,
        GetBackgroundColor = PBM_GETBKCOLOR,
        GetPos = PBM_GETPOS,
        GetRange = PBM_GETRANGE,
        GetState = PBM_GETSTATE,
        GetStep = PBM_GETSTEP,
        SetBarColor = PBM_SETBARCOLOR,
        SetBackgroundColor = PBM_SETBKCOLOR,
        SetMarquee = PBM_SETMARQUEE,
        SetPos = PBM_SETPOS,
        SetRange = PBM_SETRANGE,
        SetRange32 = PBM_SETRANGE32,
        SetState = PBM_SETSTATE,
        SetStep = PBM_SETSTEP,
        StepIt = PBM_STEPIT
    };

    enum class PropertyHeaderFlag : uint32_t {
        Default = PSH_DEFAULT,
        PropTitle = PSH_PROPTITLE,
        UseHIcon = PSH_USEHICON,
        UseIconId = PSH_USEICONID,
        PropSheetPage = PSH_PROPSHEETPAGE,
        WizardHasFinish = PSH_WIZARDHASFINISH,
        Wizard = PSH_WIZARD,
        UsePStartPage = PSH_USEPSTARTPAGE,
        NoApplyNow = PSH_NOAPPLYNOW,
        UseCallback = PSH_USECALLBACK,
        HasHelp = PSH_HASHELP,
        Modeless = PSH_MODELESS,
        RtlReading = PSH_RTLREADING,
        WizardContextHelp = PSH_WIZARDCONTEXTHELP,
        Wizard97 = PSH_WIZARD97,
        Watermark = PSH_WATERMARK,
        UseHbmWatermark = PSH_USEHBMWATERMARK,
        UseHplWatermark = PSH_USEHPLWATERMARK,
        StretchWatermark = PSH_STRETCHWATERMARK,
        Header = PSH_HEADER,
        UseHbmHeader = PSH_USEHBMHEADER,
        UsePageLang = PSH_USEPAGELANG,
        WizardLite = PSH_WIZARD_LITE,
        NoContextHelp = PSH_NOCONTEXTHELP,
        AeroWizard = PSH_AEROWIZARD,
        Resizable = PSH_RESIZABLE,
        HeaderBitmap = PSH_HEADERBITMAP,
        NoMargin = PSH_NOMARGIN
    };

    inline PropertyHeaderFlag operator|(PropertyHeaderFlag a,
                                        PropertyHeaderFlag b) {
        return static_cast<PropertyHeaderFlag>(static_cast<uint32_t>(a) |
                                               static_cast<uint32_t>(b));
    }

    enum class PropertyPageFlag : uint32_t {
        Default = PSP_DEFAULT,
        DialogInDirect = PSP_DLGINDIRECT,
        UseHIcon = PSP_USEHICON,
        UseIconId = PSP_USEICONID,
        UseTitle = PSP_USETITLE,
        RtlReading = PSP_RTLREADING,
        HasHelp = PSP_HASHELP,
        UseRefParent = PSP_USEREFPARENT,
        UseCallback = PSP_USECALLBACK,
        Premature = PSP_PREMATURE,
        HideHeader = PSP_HIDEHEADER,
        UseHeaderTitle = PSP_USEHEADERTITLE,
        UseHeaderSubTitle = PSP_USEHEADERSUBTITLE,
        UseFusionContext = PSP_USEFUSIONCONTEXT,
    };

    inline PropertyPageFlag operator|(PropertyPageFlag a, PropertyPageFlag b) {
        return static_cast<PropertyPageFlag>(static_cast<uint32_t>(a) |
                                             static_cast<uint32_t>(b));
    }

    enum class PropertyButton : uint32_t {
        Back = PSWIZB_BACK,
        Next = PSWIZB_NEXT,
        Finish = PSWIZB_FINISH,
        Cancel = PSWIZB_CANCEL,
        Show = PSWIZB_SHOW,
        Restore = PSWIZB_RESTORE,
        DisabledFinish = PSWIZB_DISABLEDFINISH,
    };

    inline PropertyButton operator|(PropertyButton a, PropertyButton b) {
        return static_cast<PropertyButton>(static_cast<uint32_t>(a) |
                                           static_cast<uint32_t>(b));
    }

    enum class PropertyMessage : uint32_t {
        AddPage = PSM_ADDPAGE,
        Apply = PSM_APPLY,
        CancelToClose = PSM_CANCELTOCLOSE,
        Changed = PSM_CHANGED,
        EnableWizButtons = PSM_ENABLEWIZBUTTONS,
        GetCurrentPageHwnd = PSM_GETCURRENTPAGEHWND,
        GetResult = PSM_GETRESULT,
        GetTabControl = PSM_GETTABCONTROL,
        HwndToIndex = PSM_HWNDTOINDEX,
        IdToIndex = PSM_IDTOINDEX,
        IndexToHwnd = PSM_INDEXTOHWND,
        IndexToId = PSM_INDEXTOID,
        IndexToPage = PSM_INDEXTOPAGE,
        InsertPage = PSM_INSERTPAGE,
        IsDialogMsg = PSM_ISDIALOGMESSAGE,
        PageToIndex = PSM_PAGETOINDEX,
        PressButton = PSM_PRESSBUTTON,
        QuerySiblings = PSM_QUERYSIBLINGS,
        RebootSystem = PSM_REBOOTSYSTEM,
        RecalcPageSizes = PSM_RECALCPAGESIZES,
        RemovePage = PSM_REMOVEPAGE,
        RestartWindows = PSM_RESTARTWINDOWS,
        SetButtonText = PSM_SETBUTTONTEXT,
        SetCurrentSelect = PSM_SETCURSEL,
        SetCurrentSelectId = PSM_SETCURSELID,
        SetFinishText = PSM_SETFINISHTEXT,
        SetHeaderSubtitle = PSM_SETHEADERSUBTITLE,
        SetHeaderTitle = PSM_SETHEADERTITLE,
        SetNextText = PSM_SETNEXTTEXT,
        SetTitle = PSM_SETTITLE,
        SetWizButtons = PSM_SETWIZBUTTONS,
        ShowWizButtons = PSM_SHOWWIZBUTTONS,
        Unchanged = PSM_UNCHANGED
    };

    enum class PropertyNotify : uint32_t {
        Apply = PSN_APPLY,
        GetObj = PSN_GETOBJECT,
        Help = PSN_HELP,
        KillActive = PSN_KILLACTIVE,
        QueryCancel = PSN_QUERYCANCEL,
        QueryInitialFocus = PSN_QUERYINITIALFOCUS,
        Reset = PSN_RESET,
        SetActive = PSN_SETACTIVE,
        TranslateAccel = PSN_TRANSLATEACCELERATOR,
        WizBack = PSN_WIZBACK,
        WizFinish = PSN_WIZFINISH,
        WizNext = PSN_WIZNEXT,
    };

    enum class RebarStyle : uint32_t {
        ToolTips = RBS_TOOLTIPS,
        VarHeight = RBS_VARHEIGHT,
        BandBorders = RBS_BANDBORDERS,
        FixedOrder = RBS_FIXEDORDER,
        RegisterDrop = RBS_REGISTERDROP,
        AutoSize = RBS_AUTOSIZE,
        VerticalGripper = RBS_VERTICALGRIPPER,
        DoubleClickToggle = RBS_DBLCLKTOGGLE,
    };

    inline RebarStyle operator|(RebarStyle a, RebarStyle b) {
        return static_cast<RebarStyle>(static_cast<uint32_t>(a) |
                                       static_cast<uint32_t>(b));
    }

    inline RebarStyle operator|(RebarStyle a, CommonStyle b) {
        return static_cast<RebarStyle>(static_cast<uint32_t>(a) |
                                       static_cast<uint32_t>(b));
    }

    inline RebarStyle operator|(CommonStyle a, RebarStyle b) {
        return static_cast<RebarStyle>(static_cast<uint32_t>(a) |
                                       static_cast<uint32_t>(b));
    }

    enum class RebarMessage : uint32_t {
        BeginDrag = RB_BEGINDRAG,
        DeleteBand = RB_DELETEBAND,
        DragMove = RB_DRAGMOVE,
        EndDrag = RB_ENDDRAG,
        GetBandBorders = RB_GETBANDBORDERS,
        GetBandCount = RB_GETBANDCOUNT,
        GetBandInfo = RB_GETBANDINFO,
        GetBandMargins = RB_GETBANDMARGINS,
        GetBarHeight = RB_GETBARHEIGHT,
        GetBarInfo = RB_GETBARINFO,
        GetBackgroundColor = RB_GETBKCOLOR,
        GetColorScheme = RB_GETCOLORSCHEME,
        GetDropTarget = RB_GETDROPTARGET,
        GetExtendedStyle = RB_GETEXTENDEDSTYLE,
        GetPalette = RB_GETPALETTE,
        GetRect = RB_GETRECT,
        GetRowCount = RB_GETROWCOUNT,
        GetRowHeight = RB_GETROWHEIGHT,
        GetTextColor = RB_GETTEXTCOLOR,
        GetToolTips = RB_GETTOOLTIPS,
        GetUnicodeFormat = RB_GETUNICODEFORMAT,
        HitTest = RB_HITTEST,
        IdToIndex = RB_IDTOINDEX,
        InsertBand = RB_INSERTBAND,
        MaximizeBand = RB_MAXIMIZEBAND,
        MinimizeBand = RB_MINIMIZEBAND,
        MoveBand = RB_MOVEBAND,
        PushChevron = RB_PUSHCHEVRON,
        SetBandInfo = RB_SETBANDINFO,
        SetBandWidth = RB_SETBANDWIDTH,
        SetBarInfo = RB_SETBARINFO,
        SetBackgroundColor = RB_SETBKCOLOR,
        SetColorScheme = RB_SETCOLORSCHEME,
        SetExtendedStyle = RB_SETEXTENDEDSTYLE,
        SetPalette = RB_SETPALETTE,
        SetParent = RB_SETPARENT,
        SetTextColor = RB_SETTEXTCOLOR,
        SetToolTips = RB_SETTOOLTIPS,
        SetUnicodeFormat = RB_SETUNICODEFORMAT,
        SetWindowTheme = RB_SETWINDOWTHEME,
        ShowBand = RB_SHOWBAND,
        SizeToRect = RB_SIZETORECT
    };

    enum class RebarNotify : uint32_t {
        CustomDraw = NM_CUSTOMDRAW,
        NcHitTest = NM_NCHITTEST,
        ReleasedCapture = NM_RELEASEDCAPTURE,
        AutoBreak = RBN_AUTOBREAK,
        AutoSize = RBN_AUTOSIZE,
        BeginDrag = RBN_BEGINDRAG,
        ChevronPushed = RBN_CHEVRONPUSHED,
        ChildSize = RBN_CHILDSIZE,
        DeletedBand = RBN_DELETEDBAND,
        DeletingBand = RBN_DELETINGBAND,
        EndDrag = RBN_ENDDRAG,
        GetObj = RBN_GETOBJECT,
        HeightChange = RBN_HEIGHTCHANGE,
        LayoutChanged = RBN_LAYOUTCHANGED,
        MinMax = RBN_MINMAX,
        SplitterDrag = RBN_SPLITTERDRAG
    };

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

    enum class REAutoUrlDetect : uint32_t {
        DisableUrl = 0,
        EnableUrl = AURL_ENABLEURL,
        EnableEmailAddr = AURL_ENABLEEMAILADDR,
        EnableTelNo = AURL_ENABLETELNO,
        EnableEAUrls = AURL_ENABLEEAURLS,
        EnableDriveLetters = AURL_ENABLEDRIVELETTERS,
        DisableMixedLGC = AURL_DISABLEMIXEDLGC,
    };

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

    enum class REOptionOP : uint32_t {
        Set = ECOOP_SET,
        Or = ECOOP_OR,
        And = ECOOP_AND,
        Xor = ECOOP_XOR,
    };

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

    enum class ImeCompMode : uint32_t {
        NotOpen = ICM_NOTOPEN,
        Level3 = ICM_LEVEL3,
        Level2 = ICM_LEVEL2,
        Level2_5 = ICM_LEVEL2_5,
        Level2Sui = ICM_LEVEL2_SUI,
        Ctf = ICM_CTF,
    };

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

    enum class ImeVersion : uint32_t {
        Version0310 = IMEVER_0310,
        Version0400 = IMEVER_0400,
    };

    enum class ImeUICap : uint32_t {
        Cap2700 = UI_CAP_2700,
        CapRot90 = UI_CAP_ROT90,
        CapRotAny = UI_CAP_ROTANY,
    };

    inline ImeUICap operator|(ImeUICap a, ImeUICap b) {
        return static_cast<ImeUICap>(static_cast<uint32_t>(a) |
                                     static_cast<uint32_t>(b));
    }

    enum class ImeCompStrCap : uint32_t {
        CompStr = SCS_CAP_COMPSTR,
        MakeRead = SCS_CAP_MAKEREAD,
        SetReconvertString = SCS_CAP_SETRECONVERTSTRING,
    };

    inline ImeCompStrCap operator|(ImeCompStrCap a, ImeCompStrCap b) {
        return static_cast<ImeCompStrCap>(static_cast<uint32_t>(a) |
                                          static_cast<uint32_t>(b));
    }

    enum class ImeSelectCap : uint32_t {
        Conversion = SELECT_CAP_CONVERSION,
        Sentence = SELECT_CAP_SENTENCE,
    };

    inline ImeSelectCap operator|(ImeSelectCap a, ImeSelectCap b) {
        return static_cast<ImeSelectCap>(static_cast<uint32_t>(a) |
                                         static_cast<uint32_t>(b));
    }

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

    enum class REEllipsisMode : uint32_t {
        Mask = ELLIPSIS_MASK,
        None = ELLIPSIS_NONE,
        End = ELLIPSIS_END,
        Word = ELLIPSIS_WORD,
    };

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

    enum class RERedoState : uint32_t {
        Unknown = UID_UNKNOWN,
        Typing = UID_TYPING,
        Delete = UID_DELETE,
        DragDrop = UID_DRAGDROP,
        Cut = UID_CUT,
        Paste = UID_PASTE,
        AutoTable = UID_AUTOTABLE,
    };

    enum class REUndoState : uint32_t {
        Unknown = UID_UNKNOWN,
        Typing = UID_TYPING,
        Delete = UID_DELETE,
        DragDrop = UID_DRAGDROP,
        Cut = UID_CUT,
        Paste = UID_PASTE,
        AutoTable = UID_AUTOTABLE,
    };

    typedef tomConstants REStoryType;

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

    enum class RETouchOption : uint32_t {
        ShowHandles = RTO_SHOWHANDLES,
        DisableHandles = RTO_DISABLEHANDLES,
        ReadingMode = RTO_READINGMODE,
    };

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

    enum class REPageRotate : uint32_t {
        Rotate0 = EPR_0,
        Rotate270 = EPR_270,
        Rotate180 = EPR_180,
        Rotate90 = EPR_90,
        RotateSE = EPR_SE,
    };

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

    enum class ScrollStyle : uint32_t {
        Horiz = SBS_HORZ,
        Vert = SBS_VERT,
        TopAlign = SBS_TOPALIGN,
        LeftAlign = SBS_LEFTALIGN,
        BottomAlign = SBS_BOTTOMALIGN,
        RightAlign = SBS_RIGHTALIGN,
        SizeBoxTopLeftAlign = SBS_SIZEBOXTOPLEFTALIGN,
        SizeBoxBottomRightAlign = SBS_SIZEBOXBOTTOMRIGHTALIGN,
        SizeBox = SBS_SIZEBOX,
        SizeGrip = SBS_SIZEGRIP,
    };

    inline ScrollStyle operator|(ScrollStyle a, ScrollStyle b) {
        return static_cast<ScrollStyle>(static_cast<uint32_t>(a) |
                                        static_cast<uint32_t>(b));
    }

    enum class ScrollType : uint32_t {
        Horiz = SB_HORZ,
        Vert = SB_VERT,
        Ctl = SB_CTL,
        Both = SB_BOTH,
    };

    inline ScrollType operator|(ScrollType a, ScrollType b) {
        return static_cast<ScrollType>(static_cast<uint32_t>(a) |
                                       static_cast<uint32_t>(b));
    }

    enum class ArrowType : uint32_t {
        EnableBoth = ESB_ENABLE_BOTH,
        DisableBoth = ESB_DISABLE_BOTH,
        DisableLeft = ESB_DISABLE_LEFT,
        DisableRight = ESB_DISABLE_RIGHT,
        DisableUp = ESB_DISABLE_UP,
        DisableDown = ESB_DISABLE_DOWN,
        DisableLeftUp = ESB_DISABLE_LTUP,
        DisableRightDown = ESB_DISABLE_RTDN,
    };

    inline ArrowType operator|(ArrowType a, ArrowType b) {
        return static_cast<ArrowType>(static_cast<uint32_t>(a) |
                                      static_cast<uint32_t>(b));
    }

    enum class ScrollCommand : uint32_t {
        LineUp = SB_LINEUP,
        LineLeft = SB_LINELEFT,
        LineDown = SB_LINEDOWN,
        LineRight = SB_LINERIGHT,
        PageUp = SB_PAGEUP,
        PageLeft = SB_PAGELEFT,
        PageDown = SB_PAGEDOWN,
        PageRight = SB_PAGERIGHT,
        ThumbPosition = SB_THUMBPOSITION,
        ThumbTrack = SB_THUMBTRACK,
        Top = SB_TOP,
        Left = SB_LEFT,
        Bottom = SB_BOTTOM,
        Right = SB_RIGHT,
        EndScroll = SB_ENDSCROLL,
    };

    inline ScrollCommand operator|(ScrollCommand a, ScrollCommand b) {
        return static_cast<ScrollCommand>(static_cast<uint32_t>(a) |
                                          static_cast<uint32_t>(b));
    }

    enum class ScrollFlag : uint32_t {
        ScrollChildren = SW_SCROLLCHILDREN,
        InValidate = SW_INVALIDATE,
        Erase = SW_ERASE,
        SmoothScroll = SW_SMOOTHSCROLL,
    };

    inline ScrollFlag operator|(ScrollFlag a, ScrollFlag b) {
        return static_cast<ScrollFlag>(static_cast<uint32_t>(a) |
                                       static_cast<uint32_t>(b));
    }

    enum class ScrollMessage : uint32_t {
        EnableArrows = SBM_ENABLE_ARROWS,
        GetPos = SBM_GETPOS,
        GetRange = SBM_GETRANGE,
        GetScrollBarInfo = SBM_GETSCROLLBARINFO,
        GetScrollInfo = SBM_GETSCROLLINFO,
        SetPos = SBM_SETPOS,
        SetRange = SBM_SETRANGE,
        SetRangeRedraw = SBM_SETRANGEREDRAW,
        SetScrollInfo = SBM_SETSCROLLINFO,
    };

    enum class ScrollNotify : uint32_t {
        CtlColorScrollBar = WM_CTLCOLORSCROLLBAR,
        HScroll = WM_HSCROLL,
        VScroll = WM_VSCROLL,
    };

    enum class StatusStyle : uint32_t {
        SizeGrip = SBARS_SIZEGRIP,
        ToolTips = SBARS_TOOLTIPS,
    };

    inline StatusStyle operator|(StatusStyle a, StatusStyle b) {
        return static_cast<StatusStyle>(static_cast<uint32_t>(a) |
                                        static_cast<uint32_t>(b));
    }

    inline StatusStyle operator|(StatusStyle a, CommonStyle b) {
        return static_cast<StatusStyle>(static_cast<uint32_t>(a) |
                                        static_cast<uint32_t>(b));
    }

    inline StatusStyle operator|(CommonStyle a, StatusStyle b) {
        return static_cast<StatusStyle>(static_cast<uint32_t>(a) |
                                        static_cast<uint32_t>(b));
    }

    enum class StatusTextFlag : uint32_t {
        None = 0,
        OwnerDraw = SBT_OWNERDRAW,
        NoBorders = SBT_NOBORDERS,
        PopOut = SBT_POPOUT,
        RtlReading = SBT_RTLREADING,
        NoTabParsing = SBT_NOTABPARSING,
    };

    inline StatusTextFlag operator|(StatusTextFlag a, StatusTextFlag b) {
        return static_cast<StatusTextFlag>(static_cast<uint32_t>(a) |
                                           static_cast<uint32_t>(b));
    }

    enum class StatusMessage : uint32_t {
        GetBorders = SB_GETBORDERS,
        GetIcon = SB_GETICON,
        GetParts = SB_GETPARTS,
        GetRect = SB_GETRECT,
        GetText = SB_GETTEXT,
        GetTextLength = SB_GETTEXTLENGTH,
        GetTipText = SB_GETTIPTEXT,
        GetUnicodeFormat = SB_GETUNICODEFORMAT,
        IsSimple = SB_ISSIMPLE,
        SetBackgroundColor = SB_SETBKCOLOR,
        SetIcon = SB_SETICON,
        SetMinHeight = SB_SETMINHEIGHT,
        SetParts = SB_SETPARTS,
        SetText = SB_SETTEXT,
        SetTipText = SB_SETTIPTEXT,
        SetUnicodeFormat = SB_SETUNICODEFORMAT,
        Simple = SB_SIMPLE,
    };

    enum class StatusNotify : uint32_t {
        Click = NM_CLICK,
        DoubleClick = NM_DBLCLK,
        RightClick = NM_RCLICK,
        RightDoubleClick = NM_RDBLCLK,
        SimpleModeChange = SBN_SIMPLEMODECHANGE,
    };

    enum class TabStyle : uint32_t {
        ScrollOpposite = TCS_SCROLLOPPOSITE,
        Bottom = TCS_BOTTOM,
        Right = TCS_RIGHT,
        MultiSelect = TCS_MULTISELECT,
        FlatButtons = TCS_FLATBUTTONS,
        ForceIconLeft = TCS_FORCEICONLEFT,
        ForceLabelLeft = TCS_FORCELABELLEFT,
        HotTrack = TCS_HOTTRACK,
        Vertical = TCS_VERTICAL,
        Tabs = TCS_TABS,
        Buttons = TCS_BUTTONS,
        SingleLine = TCS_SINGLELINE,
        MultiLine = TCS_MULTILINE,
        RightJustify = TCS_RIGHTJUSTIFY,
        FixedWidth = TCS_FIXEDWIDTH,
        RaggedRight = TCS_RAGGEDRIGHT,
        FocusOnButtonDown = TCS_FOCUSONBUTTONDOWN,
        OwnerDrawFixed = TCS_OWNERDRAWFIXED,
        ToolTips = TCS_TOOLTIPS,
        FocusNever = TCS_FOCUSNEVER,
    };

    inline TabStyle operator|(TabStyle a, TabStyle b) {
        return static_cast<TabStyle>(static_cast<uint32_t>(a) |
                                     static_cast<uint32_t>(b));
    }

    enum class TabExtendStyle : uint32_t {
        FlatSeparators = TCS_EX_FLATSEPARATORS,
        RegisterDrop = TCS_EX_REGISTERDROP,
    };

    inline TabExtendStyle operator|(TabExtendStyle a, TabExtendStyle b) {
        return static_cast<TabExtendStyle>(static_cast<uint32_t>(a) |
                                           static_cast<uint32_t>(b));
    }

    enum class TabMessage : uint32_t {
        AdjustRect = TCM_ADJUSTRECT,
        DeleteAllItems = TCM_DELETEALLITEMS,
        DeleteItem = TCM_DELETEITEM,
        DeselectAll = TCM_DESELECTALL,
        GetCurrentFocus = TCM_GETCURFOCUS,
        GetCurrentSelect = TCM_GETCURSEL,
        GetExtendedStyle = TCM_GETEXTENDEDSTYLE,
        GetImageList = TCM_GETIMAGELIST,
        GetItem = TCM_GETITEM,
        GetItemCount = TCM_GETITEMCOUNT,
        GetItemRect = TCM_GETITEMRECT,
        GetRowCount = TCM_GETROWCOUNT,
        GetToolTips = TCM_GETTOOLTIPS,
        GetUnicodeFormat = TCM_GETUNICODEFORMAT,
        HighlightItem = TCM_HIGHLIGHTITEM,
        HitTest = TCM_HITTEST,
        InsertItem = TCM_INSERTITEM,
        RemoveImage = TCM_REMOVEIMAGE,
        SetCurrentFocus = TCM_SETCURFOCUS,
        SetCurrentSelect = TCM_SETCURSEL,
        SetExtendedStyle = TCM_SETEXTENDEDSTYLE,
        SetImageList = TCM_SETIMAGELIST,
        SetItem = TCM_SETITEM,
        SetItemExtra = TCM_SETITEMEXTRA,
        SetItemSize = TCM_SETITEMSIZE,
        SetMinTabWidth = TCM_SETMINTABWIDTH,
        SetPadding = TCM_SETPADDING,
        SetToolTips = TCM_SETTOOLTIPS,
        SetUnicodeFormat = TCM_SETUNICODEFORMAT,
    };

    enum class TabNotify : uint32_t {
        Click = NM_CLICK,
        DoubleClick = NM_DBLCLK,
        RightClick = NM_RCLICK,
        RightDoubleClick = NM_RDBLCLK,
        ReleasedCapture = NM_RELEASEDCAPTURE,
        FocusChange = TCN_FOCUSCHANGE,
        GetObj = TCN_GETOBJECT,
        KeyDown = TCN_KEYDOWN,
        SelectChange = TCN_SELCHANGE,
        SelectChanging = TCN_SELCHANGING,
    };

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

    enum class TaskDialogElement : uint32_t {
        Content = TDE_CONTENT,
        ExpandedInformation = TDE_EXPANDED_INFORMATION,
        Footer = TDE_FOOTER,
        MainInstruction = TDE_MAIN_INSTRUCTION,
    };

    enum class TaskDialogIconType : uint32_t {
        Main = TDIE_ICON_MAIN,
        Footer = TDIE_ICON_FOOTER,
    };

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

    enum class ToolBarStyle : uint32_t {
        Button = TBSTYLE_BUTTON,
        Sep = TBSTYLE_SEP,
        Check = TBSTYLE_CHECK,
        Group = TBSTYLE_GROUP,
        CheckGroup = TBSTYLE_CHECKGROUP,
        DropDown = TBSTYLE_DROPDOWN,
        AutoSize = TBSTYLE_AUTOSIZE,
        NoPrefix = TBSTYLE_NOPREFIX,
        ToolTips = TBSTYLE_TOOLTIPS,
        WrapAble = TBSTYLE_WRAPABLE,
        AltDrag = TBSTYLE_ALTDRAG,
        Flat = TBSTYLE_FLAT,
        List = TBSTYLE_LIST,
        CustomErase = TBSTYLE_CUSTOMERASE,
        RegisterDrop = TBSTYLE_REGISTERDROP,
        Transparent = TBSTYLE_TRANSPARENT,
    };

    inline ToolBarStyle operator|(ToolBarStyle a, ToolBarStyle b) {
        return static_cast<ToolBarStyle>(static_cast<uint32_t>(a) |
                                         static_cast<uint32_t>(b));
    }

    inline ToolBarStyle operator|(ToolBarStyle a, CommonStyle b) {
        return static_cast<ToolBarStyle>(static_cast<uint32_t>(a) |
                                         static_cast<uint32_t>(b));
    }

    inline ToolBarStyle operator|(CommonStyle a, ToolBarStyle b) {
        return static_cast<ToolBarStyle>(static_cast<uint32_t>(a) |
                                         static_cast<uint32_t>(b));
    }

    enum class ToolBarExtendStyle : uint32_t {
        DrawDropDownArrows = TBSTYLE_EX_DRAWDDARROWS,
        HideClippedButtons = TBSTYLE_EX_HIDECLIPPEDBUTTONS,
        DoubleBuffer = TBSTYLE_EX_DOUBLEBUFFER,
        MixedButtons = TBSTYLE_EX_MIXEDBUTTONS,
        MultiColumn = TBSTYLE_EX_MULTICOLUMN,
        Vertical = TBSTYLE_EX_VERTICAL,
    };

    inline ToolBarExtendStyle operator|(ToolBarExtendStyle a,
                                        ToolBarExtendStyle b) {
        return static_cast<ToolBarExtendStyle>(static_cast<uint32_t>(a) |
                                               static_cast<uint32_t>(b));
    }

    enum class TBHotItemFlag : uint32_t {
        Other = HICF_OTHER,
        Mouse = HICF_MOUSE,
        ArrowKeys = HICF_ARROWKEYS,
        Accelerator = HICF_ACCELERATOR,
        DupAccel = HICF_DUPACCEL,
        Entering = HICF_ENTERING,
        Leaving = HICF_LEAVING,
        ReSelect = HICF_RESELECT,
        LeftMouse = HICF_LMOUSE,
        ToggleDropDown = HICF_TOGGLEDROPDOWN,
    };

    inline TBHotItemFlag operator|(TBHotItemFlag a, TBHotItemFlag b) {
        return static_cast<TBHotItemFlag>(static_cast<uint32_t>(a) |
                                          static_cast<uint32_t>(b));
    }

    enum class TBImageListID : uint32_t {
        StdSmallColor = IDB_STD_SMALL_COLOR,
        StdLargeColor = IDB_STD_LARGE_COLOR,
        ViewSmallColor = IDB_VIEW_SMALL_COLOR,
        ViewLargeColor = IDB_VIEW_LARGE_COLOR,
        HistSmallColor = IDB_HIST_SMALL_COLOR,
        HistLargeColor = IDB_HIST_LARGE_COLOR,
        HistNormal = IDB_HIST_NORMAL,
        HistHot = IDB_HIST_HOT,
        HistDisabled = IDB_HIST_DISABLED,
        HistPressed = IDB_HIST_PRESSED,
    };

    enum class TBButtonState : int32_t {
        Error = -1,
        Checked = TBSTATE_CHECKED,
        Pressed = TBSTATE_PRESSED,
        Enabled = TBSTATE_ENABLED,
        Hidden = TBSTATE_HIDDEN,
        Indeterminate = TBSTATE_INDETERMINATE,
        Wrap = TBSTATE_WRAP,
        Ellipses = TBSTATE_ELLIPSES,
        Marked = TBSTATE_MARKED,
    };

    inline TBButtonState operator|(TBButtonState a, TBButtonState b) {
        return static_cast<TBButtonState>(static_cast<int32_t>(a) |
                                          static_cast<int32_t>(b));
    }

    enum class ToolBarMessage : uint32_t {
        AddBitmap = TB_ADDBITMAP,
        AddButtons = TB_ADDBUTTONS,
        AddString = TB_ADDSTRING,
        AutoSize = TB_AUTOSIZE,
        ButtonCount = TB_BUTTONCOUNT,
        ButtonStructSize = TB_BUTTONSTRUCTSIZE,
        ChangeBitmap = TB_CHANGEBITMAP,
        CheckButton = TB_CHECKBUTTON,
        CommandToIndex = TB_COMMANDTOINDEX,
        Customize = TB_CUSTOMIZE,
        DeleteButton = TB_DELETEBUTTON,
        EnableButton = TB_ENABLEBUTTON,
        GetAnchorHighlight = TB_GETANCHORHIGHLIGHT,
        GetBitmap = TB_GETBITMAP,
        GetBitmapFlags = TB_GETBITMAPFLAGS,
        GetButton = TB_GETBUTTON,
        GetButtonInfo = TB_GETBUTTONINFO,
        GetButtonSize = TB_GETBUTTONSIZE,
        GetButtonText = TB_GETBUTTONTEXT,
        GetColorScheme = TB_GETCOLORSCHEME,
        GetDisabledImageList = TB_GETDISABLEDIMAGELIST,
        GetExtendedStyle = TB_GETEXTENDEDSTYLE,
        GetHotImageList = TB_GETHOTIMAGELIST,
        GetHotItem = TB_GETHOTITEM,
        GetIdealSize = TB_GETIDEALSIZE,
        GetImageList = TB_GETIMAGELIST,
        GetImageListCount = TB_GETIMAGELISTCOUNT,
        GetInsertMark = TB_GETINSERTMARK,
        GetInsertMarkColor = TB_GETINSERTMARKCOLOR,
        GetItemDropDownRect = TB_GETITEMDROPDOWNRECT,
        GetItemRect = TB_GETITEMRECT,
        GetMaxSize = TB_GETMAXSIZE,
        GetMetrics = TB_GETMETRICS,
        GetObj = TB_GETOBJECT,
        GetPadding = TB_GETPADDING,
        GetPressedImageList = TB_GETPRESSEDIMAGELIST,
        GetRect = TB_GETRECT,
        GetRows = TB_GETROWS,
        GetState = TB_GETSTATE,
        GetString = TB_GETSTRING,
        GetStyle = TB_GETSTYLE,
        GetTextRows = TB_GETTEXTROWS,
        GetToolTips = TB_GETTOOLTIPS,
        GetUnicodeFormat = TB_GETUNICODEFORMAT,
        HasAccelerator = TB_HASACCELERATOR,
        HideButton = TB_HIDEBUTTON,
        HitTest = TB_HITTEST,
        Indeterminate = TB_INDETERMINATE,
        InsertButton = TB_INSERTBUTTON,
        InsertMarkHitTest = TB_INSERTMARKHITTEST,
        IsButtonChecked = TB_ISBUTTONCHECKED,
        IsButtonEnabled = TB_ISBUTTONENABLED,
        IsButtonHidden = TB_ISBUTTONHIDDEN,
        IsButtonHighlighted = TB_ISBUTTONHIGHLIGHTED,
        IsButtonIndeterminate = TB_ISBUTTONINDETERMINATE,
        IsButtonPressed = TB_ISBUTTONPRESSED,
        LoadImages = TB_LOADIMAGES,
        MapAccelerator = TB_MAPACCELERATOR,
        MarkButton = TB_MARKBUTTON,
        MoveButton = TB_MOVEBUTTON,
        PressButton = TB_PRESSBUTTON,
        ReplaceBitmap = TB_REPLACEBITMAP,
        SaveRestore = TB_SAVERESTORE,
        SetAnchorHighlight = TB_SETANCHORHIGHLIGHT,
        SetBitmapSize = TB_SETBITMAPSIZE,
        SetBoundingSize = TB_SETBOUNDINGSIZE,
        SetButtonInfo = TB_SETBUTTONINFO,
        SetButtonSize = TB_SETBUTTONSIZE,
        SetButtonWidth = TB_SETBUTTONWIDTH,
        SetCmdId = TB_SETCMDID,
        SetColorScheme = TB_SETCOLORSCHEME,
        SetDisabledImageList = TB_SETDISABLEDIMAGELIST,
        SetDrawTextFlags = TB_SETDRAWTEXTFLAGS,
        SetExtendedStyle = TB_SETEXTENDEDSTYLE,
        SetHotImageList = TB_SETHOTIMAGELIST,
        SetHotItem = TB_SETHOTITEM,
        SetHotItem2 = TB_SETHOTITEM2,
        SetImageList = TB_SETIMAGELIST,
        SetIndent = TB_SETINDENT,
        SetInsertMark = TB_SETINSERTMARK,
        SetInsertMarkColor = TB_SETINSERTMARKCOLOR,
        SetListGap = TB_SETLISTGAP,
        SetMaxTextRows = TB_SETMAXTEXTROWS,
        SetMetrics = TB_SETMETRICS,
        SetPadding = TB_SETPADDING,
        SetParent = TB_SETPARENT,
        SetPressedImageList = TB_SETPRESSEDIMAGELIST,
        SetRows = TB_SETROWS,
        SetState = TB_SETSTATE,
        SetStyle = TB_SETSTYLE,
        SetToolTips = TB_SETTOOLTIPS,
        SetUnicodeFormat = TB_SETUNICODEFORMAT,
        SetWindowTheme = TB_SETWINDOWTHEME,
        TranslateAccel = (CCM_FIRST + 7),
    };

    enum class ToolBarNotify : uint32_t {
        Char = NM_CHAR,
        Click = NM_CLICK,
        CustomDraw = NM_CUSTOMDRAW,
        DoubleClick = NM_DBLCLK,
        KeyDown = NM_KEYDOWN,
        LeftDown = NM_LDOWN,
        RightClick = NM_RCLICK,
        RightDoubleClick = NM_RDBLCLK,
        ReleasedCapture = NM_RELEASEDCAPTURE,
        ToolTipsCreated = NM_TOOLTIPSCREATED,
        BeginAdjust = TBN_BEGINADJUST,
        BeginDrag = TBN_BEGINDRAG,
        CustHelp = TBN_CUSTHELP,
        DeletingButton = TBN_DELETINGBUTTON,
        DragOut = TBN_DRAGOUT,
        DragOver = TBN_DRAGOVER,
        DropDown = TBN_DROPDOWN,
        DupAccelerator = TBN_DUPACCELERATOR,
        EndAdjust = TBN_ENDADJUST,
        EndDrag = TBN_ENDDRAG,
        GetButtonInfo = TBN_GETBUTTONINFO,
        GetDispInfo = TBN_GETDISPINFO,
        GetInfoTip = TBN_GETINFOTIP,
        GetObj = TBN_GETOBJECT,
        HotItemChange = TBN_HOTITEMCHANGE,
        InitCustomize = TBN_INITCUSTOMIZE,
        MapAccelerator = TBN_MAPACCELERATOR,
        QueryDelete = TBN_QUERYDELETE,
        QueryInsert = TBN_QUERYINSERT,
        Reset = TBN_RESET,
        Restore = TBN_RESTORE,
        Save = TBN_SAVE,
        ToolBarChange = TBN_TOOLBARCHANGE,
        WrapAccelerator = TBN_WRAPACCELERATOR,
        WrapHotItem = TBN_WRAPHOTITEM,
    };

    enum class ToolTipStyle : uint32_t {
        AlwaysTip = TTS_ALWAYSTIP,
        NoPrefix = TTS_NOPREFIX,
        NoAnimate = TTS_NOANIMATE,
        NoFade = TTS_NOFADE,
        Balloon = TTS_BALLOON,
        Close = TTS_CLOSE,
        UseVisualStyle = TTS_USEVISUALSTYLE,
    };

    inline ToolTipStyle operator|(ToolTipStyle a, ToolTipStyle b) {
        return static_cast<ToolTipStyle>(static_cast<uint32_t>(a) |
                                         static_cast<uint32_t>(b));
    }

    enum class TTInfoFlag : uint32_t {
        CenterTip = TTF_CENTERTIP,
        RtlReading = TTF_RTLREADING,
        SubClass = TTF_SUBCLASS,
        Track = TTF_TRACK,
        Absolute = TTF_ABSOLUTE,
        Transparent = TTF_TRANSPARENT,
        ParseLinks = TTF_PARSELINKS,
        DiSetItem = TTF_DI_SETITEM,
    };

    inline TTInfoFlag operator|(TTInfoFlag a, TTInfoFlag b) {
        return static_cast<TTInfoFlag>(static_cast<uint32_t>(a) |
                                       static_cast<uint32_t>(b));
    }

    enum class TTDelayTime : uint32_t {
        Automatic = TTDT_AUTOMATIC,
        ReShow = TTDT_RESHOW,
        AutoPop = TTDT_AUTOPOP,
        Initial = TTDT_INITIAL,
    };

    enum class TTTitleType : uint32_t {
        None = TTI_NONE,
        Info = TTI_INFO,
        Warning = TTI_WARNING,
        Error = TTI_ERROR,
        InfoLarge = TTI_INFO_LARGE,
        WarningLarge = TTI_WARNING_LARGE,
        ErrorLarge = TTI_ERROR_LARGE,
    };

    enum class ToolTipsMessage : uint32_t {
        Activate = TTM_ACTIVATE,
        AddTool = TTM_ADDTOOL,
        AdjustRect = TTM_ADJUSTRECT,
        DeleteTool = TTM_DELTOOL,
        EnumTools = TTM_ENUMTOOLS,
        GetBubbleSize = TTM_GETBUBBLESIZE,
        GetCurrentTool = TTM_GETCURRENTTOOL,
        GetDelayTime = TTM_GETDELAYTIME,
        GetMargin = TTM_GETMARGIN,
        GetMaxTipWidth = TTM_GETMAXTIPWIDTH,
        GetText = TTM_GETTEXT,
        GetTipBackgroundColor = TTM_GETTIPBKCOLOR,
        GetTipTextColor = TTM_GETTIPTEXTCOLOR,
        GetTitle = TTM_GETTITLE,
        GetToolCount = TTM_GETTOOLCOUNT,
        GetToolInfo = TTM_GETTOOLINFO,
        HitTest = TTM_HITTEST,
        NewToolRect = TTM_NEWTOOLRECT,
        Pop = TTM_POP,
        Popup = TTM_POPUP,
        RelayEvent = TTM_RELAYEVENT,
        SetDelayTime = TTM_SETDELAYTIME,
        SetMargin = TTM_SETMARGIN,
        SetMaxTipWidth = TTM_SETMAXTIPWIDTH,
        SetTipBackgroundColor = TTM_SETTIPBKCOLOR,
        SetTipTextColor = TTM_SETTIPTEXTCOLOR,
        SetTitle = TTM_SETTITLE,
        SetToolInfo = TTM_SETTOOLINFO,
        SetWindowTheme = TTM_SETWINDOWTHEME,
        TrackActivate = TTM_TRACKACTIVATE,
        TrackPosition = TTM_TRACKPOSITION,
        Update = TTM_UPDATE,
        UpdateTipText = TTM_UPDATETIPTEXT,
        WindowFromPoint = TTM_WINDOWFROMPOINT,
    };

    enum class ToolTipsNotify : uint32_t {
        CustomDraw = NM_CUSTOMDRAW,
        GetDispInfo = TTN_GETDISPINFO,
        LinkClick = TTN_LINKCLICK,
        NeedText = TTN_NEEDTEXT,
        Pop = TTN_POP,
        Show = TTN_SHOW,
    };

    enum class TrackStyle : uint32_t {
        AutoTicks = TBS_AUTOTICKS,
        Vert = TBS_VERT,
        Horiz = TBS_HORZ,
        Top = TBS_TOP,
        Bottom = TBS_BOTTOM,
        Left = TBS_LEFT,
        Right = TBS_RIGHT,
        Both = TBS_BOTH,
        NoTicks = TBS_NOTICKS,
        EnableSelectRange = TBS_ENABLESELRANGE,
        FixedLength = TBS_FIXEDLENGTH,
        NoThumb = TBS_NOTHUMB,
        ToolTips = TBS_TOOLTIPS,
        Reversed = TBS_REVERSED,
        DownIsLeft = TBS_DOWNISLEFT,
        NotifyBeforeMove = TBS_NOTIFYBEFOREMOVE,
        TransparentBackground = TBS_TRANSPARENTBKGND,
    };

    inline TrackStyle operator|(TrackStyle a, TrackStyle b) {
        return static_cast<TrackStyle>(static_cast<uint32_t>(a) |
                                       static_cast<uint32_t>(b));
    }

    enum class TrackTipSide : uint32_t {
        Top = TBTS_TOP,
        Left = TBTS_LEFT,
        Bottom = TBTS_BOTTOM,
        Right = TBTS_RIGHT,
    };

    enum class TrackMessage : uint32_t {
        ClearSelect = TBM_CLEARSEL,
        ClearTicks = TBM_CLEARTICS,
        GetBuddy = TBM_GETBUDDY,
        GetChannelRect = TBM_GETCHANNELRECT,
        GetLineSize = TBM_GETLINESIZE,
        GetNumTicks = TBM_GETNUMTICS,
        GetPageSize = TBM_GETPAGESIZE,
        GetPos = TBM_GETPOS,
        GetPTicks = TBM_GETPTICS,
        GetRangeMax = TBM_GETRANGEMAX,
        GetRangeMin = TBM_GETRANGEMIN,
        GetSelectEnd = TBM_GETSELEND,
        GetSelectStart = TBM_GETSELSTART,
        GetThumbLength = TBM_GETTHUMBLENGTH,
        GetThumbRect = TBM_GETTHUMBRECT,
        GetTick = TBM_GETTIC,
        GetTickPos = TBM_GETTICPOS,
        GetToolTips = TBM_GETTOOLTIPS,
        GetUnicodeFormat = TBM_GETUNICODEFORMAT,
        SetBuddy = TBM_SETBUDDY,
        SetLineSize = TBM_SETLINESIZE,
        SetPageSize = TBM_SETPAGESIZE,
        SetPos = TBM_SETPOS,
        SetPosNotify = TBM_SETPOSNOTIFY,
        SetRange = TBM_SETRANGE,
        SetRangeMax = TBM_SETRANGEMAX,
        SetRangeMin = TBM_SETRANGEMIN,
        SetSelect = TBM_SETSEL,
        SetSelectEnd = TBM_SETSELEND,
        SetSelectStart = TBM_SETSELSTART,
        SetThumbLength = TBM_SETTHUMBLENGTH,
        SetTick = TBM_SETTIC,
        SetTickFreq = TBM_SETTICFREQ,
        SetTipSide = TBM_SETTIPSIDE,
        SetToolTips = TBM_SETTOOLTIPS,
        SetUnicodeFormat = TBM_SETUNICODEFORMAT
    };

    enum class TrackNotify : uint32_t {
        CustomDraw = NM_CUSTOMDRAW,
        ReleasedCapture = NM_RELEASEDCAPTURE,
        ThumbPosChanging = TRBN_THUMBPOSCHANGING,
        HScroll = WM_HSCROLL,
        VScroll = WM_VSCROLL,
    };

    enum class TreeStyle : uint32_t {
        HasButtons = TVS_HASBUTTONS,
        HasLines = TVS_HASLINES,
        LinesAtRoot = TVS_LINESATROOT,
        EditLabels = TVS_EDITLABELS,
        DisableDragDrop = TVS_DISABLEDRAGDROP,
        ShowSelectAlways = TVS_SHOWSELALWAYS,
        RtlReading = TVS_RTLREADING,
        NoToolTips = TVS_NOTOOLTIPS,
        CheckBoxes = TVS_CHECKBOXES,
        TrackSelect = TVS_TRACKSELECT,
        SingleExpand = TVS_SINGLEEXPAND,
        InfoTip = TVS_INFOTIP,
        FullRowSelect = TVS_FULLROWSELECT,
        NoScroll = TVS_NOSCROLL,
        NoEvenHeight = TVS_NONEVENHEIGHT,
        NoHScroll = TVS_NOHSCROLL,
    };

    inline TreeStyle operator|(TreeStyle a, TreeStyle b) {
        return static_cast<TreeStyle>(static_cast<uint32_t>(a) |
                                      static_cast<uint32_t>(b));
    }

    enum class TreeExtendStyle : uint32_t {
        NoSingleCollapse = TVS_EX_NOSINGLECOLLAPSE,
        MultiSelect = TVS_EX_MULTISELECT,
        DoubleBuffer = TVS_EX_DOUBLEBUFFER,
        NoIndentState = TVS_EX_NOINDENTSTATE,
        RichToolTip = TVS_EX_RICHTOOLTIP,
        AutoHScroll = TVS_EX_AUTOHSCROLL,
        FadeInOutExpandOs = TVS_EX_FADEINOUTEXPANDOS,
        PartialCheckBoxes = TVS_EX_PARTIALCHECKBOXES,
        ExclusionCheckBoxes = TVS_EX_EXCLUSIONCHECKBOXES,
        DimmedCheckBoxes = TVS_EX_DIMMEDCHECKBOXES,
        DrawImageAsync = TVS_EX_DRAWIMAGEASYNC
    };

    inline TreeExtendStyle operator|(TreeExtendStyle a, TreeExtendStyle b) {
        return static_cast<TreeExtendStyle>(static_cast<uint32_t>(a) |
                                            static_cast<uint32_t>(b));
    }

    enum class TreeItemState : uint32_t {
        Selected = TVIS_SELECTED,
        Cut = TVIS_CUT,
        DropHilited = TVIS_DROPHILITED,
        Bold = TVIS_BOLD,
        Expanded = TVIS_EXPANDED,
        ExpandedOnce = TVIS_EXPANDEDONCE,
        ExpandPartial = TVIS_EXPANDPARTIAL,
        OverlayMask = TVIS_OVERLAYMASK,
        StateImageMask = TVIS_STATEIMAGEMASK,
        UserMask = TVIS_USERMASK,
    };

    inline TreeItemState operator|(TreeItemState a, TreeItemState b) {
        return static_cast<TreeItemState>(static_cast<uint32_t>(a) |
                                          static_cast<uint32_t>(b));
    }

    enum class TreeItemExState : uint32_t {
        Flat = TVIS_EX_FLAT,
        Disabled = TVIS_EX_DISABLED,
        All = TVIS_EX_ALL,
    };

    inline TreeItemExState operator|(TreeItemExState a, TreeItemExState b) {
        return static_cast<TreeItemExState>(static_cast<uint32_t>(a) |
                                            static_cast<uint32_t>(b));
    }

    enum class TreeItemFlag : uint32_t {
        Text = TVIF_TEXT,
        Image = TVIF_IMAGE,
        Param = TVIF_PARAM,
        State = TVIF_STATE,
        Handle = TVIF_HANDLE,
        SelectedImage = TVIF_SELECTEDIMAGE,
        Children = TVIF_CHILDREN,
        Integral = TVIF_INTEGRAL,
        StateEx = TVIF_STATEEX,
        ExpandedImage = TVIF_EXPANDEDIMAGE,
    };

    enum class TreeItemCheckState : int32_t {
        Checked = 1,
        Unchecked = 0,
        Intermediate = -1,
    };

    enum class TreeImageListType : int32_t {
        Normal = TVSIL_NORMAL,
        State = TVSIL_STATE,
    };

    enum class TreeOpFlag : uint32_t {
        Root = TVGN_ROOT,
        Next = TVGN_NEXT,
        Previous = TVGN_PREVIOUS,
        Parent = TVGN_PARENT,
        Child = TVGN_CHILD,
        FirstVisible = TVGN_FIRSTVISIBLE,
        NextVisible = TVGN_NEXTVISIBLE,
        PreviousVisible = TVGN_PREVIOUSVISIBLE,
        DropHilite = TVGN_DROPHILITE,
        Caret = TVGN_CARET,
        LastVisible = TVGN_LASTVISIBLE,
        NextSelected = TVGN_NEXTSELECTED,
    };

    enum class TreeExpandFlag : uint32_t {
        Collapse = TVE_COLLAPSE,
        Expand = TVE_EXPAND,
        Toggle = TVE_TOGGLE,
        ExpandPartial = TVE_EXPANDPARTIAL,
        CollapseReset = TVE_COLLAPSERESET,
    };

    inline TreeExpandFlag operator|(TreeExpandFlag a, TreeExpandFlag b) {
        return static_cast<TreeExpandFlag>(static_cast<uint32_t>(a) |
                                           static_cast<uint32_t>(b));
    }

    enum class TreeMessage : uint32_t {
        CreateDragImage = TVM_CREATEDRAGIMAGE,
        DeleteItem = TVM_DELETEITEM,
        EditLabel = TVM_EDITLABEL,
        EndEditLabelNow = TVM_ENDEDITLABELNOW,
        EnsureVisible = TVM_ENSUREVISIBLE,
        Expand = TVM_EXPAND,
        GetBackgroundColor = TVM_GETBKCOLOR,
        GetCount = TVM_GETCOUNT,
        GetEditControl = TVM_GETEDITCONTROL,
        GetExtendedStyle = TVM_GETEXTENDEDSTYLE,
        GetImageList = TVM_GETIMAGELIST,
        GetIndent = TVM_GETINDENT,
        GetInsertMarkColor = TVM_GETINSERTMARKCOLOR,
        GetISearchString = TVM_GETISEARCHSTRING,
        GetItem = TVM_GETITEM,
        GetItemHeight = TVM_GETITEMHEIGHT,
        GetItemPartRect = TVM_GETITEMPARTRECT,
        GetItemRect = TVM_GETITEMRECT,
        GetItemState = TVM_GETITEMSTATE,
        GetLineColor = TVM_GETLINECOLOR,
        GetNextItem = TVM_GETNEXTITEM,
        GetScrollTime = TVM_GETSCROLLTIME,
        GetSelectedCount = TVM_GETSELECTEDCOUNT,
        GetTextColor = TVM_GETTEXTCOLOR,
        GetToolTips = TVM_GETTOOLTIPS,
        GetUnicodeFormat = TVM_GETUNICODEFORMAT,
        GetVisibleCount = TVM_GETVISIBLECOUNT,
        HitTest = TVM_HITTEST,
        InsertItem = TVM_INSERTITEM,
        MapAccessIdToHTreeItem = TVM_MAPACCIDTOHTREEITEM,
        MapHTreeItemToAccessId = TVM_MAPHTREEITEMTOACCID,
        SelectItem = TVM_SELECTITEM,
        SetAutoScrollInfo = TVM_SETAUTOSCROLLINFO,
        SetBackgroundColor = TVM_SETBKCOLOR,
        SetBorder = TVM_SETBORDER,
        SetExtendedStyle = TVM_SETEXTENDEDSTYLE,
        SetHot = TVM_SETHOT,
        SetImageList = TVM_SETIMAGELIST,
        SetIndent = TVM_SETINDENT,
        SetInsertMark = TVM_SETINSERTMARK,
        SetInsertMarkColor = TVM_SETINSERTMARKCOLOR,
        SetItem = TVM_SETITEM,
        SetItemHeight = TVM_SETITEMHEIGHT,
        SetLineColor = TVM_SETLINECOLOR,
        SetScrollTime = TVM_SETSCROLLTIME,
        SetTextColor = TVM_SETTEXTCOLOR,
        SetToolTips = TVM_SETTOOLTIPS,
        SetUnicodeFormat = TVM_SETUNICODEFORMAT,
        ShowInfoTip = TVM_SHOWINFOTIP,
        SortChildren = TVM_SORTCHILDREN,
        SortChildrenCallback = TVM_SORTCHILDRENCB,
    };

    enum class TreeNotify : uint32_t {
        Click = NM_CLICK,
        CustomDraw = NM_CUSTOMDRAW,
        DoubleClick = NM_DBLCLK,
        KillFocus = NM_KILLFOCUS,
        RightClick = NM_RCLICK,
        RightDoubleClick = NM_RDBLCLK,
        Return = NM_RETURN,
        SetCursor = NM_SETCURSOR,
        SetFocus = NM_SETFOCUS,
        AsyncDraw = TVN_ASYNCDRAW,
        BeginDrag = TVN_BEGINDRAG,
        BeginLabelEdit = TVN_BEGINLABELEDIT,
        BeginRDrag = TVN_BEGINRDRAG,
        DeleteItem = TVN_DELETEITEM,
        EndLabelEdit = TVN_ENDLABELEDIT,
        GetDispInfo = TVN_GETDISPINFO,
        GetInfoTip = TVN_GETINFOTIP,
        ItemChanged = TVN_ITEMCHANGED,
        ItemChanging = TVN_ITEMCHANGING,
        ItemExpanded = TVN_ITEMEXPANDED,
        ItemExpanding = TVN_ITEMEXPANDING,
        KeyDown = TVN_KEYDOWN,
        SelChanged = TVN_SELCHANGED,
        SelChanging = TVN_SELCHANGING,
        SetDispInfo = TVN_SETDISPINFO,
        SingleExpand = TVN_SINGLEEXPAND
    };

    enum class UpDownStyle : uint32_t {
        Wrap = UDS_WRAP,
        SetBuddyInt = UDS_SETBUDDYINT,
        AlignRight = UDS_ALIGNRIGHT,
        AlignLeft = UDS_ALIGNLEFT,
        AutoBuddy = UDS_AUTOBUDDY,
        ArrowKeys = UDS_ARROWKEYS,
        Horiz = UDS_HORZ,
        NoThousands = UDS_NOTHOUSANDS,
        HotTrack = UDS_HOTTRACK,
    };

    inline UpDownStyle operator|(UpDownStyle a, UpDownStyle b) {
        return static_cast<UpDownStyle>(static_cast<uint32_t>(a) |
                                        static_cast<uint32_t>(b));
    }

    enum class UpDownMessage : uint32_t {
        GetAccel = UDM_GETACCEL,
        GetBase = UDM_GETBASE,
        GetBuddy = UDM_GETBUDDY,
        GetPos = UDM_GETPOS,
        GetPos32 = UDM_GETPOS32,
        GetRange = UDM_GETRANGE,
        GetRange32 = UDM_GETRANGE32,
        GetUnicodeFormat = UDM_GETUNICODEFORMAT,
        SetAccel = UDM_SETACCEL,
        SetBase = UDM_SETBASE,
        SetBuddy = UDM_SETBUDDY,
        SetPos = UDM_SETPOS,
        SetPos32 = UDM_SETPOS32,
        SetRange = UDM_SETRANGE,
        SetRange32 = UDM_SETRANGE32,
        SetUnicodeFormat = UDM_SETUNICODEFORMAT,
    };

    enum class UpDownNotify : uint32_t {
        ReleasedCapture = NM_RELEASEDCAPTURE,
        DeltaPos = UDN_DELTAPOS,
    };
} // namespace YanLib::ui::components
#endif // COMPONENTS_H
