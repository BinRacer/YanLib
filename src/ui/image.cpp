//
// Created by forkernel on 2025/4/30.
//

#include "image.h"
#include "helper/convert.h"

namespace YanLib::ui {
    HANDLE image::load_image(HINSTANCE instance_handle,
                             const wchar_t *image_name,
                             UINT type,
                             int cx,
                             int cy,
                             UINT load) {
        HANDLE image_handle = LoadImageW(instance_handle,
                                         image_name,
                                         type,
                                         cx,
                                         cy,
                                         load);
        if (!image_handle) {
            error_code = GetLastError();
        }
        return image_handle;
    }

    HANDLE image::copy_image(HANDLE image_handle,
                             UINT type,
                             int cx,
                             int cy,
                             UINT flag) {
        HANDLE result = CopyImage(image_handle,
                                  type,
                                  cx,
                                  cy,
                                  flag);
        if (!result) {
            error_code = GetLastError();
        }
        return result;
    }

    bool image::close_image(HANDLE image_handle) {
        if (!CloseHandle(image_handle)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    DWORD image::err_code() const {
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
