//
// Created by forkernel on 2025/5/3.
//

#include "font.h"

namespace YanLib::ui::gdi {
HFONT font::create_font(const char *face_name,
    uint32_t                        charset,
    int32_t                         height,
    int32_t                         width,
    int32_t                         escapement,
    int32_t                         orientation,
    int32_t                         weight,
    bool                            is_italic,
    bool                            is_underline,
    bool                            is_strike_out,
    uint32_t                        out_precision,
    uint32_t                        clip_precision,
    uint32_t                        quality,
    uint32_t                        pitch_and_family) {
    return CreateFontA(height, width, escapement, orientation, weight,
        is_italic ? TRUE : FALSE, is_underline ? TRUE : FALSE,
        is_strike_out ? TRUE : FALSE, charset, out_precision, clip_precision,
        quality, pitch_and_family, face_name);
}

HFONT font::create_font(const wchar_t *face_name,
    uint32_t                           charset,
    int32_t                            height,
    int32_t                            width,
    int32_t                            escapement,
    int32_t                            orientation,
    int32_t                            weight,
    bool                               is_italic,
    bool                               is_underline,
    bool                               is_strike_out,
    uint32_t                           out_precision,
    uint32_t                           clip_precision,
    uint32_t                           quality,
    uint32_t                           pitch_and_family) {
    return CreateFontW(height, width, escapement, orientation, weight,
        is_italic ? TRUE : FALSE, is_underline ? TRUE : FALSE,
        is_strike_out ? TRUE : FALSE, charset, out_precision, clip_precision,
        quality, pitch_and_family, face_name);
}

HFONT font::create_font_indirect(const LOGFONTA *log_font) {
    return CreateFontIndirectA(log_font);
}

HFONT font::create_font_indirect(const LOGFONTW *log_font) {
    return CreateFontIndirectW(log_font);
}

LOGFONTA font::make_log_font(const char *face_name,
    uint8_t                              char_set,
    long                                 height,
    long                                 width,
    long                                 escapement,
    long                                 orientation,
    long                                 weight,
    bool                                 is_italic,
    bool                                 is_underline,
    bool                                 is_strike_out,
    uint8_t                              out_precision,
    uint8_t                              clip_precision,
    uint8_t                              quality,
    uint8_t                              pitch_and_family) {
    LOGFONTA log_font         = {};
    log_font.lfHeight         = height;
    log_font.lfWidth          = width;
    log_font.lfEscapement     = escapement;
    log_font.lfOrientation    = orientation;
    log_font.lfWeight         = weight;
    log_font.lfItalic         = is_italic ? TRUE : FALSE;
    log_font.lfUnderline      = is_underline ? TRUE : FALSE;
    log_font.lfStrikeOut      = is_strike_out ? TRUE : FALSE;
    log_font.lfCharSet        = char_set;
    log_font.lfOutPrecision   = out_precision;
    log_font.lfClipPrecision  = clip_precision;
    log_font.lfQuality        = quality;
    log_font.lfPitchAndFamily = pitch_and_family;
    strcpy_s(log_font.lfFaceName, LF_FACESIZE, face_name);
    return log_font;
}

LOGFONTW font::make_log_font(const wchar_t *face_name,
    uint8_t                                 char_set,
    long                                    height,
    long                                    width,
    long                                    escapement,
    long                                    orientation,
    long                                    weight,
    bool                                    is_italic,
    bool                                    is_underline,
    bool                                    is_strike_out,
    uint8_t                                 out_precision,
    uint8_t                                 clip_precision,
    uint8_t                                 quality,
    uint8_t                                 pitch_and_family) {
    LOGFONTW log_font         = {};
    log_font.lfHeight         = height;
    log_font.lfWidth          = width;
    log_font.lfEscapement     = escapement;
    log_font.lfOrientation    = orientation;
    log_font.lfWeight         = weight;
    log_font.lfItalic         = is_italic ? TRUE : FALSE;
    log_font.lfUnderline      = is_underline ? TRUE : FALSE;
    log_font.lfStrikeOut      = is_strike_out ? TRUE : FALSE;
    log_font.lfCharSet        = char_set;
    log_font.lfOutPrecision   = out_precision;
    log_font.lfClipPrecision  = clip_precision;
    log_font.lfQuality        = quality;
    log_font.lfPitchAndFamily = pitch_and_family;
    wcscpy_s(log_font.lfFaceName, LF_FACESIZE, face_name);
    return log_font;
}

HFONT font::create_font_indirect(const ENUMLOGFONTEXDVA *enum_log_font) {
    return CreateFontIndirectExA(enum_log_font);
}

HFONT font::create_font_indirect(const ENUMLOGFONTEXDVW *enum_log_font) {
    return CreateFontIndirectExW(enum_log_font);
}

HANDLE font::add_font_mem_resource(void *file_view,
    uint32_t                             size,
    uint32_t                            *num_fonts) {
    return AddFontMemResourceEx(
        file_view, size, nullptr, reinterpret_cast<unsigned long *>(num_fonts));
}

bool font::remove_font_mem_resource(HANDLE font_res_handle) {
    return RemoveFontMemResourceEx(font_res_handle);
}

int32_t font::add_font_resource(const char *font_file_name) {
    return AddFontResourceA(font_file_name);
}

int32_t font::add_font_resource(const wchar_t *font_file_name) {
    return AddFontResourceW(font_file_name);
}

bool font::remove_font_resource(const char *font_file_name) {
    return RemoveFontResourceA(font_file_name);
}

bool font::remove_font_resource(const wchar_t *font_file_name) {
    return RemoveFontResourceW(font_file_name);
}

int32_t font::add_font_resource(const char *font_file_name,
    uint32_t                                font_type) {
    return AddFontResourceExA(font_file_name, font_type, nullptr);
}

int32_t font::add_font_resource(const wchar_t *font_file_name,
    uint32_t                                   font_type) {
    return AddFontResourceExW(font_file_name, font_type, nullptr);
}

int32_t font::remove_font_resource(const char *font_file_name,
    uint32_t                                   font_type) {
    return RemoveFontResourceExA(font_file_name, font_type, nullptr);
}

int32_t font::remove_font_resource(const wchar_t *font_file_name,
    uint32_t                                      font_type) {
    return RemoveFontResourceExW(font_file_name, font_type, nullptr);
}

int32_t font::enum_font_families(HDC dc_handle,
    LOGFONTA                        *log_font,
    FONTENUMPROCA                    font_enum_proc,
    LPARAM                           lparam) {
    return EnumFontFamiliesExA(dc_handle, log_font, font_enum_proc, lparam, 0);
}

int32_t font::enum_font_families(HDC dc_handle,
    LOGFONTW                        *log_font,
    FONTENUMPROCW                    font_enum_proc,
    LPARAM                           lparam) {
    return EnumFontFamiliesExW(dc_handle, log_font, font_enum_proc, lparam, 0);
}

uint32_t font::get_font_data(HDC dc_handle,
    uint32_t                     table,
    uint32_t                     offset,
    void                        *buf,
    uint32_t                     size) {
    return GetFontData(dc_handle, table, offset, buf, size);
}

uint32_t font::get_font_language_info(HDC dc_handle) {
    return GetFontLanguageInfo(dc_handle);
}

uint32_t font::get_font_unicode_ranges(HDC dc_handle, GLYPHSET *glyph_set) {
    return GetFontUnicodeRanges(dc_handle, glyph_set);
}
} // namespace YanLib::ui::gdi
