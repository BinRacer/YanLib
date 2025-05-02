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
        DWORD error_code = 0;

    public:
        icon(const icon &other) = delete;

        icon(icon &&other) = delete;

        icon &operator=(const icon &other) = delete;

        icon &operator=(icon &&other) = delete;

        icon() = default;

        ~icon() = default;

        HICON create_icon(HINSTANCE instance_handle,
                          int width,
                          int height,
                          uint8_t planes,
                          uint8_t bits_pixel,
                          const uint8_t *and_bits,
                          const uint8_t *xor_bits);

        HICON create_icon_from_resource(uint8_t *res_buf,
                                        DWORD res_size,
                                        bool is_icon,
                                        DWORD version);

        HICON create_icon_from_resource(uint8_t *res_buf,
                                        DWORD res_size,
                                        bool is_icon,
                                        DWORD version,
                                        int desired_width,
                                        int desired_height,
                                        UINT flag);

        HICON create_icon_indirect(PICONINFO icon_info);

        HICON load_icon(HINSTANCE instance_handle, const wchar_t *icon_name);

        HICON copy_icon(HICON icon_handle);

        bool draw_icon(HDC dc_handle, int x, int y, HICON icon_handle);

        bool draw_icon(HDC dc_handle,
                       int x_left,
                       int y_top,
                       HICON icon_handle,
                       int cx_width,
                       int cy_width,
                       UINT step_if_ani_cur,
                       HBRUSH hbr_flicker_free_draw,
                       UINT flag);

        bool destroy_icon(HICON icon_handle);

        bool get_icon_info(HICON icon_handle, PICONINFO icon_info);

        bool get_icon_info(HICON icon_handle, PICONINFOEXW icon_info);

        int lookup_icon_id_from_directory(uint8_t *res_buf, bool is_icon);

        int lookup_icon_id_from_directory(uint8_t *res_buf,
                                          bool is_icon,
                                          int desired_width,
                                          int desired_height,
                                          UINT flag);

        UINT private_extract_icons(const wchar_t *file_name,
                                   int icon_index,
                                   int icon_width,
                                   int icon_height,
                                   HICON *icon_handle,
                                   UINT *icon_id,
                                   UINT icon_count,
                                   UINT flag);

        [[nodiscard]] DWORD err_code() const;

        [[nodiscard]] std::string err_string() const;

        [[nodiscard]] std::wstring err_wstring() const;
    };
}
#endif //ICON_H
