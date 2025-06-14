/* clang-format off */
/*
 * @file comp_port.cpp
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
#include "comp_port.h"
#include "helper/convert.h"

namespace YanLib::io {
    comp_port::comp_port(int32_t max_concurrency) {
        max_concurrent_threads = max_concurrency;
    }

    comp_port::~comp_port() {
        if (iocp) {
            CloseHandle(iocp);
            iocp = nullptr;
        }
    }

    bool comp_port::create() {
        iocp = CreateIoCompletionPort(INVALID_HANDLE_VALUE, nullptr, 0,
                                      max_concurrent_threads);
        if (!iocp) {
            error_code = GetLastError();
        }
        return iocp;
    }

    bool comp_port::associate_device(HANDLE file_handle, uintptr_t comp_key) {
        const bool is_ok =
                CreateIoCompletionPort(file_handle, iocp, comp_key,
                                       max_concurrent_threads) == iocp;
        if (!is_ok) {
            error_code = GetLastError();
        }
        return is_ok;
    }

    bool comp_port::associate_socket(SOCKET socket, uintptr_t comp_key) {
        return associate_device(reinterpret_cast<HANDLE>(socket), comp_key);
    }

    bool comp_port::post_status(uintptr_t comp_key,
                                uint32_t num_bytes,
                                OVERLAPPED *overlapped) {
        if (!PostQueuedCompletionStatus(iocp, num_bytes, comp_key,
                                        overlapped)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool comp_port::get_status(uintptr_t *comp_key,
                               uint32_t *num_bytes,
                               OVERLAPPED **overlapped,
                               uint32_t milli_seconds) {
        if (!num_bytes) {
            error_code = STATUS_ACCESS_VIOLATION;
            return false;
        }
        unsigned long temp = *num_bytes;
        if (!GetQueuedCompletionStatus(iocp, &temp, comp_key, overlapped,
                                       milli_seconds)) {
            error_code = GetLastError();
            *num_bytes = temp;
            return false;
        }
        *num_bytes = temp;
        return true;
    }

    bool comp_port::get_status(OVERLAPPED_ENTRY *comp_port_entries,
                               uint32_t count,
                               uint32_t *num_entries_removed,
                               uint32_t milli_seconds,
                               bool is_alert) {
        if (!num_entries_removed) {
            error_code = STATUS_ACCESS_VIOLATION;
            return false;
        }
        unsigned long temp = *num_entries_removed;
        if (!GetQueuedCompletionStatusEx(iocp, comp_port_entries, count, &temp,
                                         milli_seconds,
                                         is_alert ? TRUE : FALSE)) {
            error_code = GetLastError();
            *num_entries_removed = temp;
            return false;
        }
        *num_entries_removed = temp;
        return true;
    }

    bool comp_port::get_status(std::vector<OVERLAPPED_ENTRY> &entries,
                               uint32_t *num_entries_removed,
                               uint32_t milli_seconds,
                               bool is_alert) {
        if (!num_entries_removed) {
            error_code = STATUS_ACCESS_VIOLATION;
            return false;
        }
        unsigned long temp = *num_entries_removed;
        if (!GetQueuedCompletionStatusEx(iocp, entries.data(), entries.size(),
                                         &temp, milli_seconds,
                                         is_alert ? TRUE : FALSE)) {
            error_code = GetLastError();
            *num_entries_removed = temp;
            return false;
        }
        *num_entries_removed = temp;
        return true;
    }

    bool comp_port::cancel(HANDLE file_handle) {
        if (!CancelIo(file_handle)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool comp_port::cancel(HANDLE file_handle, OVERLAPPED *overlapped) {
        if (!CancelIoEx(file_handle, overlapped)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool comp_port::cancel_sync_io(HANDLE thread_handle) {
        if (!CancelSynchronousIo(thread_handle)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool comp_port::device_io_control(HANDLE device_handle,
                                      uint32_t io_control_code,
                                      void *in_buffer,
                                      uint32_t in_buffer_size,
                                      void *out_buffer,
                                      uint32_t out_buffer_size,
                                      uint32_t *bytes_transferred,
                                      OVERLAPPED *overlapped) {
        if (!bytes_transferred) {
            error_code = STATUS_ACCESS_VIOLATION;
            return false;
        }
        unsigned long temp = *bytes_transferred;
        if (!DeviceIoControl(device_handle, io_control_code, in_buffer,
                             in_buffer_size, out_buffer, out_buffer_size, &temp,
                             overlapped)) {
            error_code = GetLastError();
            *bytes_transferred = temp;
            return false;
        }
        *bytes_transferred = temp;
        return true;
    }

    bool comp_port::device_io_control(HANDLE device_handle,
                                      uint32_t io_control_code,
                                      std::vector<uint8_t> &in_buffer,
                                      std::vector<uint8_t> &out_buffer,
                                      uint32_t *bytes_transferred,
                                      OVERLAPPED *overlapped) {
        if (!bytes_transferred) {
            error_code = STATUS_ACCESS_VIOLATION;
            return false;
        }
        if (in_buffer.empty() || out_buffer.empty()) {
            return false;
        }
        unsigned long temp = *bytes_transferred;
        if (!DeviceIoControl(device_handle, io_control_code, in_buffer.data(),
                             in_buffer.size(), out_buffer.data(),
                             out_buffer.size(), &temp, overlapped)) {
            error_code = GetLastError();
            *bytes_transferred = temp;
            return false;
        }
        *bytes_transferred = temp;
        return true;
    }

    bool comp_port::get_overlapped_result(HANDLE file_handle,
                                          OVERLAPPED *overlapped,
                                          uint32_t *bytes_transferred,
                                          bool is_wait) {
        if (!bytes_transferred) {
            error_code = STATUS_ACCESS_VIOLATION;
            return false;
        }
        unsigned long temp = *bytes_transferred;
        if (!GetOverlappedResult(file_handle, overlapped, &temp,
                                 is_wait ? TRUE : FALSE)) {
            error_code = GetLastError();
            *bytes_transferred = temp;
            return false;
        }
        *bytes_transferred = temp;
        return true;
    }

    bool comp_port::get_overlapped_result(HANDLE file_handle,
                                          OVERLAPPED *overlapped,
                                          uint32_t *bytes_transferred,
                                          uint32_t milli_seconds,
                                          bool is_wait) {
        if (!bytes_transferred) {
            error_code = STATUS_ACCESS_VIOLATION;
            return false;
        }
        unsigned long temp = *bytes_transferred;
        if (!GetOverlappedResultEx(file_handle, overlapped, &temp,
                                   milli_seconds, is_wait ? TRUE : FALSE)) {
            error_code = GetLastError();
            *bytes_transferred = temp;
            return false;
        }
        *bytes_transferred = temp;
        return true;
    }

    bool comp_port::close() {
        const bool is_ok = CloseHandle(iocp);
        iocp = nullptr;
        return is_ok;
    }

    uint32_t comp_port::err_code() const {
        return error_code;
    }

    std::string comp_port::err_string() const {
        std::string result = helper::convert::err_string(error_code);
        return result;
    }

    std::wstring comp_port::err_wstring() const {
        std::wstring result = helper::convert::err_wstring(error_code);
        return result;
    }
} // namespace YanLib::io
