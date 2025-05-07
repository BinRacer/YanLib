//
// Created by forkernel on 2025/4/28.
//

#ifndef WINDOW_H
#define WINDOW_H
#ifndef WINNT
#define WINNT
#endif
#include <Windows.h>
#include <shellscalingapi.h>
#include <vector>
#include <string>
#include "helper/convert.h"

namespace YanLib::ui {
class window {
private:
    uint32_t error_code = 0;

public:
    window(const window &other)            = delete;

    window(window &&other)                 = delete;

    window &operator=(const window &other) = delete;

    window &operator=(window &&other)      = delete;

    window()                               = default;

    ~window()                              = default;

    HWND create(const char *class_name,
        const char         *window_name,
        HINSTANCE           instance_handle,
        void               *param       = nullptr,
        HWND                hwnd_parent = nullptr,
        HMENU               menu_handle = nullptr,
        int32_t             x           = CW_USEDEFAULT,
        int32_t             y           = CW_USEDEFAULT,
        int32_t             width       = CW_USEDEFAULT,
        int32_t             height      = CW_USEDEFAULT,
        uint32_t            style       = WS_OVERLAPPEDWINDOW,
        uint32_t            ext_style   = 0);

    HWND create(const wchar_t *class_name,
        const wchar_t         *window_name,
        HINSTANCE              instance_handle,
        void                  *param       = nullptr,
        HWND                   hwnd_parent = nullptr,
        HMENU                  menu_handle = nullptr,
        int32_t                x           = CW_USEDEFAULT,
        int32_t                y           = CW_USEDEFAULT,
        int32_t                width       = CW_USEDEFAULT,
        int32_t                height      = CW_USEDEFAULT,
        uint32_t               style       = WS_OVERLAPPEDWINDOW,
        uint32_t               ext_style   = 0);

    HWND create_mdi(const char *class_name,
        const char             *window_name,
        HINSTANCE               instance_handle,
        LPARAM                  lparam,
        HWND                    hwnd_parent,
        int32_t                 x      = CW_USEDEFAULT,
        int32_t                 y      = CW_USEDEFAULT,
        int32_t                 width  = CW_USEDEFAULT,
        int32_t                 height = CW_USEDEFAULT,
        uint32_t style = MDIS_ALLCHILDSTYLES | WS_OVERLAPPEDWINDOW);

    HWND create_mdi(const wchar_t *class_name,
        const wchar_t             *window_name,
        HINSTANCE                  instance_handle,
        LPARAM                     lparam,
        HWND                       hwnd_parent,
        int32_t                    x      = CW_USEDEFAULT,
        int32_t                    y      = CW_USEDEFAULT,
        int32_t                    width  = CW_USEDEFAULT,
        int32_t                    height = CW_USEDEFAULT,
        uint32_t style = MDIS_ALLCHILDSTYLES | WS_OVERLAPPEDWINDOW);

    WNDCLASSEXA make_class(const char *class_name,
        WNDPROC                        window_proc,
        HINSTANCE                      instance_handle,
        uint32_t                       style     = CS_HREDRAW | CS_VREDRAW,
        const char                    *menu_name = nullptr,
        int32_t                        class_extra_size  = 0,
        int32_t                        window_extra_size = 0,
        HICON   icon_handle             = LoadIconW(nullptr, IDI_APPLICATION),
        HCURSOR cursor_handle           = LoadCursorW(nullptr, IDC_ARROW),
        HBRUSH  brush_background_handle = static_cast<HBRUSH>(
            GetStockObject(WHITE_BRUSH)),
        HICON icon_small_handle = nullptr);

    WNDCLASSEXW make_class(const wchar_t *class_name,
        WNDPROC                           window_proc,
        HINSTANCE                         instance_handle,
        uint32_t                          style     = CS_HREDRAW | CS_VREDRAW,
        const wchar_t                    *menu_name = nullptr,
        int32_t                           class_extra_size  = 0,
        int32_t                           window_extra_size = 0,
        HICON   icon_handle             = LoadIconW(nullptr, IDI_APPLICATION),
        HCURSOR cursor_handle           = LoadCursorW(nullptr, IDC_ARROW),
        HBRUSH  brush_background_handle = static_cast<HBRUSH>(
            GetStockObject(WHITE_BRUSH)),
        HICON icon_small_handle = nullptr);

