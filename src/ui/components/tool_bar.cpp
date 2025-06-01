//
// Created by forkernel on 2025/6/1.
//

#include "tool_bar.h"
#include <windowsx.h>

namespace YanLib::components {
    HWND tool_bar::create(HWND parent_window_handle,
                          LPARAM lparam,
                          int32_t x,
                          int32_t y,
                          int32_t width,
                          int32_t height,
                          ToolBarStyle style,
                          WindowStyle window_style) {
        INITCOMMONCONTROLSEX icc = {};
        icc.dwSize = sizeof(INITCOMMONCONTROLSEX);
        icc.dwICC = ICC_BAR_CLASSES;
        InitCommonControlsEx(&icc);
        HWND result = CreateWindowExW(
                0L, L"ToolbarWindow32", nullptr,
                static_cast<uint32_t>(window_style) |
                        static_cast<uint32_t>(style),
                x, y, width, height, parent_window_handle, nullptr,
                reinterpret_cast<CREATESTRUCT *>(lparam)->hInstance, nullptr);
        if (!result) {
            error_code = GetLastError();
        }
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
        INITCOMMONCONTROLSEX icc = {};
        icc.dwSize = sizeof(INITCOMMONCONTROLSEX);
        icc.dwICC = ICC_BAR_CLASSES;
        InitCommonControlsEx(&icc);
        HWND result = CreateWindowExA(
                0L, "ToolbarWindow32", tool_bar_name,
                static_cast<uint32_t>(window_style) |
                        static_cast<uint32_t>(style),
                x, y, width, height, parent_window_handle, nullptr,
                reinterpret_cast<CREATESTRUCT *>(lparam)->hInstance, nullptr);
        if (!result) {
            error_code = GetLastError();
        }
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
        INITCOMMONCONTROLSEX icc = {};
        icc.dwSize = sizeof(INITCOMMONCONTROLSEX);
        icc.dwICC = ICC_BAR_CLASSES;
        InitCommonControlsEx(&icc);
        HWND result = CreateWindowExW(
                0L, L"ToolbarWindow32", tool_bar_name,
                static_cast<uint32_t>(window_style) |
                        static_cast<uint32_t>(style),
                x, y, width, height, parent_window_handle, nullptr,
                reinterpret_cast<CREATESTRUCT *>(lparam)->hInstance, nullptr);
        if (!result) {
            error_code = GetLastError();
        }
        return result;
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
} // namespace YanLib::components
