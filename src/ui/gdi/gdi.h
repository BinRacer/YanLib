/* clang-format off */
/*
 * @file gdi.h
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
#ifndef GDI_H
#define GDI_H
#include <wingdi.h>
#include <WinUser.h>
#include <cstdint>
namespace YanLib::ui::gdi {
    enum class PointType : uint8_t {
        CloseFigure = PT_CLOSEFIGURE,
        LineTo = PT_LINETO,
        BezierTo = PT_BEZIERTO,
        MoveTo = PT_MOVETO,
    };

    inline PointType operator|(PointType a, PointType b) {
        return static_cast<PointType>(static_cast<uint8_t>(a) |
                                      static_cast<uint8_t>(b));
    }

    enum class TernaryRasterCode : uint32_t {
        SrcCopy = SRCCOPY,         /* dest = source                   */
        SrcPaint = SRCPAINT,       /* dest = source OR dest           */
        SrcAnd = SRCAND,           /* dest = source AND dest          */
        SrcInvert = SRCINVERT,     /* dest = source XOR dest          */
        SrcErase = SRCERASE,       /* dest = source AND (NOT dest )   */
        NotSrcCopy = NOTSRCCOPY,   /* dest = (NOT source)             */
        NotSrcErase = NOTSRCERASE, /* dest = (NOT src) AND (NOT dest) */
        MergeCopy = MERGECOPY,     /* dest = (source AND pattern)     */
        MergePaint = MERGEPAINT,   /* dest = (NOT source) OR dest     */
        PatCopy = PATCOPY,         /* dest = pattern                  */
        PatPaint = PATPAINT,       /* dest = DPSnoo                   */
        PatInvert = PATINVERT,     /* dest = pattern XOR dest         */
        DstInvert = DSTINVERT,     /* dest = (NOT dest)               */
        Blackness = BLACKNESS,     /* dest = BLACK                    */
        Whiteness = WHITENESS,     /* dest = WHITE                    */
        NoMirrorBitmap = NOMIRRORBITMAP,
        /* Do not Mirror the bitmap in this call */
        CaptureBlt = CAPTUREBLT, /* Include layered windows */
    };

    inline TernaryRasterCode operator|(TernaryRasterCode a,
                                       TernaryRasterCode b) {
        return static_cast<TernaryRasterCode>(static_cast<uint32_t>(a) |
                                              static_cast<uint32_t>(b));
    }

    enum class GradientMode : uint32_t {
        RectH = GRADIENT_FILL_RECT_H,
        RectV = GRADIENT_FILL_RECT_V,
        Triangle = GRADIENT_FILL_TRIANGLE,
    };

    enum class FloodFill : uint32_t {
        Border = FLOODFILLBORDER,
        Surface = FLOODFILLSURFACE,
    };

    enum class StretchMode : int32_t {
        BlackOnWhite = BLACKONWHITE,
        WhiteOnBlack = WHITEONBLACK,
        ColorOnColor = COLORONCOLOR,
        HalfTone = HALFTONE,
        MaxStretchBltMode = MAXSTRETCHBLTMODE,
        StretchAndScans = STRETCH_ANDSCANS,
        StretchOrScans = STRETCH_ORSCANS,
        StretchDeleteScans = STRETCH_DELETESCANS,
        StretchHalfTone = STRETCH_HALFTONE,
    };

    enum class BrushStyle : uint32_t {
        Solid = BS_SOLID,
        Null = BS_NULL,
        Hollow = BS_HOLLOW,
        Hatched = BS_HATCHED,
        Pattern = BS_PATTERN,
        Indexed = BS_INDEXED,
        DibPattern = BS_DIBPATTERN,
        DibPatternPt = BS_DIBPATTERNPT,
        Pattern8X8 = BS_PATTERN8X8,
        DibPattern8X8 = BS_DIBPATTERN8X8,
        MonoPattern = BS_MONOPATTERN,
    };

    enum class HatchStyle : int32_t {
        Horizontal = HS_HORIZONTAL, /* ----- */
        Vertical = HS_VERTICAL,     /* ||||| */
        FDiagonal = HS_FDIAGONAL,   /* \\\\\ */
        BDiagonal = HS_BDIAGONAL,   /* ///// */
        Cross = HS_CROSS,           /* +++++ */
        DiagCross = HS_DIAGCROSS,   /* xxxxx */
    };

    enum class ColorType : int32_t {
        Scrollbar = COLOR_SCROLLBAR,
        Background = COLOR_BACKGROUND,
        ActiveCaption = COLOR_ACTIVECAPTION,
        InactiveCaption = COLOR_INACTIVECAPTION,
        Menu = COLOR_MENU,
        Window = COLOR_WINDOW,
        WindowFrame = COLOR_WINDOWFRAME,
        MenuText = COLOR_MENUTEXT,
        WindowText = COLOR_WINDOWTEXT,
        CaptionText = COLOR_CAPTIONTEXT,
        ActiveBorder = COLOR_ACTIVEBORDER,
        InactiveBorder = COLOR_INACTIVEBORDER,
        AppWorkspace = COLOR_APPWORKSPACE,
        Highlight = COLOR_HIGHLIGHT,
        HighlightText = COLOR_HIGHLIGHTTEXT,
        ButtonFace = COLOR_BTNFACE,
        ButtonShadow = COLOR_BTNSHADOW,
        GrayText = COLOR_GRAYTEXT,
        ButtonText = COLOR_BTNTEXT,
        InactiveCaptionText = COLOR_INACTIVECAPTIONTEXT,
        ButtonHighlight = COLOR_BTNHIGHLIGHT,
        DkShadow3d = COLOR_3DDKSHADOW,
        Light3d = COLOR_3DLIGHT,
        InfoText = COLOR_INFOTEXT,
        InfoBackground = COLOR_INFOBK,
        HotLight = COLOR_HOTLIGHT,
        GradientActiveCaption = COLOR_GRADIENTACTIVECAPTION,
        GradientInactiveCaption = COLOR_GRADIENTINACTIVECAPTION,
        MenuHighlight = COLOR_MENUHILIGHT,
        MenuBar = COLOR_MENUBAR,
        Desktop = COLOR_DESKTOP,
        Face3d = COLOR_3DFACE,
        Shadow3d = COLOR_3DSHADOW,
        Highlight3d = COLOR_3DHIGHLIGHT,
    };

    enum class RegionStyle : int32_t {
        And = RGN_AND,
        Or = RGN_OR,
        Xor = RGN_XOR,
        Diff = RGN_DIFF,
        Copy = RGN_COPY,
    };

    enum class RegionFlag : int32_t {
        Error = ERROR,
        NullRegion = NULLREGION,
        SimpleRegion = SIMPLEREGION,
        ComplexRegion = COMPLEXREGION,
    };

    enum class OrientationPreference : int32_t {
        None = ORIENTATION_PREFERENCE_NONE,
        Landscape = ORIENTATION_PREFERENCE_LANDSCAPE,
        Portrait = ORIENTATION_PREFERENCE_PORTRAIT,
        LandscapeFlipped = ORIENTATION_PREFERENCE_LANDSCAPE_FLIPPED,
        PortraitFlipped = ORIENTATION_PREFERENCE_PORTRAIT_FLIPPED,
    };

    inline OrientationPreference operator|(OrientationPreference a,
                                           OrientationPreference b) {
        return static_cast<OrientationPreference>(static_cast<int32_t>(a) |
                                                  static_cast<int32_t>(b));
    }

    enum class GraphicsMode : int32_t {
        None = 0,
        Compatible = GM_COMPATIBLE,
        Advanced = GM_ADVANCED,
    };

    enum class MappingMode : int32_t {
        Text = MM_TEXT,
        LoMetric = MM_LOMETRIC,
        HiMetric = MM_HIMETRIC,
        LoEnglish = MM_LOENGLISH,
        HiEnglish = MM_HIENGLISH,
        TwIps = MM_TWIPS,
        IsoTropic = MM_ISOTROPIC,
        AnIsoTropic = MM_ANISOTROPIC,
    };

    inline MappingMode operator|(MappingMode a, MappingMode b) {
        return static_cast<MappingMode>(static_cast<int32_t>(a) |
                                        static_cast<int32_t>(b));
    }

    enum class XFormMode : uint32_t {
        Identity = MWT_IDENTITY,
        LeftMultiply = MWT_LEFTMULTIPLY,
        RightMultiply = MWT_RIGHTMULTIPLY,
    };

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

    enum class StateFlag : uint32_t {
        AttachedToDesktop = DISPLAY_DEVICE_ATTACHED_TO_DESKTOP,
        MultiDriver = DISPLAY_DEVICE_MULTI_DRIVER,
        PrimaryDevice = DISPLAY_DEVICE_PRIMARY_DEVICE,
        MirroringDriver = DISPLAY_DEVICE_MIRRORING_DRIVER,
        VgaCompatible = DISPLAY_DEVICE_VGA_COMPATIBLE,
        Removable = DISPLAY_DEVICE_REMOVABLE,
        AccDriver = DISPLAY_DEVICE_ACC_DRIVER,
        ModeSpruned = DISPLAY_DEVICE_MODESPRUNED,
        RdpUdd = DISPLAY_DEVICE_RDPUDD,
        Remote = DISPLAY_DEVICE_REMOTE,
        Disconnect = DISPLAY_DEVICE_DISCONNECT,
        TsCompatible = DISPLAY_DEVICE_TS_COMPATIBLE,
        UnsafeModesOn = DISPLAY_DEVICE_UNSAFE_MODES_ON,
        Active = DISPLAY_DEVICE_ACTIVE,
        Attached = DISPLAY_DEVICE_ATTACHED,
    };

    enum class SettingMode : uint32_t {
        Current = ENUM_CURRENT_SETTINGS,
        Registry = ENUM_REGISTRY_SETTINGS,
    };

    enum class SettingFlag : uint32_t {
        RawMode = EDS_RAWMODE,
        RotatedMode = EDS_ROTATEDMODE,
    };

    inline SettingFlag operator|(SettingFlag a, SettingFlag b) {
        return static_cast<SettingFlag>(static_cast<uint32_t>(a) |
                                        static_cast<uint32_t>(b));
    }

    enum class GetDisplayConfig : uint32_t {
        AllPaths = QDC_ALL_PATHS,
        OnlyActivePaths = QDC_ONLY_ACTIVE_PATHS,
        DatabaseCurrent = QDC_DATABASE_CURRENT,
        VirtualModeAware = QDC_VIRTUAL_MODE_AWARE,
        IncludeHmd = QDC_INCLUDE_HMD,
        VirtualRefreshRateAware = QDC_VIRTUAL_REFRESH_RATE_AWARE,
    };

    inline GetDisplayConfig operator|(GetDisplayConfig a, GetDisplayConfig b) {
        return static_cast<GetDisplayConfig>(static_cast<uint32_t>(a) |
                                             static_cast<uint32_t>(b));
    }

    inline bool operator&(GetDisplayConfig a, GetDisplayConfig b) {
        return static_cast<uint32_t>(a) & static_cast<uint32_t>(b);
    }

    enum class TopologyID : int32_t {
        Internal = DISPLAYCONFIG_TOPOLOGY_INTERNAL,
        Clone = DISPLAYCONFIG_TOPOLOGY_CLONE,
        Extend = DISPLAYCONFIG_TOPOLOGY_EXTEND,
        External = DISPLAYCONFIG_TOPOLOGY_EXTERNAL,
        ForceUint32 = DISPLAYCONFIG_TOPOLOGY_FORCE_UINT32,
    };

    inline TopologyID operator|(TopologyID a, TopologyID b) {
        return static_cast<TopologyID>(static_cast<int32_t>(a) |
                                       static_cast<int32_t>(b));
    }

    enum class SetDisplayConfig : uint32_t {
        None = 0,
        TopologyInternal = SDC_TOPOLOGY_INTERNAL,
        TopologyClone = SDC_TOPOLOGY_CLONE,
        TopologyExtend = SDC_TOPOLOGY_EXTEND,
        TopologyExternal = SDC_TOPOLOGY_EXTERNAL,
        TopologySupplied = SDC_TOPOLOGY_SUPPLIED,
        UseDatabaseCurrent = SDC_USE_DATABASE_CURRENT,
        UseSuppliedDisplayConfig = SDC_USE_SUPPLIED_DISPLAY_CONFIG,
        Validate = SDC_VALIDATE,
        Apply = SDC_APPLY,
        NoOptimization = SDC_NO_OPTIMIZATION,
        SaveToDatabase = SDC_SAVE_TO_DATABASE,
        AllowChanges = SDC_ALLOW_CHANGES,
        PathPersistIfRequired = SDC_PATH_PERSIST_IF_REQUIRED,
        ForceModeEnumeration = SDC_FORCE_MODE_ENUMERATION,
        AllowPathOrderChanges = SDC_ALLOW_PATH_ORDER_CHANGES,
        VirtualModeAware = SDC_VIRTUAL_MODE_AWARE,
        VirtualRefreshRateAware = SDC_VIRTUAL_REFRESH_RATE_AWARE,
    };

    inline SetDisplayConfig operator|(SetDisplayConfig a, SetDisplayConfig b) {
        return static_cast<SetDisplayConfig>(static_cast<uint32_t>(a) |
                                             static_cast<uint32_t>(b));
    }

    enum class ChangedDisplayConfig : uint32_t {
        None = 0,
        UpdateRegistry = CDS_UPDATEREGISTRY,
        Test = CDS_TEST,
        FullScreen = CDS_FULLSCREEN,
        Global = CDS_GLOBAL,
        SetPrimary = CDS_SET_PRIMARY,
        VideoParameters = CDS_VIDEOPARAMETERS,
        EnableUnsafeModes = CDS_ENABLE_UNSAFE_MODES,
        DisableUnsafeModes = CDS_DISABLE_UNSAFE_MODES,
        Reset = CDS_RESET,
        ResetEx = CDS_RESET_EX,
        NoReset = CDS_NORESET,
    };

    inline ChangedDisplayConfig operator|(ChangedDisplayConfig a,
                                          ChangedDisplayConfig b) {
        return static_cast<ChangedDisplayConfig>(static_cast<uint32_t>(a) |
                                                 static_cast<uint32_t>(b));
    }

    enum class ChangedDisplayConfigResult : int32_t {
        Successful = DISP_CHANGE_SUCCESSFUL,
        Restart = DISP_CHANGE_RESTART,
        Failed = DISP_CHANGE_FAILED,
        BadMode = DISP_CHANGE_BADMODE,
        NotUpdated = DISP_CHANGE_NOTUPDATED,
        BadFlags = DISP_CHANGE_BADFLAGS,
        BadParam = DISP_CHANGE_BADPARAM,
        BadDualView = DISP_CHANGE_BADDUALVIEW,
    };

    enum class MonitorFlag : uint32_t {
        Null = MONITOR_DEFAULTTONULL,
        Primary = MONITOR_DEFAULTTOPRIMARY,
        Nearest = MONITOR_DEFAULTTONEAREST,
    };

    enum class Charset : uint32_t {
        ANSI = ANSI_CHARSET,
        DEFAULT = DEFAULT_CHARSET,
        SYMBOL = SYMBOL_CHARSET,
        SHIFTJIS = SHIFTJIS_CHARSET,
        HANGEUL = HANGEUL_CHARSET,
        HANGUL = HANGUL_CHARSET,
        GB2312 = GB2312_CHARSET,
        CHINESEBIG5 = CHINESEBIG5_CHARSET,
        OEM = OEM_CHARSET,
        JOHAB = JOHAB_CHARSET,
        HEBREW = HEBREW_CHARSET,
        ARABIC = ARABIC_CHARSET,
        GREEK = GREEK_CHARSET,
        TURKISH = TURKISH_CHARSET,
        VIETNAMESE = VIETNAMESE_CHARSET,
        THAI = THAI_CHARSET,
        EASTEUROPE = EASTEUROPE_CHARSET,
        RUSSIAN = RUSSIAN_CHARSET,
        MAC = MAC_CHARSET,
        BALTIC = BALTIC_CHARSET,
    };

    enum class FontWeight : int32_t {
        DontCare = FW_DONTCARE,
        Thin = FW_THIN,
        ExtraLight = FW_EXTRALIGHT,
        Light = FW_LIGHT,
        Normal = FW_NORMAL,
        Medium = FW_MEDIUM,
        SemiBold = FW_SEMIBOLD,
        Bold = FW_BOLD,
        ExtraBold = FW_EXTRABOLD,
        Heavy = FW_HEAVY,
        UltraLight = FW_ULTRALIGHT,
        Regular = FW_REGULAR,
        DemiBold = FW_DEMIBOLD,
        UltraBold = FW_ULTRABOLD,
        Black = FW_BLACK,
    };

    enum class FontOutPrecision : uint32_t {
        Default = OUT_DEFAULT_PRECIS,
        String = OUT_STRING_PRECIS,
        Character = OUT_CHARACTER_PRECIS,
        Stroke = OUT_STROKE_PRECIS,
        TrueType = OUT_TT_PRECIS,
        Device = OUT_DEVICE_PRECIS,
        Raster = OUT_RASTER_PRECIS,
        TrueTypeOnly = OUT_TT_ONLY_PRECIS,
        Outline = OUT_OUTLINE_PRECIS,
        ScreenOutline = OUT_SCREEN_OUTLINE_PRECIS,
        PostScriptOnly = OUT_PS_ONLY_PRECIS,
    };

    enum class FontClipPrecision : uint32_t {
        Default = CLIP_DEFAULT_PRECIS,
        Character = CLIP_CHARACTER_PRECIS,
        Stroke = CLIP_STROKE_PRECIS,
        Mask = CLIP_MASK,
        LHAngles = CLIP_LH_ANGLES,
        TrueTypeAlways = CLIP_TT_ALWAYS,
        DFADisable = CLIP_DFA_DISABLE,
        Embedded = CLIP_EMBEDDED,
    };

    enum class FontQuality : uint32_t {
        Default = DEFAULT_QUALITY,
        Draft = DRAFT_QUALITY,
        Proof = PROOF_QUALITY,
        NonAntiAliased = NONANTIALIASED_QUALITY,
        AntiAliased = ANTIALIASED_QUALITY,
        ClearType = CLEARTYPE_QUALITY,
        ClearTypeNatural = CLEARTYPE_NATURAL_QUALITY,
    };

    enum class FontPitch : uint32_t {
        Default = DEFAULT_PITCH,
        Fixed = FIXED_PITCH,
        Variable = VARIABLE_PITCH,
    };

    enum class FontFamily : uint32_t {
        DontCare = FF_DONTCARE,
        Roman = FF_ROMAN,
        Swiss = FF_SWISS,
        Modern = FF_MODERN,
        Script = FF_SCRIPT,
        Decorative = FF_DECORATIVE,
    };

    enum class FontType : uint32_t {
        Private = FR_PRIVATE,
        NotEnum = FR_NOT_ENUM,
    };

    enum class LangInfo : uint32_t {
        DBCS = GCP_DBCS,
        ReOrder = GCP_REORDER,
        UseKerning = GCP_USEKERNING,
        GlyphShape = GCP_GLYPHSHAPE,
        Ligate = GCP_LIGATE,
        Diacritic = GCP_DIACRITIC,
        Kashida = GCP_KASHIDA,
        Error = GCP_ERROR,
        Mask = FLI_MASK,
        Justify = GCP_JUSTIFY,
        Glyphs = FLI_GLYPHS,
        ClassIn = GCP_CLASSIN,
        MaxExtent = GCP_MAXEXTENT,
        JustifyIn = GCP_JUSTIFYIN,
        DisplayZWG = GCP_DISPLAYZWG,
        SymSwapOff = GCP_SYMSWAPOFF,
        NumericOverride = GCP_NUMERICOVERRIDE,
        NeutralOverride = GCP_NEUTRALOVERRIDE,
        NumericsLatin = GCP_NUMERICSLATIN,
        NumericsLocal = GCP_NUMERICSLOCAL,
    };

    inline LangInfo operator|(LangInfo a, LangInfo b) {
        return static_cast<LangInfo>(static_cast<uint32_t>(a) |
                                     static_cast<uint32_t>(b));
    }

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

    enum class FrameType : uint32_t {
        Caption = DFC_CAPTION,
        Menu = DFC_MENU,
        Scroll = DFC_SCROLL,
        Button = DFC_BUTTON,
        PopupMenu = DFC_POPUPMENU,
    };

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

    enum class BackGroundMode : int32_t {
        Opaque = OPAQUE,
        Transparent = TRANSPARENT,
    };

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

    enum class PaletteEntryFlag : uint8_t {
        None = 0,
        Reserved = PC_RESERVED,
        Explicit = PC_EXPLICIT,
        NoCollapse = PC_NOCOLLAPSE,
    };

    inline PaletteEntryFlag operator|(PaletteEntryFlag a, PaletteEntryFlag b) {
        return static_cast<PaletteEntryFlag>(static_cast<uint8_t>(a) |
                                             static_cast<uint8_t>(b));
    }

    enum class PaletteState : uint32_t {
        Error = SYSPAL_ERROR,
        Static = SYSPAL_STATIC,
        NoStatic = SYSPAL_NOSTATIC,
        NoStatic256 = SYSPAL_NOSTATIC256,
    };

    enum class PenStyle : uint32_t {
        Solid = PS_SOLID,
        Dash = PS_DASH,             // -------
        Dot = PS_DOT,               // .......
        DashDot = PS_DASHDOT,       // _._._._
        DashDotDot = PS_DASHDOTDOT, // _.._.._
        Null = PS_NULL,
        InsideFrame = PS_INSIDEFRAME,
        UserStyle = PS_USERSTYLE,
        Alternate = PS_ALTERNATE,
        StyleMask = PS_STYLE_MASK,
        EndCapRound = PS_ENDCAP_ROUND,
        EndCapSquare = PS_ENDCAP_SQUARE,
        EndCapFlat = PS_ENDCAP_FLAT,
        EndCapMask = PS_ENDCAP_MASK,
        JoinRound = PS_JOIN_ROUND,
        JoinBevel = PS_JOIN_BEVEL,
        JoinMiter = PS_JOIN_MITER,
        JoinMask = PS_JOIN_MASK,
        Cosmetic = PS_COSMETIC,
        Geometric = PS_GEOMETRIC,
        TypeMask = PS_TYPE_MASK
    };

    inline PenStyle operator|(PenStyle a, PenStyle b) {
        return static_cast<PenStyle>(static_cast<uint32_t>(a) |
                                     static_cast<uint32_t>(b));
    }

    enum class AnimationType : int32_t {
        Open = IDANI_OPEN,
        Caption = IDANI_CAPTION,
    };

    enum class BoundFlag : uint32_t {
        Error = 0,
        Reset = DCB_RESET,
        Accumulate = DCB_ACCUMULATE,
        Dirty = DCB_DIRTY,
        Set = DCB_SET,
        Enable = DCB_ENABLE,
        Disable = DCB_DISABLE,
    };

    enum class FillMode : int32_t {
        Error = 0,
        Alternate = ALTERNATE,
        Winding = WINDING,
    };

    enum class OutputOption : uint32_t {
        Opaque = ETO_OPAQUE,
        Clipped = ETO_CLIPPED,
        GlyphIndex = ETO_GLYPH_INDEX,
        RtlReading = ETO_RTLREADING,
        NumericsLocal = ETO_NUMERICSLOCAL,
        NumericsLatin = ETO_NUMERICSLATIN,
        IgnoreLanguage = ETO_IGNORELANGUAGE,
        PDY = ETO_PDY,
        ReverseIndexMap = ETO_REVERSE_INDEX_MAP,
    };

    inline OutputOption operator|(OutputOption a, OutputOption b) {
        return static_cast<OutputOption>(static_cast<uint32_t>(a) |
                                         static_cast<uint32_t>(b));
    }

    enum class TextFormat : uint32_t {
        top = DT_TOP,
        left = DT_LEFT,
        center = DT_CENTER,
        right = DT_RIGHT,
        vCenter = DT_VCENTER,
        bottom = DT_BOTTOM,
        wordBreak = DT_WORDBREAK,
        singleLine = DT_SINGLELINE,
        expandTabs = DT_EXPANDTABS,
        tabStop = DT_TABSTOP,
        noClip = DT_NOCLIP,
        externalLeading = DT_EXTERNALLEADING,
        calcRect = DT_CALCRECT,
        noPrefix = DT_NOPREFIX,
        internal = DT_INTERNAL,
        editControl = DT_EDITCONTROL,
        pathEllipsis = DT_PATH_ELLIPSIS,
        endEllipsis = DT_END_ELLIPSIS,
        modifyString = DT_MODIFYSTRING,
        rtlReading = DT_RTLREADING,
        wordEllipsis = DT_WORD_ELLIPSIS,
        noFullwidthCharBreak = DT_NOFULLWIDTHCHARBREAK,
        hidePrefix = DT_HIDEPREFIX,
        prefixOnly = DT_PREFIXONLY,
    };

    inline TextFormat operator|(TextFormat a, TextFormat b) {
        return static_cast<TextFormat>(static_cast<uint32_t>(a) |
                                       static_cast<uint32_t>(b));
    }

    enum class DataFormat : uint32_t {
        Metrics = GGO_METRICS,
        Bitmap = GGO_BITMAP,
        Native = GGO_NATIVE,
        Bezier = GGO_BEZIER,
        Gray2Bitmap = GGO_GRAY2_BITMAP,
        Gray4Bitmap = GGO_GRAY4_BITMAP,
        Gray8Bitmap = GGO_GRAY8_BITMAP,
        GlyphIndex = GGO_GLYPH_INDEX,
        UnHinted = GGO_UNHINTED,
    };

    enum class AlignOption : uint32_t {
        Error = 0,
        NoUpdateCP = TA_NOUPDATECP,
        UpdateCP = TA_UPDATECP,
        Left = TA_LEFT,
        Right = TA_RIGHT,
        Center = TA_CENTER,
        Top = TA_TOP,
        Bottom = TA_BOTTOM,
        Baseline = TA_BASELINE,
        RtlReading = TA_RTLREADING,
        Mask = TA_MASK,
        VBaseline = VTA_BASELINE,
        VertLeft = VTA_LEFT,
        VertRight = VTA_RIGHT,
        VertCenter = VTA_CENTER,
        VertBottom = VTA_BOTTOM,
        VertTop = VTA_TOP,
    };

    inline AlignOption operator|(AlignOption a, AlignOption b) {
        return static_cast<AlignOption>(static_cast<uint32_t>(a) |
                                        static_cast<uint32_t>(b));
    }
} // namespace YanLib::ui::gdi
#endif // GDI_H