    ATOM register_class(const WNDCLASSEXA *window_class);

    ATOM register_class(const WNDCLASSEXW *window_class);

    bool unregister_class(const char *class_name, HINSTANCE instance_handle);

    bool unregister_class(const wchar_t *class_name, HINSTANCE instance_handle);

    bool get_class_info(HINSTANCE instance_handle,
        const char               *class_name,
        WNDCLASSA                *wnd_class);

    bool get_class_info(HINSTANCE instance_handle,
        const wchar_t            *class_name,
        WNDCLASSW                *wnd_class);

    bool get_class_info(HINSTANCE instance_handle,
        const char               *class_name,
        WNDCLASSEXA              *wnd_class);

    bool get_class_info(HINSTANCE instance_handle,
        const wchar_t            *class_name,
        WNDCLASSEXW              *wnd_class);

    uint32_t get_class_long(HWND hwnd, int32_t index);

    uint32_t set_class_long(HWND hwnd, int32_t index, long value);

    ULONG_PTR get_class_long_ptr(HWND hwnd, int32_t index);

    ULONG_PTR set_class_long_ptr(HWND hwnd, int32_t index, LONG_PTR value);

    uint16_t get_class_word(HWND hwnd, int32_t index);

    uint16_t set_class_word(HWND hwnd, int32_t index, uint16_t value);

    int32_t get_class_name(HWND hwnd, std::string &class_name);

    int32_t get_class_name(HWND hwnd, std::wstring &class_name);

    int32_t enum_props(HWND hwnd, PROPENUMPROCA enum_func);

    int32_t enum_props(HWND hwnd, PROPENUMPROCW enum_func);

    int32_t enum_props(HWND hwnd, PROPENUMPROCEXA enum_func, LPARAM lparam);

    int32_t enum_props(HWND hwnd, PROPENUMPROCEXW enum_func, LPARAM lparam);

    HANDLE get_prop(HWND hwnd, const char *text);

    HANDLE get_prop(HWND hwnd, const wchar_t *text);

    bool set_prop(HWND hwnd, const char *text, HANDLE data_handle);

    bool set_prop(HWND hwnd, const wchar_t *text, HANDLE data_handle);

    HANDLE remove_prop(HWND hwnd, const char *text);

    HANDLE remove_prop(HWND hwnd, const wchar_t *text);

    bool register_shell_hook(HWND hwnd);

    bool unregister_shell_hook(HWND hwnd);

    HHOOK set_windows_hook(int32_t id_hook,
        HOOKPROC                   fn,
        HINSTANCE                  hmod,
        uint32_t                   tid);

    bool unset_windows_hook(HHOOK hhk);

    LRESULT
    call_next_hook(HHOOK hhk, int32_t code, WPARAM wparam, LPARAM lparam);

    HWINEVENTHOOK set_event_hook(uint32_t event_min,
        uint32_t                          event_max,
        HMODULE                           hmod_win_event_proc,
        WINEVENTPROC                      fn_win_event_proc,
        uint32_t                          pid,
        uint32_t                          tid,
        uint32_t                          flag);

    bool unset_event_hook(HWINEVENTHOOK hwin_event_hook);

    bool is_event_hook_installed(uint32_t event);

    void notify_event(uint32_t event,
        HWND                   hwnd,
        int32_t                object_id,
        int32_t                child_id);

    bool show(HWND hwnd, int32_t cmd_show) const;

    bool show_async(HWND hwnd, int32_t cmd_show) const;

    bool update(HWND hwnd) const;

