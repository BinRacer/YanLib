/* clang-format off */
/*
 * @file label.h
 * @date 2025-05-31
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
#ifndef LABEL_H
#define LABEL_H
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
#ifndef LABELSTYLE
#define LABELSTYLE
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
#endif
#ifndef LABELMESSAGE
#define LABELMESSAGE
    enum class LabelMessage : uint32_t {
        GetIcon = STM_GETICON,
        GetImage = STM_GETIMAGE,
        SetIcon = STM_SETICON,
        SetImage = STM_SETIMAGE,
    };
#endif
#ifndef LABELNOTIFY
#define LABELNOTIFY
    enum class LabelNotify : uint32_t {
        Clicked = STN_CLICKED,
        DoubleClick = STN_DBLCLK,
        Disable = STN_DISABLE,
        Enable = STN_ENABLE,
        CtlColorStatic = WM_CTLCOLORSTATIC,
    };
#endif
    class label {
    private:
        std::vector<HWND> label_handles = {};
        sync::rwlock label_rwlock = {};
        uint32_t error_code = 0;

    public:
        label(const label &other) = delete;

        label(label &&other) = delete;

        label &operator=(const label &other) = delete;

        label &operator=(label &&other) = delete;

        label() = default;

        ~label();

        HWND create(uintptr_t label_id,
                    HWND parent_window_handle,
                    LPARAM lparam,
                    int32_t x,
                    int32_t y,
                    int32_t width,
                    int32_t height,
                    LabelStyle style = LabelStyle::Center,
                    WindowStyle window_style = WindowStyle::Child |
                            WindowStyle::Visible);

        HWND create(const char *label_name,
                    uintptr_t label_id,
                    HWND parent_window_handle,
                    LPARAM lparam,
                    int32_t x,
                    int32_t y,
                    int32_t width,
                    int32_t height,
                    LabelStyle style = LabelStyle::Center,
                    WindowStyle window_style = WindowStyle::Child |
                            WindowStyle::Visible);

        HWND create(const wchar_t *label_name,
                    uintptr_t label_id,
                    HWND parent_window_handle,
                    LPARAM lparam,
                    int32_t x,
                    int32_t y,
                    int32_t width,
                    int32_t height,
                    LabelStyle style = LabelStyle::Center,
                    WindowStyle window_style = WindowStyle::Child |
                            WindowStyle::Visible);

        bool destroy(HWND label_handle);

        bool enable(HWND label_handle);

        bool disable(HWND label_handle);

        HICON get_icon(HWND label_handle);

        HICON set_icon(HWND label_handle, HICON icon_handle);

        HBITMAP get_bitmap(HWND label_handle);

        HBITMAP set_bitmap(HWND label_handle, HBITMAP bitmap_handle);

        HCURSOR get_cursor(HWND label_handle);

        HCURSOR set_cursor(HWND label_handle, HCURSOR cursor_handle);

        HENHMETAFILE get_enh_metafile(HWND label_handle);

        HENHMETAFILE set_enh_metafile(HWND label_handle,
                                      HENHMETAFILE enh_metafile_handle);

        int32_t get_text(HWND label_handle, std::string &text);

        int32_t get_text(HWND label_handle, std::wstring &text);

        int32_t set_text(HWND label_handle, const std::string &text);

        int32_t set_text(HWND label_handle, const std::wstring &text);

        int32_t get_text_len(HWND label_handle);

        [[nodiscard]] uint32_t err_code() const;

        [[nodiscard]] std::string err_string() const;

        [[nodiscard]] std::wstring err_wstring() const;
    };
} // namespace YanLib::ui::components
#endif // LABEL_H
