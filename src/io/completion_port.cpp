//
// Created by forkernel on 2025/4/24.
//

#include "completion_port.h"
#include "helper/convert.h"

namespace YanLib::io {
    completion_port::completion_port(int max_concurrency) {
        max_concurrent_threads = max_concurrency;
    }

    completion_port::~completion_port() {
        if (iocp) {
            CloseHandle(iocp);
            iocp = nullptr;
        }
    }

    bool completion_port::create() {
        iocp = CreateIoCompletionPort(INVALID_HANDLE_VALUE,
                                      nullptr,
                                      0,
                                      max_concurrent_threads);
        if (!iocp) {
            error_code = GetLastError();
        }
        return iocp;
    }

    bool completion_port::associate_device(HANDLE file_handle,
                                           ULONG_PTR completion_key) {
        bool is_ok = CreateIoCompletionPort(file_handle,
                                            iocp,
                                            completion_key,
                                            max_concurrent_threads) == iocp;
        if (!is_ok) {
            error_code = GetLastError();
        }
        return is_ok;
    }

    bool completion_port::associate_socket(SOCKET socket,
                                           ULONG_PTR completion_key) {
        return associate_device(reinterpret_cast<HANDLE>(socket),
                                completion_key);
    }

    bool completion_port::post_status(ULONG_PTR completion_key,
                                      DWORD num_bytes,
                                      LPOVERLAPPED overlapped) {
        if (!PostQueuedCompletionStatus(iocp,
                                        num_bytes,
                                        completion_key,
                                        overlapped)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool completion_port::get_status(ULONG_PTR *completion_key,
                                     PDWORD num_bytes,
                                     LPOVERLAPPED *overlapped,
                                     DWORD milli_seconds) {
        if (!GetQueuedCompletionStatus(iocp,
                                       num_bytes,
                                       completion_key,
                                       overlapped,
                                       milli_seconds)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool completion_port::get_status(LPOVERLAPPED_ENTRY completion_port_entries,
                                     ULONG count,
                                     PULONG num_entries_removed,
                                     DWORD milli_seconds,
                                     bool alertable) {
        if (!GetQueuedCompletionStatusEx(iocp,
                                         completion_port_entries,
                                         count,
                                         num_entries_removed,
                                         milli_seconds,
                                         alertable ? TRUE : FALSE)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool completion_port::cancel(HANDLE file_handle) {
        if (!CancelIo(file_handle)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool completion_port::cancel(HANDLE file_handle, LPOVERLAPPED overlapped) {
        if (!CancelIoEx(file_handle, overlapped)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool completion_port::cancel_sync_io(HANDLE thread_handle) {
        if (!CancelSynchronousIo(thread_handle)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool completion_port::device_io_control(HANDLE device_handle,
                                            DWORD io_control_code,
                                            void *in_buffer,
                                            DWORD in_buffer_size,
                                            void *out_buffer,
                                            DWORD out_buffer_size,
                                            LPDWORD bytes_returned,
                                            LPOVERLAPPED overlapped) {
        if (!DeviceIoControl(device_handle,
                             io_control_code,
                             in_buffer,
                             in_buffer_size,
                             out_buffer,
                             out_buffer_size,
                             bytes_returned,
                             overlapped)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool completion_port::get_overlapped_result(HANDLE file_handle,
                                                LPOVERLAPPED overlapped,
                                                LPDWORD number_of_bytes_transferred,
                                                bool is_wait) {
        if (!GetOverlappedResult(file_handle,
                                 overlapped,
                                 number_of_bytes_transferred,
                                 is_wait ? TRUE : FALSE)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool completion_port::get_overlapped_result(HANDLE file_handle,
                                                LPOVERLAPPED overlapped,
                                                LPDWORD number_of_bytes_transferred,
                                                DWORD milli_seconds,
                                                bool is_wait) {
        if (!GetOverlappedResultEx(file_handle,
                                   overlapped,
                                   number_of_bytes_transferred,
                                   milli_seconds,
                                   is_wait ? TRUE : FALSE)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool completion_port::close() {
        bool is_ok = CloseHandle(iocp);
        iocp = nullptr;
        return is_ok;
    }

    DWORD completion_port::err_code() const {
        return error_code;
    }

    std::string completion_port::err_string() const {
        std::string result = helper::convert::err_string(error_code);
        return result;
    }

    std::wstring completion_port::err_wstring() const {
        std::wstring result = helper::convert::err_wstring(error_code);
        return result;
    }
}