    bool update_layered(HWND hwnd,
        HDC                  hdc_dst,
        POINT               *coordinate_dst,
        SIZE                *size,
        HDC                  hdc_src,
        POINT               *coordinate_src,
        COLORREF             color_ref,
        BLENDFUNCTION       *blend_fn,
        uint32_t             flag);

    bool lock_update(HWND hwnd);

    bool unlock_update();

    bool animate(HWND hwnd, uint32_t time, uint32_t flag);

    bool close(HWND hwnd);

    bool close(HWND hwnd, bool is_force);

    bool exit(uint32_t flag, uint32_t reason);

    bool destroy(HWND hwnd);

    bool enable(HWND hwnd, bool enable);

    bool enum_windows(WNDENUMPROC enum_func, LPARAM lparam);

    bool
    enum_child_windows(HWND hwnd_parent, WNDENUMPROC enum_func, LPARAM lparam);

    bool enum_windows(uint32_t tid, WNDENUMPROC fn, LPARAM lparam);

    HWND find(const char *class_name, const char *window_name);

    HWND find(const wchar_t *class_name, const wchar_t *window_name);

    HWND find(HWND  hwnd_parent,
        HWND        hwnd_child_after,
        const char *class_name,
        const char *window_name);

    HWND find(HWND     hwnd_parent,
        HWND           hwnd_child_after,
        const wchar_t *class_name,
        const wchar_t *window_name);

    bool flash(HWND hwnd, bool invert);

    bool flash(FLASHWINFO *flash_info);

    bool move(HWND hwnd,
        int32_t    x,
        int32_t    y,
        int32_t    width,
        int32_t    height,
        bool       is_repaint);

    bool print(HWND hwnd, HDC dc_handle, uint32_t flag);

    bool redraw(HWND hwnd, const RECT *rect, HRGN region_handle, uint32_t flag);

    bool maximize(HWND hwnd);

    bool minimize(HWND hwnd);

    bool hide(HWND hwnd);

    bool restore(HWND hwnd);

    bool restore_minimize(HWND hwnd);

    uint16_t tile(HWND           hwnd_parent,
        uint32_t                 how,
        const RECT              *rect,
        const std::vector<HWND> &child);

    HWND get_parent(HWND hwnd);

    HWND set_parent(HWND hwnd_child, HWND hwnd_new_parent);

    HWND get_ancestor(HWND hwnd, uint32_t flag);

    bool show_popup(HWND hwnd);

    bool hide_popup(HWND hwnd);

    HWND get_last_active_popup(HWND hwnd);

    bool is_pending(HWND hwnd);

    bool is_window(HWND hwnd);

    bool is_arranged(HWND hwnd);

    bool is_enabled(HWND hwnd);

    bool is_unicode(HWND hwnd);

    bool is_visible(HWND hwnd);

    bool is_minimize(HWND hwnd);

    bool is_maximize(HWND hwnd);

    bool is_child(HWND hwnd_parent, HWND hwnd);

    bool is_popup_exist();

    uint32_t arrange_minimize(HWND hwnd);

    bool get_proc_default_layout(uint32_t *default_layout);

    bool set_proc_default_layout(uint32_t default_layout);

    HDWP prepare(int32_t num_windows);

    HDWP add(HDWP hwin_pos_info,
        HWND      hwnd,
        HWND      hwnd_insert_after,
        int32_t   x,
        int32_t   y,
        int32_t   cx,
        int32_t   cy,
        uint32_t  flag);

    bool apply(HDWP hwin_pos_info);

    bool set_pos(HWND hwnd,
        HWND          hwnd_insert_after,
        int32_t       x,
        int32_t       y,
        int32_t       cx,
        int32_t       cy,
        uint32_t      flag);

    bool calc_popup_pos(const POINT *anchor_coordinate,
        const SIZE                  *window_size,
        uint32_t                     flag,
        RECT                        *exclude_rect,
        RECT                        *popup_window_position);

    HWND find_top_child(HWND hwnd_parent, POINT coordinate);

    HWND find_top_child(HWND hwnd_parent, POINT coordinate, uint32_t flag);

