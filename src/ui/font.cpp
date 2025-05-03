//
// Created by forkernel on 2025/5/3.
//

#include "font.h"

namespace YanLib::ui {
    HFONT font::create_font(const wchar_t *face_name,
                            DWORD charset,
                            int height,
                            int width,
                            int escapement,
                            int orientation,
                            int weight,
                            bool is_italic,
                            bool is_underline,
                            bool is_strike_out,
                            DWORD out_precision,
                            DWORD clip_precision,
                            DWORD quality,
                            DWORD pitch_and_family) {
        return CreateFontW(height,
                           width,
                           escapement,
                           orientation,
                           weight,
                           is_italic ? TRUE : FALSE,
                           is_underline ? TRUE : FALSE,
                           is_strike_out ? TRUE : FALSE,
                           charset,
                           out_precision,
                           clip_precision,
                           quality,
                           pitch_and_family,
                           face_name);
    }

    HFONT font::create_font_indirect(const LOGFONTW *log_font) {
        return CreateFontIndirectW(log_font);
    }

    LOGFONTW font::make_log_font(const wchar_t *face_name,
                                 uint8_t char_set,
                                 LONG height,
                                 LONG width,
                                 LONG escapement,
                                 LONG orientation,
                                 LONG weight,
                                 bool is_italic,
                                 bool is_underline,
                                 bool is_strike_out,
                                 uint8_t out_precision,
                                 uint8_t clip_precision,
                                 uint8_t quality,
                                 uint8_t pitch_and_family) {
        LOGFONTW log_font = {};
        log_font.lfHeight = height;
        log_font.lfWidth = width;
        log_font.lfEscapement = escapement;
        log_font.lfOrientation = orientation;
        log_font.lfWeight = weight;
        log_font.lfItalic = is_italic ? TRUE : FALSE;
        log_font.lfUnderline = is_underline ? TRUE : FALSE;
        log_font.lfStrikeOut = is_strike_out ? TRUE : FALSE;
        log_font.lfOutPrecision = out_precision;
        log_font.lfClipPrecision = clip_precision;
        log_font.lfQuality = quality;
        log_font.lfPitchAndFamily = pitch_and_family;
        wcscpy_s(log_font.lfFaceName, LF_FACESIZE, face_name);
        return log_font;
    }

    HFONT font::create_font_indirect(const ENUMLOGFONTEXDVW *enum_log_font) {
        return CreateFontIndirectExW(enum_log_font);
    }

    HANDLE font::add_font_mem_resource(void *file_view,
                                       DWORD size,
                                       void *resrved,
                                       DWORD *num_fonts) {
        return AddFontMemResourceEx(file_view, size, resrved, num_fonts);
    }

    bool font::remove_font_mem_resource(HANDLE font_res_handle) {
        return RemoveFontMemResourceEx(font_res_handle);
    }

    int font::add_font_resource(const wchar_t *font_file_name) {
        return AddFontResourceW(font_file_name);
    }

    bool font::remove_font_resource(const wchar_t *font_file_name) {
        return RemoveFontResourceW(font_file_name);
    }

    int font::add_font_resource(const wchar_t *font_file_name, DWORD font_type) {
        return AddFontResourceExW(font_file_name, font_type, nullptr);
    }

    int font::remove_font_resource(const wchar_t *font_file_name, DWORD font_type) {
        return RemoveFontResourceExW(font_file_name, font_type, nullptr);
    }

    int font::enum_font_families(HDC dc_handle,
                                 LOGFONTW* log_font,
                                 FONTENUMPROCW font_enum_proc,
                                 LPARAM l_param) {
        return EnumFontFamiliesExW(dc_handle,
                                   log_font,
                                   font_enum_proc,
                                   l_param,
                                   0);
    }

    DWORD font::get_font_data(HDC dc_handle,
                              DWORD table,
                              DWORD offset,
                              void *buf,
                              DWORD size) {
        return GetFontData(dc_handle, table, offset, buf, size);
    }

    DWORD font::get_font_language_info(HDC dc_handle) {
        return GetFontLanguageInfo(dc_handle);
    }

    DWORD font::get_font_unicode_ranges(HDC dc_handle, GLYPHSET* glyph_set) {
        return GetFontUnicodeRanges(dc_handle, glyph_set);
    }
}
