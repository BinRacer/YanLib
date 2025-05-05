//
// Created by forkernel on 2025/5/4.
//

#ifndef PALETTE_H
#define PALETTE_H
#include <Windows.h>
#include <stdint.h>

namespace YanLib::ui::gdi {
    class palette {
    public:
        palette(const palette &other) = delete;

        palette(palette &&other) = delete;

        palette &operator=(const palette &other) = delete;

        palette &operator=(palette &&other) = delete;

        palette() = default;

        ~palette() = default;

        static HPALETTE create_palette(const LOGPALETTE *log_palette);

        static HPALETTE create_halftone_palette(HDC dc_handle);

        static bool get_color_adjustment(HDC dc_handle,
                                         COLORADJUSTMENT *color_adjustment);

        static bool set_color_adjustment(HDC dc_handle,
                                         const COLORADJUSTMENT *color_adjustment);

        static COLORREF get_nearest_color(HDC dc_handle, COLORREF color);

        static uint32_t get_nearest_palette_index(HPALETTE palette_handle,
                                                  COLORREF color);

        static uint32_t get_palette_entries(HPALETTE palette_handle,
                                            uint32_t start,
                                            uint32_t entry_count,
                                            PALETTEENTRY *palette_entry);

        static uint32_t set_palette_entries(HPALETTE palette_handle,
                                            uint32_t start,
                                            uint32_t entry_count,
                                            const PALETTEENTRY *palette_entry);

        static uint32_t get_system_palette_entries(HDC dc_handle,
                                                   uint32_t start,
                                                   uint32_t entry_count,
                                                   PALETTEENTRY *palette_entry);

        static uint32_t get_system_palette_use(HDC dc_handle);

        static uint32_t set_system_palette_use(HDC dc_handle, uint32_t use);

        static HPALETTE select_palette(HDC dc_handle,
                                       HPALETTE palette_handle,
                                       bool force_background);

        static bool unrealize_object(HGDIOBJ gdi_obj_handle);

        static bool update_colors(HDC dc_handle);

        static bool animate_palette(HPALETTE palette_handle,
                                    uint32_t start,
                                    uint32_t entry_count,
                                    const PALETTEENTRY *palette_entry);

        static uint32_t realize_palette(HDC dc_handle);

        static bool resize_palette(HPALETTE palette_handle, uint32_t num);
    };
}
#endif //PALETTE_H
