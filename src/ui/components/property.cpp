/* clang-format off */
/*
 * @file property.cpp
 * @date 2025-05-29
 * @license MIT License
 *
 * Copyright (c) 2025 BinRacer <native.lab@outlook.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
/* clang-format on */
#include "property.h"
#include <windowsx.h>
namespace YanLib::ui::components {
    PROPSHEETHEADERA
    property::make_header(const char *caption,
                          HWND parent_window_handle,
                          HINSTANCE instance_handle,
                          std::vector<PROPSHEETPAGEA> &prop_sheet_page,
                          PFNPROPSHEETCALLBACK callback,
                          PropertyHeaderFlag flag,
                          HICON icon_handle,
                          HBITMAP water_mark_handle,
                          HPALETTE palette_handle,
                          HBITMAP header_handle) {
        PROPSHEETHEADERA header = {};
        header.dwSize = sizeof(PROPSHEETHEADERA);
        header.dwFlags = static_cast<uint32_t>(flag);
        header.hwndParent = parent_window_handle;
        header.hInstance = instance_handle;
        header.hIcon = icon_handle;
        header.pszCaption = caption;
        header.nPages = prop_sheet_page.size();
        header.nStartPage = 0;
        header.ppsp = prop_sheet_page.data();
        header.pfnCallback = callback;
        header.hbmWatermark = water_mark_handle;
        header.hplWatermark = palette_handle;
        header.hbmHeader = header_handle;
        return header;
    }
    PROPSHEETHEADERW
    property::make_header(const wchar_t *caption,
                          HWND parent_window_handle,
                          HINSTANCE instance_handle,
                          std::vector<PROPSHEETPAGEW> &prop_sheet_page,
                          PFNPROPSHEETCALLBACK callback,
                          PropertyHeaderFlag flag,
                          HICON icon_handle,
                          HBITMAP water_mark_handle,
                          HPALETTE palette_handle,
                          HBITMAP header_handle) {
        PROPSHEETHEADERW header = {};
        header.dwSize = sizeof(PROPSHEETHEADERW);
        header.dwFlags = static_cast<uint32_t>(flag);
        header.hwndParent = parent_window_handle;
        header.hInstance = instance_handle;
        header.hIcon = icon_handle;
        header.pszCaption = caption;
        header.nPages = prop_sheet_page.size();
        header.nStartPage = 0;
        header.ppsp = prop_sheet_page.data();
        header.pfnCallback = callback;
        header.hbmWatermark = water_mark_handle;
        header.hplWatermark = palette_handle;
        header.hbmHeader = header_handle;
        return header;
    }

    HWND property::create(PROPSHEETHEADERA *header) {
        return reinterpret_cast<HWND>(PropertySheetA(header));
    }

    HWND property::create(PROPSHEETHEADERW *header) {
        return reinterpret_cast<HWND>(PropertySheetW(header));
    }

    PROPSHEETPAGEA property::make_page(const char *title,
                                       HINSTANCE instance_handle,
                                       const char *templates,
                                       DLGPROC dialog_func,
                                       LPARAM dialog_param,
                                       LPFNPSPCALLBACKA callback,
                                       PropertyPageFlag flag,
                                       const char *header_title,
                                       const char *header_subtitle,
                                       HICON icon_handle,
                                       HBITMAP header_handle,
                                       uint32_t *ref_parent,
                                       HANDLE active_context_handle) {
        PROPSHEETPAGEA page = {};
        page.dwSize = sizeof(PROPSHEETPAGEA);
        page.dwFlags = static_cast<uint32_t>(flag);
        page.hInstance = instance_handle;
        page.pszTemplate = templates;
        page.hIcon = icon_handle;
        page.pszTitle = title;
        page.pfnDlgProc = dialog_func;
        page.lParam = dialog_param;
        page.pfnCallback = callback;
        page.pcRefParent = ref_parent;
        page.pszHeaderTitle = header_title;
        page.pszHeaderSubTitle = header_subtitle;
        page.hActCtx = active_context_handle;
        page.hbmHeader = header_handle;
        return page;
    }
    PROPSHEETPAGEW property::make_page(const wchar_t *title,
                                       HINSTANCE instance_handle,
                                       const wchar_t *templates,
                                       DLGPROC dialog_func,
                                       LPARAM dialog_param,
                                       LPFNPSPCALLBACKW callback,
                                       PropertyPageFlag flag,
                                       const wchar_t *header_title,
                                       const wchar_t *header_subtitle,
                                       HICON icon_handle,
                                       HBITMAP header_handle,
                                       uint32_t *ref_parent,
                                       HANDLE active_context_handle) {
        PROPSHEETPAGEW page = {};
        page.dwSize = sizeof(PROPSHEETPAGEW);
        page.dwFlags = static_cast<uint32_t>(flag);
        page.hInstance = instance_handle;
        page.pszTemplate = templates;
        page.hIcon = icon_handle;
        page.pszTitle = title;
        page.pfnDlgProc = dialog_func;
        page.lParam = dialog_param;
        page.pfnCallback = callback;
        page.pcRefParent = ref_parent;
        page.pszHeaderTitle = header_title;
        page.pszHeaderSubTitle = header_subtitle;
        page.hActCtx = active_context_handle;
        page.hbmHeader = header_handle;
        return page;
    }

