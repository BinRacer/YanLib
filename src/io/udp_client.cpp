//
// Created by forkernel on 2025/4/5.
//

#include "udp_client.h"
#include <ws2tcpip.h>
#include "helper/convert.h"

namespace YanLib::io {
    udp_client::udp_client(bool active_ipv6) {
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
                client_socket = socket(AF_INET6,
                                       SOCK_DGRAM,
                                       IPPROTO_UDP);
            } else {
                client_socket = socket(AF_INET,
                                       SOCK_DGRAM,
                                       IPPROTO_UDP);
            }
            if (client_socket == INVALID_SOCKET) {
                error_code = WSAGetLastError();
                break;
            }
            init_done = true;
        } while (false);
        init_done = false;
    }

    udp_client::~udp_client() {
        closesocket(client_socket);
        client_socket = INVALID_SOCKET;
        WSACleanup();
    }

    bool udp_client::init_ok() {
        return init_done;
    }

    int32_t udp_client::read(char *buf, int32_t len,
                         int32_t flags,
                         sockaddr *from, int32_t *fromlen) {
        int32_t number_of_bytes = recvfrom(client_socket,
                                       buf, len,
                                       flags,
                                       from, fromlen);
        if (number_of_bytes == SOCKET_ERROR) {
            error_code = WSAGetLastError();
        }
        return number_of_bytes;
    }

    int32_t udp_client::write(const char *buf, int32_t len,
                          int32_t flags,
                          const sockaddr *to, int32_t tolen) {
        int32_t number_of_bytes = sendto(client_socket,
                                     buf, len,
                                     flags,
                                     to, tolen);
        if (number_of_bytes == SOCKET_ERROR) {
            error_code = WSAGetLastError();
        }
        return number_of_bytes;
    }

    int32_t udp_client::read(char *buf, int32_t len,
                         std::string &remote_ip, uint16_t &remote_port) {
        if (is_ipv6) {
            sockaddr_in6 client_addr{};
            int32_t client_size = sizeof (client_addr);
            int32_t number_of_bytes = recvfrom(client_socket,
                                           buf, len,
                                           0,
                                           reinterpret_cast<sockaddr *>(&client_addr),
                                           &client_size);
            if (number_of_bytes == SOCKET_ERROR) {
                error_code = WSAGetLastError();
            } else {
                if (!inet_ntop(AF_INET6,
                               &client_addr.sin6_addr,
                               remote_ip.data(),
                               INET6_ADDRSTRLEN)) {
                    error_code = WSAGetLastError();
                }
                remote_port = ntohs(client_addr.sin6_port);
            }
            return number_of_bytes;
        } else {
            sockaddr_in client_addr{};
            int32_t client_size = sizeof (client_addr);
            int32_t number_of_bytes = recvfrom(client_socket,
                                           buf, len,
                                           0,
                                           reinterpret_cast<sockaddr *>(&client_addr),
                                           &client_size);
            if (number_of_bytes == SOCKET_ERROR) {
                error_code = WSAGetLastError();
            } else {
                if (!inet_ntop(AF_INET,
                               &client_addr.sin_addr,
                               remote_ip.data(),
                               INET_ADDRSTRLEN)) {
                    error_code = WSAGetLastError();
                }
                remote_port = ntohs(client_addr.sin_port);
            }
            return number_of_bytes;
        }
    }

    int32_t udp_client::write(char *buf, int32_t len,
                          std::string &remote_ip, uint16_t &remote_port) {
        if (is_ipv6) {
            sockaddr_in6 addr{};
            addr.sin6_family = AF_INET6;
            addr.sin6_port = htons(remote_port);
            if (inet_pton(AF_INET6,
                          remote_ip.data(),
                          &addr.sin6_addr) != 1) {
                error_code = WSAGetLastError();
            }
            int32_t number_of_bytes = sendto(client_socket,
                                         buf, len,
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
            addr.sin_port = htons(remote_port);
            if (inet_pton(AF_INET,
                          remote_ip.data(),
                          &addr.sin_addr) != 1) {
                error_code = WSAGetLastError();
            }
            int32_t number_of_bytes = sendto(client_socket,
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

    std::string udp_client::read_string(std::string &remote_ip,
                                        uint16_t &remote_port,
                                        int32_t buffer_size) {
        if (buffer_size < 1024) {
            buffer_size = 1024;
        }
        std::string raw_data(buffer_size, '\0');
        int32_t bytes_read = read(raw_data.data(), buffer_size, remote_ip, remote_port);
        if (bytes_read == SOCKET_ERROR) {
            error_code = WSAGetLastError();
            return {};
        }
        raw_data.resize(bytes_read);
        raw_data.shrink_to_fit();
        return raw_data;
    }

    std::wstring udp_client::read_wstring(std::string &remote_ip,
                                          uint16_t &remote_port,
                                          int32_t buffer_size) {
        if (buffer_size < 512) {
            buffer_size = 512;
        }
        return helper::convert::str_to_wstr(
            read_string(remote_ip, remote_port,
                        static_cast<int32_t>(buffer_size * sizeof(wchar_t))));
    }

    std::string udp_client::read_string_to_end(std::string &remote_ip,
                                               uint16_t &remote_port) {
        constexpr unsigned long buffer_size = 4096;
        char *buf = new char[buffer_size];
        memset(buf, 0, buffer_size);
        std::string raw_data;
        raw_data.reserve(buffer_size);
        int32_t bytes_read = 0;
        do {
            bytes_read = read(buf, buffer_size, remote_ip, remote_port);
            if (bytes_read == SOCKET_ERROR) {
                error_code = WSAGetLastError();
                break;
            }
            raw_data.insert(raw_data.end(), buf, buf + bytes_read);
        } while (bytes_read > 0);
        delete[] buf;
        raw_data.shrink_to_fit();
        return raw_data;
    }

    std::wstring udp_client::read_wstring_to_end(std::string &remote_ip,
                                                 uint16_t &remote_port) {
        return helper::convert::str_to_wstr(
            read_string_to_end(remote_ip, remote_port));
    }

    int32_t udp_client::write_string(std::string &str,
                                 std::string &remote_ip, uint16_t &remote_port) {
        if (str.empty()) {
            return 0;
        }
        return write(str.data(), str.size(), remote_ip, remote_port);
    }

    int32_t udp_client::write_wstring(std::wstring &wstr,
                                  std::string &remote_ip, uint16_t &remote_port) {
        if (wstr.empty()) {
            return 0;
        }
        std::string raw_data = helper::convert::wstr_to_str(wstr);
        return write_string(raw_data, remote_ip, remote_port);
    }

    int32_t udp_client::err_code() const {
        return error_code;
    }

    std::string udp_client::err_string() const {
        std::string result = helper::convert::err_string(error_code);
        return result;
    }

    std::wstring udp_client::err_wstring() const {
        std::wstring result = helper::convert::err_wstring(error_code);
        return result;
    }
}
