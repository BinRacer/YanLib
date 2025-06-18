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
#include <Windows.h>
#include <minwindef.h>
#include <winnt.h>
#include <wingdi.h>
#include <windef.h>
#include <cstdint>
#include "gdi.h"
namespace YanLib::ui::gdi {
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

        static void
        set(HWND window_handle, HFONT font_handle, bool is_redraw = false);

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