    HPROPSHEETPAGE property::create_page(PROPSHEETPAGEA *page) {
        return CreatePropertySheetPageA(page);
    }

    HPROPSHEETPAGE property::create_page(PROPSHEETPAGEW *page) {
        return CreatePropertySheetPageW(page);
    }

    bool property::destroy_page(HPROPSHEETPAGE page_handle) {
        return DestroyPropertySheetPage(page_handle);
    }

    bool property::add_page(HWND property_handle, HPROPSHEETPAGE page_handle) {
        return PropSheet_AddPage(property_handle, page_handle);
    }

    bool property::insert_page(HWND property_handle,
                               int32_t index,
                               HPROPSHEETPAGE page_handle) {
        return PropSheet_InsertPage(property_handle, index, page_handle);
    }

    void property::remove_page(HWND property_handle,
                               int32_t index,
                               HPROPSHEETPAGE page_handle) {
        PropSheet_RemovePage(property_handle, index, page_handle);
    }

    void property::change_page(HWND property_handle,
                               HPROPSHEETPAGE page_handle) {
        PropSheet_Changed(property_handle, page_handle);
    }

    void property::unchange_page(HWND property_handle,
                                 HPROPSHEETPAGE page_handle) {
        PropSheet_UnChanged(property_handle, page_handle);
    }

    int32_t property::get_page_index(HWND property_handle,
                                     HPROPSHEETPAGE page_handle) {
        return PropSheet_HwndToIndex(property_handle, page_handle);
    }

    int32_t property::get_page_index2(HWND property_handle,
                                      HPROPSHEETPAGE page_handle) {
        return PropSheet_PageToIndex(property_handle, page_handle);
    }

    int32_t property::get_page_index(HWND property_handle, int32_t res_id) {
        return PropSheet_IdToIndex(property_handle, res_id);
    }

    bool property::active_curr_page(HWND property_handle,
                                    HPROPSHEETPAGE page_handle,
                                    uint32_t index) {
        return PropSheet_SetCurSel(property_handle, page_handle, index);
    }

    bool property::active_curr_page(HWND property_handle, int32_t res_id) {
        return PropSheet_SetCurSelByID(property_handle, res_id);
    }

    HPROPSHEETPAGE property::get_page_handle(HWND property_handle,
                                             int32_t index) {
        return reinterpret_cast<HPROPSHEETPAGE>(
                PropSheet_IndexToHwnd(property_handle, index));
    }

    HPROPSHEETPAGE property::get_page_handle2(HWND property_handle,
                                              int32_t index) {
        return PropSheet_IndexToPage(property_handle, index);
    }

    int32_t property::get_page_res_id(HWND property_handle, int32_t index) {
        return PropSheet_IndexToId(property_handle, index);
    }

    HWND property::get_curr_page_handle(HWND property_handle) {
        return PropSheet_GetCurrentPageHwnd(property_handle);
    }

    int32_t property::get_result(HWND property_handle) {
        return PropSheet_GetResult(property_handle);
    }

    HWND property::get_tab_control(HWND property_handle) {
        return PropSheet_GetTabControl(property_handle);
    }

    void property::set_button_text(HWND property_handle,
                                   PropertyButton button,
                                   std::string &text,
                                   helper::CodePage code_page) {
        PropSheet_SetButtonText(property_handle, static_cast<uint32_t>(button),
                                helper::convert::str_to_wstr(text, code_page)
                                        .data());
    }

