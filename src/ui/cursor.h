//
// Created by forkernel on 2025/4/30.
//

#ifndef CURSOR_H
#define CURSOR_H
#include <Windows.h>
#include <string>

namespace YanLib::ui {
    class cursor {
    private:
        unsigned long error_code = 0;

    public:
        cursor(const cursor &other) = delete;

        cursor(cursor &&other) = delete;

        cursor &operator=(const cursor &other) = delete;

        cursor &operator=(cursor &&other) = delete;

        cursor() = default;

        ~cursor() = default;

        HCURSOR create_cursor(HINSTANCE instance_handle,
                              int32_t x_hotspot,
                              int32_t y_hotspot,
                              int32_t width,
                              int32_t height,
                              const void *and_plane,
                              const void *xor_plane);

        HCURSOR load_cursor(HINSTANCE instance_handle, const wchar_t *cursor_name);

        HCURSOR load_cursor_from_file(const wchar_t *file_name);

        bool clip_cursor(const RECT *rect);

        HCURSOR copy_cursor(HCURSOR cursor_handle);

        HCURSOR get_cursor();

        HCURSOR set_cursor(HCURSOR cursor_handle);

        bool get_cursor_info(CURSORINFO *cursor_info);

        bool get_cursor_pos(POINT *point);

        bool set_cursor_pos(int32_t x, int32_t y);

        bool get_clip_cursor(RECT *rect);

        bool get_physical_cursor_pos(POINT *point);

        bool set_physical_cursor_pos(int32_t x, int32_t y);

        bool get_pointer_cursor_id(uint32_t pointer_id, uint32_t *cursor_id);

        bool get_pointer_device_cursors(HANDLE device_handle,
                                        uint32_t *cursor_count,
                                        POINTER_DEVICE_CURSOR_INFO *device_cursors);

        bool set_system_cursor(HCURSOR cursor_handle, unsigned long id);

        uint32_t set_thread_cursor_creation_scaling(uint32_t cursor_dpi);

        int32_t show_cursor();

        int32_t hide_cursor();

        bool destroy_cursor(HCURSOR cursor_handle);

        [[nodiscard]] unsigned long err_code() const;

        [[nodiscard]] std::string err_string() const;

        [[nodiscard]] std::wstring err_wstring() const;
    };
}
#endif //CURSOR_H
