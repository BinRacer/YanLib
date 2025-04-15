//
// Created by forkernel on 2025/4/5.
//

#ifndef CONVERT_H
#define CONVERT_H
#include <Windows.h>
#include <string>

namespace YanLib::helper {
    class convert {
    public:
        convert(const convert &other) = delete;

        convert(convert &&other) = delete;

        convert &operator=(const convert &other) = delete;

        convert &operator=(convert &&other) = delete;

        convert() = delete;

        ~convert() = delete;

        static std::wstring str_to_wstr(const std::string &str,
                                        UINT code_page = CP_UTF8);

        static std::string wstr_to_str(const std::wstring &wstr,
                                       UINT code_page = CP_UTF8);

        static std::string err_string(DWORD error_code);

        static std::wstring err_wstring(DWORD error_code);
    };
}
#endif //CONVERT_H
