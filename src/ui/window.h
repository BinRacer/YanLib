//
// Created by forkernel on 2025/4/28.
//

#ifndef WINDOW_H
#define WINDOW_H
#ifndef WINNT
#define WINNT
#endif
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
                           int32_t x = CW_USEDEFAULT,
                           int32_t y = CW_USEDEFAULT,
                           int32_t width = CW_USEDEFAULT,
                           int32_t height = CW_USEDEFAULT,
                           unsigned long style = WS_OVERLAPPEDWINDOW,
                           unsigned long ext_style = 0);

        HWND create_mdi_window(const wchar_t *class_name,
                               const wchar_t *window_name,
                               HINSTANCE instance_handle,
                               LPARAM l_param,
                               HWND hwnd_parent,
                               int32_t x = CW_USEDEFAULT,
                               int32_t y = CW_USEDEFAULT,
                               int32_t width = CW_USEDEFAULT,
                               int32_t height = CW_USEDEFAULT,
                               unsigned long style = MDIS_ALLCHILDSTYLES |
                                                     WS_OVERLAPPEDWINDOW);

        WNDCLASSEXW make_window_class(const wchar_t *class_name,
                                      WNDPROC window_proc,
                                      HINSTANCE instance_handle,
                                      uint32_t style = CS_HREDRAW | CS_VREDRAW,
                                      const wchar_t *menu_name = nullptr,
                                      int32_t cb_class_extra = 0,
                                      int32_t cb_window_extra = 0,
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

        unsigned long get_class_long(HWND hwnd, int32_t index);

        unsigned long set_class_long(HWND hwnd, int32_t index, long value);

        ULONG_PTR get_class_long_ptr(HWND hwnd, int32_t index);

        ULONG_PTR set_class_long_ptr(HWND hwnd, int32_t index, LONG_PTR value);

        uint16_t get_class_word(HWND hwnd, int32_t index);

        uint16_t set_class_word(HWND hwnd, int32_t index, uint16_t value);

        int32_t get_class_name(HWND hwnd, wchar_t *class_name, int32_t cch_size);

        int32_t enum_props(HWND hwnd, PROPENUMPROCW enum_func);

        int32_t enum_props(HWND hwnd, PROPENUMPROCEXW enum_func, LPARAM l_param);

        HANDLE get_prop(HWND hwnd, const wchar_t *text);

        bool set_prop(HWND hwnd, const wchar_t *text, HANDLE data_handle);

        HANDLE remove_prop(HWND hwnd, const wchar_t *text);

        bool register_shell_hook_window(HWND hwnd);

        bool deregister_shell_hook_window(HWND hwnd);

        HHOOK set_windows_hook(int32_t id_hook,
                               HOOKPROC fn,
                               HINSTANCE hmod,
                               unsigned long tid);

        bool unhook_windows_hook(HHOOK hhk);

        LRESULT call_next_hook(HHOOK hhk,
                               int32_t code,
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

        void notify_win_event(unsigned long event,
                              HWND hwnd,
                              int32_t object_id,
                              int32_t child_id);

        bool show_window(HWND hwnd, int32_t cmd_show) const;

        bool show_window_async(HWND hwnd, int32_t cmd_show) const;

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

        bool close_window(HWND hwnd);

        bool close_window(HWND hwnd, bool is_force);

        bool exit_windows(uint32_t flag, unsigned long reason);

        bool destroy_window(HWND hwnd);

        bool enable_window(HWND hwnd, bool enable);

        bool enum_windows(WNDENUMPROC enum_func, LPARAM l_param);

        bool enum_child_windows(HWND hwnd_parent,
                                WNDENUMPROC enum_func,
                                LPARAM l_param);

        bool enum_thread_windows(unsigned long tid,
                                 WNDENUMPROC fn,
                                 LPARAM l_param);

        HWND find_window(const wchar_t *class_name,
                         const wchar_t *window_name);

        HWND find_window(HWND hwnd_parent,
                         HWND hwnd_child_after,
                         const wchar_t *class_name,
                         const wchar_t *window_name);

        bool flash_window(HWND hwnd, bool invert);

        bool flash_window(FLASHWINFO *flash_info);

        bool move_window(HWND hwnd,
                         int32_t x,
                         int32_t y,
                         int32_t width,
                         int32_t height,
                         bool is_repaint);

        bool print_window(HWND hwnd,
                          HDC dc_handle,
                          uint32_t flag);

        bool redraw_window(HWND hwnd,
                           const RECT *rect,
                           HRGN region_handle,
                           uint32_t flag);

        bool maximize_window(HWND hwnd);

        bool minimize_window(HWND hwnd);

        bool hide_window(HWND hwnd);

        bool restore_window(HWND hwnd);

        bool restore_icon_window(HWND hwnd);

        uint16_t tile_windows(HWND hwnd_parent,
                              uint32_t how,
                              const RECT *rect,
                              uint32_t kids_num,
                              const HWND *kids);

        HWND get_parent_window(HWND hwnd);

        HWND set_parent_window(HWND hwnd_child, HWND hwnd_new_parent);

        HWND get_ancestor_window(HWND hwnd, uint32_t flag);

        bool show_popup_window(HWND hwnd);

        bool hide_popup_window(HWND hwnd);

        HWND get_last_active_popup_window(HWND hwnd);

        bool is_hung_app_window(HWND hwnd);

        bool is_window(HWND hwnd);

        bool is_window_arranged(HWND hwnd);

        bool is_window_enabled(HWND hwnd);

        bool is_window_unicode(HWND hwnd);

        bool is_window_visible(HWND hwnd);

        bool is_window_minimize(HWND hwnd);

        bool is_window_maximize(HWND hwnd);

        bool is_child_window(HWND hwnd_parent, HWND hwnd);

        bool is_any_popup();

        uint32_t arrange_minimize_windows(HWND hwnd);

        bool get_process_default_layout(unsigned long *default_layout);

        bool set_process_default_layout(unsigned long default_layout);

        HDWP begin_defer_window_pos(int32_t num_windows);

        HDWP defer_window_pos(HDWP hwin_pos_info,
                              HWND hwnd,
                              HWND hwnd_insert_after,
                              int32_t x,
                              int32_t y,
                              int32_t cx,
                              int32_t cy,
                              uint32_t flag);

        bool end_defer_window_pos(HDWP hwin_pos_info);

        bool set_window_pos(HWND hwnd,
                            HWND hwnd_insert_after,
                            int32_t x,
                            int32_t y,
                            int32_t cx,
                            int32_t cy,
                            uint32_t flag);

        bool calculate_popup_window_position(const POINT *anchor_point,
                                             const SIZE *window_size,
                                             uint32_t flag,
                                             RECT *exclude_rect,
                                             RECT *popup_window_position);

        HWND child_window_from_point(HWND hwnd_parent, POINT point);

        HWND child_window_from_point(HWND hwnd_parent, POINT point, uint32_t flag);

        HWND real_child_window_from_point(HWND hwnd_parent,
                                          POINT parent_client_coords);

        HWND window_from_physical_point(POINT point);

        HWND window_from_point(POINT point);

        int32_t map_window_points(HWND hwnd_from,
                                  HWND hwnd_to,
                                  POINT *point,
                                  uint32_t count);

        bool bring_window_to_top(HWND hwnd);

        LRESULT call_window_proc(WNDPROC prev_wnd_func,
                                 HWND hwnd,
                                 uint32_t msg,
                                 WPARAM w_param,
                                 LPARAM l_param);

        LRESULT default_window_proc(HWND hwnd,
                                    uint32_t msg,
                                    WPARAM w_param,
                                    LPARAM l_param);

        LRESULT default_frame_proc(HWND hwnd,
                                   HWND hwnd_mdi_client,
                                   uint32_t msg,
                                   WPARAM w_param,
                                   LPARAM l_param);

        LRESULT default_mdi_child_proc(HWND hwnd,
                                       uint32_t msg,
                                       WPARAM w_param,
                                       LPARAM l_param);

        uint16_t cascade_windows(HWND hwnd_parent,
                                 uint32_t how,
                                 const RECT *rect,
                                 uint32_t kids_count,
                                 const HWND *kids);

        void disable_process_windows_ghosting();

        HWND get_active_window();

        HWND set_active_window(HWND hwnd);

        uint32_t get_dpi_for_window(HWND hwnd);

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

        HWND get_window(HWND hwnd, uint32_t cmd);

        HWND get_next_window(HWND hwnd, uint32_t cmd);

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
                                         uint32_t *size,
                                         void *config);

        bool set_window_feedback_setting(HWND hwnd,
                                         FEEDBACK_TYPE feedback,
                                         unsigned long flag,
                                         uint32_t size,
                                         const void *config);

        bool get_window_info(HWND hwnd, WINDOWINFO *window_info);

        long get_window_long(HWND hwnd, int32_t index);

        long set_window_long(HWND hwnd,
                             int32_t index,
                             long value);

        LONG_PTR get_window_long_ptr(HWND hwnd, int32_t index);

        LONG_PTR set_window_long_ptr(HWND hwnd,
                                     int32_t index,
                                     LONG_PTR value);

        uint32_t get_window_module_file_name(HWND hwnd,
                                             wchar_t *file_name,
                                             uint32_t cch_size = MAX_PATH);

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
                                        uint32_t dpi);

        int32_t get_window_region(HWND hwnd, HRGN region_handle);

        int32_t set_window_region(HWND hwnd,
                                  HRGN region_handle,
                                  bool is_redraw);

        int32_t get_window_region_box(HWND hwnd, RECT *rect);

        int32_t get_window_text(HWND hwnd,
                                wchar_t *text,
                                int32_t cch_size);

        bool set_window_text(HWND hwnd,
                             const wchar_t *text);

        int32_t get_window_text_length(HWND hwnd);

        unsigned long get_window_thread_process_id(HWND hwnd,
                                                   unsigned long *pid);

        uint16_t get_window_word(HWND hwnd, int32_t index);

        int32_t internal_get_window_text(HWND hwnd,
                                         wchar_t *text,
                                         int32_t cch_size);

        uint32_t real_get_window_class(HWND hwnd,
                                       wchar_t *class_name,
                                       uint32_t cch_size = MAX_PATH);

        void switch_to_this_window(HWND hwnd, bool unknown = false);

        bool win_help(HWND hwnd,
                      const wchar_t *help,
                      uint32_t cmd,
                      ULONG_PTR data);

        unsigned long get_gui_resources(HANDLE proc_handle, unsigned long flag);

        bool get_gui_thread_info(unsigned long tid,
                                 GUITHREADINFO *gui_thread_info);

        bool is_gui_thread(bool is_convert);

        bool get_alt_tab_info(HWND hwnd,
                              int32_t item_index,
                              ALTTABINFO *alt_tab_info,
                              wchar_t *item_text,
                              uint32_t cch_item_text);

        [[nodiscard]] unsigned long err_code() const;

        [[nodiscard]] std::string err_string() const;

        [[nodiscard]] std::wstring err_wstring() const;
    };
}
#endif //WINDOW_H
