/* clang-format off */
/*
 * @file touch.h
 * @date 2025-05-01
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
#ifndef TOUCH_H
#define TOUCH_H
#include <Windows.h>
#include <string>
#include <vector>
#include "sync/rwlock.h"
namespace YanLib::ui::core {
#ifndef REGISTERFLAG
#define REGISTERFLAG
    enum class RegisterFlag : uint32_t {
        Default = 0,
        FineTouch = TWF_FINETOUCH,
        WantPalm = TWF_WANTPALM,
    };
    inline RegisterFlag operator|(RegisterFlag f1, RegisterFlag f2) {
        return static_cast<RegisterFlag>(static_cast<uint32_t>(f1) |
                                         static_cast<uint32_t>(f2));
    }
#endif
#ifndef POINTERTYPE
#define POINTERTYPE

    enum class PointerInputType : uint32_t {
        Pointer = PT_POINTER,
        Touch = PT_TOUCH,
        Pen = PT_PEN,
        Mouse = PT_MOUSE,
        TouchPad = PT_TOUCHPAD,
    };
#endif
#ifndef POINTERFEEDBACK
#define POINTERFEEDBACK
    enum class PointerFeedback {
        Default = POINTER_FEEDBACK_DEFAULT,
        Indirect = POINTER_FEEDBACK_INDIRECT,
        None = POINTER_FEEDBACK_NONE,
    };
    inline PointerFeedback operator|(PointerFeedback f1, PointerFeedback f2) {
        return static_cast<PointerFeedback>(static_cast<uint32_t>(f1) |
                                            static_cast<uint32_t>(f2));
    }
#endif
#ifndef TOUCHHITTESTING
#define TOUCHHITTESTING
    enum class TouchHitTesting : uint32_t {
        Default = TOUCH_HIT_TESTING_DEFAULT,
        Client = TOUCH_HIT_TESTING_CLIENT,
        None = TOUCH_HIT_TESTING_NONE,
    };
#endif
    class touch {
    private:
        std::vector<HSYNTHETICPOINTERDEVICE> device_handles = {};
        std::vector<HWND> touch_handles = {};
        sync::rwlock device_rwlock = {};
        sync::rwlock touch_rwlock = {};
        uint32_t error_code = 0;

    public:
        touch(const touch &other) = delete;

        touch(touch &&other) = delete;

        touch &operator=(const touch &other) = delete;

        touch &operator=(touch &&other) = delete;

        touch() = default;

        ~touch();

        HSYNTHETICPOINTERDEVICE
        create_synthetic_pointer_device(
                PointerInputType pointer_type = PointerInputType::Pen,
                uint32_t max_count = 1,
                PointerFeedback mode = PointerFeedback::Indirect);

        void
        destroy_synthetic_pointer_device(HSYNTHETICPOINTERDEVICE device_handle);

        bool inject_synthetic_pointer_input(
                HSYNTHETICPOINTERDEVICE device_handle,
                const std::vector<POINTER_TYPE_INFO> &pointer_info);

        bool
        register_hit_testing(HWND window_handle,
                             TouchHitTesting flag = TouchHitTesting::Client);

        bool register_window(HWND window_handle,
                             RegisterFlag flag = RegisterFlag::WantPalm);

        bool unregister_window(HWND window_handle);

        bool what_flag(HWND window_handle, RegisterFlag *flag);

        bool close_input_handle(HTOUCHINPUT touch_input_handle);

        bool get_input_info(HTOUCHINPUT touch_input_handle,
                            std::vector<TOUCHINPUT> &input);

        bool get_pointer_frame_info(uint32_t pointer_id,
                                    uint32_t *real_num,
                                    POINTER_TOUCH_INFO touch_info[]);

        bool get_pointer_frame_info_history(uint32_t pointer_id,
                                            uint32_t *row,
                                            uint32_t *col,
                                            POINTER_TOUCH_INFO touch_info[]);

        bool get_pointer_info(uint32_t pointer_id,
                              POINTER_TOUCH_INFO *touch_info);

        bool get_pointer_info_history(uint32_t pointer_id,
                                      uint32_t *real_num,
                                      POINTER_TOUCH_INFO touch_info[]);

        uint16_t get_pointer_id(WPARAM wparam);

        bool init_injection(uint32_t max_count, PointerFeedback mode);

        bool inject_input(const std::vector<POINTER_TOUCH_INFO> &contacts);

        LRESULT pack_hit_testing_proximity_evaluation(
                const TOUCH_HIT_TESTING_INPUT *hit_testing_input,
                const TOUCH_HIT_TESTING_PROXIMITY_EVALUATION *proximity_eval);

        bool evaluate_proximity_to_polygon(
                const std::vector<POINT> &control_polygon,
                const TOUCH_HIT_TESTING_INPUT *hit_testing_input,
                TOUCH_HIT_TESTING_PROXIMITY_EVALUATION *proximity_eval);

        bool evaluate_proximity_to_rect(
                const RECT *control_bounding_box,
                const TOUCH_HIT_TESTING_INPUT *hit_testing_input,
                TOUCH_HIT_TESTING_PROXIMITY_EVALUATION *proximity_eval);

        int32_t coord_to_pixel(int32_t coordinate);

        uint16_t gid_rotate_angle_to_argument(double param);

        double gid_rotate_angle_from_argument(uint16_t param);

        bool get_gesture_extra_args(HGESTUREINFO gesture_info_handle,
                                    uint8_t *buf,
                                    uint32_t size);

        bool get_gesture_info(HGESTUREINFO gesture_info_handle,
                              GESTUREINFO *gesture_info);

        bool close_gesture_info_handle(HGESTUREINFO gesture_info_handle);

        [[nodiscard]] uint32_t err_code() const;

        [[nodiscard]] std::string err_string() const;

        [[nodiscard]] std::wstring err_wstring() const;
    };
} // namespace YanLib::ui::core
#endif // TOUCH_H
