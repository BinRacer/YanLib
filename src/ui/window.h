//
// Created by forkernel on 2025/4/28.
//

#ifndef WINDOW_H
#define WINDOW_H
#include <Windows.h>
#include <string>

namespace YanLib::ui {
    class window {
    private:
        DWORD error_code = 0;

    public:
        window(const window &other) = delete;

        window(window &&other) = delete;

        window &operator=(const window &other) = delete;

        window &operator=(window &&other) = delete;

        window() = default;

        ~window() = default;

        HWND create_window(const wchar_t *class_name,
                           const wchar_t *window_name,
                           HINSTANCE instance,
                           void *param = nullptr,
                           HWND hwnd_parent = nullptr,
                           HMENU menu = nullptr,
                           int x = CW_USEDEFAULT,
                           int y = CW_USEDEFAULT,
                           int width = CW_USEDEFAULT,
                           int height = CW_USEDEFAULT,
                           DWORD style = WS_OVERLAPPEDWINDOW,
                           DWORD ext_style = 0);

        HWND create_mdi_window(const wchar_t *class_name,
                               const wchar_t *window_name,
                               HINSTANCE instance,
                               LPARAM l_param,
                               HWND hwnd_parent,
                               int x = CW_USEDEFAULT,
                               int y = CW_USEDEFAULT,
                               int width = CW_USEDEFAULT,
                               int height = CW_USEDEFAULT,
                               DWORD style = MDIS_ALLCHILDSTYLES | WS_OVERLAPPEDWINDOW);

        WNDCLASSEXW make_window_class(const wchar_t *class_name,
                                      WNDPROC window_proc,
                                      HINSTANCE instance,
                                      UINT style = CS_HREDRAW | CS_VREDRAW,
                                      const wchar_t *menu_name = nullptr,
                                      int cb_class_extra = 0,
                                      int cb_window_extra = 0,
                                      HICON icon = LoadIconW(nullptr,
                                                             IDI_APPLICATION),
                                      HCURSOR cursor = LoadCursorW(nullptr,
                                                                   IDC_ARROW),
                                      HBRUSH brush_background = static_cast<HBRUSH>(
                                          GetStockObject(WHITE_BRUSH)),
                                      HICON icon_small = nullptr);

        ATOM register_class(const WNDCLASSEXW *window_class);

        bool unregister_class(const wchar_t *class_name,
                              HINSTANCE instance);

        bool register_shell_hook_window(HWND hwnd);

        bool deregister_shell_hook_window(HWND hwnd);

        HHOOK set_windows_hook(int id_hook,
                               HOOKPROC fn,
                               HINSTANCE hmod,
                               DWORD tid);

        bool unhook_windows_hook(HHOOK hhk);

        LRESULT call_next_hook(HHOOK hhk,
                               int code,
                               WPARAM w_param,
                               LPARAM l_param);

        HWINEVENTHOOK set_win_event_hook(DWORD event_min,
                                         DWORD event_max,
                                         HMODULE hmod_win_event_proc,
                                         WINEVENTPROC fn_win_event_proc,
                                         DWORD pid,
                                         DWORD tid,
                                         DWORD flag);

        bool unhook_win_event(HWINEVENTHOOK hwin_event_hook);

        bool is_win_event_hook_installed(DWORD event);

        bool register_touch_hit_testing_window(HWND hwnd, ULONG value);

        bool register_touch_window(HWND hwnd,
                                   ULONG flag);

        bool unregister_touch_window(HWND hwnd);

        UINT register_window_message(const wchar_t *message);

        bool change_window_message_filter(UINT message, DWORD flag);

        bool change_window_message_filter(HWND hwnd,
                                          UINT message,
                                          DWORD action,
                                          PCHANGEFILTERSTRUCT change_filter_struct);

        bool show_window(HWND hwnd, int cmd_show) const;

        bool show_window_async(HWND hwnd, int cmd_show) const;

        bool update_window(HWND hwnd) const;

        bool update_layered_window(HWND hwnd,
                                   HDC hdc_dst,
                                   POINT *point_dst,
                                   SIZE *size,
                                   HDC hdc_src,
                                   POINT *point_src,
                                   COLORREF color_ref,
                                   BLENDFUNCTION *blend_fn,
                                   DWORD flag);

        bool lock_window_update(HWND hwnd);

        bool unlock_window_update();

        bool animate_window(HWND hwnd, DWORD time, DWORD flag);

        UINT arrange_iconic_windows(HWND hwnd);

        HDWP begin_defer_window_pos(int num_windows);

