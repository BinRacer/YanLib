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

namespace YanLib::io {
    class ftp {
    private:
        std::vector<HINTERNET> files{};
        HINTERNET internet_handle = nullptr;
        HINTERNET session_read_handle = nullptr;
        HINTERNET session_upload_handle = nullptr;
        std::wstring url;
        URL_COMPONENTSW uc = {};
        wchar_t scheme[16] = {};
        wchar_t _hostname[128] = {};
        wchar_t _username[32] = {};
        wchar_t _password[32] = {};
        wchar_t urlpath[512] = {};
        wchar_t extra_info[256] = {};
        uint16_t _port = 0;
        DWORD error_code = 0;

    public:
        ftp(const ftp &other) = delete;

        ftp(ftp &&other) = delete;

        ftp &operator=(const ftp &other) = delete;

        ftp &operator=(ftp &&other) = delete;

        ftp() = delete;

        explicit ftp(const std::wstring &input_url);

        explicit ftp(const std::wstring &ip,
                     const uint16_t &port,
                     const std::wstring &username = {},
                     const std::wstring &password = {});

        ~ftp();

        bool url_crack(DWORD flag = ICU_DECODE | ICU_ESCAPE);

        bool open(const wchar_t *agent_name = L"MiniFTP/0.1",
                  DWORD access_type = INTERNET_OPEN_TYPE_PRECONFIG,
                  const wchar_t *proxy = nullptr,
                  const wchar_t *proxy_bypass = nullptr,
                  DWORD flag = 0);

        bool connect(DWORD service = INTERNET_SERVICE_FTP,
                     DWORD flag = INTERNET_FLAG_PASSIVE,
                     DWORD_PTR context = 0);

        HINTERNET open_file(const wchar_t *file_name,
                            DWORD access = GENERIC_READ,
                            DWORD flag = FTP_TRANSFER_TYPE_BINARY |
                                         INTERNET_FLAG_RELOAD |
                                         INTERNET_FLAG_TRANSFER_BINARY,
                            DWORD_PTR context = 0);

        HINTERNET create_file(const wchar_t *file_name,
                              DWORD access = GENERIC_WRITE,
                              DWORD flag = FTP_TRANSFER_TYPE_BINARY |
                                           INTERNET_FLAG_RELOAD |
                                           INTERNET_FLAG_TRANSFER_BINARY,
                              DWORD_PTR context = 0);

        bool read(HINTERNET file_handle,
                  void* buf,
                  DWORD size,
                  DWORD* ret_size);

        std::vector<uint8_t> read_bytes(HINTERNET file_handle,
                                        int32_t buffer_size = 1024);

        bool write(HINTERNET file_handle,
                   const void* buf,
                   DWORD size,
                   DWORD* ret_size);

        DWORD write_bytes(HINTERNET file_handle, std::vector<uint8_t> &vec);

        int64_t size(HINTERNET file_handle);

        std::wstring pwd();

        bool cd(const wchar_t *dir);

        bool ls(std::vector<std::wstring> &files,
                std::vector<std::wstring> &dirs);

        bool ls_full_path(std::vector<std::wstring> &files,
                          std::vector<std::wstring> &dirs);


        bool mkdir(const wchar_t *dir);

        bool rmdir(const wchar_t *dir);

        bool rm(const wchar_t *file_name);

        bool rename(const wchar_t *existing_name, const wchar_t *new_name);

        std::vector<uint8_t> command(const wchar_t *command);

        bool download(const wchar_t *remote_file,
                      const wchar_t *new_file,
                      bool is_fail_if_exists = false,
                      DWORD flags_and_attrs = FILE_ATTRIBUTE_NORMAL,
                      DWORD flag = FTP_TRANSFER_TYPE_BINARY |
                                   INTERNET_FLAG_RELOAD |
                                   INTERNET_FLAG_TRANSFER_BINARY,
                      DWORD_PTR context = 0);

        bool upload(const wchar_t *local_file,
                    const wchar_t *new_remote_file,
                    DWORD flag = FTP_TRANSFER_TYPE_BINARY |
                                 INTERNET_FLAG_RELOAD |
                                 INTERNET_FLAG_TRANSFER_BINARY,
                    DWORD_PTR context = 0);

        DWORD download2(HINTERNET remote_file,
                        const wchar_t *local_file);

        DWORD upload2(HINTERNET remote_file,
                      const wchar_t *local_file);

        [[nodiscard]] DWORD err_code() const;

        [[nodiscard]] std::string err_string() const;

        [[nodiscard]] std::wstring err_wstring() const;
    };
}
#endif //FTP_H
