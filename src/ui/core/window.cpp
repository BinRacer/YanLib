/* clang-format off */
/*
 * @file window.cpp
 * @date 2025-04-28
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
#include "window.h"
#include <complex>
#include <Powrprof.h>
#pragma comment(lib, "powrprof.lib")
namespace YanLib::ui::core {
    window::~window() {
        for (auto &shutdown : shutdown_handles) {
            if (shutdown && IsWindow(shutdown)) {
                ShutdownBlockReasonDestroy(shutdown);
                shutdown = nullptr;
            }
        }
        shutdown_handles.clear();
        for (auto &window : window_handles) {
            if (window && IsWindow(window)) {
                DestroyWindow(window);
                window = nullptr;
            }
        }
        window_handles.clear();
    }

    HWND window::create(const char *class_name,
                        const char *window_name,
                        HINSTANCE instance_handle,
                        void *param,
                        HWND parent_window_handle,
                        HMENU menu_handle,
                        int32_t x,
                        int32_t y,
                        int32_t width,
                        int32_t height,
                        WindowStyle style,
                        WindowExtendStyle extend_style) {
        HWND result =
                CreateWindowExA(static_cast<uint32_t>(extend_style), class_name,
                                window_name, static_cast<uint32_t>(style), x, y,
                                width, height, parent_window_handle,
                                menu_handle, instance_handle, param);
        if (!result) {
            error_code = GetLastError();
            return nullptr;
        }
        window_rwlock.write_lock();
        window_handles.push_back(result);
        window_rwlock.write_unlock();
        return result;
    }

    HWND window::create(const wchar_t *class_name,
                        const wchar_t *window_name,
                        HINSTANCE instance_handle,
                        void *param,
                        HWND parent_window_handle,
                        HMENU menu_handle,
                        int32_t x,
                        int32_t y,
                        int32_t width,
                        int32_t height,
                        WindowStyle style,
                        WindowExtendStyle extend_style) {
        HWND result =
                CreateWindowExW(static_cast<uint32_t>(extend_style), class_name,
                                window_name, static_cast<uint32_t>(style), x, y,
                                width, height, parent_window_handle,
                                menu_handle, instance_handle, param);
        if (!result) {
            error_code = GetLastError();
            return nullptr;
        }
        window_rwlock.write_lock();
        window_handles.push_back(result);
        window_rwlock.write_unlock();
        return result;
    }

    HWND window::create_mdi(const char *class_name,
                            const char *window_name,
                            HINSTANCE instance_handle,
                            LPARAM lparam,
                            HWND parent_window_handle,
                            int32_t x,
                            int32_t y,
                            int32_t width,
                            int32_t height,
                            WindowStyle style) {
        HWND result =
                CreateMDIWindowA(class_name, window_name,
                                 static_cast<uint32_t>(style) |
                                         MDIS_ALLCHILDSTYLES,
                                 x, y, width, height, parent_window_handle,
                                 instance_handle, lparam);
        if (!result) {
            error_code = GetLastError();
            return nullptr;
        }
        window_rwlock.write_lock();
        window_handles.push_back(result);
        window_rwlock.write_unlock();
        return result;
    }

    HWND window::create_mdi(const wchar_t *class_name,
                            const wchar_t *window_name,
                            HINSTANCE instance_handle,
                            LPARAM lparam,
                            HWND parent_window_handle,
                            int32_t x,
                            int32_t y,
                            int32_t width,
                            int32_t height,
                            WindowStyle style) {
        HWND result =
                CreateMDIWindowW(class_name, window_name,
                                 static_cast<uint32_t>(style) |
                                         MDIS_ALLCHILDSTYLES,
                                 x, y, width, height, parent_window_handle,
                                 instance_handle, lparam);
        if (!result) {
            error_code = GetLastError();
            return nullptr;
        }
        window_rwlock.write_lock();
        window_handles.push_back(result);
        window_rwlock.write_unlock();
        return result;
    }

    bool window::show(HWND window_handle, ShowType cmd_show) {
        return ShowWindow(window_handle, static_cast<int32_t>(cmd_show));
    }

    bool window::show_async(HWND window_handle, ShowType cmd_show) {
        return ShowWindowAsync(window_handle, static_cast<int32_t>(cmd_show));
    }

    bool window::update(HWND window_handle) {
        return UpdateWindow(window_handle);
    }

    bool window::update_layered(HWND window_handle,
                                HDC hdc_dst,
                                POINT *coordinate_dst,
                                SIZE *size,
                                HDC hdc_src,
                                POINT *coordinate_src,
                                COLORREF color_ref,
                                BLENDFUNCTION *blend_fn,
                                UpdateLayeredFlag flag) {
        if (!UpdateLayeredWindow(window_handle, hdc_dst, coordinate_dst, size,
                                 hdc_src, coordinate_src, color_ref, blend_fn,
                                 static_cast<uint32_t>(flag))) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool window::lock_update(HWND window_handle) {
        return LockWindowUpdate(window_handle);
    }

    bool window::unlock_update() {
        return LockWindowUpdate(nullptr);
    }

    bool window::animate(HWND window_handle,
                         uint32_t milli_second,
                         AnimateFlag flag) {
        if (!AnimateWindow(window_handle, milli_second,
                           static_cast<uint32_t>(flag))) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool window::close(HWND window_handle) {
        if (!CloseWindow(window_handle)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }
#ifdef WINNT
    bool window::close(HWND window_handle, bool is_force) {
        if (!EndTask(window_handle, FALSE, is_force ? TRUE : FALSE)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }
#endif
    bool window::exit(ExitCode exit_code, ReasonCode reason_code) {
        if (!ExitWindowsEx(static_cast<uint32_t>(exit_code),
                           static_cast<uint32_t>(reason_code))) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool window::shutdown(ReasonCode reason_code) {
        if (!ExitWindowsEx(EWX_SHUTDOWN | EWX_POWEROFF,
                           static_cast<uint32_t>(reason_code))) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool window::reboot(ReasonCode reason_code) {
        if (!ExitWindowsEx(EWX_REBOOT, static_cast<uint32_t>(reason_code))) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool window::logoff(ReasonCode reason_code) {
        if (!ExitWindowsEx(EWX_LOGOFF, static_cast<uint32_t>(reason_code))) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool window::hibernate(bool wakeup_events_disabled) {
        if (!SetSuspendState(TRUE, TRUE,
                             wakeup_events_disabled ? TRUE : FALSE)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool window::create_shutdown_reason(HWND window_handle,
                                        const std::string &reason,
                                        helper::CodePage code_page) {
        const std::wstring data =
                helper::convert::str_to_wstr(reason, code_page);
        if (!ShutdownBlockReasonCreate(window_handle, data.data())) {
            error_code = GetLastError();
            return false;
        }
        shutdown_rwlock.write_lock();
        shutdown_handles.push_back(window_handle);
        shutdown_rwlock.write_unlock();
        return true;
    }

    bool window::create_shutdown_reason(HWND window_handle,
                                        const std::wstring &reason) {
        if (!ShutdownBlockReasonCreate(window_handle, reason.data())) {
            error_code = GetLastError();
            return false;
        }
        shutdown_rwlock.write_lock();
        shutdown_handles.push_back(window_handle);
        shutdown_rwlock.write_unlock();
        return true;
    }

    bool window::destroy_shutdown_reason(HWND window_handle) {
        if (!window_handle) {
            return false;
        }
        shutdown_rwlock.write_lock();
        const auto it = std::find(shutdown_handles.begin(),
                                  shutdown_handles.end(), window_handle);
        if (it != shutdown_handles.end()) {
            *it = nullptr;
        }
        shutdown_rwlock.write_unlock();
        if (!ShutdownBlockReasonDestroy(window_handle)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool window::query_shutdown_reason(HWND window_handle,
                                       const std::string &reason,
                                       uint32_t *real_size,
                                       helper::CodePage code_page) {
        if (!real_size) {
            error_code = STATUS_ACCESS_VIOLATION;
            return false;
        }
        std::wstring data = helper::convert::str_to_wstr(reason, code_page);
        unsigned long temp = data.size();
        if (!ShutdownBlockReasonQuery(window_handle, data.data(), &temp)) {
            error_code = GetLastError();
            *real_size = temp;
            return false;
        }
        *real_size = temp;
        return true;
    }

    bool window::query_shutdown_reason(HWND window_handle,
                                       std::wstring &reason,
                                       uint32_t *real_size) {
        if (!real_size) {
            error_code = STATUS_ACCESS_VIOLATION;
            return false;
        }
        unsigned long temp = reason.size();
        if (!ShutdownBlockReasonQuery(window_handle, reason.data(), &temp)) {
            error_code = GetLastError();
            *real_size = temp;
            return false;
        }
        *real_size = temp;
        return true;
    }

    bool window::destroy(HWND window_handle) {
        if (!window_handle || !IsWindow(window_handle)) {
            return false;
        }
        window_rwlock.write_lock();
        const auto it = std::find(window_handles.begin(), window_handles.end(),
                                  window_handle);
        if (it != window_handles.end()) {
            *it = nullptr;
        }
        window_rwlock.write_unlock();
        if (!DestroyWindow(window_handle)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool window::enable_input(HWND window_handle) {
        return EnableWindow(window_handle, TRUE);
    }

    bool window::disable_input(HWND window_handle) {
        return EnableWindow(window_handle, FALSE);
    }

    bool window::enumerate(WNDENUMPROC enum_func, LPARAM lparam) {
        if (!EnumWindows(enum_func, lparam)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool window::enumerate_child(HWND parent_window_handle,
                                 WNDENUMPROC enum_func,
                                 LPARAM lparam) {
        return EnumChildWindows(parent_window_handle, enum_func, lparam);
    }

    bool window::enumerate(uint32_t tid, WNDENUMPROC fn, LPARAM lparam) {
        return EnumThreadWindows(tid, fn, lparam);
    }

    HWND window::find(const char *class_name, const char *window_name) {
        return FindWindowA(class_name, window_name);
    }

    HWND window::find(const wchar_t *class_name, const wchar_t *window_name) {
        return FindWindowW(class_name, window_name);
    }

    HWND window::find(HWND parent_window_handle,
                      const char *class_name,
                      const char *window_name) {
        HWND result = FindWindowExA(parent_window_handle, nullptr, class_name,
                                    window_name);
        if (!result) {
            error_code = GetLastError();
        }
        return result;
    }

    HWND window::find(HWND parent_window_handle,
                      const wchar_t *class_name,
                      const wchar_t *window_name) {
        HWND result = FindWindowExW(parent_window_handle, nullptr, class_name,
                                    window_name);
        if (!result) {
            error_code = GetLastError();
        }
        return result;
    }

    bool window::flash(HWND window_handle, bool invert) {
        return FlashWindow(window_handle, invert ? TRUE : FALSE);
    }

    bool window::flash(FLASHWINFO *flash_info) {
        return FlashWindowEx(flash_info);
    }

    bool window::move(HWND window_handle,
                      int32_t x,
                      int32_t y,
                      int32_t width,
                      int32_t height,
                      bool repaint) {
        if (!MoveWindow(window_handle, x, y, width, height,
                        repaint ? TRUE : FALSE)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool window::print(HWND window_handle, HDC dc_handle, bool client_only) {
        return PrintWindow(window_handle, dc_handle,
                           client_only ? PW_CLIENTONLY : 0);
    }

    bool window::redraw(HWND window_handle,
                        HRGN region_handle,
                        const RECT *rect,
                        RedrawFlag flag) {
        return RedrawWindow(window_handle, rect, region_handle,
                            static_cast<uint32_t>(flag));
    }

    bool window::maximize(HWND window_handle) {
        return ShowWindow(window_handle, SW_MAXIMIZE);
    }

    bool window::minimize(HWND window_handle) {
        return ShowWindow(window_handle, SW_MINIMIZE);
    }

    bool window::hide(HWND window_handle) {
        return ShowWindow(window_handle, SW_HIDE);
    }

    bool window::restore(HWND window_handle) {
        return ShowWindow(window_handle, SW_RESTORE);
    }

    bool window::restore_minimize(HWND window_handle) {
        if (!OpenIcon(window_handle)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    uint16_t window::tile(HWND parent_window_handle,
                          const RECT *rect,
                          const std::vector<HWND> &child,
                          TileStyle style) {
        const uint16_t result =
                TileWindows(parent_window_handle, static_cast<uint32_t>(style),
                            rect, child.size(), child.data());
        if (!result) {
            error_code = GetLastError();
        }
        return result;
    }

    HWND window::get_parent(HWND window_handle) {
        HWND result = GetParent(window_handle);
        if (!result) {
            error_code = GetLastError();
        }
        return result;
    }

    HWND window::set_parent(HWND windows_handle, HWND parent_window_handle) {
        HWND result = SetParent(windows_handle, parent_window_handle);
        if (!result) {
            error_code = GetLastError();
        }
        return result;
    }

    HWND window::get_ancestor(HWND window_handle, SearchFlag flag) {
        return GetAncestor(window_handle, static_cast<uint32_t>(flag));
    }

    bool window::show_popup(HWND window_handle) {
        if (!ShowOwnedPopups(window_handle, TRUE)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool window::hide_popup(HWND window_handle) {
        if (!ShowOwnedPopups(window_handle, FALSE)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    HWND window::get_last_active_popup(HWND window_handle) {
        return GetLastActivePopup(window_handle);
    }

    bool window::is_pending(HWND window_handle) {
        return IsHungAppWindow(window_handle);
    }

    bool window::is_window(HWND window_handle) {
        return IsWindow(window_handle);
    }

    bool window::is_arranged(HWND window_handle) {
        HMODULE user32 = nullptr;
        bool result = false;
        do {
            user32 = LoadLibraryW(L"user32.dll");
            if (!user32) {
                error_code = GetLastError();
                break;
            }
            typedef int32_t(CALLBACK * prototype)(HWND);
            const auto func = reinterpret_cast<prototype>(
                    GetProcAddress(user32, "IsWindowArranged"));
            if (!func) {
                error_code = GetLastError();
                break;
            }
            result = func(window_handle);
            if (!result) {
                error_code = GetLastError();
            }
        } while (false);
        if (user32) {
            FreeLibrary(user32);
        }
        return result;
    }

    bool window::is_enabled(HWND window_handle) {
        return IsWindowEnabled(window_handle);
    }

    bool window::is_unicode(HWND window_handle) {
        return IsWindowUnicode(window_handle);
    }

    bool window::is_visible(HWND window_handle) {
        return IsWindowVisible(window_handle);
    }

    bool window::is_minimize(HWND window_handle) {
        return IsIconic(window_handle);
    }

    bool window::is_maximize(HWND window_handle) {
        return IsZoomed(window_handle);
    }

    bool window::is_child(HWND window_handle, HWND child_window_handle) {
        return IsChild(window_handle, child_window_handle);
    }

    bool window::is_popup_exist() {
        return AnyPopup();
    }

    uint32_t window::arrange_minimize(HWND window_handle) {
        const uint32_t height = ArrangeIconicWindows(window_handle);
        if (!height) {
            error_code = GetLastError();
        }
        return height;
    }

    bool window::get_proc_default_layout(Layout *layout) {
        if (!layout) {
            error_code = STATUS_ACCESS_VIOLATION;
            return false;
        }
        auto temp = static_cast<unsigned long>(*layout);
        if (!GetProcessDefaultLayout(&temp)) {
            error_code = GetLastError();
            *layout = static_cast<Layout>(temp);
            return false;
        }
        *layout = static_cast<Layout>(temp);
        return true;
    }

    bool window::set_proc_default_layout(Layout layout) {
        if (!SetProcessDefaultLayout(static_cast<uint32_t>(layout))) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool window::set_pos(HWND window_handle,
                         HWND insert_after_window_handle,
                         int32_t x,
                         int32_t y,
                         int32_t width,
                         int32_t height,
                         PosFlag flag) {
        if (!SetWindowPos(window_handle, insert_after_window_handle, x, y,
                          width, height, static_cast<uint32_t>(flag))) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool window::calc_popup_pos(const POINT *anchor_coordinate,
                                const SIZE *window_size,
                                RECT *popup_pos,
                                RECT *exclude_rect,
                                TrackPopup flag) {
        if (!CalculatePopupWindowPosition(anchor_coordinate, window_size,
                                          static_cast<uint32_t>(flag),
                                          exclude_rect, popup_pos)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    HWND window::find_top_child(HWND parent_window_handle, POINT coordinate) {
        return ChildWindowFromPoint(parent_window_handle, coordinate);
    }

    HWND window::find_top_child(HWND parent_window_handle,
                                POINT coordinate,
                                SearchFlag4 flag) {
        return ChildWindowFromPointEx(parent_window_handle, coordinate,
                                      static_cast<uint32_t>(flag));
    }

    HWND window::find_real_child(HWND parent_window_handle, POINT coordinate) {
        return RealChildWindowFromPoint(parent_window_handle, coordinate);
    }

    HWND window::find_by_physical_point(POINT coordinate) {
        return WindowFromPhysicalPoint(coordinate);
    }

    HWND window::find_by_logical_point(POINT coordinate) {
        return WindowFromPoint(coordinate);
    }

    int32_t window::transform_coordinate(HWND from_window_handle,
                                         HWND to_window_handle,
                                         std::vector<POINT> &coordinates) {
        const int32_t result =
                MapWindowPoints(from_window_handle, to_window_handle,
                                coordinates.data(), coordinates.size());
        error_code = GetLastError();
        return result;
    }

    bool window::adjust_to_top(HWND window_handle) {
        if (!BringWindowToTop(window_handle)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    LRESULT window::call_proc(WNDPROC prev_wnd_func,
                              HWND window_handle,
                              uint32_t msg,
                              WPARAM wparam,
                              LPARAM lparam) {
        return CallWindowProcW(prev_wnd_func, window_handle, msg, wparam,
                               lparam);
    }

    LRESULT window::default_proc(HWND window_handle,
                                 uint32_t msg,
                                 WPARAM wparam,
                                 LPARAM lparam) {
        return DefWindowProcW(window_handle, msg, wparam, lparam);
    }

    LRESULT window::default_mdi_proc(HWND window_handle,
                                     HWND client_mdi_window_handle,
                                     uint32_t msg,
                                     WPARAM wparam,
                                     LPARAM lparam) {
        return DefFrameProcW(window_handle, client_mdi_window_handle, msg,
                             wparam, lparam);
    }

    LRESULT window::default_mdi_child_proc(HWND window_handle,
                                           uint32_t msg,
                                           WPARAM wparam,
                                           LPARAM lparam) {
        return DefMDIChildProcW(window_handle, msg, wparam, lparam);
    }

    uint16_t window::cascade(HWND parent_window_handle,
                             uint32_t how,
                             const RECT *rect,
                             const std::vector<HWND> &child) {
        const uint16_t count = CascadeWindows(parent_window_handle, how, rect,
                                              child.size(), child.data());
        if (!count) {
            error_code = GetLastError();
        }
        return count;
    }

    void window::disable_proc_ghosting() {
        DisableProcessWindowsGhosting();
    }

    HWND window::get_active() {
        return GetActiveWindow();
    }

    HWND window::set_active(HWND window_handle) {
        HWND result = SetActiveWindow(window_handle);
        if (!result) {
            error_code = GetLastError();
        }
        return result;
    }

    uint32_t window::get_dpi(HWND window_handle) {
        return GetDpiForWindow(window_handle);
    }

    HWND window::get_foreground() {
        return GetForegroundWindow();
    }

    bool window::set_foreground(HWND window_handle) {
        return SetForegroundWindow(window_handle);
    }

    bool window::allow_set_foreground(uint32_t pid) {
        if (!AllowSetForegroundWindow(pid)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool window::lock_set_foreground() {
        return LockSetForegroundWindow(LSFW_LOCK);
    }

    bool window::unlock_set_foreground() {
        return LockSetForegroundWindow(LSFW_UNLOCK);
    }

    bool window::get_layered_attrs(HWND window_handle,
                                   COLORREF *color_ref,
                                   uint8_t *alpha,
                                   LayeredFlag *flag) {
        if (!flag) {
            error_code = STATUS_ACCESS_VIOLATION;
            return false;
        }
        auto temp = static_cast<unsigned long>(*flag);
        if (!GetLayeredWindowAttributes(window_handle, color_ref, alpha,
                                        &temp)) {
            error_code = GetLastError();
            *flag = static_cast<LayeredFlag>(temp);
            return false;
        }
        *flag = static_cast<LayeredFlag>(temp);
        return true;
    }

    bool window::set_layered_attrs(HWND window_handle,
                                   COLORREF color_ref,
                                   uint8_t alpha,
                                   LayeredFlag flag) {
        if (!SetLayeredWindowAttributes(window_handle, color_ref, alpha,
                                        static_cast<uint32_t>(flag))) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    HWND window::find(HWND window_handle, SearchFlag7 flag) {
        HWND result = GetWindow(window_handle, static_cast<uint32_t>(flag));
        if (!result) {
            error_code = GetLastError();
        }
        return result;
    }

    HWND window::find_next(HWND window_handle) {
        return find(window_handle, SearchFlag7::HwndNext);
    }

    HWND window::find_prev(HWND window_handle) {
        return find(window_handle, SearchFlag7::HwndPrev);
    }

    HWND window::find_first(HWND window_handle) {
        return find(window_handle, SearchFlag7::HwndFirst);
    }

    HWND window::find_last(HWND window_handle) {
        return find(window_handle, SearchFlag7::HwndLast);
    }

    HWND window::find_owner(HWND window_handle) {
        return find(window_handle, SearchFlag7::Owner);
    }

    HWND window::find_shell() {
        return GetShellWindow();
    }

    HWND window::find_top(HWND window_handle) {
        HWND result = GetTopWindow(window_handle);
        if (!result) {
            error_code = GetLastError();
        }
        return result;
    }

    uint32_t window::get_context_help_id(HWND window_handle) {
        return GetWindowContextHelpId(window_handle);
    }

    bool window::set_context_help_id(HWND window_handle, uint32_t param) {
        if (!SetWindowContextHelpId(window_handle, param)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool window::get_display_affinity(HWND window_handle,
                                      AffinityFlag *affinity) {
        if (!affinity) {
            error_code = STATUS_ACCESS_VIOLATION;
            return false;
        }
        auto temp = static_cast<unsigned long>(*affinity);
        if (!GetWindowDisplayAffinity(window_handle, &temp)) {
            error_code = GetLastError();
            *affinity = static_cast<AffinityFlag>(temp);
            return false;
        }
        *affinity = static_cast<AffinityFlag>(temp);
        return true;
    }

    bool window::set_display_affinity(HWND window_handle,
                                      AffinityFlag affinity) {
        if (!SetWindowDisplayAffinity(window_handle,
                                      static_cast<uint32_t>(affinity))) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool window::get_feedback_setting(HWND window_handle,
                                      FeedbackType feedback,
                                      bool *config,
                                      bool include_ancestor) {
        uint32_t size = sizeof(int32_t);
        int32_t real_config = 0;
        const int32_t is_ok =
                GetWindowFeedbackSetting(window_handle,
                                         static_cast<FEEDBACK_TYPE>(feedback),
                                         include_ancestor
                                                 ? GWFS_INCLUDE_ANCESTORS
                                                 : 0,
                                         &size, &real_config);
        *config = real_config;
        return is_ok;
    }

    bool window::set_feedback_setting(HWND window_handle,
                                      FeedbackType feedback,
                                      const void *config,
                                      uint32_t size) {
        return SetWindowFeedbackSetting(window_handle,
                                        static_cast<FEEDBACK_TYPE>(feedback), 0,
                                        size, config);
    }

    bool window::get_info(HWND window_handle, WINDOWINFO *window_info) {
        if (!GetWindowInfo(window_handle, window_info)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    int32_t window::get_long(HWND window_handle, int32_t offset) {
        const int32_t result = GetWindowLongW(window_handle, offset);
        if (!result) {
            error_code = GetLastError();
        }
        return result;
    }

    int32_t
    window::set_long(HWND window_handle, int32_t offset, int32_t value) {
        const int32_t result = SetWindowLongW(window_handle, offset, value);
        if (!result) {
            error_code = GetLastError();
        }
        return result;
    }

    intptr_t window::get_long_ptr(HWND window_handle, int32_t offset) {
        const intptr_t result = GetWindowLongPtrW(window_handle, offset);
        if (!result) {
            error_code = GetLastError();
        }
        return result;
    }

    intptr_t
    window::set_long_ptr(HWND window_handle, int32_t offset, intptr_t value) {
        const intptr_t result = SetWindowLongPtrW(window_handle, offset, value);
        if (!result) {
            error_code = GetLastError();
        }
        return result;
    }

    uint16_t window::get_word(HWND window_handle, int32_t offset) {
        const uint16_t result = GetWindowWord(window_handle, offset);
        if (!result) {
            error_code = GetLastError();
        }
        return result;
    }

    uint32_t window::get_module_file_name(HWND window_handle,
                                          std::string &file_name) {
        return GetWindowModuleFileNameA(window_handle, file_name.data(),
                                        file_name.size());
    }

    uint32_t window::get_module_file_name(HWND window_handle,
                                          std::wstring &file_name) {
        return GetWindowModuleFileNameW(window_handle, file_name.data(),
                                        file_name.size());
    }

    bool window::get_placement(HWND window_handle,
                               WINDOWPLACEMENT *window_placement) {
        if (!GetWindowPlacement(window_handle, window_placement)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool window::set_placement(HWND window_handle,
                               const WINDOWPLACEMENT *window_placement) {
        if (!SetWindowPlacement(window_handle, window_placement)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool window::get_rect(HWND window_handle, RECT *rect) {
        if (!GetWindowRect(window_handle, rect)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool window::calc_rect(RECT *rect, WindowStyle style, bool include_menu) {
        if (!AdjustWindowRect(rect, static_cast<uint32_t>(style),
                              include_menu ? TRUE : FALSE)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool window::calc_rect(RECT *rect,
                           WindowStyle style,
                           WindowExtendStyle extend_style,
                           bool include_menu) {
        if (!AdjustWindowRectEx(rect, static_cast<uint32_t>(style),
                                include_menu ? TRUE : FALSE,
                                static_cast<uint32_t>(extend_style))) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool window::calc_rect_for_dpi(RECT *rect,
                                   uint32_t dpi,
                                   WindowStyle style,
                                   WindowExtendStyle extend_style,
                                   bool include_menu) {
        if (!AdjustWindowRectExForDpi(rect, static_cast<uint32_t>(style),
                                      include_menu ? TRUE : FALSE,
                                      static_cast<uint32_t>(extend_style),
                                      dpi)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    int32_t window::get_region(HWND window_handle, HRGN region_handle) {
        return GetWindowRgn(window_handle, region_handle);
    }

    int32_t
    window::set_region(HWND window_handle, HRGN region_handle, bool redraw) {
        return SetWindowRgn(window_handle, region_handle,
                            redraw ? TRUE : FALSE);
    }

    int32_t window::get_region_box(HWND window_handle, RECT *rect) {
        return GetWindowRgnBox(window_handle, rect);
    }

    int32_t window::get_text(HWND window_handle, std::string &text) {
        const int32_t result =
                GetWindowTextA(window_handle, text.data(),
                               static_cast<int32_t>(text.size()));
        if (!result) {
            error_code = GetLastError();
        }
        return result;
    }

    int32_t window::get_text(HWND window_handle, std::wstring &text) {
        const int32_t result =
                GetWindowTextW(window_handle, text.data(),
                               static_cast<int32_t>(text.size()));
        if (!result) {
            error_code = GetLastError();
        }
        return result;
    }

    bool window::set_text(HWND window_handle, const std::string &text) {
        if (!SetWindowTextA(window_handle, text.data())) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool window::set_text(HWND window_handle, const std::wstring &text) {
        if (!SetWindowTextW(window_handle, text.data())) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    int32_t window::get_text_length(HWND window_handle) {
        const int32_t result = GetWindowTextLengthW(window_handle);
        if (!result) {
            error_code = GetLastError();
        }
        return result;
    }

    uint32_t window::get_thread_id(HWND window_handle) {
        unsigned long pid = 0;
        const uint32_t tid = GetWindowThreadProcessId(window_handle, &pid);
        if (!tid) {
            error_code = GetLastError();
        }
        return tid;
    }

    uint32_t window::get_proc_id(HWND window_handle) {
        unsigned long pid = 0;
        if (const uint32_t tid = GetWindowThreadProcessId(window_handle, &pid);
            !tid) {
            error_code = GetLastError();
        }
        return pid;
    }

    std::pair<uint32_t, uint32_t>
    window::get_window_tid_and_pid(HWND window_handle) {
        unsigned long pid = 0;
        uint32_t tid = GetWindowThreadProcessId(window_handle, &pid);
        if (!tid) {
            error_code = GetLastError();
        }
        return std::make_pair(tid, pid);
    }

    int32_t window::get_direct_text(HWND window_handle,
                                    std::string &text,
                                    helper::CodePage code_page) {
        std::wstring data(text.size(), L'\0');
        const int32_t result =
                InternalGetWindowText(window_handle, data.data(),
                                      static_cast<int32_t>(data.size()));
        text = helper::convert::wstr_to_str(data, code_page);
        if (!result) {
            error_code = GetLastError();
        }
        return result;
    }

    int32_t window::get_direct_text(HWND window_handle, std::wstring &text) {
        const int32_t result =
                InternalGetWindowText(window_handle, text.data(),
                                      static_cast<int32_t>(text.size()));
        if (!result) {
            error_code = GetLastError();
        }
        return result;
    }

    uint32_t window::get_class_name(HWND window_handle,
                                    std::string &class_name) {
        const uint32_t result =
                RealGetWindowClassA(window_handle, class_name.data(),
                                    class_name.size());
        if (!result) {
            error_code = GetLastError();
        }
        return result;
    }

    uint32_t window::get_class_name(HWND window_handle,
                                    std::wstring &class_name) {
        const uint32_t result =
                RealGetWindowClassW(window_handle, class_name.data(),
                                    class_name.size());
        if (!result) {
            error_code = GetLastError();
        }
        return result;
    }

    void window::switch_window(HWND window_handle, bool UseAccelerator) {
        SwitchToThisWindow(window_handle, UseAccelerator ? TRUE : FALSE);
    }

    bool window::show_help(HWND window_handle,
                           const char *help,
                           uintptr_t data,
                           HelpCommand cmd) {
        if (!WinHelpA(window_handle, help, static_cast<uint32_t>(cmd), data)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool window::show_help(HWND window_handle,
                           const wchar_t *help,
                           uintptr_t data,
                           HelpCommand cmd) {
        if (!WinHelpW(window_handle, help, static_cast<uint32_t>(cmd), data)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    uint32_t window::get_gui_resources(HANDLE proc_handle, ResourceFlag flag) {
        const uint32_t result =
                GetGuiResources(proc_handle, static_cast<uint32_t>(flag));
        if (!result) {
            error_code = GetLastError();
        }
        return result;
    }

    bool window::get_gui_thread_info(uint32_t tid,
                                     GUITHREADINFO *gui_thread_info) {
        if (!GetGUIThreadInfo(tid, gui_thread_info)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool window::convert_to_gui_thread() {
        const int32_t result = IsGUIThread(TRUE);
        if (result == ERROR_NOT_ENOUGH_MEMORY) {
            return false;
        }
        return result;
    }

    bool window::is_gui_thread() {
        return IsGUIThread(FALSE);
    }

    bool window::get_alt_tab_info(HWND window_handle,
                                  int32_t icon_index,
                                  ALTTABINFO *alt_tab_info,
                                  std::string &item_text) {
        if (!GetAltTabInfoA(window_handle, icon_index, alt_tab_info,
                            item_text.data(), item_text.size())) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool window::get_alt_tab_info(HWND window_handle,
                                  int32_t icon_index,
                                  ALTTABINFO *alt_tab_info,
                                  std::wstring &item_text) {
        if (!GetAltTabInfoW(window_handle, icon_index, alt_tab_info,
                            item_text.data(), item_text.size())) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    uintptr_t window::set_timer(HWND window_handle,
                                uintptr_t event_id,
                                TIMERPROC timer_func,
                                uint32_t timeout_ms) {
        const uintptr_t result =
                SetTimer(window_handle, event_id, timeout_ms, timer_func);
        if (!result) {
            error_code = GetLastError();
        }
        return result;
    }

    uintptr_t window::set_mixed_timer(HWND window_handle,
                                      uintptr_t event_id,
                                      TIMERPROC timer_func,
                                      uint32_t timeout_ms,
                                      uint32_t tolerance_delay_ms) {
        const uintptr_t result =
                SetCoalescableTimer(window_handle, event_id, timeout_ms,
                                    timer_func, tolerance_delay_ms);
        if (!result) {
            error_code = GetLastError();
        }
        return result;
    }

    bool window::kill_timer(HWND window_handle, uintptr_t event_id) {
        if (!KillTimer(window_handle, event_id)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    int32_t window::get_system_metrics(MetricCode code) {
        return GetSystemMetrics(static_cast<int32_t>(code));
    }

    int32_t window::get_system_metrics_for_dpi(MetricCode code, uint32_t dpi) {
        return GetSystemMetricsForDpi(static_cast<int32_t>(code), dpi);
    }

    bool window::system_params_info(SystemParameter action,
                                    uint32_t key,
                                    void *value,
                                    SystemParameterFlag flag) {
        if (!SystemParametersInfoW(static_cast<uint32_t>(action), key, value,
                                   static_cast<uint32_t>(flag))) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool window::system_paras_info_for_dpi(SystemParameter action,
                                           uint32_t key,
                                           void *value,
                                           uint32_t dpi,
                                           SystemParameterFlag flag) {
        if (!SystemParametersInfoForDpi(static_cast<uint32_t>(action), key,
                                        value, static_cast<uint32_t>(flag),
                                        dpi)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool window::get_user_object_security(HANDLE obj_handle,
                                          PSECURITY_INFORMATION si,
                                          PSECURITY_DESCRIPTOR sd,
                                          uint32_t size,
                                          uint32_t *real_size) {
        if (!real_size) {
            error_code = STATUS_ACCESS_VIOLATION;
            return false;
        }
        unsigned long temp = *real_size;
        if (!GetUserObjectSecurity(obj_handle, si, sd, size, &temp)) {
            error_code = GetLastError();
            *real_size = temp;
            return false;
        }
        *real_size = temp;
        return true;
    }

    bool window::set_user_object_security(HANDLE obj_handle,
                                          PSECURITY_INFORMATION si,
                                          PSECURITY_DESCRIPTOR sd) {
        if (!SetUserObjectSecurity(obj_handle, si, sd)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    uint32_t
    window::wait_for_multiple_objects(const std::vector<HANDLE> &handles,
                                      QueueType type,
                                      uint32_t milli_seconds,
                                      bool wait_all) {
        const uint32_t result =
                MsgWaitForMultipleObjects(handles.size(), handles.data(),
                                          wait_all ? TRUE : FALSE,
                                          milli_seconds,
                                          static_cast<uint32_t>(type));
        if (result == WAIT_FAILED) {
            error_code = GetLastError();
        }
        return result;
    }

    uint32_t
    window::wait_for_multiple_objects(const std::vector<HANDLE> &handles,
                                      QueueType type,
                                      uint32_t milli_seconds,
                                      WaitFlag flag) {
        const uint32_t result =
                MsgWaitForMultipleObjectsEx(handles.size(), handles.data(),
                                            milli_seconds,
                                            static_cast<uint32_t>(type),
                                            static_cast<uint32_t>(flag));
        if (result == WAIT_FAILED) {
            error_code = GetLastError();
        }
        return result;
    }

    bool window::sound_sentry() {
        return SoundSentry();
    }

    bool
    window::grant_access(HANDLE user_handle, HANDLE job_handle, bool is_grant) {
        if (!UserHandleGrantAccess(user_handle, job_handle, is_grant)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool window::set_additional_foreground_boost_procs(
            HWND top_level_window_handle,
            std::vector<HANDLE> &proc_handles) {
        if (!SetAdditionalForegroundBoostProcesses(top_level_window_handle,
                                                   proc_handles.size(),
                                                   proc_handles.data())) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool window::get_title_bar_info(HWND window_handle,
                                    TITLEBARINFO *title_bar_info) {
        if (!GetTitleBarInfo(window_handle, title_bar_info)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool window::get_auto_rotation_state(RotateState *state) {
        if (!state) {
            error_code = STATUS_ACCESS_VIOLATION;
            return false;
        }
        auto temp = static_cast<AR_STATE>(*state);
        const bool is_ok = GetAutoRotationState(&temp);
        *state = static_cast<RotateState>(temp);
        return is_ok;
    }

    helper::CodePage window::get_code_page() {
        return static_cast<helper::CodePage>(GetKBCodePage());
    }

    bool window::get_combo_box_info(HWND combo_handle,
                                    COMBOBOXINFO *combo_box_info) {
        if (!GetComboBoxInfo(combo_handle, combo_box_info)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    uint32_t window::get_list_box_info(HWND window_handle) {
        return GetListBoxInfo(window_handle);
    }

    bool window::enable_non_client_dpi_scaling(HWND window_handle) {
        if (!EnableNonClientDpiScaling(window_handle)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    uint32_t window::get_dpi_for_system() {
        return GetDpiForSystem();
    }

    uint32_t window::get_system_dpi(HANDLE proc_handle) {
        return GetSystemDpiForProcess(proc_handle);
    }

    int16_t window::get_app_command(LPARAM lparam) {
        return GET_APPCOMMAND_LPARAM(lparam);
    }

    uint16_t window::get_device(LPARAM lparam) {
        return GET_DEVICE_LPARAM(lparam);
    }

    uint16_t window::get_flags(LPARAM lparam) {
        return GET_FLAGS_LPARAM(lparam);
    }

    int16_t window::get_nc_hit_test(WPARAM wparam) {
        return GET_NCHITTEST_WPARAM(wparam);
    }

    int16_t window::get_wheel_delta(WPARAM wparam) {
        return GET_WHEEL_DELTA_WPARAM(wparam);
    }

    wchar_t *window::make_int_resource(uint16_t value) {
        return MAKEINTRESOURCEW(value);
    }

    bool window::is_int_resource(uint16_t value) {
        return IS_INTRESOURCE(value);
    }

    WPARAM window::make_wparam(int32_t low, int32_t high) {
        return MAKEWPARAM(low, high);
    }

    LPARAM window::make_lparam(int32_t low, int32_t high) {
        return MAKELPARAM(low, high);
    }

    LRESULT window::make_lresult(int32_t low, int32_t high) {
        return MAKELRESULT(low, high);
    }

    uint16_t window::get_xbutton(WPARAM wparam) {
        return GET_APPCOMMAND_LPARAM(wparam);
    }

    POINT window::points_to_point(POINTS points) {
        POINT point = {};
        point.x = points.x;
        point.y = points.y;
        return point;
    }

    POINTS window::point_to_points(POINT point) {
        POINTS points = {};
        points.x = static_cast<int16_t>(point.x);
        points.y = static_cast<int16_t>(point.y);
        return points;
    }

    uint32_t window::err_code() const {
        return error_code;
    }

    std::string window::err_string() const {
        std::string result = helper::convert::err_string(error_code);
        return result;
    }

    std::wstring window::err_wstring() const {
        std::wstring result = helper::convert::err_wstring(error_code);
        return result;
    }
} // namespace YanLib::ui::core
