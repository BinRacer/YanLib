//
// Created by forkernel on 2025/5/3.
//

#include "text.h"

namespace YanLib::ui::gdi {
    bool text::text_out(HDC dc_handle,
                        int x,
                        int y,
                        const wchar_t *text,
                        int cch_size) {
        return TextOutW(dc_handle, x, y, text, cch_size);
    }

    bool text::ext_text_out(HDC dc_handle,
                            int x,
                            int y,
                            unsigned int options,
                            const RECT *rect,
                            const wchar_t *text,
                            int cch_size,
                            const int *dx) {
        return ExtTextOutW(dc_handle, x, y, options, rect, text, cch_size, dx);
    }

    long text::tabbed_text_out(HDC dc_handle,
                               int x,
                               int y,
                               const wchar_t *text,
                               int cch_size,
                               int tab_positions,
                               const int *tab_stop_positions,
                               int tab_origin) {
        return TabbedTextOutW(dc_handle,
                              x,
                              y,
                              text,
                              cch_size,
                              tab_positions,
                              tab_stop_positions,
                              tab_origin);
    }

    bool text::poly_text_out(HDC dc_handle, const POLYTEXTW *poly_text, int num) {
        return PolyTextOutW(dc_handle, poly_text, num);
    }

    int text::draw_text(HDC dc_handle,
                        const wchar_t *text,
                        int cch_size,
                        RECT *rect,
                        unsigned int format) {
        return DrawTextW(dc_handle, text, cch_size, rect, format);
    }

    int text::draw_text(HDC dc_handle,
                        wchar_t *text,
                        int cch_size,
                        RECT *rect,
                        unsigned int format,
                        DRAWTEXTPARAMS *draw_text_param) {
        return DrawTextExW(dc_handle, text, cch_size, rect, format, draw_text_param);
    }

    unsigned long text::set_mapper_flags(HDC dc_handle, unsigned long flag) {
        return SetMapperFlags(dc_handle, flag);
    }

    bool text::set_text_justification(HDC dc_handle, int extra, int count) {
        return SetTextJustification(dc_handle, extra, count);
    }

    bool text::get_aspect_ratio_filter(HDC dc_handle, SIZE *size) {
        return GetAspectRatioFilterEx(dc_handle, size);
    }

    bool text::get_char_width32(HDC dc_handle,
                                unsigned int ch_first,
                                unsigned int ch_last,
                                int *buf) {
        return GetCharWidth32W(dc_handle, ch_first, ch_last, buf);
    }

    bool text::get_char_width_float(HDC dc_handle,
                                    unsigned int code_point_first,
                                    unsigned int code_point_last,
                                    FLOAT *buf) {
        return GetCharWidthFloatW(dc_handle, code_point_first, code_point_last, buf);
    }

    bool text::get_char_width_index(HDC dc_handle,
                                    unsigned int glyph_index_first,
                                    unsigned int glyph_index_num,
                                    unsigned short *glyph_index_array,
                                    int *widths) {
        return GetCharWidthI(dc_handle,
                             glyph_index_first,
                             glyph_index_num,
                             glyph_index_array,
                             widths);
    }

    bool text::get_char_abc_widths(HDC dc_handle,
                                   unsigned int ch_first,
                                   unsigned int ch_last,
                                   ABC *abc) {
        return GetCharABCWidthsW(dc_handle, ch_first, ch_last, abc);
    }

    bool text::get_char_abc_widths_float(HDC dc_handle,
                                         unsigned int code_point_first,
                                         unsigned int code_point_last,
                                         ABCFLOAT *abc_float) {
        return GetCharABCWidthsFloatW(dc_handle,
                                      code_point_first,
                                      code_point_last,
                                      abc_float);
    }

    bool text::get_char_abc_widths_index(HDC dc_handle,
                                         unsigned int first_glyph_index,
                                         unsigned int glyph_index_num,
                                         unsigned short *glyph_index_array,
                                         ABC *abc) {
        return GetCharABCWidthsI(dc_handle,
                                 first_glyph_index,
                                 glyph_index_num,
                                 glyph_index_array,
                                 abc);
    }

    unsigned long text::get_char_placement(HDC dc_handle,
                                   const wchar_t *text,
                                   int cch_size,
                                   int mex_extent,
                                   GCP_RESULTSW *results,
                                   unsigned long flag) {
        return GetCharacterPlacementW(dc_handle,
                                      text,
                                      cch_size,
                                      mex_extent,
                                      results,
                                      flag);
    }

