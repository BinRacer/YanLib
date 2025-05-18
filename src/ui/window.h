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
        void               *param                = nullptr,
        HWND                parent_window_handle = nullptr,
        HMENU               menu_handle          = nullptr,
        int32_t             x                    = CW_USEDEFAULT,
        int32_t             y                    = CW_USEDEFAULT,
        int32_t             width                = CW_USEDEFAULT,
        int32_t             height               = CW_USEDEFAULT,
        uint32_t            style                = WS_OVERLAPPEDWINDOW,
        uint32_t            ext_style            = 0);

    HWND create(const wchar_t *class_name,
        const wchar_t         *window_name,
        HINSTANCE              instance_handle,
        void                  *param                = nullptr,
        HWND                   parent_window_handle = nullptr,
        HMENU                  menu_handle          = nullptr,
        int32_t                x                    = CW_USEDEFAULT,
        int32_t                y                    = CW_USEDEFAULT,
        int32_t                width                = CW_USEDEFAULT,
        int32_t                height               = CW_USEDEFAULT,
        uint32_t               style                = WS_OVERLAPPEDWINDOW,
        uint32_t               ext_style            = 0);

    HWND create_mdi(const char *class_name,
        const char             *window_name,
        HINSTANCE               instance_handle,
        LPARAM                  lparam,
        HWND                    parent_window_handle,
        int32_t                 x      = CW_USEDEFAULT,
        int32_t                 y      = CW_USEDEFAULT,
        int32_t                 width  = CW_USEDEFAULT,
        int32_t                 height = CW_USEDEFAULT,
        uint32_t style = MDIS_ALLCHILDSTYLES | WS_OVERLAPPEDWINDOW);

    HWND create_mdi(const wchar_t *class_name,
        const wchar_t             *window_name,
        HINSTANCE                  instance_handle,
        LPARAM                     lparam,
        HWND                       parent_window_handle,
        int32_t                    x      = CW_USEDEFAULT,
        int32_t                    y      = CW_USEDEFAULT,
        int32_t                    width  = CW_USEDEFAULT,
        int32_t                    height = CW_USEDEFAULT,
        uint32_t style = MDIS_ALLCHILDSTYLES | WS_OVERLAPPEDWINDOW);

    int32_t enum_props(HWND window_handle, PROPENUMPROCA enum_func);

    int32_t enum_props(HWND window_handle, PROPENUMPROCW enum_func);

    int32_t
    enum_props(HWND window_handle, PROPENUMPROCEXA enum_func, LPARAM lparam);

    int32_t
    enum_props(HWND window_handle, PROPENUMPROCEXW enum_func, LPARAM lparam);

    HANDLE get_prop(HWND window_handle, const char *text);

    HANDLE get_prop(HWND window_handle, const wchar_t *text);

    bool set_prop(HWND window_handle, const char *text, HANDLE data_handle);

    bool set_prop(HWND window_handle, const wchar_t *text, HANDLE data_handle);

    HANDLE remove_prop(HWND window_handle, const char *text);

    HANDLE remove_prop(HWND window_handle, const wchar_t *text);

    bool register_shell_hook(HWND window_handle);

    bool unregister_shell_hook(HWND window_handle);

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
        HWND                   window_handle,
        int32_t                object_id,
        int32_t                child_id);

    bool show(HWND window_handle, int32_t cmd_show) const;

    bool show_async(HWND window_handle, int32_t cmd_show) const;

    bool update(HWND window_handle) const;

    bool update_layered(HWND window_handle,
        HDC                  hdc_dst,
        POINT               *coordinate_dst,
        SIZE                *size,
        HDC                  hdc_src,
        POINT               *coordinate_src,
        COLORREF             color_ref,
        BLENDFUNCTION       *blend_fn,
        uint32_t             flag);

    bool lock_update(HWND window_handle);

    bool unlock_update();

    bool animate(HWND window_handle, uint32_t time, uint32_t flag);

    bool close(HWND window_handle);

    bool close(HWND window_handle, bool is_force);

    bool exit(uint32_t flag, uint32_t reason);

    bool destroy(HWND window_handle);

    bool enable(HWND window_handle, bool enable);

    bool enum_windows(WNDENUMPROC enum_func, LPARAM lparam);

    bool enum_child_windows(HWND parent_window_handle,
        WNDENUMPROC              enum_func,
        LPARAM                   lparam);

    bool enum_windows(uint32_t tid, WNDENUMPROC fn, LPARAM lparam);

    HWND find(const char *class_name, const char *window_name);

    HWND find(const wchar_t *class_name, const wchar_t *window_name);

    HWND find(HWND  parent_window_handle,
        const char *class_name,
        const char *window_name);

    HWND find(HWND     parent_window_handle,
        const wchar_t *class_name,
        const wchar_t *window_name);

    bool flash(HWND window_handle, bool invert);

    bool flash(FLASHWINFO *flash_info);

    bool move(HWND window_handle,
        int32_t    x,
        int32_t    y,
        int32_t    width,
        int32_t    height,
        bool       is_repaint);

    bool print(HWND window_handle, HDC dc_handle, uint32_t flag);

    bool redraw(HWND window_handle,
        const RECT  *rect,
        HRGN         region_handle,
        uint32_t     flag);

    bool maximize(HWND window_handle);

    bool minimize(HWND window_handle);

    bool hide(HWND window_handle);

    bool restore(HWND window_handle);

    bool restore_minimize(HWND window_handle);

    uint16_t tile(HWND           parent_window_handle,
        uint32_t                 how,
        const RECT              *rect,
        const std::vector<HWND> &child);

    HWND get_parent(HWND window_handle);

    HWND set_parent(HWND windows_handle, HWND parent_window_handle);

    HWND get_ancestor(HWND window_handle, uint32_t flag);

    bool show_popup(HWND window_handle);

    bool hide_popup(HWND window_handle);

    HWND get_last_active_popup(HWND window_handle);

    bool is_pending(HWND window_handle);

    bool is_window(HWND window_handle);

    bool is_arranged(HWND window_handle);

    bool is_enabled(HWND window_handle);

    bool is_unicode(HWND window_handle);

    bool is_visible(HWND window_handle);

    bool is_minimize(HWND window_handle);

    bool is_maximize(HWND window_handle);

    bool is_child(HWND parent_window_handle, HWND window_handle);

    bool is_popup_exist();

    uint32_t arrange_minimize(HWND window_handle);

    bool get_proc_default_layout(uint32_t *default_layout);

    bool set_proc_default_layout(uint32_t default_layout);

    HDWP prepare(int32_t num_windows);

    HDWP add(HDWP hwin_pos_info,
        HWND      window_handle,
        HWND      insert_after_window_handle,
        int32_t   x,
        int32_t   y,
        int32_t   cx,
        int32_t   cy,
        uint32_t  flag);

    bool apply(HDWP hwin_pos_info);

    bool set_pos(HWND window_handle,
        HWND          insert_after_window_handle,
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

    HWND find_top_child(HWND parent_window_handle, POINT coordinate);

    HWND
    find_top_child(HWND parent_window_handle, POINT coordinate, uint32_t flag);

    HWND find_real_child(HWND parent_window_handle, POINT coordinate);

    HWND find_by_physical_point(POINT coordinate);

    HWND find_by_logical_point(POINT coordinate);

    int32_t transform_coordinate(HWND from_window_handle,
        HWND                          to_window_handle,
        std::vector<POINT>           &coordinates);

    bool adjust_to_top(HWND window_handle);

    LRESULT call_proc(WNDPROC prev_wnd_func,
        HWND                  window_handle,
        uint32_t              msg,
        WPARAM                wparam,
        LPARAM                lparam);

    LRESULT
    default_proc(HWND window_handle,
        uint32_t      msg,
        WPARAM        wparam,
        LPARAM        lparam);

    LRESULT default_mdi_proc(HWND window_handle,
        HWND                      client_mdi_window_handle,
        uint32_t                  msg,
        WPARAM                    wparam,
        LPARAM                    lparam);

    LRESULT default_mdi_child_proc(HWND window_handle,
        uint32_t                        msg,
        WPARAM                          wparam,
        LPARAM                          lparam);

    uint16_t cascade(HWND  parent_window_handle,
        uint32_t           how,
        const RECT        *rect,
        std::vector<HWND> &child);

    void disable_proc_ghosting();

    HWND get_active();

    HWND set_active(HWND window_handle);

    uint32_t get_dpi(HWND window_handle);

    HWND get_foreground();

    bool set_foreground(HWND window_handle);

    bool allow_set_foreground(uint32_t pid);

    bool lock_set_foreground();

    bool unlock_set_foreground();

    bool get_layered_attrs(HWND window_handle,
        COLORREF               *color_ref,
        uint8_t                *alpha,
        uint32_t               *flag);

    bool set_layered_attrs(HWND window_handle,
        COLORREF                color_ref,
        uint8_t                 alpha,
        uint32_t                flag);

    HWND find(HWND window_handle, uint32_t cmd);

    HWND find_next(HWND window_handle, uint32_t cmd);

    HWND find_shell();

    HWND find_top(HWND window_handle);

    uint32_t get_context_help_id(HWND window_handle);

    bool set_context_help_id(HWND window_handle, uint32_t param);

    bool get_display_affinity(HWND window_handle, uint32_t *affinity);

    bool set_display_affinity(HWND window_handle, uint32_t affinity);

    DPI_AWARENESS_CONTEXT get_dpi_aware_context(HWND window_handle);

    DPI_HOSTING_BEHAVIOR get_dpi_hosting_behavior(HWND window_handle);

    bool get_feedback_setting(HWND window_handle,
        FEEDBACK_TYPE              feedback,
        uint32_t                   flag,
        int                       *real_config);

    bool set_feedback_setting(HWND window_handle,
        FEEDBACK_TYPE              feedback,
        uint32_t                   size,
        const int                 *config);

    bool get_info(HWND window_handle, WINDOWINFO *window_info);

    long get_long(HWND window_handle, int32_t index);

    long set_long(HWND window_handle, int32_t index, long value);

    LONG_PTR get_long_ptr(HWND window_handle, int32_t index);

    LONG_PTR set_long_ptr(HWND window_handle, int32_t index, LONG_PTR value);

    uint32_t get_module_file_name(HWND window_handle, std::string &file_name);

    uint32_t get_module_file_name(HWND window_handle, std::wstring &file_name);

    bool get_placement(HWND window_handle, WINDOWPLACEMENT *window_placement);

    bool set_placement(HWND    window_handle,
        const WINDOWPLACEMENT *window_placement);

    bool get_rect(HWND window_handle, RECT *rect);

    bool adjust_rect(RECT *rect, uint32_t style, bool menu);

    bool adjust_rect(RECT *rect, uint32_t style, bool menu, uint32_t ext_style);

    bool adjust_rect_for_dpi(RECT *rect,
        uint32_t                   style,
        bool                       menu,
        uint32_t                   ext_style,
        uint32_t                   dpi);

    int32_t get_region(HWND window_handle, HRGN region_handle);

    int32_t set_region(HWND window_handle, HRGN region_handle, bool is_redraw);

    int32_t get_region_box(HWND window_handle, RECT *rect);

    int32_t get_text(HWND window_handle, std::string &text);

    int32_t get_text(HWND window_handle, std::wstring &text);

    bool set_text(HWND window_handle, const char *text);

    bool set_text(HWND window_handle, const wchar_t *text);

    int32_t get_text_length(HWND window_handle);

    uint32_t get_thread_id(HWND window_handle);

    uint32_t get_proc_id(HWND window_handle);

    // std::pair<tid, pid>
    std::pair<uint32_t, uint32_t> get_window_tid_and_pid(HWND window_handle);

    uint16_t get_word(HWND window_handle, int32_t index);

    int32_t get_direct_text(HWND window_handle, std::string &text);

    int32_t get_direct_text(HWND window_handle, std::wstring &text);

    uint32_t get_class(HWND window_handle, std::string &class_name);

    uint32_t get_class(HWND window_handle, std::wstring &class_name);

    void switch_window(HWND window_handle, bool unknown = false);

    bool show_help(HWND window_handle,
        const char     *help,
        uint32_t        cmd,
        ULONG_PTR       data);

    bool show_help(HWND window_handle,
        const wchar_t  *help,
        uint32_t        cmd,
        ULONG_PTR       data);

    uint32_t get_gui_resources(HANDLE proc_handle, uint32_t flag);

    bool get_gui_thread_info(uint32_t tid, GUITHREADINFO *gui_thread_info);

    bool is_gui_thread(bool is_convert);

    bool get_alt_tab_info(HWND window_handle,
        int32_t                item_index,
        ALTTABINFO            *alt_tab_info,
        std::string           &item_text);

    bool get_alt_tab_info(HWND window_handle,
        int32_t                item_index,
        ALTTABINFO            *alt_tab_info,
        std::wstring          &item_text);

    UINT_PTR set_timer(HWND window_handle,
        UINT_PTR            event_id,
        uint32_t            elapse,
        TIMERPROC           timer_func);

    UINT_PTR set_coalescable_timer(HWND window_handle,
        UINT_PTR                        event_id,
        uint32_t                        elapse,
        TIMERPROC                       timer_func,
        uint32_t                        tolerance_delay);

    bool kill_timer(HWND window_handle, UINT_PTR event_id);

    bool create_shutdown_reason(HWND window_handle, std::string &reason);

    bool create_shutdown_reason(HWND window_handle, const std::wstring &reason);

    bool destroy_shutdown_reason(HWND window_handle);

    bool query_shutdown_reason(HWND window_handle,
        std::string                &reason,
        uint32_t                   *real_size);

    bool query_shutdown_reason(HWND window_handle,
        std::wstring               &reason,
        uint32_t                   *real_size);

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

    bool register_tooltip_dismiss_notify(HWND window_handle);

    bool unregister_tooltip_dismiss_notify(HWND window_handle);

    bool sound_sentry();

    bool grant_access(HANDLE user_handle, HANDLE job_handle, bool is_grant);

    bool set_additional_foreground_boost_procs(HWND top_level_window_handle,
        std::vector<HANDLE>                        &proc_handles);

    bool get_title_bar_info(HWND window_handle, TITLEBARINFO *title_bar_info);

    bool get_auto_rotation_state(AR_STATE *state);

    helper::CodePage get_code_page();

    bool get_combobox_info(HWND combo_handle, COMBOBOXINFO *combobox_info);

    uint32_t get_listbox_info(HWND window_handle);

    bool is_dpi_aware_contexts_equal(DPI_AWARENESS_CONTEXT context1,
        DPI_AWARENESS_CONTEXT                              context2);

    bool enable_non_client_dpi_scaling(HWND window_handle);

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
