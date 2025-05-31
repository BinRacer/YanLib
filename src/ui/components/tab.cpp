//
// Created by forkernel on 2025/5/31.
//

#include "tab.h"
#include <windowsx.h>

namespace YanLib::components {
    HWND tab::create(uintptr_t tab_id,
                     HWND parent_window_handle,
                     LPARAM lparam,
                     int32_t x,
                     int32_t y,
                     int32_t width,
                     int32_t height,
                     TabStyle style,
                     WindowStyle window_style) {
        INITCOMMONCONTROLSEX icc = {};
        icc.dwSize = sizeof(INITCOMMONCONTROLSEX);
        icc.dwICC = ICC_TAB_CLASSES;
        InitCommonControlsEx(&icc);
        HWND result = CreateWindowExW(0L, L"SysTabControl32", nullptr,
                                      static_cast<uint32_t>(window_style) |
                                              static_cast<uint32_t>(style),
                                      x, y, width, height, parent_window_handle,
                                      reinterpret_cast<HMENU>(tab_id),
                                      reinterpret_cast<CREATESTRUCT *>(lparam)
                                              ->hInstance,
                                      nullptr);
        if (!result) {
            error_code = GetLastError();
        }
        return result;
    }

    HWND tab::create(const char *tab_name,
                     uintptr_t tab_id,
                     HWND parent_window_handle,
                     LPARAM lparam,
                     int32_t x,
                     int32_t y,
                     int32_t width,
                     int32_t height,
                     TabStyle style,
                     WindowStyle window_style) {
        INITCOMMONCONTROLSEX icc = {};
        icc.dwSize = sizeof(INITCOMMONCONTROLSEX);
        icc.dwICC = ICC_TAB_CLASSES;
        InitCommonControlsEx(&icc);
        HWND result = CreateWindowExA(0L, "SysTabControl32", tab_name,
                                      static_cast<uint32_t>(window_style) |
                                              static_cast<uint32_t>(style),
                                      x, y, width, height, parent_window_handle,
                                      reinterpret_cast<HMENU>(tab_id),
                                      reinterpret_cast<CREATESTRUCT *>(lparam)
                                              ->hInstance,
                                      nullptr);
        if (!result) {
            error_code = GetLastError();
        }
        return result;
    }

    HWND tab::create(const wchar_t *tab_name,
                     uintptr_t tab_id,
                     HWND parent_window_handle,
                     LPARAM lparam,
                     int32_t x,
                     int32_t y,
                     int32_t width,
                     int32_t height,
                     TabStyle style,
                     WindowStyle window_style) {
        INITCOMMONCONTROLSEX icc = {};
        icc.dwSize = sizeof(INITCOMMONCONTROLSEX);
        icc.dwICC = ICC_TAB_CLASSES;
        InitCommonControlsEx(&icc);
        HWND result = CreateWindowExW(0L, L"SysTabControl32", tab_name,
                                      static_cast<uint32_t>(window_style) |
                                              static_cast<uint32_t>(style),
                                      x, y, width, height, parent_window_handle,
                                      reinterpret_cast<HMENU>(tab_id),
                                      reinterpret_cast<CREATESTRUCT *>(lparam)
                                              ->hInstance,
                                      nullptr);
        if (!result) {
            error_code = GetLastError();
        }
        return result;
    }

    int32_t tab::get_curr_focus(HWND tab_handle) {
        return TabCtrl_GetCurFocus(tab_handle);
    }

    void tab::set_curr_focus(HWND tab_handle, int32_t tab_index) {
        TabCtrl_SetCurFocus(tab_handle, tab_index);
    }

    int32_t tab::get_curr_select(HWND tab_handle) {
        return TabCtrl_GetCurSel(tab_handle);
    }

    int32_t tab::set_curr_select(HWND tab_handle, int32_t tab_index) {
        return TabCtrl_SetCurSel(tab_handle, tab_index);
    }

    TabExtendStyle tab::get_extend_style(HWND tab_handle) {
        return static_cast<TabExtendStyle>(
                TabCtrl_GetExtendedStyle(tab_handle));
    }

    TabExtendStyle tab::set_extend_style(HWND tab_handle,
                                         TabExtendStyle style) {
        return static_cast<TabExtendStyle>(
                TabCtrl_SetExtendedStyle(tab_handle,
                                         static_cast<uint32_t>(style)));
    }

    bool tab::is_ansi_format(HWND tab_handle) {
        return !(TabCtrl_GetUnicodeFormat(tab_handle));
    }

    bool tab::is_unicode_format(HWND tab_handle) {
        return TabCtrl_GetUnicodeFormat(tab_handle);
    }

    void tab::set_ansi_format(HWND tab_handle) {
        TabCtrl_SetUnicodeFormat(tab_handle, FALSE);
    }

