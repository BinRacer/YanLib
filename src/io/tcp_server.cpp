//
// Created by forkernel on 2025/4/4.
//

#include "tcp_server.h"
#include <ws2tcpip.h>
#include "../helper/convert.h"

namespace YanLib::io {
    tcp_server::tcp_server(bool activeIpV6) {
        do {
            isIPV6 = activeIpV6;
            error_code = WSAStartup(MAKEWORD(2, 2), &wsaData);
            if (error_code != 0) {
                break;
            }
            if (LOBYTE(wsaData.wVersion) != 2 ||
                HIBYTE(wsaData.wVersion) != 2) {
                break;
            }
            if (activeIpV6) {
                server_socket = socket(AF_INET6,
                                       SOCK_STREAM,
                                       IPPROTO_TCP);
            } else {
                server_socket = socket(AF_INET,
                                       SOCK_STREAM,
                                       IPPROTO_TCP);
            }
            if (server_socket == INVALID_SOCKET) {
                error_code = WSAGetLastError();
                break;
            }
        } while (false);
    }

    tcp_server::~tcp_server() {
        for (const auto &sock: client_sockets) {
            closesocket(sock);
        }
        closesocket(server_socket);
        WSACleanup();
    }

    bool tcp_server::bind(const char *localIP, uint16_t localPort) {
        if (isIPV6) {
            sockaddr_in6 addr{};
            addr.sin6_family = AF_INET6;
            addr.sin6_port = htons(localPort);
            if (inet_pton(AF_INET6, localIP, &addr.sin6_addr) != 1) {
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
            addr.sin_port = htons(localPort);
            if (inet_pton(AF_INET, localIP, &addr.sin_addr) != 1) {
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

    bool tcp_server::listen(int backlog) {
        if (::listen(server_socket, backlog) == SOCKET_ERROR) {
            error_code = WSAGetLastError();
            return false;
        }
        return true;
    }

    SOCKET tcp_server::accept(sockaddr *addr, int *addrlen) {
        SOCKET client_socket = ::accept(server_socket, addr, addrlen);
        if (client_socket == INVALID_SOCKET) {
            error_code = WSAGetLastError();
            return INVALID_SOCKET;
        }
        rwlock.write_lock();
        client_sockets.push_back(client_socket);
        rwlock.write_unlock();
        return client_socket;
    }

    int tcp_server::read(SOCKET client_socket, char *buf,
                         int len, int flags) {
        int numberOfBytes = recv(client_socket, buf, len, flags);
        if (numberOfBytes == SOCKET_ERROR) {
            error_code = WSAGetLastError();
        }
        return numberOfBytes;
    }

    int tcp_server::write(SOCKET client_socket, const char *buf,
                          int len, int flags) {
        int numberOfBytes = send(client_socket, buf, len, flags);
        if (numberOfBytes == SOCKET_ERROR) {
            error_code = WSAGetLastError();
        }
        return numberOfBytes;
    }

    std::string tcp_server::read_string(SOCKET client_socket, int32_t bufferSize) {
        if (bufferSize < 1024) {
            bufferSize = 1024;
        }
        std::string rawData(bufferSize, '\0');
        int bytesRead = read(client_socket, rawData.data(), bufferSize);
        if (bytesRead == SOCKET_ERROR) {
            error_code = WSAGetLastError();
            return {};
        }
        rawData.resize(bytesRead);
        rawData.shrink_to_fit();
        return rawData;
    }

    std::wstring tcp_server::read_wstring(SOCKET client_socket, int32_t bufferSize) {
        if (bufferSize < 512) {
            bufferSize = 512;
        }
        return helper::convert::str_to_wstr(
            read_string(client_socket,
                        static_cast<int32_t>(bufferSize * sizeof(wchar_t))));
    }

    std::string tcp_server::read_string_to_end(SOCKET client_socket) {
        constexpr DWORD bufferSize = 4096;
        char *buf = new char[bufferSize];
        memset(buf, 0, bufferSize);
        std::string rawData;
        rawData.reserve(bufferSize);
        int bytesRead = 0;
        do {
            bytesRead = read(client_socket, buf, bufferSize);
            if (bytesRead == SOCKET_ERROR) {
                error_code = WSAGetLastError();
                break;
            }
            rawData.insert(rawData.end(), buf, buf + bytesRead);
        } while (bytesRead > 0);
        delete[] buf;
        rawData.shrink_to_fit();
        return rawData;
    }

    std::wstring tcp_server::read_wstring_to_end(SOCKET client_socket) {
        return helper::convert::str_to_wstr(read_string_to_end(client_socket));
    }

    int tcp_server::write_string(SOCKET client_socket, std::string &str) {
        if (str.empty()) {
            return 0;
        }
        return write(client_socket, str.data(), str.size(), 0);
    }

    int tcp_server::write_wstring(SOCKET client_socket, std::wstring &wstr) {
        if (wstr.empty()) {
            return 0;
        }
        std::string rawData = helper::convert::wstr_to_str(wstr);
        return write_string(client_socket, rawData);
    }

    int tcp_server::err_code() const {
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
}
