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
        DWORD error_code = 0;

    public:
        image(const image &other) = delete;

        image(image &&other) = delete;

        image &operator=(const image &other) = delete;

        image &operator=(image &&other) = delete;

        image() = default;

        ~image() = default;

        HBITMAP load_bitmap(HINSTANCE instance_handle,
                            const wchar_t *image_name,
                            int cx,
                            int cy,
                            UINT load);

        HICON load_icon(HINSTANCE instance_handle,
                        const wchar_t *image_name,
                        int cx,
                        int cy,
                        UINT load);

        HCURSOR load_cursor(HINSTANCE instance_handle,
                            const wchar_t *image_name,
                            int cx,
                            int cy,
                            UINT load);

        HBITMAP copy_bitmap(HBITMAP bitmap_handle,
                            int cx,
                            int cy,
                            UINT flag);

        HICON copy_icon(HICON icon_handle,
                        int cx,
                        int cy,
                        UINT flag);

        HCURSOR copy_cursor(HCURSOR cursor_handle,
                            int cx,
                            int cy,
                            UINT flag);

        bool close_bitmap(HBITMAP bitmap_handle);

        bool close_icon(HICON icon_handle);

        bool close_cursor(HCURSOR cursor_handle);

        [[nodiscard]] DWORD err_code() const;

        [[nodiscard]] std::string err_string() const;

        [[nodiscard]] std::wstring err_wstring() const;
    };
}
#endif //IMAGE_H
