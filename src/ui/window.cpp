//
// Created by forkernel on 2025/4/28.
//

#include "window.h"
#include "helper/convert.h"

namespace YanLib::ui {
    HWND window::create_window(const wchar_t *class_name,
                               const wchar_t *window_name,
                               HINSTANCE instance_handle, void *param,
                               HWND hwnd_parent,
                               HMENU menu_handle,
                               int32_t x,
                               int32_t y,
                               int32_t width,
                               int32_t height,
                               unsigned long style,
                               unsigned long ext_style) {
        HWND hwnd_handle = CreateWindowExW(ext_style,
                                           class_name,
                                           window_name,
                                           style,
                                           x,
                                           y,
                                           width,
                                           height,
                                           hwnd_parent,
                                           menu_handle,
                                           instance_handle,
                                           param);
        if (!hwnd_handle) {
            error_code = GetLastError();
        }
        return hwnd_handle;
    }

    HWND window::create_mdi_window(const wchar_t *class_name,
                                   const wchar_t *window_name,
                                   HINSTANCE instance_handle,
                                   LPARAM l_param,
                                   HWND hwnd_parent,
                                   int32_t x,
                                   int32_t y,
                                   int32_t width,
                                   int32_t height,
                                   unsigned long style) {
        HWND hwnd_handle = CreateMDIWindowW(class_name,
                                            window_name,
                                            style,
                                            x,
                                            y,
                                            width,
                                            height,
                                            hwnd_parent,
                                            instance_handle,
                                            l_param);
        if (!hwnd_handle) {
            error_code = GetLastError();
        }
        return hwnd_handle;
    }

    WNDCLASSEXW window::make_window_class(const wchar_t *class_name,
                                          WNDPROC window_proc,
                                          HINSTANCE instance_handle,
                                          uint32_t style,
                                          const wchar_t *menu_name,
                                          int32_t cb_class_extra,
                                          int32_t cb_window_extra,
                                          HICON icon_handle,
                                          HCURSOR cursor_handle,
                                          HBRUSH brush_background_handle,
                                          HICON icon_small_handle) {
        WNDCLASSEXW wnd_class = {};
        wnd_class.cbSize = sizeof(WNDCLASSEXW);
        wnd_class.style = style;
        wnd_class.lpfnWndProc = window_proc;
        wnd_class.cbClsExtra = cb_class_extra;
        wnd_class.cbWndExtra = cb_window_extra;
        wnd_class.hInstance = instance_handle;
        wnd_class.hIcon = icon_handle;
        wnd_class.hCursor = cursor_handle;
        wnd_class.hbrBackground = brush_background_handle;
        wnd_class.lpszMenuName = menu_name;
        wnd_class.lpszClassName = class_name;
        wnd_class.hIconSm = icon_small_handle;
        return wnd_class;
    }

    ATOM window::register_class(const WNDCLASSEXW *window_class) {
        ATOM result = RegisterClassExW(window_class);
        if (!result) {
            error_code = GetLastError();
        }
        return result;
    }

