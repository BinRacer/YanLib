//
// Created by forkernel on 2025/4/5.
//

#include "tcp_client.h"
#include <ws2tcpip.h>
#include "../helper/convert.h"

namespace YanLib::io {
    tcp_client::tcp_client(bool activeIpV6) {
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
        } while (false);
    }

    tcp_client::~tcp_client() {
        closesocket(client_socket);
        WSACleanup();
    }

    bool tcp_client::connect(const char *remoteIP, uint16_t remotePort) {
        if (isIPV6) {
            sockaddr_in6 addr{};
            addr.sin6_family = AF_INET6;
            addr.sin6_port = htons(remotePort);
            if (inet_pton(AF_INET6, remoteIP, &addr.sin6_addr) != 1) {
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
            addr.sin_port = htons(remotePort);
            if (inet_pton(AF_INET, remoteIP, &addr.sin_addr) != 1) {
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
        int numberOfBytes = recv(client_socket, buf, len, flags);
        if (numberOfBytes == SOCKET_ERROR) {
            error_code = WSAGetLastError();
        }
        return numberOfBytes;
    }

    int tcp_client::write(const char *buf,
                          int len, int flags) {
        int numberOfBytes = send(client_socket, buf, len, flags);
        if (numberOfBytes == SOCKET_ERROR) {
            error_code = WSAGetLastError();
        }
        return numberOfBytes;
    }

    std::string tcp_client::read_string(int32_t bufferSize) {
        if (bufferSize < 1024) {
            bufferSize = 1024;
        }
        std::string rawData(bufferSize, '\0');
        int bytesRead = read(rawData.data(), bufferSize);
        if (bytesRead == SOCKET_ERROR) {
            error_code = WSAGetLastError();
            return {};
        }
        rawData.resize(bytesRead);
        rawData.shrink_to_fit();
        return rawData;
    }

    std::wstring tcp_client::read_wstring(int32_t bufferSize) {
        if (bufferSize < 512) {
            bufferSize = 512;
        }
        return helper::convert::str_to_wstr(
            read_string(static_cast<int32_t>(bufferSize * sizeof(wchar_t))));
    }

    std::string tcp_client::read_string_to_end() {
        constexpr DWORD bufferSize = 4096;
        char *buf = new char[bufferSize];
        memset(buf, 0, bufferSize);
        std::string rawData;
        rawData.reserve(bufferSize);
        int bytesRead = 0;
        do {
            bytesRead = read(buf, bufferSize);
            if (bytesRead == SOCKET_ERROR) {
                error_code = WSAGetLastError();
                break;
            }
            rawData.insert(rawData.end(),
                           buf,
                           buf + bytesRead);
        } while (bytesRead > 0);
        delete[] buf;
        rawData.shrink_to_fit();
        return rawData;
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
        std::string rawData = helper::convert::wstr_to_str(wstr);
        return write_string(rawData);
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