    HWND find_real_child(HWND hwnd_parent, POINT coordinate);

    HWND find_by_physical_point(POINT coordinate);

    HWND find_by_logical_point(POINT coordinate);

    int32_t transform_coordinate(HWND hwnd_from,
        HWND                          hwnd_to,
        std::vector<POINT>           &coordinates);

    bool adjust_to_top(HWND hwnd);

    LRESULT call_proc(WNDPROC prev_wnd_func,
        HWND                  hwnd,
        uint32_t              msg,
        WPARAM                wparam,
        LPARAM                lparam);

    LRESULT
    default_proc(HWND hwnd, uint32_t msg, WPARAM wparam, LPARAM lparam);

    LRESULT default_mdi_proc(HWND hwnd,
        HWND                      hwnd_mdi_client,
        uint32_t                  msg,
        WPARAM                    wparam,
        LPARAM                    lparam);

    LRESULT default_mdi_child_proc(HWND hwnd,
        uint32_t                        msg,
        WPARAM                          wparam,
        LPARAM                          lparam);

    uint16_t cascade(HWND  hwnd_parent,
        uint32_t           how,
        const RECT        *rect,
        std::vector<HWND> &child);

    void disable_proc_ghosting();

    HWND get_active();

    HWND set_active(HWND hwnd);

    uint32_t get_dpi(HWND hwnd);

    HWND get_foreground();

    bool set_foreground(HWND hwnd);

    bool allow_set_foreground(uint32_t pid);

    bool lock_set_foreground();

    bool unlock_set_foreground();

    bool get_layered_attrs(HWND hwnd,
        COLORREF               *color_ref,
        uint8_t                *alpha,
        uint32_t               *flag);

    bool set_layered_attrs(HWND hwnd,
        COLORREF                color_ref,
        uint8_t                 alpha,
        uint32_t                flag);

    HWND find(HWND hwnd, uint32_t cmd);

    HWND find_next(HWND hwnd, uint32_t cmd);

    HWND find_shell();

    HWND find_top(HWND hwnd);

    uint32_t get_context_help_id(HWND hwnd);

    bool set_context_help_id(HWND hwnd, uint32_t param);

    bool get_display_affinity(HWND hwnd, uint32_t *affinity);

    bool set_display_affinity(HWND hwnd, uint32_t affinity);

    DPI_AWARENESS_CONTEXT get_dpi_aware_context(HWND hwnd);

    DPI_HOSTING_BEHAVIOR get_dpi_hosting_behavior(HWND hwnd);

    bool get_feedback_setting(HWND hwnd,
        FEEDBACK_TYPE              feedback,
        uint32_t                   flag,
        int                       *real_config);

    bool set_feedback_setting(HWND hwnd,
        FEEDBACK_TYPE              feedback,
        uint32_t                   size,
        const int                 *config);

    bool get_info(HWND hwnd, WINDOWINFO *window_info);

    long get_long(HWND hwnd, int32_t index);

    long set_long(HWND hwnd, int32_t index, long value);

    LONG_PTR get_long_ptr(HWND hwnd, int32_t index);

    LONG_PTR set_long_ptr(HWND hwnd, int32_t index, LONG_PTR value);

    uint32_t get_module_file_name(HWND hwnd, std::string &file_name);

    uint32_t get_module_file_name(HWND hwnd, std::wstring &file_name);

    bool get_placement(HWND hwnd, WINDOWPLACEMENT *window_placement);

    bool set_placement(HWND hwnd, const WINDOWPLACEMENT *window_placement);

    bool get_rect(HWND hwnd, RECT *rect);

    bool adjust_rect(RECT *rect, uint32_t style, bool menu);

    bool adjust_rect(RECT *rect, uint32_t style, bool menu, uint32_t ext_style);

    bool adjust_rect_for_dpi(RECT *rect,
        uint32_t                   style,
        bool                       menu,
        uint32_t                   ext_style,
        uint32_t                   dpi);

    int32_t get_region(HWND hwnd, HRGN region_handle);