        HDWP defer_window_pos(HDWP hwin_pos_info,
                              HWND hwnd,
                              HWND hwnd_insert_after,
                              int x,
                              int y,
                              int cx,
                              int cy,
                              UINT flag);

        bool end_defer_window_pos(HDWP hwin_pos_info);

        bool set_window_pos(HWND hwnd,
                            HWND hwnd_insert_after,
                            int x,
                            int y,
                            int cx,
                            int cy,
                            UINT flag);

        bool calculate_popup_window_position(const POINT *anchor_point,
                                             const SIZE *window_size,
                                             UINT flag,
                                             RECT *exclude_rect,
                                             RECT *popup_window_position);

        bool bring_window_to_top(HWND hwnd);

        LRESULT call_window_proc(WNDPROC prev_wnd_func,
                                 HWND hwnd,
                                 UINT msg,
                                 WPARAM w_param,
                                 LPARAM l_param);

        LRESULT def_window_proc(HWND hwnd,
                                UINT msg,
                                WPARAM w_param,
                                LPARAM l_param);

        WORD cascade_windows(HWND hwnd_parent,
                             UINT how,
                             const RECT *rect,
                             UINT kids_count,
                             const HWND *kids);

        HWND child_window_from_point(HWND hwnd_parent, POINT point);

        HWND child_window_from_point(HWND hwnd_parent, POINT point, UINT flag);

        HWND real_child_window_from_point(HWND hwnd_parent,
                                          POINT parent_client_coords);

        HWND window_from_physical_point(POINT point);

        HWND window_from_point(POINT point);

        int map_window_points(HWND hwnd_from,
                              HWND hwnd_to,
                              LPPOINT point,
                              UINT count);

        bool close_window(HWND hwnd);

        HWINSTA create_window_station(const wchar_t *window_station,
                                      DWORD flag,
                                      ACCESS_MASK desired_access,
                                      LPSECURITY_ATTRIBUTES security_attrs);

        HWINSTA open_window_station(const wchar_t *window_station,
                                    bool is_inherit,
                                    ACCESS_MASK desired_access);

        bool close_window_station(HWINSTA window_station);

        bool enum_window_stations(WINSTAENUMPROCW enum_func,
                                  LPARAM l_param);

        HWINSTA get_process_window_station();

        bool set_process_window_station(HWINSTA window_station);

        bool destroy_window(HWND hwnd);

        void disable_process_windows_ghosting();

        bool enable_window(HWND hwnd, bool enable);

        bool enum_windows(WNDENUMPROC enum_func, LPARAM l_param);

        bool enum_child_windows(HWND hwnd_parent,
                                WNDENUMPROC enum_func,
                                LPARAM l_param);

        bool enum_desktop_windows(HDESK desktop,
                                  WNDENUMPROC fn,
                                  LPARAM l_param);

        bool enum_thread_windows(DWORD tid,
                                 WNDENUMPROC fn,
                                 LPARAM l_param);

        bool exit_windows(UINT flag, DWORD reason);

        HWND find_window(const wchar_t *class_name,
                         const wchar_t *window_name);

        HWND find_window(HWND hwnd_parent,
                         HWND hwnd_child_after,
                         const wchar_t *class_name,
                         const wchar_t *window_name);

        bool flash_window(HWND hwnd, bool invert);

        bool flash_window(PFLASHWINFO flash_info);

        HWND get_active_window();

        HWND set_active_window(HWND hwnd);

        HWND get_desktop_window();

        UINT get_dpi_for_window(HWND hwnd);

        HWND get_foreground_window();

        bool set_foreground_window(HWND hwnd);

        bool allow_set_foreground_window(DWORD pid);

        bool lock_set_foreground_window();

        bool unlock_set_foreground_window();

        bool get_layered_window_attrs(HWND hwnd,
                                      COLORREF *color_ref,
                                      uint8_t *alpha,
                                      DWORD *flag);

        bool set_layered_window_attrs(HWND hwnd,
                                      COLORREF color_ref,
                                      uint8_t alpha,
                                      DWORD flag);

        HWND get_window(HWND hwnd, UINT cmd);

        HWND get_next_window(HWND hwnd, UINT cmd);

        HWND get_open_clipboard_window();

        HWND get_shell_window();

        HWND get_top_window(HWND hwnd);

        DWORD get_window_context_help_id(HWND hwnd);

        bool set_window_context_help_id(HWND hwnd,
                                        DWORD param);

        HDC get_window_dc(HWND hwnd);

        HWND window_from_dc(HDC hdc);

        bool get_window_display_affinity(HWND hwnd, DWORD *affinity);

