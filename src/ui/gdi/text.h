//
// Created by forkernel on 2025/5/3.
//

#ifndef TEXT_H
#define TEXT_H
#include <Windows.h>
#include <stdint.h>

namespace YanLib::ui::gdi {
    class text {
    public:
        text(const text &other) = delete;

        text(text &&other) = delete;

        text &operator=(const text &other) = delete;

        text &operator=(text &&other) = delete;

        text() = default;

        ~text() = default;

        static bool text_out(HDC dc_handle,
                             int32_t x,
                             int32_t y,
                             const wchar_t *text,
                             int32_t cch_size);

        static bool ext_text_out(HDC dc_handle,
                                 int32_t x,
                                 int32_t y,
                                 uint32_t options,
                                 const RECT *rect,
                                 const wchar_t *text,
                                 int32_t cch_size,
                                 const int32_t *dx);

        static long tabbed_text_out(HDC dc_handle,
                                    int32_t x,
                                    int32_t y,
                                    const wchar_t *text,
                                    int32_t cch_size,
                                    int32_t tab_positions,
                                    const int32_t *tab_stop_positions,
                                    int32_t tab_origin);

        static bool poly_text_out(HDC dc_handle,
                                  const POLYTEXTW *poly_text,
                                  int32_t num);

        static int32_t draw_text(HDC dc_handle,
                             const wchar_t *text,
                             int32_t cch_size,
                             RECT *rect,
                             uint32_t format);

        static int32_t draw_text(HDC dc_handle,
                             wchar_t *text,
                             int32_t cch_size,
                             RECT *rect,
                             uint32_t format,
                             DRAWTEXTPARAMS *draw_text_param);

        static unsigned long set_mapper_flags(HDC dc_handle, unsigned long flag);

        static bool set_text_justification(HDC dc_handle, int32_t extra, int32_t count);

        static bool get_aspect_ratio_filter(HDC dc_handle, SIZE *size);

        static bool get_char_width32(HDC dc_handle,
                                     uint32_t ch_first,
                                     uint32_t ch_last,
                                     int32_t *buf);

        static bool get_char_width_float(HDC dc_handle,
                                         uint32_t code_point_first,
                                         uint32_t code_point_last,
                                         FLOAT *buf);

        static bool get_char_width_index(HDC dc_handle,
                                         uint32_t glyph_index_first,
                                         uint32_t glyph_index_num,
                                         uint16_t *glyph_index_array,
                                         int32_t *widths);

        static unsigned long get_char_placement(HDC dc_handle,
                                                const wchar_t *text,
                                                int32_t cch_size,
                                                int32_t mex_extent,
                                                GCP_RESULTSW *results,
                                                unsigned long flag);

        static bool get_char_abc_widths(HDC dc_handle,
                                        uint32_t ch_first,
                                        uint32_t ch_last,
                                        ABC *abc);

        static bool get_char_abc_widths_float(HDC dc_handle,
                                              uint32_t code_point_first,
                                              uint32_t code_point_last,
                                              ABCFLOAT *abc_float);

        static bool get_char_abc_widths_index(HDC dc_handle,
                                              uint32_t first_glyph_index,
                                              uint32_t glyph_index_num,
                                              uint16_t *glyph_index_array,
                                              ABC *abc);

        static unsigned long get_glyph_indices(HDC dc_handle,
                                               const wchar_t *text,
                                               int32_t cch_size,
                                               uint16_t *glyph_index,
                                               unsigned long flag);

        static unsigned long get_glyph_outline(HDC dc_handle,
                                               uint32_t ch,
                                               uint32_t format,
                                               GLYPHMETRICS *glyph_metrics,
                                               unsigned long size,
                                               void *buf,
                                               const MAT2 *mat2);

        static unsigned long get_kerning_pairs(HDC dc_handle,
                                               unsigned long pairs,
                                               KERNINGPAIR *kern_pair);

        static bool get_rasterizer_caps(RASTERIZER_STATUS *rasterizer_status,
                                        uint32_t size);

        static unsigned long get_tabbed_text_extent(HDC dc_handle,
                                                    const wchar_t *text,
                                                    int32_t cch_size,
                                                    int32_t tab_positions,
                                                    const int32_t *tab_stop_positions);

        static uint32_t get_text_align(HDC dc_handle);

        static uint32_t set_text_align(HDC dc_handle, uint32_t align);

        static int32_t get_text_character_extra(HDC dc_handle);

        static int32_t set_text_character_extra(HDC dc_handle, int32_t extra);

        static COLORREF get_text_color(HDC dc_handle);

        static COLORREF set_text_color(HDC dc_handle, COLORREF color);

        static int32_t get_text_face(HDC dc_handle, int32_t cch_size, wchar_t *buf);

        static bool get_text_metrics(HDC dc_handle, TEXTMETRICW *text_metric);

        static uint32_t get_outline_text_metrics(
            HDC dc_handle,
            uint32_t size,
            OUTLINETEXTMETRICW *outline_text_metric);

        static bool get_text_extent_point(HDC dc_handle,
                                          const wchar_t *text,
                                          int32_t cch_size,
                                          int32_t max_extent,
                                          int32_t *fit,
                                          int32_t *dx,
                                          SIZE *size);

        static bool get_text_extent_point32(HDC dc_handle,
                                            const wchar_t *text,
                                            int32_t cch_size,
                                            SIZE *size);

        static bool get_text_extent_point_index(HDC dc_handle,
                                                uint16_t *glyph_index_array,
                                                int32_t glyph_index_num,
                                                int32_t max_extent,
                                                int32_t *fit,
                                                int32_t *dx,
                                                SIZE *size);

        static bool get_text_extent_point_index(HDC dc_handle,
                                                uint16_t *glyph_index_array,
                                                int32_t glyph_index_num,
                                                SIZE *size);
    };
}
#endif //TEXT_H
