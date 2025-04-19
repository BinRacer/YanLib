//
// Created by forkernel on 2025/4/18.
//

#include "thread.h"
#include "helper/convert.h"

namespace YanLib::sys {
    DWORD thread::err_code() const {
        return error_code;
    }

    std::string thread::err_string() const {
        std::string result = helper::convert::err_string(error_code);
        return result;
    }

    std::wstring thread::err_wstring() const {
        std::wstring result = helper::convert::err_wstring(error_code);
        return result;
    }
}
