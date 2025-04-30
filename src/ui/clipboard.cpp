//
// Created by forkernel on 2025/4/30.
//

#include "clipboard.h"
#include "helper/convert.h"

namespace YanLib::ui {
    DWORD clipboard::err_code() const {
        return error_code;
    }

    std::string clipboard::err_string() const {
        std::string result = helper::convert::err_string(error_code);
        return result;
    }

    std::wstring clipboard::err_wstring() const {
        std::wstring result = helper::convert::err_wstring(error_code);
        return result;
    }
}
