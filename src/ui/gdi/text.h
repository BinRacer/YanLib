//
// Created by forkernel on 2025/5/3.
//

#ifndef TEXT_H
#define TEXT_H
#include <Windows.h>

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
                             int x,
                             int y,
                             const wchar_t *text,
                             int cch_size);

        static bool ext_text_out(HDC dc_handle,
                                 int x,
                                 int y,
                                 unsigned int options,
                                 const RECT *rect,
                                 const wchar_t *text,
                                 int cch_size,
                                 const int *dx);

        static long tabbed_text_out(HDC dc_handle,
                                    int x,
                                    int y,
                                    const wchar_t *text,
                                    int cch_size,
                                    int tab_positions,
                                    const int *tab_stop_positions,
                                    int tab_origin);

        static bool poly_text_out(HDC dc_handle,
                                  const POLYTEXTW *poly_text,
                                  int num);

        static int draw_text(HDC dc_handle,
                             const wchar_t *text,
                             int cch_size,
                             RECT *rect,
                             unsigned int format);

        static int draw_text(HDC dc_handle,
                             wchar_t *text,
                             int cch_size,
                             RECT *rect,
                             unsigned int format,
                             DRAWTEXTPARAMS *draw_text_param);

        static unsigned long set_mapper_flags(HDC dc_handle, unsigned long flag);

        static bool set_text_justification(HDC dc_handle, int extra, int count);

        static bool get_aspect_ratio_filter(HDC dc_handle, SIZE *size);

        static bool get_char_width32(HDC dc_handle,
                                     unsigned int ch_first,
                                     unsigned int ch_last,
                                     int *buf);

        static bool get_char_width_float(HDC dc_handle,
                                         unsigned int code_point_first,
                                         unsigned int code_point_last,
                                         FLOAT *buf);

        static bool get_char_width_index(HDC dc_handle,
                                         unsigned int glyph_index_first,
                                         unsigned int glyph_index_num,
                                         unsigned short *glyph_index_array,
                                         int *widths);

        static unsigned long get_char_placement(HDC dc_handle,
                                                const wchar_t *text,
                                                int cch_size,
                                                int mex_extent,
                                                GCP_RESULTSW *results,
                                                unsigned long flag);

        static bool get_char_abc_widths(HDC dc_handle,
                                        unsigned int ch_first,
                                        unsigned int ch_last,
                                        ABC *abc);

        static bool get_char_abc_widths_float(HDC dc_handle,
                                              unsigned int code_point_first,
                                              unsigned int code_point_last,
                                              ABCFLOAT *abc_float);

        static bool get_char_abc_widths_index(HDC dc_handle,
                                              unsigned int first_glyph_index,
                                              unsigned int glyph_index_num,
                                              unsigned short *glyph_index_array,
                                              ABC *abc);

        static unsigned long get_glyph_indices(HDC dc_handle,
                                               const wchar_t *text,
                                               int cch_size,
                                               unsigned short *glyph_index,
                                               unsigned long flag);

        static unsigned long get_glyph_outline(HDC dc_handle,
                                               unsigned int ch,
                                               unsigned int format,
                                               GLYPHMETRICS *glyph_metrics,
                                               unsigned long size,
                                               void *buf,
                                               const MAT2 *mat2);

        static unsigned long get_kerning_pairs(HDC dc_handle,
                                               unsigned long pairs,
                                               KERNINGPAIR *kern_pair);

        static bool get_rasterizer_caps(RASTERIZER_STATUS *rasterizer_status,
                                        unsigned int size);

        static unsigned long get_tabbed_text_extent(HDC dc_handle,
                                                    const wchar_t *text,
                                                    int cch_size,
                                                    int tab_positions,
                                                    const int *tab_stop_positions);

        static unsigned int get_text_align(HDC dc_handle);

        static unsigned int set_text_align(HDC dc_handle, unsigned int align);

        static int get_text_character_extra(HDC dc_handle);

        static int set_text_character_extra(HDC dc_handle, int extra);

        static COLORREF get_text_color(HDC dc_handle);

        static COLORREF set_text_color(HDC dc_handle, COLORREF color);

        static int get_text_face(HDC dc_handle, int cch_size, wchar_t *buf);

        static bool get_text_metrics(HDC dc_handle, TEXTMETRICW *text_metric);

        static unsigned int get_outline_text_metrics(
            HDC dc_handle,
            unsigned int size,
            OUTLINETEXTMETRICW *outline_text_metric);

        static bool get_text_extent_point(HDC dc_handle,
                                          const wchar_t *text,
                                          int cch_size,
                                          int max_extent,
                                          int *fit,
                                          int *dx,
                                          SIZE *size);

        static bool get_text_extent_point32(HDC dc_handle,
                                            const wchar_t *text,
                                            int cch_size,
                                            SIZE *size);

        static bool get_text_extent_point_index(HDC dc_handle,
                                                unsigned short *glyph_index_array,
                                                int glyph_index_num,
                                                int max_extent,
                                                int *fit,
                                                int *dx,
                                                SIZE *size);

        static bool get_text_extent_point_index(HDC dc_handle,
                                                unsigned short *glyph_index_array,
                                                int glyph_index_num,
                                                SIZE *size);
    };
}
#endif //TEXT_H
