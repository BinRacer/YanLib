//
// Created by forkernel on 2025/5/2.
//

#include "accelerator.h"
#include "helper/convert.h"

namespace YanLib::ui {
    HACCEL accelerator::create_accelerator_table(LPACCEL accel, int count) {
        HACCEL result = CreateAcceleratorTableW(accel, count);
        if (!result) {
            error_code = GetLastError();
        }
        return result;
    }

    HACCEL accelerator::load_accelerators(HINSTANCE instance_handle,
                                          const wchar_t *table_name) {
        HACCEL result = LoadAcceleratorsW(instance_handle, table_name);
        if (!result) {
            error_code = GetLastError();
        }
        return result;
    }

    bool accelerator::destroy_accelerator_table(HACCEL accel_handle) {
        return DestroyAcceleratorTable(accel_handle);
    }

    int accelerator::translate_accelerator(HWND hwnd,
                                           HACCEL accel_handle,
                                           LPMSG msg) {
        int result = TranslateAcceleratorW(hwnd, accel_handle, msg);
        if (!result) {
            error_code = GetLastError();
        }
        return result;
    }

    int accelerator::copy_accelerator_table(HACCEL accel_handle_src,
                                            LPACCEL accel_handle_dst,
                                            int accel_entries) {
        return CopyAcceleratorTableW(accel_handle_src,
                                     accel_handle_dst,
                                     accel_entries);
    }

    DWORD accelerator::err_code() const {
        return error_code;
    }

    std::string accelerator::err_string() const {
        std::string result = helper::convert::err_string(error_code);
        return result;
    }

    std::wstring accelerator::err_wstring() const {
        std::wstring result = helper::convert::err_wstring(error_code);
        return result;
    }
}
