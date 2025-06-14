/* clang-format off */
/*
 * @file accelerator.h
 * @date 2025-05-02
 * @license MIT License
 *
 * Copyright (c) 2025 BinRacer <native.lab@outlook.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
/* clang-format on */
#ifndef ACCELERATOR_H
#define ACCELERATOR_H
#include <Windows.h>
#include <string>
#include <vector>
#include "sync/rwlock.h"

namespace YanLib::ui::core {
    class accelerator {
    private:
        std::vector<HACCEL> accel_handles = {};
        sync::rwlock rwlock = {};
        uint32_t error_code = 0;

    public:
        accelerator(const accelerator &other) = delete;

        accelerator(accelerator &&other) = delete;

        accelerator &operator=(const accelerator &other) = delete;

        accelerator &operator=(accelerator &&other) = delete;

        accelerator() = default;

        ~accelerator();

        HACCEL create(std::vector<ACCEL> &accel);

        HACCEL load(HINSTANCE instance_handle, const char *table_name);

        HACCEL load(HINSTANCE instance_handle, const wchar_t *table_name);

        bool destroy(HACCEL accel_handle);

        int32_t translate(HWND window_handle, HACCEL accel_handle, MSG *msg);

        bool translate_mdi_sys(HWND client_window_handle, MSG *msg);

        int32_t copy(HACCEL accel_handle_src, std::vector<ACCEL> &accel_dst);

        [[nodiscard]] uint32_t err_code() const;

        [[nodiscard]] std::string err_string() const;

        [[nodiscard]] std::wstring err_wstring() const;
    };
} // namespace YanLib::ui::core
#endif // ACCELERATOR_H
