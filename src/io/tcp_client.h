//
// Created by forkernel on 2025/4/5.
//

#ifndef TCP_CLIENT_H
#define TCP_CLIENT_H
#include <winsock2.h>
#include <string>
#include <vector>

#pragma comment(lib, "ws2_32.lib")
namespace YanLib::io {
    class tcp_client {
    private:
        WSADATA wsa_data{};
        volatile bool is_ipv6 = false;
        SOCKET client_socket{};
        int error_code{};

        tcp_client() = default;

    public:
        tcp_client(const tcp_client &other) = delete;

        tcp_client(tcp_client &&other) = delete;

        tcp_client &operator=(const tcp_client &other) = delete;

        tcp_client &operator=(tcp_client &&other) = delete;

        explicit tcp_client(bool active_ipv6 = false);

        ~tcp_client();

        bool connect(const char *remote_ip = "127.0.0.1",
                     uint16_t remote_port = 8080);

        int read(char *buf, int len, int flags = 0);

        int write(const char *buf, int len, int flags = 0);

        std::string read_string(int32_t buffer_size = 1024);

        std::wstring read_wstring(int32_t buffer_size = 512);

        std::string read_string_to_end();

        std::wstring read_wstring_to_end();

        int write_string(std::string &str);

        int write_wstring(std::wstring &wstr);

        [[nodiscard]] int err_code() const;

        [[nodiscard]] std::string err_string() const;

        [[nodiscard]] std::wstring err_wstring() const;
    };
}
#endif //TCP_CLIENT_H
