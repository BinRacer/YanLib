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
        WSADATA wsa_data{};
        volatile bool is_ipv6 = false;
        SOCKET server_socket{};
        int error_code{};

        udp_server() = default;

    public:
        udp_server(const udp_server &other) = delete;

        udp_server(udp_server &&other) = delete;

        udp_server &operator=(const udp_server &other) = delete;

        udp_server &operator=(udp_server &&other) = delete;

        explicit udp_server(bool active_ipv6 = false);

        ~udp_server();

        bool bind(const char *local_ip = "0.0.0.0",
                  uint16_t local_port = 8080);

        int read(char *buf, int len,
                 int flags,
                 sockaddr *from, int *fromlen);

        int write(const char *buf, int len,
                  int flags,
                  const sockaddr *to, int tolen);

        int read(char *buf, int len,
                 std::string &client_ip, uint16_t &client_port);

        int write(char *buf, int len,
                  std::string &client_ip, uint16_t &client_port);

        std::string read_string(std::string &client_ip,
                                uint16_t &client_port,
                                int32_t buffer_size = 1024);

        std::wstring read_wstring(std::string &client_ip,
                                  uint16_t &client_port,
                                  int32_t buffer_size = 512);

        std::string read_string_to_end(std::string &client_ip,
                                       uint16_t &client_port);

        std::wstring read_wstring_to_end(std::string &client_ip,
                                         uint16_t &client_port);

        int write_string(std::string &str, std::string &client_ip,
                         uint16_t &client_port);

        int write_wstring(std::wstring &wstr, std::string &client_ip,
                          uint16_t &client_port);

        int err_code() const;

        std::string err_string() const;

        std::wstring err_wstring() const;
    };
}
#endif //UDP_SERVER_H
