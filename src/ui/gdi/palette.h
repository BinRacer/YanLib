//
// Created by BinRacer <native.lab@outlook.com> on 2025/5/4.
//

#ifndef PALETTE_H
#define PALETTE_H
#include <Windows.h>
#include <cstdint>
#include <memory>
#include <vector>

namespace YanLib::ui::gdi {
#ifndef PALETTEENTRYFLAG
#define PALETTEENTRYFLAG

    enum class PaletteEntryFlag : uint8_t {
        None = 0,
        Reserved = PC_RESERVED,
        Explicit = PC_EXPLICIT,
        NoCollapse = PC_NOCOLLAPSE,
    };

    inline PaletteEntryFlag operator|(PaletteEntryFlag a, PaletteEntryFlag b) {
        return static_cast<PaletteEntryFlag>(static_cast<uint8_t>(a) |
                                             static_cast<uint8_t>(b));
    }
#endif
#ifndef PALETTESTATE
#define PALETTESTATE

    enum class PaletteState : uint32_t {
        Error = SYSPAL_ERROR,
        Static = SYSPAL_STATIC,
        NoStatic = SYSPAL_NOSTATIC,
        NoStatic256 = SYSPAL_NOSTATIC256,
    };
#endif
    class palette {
    public:
        palette(const palette &other) = delete;

        palette(palette &&other) = delete;

        palette &operator=(const palette &other) = delete;

        palette &operator=(palette &&other) = delete;

        palette() = default;

        ~palette() = default;

        static HPALETTE create(const LOGPALETTE *log_palette);

        static HPALETTE create_halftone(HDC dc_handle);

        static bool destroy(HPALETTE palette_handle);

        static bool get_color_adjustment(HDC dc_handle,
                                         COLORADJUSTMENT *color_adjustment);

        static bool
        set_color_adjustment(HDC dc_handle,
                             const COLORADJUSTMENT *color_adjustment);

        static COLORREF get_nearest_color(HDC dc_handle, COLORREF color);

        static uint32_t get_nearest_index(HPALETTE palette_handle,
                                          COLORREF color);

        static uint32_t get_entries(HPALETTE palette_handle,
                                    uint32_t index,
                                    std::vector<PALETTEENTRY> &palette_entry);

        static uint32_t
        set_entries(HPALETTE palette_handle,
                    uint32_t index,
                    const std::vector<PALETTEENTRY> &palette_entry);

        static uint32_t
        get_system_entries(HDC dc_handle,
                           uint32_t index,
                           std::vector<PALETTEENTRY> &palette_entry);


        static PaletteState get_system_state(HDC dc_handle);

        static PaletteState set_system_state(HDC dc_handle, PaletteState state);

        static HPALETTE select(HDC dc_handle,
                               HPALETTE palette_handle,
                               bool force_background = true);

        static bool unrealize_object(HGDIOBJ gdi_obj_handle);

        static bool update_colors(HDC dc_handle);

        static bool animate(HPALETTE palette_handle,
                            uint32_t index,
                            const std::vector<PALETTEENTRY> &palette_entry);

        static uint32_t realize(HDC dc_handle);

        static bool resize(HPALETTE palette_handle, uint32_t palette_num);
    };
} // namespace YanLib::ui::gdi
#endif // PALETTE_H
