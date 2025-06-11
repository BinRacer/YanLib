//
// Created by BinRacer <native.lab@outlook.com> on 2025/4/14.
//

#ifndef STRING_H
#define STRING_H
#include <string>

namespace YanLib::helper {
    class string {
    public:
        string(const string &other) = delete;

        string(string &&other) = delete;

        string &operator=(const string &other) = delete;

        string &operator=(string &&other) = delete;

        string() = delete;

        ~string() = delete;

        static bool strstri(const std::wstring &text,
                            const std::wstring &substr);

        static bool strstri(const wchar_t *text, const wchar_t *substr);
    };
} // namespace YanLib::helper

#endif // STRING_H
