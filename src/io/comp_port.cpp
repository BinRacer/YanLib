//
// Created by forkernel on 2025/4/24.
//

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

    bool comp_port::associate_device(HANDLE file_handle, ULONG_PTR comp_key) {
        bool is_ok = CreateIoCompletionPort(file_handle, iocp, comp_key,
                                            max_concurrent_threads) == iocp;
        if (!is_ok) {
            error_code = GetLastError();
        }
        return is_ok;
    }

    bool comp_port::associate_socket(SOCKET socket, ULONG_PTR comp_key) {
        return associate_device(reinterpret_cast<HANDLE>(socket), comp_key);
    }

    bool comp_port::post_status(ULONG_PTR comp_key,
                                uint32_t num_bytes,
                                OVERLAPPED* overlapped) {
        if (!PostQueuedCompletionStatus(iocp, num_bytes, comp_key,
                                        overlapped)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool comp_port::get_status(ULONG_PTR* comp_key,
                               uint32_t* num_bytes,
                               OVERLAPPED** overlapped,
                               uint32_t milli_seconds) {
        if (!GetQueuedCompletionStatus(iocp,
                                       reinterpret_cast<unsigned long*>(
                                               num_bytes),
                                       comp_key, overlapped, milli_seconds)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool comp_port::get_status(OVERLAPPED_ENTRY* comp_port_entries,
                               uint32_t count,
                               uint32_t* num_entries_removed,
                               uint32_t milli_seconds,
                               bool is_alert) {
        if (!GetQueuedCompletionStatusEx(iocp, comp_port_entries, count,
                                         reinterpret_cast<unsigned long*>(
                                                 num_entries_removed),
                                         milli_seconds,
                                         is_alert ? TRUE : FALSE)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool comp_port::get_status(std::vector<OVERLAPPED_ENTRY> &entries,
                               uint32_t* num_entries_removed,
                               uint32_t milli_seconds,
                               bool is_alert) {
        if (!GetQueuedCompletionStatusEx(iocp, entries.data(), entries.size(),
                                         reinterpret_cast<unsigned long*>(
                                                 num_entries_removed),
                                         milli_seconds,
                                         is_alert ? TRUE : FALSE)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool comp_port::cancel(HANDLE file_handle) {
        if (!CancelIo(file_handle)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool comp_port::cancel(HANDLE file_handle, OVERLAPPED* overlapped) {
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
                                      void* in_buffer,
                                      uint32_t in_buffer_size,
                                      void* out_buffer,
                                      uint32_t out_buffer_size,
                                      uint32_t* bytes_transferred,
                                      OVERLAPPED* overlapped) {
        if (!DeviceIoControl(device_handle, io_control_code, in_buffer,
                             in_buffer_size, out_buffer, out_buffer_size,
                             reinterpret_cast<unsigned long*>(
                                     bytes_transferred),
                             overlapped)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool comp_port::device_io_control(HANDLE device_handle,
                                      uint32_t io_control_code,
                                      std::vector<uint8_t> &in_buffer,
                                      std::vector<uint8_t> &out_buffer,
                                      uint32_t* bytes_transferred,
                                      OVERLAPPED* overlapped) {
        if (in_buffer.empty() || out_buffer.empty()) {
            return false;
        }
        if (!DeviceIoControl(device_handle, io_control_code, in_buffer.data(),
                             in_buffer.size(), out_buffer.data(),
                             out_buffer.size(),
                             reinterpret_cast<unsigned long*>(
                                     bytes_transferred),
                             overlapped)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool comp_port::get_overlapped_result(HANDLE file_handle,
                                          OVERLAPPED* overlapped,
                                          uint32_t* bytes_transferred,
                                          bool is_wait) {
        if (!GetOverlappedResult(file_handle, overlapped,
                                 reinterpret_cast<unsigned long*>(
                                         bytes_transferred),
                                 is_wait ? TRUE : FALSE)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool comp_port::get_overlapped_result(HANDLE file_handle,
                                          OVERLAPPED* overlapped,
                                          uint32_t* bytes_transferred,
                                          uint32_t milli_seconds,
                                          bool is_wait) {
        if (!GetOverlappedResultEx(file_handle, overlapped,
                                   reinterpret_cast<unsigned long*>(
                                           bytes_transferred),
                                   milli_seconds, is_wait ? TRUE : FALSE)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool comp_port::close() {
        bool is_ok = CloseHandle(iocp);
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
