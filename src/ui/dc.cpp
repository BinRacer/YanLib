//
// Created by forkernel on 2025/5/2.
//

#include "dc.h"
#include "helper/convert.h"

namespace YanLib::ui {
    DWORD dc::err_code() const {
        return error_code;
    }

    std::string dc::err_string() const {
        std::string result = helper::convert::err_string(error_code);
        return result;
    }

    std::wstring dc::err_wstring() const {
        std::wstring result = helper::convert::err_wstring(error_code);
        return result;
    }
}
