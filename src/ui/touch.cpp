//
// Created by forkernel on 2025/5/1.
//

#include "touch.h"
#include "helper/convert.h"

namespace YanLib::ui {
    HSYNTHETICPOINTERDEVICE
    touch::create_synthetic_pointer_device(PointerInputType pointer_type,
                                           uint32_t max_count,
                                           PointerFeedback mode) {
        HSYNTHETICPOINTERDEVICE result = CreateSyntheticPointerDevice(
                static_cast<POINTER_INPUT_TYPE>(pointer_type), max_count,
                static_cast<POINTER_FEEDBACK_MODE>(mode));
        if (!result) {
            error_code = GetLastError();
        }
        return result;
    }

    void touch::destroy_synthetic_pointer_device(
            HSYNTHETICPOINTERDEVICE device_handle) {
        DestroySyntheticPointerDevice(device_handle);
    }

    bool touch::inject_synthetic_pointer_input(
            HSYNTHETICPOINTERDEVICE device_handle,
            const std::vector<POINTER_TYPE_INFO> &pointer_info) {
        if (!InjectSyntheticPointerInput(device_handle, pointer_info.data(),
                                         pointer_info.size())) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }
    bool touch::register_hit_testing(HWND window_handle, TouchHitTesting flag) {
        if (!RegisterTouchHitTestingWindow(window_handle,
                                           static_cast<uint32_t>(flag))) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool touch::register_window(HWND window_handle, RegisterFlag flag) {
        if (!RegisterTouchWindow(window_handle, static_cast<uint32_t>(flag))) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool touch::unregister_window(HWND window_handle) {
        if (!UnregisterTouchWindow(window_handle)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool touch::what_flag(HWND window_handle, RegisterFlag* flag) {
        return IsTouchWindow(window_handle,
                             reinterpret_cast<unsigned long*>(flag));
    }

    bool touch::close_input_handle(HTOUCHINPUT touch_input_handle) {
        if (!CloseTouchInputHandle(touch_input_handle)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool touch::get_input_info(HTOUCHINPUT touch_input_handle,
                               std::vector<TOUCHINPUT> &input) {
        if (!GetTouchInputInfo(touch_input_handle, input.size(), input.data(),
                               sizeof(TOUCHINPUT))) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool touch::get_pointer_frame_info(uint32_t pointer_id,
                                       uint32_t* real_num,
                                       POINTER_TOUCH_INFO touch_info[]) {
        if (!GetPointerFrameTouchInfo(pointer_id, real_num, touch_info)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool
    touch::get_pointer_frame_info_history(uint32_t pointer_id,
                                          uint32_t* row,
                                          uint32_t* col,
                                          POINTER_TOUCH_INFO touch_info[]) {
        if (!GetPointerFrameTouchInfoHistory(pointer_id, row, col,
                                             touch_info)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool touch::get_pointer_info(uint32_t pointer_id,
                                 POINTER_TOUCH_INFO* touch_info) {
        if (!GetPointerTouchInfo(pointer_id, touch_info)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool touch::get_pointer_info_history(uint32_t pointer_id,
                                         uint32_t* real_num,
                                         POINTER_TOUCH_INFO touch_info[]) {
        if (!GetPointerTouchInfoHistory(pointer_id, real_num, touch_info)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    uint16_t touch::get_pointer_id(WPARAM wparam) {
        return GET_POINTERID_WPARAM(wparam);
    }

    bool touch::init_injection(uint32_t max_count, PointerFeedback mode) {
        if (!InitializeTouchInjection(max_count,
                                      static_cast<unsigned long>(mode))) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool touch::inject_input(const std::vector<POINTER_TOUCH_INFO> &contacts) {
        if (!InjectTouchInput(contacts.size(), contacts.data())) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    LRESULT touch::pack_hit_testing_proximity_evaluation(
            const TOUCH_HIT_TESTING_INPUT* hit_testing_input,
            const TOUCH_HIT_TESTING_PROXIMITY_EVALUATION* proximity_eval) {
        LRESULT result =
                PackTouchHitTestingProximityEvaluation(hit_testing_input,
                                                       proximity_eval);
        error_code = GetLastError();
        return result;
    }

    bool touch::evaluate_proximity_to_polygon(
            const std::vector<POINT> &control_polygon,
            const TOUCH_HIT_TESTING_INPUT* hit_testing_input,
            TOUCH_HIT_TESTING_PROXIMITY_EVALUATION* proximity_eval) {
        if (!EvaluateProximityToPolygon(control_polygon.size(),
                                        control_polygon.data(),
                                        hit_testing_input, proximity_eval)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool touch::evaluate_proximity_to_rect(
            const RECT* control_bounding_box,
            const TOUCH_HIT_TESTING_INPUT* hit_testing_input,
            TOUCH_HIT_TESTING_PROXIMITY_EVALUATION* proximity_eval) {
        if (!EvaluateProximityToRect(control_bounding_box, hit_testing_input,
                                     proximity_eval)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    int32_t touch::coord_to_pixel(int32_t coordinate) {
        return TOUCH_COORD_TO_PIXEL(coordinate);
    }

    uint16_t touch::gid_rotate_angle_to_argument(double param) {
        return GID_ROTATE_ANGLE_TO_ARGUMENT(param);
    }

    double touch::gid_rotate_angle_from_argument(uint16_t param) {
        return GID_ROTATE_ANGLE_FROM_ARGUMENT(param);
    }

    bool touch::get_gesture_extra_args(HGESTUREINFO gesture_info_handle,
                                       uint8_t* buf,
                                       uint32_t size) {
        if (!GetGestureExtraArgs(gesture_info_handle, size, buf)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool touch::get_gesture_info(HGESTUREINFO gesture_info_handle,
                                 GESTUREINFO* gesture_info) {
        if (!GetGestureInfo(gesture_info_handle, gesture_info)) {
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

    uint32_t touch::err_code() const {
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
} // namespace YanLib::ui
