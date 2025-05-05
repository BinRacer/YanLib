//
// Created by forkernel on 2025/5/4.
//

#ifndef PALETTE_H
#define PALETTE_H
#include <Windows.h>

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

        static unsigned int get_nearest_palette_index(HPALETTE palette_handle,
                                                      COLORREF color);

        static unsigned int get_palette_entries(HPALETTE palette_handle,
                                                unsigned int start,
                                                unsigned int entry_count,
                                                PALETTEENTRY *palette_entry);

        static unsigned int set_palette_entries(HPALETTE palette_handle,
                                                unsigned int start,
                                                unsigned int entry_count,
                                                const PALETTEENTRY *palette_entry);

        static unsigned int get_system_palette_entries(HDC dc_handle,
                                                       unsigned int start,
                                                       unsigned int entry_count,
                                                       PALETTEENTRY *palette_entry);

        static unsigned int get_system_palette_use(HDC dc_handle);

        static unsigned int set_system_palette_use(HDC dc_handle, unsigned int use);

        static HPALETTE select_palette(HDC dc_handle,
                                       HPALETTE palette_handle,
                                       bool force_background);

        static bool unrealize_object(HGDIOBJ gdi_obj_handle);

        static bool update_colors(HDC dc_handle);

        static bool animate_palette(HPALETTE palette_handle,
                                    unsigned int start,
                                    unsigned int entry_count,
                                    const PALETTEENTRY *palette_entry);

        static unsigned int realize_palette(HDC dc_handle);

        static bool resize_palette(HPALETTE palette_handle, unsigned int num);
    };
}
#endif //PALETTE_H
