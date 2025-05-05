//
// Created by forkernel on 2025/4/5.
//

#include "udp_server.h"
#include <ws2tcpip.h>
#include "helper/convert.h"

namespace YanLib::io {
    udp_server::udp_server(bool active_ipv6) {
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
                server_socket = socket(AF_INET6,
                                       SOCK_DGRAM,
                                       IPPROTO_UDP);
            } else {
                server_socket = socket(AF_INET,
                                       SOCK_DGRAM,
                                       IPPROTO_UDP);
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

    bool udp_server::init_ok() {
        return init_done;
    }

    bool udp_server::bind(const char *local_ip,
                          uint16_t local_port) {
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
            if (::bind(server_socket,
                       reinterpret_cast<sockaddr *>(&addr),
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
            if (::bind(server_socket,
                       reinterpret_cast<sockaddr *>(&addr),
                       sizeof(addr)) == SOCKET_ERROR) {
                error_code = WSAGetLastError();
                return false;
            }
            return true;
        }
    }

    int32_t udp_server::read(char *buf, int32_t len,
                         int32_t flags,
                         sockaddr *from, int32_t *fromlen) {
        int32_t number_of_bytes = recvfrom(server_socket,
                                       buf, len,
                                       flags,
                                       from, fromlen);
        if (number_of_bytes == SOCKET_ERROR) {
            error_code = WSAGetLastError();
        }
        return number_of_bytes;
    }

    int32_t udp_server::write(const char *buf, int32_t len,
                          int32_t flags,
                          const sockaddr *to, int32_t tolen) {
        int32_t number_of_bytes = sendto(server_socket,
                                     buf, len,
                                     flags,
                                     to, tolen);
        if (number_of_bytes == SOCKET_ERROR) {
            error_code = WSAGetLastError();
        }
        return number_of_bytes;
    }

    int32_t udp_server::read(char *buf, int32_t len,
                         std::string &client_ip,
                         uint16_t &client_port) {
        if (is_ipv6) {
            sockaddr_in6 client_addr{};
            int32_t client_size = sizeof (client_addr);
            int32_t number_of_bytes = recvfrom(server_socket,
                                           buf, len,
                                           0,
                                           reinterpret_cast<sockaddr *>(
                                               &client_addr), &client_size);
            if (number_of_bytes == SOCKET_ERROR) {
                error_code = WSAGetLastError();
            } else {
                if (!inet_ntop(AF_INET6,
                               &client_addr.sin6_addr,
                               client_ip.data(),
                               INET6_ADDRSTRLEN)) {
                    error_code = WSAGetLastError();
                }
                client_port = ntohs(client_addr.sin6_port);
            }
            return number_of_bytes;
        } else {
            sockaddr_in client_addr{};
            int32_t client_size = sizeof (client_addr);
            int32_t number_of_bytes = recvfrom(server_socket,
                                           buf,
                                           len,
                                           0,
                                           reinterpret_cast<sockaddr *>(
                                               &client_addr),
                                           &client_size);
            if (number_of_bytes == SOCKET_ERROR) {
                error_code = WSAGetLastError();
            } else {
                if (!inet_ntop(AF_INET,
                               &client_addr.sin_addr,
                               client_ip.data(),
                               INET_ADDRSTRLEN)) {
                    error_code = WSAGetLastError();
                }
                client_port = ntohs(client_addr.sin_port);
            }
            return number_of_bytes;
        }
    }

    int32_t udp_server::write(char *buf, int32_t len,
                          std::string &client_ip,
                          uint16_t &client_port) {
        if (is_ipv6) {
            sockaddr_in6 addr{};
            addr.sin6_family = AF_INET6;
            addr.sin6_port = htons(client_port);
            if (inet_pton(AF_INET6,
                          client_ip.data(),
                          &addr.sin6_addr) != 1) {
                error_code = WSAGetLastError();
            }
            int32_t number_of_bytes = sendto(server_socket,
                                         buf,
                                         len,
                                         0,
                                         reinterpret_cast<sockaddr *>(&addr),
                                         sizeof(addr));
            if (number_of_bytes == SOCKET_ERROR) {
                error_code = WSAGetLastError();
            }
            return number_of_bytes;
        } else {
            sockaddr_in addr{};
            addr.sin_family = AF_INET;
            addr.sin_port = htons(client_port);
            if (inet_pton(AF_INET,
                          client_ip.data(),
                          &addr.sin_addr) != 1) {
                error_code = WSAGetLastError();
            }
            int32_t number_of_bytes = sendto(server_socket,
                                         buf, len,
                                         0,
                                         reinterpret_cast<sockaddr *>(&addr),
                                         sizeof(addr));
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
        int32_t bytes_read = read(raw_data.data(),
                              buffer_size,
                              client_ip,
                              client_port);
        if (bytes_read == SOCKET_ERROR) {
            error_code = WSAGetLastError();
            return {};
        }
        raw_data.resize(bytes_read);
        raw_data.shrink_to_fit();
        return raw_data;
    }

    std::wstring udp_server::read_wstring(std::string &client_ip,
                                          uint16_t &client_port,
                                          int32_t buffer_size) {
        if (buffer_size < 512) {
            buffer_size = 512;
        }
        return helper::convert::str_to_wstr(
            read_string(client_ip, client_port,
                        static_cast<int32_t>(buffer_size * sizeof(wchar_t))));
    }

    std::string udp_server::read_string_to_end(std::string &client_ip,
                                               uint16_t &client_port) {
        constexpr unsigned long buffer_size = 4096;
        char *buf = new char[buffer_size];
        memset(buf, 0, buffer_size);
        std::string raw_data;
        raw_data.reserve(buffer_size);
        int32_t bytes_read = 0;
        do {
            bytes_read = read(buf,
                              buffer_size,
                              client_ip,
                              client_port);
            if (bytes_read == SOCKET_ERROR) {
                error_code = WSAGetLastError();
                break;
            }
            raw_data.insert(raw_data.end(),
                            buf,
                            buf + bytes_read);
        } while (bytes_read > 0);
        delete[] buf;
        raw_data.shrink_to_fit();
        return raw_data;
    }

    std::wstring udp_server::read_wstring_to_end(std::string &client_ip,
                                                 uint16_t &client_port) {
        return helper::convert::str_to_wstr(
            read_string_to_end(client_ip, client_port));
    }

    int32_t udp_server::write_string(std::string &str,
                                 std::string &client_ip,
                                 uint16_t &client_port) {
        if (str.empty()) {
            return 0;
        }
        return write(str.data(), str.size(), client_ip, client_port);
    }

    int32_t udp_server::write_wstring(std::wstring &wstr,
                                  std::string &client_ip,
                                  uint16_t &client_port) {
        if (wstr.empty()) {
            return 0;
        }
        std::string raw_data = helper::convert::wstr_to_str(wstr);
        return write_string(raw_data, client_ip, client_port);
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
}
