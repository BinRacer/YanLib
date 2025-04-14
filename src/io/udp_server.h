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
        WSADATA wsaData{};
        volatile bool isIPV6 = false;
        SOCKET server_socket{};
        int error_code{};

        udp_server() = default;

    public:
        udp_server(const udp_server &other) = delete;

        udp_server(udp_server &&other) = delete;

        udp_server &operator=(const udp_server &other) = delete;

        udp_server &operator=(udp_server &&other) = delete;

        explicit udp_server(bool activeIpV6 = false);

        ~udp_server();

        bool bind(const char *localIP = "0.0.0.0",
                  uint16_t localPort = 8080);

        int read(char *buf, int len,
                 int flags,
                 sockaddr *from, int *fromlen);

        int write(const char *buf, int len,
                  int flags,
                  const sockaddr *to, int tolen);

        int read(char *buf, int len,
                 std::string &clientIP, uint16_t &clientPort);

        int write(char *buf, int len,
                  std::string &clientIP, uint16_t &clientPort);

        std::string read_string(std::string &clientIP,
                                uint16_t &clientPort,
                                int32_t bufferSize = 1024);

        std::wstring read_wstring(std::string &clientIP,
                                  uint16_t &clientPort,
                                  int32_t bufferSize = 512);

        std::string read_string_to_end(std::string &clientIP,
                                       uint16_t &clientPort);

        std::wstring read_wstring_to_end(std::string &clientIP,
                                         uint16_t &clientPort);

        int write_string(std::string &str, std::string &clientIP,
                         uint16_t &clientPort);

        int write_wstring(std::wstring &wstr, std::string &clientIP,
                          uint16_t &clientPort);

        int err_code() const;

        std::string err_string() const;

        std::wstring err_wstring() const;
    };
}
#endif //UDP_SERVER_H
