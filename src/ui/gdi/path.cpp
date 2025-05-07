//
// Created by forkernel on 2025/5/4.
//

#include "path.h"

namespace YanLib::ui::gdi {
bool path::begin_path(HDC dc_handle) {
    return BeginPath(dc_handle);
}

bool path::end_path(HDC dc_handle) {
    return EndPath(dc_handle);
}

int32_t path::get_path(HDC dc_handle,
    std::vector<POINT>    &point,
    std::vector<uint8_t>  &point_type) {
    if (point.size() != point_type.size()) {
        return 0;
    }
    return GetPath(dc_handle, point.data(), point_type.data(),
        static_cast<int>(point.size()));
}

bool path::fill_path(HDC dc_handle) {
    return FillPath(dc_handle);
}

bool path::abort_path(HDC dc_handle) {
    return AbortPath(dc_handle);
}

bool path::flatten_path(HDC dc_handle) {
    return FlattenPath(dc_handle);
}

bool path::stroke_and_fill_path(HDC dc_handle) {
    return StrokeAndFillPath(dc_handle);
}

bool path::stroke_path(HDC dc_handle) {
    return StrokePath(dc_handle);
}

bool path::widen_path(HDC dc_handle) {
    return WidenPath(dc_handle);
}

HRGN path::path_to_region(HDC dc_handle) {
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
