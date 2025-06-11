//
// Created by BinRacer <native.lab@outlook.com> on 2025/5/4.
//

#include "pen.h"

namespace YanLib::ui::gdi {
    HPEN pen::create(COLORREF color, int32_t width, PenStyle style) {
        return CreatePen(static_cast<int32_t>(style), width, color);
    }

    HPEN pen::create(const LOGPEN *log_pen) {
        return CreatePenIndirect(log_pen);
    }

    LOGPEN pen::make(COLORREF color, POINT width, PenStyle style) {
        LOGPEN result = {};
        result.lopnColor = color;
        result.lopnWidth = width;
        result.lopnStyle = static_cast<uint32_t>(style);
        return result;
    }

    HPEN pen::create(uint32_t width,
                     const LOGBRUSH *log_brush,
                     std::vector<uint32_t> &len,
                     PenStyle style) {
        return ExtCreatePen(static_cast<uint32_t>(style), width, log_brush,
                            len.size(),
                            len.empty() ? nullptr
                                        : reinterpret_cast<unsigned long *>(
                                                  len.data()));
    }

    HPEN pen::create_safe(uint32_t width,
                          const LOGBRUSH *log_brush,
                          std::vector<uint32_t> &len,
                          PenStyle style) {
        std::vector<unsigned long> temp(len.size());
        for (const auto &item : len) {
            temp.push_back(item);
        }
        HPEN result =
                ExtCreatePen(static_cast<uint32_t>(style), width, log_brush,
                             len.size(), temp.empty() ? nullptr : temp.data());
        for (const auto &item : temp) {
            len.push_back(item);
        }
        return result;
    }

    bool pen::destroy(HPEN pen_handle) {
        return DeleteObject(pen_handle);
    }

    COLORREF pen::set_dc_color(HDC dc_handle, COLORREF color) {
        return SetDCPenColor(dc_handle, color);
    }
} // namespace YanLib::ui::gdi
