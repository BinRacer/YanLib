//
// Created by forkernel on 2025/4/30.
//

#ifndef IMAGE_H
#define IMAGE_H
#include <Windows.h>
#include <string>

namespace YanLib::ui {
    class image {
    private:
        unsigned long error_code = 0;

    public:
        image(const image &other) = delete;

        image(image &&other) = delete;

        image &operator=(const image &other) = delete;

        image &operator=(image &&other) = delete;

        image() = default;

        ~image() = default;

        HBITMAP load_bitmap(HINSTANCE instance_handle,
                            const wchar_t *image_name,
                            int32_t cx,
                            int32_t cy,
                            uint32_t load);

        HICON load_icon(HINSTANCE instance_handle,
                        const wchar_t *image_name,
                        int32_t cx,
                        int32_t cy,
                        uint32_t load);

        HCURSOR load_cursor(HINSTANCE instance_handle,
                            const wchar_t *image_name,
                            int32_t cx,
                            int32_t cy,
                            uint32_t load);

        HBITMAP copy_bitmap(HBITMAP bitmap_handle,
                            int32_t cx,
                            int32_t cy,
                            uint32_t flag);

        HICON copy_icon(HICON icon_handle,
                        int32_t cx,
                        int32_t cy,
                        uint32_t flag);

        HCURSOR copy_cursor(HCURSOR cursor_handle,
                            int32_t cx,
                            int32_t cy,
                            uint32_t flag);

        bool close_bitmap(HBITMAP bitmap_handle);

        bool close_icon(HICON icon_handle);

        bool close_cursor(HCURSOR cursor_handle);

        [[nodiscard]] unsigned long err_code() const;

        [[nodiscard]] std::string err_string() const;

        [[nodiscard]] std::wstring err_wstring() const;
    };
}
#endif //IMAGE_H
