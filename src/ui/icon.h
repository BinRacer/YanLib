//
// Created by forkernel on 2025/4/30.
//

#ifndef ICON_H
#define ICON_H
#include <Windows.h>
#include <string>

namespace YanLib::ui {
    class icon {
    private:
        unsigned long error_code = 0;

    public:
        icon(const icon &other) = delete;

        icon(icon &&other) = delete;

        icon &operator=(const icon &other) = delete;

        icon &operator=(icon &&other) = delete;

        icon() = default;

        ~icon() = default;

        HICON create_icon(HINSTANCE instance_handle,
                          int32_t width,
                          int32_t height,
                          uint8_t planes,
                          uint8_t bits_pixel,
                          const uint8_t *and_bits,
                          const uint8_t *xor_bits);

        HICON create_icon_from_resource(uint8_t *res_buf,
                                        unsigned long res_size,
                                        bool is_icon,
                                        unsigned long version);

        HICON create_icon_from_resource(uint8_t *res_buf,
                                        unsigned long res_size,
                                        bool is_icon,
                                        unsigned long version,
                                        int32_t desired_width,
                                        int32_t desired_height,
                                        uint32_t flag);

        HICON create_icon_indirect(ICONINFO *icon_info);

        HICON load_icon(HINSTANCE instance_handle, const wchar_t *icon_name);

        HICON copy_icon(HICON icon_handle);

        bool draw_icon(HDC dc_handle, int32_t x, int32_t y, HICON icon_handle);

        bool draw_icon(HDC dc_handle,
                       int32_t x_left,
                       int32_t y_top,
                       HICON icon_handle,
                       int32_t cx_width,
                       int32_t cy_width,
                       uint32_t step_if_ani_cur,
                       HBRUSH hbr_flicker_free_draw,
                       uint32_t flag);

        bool destroy_icon(HICON icon_handle);

        bool get_icon_info(HICON icon_handle, ICONINFO *icon_info);

        bool get_icon_info(HICON icon_handle, ICONINFOEXW *icon_info);

        int32_t lookup_icon_id_from_directory(uint8_t *res_buf, bool is_icon);

        int32_t lookup_icon_id_from_directory(uint8_t *res_buf,
                                          bool is_icon,
                                          int32_t desired_width,
                                          int32_t desired_height,
                                          uint32_t flag);

        uint32_t private_extract_icons(const wchar_t *file_name,
                                           int32_t icon_index,
                                           int32_t icon_width,
                                           int32_t icon_height,
                                           HICON *icon_handle,
                                           uint32_t *icon_id,
                                           uint32_t icon_count,
                                           uint32_t flag);

        [[nodiscard]] unsigned long err_code() const;

        [[nodiscard]] std::string err_string() const;

        [[nodiscard]] std::wstring err_wstring() const;
    };
}
#endif //ICON_H
