//
// Created by forkernel on 2025/4/24.
//

#include "pe.h"
#include "helper/convert.h"

namespace YanLib::io {
    DWORD pe::err_code() const {
        return error_code;
    }

    std::string pe::err_string() const {
        std::string result = helper::convert::err_string(error_code);
        return result;
    }

    std::wstring pe::err_wstring() const {
        std::wstring result = helper::convert::err_wstring(error_code);
        return result;
    }
}
