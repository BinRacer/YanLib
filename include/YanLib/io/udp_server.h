//
// Created by forkernel on 2025/4/5.
//

#ifndef UDP_SERVER_H
#define UDP_SERVER_H
#include <winsock2.h>
#include <string>

#pragma comment(lib, "ws2_32.lib")
namespace YanLib {
    namespace io {
        class udp_server {
        public:
            udp_server(const udp_server &other) = delete;

            udp_server(udp_server &&other) = delete;

            udp_server &operator=(const udp_server &other) = delete;

            udp_server &operator=(udp_server &&other) = delete;

            explicit udp_server(bool activeIpV6 = false);

            ~udp_server();

            bool bind(const char *localIP = "0.0.0.0",
                      unsigned short localPort = 8080);

            int read(char *buf, int len,
                     int flags,
                     sockaddr *from, int *fromlen);

            int write(const char *buf, int len,
                      int flags,
                      const sockaddr *to, int tolen);

            int read(char *buf, int len,
                     std::string &clientIP, unsigned short &clientPort);

            int write(char *buf, int len,
                      std::string &clientIP, unsigned short &clientPort);

            std::string read_string(std::string &clientIP,
                                    unsigned short &clientPort,
                                    int32_t bufferSize = 1024);

            std::wstring read_wstring(std::string &clientIP,
                                      unsigned short &clientPort,
                                      int32_t bufferSize = 512);

            std::string read_string_to_end(std::string &clientIP,
                                           unsigned short &clientPort);

            std::wstring read_wstring_to_end(std::string &clientIP,
                                             unsigned short &clientPort);

            int write_string(std::string &str, std::string &clientIP,
                             unsigned short &clientPort);

            int write_wstring(std::wstring &wstr, std::string &clientIP,
                              unsigned short &clientPort);

            int err_code() const;

            std::string err_string() const;

            std::wstring err_wstring() const;
        };
    }
}

#endif //UDP_SERVER_H
