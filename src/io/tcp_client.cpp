//
// Created by forkernel on 2025/4/5.
//

#include "tcp_client.h"
#include <ws2tcpip.h>
#include "helper/convert.h"

namespace YanLib::io {
    tcp_client::tcp_client(bool active_ipv6) {
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
                                       SOCK_STREAM,
                                       IPPROTO_TCP);
            } else {
                client_socket = socket(AF_INET,
                                       SOCK_STREAM,
                                       IPPROTO_TCP);
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

    bool tcp_client::init_ok() {
        return init_done;
    }

    bool tcp_client::connect(const char *remote_ip, uint16_t remote_port) {
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
            if (::connect(client_socket,
                          reinterpret_cast<sockaddr *>(&addr),
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
            if (::connect(client_socket,
                          reinterpret_cast<sockaddr *>(&addr),
                          sizeof(addr)) == SOCKET_ERROR) {
                error_code = WSAGetLastError();
                return false;
            }
            return true;
        }
    }

    int tcp_client::read(char *buf,
                         int len, int flags) {
        int number_of_bytes = recv(client_socket, buf, len, flags);
        if (number_of_bytes == SOCKET_ERROR) {
            error_code = WSAGetLastError();
        }
        return number_of_bytes;
    }

    int tcp_client::write(const char *buf,
                          int len, int flags) {
        int number_of_bytes = send(client_socket, buf, len, flags);
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
        int bytes_read = read(raw_data.data(), buffer_size);
        if (bytes_read == SOCKET_ERROR) {
            error_code = WSAGetLastError();
            return {};
        }
        raw_data.resize(bytes_read);
        raw_data.shrink_to_fit();
        return raw_data;
    }

    std::wstring tcp_client::read_wstring(int32_t buffer_size) {
        if (buffer_size < 512) {
            buffer_size = 512;
        }
        return helper::convert::str_to_wstr(
            read_string(static_cast<int32_t>(buffer_size * sizeof(wchar_t))));
    }

    std::string tcp_client::read_string_to_end() {
        constexpr unsigned long buffer_size = 4096;
        char *buf = new char[buffer_size];
        memset(buf, 0, buffer_size);
        std::string raw_data;
        raw_data.reserve(buffer_size);
        int bytes_read = 0;
        do {
            bytes_read = read(buf, buffer_size);
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

    std::wstring tcp_client::read_wstring_to_end() {
        return helper::convert::str_to_wstr(read_string_to_end());
    }

    int tcp_client::write_string(std::string &str) {
        if (str.empty()) {
            return 0;
        }
        return write(str.data(), str.size(), 0);
    }

    int tcp_client::write_wstring(std::wstring &wstr) {
        if (wstr.empty()) {
            return 0;
        }
        std::string raw_data = helper::convert::wstr_to_str(wstr);
        return write_string(raw_data);
    }

    int tcp_client::err_code() const {
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
}
