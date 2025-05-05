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
        unsigned long error_code = 0;

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
                         unsigned long num_bytes = 0,
                         OVERLAPPED* overlapped = nullptr);

        bool get_status(ULONG_PTR *completion_key,
                        unsigned long* num_bytes,
                        OVERLAPPED* *overlapped,
                        unsigned long milli_seconds = INFINITE);

        bool get_status(OVERLAPPED_ENTRY* completion_port_entries,
                        unsigned long count,
                        unsigned long* num_entries_removed,
                        unsigned long milli_seconds = INFINITE,
                        bool alertable = false);

        bool cancel(HANDLE file_handle);

        bool cancel(HANDLE file_handle, OVERLAPPED* overlapped);

        bool cancel_sync_io(HANDLE thread_handle);

        bool device_io_control(HANDLE device_handle,
                               unsigned long io_control_code,
                               void *in_buffer,
                               unsigned long in_buffer_size,
                               void *out_buffer,
                               unsigned long out_buffer_size,
                               unsigned long* bytes_returned,
                               OVERLAPPED* overlapped);

        bool get_overlapped_result(HANDLE file_handle,
                                   OVERLAPPED* overlapped,
                                   unsigned long* number_of_bytes_transferred,
                                   bool is_wait);

        bool get_overlapped_result(HANDLE file_handle,
                                   OVERLAPPED* overlapped,
                                   unsigned long* number_of_bytes_transferred,
                                   unsigned long milli_seconds,
                                   bool is_wait);

        bool close();

        [[nodiscard]] unsigned long err_code() const;

        [[nodiscard]] std::string err_string() const;

        [[nodiscard]] std::wstring err_wstring() const;
    };
}
#endif //COMPLETION_PORT_H
