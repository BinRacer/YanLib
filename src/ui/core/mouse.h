/* clang-format off */
/*
 * @file mouse.h
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
#ifndef MOUSE_H
#define MOUSE_H
#include <Windows.h>
#include <string>
#include <vector>
#include "sync/rwlock.h"
namespace YanLib::ui::core {
#ifndef MOUSEEVENT
#define MOUSEEVENT

    enum class MouseEvent : uint32_t {
        Move = MOUSEEVENTF_MOVE,
        LeftDown = MOUSEEVENTF_LEFTDOWN,
        LeftUp = MOUSEEVENTF_LEFTUP,
        RightDown = MOUSEEVENTF_RIGHTDOWN,
        RightUp = MOUSEEVENTF_RIGHTUP,
        MiddleDown = MOUSEEVENTF_MIDDLEDOWN,
        MiddleUp = MOUSEEVENTF_MIDDLEUP,
        XDown = MOUSEEVENTF_XDOWN,
        XUp = MOUSEEVENTF_XUP,
        Wheel = MOUSEEVENTF_WHEEL,
        MoveNoCoalesce = MOUSEEVENTF_MOVE_NOCOALESCE,
        VirtualDesk = MOUSEEVENTF_VIRTUALDESK,
        Absolute = MOUSEEVENTF_ABSOLUTE,
    };

    inline MouseEvent operator|(MouseEvent a, MouseEvent b) {
        return static_cast<MouseEvent>(static_cast<uint32_t>(a) |
                                       static_cast<uint32_t>(b));
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
#ifndef POINTERFLAG
#define POINTERFLAG

    enum class PointerFlag : uint32_t {
        None = POINTER_FLAG_NONE,
        New = POINTER_FLAG_NEW,
        InRange = POINTER_FLAG_INRANGE,
        InContact = POINTER_FLAG_INCONTACT,
        FirstButton = POINTER_FLAG_FIRSTBUTTON,
        SecondButton = POINTER_FLAG_SECONDBUTTON,
        ThirdButton = POINTER_FLAG_THIRDBUTTON,
        FourthButton = POINTER_FLAG_FOURTHBUTTON,
        FifthButton = POINTER_FLAG_FIFTHBUTTON,
        Primary = POINTER_FLAG_PRIMARY,
        Confidence = POINTER_FLAG_CONFIDENCE,
        Canceled = POINTER_FLAG_CANCELED,
        Down = POINTER_FLAG_DOWN,
        Update = POINTER_FLAG_UPDATE,
        Up = POINTER_FLAG_UP,
        Wheel = POINTER_FLAG_WHEEL,
        HWheel = POINTER_FLAG_HWHEEL,
        CaptureChanged = POINTER_FLAG_CAPTURECHANGED,
        HasTransform = POINTER_FLAG_HASTRANSFORM,
    };

    inline PointerFlag operator|(PointerFlag a, PointerFlag b) {
        return static_cast<PointerFlag>(static_cast<uint32_t>(a) |
                                        static_cast<uint32_t>(b));
    }
#endif

    class mouse {
    private:
        std::vector<std::pair<HWND, PointerInputType>> pointers = {};
        sync::rwlock rwlock = {};
        uint32_t error_code = 0;

    public:
        mouse(const mouse &other) = delete;

        mouse(mouse &&other) = delete;

        mouse &operator=(const mouse &other) = delete;

        mouse &operator=(mouse &&other) = delete;

        mouse() = default;

        ~mouse();

        bool enable_pointer();

        bool disable_pointer();

        bool is_pointer_enabled();

        bool drag_track(HWND window_handle, POINT point);

        uint32_t get_double_click_time();

        bool set_double_click_time(uint32_t milli_seconds);

        HWND get_capture();

        HWND set_capture(HWND window_handle);

        bool release_capture();

        uint32_t send_input(std::vector<INPUT> &input);

        void send_event(uint32_t x,
                        uint32_t y,
                        MouseEvent flag = MouseEvent::Move,
                        uint32_t data = 0,
                        uintptr_t extra_info = 0);

        bool track_event(TRACKMOUSEEVENT *event_track);

        bool swap_button(bool is_swap);

        bool register_pointer(HWND window_handle,
                              PointerInputType type = PointerInputType::Touch);

        bool
        unregister_pointer(HWND window_handle,
                           PointerInputType type = PointerInputType::Touch);

        bool get_last_input_info(LASTINPUTINFO *last_input_info);

        bool get_input_transform(uint32_t pointer_id,
                                 std::vector<INPUT_TRANSFORM> &input_transform);

        bool get_pointer_device(HANDLE device_handle,
                                POINTER_DEVICE_INFO *pointer_device);

        bool
        get_pointer_device_properties(HANDLE device_handle,
                                      uint32_t *real_num,
                                      POINTER_DEVICE_PROPERTY properties[]);

        bool get_pointer_device_rects(HANDLE device_handle,
                                      RECT *pointer_device_rect,
                                      RECT *display_rect);

        bool get_pointer_devices(uint32_t *real_num,
                                 POINTER_DEVICE_INFO pointer_devices[]);

        bool get_pointer_frame_info(uint32_t pointer_id,
                                    uint32_t *real_num,
                                    POINTER_INFO pointer_info[]);

        bool get_pointer_frame_info_history(uint32_t pointer_id,
                                            uint32_t *row,
                                            uint32_t *col,
                                            POINTER_INFO pointer_info[]);

        bool get_pen_frame_info(uint32_t pointer_id,
                                uint32_t *real_num,
                                POINTER_PEN_INFO pen_info[]);

        bool get_pen_frame_info_history(uint32_t pointer_id,
                                        uint32_t *row,
                                        uint32_t *col,
                                        POINTER_PEN_INFO pen_info[]);

        bool get_pointer_info(uint32_t pointer_id, POINTER_INFO *pointer_info);

        bool get_pointer_info_history(uint32_t pointer_id,
                                      uint32_t *real_num,
                                      POINTER_INFO pointer_info[]);

        bool get_pen_info(uint32_t pointer_id, POINTER_PEN_INFO *pen_info);

        bool get_pen_info_history(uint32_t pointer_id,
                                  uint32_t *real_num,
                                  POINTER_PEN_INFO pen_info[]);

        bool get_pointer_type(uint32_t pointer_id, PointerInputType *type);

        bool get_raw_pointer_device_data(
                uint32_t pointer_id,
                uint32_t history_count,
                std::vector<POINTER_DEVICE_PROPERTY> &properties,
                int32_t *value);

        int32_t get_move_points(uint32_t cb_size,
                                MOUSEMOVEPOINT *mouse_move_point,
                                std::vector<MOUSEMOVEPOINT> &point,
                                uint32_t resolution);

        bool register_pointer_device_notify(HWND window_handle,
                                            bool notify_range);

        bool is_pointer_flag_set(WPARAM wparam, PointerFlag flag);

        bool is_pointer_in_contact_set(WPARAM wparam);

        bool is_pointer_in_range_set(WPARAM wparam);

        bool is_pointer_new_set(WPARAM wparam);

        bool is_pointer_primary_set(WPARAM wparam);

        bool is_pointer_confidence_set(WPARAM wparam);

        bool is_pointer_canceled_set(WPARAM wparam);

        bool is_pointer_first_button_set(WPARAM wparam);

        bool is_pointer_second_button_set(WPARAM wparam);

        bool is_pointer_third_button_set(WPARAM wparam);

        bool is_pointer_fourth_button_set(WPARAM wparam);

        bool is_pointer_fifth_button_set(WPARAM wparam);

        [[nodiscard]] uint32_t err_code() const;

        [[nodiscard]] std::string err_string() const;

        [[nodiscard]] std::wstring err_wstring() const;
    };
} // namespace YanLib::ui::core
#endif // MOUSE_H