    int32_t set_region(HWND hwnd, HRGN region_handle, bool is_redraw);

    int32_t get_region_box(HWND hwnd, RECT *rect);

    int32_t get_text(HWND hwnd, std::string &text);

    int32_t get_text(HWND hwnd, std::wstring &text);

    bool set_text(HWND hwnd, const char *text);

    bool set_text(HWND hwnd, const wchar_t *text);

    int32_t get_text_length(HWND hwnd);

    uint32_t get_thread_id(HWND hwnd);

    uint32_t get_proc_id(HWND hwnd);

    // std::pair<tid, pid>
    std::pair<uint32_t, uint32_t> get_window_tid_and_pid(HWND hwnd);

    uint16_t get_word(HWND hwnd, int32_t index);

    int32_t get_direct_text(HWND hwnd, std::string &text);

    int32_t get_direct_text(HWND hwnd, std::wstring &text);

    uint32_t get_class(HWND hwnd, std::string &class_name);

    uint32_t get_class(HWND hwnd, std::wstring &class_name);

    void switch_window(HWND hwnd, bool unknown = false);

    bool show_help(HWND hwnd, const char *help, uint32_t cmd, ULONG_PTR data);

    bool
    show_help(HWND hwnd, const wchar_t *help, uint32_t cmd, ULONG_PTR data);

    uint32_t get_gui_resources(HANDLE proc_handle, uint32_t flag);

    bool get_gui_thread_info(uint32_t tid, GUITHREADINFO *gui_thread_info);

    bool is_gui_thread(bool is_convert);

    bool get_alt_tab_info(HWND hwnd,
        int32_t                item_index,
        ALTTABINFO            *alt_tab_info,
        std::string           &item_text);

    bool get_alt_tab_info(HWND hwnd,
        int32_t                item_index,
        ALTTABINFO            *alt_tab_info,
        std::wstring          &item_text);

    UINT_PTR set_timer(HWND hwnd,
        UINT_PTR            event_id,
        uint32_t            elapse,
        TIMERPROC           timer_func);

    UINT_PTR set_coalescable_timer(HWND hwnd,
        UINT_PTR                        event_id,
        uint32_t                        elapse,
        TIMERPROC                       timer_func,
        uint32_t                        tolerance_delay);

    bool kill_timer(HWND hwnd, UINT_PTR event_id);

    bool create_shutdown_reason(HWND hwnd, std::string &reason);

    bool create_shutdown_reason(HWND hwnd, const std::wstring &reason);

    bool destroy_shutdown_reason(HWND hwnd);

    bool
    query_shutdown_reason(HWND hwnd, std::string &reason, uint32_t *real_size);

    bool
    query_shutdown_reason(HWND hwnd, std::wstring &reason, uint32_t *real_size);

    int get_system_metrics(int flag);

    bool system_params_info(uint32_t ui_action,
        uint32_t                     ui_param,
        void                        *param,
        uint32_t                     win_ini);

    bool system_paras_info_for_dpi(uint32_t ui_action,
        uint32_t                            ui_param,
        void                               *param,
        uint32_t                            win_ini,
        uint32_t                            dpi);

    bool get_user_object_security(HANDLE obj_handle,
        PSECURITY_INFORMATION            si,
        PSECURITY_DESCRIPTOR             sd,
        uint32_t                         size,
        uint32_t                        *real_size);

    bool set_user_object_security(HANDLE obj_handle,
        PSECURITY_INFORMATION            si,
        PSECURITY_DESCRIPTOR             sd);

    uint32_t wait_for_multiple_objects(std::vector<HANDLE> &handles,
        bool                                                wait_all,
        uint32_t                                            milli_seconds,
        uint32_t                                            wake_mask);

    uint32_t wait_for_multiple_objects(std::vector<HANDLE> &handles,
        uint32_t                                            milli_seconds,
        uint32_t                                            wake_mask,
        uint32_t                                            flag);