        bool set_window_display_affinity(HWND hwnd, DWORD affinity);

        DPI_AWARENESS_CONTEXT get_window_dpi_awareness_context(HWND hwnd);

        DPI_HOSTING_BEHAVIOR get_window_dpi_hosting_behavior(HWND hwnd);

        bool get_window_feedback_setting(HWND hwnd,
                                         FEEDBACK_TYPE feedback,
                                         DWORD flag,
                                         UINT32 *size,
                                         void *config);

        bool set_window_feedback_setting(HWND hwnd,
                                         FEEDBACK_TYPE feedback,
                                         DWORD flag,
                                         UINT32 size,
                                         const void *config);

        bool get_window_info(HWND hwnd, PWINDOWINFO window_info);

        LONG get_window_long(HWND hwnd, int index);

        LONG set_window_long(HWND hwnd,
                             int index,
                             LONG value);

        LONG_PTR get_window_long_ptr(HWND hwnd, int index);

        LONG_PTR set_window_long_ptr(HWND hwnd,
                                     int index,
                                     LONG_PTR value);

        UINT get_window_module_file_name(HWND hwnd,
                                         wchar_t *file_name,
                                         UINT cch_size = MAX_PATH);

        bool get_window_placement(HWND hwnd,
                                  WINDOWPLACEMENT *window_placement);

        bool set_window_placement(HWND hwnd,
                                  const WINDOWPLACEMENT *window_placement);

        bool get_window_rect(HWND hwnd, LPRECT rect);

        bool adjust_window_rect(LPRECT rect, DWORD style, bool menu);

        bool adjust_window_rect(LPRECT rect,
                                DWORD style,
                                bool menu,
                                DWORD ext_style);

        bool adjust_window_rect_for_dpi(LPRECT rect,
                                        DWORD style,
                                        bool menu,
                                        DWORD ext_style,
                                        UINT dpi);

        int get_window_rgn(HWND hwnd, HRGN hrgn);

        int set_window_rgn(HWND hwnd,
                           HRGN hrgn,
                           bool is_redraw);

        int get_window_rgn_box(HWND hwnd, LPRECT rect);

        int get_window_text(HWND hwnd,
                            wchar_t *text,
                            int cch_size);

        bool set_window_text(HWND hwnd,
                             const wchar_t *text);

        int get_window_text_length(HWND hwnd);

        DWORD get_window_thread_process_id(HWND hwnd,
                                           LPDWORD pid);

        WORD get_window_word(HWND hwnd, int index);

        bool inherit_window_monitor(HWND hwnd,
                                    HWND hwnd_inherit);

        int internal_get_window_text(HWND hwnd,
                                     wchar_t *text,
                                     int cch_size);

        bool is_hung_app_window(HWND hwnd);

        bool is_touch_window(HWND hwnd,
                             PULONG flag);

        bool is_window(HWND hwnd);

        bool is_window_arranged(HWND hwnd);

        bool is_window_enabled(HWND hwnd);

        bool is_window_unicode(HWND hwnd);

        bool is_window_visible(HWND hwnd);

        HMONITOR monitor_from_window(HWND hwnd,
                                     DWORD flag);

        bool move_window(HWND hwnd,
                         int x,
                         int y,
                         int width,
                         int height,
                         bool is_repaint);

        bool print_window(HWND hwnd,
                          HDC hdc,
                          UINT flag);

        UINT real_get_window_class(HWND hwnd,
                                   wchar_t *class_name,
                                   UINT cch_size = MAX_PATH);

        bool redraw_window(HWND hwnd,
                           const RECT *rect,
                           HRGN hrgn,
                           UINT flag);

        bool scroll_window(HWND hwnd,
                           int x_amount,
                           int y_amount,
                           const RECT *rect,
                           const RECT *clip_rect);

        int scroll_window(HWND hwnd,
                          int dx,
                          int dy,
                          const RECT *rect_scroll,
                          const RECT *rect_clip,
                          HRGN hrgn_update,
                          LPRECT rect_update,
                          UINT flag);

        void switch_to_this_window(HWND hwnd, bool unknown = false);

        WORD tile_windows(HWND hwnd_parent,
                          UINT how,
                          const RECT *rect,
                          UINT kids_num,
                          const HWND *kids);

        bool win_help(HWND hwnd,
                      const wchar_t *help,
                      UINT cmd,
                      ULONG_PTR data);

        [[nodiscard]] DWORD err_code() const;

        [[nodiscard]] std::string err_string() const;

        [[nodiscard]] std::wstring err_wstring() const;
    };
}
#endif //WINDOW_H
