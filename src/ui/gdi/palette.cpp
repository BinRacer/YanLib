//
// Created by BinRacer <native.lab@outlook.com> on 2025/5/4.
//

#include "palette.h"

namespace YanLib::ui::gdi {
    HPALETTE palette::create(const LOGPALETTE *log_palette) {
        return CreatePalette(log_palette);
    }

    HPALETTE palette::create_halftone(HDC dc_handle) {
        return CreateHalftonePalette(dc_handle);
    }

    bool palette::destroy(HPALETTE palette_handle) {
        return DeleteObject(palette_handle);
    }

    bool palette::get_color_adjustment(HDC dc_handle,
                                       COLORADJUSTMENT *color_adjustment) {
        return GetColorAdjustment(dc_handle, color_adjustment);
    }

    bool
    palette::set_color_adjustment(HDC dc_handle,
                                  const COLORADJUSTMENT *color_adjustment) {
        return SetColorAdjustment(dc_handle, color_adjustment);
    }

    COLORREF palette::get_nearest_color(HDC dc_handle, COLORREF color) {
        return GetNearestColor(dc_handle, color);
    }

    uint32_t palette::get_nearest_index(HPALETTE palette_handle,
                                        COLORREF color) {
        return GetNearestPaletteIndex(palette_handle, color);
    }

    uint32_t palette::get_entries(HPALETTE palette_handle,
                                  uint32_t index,
                                  std::vector<PALETTEENTRY> &palette_entry) {
        return GetPaletteEntries(palette_handle, index, palette_entry.size(),
                                 palette_entry.data());
    }

    uint32_t
    palette::set_entries(HPALETTE palette_handle,
                         uint32_t index,
                         const std::vector<PALETTEENTRY> &palette_entry) {
        return SetPaletteEntries(palette_handle, index, palette_entry.size(),
                                 palette_entry.data());
    }

    uint32_t
    palette::get_system_entries(HDC dc_handle,
                                uint32_t index,
                                std::vector<PALETTEENTRY> &palette_entry) {
        return GetSystemPaletteEntries(dc_handle, index, palette_entry.size(),
                                       palette_entry.data());
    }

    PaletteState palette::get_system_state(HDC dc_handle) {
        return static_cast<PaletteState>(GetSystemPaletteUse(dc_handle));
    }

    PaletteState palette::set_system_state(HDC dc_handle, PaletteState state) {
        return static_cast<PaletteState>(
                SetSystemPaletteUse(dc_handle, static_cast<uint32_t>(state)));
    }

    HPALETTE palette::select(HDC dc_handle,
                             HPALETTE palette_handle,
                             bool force_background) {
        return SelectPalette(dc_handle, palette_handle,
                             force_background ? TRUE : FALSE);
    }

    bool palette::unrealize_object(HGDIOBJ gdi_obj_handle) {
        return UnrealizeObject(gdi_obj_handle);
    }

    bool palette::update_colors(HDC dc_handle) {
        return UpdateColors(dc_handle);
    }

    bool palette::animate(HPALETTE palette_handle,
                          uint32_t index,
                          const std::vector<PALETTEENTRY> &palette_entry) {
        return AnimatePalette(palette_handle, index, palette_entry.size(),
                              palette_entry.data());
    }

    uint32_t palette::realize(HDC dc_handle) {
        return RealizePalette(dc_handle);
    }

    bool palette::resize(HPALETTE palette_handle, uint32_t palette_num) {
        return ResizePalette(palette_handle, palette_num);
    }
} // namespace YanLib::ui::gdi
