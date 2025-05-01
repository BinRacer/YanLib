//
// Created by forkernel on 2025/5/1.
//

#ifndef MOUSE_H
#define MOUSE_H
#include <Windows.h>
#include <string>

namespace YanLib::ui {
    class mouse {
    private:
        DWORD error_code = 0;

    public:
        mouse(const mouse &other) = delete;

        mouse(mouse &&other) = delete;

        mouse &operator=(const mouse &other) = delete;

        mouse &operator=(mouse &&other) = delete;

        mouse() = default;

        ~mouse() = default;

        bool enable_mouse_in_pointer(bool enable);

        bool is_mouse_in_pointer_enabled();

        bool drag_detect(HWND hwnd, POINT point);

        UINT get_double_click_time();

        bool set_double_click_time(UINT milli_seconds);

        HWND get_capture();

        HWND set_capture(HWND hwnd);

        bool release_capture();

        UINT send_input(UINT inputs_count, LPINPUT inputs, int cb_size);

        void send_mouse_event(DWORD flag,
                              DWORD x,
                              DWORD y,
                              DWORD data,
                              ULONG_PTR extra_info);

        bool track_mouse_event(LPTRACKMOUSEEVENT event_track);

        bool swap_mouse_button(bool is_swap);

        bool register_pointer_input_target(HWND hwnd,
                                           POINTER_INPUT_TYPE pointer_type);

        bool unregister_pointer_input_target(HWND hwnd,
                                             POINTER_INPUT_TYPE pointer_type);

        bool get_last_input_info(PLASTINPUTINFO last_input_info);

        bool get_pointer_input_transform(UINT32 pointer_id,
                                         UINT32 history_count,
                                         INPUT_TRANSFORM *input_transform);

        bool get_pointer_device(HANDLE device_handle,
                                POINTER_DEVICE_INFO *pointer_device);

        bool get_pointer_device_properties(
            HANDLE device_handle,
            UINT32 *property_count,
            POINTER_DEVICE_PROPERTY *pointer_properties);

        bool get_pointer_device_rects(HANDLE device_handle,
                                      RECT *pointer_device_rect,
                                      RECT *display_rect);

        bool get_pointer_devices(UINT32 *device_count,
                                 POINTER_DEVICE_INFO *pointer_devices);

        bool get_pointer_frame_info(UINT32 pointer_id,
                                    UINT32 *pointer_count,
                                    POINTER_INFO *pointer_info);

        bool get_pointer_frame_info_history(UINT32 pointer_id,
                                            UINT32 *entries_count,
                                            UINT32 *pointer_count,
                                            POINTER_INFO *pointer_info);

        bool get_pointer_frame_pen_info(UINT32 pointer_id,
                                        UINT32 *pointer_count,
                                        POINTER_PEN_INFO *pen_info);

        bool get_pointer_frame_pen_info_history(UINT32 pointer_id,
                                                UINT32 *entries_count,
                                                UINT32 *pointer_count,
                                                POINTER_PEN_INFO *pen_info);

        bool get_pointer_info(UINT32 pointer_id, POINTER_INFO *pointer_info);

        bool get_pointer_info_history(UINT32 pointer_id,
                                      UINT32 *entries_count,
                                      POINTER_INFO *pointer_info);

        bool get_pointer_pen_info(UINT32 pointer_id,
                                  POINTER_PEN_INFO *pen_info);

        bool get_pointer_pen_info_history(UINT32 pointer_id,
                                          UINT32 *entries_count,
                                          POINTER_PEN_INFO *pen_info);

        bool get_pointer_type(UINT32 pointer_id,
                              POINTER_INPUT_TYPE *pointer_type);

        bool get_raw_pointer_device_data(UINT32 pointer_id,
                                         UINT32 history_count,
                                         UINT32 properties_count,
                                         POINTER_DEVICE_PROPERTY *properties,
                                         LONG *values);

        int get_mouse_move_points(UINT cb_size,
                                  LPMOUSEMOVEPOINT mouse_move_point,
                                  LPMOUSEMOVEPOINT points_buf,
                                  int points_count,
                                  DWORD resolution);

        bool register_pointer_device_notifications(HWND hwnd, bool notify_range);

        bool is_pointer_flag_set_wparam(WPARAM w_param, DWORD flag);

        bool is_pointer_in_contact_wparam(WPARAM w_param);

        bool is_pointer_in_range_wparam(WPARAM w_param);

        bool is_pointer_new_wparam(WPARAM w_param);

        bool is_pointer_primary_wparam(WPARAM w_param);

        bool has_pointer_confidence_wparam(WPARAM w_param);

        bool is_pointer_canceled_wparam(WPARAM w_param);

        bool is_pointer_first_button_wparam(WPARAM w_param);

        bool is_pointer_second_button_wparam(WPARAM w_param);

        bool is_pointer_third_button_wparam(WPARAM w_param);

        bool is_pointer_fourth_button_wparam(WPARAM w_param);

        bool is_pointer_fifth_button_wparam(WPARAM w_param);

        [[nodiscard]] DWORD err_code() const;

        [[nodiscard]] std::string err_string() const;

        [[nodiscard]] std::wstring err_wstring() const;
    };
}
#endif //MOUSE_H
