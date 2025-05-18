//
// Created by forkernel on 2025/5/2.
//

#ifndef ACCELERATOR_H
#define ACCELERATOR_H
#include <Windows.h>
#include <string>
#include <vector>
#include "sync/rwlock.h"

namespace YanLib::ui {
class accelerator {
private:
    std::vector<HACCEL> accel_handles = {};
    sync::rwlock        rwlock        = {};
    uint32_t            error_code    = 0;

public:
    accelerator(const accelerator &other)            = delete;

    accelerator(accelerator &&other)                 = delete;

    accelerator &operator=(const accelerator &other) = delete;

    accelerator &operator=(accelerator &&other)      = delete;

    accelerator()                                    = default;

    ~accelerator();

    HACCEL create_table(std::vector<ACCEL> &accel);

    HACCEL load(HINSTANCE instance_handle, const char *table_name);

    HACCEL load(HINSTANCE instance_handle, const wchar_t *table_name);

    bool destroy_table(HACCEL accel_handle);

    int32_t translate(HWND window_handle, HACCEL accel_handle, MSG *msg);

    bool translate_mdi_sys(HWND client_window_handle, MSG *msg);

    int32_t copy_table(HACCEL accel_handle_src, std::vector<ACCEL> &accel_dst);

    [[nodiscard]] uint32_t err_code() const;

    [[nodiscard]] std::string err_string() const;

    [[nodiscard]] std::wstring err_wstring() const;
};
} // namespace YanLib::ui
#endif // ACCELERATOR_H
