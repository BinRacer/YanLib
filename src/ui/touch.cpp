//
// Created by forkernel on 2025/5/1.
//

#include "touch.h"
#include "helper/convert.h"

namespace YanLib::ui {
    bool touch::register_touch_hit_testing_window(HWND hwnd, ULONG value) {
        if (!RegisterTouchHitTestingWindow(hwnd, value)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool touch::register_touch_window(HWND hwnd, ULONG flag) {
        if (!RegisterTouchWindow(hwnd, flag)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool touch::unregister_touch_window(HWND hwnd) {
        if (!UnregisterTouchWindow(hwnd)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool touch::is_touch_window(HWND hwnd, PULONG flag) {
        return IsTouchWindow(hwnd, flag);
    }

    HSYNTHETICPOINTERDEVICE
    touch::create_synthetic_pointer_device(POINTER_INPUT_TYPE pointer_type,
                                           ULONG max_count,
                                           POINTER_FEEDBACK_MODE mode) {
        HSYNTHETICPOINTERDEVICE result =
                CreateSyntheticPointerDevice(pointer_type, max_count, mode);
        if (!result) {
            error_code = GetLastError();
        }
        return result;
    }

    void
    touch::destroy_synthetic_pointer_device(HSYNTHETICPOINTERDEVICE device_handle) {
        DestroySyntheticPointerDevice(device_handle);
    }

    bool touch::close_touch_input_handle(HTOUCHINPUT touch_input_handle) {
        if (!CloseTouchInputHandle(touch_input_handle)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool touch::get_touch_input_info(HTOUCHINPUT touch_input_handle,
                                     UINT inputs_count,
                                     PTOUCHINPUT inputs,
                                     int cb_size) {
        if (!GetTouchInputInfo(touch_input_handle,
                               inputs_count,
                               inputs,
                               cb_size)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool touch::get_pointer_frame_touch_info(UINT32 pointer_id,
                                             UINT32 *pointer_count,
                                             POINTER_TOUCH_INFO *touch_info) {
        if (!GetPointerFrameTouchInfo(pointer_id,
                                      pointer_count,
                                      touch_info)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool touch::get_pointer_frame_touch_info_history(UINT32 pointer_id,
                                                     UINT32 *entries_count,
                                                     UINT32 *pointer_count,
                                                     POINTER_TOUCH_INFO *touch_info) {
        if (!GetPointerFrameTouchInfoHistory(pointer_id,
                                             entries_count,
                                             pointer_count,
                                             touch_info)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool touch::get_pointer_touch_info(UINT32 pointer_id,
                                       POINTER_TOUCH_INFO *touch_info) {
        if (!GetPointerTouchInfo(pointer_id, touch_info)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool touch::get_pointer_touch_info_history(UINT32 pointer_id,
                                               UINT32 *entries_count,
                                               POINTER_TOUCH_INFO *touch_info) {
        if (!GetPointerTouchInfoHistory(pointer_id,
                                        entries_count,
                                        touch_info)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    WORD touch::get_pointer_id_wparam(WPARAM w_param) {
        return GET_POINTERID_WPARAM(w_param);
    }

    bool touch::get_gesture_extra_args(HGESTUREINFO gesture_info_handle,
                                       UINT extra_args_size,
                                       uint8_t *extra_args_buf) {
        if (!GetGestureExtraArgs(gesture_info_handle,
                                 extra_args_size,
                                 extra_args_buf)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool touch::get_gesture_info(HGESTUREINFO gesture_info_handle,
                                 PGESTUREINFO gesture_info) {
        if (!GetGestureInfo(gesture_info_handle,
                            gesture_info)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool touch::close_gesture_info_handle(HGESTUREINFO gesture_info_handle) {
        if (!CloseGestureInfoHandle(gesture_info_handle)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool touch::initialize_touch_injection(UINT32 max_count, DWORD mode) {
        if (!InitializeTouchInjection(max_count, mode)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool touch::inject_synthetic_pointer_input(HSYNTHETICPOINTERDEVICE device_handle,
                                               const POINTER_TYPE_INFO *pointer_info,
                                               UINT32 count) {
        if (!InjectSyntheticPointerInput(device_handle,
                                         pointer_info,
                                         count)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool touch::inject_touch_input(UINT32 count, const POINTER_TOUCH_INFO *contacts) {
        if (!InjectTouchInput(count, contacts)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    LRESULT touch::pack_touch_hit_testing_proximity_evaluation(
        const TOUCH_HIT_TESTING_INPUT *hit_testing_input,
        const TOUCH_HIT_TESTING_PROXIMITY_EVALUATION *proximity_eval) {
        LRESULT result =
                PackTouchHitTestingProximityEvaluation(hit_testing_input,
                                                       proximity_eval);
        error_code = GetLastError();
        return result;
    }

    bool touch::evaluate_proximity_to_polygon(
        UINT32 num_vertices,
        const POINT *control_polygon,
        const TOUCH_HIT_TESTING_INPUT *hit_testing_input,
        TOUCH_HIT_TESTING_PROXIMITY_EVALUATION *proximity_eval) {
        if (!EvaluateProximityToPolygon(num_vertices,
                                        control_polygon,
                                        hit_testing_input,
                                        proximity_eval)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool touch::evaluate_proximity_to_rect(
        const RECT *control_bounding_box,
        const TOUCH_HIT_TESTING_INPUT *hit_testing_input,
        TOUCH_HIT_TESTING_PROXIMITY_EVALUATION *proximity_eval) {
        if (!EvaluateProximityToRect(control_bounding_box,
                                     hit_testing_input,
                                     proximity_eval)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    LONG touch::touch_coord_to_pixel(LONG coordinate) {
        return TOUCH_COORD_TO_PIXEL(coordinate);
    }

    uint16_t touch::gid_rotate_angle_to_argument(double param) {
        return GID_ROTATE_ANGLE_TO_ARGUMENT(param);
    }

    double touch::gid_rotate_angle_from_argument(uint16_t param) {
        return GID_ROTATE_ANGLE_FROM_ARGUMENT(param);
    }

    DWORD touch::err_code() const {
        return error_code;
    }

    std::string touch::err_string() const {
        std::string result = helper::convert::err_string(error_code);
        return result;
    }

    std::wstring touch::err_wstring() const {
        std::wstring result = helper::convert::err_wstring(error_code);
        return result;
    }
}
