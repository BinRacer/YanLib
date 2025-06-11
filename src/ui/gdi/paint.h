/* clang-format off */
/*
 * @file paint.h
 * @date 2025-05-05
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
#ifndef PAINT_H
#define PAINT_H
#include <utility>
#include <Windows.h>
#include <string>

namespace YanLib::ui::gdi {
#ifndef DRAWOPTION
#define DRAWOPTION

    enum class DrawOption : uint32_t {
        None = 0,
        Active = DC_ACTIVE,
        SmallCap = DC_SMALLCAP,
        Icon = DC_ICON,
        Text = DC_TEXT,
        InButton = DC_INBUTTON,
        Gradient = DC_GRADIENT,
        Buttons = DC_BUTTONS,
    };

    inline DrawOption operator|(DrawOption a, DrawOption b) {
        return static_cast<DrawOption>(static_cast<uint32_t>(a) |
                                       static_cast<uint32_t>(b));
    }
#endif
#ifndef BORDERSTYLE
#define BORDERSTYLE

    enum class BorderStyle : uint32_t {
        // outer style
        RaisedOuter = BDR_RAISEDOUTER,
        SunkenOuter = BDR_SUNKENOUTER,
        // inner style
        RaisedInner = BDR_RAISEDINNER,
        SunkenInner = BDR_SUNKENINNER,
        // mixed style
        Raised = BDR_RAISED,
        Sunken = BDR_SUNKEN,
    };

    inline BorderStyle operator|(BorderStyle a, BorderStyle b) {
        return static_cast<BorderStyle>(static_cast<uint32_t>(a) |
                                        static_cast<uint32_t>(b));
    }
#endif
#ifndef BORDERFLAG
#define BORDERFLAG

    enum class BorderFlag : uint32_t {
        Left = BF_LEFT,
        Top = BF_TOP,
        Right = BF_RIGHT,
        Bottom = BF_BOTTOM,
        TopLeft = BF_TOPLEFT,
        TopRight = BF_TOPRIGHT,
        BottomLeft = BF_BOTTOMLEFT,
        BottomRight = BF_BOTTOMRIGHT,
        Rect = BF_RECT,
        Diagonal = BF_DIAGONAL,
        DiagonalEndTopRight = BF_DIAGONAL_ENDTOPRIGHT,
        DiagonalEndTopLeft = BF_DIAGONAL_ENDTOPLEFT,
        DiagonalEndBottomLeft = BF_DIAGONAL_ENDBOTTOMLEFT,
        DiagonalEndBottomRight = BF_DIAGONAL_ENDBOTTOMRIGHT,
        Middle = BF_MIDDLE,
        Soft = BF_SOFT,
        Adjust = BF_ADJUST,
        Flat = BF_FLAT,
        Mono = BF_MONO,
    };

    inline BorderFlag operator|(BorderFlag a, BorderFlag b) {
        return static_cast<BorderFlag>(static_cast<uint32_t>(a) |
                                       static_cast<uint32_t>(b));
    }
#endif
#ifndef IMAGETYPESTATE
#define IMAGETYPESTATE

    enum class ImageTypeState : uint32_t {
        // image type
        TypeComplex = DST_COMPLEX,
        TypeText = DST_TEXT,
        TypePrefixText = DST_PREFIXTEXT,
        TypeIcon = DST_ICON,
        TypeBitmap = DST_BITMAP,
        // state type
        StateNormal = DSS_NORMAL,
        StateUnion = DSS_UNION,
        StateDisabled = DSS_DISABLED,
        StateMono = DSS_MONO,
        StateHidePrefix = DSS_HIDEPREFIX,
        StatePrefixOnly = DSS_PREFIXONLY,
        StateRight = DSS_RIGHT,
    };

    inline ImageTypeState operator|(ImageTypeState a, ImageTypeState b) {
        return static_cast<ImageTypeState>(static_cast<uint32_t>(a) |
                                           static_cast<uint32_t>(b));
    }
#endif
#ifndef FRAMETYPE
#define FRAMETYPE

    enum class FrameType : uint32_t {
        Caption = DFC_CAPTION,
        Menu = DFC_MENU,
        Scroll = DFC_SCROLL,
        Button = DFC_BUTTON,
        PopupMenu = DFC_POPUPMENU,
    };
#endif
#ifndef FRAMESTATE
#define FRAMESTATE

    enum class FrameState : uint32_t {
        CaptionClose = DFCS_CAPTIONCLOSE,
        CaptionMin = DFCS_CAPTIONMIN,
        CaptionMax = DFCS_CAPTIONMAX,
        CaptionRestore = DFCS_CAPTIONRESTORE,
        CaptionHelp = DFCS_CAPTIONHELP,
        MenuArrow = DFCS_MENUARROW,
        MenuCheck = DFCS_MENUCHECK,
        MenuBullet = DFCS_MENUBULLET,
        MenuArrowRight = DFCS_MENUARROWRIGHT,
        ScrollUp = DFCS_SCROLLUP,
        ScrollDown = DFCS_SCROLLDOWN,
        ScrollLeft = DFCS_SCROLLLEFT,
        ScrollRight = DFCS_SCROLLRIGHT,
        ScrollComboBox = DFCS_SCROLLCOMBOBOX,
        ScrollSizeGrip = DFCS_SCROLLSIZEGRIP,
        ScrollSizeGripRight = DFCS_SCROLLSIZEGRIPRIGHT,
        ButtonCheck = DFCS_BUTTONCHECK,
        ButtonRadioImage = DFCS_BUTTONRADIOIMAGE,
        ButtonRadioMask = DFCS_BUTTONRADIOMASK,
        ButtonRadio = DFCS_BUTTONRADIO,
        Button3State = DFCS_BUTTON3STATE,
        ButtonPush = DFCS_BUTTONPUSH,
        Inactive = DFCS_INACTIVE,
        Pushed = DFCS_PUSHED,
        Checked = DFCS_CHECKED,
        Transparent1 = DFCS_TRANSPARENT,
        Hot = DFCS_HOT,
        AdjustRect = DFCS_ADJUSTRECT,
        Flat = DFCS_FLAT,
        Mono = DFCS_MONO,
    };

    inline FrameState operator|(FrameState a, FrameState b) {
        return static_cast<FrameState>(static_cast<uint32_t>(a) |
                                       static_cast<uint32_t>(b));
    }
#endif
#ifndef BACKGROUNDMODE
#define BACKGROUNDMODE

    enum class BackGroundMode : int32_t {
        Opaque = OPAQUE,
        Transparent = TRANSPARENT,
    };
#endif
#ifndef BINARYRASTERCODE
#define BINARYRASTERCODE

    enum class BinaryRasterCode : int32_t {
        Black = R2_BLACK,             /*  0       */
        NotMergePen = R2_NOTMERGEPEN, /* DPon     */
        MaskNotPen = R2_MASKNOTPEN,   /* DPna     */
        NotCopyPen = R2_NOTCOPYPEN,   /* PN       */
        MaskPenNot = R2_MASKPENNOT,   /* PDna     */
        Not = R2_NOT,                 /* Dn       */
        XorPen = R2_XORPEN,           /* DPx      */
        NotMaskPen = R2_NOTMASKPEN,   /* DPan     */
        MaskPen = R2_MASKPEN,         /* DPa      */
        NotXorPen = R2_NOTXORPEN,     /* DPxn     */
        Nop = R2_NOP,                 /* D        */
        MergeNotPen = R2_MERGENOTPEN, /* DPno     */
        CopyPen = R2_COPYPEN,         /* P        */
        MergePenNot = R2_MERGEPENNOT, /* PDno     */
        MergePen = R2_MERGEPEN,       /* DPo      */
        White = R2_WHITE,             /*  1       */
    };

    inline BinaryRasterCode operator|(BinaryRasterCode a, BinaryRasterCode b) {
        return static_cast<BinaryRasterCode>(static_cast<int32_t>(a) |
                                             static_cast<int32_t>(b));
    }
