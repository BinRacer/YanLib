//
// Created by forkernel on 2025/5/5.
//

#ifndef META_H
#define META_H
#include <cstdint>
#include <Windows.h>

namespace YanLib::ui::gdi {
    class meta {
    public:
        meta(const meta &other) = delete;

        meta(meta &&other) = delete;

        meta &operator=(const meta &other) = delete;

        meta &operator=(meta &&other) = delete;

        meta() = default;

        ~meta() = default;

        static HDC create_enhance_meta_file(HDC dc_handle,
                                            const wchar_t *file_name,
                                            const RECT *rect,
                                            const wchar_t *desc);

        static HENHMETAFILE close_enhance_meta_file(HDC dc_handle);

        static bool delete_enhance_meta_file(HENHMETAFILE enh_meta_file_handle);

        static bool enum_enhance_meta_file(HDC dc_handle,
                                           HENHMETAFILE enh_meta_file_handle,
                                           ENHMFENUMPROC enh_meta_file_proc,
                                           void *param,
                                           const RECT *rect);

        static HENHMETAFILE copy_enhance_meta_file(
            HENHMETAFILE enh_meta_file_handle,
            const wchar_t *file_name);

        static bool play_enhance_meta_file(HDC dc_handle,
                                           HENHMETAFILE enh_meta_file_handle,
                                           const RECT *rect);

        static bool play_enhance_meta_file_record(
            HDC dc_handle,
            HANDLETABLE *table_handle,
            const ENHMETARECORD *enh_meta_record,
            unsigned int table_num);

        static HENHMETAFILE get_enhance_meta_file(const wchar_t *file_name);

        static unsigned int get_enhance_meta_file_header(HENHMETAFILE enh_meta_file_handle,
                                                 unsigned int size,
                                                 ENHMETAHEADER *buf);

        static unsigned int get_enhance_meta_file_description(
            HENHMETAFILE enh_meta_file_handle,
            unsigned int cch_size,
            wchar_t *description);

        static unsigned int get_enhance_meta_file_palette_entries(
            HENHMETAFILE enh_meta_file_handle,
            unsigned int num,
            PALETTEENTRY *palette_entries);

        static unsigned int get_win_meta_file_bits(HENHMETAFILE enh_meta_file_handle,
                                           unsigned int size,
                                           uint8_t *buf,
                                           int map_mode,
                                           HDC dc_handle);

        static HENHMETAFILE set_win_meta_file_bits(
            unsigned int size,
            const uint8_t *buf,
            HDC dc_handle,
            const METAFILEPICT *meta_file_pict);

        static unsigned int get_enhance_meta_file_bits(HENHMETAFILE enh_meta_file_handle,
                                               unsigned int size,
                                               uint8_t *buf);

        static HENHMETAFILE set_enhance_meta_file_bits(unsigned int size,
                                                       const uint8_t *buf);

        static bool gdi_comment(HDC dc_handle,
                                unsigned int size,
                                const uint8_t *buf);
    };
}
#endif //META_H
