//
// Created by forkernel on 2025/5/5.
//

#include "scroll.h"
#include "helper/convert.h"

namespace YanLib::ui {
bool scroll::enable(HWND hwnd, ScrollType scroll_type, ArrowType arrow_type) {
    if (!EnableScrollBar(hwnd, static_cast<uint32_t>(scroll_type),
            static_cast<uint32_t>(arrow_type))) {
        error_code = GetLastError();
        return false;
    }
    return true;
}

bool scroll::show(HWND hwnd, ScrollType scroll_type) {
    if (!ShowScrollBar(hwnd, static_cast<uint32_t>(scroll_type), TRUE)) {
        error_code = GetLastError();
        return false;
    }
    return true;
}

bool scroll::hide(HWND hwnd, ScrollType scroll_type) {
    if (!ShowScrollBar(hwnd, static_cast<uint32_t>(scroll_type), FALSE)) {
        error_code = GetLastError();
        return false;
    }
    return true;
}

bool scroll::get_info(HWND hwnd,
    SCROLLBARINFO         *scroll_bar_info,
    ObjectID               object_id) {
    if (!GetScrollBarInfo(
            hwnd, static_cast<int32_t>(object_id), scroll_bar_info)) {
        error_code = GetLastError();
        return false;
    }
    return true;
}

bool scroll::get_info(HWND hwnd,
    SCROLLINFO            *scroll_info,
    ScrollType             scroll_type) {
    if (!GetScrollInfo(hwnd, static_cast<uint32_t>(scroll_type), scroll_info)) {
        error_code = GetLastError();
        return false;
    }
    return true;
}

int32_t scroll::set_info(HWND hwnd,
    SCROLLINFO               *scroll_info,
    ScrollType                scroll_type,
    bool                      is_redraw) {
    return SetScrollInfo(hwnd, static_cast<uint32_t>(scroll_type), scroll_info,
        is_redraw ? TRUE : FALSE);
}

int32_t scroll::get_pos(HWND hwnd, ScrollType scroll_type) {
    int32_t result = GetScrollPos(hwnd, static_cast<uint32_t>(scroll_type));
    if (!result) {
        error_code = GetLastError();
    }
    return result;
}

int32_t scroll::set_pos(HWND hwnd,
    int32_t                  pos,
    ScrollType               scroll_type,
    bool                     is_redraw) {
    int32_t result = SetScrollPos(hwnd, static_cast<uint32_t>(scroll_type), pos,
        is_redraw ? TRUE : FALSE);
    if (!result) {
        error_code = GetLastError();
    }
    return result;
}

bool scroll::get_range(HWND hwnd,
    int32_t                *min_pos,
    int32_t                *max_pos,
    ScrollType              scroll_type) {
    if (!GetScrollRange(
            hwnd, static_cast<uint32_t>(scroll_type), min_pos, max_pos)) {
        error_code = GetLastError();
        return false;
    }
    return true;
}

bool scroll::set_range(HWND hwnd,
    int32_t                 min_pos,
    int32_t                 max_pos,
    ScrollType              scroll_type,
    bool                    is_redraw) {
    if (!SetScrollRange(hwnd, static_cast<uint32_t>(scroll_type), min_pos,
            max_pos, is_redraw ? TRUE : FALSE)) {
        error_code = GetLastError();
        return false;
    }
    return true;
}

bool scroll::scroll_window(HWND hwnd,
    int32_t                     x_amount,
    int32_t                     y_amount,
    const RECT                 *rect,
    const RECT                 *clip_rect) {
    if (!ScrollWindow(hwnd, x_amount, y_amount, rect, clip_rect)) {
        error_code = GetLastError();
        return false;
    }
    return true;
}

int32_t scroll::scroll_window_extend(HWND hwnd,
    int32_t                               dx,
    int32_t                               dy,
    const RECT                           *rect_scroll,
    const RECT                           *rect_clip,
    HRGN                                  region_handle_update,
    RECT                                 *rect_update,
    ScrollFlag                            flag) {
    int32_t result = ScrollWindowEx(hwnd, dx, dy, rect_scroll, rect_clip,
        region_handle_update, rect_update, static_cast<uint32_t>(flag));
    if (!result) {
        error_code = GetLastError();
    }
    return result;
}

uint32_t scroll::err_code() const {
    return error_code;
}

std::string scroll::err_string() const {
    std::string result = helper::convert::err_string(error_code);
    return result;
}

std::wstring scroll::err_wstring() const {
    std::wstring result = helper::convert::err_wstring(error_code);
    return result;
}
} // namespace YanLib::ui
