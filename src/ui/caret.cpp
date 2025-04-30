//
// Created by forkernel on 2025/4/30.
//

#include "caret.h"
#include "helper/convert.h"

namespace YanLib::ui {
    bool caret::create_caret(HWND hwnd,
                             HBITMAP bitmap_handle,
                             int width,
                             int height) {
        if (!CreateCaret(hwnd, bitmap_handle, width, height)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    UINT caret::get_caret_blink_time() {
        UINT result = GetCaretBlinkTime();
        if (!result) {
            error_code = GetLastError();
        }
        return result;
    }

    bool caret::set_caret_blink_time(UINT milli_second) {
        if (!SetCaretBlinkTime(milli_second)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool caret::get_caret_pos(LPPOINT point) {
        if (!GetCaretPos(point)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool caret::set_caret_pos(int x, int y) {
        if (!SetCaretPos(x, y)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool caret::show_caret(HWND hwnd) {
        if (!ShowCaret(hwnd)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool caret::hide_caret(HWND hwnd) {
        if (!HideCaret(hwnd)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool caret::destroy_caret() {
        if (!DestroyCaret()) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    DWORD caret::err_code() const {
        return error_code;
    }

    std::string caret::err_string() const {
        std::string result = helper::convert::err_string(error_code);
        return result;
    }

    std::wstring caret::err_wstring() const {
        std::wstring result = helper::convert::err_wstring(error_code);
        return result;
    }
}
