//
// Created by forkernel on 2025/4/30.
//

#include "menu.h"
#include "helper/convert.h"

namespace YanLib::ui {
    bool menu::append_menu(HMENU menu_handle,
                           UINT flag,
                           UINT_PTR id_new_item,
                           const wchar_t *new_item) {
        if (!AppendMenuW(menu_handle, flag, id_new_item, new_item)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    DWORD menu::err_code() const {
        return error_code;
    }

    std::string menu::err_string() const {
        std::string result = helper::convert::err_string(error_code);
        return result;
    }

    std::wstring menu::err_wstring() const {
        std::wstring result = helper::convert::err_wstring(error_code);
        return result;
    }
}
