//
// Created by forkernel on 2025/4/4.
//

#ifndef TCP_H
#define TCP_H
#include <winsock2.h>
#include <string>
#include <vector>
#include "sync/rwlock.h"
#pragma comment(lib, "WS2_32.Lib")
namespace YanLib::io {
    class tcp_server {
    private:
        WSADATA wsa_data = {};
        volatile bool is_ipv6 = false;
        SOCKET server_socket = INVALID_SOCKET;
        volatile bool init_done = false;
        int32_t error_code = {};
        sync::rwlock rwlock = {};
        std::vector<SOCKET> client_sockets = {};

        tcp_server() = default;

    public:
        tcp_server(const tcp_server &other) = delete;

        tcp_server(tcp_server &&other) = delete;

        tcp_server &operator=(const tcp_server &other) = delete;

        tcp_server &operator=(tcp_server &&other) = delete;

        explicit tcp_server(bool active_ipv6 = false);

        ~tcp_server();

        [[nodiscard]] bool is_ok() const;

        bool bind(const char *local_ip = "0.0.0.0", uint16_t local_port = 8080);

        bool listen(int32_t backlog = SOMAXCONN);

        SOCKET accept(sockaddr *addr, int32_t *addr_len);

        int32_t
        read(SOCKET client_socket, char *buf, int32_t len, int32_t flags = 0);

        int32_t write(SOCKET client_socket,
                      const char *buf,
                      int32_t len,
                      int32_t flags = 0);

        std::string read_string(SOCKET client_socket,
                                int32_t buffer_size = 1024);

        std::string read_string_to_end(SOCKET client_socket);

        int32_t write_string(SOCKET client_socket, std::string &str);

        [[nodiscard]] int32_t err_code() const;

        [[nodiscard]] std::string err_string() const;

        [[nodiscard]] std::wstring err_wstring() const;
    };
} // namespace YanLib::io
#endif // TCP_H
