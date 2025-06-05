//
// Created by forkernel on 2025/5/31.
//

#include "link.h"
#include <windowsx.h>

namespace YanLib::ui::components {
    HWND link::create(uintptr_t link_id,
                      HWND parent_window_handle,
                      LPARAM lparam,
                      int32_t x,
                      int32_t y,
                      int32_t width,
                      int32_t height,
                      LinkStyle style,
                      WindowStyle window_style) {
        INITCOMMONCONTROLSEX icc = {};
        icc.dwSize = sizeof(INITCOMMONCONTROLSEX);
        icc.dwICC = ICC_LINK_CLASS;
        InitCommonControlsEx(&icc);
        HWND result = CreateWindowExW(0L, L"SysLink", nullptr,
                                      static_cast<uint32_t>(window_style) |
                                              static_cast<uint32_t>(style),
                                      x, y, width, height, parent_window_handle,
                                      reinterpret_cast<HMENU>(link_id),
                                      reinterpret_cast<CREATESTRUCT *>(lparam)
                                              ->hInstance,
                                      nullptr);
        if (!result) {
            error_code = GetLastError();
        }
        return result;
    }

    HWND link::create(const char *link_name,
                      uintptr_t link_id,
                      HWND parent_window_handle,
                      LPARAM lparam,
                      int32_t x,
                      int32_t y,
                      int32_t width,
                      int32_t height,
                      LinkStyle style,
                      WindowStyle window_style,
                      helper::CodePage code_page) {
        INITCOMMONCONTROLSEX icc = {};
        icc.dwSize = sizeof(INITCOMMONCONTROLSEX);
        icc.dwICC = ICC_LINK_CLASS;
        InitCommonControlsEx(&icc);
        HWND result = CreateWindowExW(
                0L, L"SysLink",
                helper::convert::str_to_wstr(link_name, code_page).data(),
                static_cast<uint32_t>(window_style) |
                        static_cast<uint32_t>(style),
                x, y, width, height, parent_window_handle,
                reinterpret_cast<HMENU>(link_id),
                reinterpret_cast<CREATESTRUCT *>(lparam)->hInstance, nullptr);
        if (!result) {
            error_code = GetLastError();
        }
        return result;
    }

    HWND link::create(const wchar_t *link_name,
                      uintptr_t link_id,
                      HWND parent_window_handle,
                      LPARAM lparam,
                      int32_t x,
                      int32_t y,
                      int32_t width,
                      int32_t height,
                      LinkStyle style,
                      WindowStyle window_style) {
        INITCOMMONCONTROLSEX icc = {};
        icc.dwSize = sizeof(INITCOMMONCONTROLSEX);
        icc.dwICC = ICC_LINK_CLASS;
        InitCommonControlsEx(&icc);
        HWND result = CreateWindowExW(0L, L"SysLink", link_name,
                                      static_cast<uint32_t>(window_style) |
                                              static_cast<uint32_t>(style),
                                      x, y, width, height, parent_window_handle,
                                      reinterpret_cast<HMENU>(link_id),
                                      reinterpret_cast<CREATESTRUCT *>(lparam)
                                              ->hInstance,
                                      nullptr);
        if (!result) {
            error_code = GetLastError();
        }
        return result;
    }

    int64_t link::get_ideal_height(HWND link_handle) {
        return SendMessageW(link_handle, LM_GETIDEALHEIGHT, 0, 0);
    }

    int64_t link::get_ideal_size(HWND link_handle, int32_t width, SIZE *size) {
        return SendMessageW(link_handle, LM_GETIDEALSIZE, width,
                            reinterpret_cast<LPARAM>(size));
    }

    bool link::get_item(HWND link_handle, LITEM *item) {
        return SendMessageW(link_handle, LM_GETITEM, 0,
                            reinterpret_cast<LPARAM>(item));
    }

    bool link::set_item(HWND link_handle, LITEM *item) {
        return SendMessageW(link_handle, LM_SETITEM, 0,
                            reinterpret_cast<LPARAM>(item));
    }

    bool link::hit_test(HWND link_handle, LHITTESTINFO *hit_test_info) {
        return SendMessageW(link_handle, LM_HITTEST, 0,
                            reinterpret_cast<LPARAM>(hit_test_info));
    }

    uint32_t link::err_code() const {
        return error_code;
    }

    std::string link::err_string() const {
        std::string result = helper::convert::err_string(error_code);
        return result;
    }

    std::wstring link::err_wstring() const {
        std::wstring result = helper::convert::err_wstring(error_code);
        return result;
    }
} // namespace YanLib::ui::components
