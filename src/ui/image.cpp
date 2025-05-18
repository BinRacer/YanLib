//
// Created by forkernel on 2025/4/30.
//

#include "image.h"
#include "helper/convert.h"

namespace YanLib::ui {
    image::~image() {
        for (auto &bitmap : bitmap_handles) {
            if (bitmap) {
                DeleteObject(bitmap);
                bitmap = nullptr;
            }
        }
        bitmap_handles.clear();
        for (auto &icon : icon_handles) {
            if (icon) {
                DestroyIcon(icon);
                icon = nullptr;
            }
        }
        icon_handles.clear();
        for (auto &cursor : cursor_handles) {
            if (cursor) {
                DestroyCursor(cursor);
                cursor = nullptr;
            }
        }
        cursor_handles.clear();
    }

    HBITMAP image::load_bitmap(HINSTANCE instance_handle,
                               const char* image_name,
                               int32_t cx,
                               int32_t cy,
                               ImageFlag flag) {
        auto bitmap = static_cast<HBITMAP>(
                LoadImageA(instance_handle, image_name, IMAGE_BITMAP, cx, cy,
                           static_cast<uint32_t>(flag)));
        if (!bitmap) {
            error_code = GetLastError();
            return nullptr;
        }
        if (static_cast<uint32_t>(flag) & LR_SHARED) {
            return bitmap;
        }
        bitmap_rwlock.write_lock();
        bitmap_handles.push_back(bitmap);
        bitmap_rwlock.write_unlock();
        return bitmap;
    }

    HBITMAP image::load_bitmap(HINSTANCE instance_handle,
                               const wchar_t* image_name,
                               int32_t cx,
                               int32_t cy,
                               ImageFlag flag) {
        auto bitmap = static_cast<HBITMAP>(
                LoadImageW(instance_handle, image_name, IMAGE_BITMAP, cx, cy,
                           static_cast<uint32_t>(flag)));
        if (!bitmap) {
            error_code = GetLastError();
            return nullptr;
        }
        if (static_cast<uint32_t>(flag) & LR_SHARED) {
            return bitmap;
        }
        bitmap_rwlock.write_lock();
        bitmap_handles.push_back(bitmap);
        bitmap_rwlock.write_unlock();
        return bitmap;
    }

    HICON image::load_icon(HINSTANCE instance_handle,
                           const char* image_name,
                           int32_t cx,
                           int32_t cy,
                           ImageFlag flag) {
        auto icon = static_cast<HICON>(LoadImageA(instance_handle, image_name,
                                                  IMAGE_ICON, cx, cy,
                                                  static_cast<uint32_t>(flag)));
        if (!icon) {
            error_code = GetLastError();
            return nullptr;
        }
        if (static_cast<uint32_t>(flag) & LR_SHARED) {
            return icon;
        }
        icon_rwlock.write_lock();
        icon_handles.push_back(icon);
        icon_rwlock.write_unlock();
        return icon;
    }

    HICON image::load_icon(HINSTANCE instance_handle,
                           const wchar_t* image_name,
                           int32_t cx,
                           int32_t cy,
                           ImageFlag flag) {
        auto icon = static_cast<HICON>(LoadImageW(instance_handle, image_name,
                                                  IMAGE_ICON, cx, cy,
                                                  static_cast<uint32_t>(flag)));
        if (!icon) {
            error_code = GetLastError();
            return nullptr;
        }
        if (static_cast<uint32_t>(flag) & LR_SHARED) {
            return icon;
        }
        icon_rwlock.write_lock();
        icon_handles.push_back(icon);
        icon_rwlock.write_unlock();
        return icon;
    }

    HCURSOR image::load_cursor(HINSTANCE instance_handle,
                               const char* image_name,
                               int32_t cx,
                               int32_t cy,
                               ImageFlag flag) {
        auto cursor = static_cast<HCURSOR>(
                LoadImageA(instance_handle, image_name, IMAGE_CURSOR, cx, cy,
                           static_cast<uint32_t>(flag)));
        if (!cursor) {
            error_code = GetLastError();
            return nullptr;
        }
        if (static_cast<uint32_t>(flag) & LR_SHARED) {
            return cursor;
        }
        cursor_rwlock.write_lock();
        cursor_handles.push_back(cursor);
        cursor_rwlock.write_unlock();
        return cursor;
    }

