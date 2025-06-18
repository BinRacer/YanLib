/* clang-format off */
/*
 * @file text.h
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
#ifndef TEXT_H
#define TEXT_H
#include <Windows.h>
#include <WinUser.h>
#include <wingdi.h>
#include <windef.h>
#include <cstdint>
#include <vector>
#include <string>
#include "gdi.h"
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
        out(HDC dc_handle, int32_t x, int32_t y, const std::string &text);

        static bool
        out(HDC dc_handle, int32_t x, int32_t y, const std::wstring &text);

        static bool out(HDC dc_handle,
                        int32_t x,
                        int32_t y,
                        const RECT *rect,
                        const std::string &text,
                        const int32_t dx[],
                        OutputOption options = OutputOption::Clipped |
                                OutputOption::Opaque |
                                OutputOption::GlyphIndex);

        static bool out(HDC dc_handle,
                        int32_t x,
                        int32_t y,
                        const RECT *rect,
                        const std::wstring &text,
                        const int32_t dx[],
                        OutputOption options = OutputOption::Clipped |
                                OutputOption::Opaque |
                                OutputOption::GlyphIndex);

        static int32_t tabbed_out(HDC dc_handle,
                                  int32_t x,
                                  int32_t y,
                                  const std::string &text,
                                  int32_t tab_pos,
                                  const int32_t *tab_stop_pos,
                                  int32_t tab_origin);

        static int32_t tabbed_out(HDC dc_handle,
                                  int32_t x,
                                  int32_t y,
                                  const std::wstring &text,
                                  int32_t tab_pos,
                                  const int32_t *tab_stop_pos,
                                  int32_t tab_origin);

        static bool poly_out(HDC dc_handle,
                             const std::vector<POLYTEXTA> &poly_text);

        static bool poly_out(HDC dc_handle,
                             const std::vector<POLYTEXTW> &poly_text);

        static int32_t draw(HDC dc_handle,
                            const std::string &text,
                            RECT *rect,
                            TextFormat format);

        static int32_t draw(HDC dc_handle,
                            const std::wstring &text,
                            RECT *rect,
                            TextFormat format);

        static int32_t draw(HDC dc_handle,
                            std::string &text,
                            RECT *rect,
                            DRAWTEXTPARAMS *draw_text_param /* nullptr */,
                            TextFormat format);

        static int32_t draw(HDC dc_handle,
                            std::wstring &text,
                            RECT *rect,
                            DRAWTEXTPARAMS *draw_text_param /* nullptr */,
                            TextFormat format);

        static uint32_t set_mapper_on(HDC dc_handle);

        static uint32_t set_mapper_off(HDC dc_handle);

        static bool
        set_justification(HDC dc_handle, int32_t extra, int32_t count);

        static bool get_aspect_ratio_filter(HDC dc_handle, SIZE *size);

        static bool get_char_width32(HDC dc_handle,
                                     uint32_t first,
                                     uint32_t last,
                                     int32_t *buf);

        static bool get_char_width_float(HDC dc_handle,
                                         uint32_t code_point_first,
                                         uint32_t code_point_last,
                                         FLOAT *buf);

        static bool get_char_width_index(HDC dc_handle,
                                         uint32_t index,
                                         std::vector<uint16_t> &glyph_index,
                                         int32_t *widths);

        static uint32_t get_char_placement(HDC dc_handle,
                                           const std::string &text,
                                           int32_t mex_extent,
                                           GCP_RESULTSA *results,
                                           LangInfo flag);

        static uint32_t get_char_placement(HDC dc_handle,
                                           const std::wstring &text,
                                           int32_t mex_extent,
                                           GCP_RESULTSW *results,
                                           LangInfo flag);

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

        static uint32_t
        get_glyph_indices(HDC dc_handle,
                          const std::string &text,
                          std::vector<uint16_t> &glyph_index,
                          uint32_t flag = GGI_MARK_NONEXISTING_GLYPHS);

        static uint32_t
        get_glyph_indices(HDC dc_handle,
                          const std::wstring &text,
                          std::vector<uint16_t> &glyph_index,
                          uint32_t flag = GGI_MARK_NONEXISTING_GLYPHS);

        static uint32_t get_glyph_outline(HDC dc_handle,
                                          uint32_t ch,
                                          DataFormat format,
                                          GLYPHMETRICS *glyph_metrics,
                                          void *buf,
                                          uint32_t size,
                                          const MAT2 *mat2);

        static uint32_t get_kerning_pairs(HDC dc_handle,
                                          uint32_t pairs,
                                          KERNINGPAIR *kern_pair);

        static bool get_rasterizer_caps(RASTERIZER_STATUS *rasterizer_status);

        static uint32_t get_tabbed_extent(HDC dc_handle,
                                          const std::string &text,
                                          int32_t tab_pos,
                                          const int32_t *tab_stop_pos);

        static uint32_t get_tabbed_extent(HDC dc_handle,
                                          const std::wstring &text,
                                          int32_t tab_pos,
                                          const int32_t *tab_stop_pos);

        static AlignOption get_align(HDC dc_handle);

        static AlignOption set_align(HDC dc_handle, AlignOption align);

        static int32_t get_character_extra(HDC dc_handle);

        static int32_t set_character_extra(HDC dc_handle, int32_t extra);

        static COLORREF get_color(HDC dc_handle);

        static COLORREF set_color(HDC dc_handle, COLORREF color);

        static int32_t get_face(HDC dc_handle, std::string &face_name);

        static int32_t get_face(HDC dc_handle, std::wstring &face_name);

        static bool get_metrics(HDC dc_handle, TEXTMETRICA *text_metric);

        static bool get_metrics(HDC dc_handle, TEXTMETRICW *text_metric);

        static uint32_t
        get_outline_metrics(HDC dc_handle,
                            OUTLINETEXTMETRICA *outline_text_metric,
                            uint32_t size);

        static uint32_t
        get_outline_metrics(HDC dc_handle,
                            OUTLINETEXTMETRICW *outline_text_metric,
                            uint32_t size);

        static bool get_extent_point(HDC dc_handle,
                                     const std::string &text,
                                     int32_t max_extent,
                                     int32_t *fit,
                                     int32_t *dx,
                                     SIZE *size);

        static bool get_extent_point(HDC dc_handle,
                                     const std::wstring &text,
                                     int32_t max_extent,
                                     int32_t *fit,
                                     int32_t *dx,
                                     SIZE *size);

        static bool
        get_extent_point32(HDC dc_handle, const std::string &text, SIZE *size);

        static bool
        get_extent_point32(HDC dc_handle, const std::wstring &text, SIZE *size);

        static bool get_extent_point_index(HDC dc_handle,
                                           std::vector<uint16_t> &glyph_index,
                                           int32_t max_extent,
                                           int32_t *fit,
                                           int32_t *dx,
                                           SIZE *size);

        static bool get_extent_point_index(HDC dc_handle,
                                           std::vector<uint16_t> &glyph_index,
                                           SIZE *size);
    };
} // namespace YanLib::ui::gdi
#endif // TEXT_H
