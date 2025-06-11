/* clang-format off */
/*
 * @file rebar.h
 * @date 2025-05-29
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
#ifndef REBAR_H
#define REBAR_H
#ifndef UNICODE
#define UNICODE
#endif
#ifndef _UNICODE
#define _UNICODE
#endif
#include <Windows.h>
#include <CommCtrl.h>
#include <Uxtheme.h>
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
#ifndef REBARSTYLE
#define REBARSTYLE
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
#endif
#ifndef COMMONSTYLE
#define COMMONSTYLE
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
#endif
    inline RebarStyle operator|(RebarStyle a, CommonStyle b) {
        return static_cast<RebarStyle>(static_cast<uint32_t>(a) |
                                       static_cast<uint32_t>(b));
    }
    inline RebarStyle operator|(CommonStyle a, RebarStyle b) {
        return static_cast<RebarStyle>(static_cast<uint32_t>(a) |
                                       static_cast<uint32_t>(b));
    }
#ifndef REBARMESSAGE
#define REBARMESSAGE
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
#endif
#ifndef REBARNOTIFY
#define REBARNOTIFY
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
#endif
    class rebar {
    private:
        std::vector<HWND> rebar_handles = {};
        sync::rwlock rebar_rwlock = {};
        uint32_t error_code = 0;

    public:
        rebar(const rebar &other) = delete;

        rebar(rebar &&other) = delete;

        rebar &operator=(const rebar &other) = delete;

        rebar &operator=(rebar &&other) = delete;

        rebar();

        ~rebar();

        HWND create(HWND parent_window_handle,
                    LPARAM lparam,
                    int32_t x = 0,
                    int32_t y = 0,
                    int32_t width = 0,
                    int32_t height = 0,
                    RebarStyle style = RebarStyle::VarHeight |
                            RebarStyle::BandBorders | RebarStyle::AutoSize |
                            CommonStyle::Adjustable,
                    WindowStyle window_style = WindowStyle::Child |
                            WindowStyle::Visible | WindowStyle::ClipSiblings |
                            WindowStyle::ClipChildren);

        HWND create(const char *rebar_name,
                    HWND parent_window_handle,
                    LPARAM lparam,
                    int32_t x = 0,
                    int32_t y = 0,
                    int32_t width = 0,
                    int32_t height = 0,
                    RebarStyle style = RebarStyle::VarHeight |
                            RebarStyle::BandBorders | RebarStyle::AutoSize |
                            CommonStyle::Adjustable,
                    WindowStyle window_style = WindowStyle::Child |
                            WindowStyle::Visible | WindowStyle::ClipSiblings |
                            WindowStyle::ClipChildren);

        HWND create(const wchar_t *rebar_name,
                    HWND parent_window_handle,
                    LPARAM lparam,
                    int32_t x = 0,
                    int32_t y = 0,
                    int32_t width = 0,
                    int32_t height = 0,
                    RebarStyle style = RebarStyle::VarHeight |
                            RebarStyle::BandBorders | RebarStyle::AutoSize |
                            CommonStyle::Adjustable,
                    WindowStyle window_style = WindowStyle::Child |
                            WindowStyle::Visible | WindowStyle::ClipSiblings |
                            WindowStyle::ClipChildren);

        bool destroy(HWND rebar_handle);

        void begin_drag(HWND rebar_handle, int32_t index, POINT point);

        void move_drag(HWND rebar_handle, POINT point);

        void end_drag(HWND rebar_handle);

        bool insert_band(HWND rebar_handle,
                         REBARBANDINFOW *band_info,
                         int32_t index = -1);

        bool move_band(HWND rebar_handle, int32_t index_from, int32_t index_to);

        bool delete_band(HWND rebar_handle, int32_t index);

        bool show_band(HWND rebar_handle, int32_t index);

        bool hide_band(HWND rebar_handle, int32_t index);

        void maximize_band(HWND rebar_handle,
                           int32_t index,
                           int32_t ideal_width = 0);

        void minimize_band(HWND rebar_handle, int32_t index);

        void get_band_borders(HWND rebar_handle, int32_t index, RECT *rect);

        uint32_t get_band_count(HWND rebar_handle);

        bool get_band_info(HWND rebar_handle,
                           int32_t index,
                           REBARBANDINFOW *band_info);

        bool set_band_info(HWND rebar_handle,
                           int32_t index,
                           REBARBANDINFOW *band_info);

        void get_band_margins(HWND rebar_handle, MARGINS *margin);

        bool set_band_width(HWND rebar_handle, int32_t index, int32_t width);

        uint32_t get_height(HWND rebar_handle);

        bool get_info(HWND rebar_handle, REBARINFO *info);

        bool set_info(HWND rebar_handle, REBARINFO *info);

        COLORREF get_background_color(HWND rebar_handle);

        COLORREF set_background_color(HWND rebar_handle, COLORREF color);

        bool get_color_scheme(HWND rebar_handle, COLORSCHEME *color_scheme);

        void set_color_scheme(HWND rebar_handle, COLORSCHEME *color_scheme);

        void get_drop_target(HWND rebar_handle, IDropTarget **target);

        COLORREF get_text_color(HWND rebar_handle);

        COLORREF set_text_color(HWND rebar_handle, COLORREF color);

        HPALETTE get_palette(HWND rebar_handle);

        HPALETTE set_palette(HWND rebar_handle, HPALETTE palette);

        bool get_rect(HWND rebar_handle, int32_t index, RECT *rect);

        uint32_t get_row_count(HWND rebar_handle);

        uint32_t get_row_height(HWND rebar_handle, int32_t index);

        HWND get_tool_tips(HWND rebar_handle);

        void set_tool_tips(HWND rebar_handle, HWND tool_tips_handle);

        bool is_ansi_format(HWND rebar_handle);

        bool is_unicode_format(HWND rebar_handle);

        void set_ansi_format(HWND rebar_handle);

        void set_unicode_format(HWND rebar_handle);

        int32_t hit_test(HWND rebar_handle, RBHITTESTINFO *hit_test_info);

        int32_t id_to_index(HWND rebar_handle, uint32_t id);

        void push_chevron(HWND rebar_handle, int32_t index, int32_t value);

        HWND set_parent(HWND rebar_handle, HWND parent_window_handle);

        void
        set_window_theme(HWND rebar_handle,
                         std::string &theme /* "Explorer" */,
                         helper::CodePage code_page = helper::curr_code_page());

        void set_window_theme(HWND rebar_handle,
                              std::wstring &theme /* L"Explorer" */);

        bool size_to_rect(HWND rebar_handle, RECT *rect);

        [[nodiscard]] uint32_t err_code() const;

        [[nodiscard]] std::string err_string() const;

        [[nodiscard]] std::wstring err_wstring() const;
    };
} // namespace YanLib::ui::components
#endif // REBAR_H
