//
// Created by forkernel on 2025/4/30.
//

#ifndef CLIPBOARD_H
#define CLIPBOARD_H
#include <Windows.h>
#include <string>

namespace YanLib::ui {
    class clipboard {
    private:
        unsigned long error_code = 0;

    public:
        clipboard(const clipboard &other) = delete;

        clipboard(clipboard &&other) = delete;

        clipboard &operator=(const clipboard &other) = delete;

        clipboard &operator=(clipboard &&other) = delete;

        clipboard() = default;

        ~clipboard() = default;

        bool open_clipboard(HWND hwnd = nullptr);

        uint32_t register_clipboard_format(const wchar_t *format);

        bool empty_clipboard();

        bool close_clipboard();

        HANDLE get_clipboard_data(uint32_t format);

        HANDLE set_clipboard_data(uint32_t format, HANDLE mem_handle);

        int32_t get_clipboard_format_name(uint32_t format, wchar_t *format_name, int32_t cch_max);

        HWND get_open_clipboard_window();

        HWND get_clipboard_owner();

        unsigned long get_clipboard_sequence_number();

        HWND get_clipboard_viewer();

        int32_t get_priority_clipboard_format(uint32_t *format_priority_list, int32_t formats);

        bool get_updated_clipboard_formats(uint32_t *formats,
                                           uint32_t formats_count,
                                           uint32_t *formats_out);

        bool is_clipboard_format_available(uint32_t format);

        bool add_clipboard_format_listener(HWND hwnd);

        bool remove_clipboard_format_listener(HWND hwnd);

        bool change_clipboard_chain(HWND hwnd_remove, HWND hwnd_new_next);

        uint32_t enum_clipboard_formats(uint32_t format);

        int32_t count_clipboard_formats();

        [[nodiscard]] unsigned long err_code() const;

        [[nodiscard]] std::string err_string() const;

        [[nodiscard]] std::wstring err_wstring() const;
    };
}
#endif //CLIPBOARD_H
