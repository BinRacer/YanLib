//
// Created by forkernel on 2025/5/1.
//

#ifndef TOUCH_H
#define TOUCH_H
#include <Windows.h>
#include <string>

namespace YanLib::ui {
    class touch {
    private:
        DWORD error_code = 0;

    public:
        touch(const touch &other) = delete;

        touch(touch &&other) = delete;

        touch &operator=(const touch &other) = delete;

        touch &operator=(touch &&other) = delete;

        touch() = default;

        ~touch() = default;

        HSYNTHETICPOINTERDEVICE
        create_synthetic_pointer_device(POINTER_INPUT_TYPE pointer_type,
                                        ULONG max_count,
                                        POINTER_FEEDBACK_MODE mode);

        void destroy_synthetic_pointer_device(HSYNTHETICPOINTERDEVICE device_handle);

        bool close_touch_input_handle(HTOUCHINPUT touch_input_handle);

        bool get_touch_input_info(HTOUCHINPUT touch_input_handle,
                                  UINT inputs_count,
                                  PTOUCHINPUT inputs,
                                  int cb_size);

        bool get_pointer_frame_touch_info(UINT32 pointer_id,
                                          UINT32 *pointer_count,
                                          POINTER_TOUCH_INFO *touch_info);

        bool get_pointer_frame_touch_info_history(UINT32 pointer_id,
                                                  UINT32 *entries_count,
                                                  UINT32 *pointer_count,
                                                  POINTER_TOUCH_INFO *touch_info);

        bool get_pointer_touch_info(UINT32 pointer_id,
                                    POINTER_TOUCH_INFO *touch_info);

        bool get_pointer_touch_info_history(UINT32 pointer_id,
                                            UINT32 *entries_count,
                                            POINTER_TOUCH_INFO *touch_info);

        WORD get_pointer_id_wparam(WPARAM w_param);

        bool get_gesture_extra_args(HGESTUREINFO gesture_info_handle,
                                    UINT extra_args_size,
                                    uint8_t *extra_args_buf);

        bool get_gesture_info(HGESTUREINFO gesture_info_handle,
                              PGESTUREINFO gesture_info);

        bool close_gesture_info_handle(HGESTUREINFO gesture_info_handle);

        bool initialize_touch_injection(UINT32 max_count, DWORD mode);

        bool inject_synthetic_pointer_input(HSYNTHETICPOINTERDEVICE device_handle,
                                            const POINTER_TYPE_INFO *pointer_info,
                                            UINT32 count);

        bool inject_touch_input(UINT32 count, const POINTER_TOUCH_INFO *contacts);

        LRESULT pack_touch_hit_testing_proximity_evaluation(
            const TOUCH_HIT_TESTING_INPUT *hit_testing_input,
            const TOUCH_HIT_TESTING_PROXIMITY_EVALUATION *proximity_eval);

        bool evaluate_proximity_to_polygon(
            UINT32 num_vertices,
            const POINT *control_polygon,
            const TOUCH_HIT_TESTING_INPUT *hit_testing_input,
            TOUCH_HIT_TESTING_PROXIMITY_EVALUATION *proximity_eval);

        bool evaluate_proximity_to_rect(
            const RECT *control_bounding_box,
            const TOUCH_HIT_TESTING_INPUT *hit_testing_input,
            TOUCH_HIT_TESTING_PROXIMITY_EVALUATION *proximity_eval);

        LONG touch_coord_to_pixel(LONG coordinate);

        uint16_t gid_rotate_angle_to_argument(double param);

        double gid_rotate_angle_from_argument(uint16_t param);

        [[nodiscard]] DWORD err_code() const;

        [[nodiscard]] std::string err_string() const;

        [[nodiscard]] std::wstring err_wstring() const;
    };
}
#endif //TOUCH_H
