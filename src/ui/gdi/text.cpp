//
// Created by forkernel on 2025/5/3.
//

#include "text.h"

namespace YanLib::ui::gdi {
bool text::text_out(HDC dc_handle,
    int32_t             x,
    int32_t             y,
    const std::string  &text) {
    return TextOutA(
        dc_handle, x, y, text.data(), static_cast<int>(text.size()));
}

bool text::text_out(HDC dc_handle,
    int32_t             x,
    int32_t             y,
    const std::wstring &text) {
    return TextOutW(
        dc_handle, x, y, text.data(), static_cast<int>(text.size()));
}

bool text::ext_text_out(HDC dc_handle,
    int32_t                 x,
    int32_t                 y,
    uint32_t                options,
    const RECT             *rect,
    const std::string      &text,
    const int32_t          *dx) {
    return ExtTextOutA(
        dc_handle, x, y, options, rect, text.data(), text.size(), dx);
}

bool text::ext_text_out(HDC dc_handle,
    int32_t                 x,
    int32_t                 y,
    uint32_t                options,
    const RECT             *rect,
    const std::wstring     &text,
    const int32_t          *dx) {
    return ExtTextOutW(
        dc_handle, x, y, options, rect, text.data(), text.size(), dx);
}

long text::tabbed_text_out(HDC dc_handle,
    int32_t                    x,
    int32_t                    y,
    const std::string         &text,
    int32_t                    tab_pos,
    const int32_t             *tab_stop_pos,
    int32_t                    tab_origin) {
    return TabbedTextOutA(dc_handle, x, y, text.data(),
        static_cast<int>(text.size()), tab_pos, tab_stop_pos, tab_origin);
}

long text::tabbed_text_out(HDC dc_handle,
    int32_t                    x,
    int32_t                    y,
    const std::wstring        &text,
    int32_t                    tab_pos,
    const int32_t             *tab_stop_pos,
    int32_t                    tab_origin) {
    return TabbedTextOutW(dc_handle, x, y, text.data(),
        static_cast<int>(text.size()), tab_pos, tab_stop_pos, tab_origin);
}

bool text::poly_text_out(HDC      dc_handle,
    const std::vector<POLYTEXTA> &poly_text) {
    return PolyTextOutA(
        dc_handle, poly_text.data(), static_cast<int>(poly_text.size()));
}

bool text::poly_text_out(HDC      dc_handle,
    const std::vector<POLYTEXTW> &poly_text) {
    return PolyTextOutW(
        dc_handle, poly_text.data(), static_cast<int>(poly_text.size()));
}

int32_t text::draw_text(HDC dc_handle,
    const std::string      &text,
    RECT                   *rect,
    uint32_t                format) {
    return DrawTextA(
        dc_handle, text.data(), static_cast<int>(text.size()), rect, format);
}

int32_t text::draw_text(HDC dc_handle,
    const std::wstring     &text,
    RECT                   *rect,
    uint32_t                format) {
    return DrawTextW(
        dc_handle, text.data(), static_cast<int>(text.size()), rect, format);
}

int32_t text::draw_text(HDC dc_handle,
    std::string            &text,
    RECT                   *rect,
    uint32_t                format,
    DRAWTEXTPARAMS         *draw_text_param) {
    return DrawTextExA(dc_handle, text.data(), static_cast<int>(text.size()),
        rect, format, draw_text_param);
}

int32_t text::draw_text(HDC dc_handle,
    std::wstring           &text,
    RECT                   *rect,
    uint32_t                format,
    DRAWTEXTPARAMS         *draw_text_param) {
    return DrawTextExW(dc_handle, text.data(), static_cast<int>(text.size()),
        rect, format, draw_text_param);
}

uint32_t text::set_mapper_flags(HDC dc_handle, uint32_t flag) {
    return SetMapperFlags(dc_handle, flag);
}

bool text::set_text_justification(HDC dc_handle, int32_t extra, int32_t count) {
    return SetTextJustification(dc_handle, extra, count);
}

bool text::get_aspect_ratio_filter(HDC dc_handle, SIZE *size) {
    return GetAspectRatioFilterEx(dc_handle, size);
}

bool text::get_char_width32(HDC dc_handle,
    uint32_t                    first,
    uint32_t                    last,
    int32_t                    *buf) {
    return GetCharWidth32W(dc_handle, first, last, buf);
}

bool text::get_char_width_float(HDC dc_handle,
    uint32_t                        code_point_first,
    uint32_t                        code_point_last,
    FLOAT                          *buf) {
    return GetCharWidthFloatW(
        dc_handle, code_point_first, code_point_last, buf);
}

bool text::get_char_width_index(HDC dc_handle,
    uint32_t                        index,
    std::vector<uint16_t>          &glyph_index,
    int32_t                        *widths) {
    return GetCharWidthI(
        dc_handle, index, glyph_index.size(), glyph_index.data(), widths);
}

bool text::get_char_abc_widths(HDC dc_handle,
    uint32_t                       first,
    uint32_t                       last,
    ABC                            abc[]) {
    return GetCharABCWidthsW(dc_handle, first, last, abc);
}

bool text::get_char_abc_widths_float(HDC dc_handle,
    uint32_t                             first,
    uint32_t                             last,
    ABCFLOAT                             abc_float[]) {
    return GetCharABCWidthsFloatW(dc_handle, first, last, abc_float);
}

bool text::get_char_abc_widths_index(HDC dc_handle,
    uint32_t                             index,
    std::vector<uint16_t>               &glyph_index,
    std::vector<ABC>                    &abc) {
    return GetCharABCWidthsI(
        dc_handle, index, glyph_index.size(), glyph_index.data(), abc.data());
}

uint32_t text::get_char_placement(HDC dc_handle,
    const std::string                &text,
    int32_t                           mex_extent,
    GCP_RESULTSA                     *results,
    uint32_t                          flag) {
    return GetCharacterPlacementA(dc_handle, text.data(),
        static_cast<int>(text.size()), mex_extent, results, flag);
}

uint32_t text::get_char_placement(HDC dc_handle,
    const std::wstring               &text,
    int32_t                           mex_extent,
    GCP_RESULTSW                     *results,
    uint32_t                          flag) {
    return GetCharacterPlacementW(dc_handle, text.data(),
        static_cast<int>(text.size()), mex_extent, results, flag);
}

uint32_t text::get_glyph_indices(HDC dc_handle,
    const std::string               &text,
    std::vector<uint16_t>           &glyph_index,
    uint32_t                         flag) {
    return GetGlyphIndicesA(dc_handle, text.data(),
        static_cast<int>(text.size()), glyph_index.data(), flag);
}

uint32_t text::get_glyph_indices(HDC dc_handle,
    const std::wstring              &text,
    std::vector<uint16_t>           &glyph_index,
    uint32_t                         flag) {
    return GetGlyphIndicesW(dc_handle, text.data(),
        static_cast<int>(text.size()), glyph_index.data(), flag);
}

uint32_t text::get_glyph_outline(HDC dc_handle,
    uint32_t                         ch,
    uint32_t                         format,
    GLYPHMETRICS                    *glyph_metrics,
    uint32_t                         size,
    void                            *buf,
    const MAT2                      *mat2) {
    return GetGlyphOutlineW(
        dc_handle, ch, format, glyph_metrics, size, buf, mat2);
}

uint32_t
text::get_kerning_pairs(HDC dc_handle, uint32_t pairs, KERNINGPAIR *kern_pair) {
    return GetKerningPairsW(dc_handle, pairs, kern_pair);
}

bool text::get_rasterizer_caps(RASTERIZER_STATUS *rasterizer_status) {
    return GetRasterizerCaps(rasterizer_status, sizeof(RASTERIZER_STATUS));
}

uint32_t text::get_tabbed_text_extent(HDC dc_handle,
    const std::string                    &text,
    int32_t                               tab_pos,
    const int32_t                        *tab_stop_pos) {
    return GetTabbedTextExtentA(dc_handle, text.data(),
        static_cast<int>(text.size()), tab_pos, tab_stop_pos);
}

uint32_t text::get_tabbed_text_extent(HDC dc_handle,
    const std::wstring                   &text,
    int32_t                               tab_pos,
    const int32_t                        *tab_stop_pos) {
    return GetTabbedTextExtentW(dc_handle, text.data(),
        static_cast<int>(text.size()), tab_pos, tab_stop_pos);
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

int32_t text::get_text_face(HDC dc_handle, std::string &text) {
    return GetTextFaceA(dc_handle, static_cast<int>(text.size()), text.data());
}

int32_t text::get_text_face(HDC dc_handle, std::wstring &text) {
    return GetTextFaceW(dc_handle, static_cast<int>(text.size()), text.data());
}

bool text::get_text_metrics(HDC dc_handle, TEXTMETRICA *text_metric) {
    return GetTextMetricsA(dc_handle, text_metric);
}

bool text::get_text_metrics(HDC dc_handle, TEXTMETRICW *text_metric) {
    return GetTextMetricsW(dc_handle, text_metric);
}

uint32_t text::get_outline_text_metrics(HDC dc_handle,
    uint32_t                                size,
    OUTLINETEXTMETRICA                     *outline_text_metric) {
    return GetOutlineTextMetricsA(dc_handle, size, outline_text_metric);
}

uint32_t text::get_outline_text_metrics(HDC dc_handle,
    uint32_t                                size,
    OUTLINETEXTMETRICW                     *outline_text_metric) {
    return GetOutlineTextMetricsW(dc_handle, size, outline_text_metric);
}

bool text::get_text_extent_point(HDC dc_handle,
    const std::string               &text,
    int32_t                          max_extent,
    int32_t                         *fit,
    int32_t                         *dx,
    SIZE                            *size) {
    return GetTextExtentExPointA(dc_handle, text.data(),
        static_cast<int>(text.size()), max_extent, fit, dx, size);
}

bool text::get_text_extent_point(HDC dc_handle,
    const std::wstring              &text,
    int32_t                          max_extent,
    int32_t                         *fit,
    int32_t                         *dx,
    SIZE                            *size) {
    return GetTextExtentExPointW(dc_handle, text.data(),
        static_cast<int>(text.size()), max_extent, fit, dx, size);
}

bool text::get_text_extent_point32(HDC dc_handle,
    const std::string                 &text,
    SIZE                              *size) {
    return GetTextExtentPoint32A(
        dc_handle, text.data(), static_cast<int>(text.size()), size);
}

bool text::get_text_extent_point32(HDC dc_handle,
    const std::wstring                &text,
    SIZE                              *size) {
    return GetTextExtentPoint32W(
        dc_handle, text.data(), static_cast<int>(text.size()), size);
}

bool text::get_text_extent_point_index(HDC dc_handle,
    std::vector<uint16_t>                 &glyph_index,
    int32_t                                max_extent,
    int32_t                               *fit,
    int32_t                               *dx,
    SIZE                                  *size) {
    return GetTextExtentExPointI(dc_handle, glyph_index.data(),
        static_cast<int>(glyph_index.size()), max_extent, fit, dx, size);
}

bool text::get_text_extent_point_index(HDC dc_handle,
    std::vector<uint16_t>                 &glyph_index,
    SIZE                                  *size) {
    return GetTextExtentPointI(dc_handle, glyph_index.data(),
        static_cast<int>(glyph_index.size()), size);
}
} // namespace YanLib::ui::gdi
