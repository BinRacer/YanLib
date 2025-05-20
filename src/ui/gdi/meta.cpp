//
// Created by forkernel on 2025/5/5.
//

#include "meta.h"

namespace YanLib::ui::gdi {
    HDC meta::create_enhance_file(HDC dc_handle,
                                  const char *file_name,
                                  const RECT *rect,
                                  const char *description) {
        return CreateEnhMetaFileA(dc_handle, file_name, rect, description);
    }

    HDC meta::create_enhance_file(HDC dc_handle,
                                  const wchar_t *file_name,
                                  const RECT *rect,
                                  const wchar_t *description) {
        return CreateEnhMetaFileW(dc_handle, file_name, rect, description);
    }

    HENHMETAFILE meta::close_enhance_file(HDC dc_handle) {
        return CloseEnhMetaFile(dc_handle);
    }

    bool meta::delete_enhance_file(HENHMETAFILE enh_meta_file_handle) {
        return DeleteEnhMetaFile(enh_meta_file_handle);
    }

    bool meta::enum_enhance_file(HDC dc_handle,
                                 HENHMETAFILE enh_meta_file_handle,
                                 ENHMFENUMPROC enh_meta_file_proc,
                                 void *param,
                                 const RECT *rect) {
        return EnumEnhMetaFile(dc_handle, enh_meta_file_handle,
                               enh_meta_file_proc, param, rect);
    }

    HENHMETAFILE meta::copy_enhance_file(HENHMETAFILE enh_meta_file_handle,
                                         const char *file_name) {
        return CopyEnhMetaFileA(enh_meta_file_handle, file_name);
    }

    HENHMETAFILE meta::copy_enhance_file(HENHMETAFILE enh_meta_file_handle,
                                         const wchar_t *file_name) {
        return CopyEnhMetaFileW(enh_meta_file_handle, file_name);
    }

    bool meta::play_enhance_file(HDC dc_handle,
                                 HENHMETAFILE enh_meta_file_handle,
                                 const RECT *rect) {
        return PlayEnhMetaFile(dc_handle, enh_meta_file_handle, rect);
    }

    bool meta::play_enhance_file_record(HDC dc_handle,
                                        std::vector<HANDLETABLE> &handles,
                                        const ENHMETARECORD *enh_meta_record) {
        return PlayEnhMetaFileRecord(dc_handle, handles.data(), enh_meta_record,
                                     handles.size());
    }

    HENHMETAFILE meta::get_enhance_file(const char *file_name) {
        return GetEnhMetaFileA(file_name);
    }

    HENHMETAFILE meta::get_enhance_file(const wchar_t *file_name) {
        return GetEnhMetaFileW(file_name);
    }

    uint32_t meta::get_enhance_file_header(HENHMETAFILE enh_meta_file_handle,
                                           ENHMETAHEADER *buf,
                                           uint32_t size) {
        return GetEnhMetaFileHeader(enh_meta_file_handle, size, buf);
    }

    uint32_t
    meta::get_enhance_file_description(HENHMETAFILE enh_meta_file_handle,
                                       std::string &description) {
        return GetEnhMetaFileDescriptionA(enh_meta_file_handle,
                                          description.size(),
                                          description.data());
    }

    uint32_t
    meta::get_enhance_file_description(HENHMETAFILE enh_meta_file_handle,
                                       std::wstring &description) {
        return GetEnhMetaFileDescriptionW(enh_meta_file_handle,
                                          description.size(),
                                          description.data());
    }

    uint32_t meta::get_enhance_file_palette_entries(
            HENHMETAFILE enh_meta_file_handle,
            std::vector<PALETTEENTRY> &palette_entry) {
        return GetEnhMetaFilePaletteEntries(enh_meta_file_handle,
                                            palette_entry.size(),
                                            palette_entry.data());
    }

    uint32_t meta::get_window_file_bits(HENHMETAFILE enh_meta_file_handle,
                                        uint8_t *buf,
                                        uint32_t size,
                                        MappingMode mode,
                                        HDC dc_handle) {
        return GetWinMetaFileBits(enh_meta_file_handle, size, buf,
                                  static_cast<int32_t>(mode), dc_handle);
    }

    HENHMETAFILE
    meta::set_window_file_bits(const uint8_t *buf,
                               uint32_t size,
                               HDC dc_handle,
                               const METAFILEPICT *meta_file_pict) {
        return SetWinMetaFileBits(size, buf, dc_handle, meta_file_pict);
    }

    uint32_t meta::get_enhance_file_bits(HENHMETAFILE enh_meta_file_handle,
                                         uint8_t *buf,
                                         uint32_t size) {
        return GetEnhMetaFileBits(enh_meta_file_handle, size, buf);
    }

    HENHMETAFILE meta::set_enhance_file_bits(const uint8_t *buf,
                                             uint32_t size) {
        return SetEnhMetaFileBits(size, buf);
    }

    bool meta::gdi_comment(HDC dc_handle, const uint8_t *buf, uint32_t size) {
        return GdiComment(dc_handle, size, buf);
    }
} // namespace YanLib::ui::gdi
