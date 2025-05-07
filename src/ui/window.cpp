//
// Created by forkernel on 2025/4/28.
//

#include "window.h"

namespace YanLib::ui {
HWND window::create(const char *class_name,
    const char                 *window_name,
    HINSTANCE                   instance_handle,
    void                       *param,
    HWND                        hwnd_parent,
    HMENU                       menu_handle,
    int32_t                     x,
    int32_t                     y,
    int32_t                     width,
    int32_t                     height,
    uint32_t                    style,
    uint32_t                    ext_style) {
    HWND hwnd_handle =
        CreateWindowExA(ext_style, class_name, window_name, style, x, y, width,
            height, hwnd_parent, menu_handle, instance_handle, param);
    if (!hwnd_handle) {
        error_code = GetLastError();
    }
    return hwnd_handle;
}

HWND window::create(const wchar_t *class_name,
    const wchar_t                 *window_name,
    HINSTANCE                      instance_handle,
    void                          *param,
    HWND                           hwnd_parent,
    HMENU                          menu_handle,
    int32_t                        x,
    int32_t                        y,
    int32_t                        width,
    int32_t                        height,
    uint32_t                       style,
    uint32_t                       ext_style) {
    HWND hwnd_handle =
        CreateWindowExW(ext_style, class_name, window_name, style, x, y, width,
            height, hwnd_parent, menu_handle, instance_handle, param);
    if (!hwnd_handle) {
        error_code = GetLastError();
    }
    return hwnd_handle;
}

HWND window::create_mdi(const char *class_name,
    const char                     *window_name,
    HINSTANCE                       instance_handle,
    LPARAM                          lparam,
    HWND                            hwnd_parent,
    int32_t                         x,
    int32_t                         y,
    int32_t                         width,
    int32_t                         height,
    uint32_t                        style) {
    HWND hwnd_handle = CreateMDIWindowA(class_name, window_name, style, x, y,
        width, height, hwnd_parent, instance_handle, lparam);
    if (!hwnd_handle) {
        error_code = GetLastError();
    }
    return hwnd_handle;
}

HWND window::create_mdi(const wchar_t *class_name,
    const wchar_t                     *window_name,
    HINSTANCE                          instance_handle,
    LPARAM                             lparam,
    HWND                               hwnd_parent,
    int32_t                            x,
    int32_t                            y,
    int32_t                            width,
    int32_t                            height,
    uint32_t                           style) {
    HWND hwnd_handle = CreateMDIWindowW(class_name, window_name, style, x, y,
        width, height, hwnd_parent, instance_handle, lparam);
    if (!hwnd_handle) {
        error_code = GetLastError();
    }
    return hwnd_handle;
}

WNDCLASSEXA window::make_class(const char *class_name,
    WNDPROC                                window_proc,
    HINSTANCE                              instance_handle,
    uint32_t                               style,
    const char                            *menu_name,
    int32_t                                class_extra_size,
    int32_t                                window_extra_size,
    HICON                                  icon_handle,
    HCURSOR                                cursor_handle,
    HBRUSH                                 brush_background_handle,
    HICON                                  icon_small_handle) {
    WNDCLASSEXA wnd_class   = {};
    wnd_class.cbSize        = sizeof(WNDCLASSEXA);
    wnd_class.style         = style;
    wnd_class.lpfnWndProc   = window_proc;
    wnd_class.cbClsExtra    = class_extra_size;
    wnd_class.cbWndExtra    = window_extra_size;
    wnd_class.hInstance     = instance_handle;
    wnd_class.hIcon         = icon_handle;
    wnd_class.hCursor       = cursor_handle;
    wnd_class.hbrBackground = brush_background_handle;
    wnd_class.lpszMenuName  = menu_name;
    wnd_class.lpszClassName = class_name;
    wnd_class.hIconSm       = icon_small_handle;
    return wnd_class;
}

WNDCLASSEXW window::make_class(const wchar_t *class_name,
    WNDPROC                                   window_proc,
    HINSTANCE                                 instance_handle,
    uint32_t                                  style,
    const wchar_t                            *menu_name,
    int32_t                                   class_extra_size,
    int32_t                                   window_extra_size,
    HICON                                     icon_handle,
    HCURSOR                                   cursor_handle,
    HBRUSH                                    brush_background_handle,
    HICON                                     icon_small_handle) {
    WNDCLASSEXW wnd_class   = {};
    wnd_class.cbSize        = sizeof(WNDCLASSEXW);
    wnd_class.style         = style;
    wnd_class.lpfnWndProc   = window_proc;
    wnd_class.cbClsExtra    = class_extra_size;
    wnd_class.cbWndExtra    = window_extra_size;
    wnd_class.hInstance     = instance_handle;
    wnd_class.hIcon         = icon_handle;
    wnd_class.hCursor       = cursor_handle;
    wnd_class.hbrBackground = brush_background_handle;
    wnd_class.lpszMenuName  = menu_name;
    wnd_class.lpszClassName = class_name;
    wnd_class.hIconSm       = icon_small_handle;
    return wnd_class;
}

ATOM window::register_class(const WNDCLASSEXA *window_class) {
    ATOM result = RegisterClassExA(window_class);
    if (!result) {
        error_code = GetLastError();
    }
    return result;
}

ATOM window::register_class(const WNDCLASSEXW *window_class) {
    ATOM result = RegisterClassExW(window_class);
    if (!result) {
        error_code = GetLastError();
    }
    return result;
}

bool window::unregister_class(const char *class_name,
    HINSTANCE                             instance_handle) {
    if (!UnregisterClassA(class_name, instance_handle)) {
        error_code = GetLastError();
        return false;
    }
    return true;
}

bool window::unregister_class(const wchar_t *class_name,
    HINSTANCE                                instance_handle) {
    if (!UnregisterClassW(class_name, instance_handle)) {
        error_code = GetLastError();
        return false;
    }
    return true;
}

bool window::get_class_info(HINSTANCE instance_handle,
    const char                       *class_name,
    WNDCLASSA                        *wnd_class) {
    if (!GetClassInfoA(instance_handle, class_name, wnd_class)) {
        error_code = GetLastError();
        return false;
    }
    return true;
}

bool window::get_class_info(HINSTANCE instance_handle,
    const wchar_t                    *class_name,
    WNDCLASSW                        *wnd_class) {
    if (!GetClassInfoW(instance_handle, class_name, wnd_class)) {
        error_code = GetLastError();
        return false;
    }
    return true;
}

bool window::get_class_info(HINSTANCE instance_handle,
    const char                       *class_name,
    WNDCLASSEXA                      *wnd_class) {
    if (!GetClassInfoExA(instance_handle, class_name, wnd_class)) {
        error_code = GetLastError();
        return false;
    }
    return true;
}

bool window::get_class_info(HINSTANCE instance_handle,
    const wchar_t                    *class_name,
    WNDCLASSEXW                      *wnd_class) {
    if (!GetClassInfoExW(instance_handle, class_name, wnd_class)) {
        error_code = GetLastError();
        return false;
    }
    return true;
}

uint32_t window::get_class_long(HWND hwnd, int32_t index) {
    uint32_t result = GetClassLongW(hwnd, index);
    if (!result) {
        error_code = GetLastError();
    }
    return result;
}

uint32_t window::set_class_long(HWND hwnd, int32_t index, long value) {
    uint32_t result = SetClassLongW(hwnd, index, value);
    if (!result) {
        error_code = GetLastError();
    }
    return result;
}

ULONG_PTR window::get_class_long_ptr(HWND hwnd, int32_t index) {
    ULONG_PTR result = GetClassLongPtrW(hwnd, index);
    if (!result) {
        error_code = GetLastError();
    }
    return result;
}

ULONG_PTR window::set_class_long_ptr(HWND hwnd, int32_t index, LONG_PTR value) {
    ULONG_PTR result = SetClassLongPtrW(hwnd, index, value);
    if (!result) {
        error_code = GetLastError();
    }
    return result;
}

uint16_t window::get_class_word(HWND hwnd, int32_t index) {
    uint16_t result = GetClassWord(hwnd, index);
    if (!result) {
        error_code = GetLastError();
    }
    return result;
}

uint16_t window::set_class_word(HWND hwnd, int32_t index, uint16_t value) {
    uint16_t result = SetClassWord(hwnd, index, value);
    if (!result) {
        error_code = GetLastError();
    }
    return result;
}

int32_t window::get_class_name(HWND hwnd, std::string &class_name) {
    int32_t result = GetClassNameA(
        hwnd, class_name.data(), static_cast<int>(class_name.size()));
    if (!result) {
        error_code = GetLastError();
    }
    return result;
}

int32_t window::get_class_name(HWND hwnd, std::wstring &class_name) {
    int32_t result = GetClassNameW(
        hwnd, class_name.data(), static_cast<int>(class_name.size()));
    if (!result) {
        error_code = GetLastError();
    }
    return result;
}

int32_t window::enum_props(HWND hwnd, PROPENUMPROCA enum_func) {
    return EnumPropsA(hwnd, enum_func);
}

int32_t window::enum_props(HWND hwnd, PROPENUMPROCW enum_func) {
    return EnumPropsW(hwnd, enum_func);
}

int32_t
window::enum_props(HWND hwnd, PROPENUMPROCEXA enum_func, LPARAM lparam) {
    return EnumPropsExA(hwnd, enum_func, lparam);
}

int32_t
window::enum_props(HWND hwnd, PROPENUMPROCEXW enum_func, LPARAM lparam) {
    return EnumPropsExW(hwnd, enum_func, lparam);
}

HANDLE window::get_prop(HWND hwnd, const char *text) {
    return GetPropA(hwnd, text);
}

HANDLE window::get_prop(HWND hwnd, const wchar_t *text) {
    return GetPropW(hwnd, text);
}

bool window::set_prop(HWND hwnd, const char *text, HANDLE data_handle) {
    if (!SetPropA(hwnd, text, data_handle)) {
        error_code = GetLastError();
        return false;
    }
    return true;
}

bool window::set_prop(HWND hwnd, const wchar_t *text, HANDLE data_handle) {
    if (!SetPropW(hwnd, text, data_handle)) {
        error_code = GetLastError();
        return false;
    }
    return true;
}

HANDLE window::remove_prop(HWND hwnd, const char *text) {
    return RemovePropA(hwnd, text);
}

HANDLE window::remove_prop(HWND hwnd, const wchar_t *text) {
    return RemovePropW(hwnd, text);
}

bool window::register_shell_hook(HWND hwnd) {
    return RegisterShellHookWindow(hwnd);
}

bool window::unregister_shell_hook(HWND hwnd) {
    return DeregisterShellHookWindow(hwnd);
}

HHOOK window::set_windows_hook(int32_t id_hook,
    HOOKPROC                           fn,
    HINSTANCE                          hmod,
    uint32_t                           tid) {
    HHOOK result = SetWindowsHookExW(id_hook, fn, hmod, tid);
    if (!result) {
        error_code = GetLastError();
    }
    return result;
}

bool window::unset_windows_hook(HHOOK hhk) {
    if (!UnhookWindowsHookEx(hhk)) {
        error_code = GetLastError();
        return false;
    }
    return true;
}

LRESULT
window::call_next_hook(HHOOK hhk, int32_t code, WPARAM wparam, LPARAM lparam) {
    return CallNextHookEx(hhk, code, wparam, lparam);
}

HWINEVENTHOOK window::set_event_hook(uint32_t event_min,
    uint32_t                                  event_max,
    HMODULE                                   hmod_win_event_proc,
    WINEVENTPROC                              fn_win_event_proc,
    uint32_t                                  pid,
    uint32_t                                  tid,
    uint32_t                                  flag) {
    return SetWinEventHook(event_min, event_max, hmod_win_event_proc,
        fn_win_event_proc, pid, tid, flag);
}

bool window::unset_event_hook(HWINEVENTHOOK hwin_event_hook) {
    return UnhookWinEvent(hwin_event_hook);
}

bool window::is_event_hook_installed(uint32_t event) {
    return IsWinEventHookInstalled(event);
}

void window::notify_event(uint32_t event,
    HWND                           hwnd,
    int32_t                        object_id,
    int32_t                        child_id) {
    NotifyWinEvent(event, hwnd, object_id, child_id);
}

bool window::show(HWND hwnd, int32_t cmd_show) const {
    return ShowWindow(hwnd, cmd_show);
}

bool window::show_async(HWND hwnd, int32_t cmd_show) const {
    return ShowWindowAsync(hwnd, cmd_show);
}

bool window::update(HWND hwnd) const {
    return UpdateWindow(hwnd);
}

bool window::update_layered(HWND hwnd,
    HDC                          hdc_dst,
    POINT                       *coordinate_dst,
    SIZE                        *size,
    HDC                          hdc_src,
    POINT                       *coordinate_src,
    COLORREF                     color_ref,
    BLENDFUNCTION               *blend_fn,
    uint32_t                     flag) {
    if (!UpdateLayeredWindow(hwnd, hdc_dst, coordinate_dst, size, hdc_src,
            coordinate_src, color_ref, blend_fn, flag)) {
        error_code = GetLastError();
        return false;
    }
    return true;
}

bool window::lock_update(HWND hwnd) {
    return LockWindowUpdate(hwnd);
}

bool window::unlock_update() {
    return LockWindowUpdate(nullptr);
}

bool window::animate(HWND hwnd, uint32_t time, uint32_t flag) {
    if (!AnimateWindow(hwnd, time, flag)) {
        error_code = GetLastError();
        return false;
    }
    return true;
}

bool window::close(HWND hwnd) {
    if (!CloseWindow(hwnd)) {
        error_code = GetLastError();
        return false;
    }
    return true;
}

bool window::close(HWND hwnd, bool is_force) {
    if (!EndTask(hwnd, FALSE, is_force ? TRUE : FALSE)) {
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

bool window::destroy(HWND hwnd) {
    if (!DestroyWindow(hwnd)) {
        error_code = GetLastError();
        return false;
    }
    return true;
}

bool window::enable(HWND hwnd, bool enable) {
    return EnableWindow(hwnd, enable ? TRUE : FALSE);
}

bool window::enum_windows(WNDENUMPROC enum_func, LPARAM lparam) {
    if (!EnumWindows(enum_func, lparam)) {
        error_code = GetLastError();
        return false;
    }
    return true;
}

bool window::enum_child_windows(HWND hwnd_parent,
    WNDENUMPROC                      enum_func,
    LPARAM                           lparam) {
    return EnumChildWindows(hwnd_parent, enum_func, lparam);
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

HWND window::find(HWND hwnd_parent,
    HWND               hwnd_child_after,
    const char        *class_name,
    const char        *window_name) {
    HWND hwnd =
        FindWindowExA(hwnd_parent, hwnd_child_after, class_name, window_name);
    if (!hwnd) {
        error_code = GetLastError();
    }
    return hwnd;
}

HWND window::find(HWND hwnd_parent,
    HWND               hwnd_child_after,
    const wchar_t     *class_name,
    const wchar_t     *window_name) {
    HWND hwnd =
        FindWindowExW(hwnd_parent, hwnd_child_after, class_name, window_name);
    if (!hwnd) {
        error_code = GetLastError();
    }
    return hwnd;
}

bool window::flash(HWND hwnd, bool invert) {
    return FlashWindow(hwnd, invert ? TRUE : FALSE);
}

bool window::flash(FLASHWINFO *flash_info) {
    return FlashWindowEx(flash_info);
}

bool window::move(HWND hwnd,
    int32_t            x,
    int32_t            y,
    int32_t            width,
    int32_t            height,
    bool               is_repaint) {
    if (!MoveWindow(hwnd, x, y, width, height, is_repaint ? TRUE : FALSE)) {
        error_code = GetLastError();
        return false;
    }
    return true;
}

bool window::print(HWND hwnd, HDC dc_handle, uint32_t flag) {
    return PrintWindow(hwnd, dc_handle, flag);
}

bool window::redraw(HWND hwnd,
    const RECT          *rect,
    HRGN                 region_handle,
    uint32_t             flag) {
    return RedrawWindow(hwnd, rect, region_handle, flag);
}

bool window::maximize(HWND hwnd) {
    return ShowWindow(hwnd, SW_MAXIMIZE);
}

bool window::minimize(HWND hwnd) {
    return ShowWindow(hwnd, SW_MINIMIZE);
}

bool window::hide(HWND hwnd) {
    return ShowWindow(hwnd, SW_HIDE);
}

bool window::restore(HWND hwnd) {
    return ShowWindow(hwnd, SW_RESTORE);
}

bool window::restore_minimize(HWND hwnd) {
    if (!OpenIcon(hwnd)) {
        error_code = GetLastError();
        return false;
    }
    return true;
}

uint16_t window::tile(HWND   hwnd_parent,
    uint32_t                 how,
    const RECT              *rect,
    const std::vector<HWND> &child) {
    uint16_t result =
        TileWindows(hwnd_parent, how, rect, child.size(), child.data());
    if (!result) {
        error_code = GetLastError();
    }
    return result;
}

HWND window::get_parent(HWND hwnd) {
    HWND result = GetParent(hwnd);
    if (!result) {
        error_code = GetLastError();
    }
    return result;
}

HWND window::set_parent(HWND hwnd_child, HWND hwnd_new_parent) {
    HWND result = SetParent(hwnd_child, hwnd_new_parent);
    if (!result) {
        error_code = GetLastError();
    }
    return result;
}

HWND window::get_ancestor(HWND hwnd, uint32_t flag) {
    return GetAncestor(hwnd, flag);
}

bool window::show_popup(HWND hwnd) {
    if (!ShowOwnedPopups(hwnd, TRUE)) {
        error_code = GetLastError();
        return false;
    }
    return true;
}

bool window::hide_popup(HWND hwnd) {
    if (!ShowOwnedPopups(hwnd, FALSE)) {
        error_code = GetLastError();
        return false;
    }
    return true;
}

HWND window::get_last_active_popup(HWND hwnd) {
    return GetLastActivePopup(hwnd);
}

bool window::is_pending(HWND hwnd) {
    return IsHungAppWindow(hwnd);
}

bool window::is_window(HWND hwnd) {
    return IsWindow(hwnd);
}

bool window::is_arranged(HWND hwnd) {
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
        if (!IsWindowArranged(hwnd)) {
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

bool window::is_enabled(HWND hwnd) {
    return IsWindowEnabled(hwnd);
}

bool window::is_unicode(HWND hwnd) {
    return IsWindowUnicode(hwnd);
}

bool window::is_visible(HWND hwnd) {
    return IsWindowVisible(hwnd);
}

bool window::is_minimize(HWND hwnd) {
    return IsIconic(hwnd);
}

bool window::is_maximize(HWND hwnd) {
    return IsZoomed(hwnd);
}

bool window::is_child(HWND hwnd_parent, HWND hwnd) {
    return IsChild(hwnd_parent, hwnd);
}

bool window::is_popup_exist() {
    return AnyPopup();
}

uint32_t window::arrange_minimize(HWND hwnd) {
    uint32_t height = ArrangeIconicWindows(hwnd);
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

HDWP window::prepare(int32_t num_windows) {
    HDWP hdwp = BeginDeferWindowPos(num_windows);
    if (!hdwp) {
        error_code = GetLastError();
    }
    return hdwp;
}

HDWP window::add(HDWP hwin_pos_info,
    HWND              hwnd,
    HWND              hwnd_insert_after,
    int32_t           x,
    int32_t           y,
    int32_t           cx,
    int32_t           cy,
    uint32_t          flag) {
    HDWP hdwp = DeferWindowPos(
        hwin_pos_info, hwnd, hwnd_insert_after, x, y, cx, cy, flag);
    if (!hdwp) {
        error_code = GetLastError();
    }
    return hdwp;
}

bool window::apply(HDWP hwin_pos_info) {
    if (!EndDeferWindowPos(hwin_pos_info)) {
        error_code = GetLastError();
        return false;
    }
    return true;
}

bool window::set_pos(HWND hwnd,
    HWND                  hwnd_insert_after,
    int32_t               x,
    int32_t               y,
    int32_t               cx,
    int32_t               cy,
    uint32_t              flag) {
    if (!SetWindowPos(hwnd, hwnd_insert_after, x, y, cx, cy, flag)) {
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

HWND window::find_top_child(HWND hwnd_parent, POINT coordinate) {
    return ChildWindowFromPoint(hwnd_parent, coordinate);
}

HWND window::find_top_child(HWND hwnd_parent, POINT coordinate, uint32_t flag) {
    return ChildWindowFromPointEx(hwnd_parent, coordinate, flag);
}

HWND window::find_real_child(HWND hwnd_parent, POINT coordinate) {
    return RealChildWindowFromPoint(hwnd_parent, coordinate);
}

HWND window::find_by_physical_point(POINT coordinate) {
    return WindowFromPhysicalPoint(coordinate);
}

HWND window::find_by_logical_point(POINT coordinate) {
    return WindowFromPoint(coordinate);
}

int32_t window::transform_coordinate(HWND hwnd_from,
    HWND                                  hwnd_to,
    std::vector<POINT>                   &coordinates) {
    int32_t result = MapWindowPoints(
        hwnd_from, hwnd_to, coordinates.data(), coordinates.size());
    error_code = GetLastError();
    return result;
}

bool window::adjust_to_top(HWND hwnd) {
    if (!BringWindowToTop(hwnd)) {
        error_code = GetLastError();
        return false;
    }
    return true;
}

LRESULT window::call_proc(WNDPROC prev_wnd_func,
    HWND                          hwnd,
    uint32_t                      msg,
    WPARAM                        wparam,
    LPARAM                        lparam) {
    return CallWindowProcW(prev_wnd_func, hwnd, msg, wparam, lparam);
}

LRESULT
window::default_proc(HWND hwnd, uint32_t msg, WPARAM wparam, LPARAM lparam) {
    return DefWindowProcW(hwnd, msg, wparam, lparam);
}

LRESULT window::default_mdi_proc(HWND hwnd,
    HWND                              hwnd_mdi_client,
    uint32_t                          msg,
    WPARAM                            wparam,
    LPARAM                            lparam) {
    return DefFrameProcW(hwnd, hwnd_mdi_client, msg, wparam, lparam);
}

LRESULT window::default_mdi_child_proc(HWND hwnd,
    uint32_t                                msg,
    WPARAM                                  wparam,
    LPARAM                                  lparam) {
    return DefMDIChildProcW(hwnd, msg, wparam, lparam);
}

uint16_t window::cascade(HWND hwnd_parent,
    uint32_t                  how,
    const RECT               *rect,
    std::vector<HWND>        &child) {
    uint16_t count =
        CascadeWindows(hwnd_parent, how, rect, child.size(), child.data());
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

HWND window::set_active(HWND hwnd) {
    HWND hwnd_handle = SetActiveWindow(hwnd);
    if (!hwnd_handle) {
        error_code = GetLastError();
    }
    return hwnd_handle;
}

uint32_t window::get_dpi(HWND hwnd) {
    return GetDpiForWindow(hwnd);
}

HWND window::get_foreground() {
    return GetForegroundWindow();
}

bool window::set_foreground(HWND hwnd) {
    return SetForegroundWindow(hwnd);
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

bool window::get_layered_attrs(HWND hwnd,
    COLORREF                       *color_ref,
    uint8_t                        *alpha,
    uint32_t                       *flag) {
    if (!GetLayeredWindowAttributes(
            hwnd, color_ref, alpha, reinterpret_cast<unsigned long *>(flag))) {
        error_code = GetLastError();
        return false;
    }
    return true;
}

bool window::set_layered_attrs(HWND hwnd,
    COLORREF                        color_ref,
    uint8_t                         alpha,
    uint32_t                        flag) {
    if (!SetLayeredWindowAttributes(hwnd, color_ref, alpha, flag)) {
        error_code = GetLastError();
        return false;
    }
    return true;
}

HWND window::find(HWND hwnd, uint32_t cmd) {
    HWND hwnd_handle = GetWindow(hwnd, cmd);
    if (!hwnd_handle) {
        error_code = GetLastError();
    }
    return hwnd_handle;
}

HWND window::find_next(HWND hwnd, uint32_t cmd) {
    return GetNextWindow(hwnd, cmd);
}

HWND window::find_shell() {
    return GetShellWindow();
}

HWND window::find_top(HWND hwnd) {
    HWND hwnd_handle = GetTopWindow(hwnd);
    if (!hwnd_handle) {
        error_code = GetLastError();
    }
    return hwnd_handle;
}

uint32_t window::get_context_help_id(HWND hwnd) {
    return GetWindowContextHelpId(hwnd);
}

bool window::set_context_help_id(HWND hwnd, uint32_t param) {
    if (!SetWindowContextHelpId(hwnd, param)) {
        error_code = GetLastError();
        return false;
    }
    return true;
}

bool window::get_display_affinity(HWND hwnd, uint32_t *affinity) {
    if (!GetWindowDisplayAffinity(
            hwnd, reinterpret_cast<unsigned long *>(affinity))) {
        error_code = GetLastError();
        return false;
    }
    return true;
}

bool window::set_display_affinity(HWND hwnd, uint32_t affinity) {
    if (!SetWindowDisplayAffinity(hwnd, affinity)) {
        error_code = GetLastError();
        return false;
    }
    return true;
}

DPI_AWARENESS_CONTEXT window::get_dpi_aware_context(HWND hwnd) {
    return GetWindowDpiAwarenessContext(hwnd);
}

DPI_HOSTING_BEHAVIOR window::get_dpi_hosting_behavior(HWND hwnd) {
    return GetWindowDpiHostingBehavior(hwnd);
}

bool window::get_feedback_setting(HWND hwnd,
    FEEDBACK_TYPE                      feedback,
    uint32_t                           flag,
    int                               *real_config) {
    uint32_t size = sizeof(int);
    return GetWindowFeedbackSetting(hwnd, feedback, flag, &size, real_config);
}

bool window::set_feedback_setting(HWND hwnd,
    FEEDBACK_TYPE                      feedback,
    uint32_t                           size,
    const int                         *config) {
    return SetWindowFeedbackSetting(hwnd, feedback, 0, size, config);
}

bool window::get_info(HWND hwnd, WINDOWINFO *window_info) {
    if (!GetWindowInfo(hwnd, window_info)) {
        error_code = GetLastError();
        return false;
    }
    return true;
}

long window::get_long(HWND hwnd, int32_t index) {
    long result = GetWindowLongW(hwnd, index);
    if (!result) {
        error_code = GetLastError();
    }
    return result;
}

long window::set_long(HWND hwnd, int32_t index, long value) {
    long result = SetWindowLongW(hwnd, index, value);
    if (!result) {
        error_code = GetLastError();
    }
    return result;
}

LONG_PTR window::get_long_ptr(HWND hwnd, int32_t index) {
    LONG_PTR result = GetWindowLongPtrW(hwnd, index);
    if (!result) {
        error_code = GetLastError();
    }
    return result;
}

LONG_PTR window::set_long_ptr(HWND hwnd, int32_t index, LONG_PTR value) {
    LONG_PTR result = SetWindowLongPtrW(hwnd, index, value);
    if (!result) {
        error_code = GetLastError();
    }
    return result;
}

uint32_t window::get_module_file_name(HWND hwnd, std::string &file_name) {
    return GetWindowModuleFileNameA(hwnd, file_name.data(), file_name.size());
}

uint32_t window::get_module_file_name(HWND hwnd, std::wstring &file_name) {
    return GetWindowModuleFileNameW(hwnd, file_name.data(), file_name.size());
}

bool window::get_placement(HWND hwnd, WINDOWPLACEMENT *window_placement) {
    if (!GetWindowPlacement(hwnd, window_placement)) {
        error_code = GetLastError();
        return false;
    }
    return true;
}

bool window::set_placement(HWND hwnd, const WINDOWPLACEMENT *window_placement) {
    if (!SetWindowPlacement(hwnd, window_placement)) {
        error_code = GetLastError();
        return false;
    }
    return true;
}

bool window::get_rect(HWND hwnd, RECT *rect) {
    if (!GetWindowRect(hwnd, rect)) {
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

int32_t window::get_region(HWND hwnd, HRGN region_handle) {
    return GetWindowRgn(hwnd, region_handle);
}

int32_t window::set_region(HWND hwnd, HRGN region_handle, bool is_redraw) {
    return SetWindowRgn(hwnd, region_handle, is_redraw ? TRUE : FALSE);
}

int32_t window::get_region_box(HWND hwnd, RECT *rect) {
    return GetWindowRgnBox(hwnd, rect);
}

int32_t window::get_text(HWND hwnd, std::string &text) {
    int32_t result =
        GetWindowTextA(hwnd, text.data(), static_cast<int>(text.size()));
    if (!result) {
        error_code = GetLastError();
    }
    return result;
}

int32_t window::get_text(HWND hwnd, std::wstring &text) {
    int32_t result =
        GetWindowTextW(hwnd, text.data(), static_cast<int>(text.size()));
    if (!result) {
        error_code = GetLastError();
    }
    return result;
}

bool window::set_text(HWND hwnd, const char *text) {
    if (!SetWindowTextA(hwnd, text)) {
        error_code = GetLastError();
        return false;
    }
    return true;
}

bool window::set_text(HWND hwnd, const wchar_t *text) {
    if (!SetWindowTextW(hwnd, text)) {
        error_code = GetLastError();
        return false;
    }
    return true;
}

int32_t window::get_text_length(HWND hwnd) {
    int32_t result = GetWindowTextLengthW(hwnd);
    if (!result) {
        error_code = GetLastError();
    }
    return result;
}

uint32_t window::get_thread_id(HWND hwnd) {
    uint32_t pid = 0;
    uint32_t tid =
        GetWindowThreadProcessId(hwnd, reinterpret_cast<unsigned long *>(&pid));
    if (!tid) {
        error_code = GetLastError();
    }
    return tid;
}

uint32_t window::get_proc_id(HWND hwnd) {
    uint32_t pid = 0;
    uint32_t tid =
        GetWindowThreadProcessId(hwnd, reinterpret_cast<unsigned long *>(&pid));
    if (!tid) {
        error_code = GetLastError();
    }
    return pid;
}

std::pair<uint32_t, uint32_t> window::get_window_tid_and_pid(HWND hwnd) {
    uint32_t pid = 0;
    uint32_t tid =
        GetWindowThreadProcessId(hwnd, reinterpret_cast<unsigned long *>(&pid));
    if (!tid) {
        error_code = GetLastError();
    }
    return std::make_pair(tid, pid);
}

uint16_t window::get_word(HWND hwnd, int32_t index) {
    uint16_t result = GetWindowWord(hwnd, index);
    if (!result) {
        error_code = GetLastError();
    }
    return result;
}

int32_t window::get_direct_text(HWND hwnd, std::string &text) {
    std::wstring data(text.size(), L'\0');
    int32_t      result =
        InternalGetWindowText(hwnd, data.data(), static_cast<int>(data.size()));
    text = helper::convert::wstr_to_str(data);
    if (!result) {
        error_code = GetLastError();
    }
    return result;
}

int32_t window::get_direct_text(HWND hwnd, std::wstring &text) {
    int32_t result =
        InternalGetWindowText(hwnd, text.data(), static_cast<int>(text.size()));
    if (!result) {
        error_code = GetLastError();
    }
    return result;
}

uint32_t window::get_class(HWND hwnd, std::string &class_name) {
    uint32_t result =
        RealGetWindowClassA(hwnd, class_name.data(), class_name.size());
    if (!result) {
        error_code = GetLastError();
    }
    return result;
}

uint32_t window::get_class(HWND hwnd, std::wstring &class_name) {
    uint32_t result =
        RealGetWindowClassW(hwnd, class_name.data(), class_name.size());
    if (!result) {
        error_code = GetLastError();
    }
    return result;
}

void window::switch_window(HWND hwnd, bool unknown) {
    SwitchToThisWindow(hwnd, unknown ? TRUE : FALSE);
}

bool window::show_help(HWND hwnd,
    const char             *help,
    uint32_t                cmd,
    ULONG_PTR               data) {
    if (!WinHelpA(hwnd, help, cmd, data)) {
        error_code = GetLastError();
        return false;
    }
    return true;
}

bool window::show_help(HWND hwnd,
    const wchar_t          *help,
    uint32_t                cmd,
    ULONG_PTR               data) {
    if (!WinHelpW(hwnd, help, cmd, data)) {
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

bool window::get_alt_tab_info(HWND hwnd,
    int32_t                        item_index,
    ALTTABINFO                    *alt_tab_info,
    std::string                   &item_text) {
    if (!GetAltTabInfoA(hwnd, item_index, alt_tab_info, item_text.data(),
            item_text.size())) {
        error_code = GetLastError();
        return false;
    }
    return true;
}

bool window::get_alt_tab_info(HWND hwnd,
    int32_t                        item_index,
    ALTTABINFO                    *alt_tab_info,
    std::wstring                  &item_text) {
    if (!GetAltTabInfoW(hwnd, item_index, alt_tab_info, item_text.data(),
            item_text.size())) {
        error_code = GetLastError();
        return false;
    }
    return true;
}

UINT_PTR window::set_timer(HWND hwnd,
    UINT_PTR                    event_id,
    uint32_t                    elapse,
    TIMERPROC                   timer_func) {
    UINT_PTR result = SetTimer(hwnd, event_id, elapse, timer_func);
    if (!result) {
        error_code = GetLastError();
    }
    return result;
}

UINT_PTR window::set_coalescable_timer(HWND hwnd,
    UINT_PTR                                event_id,
    uint32_t                                elapse,
    TIMERPROC                               timer_func,
    uint32_t                                tolerance_delay) {
    UINT_PTR result = SetCoalescableTimer(
        hwnd, event_id, elapse, timer_func, tolerance_delay);
    if (!result) {
        error_code = GetLastError();
    }
    return result;
}

bool window::kill_timer(HWND hwnd, UINT_PTR event_id) {
    if (!KillTimer(hwnd, event_id)) {
        error_code = GetLastError();
        return false;
    }
    return true;
}

bool window::create_shutdown_reason(HWND hwnd, std::string &reason) {
    std::wstring data = helper::convert::str_to_wstr(reason);
    if (!ShutdownBlockReasonCreate(hwnd, data.data())) {
        error_code = GetLastError();
        return false;
    }
    return true;
}

bool window::create_shutdown_reason(HWND hwnd, const std::wstring &reason) {
    if (!ShutdownBlockReasonCreate(hwnd, reason.data())) {
        error_code = GetLastError();
        return false;
    }
    return true;
}

bool window::destroy_shutdown_reason(HWND hwnd) {
    if (!ShutdownBlockReasonDestroy(hwnd)) {
        error_code = GetLastError();
        return false;
    }
    return true;
}

bool window::query_shutdown_reason(HWND hwnd,
    std::string                        &reason,
    uint32_t                           *real_size) {
    std::wstring data = helper::convert::str_to_wstr(reason);
    *real_size        = data.size();
    if (!ShutdownBlockReasonQuery(
            hwnd, data.data(), reinterpret_cast<unsigned long *>(real_size))) {
        error_code = GetLastError();
        return false;
    }
    return true;
}

bool window::query_shutdown_reason(HWND hwnd,
    std::wstring                       &reason,
    uint32_t                           *real_size) {
    if (!ShutdownBlockReasonQuery(hwnd, reason.data(),
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

bool window::register_tooltip_dismiss_notify(HWND hwnd) {
    return RegisterForTooltipDismissNotification(hwnd, TDF_REGISTER);
}

bool window::unregister_tooltip_dismiss_notify(HWND hwnd) {
    return RegisterForTooltipDismissNotification(hwnd, TDF_UNREGISTER);
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

bool window::get_title_bar_info(HWND hwnd, TITLEBARINFO *title_bar_info) {
    if (!GetTitleBarInfo(hwnd, title_bar_info)) {
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

bool window::get_combobox_info(HWND combo_hwnd, COMBOBOXINFO *combobox_info) {
    if (!GetComboBoxInfo(combo_hwnd, combobox_info)) {
        error_code = GetLastError();
        return false;
    }
    return true;
}

uint32_t window::get_listbox_info(HWND hwnd) {
    return GetListBoxInfo(hwnd);
}

bool window::is_dpi_aware_contexts_equal(DPI_AWARENESS_CONTEXT context1,
    DPI_AWARENESS_CONTEXT                                      context2) {
    return AreDpiAwarenessContextsEqual(context1, context2);
}

bool window::enable_non_client_dpi_scaling(HWND hwnd) {
    if (!EnableNonClientDpiScaling(hwnd)) {
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
