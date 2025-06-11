//
// Created by BinRacer <native.lab@outlook.com> on 2025/5/31.
//

#include "status.h"
#include <windowsx.h>

namespace YanLib::ui::components {
    HWND status::create(uintptr_t status_id,
                        HWND parent_window_handle,
                        LPARAM lparam,
                        int32_t x,
                        int32_t y,
                        int32_t width,
                        int32_t height,
                        StatusStyle style,
                        WindowStyle window_style) {
        HWND result = CreateWindowExW(0L, L"msctls_statusbar32", nullptr,
                                      static_cast<uint32_t>(window_style) |
                                              static_cast<uint32_t>(style),
                                      x, y, width, height, parent_window_handle,
                                      reinterpret_cast<HMENU>(status_id),
                                      reinterpret_cast<CREATESTRUCT *>(lparam)
                                              ->hInstance,
                                      nullptr);
        if (!result) {
            error_code = GetLastError();
        }
        return result;
    }

    HWND status::create(const char *status_name,
                        uintptr_t status_id,
                        HWND parent_window_handle,
                        LPARAM lparam,
                        int32_t x,
                        int32_t y,
                        int32_t width,
                        int32_t height,
                        StatusStyle style,
                        WindowStyle window_style) {
        HWND result = CreateWindowExA(0L, "msctls_statusbar32", status_name,
                                      static_cast<uint32_t>(window_style) |
                                              static_cast<uint32_t>(style),
                                      x, y, width, height, parent_window_handle,
                                      reinterpret_cast<HMENU>(status_id),
                                      reinterpret_cast<CREATESTRUCT *>(lparam)
                                              ->hInstance,
                                      nullptr);
        if (!result) {
            error_code = GetLastError();
        }
        return result;
    }

    HWND status::create(const wchar_t *status_name,
                        uintptr_t status_id,
                        HWND parent_window_handle,
                        LPARAM lparam,
                        int32_t x,
                        int32_t y,
                        int32_t width,
                        int32_t height,
                        StatusStyle style,
                        WindowStyle window_style) {
        HWND result = CreateWindowExW(0L, L"msctls_statusbar32", status_name,
                                      static_cast<uint32_t>(window_style) |
                                              static_cast<uint32_t>(style),
                                      x, y, width, height, parent_window_handle,
                                      reinterpret_cast<HMENU>(status_id),
                                      reinterpret_cast<CREATESTRUCT *>(lparam)
                                              ->hInstance,
                                      nullptr);
        if (!result) {
            error_code = GetLastError();
        }
        return result;
    }

    void status::draw_status_text(HDC dc_handle,
                                  RECT *rect,
                                  const char *text,
                                  StatusTextFlag flag) {
        DrawStatusTextA(dc_handle, rect, text, static_cast<uint32_t>(flag));
    }

    void status::draw_status_text(HDC dc_handle,
                                  RECT *rect,
                                  const wchar_t *text,
                                  StatusTextFlag flag) {
        DrawStatusTextW(dc_handle, rect, text, static_cast<uint32_t>(flag));
    }

    void status::menu_help(uint32_t message,
                           WPARAM wparam,
                           LPARAM lparam,
                           HMENU menu_handle,
                           HINSTANCE instance_handle,
                           HWND status_handle,
                           uint32_t id[]) {
        MenuHelp(message, wparam, lparam, menu_handle, instance_handle,
                 status_handle, id);
    }

    bool status::get_borders(HWND status_handle, int32_t borders[3]) {
        return SendMessageW(status_handle, SB_GETBORDERS, 0,
                            reinterpret_cast<LPARAM>(borders));
    }

    bool status::get_rect(HWND status_handle, int32_t index, RECT *rect) {
        return SendMessageW(status_handle, SB_GETRECT, index,
                            reinterpret_cast<LPARAM>(rect));
    }

    COLORREF status::set_background_color(HWND status_handle, COLORREF color) {
        return SendMessageW(status_handle, SB_SETBKCOLOR, 0, color);
    }

    void status::set_min_height(HWND status_handle, int32_t height) {
        SendMessageW(status_handle, SB_SETMINHEIGHT, height, 0);
    }

    HICON status::get_icon(HWND status_handle, int32_t index) {
        return reinterpret_cast<HICON>(
                SendMessageW(status_handle, SB_GETICON, index, 0));
    }

    bool status::set_icon(HWND status_handle, HICON icon, int32_t index) {
        return SendMessageW(status_handle, SB_SETICON, index,
                            reinterpret_cast<LPARAM>(icon));
    }

    bool status::delete_icon(HWND status_handle, int32_t index) {
        return SendMessageW(status_handle, SB_SETICON, index, 0);
    }

    int64_t status::get_parts(HWND status_handle, std::vector<int32_t> &parts) {
        return SendMessageW(status_handle, SB_GETPARTS, parts.size(),
                            reinterpret_cast<LPARAM>(parts.data()));
    }

