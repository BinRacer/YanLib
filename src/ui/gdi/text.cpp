/* clang-format off */
/*
 * @file text.cpp
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
#include "text.h"

namespace YanLib::ui::gdi {
    bool
    text::out(HDC dc_handle, int32_t x, int32_t y, const std::string &text) {
        return TextOutA(dc_handle, x, y, text.data(),
                        static_cast<int32_t>(text.size()));
    }

    bool
    text::out(HDC dc_handle, int32_t x, int32_t y, const std::wstring &text) {
        return TextOutW(dc_handle, x, y, text.data(),
                        static_cast<int32_t>(text.size()));
    }

    bool text::out(HDC dc_handle,
                   int32_t x,
                   int32_t y,
                   const RECT *rect,
                   const std::string &text,
                   const int32_t dx[],
                   OutputOption options) {
        return ExtTextOutA(dc_handle, x, y, static_cast<uint32_t>(options),
                           rect, text.data(), text.size(), dx);
    }

    bool text::out(HDC dc_handle,
                   int32_t x,
                   int32_t y,
                   const RECT *rect,
                   const std::wstring &text,
                   const int32_t dx[],
                   OutputOption options) {
        return ExtTextOutW(dc_handle, x, y, static_cast<uint32_t>(options),
                           rect, text.data(), text.size(), dx);
    }

    int32_t text::tabbed_out(HDC dc_handle,
                             int32_t x,
                             int32_t y,
                             const std::string &text,
                             int32_t tab_pos,
                             const int32_t *tab_stop_pos,
                             int32_t tab_origin) {
        return TabbedTextOutA(dc_handle, x, y, text.data(),
                              static_cast<int32_t>(text.size()), tab_pos,
                              tab_stop_pos, tab_origin);
    }

    int32_t text::tabbed_out(HDC dc_handle,
                             int32_t x,
                             int32_t y,
                             const std::wstring &text,
                             int32_t tab_pos,
                             const int32_t *tab_stop_pos,
                             int32_t tab_origin) {
        return TabbedTextOutW(dc_handle, x, y, text.data(),
                              static_cast<int32_t>(text.size()), tab_pos,
                              tab_stop_pos, tab_origin);
    }

    bool text::poly_out(HDC dc_handle,
                        const std::vector<POLYTEXTA> &poly_text) {
        return PolyTextOutA(dc_handle, poly_text.data(),
                            static_cast<int32_t>(poly_text.size()));
    }

    bool text::poly_out(HDC dc_handle,
                        const std::vector<POLYTEXTW> &poly_text) {
        return PolyTextOutW(dc_handle, poly_text.data(),
                            static_cast<int32_t>(poly_text.size()));
    }

    int32_t text::draw(HDC dc_handle,
                       const std::string &text,
                       RECT *rect,
                       TextFormat format) {
        return DrawTextA(dc_handle, text.data(),
                         static_cast<int32_t>(text.size()), rect,
                         static_cast<uint32_t>(format));
    }

    int32_t text::draw(HDC dc_handle,
                       const std::wstring &text,
                       RECT *rect,
                       TextFormat format) {
        return DrawTextW(dc_handle, text.data(),
                         static_cast<int32_t>(text.size()), rect,
                         static_cast<uint32_t>(format));
    }

    int32_t text::draw(HDC dc_handle,
                       std::string &text,
                       RECT *rect,
                       DRAWTEXTPARAMS *draw_text_param,
                       TextFormat format) {
        return DrawTextExA(dc_handle, text.data(),
                           static_cast<int32_t>(text.size()), rect,
                           static_cast<uint32_t>(format), draw_text_param);
    }

    int32_t text::draw(HDC dc_handle,
                       std::wstring &text,
                       RECT *rect,
                       DRAWTEXTPARAMS *draw_text_param,
                       TextFormat format) {
        return DrawTextExW(dc_handle, text.data(),
                           static_cast<int32_t>(text.size()), rect,
                           static_cast<uint32_t>(format), draw_text_param);
    }

    uint32_t text::set_mapper_on(HDC dc_handle) {
        return SetMapperFlags(dc_handle, TRUE);
    }

    uint32_t text::set_mapper_off(HDC dc_handle) {
        return SetMapperFlags(dc_handle, FALSE);
    }

    bool text::set_justification(HDC dc_handle, int32_t extra, int32_t count) {
        return SetTextJustification(dc_handle, extra, count);
    }

    bool text::get_aspect_ratio_filter(HDC dc_handle, SIZE *size) {
        return GetAspectRatioFilterEx(dc_handle, size);
    }

    bool text::get_char_width32(HDC dc_handle,
                                uint32_t first,
                                uint32_t last,
                                int32_t *buf) {
        return GetCharWidth32W(dc_handle, first, last, buf);
    }

    bool text::get_char_width_float(HDC dc_handle,
                                    uint32_t code_point_first,
                                    uint32_t code_point_last,
                                    FLOAT *buf) {
        return GetCharWidthFloatW(dc_handle, code_point_first, code_point_last,
                                  buf);
    }

    bool text::get_char_width_index(HDC dc_handle,
                                    uint32_t index,
                                    std::vector<uint16_t> &glyph_index,
                                    int32_t *widths) {
        return GetCharWidthI(dc_handle, index, glyph_index.size(),
                             glyph_index.data(), widths);
    }

    bool text::get_char_abc_widths(HDC dc_handle,
                                   uint32_t first,
                                   uint32_t last,
                                   ABC abc[]) {
        return GetCharABCWidthsW(dc_handle, first, last, abc);
    }

    bool text::get_char_abc_widths_float(HDC dc_handle,
                                         uint32_t first,
                                         uint32_t last,
                                         ABCFLOAT abc_float[]) {
        return GetCharABCWidthsFloatW(dc_handle, first, last, abc_float);
    }

    bool text::get_char_abc_widths_index(HDC dc_handle,
                                         uint32_t index,
                                         std::vector<uint16_t> &glyph_index,
                                         std::vector<ABC> &abc) {
        return GetCharABCWidthsI(dc_handle, index, glyph_index.size(),
                                 glyph_index.data(), abc.data());
    }

    uint32_t text::get_char_placement(HDC dc_handle,
                                      const std::string &text,
                                      int32_t mex_extent,
                                      GCP_RESULTSA *results,
                                      LangInfo flag) {
        return GetCharacterPlacementA(dc_handle, text.data(),
                                      static_cast<int32_t>(text.size()),
                                      mex_extent, results,
                                      static_cast<uint32_t>(flag));
    }

    uint32_t text::get_char_placement(HDC dc_handle,
                                      const std::wstring &text,
                                      int32_t mex_extent,
                                      GCP_RESULTSW *results,
                                      LangInfo flag) {
        return GetCharacterPlacementW(dc_handle, text.data(),
                                      static_cast<int32_t>(text.size()),
                                      mex_extent, results,
                                      static_cast<uint32_t>(flag));
    }

    uint32_t text::get_glyph_indices(HDC dc_handle,
                                     const std::string &text,
                                     std::vector<uint16_t> &glyph_index,
                                     uint32_t flag) {
        return GetGlyphIndicesA(dc_handle, text.data(),
                                static_cast<int32_t>(text.size()),
                                glyph_index.data(), flag);
    }

    uint32_t text::get_glyph_indices(HDC dc_handle,
                                     const std::wstring &text,
                                     std::vector<uint16_t> &glyph_index,
                                     uint32_t flag) {
        return GetGlyphIndicesW(dc_handle, text.data(),
                                static_cast<int32_t>(text.size()),
                                glyph_index.data(), flag);
    }

    uint32_t text::get_glyph_outline(HDC dc_handle,
                                     uint32_t ch,
                                     DataFormat format,
                                     GLYPHMETRICS *glyph_metrics,
                                     void *buf,
                                     uint32_t size,
                                     const MAT2 *mat2) {
        return GetGlyphOutlineW(dc_handle, ch, static_cast<uint32_t>(format),
                                glyph_metrics, size, buf, mat2);
    }

    uint32_t text::get_kerning_pairs(HDC dc_handle,
                                     uint32_t pairs,
                                     KERNINGPAIR *kern_pair) {
        return GetKerningPairsW(dc_handle, pairs, kern_pair);
    }

    bool text::get_rasterizer_caps(RASTERIZER_STATUS *rasterizer_status) {
        return GetRasterizerCaps(rasterizer_status, sizeof(RASTERIZER_STATUS));
    }

    uint32_t text::get_tabbed_extent(HDC dc_handle,
                                     const std::string &text,
                                     int32_t tab_pos,
                                     const int32_t *tab_stop_pos) {
        return GetTabbedTextExtentA(dc_handle, text.data(),
                                    static_cast<int32_t>(text.size()), tab_pos,
                                    tab_stop_pos);
    }

    uint32_t text::get_tabbed_extent(HDC dc_handle,
                                     const std::wstring &text,
                                     int32_t tab_pos,
                                     const int32_t *tab_stop_pos) {
        return GetTabbedTextExtentW(dc_handle, text.data(),
                                    static_cast<int32_t>(text.size()), tab_pos,
                                    tab_stop_pos);
    }

    AlignOption text::get_align(HDC dc_handle) {
        return static_cast<AlignOption>(GetTextAlign(dc_handle));
    }

    AlignOption text::set_align(HDC dc_handle, AlignOption align) {
        return static_cast<AlignOption>(
                SetTextAlign(dc_handle, static_cast<UINT>(align)));
    }

    int32_t text::get_character_extra(HDC dc_handle) {
        return GetTextCharacterExtra(dc_handle);
    }

    int32_t text::set_character_extra(HDC dc_handle, int32_t extra) {
        return SetTextCharacterExtra(dc_handle, extra);
    }

    COLORREF text::get_color(HDC dc_handle) {
        return GetTextColor(dc_handle);
    }

    COLORREF text::set_color(HDC dc_handle, COLORREF color) {
        return SetTextColor(dc_handle, color);
    }

    int32_t text::get_face(HDC dc_handle, std::string &face_name) {
        return GetTextFaceA(dc_handle, static_cast<int32_t>(face_name.size()),
                            face_name.data());
    }

    int32_t text::get_face(HDC dc_handle, std::wstring &face_name) {
        return GetTextFaceW(dc_handle, static_cast<int32_t>(face_name.size()),
                            face_name.data());
    }

    bool text::get_metrics(HDC dc_handle, TEXTMETRICA *text_metric) {
        return GetTextMetricsA(dc_handle, text_metric);
    }

    bool text::get_metrics(HDC dc_handle, TEXTMETRICW *text_metric) {
        return GetTextMetricsW(dc_handle, text_metric);
    }

    uint32_t text::get_outline_metrics(HDC dc_handle,
                                       OUTLINETEXTMETRICA *outline_text_metric,
                                       uint32_t size) {
        return GetOutlineTextMetricsA(dc_handle, size, outline_text_metric);
    }

    uint32_t text::get_outline_metrics(HDC dc_handle,
                                       OUTLINETEXTMETRICW *outline_text_metric,
                                       uint32_t size) {
        return GetOutlineTextMetricsW(dc_handle, size, outline_text_metric);
    }

    bool text::get_extent_point(HDC dc_handle,
                                const std::string &text,
                                int32_t max_extent,
                                int32_t *fit,
                                int32_t *dx,
                                SIZE *size) {
        return GetTextExtentExPointA(dc_handle, text.data(),
                                     static_cast<int32_t>(text.size()),
                                     max_extent, fit, dx, size);
    }

    bool text::get_extent_point(HDC dc_handle,
                                const std::wstring &text,
                                int32_t max_extent,
                                int32_t *fit,
                                int32_t *dx,
                                SIZE *size) {
        return GetTextExtentExPointW(dc_handle, text.data(),
                                     static_cast<int32_t>(text.size()),
                                     max_extent, fit, dx, size);
    }

    bool text::get_extent_point32(HDC dc_handle,
                                  const std::string &text,
                                  SIZE *size) {
        return GetTextExtentPoint32A(dc_handle, text.data(),
                                     static_cast<int32_t>(text.size()), size);
    }

    bool text::get_extent_point32(HDC dc_handle,
                                  const std::wstring &text,
                                  SIZE *size) {
        return GetTextExtentPoint32W(dc_handle, text.data(),
                                     static_cast<int32_t>(text.size()), size);
    }

    bool text::get_extent_point_index(HDC dc_handle,
                                      std::vector<uint16_t> &glyph_index,
                                      int32_t max_extent,
                                      int32_t *fit,
                                      int32_t *dx,
                                      SIZE *size) {
        return GetTextExtentExPointI(dc_handle, glyph_index.data(),
                                     static_cast<int32_t>(glyph_index.size()),
                                     max_extent, fit, dx, size);
    }

    bool text::get_extent_point_index(HDC dc_handle,
                                      std::vector<uint16_t> &glyph_index,
                                      SIZE *size) {
        return GetTextExtentPointI(dc_handle, glyph_index.data(),
                                   static_cast<int32_t>(glyph_index.size()),
                                   size);
    }
} // namespace YanLib::ui::gdi
