/* clang-format off */
/*
 * @file udp_server.h
 * @date 2025-04-05
 * @license MIT License
 *
 * Copyright (c) 2025 BinRacer <native.lab@outlook.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
/* clang-format on */
#ifndef UDP_SERVER_H
#define UDP_SERVER_H
#include <WinSock2.h>
#include <string>
#pragma comment(lib, "WS2_32.Lib")
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

        bool bind(const char *local_ip = "0.0.0.0", uint16_t local_port = 8080);

        int32_t read(char *buf,
                     int32_t len,
                     int32_t flags,
                     sockaddr *from,
                     int32_t *from_len);

        int32_t write(const char *buf,
                      int32_t len,
                      int32_t flags,
                      const sockaddr *to,
                      int32_t to_len);

        int32_t read(char *buf,
                     int32_t len,
                     std::string &client_ip,
                     uint16_t &client_port);

        int32_t write(const char *buf,
                      int32_t len,
                      const std::string &client_ip,
                      const uint16_t &client_port);

        std::string read_string(std::string &client_ip,
                                uint16_t &client_port,
                                int32_t buffer_size = 1024);

        std::string read_string_to_end(std::string &client_ip,
                                       uint16_t &client_port);

        int32_t write_string(const std::string &str,
                             const std::string &client_ip,
                             const uint16_t &client_port);

        [[nodiscard]] int32_t err_code() const;

        [[nodiscard]] std::string err_string() const;

        [[nodiscard]] std::wstring err_wstring() const;
    };
} // namespace YanLib::io
#endif // UDP_SERVER_H
