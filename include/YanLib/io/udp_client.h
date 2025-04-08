//
// Created by forkernel on 2025/4/5.
//

#ifndef UDP_CLIENT_H
#define UDP_CLIENT_H

#include <winsock2.h>
#include <string>

#pragma comment(lib, "ws2_32.lib")
namespace YanLib {
    namespace io {
        class udp_client {
        public:
            udp_client(const udp_client &other) = delete;

            udp_client(udp_client &&other) = delete;

            udp_client &operator=(const udp_client &other) = delete;

            udp_client &operator=(udp_client &&other) = delete;

            explicit udp_client(bool activeIpV6 = false);

            ~udp_client();

            int read(char *buf, int len,
                     int flags,
                     sockaddr *from, int *fromlen);

            int write(const char *buf, int len,
                      int flags,
                      const sockaddr *to, int tolen);

            int read(char *buf, int len,
                     std::string &remoteIP, unsigned short &remotePort);

            int write(char *buf, int len,
                      std::string &remoteIP, unsigned short &remotePort);

            std::string read_string(std::string &remoteIP,
                                    unsigned short &remotePort,
                                    int32_t bufferSize = 1024);

            std::wstring read_wstring(std::string &remoteIP,
                                      unsigned short &remotePort,
                                      int32_t bufferSize = 512);

            std::string read_string_to_end(std::string &remoteIP,
                                           unsigned short &remotePort);

            std::wstring read_wstring_to_end(std::string &remoteIP,
                                             unsigned short &remotePort);

            int write_string(std::string &str,
                             std::string &remoteIP, unsigned short &remotePort);

            int write_wstring(std::wstring &wstr,
                              std::string &remoteIP, unsigned short &remotePort);

            int err_code() const;

            std::string err_string() const;

            std::wstring err_wstring() const;
        };
    }
}
#endif //UDP_CLIENT_H
