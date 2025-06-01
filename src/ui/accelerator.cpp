//
// Created by forkernel on 2025/5/2.
//

#include "accelerator.h"
#include "helper/convert.h"

namespace YanLib::ui {
    accelerator::~accelerator() {
        for (auto &accel : accel_handles) {
            if (accel) {
                DestroyAcceleratorTable(accel);
                accel = nullptr;
            }
        }
        accel_handles.clear();
    }

    HACCEL accelerator::create_table(std::vector<ACCEL> &accel) {
        HACCEL result =
                CreateAcceleratorTableW(accel.data(),
                                        static_cast<int32_t>(accel.size()));
        if (!result) {
            error_code = GetLastError();
            return nullptr;
        }
        rwlock.write_lock();
        accel_handles.push_back(result);
        rwlock.write_unlock();
        return result;
    }

    HACCEL accelerator::load(HINSTANCE instance_handle,
                             const char *table_name) {
        HACCEL result = LoadAcceleratorsA(instance_handle, table_name);
        if (!result) {
            error_code = GetLastError();
        }
        return result;
    }

    HACCEL accelerator::load(HINSTANCE instance_handle,
                             const wchar_t *table_name) {
        HACCEL result = LoadAcceleratorsW(instance_handle, table_name);
        if (!result) {
            error_code = GetLastError();
        }
        return result;
    }

    bool accelerator::destroy_table(HACCEL accel_handle) {
        if (!accel_handle) {
            return false;
        }
        rwlock.write_lock();
        const auto it = std::find(accel_handles.begin(), accel_handles.end(),
                                  accel_handle);
        if (it != accel_handles.end()) {
            *it = nullptr;
        }
        rwlock.write_unlock();
        return DestroyAcceleratorTable(accel_handle);
    }

    int32_t
    accelerator::translate(HWND window_handle, HACCEL accel_handle, MSG *msg) {
        int32_t result =
                TranslateAcceleratorW(window_handle, accel_handle, msg);
        if (!result) {
            error_code = GetLastError();
        }
        return result;
    }

    bool accelerator::translate_mdi_sys(HWND client_window_handle, MSG *msg) {
        return TranslateMDISysAccel(client_window_handle, msg);
    }

    int32_t accelerator::copy_table(HACCEL accel_handle_src,
                                    std::vector<ACCEL> &accel_dst) {
        return CopyAcceleratorTableW(accel_handle_src, accel_dst.data(),
                                     static_cast<int32_t>(accel_dst.size()));
    }

    uint32_t accelerator::err_code() const {
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
} // namespace YanLib::ui
