/* clang-format off */
/*
 * @file property.h
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
#ifndef PROPERTY_H
#define PROPERTY_H
#ifndef UNICODE
#define UNICODE
#endif
#ifndef _UNICODE
#define _UNICODE
#endif
#include <Windows.h>
#include <CommCtrl.h>
#include <commoncontrols.h>
#include <WinUser.h>
#include <minwindef.h>
#include <windef.h>
#include <prsht.h>
#include <cstdint>
#include <string>
#include <vector>
#include "helper/convert.h"
#include "components.h"
#pragma comment(lib, "ComCtl32.Lib")
#pragma comment(linker, "\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#pragma comment(lib, "User32.Lib")
namespace YanLib::ui::components {
    class property {
    public:
        property(const property &other) = delete;

        property(property &&other) = delete;

        property &operator=(const property &other) = delete;

        property &operator=(property &&other) = delete;

        property() = default;

        ~property() = default;


        static PROPSHEETHEADERA make_header(
                const char *caption /* L"系统设置" */,
                HWND parent_window_handle,
                HINSTANCE instance_handle,
                std::vector<PROPSHEETPAGEA> &prop_sheet_page,
                PFNPROPSHEETCALLBACK callback = nullptr,
                PropertyHeaderFlag flag = PropertyHeaderFlag::PropSheetPage |
                        PropertyHeaderFlag::NoApplyNow,
                HICON icon_handle = nullptr,
                HBITMAP water_mark_handle = nullptr,
                HPALETTE palette_handle = nullptr,
                HBITMAP header_handle = nullptr);

        static PROPSHEETHEADERW make_header(
                const wchar_t *caption /* L"系统设置" */,
                HWND parent_window_handle,
                HINSTANCE instance_handle,
                std::vector<PROPSHEETPAGEW> &prop_sheet_page,
                PFNPROPSHEETCALLBACK callback = nullptr,
                PropertyHeaderFlag flag = PropertyHeaderFlag::PropSheetPage |
                        PropertyHeaderFlag::NoApplyNow,
                HICON icon_handle = nullptr,
                HBITMAP water_mark_handle = nullptr,
                HPALETTE palette_handle = nullptr,
                HBITMAP header_handle = nullptr);

        static HWND create(PROPSHEETHEADERA *header);

        static HWND create(PROPSHEETHEADERW *header);

        static PROPSHEETPAGEA
        make_page(const char *title,
                  HINSTANCE instance_handle,
                  const char *templates,
                  DLGPROC dialog_func,
                  LPARAM dialog_param = 0,
                  LPFNPSPCALLBACKA callback = nullptr,
                  PropertyPageFlag flag = PropertyPageFlag::UseTitle,
                  const char *header_title = nullptr,
                  const char *header_subtitle = nullptr,
                  HICON icon_handle = nullptr,
                  HBITMAP header_handle = nullptr,
                  uint32_t *ref_parent = nullptr,
                  HANDLE active_context_handle = nullptr);

        static PROPSHEETPAGEW
        make_page(const wchar_t *title,
                  HINSTANCE instance_handle,
                  const wchar_t *templates,
                  DLGPROC dialog_func,
                  LPARAM dialog_param = 0,
                  LPFNPSPCALLBACKW callback = nullptr,
                  PropertyPageFlag flag = PropertyPageFlag::UseTitle,
                  const wchar_t *header_title = nullptr,
                  const wchar_t *header_subtitle = nullptr,
                  HICON icon_handle = nullptr,
                  HBITMAP header_handle = nullptr,
                  uint32_t *ref_parent = nullptr,
                  HANDLE active_context_handle = nullptr);

        static HPROPSHEETPAGE create_page(PROPSHEETPAGEA *page);

        static HPROPSHEETPAGE create_page(PROPSHEETPAGEW *page);

        static bool destroy_page(HPROPSHEETPAGE page_handle);

        static bool add_page(HWND property_handle, HPROPSHEETPAGE page_handle);

        static bool insert_page(HWND property_handle,
                                int32_t index,
                                HPROPSHEETPAGE page_handle);

        static void remove_page(HWND property_handle,
                                int32_t index,
                                HPROPSHEETPAGE page_handle);

        static void change_page(HWND property_handle,
                                HPROPSHEETPAGE page_handle);

        static void unchange_page(HWND property_handle,
                                  HPROPSHEETPAGE page_handle);

        static int32_t get_page_index(HWND property_handle,
                                      HPROPSHEETPAGE page_handle);

        static int32_t get_page_index2(HWND property_handle,
                                       HPROPSHEETPAGE page_handle);

        static int32_t get_page_index(HWND property_handle, int32_t res_id);

        static bool active_curr_page(HWND property_handle,
                                     HPROPSHEETPAGE page_handle,
                                     uint32_t index);

        static bool active_curr_page(HWND property_handle, int32_t res_id);

        static HPROPSHEETPAGE get_page_handle(HWND property_handle,
                                              int32_t index);

        static HPROPSHEETPAGE get_page_handle2(HWND property_handle,
                                               int32_t index);

        static int32_t get_page_res_id(HWND property_handle, int32_t index);

        static HWND get_curr_page_handle(HWND property_handle);

        static int32_t get_result(HWND property_handle);

        static HWND get_tab_control(HWND property_handle);

        static void
        set_button_text(HWND property_handle,
                        PropertyButton button,
                        std::string &text,
                        helper::CodePage code_page = helper::curr_code_page());

        static void set_button_text(HWND property_handle,
                                    PropertyButton button,
                                    std::wstring &text);

        static void set_finish_button_text(
                HWND property_handle,
                std::string &text,
                helper::CodePage code_page = helper::curr_code_page());

        static void set_finish_button_text(HWND property_handle,
                                           std::wstring &text);

        static void set_next_button_text(
                HWND property_handle,
                std::string &text,
                helper::CodePage code_page = helper::curr_code_page());

        static void set_next_button_text(HWND property_handle,
                                         std::wstring &text);

        static void set_header_sub_title(
                HWND property_handle,
                int32_t index,
                std::string &text,
                helper::CodePage code_page = helper::curr_code_page());

        static void set_header_sub_title(HWND property_handle,
                                         int32_t index,
                                         std::wstring &text);

        static void
        set_header_title(HWND property_handle,
                         int32_t index,
                         std::string &text,
                         helper::CodePage code_page = helper::curr_code_page());

        static void set_header_title(HWND property_handle,
                                     int32_t index,
                                     std::wstring &text);

        static void
        set_title(HWND property_handle,
                  PropertyHeaderFlag flag,
                  std::string &text,
                  helper::CodePage code_page = helper::curr_code_page());

        static void set_title(HWND property_handle,
                              PropertyHeaderFlag flag,
                              std::wstring &text);

        static void set_wiz_buttons(HWND property_handle,
                                    PropertyButton button);

        static void enable_wiz_buttons(HWND property_handle,
                                       PropertyButton button,
                                       PropertyButton mask);

        static void show_wiz_buttons(HWND property_handle,
                                     PropertyButton button,
                                     PropertyButton mask);

        static bool apply(HWND property_handle);

        static void cancel_to_close(HWND property_handle);

        static bool is_dialog_message(HWND property_handle, MSG *message);

        static void press_button(HWND property_handle, PropertyButton button);

        static bool
        query_siblings(HWND property_handle, WPARAM wparam, LPARAM lparam);

        static void reboot_system(HWND property_handle);

        static void restart_windows(HWND property_handle);

        static bool recalc_page_sizes(HWND property_handle);
    };
} // namespace YanLib::ui::components
#endif // PROPERTY_H
