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

        unsigned int register_clipboard_format(const wchar_t *format);

        bool empty_clipboard();

        bool close_clipboard();

        HANDLE get_clipboard_data(unsigned int format);

        HANDLE set_clipboard_data(unsigned int format, HANDLE mem_handle);

        int get_clipboard_format_name(unsigned int format, wchar_t *format_name, int cch_max);

        HWND get_open_clipboard_window();

        HWND get_clipboard_owner();

        unsigned long get_clipboard_sequence_number();

        HWND get_clipboard_viewer();

        int get_priority_clipboard_format(unsigned int *format_priority_list, int formats);

        bool get_updated_clipboard_formats(unsigned int *formats,
                                           unsigned int formats_count,
                                           unsigned int *formats_out);

        bool is_clipboard_format_available(unsigned int format);

        bool add_clipboard_format_listener(HWND hwnd);

        bool remove_clipboard_format_listener(HWND hwnd);

        bool change_clipboard_chain(HWND hwnd_remove, HWND hwnd_new_next);

        unsigned int enum_clipboard_formats(unsigned int format);

        int count_clipboard_formats();

        [[nodiscard]] unsigned long err_code() const;

        [[nodiscard]] std::string err_string() const;

        [[nodiscard]] std::wstring err_wstring() const;
    };
}
#endif //CLIPBOARD_H