    void tab::set_unicode_format(HWND tab_handle) {
        TabCtrl_SetUnicodeFormat(tab_handle, TRUE);
    }

    HIMAGELIST tab::get_image_list(HWND tab_handle) {
        return TabCtrl_GetImageList(tab_handle);
    }

    HIMAGELIST tab::set_image_list(HWND tab_handle, HIMAGELIST image_list) {
        return TabCtrl_SetImageList(tab_handle, image_list);
    }

    void tab::remove_image(HWND tab_handle, int32_t image_index) {
        TabCtrl_RemoveImage(tab_handle, image_index);
    }

    HWND tab::get_tool_tips(HWND tab_handle) {
        return TabCtrl_GetToolTips(tab_handle);
    }

    void tab::set_tool_tips(HWND tab_handle, HWND tool_tips_handle) {
        TabCtrl_SetToolTips(tab_handle, tool_tips_handle);
    }

    int32_t tab::get_item_count(HWND tab_handle) {
        return TabCtrl_GetItemCount(tab_handle);
    }

    bool tab::get_item_rect(HWND tab_handle, int32_t tab_index, RECT *rect) {
        return TabCtrl_GetItemRect(tab_handle, tab_index, rect);
    }

    bool tab::get_item(HWND tab_handle, int32_t tab_index, TCITEMW *item) {
        return TabCtrl_GetItem(tab_handle, tab_index, item);
    }

    bool tab::set_item(HWND tab_handle, int32_t tab_index, TCITEMW *item) {
        return TabCtrl_SetItem(tab_handle, tab_index, item);
    }

    bool tab::set_item_extra(HWND tab_handle, int32_t size) {
        return TabCtrl_SetItemExtra(tab_handle, size);
    }

    std::pair<uint32_t, uint32_t>
    tab::set_item_size(HWND tab_handle, int32_t width, int32_t height) {
        uint32_t result = TabCtrl_SetItemSize(tab_handle, width, height);
        return std::make_pair(LOWORD(result), HIWORD(result));
    }

    SIZE tab::set_item_size(HWND tab_handle, SIZE size) {
        uint32_t result = TabCtrl_SetItemSize(tab_handle, size.cx, size.cy);
        return {LOWORD(result), HIWORD(result)};
    }

    int32_t
    tab::insert_item(HWND tab_handle, int32_t tab_index, TCITEMW *item) {
        return TabCtrl_InsertItem(tab_handle, tab_index, item);
    }

    bool tab::delete_item(HWND tab_handle, int32_t tab_index) {
        return TabCtrl_DeleteItem(tab_handle, tab_index);
    }

    bool tab::delete_all_items(HWND tab_handle) {
        return TabCtrl_DeleteAllItems(tab_handle);
    }

    bool tab::highlight_item(HWND tab_handle, int32_t tab_index) {
        return TabCtrl_HighlightItem(tab_handle, tab_index, TRUE);
    }

    bool tab::unhighlight_item(HWND tab_handle, int32_t tab_index) {
        return TabCtrl_HighlightItem(tab_handle, tab_index, FALSE);
    }

    int32_t tab::hit_test(HWND tab_handle, TCHITTESTINFO *hit_test_info) {
        return TabCtrl_HitTest(tab_handle, hit_test_info);
    }

    int32_t tab::get_row_count(HWND tab_handle) {
        return TabCtrl_GetRowCount(tab_handle);
    }

    int32_t tab::set_min_width(HWND tab_handle, int32_t width) {
        return TabCtrl_SetMinTabWidth(tab_handle, width);
    }

    void tab::set_padding(HWND tab_handle, int32_t horiz, int32_t vert) {
        TabCtrl_SetPadding(tab_handle, horiz, vert);
    }

    void tab::display_rect_to_window_rect(HWND tab_handle, RECT *rect) {
        TabCtrl_AdjustRect(tab_handle, TRUE, rect);
    }

    void tab::window_rect_to_display_rect(HWND tab_handle, RECT *rect) {
        TabCtrl_AdjustRect(tab_handle, FALSE, rect);
    }

    void tab::reset_curr_item(HWND tab_handle) {
        TabCtrl_DeselectAll(tab_handle, TRUE);
    }

    void tab::reset_all_items(HWND tab_handle) {
        TabCtrl_DeselectAll(tab_handle, FALSE);
    }

    uint32_t tab::err_code() const {
        return error_code;
    }

    std::string tab::err_string() const {
        std::string result = helper::convert::err_string(error_code);
        return result;
    }

    std::wstring tab::err_wstring() const {
        std::wstring result = helper::convert::err_wstring(error_code);
        return result;
    }
} // namespace YanLib::components
