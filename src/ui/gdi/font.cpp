/* clang-format off */
/*
 * @file font.cpp
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
#include "font.h"

namespace YanLib::ui::gdi {
    HFONT font::create(const char *face_name,
                       Charset charset,
                       int32_t height,
                       int32_t width,
                       int32_t escapement,
                       int32_t orientation,
                       FontWeight weight,
                       bool is_italic,
                       bool is_underline,
                       bool is_strike_out,
                       FontOutPrecision output,
                       FontClipPrecision clip,
                       FontQuality quality,
                       FontPitch pitch,
                       FontFamily family) {
        return CreateFontA(height, width, escapement, orientation,
                           static_cast<int32_t>(weight),
                           is_italic ? TRUE : FALSE,
                           is_underline ? TRUE : FALSE,
                           is_strike_out ? TRUE : FALSE,
                           static_cast<uint32_t>(charset),
                           static_cast<uint32_t>(output),
                           static_cast<uint32_t>(clip),
                           static_cast<uint32_t>(quality),
                           static_cast<uint32_t>(pitch) |
                                   static_cast<uint32_t>(family),
                           face_name);
    }

    HFONT font::create(const wchar_t *face_name,
                       Charset charset,
                       int32_t height,
                       int32_t width,
                       int32_t escapement,
                       int32_t orientation,
                       FontWeight weight,
                       bool is_italic,
                       bool is_underline,
                       bool is_strike_out,
                       FontOutPrecision output,
                       FontClipPrecision clip,
                       FontQuality quality,
                       FontPitch pitch,
                       FontFamily family) {
        return CreateFontW(height, width, escapement, orientation,
                           static_cast<int32_t>(weight),
                           is_italic ? TRUE : FALSE,
                           is_underline ? TRUE : FALSE,
                           is_strike_out ? TRUE : FALSE,
                           static_cast<uint32_t>(charset),
                           static_cast<uint32_t>(output),
                           static_cast<uint32_t>(clip),
                           static_cast<uint32_t>(quality),
                           static_cast<uint32_t>(pitch) |
                                   static_cast<uint32_t>(family),
                           face_name);
    }

    HFONT font::create(const LOGFONTA *log_font) {
        return CreateFontIndirectA(log_font);
    }

    HFONT font::create(const LOGFONTW *log_font) {
        return CreateFontIndirectW(log_font);
    }

    LOGFONTA font::make(const char *face_name,
                        Charset charset,
                        int32_t height,
                        int32_t width,
                        int32_t escapement,
                        int32_t orientation,
                        FontWeight weight,
                        bool is_italic,
                        bool is_underline,
                        bool is_strike_out,
                        FontOutPrecision output,
                        FontClipPrecision clip,
                        FontQuality quality,
                        FontPitch pitch,
                        FontFamily family) {
        LOGFONTA log_font = {};
        log_font.lfHeight = height;
        log_font.lfWidth = width;
        log_font.lfEscapement = escapement;
        log_font.lfOrientation = orientation;
        log_font.lfWeight = static_cast<int32_t>(weight);
        log_font.lfItalic = is_italic ? TRUE : FALSE;
        log_font.lfUnderline = is_underline ? TRUE : FALSE;
        log_font.lfStrikeOut = is_strike_out ? TRUE : FALSE;
        log_font.lfCharSet = static_cast<uint32_t>(charset) < UINT8_MAX
                ? static_cast<uint8_t>(charset)
                : static_cast<uint8_t>(Charset::DEFAULT);
        log_font.lfOutPrecision = static_cast<uint32_t>(output) < UINT8_MAX
                ? static_cast<uint8_t>(output)
                : static_cast<uint8_t>(FontOutPrecision::Default);
        log_font.lfClipPrecision = static_cast<uint32_t>(clip) < UINT8_MAX
                ? static_cast<uint8_t>(clip)
                : static_cast<uint8_t>(FontClipPrecision::Default);
        log_font.lfQuality = static_cast<uint32_t>(quality) < UINT8_MAX
                ? static_cast<uint8_t>(quality)
                : static_cast<uint8_t>(FontQuality::Default);
        log_font.lfPitchAndFamily =
                (static_cast<uint32_t>(pitch) < UINT8_MAX
                         ? static_cast<uint8_t>(pitch)
                         : static_cast<uint8_t>(FontPitch::Default)) |
                (static_cast<uint32_t>(family) < UINT8_MAX
                         ? static_cast<uint8_t>(family)
                         : static_cast<uint8_t>(FontFamily::DontCare));
        strcpy_s(log_font.lfFaceName, LF_FACESIZE, face_name);
        return log_font;
    }

    LOGFONTW font::make(const wchar_t *face_name,
                        Charset charset,
                        int32_t height,
                        int32_t width,
                        int32_t escapement,
                        int32_t orientation,
                        FontWeight weight,
                        bool is_italic,
                        bool is_underline,
                        bool is_strike_out,
                        FontOutPrecision output,
                        FontClipPrecision clip,
                        FontQuality quality,
                        FontPitch pitch,
                        FontFamily family) {
        LOGFONTW log_font = {};
        log_font.lfHeight = height;
        log_font.lfWidth = width;
        log_font.lfEscapement = escapement;
        log_font.lfOrientation = orientation;
        log_font.lfWeight = static_cast<int32_t>(weight);
        log_font.lfItalic = is_italic ? TRUE : FALSE;
        log_font.lfUnderline = is_underline ? TRUE : FALSE;
        log_font.lfStrikeOut = is_strike_out ? TRUE : FALSE;
        log_font.lfCharSet = static_cast<uint32_t>(charset) < UINT8_MAX
                ? static_cast<uint8_t>(charset)
                : static_cast<uint8_t>(Charset::DEFAULT);
        log_font.lfOutPrecision = static_cast<uint32_t>(output) < UINT8_MAX
                ? static_cast<uint8_t>(output)
                : static_cast<uint8_t>(FontOutPrecision::Default);
        log_font.lfClipPrecision = static_cast<uint32_t>(clip) < UINT8_MAX
                ? static_cast<uint8_t>(clip)
                : static_cast<uint8_t>(FontClipPrecision::Default);
        log_font.lfQuality = static_cast<uint32_t>(quality) < UINT8_MAX
                ? static_cast<uint8_t>(quality)
                : static_cast<uint8_t>(FontQuality::Default);
        log_font.lfPitchAndFamily =
                (static_cast<uint32_t>(pitch) < UINT8_MAX
                         ? static_cast<uint8_t>(pitch)
                         : static_cast<uint8_t>(FontPitch::Default)) |
                (static_cast<uint32_t>(family) < UINT8_MAX
                         ? static_cast<uint8_t>(family)
                         : static_cast<uint8_t>(FontFamily::DontCare));
        wcscpy_s(log_font.lfFaceName, LF_FACESIZE, face_name);
        return log_font;
    }

    HFONT font::create(const ENUMLOGFONTEXDVA *enum_log_font) {
        return CreateFontIndirectExA(enum_log_font);
    }

    HFONT font::create(const ENUMLOGFONTEXDVW *enum_log_font) {
        return CreateFontIndirectExW(enum_log_font);
    }

    bool font::destroy(HFONT font_handle) {
        return DeleteObject(font_handle);
    }

    HANDLE font::add_mem_resource(void *file_view,
                                  uint32_t file_view_size,
                                  uint32_t *num_fonts) {
        if (!num_fonts) {
            return nullptr;
        }
        unsigned long temp = *num_fonts;
        HANDLE result =
                AddFontMemResourceEx(file_view, file_view_size, nullptr, &temp);
        *num_fonts = temp;
        return result;
    }

    bool font::remove_mem_resource(HANDLE font_res_handle) {
        return RemoveFontMemResourceEx(font_res_handle);
    }

    int32_t font::add_resource(const char *font_file_name) {
        return AddFontResourceA(font_file_name);
    }

    int32_t font::add_resource(const wchar_t *font_file_name) {
        return AddFontResourceW(font_file_name);
    }

    bool font::remove_resource(const char *font_file_name) {
        return RemoveFontResourceA(font_file_name);
    }

    bool font::remove_resource(const wchar_t *font_file_name) {
        return RemoveFontResourceW(font_file_name);
    }

    int32_t font::add_resource(const char *font_file_name, FontType type) {
        return AddFontResourceExA(font_file_name, static_cast<uint32_t>(type),
                                  nullptr);
    }

    int32_t font::add_resource(const wchar_t *font_file_name, FontType type) {
        return AddFontResourceExW(font_file_name, static_cast<uint32_t>(type),
                                  nullptr);
    }

    int32_t font::remove_resource(const char *font_file_name, FontType type) {
        return RemoveFontResourceExA(font_file_name,
                                     static_cast<uint32_t>(type), nullptr);
    }

    int32_t font::remove_resource(const wchar_t *font_file_name,
                                  FontType type) {
        return RemoveFontResourceExW(font_file_name,
                                     static_cast<uint32_t>(type), nullptr);
    }

    int32_t font::enum_families(HDC dc_handle,
                                LOGFONTA *log_font,
                                FONTENUMPROCA font_enum_proc,
                                LPARAM lparam) {
        return EnumFontFamiliesExA(dc_handle, log_font, font_enum_proc, lparam,
                                   0);
    }

    int32_t font::enum_families(HDC dc_handle,
                                LOGFONTW *log_font,
                                FONTENUMPROCW font_enum_proc,
                                LPARAM lparam) {
        return EnumFontFamiliesExW(dc_handle, log_font, font_enum_proc, lparam,
                                   0);
    }

    uint32_t font::get_data(HDC dc_handle,
                            void *buf,
                            uint32_t size,
                            uint32_t table,
                            uint32_t offset) {
        return GetFontData(dc_handle, table, offset, buf, size);
    }

    LangInfo font::get_language_info(HDC dc_handle) {
        return static_cast<LangInfo>(GetFontLanguageInfo(dc_handle));
    }

    uint32_t font::get_unicode_ranges(HDC dc_handle, GLYPHSET *glyph_set) {
        return GetFontUnicodeRanges(dc_handle, glyph_set);
    }
} // namespace YanLib::ui::gdi
