//
// Created by forkernel on 2025/5/3.
//

#ifndef FONT_H
#define FONT_H
#include <cstdint>
#include <Windows.h>

namespace YanLib::ui::gdi {
    class font {
    public:
        font(const font &other) = delete;

        font(font &&other) = delete;

        font &operator=(const font &other) = delete;

        font &operator=(font &&other) = delete;

        font() = default;

        ~font() = default;

        static HFONT create_font(const wchar_t *face_name = L"宋体",
                                 unsigned long charset = GB2312_CHARSET,
                                 int height = 12,
                                 int width = 0,
                                 int escapement = 0,
                                 int orientation = 0,
                                 int weight = 0,
                                 bool is_italic = false,
                                 bool is_underline = false,
                                 bool is_strike_out = false,
                                 unsigned long out_precision = 0,
                                 unsigned long clip_precision = 0,
                                 unsigned long quality = 0,
                                 unsigned long pitch_and_family = 0);

        static HFONT create_font_indirect(const LOGFONTW *log_font);

        static LOGFONTW make_log_font(const wchar_t *face_name = L"宋体",
                                      uint8_t char_set = GB2312_CHARSET,
                                      long height = 12,
                                      long width = 0,
                                      long escapement = 0,
                                      long orientation = 0,
                                      long weight = 0,
                                      bool is_italic = false,
                                      bool is_underline = false,
                                      bool is_strike_out = false,
                                      uint8_t out_precision = 0,
                                      uint8_t clip_precision = 0,
                                      uint8_t quality = 0,
                                      uint8_t pitch_and_family = 0);

        static HFONT create_font_indirect(const ENUMLOGFONTEXDVW *enum_log_font);

        static HANDLE add_font_mem_resource(void *file_view,
                                            unsigned long size,
                                            void *resrved,
                                            unsigned long *num_fonts);

        static bool remove_font_mem_resource(HANDLE font_res_handle);

        static int add_font_resource(const wchar_t *font_file_name);

        static bool remove_font_resource(const wchar_t *font_file_name);

        static int add_font_resource(const wchar_t *font_file_name, unsigned long font_type);

        static int remove_font_resource(const wchar_t *font_file_name,
                                        unsigned long font_type);

        static int enum_font_families(HDC dc_handle,
                                      LOGFONTW *log_font,
                                      FONTENUMPROCW font_enum_proc,
                                      LPARAM l_param);

        static unsigned long get_font_data(HDC dc_handle,
                                           unsigned long table,
                                           unsigned long offset,
                                           void *buf,
                                           unsigned long size);

        static unsigned long get_font_language_info(HDC dc_handle);

        static unsigned long get_font_unicode_ranges(HDC dc_handle, GLYPHSET *glyph_set);
    };
}
#endif //FONT_H
