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
        DWORD error_code = 0;

    public:
        caret(const caret &other) = delete;

        caret(caret &&other) = delete;

        caret &operator=(const caret &other) = delete;

        caret &operator=(caret &&other) = delete;

        caret() = default;

        ~caret() = default;

        bool create_caret(HWND hwnd, HBITMAP bitmap_handle, int width, int height);

        UINT get_caret_blink_time();

        bool set_caret_blink_time(UINT milli_second);

        bool get_caret_pos(LPPOINT point);

        bool set_caret_pos(int x, int y);

        bool show_caret(HWND hwnd);

        bool hide_caret(HWND hwnd);

        bool destroy_caret();

        [[nodiscard]] DWORD err_code() const;

        [[nodiscard]] std::string err_string() const;

        [[nodiscard]] std::wstring err_wstring() const;
    };
}
#endif //CARET_H
