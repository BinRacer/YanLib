/* clang-format off */
/*
 * @file meta.h
 * @date 2025-05-05
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
#ifndef META_H
#define META_H
#include <cstdint>
#include <vector>
#include <string>
#include <Windows.h>

namespace YanLib::ui::gdi {
#ifndef MAPPINGMODE
#define MAPPINGMODE

    enum class MappingMode : int32_t {
        Text = MM_TEXT,
        LoMetric = MM_LOMETRIC,
        HiMetric = MM_HIMETRIC,
        LoEnglish = MM_LOENGLISH,
        HiEnglish = MM_HIENGLISH,
        TwIps = MM_TWIPS,
        IsoTropic = MM_ISOTROPIC,
        AnIsoTropic = MM_ANISOTROPIC,
    };

    inline MappingMode operator|(MappingMode a, MappingMode b) {
        return static_cast<MappingMode>(static_cast<int32_t>(a) |
                                        static_cast<int32_t>(b));
    }
#endif
    class meta {
    public:
        meta(const meta &other) = delete;

        meta(meta &&other) = delete;

        meta &operator=(const meta &other) = delete;

        meta &operator=(meta &&other) = delete;

        meta() = default;

        ~meta() = default;

        static HDC create_enhance_file(HDC dc_handle,
                                       const char *file_name,
                                       const RECT *rect,
                                       const char *description = nullptr);

        static HDC create_enhance_file(HDC dc_handle,
                                       const wchar_t *file_name,
                                       const RECT *rect,
                                       const wchar_t *description = nullptr);

        static HENHMETAFILE close_enhance_file(HDC dc_handle);

        static bool destroy_enhance_file(HENHMETAFILE enh_meta_file_handle);

        static bool enum_enhance_file(HDC dc_handle,
                                      HENHMETAFILE enh_meta_file_handle,
                                      ENHMFENUMPROC enh_meta_file_proc,
                                      void *param = nullptr,
                                      const RECT *rect = nullptr);

        static HENHMETAFILE copy_enhance_file(HENHMETAFILE enh_meta_file_handle,
                                              const char *file_name);

        static HENHMETAFILE copy_enhance_file(HENHMETAFILE enh_meta_file_handle,
                                              const wchar_t *file_name);

        static bool play_enhance_file(HDC dc_handle,
                                      HENHMETAFILE enh_meta_file_handle,
                                      const RECT *rect);

        static bool
        play_enhance_file_record(HDC dc_handle,
                                 std::vector<HANDLETABLE> &handles,
                                 const ENHMETARECORD *enh_meta_record);

        static HENHMETAFILE get_enhance_file(const char *file_name);

        static HENHMETAFILE get_enhance_file(const wchar_t *file_name);

        static uint32_t
        get_enhance_file_header(HENHMETAFILE enh_meta_file_handle,
                                ENHMETAHEADER *buf,
                                uint32_t size);

        static uint32_t
        get_enhance_file_description(HENHMETAFILE enh_meta_file_handle,
                                     std::string &description);

        static uint32_t
        get_enhance_file_description(HENHMETAFILE enh_meta_file_handle,
                                     std::wstring &description);

        static uint32_t get_enhance_file_palette_entries(
                HENHMETAFILE enh_meta_file_handle,
                std::vector<PALETTEENTRY> &palette_entry);


        static uint32_t
        get_window_file_bits(HENHMETAFILE enh_meta_file_handle,
                             uint8_t *buf,
                             uint32_t size,
                             MappingMode mode = MappingMode::AnIsoTropic,
                             HDC dc_handle = nullptr);

        static HENHMETAFILE
        set_window_file_bits(const uint8_t *buf,
                             uint32_t size,
                             HDC dc_handle = nullptr,
                             const METAFILEPICT *meta_file_pict = nullptr);

        static uint32_t get_enhance_file_bits(HENHMETAFILE enh_meta_file_handle,
                                              uint8_t *buf,
                                              uint32_t size);

        static HENHMETAFILE set_enhance_file_bits(const uint8_t *buf,
                                                  uint32_t size);

        static bool
        gdi_comment(HDC dc_handle, const uint8_t *buf, uint32_t size);
    };
} // namespace YanLib::ui::gdi
#endif // META_H
