/* clang-format off */
/*
 * @file palette.h
 * @date 2025-05-04
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
#ifndef PALETTE_H
#define PALETTE_H
#include <Windows.h>
#include <wingdi.h>
#include <windef.h>
#include <cstdint>
#include <memory>
#include <vector>
#include "gdi.h"
namespace YanLib::ui::gdi {
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