    bool status::set_parts(HWND status_handle, std::vector<int32_t> &parts) {
        return SendMessageW(status_handle, SB_SETPARTS, parts.size(),
                            reinterpret_cast<LPARAM>(parts.data()));
    }

    std::pair<uint32_t, StatusTextFlag>
    status::get_text(HWND status_handle,
                     uint8_t index,
                     std::string &text,
                     helper::CodePage code_page) {
        std::wstring temp(text.size(), L'\0');
        const auto result = static_cast<int32_t>(
                SendMessageW(status_handle, SB_GETTEXT, index,
                             reinterpret_cast<LPARAM>(temp.data())));
        text.clear();
        text = helper::convert::wstr_to_str(temp, code_page);
        return std::make_pair(static_cast<uint32_t>(text.size()),
                              static_cast<StatusTextFlag>(HIWORD(result)));
    }

    std::pair<uint32_t, StatusTextFlag>
    status::get_text(HWND status_handle, uint8_t index, std::wstring &text) {
        const auto result = static_cast<int32_t>(
                SendMessageW(status_handle, SB_GETTEXT, index,
                             reinterpret_cast<LPARAM>(text.data())));
        return std::make_pair(LOWORD(result),
                              static_cast<StatusTextFlag>(HIWORD(result)));
    }

    bool status::set_text(HWND status_handle,
                          uint8_t index,
                          StatusTextFlag flag,
                          std::string &text,
                          helper::CodePage code_page) {
        return SendMessageW(
                status_handle, SB_SETTEXT, index | static_cast<uint32_t>(flag),
                reinterpret_cast<LPARAM>(
                        helper::convert::str_to_wstr(text, code_page).data()));
    }

    bool status::set_text(HWND status_handle,
                          uint8_t index,
                          StatusTextFlag flag,
                          std::wstring &text) {
        return SendMessageW(status_handle, SB_SETTEXT,
                            index | static_cast<uint32_t>(flag),
                            reinterpret_cast<LPARAM>(text.data()));
    }

    std::pair<uint32_t, StatusTextFlag> status::get_text_len(HWND status_handle,
                                                             uint8_t index) {
        const auto result = static_cast<int32_t>(
                SendMessageW(status_handle, SB_GETTEXTLENGTH, index, 0));
        return std::make_pair(LOWORD(result),
                              static_cast<StatusTextFlag>(HIWORD(result)));
    }

    void status::get_tip_text(HWND status_handle,
                              uint8_t index,
                              std::string &text,
                              helper::CodePage code_page) {
        std::wstring temp(text.size(), L'\0');
        SendMessageW(status_handle, SB_GETTIPTEXT, MAKEWORD(index, temp.size()),
                     reinterpret_cast<LPARAM>(temp.data()));
        text.clear();
        text = helper::convert::wstr_to_str(temp, code_page);
    }

    void status::get_tip_text(HWND status_handle,
                              uint8_t index,
                              std::wstring &text) {
        SendMessageW(status_handle, SB_GETTIPTEXT, MAKEWORD(index, text.size()),
                     reinterpret_cast<LPARAM>(text.data()));
    }

    void status::set_tip_text(HWND status_handle,
                              uint8_t index,
                              std::string &text,
                              helper::CodePage code_page) {
        SendMessageW(status_handle, SB_SETTIPTEXT, index,
                     reinterpret_cast<LPARAM>(
                             helper::convert::str_to_wstr(text, code_page)
                                     .data()));
    }

    void status::set_tip_text(HWND status_handle,
                              uint8_t index,
                              std::wstring &text) {
        SendMessageW(status_handle, SB_SETTIPTEXT, index,
                     reinterpret_cast<LPARAM>(text.data()));
    }

    bool status::is_ansi_format(HWND status_handle) {
        return !SendMessageW(status_handle, SB_GETUNICODEFORMAT, 0, 0);
    }

    bool status::is_unicode_format(HWND status_handle) {
        return SendMessageW(status_handle, SB_GETUNICODEFORMAT, 0, 0);
    }

    void status::set_ansi_format(HWND status_handle) {
        SendMessageW(status_handle, SB_SETUNICODEFORMAT, FALSE, 0);
    }

    void status::set_unicode_format(HWND status_handle) {
        SendMessageW(status_handle, SB_SETUNICODEFORMAT, TRUE, 0);
    }

    bool status::is_simple(HWND status_handle) {
        return SendMessageW(status_handle, SB_ISSIMPLE, 0, 0);
    }

    void status::show_simple(HWND status_handle) {
        SendMessageW(status_handle, SB_SIMPLE, TRUE, 0);
    }

    void status::show_parts(HWND status_handle) {
        SendMessageW(status_handle, SB_SIMPLE, FALSE, 0);
    }

    uint32_t status::err_code() const {
        return error_code;
    }

    std::string status::err_string() const {
        std::string result = helper::convert::err_string(error_code);
        return result;
    }

    std::wstring status::err_wstring() const {
        std::wstring result = helper::convert::err_wstring(error_code);
        return result;
    }
} // namespace YanLib::ui::components
