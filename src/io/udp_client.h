//
// Created by forkernel on 2025/4/5.
//

#ifndef UDP_CLIENT_H
#define UDP_CLIENT_H

#include <winsock2.h>
#include <string>

#pragma comment(lib, "ws2_32.lib")
namespace YanLib::io {
class udp_client {
private:
    WSADATA       wsa_data      = {};
    volatile bool is_ipv6       = false;
    SOCKET        client_socket = INVALID_SOCKET;
    volatile bool init_done     = false;
    int32_t       error_code    = 0;

    udp_client()                = default;

public:
    udp_client(const udp_client &other)            = delete;

    udp_client(udp_client &&other)                 = delete;

    udp_client &operator=(const udp_client &other) = delete;

    udp_client &operator=(udp_client &&other)      = delete;

    explicit udp_client(bool active_ipv6 = false);

    ~udp_client();

    [[nodiscard]] bool init_ok() const;

    int32_t read(char *buf,
        int32_t        len,
        int32_t        flags,
        sockaddr      *from,
        int32_t       *from_len);

    int32_t write(const char *buf,
        int32_t               len,
        int32_t               flags,
        const sockaddr       *to,
        int32_t               to_len);

    int32_t
    read(char *buf, int32_t len, std::string &remote_ip, uint16_t &remote_port);

    int32_t write(char *buf,
        int32_t         len,
        std::string    &remote_ip,
        uint16_t       &remote_port);

    std::string read_string(std::string &remote_ip,
        uint16_t                        &remote_port,
        int32_t                          buffer_size = 1024);

    std::string read_string_to_end(std::string &remote_ip,
        uint16_t                               &remote_port);

    int32_t write_string(std::string &str,
        std::string                  &remote_ip,
        uint16_t                     &remote_port);

    [[nodiscard]] int32_t err_code() const;

    [[nodiscard]] std::string err_string() const;

    [[nodiscard]] std::wstring err_wstring() const;
};
} // namespace YanLib::io
#endif // UDP_CLIENT_H
