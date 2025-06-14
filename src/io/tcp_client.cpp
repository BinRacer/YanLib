/* clang-format off */
/*
 * @file tcp_client.cpp
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
#include "tcp_client.h"
#include <ws2tcpip.h>
#include "helper/convert.h"

namespace YanLib::io {
    tcp_client::tcp_client(const bool active_ipv6) {
        do {
            is_ipv6 = active_ipv6;
            error_code = WSAStartup(MAKEWORD(2, 2), &wsa_data);
            if (error_code != 0) {
                break;
            }
            if (LOBYTE(wsa_data.wVersion) != 2 ||
                HIBYTE(wsa_data.wVersion) != 2) {
                break;
            }
            if (active_ipv6) {
                client_socket = socket(AF_INET6, SOCK_STREAM, IPPROTO_TCP);
            } else {
                client_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
            }
            if (client_socket == INVALID_SOCKET) {
                error_code = WSAGetLastError();
                break;
            }
            init_done = true;
        } while (false);
        init_done = false;
    }

    tcp_client::~tcp_client() {
        closesocket(client_socket);
        client_socket = INVALID_SOCKET;
        WSACleanup();
    }

    bool tcp_client::is_ok() const {
        return init_done;
    }

    bool tcp_client::connect(const char *remote_ip,
                             const uint16_t remote_port) {
        if (!init_done) {
            return false;
        }
        if (is_ipv6) {
            sockaddr_in6 addr{};
            addr.sin6_family = AF_INET6;
            addr.sin6_port = htons(remote_port);
            if (inet_pton(AF_INET6, remote_ip, &addr.sin6_addr) != 1) {
                error_code = WSAGetLastError();
                return false;
            }
            if (::connect(client_socket, reinterpret_cast<sockaddr *>(&addr),
                          sizeof(addr)) == SOCKET_ERROR) {
                error_code = WSAGetLastError();
                return false;
            }
            return true;
        } else {
            sockaddr_in addr{};
            addr.sin_family = AF_INET;
            addr.sin_port = htons(remote_port);
            if (inet_pton(AF_INET, remote_ip, &addr.sin_addr) != 1) {
                error_code = WSAGetLastError();
                return false;
            }
            if (::connect(client_socket, reinterpret_cast<sockaddr *>(&addr),
                          sizeof(addr)) == SOCKET_ERROR) {
                error_code = WSAGetLastError();
                return false;
            }
            return true;
        }
    }

    int32_t tcp_client::read(char *buf, int32_t len, const int32_t flags) {
        const int32_t number_of_bytes = recv(client_socket, buf, len, flags);
        if (number_of_bytes == SOCKET_ERROR) {
            error_code = WSAGetLastError();
        }
        return number_of_bytes;
    }

    int32_t
    tcp_client::write(const char *buf, int32_t len, const int32_t flags) {
        const int32_t number_of_bytes = send(client_socket, buf, len, flags);
        if (number_of_bytes == SOCKET_ERROR) {
            error_code = WSAGetLastError();
        }
        return number_of_bytes;
    }

    std::string tcp_client::read_string(int32_t buffer_size) {
        if (buffer_size < 1024) {
            buffer_size = 1024;
        }
        std::string raw_data(buffer_size, '\0');
        const int32_t bytes_read = read(raw_data.data(), buffer_size);
        if (bytes_read == SOCKET_ERROR) {
            error_code = WSAGetLastError();
            return {};
        }
        raw_data.resize(bytes_read);
        raw_data.shrink_to_fit();
        return raw_data;
    }

    std::string tcp_client::read_string_to_end() {
        constexpr uint32_t buffer_size = 4096;
        std::string buf(buffer_size, '\0');
        std::string raw_data;
        raw_data.reserve(buffer_size);
        int32_t bytes_read = 0;
        do {
            bytes_read = read(buf.data(), buffer_size);
            if (bytes_read == SOCKET_ERROR) {
                error_code = WSAGetLastError();
                break;
            }
            raw_data.insert(raw_data.end(), buf.data(),
                            buf.data() + bytes_read);
        } while (bytes_read > 0);
        raw_data.shrink_to_fit();
        return raw_data;
    }

    int32_t tcp_client::write_string(const std::string &str) {
        if (str.empty()) {
            return 0;
        }
        return write(str.data(), static_cast<int32_t>(str.size()), 0);
    }

    int32_t tcp_client::err_code() const {
        return error_code;
    }

    std::string tcp_client::err_string() const {
        std::string result = helper::convert::err_string(error_code);
        return result;
    }

    std::wstring tcp_client::err_wstring() const {
        std::wstring result = helper::convert::err_wstring(error_code);
        return result;
    }
} // namespace YanLib::io
