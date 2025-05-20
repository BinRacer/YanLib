//
// Created by forkernel on 2025/5/4.
//

#include "path.h"

namespace YanLib::ui::gdi {
    bool path::begin(HDC dc_handle) {
        return BeginPath(dc_handle);
    }

    bool path::end(HDC dc_handle) {
        return EndPath(dc_handle);
    }

    int32_t path::get(HDC dc_handle,
                      std::vector<POINT> &point,
                      std::vector<PointType> &point_type) {
        if (point.size() != point_type.size()) {
            return 0;
        }
        return GetPath(dc_handle, point.data(),
                       reinterpret_cast<uint8_t *>(point_type.data()),
                       static_cast<int32_t>(point.size()));
    }

    bool path::fill(HDC dc_handle) {
        return FillPath(dc_handle);
    }

    bool path::abort(HDC dc_handle) {
        return AbortPath(dc_handle);
    }

    bool path::flatten(HDC dc_handle) {
        return FlattenPath(dc_handle);
    }

    bool path::stroke_and_fill(HDC dc_handle) {
        return StrokeAndFillPath(dc_handle);
    }

    bool path::stroke(HDC dc_handle) {
        return StrokePath(dc_handle);
    }

    bool path::widen(HDC dc_handle) {
        return WidenPath(dc_handle);
    }

    HRGN path::get_region(HDC dc_handle) {
        return PathToRegion(dc_handle);
    }

    bool path::close_figure(HDC dc_handle) {
        return CloseFigure(dc_handle);
    }

    bool path::get_miter_limit(HDC dc_handle, FLOAT *limit) {
        return GetMiterLimit(dc_handle, limit);
    }

    bool path::set_miter_limit(HDC dc_handle, FLOAT limit, FLOAT *old) {
        return SetMiterLimit(dc_handle, limit, old);
    }
} // namespace YanLib::ui::gdi
