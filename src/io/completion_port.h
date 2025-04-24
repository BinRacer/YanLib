//
// Created by forkernel on 2025/4/24.
//

#ifndef COMPLETION_PORT_H
#define COMPLETION_PORT_H
#include <Windows.h>
#include <string>

namespace YanLib::io {
    class completion_port {
    private:
        HANDLE iocp = nullptr;
        int max_concurrent_threads = 0;
        DWORD error_code = 0;

        completion_port() = default;

    public:
        completion_port(const completion_port &other) = delete;

        completion_port(completion_port &&other) = delete;

        completion_port &operator=(const completion_port &other) = delete;

        completion_port &operator=(completion_port &&other) = delete;

        explicit completion_port(int max_concurrency = 0);

        ~completion_port();

        bool create();

        bool associate_device(HANDLE file_handle,
                              ULONG_PTR completion_key);

        bool associate_socket(SOCKET socket,
                              ULONG_PTR completion_key);

        bool post_status(ULONG_PTR completion_key,
                         DWORD num_bytes = 0,
                         LPOVERLAPPED overlapped = nullptr);

        bool get_status(ULONG_PTR *completion_key,
                        PDWORD num_bytes,
                        LPOVERLAPPED *overlapped,
                        DWORD milli_seconds = INFINITE);

        bool get_status(LPOVERLAPPED_ENTRY completion_port_entries,
                        ULONG count,
                        PULONG num_entries_removed,
                        DWORD milli_seconds = INFINITE,
                        bool alertable = false);

        bool cancel(HANDLE file_handle);

        bool cancel(HANDLE file_handle, LPOVERLAPPED overlapped);

        bool cancel_sync_io(HANDLE thread_handle);

        bool device_io_control(HANDLE device_handle,
                               DWORD io_control_code,
                               void *in_buffer,
                               DWORD in_buffer_size,
                               void *out_buffer,
                               DWORD out_buffer_size,
                               LPDWORD bytes_returned,
                               LPOVERLAPPED overlapped);

        bool get_overlapped_result(HANDLE file_handle,
                                   LPOVERLAPPED overlapped,
                                   LPDWORD number_of_bytes_transferred,
                                   bool is_wait);

        bool get_overlapped_result(HANDLE file_handle,
                                   LPOVERLAPPED overlapped,
                                   LPDWORD number_of_bytes_transferred,
                                   DWORD milli_seconds,
                                   bool is_wait);

        bool close();

        [[nodiscard]] DWORD err_code() const;

        [[nodiscard]] std::string err_string() const;

        [[nodiscard]] std::wstring err_wstring() const;
    };
}
#endif //COMPLETION_PORT_H
