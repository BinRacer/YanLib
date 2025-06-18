/* clang-format off */
/*
 * @file comp_port.h
 * @date 2025-04-24
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
#ifndef COMP_PORT_H
#define COMP_PORT_H
#include <Windows.h>
#include <WinBase.h>
#include <minwinbase.h>
#include <winsock.h>
#include <winnt.h>
#include <vector>
#include <string>

namespace YanLib::io {
    class comp_port {
    private:
        HANDLE iocp = nullptr;
        int32_t max_concurrent_threads = 0;
        uint32_t error_code = 0;

        comp_port() = default;

    public:
        comp_port(const comp_port &other) = delete;

        comp_port(comp_port &&other) = delete;

        comp_port &operator=(const comp_port &other) = delete;

        comp_port &operator=(comp_port &&other) = delete;

        explicit comp_port(int32_t max_concurrency = 0);

        ~comp_port();

        bool create();

        bool associate_device(HANDLE file_handle, uintptr_t comp_key);

        bool associate_socket(SOCKET socket, uintptr_t comp_key);

        bool post_status(uintptr_t comp_key,
                         uint32_t num_bytes = 0,
                         OVERLAPPED *overlapped = nullptr);

        bool get_status(uintptr_t *comp_key,
                        uint32_t *num_bytes,
                        OVERLAPPED **overlapped,
                        uint32_t milli_seconds = INFINITE);

        bool get_status(OVERLAPPED_ENTRY *comp_port_entries,
                        uint32_t count,
                        uint32_t *num_entries_removed,
                        uint32_t milli_seconds = INFINITE,
                        bool is_alert = false);

        bool get_status(std::vector<OVERLAPPED_ENTRY> &entries,
                        uint32_t *num_entries_removed,
                        uint32_t milli_seconds = INFINITE,
                        bool is_alert = false);

        bool cancel(HANDLE file_handle);

        bool cancel(HANDLE file_handle, OVERLAPPED *overlapped);

        bool cancel_sync_io(HANDLE thread_handle);

        bool device_io_control(HANDLE device_handle,
                               uint32_t io_control_code,
                               void *in_buffer,
                               uint32_t in_buffer_size,
                               void *out_buffer,
                               uint32_t out_buffer_size,
                               uint32_t *bytes_transferred,
                               OVERLAPPED *overlapped);

        bool device_io_control(HANDLE device_handle,
                               uint32_t io_control_code,
                               std::vector<uint8_t> &in_buffer,
                               std::vector<uint8_t> &out_buffer,
                               uint32_t *bytes_transferred,
                               OVERLAPPED *overlapped);

        bool get_overlapped_result(HANDLE file_handle,
                                   OVERLAPPED *overlapped,
                                   uint32_t *bytes_transferred,
                                   bool is_wait);

        bool get_overlapped_result(HANDLE file_handle,
                                   OVERLAPPED *overlapped,
                                   uint32_t *bytes_transferred,
                                   uint32_t milli_seconds,
                                   bool is_wait);

        bool close();

        [[nodiscard]] uint32_t err_code() const;

        [[nodiscard]] std::string err_string() const;

        [[nodiscard]] std::wstring err_wstring() const;
    };
} // namespace YanLib::io
#endif // COMP_PORT_H
