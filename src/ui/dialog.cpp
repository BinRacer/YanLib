//
// Created by forkernel on 2025/4/30.
//

#include "dialog.h"
#include "helper/convert.h"

namespace YanLib::ui {
    bool dialog::check_dialog_button(HWND hwnd_dialog,
                                     int id_button,
                                     UINT check) {
        if (!CheckDlgButton(hwnd_dialog,
                            id_button,
                            check)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    LRESULT dialog::default_dialog_proc(HWND hwnd_dialog,
                                        UINT msg,
                                        WPARAM w_param,
                                        LPARAM l_param) {
        return DefDlgProcW(hwnd_dialog,
                           msg,
                           w_param,
                           l_param);
    }

    DWORD dialog::err_code() const {
        return error_code;
    }

    std::string dialog::err_string() const {
        std::string result = helper::convert::err_string(error_code);
        return result;
    }

    std::wstring dialog::err_wstring() const {
        std::wstring result = helper::convert::err_wstring(error_code);
        return result;
    }
}
