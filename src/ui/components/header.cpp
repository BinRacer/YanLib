//
// Created by forkernel on 2025/5/25.
//

#include "header.h"
#include <windowsx.h>
#include "helper/convert.h"
namespace YanLib::ui::components {
    HWND header::create(uintptr_t header_id,
                        HWND parent_window_handle,
                        LPARAM lparam,
                        int32_t x,
                        int32_t y,
                        int32_t width,
                        int32_t height,
                        HeaderStyle style,
                        WindowStyle window_style) {
        INITCOMMONCONTROLSEX icc = {};
        icc.dwSize = sizeof(INITCOMMONCONTROLSEX);
        icc.dwICC = ICC_LISTVIEW_CLASSES | ICC_WIN95_CLASSES;
        InitCommonControlsEx(&icc);
        HWND result = CreateWindowExW(0L, L"SysHeader32", nullptr,
                                      static_cast<uint32_t>(window_style) |
                                              static_cast<uint32_t>(style),
                                      x, y, width, height, parent_window_handle,
                                      reinterpret_cast<HMENU>(header_id),
                                      reinterpret_cast<CREATESTRUCT *>(lparam)
                                              ->hInstance,
                                      nullptr);
        if (!result) {
            error_code = GetLastError();
        }
        return result;
    }

    HWND header::create(const char *header_name,
                        uintptr_t header_id,
                        HWND parent_window_handle,
                        LPARAM lparam,
                        int32_t x,
                        int32_t y,
                        int32_t width,
                        int32_t height,
                        HeaderStyle style,
                        WindowStyle window_style) {
        INITCOMMONCONTROLSEX icc = {};
        icc.dwSize = sizeof(INITCOMMONCONTROLSEX);
        icc.dwICC = ICC_LISTVIEW_CLASSES | ICC_WIN95_CLASSES;
        InitCommonControlsEx(&icc);
        HWND result = CreateWindowExA(0L, "SysHeader32", header_name,
                                      static_cast<uint32_t>(window_style) |
                                              static_cast<uint32_t>(style),
                                      x, y, width, height, parent_window_handle,
                                      reinterpret_cast<HMENU>(header_id),
                                      reinterpret_cast<CREATESTRUCT *>(lparam)
                                              ->hInstance,
                                      nullptr);
        if (!result) {
            error_code = GetLastError();
        }
        return result;
    }

    HWND header::create(const wchar_t *header_name,
                        uintptr_t header_id,
                        HWND parent_window_handle,
                        LPARAM lparam,
                        int32_t x,
                        int32_t y,
                        int32_t width,
                        int32_t height,
                        HeaderStyle style,
                        WindowStyle window_style) {
        INITCOMMONCONTROLSEX icc = {};
        icc.dwSize = sizeof(INITCOMMONCONTROLSEX);
        icc.dwICC = ICC_LISTVIEW_CLASSES | ICC_WIN95_CLASSES;
        InitCommonControlsEx(&icc);
        HWND result = CreateWindowExW(0L, L"SysHeader32", header_name,
                                      static_cast<uint32_t>(window_style) |
                                              static_cast<uint32_t>(style),
                                      x, y, width, height, parent_window_handle,
                                      reinterpret_cast<HMENU>(header_id),
                                      reinterpret_cast<CREATESTRUCT *>(lparam)
                                              ->hInstance,
                                      nullptr);
        if (!result) {
            error_code = GetLastError();
        }
        return result;
    }

    HIMAGELIST header::create_drag_image(HWND header_handle, int32_t index) {
        return Header_CreateDragImage(header_handle, index);
    }

    HIMAGELIST header::get_image_list(HWND header_handle) {
        return Header_GetImageList(header_handle);
    }

    HIMAGELIST header::set_image_list(HWND header_handle,
                                      HIMAGELIST image_list_handle) {

        return Header_SetImageList(header_handle, image_list_handle);
    }

    HIMAGELIST header::get_state_image_list(HWND header_handle) {
        return Header_GetStateImageList(header_handle);
    }

    HIMAGELIST header::set_state_image_list(HWND header_handle,
                                            HIMAGELIST image_list_handle) {
        return Header_SetStateImageList(header_handle, image_list_handle);
    }

