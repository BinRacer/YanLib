//
// Created by forkernel on 2025/4/28.
//

#include "window.h"

namespace YanLib::ui {
HWND window::create(const char *class_name,
    const char                 *window_name,
    HINSTANCE                   instance_handle,
    void                       *param,
    HWND                        parent_window_handle,
    HMENU                       menu_handle,
    int32_t                     x,
    int32_t                     y,
    int32_t                     width,
    int32_t                     height,
    uint32_t                    style,
    uint32_t                    ext_style) {
    HWND result =
        CreateWindowExA(ext_style, class_name, window_name, style, x, y, width,
            height, parent_window_handle, menu_handle, instance_handle, param);
    if (!result) {
        error_code = GetLastError();
    }
    return result;
}

HWND window::create(const wchar_t *class_name,
    const wchar_t                 *window_name,
    HINSTANCE                      instance_handle,
    void                          *param,
    HWND                           parent_window_handle,
    HMENU                          menu_handle,
    int32_t                        x,
    int32_t                        y,
    int32_t                        width,
    int32_t                        height,
    uint32_t                       style,
    uint32_t                       ext_style) {
    HWND result =
        CreateWindowExW(ext_style, class_name, window_name, style, x, y, width,
            height, parent_window_handle, menu_handle, instance_handle, param);
    if (!result) {
        error_code = GetLastError();
    }
    return result;
}

HWND window::create_mdi(const char *class_name,
    const char                     *window_name,
    HINSTANCE                       instance_handle,
    LPARAM                          lparam,
    HWND                            parent_window_handle,
    int32_t                         x,
    int32_t                         y,
    int32_t                         width,
    int32_t                         height,
    uint32_t                        style) {
    HWND result = CreateMDIWindowA(class_name, window_name, style, x, y, width,
        height, parent_window_handle, instance_handle, lparam);
    if (!result) {
        error_code = GetLastError();
    }
    return result;
}

HWND window::create_mdi(const wchar_t *class_name,
    const wchar_t                     *window_name,
    HINSTANCE                          instance_handle,
    LPARAM                             lparam,
    HWND                               parent_window_handle,
    int32_t                            x,
    int32_t                            y,
    int32_t                            width,
    int32_t                            height,
    uint32_t                           style) {
    HWND result = CreateMDIWindowW(class_name, window_name, style, x, y, width,
        height, parent_window_handle, instance_handle, lparam);
    if (!result) {
        error_code = GetLastError();
    }
    return result;
}

bool window::show(HWND window_handle, int32_t cmd_show) const {
    return ShowWindow(window_handle, cmd_show);
}

bool window::show_async(HWND window_handle, int32_t cmd_show) const {
    return ShowWindowAsync(window_handle, cmd_show);
}

bool window::update(HWND window_handle) const {
    return UpdateWindow(window_handle);
}

bool window::update_layered(HWND window_handle,
    HDC                          hdc_dst,
    POINT                       *coordinate_dst,
    SIZE                        *size,
    HDC                          hdc_src,
    POINT                       *coordinate_src,
    COLORREF                     color_ref,
    BLENDFUNCTION               *blend_fn,
    uint32_t                     flag) {
    if (!UpdateLayeredWindow(window_handle, hdc_dst, coordinate_dst, size,
            hdc_src, coordinate_src, color_ref, blend_fn, flag)) {
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

bool window::animate(HWND window_handle, uint32_t time, uint32_t flag) {
    if (!AnimateWindow(window_handle, time, flag)) {
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

bool window::close(HWND window_handle, bool is_force) {
    if (!EndTask(window_handle, FALSE, is_force ? TRUE : FALSE)) {
        error_code = GetLastError();
        return false;
    }
    return true;
}

bool window::exit(uint32_t flag, uint32_t reason) {
    if (!ExitWindowsEx(flag, reason)) {
        error_code = GetLastError();
        return false;
    }
    return true;
}

bool window::destroy(HWND window_handle) {
    if (!DestroyWindow(window_handle)) {
        error_code = GetLastError();
        return false;
    }
    return true;
}

bool window::enable(HWND window_handle, bool enable) {
    return EnableWindow(window_handle, enable ? TRUE : FALSE);
}

bool window::enum_windows(WNDENUMPROC enum_func, LPARAM lparam) {
    if (!EnumWindows(enum_func, lparam)) {
        error_code = GetLastError();
        return false;
    }
    return true;
}

bool window::enum_child_windows(HWND parent_window_handle,
    WNDENUMPROC                      enum_func,
    LPARAM                           lparam) {
    return EnumChildWindows(parent_window_handle, enum_func, lparam);
}

bool window::enum_windows(uint32_t tid, WNDENUMPROC fn, LPARAM lparam) {
    return EnumThreadWindows(tid, fn, lparam);
}

HWND window::find(const char *class_name, const char *window_name) {
    return FindWindowA(class_name, window_name);
}

HWND window::find(const wchar_t *class_name, const wchar_t *window_name) {
    return FindWindowW(class_name, window_name);
}

HWND window::find(HWND parent_window_handle,
    const char        *class_name,
    const char        *window_name) {
    HWND result =
        FindWindowExA(parent_window_handle, nullptr, class_name, window_name);
    if (!result) {
        error_code = GetLastError();
    }
    return result;
}

HWND window::find(HWND parent_window_handle,
    const wchar_t     *class_name,
    const wchar_t     *window_name) {
    HWND result =
        FindWindowExW(parent_window_handle, nullptr, class_name, window_name);
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
    int32_t            x,
    int32_t            y,
    int32_t            width,
    int32_t            height,
    bool               is_repaint) {
    if (!MoveWindow(
            window_handle, x, y, width, height, is_repaint ? TRUE : FALSE)) {
        error_code = GetLastError();
        return false;
    }
    return true;
}

bool window::print(HWND window_handle, HDC dc_handle, uint32_t flag) {
    return PrintWindow(window_handle, dc_handle, flag);
}

bool window::redraw(HWND window_handle,
    const RECT          *rect,
    HRGN                 region_handle,
    uint32_t             flag) {
    return RedrawWindow(window_handle, rect, region_handle, flag);
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

uint16_t window::tile(HWND   parent_window_handle,
    uint32_t                 how,
    const RECT              *rect,
    const std::vector<HWND> &child) {
    uint16_t result = TileWindows(
        parent_window_handle, how, rect, child.size(), child.data());
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

HWND window::get_ancestor(HWND window_handle, uint32_t flag) {
    return GetAncestor(window_handle, flag);
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
    bool    is_ok   = false;
    HMODULE hmodule = nullptr;
    do {
        hmodule = LoadLibraryW(L"user32.dll");
        if (!hmodule) {
            error_code = GetLastError();
            break;
        }
        typedef int32_t(CALLBACK * fn)(HWND);
        auto IsWindowArranged =
            reinterpret_cast<fn>(GetProcAddress(hmodule, "IsWindowArranged"));
        if (!IsWindowArranged) {
            error_code = GetLastError();
            break;
        }
        if (!IsWindowArranged(window_handle)) {
            error_code = GetLastError();
            is_ok      = true;
            break;
        }
    } while (false);
    if (hmodule) {
        FreeLibrary(hmodule);
    }
    return is_ok;
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

bool window::is_child(HWND parent_window_handle, HWND window_handle) {
    return IsChild(parent_window_handle, window_handle);
}

bool window::is_popup_exist() {
    return AnyPopup();
}

uint32_t window::arrange_minimize(HWND window_handle) {
    uint32_t height = ArrangeIconicWindows(window_handle);
    if (!height) {
        error_code = GetLastError();
    }
    return height;
}

bool window::get_proc_default_layout(uint32_t *default_layout) {
    if (!GetProcessDefaultLayout(
            reinterpret_cast<unsigned long *>(default_layout))) {
        error_code = GetLastError();
        return false;
    }
    return true;
}

bool window::set_proc_default_layout(uint32_t default_layout) {
    if (!SetProcessDefaultLayout(default_layout)) {
        error_code = GetLastError();
        return false;
    }
    return true;
}

bool window::set_pos(HWND window_handle,
    HWND                  insert_after_window_handle,
    int32_t               x,
    int32_t               y,
    int32_t               cx,
    int32_t               cy,
    uint32_t              flag) {
    if (!SetWindowPos(
            window_handle, insert_after_window_handle, x, y, cx, cy, flag)) {
        error_code = GetLastError();
        return false;
    }
    return true;
}

bool window::calc_popup_pos(const POINT *anchor_coordinate,
    const SIZE                          *window_size,
    uint32_t                             flag,
    RECT                                *exclude_rect,
    RECT                                *popup_window_position) {
    if (!CalculatePopupWindowPosition(anchor_coordinate, window_size, flag,
            exclude_rect, popup_window_position)) {
        error_code = GetLastError();
        return false;
    }
    return true;
}

HWND window::find_top_child(HWND parent_window_handle, POINT coordinate) {
    return ChildWindowFromPoint(parent_window_handle, coordinate);
}

HWND window::find_top_child(HWND parent_window_handle,
    POINT                        coordinate,
    uint32_t                     flag) {
    return ChildWindowFromPointEx(parent_window_handle, coordinate, flag);
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
    HWND                                  to_window_handle,
    std::vector<POINT>                   &coordinates) {
    int32_t result = MapWindowPoints(from_window_handle, to_window_handle,
        coordinates.data(), coordinates.size());
    error_code     = GetLastError();
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
    HWND                          window_handle,
    uint32_t                      msg,
    WPARAM                        wparam,
    LPARAM                        lparam) {
    return CallWindowProcW(prev_wnd_func, window_handle, msg, wparam, lparam);
}

LRESULT
window::default_proc(HWND window_handle,
    uint32_t              msg,
    WPARAM                wparam,
    LPARAM                lparam) {
    return DefWindowProcW(window_handle, msg, wparam, lparam);
}

LRESULT window::default_mdi_proc(HWND window_handle,
    HWND                              client_mdi_window_handle,
    uint32_t                          msg,
    WPARAM                            wparam,
    LPARAM                            lparam) {
    return DefFrameProcW(
        window_handle, client_mdi_window_handle, msg, wparam, lparam);
}

LRESULT window::default_mdi_child_proc(HWND window_handle,
    uint32_t                                msg,
    WPARAM                                  wparam,
    LPARAM                                  lparam) {
    return DefMDIChildProcW(window_handle, msg, wparam, lparam);
}

uint16_t window::cascade(HWND parent_window_handle,
    uint32_t                  how,
    const RECT               *rect,
    std::vector<HWND>        &child) {
    uint16_t count = CascadeWindows(
        parent_window_handle, how, rect, child.size(), child.data());
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
    COLORREF                       *color_ref,
    uint8_t                        *alpha,
    uint32_t                       *flag) {
    if (!GetLayeredWindowAttributes(window_handle, color_ref, alpha,
            reinterpret_cast<unsigned long *>(flag))) {
        error_code = GetLastError();
        return false;
    }
    return true;
}

bool window::set_layered_attrs(HWND window_handle,
    COLORREF                        color_ref,
    uint8_t                         alpha,
    uint32_t                        flag) {
    if (!SetLayeredWindowAttributes(window_handle, color_ref, alpha, flag)) {
        error_code = GetLastError();
        return false;
    }
    return true;
}

HWND window::find(HWND window_handle, uint32_t cmd) {
    HWND result = GetWindow(window_handle, cmd);
    if (!result) {
        error_code = GetLastError();
    }
    return result;
}

HWND window::find_next(HWND window_handle, uint32_t cmd) {
    return GetNextWindow(window_handle, cmd);
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

bool window::get_display_affinity(HWND window_handle, uint32_t *affinity) {
    if (!GetWindowDisplayAffinity(
            window_handle, reinterpret_cast<unsigned long *>(affinity))) {
        error_code = GetLastError();
        return false;
    }
    return true;
}

bool window::set_display_affinity(HWND window_handle, uint32_t affinity) {
    if (!SetWindowDisplayAffinity(window_handle, affinity)) {
        error_code = GetLastError();
        return false;
    }
    return true;
}

DPI_AWARENESS_CONTEXT window::get_dpi_aware_context(HWND window_handle) {
    return GetWindowDpiAwarenessContext(window_handle);
}

DPI_HOSTING_BEHAVIOR window::get_dpi_hosting_behavior(HWND window_handle) {
    return GetWindowDpiHostingBehavior(window_handle);
}

bool window::get_feedback_setting(HWND window_handle,
    FEEDBACK_TYPE                      feedback,
    uint32_t                           flag,
    int                               *real_config) {
    uint32_t size = sizeof(int);
    return GetWindowFeedbackSetting(
        window_handle, feedback, flag, &size, real_config);
}

bool window::set_feedback_setting(HWND window_handle,
    FEEDBACK_TYPE                      feedback,
    uint32_t                           size,
    const int                         *config) {
    return SetWindowFeedbackSetting(window_handle, feedback, 0, size, config);
}

bool window::get_info(HWND window_handle, WINDOWINFO *window_info) {
    if (!GetWindowInfo(window_handle, window_info)) {
        error_code = GetLastError();
        return false;
    }
    return true;
}

long window::get_long(HWND window_handle, int32_t index) {
    long result = GetWindowLongW(window_handle, index);
    if (!result) {
        error_code = GetLastError();
    }
    return result;
}

long window::set_long(HWND window_handle, int32_t index, long value) {
    long result = SetWindowLongW(window_handle, index, value);
    if (!result) {
        error_code = GetLastError();
    }
    return result;
}

LONG_PTR window::get_long_ptr(HWND window_handle, int32_t index) {
    LONG_PTR result = GetWindowLongPtrW(window_handle, index);
    if (!result) {
        error_code = GetLastError();
    }
    return result;
}

LONG_PTR
window::set_long_ptr(HWND window_handle, int32_t index, LONG_PTR value) {
    LONG_PTR result = SetWindowLongPtrW(window_handle, index, value);
    if (!result) {
        error_code = GetLastError();
    }
    return result;
}

uint32_t window::get_module_file_name(HWND window_handle,
    std::string                           &file_name) {
    return GetWindowModuleFileNameA(
        window_handle, file_name.data(), file_name.size());
}

uint32_t window::get_module_file_name(HWND window_handle,
    std::wstring                          &file_name) {
    return GetWindowModuleFileNameW(
        window_handle, file_name.data(), file_name.size());
}

bool window::get_placement(HWND window_handle,
    WINDOWPLACEMENT            *window_placement) {
    if (!GetWindowPlacement(window_handle, window_placement)) {
        error_code = GetLastError();
        return false;
    }
    return true;
}

bool window::set_placement(HWND window_handle,
    const WINDOWPLACEMENT      *window_placement) {
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

bool window::adjust_rect(RECT *rect, uint32_t style, bool menu) {
    if (!AdjustWindowRect(rect, style, menu ? TRUE : FALSE)) {
        error_code = GetLastError();
        return false;
    }
    return true;
}

bool window::adjust_rect(RECT *rect,
    uint32_t                   style,
    bool                       menu,
    uint32_t                   ext_style) {
    if (!AdjustWindowRectEx(rect, style, menu ? TRUE : FALSE, ext_style)) {
        error_code = GetLastError();
        return false;
    }
    return true;
}

bool window::adjust_rect_for_dpi(RECT *rect,
    uint32_t                           style,
    bool                               menu,
    uint32_t                           ext_style,
    uint32_t                           dpi) {
    if (!AdjustWindowRectExForDpi(
            rect, style, menu ? TRUE : FALSE, ext_style, dpi)) {
        error_code = GetLastError();
        return false;
    }
    return true;
}

int32_t window::get_region(HWND window_handle, HRGN region_handle) {
    return GetWindowRgn(window_handle, region_handle);
}

int32_t
window::set_region(HWND window_handle, HRGN region_handle, bool is_redraw) {
    return SetWindowRgn(window_handle, region_handle, is_redraw ? TRUE : FALSE);
}

int32_t window::get_region_box(HWND window_handle, RECT *rect) {
    return GetWindowRgnBox(window_handle, rect);
}

int32_t window::get_text(HWND window_handle, std::string &text) {
    int32_t result = GetWindowTextA(
        window_handle, text.data(), static_cast<int>(text.size()));
    if (!result) {
        error_code = GetLastError();
    }
    return result;
}

int32_t window::get_text(HWND window_handle, std::wstring &text) {
    int32_t result = GetWindowTextW(
        window_handle, text.data(), static_cast<int>(text.size()));
    if (!result) {
        error_code = GetLastError();
    }
    return result;
}

bool window::set_text(HWND window_handle, const char *text) {
    if (!SetWindowTextA(window_handle, text)) {
        error_code = GetLastError();
        return false;
    }
    return true;
}

bool window::set_text(HWND window_handle, const wchar_t *text) {
    if (!SetWindowTextW(window_handle, text)) {
        error_code = GetLastError();
        return false;
    }
    return true;
}

int32_t window::get_text_length(HWND window_handle) {
    int32_t result = GetWindowTextLengthW(window_handle);
    if (!result) {
        error_code = GetLastError();
    }
    return result;
}

uint32_t window::get_thread_id(HWND window_handle) {
    uint32_t pid = 0;
    uint32_t tid = GetWindowThreadProcessId(
        window_handle, reinterpret_cast<unsigned long *>(&pid));
    if (!tid) {
        error_code = GetLastError();
    }
    return tid;
}

uint32_t window::get_proc_id(HWND window_handle) {
    uint32_t pid = 0;
    uint32_t tid = GetWindowThreadProcessId(
        window_handle, reinterpret_cast<unsigned long *>(&pid));
    if (!tid) {
        error_code = GetLastError();
    }
    return pid;
}

std::pair<uint32_t, uint32_t> window::get_window_tid_and_pid(
    HWND window_handle) {
    uint32_t pid = 0;
    uint32_t tid = GetWindowThreadProcessId(
        window_handle, reinterpret_cast<unsigned long *>(&pid));
    if (!tid) {
        error_code = GetLastError();
    }
    return std::make_pair(tid, pid);
}

uint16_t window::get_word(HWND window_handle, int32_t index) {
    uint16_t result = GetWindowWord(window_handle, index);
    if (!result) {
        error_code = GetLastError();
    }
    return result;
}

int32_t window::get_direct_text(HWND window_handle, std::string &text) {
    std::wstring data(text.size(), L'\0');
    int32_t      result = InternalGetWindowText(
        window_handle, data.data(), static_cast<int>(data.size()));
    text = helper::convert::wstr_to_str(data);
    if (!result) {
        error_code = GetLastError();
    }
    return result;
}

int32_t window::get_direct_text(HWND window_handle, std::wstring &text) {
    int32_t result = InternalGetWindowText(
        window_handle, text.data(), static_cast<int>(text.size()));
    if (!result) {
        error_code = GetLastError();
    }
    return result;
}

uint32_t window::get_class(HWND window_handle, std::string &class_name) {
    uint32_t result = RealGetWindowClassA(
        window_handle, class_name.data(), class_name.size());
    if (!result) {
        error_code = GetLastError();
    }
    return result;
}

uint32_t window::get_class(HWND window_handle, std::wstring &class_name) {
    uint32_t result = RealGetWindowClassW(
        window_handle, class_name.data(), class_name.size());
    if (!result) {
        error_code = GetLastError();
    }
    return result;
}

void window::switch_window(HWND window_handle, bool unknown) {
    SwitchToThisWindow(window_handle, unknown ? TRUE : FALSE);
}

bool window::show_help(HWND window_handle,
    const char             *help,
    uint32_t                cmd,
    ULONG_PTR               data) {
    if (!WinHelpA(window_handle, help, cmd, data)) {
        error_code = GetLastError();
        return false;
    }
    return true;
}

bool window::show_help(HWND window_handle,
    const wchar_t          *help,
    uint32_t                cmd,
    ULONG_PTR               data) {
    if (!WinHelpW(window_handle, help, cmd, data)) {
        error_code = GetLastError();
        return false;
    }
    return true;
}

uint32_t window::get_gui_resources(HANDLE proc_handle, uint32_t flag) {
    uint32_t result = GetGuiResources(proc_handle, flag);
    if (!result) {
        error_code = GetLastError();
    }
    return result;
}

bool window::get_gui_thread_info(uint32_t tid, GUITHREADINFO *gui_thread_info) {
    if (!GetGUIThreadInfo(tid, gui_thread_info)) {
        error_code = GetLastError();
        return false;
    }
    return true;
}

bool window::is_gui_thread(bool is_convert) {
    int result = IsGUIThread(is_convert ? TRUE : FALSE);
    if (result == ERROR_NOT_ENOUGH_MEMORY) {
        return false;
    }
    return result;
}

bool window::get_alt_tab_info(HWND window_handle,
    int32_t                        item_index,
    ALTTABINFO                    *alt_tab_info,
    std::string                   &item_text) {
    if (!GetAltTabInfoA(window_handle, item_index, alt_tab_info,
            item_text.data(), item_text.size())) {
        error_code = GetLastError();
        return false;
    }
    return true;
}

bool window::get_alt_tab_info(HWND window_handle,
    int32_t                        item_index,
    ALTTABINFO                    *alt_tab_info,
    std::wstring                  &item_text) {
    if (!GetAltTabInfoW(window_handle, item_index, alt_tab_info,
            item_text.data(), item_text.size())) {
        error_code = GetLastError();
        return false;
    }
    return true;
}

UINT_PTR window::set_timer(HWND window_handle,
    UINT_PTR                    event_id,
    uint32_t                    elapse,
    TIMERPROC                   timer_func) {
    UINT_PTR result = SetTimer(window_handle, event_id, elapse, timer_func);
    if (!result) {
        error_code = GetLastError();
    }
    return result;
}

UINT_PTR window::set_coalescable_timer(HWND window_handle,
    UINT_PTR                                event_id,
    uint32_t                                elapse,
    TIMERPROC                               timer_func,
    uint32_t                                tolerance_delay) {
    UINT_PTR result = SetCoalescableTimer(
        window_handle, event_id, elapse, timer_func, tolerance_delay);
    if (!result) {
        error_code = GetLastError();
    }
    return result;
}

bool window::kill_timer(HWND window_handle, UINT_PTR event_id) {
    if (!KillTimer(window_handle, event_id)) {
        error_code = GetLastError();
        return false;
    }
    return true;
}

bool window::create_shutdown_reason(HWND window_handle, std::string &reason) {
    std::wstring data = helper::convert::str_to_wstr(reason);
    if (!ShutdownBlockReasonCreate(window_handle, data.data())) {
        error_code = GetLastError();
        return false;
    }
    return true;
}

bool window::create_shutdown_reason(HWND window_handle,
    const std::wstring                  &reason) {
    if (!ShutdownBlockReasonCreate(window_handle, reason.data())) {
        error_code = GetLastError();
        return false;
    }
    return true;
}

bool window::destroy_shutdown_reason(HWND window_handle) {
    if (!ShutdownBlockReasonDestroy(window_handle)) {
        error_code = GetLastError();
        return false;
    }
    return true;
}

bool window::query_shutdown_reason(HWND window_handle,
    std::string                        &reason,
    uint32_t                           *real_size) {
    std::wstring data = helper::convert::str_to_wstr(reason);
    *real_size        = data.size();
    if (!ShutdownBlockReasonQuery(window_handle, data.data(),
            reinterpret_cast<unsigned long *>(real_size))) {
        error_code = GetLastError();
        return false;
    }
    return true;
}

bool window::query_shutdown_reason(HWND window_handle,
    std::wstring                       &reason,
    uint32_t                           *real_size) {
    if (!ShutdownBlockReasonQuery(window_handle, reason.data(),
            reinterpret_cast<unsigned long *>(real_size))) {
        error_code = GetLastError();
        return false;
    }
    return true;
}

int window::get_system_metrics(int flag) {
    return GetSystemMetrics(flag);
}

bool window::system_params_info(uint32_t ui_action,
    uint32_t                             ui_param,
    void                                *param,
    uint32_t                             win_ini) {
    if (!SystemParametersInfoW(ui_action, ui_param, param, win_ini)) {
        error_code = GetLastError();
        return false;
    }
    return true;
}

bool window::system_paras_info_for_dpi(uint32_t ui_action,
    uint32_t                                    ui_param,
    void                                       *param,
    uint32_t                                    win_ini,
    uint32_t                                    dpi) {
    if (!SystemParametersInfoForDpi(ui_action, ui_param, param, win_ini, dpi)) {
        error_code = GetLastError();
        return false;
    }
    return true;
}

bool window::get_user_object_security(HANDLE obj_handle,
    PSECURITY_INFORMATION                    si,
    PSECURITY_DESCRIPTOR                     sd,
    uint32_t                                 size,
    uint32_t                                *real_size) {
    if (!GetUserObjectSecurity(obj_handle, si, sd, size,
            reinterpret_cast<unsigned long *>(real_size))) {
        error_code = GetLastError();
        return false;
    }
    return true;
}

bool window::set_user_object_security(HANDLE obj_handle,
    PSECURITY_INFORMATION                    si,
    PSECURITY_DESCRIPTOR                     sd) {
    if (!SetUserObjectSecurity(obj_handle, si, sd)) {
        error_code = GetLastError();
        return false;
    }
    return true;
}

uint32_t window::wait_for_multiple_objects(std::vector<HANDLE> &handles,
    bool                                                        wait_all,
    uint32_t                                                    milli_seconds,
    uint32_t                                                    wake_mask) {
    uint32_t result = MsgWaitForMultipleObjects(handles.size(), handles.data(),
        wait_all ? TRUE : FALSE, milli_seconds, wake_mask);
    if (result == WAIT_FAILED) {
        error_code = GetLastError();
    }
    return result;
}

uint32_t window::wait_for_multiple_objects(std::vector<HANDLE> &handles,
    uint32_t                                                    milli_seconds,
    uint32_t                                                    wake_mask,
    uint32_t                                                    flag) {
    uint32_t result = MsgWaitForMultipleObjectsEx(
        handles.size(), handles.data(), milli_seconds, wake_mask, flag);
    if (result == WAIT_FAILED) {
        error_code = GetLastError();
    }
    return result;
}

HDEVNOTIFY window::register_device_notify(HANDLE recipient_handle,
    void                                        *notification_filter,
    uint32_t                                     flag) {
    HDEVNOTIFY result = RegisterDeviceNotificationW(
        recipient_handle, notification_filter, flag);
    if (!result) {
        error_code = GetLastError();
    }
    return result;
}

bool window::unregister_device_notify(HDEVNOTIFY device_notify_handle) {
    if (!UnregisterDeviceNotification(device_notify_handle)) {
        error_code = GetLastError();
        return false;
    }
    return true;
}

HPOWERNOTIFY window::register_power_setting_notify(HANDLE recipient_handle,
    const GUID                                           *power_setting_guid,
    uint32_t                                              flag) {
    HPOWERNOTIFY result = RegisterPowerSettingNotification(
        recipient_handle, power_setting_guid, flag);
    if (!result) {
        error_code = GetLastError();
    }
    return result;
}

bool window::unregister_power_setting_notify(HPOWERNOTIFY power_notify_handle) {
    if (!UnregisterPowerSettingNotification(power_notify_handle)) {
        error_code = GetLastError();
        return false;
    }
    return true;
}

HPOWERNOTIFY window::register_suspend_resume_notify(HANDLE recipient_handle,
    uint32_t                                               flag) {
    HPOWERNOTIFY result =
        RegisterSuspendResumeNotification(recipient_handle, flag);
    if (!result) {
        error_code = GetLastError();
    }
    return result;
}

bool window::unregister_suspend_resume_notify(
    HPOWERNOTIFY power_notify_handle) {
    if (!UnregisterSuspendResumeNotification(power_notify_handle)) {
        error_code = GetLastError();
        return false;
    }
    return true;
}

bool window::register_tooltip_dismiss_notify(HWND window_handle) {
    return RegisterForTooltipDismissNotification(window_handle, TDF_REGISTER);
}

bool window::unregister_tooltip_dismiss_notify(HWND window_handle) {
    return RegisterForTooltipDismissNotification(window_handle, TDF_UNREGISTER);
}

bool window::sound_sentry() {
    return SoundSentry();
}

bool window::grant_access(HANDLE user_handle,
    HANDLE                       job_handle,
    bool                         is_grant) {
    if (!UserHandleGrantAccess(user_handle, job_handle, is_grant)) {
        error_code = GetLastError();
        return false;
    }
    return true;
}

bool window::set_additional_foreground_boost_procs(HWND top_level_window_handle,
    std::vector<HANDLE>                                &proc_handles) {
    if (!SetAdditionalForegroundBoostProcesses(top_level_window_handle,
            proc_handles.size(), proc_handles.data())) {
        error_code = GetLastError();
        return false;
    }
    return true;
}

bool window::get_title_bar_info(HWND window_handle,
    TITLEBARINFO                    *title_bar_info) {
    if (!GetTitleBarInfo(window_handle, title_bar_info)) {
        error_code = GetLastError();
        return false;
    }
    return true;
}

bool window::get_auto_rotation_state(AR_STATE *state) {
    return GetAutoRotationState(state);
}

helper::CodePage window::get_code_page() {
    return static_cast<helper::CodePage>(GetKBCodePage());
}

bool window::get_combobox_info(HWND combo_handle, COMBOBOXINFO *combobox_info) {
    if (!GetComboBoxInfo(combo_handle, combobox_info)) {
        error_code = GetLastError();
        return false;
    }
    return true;
}

uint32_t window::get_listbox_info(HWND window_handle) {
    return GetListBoxInfo(window_handle);
}

bool window::is_dpi_aware_contexts_equal(DPI_AWARENESS_CONTEXT context1,
    DPI_AWARENESS_CONTEXT                                      context2) {
    return AreDpiAwarenessContextsEqual(context1, context2);
}

bool window::enable_non_client_dpi_scaling(HWND window_handle) {
    if (!EnableNonClientDpiScaling(window_handle)) {
        error_code = GetLastError();
        return false;
    }
    return true;
}

bool window::is_proc_dpi_aware() {
    return IsProcessDPIAware();
}

bool window::is_valid_dpi_aware_context(DPI_AWARENESS_CONTEXT value) {
    return IsValidDpiAwarenessContext(value);
}

uint32_t window::get_dpi_for_system() {
    return GetDpiForSystem();
}

uint32_t window::get_dpi_from_dpi_aware_context(DPI_AWARENESS_CONTEXT value) {
    return GetDpiFromDpiAwarenessContext(value);
}

DPI_AWARENESS window::get_aware_from_dpi_aware_context(
    DPI_AWARENESS_CONTEXT value) {
    return GetAwarenessFromDpiAwarenessContext(value);
}

DPI_AWARENESS_CONTEXT window::get_proc_dpi_aware_context(HANDLE proc_handle) {
    return GetDpiAwarenessContextForProcess(proc_handle);
}

int32_t window::get_system_metrics_for_dpi(int32_t index, uint32_t dpi) {
    int32_t result = GetSystemMetricsForDpi(index, dpi);
    if (!result) {
        error_code = GetLastError();
    }
    return result;
}

uint32_t window::get_system_dpi(HANDLE proc_handle) {
    return GetSystemDpiForProcess(proc_handle);
}

HRESULT window::get_proc_dpi_aware(HANDLE proc_handle,
    PROCESS_DPI_AWARENESS                *value) {
    return GetProcessDpiAwareness(proc_handle, value);
}

HRESULT window::set_proc_dpi_aware(PROCESS_DPI_AWARENESS value) {
    return SetProcessDpiAwareness(value);
}

bool window::set_proc_dpi_aware_context(DPI_AWARENESS_CONTEXT value) {
    if (!SetProcessDpiAwarenessContext(value)) {
        error_code = GetLastError();
        return false;
    }
    return true;
}

DPI_AWARENESS_CONTEXT window::get_thread_dpi_aware_context() {
    return GetThreadDpiAwarenessContext();
}

DPI_AWARENESS_CONTEXT window::set_thread_dpi_aware_context(
    DPI_AWARENESS_CONTEXT dpi_context) {
    return SetThreadDpiAwarenessContext(dpi_context);
}

DPI_HOSTING_BEHAVIOR window::get_thread_dpi_hosting_behavior() {
    return GetThreadDpiHostingBehavior();
}

DPI_HOSTING_BEHAVIOR window::set_thread_dpi_hosting_behavior(
    DPI_HOSTING_BEHAVIOR value) {
    return SetThreadDpiHostingBehavior(value);
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

WPARAM window::make_wparam(long low, long high) {
    return MAKEWPARAM(low, high);
}

LPARAM window::make_lparam(long low, long high) {
    return MAKELPARAM(low, high);
}

LRESULT window::make_lresult(long low, long high) {
    return MAKELRESULT(low, high);
}

uint16_t window::get_xbutton(WPARAM wparam) {
    return GET_APPCOMMAND_LPARAM(wparam);
}

POINT window::points_to_point(POINTS points) {
    POINT point = {};
    point.x     = points.x;
    point.y     = points.y;
    return point;
}

POINTS window::point_to_points(POINT point) {
    POINTS points = {};
    points.x      = static_cast<int16_t>(point.x);
    points.y      = static_cast<int16_t>(point.y);
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
} // namespace YanLib::ui
