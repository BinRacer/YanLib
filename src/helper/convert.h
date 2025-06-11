/* clang-format off */
/*
 * @file convert.h
 * @date 2025-04-05
 * @license MIT License
 *
 * Copyright (c) 2025 BinRacer <native.lab@outlook.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
/* clang-format on */
#ifndef CONVERT_H
#define CONVERT_H
#include <Windows.h>
#include <string>

namespace YanLib::helper {
#ifndef CODEPAGE
#define CODEPAGE

    enum class CodePage : uint32_t {
        // ======================
        // Windows System Code Pages
        // ======================
        A_CP = 0,        // Default ANSI code page
        OEM_CP = 1,      // Default OEM code page
        MAC_CP = 2,      // Default MAC code page
        THREAD_A_CP = 3, // Current thread's ANSI code page
        SYMBOL = 42,     // Symbol translations

        // ======================
        // Chinese Encodings
        // ======================
        GB2312 = 936,           // Simplified Chinese (ANSI/OEM)
        GB18030 = 54936,        // Chinese National Standard Extension
        BIG5 = 950,             // Traditional Chinese (Big5)
        X_CHINESE_CNS = 20000,  // CNS 11643 (Taiwan)
        X_CP20001 = 20001,      // TCA Taiwan
        X_CHINESE_ETEN = 20002, // ETEN Extended
        X_CP20003 = 20003,      // IBM 5550 Taiwan
        X_CP20004 = 20004,      // Teletext Taiwan
        X_CP20005 = 20005,      // Wang Taiwan
        HZ_GB2312 = 52936,      // HZ-GB2312 Simplified Chinese

        // ======================
        // Unicode Standards
        // ======================
        UTF16_LE = 1200, // UTF-16 Little Endian
        UTF16_BE = 1201, // UTF-16 Big Endian
        UTF32_LE = 12000,
        UTF32_BE = 12001,
        UTF7 = 65000,
        UTF8 = 65001,

        // ======================
        // Windows Code Pages
        // ======================
        WIN1250 = 1250, // Central European
        WIN1251 = 1251, // Cyrillic
        WIN1252 = 1252, // Western European
        WIN1253 = 1253, // Greek
        WIN1254 = 1254, // Turkish
        WIN1255 = 1255, // Hebrew
        WIN1256 = 1256, // Arabic
        WIN1257 = 1257, // Baltic
        WIN1258 = 1258, // Vietnamese

        // ======================
        // ISO Standards
        // ======================
        ISO88591 = 28591,  // Latin-1 (Western European)
        ISO88592 = 28592,  // Latin-2 (Central European)
        ISO88593 = 28593,  // Latin-3 (South European)
        ISO88594 = 28594,  // Latin-4 (Baltic)
        ISO88595 = 28595,  // Cyrillic
        ISO88596 = 28596,  // Arabic
        ISO88597 = 28597,  // Greek
        ISO88598 = 28598,  // Hebrew (Visual)
        ISO88599 = 28599,  // Turkish
        ISO885913 = 28603, // Estonian
        ISO885915 = 28605, // Latin-9

        // ======================
        // IBM EBCDIC Encodings
        // ======================
        IBM037 = 37,    // US-Canada (EBCDIC)
        IBM500 = 500,   // International EBCDIC
        IBM1026 = 1026, // Turkish EBCDIC
        IBM1140 = 1140, // US-Canada (Euro Extended)
        IBM1141 = 1141, // Germany (Euro Extended)
        IBM1142 = 1142, // Denmark-Norway (Euro Extended)
        IBM1143 = 1143, // Finland-Sweden (Euro Extended)
        IBM1144 = 1144, // Italy (Euro Extended)
        IBM1145 = 1145, // Spain (Euro Extended)
        IBM1146 = 1146, // UK (Euro Extended)
        IBM1147 = 1147, // France (Euro Extended)
        IBM1148 = 1148, // International (Euro Extended)
        IBM1149 = 1149, // Icelandic (Euro Extended)

        // ======================
        // OEM Encodings
        // ======================
        IBM437 = 437,   // United States (OEM)
        IBM720 = 720,   // Arabic (Transparent ASMO)
        IBM737 = 737,   // Greek (OEM)
        IBM775 = 775,   // Baltic (OEM)
        IBM850 = 850,   // Latin-1 (Multilingual)
        IBM852 = 852,   // Latin-2 (Central European)
        IBM855 = 855,   // Cyrillic (OEM)
        IBM857 = 857,   // Turkish (OEM)
        IBM00858 = 858, // Latin-1 + Euro Symbol
        IBM860 = 860,   // Portuguese (OEM)
        IBM861 = 861,   // Icelandic (OEM)
        IBM863 = 863,   // Canadian French (OEM)
        IBM864 = 864,   // Arabic (OEM)
        IBM865 = 865,   // Nordic (OEM)
        IBM866 = 866,   // Cyrillic (Russian OEM)
        IBM869 = 869,   // Modern Greek (OEM)

        // ======================
        // Other Significant Encodings
        // ======================
        JOHAB = 1361,             // Korean Johab
        MAC_ROMAN = 10000,        // Western European (Mac)
        X_MAC_JAPANESE = 10001,   // Japanese (Mac)
        X_MAC_CYRILLIC = 10007,   // Cyrillic (Mac)
        X_ISCII_GUJARATI = 57011, // ISCII Gujarati
        EUC_JP = 20932,           // Japanese EUC
    };
    inline CodePage curr_code_page() {
        return static_cast<CodePage>(GetKBCodePage());
    }
#endif

    class convert {
    public:
        convert(const convert &other) = delete;

        convert(convert &&other) = delete;

        convert &operator=(const convert &other) = delete;

        convert &operator=(convert &&other) = delete;

        convert() = delete;

        ~convert() = delete;

        static std::wstring str_to_wstr(const std::string &str,
                                        CodePage code_page = curr_code_page());

        static std::string wstr_to_str(const std::wstring &wstr,
                                       CodePage code_page = curr_code_page());

        static std::string err_string(uint32_t error_code);

        static std::wstring err_wstring(uint32_t error_code);
    };
} // namespace YanLib::helper
#endif // CONVERT_H
