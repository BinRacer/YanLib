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

        static HFONT create_font(const char* face_name, /* "宋体" */
                                 uint32_t charset = GB2312_CHARSET,
                                 int32_t height = 12,
                                 int32_t width = 0,
                                 int32_t escapement = 0,
                                 int32_t orientation = 0,
                                 int32_t weight = 0,
                                 bool is_italic = false,
                                 bool is_underline = false,
                                 bool is_strike_out = false,
                                 uint32_t out_precision = 0,
                                 uint32_t clip_precision = 0,
                                 uint32_t quality = 0,
                                 uint32_t pitch_and_family = 0);

        static HFONT create_font(const wchar_t* face_name, /* L"宋体" */
                                 uint32_t charset = GB2312_CHARSET,
                                 int32_t height = 12,
                                 int32_t width = 0,
                                 int32_t escapement = 0,
                                 int32_t orientation = 0,
                                 int32_t weight = 0,
                                 bool is_italic = false,
                                 bool is_underline = false,
                                 bool is_strike_out = false,
                                 uint32_t out_precision = 0,
                                 uint32_t clip_precision = 0,
                                 uint32_t quality = 0,
                                 uint32_t pitch_and_family = 0);

        static HFONT create_font_indirect(const LOGFONTA* log_font);

        static HFONT create_font_indirect(const LOGFONTW* log_font);

        static LOGFONTA make_log_font(const char* face_name, /* "宋体" */
                                      uint8_t char_set = GB2312_CHARSET,
                                      int32_t height = 12,
                                      int32_t width = 0,
                                      int32_t escapement = 0,
                                      int32_t orientation = 0,
                                      int32_t weight = 0,
                                      bool is_italic = false,
                                      bool is_underline = false,
                                      bool is_strike_out = false,
                                      uint8_t out_precision = 0,
                                      uint8_t clip_precision = 0,
                                      uint8_t quality = 0,
                                      uint8_t pitch_and_family = 0);

        static LOGFONTW make_log_font(const wchar_t* face_name, /* L"宋体" */
                                      uint8_t char_set = GB2312_CHARSET,
                                      int32_t height = 12,
                                      int32_t width = 0,
                                      int32_t escapement = 0,
                                      int32_t orientation = 0,
                                      int32_t weight = 0,
                                      bool is_italic = false,
                                      bool is_underline = false,
                                      bool is_strike_out = false,
                                      uint8_t out_precision = 0,
                                      uint8_t clip_precision = 0,
                                      uint8_t quality = 0,
                                      uint8_t pitch_and_family = 0);

        static HFONT
        create_font_indirect(const ENUMLOGFONTEXDVA* enum_log_font);

        static HFONT
        create_font_indirect(const ENUMLOGFONTEXDVW* enum_log_font);

        static HANDLE add_font_mem_resource(void* file_view,
                                            uint32_t size,
                                            uint32_t* num_fonts);

        static bool remove_font_mem_resource(HANDLE font_res_handle);

        static int32_t add_font_resource(const char* font_file_name);

        static int32_t add_font_resource(const wchar_t* font_file_name);

        static bool remove_font_resource(const char* font_file_name);

        static bool remove_font_resource(const wchar_t* font_file_name);

        static int32_t add_font_resource(const char* font_file_name,
                                         uint32_t font_type);

        static int32_t add_font_resource(const wchar_t* font_file_name,
                                         uint32_t font_type);

        static int32_t remove_font_resource(const char* font_file_name,
                                            uint32_t font_type);

        static int32_t remove_font_resource(const wchar_t* font_file_name,
                                            uint32_t font_type);

        static int32_t enum_font_families(HDC dc_handle,
                                          LOGFONTA* log_font,
                                          FONTENUMPROCA font_enum_proc,
                                          LPARAM lparam);

        static int32_t enum_font_families(HDC dc_handle,
                                          LOGFONTW* log_font,
                                          FONTENUMPROCW font_enum_proc,
                                          LPARAM lparam);

        static uint32_t get_font_data(HDC dc_handle,
                                      uint32_t table,
                                      uint32_t offset,
                                      void* buf,
                                      uint32_t size);

        static uint32_t get_font_language_info(HDC dc_handle);

        static uint32_t get_font_unicode_ranges(HDC dc_handle,
                                                GLYPHSET* glyph_set);
    };
} // namespace YanLib::ui::gdi
#endif // FONT_H
