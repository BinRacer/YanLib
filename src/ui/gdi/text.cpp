//
// Created by forkernel on 2025/5/3.
//

#include "text.h"

namespace YanLib::ui::gdi {
    bool text::text_out(HDC dc_handle,
                        int32_t x,
                        int32_t y,
                        const wchar_t *text,
                        int32_t cch_size) {
        return TextOutW(dc_handle, x, y, text, cch_size);
    }

    bool text::ext_text_out(HDC dc_handle,
                            int32_t x,
                            int32_t y,
                            uint32_t options,
                            const RECT *rect,
                            const wchar_t *text,
                            int32_t cch_size,
                            const int32_t *dx) {
        return ExtTextOutW(dc_handle, x, y, options, rect, text, cch_size, dx);
    }

    long text::tabbed_text_out(HDC dc_handle,
                               int32_t x,
                               int32_t y,
                               const wchar_t *text,
                               int32_t cch_size,
                               int32_t tab_positions,
                               const int32_t *tab_stop_positions,
                               int32_t tab_origin) {
        return TabbedTextOutW(dc_handle,
                              x,
                              y,
                              text,
                              cch_size,
                              tab_positions,
                              tab_stop_positions,
                              tab_origin);
    }

    bool text::poly_text_out(HDC dc_handle, const POLYTEXTW *poly_text, int32_t num) {
        return PolyTextOutW(dc_handle, poly_text, num);
    }

    int32_t text::draw_text(HDC dc_handle,
                        const wchar_t *text,
                        int32_t cch_size,
                        RECT *rect,
                        uint32_t format) {
        return DrawTextW(dc_handle, text, cch_size, rect, format);
    }

    int32_t text::draw_text(HDC dc_handle,
                        wchar_t *text,
                        int32_t cch_size,
                        RECT *rect,
                        uint32_t format,
                        DRAWTEXTPARAMS *draw_text_param) {
        return DrawTextExW(dc_handle, text, cch_size, rect, format, draw_text_param);
    }

    unsigned long text::set_mapper_flags(HDC dc_handle, unsigned long flag) {
        return SetMapperFlags(dc_handle, flag);
    }

    bool text::set_text_justification(HDC dc_handle, int32_t extra, int32_t count) {
        return SetTextJustification(dc_handle, extra, count);
    }

    bool text::get_aspect_ratio_filter(HDC dc_handle, SIZE *size) {
        return GetAspectRatioFilterEx(dc_handle, size);
    }

    bool text::get_char_width32(HDC dc_handle,
                                uint32_t ch_first,
                                uint32_t ch_last,
                                int32_t *buf) {
        return GetCharWidth32W(dc_handle, ch_first, ch_last, buf);
    }

    bool text::get_char_width_float(HDC dc_handle,
                                    uint32_t code_point_first,
                                    uint32_t code_point_last,
                                    FLOAT *buf) {
        return GetCharWidthFloatW(dc_handle, code_point_first, code_point_last, buf);
    }

    bool text::get_char_width_index(HDC dc_handle,
                                    uint32_t glyph_index_first,
                                    uint32_t glyph_index_num,
                                    uint16_t *glyph_index_array,
                                    int32_t *widths) {
        return GetCharWidthI(dc_handle,
                             glyph_index_first,
                             glyph_index_num,
                             glyph_index_array,
                             widths);
    }

    bool text::get_char_abc_widths(HDC dc_handle,
                                   uint32_t ch_first,
                                   uint32_t ch_last,
                                   ABC *abc) {
        return GetCharABCWidthsW(dc_handle, ch_first, ch_last, abc);
    }

    bool text::get_char_abc_widths_float(HDC dc_handle,
                                         uint32_t code_point_first,
                                         uint32_t code_point_last,
                                         ABCFLOAT *abc_float) {
        return GetCharABCWidthsFloatW(dc_handle,
                                      code_point_first,
                                      code_point_last,
                                      abc_float);
    }

    bool text::get_char_abc_widths_index(HDC dc_handle,
                                         uint32_t first_glyph_index,
                                         uint32_t glyph_index_num,
                                         uint16_t *glyph_index_array,
                                         ABC *abc) {
        return GetCharABCWidthsI(dc_handle,
                                 first_glyph_index,
                                 glyph_index_num,
                                 glyph_index_array,
                                 abc);
    }

    unsigned long text::get_char_placement(HDC dc_handle,
                                           const wchar_t *text,
                                           int32_t cch_size,
                                           int32_t mex_extent,
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
                                          int32_t cch_size,
                                          uint16_t *glyph_index,
                                          unsigned long flag) {
        return GetGlyphIndicesW(dc_handle, text, cch_size, glyph_index, flag);
    }

    unsigned long text::get_glyph_outline(HDC dc_handle,
                                          uint32_t ch,
                                          uint32_t format,
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
                                   uint32_t size) {
        return GetRasterizerCaps(rasterizer_status, size);
    }

    unsigned long text::get_tabbed_text_extent(HDC dc_handle,
                                               const wchar_t *text,
                                               int32_t cch_size,
                                               int32_t tab_positions,
                                               const int32_t *tab_stop_positions) {
        return GetTabbedTextExtentW(dc_handle,
                                    text,
                                    cch_size,
                                    tab_positions,
                                    tab_stop_positions);
    }

    uint32_t text::get_text_align(HDC dc_handle) {
        return GetTextAlign(dc_handle);
    }

    uint32_t text::set_text_align(HDC dc_handle, uint32_t align) {
        return SetTextAlign(dc_handle, align);
    }

    int32_t text::get_text_character_extra(HDC dc_handle) {
        return GetTextCharacterExtra(dc_handle);
    }

    int32_t text::set_text_character_extra(HDC dc_handle, int32_t extra) {
        return SetTextCharacterExtra(dc_handle, extra);
    }

    COLORREF text::get_text_color(HDC dc_handle) {
        return GetTextColor(dc_handle);
    }

    COLORREF text::set_text_color(HDC dc_handle, COLORREF color) {
        return SetTextColor(dc_handle, color);
    }

    int32_t text::get_text_face(HDC dc_handle, int32_t cch_size, wchar_t *buf) {
        return GetTextFaceW(dc_handle, cch_size, buf);
    }

    bool text::get_text_metrics(HDC dc_handle, TEXTMETRICW *text_metric) {
        return GetTextMetricsW(dc_handle, text_metric);
    }

    uint32_t text::get_outline_text_metrics(HDC dc_handle,
                                                uint32_t size,
                                                OUTLINETEXTMETRICW *outline_text_metric) {
        return GetOutlineTextMetricsW(dc_handle, size, outline_text_metric);
    }

    bool text::get_text_extent_point(HDC dc_handle,
                                     const wchar_t *text,
                                     int32_t cch_size,
                                     int32_t max_extent,
                                     int32_t *fit,
                                     int32_t *dx,
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
                                       int32_t cch_size,
                                       SIZE *size) {
        return GetTextExtentPoint32W(dc_handle, text, cch_size, size);
    }

    bool text::get_text_extent_point_index(HDC dc_handle,
                                           uint16_t *glyph_index_array,
                                           int32_t glyph_index_num,
                                           int32_t max_extent,
                                           int32_t *fit,
                                           int32_t *dx,
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
                                           uint16_t *glyph_index_array,
                                           int32_t glyph_index_num,
                                           SIZE *size) {
        return GetTextExtentPointI(dc_handle,
                                   glyph_index_array,
                                   glyph_index_num,
                                   size);
    }
}
