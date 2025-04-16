//
// Created by forkernel on 2025/4/5.
//

#include "udp_client.h"
#include <ws2tcpip.h>
#include "helper/convert.h"

namespace YanLib::io {
    udp_client::udp_client(bool activeIpV6) {
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
        } while (false);
    }

    udp_client::~udp_client() {
        closesocket(client_socket);
        WSACleanup();
    }

    int udp_client::read(char *buf, int len,
                         int flags,
                         sockaddr *from, int *fromlen) {
        int numberOfBytes = recvfrom(client_socket,
                                     buf, len,
                                     flags,
                                     from, fromlen);
        if (numberOfBytes == SOCKET_ERROR) {
            error_code = WSAGetLastError();
        }
        return numberOfBytes;
    }

    int udp_client::write(const char *buf, int len,
                          int flags,
                          const sockaddr *to, int tolen) {
        int numberOfBytes = sendto(client_socket,
                                   buf, len,
                                   flags,
                                   to, tolen);
        if (numberOfBytes == SOCKET_ERROR) {
            error_code = WSAGetLastError();
        }
        return numberOfBytes;
    }

    int udp_client::read(char *buf, int len,
                         std::string &remoteIP, uint16_t &remotePort) {
        if (isIPV6) {
            sockaddr_in6 client_addr{};
            int client_size = sizeof (client_addr);
            int numberOfBytes = recvfrom(client_socket,
                                         buf, len,
                                         0,
                                         reinterpret_cast<sockaddr *>(&client_addr),
                                         &client_size);
            if (numberOfBytes == SOCKET_ERROR) {
                error_code = WSAGetLastError();
            } else {
                if (!inet_ntop(AF_INET6,
                               &client_addr.sin6_addr,
                               remoteIP.data(),
                               INET6_ADDRSTRLEN)) {
                    error_code = WSAGetLastError();
                }
                remotePort = ntohs(client_addr.sin6_port);
            }
            return numberOfBytes;
        } else {
            sockaddr_in client_addr{};
            int client_size = sizeof (client_addr);
            int numberOfBytes = recvfrom(client_socket,
                                         buf, len,
                                         0,
                                         reinterpret_cast<sockaddr *>(&client_addr),
                                         &client_size);
            if (numberOfBytes == SOCKET_ERROR) {
                error_code = WSAGetLastError();
            } else {
                if (!inet_ntop(AF_INET,
                               &client_addr.sin_addr,
                               remoteIP.data(),
                               INET_ADDRSTRLEN)) {
                    error_code = WSAGetLastError();
                }
                remotePort = ntohs(client_addr.sin_port);
            }
            return numberOfBytes;
        }
    }

    int udp_client::write(char *buf, int len,
                          std::string &remoteIP, uint16_t &remotePort) {
        if (isIPV6) {
            sockaddr_in6 addr{};
            addr.sin6_family = AF_INET6;
            addr.sin6_port = htons(remotePort);
            if (inet_pton(AF_INET6,
                          remoteIP.data(),
                          &addr.sin6_addr) != 1) {
                error_code = WSAGetLastError();
            }
            int numberOfBytes = sendto(client_socket,
                                       buf, len,
                                       0,
                                       reinterpret_cast<sockaddr *>(&addr),
                                       sizeof(addr));
            if (numberOfBytes == SOCKET_ERROR) {
                error_code = WSAGetLastError();
            }
            return numberOfBytes;
        } else {
            sockaddr_in addr{};
            addr.sin_family = AF_INET;
            addr.sin_port = htons(remotePort);
            if (inet_pton(AF_INET,
                          remoteIP.data(),
                          &addr.sin_addr) != 1) {
                error_code = WSAGetLastError();
            }
            int numberOfBytes = sendto(client_socket,
                                       buf, len,
                                       0,
                                       reinterpret_cast<sockaddr *>(&addr),
                                       sizeof(addr));
            if (numberOfBytes == SOCKET_ERROR) {
                error_code = WSAGetLastError();
            }
            return numberOfBytes;
        }
    }

    std::string udp_client::read_string(std::string &remoteIP,
                                        uint16_t &remotePort,
                                        int32_t bufferSize) {
        if (bufferSize < 1024) {
            bufferSize = 1024;
        }
        std::string rawData(bufferSize, '\0');
        int bytesRead = read(rawData.data(), bufferSize, remoteIP, remotePort);
        if (bytesRead == SOCKET_ERROR) {
            error_code = WSAGetLastError();
            return {};
        }
        rawData.resize(bytesRead);
        rawData.shrink_to_fit();
        return rawData;
    }

    std::wstring udp_client::read_wstring(std::string &remoteIP,
                                          uint16_t &remotePort,
                                          int32_t bufferSize) {
        if (bufferSize < 512) {
            bufferSize = 512;
        }
        return helper::convert::str_to_wstr(
            read_string(remoteIP, remotePort,
                        static_cast<int32_t>(bufferSize * sizeof(wchar_t))));
    }

    std::string udp_client::read_string_to_end(std::string &remoteIP,
                                               uint16_t &remotePort) {
        constexpr DWORD bufferSize = 4096;
        char *buf = new char[bufferSize];
        memset(buf, 0, bufferSize);
        std::string rawData;
        rawData.reserve(bufferSize);
        int bytesRead = 0;
        do {
            bytesRead = read(buf, bufferSize, remoteIP, remotePort);
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

    std::wstring udp_client::read_wstring_to_end(std::string &remoteIP,
                                                 uint16_t &remotePort) {
        return helper::convert::str_to_wstr(
            read_string_to_end(remoteIP, remotePort));
    }

    int udp_client::write_string(std::string &str,
                                 std::string &remoteIP, uint16_t &remotePort) {
        if (str.empty()) {
            return 0;
        }
        return write(str.data(), str.size(), remoteIP, remotePort);
    }

    int udp_client::write_wstring(std::wstring &wstr,
                                  std::string &remoteIP, uint16_t &remotePort) {
        if (wstr.empty()) {
            return 0;
        }
        std::string rawData = helper::convert::wstr_to_str(wstr);
        return write_string(rawData, remoteIP, remotePort);
    }

    int udp_client::err_code() const {
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
