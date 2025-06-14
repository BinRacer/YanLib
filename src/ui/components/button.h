/* clang-format off */
/*
 * @file button.h
 * @date 2025-05-23
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
#ifndef BUTTON_H
#define BUTTON_H
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
        std::vector<HWND> button_handles = {};
        sync::rwlock button_rwlock = {};
        uint32_t error_code = 0;

    public:
        button(const button &other) = delete;

        button(button &&other) = delete;

        button &operator=(const button &other) = delete;

        button &operator=(button &&other) = delete;

        button() = default;

        ~button();

        HWND create(uintptr_t button_id,
                    HWND parent_window_handle,
                    LPARAM lparam,
                    int32_t x,
                    int32_t y,
                    int32_t width = 100,
                    int32_t height = 30,
                    ButtonStyle style = ButtonStyle::PushButton,
                    WindowStyle window_style = WindowStyle::Child |
                            WindowStyle::Visible);

        HWND create(const char *button_name,
                    uintptr_t button_id,
                    HWND parent_window_handle,
                    LPARAM lparam,
                    int32_t x,
                    int32_t y,
                    int32_t width = 100,
                    int32_t height = 30,
                    ButtonStyle style = ButtonStyle::PushButton,
                    WindowStyle window_style = WindowStyle::Child |
                            WindowStyle::Visible);

        HWND create(const wchar_t *button_name,
                    uintptr_t button_id,
                    HWND parent_window_handle,
                    LPARAM lparam,
                    int32_t x,
                    int32_t y,
                    int32_t width = 100,
                    int32_t height = 30,
                    ButtonStyle style = ButtonStyle::PushButton,
                    WindowStyle window_style = WindowStyle::Child |
                            WindowStyle::Visible);

        bool destroy(HWND button_handle);

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
                      helper::CodePage code_page = helper::curr_code_page());

        bool set_note(HWND button_handle,
                      std::string &note,
                      helper::CodePage code_page = helper::curr_code_page());

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
} // namespace YanLib::ui::components
#endif // BUTTON_H
