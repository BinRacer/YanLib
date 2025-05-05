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

        bool enable_scroll_bar(HWND hwnd, uint32_t scroll_type, uint32_t arrow_type);

        bool show_scroll_bar(HWND hwnd, int32_t scroll_type);

        bool hide_scroll_bar(HWND hwnd, int32_t scroll_type);

        bool get_scroll_bar_info(HWND hwnd,
                                 long object_id,
                                 SCROLLBARINFO *scroll_bar_info);

        bool get_scroll_info(HWND hwnd, int32_t scroll_type, SCROLLINFO *scroll_info);

        int32_t set_scroll_info(HWND hwnd,
                            int32_t scroll_type,
                            SCROLLINFO *scroll_info,
                            bool is_redraw);

        int32_t get_scroll_pos(HWND hwnd, int32_t scroll_info);

        int32_t set_scroll_pos(HWND hwnd,
                           int32_t scroll_type,
                           int32_t pos,
                           bool is_redraw);

        bool get_scroll_range(HWND hwnd,
                              int32_t scroll_type,
                              int32_t *min_pos,
                              int32_t *max_pos);

        bool set_scroll_range(HWND hwnd,
                              int32_t scroll_type,
                              int32_t min_pos,
                              int32_t max_pos,
                              bool is_redraw);

        [[nodiscard]] unsigned long err_code() const;

        [[nodiscard]] std::string err_string() const;

        [[nodiscard]] std::wstring err_wstring() const;
    };
}
#endif //SCROLL_H
