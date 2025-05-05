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
        unsigned long error_code = 0;

    public:
        window(const window &other) = delete;

        window(window &&other) = delete;

        window &operator=(const window &other) = delete;

        window &operator=(window &&other) = delete;

        window() = default;

        ~window() = default;

        HWND create_window(const wchar_t *class_name,
                           const wchar_t *window_name,
                           HINSTANCE instance_handle,
                           void *param = nullptr,
                           HWND hwnd_parent = nullptr,
                           HMENU menu_handle = nullptr,
                           int x = CW_USEDEFAULT,
                           int y = CW_USEDEFAULT,
                           int width = CW_USEDEFAULT,
                           int height = CW_USEDEFAULT,
                           unsigned long style = WS_OVERLAPPEDWINDOW,
                           unsigned long ext_style = 0);

        HWND create_mdi_window(const wchar_t *class_name,
                               const wchar_t *window_name,
                               HINSTANCE instance_handle,
                               LPARAM l_param,
                               HWND hwnd_parent,
                               int x = CW_USEDEFAULT,
                               int y = CW_USEDEFAULT,
                               int width = CW_USEDEFAULT,
                               int height = CW_USEDEFAULT,
                               unsigned long style = MDIS_ALLCHILDSTYLES |
                                                     WS_OVERLAPPEDWINDOW);

        WNDCLASSEXW make_window_class(const wchar_t *class_name,
                                      WNDPROC window_proc,
                                      HINSTANCE instance_handle,
                                      unsigned int style = CS_HREDRAW | CS_VREDRAW,
                                      const wchar_t *menu_name = nullptr,
                                      int cb_class_extra = 0,
                                      int cb_window_extra = 0,
                                      HICON icon_handle = LoadIconW(
                                          nullptr,
                                          IDI_APPLICATION),
                                      HCURSOR cursor_handle = LoadCursorW(
                                          nullptr,
                                          IDC_ARROW),
                                      HBRUSH brush_background_handle =
                                              static_cast<HBRUSH>(
                                                  GetStockObject(WHITE_BRUSH)),
                                      HICON icon_small_handle = nullptr);

        ATOM register_class(const WNDCLASSEXW *window_class);

        bool unregister_class(const wchar_t *class_name,
                              HINSTANCE instance_handle);

        bool get_class_info(HINSTANCE instance_handle,
                            const wchar_t *class_name,
                            WNDCLASSW *wnd_class);

        bool get_class_info(HINSTANCE instance_handle,
                            const wchar_t *class_name,
                            WNDCLASSEXW *wnd_class);

        unsigned long get_class_long(HWND hwnd, int index);

        unsigned long set_class_long(HWND hwnd, int index, long value);

        ULONG_PTR get_class_long_ptr(HWND hwnd, int index);

        ULONG_PTR set_class_long_ptr(HWND hwnd, int index, LONG_PTR value);

        unsigned short get_class_word(HWND hwnd, int index);

        unsigned short set_class_word(HWND hwnd, int index, unsigned short value);

        int get_class_name(HWND hwnd, wchar_t *class_name, int cch_size);

        int enum_props(HWND hwnd, PROPENUMPROCW enum_func);

        int enum_props(HWND hwnd, PROPENUMPROCEXW enum_func, LPARAM l_param);

        HANDLE get_prop(HWND hwnd, const wchar_t *text);

        bool set_prop(HWND hwnd, const wchar_t *text, HANDLE data_handle);

        HANDLE remove_prop(HWND hwnd, const wchar_t *text);

        bool register_shell_hook_window(HWND hwnd);

        bool deregister_shell_hook_window(HWND hwnd);

        HHOOK set_windows_hook(int id_hook,
                               HOOKPROC fn,
                               HINSTANCE hmod,
                               unsigned long tid);

        bool unhook_windows_hook(HHOOK hhk);

        LRESULT call_next_hook(HHOOK hhk,
                               int code,
                               WPARAM w_param,
                               LPARAM l_param);

        HWINEVENTHOOK set_win_event_hook(unsigned long event_min,
                                         unsigned long event_max,
                                         HMODULE hmod_win_event_proc,
                                         WINEVENTPROC fn_win_event_proc,
                                         unsigned long pid,
                                         unsigned long tid,
                                         unsigned long flag);

        bool unhook_win_event(HWINEVENTHOOK hwin_event_hook);

        bool is_win_event_hook_installed(unsigned long event);

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
                                   unsigned long flag);

        bool lock_window_update(HWND hwnd);

        bool unlock_window_update();

        bool animate_window(HWND hwnd, unsigned long time, unsigned long flag);

        unsigned int arrange_minimize_windows(HWND hwnd);

        HDWP begin_defer_window_pos(int num_windows);

        HDWP defer_window_pos(HDWP hwin_pos_info,
                              HWND hwnd,
                              HWND hwnd_insert_after,
                              int x,
                              int y,
                              int cx,
                              int cy,
                              unsigned int flag);

        bool end_defer_window_pos(HDWP hwin_pos_info);

        bool set_window_pos(HWND hwnd,
                            HWND hwnd_insert_after,
                            int x,
                            int y,
                            int cx,
                            int cy,
                            unsigned int flag);

        bool calculate_popup_window_position(const POINT *anchor_point,
                                             const SIZE *window_size,
                                             unsigned int flag,
                                             RECT *exclude_rect,
                                             RECT *popup_window_position);

        bool bring_window_to_top(HWND hwnd);

        LRESULT call_window_proc(WNDPROC prev_wnd_func,
                                 HWND hwnd,
                                 unsigned int msg,
                                 WPARAM w_param,
                                 LPARAM l_param);

        LRESULT default_window_proc(HWND hwnd,
                                    unsigned int msg,
                                    WPARAM w_param,
                                    LPARAM l_param);

        LRESULT default_frame_proc(HWND hwnd,
                                   HWND hwnd_mdi_client,
                                   unsigned int msg,
                                   WPARAM w_param,
                                   LPARAM l_param);

        LRESULT default_mdi_child_proc(HWND hwnd,
                                       unsigned int msg,
                                       WPARAM w_param,
                                       LPARAM l_param);

        unsigned short cascade_windows(HWND hwnd_parent,
                                       unsigned int how,
                                       const RECT *rect,
                                       unsigned int kids_count,
                                       const HWND *kids);

        HWND child_window_from_point(HWND hwnd_parent, POINT point);

        HWND child_window_from_point(HWND hwnd_parent, POINT point, unsigned int flag);

        HWND real_child_window_from_point(HWND hwnd_parent,
                                          POINT parent_client_coords);

        HWND window_from_physical_point(POINT point);

        HWND window_from_point(POINT point);

        int map_window_points(HWND hwnd_from,
                              HWND hwnd_to,
                              POINT *point,
                              unsigned int count);

        bool close_window(HWND hwnd);

        bool destroy_window(HWND hwnd);

        void disable_process_windows_ghosting();

        bool enable_window(HWND hwnd, bool enable);

        bool enum_windows(WNDENUMPROC enum_func, LPARAM l_param);

        bool enum_child_windows(HWND hwnd_parent,
                                WNDENUMPROC enum_func,
                                LPARAM l_param);

        bool enum_thread_windows(unsigned long tid,
                                 WNDENUMPROC fn,
                                 LPARAM l_param);

        bool exit_windows(unsigned int flag, unsigned long reason);

        HWND find_window(const wchar_t *class_name,
                         const wchar_t *window_name);

        HWND find_window(HWND hwnd_parent,
                         HWND hwnd_child_after,
                         const wchar_t *class_name,
                         const wchar_t *window_name);

        bool flash_window(HWND hwnd, bool invert);

        bool flash_window(FLASHWINFO *flash_info);

        HWND get_active_window();

        HWND set_active_window(HWND hwnd);

        unsigned int get_dpi_for_window(HWND hwnd);

        HWND get_foreground_window();

        bool set_foreground_window(HWND hwnd);

        bool allow_set_foreground_window(unsigned long pid);

        bool lock_set_foreground_window();

        bool unlock_set_foreground_window();

        bool get_layered_window_attrs(HWND hwnd,
                                      COLORREF *color_ref,
                                      uint8_t *alpha,
                                      unsigned long *flag);

        bool set_layered_window_attrs(HWND hwnd,
                                      COLORREF color_ref,
                                      uint8_t alpha,
                                      unsigned long flag);

        HWND get_window(HWND hwnd, unsigned int cmd);

        HWND get_next_window(HWND hwnd, unsigned int cmd);

        HWND get_shell_window();

        HWND get_top_window(HWND hwnd);

        unsigned long get_window_context_help_id(HWND hwnd);

        bool set_window_context_help_id(HWND hwnd,
                                        unsigned long param);

        bool get_window_display_affinity(HWND hwnd, unsigned long *affinity);

        bool set_window_display_affinity(HWND hwnd, unsigned long affinity);

        DPI_AWARENESS_CONTEXT get_window_dpi_awareness_context(HWND hwnd);

        DPI_HOSTING_BEHAVIOR get_window_dpi_hosting_behavior(HWND hwnd);

        bool get_window_feedback_setting(HWND hwnd,
                                         FEEDBACK_TYPE feedback,
                                         unsigned long flag,
                                         unsigned int *size,
                                         void *config);

        bool set_window_feedback_setting(HWND hwnd,
                                         FEEDBACK_TYPE feedback,
                                         unsigned long flag,
                                         unsigned int size,
                                         const void *config);

        bool get_window_info(HWND hwnd, WINDOWINFO *window_info);

        long get_window_long(HWND hwnd, int index);

        long set_window_long(HWND hwnd,
                             int index,
                             long value);

        LONG_PTR get_window_long_ptr(HWND hwnd, int index);

        LONG_PTR set_window_long_ptr(HWND hwnd,
                                     int index,
                                     LONG_PTR value);

        unsigned int get_window_module_file_name(HWND hwnd,
                                                 wchar_t *file_name,
                                                 unsigned int cch_size = MAX_PATH);

        bool get_window_placement(HWND hwnd,
                                  WINDOWPLACEMENT *window_placement);

        bool set_window_placement(HWND hwnd,
                                  const WINDOWPLACEMENT *window_placement);

        bool get_window_rect(HWND hwnd, RECT *rect);

        bool adjust_window_rect(RECT *rect, unsigned long style, bool menu);

        bool adjust_window_rect(RECT *rect,
                                unsigned long style,
                                bool menu,
                                unsigned long ext_style);

        bool adjust_window_rect_for_dpi(RECT *rect,
                                        unsigned long style,
                                        bool menu,
                                        unsigned long ext_style,
                                        unsigned int dpi);

        int get_window_region(HWND hwnd, HRGN region_handle);

        int set_window_region(HWND hwnd,
                              HRGN region_handle,
                              bool is_redraw);

        int get_window_region_box(HWND hwnd, RECT *rect);

        int get_window_text(HWND hwnd,
                            wchar_t *text,
                            int cch_size);

        bool set_window_text(HWND hwnd,
                             const wchar_t *text);

        int get_window_text_length(HWND hwnd);

        unsigned long get_window_thread_process_id(HWND hwnd,
                                                   unsigned long *pid);

        unsigned short get_window_word(HWND hwnd, int index);

        bool inherit_window_monitor(HWND hwnd,
                                    HWND hwnd_inherit);

        int internal_get_window_text(HWND hwnd,
                                     wchar_t *text,
                                     int cch_size);

        bool is_hung_app_window(HWND hwnd);

        bool is_window(HWND hwnd);

        bool is_window_arranged(HWND hwnd);

        bool is_window_enabled(HWND hwnd);

        bool is_window_unicode(HWND hwnd);

        bool is_window_visible(HWND hwnd);

        bool is_any_popup();

        HMONITOR monitor_from_window(HWND hwnd,
                                     unsigned long flag);

        bool move_window(HWND hwnd,
                         int x,
                         int y,
                         int width,
                         int height,
                         bool is_repaint);

        bool print_window(HWND hwnd,
                          HDC dc_handle,
                          unsigned int flag);

        unsigned int real_get_window_class(HWND hwnd,
                                           wchar_t *class_name,
                                           unsigned int cch_size = MAX_PATH);

        bool redraw_window(HWND hwnd,
                           const RECT *rect,
                           HRGN region_handle,
                           unsigned int flag);

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
                          HRGN region_handle_update,
                          RECT *rect_update,
                          unsigned int flag);

        void switch_to_this_window(HWND hwnd, bool unknown = false);

        unsigned short tile_windows(HWND hwnd_parent,
                                    unsigned int how,
                                    const RECT *rect,
                                    unsigned int kids_num,
                                    const HWND *kids);

        bool win_help(HWND hwnd,
                      const wchar_t *help,
                      unsigned int cmd,
                      ULONG_PTR data);

        bool restore_window(HWND hwnd);

        bool is_window_minimize(HWND hwnd);

        bool is_window_maximize(HWND hwnd);

        [[nodiscard]] unsigned long err_code() const;

        [[nodiscard]] std::string err_string() const;

        [[nodiscard]] std::wstring err_wstring() const;
    };
}
#endif //WINDOW_H
