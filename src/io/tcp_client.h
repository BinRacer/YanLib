/* clang-format off */
/*
 * @file tcp_client.h
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
#ifndef TCP_CLIENT_H
#define TCP_CLIENT_H
#include <winsock2.h>
#include <string>
#include <vector>
#pragma comment(lib, "WS2_32.Lib")
namespace YanLib::io {
    class tcp_client {
    private:
        WSADATA wsa_data = {};
        volatile bool is_ipv6 = false;
        SOCKET client_socket = INVALID_SOCKET;
        volatile bool init_done = false;
        int32_t error_code = 0;

        tcp_client() = default;

    public:
        tcp_client(const tcp_client &other) = delete;

        tcp_client(tcp_client &&other) = delete;

        tcp_client &operator=(const tcp_client &other) = delete;

        tcp_client &operator=(tcp_client &&other) = delete;

        explicit tcp_client(bool active_ipv6 = false);

        ~tcp_client();

        [[nodiscard]] bool is_ok() const;

        bool connect(const char *remote_ip = "127.0.0.1",
                     uint16_t remote_port = 8080);

        int32_t read(char *buf, int32_t len, int32_t flags = 0);

        int32_t write(const char *buf, int32_t len, int32_t flags = 0);

        std::string read_string(int32_t buffer_size = 1024);

        std::string read_string_to_end();

        int32_t write_string(const std::string &str);

        [[nodiscard]] int32_t err_code() const;

        [[nodiscard]] std::string err_string() const;

        [[nodiscard]] std::wstring err_wstring() const;
    };
} // namespace YanLib::io
#endif // TCP_CLIENT_H
