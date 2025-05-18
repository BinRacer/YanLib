//
// Created by forkernel on 2025/4/5.
//

#ifndef UDP_SERVER_H
#define UDP_SERVER_H
#include <winsock2.h>
#include <string>

#pragma comment(lib, "ws2_32.lib")
namespace YanLib::io {
    class udp_server {
    private:
        WSADATA wsa_data = {};
        volatile bool is_ipv6 = false;
        SOCKET server_socket = INVALID_SOCKET;
        volatile bool init_done = false;
        int32_t error_code = 0;

        udp_server() = default;

    public:
        udp_server(const udp_server &other) = delete;

        udp_server(udp_server &&other) = delete;

        udp_server &operator=(const udp_server &other) = delete;

        udp_server &operator=(udp_server &&other) = delete;

        explicit udp_server(bool active_ipv6 = false);

        ~udp_server();

        [[nodiscard]] bool init_ok() const;

        bool bind(const char* local_ip = "0.0.0.0", uint16_t local_port = 8080);

        int32_t read(char* buf,
                     int32_t len,
                     int32_t flags,
                     sockaddr* from,
                     int32_t* from_len);

        int32_t write(const char* buf,
                      int32_t len,
                      int32_t flags,
                      const sockaddr* to,
                      int32_t to_len);

        int32_t read(char* buf,
                     int32_t len,
                     std::string &client_ip,
                     uint16_t &client_port);

        int32_t write(char* buf,
                      int32_t len,
                      std::string &client_ip,
                      uint16_t &client_port);

        std::string read_string(std::string &client_ip,
                                uint16_t &client_port,
                                int32_t buffer_size = 1024);

        std::string read_string_to_end(std::string &client_ip,
                                       uint16_t &client_port);

        int32_t write_string(std::string &str,
                             std::string &client_ip,
                             uint16_t &client_port);

        [[nodiscard]] int32_t err_code() const;

        [[nodiscard]] std::string err_string() const;

        [[nodiscard]] std::wstring err_wstring() const;
    };
} // namespace YanLib::io
#endif // UDP_SERVER_H
