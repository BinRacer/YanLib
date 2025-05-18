//
// Created by forkernel on 2025/5/18.
//

#ifndef WINDOW_POS_H
#define WINDOW_POS_H
#include <Windows.h>
#include <string>

namespace YanLib::ui {
class window_pos {
private:
    uint32_t error_code = 0;

public:
    window_pos(const window_pos &other)            = delete;

    window_pos(window_pos &&other)                 = delete;

    window_pos &operator=(const window_pos &other) = delete;

    window_pos &operator=(window_pos &&other)      = delete;

    window_pos()                                   = default;

    ~window_pos()                                  = default;

    HDWP prepare(int32_t window_num);

    HDWP add(HDWP window_pos_handle,
        HWND      window_handle,
        HWND      insert_after_window_handle,
        int32_t   x,
        int32_t   y,
        int32_t   cx,
        int32_t   cy,
        uint32_t  flag);

    bool apply(HDWP window_pos_handle);

    [[nodiscard]] uint32_t err_code() const;

    [[nodiscard]] std::string err_string() const;

    [[nodiscard]] std::wstring err_wstring() const;
};
} // namespace YanLib::ui
#endif // WINDOW_POS_H
