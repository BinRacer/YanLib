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
        DWORD error_code = 0;

    public:
        clipboard(const clipboard &other) = delete;

        clipboard(clipboard &&other) = delete;

        clipboard &operator=(const clipboard &other) = delete;

        clipboard &operator=(clipboard &&other) = delete;

        clipboard() = default;

        ~clipboard() = default;

        bool open_clipboard(HWND hwnd = nullptr);

        UINT register_clipboard_format(const wchar_t *format);

        bool empty_clipboard();

        bool close_clipboard();

        HANDLE get_clipboard_data(UINT format);

        HANDLE set_clipboard_data(UINT format, HANDLE mem_handle);

        int get_clipboard_format_name(UINT format, wchar_t *format_name, int cch_max);

        HWND get_open_clipboard_window();

        HWND get_clipboard_owner();

        DWORD get_clipboard_sequence_number();

        HWND get_clipboard_viewer();

        int get_priority_clipboard_format(UINT *format_priority_list, int formats);

        bool get_updated_clipboard_formats(UINT* formats,
                                           UINT formats_count,
                                           UINT* formats_out);

        bool is_clipboard_format_available(UINT format);

        bool add_clipboard_format_listener(HWND hwnd);

        bool remove_clipboard_format_listener(HWND hwnd);

        bool change_clipboard_chain(HWND hwnd_remove, HWND hwnd_new_next);

        UINT enum_clipboard_formats(UINT format);

        int count_clipboard_formats();

        [[nodiscard]] DWORD err_code() const;

        [[nodiscard]] std::string err_string() const;

        [[nodiscard]] std::wstring err_wstring() const;
    };
}
#endif //CLIPBOARD_H
