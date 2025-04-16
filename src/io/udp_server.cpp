//
// Created by forkernel on 2025/4/5.
//

#include "udp_server.h"
#include <ws2tcpip.h>
#include "helper/convert.h"

namespace YanLib::io {
    udp_server::udp_server(bool activeIpV6) {
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
        } while (false);
    }

    udp_server::~udp_server() {
        closesocket(server_socket);
        WSACleanup();
    }

    bool udp_server::bind(const char *localIP,
                          uint16_t localPort) {
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

    int udp_server::read(char *buf, int len,
                         int flags,
                         sockaddr *from, int *fromlen) {
        int numberOfBytes = recvfrom(server_socket,
                                     buf, len,
                                     flags,
                                     from, fromlen);
        if (numberOfBytes == SOCKET_ERROR) {
            error_code = WSAGetLastError();
        }
        return numberOfBytes;
    }

    int udp_server::write(const char *buf, int len,
                          int flags,
                          const sockaddr *to, int tolen) {
        int numberOfBytes = sendto(server_socket,
                                   buf, len,
                                   flags,
                                   to, tolen);
        if (numberOfBytes == SOCKET_ERROR) {
            error_code = WSAGetLastError();
        }
        return numberOfBytes;
    }

    int udp_server::read(char *buf, int len,
                         std::string &clientIP,
                         uint16_t &clientPort) {
        if (isIPV6) {
            sockaddr_in6 client_addr{};
            int client_size = sizeof (client_addr);
            int numberOfBytes = recvfrom(server_socket,
                                         buf, len,
                                         0,
                                         reinterpret_cast<sockaddr *>(&client_addr), &client_size);
            if (numberOfBytes == SOCKET_ERROR) {
                error_code = WSAGetLastError();
            } else {
                if (!inet_ntop(AF_INET6,
                               &client_addr.sin6_addr,
                               clientIP.data(),
                               INET6_ADDRSTRLEN)) {
                    error_code = WSAGetLastError();
                }
                clientPort = ntohs(client_addr.sin6_port);
            }
            return numberOfBytes;
        } else {
            sockaddr_in client_addr{};
            int client_size = sizeof (client_addr);
            int numberOfBytes = recvfrom(server_socket,
                                         buf, len,
                                         0,
                                         reinterpret_cast<sockaddr *>(&client_addr), &client_size);
            if (numberOfBytes == SOCKET_ERROR) {
                error_code = WSAGetLastError();
            } else {
                if (!inet_ntop(AF_INET,
                               &client_addr.sin_addr,
                               clientIP.data(),
                               INET_ADDRSTRLEN)) {
                    error_code = WSAGetLastError();
                }
                clientPort = ntohs(client_addr.sin_port);
            }
            return numberOfBytes;
        }
    }

    int udp_server::write(char *buf, int len,
                          std::string &clientIP,
                          uint16_t &clientPort) {
        if (isIPV6) {
            sockaddr_in6 addr{};
            addr.sin6_family = AF_INET6;
            addr.sin6_port = htons(clientPort);
            if (inet_pton(AF_INET6,
                          clientIP.data(),
                          &addr.sin6_addr) != 1) {
                error_code = WSAGetLastError();
            }
            int numberOfBytes = sendto(server_socket,
                                       buf, len,
                                       0,
                                       reinterpret_cast<sockaddr *>(&addr), sizeof(addr));
            if (numberOfBytes == SOCKET_ERROR) {
                error_code = WSAGetLastError();
            }
            return numberOfBytes;
        } else {
            sockaddr_in addr{};
            addr.sin_family = AF_INET;
            addr.sin_port = htons(clientPort);
            if (inet_pton(AF_INET,
                          clientIP.data(),
                          &addr.sin_addr) != 1) {
                error_code = WSAGetLastError();
            }
            int numberOfBytes = sendto(server_socket,
                                       buf, len,
                                       0,
                                       reinterpret_cast<sockaddr *>(&addr), sizeof(addr));
            if (numberOfBytes == SOCKET_ERROR) {
                error_code = WSAGetLastError();
            }
            return numberOfBytes;
        }
    }

    std::string udp_server::read_string(std::string &clientIP,
                                        uint16_t &clientPort,
                                        int32_t bufferSize) {
        if (bufferSize < 1024) {
            bufferSize = 1024;
        }
        std::string rawData(bufferSize, '\0');
        int bytesRead = read(rawData.data(),
                             bufferSize,
                             clientIP,
                             clientPort);
        if (bytesRead == SOCKET_ERROR) {
            error_code = WSAGetLastError();
            return {};
        }
        rawData.resize(bytesRead);
        rawData.shrink_to_fit();
        return rawData;
    }

    std::wstring udp_server::read_wstring(std::string &clientIP,
                                          uint16_t &clientPort,
                                          int32_t bufferSize) {
        if (bufferSize < 512) {
            bufferSize = 512;
        }
        return helper::convert::str_to_wstr(
            read_string(clientIP, clientPort,
                        static_cast<int32_t>(bufferSize * sizeof(wchar_t))));
    }

    std::string udp_server::read_string_to_end(std::string &clientIP,
                                               uint16_t &clientPort) {
        constexpr DWORD bufferSize = 4096;
        char *buf = new char[bufferSize];
        memset(buf, 0, bufferSize);
        std::string rawData;
        rawData.reserve(bufferSize);
        int bytesRead = 0;
        do {
            bytesRead = read(buf,
                             bufferSize,
                             clientIP,
                             clientPort);
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

    std::wstring udp_server::read_wstring_to_end(std::string &clientIP,
                                                 uint16_t &clientPort) {
        return helper::convert::str_to_wstr(
            read_string_to_end(clientIP, clientPort));
    }

    int udp_server::write_string(std::string &str,
                                 std::string &clientIP,
                                 uint16_t &clientPort) {
        if (str.empty()) {
            return 0;
        }
        return write(str.data(), str.size(), clientIP, clientPort);
    }

    int udp_server::write_wstring(std::wstring &wstr,
                                  std::string &clientIP,
                                  uint16_t &clientPort) {
        if (wstr.empty()) {
            return 0;
        }
        std::string rawData = helper::convert::wstr_to_str(wstr);
        return write_string(rawData, clientIP, clientPort);
    }

    int udp_server::err_code() const {
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