    HCURSOR image::load_cursor(HINSTANCE instance_handle,
                               const wchar_t* image_name,
                               int32_t cx,
                               int32_t cy,
                               ImageFlag flag) {
        auto cursor = static_cast<HCURSOR>(
                LoadImageW(instance_handle, image_name, IMAGE_CURSOR, cx, cy,
                           static_cast<uint32_t>(flag)));
        if (!cursor) {
            error_code = GetLastError();
            return nullptr;
        }
        if (static_cast<uint32_t>(flag) & LR_SHARED) {
            return cursor;
        }
        cursor_rwlock.write_lock();
        cursor_handles.push_back(cursor);
        cursor_rwlock.write_unlock();
        return cursor;
    }

    HBITMAP image::copy_bitmap(HBITMAP bitmap_handle,
                               int32_t cx,
                               int32_t cy,
                               ImageFlag flag) {
        auto bitmap = static_cast<HBITMAP>(
                CopyImage(bitmap_handle, IMAGE_BITMAP, cx, cy,
                          static_cast<uint32_t>(flag)));
        if (!bitmap) {
            error_code = GetLastError();
            return nullptr;
        }
        if (static_cast<uint32_t>(flag) & LR_SHARED) {
            return bitmap;
        }
        bitmap_rwlock.write_lock();
        bitmap_handles.push_back(bitmap);
        bitmap_rwlock.write_unlock();
        return bitmap;
    }

    HICON image::copy_icon(HICON icon_handle,
                           int32_t cx,
                           int32_t cy,
                           ImageFlag flag) {
        auto icon =
                static_cast<HICON>(CopyImage(icon_handle, IMAGE_ICON, cx, cy,
                                             static_cast<uint32_t>(flag)));
        if (!icon) {
            error_code = GetLastError();
            return nullptr;
        }
        if (static_cast<uint32_t>(flag) & LR_SHARED) {
            return icon;
        }
        icon_rwlock.write_lock();
        icon_handles.push_back(icon);
        icon_rwlock.write_unlock();
        return icon;
    }

    HCURSOR image::copy_cursor(HCURSOR cursor_handle,
                               int32_t cx,
                               int32_t cy,
                               ImageFlag flag) {
        auto cursor = static_cast<HCURSOR>(
                CopyImage(cursor_handle, IMAGE_CURSOR, cx, cy,
                          static_cast<uint32_t>(flag)));
        if (!cursor) {
            error_code = GetLastError();
            return nullptr;
        }
        if (static_cast<uint32_t>(flag) & LR_SHARED) {
            return cursor;
        }
        cursor_rwlock.write_lock();
        cursor_handles.push_back(cursor);
        cursor_rwlock.write_unlock();
        return cursor;
    }

    bool image::close_bitmap(HBITMAP bitmap_handle) {
        if (!bitmap_handle) {
            return false;
        }
        bitmap_rwlock.write_lock();
        const auto it = std::find(bitmap_handles.begin(), bitmap_handles.end(),
                                  bitmap_handle);
        if (it != bitmap_handles.end()) {
            *it = nullptr;
        }
        bitmap_rwlock.write_unlock();
        return DeleteObject(bitmap_handle);
    }

    bool image::close_icon(HICON icon_handle) {
        if (!icon_handle) {
            return false;
        }
        icon_rwlock.write_lock();
        const auto it = std::find(icon_handles.begin(), icon_handles.end(),
                                  icon_handle);
        if (it != icon_handles.end()) {
            *it = nullptr;
        }
        icon_rwlock.write_unlock();
        if (!DestroyIcon(icon_handle)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool image::close_cursor(HCURSOR cursor_handle) {
        if (!cursor_handle) {
            return false;
        }
        cursor_rwlock.write_lock();
        const auto it = std::find(cursor_handles.begin(), cursor_handles.end(),
                                  cursor_handle);
        if (it != cursor_handles.end()) {
            *it = nullptr;
        }
        cursor_rwlock.write_unlock();
        if (!DestroyCursor(cursor_handle)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    uint32_t image::err_code() const {
        return error_code;
    }

    std::string image::err_string() const {
        std::string result = helper::convert::err_string(error_code);
        return result;
    }

    std::wstring image::err_wstring() const {
        std::wstring result = helper::convert::err_wstring(error_code);
        return result;
    }
} // namespace YanLib::ui
