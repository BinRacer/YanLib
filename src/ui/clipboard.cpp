//
// Created by forkernel on 2025/4/30.
//

#include "clipboard.h"
#include "helper/convert.h"

namespace YanLib::ui {
    bool clipboard::open_clipboard(HWND hwnd) {
        if (!OpenClipboard(hwnd)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    UINT clipboard::register_clipboard_format(const wchar_t *format) {
        UINT result = RegisterClipboardFormatW(format);
        if (!result) {
            error_code = GetLastError();
        }
        return result;
    }

    bool clipboard::empty_clipboard() {
        if (!EmptyClipboard()) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool clipboard::close_clipboard() {
        if (!CloseClipboard()) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    HANDLE clipboard::get_clipboard_data(UINT format) {
        HANDLE result = GetClipboardData(format);
        if (!result) {
            error_code = GetLastError();
        }
        return result;
    }

    HANDLE clipboard::set_clipboard_data(UINT format, HANDLE mem_handle) {
        HANDLE result = SetClipboardData(format, mem_handle);
        if (!result) {
            error_code = GetLastError();
        }
        return result;
    }

    int clipboard::get_clipboard_format_name(UINT format,
                                             wchar_t *format_name,
                                             int cch_max) {
        int result = GetClipboardFormatNameW(format, format_name, cch_max);
        if (!result) {
            error_code = GetLastError();
        }
        return result;
    }

    HWND clipboard::get_open_clipboard_window() {
        HWND hwnd = GetOpenClipboardWindow();
        if (!hwnd) {
            error_code = GetLastError();
        }
        return hwnd;
    }

    HWND clipboard::get_clipboard_owner() {
        HWND result = GetClipboardOwner();
        if (!result) {
            error_code = GetLastError();
        }
        return result;
    }

    DWORD clipboard::get_clipboard_sequence_number() {
        return GetClipboardSequenceNumber();
    }

    HWND clipboard::get_clipboard_viewer() {
        HWND result = GetClipboardViewer();
        if (!result) {
            error_code = GetLastError();
        }
        return result;
    }

    int clipboard::get_priority_clipboard_format(UINT *format_priority_list,
                                                 int formats) {
        int result = GetPriorityClipboardFormat(format_priority_list, formats);
        if (result == -1) {
            error_code = GetLastError();
        }
        return result;
    }

    bool clipboard::get_updated_clipboard_formats(PUINT formats,
                                                  UINT formats_count,
                                                  PUINT formats_out) {
        if (!GetUpdatedClipboardFormats(formats,
                                        formats_count,
                                        formats_out)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool clipboard::is_clipboard_format_available(UINT format) {
        if (!IsClipboardFormatAvailable(format)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool clipboard::add_clipboard_format_listener(HWND hwnd) {
        if (!AddClipboardFormatListener(hwnd)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool clipboard::remove_clipboard_format_listener(HWND hwnd) {
        if (!RemoveClipboardFormatListener(hwnd)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool clipboard::change_clipboard_chain(HWND hwnd_remove, HWND hwnd_new_next) {
        return ChangeClipboardChain(hwnd_remove, hwnd_new_next);
    }

    UINT clipboard::enum_clipboard_formats(UINT format) {
        UINT result = EnumClipboardFormats(format);
        if (!result) {
            error_code = GetLastError();
        }
        return result;
    }

    int clipboard::count_clipboard_formats() {
        int result = CountClipboardFormats();
        if (!result) {
            error_code = GetLastError();
        }
        return result;
    }

    DWORD clipboard::err_code() const {
        return error_code;
    }

    std::string clipboard::err_string() const {
        std::string result = helper::convert::err_string(error_code);
        return result;
    }

    std::wstring clipboard::err_wstring() const {
        std::wstring result = helper::convert::err_wstring(error_code);
        return result;
    }
}
