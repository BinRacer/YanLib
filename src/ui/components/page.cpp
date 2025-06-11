/* clang-format off */
/*
 * @file page.cpp
 * @date 2025-05-28
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
#include "page.h"
#include <windowsx.h>
#include "helper/convert.h"
namespace YanLib::ui::components {
    page::page() {
        INITCOMMONCONTROLSEX icc = {};
        icc.dwSize = sizeof(INITCOMMONCONTROLSEX);
        icc.dwICC = ICC_PAGESCROLLER_CLASS;
        InitCommonControlsEx(&icc);
    }

    page::~page() {
        for (auto &handle : pages_handles) {
            if (handle && IsWindow(handle)) {
                DestroyWindow(handle);
                handle = nullptr;
            }
        }
        pages_handles.clear();
    }

    HWND page::create(uintptr_t page_id,
                      HWND parent_window_handle,
                      LPARAM lparam,
                      int32_t x,
                      int32_t y,
                      int32_t width,
                      int32_t height,
                      PageStyle style,
                      WindowStyle window_style) {
        HWND result = CreateWindowExW(0L, L"SysPager", nullptr,
                                      static_cast<uint32_t>(window_style) |
                                              static_cast<uint32_t>(style),
                                      x, y, width, height, parent_window_handle,
                                      reinterpret_cast<HMENU>(page_id),
                                      reinterpret_cast<CREATESTRUCT *>(lparam)
                                              ->hInstance,
                                      nullptr);
        if (!result) {
            error_code = GetLastError();
            return nullptr;
        }
        pages_rwlock.write_lock();
        pages_handles.push_back(result);
        pages_rwlock.write_unlock();
        return result;
    }

    HWND page::create(const char *page_name,
                      uintptr_t page_id,
                      HWND parent_window_handle,
                      LPARAM lparam,
                      int32_t x,
                      int32_t y,
                      int32_t width,
                      int32_t height,
                      PageStyle style,
                      WindowStyle window_style) {
        HWND result = CreateWindowExA(0L, "SysPager", page_name,
                                      static_cast<uint32_t>(window_style) |
                                              static_cast<uint32_t>(style),
                                      x, y, width, height, parent_window_handle,
                                      reinterpret_cast<HMENU>(page_id),
                                      reinterpret_cast<CREATESTRUCT *>(lparam)
                                              ->hInstance,
                                      nullptr);
        if (!result) {
            error_code = GetLastError();
            return nullptr;
        }
        pages_rwlock.write_lock();
        pages_handles.push_back(result);
        pages_rwlock.write_unlock();
        return result;
    }

    HWND page::create(const wchar_t *page_name,
                      uintptr_t page_id,
                      HWND parent_window_handle,
                      LPARAM lparam,
                      int32_t x,
                      int32_t y,
                      int32_t width,
                      int32_t height,
                      PageStyle style,
                      WindowStyle window_style) {
        HWND result = CreateWindowExW(0L, L"SysPager", page_name,
                                      static_cast<uint32_t>(window_style) |
                                              static_cast<uint32_t>(style),
                                      x, y, width, height, parent_window_handle,
                                      reinterpret_cast<HMENU>(page_id),
                                      reinterpret_cast<CREATESTRUCT *>(lparam)
                                              ->hInstance,
                                      nullptr);
        if (!result) {
            error_code = GetLastError();
            return nullptr;
        }
        pages_rwlock.write_lock();
        pages_handles.push_back(result);
        pages_rwlock.write_unlock();
        return result;
    }

    bool page::destroy(HWND page_handle) {
        if (!page_handle || !IsWindow(page_handle)) {
            return false;
        }
        pages_rwlock.write_lock();
        const auto it = std::find(pages_handles.begin(), pages_handles.end(),
                                  page_handle);
        if (it != pages_handles.end()) {
            *it = nullptr;
        }
        pages_rwlock.write_unlock();
        if (!DestroyWindow(page_handle)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    void page::enable_forward_mouse(HWND page_handle) {
        Pager_ForwardMouse(page_handle, TRUE);
    }

    void page::disable_forward_mouse(HWND page_handle) {
        Pager_ForwardMouse(page_handle, FALSE);
    }

    COLORREF page::get_background_color(HWND page_handle) {
        return Pager_GetBkColor(page_handle);
    }

    COLORREF page::set_background_color(HWND page_handle, COLORREF color) {
        return Pager_SetBkColor(page_handle, color);
    }

    int32_t page::get_border(HWND page_handle) {
        return Pager_GetBorder(page_handle);
    }

    int32_t page::set_border(HWND page_handle, int32_t border) {
        return Pager_SetBorder(page_handle, border);
    }

    int32_t page::get_button_size(HWND page_handle) {
        return Pager_GetButtonSize(page_handle);
    }

    int32_t page::set_button_size(HWND page_handle, int32_t size) {
        return Pager_SetButtonSize(page_handle, size);
    }

    PageButtonState page::get_button_state(HWND page_handle,
                                           PageButtonIndex index) {
        return static_cast<PageButtonState>(
                Pager_GetButtonState(page_handle,
                                     static_cast<uint32_t>(index)));
    }

    void page::get_drop_target(HWND page_handle, IDropTarget **target) {
        Pager_GetDropTarget(page_handle, target);
    }

    int32_t page::get_pos(HWND page_handle) {
        return Pager_GetPos(page_handle);
    }

    void page::set_pos(HWND page_handle, int32_t pos) {
        Pager_SetPos(page_handle, pos);
    }

    void page::recalc_size(HWND page_handle) {
        Pager_RecalcSize(page_handle);
    }

    void page::set_child(HWND page_handle, HWND child_window_handle) {
        Pager_SetChild(page_handle, child_window_handle);
    }

    void page::set_scroll_info(HWND page_handle,
                               uint32_t timeout_ms,
                               uint32_t line_num,
                               uint32_t per_line_pixels) {
        Pager_SetScrollInfo(page_handle, timeout_ms, line_num, per_line_pixels);
    }

    uint32_t page::err_code() const {
        return error_code;
    }

    std::string page::err_string() const {
        std::string result = helper::convert::err_string(error_code);
        return result;
    }

    std::wstring page::err_wstring() const {
        std::wstring result = helper::convert::err_wstring(error_code);
        return result;
    }
} // namespace YanLib::ui::components
