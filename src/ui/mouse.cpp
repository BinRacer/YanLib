//
// Created by forkernel on 2025/5/1.
//

#include "mouse.h"
#include "helper/convert.h"

namespace YanLib::ui {
    bool mouse::enable_mouse_in_pointer(bool enable) {
        if (!EnableMouseInPointer(enable ? TRUE : FALSE)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool mouse::is_mouse_in_pointer_enabled() {
        return IsMouseInPointerEnabled();
    }

    bool mouse::drag_detect(HWND hwnd, POINT point) {
        return DragDetect(hwnd, point);
    }

    unsigned int mouse::get_double_click_time() {
        return GetDoubleClickTime();
    }

    bool mouse::set_double_click_time(unsigned int milli_seconds) {
        if (!SetDoubleClickTime(milli_seconds)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    HWND mouse::get_capture() {
        return GetCapture();
    }

    HWND mouse::set_capture(HWND hwnd) {
        return SetCapture(hwnd);
    }

    bool mouse::release_capture() {
        if (!ReleaseCapture()) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    unsigned int mouse::send_input(unsigned int inputs_count, INPUT *inputs, int cb_size) {
        unsigned int result = SendInput(inputs_count, inputs, cb_size);
        if (!result) {
            error_code = GetLastError();
        }
        return result;
    }

    void mouse::send_mouse_event(unsigned long flag,
                                 unsigned long x,
                                 unsigned long y,
                                 unsigned long data,
                                 ULONG_PTR extra_info) {
        mouse_event(flag, x, y, data, extra_info);
    }

    bool mouse::track_mouse_event(TRACKMOUSEEVENT *event_track) {
        if (!TrackMouseEvent(event_track)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool mouse::swap_mouse_button(bool is_swap) {
        return SwapMouseButton(is_swap ? TRUE : FALSE);
    }

    bool mouse::register_pointer_input_target(HWND hwnd,
                                              POINTER_INPUT_TYPE pointer_type) {
        if (!RegisterPointerInputTarget(hwnd, pointer_type)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool mouse::unregister_pointer_input_target(HWND hwnd,
                                                POINTER_INPUT_TYPE pointer_type) {
        if (!UnregisterPointerInputTarget(hwnd, pointer_type)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool mouse::get_last_input_info(LASTINPUTINFO *last_input_info) {
        return GetLastInputInfo(last_input_info);
    }

    bool mouse::get_pointer_input_transform(unsigned int pointer_id,
                                            unsigned int history_count,
                                            INPUT_TRANSFORM *input_transform) {
        if (!GetPointerInputTransform(pointer_id,
                                      history_count,
                                      input_transform)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool mouse::get_pointer_device(HANDLE device_handle,
                                   POINTER_DEVICE_INFO *pointer_device) {
        if (!GetPointerDevice(device_handle, pointer_device)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool mouse::get_pointer_device_properties(
        HANDLE device_handle,
        unsigned int *property_count,
        POINTER_DEVICE_PROPERTY *pointer_properties) {
        if (!GetPointerDeviceProperties(device_handle,
                                        property_count,
                                        pointer_properties)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool mouse::get_pointer_device_rects(HANDLE device_handle,
                                         RECT *pointer_device_rect,
                                         RECT *display_rect) {
        if (!GetPointerDeviceRects(device_handle,
                                   pointer_device_rect,
                                   display_rect)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool mouse::get_pointer_devices(unsigned int *device_count,
                                    POINTER_DEVICE_INFO *pointer_devices) {
        if (!GetPointerDevices(device_count, pointer_devices)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool mouse::get_pointer_frame_info(unsigned int pointer_id,
                                       unsigned int *pointer_count,
                                       POINTER_INFO *pointer_info) {
        if (!GetPointerFrameInfo(pointer_id,
                                 pointer_count,
                                 pointer_info)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool mouse::get_pointer_frame_info_history(unsigned int pointer_id,
                                               unsigned int *entries_count,
                                               unsigned int *pointer_count,
                                               POINTER_INFO *pointer_info) {
        if (!GetPointerFrameInfoHistory(pointer_id,
                                        entries_count,
                                        pointer_count,
                                        pointer_info)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool mouse::get_pointer_frame_pen_info(unsigned int pointer_id,
                                           unsigned int *pointer_count,
                                           POINTER_PEN_INFO *pen_info) {
        if (!GetPointerFramePenInfo(pointer_id,
                                    pointer_count,
                                    pen_info)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool mouse::get_pointer_frame_pen_info_history(unsigned int pointer_id,
                                                   unsigned int *entries_count,
                                                   unsigned int *pointer_count,
                                                   POINTER_PEN_INFO *pen_info) {
        if (!GetPointerFramePenInfoHistory(pointer_id,
                                           entries_count,
                                           pointer_count,
                                           pen_info)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool mouse::get_pointer_info(unsigned int pointer_id,
                                 POINTER_INFO *pointer_info) {
        if (!GetPointerInfo(pointer_id, pointer_info)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool mouse::get_pointer_info_history(unsigned int pointer_id,
                                         unsigned int *entries_count,
                                         POINTER_INFO *pointer_info) {
        if (!GetPointerInfoHistory(pointer_id,
                                   entries_count,
                                   pointer_info)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool mouse::get_pointer_pen_info(unsigned int pointer_id,
                                     POINTER_PEN_INFO *pen_info) {
        if (!GetPointerPenInfo(pointer_id, pen_info)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool mouse::get_pointer_pen_info_history(unsigned int pointer_id,
                                             unsigned int *entries_count,
                                             POINTER_PEN_INFO *pen_info) {
        if (!GetPointerPenInfoHistory(pointer_id,
                                      entries_count,
                                      pen_info)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool mouse::get_pointer_type(unsigned int pointer_id,
                                 POINTER_INPUT_TYPE *pointer_type) {
        if (!GetPointerType(pointer_id, pointer_type)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool mouse::get_raw_pointer_device_data(unsigned int pointer_id,
                                            unsigned int history_count,
                                            unsigned int properties_count,
                                            POINTER_DEVICE_PROPERTY *properties,
                                            long *values) {
        if (!GetRawPointerDeviceData(pointer_id,
                                     history_count,
                                     properties_count,
                                     properties,
                                     values)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    int mouse::get_mouse_move_points(unsigned int cb_size,
                                     MOUSEMOVEPOINT *mouse_move_point,
                                     MOUSEMOVEPOINT *points_buf,
                                     int points_count,
                                     unsigned long resolution) {
        int result = GetMouseMovePointsEx(cb_size,
                                          mouse_move_point,
                                          points_buf,
                                          points_count,
                                          resolution);
        if (result == -1) {
            error_code = GetLastError();
        }
        return result;
    }

    bool mouse::register_pointer_device_notifications(HWND hwnd, bool notify_range) {
        if (!RegisterPointerDeviceNotifications(hwnd, notify_range)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool mouse::is_pointer_flag_set_wparam(WPARAM w_param, unsigned long flag) {
        return IS_POINTER_FLAG_SET_WPARAM(w_param, flag);
    }

    bool mouse::is_pointer_in_contact_wparam(WPARAM w_param) {
        return IS_POINTER_INCONTACT_WPARAM(w_param);
    }

    bool mouse::is_pointer_in_range_wparam(WPARAM w_param) {
        return IS_POINTER_INRANGE_WPARAM(w_param);
    }

    bool mouse::is_pointer_new_wparam(WPARAM w_param) {
        return IS_POINTER_NEW_WPARAM(w_param);
    }

    bool mouse::is_pointer_primary_wparam(WPARAM w_param) {
        return IS_POINTER_PRIMARY_WPARAM(w_param);
    }

    bool mouse::has_pointer_confidence_wparam(WPARAM w_param) {
        return HAS_POINTER_CONFIDENCE_WPARAM(w_param);
    }

    bool mouse::is_pointer_canceled_wparam(WPARAM w_param) {
        return IS_POINTER_CANCELED_WPARAM(w_param);
    }

    bool mouse::is_pointer_first_button_wparam(WPARAM w_param) {
        return IS_POINTER_FIRSTBUTTON_WPARAM(w_param);
    }

    bool mouse::is_pointer_second_button_wparam(WPARAM w_param) {
        return IS_POINTER_SECONDBUTTON_WPARAM(w_param);
    }

    bool mouse::is_pointer_third_button_wparam(WPARAM w_param) {
        return IS_POINTER_THIRDBUTTON_WPARAM(w_param);
    }

    bool mouse::is_pointer_fourth_button_wparam(WPARAM w_param) {
        return IS_POINTER_FOURTHBUTTON_WPARAM(w_param);
    }

    bool mouse::is_pointer_fifth_button_wparam(WPARAM w_param) {
        return IS_POINTER_FIFTHBUTTON_WPARAM(w_param);
    }

    unsigned long mouse::err_code() const {
        return error_code;
    }

    std::string mouse::err_string() const {
        std::string result = helper::convert::err_string(error_code);
        return result;
    }

    std::wstring mouse::err_wstring() const {
        std::wstring result = helper::convert::err_wstring(error_code);
        return result;
    }
}
