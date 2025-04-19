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
        WSADATA wsa_data{};
        volatile bool is_ipv6 = false;
        SOCKET client_socket{};
        int error_code{};

        udp_client() = default;

    public:
        udp_client(const udp_client &other) = delete;

        udp_client(udp_client &&other) = delete;

        udp_client &operator=(const udp_client &other) = delete;

        udp_client &operator=(udp_client &&other) = delete;

        explicit udp_client(bool active_ipv6 = false);

        ~udp_client();

        int read(char *buf, int len,
                 int flags,
                 sockaddr *from, int *fromlen);

        int write(const char *buf, int len,
                  int flags,
                  const sockaddr *to, int tolen);

        int read(char *buf, int len,
                 std::string &remote_ip, uint16_t &remote_port);

        int write(char *buf, int len,
                  std::string &remote_ip, uint16_t &remote_port);

        std::string read_string(std::string &remote_ip,
                                uint16_t &remote_port,
                                int32_t buffer_size = 1024);

        std::wstring read_wstring(std::string &remote_ip,
                                  uint16_t &remote_port,
                                  int32_t buffer_size = 512);

        std::string read_string_to_end(std::string &remote_ip,
                                       uint16_t &remote_port);

        std::wstring read_wstring_to_end(std::string &remote_ip,
                                         uint16_t &remote_port);

        int write_string(std::string &str,
                         std::string &remote_ip, uint16_t &remote_port);

        int write_wstring(std::wstring &wstr,
                          std::string &remote_ip, uint16_t &remote_port);

        int err_code() const;

        std::string err_string() const;

        std::wstring err_wstring() const;
    };
}
#endif //UDP_CLIENT_H
