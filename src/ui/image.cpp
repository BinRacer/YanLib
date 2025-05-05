//
// Created by forkernel on 2025/4/30.
//

#include "image.h"
#include "helper/convert.h"

namespace YanLib::ui {
    HBITMAP image::load_bitmap(HINSTANCE instance_handle,
                               const wchar_t *image_name,
                               int cx,
                               int cy,
                               unsigned int load) {
        HBITMAP bitmap = static_cast<HBITMAP>(LoadImageW(instance_handle,
                                                         image_name,
                                                         IMAGE_BITMAP,
                                                         cx,
                                                         cy,
                                                         load));
        if (!bitmap) {
            error_code = GetLastError();
        }
        return bitmap;
    }

    HICON image::load_icon(HINSTANCE instance_handle,
                           const wchar_t *image_name,
                           int cx,
                           int cy,
                           unsigned int load) {
        HICON icon = static_cast<HICON>(LoadImageW(instance_handle,
                                                   image_name,
                                                   IMAGE_ICON,
                                                   cx,
                                                   cy,
                                                   load));
        if (!icon) {
            error_code = GetLastError();
        }
        return icon;
    }

    HCURSOR image::load_cursor(HINSTANCE instance_handle,
                               const wchar_t *image_name,
                               int cx,
                               int cy,
                               unsigned int load) {
        HCURSOR cursor = static_cast<HCURSOR>(LoadImageW(instance_handle,
                                                         image_name,
                                                         IMAGE_CURSOR,
                                                         cx,
                                                         cy,
                                                         load));
        if (!cursor) {
            error_code = GetLastError();
        }
        return cursor;
    }

    HBITMAP image::copy_bitmap(HBITMAP bitmap_handle,
                               int cx,
                               int cy,
                               unsigned int flag) {
        HBITMAP result = static_cast<HBITMAP>(CopyImage(bitmap_handle,
                                                        IMAGE_BITMAP,
                                                        cx,
                                                        cy,
                                                        flag));
        if (!result) {
            error_code = GetLastError();
        }
        return result;
    }

    HICON image::copy_icon(HICON icon_handle,
                           int cx,
                           int cy,
                           unsigned int flag) {
        HICON result = static_cast<HICON>(CopyImage(icon_handle,
                                                    IMAGE_ICON,
                                                    cx,
                                                    cy,
                                                    flag));
        if (!result) {
            error_code = GetLastError();
        }
        return result;
    }

    HCURSOR image::copy_cursor(HCURSOR cursor_handle,
                               int cx,
                               int cy,
                               unsigned int flag) {
        HCURSOR result = static_cast<HCURSOR>(CopyImage(cursor_handle,
                                                        IMAGE_CURSOR,
                                                        cx,
                                                        cy,
                                                        flag));
        if (!result) {
            error_code = GetLastError();
        }
        return result;
    }

    bool image::close_bitmap(HBITMAP bitmap_handle) {
        return DeleteObject(bitmap_handle);
    }

    bool image::close_icon(HICON icon_handle) {
        if (!DestroyIcon(icon_handle)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool image::close_cursor(HCURSOR cursor_handle) {
        if (!DestroyCursor(cursor_handle)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    unsigned long image::err_code() const {
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
}