#endif
    class paint {
    public:
        paint(const paint &other) = delete;

        paint(paint &&other) = delete;

        paint &operator=(const paint &other) = delete;

        paint &operator=(paint &&other) = delete;

        paint() = default;

        ~paint() = default;

        static HDC begin(HWND window_handle, PAINTSTRUCT *paint_struct);

        static bool end(HWND window_handle, const PAINTSTRUCT *paint_struct);

        static bool draw_caption(HWND window_handle,
                                 HDC dc_handle,
                                 const RECT *rect,
                                 DrawOption option);

        static bool draw_edge(HDC dc_handle,
                              RECT *rect,
                              BorderStyle border = BorderStyle::Raised,
                              BorderFlag flag = BorderFlag::Rect);

        static bool draw_state(HDC dc_handle,
                               HBRUSH brush_handle,
                               DRAWSTATEPROC draw_state_proc,
                               LPARAM lparam,
                               WPARAM wparam,
                               int32_t x,
                               int32_t y,
                               int32_t width,
                               int32_t height,
                               ImageTypeState flag);

        static bool draw_frame_control(HDC hdc,
                                       RECT *rect,
                                       FrameType type,
                                       FrameState state);

        static uint32_t get_gdi_batch_limit();

        static uint32_t set_gdi_batch_limit(uint32_t limit);

        static COLORREF get_background_color(HDC dc_handle);

        static COLORREF set_background_color(HDC dc_handle, COLORREF color);

        static BackGroundMode get_background_mode(HDC dc_handle);

        static BackGroundMode set_background_mode(HDC dc_handle,
                                                  BackGroundMode mode);

        static BinaryRasterCode get_rop2(HDC dc_handle);

        static BinaryRasterCode set_rop2(HDC dc_handle, BinaryRasterCode mode);

        static bool gray_string(HDC dc_handle,
                                HBRUSH brush_handle,
                                GRAYSTRINGPROC gray_string_proc,
                                LPARAM lparam,
                                int32_t char_num,
                                int32_t x,
                                int32_t y,
                                int32_t width,
                                int32_t height);

        static std::pair<int32_t, uint32_t>
        load_string(HINSTANCE instance_handle, uint32_t id, std::string &text);

        static std::pair<int32_t, uint32_t>
        load_string(HINSTANCE instance_handle, uint32_t id, std::wstring &text);

        static bool gdi_flush();
    };
} // namespace YanLib::ui::gdi
#endif // PAINT_H
