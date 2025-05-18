//
// Created by forkernel on 2025/4/14.
//

#include "string.h"
#include <algorithm>
#include <cwctype>

namespace YanLib::helper {
    bool string::strstri(const std::wstring &text, const std::wstring &substr) {
        if (substr.empty())
            return false;
        if (text.empty())
            return false;

        auto case_insensitive_compare = [](wchar_t a, wchar_t b) -> bool {
            return std::towlower(a) == std::towlower(b);
        };
        const auto it = std::search(text.begin(), text.end(), substr.begin(),
                                    substr.end(), case_insensitive_compare);
        return it != text.end();
    }

    bool string::strstri(const wchar_t* text, const wchar_t* substr) {
        if (!text || !substr || wcslen(text) == 0 || wcslen(substr) == 0)
            return false;

        auto case_insensitive_compare = [](wchar_t a, wchar_t b) -> bool {
            return std::towlower(a) == std::towlower(b);
        };

        const wchar_t* result =
                std::search(text, text + wcslen(text), substr,
                            substr + wcslen(substr), case_insensitive_compare);

        return *result ? true : false;
    }
} // namespace YanLib::helper