    int32_t header::get_bitmap_margin(HWND header_handle) {
        return Header_GetBitmapMargin(header_handle);
    }

    int32_t header::set_bitmap_margin(HWND header_handle, int32_t width) {
        return Header_SetBitmapMargin(header_handle, width);
    }

    bool header::clear_all_filters(HWND header_handle) {
        return Header_ClearAllFilters(header_handle);
    }

    bool header::clear_filter(HWND header_handle, int32_t index) {
        return Header_ClearFilter(header_handle, index);
    }

    bool
    header::set_filter(HWND header_handle, int32_t index, bool discard_change) {
        return Header_EditFilter(header_handle, index,
                                 discard_change ? TRUE : FALSE);
    }

    int32_t header::insert_item(HWND header_handle,
                                const HDITEMW *item,
                                int32_t index) {
        return Header_InsertItem(header_handle, index, item);
    }

    bool header::delete_item(HWND header_handle, int32_t index) {
        return Header_DeleteItem(header_handle, index);
    }

    bool header::get_item(HWND header_handle, HDITEMW *item, int32_t index) {
        return Header_GetItem(header_handle, index, item);
    }

    bool header::set_item(HWND header_handle, HDITEMW *item, int32_t index) {
        return Header_SetItem(header_handle, index, item);
    }

    int32_t header::get_item_count(HWND header_handle) {
        return Header_GetItemCount(header_handle);
    }

    bool header::get_item_rect(HWND header_handle, RECT *rect, int32_t index) {
        return Header_GetItemRect(header_handle, index, rect);
    }

    bool header::get_item_drop_down_rect(HWND header_handle,
                                         RECT *rect,
                                         int32_t index) {

        return Header_GetItemDropDownRect(header_handle, index, rect);
    }

    int32_t header::get_focused_item(HWND header_handle) {
        return Header_GetFocusedItem(header_handle);
    }

    bool header::set_focused_item(HWND header_handle, int32_t index) {
        return Header_SetFocusedItem(header_handle, index);
    }

    bool header::get_item_order(HWND header_handle,
                                std::vector<int32_t> &order) {
        return Header_GetOrderArray(header_handle, order.size(), order.data());
    }

    bool header::set_item_order(HWND header_handle,
                                std::vector<int32_t> &order) {
        return Header_SetOrderArray(header_handle, order.size(), order.data());
    }

    int32_t header::order_to_index(HWND header_handle, int32_t order) {
        return Header_OrderToIndex(header_handle, order);
    }

    bool header::get_overflow_rect(HWND header_handle, RECT *rect) {
        return Header_GetOverflowRect(header_handle, rect);
    }

    bool header::is_ansi_format(HWND header_handle) {
        return !(Header_GetUnicodeFormat(header_handle));
    }

    bool header::is_unicode_format(HWND header_handle) {
        return Header_GetUnicodeFormat(header_handle);
    }

    void header::set_unicode_format(HWND header_handle) {
        Header_SetUnicodeFormat(header_handle, TRUE);
    }

    void header::set_ansi_format(HWND header_handle) {
        Header_SetUnicodeFormat(header_handle, FALSE);
    }

    bool header::get_layout(HWND header_handle, HDLAYOUT *layout) {
        return Header_Layout(header_handle, layout);
    }

    int32_t header::set_filter_change_timeout(HWND header_handle,
                                              int32_t milli_seconds) {

        return Header_SetFilterChangeTimeout(header_handle, milli_seconds);
    }

    int32_t
    header::set_hot_divider(HWND header_handle, uint32_t x, uint32_t y) {
        uint32_t pos = MAKEWORD(x, y);
        return Header_SetHotDivider(header_handle, TRUE, pos);
    }

    int32_t header::set_hot_divider(HWND header_handle, uint32_t index) {
        return Header_SetHotDivider(header_handle, FALSE, index);
    }

    uint32_t header::err_code() const {
        return error_code;
    }

    std::string header::err_string() const {
        std::string result = helper::convert::err_string(error_code);
        return result;
    }

    std::wstring header::err_wstring() const {
        std::wstring result = helper::convert::err_wstring(error_code);
        return result;
    }
} // namespace YanLib::ui::components
