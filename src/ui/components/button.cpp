//
// Created by forkernel on 2025/5/23.
//

#include "button.h"
#include <windowsx.h>
namespace YanLib::components {
    HWND button::create(uintptr_t button_id,
                        HWND parent_window_handle,
                        LPARAM lparam,
                        int32_t x,
                        int32_t y,
                        int32_t width,
                        int32_t height,
                        ButtonStyle style,
                        WindowStyle window_style) {
        HWND result = CreateWindowExW(0L, L"Button", nullptr,
                                      static_cast<uint32_t>(window_style) |
                                              static_cast<uint32_t>(style),
                                      x, y, width, height, parent_window_handle,
                                      reinterpret_cast<HMENU>(button_id),
                                      reinterpret_cast<CREATESTRUCT *>(lparam)
                                              ->hInstance,
                                      nullptr);
        if (!result) {
            error_code = GetLastError();
        }
        return result;
    }
    HWND button::create(const char *button_name,
                        uintptr_t button_id,
                        HWND parent_window_handle,
                        LPARAM lparam,
                        int32_t x,
                        int32_t y,
                        int32_t width,
                        int32_t height,
                        ButtonStyle style,
                        WindowStyle window_style) {
        HWND result = CreateWindowExA(0L, "Button", button_name,
                                      static_cast<uint32_t>(window_style) |
                                              static_cast<uint32_t>(style),
                                      x, y, width, height, parent_window_handle,
                                      reinterpret_cast<HMENU>(button_id),
                                      reinterpret_cast<CREATESTRUCT *>(lparam)
                                              ->hInstance,
                                      nullptr);
        if (!result) {
            error_code = GetLastError();
        }
        return result;
    }

    HWND button::create(const wchar_t *button_name,
                        uintptr_t button_id,
                        HWND parent_window_handle,
                        LPARAM lparam,
                        int32_t x,
                        int32_t y,
                        int32_t width,
                        int32_t height,
                        ButtonStyle style,
                        WindowStyle window_style) {
        HWND result = CreateWindowExW(0L, L"Button", button_name,
                                      static_cast<uint32_t>(window_style) |
                                              static_cast<uint32_t>(style),
                                      x, y, width, height, parent_window_handle,
                                      reinterpret_cast<HMENU>(button_id),
                                      reinterpret_cast<CREATESTRUCT *>(lparam)
                                              ->hInstance,
                                      nullptr);
        if (!result) {
            error_code = GetLastError();
        }
        return result;
    }

    bool button::enable(HWND button_handle) {
        return Button_Enable(button_handle, TRUE);
    }

    bool button::disable(HWND button_handle) {
        return Button_Enable(button_handle, FALSE);
    }

    ButtonState button::get_check(HWND button_handle) {
        return static_cast<ButtonState>(Button_GetCheck(button_handle));
    }

    void button::set_check(HWND button_handle, ButtonState state) {
        Button_SetCheck(button_handle, static_cast<uint32_t>(state));
    }

    bool button::get_ideal_size(HWND button_handle, SIZE *size) {
        return Button_GetIdealSize(button_handle, size);
    }

    bool button::get_image_list(HWND button_handle,
                                BUTTON_IMAGELIST *image_list) {
        return Button_GetImageList(button_handle, image_list);
    }

    bool button::set_image_list(HWND button_handle,
                                BUTTON_IMAGELIST *image_list) {
        return Button_SetImageList(button_handle, image_list);
    }

    int64_t button::get_note_len(HWND button_handle) {
        return Button_GetNoteLength(button_handle);
    }

    bool button::get_note(HWND button_handle,
                          std::string &note,
                          helper::CodePage code_page) {
        std::wstring temp(note.size(), L'\0');
        bool is_ok = Button_GetNote(button_handle, temp.data(), temp.size());
        note.clear();
        note = helper::convert::wstr_to_str(temp, code_page);
        return is_ok;
    }

    bool button::set_note(HWND button_handle,
                          std::string &note,
                          helper::CodePage code_page) {
        auto temp = helper::convert::str_to_wstr(note, code_page);
        return Button_SetNote(button_handle, temp.data());
    }

    bool button::get_note(HWND button_handle, std::wstring &note) {
        return Button_GetNote(button_handle, note.data(), note.size());
    }

