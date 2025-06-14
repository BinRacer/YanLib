/* clang-format off */
/*
 * @file mouse.cpp
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
#include "mouse.h"
#include "helper/convert.h"

namespace YanLib::ui::core {
    mouse::~mouse() {
        for (auto &[hwnd, type] : pointers) {
            if (static_cast<uint32_t>(type) != UINT32_MAX) {
                UnregisterPointerInputTarget(hwnd, static_cast<uint32_t>(type));
                hwnd = nullptr;
                type = static_cast<PointerInputType>(UINT32_MAX);
            }
        }
        pointers.clear();
    }
    bool mouse::enable_pointer() {
        if (!EnableMouseInPointer(TRUE)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool mouse::disable_pointer() {
        if (!EnableMouseInPointer(FALSE)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool mouse::is_pointer_enabled() {
        return IsMouseInPointerEnabled();
    }

    bool mouse::drag_track(HWND window_handle, POINT point) {
        return DragDetect(window_handle, point);
    }

    uint32_t mouse::get_double_click_time() {
        return GetDoubleClickTime();
    }

    bool mouse::set_double_click_time(uint32_t milli_seconds) {
        if (!SetDoubleClickTime(milli_seconds)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    HWND mouse::get_capture() {
        return GetCapture();
    }

    HWND mouse::set_capture(HWND window_handle) {
        return SetCapture(window_handle);
    }

    bool mouse::release_capture() {
        if (!ReleaseCapture()) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    uint32_t mouse::send_input(std::vector<INPUT> &input) {
        const uint32_t result =
                SendInput(input.size(), input.data(), sizeof(INPUT));
        if (!result) {
            error_code = GetLastError();
        }
        return result;
    }

    void mouse::send_event(uint32_t x,
                           uint32_t y,
                           MouseEvent flag,
                           uint32_t data,
                           uintptr_t extra_info) {
        mouse_event(static_cast<uint32_t>(flag), x, y, data, extra_info);
    }

    bool mouse::track_event(TRACKMOUSEEVENT *event_track) {
        if (!TrackMouseEvent(event_track)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool mouse::swap_button(bool is_swap) {
        return SwapMouseButton(is_swap ? TRUE : FALSE);
    }

    bool mouse::register_pointer(HWND window_handle, PointerInputType type) {
        if (!RegisterPointerInputTarget(window_handle,
                                        static_cast<POINTER_INPUT_TYPE>(
                                                type))) {
            error_code = GetLastError();
            return false;
        }
        rwlock.write_lock();
        pointers.emplace_back(window_handle, type);
        rwlock.write_unlock();
        return true;
    }

    bool mouse::unregister_pointer(HWND window_handle, PointerInputType type) {
        rwlock.write_lock();
        const auto it = std::find(pointers.begin(), pointers.end(),
                                  std::make_pair(window_handle, type));
        if (it != pointers.end()) {
            *it = std::make_pair(nullptr,
                                 static_cast<PointerInputType>(UINT32_MAX));
        }
        rwlock.write_unlock();
        if (!UnregisterPointerInputTarget(window_handle,
                                          static_cast<POINTER_INPUT_TYPE>(
                                                  type))) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool mouse::get_last_input_info(LASTINPUTINFO *last_input_info) {
        return GetLastInputInfo(last_input_info);
    }

    bool
    mouse::get_input_transform(uint32_t pointer_id,
                               std::vector<INPUT_TRANSFORM> &input_transform) {
        if (!GetPointerInputTransform(pointer_id, input_transform.size(),
                                      input_transform.data())) {
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

    bool
    mouse::get_pointer_device_properties(HANDLE device_handle,
                                         uint32_t *real_num,
                                         POINTER_DEVICE_PROPERTY properties[]) {
        if (!GetPointerDeviceProperties(device_handle, real_num, properties)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool mouse::get_pointer_device_rects(HANDLE device_handle,
                                         RECT *pointer_device_rect,
                                         RECT *display_rect) {
        if (!GetPointerDeviceRects(device_handle, pointer_device_rect,
                                   display_rect)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool mouse::get_pointer_devices(uint32_t *real_num,
                                    POINTER_DEVICE_INFO pointer_devices[]) {
        if (!GetPointerDevices(real_num, pointer_devices)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool mouse::get_pointer_frame_info(uint32_t pointer_id,
                                       uint32_t *real_num,
                                       POINTER_INFO pointer_info[]) {
        if (!GetPointerFrameInfo(pointer_id, real_num, pointer_info)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool mouse::get_pointer_frame_info_history(uint32_t pointer_id,
                                               uint32_t *row,
                                               uint32_t *col,
                                               POINTER_INFO pointer_info[]) {
        if (!GetPointerFrameInfoHistory(pointer_id, row, col, pointer_info)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool mouse::get_pen_frame_info(uint32_t pointer_id,
                                   uint32_t *real_num,
                                   POINTER_PEN_INFO pen_info[]) {
        if (!GetPointerFramePenInfo(pointer_id, real_num, pen_info)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool mouse::get_pen_frame_info_history(uint32_t pointer_id,
                                           uint32_t *row,
                                           uint32_t *col,
                                           POINTER_PEN_INFO pen_info[]) {
        if (!GetPointerFramePenInfoHistory(pointer_id, row, col, pen_info)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool mouse::get_pointer_info(uint32_t pointer_id,
                                 POINTER_INFO *pointer_info) {
        if (!GetPointerInfo(pointer_id, pointer_info)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool mouse::get_pointer_info_history(uint32_t pointer_id,
                                         uint32_t *real_num,
                                         POINTER_INFO pointer_info[]) {
        if (!GetPointerInfoHistory(pointer_id, real_num, pointer_info)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool mouse::get_pen_info(uint32_t pointer_id, POINTER_PEN_INFO *pen_info) {
        if (!GetPointerPenInfo(pointer_id, pen_info)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool mouse::get_pen_info_history(uint32_t pointer_id,
                                     uint32_t *real_num,
                                     POINTER_PEN_INFO pen_info[]) {
        if (!GetPointerPenInfoHistory(pointer_id, real_num, pen_info)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool mouse::get_pointer_type(uint32_t pointer_id, PointerInputType *type) {
        if (!type) {
            error_code = STATUS_ACCESS_VIOLATION;
            return false;
        }
        DWORD pointer_type = 0;
        if (!GetPointerType(pointer_id, &pointer_type)) {
            error_code = GetLastError();
            return false;
        }
        *type = static_cast<PointerInputType>(pointer_type);
        return true;
    }

    bool mouse::get_raw_pointer_device_data(
            uint32_t pointer_id,
            uint32_t history_count,
            std::vector<POINTER_DEVICE_PROPERTY> &properties,
            int32_t *value) {
        if (!value) {
            error_code = STATUS_ACCESS_VIOLATION;
            return false;
        }
        long temp = *value;
        if (!GetRawPointerDeviceData(pointer_id, history_count,
                                     properties.size(), properties.data(),
                                     &temp)) {
            error_code = GetLastError();
            *value = temp;
            return false;
        }
        *value = temp;
        return true;
    }

    int32_t mouse::get_move_points(uint32_t cb_size,
                                   MOUSEMOVEPOINT *mouse_move_point,
                                   std::vector<MOUSEMOVEPOINT> &point,
                                   uint32_t resolution) {
        const int32_t result =
                GetMouseMovePointsEx(cb_size, mouse_move_point, point.data(),
                                     static_cast<int32_t>(point.size()),
                                     resolution);
        if (result == -1) {
            error_code = GetLastError();
        }
        return result;
    }

    bool mouse::register_pointer_device_notify(HWND window_handle,
                                               bool notify_range) {
        if (!RegisterPointerDeviceNotifications(window_handle, notify_range)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool mouse::is_pointer_flag_set(WPARAM wparam, PointerFlag flag) {
        return IS_POINTER_FLAG_SET_WPARAM(wparam, static_cast<uint32_t>(flag));
    }

    bool mouse::is_pointer_in_contact_set(WPARAM wparam) {
        return IS_POINTER_INCONTACT_WPARAM(wparam);
    }

    bool mouse::is_pointer_in_range_set(WPARAM wparam) {
        return IS_POINTER_INRANGE_WPARAM(wparam);
    }

    bool mouse::is_pointer_new_set(WPARAM wparam) {
        return IS_POINTER_NEW_WPARAM(wparam);
    }

    bool mouse::is_pointer_primary_set(WPARAM wparam) {
        return IS_POINTER_PRIMARY_WPARAM(wparam);
    }

    bool mouse::is_pointer_confidence_set(WPARAM wparam) {
        return HAS_POINTER_CONFIDENCE_WPARAM(wparam);
    }

    bool mouse::is_pointer_canceled_set(WPARAM wparam) {
        return IS_POINTER_CANCELED_WPARAM(wparam);
    }

    bool mouse::is_pointer_first_button_set(WPARAM wparam) {
        return IS_POINTER_FIRSTBUTTON_WPARAM(wparam);
    }

    bool mouse::is_pointer_second_button_set(WPARAM wparam) {
        return IS_POINTER_SECONDBUTTON_WPARAM(wparam);
    }

    bool mouse::is_pointer_third_button_set(WPARAM wparam) {
        return IS_POINTER_THIRDBUTTON_WPARAM(wparam);
    }

    bool mouse::is_pointer_fourth_button_set(WPARAM wparam) {
        return IS_POINTER_FOURTHBUTTON_WPARAM(wparam);
    }

    bool mouse::is_pointer_fifth_button_set(WPARAM wparam) {
        return IS_POINTER_FIFTHBUTTON_WPARAM(wparam);
    }

    uint32_t mouse::err_code() const {
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
} // namespace YanLib::ui::core