    HDEVNOTIFY register_device_notify(HANDLE recipient_handle,
        void                                *notification_filter,
        uint32_t                             flag);

    bool unregister_device_notify(HDEVNOTIFY device_notify_handle);

    HPOWERNOTIFY register_power_setting_notify(HANDLE recipient_handle,
        const GUID                                   *power_setting_guid,
        uint32_t                                      flag);

    bool unregister_power_setting_notify(HPOWERNOTIFY power_notify_handle);

    HPOWERNOTIFY register_suspend_resume_notify(HANDLE recipient_handle,
        uint32_t                                       flag);

    bool unregister_suspend_resume_notify(HPOWERNOTIFY power_notify_handle);

    bool register_tooltip_dismiss_notify(HWND hwnd);

    bool unregister_tooltip_dismiss_notify(HWND hwnd);

    bool sound_sentry();

    bool grant_access(HANDLE user_handle, HANDLE job_handle, bool is_grant);

    bool set_additional_foreground_boost_procs(HWND top_level_window_handle,
        std::vector<HANDLE>                        &proc_handles);

    bool get_title_bar_info(HWND hwnd, TITLEBARINFO *title_bar_info);

    bool get_auto_rotation_state(AR_STATE *state);

    helper::CodePage get_code_page();

    bool get_combobox_info(HWND combo_hwnd, COMBOBOXINFO *combobox_info);

    uint32_t get_listbox_info(HWND hwnd);

    bool is_dpi_aware_contexts_equal(DPI_AWARENESS_CONTEXT context1,
        DPI_AWARENESS_CONTEXT                              context2);

    bool enable_non_client_dpi_scaling(HWND hwnd);

    bool is_proc_dpi_aware();

    bool is_valid_dpi_aware_context(DPI_AWARENESS_CONTEXT value);

    uint32_t get_dpi_for_system();

    uint32_t get_dpi_from_dpi_aware_context(DPI_AWARENESS_CONTEXT value);

    DPI_AWARENESS get_aware_from_dpi_aware_context(DPI_AWARENESS_CONTEXT value);

    DPI_AWARENESS_CONTEXT get_proc_dpi_aware_context(HANDLE proc_handle);

    bool set_proc_dpi_aware_context(DPI_AWARENESS_CONTEXT value);

    int32_t get_system_metrics_for_dpi(int32_t index, uint32_t dpi);

    uint32_t get_system_dpi(HANDLE proc_handle);

    HRESULT get_proc_dpi_aware(HANDLE proc_handle,
        PROCESS_DPI_AWARENESS        *value);

    HRESULT set_proc_dpi_aware(PROCESS_DPI_AWARENESS value);

    DPI_AWARENESS_CONTEXT get_thread_dpi_aware_context();

    DPI_AWARENESS_CONTEXT set_thread_dpi_aware_context(
        DPI_AWARENESS_CONTEXT dpi_context);

    DPI_HOSTING_BEHAVIOR get_thread_dpi_hosting_behavior();

    DPI_HOSTING_BEHAVIOR set_thread_dpi_hosting_behavior(
        DPI_HOSTING_BEHAVIOR value);

    int16_t get_app_command(LPARAM lparam);

    uint16_t get_device(LPARAM lparam);

    uint16_t get_flags(LPARAM lparam);

    int16_t get_nc_hit_test(WPARAM wparam);

    int16_t get_wheel_delta(WPARAM wparam);

    wchar_t *make_int_resource(uint16_t value);

    bool is_int_resource(uint16_t value);

    WPARAM make_wparam(long low, long high);

    LPARAM make_lparam(long low, long high);

    LRESULT make_lresult(long low, long high);

    uint16_t get_xbutton(WPARAM wparam);

    POINT points_to_point(POINTS points);

    POINTS point_to_points(POINT point);

    [[nodiscard]] uint32_t err_code() const;

    [[nodiscard]] std::string err_string() const;

    [[nodiscard]] std::wstring err_wstring() const;
};
} // namespace YanLib::ui
#endif // WINDOW_H