    bool button::set_note(HWND button_handle, std::wstring &note) {
        return Button_SetNote(button_handle, note.data());
    }

    bool button::get_split_info(HWND button_handle,
                                BUTTON_SPLITINFO *split_info) {
        return Button_GetSplitInfo(button_handle, split_info);
    }

    bool button::set_split_info(HWND button_handle,
                                BUTTON_SPLITINFO *split_info) {
        return Button_SetSplitInfo(button_handle, split_info);
    }

    int32_t button::get_text_len(HWND button_handle) {
        SetLastError(ERROR_SUCCESS);
        int32_t result = GetWindowTextLengthW(button_handle);
        error_code = GetLastError();
        return result;
    }

    int32_t button::get_text(HWND button_handle, std::string &text) {
        int32_t result = GetWindowTextA(button_handle, text.data(),
                                        static_cast<int32_t>(text.size()));
        if (!result) {
            error_code = GetLastError();
        }
        return result;
    }

    bool button::set_text(HWND button_handle, std::string &text) {
        if (!SetWindowTextA(button_handle, text.data())) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    int32_t button::get_text(HWND button_handle, std::wstring &text) {
        int32_t result = GetWindowTextW(button_handle, text.data(),
                                        static_cast<int32_t>(text.size()));
        if (!result) {
            error_code = GetLastError();
        }
        return result;
    }

    bool button::set_text(HWND button_handle, std::wstring &text) {
        if (!SetWindowTextW(button_handle, text.data())) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    TextAlign button::get_text_align(HWND button_handle) {
        intptr_t style = GetWindowLongPtrW(button_handle, GWL_STYLE);
        return static_cast<TextAlign>(style & BS_TYPEMASK);
    }

    void button::set_text_align(HWND button_handle, TextAlign align) {
        intptr_t style = GetWindowLongPtrW(button_handle, GWL_STYLE);
        style &= ~(BS_LEFT | BS_CENTER | BS_RIGHT | BS_TOP | BS_BOTTOM |
                   BS_VCENTER);
        style |= static_cast<uint32_t>(align);
        SetWindowLongPtrW(button_handle, GWL_STYLE, style);
        InvalidateRect(button_handle, nullptr, TRUE);
    }

    bool button::get_text_margin(HWND button_handle, RECT *margin) {
        return Button_GetTextMargin(button_handle, margin);
    }

    bool button::set_text_margin(HWND button_handle, RECT *margin) {
        return Button_SetTextMargin(button_handle, margin);
    }

    ButtonState button::get_state(HWND button_handle) {
        return static_cast<ButtonState>(Button_GetState(button_handle));
    }

    void button::hilite(HWND button_handle) {
        Button_SetState(button_handle, TRUE);
    }

    void button::unhilite(HWND button_handle) {
        Button_SetState(button_handle, FALSE);
    }

    bool button::active_drop_down_state(HWND button_handle) {
        return Button_SetDropDownState(button_handle, TRUE);
    }

    bool button::inactive_drop_down_state(HWND button_handle) {
        return Button_SetDropDownState(button_handle, FALSE);
    }

    LRESULT button::set_elevation_state(HWND button_handle) {
        return Button_SetElevationRequiredState(button_handle, TRUE);
    }

    LRESULT button::unset_elevation_state(HWND button_handle) {
        return Button_SetElevationRequiredState(button_handle, FALSE);
    }

    ButtonStyle button::get_style(HWND button_handle) {
        intptr_t style = GetWindowLongPtrW(button_handle, GWL_STYLE);
        return static_cast<ButtonStyle>(style & BS_TYPEMASK);
    }

    void
    button::set_style(HWND button_handle, ButtonStyle style, bool is_redraw) {
        Button_SetStyle(button_handle, static_cast<uint32_t>(style),
                        is_redraw ? TRUE : FALSE);
    }

    uint32_t button::err_code() const {
        return error_code;
    }

    std::string button::err_string() const {
        std::string result = helper::convert::err_string(error_code);
        return result;
    }

    std::wstring button::err_wstring() const {
        std::wstring result = helper::convert::err_wstring(error_code);
        return result;
    }
} // namespace YanLib::components