    bool window::unregister_class(const wchar_t *class_name,
                                  HINSTANCE instance_handle) {
        if (!UnregisterClassW(class_name, instance_handle)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool window::get_class_info(HINSTANCE instance_handle,
                                const wchar_t *class_name,
                                WNDCLASSW *wnd_class) {
        if (!GetClassInfoW(instance_handle,
                           class_name,
                           wnd_class)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool window::get_class_info(HINSTANCE instance_handle,
                                const wchar_t *class_name,
                                WNDCLASSEXW *wnd_class) {
        if (!GetClassInfoExW(instance_handle,
                             class_name,
                             wnd_class)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    unsigned long window::get_class_long(HWND hwnd, int32_t index) {
        unsigned long result = GetClassLongW(hwnd, index);
        if (!result) {
            error_code = GetLastError();
        }
        return result;
    }

    unsigned long window::set_class_long(HWND hwnd, int32_t index, long value) {
        unsigned long result = SetClassLongW(hwnd, index, value);
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

    int32_t window::get_class_name(HWND hwnd, wchar_t *class_name, int32_t cch_size) {
        int32_t result = GetClassNameW(hwnd, class_name, cch_size);
        if (!result) {
            error_code = GetLastError();
        }
        return result;
    }

    int32_t window::enum_props(HWND hwnd, PROPENUMPROCW enum_func) {
        return EnumPropsW(hwnd, enum_func);
    }

    int32_t window::enum_props(HWND hwnd, PROPENUMPROCEXW enum_func, LPARAM l_param) {
        return EnumPropsExW(hwnd, enum_func, l_param);
    }

    HANDLE window::get_prop(HWND hwnd, const wchar_t *text) {
        return GetPropW(hwnd, text);
    }

    bool window::set_prop(HWND hwnd, const wchar_t *text, HANDLE data_handle) {
        if (!SetPropW(hwnd, text, data_handle)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    HANDLE window::remove_prop(HWND hwnd, const wchar_t *text) {
        return RemovePropW(hwnd, text);
    }

    bool window::register_shell_hook_window(HWND hwnd) {
        return RegisterShellHookWindow(hwnd);
    }

    bool window::deregister_shell_hook_window(HWND hwnd) {
        return DeregisterShellHookWindow(hwnd);
    }

    HHOOK window::set_windows_hook(int32_t id_hook,
                                   HOOKPROC fn,
                                   HINSTANCE hmod,
                                   unsigned long tid) {
        HHOOK result = SetWindowsHookExW(id_hook, fn, hmod, tid);
        if (!result) {
            error_code = GetLastError();
        }
        return result;
    }

    bool window::unhook_windows_hook(HHOOK hhk) {
        if (!UnhookWindowsHookEx(hhk)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    LRESULT window::call_next_hook(HHOOK hhk,
                                   int32_t code,
                                   WPARAM w_param,
                                   LPARAM l_param) {
        return CallNextHookEx(hhk, code, w_param, l_param);
    }

    HWINEVENTHOOK window::set_win_event_hook(unsigned long event_min,
                                             unsigned long event_max,
                                             HMODULE hmod_win_event_proc,
                                             WINEVENTPROC fn_win_event_proc,
                                             unsigned long pid,
                                             unsigned long tid,
                                             unsigned long flag) {
        return SetWinEventHook(event_min,
                               event_max,
                               hmod_win_event_proc,
                               fn_win_event_proc,
                               pid,
                               tid,
                               flag);
    }

    bool window::unhook_win_event(HWINEVENTHOOK hwin_event_hook) {
        return UnhookWinEvent(hwin_event_hook);
    }

    bool window::is_win_event_hook_installed(unsigned long event) {
        return IsWinEventHookInstalled(event);
    }

    bool window::show_window(HWND hwnd, int32_t cmd_show) const {
        return ShowWindow(hwnd, cmd_show);
    }

    bool window::show_window_async(HWND hwnd, int32_t cmd_show) const {
        return ShowWindowAsync(hwnd, cmd_show);
    }

    bool window::update_window(HWND hwnd) const {
        return UpdateWindow(hwnd);
    }

    bool window::update_layered_window(HWND hwnd,
                                       HDC hdc_dst,
                                       POINT *point_dst,
                                       SIZE *size,
                                       HDC hdc_src,
                                       POINT *point_src,
                                       COLORREF color_ref,
                                       BLENDFUNCTION *blend_fn,
                                       unsigned long flag) {
        if (!UpdateLayeredWindow(hwnd,
                                 hdc_dst,
                                 point_dst,
                                 size,
                                 hdc_src,
                                 point_src,
                                 color_ref,
                                 blend_fn,
                                 flag)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool window::lock_window_update(HWND hwnd) {
        return LockWindowUpdate(hwnd);
    }

    bool window::unlock_window_update() {
        return LockWindowUpdate(nullptr);
    }

    bool window::animate_window(HWND hwnd, unsigned long time, unsigned long flag) {
        if (!AnimateWindow(hwnd, time, flag)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    uint32_t window::arrange_minimize_windows(HWND hwnd) {
        uint32_t height = ArrangeIconicWindows(hwnd);
        if (!height) {
            error_code = GetLastError();
        }
        return height;
    }

    HDWP window::begin_defer_window_pos(int32_t num_windows) {
        HDWP hdwp = BeginDeferWindowPos(num_windows);
        if (!hdwp) {
            error_code = GetLastError();
        }
        return hdwp;
    }

    HDWP window::defer_window_pos(HDWP hwin_pos_info,
                                  HWND hwnd,
                                  HWND hwnd_insert_after,
                                  int32_t x,
                                  int32_t y,
                                  int32_t cx,
                                  int32_t cy,
                                  uint32_t flag) {
        HDWP hdwp = DeferWindowPos(hwin_pos_info,
                                   hwnd,
                                   hwnd_insert_after,
                                   x,
                                   y,
                                   cx,
                                   cy,
                                   flag);
        if (!hdwp) {
            error_code = GetLastError();
        }
        return hdwp;
    }

    bool window::end_defer_window_pos(HDWP hwin_pos_info) {
        if (!EndDeferWindowPos(hwin_pos_info)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool window::set_window_pos(HWND hwnd,
                                HWND hwnd_insert_after,
                                int32_t x,
                                int32_t y,
                                int32_t cx,
                                int32_t cy,
                                uint32_t flag) {
        if (!SetWindowPos(hwnd,
                          hwnd_insert_after,
                          x,
                          y,
                          cx,
                          cy,
                          flag)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool window::calculate_popup_window_position(const POINT *anchor_point,
                                                 const SIZE *window_size,
                                                 uint32_t flag,
                                                 RECT *exclude_rect,
                                                 RECT *popup_window_position) {
        if (!CalculatePopupWindowPosition(anchor_point,
                                          window_size,
                                          flag,
                                          exclude_rect,
                                          popup_window_position)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool window::bring_window_to_top(HWND hwnd) {
        if (!BringWindowToTop(hwnd)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    LRESULT window::call_window_proc(WNDPROC prev_wnd_func,
                                     HWND hwnd,
                                     uint32_t msg,
                                     WPARAM w_param,
                                     LPARAM l_param) {
        return CallWindowProcW(prev_wnd_func,
                               hwnd,
                               msg,
                               w_param,
                               l_param);
    }

    LRESULT window::default_window_proc(HWND hwnd,
                                        uint32_t msg,
                                        WPARAM w_param,
                                        LPARAM l_param) {
        return DefWindowProcW(hwnd, msg, w_param, l_param);
    }

    LRESULT window::default_frame_proc(HWND hwnd,
                                       HWND hwnd_mdi_client,
                                       uint32_t msg,
                                       WPARAM w_param,
                                       LPARAM l_param) {
        return DefFrameProcW(hwnd, hwnd_mdi_client, msg, w_param, l_param);
    }

    LRESULT window::default_mdi_child_proc(HWND hwnd,
                                           uint32_t msg,
                                           WPARAM w_param,
                                           LPARAM l_param) {
        return DefMDIChildProcW(hwnd, msg, w_param, l_param);
    }

    uint16_t window::cascade_windows(HWND hwnd_parent,
                                           uint32_t how,
                                           const RECT *rect,
                                           uint32_t kids_count,
                                           const HWND *kids) {
        uint16_t count = CascadeWindows(hwnd_parent,
                                              how,
                                              rect,
                                              kids_count,
                                              kids);
        if (!count) {
            error_code = GetLastError();
        }
        return count;
    }

    HWND window::child_window_from_point(HWND hwnd_parent, POINT point) {
        return ChildWindowFromPoint(hwnd_parent, point);
    }

    HWND window::child_window_from_point(HWND hwnd_parent, POINT point, uint32_t flag) {
        return ChildWindowFromPointEx(hwnd_parent, point, flag);
    }

    HWND window::real_child_window_from_point(HWND hwnd_parent,
                                              POINT parent_client_coords) {
        return RealChildWindowFromPoint(hwnd_parent, parent_client_coords);
    }

    HWND window::window_from_physical_point(POINT point) {
        return WindowFromPhysicalPoint(point);
    }

    HWND window::window_from_point(POINT point) {
        return WindowFromPoint(point);
    }

    int32_t window::map_window_points(HWND hwnd_from,
                                  HWND hwnd_to,
                                  POINT *point,
                                  uint32_t count) {
        int32_t result = MapWindowPoints(hwnd_from, hwnd_to, point, count);
        error_code = GetLastError();
        return result;
    }

    bool window::close_window(HWND hwnd) {
        if (!CloseWindow(hwnd)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool window::destroy_window(HWND hwnd) {
        if (!DestroyWindow(hwnd)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    void window::disable_process_windows_ghosting() {
        DisableProcessWindowsGhosting();
    }

    bool window::enable_window(HWND hwnd, bool enable) {
        return EnableWindow(hwnd, enable ? TRUE : FALSE);
    }

    bool window::enum_windows(WNDENUMPROC enum_func, LPARAM l_param) {
        if (!EnumWindows(enum_func, l_param)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool window::enum_child_windows(HWND hwnd_parent,
                                    WNDENUMPROC enum_func,
                                    LPARAM l_param) {
        return EnumChildWindows(hwnd_parent, enum_func, l_param);
    }

    bool window::enum_thread_windows(unsigned long tid,
                                     WNDENUMPROC fn,
                                     LPARAM l_param) {
        return EnumThreadWindows(tid, fn, l_param);
    }

    bool window::exit_windows(uint32_t flag, unsigned long reason) {
        if (!ExitWindowsEx(flag, reason)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    HWND window::find_window(const wchar_t *class_name,
                             const wchar_t *window_name) {
        return FindWindowW(class_name, window_name);
    }

    HWND window::find_window(HWND hwnd_parent,
                             HWND hwnd_child_after,
                             const wchar_t *class_name,
                             const wchar_t *window_name) {
        HWND hwnd = FindWindowExW(hwnd_parent,
                                  hwnd_child_after,
                                  class_name,
                                  window_name);
        if (!hwnd) {
            error_code = GetLastError();
        }
        return hwnd;
    }

    bool window::flash_window(HWND hwnd, bool invert) {
        return FlashWindow(hwnd, invert ? TRUE : FALSE);
    }

    bool window::flash_window(FLASHWINFO *flash_info) {
        return FlashWindowEx(flash_info);
    }

    HWND window::get_active_window() {
        return GetActiveWindow();
    }

    HWND window::set_active_window(HWND hwnd) {
        HWND hwnd_handle = SetActiveWindow(hwnd);
        if (!hwnd_handle) {
            error_code = GetLastError();
        }
        return hwnd_handle;
    }

    uint32_t window::get_dpi_for_window(HWND hwnd) {
        return GetDpiForWindow(hwnd);
    }

    HWND window::get_foreground_window() {
        return GetForegroundWindow();
    }

    bool window::set_foreground_window(HWND hwnd) {
        return SetForegroundWindow(hwnd);
    }

    bool window::allow_set_foreground_window(unsigned long pid) {
        if (!AllowSetForegroundWindow(pid)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool window::lock_set_foreground_window() {
        return LockSetForegroundWindow(LSFW_LOCK);
    }

    bool window::unlock_set_foreground_window() {
        return LockSetForegroundWindow(LSFW_UNLOCK);
    }

    bool window::get_layered_window_attrs(HWND hwnd,
                                          COLORREF *color_ref,
                                          uint8_t *alpha,
                                          unsigned long *flag) {
        if (!GetLayeredWindowAttributes(hwnd,
                                        color_ref,
                                        alpha,
                                        flag)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool window::set_layered_window_attrs(HWND hwnd,
                                          COLORREF color_ref,
                                          uint8_t alpha,
                                          unsigned long flag) {
        if (!SetLayeredWindowAttributes(hwnd,
                                        color_ref,
                                        alpha,
                                        flag)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }


    HWND window::get_window(HWND hwnd, uint32_t cmd) {
        HWND hwnd_handle = GetWindow(hwnd, cmd);
        if (!hwnd_handle) {
            error_code = GetLastError();
        }
        return hwnd_handle;
    }

    HWND window::get_next_window(HWND hwnd, uint32_t cmd) {
        return GetWindow(hwnd, cmd);
    }

    HWND window::get_shell_window() {
        return GetShellWindow();
    }

    HWND window::get_top_window(HWND hwnd) {
        HWND hwnd_handle = GetTopWindow(hwnd);
        if (!hwnd_handle) {
            error_code = GetLastError();
        }
        return hwnd_handle;
    }

    unsigned long window::get_window_context_help_id(HWND hwnd) {
        return GetWindowContextHelpId(hwnd);
    }

    bool window::set_window_context_help_id(HWND hwnd, unsigned long param) {
        if (!SetWindowContextHelpId(hwnd, param)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool window::get_window_display_affinity(HWND hwnd, unsigned long *affinity) {
        if (!GetWindowDisplayAffinity(hwnd, affinity)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool window::set_window_display_affinity(HWND hwnd, unsigned long affinity) {
        if (!SetWindowDisplayAffinity(hwnd, affinity)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    DPI_AWARENESS_CONTEXT window::get_window_dpi_awareness_context(HWND hwnd) {
        return GetWindowDpiAwarenessContext(hwnd);
    }

    DPI_HOSTING_BEHAVIOR window::get_window_dpi_hosting_behavior(HWND hwnd) {
        return GetWindowDpiHostingBehavior(hwnd);
    }

    bool window::get_window_feedback_setting(HWND hwnd,
                                             FEEDBACK_TYPE feedback,
                                             unsigned long flag,
                                             uint32_t *size,
                                             void *config) {
        return GetWindowFeedbackSetting(hwnd,
                                        feedback,
                                        flag,
                                        size,
                                        config);
    }

    bool window::set_window_feedback_setting(HWND hwnd,
                                             FEEDBACK_TYPE feedback,
                                             unsigned long flag,
                                             uint32_t size,
                                             const void *config) {
        return SetWindowFeedbackSetting(hwnd,
                                        feedback,
                                        flag,
                                        size,
                                        config);
    }

    bool window::get_window_info(HWND hwnd, WINDOWINFO *window_info) {
        if (!GetWindowInfo(hwnd, window_info)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    long window::get_window_long(HWND hwnd, int32_t index) {
        long result = GetWindowLongW(hwnd, index);
        if (!result) {
            error_code = GetLastError();
        }
        return result;
    }

    long window::set_window_long(HWND hwnd, int32_t index, long value) {
        long result = SetWindowLongW(hwnd, index, value);
        if (!result) {
            error_code = GetLastError();
        }
        return result;
    }

    LONG_PTR window::get_window_long_ptr(HWND hwnd, int32_t index) {
        LONG_PTR result = GetWindowLongPtrW(hwnd, index);
        if (!result) {
            error_code = GetLastError();
        }
        return result;
    }

    LONG_PTR window::set_window_long_ptr(HWND hwnd, int32_t index, LONG_PTR value) {
        LONG_PTR result = SetWindowLongPtrW(hwnd, index, value);
        if (!result) {
            error_code = GetLastError();
        }
        return result;
    }

    uint32_t window::get_window_module_file_name(HWND hwnd,
                                                     wchar_t *file_name,
                                                     uint32_t cch_size) {
        return GetWindowModuleFileNameW(hwnd, file_name, cch_size);
    }

    bool window::get_window_placement(HWND hwnd,
                                      WINDOWPLACEMENT *window_placement) {
        if (!GetWindowPlacement(hwnd, window_placement)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool window::set_window_placement(HWND hwnd,
                                      const WINDOWPLACEMENT *window_placement) {
        if (!SetWindowPlacement(hwnd, window_placement)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool window::get_window_rect(HWND hwnd, RECT *rect) {
        if (!GetWindowRect(hwnd, rect)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }


    bool window::adjust_window_rect(RECT *rect, unsigned long style, bool menu) {
        if (!AdjustWindowRect(rect,
                              style,
                              menu ? TRUE : FALSE)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool window::adjust_window_rect(RECT *rect,
                                    unsigned long style,
                                    bool menu,
                                    unsigned long ext_style) {
        if (!AdjustWindowRectEx(rect,
                                style,
                                menu ? TRUE : FALSE,
                                ext_style)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool window::adjust_window_rect_for_dpi(RECT *rect,
                                            unsigned long style,
                                            bool menu,
                                            unsigned long ext_style,
                                            uint32_t dpi) {
        if (!AdjustWindowRectExForDpi(rect,
                                      style,
                                      menu ? TRUE : FALSE,
                                      ext_style,
                                      dpi)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    int32_t window::get_window_region(HWND hwnd, HRGN region_handle) {
        return GetWindowRgn(hwnd, region_handle);
    }

    int32_t window::set_window_region(HWND hwnd, HRGN region_handle, bool is_redraw) {
        return SetWindowRgn(hwnd, region_handle, is_redraw ? TRUE : FALSE);
    }

    int32_t window::get_window_region_box(HWND hwnd, RECT *rect) {
        return GetWindowRgnBox(hwnd, rect);
    }

    int32_t window::get_window_text(HWND hwnd, wchar_t *text, int32_t cch_size) {
        int32_t result = GetWindowTextW(hwnd, text, cch_size);
        if (!result) {
            error_code = GetLastError();
        }
        return result;
    }

    bool window::set_window_text(HWND hwnd, const wchar_t *text) {
        if (!SetWindowTextW(hwnd, text)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    int32_t window::get_window_text_length(HWND hwnd) {
        int32_t result = GetWindowTextLengthW(hwnd);
        if (!result) {
            error_code = GetLastError();
        }
        return result;
    }

    unsigned long window::get_window_thread_process_id(HWND hwnd, unsigned long *pid) {
        unsigned long result = GetWindowThreadProcessId(hwnd, pid);
        if (!result) {
            error_code = GetLastError();
        }
        return result;
    }

    uint16_t window::get_window_word(HWND hwnd, int32_t index) {
        uint16_t result = GetWindowWord(hwnd, index);
        if (!result) {
            error_code = GetLastError();
        }
        return result;
    }

    bool window::inherit_window_monitor(HWND hwnd, HWND hwnd_inherit) {
        return InheritWindowMonitor(hwnd, hwnd_inherit);
    }

    int32_t window::internal_get_window_text(HWND hwnd,
                                         wchar_t *text,
                                         int32_t cch_size) {
        int32_t result = InternalGetWindowText(hwnd, text, cch_size);
        if (!result) {
            error_code = GetLastError();
        }
        return result;
    }

    bool window::is_hung_app_window(HWND hwnd) {
        return IsHungAppWindow(hwnd);
    }

    bool window::is_window(HWND hwnd) {
        return IsWindow(hwnd);
    }

    bool window::is_window_arranged(HWND hwnd) {
        bool is_ok = false;
        HMODULE hmodule = nullptr;
        do {
            hmodule = LoadLibraryW(L"user32.dll");
            if (!hmodule) {
                error_code = GetLastError();
                break;
            }
            typedef BOOL (CALLBACK *fn)(HWND);
            fn IsWindowArranged = reinterpret_cast<fn>(
                GetProcAddress(hmodule,
                               "IsWindowArranged"));
            if (!IsWindowArranged) {
                error_code = GetLastError();
                break;
            }
            if (!IsWindowArranged(hwnd)) {
                error_code = GetLastError();
                is_ok = true;
                break;
            }
        } while (false);
        if (hmodule) {
            FreeLibrary(hmodule);
        }
        return is_ok;
    }

    bool window::is_window_enabled(HWND hwnd) {
        return IsWindowEnabled(hwnd);
    }

    bool window::is_window_unicode(HWND hwnd) {
        return IsWindowUnicode(hwnd);
    }

    bool window::is_window_visible(HWND hwnd) {
        return IsWindowVisible(hwnd);
    }

    bool window::is_any_popup() {
        return AnyPopup();
    }

    HMONITOR window::monitor_from_window(HWND hwnd, unsigned long flag) {
        return MonitorFromWindow(hwnd, flag);
    }

    bool window::move_window(HWND hwnd,
                             int32_t x,
                             int32_t y,
                             int32_t width,
                             int32_t height,
                             bool is_repaint) {
        if (!MoveWindow(hwnd,
                        x,
                        y,
                        width,
                        height,
                        is_repaint ? TRUE : FALSE)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool window::print_window(HWND hwnd, HDC dc_handle, uint32_t flag) {
        return PrintWindow(hwnd, dc_handle, flag);
    }

    uint32_t window::real_get_window_class(HWND hwnd,
                                               wchar_t *class_name,
                                               uint32_t cch_size) {
        uint32_t result = RealGetWindowClassW(hwnd, class_name, cch_size);
        if (!result) {
            error_code = GetLastError();
        }
        return result;
    }

    bool window::redraw_window(HWND hwnd,
                               const RECT *rect,
                               HRGN region_handle,
                               uint32_t flag) {
        return RedrawWindow(hwnd,
                            rect,
                            region_handle,
                            flag);
    }

    bool window::scroll_window(HWND hwnd,
                               int32_t x_amount,
                               int32_t y_amount,
                               const RECT *rect,
                               const RECT *clip_rect) {
        if (!ScrollWindow(hwnd, x_amount, y_amount, rect, clip_rect)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    int32_t window::scroll_window(HWND hwnd,
                              int32_t dx,
                              int32_t dy,
                              const RECT *rect_scroll,
                              const RECT *rect_clip,
                              HRGN region_handle_update,
                              RECT *rect_update,
                              uint32_t flag) {
        int32_t result = ScrollWindowEx(hwnd,
                                    dx,
                                    dy,
                                    rect_scroll,
                                    rect_clip,
                                    region_handle_update,
                                    rect_update,
                                    flag);
        if (!result) {
            error_code = GetLastError();
        }
        return result;
    }

    void window::switch_to_this_window(HWND hwnd, bool unknown) {
        SwitchToThisWindow(hwnd, unknown ? TRUE : FALSE);
    }

    uint16_t window::tile_windows(HWND hwnd_parent,
                                        uint32_t how,
                                        const RECT *rect,
                                        uint32_t kids_num,
                                        const HWND *kids) {
        uint16_t result = TileWindows(hwnd_parent, how, rect, kids_num, kids);
        if (!result) {
            error_code = GetLastError();
        }
        return result;
    }

    bool window::win_help(HWND hwnd,
                          const wchar_t *help,
                          uint32_t cmd,
                          ULONG_PTR data) {
        if (!WinHelpW(hwnd,
                      help,
                      cmd,
                      data)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool window::restore_window(HWND hwnd) {
        if (!OpenIcon(hwnd)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool window::is_window_minimize(HWND hwnd) {
        return IsIconic(hwnd);
    }

    bool window::is_window_maximize(HWND hwnd) {
        return IsZoomed(hwnd);
    }

    unsigned long window::err_code() const {
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
}
