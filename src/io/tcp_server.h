//
// Created by forkernel on 2025/4/4.
//

#ifndef TCP_H
#define TCP_H
#include <winsock2.h>
#include <string>
#include <list>
#include "sync/rwlock.h"

#pragma comment(lib, "ws2_32.lib")
namespace YanLib::io {
    class tcp_server {
    private:
        WSADATA wsa_data{};
        volatile bool is_ipv6 = false;
        SOCKET server_socket{};
        int error_code{};
        sync::rwlock rwlock{};
        std::list<SOCKET> client_sockets{};

        tcp_server() = default;

    public:
        tcp_server(const tcp_server &other) = delete;

        tcp_server(tcp_server &&other) = delete;

        tcp_server &operator=(const tcp_server &other) = delete;

        tcp_server &operator=(tcp_server &&other) = delete;

        explicit tcp_server(bool active_ipv6 = false);

        ~tcp_server();

        bool bind(const char *local_ip = "0.0.0.0",
                  uint16_t local_port = 8080);

        bool listen(int backlog = SOMAXCONN);

        SOCKET accept(sockaddr *addr, int *addrlen);

        int read(SOCKET client_socket, char *buf,
                 int len, int flags = 0);

        int write(SOCKET client_socket, const char *buf,
                  int len, int flags = 0);

        std::string read_string(SOCKET client_socket, int32_t buffer_size = 1024);

        std::wstring read_wstring(SOCKET client_socket, int32_t buffer_size = 512);

        std::string read_string_to_end(SOCKET client_socket);

        std::wstring read_wstring_to_end(SOCKET client_socket);

        int write_string(SOCKET client_socket, std::string &str);

        int write_wstring(SOCKET client_socket, std::wstring &wstr);

        [[nodiscard]] int err_code() const;

        [[nodiscard]] std::string err_string() const;

        [[nodiscard]] std::wstring err_wstring() const;
    };
}
#endif //TCP_H
