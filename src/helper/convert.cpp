//
// Created by forkernel on 2025/4/5.
//

#include "convert.h"

namespace YanLib::helper {
    std::wstring convert::str_to_wstr(const std::string &str, UINT code_page) {
        int len = MultiByteToWideChar(code_page,
                                      0,
                                      str.data(),
                                      -1,
                                      nullptr,
                                      0);
        if (len <= 0) return {};
        std::wstring wstr(len, 0);
        MultiByteToWideChar(code_page,
                            0,
                            str.data(),
                            -1, &wstr[0],
                            len);
        wstr.resize(len - 1);
        wstr.shrink_to_fit();
        return wstr;
    }

    std::string convert::wstr_to_str(const std::wstring &wstr, UINT code_page) {
        int len = WideCharToMultiByte(code_page,
                                      0,
                                      wstr.data(),
                                      -1,
                                      nullptr,
                                      0,
                                      nullptr,
                                      nullptr);
        if (len <= 0) return {};
        std::string str(len, 0);
        WideCharToMultiByte(code_page,
                            0,
                            wstr.data(),
                            -1,
                            &str[0],
                            len,
                            nullptr,
                            nullptr);
        str.resize(len - 1);
        str.shrink_to_fit();
        return str;
    }

    std::string convert::err_string(DWORD error_code) {
        std::string result = wstr_to_str(err_wstring(error_code));
        return result;
    }

    std::wstring convert::err_wstring(DWORD error_code) {
        std::wstring result;
        HLOCAL hlocal = nullptr;
        DWORD system_locale = MAKELANGID(LANG_NEUTRAL, SUBLANG_NEUTRAL);
        DWORD is_ok = FormatMessageW(
            FORMAT_MESSAGE_FROM_SYSTEM |
            FORMAT_MESSAGE_IGNORE_INSERTS |
            FORMAT_MESSAGE_ALLOCATE_BUFFER,
            nullptr,
            error_code,
            system_locale,
            reinterpret_cast<wchar_t *>(&hlocal),
            0,
            nullptr);
        if (!is_ok) {
            // Is it a network-related error?
            const HMODULE module_handle = LoadLibraryExW(
                L"netmsg.dll",
                nullptr,
                DONT_RESOLVE_DLL_REFERENCES);

            if (module_handle != nullptr) {
                is_ok = FormatMessageW(
                    FORMAT_MESSAGE_FROM_HMODULE |
                    FORMAT_MESSAGE_IGNORE_INSERTS |
                    FORMAT_MESSAGE_ALLOCATE_BUFFER,
                    module_handle,
                    error_code,
                    system_locale,
                    reinterpret_cast<wchar_t *>(&hlocal),
                    0,
                    nullptr);
                FreeLibrary(module_handle);
            }
        }

        if (is_ok && (hlocal != nullptr)) {
            result = static_cast<wchar_t *>(LocalLock(hlocal));
            LocalFree(hlocal);
        }
        return result;
    }
}
