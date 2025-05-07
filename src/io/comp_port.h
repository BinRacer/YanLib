//
// Created by forkernel on 2025/4/24.
//

#ifndef COMP_PORT_H
#define COMP_PORT_H
#include <Windows.h>
#include <vector>
#include <string>

namespace YanLib::io {
class comp_port {
private:
    HANDLE   iocp                   = nullptr;
    int32_t  max_concurrent_threads = 0;
    uint32_t error_code             = 0;

    comp_port()                     = default;

public:
    comp_port(const comp_port &other)            = delete;

    comp_port(comp_port &&other)                 = delete;

    comp_port &operator=(const comp_port &other) = delete;

    comp_port &operator=(comp_port &&other)      = delete;

    explicit comp_port(int32_t max_concurrency = 0);

    ~comp_port();

    bool create();

    bool associate_device(HANDLE file_handle, ULONG_PTR comp_key);

    bool associate_socket(SOCKET socket, ULONG_PTR comp_key);

    bool post_status(ULONG_PTR comp_key,
        uint32_t               num_bytes  = 0,
        OVERLAPPED            *overlapped = nullptr);

    bool get_status(ULONG_PTR *comp_key,
        uint32_t              *num_bytes,
        OVERLAPPED           **overlapped,
        uint32_t               milli_seconds = INFINITE);

    bool get_status(OVERLAPPED_ENTRY *comp_port_entries,
        uint32_t                      count,
        uint32_t                     *num_entries_removed,
        uint32_t                      milli_seconds = INFINITE,
        bool                          is_alert      = false);

    bool get_status(std::vector<OVERLAPPED_ENTRY> &entries,
        uint32_t                                  *num_entries_removed,
        uint32_t                                   milli_seconds = INFINITE,
        bool                                       is_alert      = false);

    bool cancel(HANDLE file_handle);

    bool cancel(HANDLE file_handle, OVERLAPPED *overlapped);

    bool cancel_sync_io(HANDLE thread_handle);

    bool device_io_control(HANDLE device_handle,
        uint32_t                  io_control_code,
        void                     *in_buffer,
        uint32_t                  in_buffer_size,
        void                     *out_buffer,
        uint32_t                  out_buffer_size,
        uint32_t                 *bytes_transferred,
        OVERLAPPED               *overlapped);

    bool device_io_control(HANDLE device_handle,
        uint32_t                  io_control_code,
        std::vector<uint8_t>     &in_buffer,
        std::vector<uint8_t>     &out_buffer,
        uint32_t                 *bytes_transferred,
        OVERLAPPED               *overlapped);

    bool get_overlapped_result(HANDLE file_handle,
        OVERLAPPED                   *overlapped,
        uint32_t                     *bytes_transferred,
        bool                          is_wait);

    bool get_overlapped_result(HANDLE file_handle,
        OVERLAPPED                   *overlapped,
        uint32_t                     *bytes_transferred,
        uint32_t                      milli_seconds,
        bool                          is_wait);

    bool close();

    [[nodiscard]] uint32_t err_code() const;

    [[nodiscard]] std::string err_string() const;

    [[nodiscard]] std::wstring err_wstring() const;
};
} // namespace YanLib::io
#endif // COMP_PORT_H
