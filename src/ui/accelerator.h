//
// Created by forkernel on 2025/5/2.
//

#ifndef ACCELERATOR_H
#define ACCELERATOR_H
#include <Windows.h>
#include <string>

namespace YanLib::ui {
    class accelerator {
    private:
        unsigned long error_code = 0;

    public:
        accelerator(const accelerator &other) = delete;

        accelerator(accelerator &&other) = delete;

        accelerator &operator=(const accelerator &other) = delete;

        accelerator &operator=(accelerator &&other) = delete;

        accelerator() = default;

        ~accelerator() = default;

        HACCEL create_accelerator_table(ACCEL* accel, int count);

        HACCEL load_accelerators(HINSTANCE instance_handle,
                                 const wchar_t *table_name);

        bool destroy_accelerator_table(HACCEL accel_handle);

        int translate_accelerator(HWND hwnd, HACCEL accel_handle, MSG* msg);

        int copy_accelerator_table(HACCEL accel_handle_src,
                                   ACCEL* accel_handle_dst,
                                   int accel_entries);

        [[nodiscard]] unsigned long err_code() const;

        [[nodiscard]] std::string err_string() const;

        [[nodiscard]] std::wstring err_wstring() const;
    };
}
#endif //ACCELERATOR_H
