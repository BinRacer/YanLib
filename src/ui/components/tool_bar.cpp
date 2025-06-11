/* clang-format off */
/*
 * @file tool_bar.cpp
 * @date 2025-06-01
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
#include "tool_bar.h"
#include <windowsx.h>

namespace YanLib::ui::components {
    tool_bar::tool_bar() {
        INITCOMMONCONTROLSEX icc = {};
        icc.dwSize = sizeof(INITCOMMONCONTROLSEX);
        icc.dwICC = ICC_BAR_CLASSES;
        InitCommonControlsEx(&icc);
    }

    tool_bar::~tool_bar() {
        for (auto &handle : tool_bar_handles) {
            if (handle && IsWindow(handle)) {
                DestroyWindow(handle);
                handle = nullptr;
            }
        }
        tool_bar_handles.clear();
    }

    HWND tool_bar::create(HWND parent_window_handle,
                          LPARAM lparam,
                          int32_t x,
                          int32_t y,
                          int32_t width,
                          int32_t height,
                          ToolBarStyle style,
                          WindowStyle window_style) {
        HWND result = CreateWindowExW(
                0L, L"ToolbarWindow32", nullptr,
                static_cast<uint32_t>(window_style) |
                        static_cast<uint32_t>(style),
                x, y, width, height, parent_window_handle, nullptr,
                reinterpret_cast<CREATESTRUCT *>(lparam)->hInstance, nullptr);
        if (!result) {
            error_code = GetLastError();
            return nullptr;
        }
        tool_bar_rwlock.write_lock();
        tool_bar_handles.push_back(result);
        tool_bar_rwlock.write_unlock();
        return result;
    }

    HWND tool_bar::create(const char *tool_bar_name,
                          HWND parent_window_handle,
                          LPARAM lparam,
                          int32_t x,
                          int32_t y,
                          int32_t width,
                          int32_t height,
                          ToolBarStyle style,
                          WindowStyle window_style) {
        HWND result = CreateWindowExA(
                0L, "ToolbarWindow32", tool_bar_name,
                static_cast<uint32_t>(window_style) |
                        static_cast<uint32_t>(style),
                x, y, width, height, parent_window_handle, nullptr,
                reinterpret_cast<CREATESTRUCT *>(lparam)->hInstance, nullptr);
        if (!result) {
            error_code = GetLastError();
            return nullptr;
        }
        tool_bar_rwlock.write_lock();
        tool_bar_handles.push_back(result);
        tool_bar_rwlock.write_unlock();
        return result;
    }

    HWND tool_bar::create(const wchar_t *tool_bar_name,
                          HWND parent_window_handle,
                          LPARAM lparam,
                          int32_t x,
                          int32_t y,
                          int32_t width,
                          int32_t height,
                          ToolBarStyle style,
                          WindowStyle window_style) {
        HWND result = CreateWindowExW(
                0L, L"ToolbarWindow32", tool_bar_name,
                static_cast<uint32_t>(window_style) |
                        static_cast<uint32_t>(style),
                x, y, width, height, parent_window_handle, nullptr,
                reinterpret_cast<CREATESTRUCT *>(lparam)->hInstance, nullptr);
        if (!result) {
            error_code = GetLastError();
            return nullptr;
        }
        tool_bar_rwlock.write_lock();
        tool_bar_handles.push_back(result);
        tool_bar_rwlock.write_unlock();
        return result;
    }

    bool tool_bar::destroy(HWND tool_bar_handle) {
        if (!tool_bar_handle || !IsWindow(tool_bar_handle)) {
            return false;
        }
        tool_bar_rwlock.write_lock();
        const auto it = std::find(tool_bar_handles.begin(),
                                  tool_bar_handles.end(), tool_bar_handle);
        if (it != tool_bar_handles.end()) {
            *it = nullptr;
        }
        tool_bar_rwlock.write_unlock();
        if (!DestroyWindow(tool_bar_handle)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    HBITMAP tool_bar::create_mapped_bitmap(HINSTANCE instance_handle,
                                           intptr_t bitmap_id,
                                           std::vector<COLORMAP> &color_map,
                                           bool use_mask) {
        HBITMAP result =
                CreateMappedBitmap(instance_handle, bitmap_id,
                                   use_mask ? CMB_MASKED : 0, color_map.data(),
                                   static_cast<int32_t>(color_map.size()));
        if (!result) {
            error_code = GetLastError();
        }
        return result;
    }

    bool tool_bar::is_anchor_highlight(HWND tool_bar_handle) {
        return SendMessageW(tool_bar_handle, TB_GETANCHORHIGHLIGHT, 0, 0);
    }

    void tool_bar::enable_anchor_highlight(HWND tool_bar_handle) {
        SendMessageW(tool_bar_handle, TB_SETANCHORHIGHLIGHT, TRUE, 0);
    }

    void tool_bar::disable_anchor_highlight(HWND tool_bar_handle) {
        SendMessageW(tool_bar_handle, TB_SETANCHORHIGHLIGHT, FALSE, 0);
    }

    bool tool_bar::get_color_scheme(HWND tool_bar_handle,
                                    COLORSCHEME *color_scheme) {
        return SendMessageW(tool_bar_handle, TB_GETCOLORSCHEME, 0,
                            reinterpret_cast<LPARAM>(color_scheme));
    }

    void tool_bar::set_color_scheme(HWND tool_bar_handle,
                                    COLORSCHEME *color_scheme) {
        SendMessageW(tool_bar_handle, TB_SETCOLORSCHEME, 0,
                     reinterpret_cast<LPARAM>(color_scheme));
    }

    HIMAGELIST tool_bar::get_disabled_image_list(HWND tool_bar_handle) {
        return reinterpret_cast<HIMAGELIST>(
                SendMessageW(tool_bar_handle, TB_GETDISABLEDIMAGELIST, 0, 0));
    }

    HIMAGELIST tool_bar::set_disabled_image_list(HWND tool_bar_handle,
                                                 HIMAGELIST image_list_handle) {
        return reinterpret_cast<HIMAGELIST>(
                SendMessageW(tool_bar_handle, TB_SETDISABLEDIMAGELIST, 0,
                             reinterpret_cast<LPARAM>(image_list_handle)));
    }

    HIMAGELIST tool_bar::get_hot_image_list(HWND tool_bar_handle) {
        return reinterpret_cast<HIMAGELIST>(
                SendMessageW(tool_bar_handle, TB_GETHOTIMAGELIST, 0, 0));
    }

    HIMAGELIST tool_bar::set_hot_image_list(HWND tool_bar_handle,
                                            HIMAGELIST image_list_handle) {
        return reinterpret_cast<HIMAGELIST>(
                SendMessageW(tool_bar_handle, TB_SETHOTIMAGELIST, 0,
                             reinterpret_cast<LPARAM>(image_list_handle)));
    }

    HIMAGELIST tool_bar::get_image_list(HWND tool_bar_handle) {
        return reinterpret_cast<HIMAGELIST>(
                SendMessageW(tool_bar_handle, TB_GETIMAGELIST, 0, 0));
    }

    HIMAGELIST tool_bar::set_image_list(HWND tool_bar_handle,
                                        int64_t index,
                                        HIMAGELIST image_list_handle) {
        return reinterpret_cast<HIMAGELIST>(
                SendMessageW(tool_bar_handle, TB_SETIMAGELIST, index,
                             reinterpret_cast<LPARAM>(image_list_handle)));
    }

    HIMAGELIST tool_bar::remove_image_list(HWND tool_bar_handle,
                                           int64_t index) {
        return reinterpret_cast<HIMAGELIST>(
                SendMessageW(tool_bar_handle, TB_SETIMAGELIST, index, 0));
    }

    HIMAGELIST tool_bar::get_pressed_image_list(HWND tool_bar_handle) {
        return reinterpret_cast<HIMAGELIST>(
                SendMessageW(tool_bar_handle, TB_GETPRESSEDIMAGELIST, 0, 0));
    }

    HIMAGELIST tool_bar::set_pressed_image_list(HWND tool_bar_handle,
                                                int64_t index,
                                                HIMAGELIST image_list_handle) {
        return reinterpret_cast<HIMAGELIST>(
                SendMessageW(tool_bar_handle, TB_SETPRESSEDIMAGELIST, index,
                             reinterpret_cast<LPARAM>(image_list_handle)));
    }

    HIMAGELIST tool_bar::remove_pressed_image_list(HWND tool_bar_handle,
                                                   int64_t index) {
        return reinterpret_cast<HIMAGELIST>(SendMessageW(tool_bar_handle,
                                                         TB_SETPRESSEDIMAGELIST,
                                                         index, 0));
    }

    int64_t tool_bar::get_image_list_count(HWND tool_bar_handle) {
        return SendMessageW(tool_bar_handle, TB_GETIMAGELISTCOUNT, 0, 0);
    }

    int64_t tool_bar::load_images(HWND tool_bar_handle, TBImageListID id) {
        return SendMessageW(tool_bar_handle, TB_LOADIMAGES,
                            static_cast<uint32_t>(id),
                            reinterpret_cast<LPARAM>(HINST_COMMCTRL));
    }

    ToolBarExtendStyle tool_bar::get_extend_style(HWND tool_bar_handle) {
        return static_cast<ToolBarExtendStyle>(
                SendMessageW(tool_bar_handle, TB_GETEXTENDEDSTYLE, 0, 0));
    }

    ToolBarExtendStyle tool_bar::set_extend_style(HWND tool_bar_handle,
                                                  ToolBarExtendStyle style) {
        return static_cast<ToolBarExtendStyle>(
                SendMessageW(tool_bar_handle, TB_SETEXTENDEDSTYLE, 0,
                             static_cast<uint32_t>(style)));
    }

    int64_t tool_bar::get_hot_item(HWND tool_bar_handle) {
        return SendMessageW(tool_bar_handle, TB_GETHOTITEM, 0, 0);
    }

    int64_t tool_bar::set_hot_item(HWND tool_bar_handle, int64_t index) {
        return SendMessageW(tool_bar_handle, TB_SETHOTITEM, index, 0);
    }

    int64_t tool_bar::set_hot_item(HWND tool_bar_handle,
                                   int64_t index,
                                   TBHotItemFlag flag) {
        return SendMessageW(tool_bar_handle, TB_SETHOTITEM2, index,
                            static_cast<uint32_t>(flag));
    }

    int64_t tool_bar::add_bitmap(HWND tool_bar_handle,
                                 int64_t image_num,
                                 TBADDBITMAP *bitmap) {
        return SendMessageW(tool_bar_handle, TB_ADDBITMAP, image_num,
                            reinterpret_cast<LPARAM>(bitmap));
    }

    bool tool_bar::change_bitmap(HWND tool_bar_handle,
                                 int64_t index,
                                 int64_t bitmap_id) {
        return SendMessageW(tool_bar_handle, TB_CHANGEBITMAP, bitmap_id, index);
    }

    bool tool_bar::replace_bitmap(HWND tool_bar_handle,
                                  TBREPLACEBITMAP *bitmap) {
        return SendMessageW(tool_bar_handle, TB_REPLACEBITMAP, 0,
                            reinterpret_cast<LPARAM>(bitmap));
    }

    bool tool_bar::set_bitmap_size(HWND tool_bar_handle,
                                   int32_t width,
                                   int32_t height) {
        return SendMessageW(tool_bar_handle, TB_SETBITMAPSIZE, 0,
                            MAKELPARAM(width, height));
    }

    bool tool_bar::set_bitmap_size(HWND tool_bar_handle, SIZE size) {
        return SendMessageW(tool_bar_handle, TB_SETBITMAPSIZE, 0,
                            MAKELPARAM(size.cx, size.cy));
    }

    int64_t tool_bar::get_bitmap_index(HWND tool_bar_handle,
                                       int64_t bitmap_id) {
        return SendMessageW(tool_bar_handle, TB_GETBITMAP, bitmap_id, 0);
    }

    bool tool_bar::support_large_bitmap(HWND tool_bar_handle) {
        return SendMessageW(tool_bar_handle, TB_GETBITMAPFLAGS, 0, 0) &
                TBBF_LARGE;
    }

    bool tool_bar::add_button(HWND tool_bar_handle,
                              std::vector<TBBUTTON> &buttons) {
        return SendMessageW(tool_bar_handle, TB_ADDBUTTONS, buttons.size(),
                            reinterpret_cast<LPARAM>(buttons.data()));
    }

    bool tool_bar::insert_button(HWND tool_bar_handle,
                                 int64_t index,
                                 TBBUTTON *button) {
        return SendMessageW(tool_bar_handle, TB_INSERTBUTTON, index,
                            reinterpret_cast<LPARAM>(button));
    }

    bool tool_bar::delete_button(HWND tool_bar_handle, int64_t index) {
        return SendMessageW(tool_bar_handle, TB_DELETEBUTTON, index, 0);
    }

    bool tool_bar::move_button(HWND tool_bar_handle,
                               int64_t index_from,
                               int64_t index_to) {
        return SendMessageW(tool_bar_handle, TB_MOVEBUTTON, index_from,
                            index_to);
    }

    int64_t tool_bar::get_button_count(HWND tool_bar_handle) {
        return SendMessageW(tool_bar_handle, TB_BUTTONCOUNT, 0, 0);
    }

    int64_t tool_bar::get_button_info(HWND tool_bar_handle,
                                      int64_t button_id,
                                      TBBUTTONINFOA *button_info) {
        return SendMessageW(tool_bar_handle, TB_GETBUTTONINFOA, button_id,
                            reinterpret_cast<LPARAM>(button_info));
    }

    int64_t tool_bar::get_button_info(HWND tool_bar_handle,
                                      int64_t button_id,
                                      TBBUTTONINFOW *button_info) {
        return SendMessageW(tool_bar_handle, TB_GETBUTTONINFOW, button_id,
                            reinterpret_cast<LPARAM>(button_info));
    }

    bool tool_bar::set_button_info(HWND tool_bar_handle,
                                   int64_t button_id,
                                   TBBUTTONINFOA *button_info) {
        return SendMessageW(tool_bar_handle, TB_SETBUTTONINFOA, button_id,
                            reinterpret_cast<LPARAM>(button_info));
    }

    bool tool_bar::set_button_info(HWND tool_bar_handle,
                                   int64_t button_id,
                                   TBBUTTONINFOW *button_info) {
        return SendMessageW(tool_bar_handle, TB_SETBUTTONINFOW, button_id,
                            reinterpret_cast<LPARAM>(button_info));
    }

    bool tool_bar::get_button(HWND tool_bar_handle,
                              int64_t index,
                              TBBUTTON *button) {
        return SendMessageW(tool_bar_handle, TB_GETBUTTON, index,
                            reinterpret_cast<LPARAM>(button));
    }

    int64_t tool_bar::get_button_text(HWND tool_bar_handle,
                                      int64_t button_id,
                                      std::string &button_text,
                                      helper::CodePage code_page) {
        std::wstring temp(button_text.size(), L'\0');
        SendMessageW(tool_bar_handle, TB_GETBUTTONTEXT, button_id,
                     reinterpret_cast<LPARAM>(temp.data()));
        button_text.clear();
        button_text = helper::convert::wstr_to_str(temp, code_page);
        return static_cast<int64_t>(button_text.size());
    }

    int64_t tool_bar::get_button_text(HWND tool_bar_handle,
                                      int64_t button_id,
                                      std::wstring &button_text) {
        return SendMessageW(tool_bar_handle, TB_GETBUTTONTEXT, button_id,
                            reinterpret_cast<LPARAM>(button_text.data()));
    }

    std::pair<uint32_t, uint32_t>
    tool_bar::get_button_size(HWND tool_bar_handle) {
        const auto result = static_cast<uint32_t>(
                SendMessageW(tool_bar_handle, TB_GETBUTTONSIZE, 0, 0));
        return std::make_pair(LOWORD(result), HIWORD(result));
    }

    bool tool_bar::get_button_size(HWND tool_bar_handle, SIZE *size) {
        if (!size) {
            return false;
        }
        const auto result = static_cast<uint32_t>(
                SendMessageW(tool_bar_handle, TB_GETBUTTONSIZE, 0, 0));
        size->cx = LOWORD(result);
        size->cy = HIWORD(result);
        return true;
    }

    bool tool_bar::set_button_size(HWND tool_bar_handle,
                                   uint32_t width,
                                   uint32_t height) {
        return SendMessageW(tool_bar_handle, TB_SETBUTTONSIZE, 0,
                            MAKELPARAM(width, height));
    }

    bool tool_bar::set_button_size(HWND tool_bar_handle, SIZE size) {
        return SendMessageW(tool_bar_handle, TB_SETBUTTONSIZE, 0,
                            MAKELPARAM(size.cx, size.cy));
    }

    bool tool_bar::set_button_width(HWND tool_bar_handle,
                                    uint32_t min,
                                    uint32_t max) {
        return SendMessageW(tool_bar_handle, TB_SETBUTTONWIDTH, 0,
                            MAKELPARAM(min, max));
    }

    bool tool_bar::check_button(HWND tool_bar_handle, int64_t button_id) {
        return SendMessageW(tool_bar_handle, TB_CHECKBUTTON, button_id, TRUE);
    }

    bool tool_bar::uncheck_button(HWND tool_bar_handle, int64_t button_id) {
        return SendMessageW(tool_bar_handle, TB_CHECKBUTTON, button_id, FALSE);
    }

    bool tool_bar::enable_button(HWND tool_bar_handle, int64_t button_id) {
        return SendMessageW(tool_bar_handle, TB_ENABLEBUTTON, button_id, TRUE);
    }

    bool tool_bar::disable_button(HWND tool_bar_handle, int64_t button_id) {
        return SendMessageW(tool_bar_handle, TB_ENABLEBUTTON, button_id, FALSE);
    }

    bool tool_bar::show_button(HWND tool_bar_handle, int64_t button_id) {
        return SendMessageW(tool_bar_handle, TB_HIDEBUTTON, button_id, FALSE);
    }

    bool tool_bar::hide_button(HWND tool_bar_handle, int64_t button_id) {
        return SendMessageW(tool_bar_handle, TB_HIDEBUTTON, button_id, TRUE);
    }

    bool tool_bar::mark_button(HWND tool_bar_handle, int64_t button_id) {
        return SendMessageW(tool_bar_handle, TB_MARKBUTTON, button_id, TRUE);
    }

    bool tool_bar::unmark_button(HWND tool_bar_handle, int64_t button_id) {
        return SendMessageW(tool_bar_handle, TB_MARKBUTTON, button_id, FALSE);
    }

    bool tool_bar::press_button(HWND tool_bar_handle, int64_t button_id) {
        return SendMessageW(tool_bar_handle, TB_PRESSBUTTON, button_id, TRUE);
    }

    bool tool_bar::release_button(HWND tool_bar_handle, int64_t button_id) {
        return SendMessageW(tool_bar_handle, TB_PRESSBUTTON, button_id, FALSE);
    }

    bool tool_bar::is_button_checked(HWND tool_bar_handle, int64_t button_id) {
        return SendMessageW(tool_bar_handle, TB_ISBUTTONCHECKED, button_id, 0);
    }

    bool tool_bar::is_button_enabled(HWND tool_bar_handle, int64_t button_id) {
        return SendMessageW(tool_bar_handle, TB_ISBUTTONENABLED, button_id, 0);
    }

    bool tool_bar::is_button_show(HWND tool_bar_handle, int64_t button_id) {
        return !SendMessageW(tool_bar_handle, TB_ISBUTTONHIDDEN, button_id, 0);
    }

    bool tool_bar::is_button_hidden(HWND tool_bar_handle, int64_t button_id) {
        return SendMessageW(tool_bar_handle, TB_ISBUTTONHIDDEN, button_id, 0);
    }

    bool tool_bar::is_button_highlighted(HWND tool_bar_handle,
                                         int64_t button_id) {
        return SendMessageW(tool_bar_handle, TB_ISBUTTONHIGHLIGHTED, button_id,
                            0);
    }

    bool tool_bar::is_button_indeterminate(HWND tool_bar_handle,
                                           int64_t button_id) {
        return SendMessageW(tool_bar_handle, TB_ISBUTTONINDETERMINATE,
                            button_id, 0);
    }

    bool tool_bar::is_button_pressed(HWND tool_bar_handle, int64_t button_id) {
        return SendMessageW(tool_bar_handle, TB_ISBUTTONPRESSED, button_id, 0);
    }

    void tool_bar::set_button_struct_size(HWND tool_bar_handle, int64_t size) {
        SendMessageW(tool_bar_handle, TB_BUTTONSTRUCTSIZE, size, 0);
    }

    bool tool_bar::get_ideal_size(HWND tool_bar_handle, SIZE *size) {
        bool is_ok = SendMessageW(tool_bar_handle, TB_GETIDEALSIZE, TRUE,
                                  reinterpret_cast<LPARAM>(size));
        if (!is_ok) {
            return false;
        }
        is_ok = SendMessageW(tool_bar_handle, TB_GETIDEALSIZE, FALSE,
                             reinterpret_cast<LPARAM>(size));
        return is_ok;
    }

    int64_t tool_bar::command_to_index(HWND tool_bar_handle,
                                       int64_t command_id) {
        return SendMessageW(tool_bar_handle, TB_COMMANDTOINDEX, command_id, 0);
    }

    bool tool_bar::get_max_size(HWND tool_bar_handle, SIZE *size) {
        return SendMessageW(tool_bar_handle, TB_GETMAXSIZE, 0,
                            reinterpret_cast<LPARAM>(size));
    }

    TBButtonState tool_bar::get_button_state(HWND tool_bar_handle,
                                             int64_t index) {
        return static_cast<TBButtonState>(
                SendMessageW(tool_bar_handle, TB_GETSTATE, index, 0));
    }

    bool tool_bar::set_button_state(HWND tool_bar_handle,
                                    int64_t button_id,
                                    TBButtonState state) {
        return SendMessageW(tool_bar_handle, TB_SETSTATE, button_id,
                            static_cast<int32_t>(state));
    }

    bool tool_bar::set_indeterminate(HWND tool_bar_handle, int64_t button_id) {
        return SendMessageW(tool_bar_handle, TB_INDETERMINATE, button_id, TRUE);
    }

    bool tool_bar::clear_indeterminate(HWND tool_bar_handle,
                                       int64_t button_id) {
        return SendMessageW(tool_bar_handle, TB_INDETERMINATE, button_id,
                            FALSE);
    }

    void tool_bar::get_insert_mark(HWND tool_bar_handle,
                                   TBINSERTMARK *insert_mark) {
        SendMessageW(tool_bar_handle, TB_GETINSERTMARK, 0,
                     reinterpret_cast<LPARAM>(insert_mark));
    }

    void tool_bar::set_insert_mark(HWND tool_bar_handle,
                                   TBINSERTMARK *insert_mark) {
        SendMessageW(tool_bar_handle, TB_SETINSERTMARK, 0,
                     reinterpret_cast<LPARAM>(insert_mark));
    }

    COLORREF tool_bar::get_insert_mark_color(HWND tool_bar_handle) {
        return SendMessageW(tool_bar_handle, TB_GETINSERTMARKCOLOR, 0, 0);
    }

    COLORREF tool_bar::set_insert_mark_color(HWND tool_bar_handle,
                                             COLORREF color) {
        return SendMessageW(tool_bar_handle, TB_SETINSERTMARKCOLOR, 0, color);
    }

    bool tool_bar::insert_mark_hit_test(HWND tool_bar_handle,
                                        POINT *point,
                                        TBINSERTMARK *insert_mark) {
        return SendMessageW(tool_bar_handle, TB_INSERTMARKHITTEST,
                            reinterpret_cast<WPARAM>(point),
                            reinterpret_cast<LPARAM>(insert_mark));
    }

    void tool_bar::get_item_drop_down_rect(HWND tool_bar_handle,
                                           int64_t index,
                                           RECT *rect) {
        SendMessageW(tool_bar_handle, TB_GETITEMDROPDOWNRECT, index,
                     reinterpret_cast<LPARAM>(rect));
    }

    bool
    tool_bar::get_item_rect(HWND tool_bar_handle, int64_t index, RECT *rect) {
        return SendMessageW(tool_bar_handle, TB_GETITEMRECT, index,
                            reinterpret_cast<LPARAM>(rect));
    }

    bool tool_bar::get_button_rect(HWND tool_bar_handle,
                                   int64_t button_id,
                                   RECT *rect) {
        return SendMessageW(tool_bar_handle, TB_GETRECT, button_id,
                            reinterpret_cast<LPARAM>(rect));
    }

    void tool_bar::get_metrics(HWND tool_bar_handle, TBMETRICS *metrics) {
        SendMessageW(tool_bar_handle, TB_GETMETRICS, 0,
                     reinterpret_cast<LPARAM>(metrics));
    }

    void tool_bar::set_metrics(HWND tool_bar_handle, TBMETRICS *metrics) {
        SendMessageW(tool_bar_handle, TB_SETMETRICS, 0,
                     reinterpret_cast<LPARAM>(metrics));
    }

    std::pair<uint32_t, uint32_t> tool_bar::get_padding(HWND tool_bar_handle) {
        const auto result = static_cast<uint32_t>(
                SendMessageW(tool_bar_handle, TB_GETPADDING, 0, 0));
        return std::make_pair(LOWORD(result), HIWORD(result));
    }

    void
    tool_bar::set_padding(HWND tool_bar_handle, uint32_t horiz, uint32_t vert) {
        SendMessageW(tool_bar_handle, TB_SETPADDING, 0,
                     MAKELPARAM(horiz, vert));
    }

    int64_t tool_bar::get_rows(HWND tool_bar_handle) {
        return SendMessageW(tool_bar_handle, TB_GETROWS, 0, 0);
    }

    void tool_bar::set_rows(HWND tool_bar_handle,
                            uint32_t count,
                            RECT *rect,
                            bool more_rows) {
        SendMessageW(tool_bar_handle, TB_SETROWS,
                     MAKEWPARAM(count, more_rows ? TRUE : FALSE),
                     reinterpret_cast<LPARAM>(rect));
    }

    int64_t tool_bar::get_text_rows(HWND tool_bar_handle) {
        return SendMessageW(tool_bar_handle, TB_GETTEXTROWS, 0, 0);
    }

    bool tool_bar::set_text_rows(HWND tool_bar_handle, int64_t count) {
        return SendMessageW(tool_bar_handle, TB_SETMAXTEXTROWS, count, 0);
    }

    int64_t tool_bar::add_string(HWND tool_bar_handle,
                                 HINSTANCE instance_handle,
                                 int64_t res_id) {
        return SendMessageW(tool_bar_handle, TB_ADDSTRING,
                            reinterpret_cast<WPARAM>(instance_handle), res_id);
    }

    int64_t tool_bar::add_string(HWND tool_bar_handle, wchar_t res_str[]) {
        return SendMessageW(tool_bar_handle, TB_ADDSTRING, 0,
                            reinterpret_cast<LPARAM>(res_str));
    }

    int64_t tool_bar::get_string(HWND tool_bar_handle,
                                 int64_t index,
                                 std::string &str,
                                 helper::CodePage code_page) {
        std::wstring temp(str.size(), L'\0');
        SendMessageW(tool_bar_handle, TB_GETSTRING,
                     MAKEWPARAM(temp.size(), index),
                     reinterpret_cast<LPARAM>(temp.data()));
        str.clear();
        str = helper::convert::wstr_to_str(temp, code_page);
        return static_cast<int64_t>(temp.size());
    }

    int64_t tool_bar::get_string(HWND tool_bar_handle,
                                 int64_t index,
                                 std::wstring &str) {
        return SendMessageW(tool_bar_handle, TB_GETSTRING,
                            MAKEWPARAM(str.size(), index),
                            reinterpret_cast<LPARAM>(str.data()));
    }

    ToolBarStyle tool_bar::get_style(HWND tool_bar_handle) {
        return static_cast<ToolBarStyle>(
                SendMessageW(tool_bar_handle, TB_GETSTYLE, 0, 0));
    }

    void tool_bar::set_style(HWND tool_bar_handle, ToolBarStyle style) {
        SendMessageW(tool_bar_handle, TB_SETSTYLE, 0,
                     static_cast<uint32_t>(style));
    }

    HWND tool_bar::get_tool_tips(HWND tool_bar_handle) {
        return reinterpret_cast<HWND>(
                SendMessageW(tool_bar_handle, TB_GETTOOLTIPS, 0, 0));
    }

    void tool_bar::set_tool_tips(HWND tool_bar_handle, HWND tool_tips_handle) {
        SendMessageW(tool_bar_handle, TB_SETTOOLTIPS,
                     reinterpret_cast<WPARAM>(tool_tips_handle), 0);
    }

    bool tool_bar::is_ansi_format(HWND tool_bar_handle) {
        return !SendMessageW(tool_bar_handle, TB_GETUNICODEFORMAT, 0, 0);
    }

    bool tool_bar::is_unicode_format(HWND tool_bar_handle) {
        return SendMessageW(tool_bar_handle, TB_GETUNICODEFORMAT, 0, 0);
    }

    void tool_bar::set_ansi_format(HWND tool_bar_handle) {
        SendMessageW(tool_bar_handle, TB_SETUNICODEFORMAT, FALSE, 0);
    }

    void tool_bar::set_unicode_format(HWND tool_bar_handle) {
        SendMessageW(tool_bar_handle, TB_SETUNICODEFORMAT, TRUE, 0);
    }

    void tool_bar::set_bounding_size(HWND tool_bar_handle, SIZE *size) {
        SendMessageW(tool_bar_handle, TB_SETBOUNDINGSIZE, 0,
                     reinterpret_cast<LPARAM>(size));
    }

    bool tool_bar::set_command_id(HWND tool_bar_handle,
                                  int64_t index,
                                  int64_t command_id) {
        return SendMessageW(tool_bar_handle, TB_SETCMDID, index, command_id);
    }

    TextFormat tool_bar::set_draw_text_flag(HWND tool_bar_handle,
                                            TextFormat format,
                                            TextFormat mask) {
        return static_cast<TextFormat>(
                SendMessageW(tool_bar_handle, TB_SETDRAWTEXTFLAGS,
                             static_cast<uint32_t>(mask),
                             static_cast<uint32_t>(format)));
    }

    bool tool_bar::set_indent(HWND tool_bar_handle, int64_t size) {
        return SendMessageW(tool_bar_handle, TB_SETINDENT, size, 0);
    }

    void tool_bar::set_list_gap(HWND tool_bar_handle, int64_t gap_size) {
        SendMessageW(tool_bar_handle, TB_SETLISTGAP, gap_size, 0);
    }

    HWND tool_bar::set_parent(HWND tool_bar_handle, HWND parent_window_handle) {
        return reinterpret_cast<HWND>(
                SendMessageW(tool_bar_handle, TB_SETPARENT,
                             reinterpret_cast<WPARAM>(parent_window_handle),
                             0));
    }

    void tool_bar::set_window_theme(HWND tool_bar_handle,
                                    std::string &window_theme,
                                    helper::CodePage code_page) {
        auto temp = helper::convert::str_to_wstr(window_theme, code_page);
        SendMessageW(tool_bar_handle, TB_SETWINDOWTHEME, 0,
                     reinterpret_cast<LPARAM>(temp.data()));
    }

    void tool_bar::set_window_theme(HWND tool_bar_handle,
                                    std::wstring &window_theme) {
        SendMessageW(tool_bar_handle, TB_SETWINDOWTHEME, 0,
                     reinterpret_cast<LPARAM>(window_theme.data()));
    }

    void tool_bar::auto_size(HWND tool_bar_handle) {
        SendMessageW(tool_bar_handle, TB_AUTOSIZE, 0, 0);
    }

    void tool_bar::show_customize_dialog(HWND tool_bar_handle) {
        SendMessageW(tool_bar_handle, TB_CUSTOMIZE, 0, 0);
    }

    bool tool_bar::has_accelerator(HWND tool_bar_handle, wchar_t accel) {
        int64_t result = 0;
        SendMessageW(tool_bar_handle, TB_HASACCELERATOR, accel,
                     reinterpret_cast<LPARAM>(&result));
        return result;
    }

    int64_t tool_bar::hit_test(HWND tool_bar_handle, POINT *point) {
        return SendMessageW(tool_bar_handle, TB_HITTEST, 0,
                            reinterpret_cast<LPARAM>(point));
    }

    bool tool_bar::map_accelerator(HWND tool_bar_handle,
                                   wchar_t accel,
                                   uint32_t *button_id) {
        return SendMessageW(tool_bar_handle, TB_MAPACCELERATOR, accel,
                            reinterpret_cast<LPARAM>(button_id));
    }

    void tool_bar::save(HWND tool_bar_handle, TBSAVEPARAMSW *param) {
        SendMessageW(tool_bar_handle, TB_SAVERESTORE, TRUE,
                     reinterpret_cast<LPARAM>(param));
    }

    void tool_bar::restore(HWND tool_bar_handle, TBSAVEPARAMSW *param) {
        SendMessageW(tool_bar_handle, TB_SAVERESTORE, FALSE,
                     reinterpret_cast<LPARAM>(param));
    }

    bool tool_bar::get_object(HWND tool_bar_handle, IDropTarget **target) {
        return SendMessageW(tool_bar_handle, TB_GETOBJECT,
                            reinterpret_cast<WPARAM>(&IID_IDropTarget),
                            reinterpret_cast<LPARAM>(target)) == S_OK;
    }

    uint32_t tool_bar::err_code() const {
        return error_code;
    }

    std::string tool_bar::err_string() const {
        std::string result = helper::convert::err_string(error_code);
        return result;
    }

    std::wstring tool_bar::err_wstring() const {
        std::wstring result = helper::convert::err_wstring(error_code);
        return result;
    }
} // namespace YanLib::ui::components
