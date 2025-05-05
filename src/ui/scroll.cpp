//
// Created by forkernel on 2025/5/5.
//

#include "scroll.h"
#include "helper/convert.h"

namespace YanLib::ui {
    bool scroll::enable_scroll_bar(HWND hwnd, uint32_t scroll_type, uint32_t arrow_type) {
        if (!EnableScrollBar(hwnd, scroll_type, arrow_type)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool scroll::show_scroll_bar(HWND hwnd, int32_t scroll_type) {
        if (!ShowScrollBar(hwnd, scroll_type, TRUE)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool scroll::hide_scroll_bar(HWND hwnd, int32_t scroll_type) {
        if (!ShowScrollBar(hwnd, scroll_type, FALSE)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool scroll::get_scroll_bar_info(HWND hwnd,
                                     long object_id,
                                     SCROLLBARINFO *scroll_bar_info) {
        if (!GetScrollBarInfo(hwnd, object_id, scroll_bar_info)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool scroll::get_scroll_info(HWND hwnd,
                                 int32_t scroll_type,
                                 SCROLLINFO *scroll_info) {
        if (!GetScrollInfo(hwnd, scroll_type, scroll_info)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    int32_t scroll::set_scroll_info(HWND hwnd,
                                int32_t scroll_type,
                                SCROLLINFO *scroll_info,
                                bool is_redraw) {
        return SetScrollInfo(hwnd,
                             scroll_type,
                             scroll_info,
                             is_redraw ? TRUE : FALSE);
    }

    int32_t scroll::get_scroll_pos(HWND hwnd, int32_t scroll_info) {
        int32_t result = GetScrollPos(hwnd, scroll_info);
        if (!result) {
            error_code = GetLastError();
        }
        return result;
    }

    int32_t scroll::set_scroll_pos(HWND hwnd,
                               int32_t scroll_type,
                               int32_t pos,
                               bool is_redraw) {
        int32_t result = SetScrollPos(hwnd,
                                  scroll_type,
                                  pos,
                                  is_redraw ? TRUE : FALSE);
        if (!result) {
            error_code = GetLastError();
        }
        return result;
    }

    bool scroll::get_scroll_range(HWND hwnd,
                                  int32_t scroll_type,
                                  int32_t *min_pos,
                                  int32_t *max_pos) {
        if (!GetScrollRange(hwnd, scroll_type, min_pos, max_pos)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool scroll::set_scroll_range(HWND hwnd,
                                  int32_t scroll_type,
                                  int32_t min_pos,
                                  int32_t max_pos,
                                  bool is_redraw) {
        if (!SetScrollRange(hwnd,
                            scroll_type,
                            min_pos,
                            max_pos,
                            is_redraw ? TRUE : FALSE)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    unsigned long scroll::err_code() const {
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
}