    unsigned long text::get_glyph_indices(HDC dc_handle,
                                  const wchar_t *text,
                                  int cch_size,
                                  unsigned short *glyph_index,
                                  unsigned long flag) {
        return GetGlyphIndicesW(dc_handle, text, cch_size, glyph_index, flag);
    }

    unsigned long text::get_glyph_outline(HDC dc_handle,
                                  unsigned int ch,
                                  unsigned int format,
                                  GLYPHMETRICS *glyph_metrics,
                                  unsigned long size,
                                  void *buf,
                                  const MAT2 *mat2) {
        return GetGlyphOutlineW(dc_handle,
                                ch,
                                format,
                                glyph_metrics,
                                size,
                                buf,
                                mat2);
    }

    unsigned long text::get_kerning_pairs(HDC dc_handle,
                                  unsigned long pairs,
                                  KERNINGPAIR *kern_pair) {
        return GetKerningPairsW(dc_handle, pairs, kern_pair);
    }

    bool text::get_rasterizer_caps(RASTERIZER_STATUS *rasterizer_status,
                                   unsigned int size) {
        return GetRasterizerCaps(rasterizer_status, size);
    }

    unsigned long text::get_tabbed_text_extent(HDC dc_handle,
                                       const wchar_t *text,
                                       int cch_size,
                                       int tab_positions,
                                       const int *tab_stop_positions) {
        return GetTabbedTextExtentW(dc_handle,
                                    text,
                                    cch_size,
                                    tab_positions,
                                    tab_stop_positions);
    }

    unsigned int text::get_text_align(HDC dc_handle) {
        return GetTextAlign(dc_handle);
    }

    unsigned int text::set_text_align(HDC dc_handle, unsigned int align) {
        return SetTextAlign(dc_handle, align);
    }

    int text::get_text_character_extra(HDC dc_handle) {
        return GetTextCharacterExtra(dc_handle);
    }

    int text::set_text_character_extra(HDC dc_handle, int extra) {
        return SetTextCharacterExtra(dc_handle, extra);
    }

    COLORREF text::get_text_color(HDC dc_handle) {
        return GetTextColor(dc_handle);
    }

    COLORREF text::set_text_color(HDC dc_handle, COLORREF color) {
        return SetTextColor(dc_handle, color);
    }

    int text::get_text_face(HDC dc_handle, int cch_size, wchar_t *buf) {
        return GetTextFaceW(dc_handle, cch_size, buf);
    }

    bool text::get_text_metrics(HDC dc_handle, TEXTMETRICW *text_metric) {
        return GetTextMetricsW(dc_handle, text_metric);
    }

    unsigned int text::get_outline_text_metrics(HDC dc_handle,
                                        unsigned int size,
                                        OUTLINETEXTMETRICW *outline_text_metric) {
        return GetOutlineTextMetricsW(dc_handle, size, outline_text_metric);
    }

    bool text::get_text_extent_point(HDC dc_handle,
                                     const wchar_t *text,
                                     int cch_size,
                                     int max_extent,
                                     int *fit,
                                     int *dx,
                                     SIZE *size) {
        return GetTextExtentExPointW(dc_handle,
                                     text,
                                     cch_size,
                                     max_extent,
                                     fit,
                                     dx,
                                     size);
    }

    bool text::get_text_extent_point32(HDC dc_handle,
                                       const wchar_t *text,
                                       int cch_size,
                                       SIZE *size) {
        return GetTextExtentPoint32W(dc_handle, text, cch_size, size);
    }

    bool text::get_text_extent_point_index(HDC dc_handle,
                                           unsigned short *glyph_index_array,
                                           int glyph_index_num,
                                           int max_extent,
                                           int *fit,
                                           int *dx,
                                           SIZE *size) {
        return GetTextExtentExPointI(dc_handle,
                                     glyph_index_array,
                                     glyph_index_num,
                                     max_extent,
                                     fit,
                                     dx,
                                     size);
    }

    bool text::get_text_extent_point_index(HDC dc_handle,
                                           unsigned short *glyph_index_array,
                                           int glyph_index_num,
                                           SIZE *size) {
        return GetTextExtentPointI(dc_handle,
                                   glyph_index_array,
                                   glyph_index_num,
                                   size);
    }
}
