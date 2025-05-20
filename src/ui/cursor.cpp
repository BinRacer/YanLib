//
// Created by forkernel on 2025/4/30.
//

#include "cursor.h"
#include "helper/convert.h"

namespace YanLib::ui {
    cursor::~cursor() {
        for (auto &cursor : cursor_handles) {
            if (cursor) {
                DestroyCursor(cursor);
                cursor = nullptr;
            }
        }
        cursor_handles.clear();
    }

    HCURSOR cursor::create(HINSTANCE instance_handle,
                           int32_t x_hotspot,
                           int32_t y_hotspot,
                           int32_t width,
                           int32_t height,
                           const void *and_plane,
                           const void *xor_plane) {
        HCURSOR result = CreateCursor(instance_handle, x_hotspot, y_hotspot,
                                      width, height, and_plane, xor_plane);
        if (!result) {
            error_code = GetLastError();
            return nullptr;
        }
        rwlock.write_lock();
        cursor_handles.push_back(result);
        rwlock.write_unlock();
        return result;
    }

    HCURSOR cursor::load(HINSTANCE instance_handle, const char *cursor_name) {
        HCURSOR result = LoadCursorA(instance_handle, cursor_name);
        if (!result) {
            error_code = GetLastError();
        }
        return result;
    }

    HCURSOR cursor::load(HINSTANCE instance_handle,
                         const wchar_t *cursor_name) {
        HCURSOR result = LoadCursorW(instance_handle, cursor_name);
        if (!result) {
            error_code = GetLastError();
        }
        return result;
    }

    HCURSOR cursor::load(const char *file_name) {
        HCURSOR result = LoadCursorFromFileA(file_name);
        if (!result) {
            error_code = GetLastError();
        }
        return result;
    }

    HCURSOR cursor::load(const wchar_t *file_name) {
        HCURSOR result = LoadCursorFromFileW(file_name);
        if (!result) {
            error_code = GetLastError();
        }
        return result;
    }

    bool cursor::clip(const RECT *rect) {
        if (!ClipCursor(rect)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    HCURSOR cursor::copy(HCURSOR cursor_handle) {
        auto result = CopyCursor(cursor_handle);
        if (!result) {
            error_code = GetLastError();
            return nullptr;
        }
        rwlock.write_lock();
        cursor_handles.push_back(result);
        rwlock.write_unlock();
        return result;
    }

    HCURSOR cursor::get_cursor() {
        return GetCursor();
    }

    HCURSOR cursor::set_cursor(HCURSOR cursor_handle) {
        return SetCursor(cursor_handle);
    }

    bool cursor::get_info(CURSORINFO *cursor_info) {
        if (!GetCursorInfo(cursor_info)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool cursor::get_pos(POINT *point) {
        if (!GetCursorPos(point)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool cursor::set_pos(int32_t x, int32_t y) {
        if (!SetCursorPos(x, y)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool cursor::get_clip(RECT *rect) {
        if (!GetClipCursor(rect)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool cursor::get_physical_pos(POINT *point) {
        if (!GetPhysicalCursorPos(point)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool cursor::set_physical_pos(int32_t x, int32_t y) {
        if (!SetPhysicalCursorPos(x, y)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool cursor::get_pointer_id(uint32_t pointer_id, uint32_t *cursor_id) {
        if (!GetPointerCursorId(pointer_id, cursor_id)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool cursor::get_pointer_device(HANDLE device_handle,
                                    uint32_t *cursor_count,
                                    POINTER_DEVICE_CURSOR_INFO cursor[]) {
        if (!GetPointerDeviceCursors(device_handle, cursor_count, cursor)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool cursor::set_system_cursor(HCURSOR cursor_handle, uint32_t id) {
        if (!SetSystemCursor(cursor_handle, id)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    uint32_t cursor::set_thread_scaling(uint32_t cursor_dpi) {
        return SetThreadCursorCreationScaling(cursor_dpi);
    }

    int32_t cursor::show_cursor() {
        return ShowCursor(TRUE);
    }

    int32_t cursor::hide_cursor() {
        return ShowCursor(FALSE);
    }

    bool cursor::destroy(HCURSOR cursor_handle) {
        if (!cursor_handle) {
            return false;
        }
        rwlock.write_lock();
        const auto it = std::find(cursor_handles.begin(), cursor_handles.end(),
                                  cursor_handle);
        if (it != cursor_handles.end()) {
            *it = nullptr;
        }
        rwlock.write_unlock();
        if (!DestroyCursor(cursor_handle)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    uint32_t cursor::err_code() const {
        return error_code;
    }

    std::string cursor::err_string() const {
        std::string result = helper::convert::err_string(error_code);
        return result;
    }

    std::wstring cursor::err_wstring() const {
        std::wstring result = helper::convert::err_wstring(error_code);
        return result;
    }
} // namespace YanLib::ui
