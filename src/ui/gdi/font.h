/* clang-format off */
/*
 * @file font.h
 * @date 2025-05-03
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
#ifndef FONT_H
#define FONT_H
#include <cstdint>
#include <Windows.h>

namespace YanLib::ui::gdi {
#ifndef CHARSET
#define CHARSET

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
#endif
#ifndef FONTWEIGHT
#define FONTWEIGHT

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
#endif
#ifndef FONTOUTPRECISION
#define FONTOUTPRECISION

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
#endif
#ifndef FONTCLIPPRECISION
#define FONTCLIPPRECISION

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
#endif
#ifndef FONTQUALITY
#define FONTQUALITY

    enum class FontQuality : uint32_t {
        Default = DEFAULT_QUALITY,
        Draft = DRAFT_QUALITY,
        Proof = PROOF_QUALITY,
        NonAntiAliased = NONANTIALIASED_QUALITY,
        AntiAliased = ANTIALIASED_QUALITY,
        ClearType = CLEARTYPE_QUALITY,
        ClearTypeNatural = CLEARTYPE_NATURAL_QUALITY,
    };
#endif
#ifndef FONTPITCH
#define FONTPITCH

    enum class FontPitch : uint32_t {
        Default = DEFAULT_PITCH,
        Fixed = FIXED_PITCH,
        Variable = VARIABLE_PITCH,
    };
#endif
#ifndef FONTFAMILY
#define FONTFAMILY

    enum class FontFamily : uint32_t {
        DontCare = FF_DONTCARE,
        Roman = FF_ROMAN,
        Swiss = FF_SWISS,
        Modern = FF_MODERN,
        Script = FF_SCRIPT,
        Decorative = FF_DECORATIVE,
    };
#endif
#ifndef FONTTYPE
#define FONTTYPE
    enum class FontType : uint32_t {
        Private = FR_PRIVATE,
        NotEnum = FR_NOT_ENUM,
    };
#endif
#ifndef LANGINFO
#define LANGINFO
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
#endif
    class font {
    public:
        font(const font &other) = delete;

        font(font &&other) = delete;

        font &operator=(const font &other) = delete;

        font &operator=(font &&other) = delete;

        font() = default;

        ~font() = default;

        static HFONT create(const char *face_name /* "宋体" */,
                            Charset charset = Charset::GB2312,
                            int32_t height = 12,
                            int32_t width = 0,
                            int32_t escapement = 0,
                            int32_t orientation = 0,
                            FontWeight weight = FontWeight::DontCare,
                            bool is_italic = false,
                            bool is_underline = false,
                            bool is_strike_out = false,
                            FontOutPrecision output = FontOutPrecision::Default,
                            FontClipPrecision clip = FontClipPrecision::Default,
                            FontQuality quality = FontQuality::Default,
                            FontPitch pitch = FontPitch::Default,
                            FontFamily family = FontFamily::DontCare);

        static HFONT create(const wchar_t *face_name /* L"宋体" */,
                            Charset charset = Charset::GB2312,
                            int32_t height = 12,
                            int32_t width = 0,
                            int32_t escapement = 0,
                            int32_t orientation = 0,
                            FontWeight weight = FontWeight::DontCare,
                            bool is_italic = false,
                            bool is_underline = false,
                            bool is_strike_out = false,
                            FontOutPrecision output = FontOutPrecision::Default,
                            FontClipPrecision clip = FontClipPrecision::Default,
                            FontQuality quality = FontQuality::Default,
                            FontPitch pitch = FontPitch::Default,
                            FontFamily family = FontFamily::DontCare);

        static HFONT create(const LOGFONTA *log_font);

        static HFONT create(const LOGFONTW *log_font);

        static LOGFONTA
        make(const char *face_name /* "宋体" */,
             Charset charset = Charset::GB2312,
             int32_t height = 12,
             int32_t width = 0,
             int32_t escapement = 0,
             int32_t orientation = 0,
             FontWeight weight = FontWeight::DontCare,
             bool is_italic = false,
             bool is_underline = false,
             bool is_strike_out = false,
             FontOutPrecision output = FontOutPrecision::Default,
             FontClipPrecision clip = FontClipPrecision::Default,
             FontQuality quality = FontQuality::Default,
             FontPitch pitch = FontPitch::Default,
             FontFamily family = FontFamily::DontCare);

        static LOGFONTW
        make(const wchar_t *face_name /* L"宋体" */,
             Charset charset = Charset::GB2312,
             int32_t height = 12,
             int32_t width = 0,
             int32_t escapement = 0,
             int32_t orientation = 0,
             FontWeight weight = FontWeight::DontCare,
             bool is_italic = false,
             bool is_underline = false,
             bool is_strike_out = false,
             FontOutPrecision output = FontOutPrecision::Default,
             FontClipPrecision clip = FontClipPrecision::Default,
             FontQuality quality = FontQuality::Default,
             FontPitch pitch = FontPitch::Default,
             FontFamily family = FontFamily::DontCare);

        static HFONT create(const ENUMLOGFONTEXDVA *enum_log_font);

        static HFONT create(const ENUMLOGFONTEXDVW *enum_log_font);

        static bool destroy(HFONT font_handle);

        static HANDLE add_mem_resource(void *file_view,
                                       uint32_t file_view_size,
                                       uint32_t *num_fonts);

        static bool remove_mem_resource(HANDLE font_res_handle);

        static int32_t add_resource(const char *font_file_name);

        static int32_t add_resource(const wchar_t *font_file_name);

        static bool remove_resource(const char *font_file_name);

        static bool remove_resource(const wchar_t *font_file_name);

        static int32_t add_resource(const char *font_file_name,
                                    FontType type /* FontType::NotEnum */);

        static int32_t add_resource(const wchar_t *font_file_name,
                                    FontType type /* FontType::NotEnum */);

        static int32_t remove_resource(const char *font_file_name,
                                       FontType type /* FontType::NotEnum */);

        static int32_t remove_resource(const wchar_t *font_file_name,
                                       FontType type /* FontType::NotEnum */);

        static int32_t enum_families(HDC dc_handle,
                                     LOGFONTA *log_font,
                                     FONTENUMPROCA font_enum_proc,
                                     LPARAM lparam);

        static int32_t enum_families(HDC dc_handle,
                                     LOGFONTW *log_font,
                                     FONTENUMPROCW font_enum_proc,
                                     LPARAM lparam);

        static uint32_t get_data(HDC dc_handle,
                                 void *buf,
                                 uint32_t size,
                                 uint32_t table = 0x6E616D65 /* name table */,
                                 uint32_t offset = 0);

        static LangInfo get_language_info(HDC dc_handle);

        static uint32_t get_unicode_ranges(HDC dc_handle, GLYPHSET *glyph_set);
    };
} // namespace YanLib::ui::gdi
#endif // FONT_H
