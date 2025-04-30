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

        HANDLE load_image(HINSTANCE instance_handle,
                          const wchar_t *image_name,
                          UINT type,
                          int cx,
                          int cy,
                          UINT load);

        HANDLE copy_image(HANDLE image_handle,
                          UINT type,
                          int cx,
                          int cy,
                          UINT flag);

        bool close_image(HANDLE image_handle);

        [[nodiscard]] DWORD err_code() const;

        [[nodiscard]] std::string err_string() const;

        [[nodiscard]] std::wstring err_wstring() const;
    };
}
#endif //IMAGE_H
