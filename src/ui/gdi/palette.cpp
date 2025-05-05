//
// Created by forkernel on 2025/5/4.
//

#include "palette.h"

namespace YanLib::ui::gdi {
    HPALETTE palette::create_palette(const LOGPALETTE *log_palette) {
        return CreatePalette(log_palette);
    }

    HPALETTE palette::create_halftone_palette(HDC dc_handle) {
        return CreateHalftonePalette(dc_handle);
    }

    bool palette::get_color_adjustment(HDC dc_handle,
                                       COLORADJUSTMENT *color_adjustment) {
        return GetColorAdjustment(dc_handle, color_adjustment);
    }

    bool palette::set_color_adjustment(HDC dc_handle,
                                       const COLORADJUSTMENT *color_adjustment) {
        return SetColorAdjustment(dc_handle, color_adjustment);
    }

    COLORREF palette::get_nearest_color(HDC dc_handle, COLORREF color) {
        return GetNearestColor(dc_handle, color);
    }

    uint32_t palette::get_nearest_palette_index(HPALETTE palette_handle,
                                                    COLORREF color) {
        return GetNearestPaletteIndex(palette_handle, color);
    }

    uint32_t palette::get_palette_entries(HPALETTE palette_handle,
                                              uint32_t start,
                                              uint32_t entry_count,
                                              PALETTEENTRY *palette_entry) {
        return GetPaletteEntries(palette_handle,
                                 start,
                                 entry_count,
                                 palette_entry);
    }

    uint32_t palette::set_palette_entries(HPALETTE palette_handle,
                                              uint32_t start,
                                              uint32_t entry_count,
                                              const PALETTEENTRY *palette_entry) {
        return SetPaletteEntries(palette_handle,
                                 start,
                                 entry_count,
                                 palette_entry);
    }

    uint32_t palette::get_system_palette_entries(HDC dc_handle,
                                                     uint32_t start,
                                                     uint32_t entry_count,
                                                     PALETTEENTRY *palette_entry) {
        return GetSystemPaletteEntries(dc_handle,
                                       start,
                                       entry_count,
                                       palette_entry);
    }

    uint32_t palette::get_system_palette_use(HDC dc_handle) {
        return GetSystemPaletteUse(dc_handle);
    }

    uint32_t palette::set_system_palette_use(HDC dc_handle, uint32_t use) {
        return SetSystemPaletteUse(dc_handle, use);
    }

    HPALETTE palette::select_palette(HDC dc_handle,
                                     HPALETTE palette_handle,
                                     bool force_background) {
        return SelectPalette(dc_handle,
                             palette_handle,
                             force_background ? TRUE : FALSE);
    }

    bool palette::unrealize_object(HGDIOBJ gdi_obj_handle) {
        return UnrealizeObject(gdi_obj_handle);
    }

    bool palette::update_colors(HDC dc_handle) {
        return UpdateColors(dc_handle);
    }

    bool palette::animate_palette(HPALETTE palette_handle,
                                  uint32_t start,
                                  uint32_t entry_count,
                                  const PALETTEENTRY *palette_entry) {
        return AnimatePalette(palette_handle,
                              start,
                              entry_count,
                              palette_entry);
    }

    uint32_t palette::realize_palette(HDC dc_handle) {
        return RealizePalette(dc_handle);
    }

    bool palette::resize_palette(HPALETTE palette_handle, uint32_t num) {
        return ResizePalette(palette_handle, num);
    }
}
