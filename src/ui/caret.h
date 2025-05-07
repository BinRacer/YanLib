//
// Created by forkernel on 2025/4/30.
//

#ifndef CARET_H
#define CARET_H
#include <Windows.h>
#include <string>

namespace YanLib::ui {
class caret {
private:
    HWND          window_handle = nullptr;
    volatile bool is_create     = false;
    uint32_t      error_code    = 0;

public:
    caret(const caret &other)            = delete;

    caret(caret &&other)                 = delete;

    caret &operator=(const caret &other) = delete;

    caret &operator=(caret &&other)      = delete;

    caret()                              = delete;

    ~caret();

    explicit caret(HWND hwnd,
        HBITMAP         bitmap_handle,
        int32_t         width,
        int32_t         height);

    [[nodiscard]] bool is_ok() const;

    uint32_t get_blink_time();

    bool set_blink_time(uint32_t milli_second);

    bool get_pos(POINT *point);

    bool set_pos(int32_t x, int32_t y);

    bool show();

    bool hide();

    [[nodiscard]] uint32_t err_code() const;

    [[nodiscard]] std::string err_string() const;

    [[nodiscard]] std::wstring err_wstring() const;
};
} // namespace YanLib::ui
#endif // CARET_H
