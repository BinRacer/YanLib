//
// Created by forkernel on 2025/5/3.
//

#ifndef TEXT_H
#define TEXT_H
#include <Windows.h>
#include <cstdint>
#include <vector>
#include <string>

namespace YanLib::ui::gdi {
    class text {
    public:
        text(const text &other) = delete;

        text(text &&other) = delete;

        text &operator=(const text &other) = delete;

        text &operator=(text &&other) = delete;

        text() = default;

        ~text() = default;

        static bool
        text_out(HDC dc_handle, int32_t x, int32_t y, const std::string &text);

        static bool
        text_out(HDC dc_handle, int32_t x, int32_t y, const std::wstring &text);

        static bool ext_text_out(HDC dc_handle,
                                 int32_t x,
                                 int32_t y,
                                 uint32_t options,
                                 const RECT* rect,
                                 const std::string &text,
                                 const int32_t* dx);

        static bool ext_text_out(HDC dc_handle,
                                 int32_t x,
                                 int32_t y,
                                 uint32_t options,
                                 const RECT* rect,
                                 const std::wstring &text,
                                 const int32_t* dx);

        static int32_t tabbed_text_out(HDC dc_handle,
                                       int32_t x,
                                       int32_t y,
                                       const std::string &text,
                                       int32_t tab_pos,
                                       const int32_t* tab_stop_pos,
                                       int32_t tab_origin);

        static int32_t tabbed_text_out(HDC dc_handle,
                                       int32_t x,
                                       int32_t y,
                                       const std::wstring &text,
                                       int32_t tab_pos,
                                       const int32_t* tab_stop_pos,
                                       int32_t tab_origin);

        static bool poly_text_out(HDC dc_handle,
                                  const std::vector<POLYTEXTA> &poly_text);

        static bool poly_text_out(HDC dc_handle,
                                  const std::vector<POLYTEXTW> &poly_text);

        static int32_t draw_text(HDC dc_handle,
                                 const std::string &text,
                                 RECT* rect,
                                 uint32_t format);

        static int32_t draw_text(HDC dc_handle,
                                 const std::wstring &text,
                                 RECT* rect,
                                 uint32_t format);

        static int32_t draw_text(HDC dc_handle,
                                 std::string &text,
                                 RECT* rect,
                                 uint32_t format,
                                 DRAWTEXTPARAMS* draw_text_param);

        static int32_t draw_text(HDC dc_handle,
                                 std::wstring &text,
                                 RECT* rect,
                                 uint32_t format,
                                 DRAWTEXTPARAMS* draw_text_param);

        static uint32_t set_mapper_flags(HDC dc_handle, uint32_t flag);

        static bool
        set_text_justification(HDC dc_handle, int32_t extra, int32_t count);

        static bool get_aspect_ratio_filter(HDC dc_handle, SIZE* size);

        static bool get_char_width32(HDC dc_handle,
                                     uint32_t first,
                                     uint32_t last,
                                     int32_t* buf);

        static bool get_char_width_float(HDC dc_handle,
                                         uint32_t code_point_first,
                                         uint32_t code_point_last,
                                         FLOAT* buf);

        static bool get_char_width_index(HDC dc_handle,
                                         uint32_t index,
                                         std::vector<uint16_t> &glyph_index,
                                         int32_t* widths);

        static uint32_t get_char_placement(HDC dc_handle,
                                           const std::string &text,
                                           int32_t mex_extent,
                                           GCP_RESULTSA* results,
                                           uint32_t flag);

        static uint32_t get_char_placement(HDC dc_handle,
                                           const std::wstring &text,
                                           int32_t mex_extent,
                                           GCP_RESULTSW* results,
                                           uint32_t flag);

        static bool get_char_abc_widths(HDC dc_handle,
                                        uint32_t first,
                                        uint32_t last,
                                        ABC abc[]);

        static bool get_char_abc_widths_float(HDC dc_handle,
                                              uint32_t first,
                                              uint32_t last,
                                              ABCFLOAT abc_float[]);

        static bool
        get_char_abc_widths_index(HDC dc_handle,
                                  uint32_t index,
                                  std::vector<uint16_t> &glyph_index,
                                  std::vector<ABC> &abc);

        static uint32_t get_glyph_indices(HDC dc_handle,
                                          const std::string &text,
                                          std::vector<uint16_t> &glyph_index,
                                          uint32_t flag);

        static uint32_t get_glyph_indices(HDC dc_handle,
                                          const std::wstring &text,
                                          std::vector<uint16_t> &glyph_index,
                                          uint32_t flag);

        static uint32_t get_glyph_outline(HDC dc_handle,
                                          uint32_t ch,
                                          uint32_t format,
                                          GLYPHMETRICS* glyph_metrics,
                                          uint32_t size,
                                          void* buf,
                                          const MAT2* mat2);

        static uint32_t get_kerning_pairs(HDC dc_handle,
                                          uint32_t pairs,
                                          KERNINGPAIR* kern_pair);

        static bool get_rasterizer_caps(RASTERIZER_STATUS* rasterizer_status);

        static uint32_t get_tabbed_text_extent(HDC dc_handle,
                                               const std::string &text,
                                               int32_t tab_pos,
                                               const int32_t* tab_stop_pos);

        static uint32_t get_tabbed_text_extent(HDC dc_handle,
                                               const std::wstring &text,
                                               int32_t tab_pos,
                                               const int32_t* tab_stop_pos);

        static uint32_t get_text_align(HDC dc_handle);

        static uint32_t set_text_align(HDC dc_handle, uint32_t align);

        static int32_t get_text_character_extra(HDC dc_handle);

        static int32_t set_text_character_extra(HDC dc_handle, int32_t extra);

        static COLORREF get_text_color(HDC dc_handle);

        static COLORREF set_text_color(HDC dc_handle, COLORREF color);

        static int32_t get_text_face(HDC dc_handle, std::string &text);

        static int32_t get_text_face(HDC dc_handle, std::wstring &text);

        static bool get_text_metrics(HDC dc_handle, TEXTMETRICA* text_metric);

        static bool get_text_metrics(HDC dc_handle, TEXTMETRICW* text_metric);

        static uint32_t
        get_outline_text_metrics(HDC dc_handle,
                                 uint32_t size,
                                 OUTLINETEXTMETRICA* outline_text_metric);

        static uint32_t
        get_outline_text_metrics(HDC dc_handle,
                                 uint32_t size,
                                 OUTLINETEXTMETRICW* outline_text_metric);

        static bool get_text_extent_point(HDC dc_handle,
                                          const std::string &text,
                                          int32_t max_extent,
                                          int32_t* fit,
                                          int32_t* dx,
                                          SIZE* size);

        static bool get_text_extent_point(HDC dc_handle,
                                          const std::wstring &text,
                                          int32_t max_extent,
                                          int32_t* fit,
                                          int32_t* dx,
                                          SIZE* size);

        static bool get_text_extent_point32(HDC dc_handle,
                                            const std::string &text,
                                            SIZE* size);

        static bool get_text_extent_point32(HDC dc_handle,
                                            const std::wstring &text,
                                            SIZE* size);

        static bool
        get_text_extent_point_index(HDC dc_handle,
                                    std::vector<uint16_t> &glyph_index,
                                    int32_t max_extent,
                                    int32_t* fit,
                                    int32_t* dx,
                                    SIZE* size);

        static bool
        get_text_extent_point_index(HDC dc_handle,
                                    std::vector<uint16_t> &glyph_index,
                                    SIZE* size);
    };
} // namespace YanLib::ui::gdi
#endif // TEXT_H
