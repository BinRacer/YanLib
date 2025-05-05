//
// Created by forkernel on 2025/5/5.
//

#include "meta.h"

namespace YanLib::ui::gdi {
    HDC meta::create_enhance_meta_file(HDC dc_handle,
                                       const wchar_t *file_name,
                                       const RECT *rect,
                                       const wchar_t *desc) {
        return CreateEnhMetaFileW(dc_handle, file_name, rect, desc);
    }

    HENHMETAFILE meta::close_enhance_meta_file(HDC dc_handle) {
        return CloseEnhMetaFile(dc_handle);
    }

    bool meta::delete_enhance_meta_file(HENHMETAFILE enh_meta_file_handle) {
        return DeleteEnhMetaFile(enh_meta_file_handle);
    }

    bool meta::enum_enhance_meta_file(HDC dc_handle,
                                      HENHMETAFILE enh_meta_file_handle,
                                      ENHMFENUMPROC enh_meta_file_proc,
                                      void *param,
                                      const RECT *rect) {
        return EnumEnhMetaFile(dc_handle,
                               enh_meta_file_handle,
                               enh_meta_file_proc,
                               param,
                               rect);
    }

    HENHMETAFILE meta::copy_enhance_meta_file(HENHMETAFILE enh_meta_file_handle,
                                              const wchar_t *file_name) {
        return CopyEnhMetaFileW(enh_meta_file_handle, file_name);
    }

    bool meta::play_enhance_meta_file(HDC dc_handle,
                                      HENHMETAFILE enh_meta_file_handle,
                                      const RECT *rect) {
        return PlayEnhMetaFile(dc_handle, enh_meta_file_handle, rect);
    }

    bool meta::play_enhance_meta_file_record(HDC dc_handle,
                                             HANDLETABLE *table_handle,
                                             const ENHMETARECORD *enh_meta_record,
                                             unsigned int table_num) {
        return PlayEnhMetaFileRecord(dc_handle,
                                     table_handle,
                                     enh_meta_record,
                                     table_num);
    }

    HENHMETAFILE meta::get_enhance_meta_file(const wchar_t *file_name) {
        return GetEnhMetaFileW(file_name);
    }

    unsigned int meta::get_enhance_meta_file_header(HENHMETAFILE enh_meta_file_handle,
                                            unsigned int size,
                                            ENHMETAHEADER *buf) {
        return GetEnhMetaFileHeader(enh_meta_file_handle, size, buf);
    }

    unsigned int meta::get_enhance_meta_file_description(HENHMETAFILE enh_meta_file_handle,
                                                 unsigned int cch_size,
                                                 wchar_t *description) {
        return GetEnhMetaFileDescriptionW(enh_meta_file_handle,
                                          cch_size,
                                          description);
    }

    unsigned int meta::get_enhance_meta_file_palette_entries(
        HENHMETAFILE enh_meta_file_handle,
        unsigned int num,
        PALETTEENTRY *palette_entries) {
        return GetEnhMetaFilePaletteEntries(enh_meta_file_handle,
                                            num,
                                            palette_entries);
    }

    unsigned int meta::get_win_meta_file_bits(HENHMETAFILE enh_meta_file_handle,
                                      unsigned int size,
                                      uint8_t *buf,
                                      int map_mode,
                                      HDC dc_handle) {
        return GetWinMetaFileBits(enh_meta_file_handle,
                                  size,
                                  buf,
                                  map_mode,
                                  dc_handle);
    }

    HENHMETAFILE meta::set_win_meta_file_bits(
        unsigned int size,
        const uint8_t *buf,
        HDC dc_handle,
        const METAFILEPICT *meta_file_pict) {
        return SetWinMetaFileBits(size, buf, dc_handle, meta_file_pict);
    }

    unsigned int meta::get_enhance_meta_file_bits(HENHMETAFILE enh_meta_file_handle,
                                          unsigned int size,
                                          uint8_t *buf) {
        return GetEnhMetaFileBits(enh_meta_file_handle, size, buf);
    }

    HENHMETAFILE meta::set_enhance_meta_file_bits(unsigned int size,
                                                  const uint8_t *buf) {
        return SetEnhMetaFileBits(size, buf);
    }

    bool meta::gdi_comment(HDC dc_handle, unsigned int size, const uint8_t *buf) {
        return GdiComment(dc_handle, size, buf);
    }
}
