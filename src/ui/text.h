//
// Created by forkernel on 2025/5/3.
//

#ifndef TEXT_H
#define TEXT_H
#include <Windows.h>

namespace YanLib::ui {
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
                                 UINT options,
                                 const RECT *rect,
                                 const wchar_t *text,
                                 int cch_size,
                                 const INT *dx);

        static LONG tabbed_text_out(HDC dc_handle,
                                    int x,
                                    int y,
                                    const wchar_t *text,
                                    int cch_size,
                                    int tab_positions,
                                    const INT *tab_stop_positions,
                                    int tab_origin);

        static bool poly_text_out(HDC dc_handle,
                                  const POLYTEXTW *poly_text,
                                  int num);

        static int draw_text(HDC dc_handle,
                             const wchar_t *text,
                             int cch_size,
                             RECT* rect,
                             UINT format);

        static int draw_text(HDC dc_handle,
                             wchar_t *text,
                             int cch_size,
                             RECT* rect,
                             UINT format,
                             DRAWTEXTPARAMS* draw_text_param);

        static DWORD set_mapper_flags(HDC dc_handle, DWORD flag);

        static bool set_text_justification(HDC dc_handle, int extra, int count);

        static bool get_aspect_ratio_filter(HDC dc_handle, SIZE* size);

        static bool get_char_width32(HDC dc_handle,
                                     UINT ch_first,
                                     UINT ch_last,
                                     INT* buf);

        static bool get_char_width_float(HDC dc_handle,
                                         UINT code_point_first,
                                         UINT code_point_last,
                                         FLOAT* buf);

        static bool get_char_width_index(HDC dc_handle,
                                         UINT glyph_index_first,
                                         UINT glyph_index_num,
                                         WORD* glyph_index_array,
                                         INT* widths);

        static DWORD get_char_placement(HDC dc_handle,
                                        const wchar_t *text,
                                        int cch_size,
                                        int mex_extent,
                                        GCP_RESULTSW* results,
                                        DWORD flag);

        static bool get_char_abc_widths(HDC dc_handle,
                                        UINT ch_first,
                                        UINT ch_last,
                                        ABC* abc);

        static bool get_char_abc_widths_float(HDC dc_handle,
                                              UINT code_point_first,
                                              UINT code_point_last,
                                              ABCFLOAT* abc_float);

        static bool get_char_abc_widths_index(HDC dc_handle,
                                              UINT first_glyph_index,
                                              UINT glyph_index_num,
                                              WORD* glyph_index_array,
                                              ABC* abc);

        static DWORD get_glyph_indices(HDC dc_handle,
                                       const wchar_t *text,
                                       int cch_size,
                                       WORD* glyph_index,
                                       DWORD flag);

        static DWORD get_glyph_outline(HDC dc_handle,
                                       UINT ch,
                                       UINT format,
                                       GLYPHMETRICS* glyph_metrics,
                                       DWORD size,
                                       void *buf,
                                       const MAT2 *mat2);

        static DWORD get_kerning_pairs(HDC dc_handle,
                                       DWORD pairs,
                                       KERNINGPAIR* kern_pair);

        static bool get_rasterizer_caps(RASTERIZER_STATUS* rasterizer_status,
                                        UINT size);

        static DWORD get_tabbed_text_extent(HDC dc_handle,
                                            const wchar_t *text,
                                            int cch_size,
                                            int tab_positions,
                                            const INT *tab_stop_positions);

        static UINT get_text_align(HDC dc_handle);

        static UINT set_text_align(HDC dc_handle, UINT align);

        static int get_text_character_extra(HDC dc_handle);

        static int set_text_character_extra(HDC dc_handle, int extra);

        static COLORREF get_text_color(HDC dc_handle);

        static COLORREF set_text_color(HDC dc_handle, COLORREF color);

        static int get_text_face(HDC dc_handle, int cch_size, wchar_t *buf);

        static bool get_text_metrics(HDC dc_handle, TEXTMETRICW* text_metric);

        static UINT get_outline_text_metrics(
            HDC dc_handle,
            UINT size,
            OUTLINETEXTMETRICW* outline_text_metric);

        static bool get_text_extent_point(HDC dc_handle,
                                          const wchar_t *text,
                                          int cch_size,
                                          int max_extent,
                                          INT* fit,
                                          INT* dx,
                                          SIZE* size);

        static bool get_text_extent_point32(HDC dc_handle,
                                            const wchar_t *text,
                                            int cch_size,
                                            SIZE* size);

        static bool get_text_extent_point_index(HDC dc_handle,
                                                WORD* glyph_index_array,
                                                int glyph_index_num,
                                                int max_extent,
                                                INT* fit,
                                                INT* dx,
                                                SIZE* size);

        static bool get_text_extent_point_index(HDC dc_handle,
                                                WORD* glyph_index_array,
                                                int glyph_index_num,
                                                SIZE* size);
    };
}
#endif //TEXT_H
