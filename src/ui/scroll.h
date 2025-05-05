//
// Created by forkernel on 2025/5/5.
//

#ifndef SCROLL_H
#define SCROLL_H
#include <Windows.h>
#include <string>

namespace YanLib::ui {
    class scroll {
    private:
        unsigned long error_code = 0;

    public:
        scroll(const scroll &other) = delete;

        scroll(scroll &&other) = delete;

        scroll &operator=(const scroll &other) = delete;

        scroll &operator=(scroll &&other) = delete;

        scroll() = default;

        ~scroll() = default;

        bool enable_scroll_bar(HWND hwnd, unsigned int scroll_type, unsigned int arrow_type);

        bool show_scroll_bar(HWND hwnd, int scroll_type);

        bool hide_scroll_bar(HWND hwnd, int scroll_type);

        bool get_scroll_bar_info(HWND hwnd,
                                 long object_id,
                                 SCROLLBARINFO *scroll_bar_info);

        bool get_scroll_info(HWND hwnd, int scroll_type, SCROLLINFO *scroll_info);

        int set_scroll_info(HWND hwnd,
                            int scroll_type,
                            SCROLLINFO *scroll_info,
                            bool is_redraw);

        int get_scroll_pos(HWND hwnd, int scroll_info);

        int set_scroll_pos(HWND hwnd,
                           int scroll_type,
                           int pos,
                           bool is_redraw);

        bool get_scroll_range(HWND hwnd,
                              int scroll_type,
                              int *min_pos,
                              int *max_pos);

        bool set_scroll_range(HWND hwnd,
                              int scroll_type,
                              int min_pos,
                              int max_pos,
                              bool is_redraw);

        [[nodiscard]] unsigned long err_code() const;

        [[nodiscard]] std::string err_string() const;

        [[nodiscard]] std::wstring err_wstring() const;
    };
}
#endif //SCROLL_H