    void property::set_button_text(HWND property_handle,
                                   PropertyButton button,
                                   std::wstring &text) {
        PropSheet_SetButtonText(property_handle, static_cast<uint32_t>(button),
                                text.data());
    }

    void property::set_finish_button_text(HWND property_handle,
                                          std::string &text,
                                          helper::CodePage code_page) {
        PropSheet_SetFinishText(property_handle,
                                helper::convert::str_to_wstr(text, code_page)
                                        .data());
    }
    void property::set_finish_button_text(HWND property_handle,
                                          std::wstring &text) {
        PropSheet_SetFinishText(property_handle, text.data());
    }

    void property::set_next_button_text(HWND property_handle,
                                        std::string &text,
                                        helper::CodePage code_page) {
        PropSheet_SetNextText(property_handle,
                              helper::convert::str_to_wstr(text, code_page)
                                      .data());
    }

    void property::set_next_button_text(HWND property_handle,
                                        std::wstring &text) {
        PropSheet_SetNextText(property_handle, text.data());
    }

    void property::set_header_sub_title(HWND property_handle,
                                        int32_t index,
                                        std::string &text,
                                        helper::CodePage code_page) {
        PropSheet_SetHeaderSubTitle(
                property_handle, index,
                helper::convert::str_to_wstr(text, code_page).data());
    }

    void property::set_header_sub_title(HWND property_handle,
                                        int32_t index,
                                        std::wstring &text) {
        PropSheet_SetHeaderSubTitle(property_handle, index, text.data());
    }


    void property::set_header_title(HWND property_handle,
                                    int32_t index,
                                    std::string &text,
                                    helper::CodePage code_page) {
        PropSheet_SetHeaderTitle(property_handle, index,
                                 helper::convert::str_to_wstr(text, code_page)
                                         .data());
    }

    void property::set_header_title(HWND property_handle,
                                    int32_t index,
                                    std::wstring &text) {
        PropSheet_SetHeaderTitle(property_handle, index, text.data());
    }

    void property::set_title(HWND property_handle,
                             PropertyHeaderFlag flag,
                             std::string &text,
                             helper::CodePage code_page) {
        PropSheet_SetTitle(property_handle, static_cast<uint32_t>(flag),
                           helper::convert::str_to_wstr(text, code_page)
                                   .data());
    }
    void property::set_title(HWND property_handle,
                             PropertyHeaderFlag flag,
                             std::wstring &text) {
        PropSheet_SetTitle(property_handle, static_cast<uint32_t>(flag),
                           text.data());
    }

    void property::set_wiz_buttons(HWND property_handle,
                                   PropertyButton button) {
        PropSheet_SetWizButtons(property_handle, static_cast<uint32_t>(button));
    }

    void property::enable_wiz_buttons(HWND property_handle,
                                      PropertyButton button,
                                      PropertyButton mask) {
        PropSheet_EnableWizButtons(property_handle,
                                   static_cast<uint32_t>(button),
                                   static_cast<uint32_t>(mask));
    }

    void property::show_wiz_buttons(HWND property_handle,
                                    PropertyButton button,
                                    PropertyButton mask) {
        PropSheet_ShowWizButtons(property_handle, static_cast<uint32_t>(button),
                                 static_cast<uint32_t>(mask));
    }

    bool property::apply(HWND property_handle) {
        return PropSheet_Apply(property_handle);
    }

    void property::cancel_to_close(HWND property_handle) {
        PropSheet_CancelToClose(property_handle);
    }

    bool property::is_dialog_message(HWND property_handle, MSG *message) {
        return PropSheet_IsDialogMessage(property_handle, message);
    }

    void property::press_button(HWND property_handle, PropertyButton button) {
        PropSheet_PressButton(property_handle, static_cast<uint32_t>(button));
    }

    bool property::query_siblings(HWND property_handle,
                                  WPARAM wparam,
                                  LPARAM lparam) {
        return PropSheet_QuerySiblings(property_handle, wparam, lparam);
    }

    void property::reboot_system(HWND property_handle) {
        PropSheet_RebootSystem(property_handle);
    }

    void property::restart_windows(HWND property_handle) {
        PropSheet_RestartWindows(property_handle);
    }

    bool property::recalc_page_sizes(HWND property_handle) {
        return PropSheet_RecalcPageSizes(property_handle);
    }
} // namespace YanLib::ui::components
