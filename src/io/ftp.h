//
// Created by forkernel on 2025/4/6.
//

#ifndef FTP_H
#define FTP_H
#include <Windows.h>
#include <WinInet.h>
#include <string>
#include <vector>
#pragma comment(lib, "WinInet.lib")

namespace YanLib {
    namespace io {
        class ftp {
        private:
            std::vector<HINTERNET> files{};
            HINTERNET hInternet = nullptr;
            HINTERNET hSessionRead = nullptr;
            HINTERNET hSessionUpload = nullptr;
            std::wstring url;
            URL_COMPONENTSW uc = {};
            wchar_t scheme[16] = {};
            wchar_t _hostname[128] = {};
            wchar_t _username[32] = {};
            wchar_t _password[32] = {};
            wchar_t urlpath[512] = {};
            wchar_t extra_info[256] = {};
            unsigned short _port = 0;
            DWORD error_code = 0;

        public:
            ftp(const ftp &other) = delete;

            ftp(ftp &&other) = delete;

            ftp &operator=(const ftp &other) = delete;

            ftp &operator=(ftp &&other) = delete;

            ftp() = delete;

            explicit ftp(const std::wstring &input_url);

            explicit ftp(const std::wstring &ip,
                         const unsigned short &port,
                         const std::wstring &username = nullptr,
                         const std::wstring &password = nullptr);

            ~ftp();

            bool url_crack(DWORD dwFlags = ICU_DECODE | ICU_ESCAPE);

            bool open(const wchar_t *lpszAgent = L"MiniFTP/0.1",
                      DWORD dwAccessType = INTERNET_OPEN_TYPE_PRECONFIG,
                      const wchar_t *lpszProxy = nullptr,
                      const wchar_t *lpszProxyBypass = nullptr,
                      DWORD dwFlags = 0);

            bool connect(DWORD dwService = INTERNET_SERVICE_FTP,
                         DWORD dwFlags = INTERNET_FLAG_PASSIVE,
                         DWORD_PTR dwContext = 0);

            HINTERNET open_file(const wchar_t *lpszFileName,
                                DWORD dwAccess = GENERIC_READ,
                                DWORD dwFlags = FTP_TRANSFER_TYPE_BINARY |
                                                INTERNET_FLAG_RELOAD |
                                                INTERNET_FLAG_TRANSFER_BINARY,
                                DWORD_PTR dwContext = 0);

            HINTERNET create_file(const wchar_t *lpszFileName,
                                  DWORD dwAccess = GENERIC_WRITE,
                                  DWORD dwFlags = FTP_TRANSFER_TYPE_BINARY |
                                                  INTERNET_FLAG_RELOAD |
                                                  INTERNET_FLAG_TRANSFER_BINARY,
                                  DWORD_PTR dwContext = 0);

            bool read(HINTERNET hFile,
                      LPVOID lpBuffer,
                      DWORD dwNumberOfBytesToRead,
                      LPDWORD lpdwNumberOfBytesRead);

            std::vector<unsigned char> read_bytes(HINTERNET hFile,
                                                  int32_t bufferSize = 1024);

            bool write(HINTERNET hFile,
                       LPCVOID lpBuffer,
                       DWORD dwNumberOfBytesToWrite,
                       LPDWORD lpdwNumberOfBytesWritten);

            DWORD write_bytes(HINTERNET hFile, std::vector<unsigned char> &vec);

            int64_t size(HINTERNET hFile);

            std::wstring pwd();

            bool cd(const wchar_t *lpszDirectory);

            bool ls(std::vector<std::wstring> &files,
                    std::vector<std::wstring> &dirs);

            bool ls_full_path(std::vector<std::wstring> &files,
                              std::vector<std::wstring> &dirs);


            bool mkdir(const wchar_t *lpszDirectory);

            bool rmdir(const wchar_t *lpszDirectory);

            bool rm(const wchar_t *lpszFileName);

            bool rename(const wchar_t *lpszExisting, const wchar_t *lpszNew);

            std::vector<unsigned char> command(const wchar_t *lpszCommand);

            bool download(const wchar_t *lpszRemoteFile,
                          const wchar_t *lpszNewFile,
                          BOOL fFailIfExists = FALSE,
                          DWORD dwFlagsAndAttributes = FILE_ATTRIBUTE_NORMAL,
                          DWORD dwFlags = FTP_TRANSFER_TYPE_BINARY |
                                          INTERNET_FLAG_RELOAD |
                                          INTERNET_FLAG_TRANSFER_BINARY,
                          DWORD_PTR dwContext = 0);

            bool upload(const wchar_t *lpszLocalFile,
                        const wchar_t *lpszNewRemoteFile,
                        DWORD dwFlags = FTP_TRANSFER_TYPE_BINARY |
                                        INTERNET_FLAG_RELOAD |
                                        INTERNET_FLAG_TRANSFER_BINARY,
                        DWORD_PTR dwContext = 0);

            DWORD download2(HINTERNET remote_file,
                            const wchar_t *local_file);

            DWORD upload2(HINTERNET remote_file,
                          const wchar_t *local_file);

            DWORD err_code() const;

            std::string err_string() const;

            std::wstring err_wstring() const;
        };
    }
}

#endif //FTP_H
