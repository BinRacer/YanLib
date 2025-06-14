/* clang-format off */
/*
 * @file udp_server.cpp
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
#include "udp_server.h"
#include <ws2tcpip.h>
#include "helper/convert.h"

namespace YanLib::io {
    udp_server::udp_server(const bool active_ipv6) {
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
                server_socket = socket(AF_INET6, SOCK_DGRAM, IPPROTO_UDP);
            } else {
                server_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
            }
            if (server_socket == INVALID_SOCKET) {
                error_code = WSAGetLastError();
                break;
            }
            init_done = true;
        } while (false);
        init_done = false;
    }

    udp_server::~udp_server() {
        closesocket(server_socket);
        server_socket = INVALID_SOCKET;
        WSACleanup();
    }

    bool udp_server::init_ok() const {
        return init_done;
    }

    bool udp_server::bind(const char *local_ip, const uint16_t local_port) {
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

    int32_t udp_server::read(char *buf,
                             int32_t len,
                             int32_t flags,
                             sockaddr *from,
                             int32_t *from_len) {
        const int32_t number_of_bytes =
                recvfrom(server_socket, buf, len, flags, from, from_len);
        if (number_of_bytes == SOCKET_ERROR) {
            error_code = WSAGetLastError();
        }
        return number_of_bytes;
    }

    int32_t udp_server::write(const char *buf,
                              int32_t len,
                              int32_t flags,
                              const sockaddr *to,
                              int32_t to_len) {
        const int32_t number_of_bytes =
                sendto(server_socket, buf, len, flags, to, to_len);
        if (number_of_bytes == SOCKET_ERROR) {
            error_code = WSAGetLastError();
        }
        return number_of_bytes;
    }

    int32_t udp_server::read(char *buf,
                             int32_t len,
                             std::string &client_ip,
                             uint16_t &client_port) {
        if (is_ipv6) {
            sockaddr_in6 client_addr{};
            int32_t client_size = sizeof(client_addr);
            const int32_t number_of_bytes =
                    recvfrom(server_socket, buf, len, 0,
                             reinterpret_cast<sockaddr *>(&client_addr),
                             &client_size);
            if (number_of_bytes == SOCKET_ERROR) {
                error_code = WSAGetLastError();
            } else {
                if (!inet_ntop(AF_INET6, &client_addr.sin6_addr,
                               client_ip.data(), INET6_ADDRSTRLEN)) {
                    error_code = WSAGetLastError();
                }
                client_port = ntohs(client_addr.sin6_port);
            }
            return number_of_bytes;
        } else {
            sockaddr_in client_addr{};
            int32_t client_size = sizeof(client_addr);
            const int32_t number_of_bytes =
                    recvfrom(server_socket, buf, len, 0,
                             reinterpret_cast<sockaddr *>(&client_addr),
                             &client_size);
            if (number_of_bytes == SOCKET_ERROR) {
                error_code = WSAGetLastError();
            } else {
                if (!inet_ntop(AF_INET, &client_addr.sin_addr, client_ip.data(),
                               INET_ADDRSTRLEN)) {
                    error_code = WSAGetLastError();
                }
                client_port = ntohs(client_addr.sin_port);
            }
            return number_of_bytes;
        }
    }

    int32_t udp_server::write(const char *buf,
                              int32_t len,
                              const std::string &client_ip,
                              const uint16_t &client_port) {
        if (is_ipv6) {
            sockaddr_in6 addr{};
            addr.sin6_family = AF_INET6;
            addr.sin6_port = htons(client_port);
            if (inet_pton(AF_INET6, client_ip.data(), &addr.sin6_addr) != 1) {
                error_code = WSAGetLastError();
            }
            const int32_t number_of_bytes =
                    sendto(server_socket, buf, len, 0,
                           reinterpret_cast<sockaddr *>(&addr), sizeof(addr));
            if (number_of_bytes == SOCKET_ERROR) {
                error_code = WSAGetLastError();
            }
            return number_of_bytes;
        } else {
            sockaddr_in addr{};
            addr.sin_family = AF_INET;
            addr.sin_port = htons(client_port);
            if (inet_pton(AF_INET, client_ip.data(), &addr.sin_addr) != 1) {
                error_code = WSAGetLastError();
            }
            const int32_t number_of_bytes =
                    sendto(server_socket, buf, len, 0,
                           reinterpret_cast<sockaddr *>(&addr), sizeof(addr));
            if (number_of_bytes == SOCKET_ERROR) {
                error_code = WSAGetLastError();
            }
            return number_of_bytes;
        }
    }

    std::string udp_server::read_string(std::string &client_ip,
                                        uint16_t &client_port,
                                        int32_t buffer_size) {
        if (buffer_size < 1024) {
            buffer_size = 1024;
        }
        std::string raw_data(buffer_size, '\0');
        const int32_t bytes_read =
                read(raw_data.data(), buffer_size, client_ip, client_port);
        if (bytes_read == SOCKET_ERROR) {
            error_code = WSAGetLastError();
            return {};
        }
        raw_data.resize(bytes_read);
        raw_data.shrink_to_fit();
        return raw_data;
    }

    std::string udp_server::read_string_to_end(std::string &client_ip,
                                               uint16_t &client_port) {
        constexpr uint32_t buffer_size = 4096;
        std::string buf(buffer_size, '\0');
        std::string raw_data;
        raw_data.reserve(buffer_size);
        int32_t bytes_read = 0;
        do {
            bytes_read = read(buf.data(), buffer_size, client_ip, client_port);
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

    int32_t udp_server::write_string(const std::string &str,
                                     const std::string &client_ip,
                                     const uint16_t &client_port) {
        if (str.empty()) {
            return 0;
        }
        return write(str.data(), static_cast<int32_t>(str.size()), client_ip,
                     client_port);
    }

    int32_t udp_server::err_code() const {
        return error_code;
    }

    std::string udp_server::err_string() const {
        std::string result = helper::convert::err_string(error_code);
        return result;
    }

    std::wstring udp_server::err_wstring() const {
        std::wstring result = helper::convert::err_wstring(error_code);
        return result;
    }
} // namespace YanLib::io
