/* clang-format off */
/*
 * @file tcp_server.cpp
 * @date 2025-04-04
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
#include "tcp_server.h"
#include <ws2tcpip.h>
#include "helper/convert.h"

namespace YanLib::io {
    tcp_server::tcp_server(const bool active_ipv6) {
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
                server_socket = socket(AF_INET6, SOCK_STREAM, IPPROTO_TCP);
            } else {
                server_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
            }
            if (server_socket == INVALID_SOCKET) {
                error_code = WSAGetLastError();
                break;
            }
            init_done = true;
        } while (false);
        init_done = false;
    }

    tcp_server::~tcp_server() {
        for (auto &sock : client_sockets) {
            closesocket(sock);
            sock = INVALID_SOCKET;
        }
        closesocket(server_socket);
        server_socket = INVALID_SOCKET;
        WSACleanup();
    }

    bool tcp_server::is_ok() const {
        return init_done;
    }

    bool tcp_server::bind(const char *local_ip, const uint16_t local_port) {
        if (!init_done) {
            return false;
        }
        if (is_ipv6) {
            sockaddr_in6 addr{};
            addr.sin6_family = AF_INET6;
            addr.sin6_port = htons(local_port);
            if (inet_pton(AF_INET6, local_ip, &addr.sin6_addr) != 1) {
                error_code = WSAGetLastError();
                return false;
            }
            if (::bind(server_socket, reinterpret_cast<sockaddr *>(&addr),
                       sizeof(addr)) == SOCKET_ERROR) {
                error_code = WSAGetLastError();
                return false;
            }
            return true;
        } else {
            sockaddr_in addr{};
            addr.sin_family = AF_INET;
            addr.sin_port = htons(local_port);
            if (inet_pton(AF_INET, local_ip, &addr.sin_addr) != 1) {
                error_code = WSAGetLastError();
                return false;
            }
            if (::bind(server_socket, reinterpret_cast<sockaddr *>(&addr),
                       sizeof(addr)) == SOCKET_ERROR) {
                error_code = WSAGetLastError();
                return false;
            }
            return true;
        }
    }

    bool tcp_server::listen(const int32_t backlog) {
        if (!init_done) {
            return false;
        }
        if (::listen(server_socket, backlog) == SOCKET_ERROR) {
            error_code = WSAGetLastError();
            return false;
        }
        return true;
    }

    SOCKET tcp_server::accept(sockaddr *addr, int32_t *addr_len) {
        if (!init_done) {
            return INVALID_SOCKET;
        }
        const SOCKET client_socket = ::accept(server_socket, addr, addr_len);
        if (client_socket == INVALID_SOCKET) {
            error_code = WSAGetLastError();
            return INVALID_SOCKET;
        }
        rwlock.write_lock();
        client_sockets.push_back(client_socket);
        rwlock.write_unlock();
        return client_socket;
    }

    int32_t tcp_server::read(SOCKET client_socket,
                             char *buf,
                             int32_t len,
                             const int32_t flags) {
        const int32_t number_of_bytes = recv(client_socket, buf, len, flags);
        if (number_of_bytes == SOCKET_ERROR) {
            error_code = WSAGetLastError();
        }
        return number_of_bytes;
    }

    int32_t tcp_server::write(SOCKET client_socket,
                              const char *buf,
                              int32_t len,
                              const int32_t flags) {
        const int32_t number_of_bytes = send(client_socket, buf, len, flags);
        if (number_of_bytes == SOCKET_ERROR) {
            error_code = WSAGetLastError();
        }
        return number_of_bytes;
    }

    std::string tcp_server::read_string(SOCKET client_socket,
                                        int32_t buffer_size) {
        if (buffer_size < 1024) {
            buffer_size = 1024;
        }
        std::string raw_data(buffer_size, '\0');
        const int32_t bytes_read =
                read(client_socket, raw_data.data(), buffer_size);
        if (bytes_read == SOCKET_ERROR) {
            error_code = WSAGetLastError();
            return {};
        }
        raw_data.resize(bytes_read);
        raw_data.shrink_to_fit();
        return raw_data;
    }

    std::string tcp_server::read_string_to_end(SOCKET client_socket) {
        constexpr uint32_t buffer_size = 4096;
        std::string buf(buffer_size, '\0');
        std::string raw_data;
        raw_data.reserve(buffer_size);
        int32_t bytes_read = 0;
        do {
            bytes_read = read(client_socket, buf.data(), buffer_size);
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

    int32_t tcp_server::write_string(SOCKET client_socket,
                                     const std::string &str) {
        if (str.empty()) {
            return 0;
        }
        return write(client_socket, str.data(),
                     static_cast<int32_t>(str.size()), 0);
    }

    int32_t tcp_server::err_code() const {
        return error_code;
    }

    std::string tcp_server::err_string() const {
        std::string result = helper::convert::err_string(error_code);
        return result;
    }

    std::wstring tcp_server::err_wstring() const {
        std::wstring result = helper::convert::err_wstring(error_code);
        return result;
    }
} // namespace YanLib::io
