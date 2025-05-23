//
// Created by forkernel on 2025/5/23.
//

#ifndef BUTTON_H
#define BUTTON_H
#include <Windows.h>
#include <CommCtrl.h>
#include <cstdint>
#include <string>
#include "helper/convert.h"
#pragma comment(lib, "Comctl32.lib")
namespace YanLib::components {
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
#ifndef BUTTONSTYLE
#define BUTTONSTYLE

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
#endif
#ifndef BUTTONSTATE
#define BUTTONSTATE

    enum class ButtonState : uint32_t {
        Unchecked = BST_UNCHECKED,
        Checked = BST_CHECKED,
        Indeterminate = BST_INDETERMINATE,
        Pushed = BST_PUSHED,
        Focus = BST_FOCUS,
        DropDownPushed = BST_DROPDOWNPUSHED,
        Hot = BST_HOT,
    };
#endif
#ifndef TEXTALIGN
#define TEXTALIGN

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
#endif
#ifndef BUTTONMESSAGE
#define BUTTONMESSAGE

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
#endif
#ifndef BUTTONNOTIFY
#define BUTTONNOTIFY

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
#endif
    class button {
    private:
        uint32_t error_code = 0;

    public:
        button(const button &other) = delete;

        button(button &&other) = delete;

        button &operator=(const button &other) = delete;

        button &operator=(button &&other) = delete;

        button() = default;

        ~button() = default;

        HWND
        create(const char *button_text,
               intptr_t button_id,
               HWND parent_window_handle,
               LPARAM lparam,
               int32_t x,
               int32_t y,
               int32_t width = 100,
               int32_t height = 30,
               ButtonStyle style = ButtonStyle::PushButton,
               WindowStyle window_style = WindowStyle::Child |
                       WindowStyle::Visible,
               WindowExtendStyle extend_window_style = WindowExtendStyle::None,
               void *param = nullptr);

        HWND
        create(const wchar_t *button_text,
               intptr_t button_id,
               HWND parent_window_handle,
               LPARAM lparam,
               int32_t x,
               int32_t y,
               int32_t width = 100,
               int32_t height = 30,
               ButtonStyle style = ButtonStyle::PushButton,
               WindowStyle window_style = WindowStyle::Child |
                       WindowStyle::Visible,
               WindowExtendStyle extend_window_style = WindowExtendStyle::None,
               void *param = nullptr);

        bool enable(HWND button_handle);

        bool disable(HWND button_handle);

        ButtonState get_check(HWND button_handle);

        void set_check(HWND button_handle, ButtonState state);

        bool get_ideal_size(HWND button_handle, SIZE *size);

        bool get_image_list(HWND button_handle, BUTTON_IMAGELIST *image_list);

        bool set_image_list(HWND button_handle, BUTTON_IMAGELIST *image_list);

        int64_t get_note_len(HWND button_handle);

        bool get_note(HWND button_handle,
                      std::string &note,
                      helper::CodePage code_page = helper::CodePage::GB2312);

        bool set_note(HWND button_handle,
                      std::string &note,
                      helper::CodePage code_page = helper::CodePage::GB2312);

        bool get_note(HWND button_handle, std::wstring &note);

        bool set_note(HWND button_handle, std::wstring &note);

        bool get_split_info(HWND button_handle, BUTTON_SPLITINFO *split_info);

        bool set_split_info(HWND button_handle, BUTTON_SPLITINFO *split_info);

        int32_t get_text_len(HWND button_handle);

        int32_t get_text(HWND button_handle, std::string &text);

        bool set_text(HWND button_handle, std::string &text);

        int32_t get_text(HWND button_handle, std::wstring &text);

        bool set_text(HWND button_handle, std::wstring &text);

        TextAlign get_text_align(HWND button_handle);

        void set_text_align(HWND button_handle, TextAlign align);

        bool get_text_margin(HWND button_handle, RECT *margin);

        bool set_text_margin(HWND button_handle, RECT *margin);

        ButtonState get_state(HWND button_handle);

        void hilite(HWND button_handle);

        void unhilite(HWND button_handle);

        bool active_drop_down_state(HWND button_handle);

        bool inactive_drop_down_state(HWND button_handle);

        LRESULT set_elevation_state(HWND button_handle);

        LRESULT unset_elevation_state(HWND button_handle);

        ButtonStyle get_style(HWND button_handle);

        void
        set_style(HWND button_handle, ButtonStyle style, bool is_redraw = true);

        [[nodiscard]] uint32_t err_code() const;

        [[nodiscard]] std::string err_string() const;

        [[nodiscard]] std::wstring err_wstring() const;
    };
} // namespace YanLib::components
#endif // BUTTON_H
