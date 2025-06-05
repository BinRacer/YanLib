//
// Created by forkernel on 2025/5/18.
//

#include "window_pos.h"
#include "helper/convert.h"

namespace YanLib::ui::core {
    HDWP window_pos::prepare(int32_t window_num) {
        HDWP result = BeginDeferWindowPos(window_num);
        if (!result) {
            error_code = GetLastError();
        }
        return result;
    }

    HDWP window_pos::add(HDWP window_pos_handle,
                         HWND window_handle,
                         HWND insert_after_window_handle,
                         int32_t x,
                         int32_t y,
                         int32_t width,
                         int32_t height,
                         PosFlag flag) {
        HDWP result = DeferWindowPos(window_pos_handle, window_handle,
                                     insert_after_window_handle, x, y, width,
                                     height, static_cast<uint32_t>(flag));
        if (!result) {
            error_code = GetLastError();
        }
        return result;
    }

    bool window_pos::apply(HDWP window_pos_handle) {
        if (!EndDeferWindowPos(window_pos_handle)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    uint32_t window_pos::err_code() const {
        return error_code;
    }

    std::string window_pos::err_string() const {
        std::string result = helper::convert::err_string(error_code);
        return result;
    }

    std::wstring window_pos::err_wstring() const {
        std::wstring result = helper::convert::err_wstring(error_code);
        return result;
    }
} // namespace YanLib::ui::core
