/* clang-format off */
/*
 * @file dc.h
 * @date 2025-05-02
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
#ifndef DC_H
#define DC_H
#include <utility>
#include <Windows.h>

namespace YanLib::ui::gdi {
#ifndef DCFLAG
#define DCFLAG

    enum class DCFlag : uint32_t {
        Window = DCX_WINDOW,
        Cache = DCX_CACHE,
        NoReSetAttrs = DCX_NORESETATTRS,
        ClipChildren = DCX_CLIPCHILDREN,
        ClipSiblings = DCX_CLIPSIBLINGS,
        ParentClip = DCX_PARENTCLIP,
        ExcludeRegion = DCX_EXCLUDERGN,
        IntersectRegion = DCX_INTERSECTRGN,
        ExcludeUpdate = DCX_EXCLUDEUPDATE,
        IntersectUpdate = DCX_INTERSECTUPDATE,
        LockWindowUpdate = DCX_LOCKWINDOWUPDATE,
        Validate = DCX_VALIDATE,
    };

    inline DCFlag operator|(DCFlag a, DCFlag b) {
        return static_cast<DCFlag>(static_cast<uint32_t>(a) |
                                   static_cast<uint32_t>(b));
    }
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
#ifndef OBJECTTYPE
#define OBJECTTYPE

    enum class ObjectType : uint32_t {
        Pen = OBJ_PEN,
        Brush = OBJ_BRUSH,
        DC = OBJ_DC,
        MetaDC = OBJ_METADC,
        Palette = OBJ_PAL,
        Font = OBJ_FONT,
        Bitmap = OBJ_BITMAP,
        Region = OBJ_REGION,
        MetaFile = OBJ_METAFILE,
        MemDC = OBJ_MEMDC,
        ExtPen = OBJ_EXTPEN,
        EnhMetaDc = OBJ_ENHMETADC,
        EnhMetaFile = OBJ_ENHMETAFILE,
        ColorSpace = OBJ_COLORSPACE,
    };
#endif
#ifndef STOCKLOGICALOBJECT
#define STOCKLOGICALOBJECT

    enum class StockLogicalObject : int32_t {
        WhiteBrush = WHITE_BRUSH,
        LightGrayBrush = LTGRAY_BRUSH,
        GrayBrush = GRAY_BRUSH,
        DarkGrayBrush = DKGRAY_BRUSH,
        BlackBrush = BLACK_BRUSH,
        NullBrush = NULL_BRUSH,
        HollowBrush = HOLLOW_BRUSH,
        WhitePen = WHITE_PEN,
        BlackPen = BLACK_PEN,
        NullPen = NULL_PEN,
        OemFixedFont = OEM_FIXED_FONT,
        AnsiFixedFont = ANSI_FIXED_FONT,
        AnsiVarFont = ANSI_VAR_FONT,
        SystemFont = SYSTEM_FONT,
        DeviceDefaultFont = DEVICE_DEFAULT_FONT,
        DefaultPalette = DEFAULT_PALETTE,
        SystemFixedFont = SYSTEM_FIXED_FONT,
        DefaultGuiFont = DEFAULT_GUI_FONT,
        DCBrush = DC_BRUSH,
        DCPen = DC_PEN,
    };
#endif
#ifndef DEVICEPARAMETER
#define DEVICEPARAMETER

    enum class DeviceParameter : int32_t {
        DriverVersion = DRIVERVERSION,
        Technology = TECHNOLOGY,
        HorizSize = HORZSIZE,
        VertSize = VERTSIZE,
        HorizRes = HORZRES,
        VertRes = VERTRES,
        BitsPixel = BITSPIXEL,
        Planes = PLANES,
        NumBrushes = NUMBRUSHES,
        NumPens = NUMPENS,
        NumMarkers = NUMMARKERS,
        NumFonts = NUMFONTS,
        NumColors = NUMCOLORS,
        PDeviceSize = PDEVICESIZE,
        CurveCaps = CURVECAPS,
        LineCaps = LINECAPS,
        PolygonalCaps = POLYGONALCAPS,
        TextCaps = TEXTCAPS,
        ClipCaps = CLIPCAPS,
        RasterCaps = RASTERCAPS,
        AspectX = ASPECTX,
        AspectY = ASPECTY,
        AspectXY = ASPECTXY,
        LogPixelsX = LOGPIXELSX,
        LogPixelsY = LOGPIXELSY,
        SizePalette = SIZEPALETTE,
        NumReserved = NUMRESERVED,
        ColorRes = COLORRES,
        PhysicalWidth = PHYSICALWIDTH,
        PhysicalHeight = PHYSICALHEIGHT,
        PhysicalOffsetX = PHYSICALOFFSETX,
        PhysicalOffsetY = PHYSICALOFFSETY,
        ScalingFactorX = SCALINGFACTORX,
        ScalingFactorY = SCALINGFACTORY,
        VRefresh = VREFRESH,
        DesktopVertRes = DESKTOPVERTRES,
        DesktopHorizRes = DESKTOPHORZRES,
        BltAlignment = BLTALIGNMENT,
        ShadeBlendCaps = SHADEBLENDCAPS,
        ColorMgmtCaps = COLORMGMTCAPS,
    };
#endif
#ifndef DEVICECAPABILITY
#define DEVICECAPABILITY

    enum class DeviceCapability : uint16_t {
        Fields = DC_FIELDS,
        Papers = DC_PAPERS,
        PaperSize = DC_PAPERSIZE,
        MinExtent = DC_MINEXTENT,
        MaxExtent = DC_MAXEXTENT,
        Bins = DC_BINS,
        Duplex = DC_DUPLEX,
        Size = DC_SIZE,
        Extra = DC_EXTRA,
        Version = DC_VERSION,
        Driver = DC_DRIVER,
        BinNames = DC_BINNAMES,
        EnumResolutions = DC_ENUMRESOLUTIONS,
        FileDependencies = DC_FILEDEPENDENCIES,
        TrueType = DC_TRUETYPE,
        PaperNames = DC_PAPERNAMES,
        Orientation = DC_ORIENTATION,
        Copies = DC_COPIES,
        BinAdjust = DC_BINADJUST,
        EmfCompliant = DC_EMF_COMPLIANT,
        DataTypeProduced = DC_DATATYPE_PRODUCED,
        Collate = DC_COLLATE,
        Manufacturer = DC_MANUFACTURER,
        Model = DC_MODEL,
        Personality = DC_PERSONALITY,
        PrintRate = DC_PRINTRATE,
        PrintRateUnit = DC_PRINTRATEUNIT,
        PrinterMem = DC_PRINTERMEM,
        MediaReady = DC_MEDIAREADY,
        Staple = DC_STAPLE,
        PrintRatePpm = DC_PRINTRATEPPM,
        ColorDevice = DC_COLORDEVICE,
        Nup = DC_NUP,
        MediaTypeNames = DC_MEDIATYPENAMES,
        MediaTypes = DC_MEDIATYPES,
    };
#endif
    class dc {
    public:
        dc(const dc &other) = delete;

        dc(dc &&other) = delete;

        dc &operator=(const dc &other) = delete;

        dc &operator=(dc &&other) = delete;

        dc() = default;

        ~dc() = default;

        static HDC create(const char *driver_name /* "DISPLAY" */,
                          const char *device_name = nullptr,
                          const DEVMODEA *device_mode = nullptr);

        static HDC create(const wchar_t *driver_name /* L"DISPLAY" */,
                          const wchar_t *device_name = nullptr,
                          const DEVMODEW *device_mode = nullptr);

        static HDC create_compatible(HDC dc_handle);

        static HDC create_ic(const char *driver_name /* L"WINSPOOL" */,
                             const char *device_name
                             /* L"Microsoft Print to PDF" */,
                             const DEVMODEA *device_mode = nullptr);

        static HDC create_ic(const wchar_t *driver_name /* L"WINSPOOL" */,
                             const wchar_t *device_name
                             /* L"Microsoft Print to PDF" */,
                             const DEVMODEW *device_mode = nullptr);

        static HDC get(HWND window_handle);

        static HDC get(HWND window_handle,
                       HRGN region_clip_handle /* nullptr */,
                       DCFlag flag = DCFlag::Window | DCFlag::Cache |
                               DCFlag::ClipSiblings);

        static int32_t release(HWND window_handle, HDC dc_handle);

        static bool destroy(HDC dc_handle);

        // std::pair<result, error_code>
        static std::pair<bool, uint32_t>
        scroll(HDC dc_handle,
               int32_t x,
               int32_t y,
               const RECT *rect_scroll,
               const RECT *rect_clip = nullptr,
               HRGN region_update_handle = nullptr,
               RECT *rect_update = nullptr);

        // std::pair<Layout, error_code>
        static std::pair<Layout, uint32_t> get_layout(HDC dc_handle);

        static Layout set_layout(HDC dc_handle, Layout layout);

        static HDC get_window_dc(HWND window_handle);

        static HWND get_window(HDC dc_handle);

        static bool cancel(HDC dc_handle);

        static HDC reset(HDC dc_handle, const DEVMODEA *device_mode);

        static HDC reset(HDC dc_handle, const DEVMODEW *device_mode);

        static int32_t save(HDC dc_handle);

        static bool restore(HDC dc_handle, int32_t saved_dc_state);

        static COLORREF get_brush_color(HDC dc_handle);

        static COLORREF set_brush_color(HDC dc_handle, COLORREF color);

        static bool get_origin(HDC dc_handle, POINT *point);

        static COLORREF get_pen_color(HDC dc_handle);

        static COLORREF set_pen_color(HDC dc_handle, COLORREF color);

        static int32_t get_object(HANDLE gdi_handle, void *buf, int32_t size);

        static ObjectType get_object_type(HGDIOBJ gdi_obj_handle);

        static HGDIOBJ get_stock_object(StockLogicalObject type);

        static HGDIOBJ get_curr_object(HDC dc_handle, ObjectType type);

        static HGDIOBJ select_object(HDC dc_handle, HGDIOBJ gdi_obj_handle);

        static bool destroy_object(HGDIOBJ gdi_obj_handle);

        static int32_t enum_objects(HDC dc_handle,
                                    GOBJENUMPROC func,
                                    LPARAM lparam,
                                    ObjectType type);

        static int32_t get_device_caps(HDC dc_handle, DeviceParameter param);

        static int32_t device_capabilities(
                const char *device_name /* "Microsoft Print to PDF" */,
                const char *port /* "PORTPROMPT:" */,
                DeviceCapability capability /* DeviceCapability::PaperNames */,
                char *output,
                const DEVMODEA *device_mode = nullptr);

        static int32_t device_capabilities(
                const wchar_t *device_name /* L"Microsoft Print to PDF" */,
                const wchar_t *port /* L"PORTPROMPT:" */,
                DeviceCapability capability /* DeviceCapability::PaperNames */,
                wchar_t *output,
                const DEVMODEW *device_mode = nullptr);

        static int32_t draw_escape(HDC dc_handle,
                                   int32_t escape_func,
                                   const char *buf,
                                   int32_t size);
    };
} // namespace YanLib::ui::gdi
#endif // DC_H
