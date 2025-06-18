/* clang-format off */
/*
 * @file window.h
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
#ifndef WINDOW_H
#define WINDOW_H
#include <Windows.h>
#include <winnt.h>
#include <minwindef.h>
#include <wingdi.h>
#include <WinUser.h>
#include <windef.h>
#include <vector>
#include <string>
#include "sync/rwlock.h"
#include "helper/convert.h"
#include "core.h"
namespace YanLib::ui::core {
    class window {
    private:
        std::vector<HWND> window_handles = {};
        std::vector<HWND> shutdown_handles = {};
        sync::rwlock window_rwlock = {};
        sync::rwlock shutdown_rwlock = {};
        uint32_t error_code = 0;

    public:
        window(const window &other) = delete;

        window(window &&other) = delete;

        window &operator=(const window &other) = delete;

        window &operator=(window &&other) = delete;

        window() = default;

        ~window();

        HWND create(const char *class_name,
                    const char *window_name,
                    HINSTANCE instance_handle,
                    void *param = nullptr,
                    HWND parent_window_handle = nullptr,
                    HMENU menu_handle = nullptr,
                    int32_t x = CW_USEDEFAULT,
                    int32_t y = CW_USEDEFAULT,
                    int32_t width = CW_USEDEFAULT,
                    int32_t height = CW_USEDEFAULT,
                    WindowStyle style = WindowStyle::OverlappedWindow,
                    WindowExtendStyle extend_style = WindowExtendStyle::None);

        HWND create(const wchar_t *class_name,
                    const wchar_t *window_name,
                    HINSTANCE instance_handle,
                    void *param = nullptr,
                    HWND parent_window_handle = nullptr,
                    HMENU menu_handle = nullptr,
                    int32_t x = CW_USEDEFAULT,
                    int32_t y = CW_USEDEFAULT,
                    int32_t width = CW_USEDEFAULT,
                    int32_t height = CW_USEDEFAULT,
                    WindowStyle style = WindowStyle::OverlappedWindow,
                    WindowExtendStyle extend_style = WindowExtendStyle::None);

        HWND create_mdi(const char *class_name,
                        const char *window_name,
                        HINSTANCE instance_handle,
                        LPARAM lparam,
                        HWND parent_window_handle,
                        int32_t x = CW_USEDEFAULT,
                        int32_t y = CW_USEDEFAULT,
                        int32_t width = CW_USEDEFAULT,
                        int32_t height = CW_USEDEFAULT,
                        WindowStyle style = WindowStyle::OverlappedWindow);

        HWND create_mdi(const wchar_t *class_name,
                        const wchar_t *window_name,
                        HINSTANCE instance_handle,
                        LPARAM lparam,
                        HWND parent_window_handle,
                        int32_t x = CW_USEDEFAULT,
                        int32_t y = CW_USEDEFAULT,
                        int32_t width = CW_USEDEFAULT,
                        int32_t height = CW_USEDEFAULT,
                        WindowStyle style = WindowStyle::OverlappedWindow);

        bool show(HWND window_handle, ShowType cmd_show = ShowType::ShowNormal);

        bool show_async(HWND window_handle,
                        ShowType cmd_show = ShowType::ShowNormal);

        bool update(HWND window_handle);

        bool update_layered(HWND window_handle,
                            HDC hdc_dst,
                            POINT *coordinate_dst,
                            SIZE *size,
                            HDC hdc_src,
                            POINT *coordinate_src,
                            COLORREF color_ref,
                            BLENDFUNCTION *blend_fn,
                            UpdateLayeredFlag flag = UpdateLayeredFlag::Alpha);

        bool lock_update(HWND window_handle);

        bool unlock_update();

        bool animate(HWND window_handle,
                     uint32_t milli_second = 200,
                     AnimateFlag flag = AnimateFlag::Hide | AnimateFlag::Blend);

        bool close(HWND window_handle);
#ifdef WINNT
        bool close(HWND window_handle, bool is_force);
#endif
        bool exit(ExitCode exit_code = ExitCode::Shutdown |
                          ExitCode::HybridShutdown | ExitCode::PowerOff,
                  ReasonCode reason_code = ReasonCode::MajorApplication |
                          ReasonCode::MinorMaintenance | ReasonCode::Planned);

        bool shutdown(ReasonCode reason_code = ReasonCode::MajorApplication |
                              ReasonCode::MinorMaintenance |
                              ReasonCode::Planned);

        bool reboot(ReasonCode reason_code = ReasonCode::MajorApplication |
                            ReasonCode::MinorMaintenance | ReasonCode::Planned);

        bool logoff(ReasonCode reason_code = ReasonCode::MajorApplication |
                            ReasonCode::MinorMaintenance | ReasonCode::Planned);

        bool hibernate(bool wakeup_events_disabled = false);

        bool create_shutdown_reason(
                HWND window_handle,
                const std::string &reason,
                helper::CodePage code_page = helper::curr_code_page());

        bool create_shutdown_reason(HWND window_handle,
                                    const std::wstring &reason);

        bool destroy_shutdown_reason(HWND window_handle);

        bool query_shutdown_reason(
                HWND window_handle,
                const std::string &reason,
                uint32_t *real_size,
                helper::CodePage code_page = helper::curr_code_page());

        bool query_shutdown_reason(HWND window_handle,
                                   std::wstring &reason,
                                   uint32_t *real_size);

        bool destroy(HWND window_handle);

        bool enable_input(HWND window_handle);

        bool disable_input(HWND window_handle);

        bool enumerate(WNDENUMPROC enum_func, LPARAM lparam = 0);

        bool enumerate_child(HWND parent_window_handle,
                             WNDENUMPROC enum_func,
                             LPARAM lparam = 0);

        bool enumerate(uint32_t tid, WNDENUMPROC fn, LPARAM lparam = 0);

        HWND find(const char *class_name, const char *window_name);

        HWND find(const wchar_t *class_name, const wchar_t *window_name);

        HWND find(HWND parent_window_handle,
                  const char *class_name,
                  const char *window_name);

        HWND find(HWND parent_window_handle,
                  const wchar_t *class_name,
                  const wchar_t *window_name);

        bool flash(HWND window_handle, bool invert = true);

        bool flash(FLASHWINFO *flash_info);

        bool move(HWND window_handle,
                  int32_t x,
                  int32_t y,
                  int32_t width,
                  int32_t height,
                  bool repaint = true);

        bool print(HWND window_handle, HDC dc_handle, bool client_only = false);

        bool redraw(HWND window_handle,
                    HRGN region_handle,
                    const RECT *rect,
                    RedrawFlag flag = RedrawFlag::Invalidate |
                            RedrawFlag::Erase | RedrawFlag::UpdateNow |
                            RedrawFlag::AllChildren);

        bool maximize(HWND window_handle);

        bool minimize(HWND window_handle);

        bool hide(HWND window_handle);

        bool restore(HWND window_handle);

        bool restore_minimize(HWND window_handle);

        uint16_t tile(HWND parent_window_handle,
                      const RECT *rect,
                      const std::vector<HWND> &child,
                      TileStyle style = TileStyle::Vertical |
                              TileStyle::SkipDisabled);

        HWND get_parent(HWND window_handle);

        HWND set_parent(HWND windows_handle, HWND parent_window_handle);

        HWND get_ancestor(HWND window_handle,
                          SearchFlag flag = SearchFlag::Root);

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

        bool is_child(HWND window_handle, HWND child_window_handle);

        bool is_popup_exist();

        uint32_t arrange_minimize(HWND window_handle);

        bool get_proc_default_layout(Layout *layout);

        bool set_proc_default_layout(Layout layout);

        bool set_pos(HWND window_handle,
                     HWND insert_after_window_handle = nullptr,
                     int32_t x = CW_USEDEFAULT,
                     int32_t y = CW_USEDEFAULT,
                     int32_t width = CW_USEDEFAULT,
                     int32_t height = CW_USEDEFAULT,
                     PosFlag flag = PosFlag::NoZOrder | PosFlag::ShowWindow);

        bool calc_popup_pos(const POINT *anchor_coordinate,
                            const SIZE *window_size,
                            RECT *popup_pos,
                            RECT *exclude_rect = nullptr,
                            TrackPopup flag = TrackPopup::RightAlign |
                                    TrackPopup::BottomAlign |
                                    TrackPopup::ReturnCmd |
                                    TrackPopup::LeftButton);

        HWND find_top_child(HWND parent_window_handle, POINT coordinate);

        HWND find_top_child(HWND parent_window_handle,
                            POINT coordinate,
                            SearchFlag4 flag = SearchFlag4::All);

        HWND find_real_child(HWND parent_window_handle, POINT coordinate);

        HWND find_by_physical_point(POINT coordinate);

        HWND find_by_logical_point(POINT coordinate);

        int32_t transform_coordinate(HWND from_window_handle,
                                     HWND to_window_handle,
                                     std::vector<POINT> &coordinates);

        bool adjust_to_top(HWND window_handle);

        LRESULT call_proc(WNDPROC prev_wnd_func,
                          HWND window_handle,
                          uint32_t msg,
                          WPARAM wparam,
                          LPARAM lparam);

        LRESULT default_proc(HWND window_handle,
                             uint32_t msg,
                             WPARAM wparam,
                             LPARAM lparam);

        LRESULT default_mdi_proc(HWND window_handle,
                                 HWND client_mdi_window_handle,
                                 uint32_t msg,
                                 WPARAM wparam,
                                 LPARAM lparam);

        LRESULT default_mdi_child_proc(HWND window_handle,
                                       uint32_t msg,
                                       WPARAM wparam,
                                       LPARAM lparam);

        uint16_t cascade(HWND parent_window_handle,
                         uint32_t how,
                         const RECT *rect,
                         const std::vector<HWND> &child);

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
                               COLORREF *color_ref,
                               uint8_t *alpha,
                               LayeredFlag *flag);

        bool set_layered_attrs(HWND window_handle,
                               COLORREF color_ref,
                               uint8_t alpha,
                               LayeredFlag flag);

        HWND find(HWND window_handle, SearchFlag7 flag = SearchFlag7::Child);

        HWND find_next(HWND window_handle);

        HWND find_prev(HWND window_handle);

        HWND find_first(HWND window_handle);

        HWND find_last(HWND window_handle);

        HWND find_owner(HWND window_handle);

        HWND find_shell();

        HWND find_top(HWND window_handle);

        uint32_t get_context_help_id(HWND window_handle);

        bool set_context_help_id(HWND window_handle, uint32_t param);

        bool get_display_affinity(HWND window_handle, AffinityFlag *affinity);

        bool set_display_affinity(HWND window_handle, AffinityFlag affinity);

        bool get_feedback_setting(HWND window_handle,
                                  FeedbackType feedback,
                                  bool *config,
                                  bool include_ancestor = false);

        bool set_feedback_setting(HWND window_handle,
                                  FeedbackType feedback,
                                  const void *config,
                                  uint32_t size);

        bool get_info(HWND window_handle, WINDOWINFO *window_info);

        // can fill offset with WindowLongOffset enum
        int32_t get_long(HWND window_handle, int32_t offset);

        // can fill offset with WindowLongOffset enum
        int32_t set_long(HWND window_handle, int32_t offset, int32_t value);

        // can fill offset with WindowLongOffset enum
        intptr_t get_long_ptr(HWND window_handle, int32_t offset);

        // can fill offset with WindowLongOffset enum
        intptr_t
        set_long_ptr(HWND window_handle, int32_t offset, intptr_t value);

        // can fill offset with WindowWordOffset enum
        uint16_t get_word(HWND window_handle, int32_t offset);

        uint32_t get_module_file_name(HWND window_handle,
                                      std::string &file_name);

        uint32_t get_module_file_name(HWND window_handle,
                                      std::wstring &file_name);

        bool get_placement(HWND window_handle,
                           WINDOWPLACEMENT *window_placement);

        bool set_placement(HWND window_handle,
                           const WINDOWPLACEMENT *window_placement);

        bool get_rect(HWND window_handle, RECT *rect);

        bool calc_rect(RECT *rect, WindowStyle style, bool include_menu = true);

        bool calc_rect(RECT *rect,
                       WindowStyle style,
                       WindowExtendStyle extend_style = WindowExtendStyle::None,
                       bool include_menu = true);

        bool calc_rect_for_dpi(
                RECT *rect,
                uint32_t dpi,
                WindowStyle style,
                WindowExtendStyle extend_style = WindowExtendStyle::None,
                bool include_menu = true);

        int32_t get_region(HWND window_handle, HRGN region_handle);

        int32_t
        set_region(HWND window_handle, HRGN region_handle, bool redraw = true);

        int32_t get_region_box(HWND window_handle, RECT *rect);

        int32_t get_text(HWND window_handle, std::string &text);

        int32_t get_text(HWND window_handle, std::wstring &text);

        bool set_text(HWND window_handle, const std::string &text);

        bool set_text(HWND window_handle, const std::wstring &text);

        int32_t get_text_length(HWND window_handle);

        uint32_t get_thread_id(HWND window_handle);

        uint32_t get_proc_id(HWND window_handle);

        // std::pair<tid, pid>
        std::pair<uint32_t, uint32_t>
        get_window_tid_and_pid(HWND window_handle);

        int32_t
        get_direct_text(HWND window_handle,
                        std::string &text,
                        helper::CodePage code_page = helper::curr_code_page());

        int32_t get_direct_text(HWND window_handle, std::wstring &text);

        uint32_t get_class_name(HWND window_handle, std::string &class_name);

        uint32_t get_class_name(HWND window_handle, std::wstring &class_name);

        void switch_window(HWND window_handle, bool UseAccelerator = false);

        bool show_help(HWND window_handle,
                       const char *help,
                       uintptr_t data,
                       HelpCommand cmd);

        bool show_help(HWND window_handle,
                       const wchar_t *help,
                       uintptr_t data,
                       HelpCommand cmd);

        uint32_t get_gui_resources(HANDLE proc_handle, ResourceFlag flag);

        bool get_gui_thread_info(uint32_t tid, GUITHREADINFO *gui_thread_info);

        bool convert_to_gui_thread();

        bool is_gui_thread();

        bool get_alt_tab_info(HWND window_handle,
                              int32_t icon_index,
                              ALTTABINFO *alt_tab_info,
                              std::string &item_text);

        bool get_alt_tab_info(HWND window_handle,
                              int32_t icon_index,
                              ALTTABINFO *alt_tab_info,
                              std::wstring &item_text);

        uintptr_t set_timer(HWND window_handle,
                            uintptr_t event_id,
                            TIMERPROC timer_func,
                            uint32_t timeout_ms = 1000);

        uintptr_t set_mixed_timer(
                HWND window_handle,
                uintptr_t event_id,
                TIMERPROC timer_func,
                uint32_t timeout_ms = 1000,
                uint32_t tolerance_delay_ms = TIMERV_DEFAULT_COALESCING);

        bool kill_timer(HWND window_handle, uintptr_t event_id);

        int32_t get_system_metrics(MetricCode code);

        int32_t get_system_metrics_for_dpi(MetricCode code, uint32_t dpi);

        bool system_params_info(SystemParameter action,
                                uint32_t key,
                                void *value,
                                SystemParameterFlag flag);

        bool system_paras_info_for_dpi(SystemParameter action,
                                       uint32_t key,
                                       void *value,
                                       uint32_t dpi,
                                       SystemParameterFlag flag);

        bool get_user_object_security(HANDLE obj_handle,
                                      PSECURITY_INFORMATION si,
                                      PSECURITY_DESCRIPTOR sd,
                                      uint32_t size,
                                      uint32_t *real_size);

        bool set_user_object_security(HANDLE obj_handle,
                                      PSECURITY_INFORMATION si,
                                      PSECURITY_DESCRIPTOR sd);

        uint32_t wait_for_multiple_objects(const std::vector<HANDLE> &handles,
                                           QueueType type,
                                           uint32_t milli_seconds,
                                           bool wait_all);

        uint32_t wait_for_multiple_objects(const std::vector<HANDLE> &handles,
                                           QueueType type,
                                           uint32_t milli_seconds,
                                           WaitFlag flag);

        bool sound_sentry();

        bool grant_access(HANDLE user_handle,
                          HANDLE job_handle,
                          bool is_grant = true);

        bool set_additional_foreground_boost_procs(
                HWND top_level_window_handle,
                std::vector<HANDLE> &proc_handles);

        bool get_title_bar_info(HWND window_handle,
                                TITLEBARINFO *title_bar_info);

        bool get_auto_rotation_state(RotateState *state);

        helper::CodePage get_code_page();

        bool get_combo_box_info(HWND combo_handle,
                                COMBOBOXINFO *combo_box_info);

        uint32_t get_list_box_info(HWND window_handle);

        bool enable_non_client_dpi_scaling(HWND window_handle);

        uint32_t get_dpi_for_system();

        uint32_t get_system_dpi(HANDLE proc_handle);

        int16_t get_app_command(LPARAM lparam);

        uint16_t get_device(LPARAM lparam);

        uint16_t get_flags(LPARAM lparam);

        int16_t get_nc_hit_test(WPARAM wparam);

        int16_t get_wheel_delta(WPARAM wparam);

        wchar_t *make_int_resource(uint16_t value);

        bool is_int_resource(uint16_t value);

        WPARAM make_wparam(int32_t low, int32_t high);

        LPARAM make_lparam(int32_t low, int32_t high);

        LRESULT make_lresult(int32_t low, int32_t high);

        uint16_t get_xbutton(WPARAM wparam);

        POINT points_to_point(POINTS points);

        POINTS point_to_points(POINT point);

        [[nodiscard]] uint32_t err_code() const;

        [[nodiscard]] std::string err_string() const;

        [[nodiscard]] std::wstring err_wstring() const;
    };
} // namespace YanLib::ui::core
#endif // WINDOW_H
